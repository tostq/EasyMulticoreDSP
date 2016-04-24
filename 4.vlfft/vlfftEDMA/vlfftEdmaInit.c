/*
 * vlfftEdmaInit( )
 *   This module initializes EDMA low level driver
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


void vlfftEdmaInit( DMAparams_t *DMAparams) {
	EDMA3_DRV_Handle hEdma;

	unsigned int chId0= 0;
	unsigned int chId1= 0;
	unsigned int tcc0= 0;
	unsigned int tcc1= 0;
	unsigned int edmaInstance = 0;

	EDMA3_DRV_Result edmaResult = EDMA3_DRV_SOK;
	EDMA3_DRV_Result result = EDMA3_DRV_SOK, result1 = EDMA3_DRV_SOK;

	// EDMA LLD init
	hEdma = edma3init(edmaInstance, &edmaResult);

	/* Setup for Channel 1*/
	tcc0 = EDMA3_DRV_TCC_ANY;
	chId0= EDMA3_DRV_DMA_CHANNEL_ANY;

	/* Request any DMA channel and any TCC */
	result = EDMA3_DRV_requestChannel (hEdma, &chId0, &tcc0, (EDMA3_RM_EventQueue)0, NULL, NULL);
	if (result == EDMA3_DRV_SOK) {
#ifdef ENABLE_PRINTF
		printf("DMA channel 0: %d\n", chId0);
#endif
	} else {
#ifdef ENABLE_PRINTF
		printf("DMA channel 0 request failed!\n");
#endif
	}


	tcc1= EDMA3_DRV_TCC_ANY;
	chId1= EDMA3_DRV_DMA_CHANNEL_ANY;
	result1= EDMA3_DRV_requestChannel (hEdma, &chId1, &tcc1, (EDMA3_RM_EventQueue)0, NULL, NULL);
	if (result1== EDMA3_DRV_SOK) {
#ifdef ENABLE_PRINTF
		printf("DMA channel 1: %d\n", chId0);
#endif
	} else {
#ifdef ENABLE_PRINTF
		printf("DMA channel 1 request failed!\n");
#endif
	}


	DMAparams->hEdma = hEdma;
	DMAparams->chId0 = chId0;
	DMAparams->tcc0 = tcc0;
	DMAparams->chId1 = chId1;
	DMAparams->tcc1  = tcc1;

}
