/*
 * vlfftParamsInit()
 *   Initialize parameters for multicore FFT
 *
 * vlfftBuffersInit()
 *   Initialize buffer pointers for multicore FFT
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

/*  vlfft local define */
#include "../vlfftInc/vlfftDebug.h"
#include "../vlfftInc/vlfftMessgQ.h"
#include "../vlfftInc/vlfft.h"
#include "../vlfftInc/vlfftconfig.h"


/****************************************/
/*    N=N1*N2                           */
/*      1st iteration                   */
/*           compute N2 FFT of size N1  */
/*      2nd iteration                   */
/*           compute N1 FFT of size N2  */
/*                                      */
/****************************************/
void vlfftParamsInit(VLFFTparams_t *VLFFTparams, float *pW1, float *pW2, float *pTwiddle, Uint32 coreNum ) {
	VLFFTparams->maxNumCores = MAX_NUMBER_CORES;
	VLFFTparams->numCoresForFftCompute = NUM_CORES_FOR_FFT_COMPUTE;
	VLFFTparams->log2NumCoresForFftCompute = LOG2_NUM_CORES_FOR_COMPUTE;

	VLFFTparams->radix_1stIter = RADIX_1stIter;
	VLFFTparams->log4N_1stIter = LOG4N_1stIter;
	VLFFTparams->radix_2ndIter = RADIX_2ndIter;
	VLFFTparams->log4N_2ndIter = LOG4N_2ndIter;

	VLFFTparams->N  = VLFFT_SIZE;
	VLFFTparams->N1 = VLFFT_N1;
	VLFFTparams->N2 = VLFFT_N2;
	VLFFTparams->samplesPerBlock = SAMPLES_PER_TRANSFER_BLOCK;

	VLFFTparams->fftSize1stIter       = VLFFTparams->N1;
	VLFFTparams->numFFTs1stIter       = VLFFTparams->N2;
	VLFFTparams->numFFTsPerCore1stIter= VLFFTparams->N2>>(VLFFTparams->log2NumCoresForFftCompute);
	VLFFTparams->numBlocksPerCore1stIter= (VLFFTparams->numFFTsPerCore1stIter) >> LOG2_SAMPLES_PER_TRANSFER_BLOCK;
	VLFFTparams->numFFTsPerBlock1stIter = NUM_FFTS_PER_BLOCK;

	VLFFTparams->fftSize2ndIter       = VLFFTparams->N2;
	VLFFTparams->numFFTs2ndIter       = VLFFTparams->N1;
	VLFFTparams->numFFTsPerCore2ndIter  = VLFFTparams->N1>>VLFFTparams->log2NumCoresForFftCompute;
	VLFFTparams->numBlocksPerCore2ndIter= (VLFFTparams->numFFTsPerCore2ndIter) >> (LOG2_SAMPLES_PER_TRANSFER_BLOCK);
	VLFFTparams->numFFTsPerBlock2ndIter = NUM_FFTS_PER_BLOCK;


	VLFFTparams->offset1stIterIn      = coreNum*BYTES_PER_COMPLEX_SAMPLE;
	VLFFTparams->offset1stIterIn     *= VLFFTparams->samplesPerBlock;
	VLFFTparams->offset1stIterIn     *= VLFFTparams->numBlocksPerCore1stIter;

	VLFFTparams->step1stIterIn = VLFFTparams->N2*BYTES_PER_COMPLEX_SAMPLE;
	VLFFTparams->offset1stIterOut = coreNum*VLFFTparams->fftSize1stIter*BYTES_PER_COMPLEX_SAMPLE*VLFFTparams->numFFTsPerCore1stIter;


	VLFFTparams->offset2ndIterIn      = coreNum*BYTES_PER_COMPLEX_SAMPLE;
	VLFFTparams->offset2ndIterIn     *= VLFFTparams->samplesPerBlock;
	VLFFTparams->offset2ndIterIn     *= VLFFTparams->numBlocksPerCore2ndIter;

	VLFFTparams->step2ndIterIn = VLFFTparams->N1*BYTES_PER_COMPLEX_SAMPLE;
	VLFFTparams->offset2ndIterOut = VLFFTparams->offset2ndIterIn;
	VLFFTparams->step2ndIterOut = VLFFTparams->N1*BYTES_PER_COMPLEX_SAMPLE;

	VLFFTparams->pW1 = pW1;
	VLFFTparams->pW2 = pW2;

	tw_gen (VLFFTparams->pW1, VLFFT_N1);
	tw_gen (VLFFTparams->pW2, VLFFT_N2);

	VLFFTparams->pTwiddle = pTwiddle;
	genTwiddle(VLFFTparams->pTwiddle, VLFFTparams->numFFTsPerCore1stIter, coreNum);

}

void vlfftBuffersInit( VLFFTbuffers_t  *VLFFTbuffers,
                       float           *pInBufInternal,
                       float           *pOutBufInternal,
                       float           *pWorkBuf0Internal,
                       float           *pfftInBuf,
                       float           *pfftOutBuf
                     ) {

	VLFFTbuffers->pInBufInternal  = pInBufInternal;
	VLFFTbuffers->pOutBufInternal = pOutBufInternal;
	VLFFTbuffers->pWorkBuf0Internal = pWorkBuf0Internal;
	VLFFTbuffers->pfftInBuf = pfftInBuf;
	VLFFTbuffers->pfftOutBuf= pfftOutBuf;
}
