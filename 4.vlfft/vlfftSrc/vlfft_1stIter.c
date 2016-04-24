/*
 * VLFFT_1stIter()
 *
 *    1st iteration computation of multicore FFT
 *
 * Copyright (C) {2011} Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/


#include <xdc/std.h>
#include <string.h>

/*  -----------------------------------XDC.RUNTIME module Headers    */
#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>

/*  ----------------------------------- IPC module Headers           */
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/HeapBufMP.h>
#include <ti/ipc/MultiProc.h>

/*  ----------------------------------- BIOS6 module Headers         */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>


/*  ----------------------------------- To get globals from .cfg Header */
#include <xdc/cfg/global.h>

/* vlfft.h */
#include "../vlfftInc/vlfftDebug.h"
#include "../vlfftInc/vlfftMessgQ.h"
#include "../vlfftInc/vlfft.h"
#include "../vlfftInc/vlfftconfig.h"

extern void vlfftEdmaConfig_srcAddrdstAddr_1( EDMA3_DRV_Handle , EDMA3_DRV_PaRAMRegs*, Uint32 , Uint32 , Uint32 );

//extern unsigned char brev[];

void multTwiddle_vec_sa(   float *pInTwiddle, float wStepRe, float wStepIm, int fftSize, float *pOutTwiddle );
void multTwiddle_vec_1_sa( float *pInTwiddle, float wStepRe, float wStepIm, int fftSize, float *pOutTwiddle );

#if ENABLE_BENCHMARKING
extern unsigned long long global_timer_dmaWait;
extern unsigned long long global_timer_fft;
extern unsigned long long global_timer_transpose;
#endif


