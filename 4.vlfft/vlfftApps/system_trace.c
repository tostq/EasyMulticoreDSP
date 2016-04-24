/*
 * system_trace.c
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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
 *  =========================== REVISION INFORMATION ===========================
 *  Revision Information
 *   Changed: $LastChangedDate: 2012-05-16 04:17:15 -0400 (Wed, 16 May 2012) $
 *   Revision: $LastChangedRevision: 109 $
 *   Last Update By: $Author: danrinkes@gmail.com $
 *  ============================================================================
 *
        1         2         3         4         5         6          7
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/


#include <system_trace.h>

/* Global Variables */
STMHandle *pSTMHandle;



void initializeSTM(void) {
	STMBufObj *pSTMBufInfo = NULL;
	STMConfigObj STMConfigInfo;

	STMConfigInfo.optimized_prinf=false;
	STMConfigInfo.STM_BaseAddress = STM_BASE_ADDRESS;
	STMConfigInfo.STM_ChannelResolution = STM_CHAN_RESOLUTION;
	STMConfigInfo.pCallBack = STMLog_CallBack;

	/*
	 * Open the STM port
	 */
	pSTMHandle = STMXport_open(pSTMBufInfo, &STMConfigInfo);

	if (pSTMHandle == 0)
		exit (0);
}

void closeSTM(void) {
	STMXport_close(pSTMHandle);
}

void* cTools_memAlloc(size_t sizeInBytes) {
	return malloc(sizeInBytes);
}

void* cTools_memMap(unsigned int phyAddr, unsigned int mapSizeInBytes) {
	return (void*)phyAddr;
}

void cTools_memFree(void* ptr) {
	free(ptr);
}

void cTools_memUnMap(void* vAddr, unsigned int mapSizeInBytes) {
	return;
}
