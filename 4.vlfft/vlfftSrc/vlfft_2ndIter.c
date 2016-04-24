/*
 * VLFFT_2ndIter( )
 *
 *    2nd iteration of computation for multicore FFT
 *
 * Copyright (C) {YEAR} Texas Instruments Incorporated - http://www.ti.com/
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




extern unsigned char brev[];

void transpose_1( float *pIn, float *pOut, Int32 rows, Int32 cols );

#if ENABLE_BENCHMARKING
extern unsigned long long global_timer_dmaWait_2nd;
extern unsigned long long global_timer_fft_2nd;
extern unsigned long long global_timer_transpose0_2nd;
extern unsigned long long global_timer_transpose1_2nd;
#endif

Uint32 debugBufAddr[16];
Uint32 debugBufAddrIndex=0;

float debugBufData[16];
Uint32 debugBufDataIndex=0;


void VLFFT_2ndIter( float          *pIn,
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

	float            *ptrInDDR, *ptrOutDDR;
	float            *pInBufInternal, *pOutBufInternal, *pWorkBuf0Internal;
	float            *pfftOut, *pfftIn, *pW2;
	Uint32           fftSize, fftSize2;

	hEdma = DMAparams->hEdma;

	pInBufInternal = VLFFTbuffers->pInBufInternal;
	pOutBufInternal = VLFFTbuffers->pOutBufInternal;
	pWorkBuf0Internal = VLFFTbuffers->pWorkBuf0Internal;
	fftSize  = VLFFTparams->N2;
	fftSize2 = VLFFTparams->N2*2;
	pW2 = VLFFTparams->pW2;

	inIndex  = 0;
	outIndex = 0;
	stepInSrc  = (Uint32)(VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE);
	stepInDst  = (Uint32)(VLFFTparams->N2*SAMPLES_PER_TRANSFER_BLOCK*BYTES_PER_COMPLEX_SAMPLE);
	stepOutSrc = (Uint32)(VLFFTparams->N2*SAMPLES_PER_TRANSFER_BLOCK*BYTES_PER_COMPLEX_SAMPLE);
	stepOutDst = (Uint32)(VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE);
	numBlks = VLFFTparams->numBlocksPerCore2ndIter;

	ptrInDDR  = pIn;
	ptrOutDDR = pOut;
	/***********************/
	/* Trigger DMA channel */
	/***********************/

	// configure in pong buffer
	srcAddr = (Uint32)ptrInDDR + VLFFTparams->offset2ndIterIn;
	dstAddr = (Uint32)pInBufInternal + DMAparams->globalAddrOffset;
	vlfftEdmaConfig_srcAddrdstAddr( hEdma, &DMAparams->paramSet0, DMAparams->chId0, srcAddr, dstAddr );
	inIndex += 1;

	srcAddr = (Uint32)pWorkBuf0Internal + DMAparams->globalAddrOffset;
	dstAddr = (Uint32)ptrOutDDR;
	vlfftEdmaConfig_srcAddrdstAddr( hEdma, &DMAparams->paramSet1, DMAparams->chId1, srcAddr, dstAddr );

	edmaTrigger( hEdma, DMAparams->chId0 );
	edmaPoll(    hEdma, DMAparams->tcc1  );



	for(blkIdx = 0; blkIdx<numBlks; blkIdx++) {

		/***********************************************/
		/* configure: in pong buffer, out pong buffer  */
		/***********************************************/
		// configure in Channel
		tempIndex = inIndex;
		if( inIndex>= numBlks ) tempIndex = numBlks-1;

		srcInAddr = (Uint32)ptrInDDR + VLFFTparams->offset2ndIterIn  + stepInSrc*tempIndex;
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
		aCnt = DMAparams->aCntOutput_2ndIter;
		bCnt = DMAparams->bCntOutput_2ndIter;
		cCnt = DMAparams->cCntOutput_2ndIter;
		if( blkIdx < 1) {
			aCnt = 4;
			bCnt = 1;
			cCnt = 1;
		}
		srcOutAddr = (Uint32)pOutBufInternal + stepOutSrc*(outIndex&0x1) + DMAparams->globalAddrOffset;
		dstOutAddr = (Uint32)ptrOutDDR + VLFFTparams->offset2ndIterOut + stepOutDst*outIndex;

		vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt( hEdma, &DMAparams->paramSet1, DMAparams->chId1, srcOutAddr, dstOutAddr, aCnt, bCnt, cCnt );
		edmaTrigger( hEdma, DMAparams->chId0 );


		/***********************************************************/
		/*                         transpose                       */
		/***********************************************************/
		transpose_1( &pInBufInternal[(stepOutSrc)*(blkIdx&0x1)>>2],
		             &pOutBufInternal[(stepOutSrc*(blkIdx&0x1  ))>>2],
		             VLFFTparams->N2,
		             SAMPLES_PER_TRANSFER_BLOCK );

		pfftOut = pWorkBuf0Internal;
		pfftIn  = &pOutBufInternal[(stepOutSrc*(blkIdx&0x1  ))>>2];
		if( VLFFTparams->radix_2ndIter == 4 ) {
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*0], &pW2[0], &pfftOut[fftSize2*0], VLFFTparams->log4N_2ndIter );
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*1], &pW2[0], &pfftOut[fftSize2*1], VLFFTparams->log4N_2ndIter );
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*2], &pW2[0], &pfftOut[fftSize2*2], VLFFTparams->log4N_2ndIter );
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*3], &pW2[0], &pfftOut[fftSize2*3], VLFFTparams->log4N_2ndIter );
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*4], &pW2[0], &pfftOut[fftSize2*4], VLFFTparams->log4N_2ndIter );
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*5], &pW2[0], &pfftOut[fftSize2*5], VLFFTparams->log4N_2ndIter );
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*6], &pW2[0], &pfftOut[fftSize2*6], VLFFTparams->log4N_2ndIter );
			DSPF_sp_radix4_fftSPxSP( fftSize, &pfftIn[fftSize2*7], &pW2[0], &pfftOut[fftSize2*7], VLFFTparams->log4N_2ndIter );
		} else {
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*0], &pW2[0], &pfftOut[fftSize2*0] );
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*1], &pW2[0], &pfftOut[fftSize2*1] );
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*2], &pW2[0], &pfftOut[fftSize2*2] );
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*3], &pW2[0], &pfftOut[fftSize2*3] );
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*4], &pW2[0], &pfftOut[fftSize2*4] );
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*5], &pW2[0], &pfftOut[fftSize2*5] );
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*6], &pW2[0], &pfftOut[fftSize2*6] );
			DSPF_sp_mixedRadix_fftSPxSP( fftSize, &pfftIn[fftSize2*7], &pW2[0], &pfftOut[fftSize2*7] );
		}


		/***********************************************************/
		/*                         transpose                       */
		/***********************************************************/
		transpose_2( pWorkBuf0Internal,
		             &pOutBufInternal[(stepOutSrc*(blkIdx&0x1  ))>>2],
		             SAMPLES_PER_TRANSFER_BLOCK,
		             VLFFTparams->N2 );

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
	dstOutAddr = (Uint32)ptrOutDDR + VLFFTparams->offset2ndIterOut + stepOutDst*outIndex;
	aCnt = DMAparams->aCntOutput_2ndIter;
	bCnt = DMAparams->bCntOutput_2ndIter;
	cCnt = DMAparams->cCntOutput_2ndIter;
	vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt( hEdma, &DMAparams->paramSet1, DMAparams->chId1, srcOutAddr, dstOutAddr, aCnt, bCnt, cCnt );

	edmaTrigger( hEdma, DMAparams->chId0 );
	edmaPoll(    hEdma, DMAparams->tcc1  );

}


