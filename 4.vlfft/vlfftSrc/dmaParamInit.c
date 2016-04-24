/*
 * DMAparamInit()
 *
 *   This module initializes parameters for multicore FFT
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
#include "../vlfftInc/vlfftDMAResources.h"



void  DMAparamInit( DMAparams_t *DMAparams, VLFFTparams_t *VLFFTparams, Uint32 coreNum ) {
	DMAparams->instNum = 0;

	if (coreNum == 0) DMAparams->coreNum = 0;
	if (coreNum == 1) DMAparams->coreNum = 1;
	if (coreNum == 2) DMAparams->coreNum = 2;
	if (coreNum == 3) DMAparams->coreNum = 3;
	if (coreNum == 4) DMAparams->coreNum = 4;
	if (coreNum == 5) DMAparams->coreNum = 5;
	if (coreNum == 6) DMAparams->coreNum = 6;
	if (coreNum == 7) DMAparams->coreNum = 7;

	DMAparams->regionNum = coreNum;

	if( DMAparams->coreNum==0 ) {
		DMAparams->dmaChannelIn  = VLFFT_CORE0_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut = VLFFT_CORE0_OUT_DMA_CHANNEL;

		DMAparams->intrNum    = VLFFT_CORE0_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE0_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE0_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE0_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE0_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =      VLFFT_CORE0_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping = VLFFT_CORE0_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong = VLFFT_CORE0_OutPaRAM_PONG;

		DMAparams->globalAddrOffset = CORE0_L2SRAM_GLOBAL_ADDR_OFFSET;
	}
	if( DMAparams->coreNum==1 ) {
		DMAparams->dmaChannelIn = VLFFT_CORE1_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut = VLFFT_CORE1_OUT_DMA_CHANNEL;

		DMAparams->intrNum = VLFFT_CORE1_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE1_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE1_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE1_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE1_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =      VLFFT_CORE1_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping = VLFFT_CORE1_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong = VLFFT_CORE1_OutPaRAM_PONG;

		DMAparams->globalAddrOffset = CORE1_L2SRAM_GLOBAL_ADDR_OFFSET;
	}
	if( DMAparams->coreNum==2 ) {
		DMAparams->dmaChannelIn = VLFFT_CORE2_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut = VLFFT_CORE2_OUT_DMA_CHANNEL;

		DMAparams->intrNum = VLFFT_CORE2_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE2_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE2_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE2_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE2_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =      VLFFT_CORE2_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping = VLFFT_CORE2_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong = VLFFT_CORE2_OutPaRAM_PONG;

		DMAparams->globalAddrOffset = CORE2_L2SRAM_GLOBAL_ADDR_OFFSET;
	}
	if( DMAparams->coreNum==3 ) {
		DMAparams->dmaChannelIn = VLFFT_CORE3_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut = VLFFT_CORE3_OUT_DMA_CHANNEL;

		DMAparams->intrNum = VLFFT_CORE3_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE3_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE3_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE3_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE3_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =      VLFFT_CORE3_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping = VLFFT_CORE3_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong = VLFFT_CORE3_OutPaRAM_PONG;

		DMAparams->globalAddrOffset = CORE3_L2SRAM_GLOBAL_ADDR_OFFSET;
	}
	if( DMAparams->coreNum==4 ) {
		DMAparams->dmaChannelIn = VLFFT_CORE4_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut = VLFFT_CORE4_OUT_DMA_CHANNEL;

		DMAparams->intrNum = VLFFT_CORE4_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE4_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE4_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE4_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE4_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =     VLFFT_CORE4_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping =VLFFT_CORE4_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong =VLFFT_CORE4_OutPaRAM_PONG;

		DMAparams->globalAddrOffset = CORE4_L2SRAM_GLOBAL_ADDR_OFFSET;
	}
	if( DMAparams->coreNum==5 ) {
		DMAparams->dmaChannelIn = VLFFT_CORE5_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut =VLFFT_CORE5_OUT_DMA_CHANNEL;

		DMAparams->intrNum = VLFFT_CORE5_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE5_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE5_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE5_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE5_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =     VLFFT_CORE5_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping =VLFFT_CORE5_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong =VLFFT_CORE5_OutPaRAM_PONG;

		DMAparams->globalAddrOffset = CORE5_L2SRAM_GLOBAL_ADDR_OFFSET;
	}
	if( DMAparams->coreNum==6 ) {
		DMAparams->dmaChannelIn = VLFFT_CORE6_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut =VLFFT_CORE6_OUT_DMA_CHANNEL;

		DMAparams->intrNum = VLFFT_CORE6_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE6_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE6_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE6_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE6_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =     VLFFT_CORE6_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping =VLFFT_CORE6_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong =VLFFT_CORE6_OutPaRAM_PONG;

		DMAparams->globalAddrOffset = CORE6_L2SRAM_GLOBAL_ADDR_OFFSET;
	}
	if( DMAparams->coreNum==7 ) {
		DMAparams->dmaChannelIn = VLFFT_CORE7_IN_DMA_CHANNEL;
		DMAparams->dmaChannelOut =VLFFT_CORE7_OUT_DMA_CHANNEL;

		DMAparams->intrNum = VLFFT_CORE7_INTR_NUM;
		DMAparams->intrOutNum = VLFFT_CORE7_OUT_INTR_NUM;

		DMAparams->indexInPaRAM =      VLFFT_CORE7_InPaRAM;
		DMAparams->indexInPaRAM_Ping = VLFFT_CORE7_InPaRAM_PING;
		DMAparams->indexInPaRAM_Pong = VLFFT_CORE7_InPaRAM_PONG;

		DMAparams->indexOutPaRAM =     VLFFT_CORE7_OutPaRAM;
		DMAparams->indexOutPaRAM_Ping =VLFFT_CORE7_OutPaRAM_PING;
		DMAparams->indexOutPaRAM_Pong =VLFFT_CORE7_OutPaRAM_PONG;


		DMAparams->globalAddrOffset = CORE7_L2SRAM_GLOBAL_ADDR_OFFSET;
	}


	/********************************/
	/*     1st iter DMA param       */
	/********************************/
	DMAparams->aCntInput_1stIter = VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE;
	DMAparams->bCntInput_1stIter = VLFFTparams->N1;
	DMAparams->cCntInput_1stIter = 1;
	DMAparams->bCntRldInput_1stIter = 0;

	DMAparams->aCntOutput_1stIter = (VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE*VLFFTparams->N1)>>2;
	DMAparams->bCntOutput_1stIter = 4;
	DMAparams->cCntOutput_1stIter = 1;
	DMAparams->bCntRldOutput_1stIter = 0;


	DMAparams->srcInputBIDX_1stIter = VLFFTparams->step1stIterIn;
	DMAparams->dstInputBIDX_1stIter = DMAparams->aCntInput_1stIter;
	DMAparams->srcInputCIDX_1stIter = 0;
	DMAparams->dstInputCIDX_1stIter = 0;

	DMAparams->srcOutputBIDX_1stIter = (VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE*VLFFTparams->N1)>>2;
	DMAparams->dstOutputBIDX_1stIter = (VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE*VLFFTparams->N1)>>2;
	DMAparams->srcOutputCIDX_1stIter = 0;
	DMAparams->dstOutputCIDX_1stIter = 0;


	/********************************/
	/*     2nd iter DMA param       */
	/********************************/
	DMAparams->aCntInput_2ndIter = VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE;
	DMAparams->bCntInput_2ndIter = VLFFTparams->N2;
	DMAparams->cCntInput_2ndIter = 1;
	DMAparams->bCntRldInput_2ndIter = 0;

	DMAparams->aCntOutput_2ndIter = VLFFTparams->samplesPerBlock*BYTES_PER_COMPLEX_SAMPLE;
	DMAparams->bCntOutput_2ndIter = VLFFTparams->N2;
	DMAparams->cCntOutput_2ndIter = 1;
	DMAparams->bCntRldOutput_2ndIter = 0;


	DMAparams->srcInputBIDX_2ndIter = VLFFTparams->step2ndIterIn;
	DMAparams->dstInputBIDX_2ndIter = DMAparams->aCntInput_2ndIter;
	DMAparams->srcInputCIDX_2ndIter = 0;
	DMAparams->dstInputCIDX_2ndIter = 0;

	DMAparams->srcOutputBIDX_2ndIter = DMAparams->aCntInput_2ndIter;
	DMAparams->dstOutputBIDX_2ndIter = VLFFTparams->step2ndIterIn;
	DMAparams->srcOutputCIDX_2ndIter = 0;
	DMAparams->dstOutputCIDX_2ndIter = 0;

}


