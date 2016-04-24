/*
 * genTestData.c
 *
 * This file contains function for generating test data for computing very
 * large size FFT.
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



void genTestData( float *inData ) {
	Int32    k, j;

	for(k=0; k<VLFFT_N2; k++) {
		for(j=0; j<VLFFT_N1; j++) {
			inData[j*2*VLFFT_N2 + 2*k  ] = k*2*VLFFT_N1 + 2*j;
			inData[j*2*VLFFT_N2 + 2*k+1] = k*2*VLFFT_N1 + 2*j+1;
		}
	}
	Edma3_CacheFlush((unsigned int)inData, VLFFT_N1*VLFFT_N2*BYTES_PER_COMPLEX_SAMPLE);

}

void genTestData2( float *inData ) {
	Int32    k, j;

	for(k=0; k<VLFFT_N1; k++) {
		for(j=0; j<VLFFT_N2; j++) {
			inData[j*2*VLFFT_N1 + 2*k  ] = k*2*VLFFT_N2 + 2*j;
			inData[j*2*VLFFT_N1 + 2*k+1] = k*2*VLFFT_N2 + 2*j+1;
		}
	}
	Edma3_CacheFlush((unsigned int)inData, VLFFT_N1*VLFFT_N2*BYTES_PER_COMPLEX_SAMPLE);

}

void genFFTTestData( float *inData ) {
	Int32 i;

	for(i=0; i<VLFFT_SIZE*2;  i++)
		inData[i] = 0;

	for(i=0; i<VLFFT_N2; i++) {
#if USE_BDTI_FFT
		inData[2*i] = 0.0;
		inData[2*i+1]=1.0;
#else
		inData[2*i] = 1.0;
		inData[2*i+1]=0.0;
#endif
	}
	Edma3_CacheFlush((unsigned int)inData, VLFFT_N1*VLFFT_N2*BYTES_PER_COMPLEX_SAMPLE);

}

