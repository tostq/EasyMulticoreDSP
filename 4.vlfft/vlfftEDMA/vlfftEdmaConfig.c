/*
 * vlfftEdmaConfig_1stIter( )
 *   This module configures DMA channels for 1st iteration of FFT computation
 *
 * vlfftEdmaConfig2ndtIter( )
 *   This module configures DMA channels for 2nd iteration of FFT computation
 *
 * vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt()
 *   This module configures source address, destination address, Acnt, Bcnt, and Ccnt
 *   of a DMA channel
 *
 * vlfftEdmaConfig_srcAddrdstAddr( )
 *   This module configures source and destination of a DMA channel
 *
 * edmaTrigger( )
 *   This module trigger a DMA channel
 *
 * edmaPoll()
 *   This module poll a DMA channel for completion
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

/*  ----------------------------------- EDMA3 Low Level Driver       */
#include "vlfftEdmaLLD.h"

/*  ----------------------------------- To get globals from .cfg Header */
#include <xdc/cfg/global.h>

/* vlfft.h */
#include "../vlfftInc/vlfftDebug.h"
#include "../vlfftInc/vlfftMessgQ.h"
#include "../vlfftInc/vlfft.h"
#include "../vlfftInc/vlfftconfig.h"


void vlfftEdmaConfig_1stIter( DMAparams_t *DMAparams) {
	EDMA3_DRV_Handle hEdma;

	unsigned int chId0= 0;
	unsigned int chId1= 0;
	unsigned int tcc1= 0;

	chId0 = DMAparams->chId0;
	chId1 = DMAparams->chId1;
	tcc1  = DMAparams->tcc1;

	hEdma = DMAparams->hEdma;

	/*****************************/
	/* configure param set 0     */
	/*****************************/
	DMAparams->paramSet0.srcAddr    = 0;
	DMAparams->paramSet0.destAddr   = 0;

	DMAparams->paramSet0.srcBIdx    = DMAparams->srcInputBIDX_1stIter;
	DMAparams->paramSet0.destBIdx   = DMAparams->dstInputBIDX_1stIter;
	DMAparams->paramSet0.srcCIdx    = DMAparams->srcInputCIDX_1stIter;
	DMAparams->paramSet0.destCIdx   = DMAparams->dstInputCIDX_1stIter;
	DMAparams->paramSet0.aCnt       = DMAparams->aCntInput_1stIter;
	DMAparams->paramSet0.bCnt       = DMAparams->bCntInput_1stIter;
	DMAparams->paramSet0.cCnt       = DMAparams->cCntInput_1stIter;
	DMAparams->paramSet0.bCntReload = DMAparams->bCntRldInput_1stIter;
	DMAparams->paramSet0.linkAddr   = 0xFFFFu;

	DMAparams->paramSet0.opt = 0x0;
	/* Src & Dest are in INCR modes */
	DMAparams->paramSet0.opt &= 0xFFFFFFFCu;

	/* Program the TCC */
	DMAparams->paramSet0.opt |= ((tcc1 << OPT_TCC_SHIFT) & OPT_TCC_MASK);   // chain ch1 to ch0

	/* Enable Chaining */
	DMAparams->paramSet0.opt |= (1 << OPT_TCCHEN_SHIFT);

	/* AB Sync Transfer Mode */
	DMAparams->paramSet0.opt |= (1 << OPT_SYNCDIM_SHIFT);

	/* Now, write the PaRAM Set. */
	EDMA3_DRV_setPaRAM(hEdma, chId0, &DMAparams->paramSet0);

	/*****************************/
	/* configure param set 1     */
	/*****************************/
	DMAparams->paramSet1.srcAddr    = 0;
	DMAparams->paramSet1.destAddr   = 0;

	DMAparams->paramSet1.srcBIdx    = DMAparams->srcOutputBIDX_1stIter;
	DMAparams->paramSet1.destBIdx   = DMAparams->dstOutputBIDX_1stIter;
	DMAparams->paramSet1.srcCIdx    = DMAparams->srcOutputCIDX_1stIter;
	DMAparams->paramSet1.destCIdx   = DMAparams->dstOutputCIDX_1stIter;
	DMAparams->paramSet1.aCnt       = DMAparams->aCntOutput_1stIter;
	DMAparams->paramSet1.bCnt       = DMAparams->bCntOutput_1stIter;
	DMAparams->paramSet1.cCnt       = DMAparams->cCntOutput_1stIter;
	DMAparams->paramSet1.bCntReload = DMAparams->bCntRldOutput_1stIter;
	DMAparams->paramSet1.linkAddr   = 0xFFFFu;

	DMAparams->paramSet1.opt = 0x0;
	/* Src & Dest are in INCR modes */
	DMAparams->paramSet1.opt &= 0xFFFFFFFCu;

	/* Program the TCC */
	DMAparams->paramSet1.opt |= ((tcc1 << OPT_TCC_SHIFT) & OPT_TCC_MASK);

	/* Enable Final transfer completion interrupt */
	DMAparams->paramSet1.opt |= (1 << OPT_TCINTEN_SHIFT);

	/* AB Sync Transfer Mode */
	DMAparams->paramSet1.opt |= (1 << OPT_SYNCDIM_SHIFT);

	/* Now, write the PaRAM Set. */
	EDMA3_DRV_setPaRAM(hEdma, chId1, &DMAparams->paramSet1);
}

