/*
 * vlfft.h
 *
 *   This file contains definitions for multicore FFT implementation
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



#include	<ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>



typedef	struct {
	Int32		instNum;
	Uint32		dmaChannelIn;
	Uint32		dmaChannelOut;
	Int32		intrNum;
	Int32		intrOutNum;
	Uint32		coreNum;
	Uint32		globalAddrOffset;
	Uint32		regionNum;

#if	ENABLE_DMA_TRANSPOSE	||	ENABLE_TRANSPOSE_L1SRAM
	Uint32		dmaChannelTranspose0;
	Uint32		intrNumTranspose0;
	Uint32		indexTranspose0PaRAM;

	Uint32		dmaChannelTranspose1;
	Uint32		intrNumTranspose1;
	Uint32		indexTranspose1PaRAM;
#endif

	Uint32		indexInPaRAM;
	Uint32		indexInPaRAM_Ping;
	Uint32		indexInPaRAM_Pong;

	Uint32		indexOutPaRAM;
	Uint32		indexOutPaRAM_Ping;
	Uint32		indexOutPaRAM_Pong;

	Uint32		dmaInSrcPingBuffAddr;
	Uint32		dmaInSrcPongBuffAddr;
	Uint32		dmaInDstPingBuffAddr;
	Uint32		dmaInDstPongBuffAddr;

	Uint32		dmaOutSrcPingBuffAddr;
	Uint32		dmaOutSrcPongBuffAddr;
	Uint32		dmaOutDstPingBuffAddr;
	Uint32		dmaOutDstPongBuffAddr;

	Uint32		aCntInput_1stIter;
	Uint32		bCntInput_1stIter;
	Uint32		cCntInput_1stIter;
	Uint32		bCntRldInput_1stIter;

	Uint32		aCntOutput_1stIter;
	Uint32		bCntOutput_1stIter;
	Uint32		cCntOutput_1stIter;
	Uint32		bCntRldOutput_1stIter;

#if	ENABLE_DMA_TRANSPOSE || ENABLE_TRANSPOSE_L1SRAM
	Uint32		aCntTranspose0_1stIter;
	Uint32		bCntTranspose0_1stIter;
	Uint32		cCntTranspose0_1stIter;
	Uint32		bCntRldTranspose0_1stIter;
#endif

	Uint32				srcInputBIDX_1stIter;
	Uint32				dstInputBIDX_1stIter;
	Uint32				srcOutputBIDX_1stIter;
	Uint32				dstOutputBIDX_1stIter;

	Uint32				srcInputCIDX_1stIter;
	Uint32				dstInputCIDX_1stIter;
	Uint32				srcOutputCIDX_1stIter;
	Uint32				dstOutputCIDX_1stIter;

#if	ENABLE_DMA_TRANSPOSE	||	ENABLE_TRANSPOSE_L1SRAM
	Uint32				srcTranspose0BIDX_1stIter;
	Uint32				dstTranspose0BIDX_1stIter;
	Uint32				srcTranspose0CIDX_1stIter;
	Uint32				dstTranspose0CIDX_1stIter;
#endif


	Uint32				aCntInput_2ndIter;
	Uint32				bCntInput_2ndIter;
	Uint32				cCntInput_2ndIter;
	Uint32				bCntRldInput_2ndIter;

	Uint32				aCntOutput_2ndIter;
	Uint32				bCntOutput_2ndIter;
	Uint32				cCntOutput_2ndIter;
	Uint32				bCntRldOutput_2ndIter;

#if	ENABLE_DMA_TRANSPOSE || ENABLE_TRANSPOSE_L1SRAM
	Uint32				aCntTranspose0_2ndIter;
	Uint32				bCntTranspose0_2ndIter;
	Uint32				cCntTranspose0_2ndIter;
	Uint32				bCntRldTranspose0_2ndIter;

	Uint32				aCntTranspose1_2ndIter;
	Uint32				bCntTranspose1_2ndIter;
	Uint32				cCntTranspose1_2ndIter;
	Uint32				bCntRldTranspose1_2ndIter;
#endif

	Uint32				srcInputBIDX_2ndIter;
	Uint32				dstInputBIDX_2ndIter;
	Uint32				srcOutputBIDX_2ndIter;
	Uint32				dstOutputBIDX_2ndIter;

#if	ENABLE_DMA_TRANSPOSE || ENABLE_TRANSPOSE_L1SRAM
	Uint32				srcTranspose0BIDX_2ndIter;
	Uint32				dstTranspose0BIDX_2ndIter;
	Uint32				srcTranspose0CIDX_2ndIter;
	Uint32				dstTranspose0CIDX_2ndIter;

	Uint32				srcTranspose1BIDX_2ndIter;
	Uint32				dstTranspose1BIDX_2ndIter;
	Uint32				srcTranspose1CIDX_2ndIter;
	Uint32				dstTranspose1CIDX_2ndIter;
#endif

	Uint32				srcInputCIDX_2ndIter;
	Uint32				dstInputCIDX_2ndIter;
	Uint32				srcOutputCIDX_2ndIter;
	Uint32				dstOutputCIDX_2ndIter;


	EDMA3_DRV_Handle	hEdma;

	EDMA3_DRV_PaRAMRegs	paramSet0;
	EDMA3_DRV_PaRAMRegs	paramSet1;

	Uint32				chId0;
	Uint32				chId1;
	Uint32				tcc0;
	Uint32				tcc1;


}	DMAparams_t;

/****************************************/
/*		N=N1*N2														*/
/*			1st	iteration										*/
/*						compute	N2	FFT	of	size	N1	*/
/*			2nd	iteration										*/
/*						compute	N1	FFT	of	size	N2	*/
/*																			*/
/****************************************/
typedef	struct {
	Uint32				maxNumCores;
	Uint32				numCoresForFftCompute;
	Uint32				log2NumCoresForFftCompute;
	Uint32				radix_1stIter;
	Uint32				log4N_1stIter;
	Uint32				radix_2ndIter;
	Uint32				log4N_2ndIter;

	Uint32				N;
	Uint32				N1;
	Uint32				N2;
	Uint32				samplesPerBlock;

	//	1st	iteration
	Uint32				offset1stIterIn;
	Uint32				step1stIterIn;
	Uint32				offset1stIterOut;
	Uint32				step1stIterOut;

	Uint32				fftSize1stIter;			//	1st	iter	FFT	size	=	N1
	Uint32				numFFTs1stIter;			//	N2
	Uint32				numFFTsPerCore1stIter;//	N2/8
	Uint32				numFFTsPerBlock1stIter;		//	N2/8

	Uint32				numBlocksPerCore1stIter;

	//	2nd	iteration
	Uint32				offset2ndIterIn;
	Uint32				step2ndIterIn;
	Uint32				offset2ndIterOut;
	Uint32				step2ndIterOut;

	Uint32				fftSize2ndIter;					//	2nd	iter	FFT	size	=	N2
	Uint32				numFFTs2ndIter;					//	N2
	Uint32				numFFTsPerCore2ndIter;	//	N2/8
	Uint32				numFFTsPerBlock2ndIter;		//	N2/8

	Uint32				numBlocksPerCore2ndIter;

	float				*pW1;
	float				*pW2;
	float				*pTwiddle;

} VLFFTparams_t;