void VLFFT_1stIter( float          *pIn,
                    float          *pOut,
                    VLFFTparams_t  *VLFFTparams,
                    VLFFTbuffers_t *VLFFTbuffers,
                    DMAparams_t    *DMAparams,
                    Uint32         coreNum) {
	EDMA3_DRV_Handle hEdma;
	Int              inIndex, outIndex, blkIdx;
	Uint32           numBlks, tempIndex;
	Uint32           aCnt, bCnt, cCnt;
	Uint32           srcAddr, dstAddr;
	Uint32           srcInAddr, dstInAddr;
	Uint32           srcOutAddr,dstOutAddr;
	Uint32           stepInSrc, stepInDst, stepOutSrc, stepOutDst;

	Uint32           fftSize, fftSize2, n2_start;
	float *pW1, *pWorkBuf0Internal, *pOutBufInternal, *pfftOut, *pOutTwiddle, *pTwiddle;

	float            *ptrInDDR, *ptrOutDDR;
	float            *pInBufInternal;
	float            wStepRe, wStepIm;
	int              numFFTs;

	hEdma = DMAparams->hEdma;

	fftSize = VLFFTparams->N1;
	fftSize2= VLFFTparams->N1*2;
	pW1 = VLFFTparams->pW1;

	pInBufInternal = VLFFTbuffers->pInBufInternal;
	pOutBufInternal = VLFFTbuffers->pOutBufInternal;
	pWorkBuf0Internal = VLFFTbuffers->pWorkBuf0Internal;
	pTwiddle = VLFFTparams->pTwiddle;
	numBlks = VLFFTparams->numBlocksPerCore1stIter;


	/******************************************************/
	/*         others misc init                           */
	/******************************************************/
	inIndex  = 0;
	outIndex = 0;
	stepInSrc  = (Uint32)(VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE);
	stepInDst  = (Uint32)(VLFFTparams->N1*SAMPLES_PER_TRANSFER_BLOCK*BYTES_PER_COMPLEX_SAMPLE);
	stepOutSrc = (Uint32)(VLFFTparams->N1*SAMPLES_PER_TRANSFER_BLOCK*BYTES_PER_COMPLEX_SAMPLE);
	stepOutDst = (Uint32)(VLFFTparams->N1*SAMPLES_PER_TRANSFER_BLOCK*BYTES_PER_COMPLEX_SAMPLE);

	ptrInDDR  = pIn;
	ptrOutDDR = pOut;

	/***********************/
	/* Trigger DMA channel */
	/***********************/
	srcAddr = (Uint32)ptrInDDR + VLFFTparams->offset1stIterIn;
	dstAddr = (Uint32)pInBufInternal + DMAparams->globalAddrOffset;
	vlfftEdmaConfig_srcAddrdstAddr_1( hEdma, &DMAparams->paramSet0, DMAparams->chId0, srcAddr, dstAddr );
	inIndex += 1;

	srcAddr = (Uint32)pWorkBuf0Internal + DMAparams->globalAddrOffset;
	dstAddr = (Uint32)ptrOutDDR + VLFFTparams->offset1stIterOut;
	vlfftEdmaConfig_srcAddrdstAddr_1( hEdma, &DMAparams->paramSet1, DMAparams->chId1, srcAddr, dstAddr );

	edmaTrigger( hEdma, DMAparams->chId0 );
	edmaPoll(    hEdma, DMAparams->tcc1  );


	/*********************************************/
	/*   start for for nllks = 8                 */
	/*********************************************/

	n2_start = VLFFTparams->numFFTsPerBlock1stIter*numBlks*coreNum;
	for(blkIdx = 0; blkIdx<numBlks; blkIdx++) {

		/***********************************************/
		/* configure: in pong buffer, out pong buffer  */
		/***********************************************/

		// configure in Channel
		tempIndex = inIndex;
		if( inIndex>= numBlks ) tempIndex = numBlks-1;

		srcInAddr = (Uint32)ptrInDDR + VLFFTparams->offset1stIterIn + stepInSrc*tempIndex;
		dstInAddr = (Uint32)pInBufInternal + stepInDst*(inIndex&0x1) + DMAparams->globalAddrOffset;

		aCnt = DMAparams->paramSet0.aCnt;
		bCnt = DMAparams->paramSet0.bCnt;
		cCnt = DMAparams->paramSet0.cCnt;
		if( blkIdx==(numBlks-1) ) {
			aCnt = 4;
			bCnt = 1;
			cCnt = 1;
		}
		vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt( hEdma, &DMAparams->paramSet0, DMAparams->chId0, srcInAddr, dstInAddr, aCnt, bCnt, cCnt );


		// configure out Channel
		aCnt = DMAparams->aCntOutput_1stIter;
		bCnt = DMAparams->bCntOutput_1stIter;
		cCnt = DMAparams->cCntOutput_1stIter;
		if( blkIdx < 1) {
			aCnt = 4;
			bCnt = 1;
			cCnt = 1;
		}
		srcOutAddr = (Uint32)pOutBufInternal + stepOutSrc*(outIndex&0x1) + DMAparams->globalAddrOffset;
		dstOutAddr = (Uint32)ptrOutDDR + VLFFTparams->offset1stIterOut + stepOutDst*outIndex;

		vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt( hEdma, &DMAparams->paramSet1, DMAparams->chId1, srcOutAddr, dstOutAddr, aCnt, bCnt, cCnt );

		edmaTrigger( hEdma, DMAparams->chId0 );


		/***********************************************************/
		/*                         transpose                       */
		/***********************************************************/
		transpose_1( &pInBufInternal[(stepOutSrc)*(blkIdx&0x1)>>2],
		             &VLFFTbuffers->pWorkBuf0Internal[0],
		             VLFFTparams->N1,
		             SAMPLES_PER_TRANSFER_BLOCK );


		/***********************************************************/
		/*                         compute FFT                     */
		/***********************************************************/
		pfftOut = VLFFTbuffers->pfftOutBuf;
		pOutTwiddle = &pOutBufInternal[(stepOutSrc*(blkIdx&0x1))>>2];
		numFFTs = VLFFTparams->numFFTsPerBlock1stIter;

		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*0], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*0], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*0    ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*0 + 1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*0]);


		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*1], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*1], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*1    ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*1 + 1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*1]);


		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*2], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*2], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*2  ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*2+1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*2]);


		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*3], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*3], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*3  ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*3+1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*3]);


		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*4], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*4], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*4  ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*4+1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*4]);


		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*5], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*5], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*5  ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*5+1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*5]);


		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*6], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*6], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*6  ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*6+1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*6]);


		if( VLFFTparams->radix_1stIter == 4 )
			DSPF_sp_radix4_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*7], &pW1[0], pfftOut, VLFFTparams->log4N_1stIter );
		else
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pWorkBuf0Internal[fftSize2*7], &pW1[0], pfftOut );

		wStepRe = pTwiddle[blkIdx*numFFTs*2 + 2*7  ];
		wStepIm = pTwiddle[blkIdx*numFFTs*2 + 2*7+1];
		multTwiddle_vec_1_sa( pfftOut, wStepRe, wStepIm, fftSize, &pOutTwiddle[fftSize2*7]);

		n2_start += VLFFTparams->numFFTsPerBlock1stIter;

		edmaPoll(    hEdma, DMAparams->tcc1  );

		inIndex += 1;
		outIndex += 1;
		if( blkIdx<1  ) outIndex = 0;

	}

	/***********************************************/
	/* configure: last DMA for output              */
	/***********************************************/

	// configure in Channel
	aCnt = 4;
	bCnt = 1;
	cCnt = 1;
	vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt( hEdma, &DMAparams->paramSet0, DMAparams->chId0, srcInAddr, dstInAddr, aCnt, bCnt, cCnt );


	// configure out Channel
	srcOutAddr = (Uint32)pOutBufInternal + stepOutSrc*(outIndex&0x1) + DMAparams->globalAddrOffset;
	dstOutAddr = (Uint32)ptrOutDDR + VLFFTparams->offset1stIterOut + stepOutDst*outIndex;
	aCnt = DMAparams->aCntOutput_1stIter;
	bCnt = DMAparams->bCntOutput_1stIter;
	cCnt = DMAparams->cCntOutput_1stIter;
	vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt( hEdma, &DMAparams->paramSet1, DMAparams->chId1, srcOutAddr, dstOutAddr, aCnt, bCnt, cCnt );

	edmaTrigger( hEdma, DMAparams->chId0 );
	edmaPoll(    hEdma, DMAparams->tcc1  );

}


