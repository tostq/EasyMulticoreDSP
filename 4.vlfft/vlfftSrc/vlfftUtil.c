/*
 * transpose_1()
 *     Transpose a Nx8 matrix into a 8xN matrix
 *
 * transpose_2()
 *     Transpose a 8xN matrix into a Nx8 matrix
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



#include "stdio.h"
#include <stdlib.h>


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



void transpose_1( float *pIn, float *pOut, Int32 rows, Int32 cols ) {
	transpose_2Cols_rowsX8_cplxMatrix_sa  ( &pIn[0 ], &pOut[0],       rows );
	transpose_2Cols_rowsX8_cplxMatrix_sa  ( &pIn[4 ], &pOut[4 *rows], rows );
	transpose_2Cols_rowsX8_cplxMatrix_sa  ( &pIn[8 ], &pOut[8 *rows], rows );
	transpose_2Cols_rowsX8_cplxMatrix_sa  ( &pIn[12], &pOut[12*rows], rows );
}


void transpose_2( float *pIn, float *pOut, Int32 rows, Int32 cols ) {
	transpose_2Rows_8XCols_cplxMatrix_sa( &pIn[0],       &pOut[0 ],  cols );
	transpose_2Rows_8XCols_cplxMatrix_sa( &pIn[4 *cols], &pOut[4 ],  cols );
	transpose_2Rows_8XCols_cplxMatrix_sa( &pIn[8 *cols], &pOut[8 ],  cols );
	transpose_2Rows_8XCols_cplxMatrix_sa( &pIn[12*cols], &pOut[12],  cols );
}



int compare_float( int N, float *pIn1, float *pIn2) {
	int i, index=0,flag=0;
	float diff;

	for(i=0; i<N; i++) {
		diff = pIn1[i] - pIn2[i];
		if( diff< 0.0 ) diff = -diff;

		if( diff > 0.01 ) {
			index = i;
			flag=1;
			break;
		}
	}
	if( flag == 1 ) {
		printf("   max error index:    %d\n", index  );
		printf("   real, %f, real_ref: %f, %f\n", pIn1[2*i],   pIn2[2*i]  );
		printf("   imag, %f, imag_ref: %f, %f\n", pIn1[2*i+1], pIn2[2*i+1]  );
	}

	return flag;
}

void copy_float( int N, float *pSrc, float *pDst ) {
	int i;

	for(i=0; i<N; i++)
		pDst[i] = pSrc[i];
}