typedef	struct {

	float					*pInBufInternal;
	float					*pOutBufInternal;
	float					*pWorkBuf0Internal;
	float					*pWorkBuf1Internal;
	float					*pfftInBuf;
	float					*pfftOutBuf;
#if	ENABLE_TRANSPOSE_L1SRAM
	float					*pInBufL1SRAM;
	float					*pOutBufL1SRAM;
#endif
}	VLFFTbuffers_t;

void	vlfftEdmaInit(	DMAparams_t	*DMAparams);
void	vlfftEdmaConfig_1stIter(	DMAparams_t	*DMAparams);
void	vlfftEdmaConfig_2ndIter(	DMAparams_t	*DMAparams);
void	vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt(	EDMA3_DRV_Handle		hEdma,
    EDMA3_DRV_PaRAMRegs	*pParamSet,
    Uint32							chId,
    Uint32							srcAddr,
    Uint32							dstAddr,
    Uint32							aCnt,
    Uint32							bCnt,
    Uint32							cCnt	);
void	vlfftEdmaConfig_srcAddrdstAddr(	EDMA3_DRV_Handle	hEdma,	EDMA3_DRV_PaRAMRegs	*pParamSet,	Uint32	chId,	Uint32	srcAddr,	Uint32	dstAddr	);
void	edmaTrigger(	EDMA3_DRV_Handle	hEdma,	Uint32	chId	);
void	edmaPoll(	EDMA3_DRV_Handle	hEdma,	Uint32	tcc	);