void vlfftEdmaConfig_2ndIter( DMAparams_t *DMAparams) {
	EDMA3_DRV_Handle hEdma;

	unsigned int chId0= 0;
	unsigned int chId1= 0;
	unsigned int tcc1= 0;

	chId0 = DMAparams->chId0;
	chId1 = DMAparams->chId1;
	tcc1  = DMAparams->tcc1;

	hEdma = DMAparams->hEdma;

	/*****************************/
	/* configure param set 0     */
	/*****************************/
	DMAparams->paramSet0.srcAddr    = 0;
	DMAparams->paramSet0.destAddr   = 0;

	DMAparams->paramSet0.srcBIdx    = DMAparams->srcInputBIDX_2ndIter;
	DMAparams->paramSet0.destBIdx   = DMAparams->dstInputBIDX_2ndIter;
	DMAparams->paramSet0.srcCIdx    = DMAparams->srcInputCIDX_2ndIter;
	DMAparams->paramSet0.destCIdx   = DMAparams->dstInputCIDX_2ndIter;
	DMAparams->paramSet0.aCnt       = DMAparams->aCntInput_2ndIter;
	DMAparams->paramSet0.bCnt       = DMAparams->bCntInput_2ndIter;
	DMAparams->paramSet0.cCnt       = DMAparams->cCntInput_2ndIter;
	DMAparams->paramSet0.bCntReload = DMAparams->bCntRldInput_2ndIter;
	DMAparams->paramSet0.linkAddr   = 0xFFFFu;

	DMAparams->paramSet0.opt = 0x0;
	/* Src & Dest are in INCR modes */
	DMAparams->paramSet0.opt &= 0xFFFFFFFCu;

	/* Program the TCC */
	DMAparams->paramSet0.opt |= ((tcc1 << OPT_TCC_SHIFT) & OPT_TCC_MASK);   // chain ch1 to ch0

	/* Enable Chaining */
	DMAparams->paramSet0.opt |= (1 << OPT_TCCHEN_SHIFT);

	/* AB Sync Transfer Mode */
	DMAparams->paramSet0.opt |= (1 << OPT_SYNCDIM_SHIFT);

	/* Now, write the PaRAM Set. */
	EDMA3_DRV_setPaRAM(hEdma, chId0, &DMAparams->paramSet0);

	/*****************************/
	/* configure param set 1     */
	/*****************************/
	DMAparams->paramSet1.srcAddr    = 0;
	DMAparams->paramSet1.destAddr   = 0;

	DMAparams->paramSet1.srcBIdx    = DMAparams->srcOutputBIDX_2ndIter;
	DMAparams->paramSet1.destBIdx   = DMAparams->dstOutputBIDX_2ndIter;
	DMAparams->paramSet1.srcCIdx    = DMAparams->srcOutputCIDX_2ndIter;
	DMAparams->paramSet1.destCIdx   = DMAparams->dstOutputCIDX_2ndIter;
	DMAparams->paramSet1.aCnt       = DMAparams->aCntOutput_2ndIter;
	DMAparams->paramSet1.bCnt       = DMAparams->bCntOutput_2ndIter;
	DMAparams->paramSet1.cCnt       = DMAparams->cCntOutput_2ndIter;
	DMAparams->paramSet1.bCntReload = DMAparams->bCntRldOutput_2ndIter;
	DMAparams->paramSet1.linkAddr   = 0xFFFFu;

	DMAparams->paramSet1.opt = 0x0;
	/* Src & Dest are in INCR modes */
	DMAparams->paramSet1.opt &= 0xFFFFFFFCu;

	/* Program the TCC */
	DMAparams->paramSet1.opt |= ((tcc1 << OPT_TCC_SHIFT) & OPT_TCC_MASK);

	/* Enable Final transfer completion interrupt */
	DMAparams->paramSet1.opt |= (1 << OPT_TCINTEN_SHIFT);

	/* AB Sync Transfer Mode */
	DMAparams->paramSet1.opt |= (1 << OPT_SYNCDIM_SHIFT);

	/* Now, write the PaRAM Set. */
	EDMA3_DRV_setPaRAM(hEdma, chId1, &DMAparams->paramSet1);
}


void vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt( EDMA3_DRV_Handle    hEdma,
    EDMA3_DRV_PaRAMRegs *pParamSet,
    Uint32              chId,
    Uint32              srcAddr,
    Uint32              dstAddr,
    Uint32              aCnt,
    Uint32              bCnt,
    Uint32              cCnt ) {
	pParamSet->srcAddr    = srcAddr;
	pParamSet->destAddr   = dstAddr;
	pParamSet->aCnt       = aCnt;
	pParamSet->bCnt       = bCnt;
	pParamSet->cCnt       = cCnt;

	/* Now, write the PaRAM Set. */
	EDMA3_DRV_setPaRAM(hEdma, chId, pParamSet);
}

void vlfftEdmaConfig_srcAddrdstAddr_aCntbCntcCnt_1( EDMA3_DRV_Handle    hEdma,
    EDMA3_DRV_PaRAMRegs *pParamSet,
    Uint32              chId,
    Uint32              srcAddr,
    Uint32              dstAddr,
    Uint32              aCnt,
    Uint32              bCnt,
    Uint32              cCnt ) {
	pParamSet->srcAddr    = srcAddr;
	pParamSet->destAddr   = dstAddr;
	pParamSet->aCnt       = aCnt;
	pParamSet->bCnt       = bCnt;
	pParamSet->cCnt       = cCnt;

	/* Now, write the PaRAM Set. */
//  EDMA3_DRV_setPaRAM(hEdma, chId, pParamSet);

	/* Now, write the PaRAM Set. */
	EDMA3_DRV_setSrcParams (hEdma, chId, srcAddr, EDMA3_DRV_ADDR_MODE_INCR, EDMA3_DRV_W8BIT);
	EDMA3_DRV_setDestParams(hEdma, chId, dstAddr, EDMA3_DRV_ADDR_MODE_INCR, EDMA3_DRV_W8BIT);
	EDMA3_DRV_setTransferParams (hEdma, chId, aCnt, bCnt, cCnt, bCnt, EDMA3_DRV_SYNC_AB);

}


/*    updated   */
void vlfftEdmaConfig_srcAddrdstAddr( EDMA3_DRV_Handle hEdma, EDMA3_DRV_PaRAMRegs *pParamSet, Uint32 chId, Uint32 srcAddr, Uint32 dstAddr ) {
	pParamSet->srcAddr    = srcAddr;
	pParamSet->destAddr   = dstAddr;

	/* Now, write the PaRAM Set. */
	EDMA3_DRV_setPaRAM(hEdma, chId, pParamSet);
}


void vlfftEdmaConfig_srcAddrdstAddr_1( EDMA3_DRV_Handle hEdma, EDMA3_DRV_PaRAMRegs *pParamSet, Uint32 chId, Uint32 srcAddr, Uint32 dstAddr ) {
	pParamSet->srcAddr    = srcAddr;
	pParamSet->destAddr   = dstAddr;

	/* Now, write the PaRAM Set. */
//  EDMA3_DRV_setPaRAM(hEdma, chId, pParamSet);
	EDMA3_DRV_setSrcParams (hEdma, chId, srcAddr, EDMA3_DRV_ADDR_MODE_INCR, EDMA3_DRV_W8BIT);
	EDMA3_DRV_setDestParams(hEdma, chId, dstAddr, EDMA3_DRV_ADDR_MODE_INCR, EDMA3_DRV_W8BIT);

}


void edmaTrigger( EDMA3_DRV_Handle hEdma, Uint32 chId ) {
	EDMA3_DRV_Result  result = EDMA3_DRV_SOK;

	// trigger DMA transfer
	result = EDMA3_DRV_enableTransfer (hEdma, chId, EDMA3_DRV_TRIG_MODE_MANUAL);
	if (result != EDMA3_DRV_SOK)
		printf ("edma3_test: EDMA3_DRV_enableTransfer Failed, error code: %d\r\n", result);
}


void edmaPoll( EDMA3_DRV_Handle hEdma, Uint32 tcc ) {
	EDMA3_DRV_Result result = EDMA3_DRV_SOK;

	// Now enable the transfer as many times as calculated above.
	result = EDMA3_DRV_waitAndClearTcc (hEdma, tcc);
	if (result != EDMA3_DRV_SOK)
		printf ("edma3_test: EDMA3_DRV_enableTransfer Failed, error code: %d\r\n", result);
}