void	genTwiddle(float	*pTwiddle,	int	numFFTsPerCore,	int	coreNum);

void	DSPF_sp_mixedRadix_fftSPxSP(	Uint32	n,	float	*pIn,	float	*pTwiddle,	float	*pOut	);
void	DSPF_sp_radix4_fftSPxSP(	Uint32	n,	float	*pIn,	float	*pTwiddle,	float	*pOut,	Uint32	log4NMinus1	);

void	transpose_1(	float	*pIn,	float	*pOut,	Int32	rows,	Int32	cols	);
void	transpose_2(	float	*pIn,	float	*pOut,	Int32	rows,	Int32	cols	);
void	transpose_2Cols_rowsX8_cplxMatrix_sa	(	float	*pIn,	float	*pOut,	Uint32	rows	);
void	transpose_2Rows_8XCols_cplxMatrix_sa	(	float	*pIn,	float	*pOut,	Uint32	cols	);

void	vlfftParamsInit(VLFFTparams_t	*VLFFTparams,	float	*pW1,	float	*pW2,	float	*pTwiddle,	Uint32	coreNum	);
void	vlfftBuffersInit(	VLFFTbuffers_t	*VLFFTbuffers,
                        float						*pInBufInternal,
                        float						*pOutBufInternal,
                        float						*pWorkBuf0Internal,
                        float						*pfftInBuf,
                        float						*pfftOutBuf
                     );
void	DMAparamInit(	DMAparams_t	*DMAparams,	VLFFTparams_t	*VLFFTparams,	Uint32	coreNum	);
void	dmaConfigVLFFT_1stIter(	DMAparams_t	*DMAparams,	VLFFTparams_t	*VLFFTparams	);
void	dmaConfigVLFFT_2ndIter(	DMAparams_t	*DMAparams,	VLFFTparams_t	*VLFFTparams	);

void	VLFFT_1stIter(	float					*pIn,
                      float					*pOut,
                      VLFFTparams_t	*VLFFTparams,
                      VLFFTbuffers_t	*VLFFTbuffers,
                      DMAparams_t		*DMAparams,
                      Uint32					coreNum);

void	VLFFT_2ndIter(	float					*pIn,
                      float					*pOut,
                      VLFFTparams_t	*VLFFTparams,
                      VLFFTbuffers_t	*VLFFTbuffers,
                      DMAparams_t		*DMAparams,
                      Uint32					coreNum);



void	broadcastMessages(	vlfftMessageQParams_t	*messageQParams,	const	UInt32	maxNumCores,	const	UInt32	numCoresForFftCompute,	const	vlfftMode	cmd	);
void	broadcastMessagesToActiveCores(	vlfftMessageQParams_t	*messageQParams,	const	UInt32	maxNumCores,	const	UInt32	numCoresForFftCompute,	const	vlfftMode	cmd	);
void	broadcastMessagesToAllCores(	vlfftMessageQParams_t	*messageQParams,	const	UInt32	maxNumCores,	const	UInt32	numCoresForFftCompute,	const	vlfftMode	cmd	);
Int32	getAllMessages(	vlfftMessageQParams_t	*messageQParams,	const	UInt32	maxNumCores,	const	UInt32	numCoresForFftCompute	);
void	initMessageQueues(	vlfftMessageQParams_t	*messageQParams,	const	UInt32	maxNumCores	);

void	tw_gen	(float	*w,	int	n);
















