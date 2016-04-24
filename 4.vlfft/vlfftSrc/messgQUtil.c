/*
 * broadcastMessages()
 *    Broadcast message from master core to all the slave cores based on IPC MessageQ
 *
 * broadcastMessagesToActiveCores()
 *    Broadcast message from master core to active slave cores
 *
 * getAllMessages()
 *    Master collect message from all the slave cores
 *
 * initMessageQueues()
 *    Initialize all the message queues.
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

#ifdef ENABLE_SYSTEM_TRACE_LOGS
#include <system_trace.h>
#endif

/* vlfft.h */
#include "../vlfftInc/vlfftMessgQ.h"
#include "../vlfftInc/vlfft.h"
#include "../vlfftInc/vlfftconfig.h"

extern Char core0QueueName[];
extern Char core1QueueName[];
extern Char core2QueueName[];
extern Char core3QueueName[];
extern Char core4QueueName[];
extern Char core5QueueName[];
extern Char core6QueueName[];
extern Char core7QueueName[];

#define DEBUG_DISPLAY  0
#define USE_BDTI_FFT   1

#ifdef ENABLE_SYSTEM_TRACE_LOGS
extern STMHandle *pSTMHandle;
#endif

/****************************************************************/
/*    broadcast messages to core 1 - core numCoresToCompute-1   */
/****************************************************************/
void broadcastMessages(  vlfftMessageQParams_t *messageQParams, const UInt32 maxNumCores, const UInt32 numCoresForFftCompute, const vlfftMode cmd ) {
	UInt16           msgId = 0;
	UInt32           indexCore;

	for(indexCore=1; indexCore<numCoresForFftCompute; indexCore++) {
		/*
		 *  Send a message to processor 1
		 */
		messageQParams->msg[indexCore]->mode = cmd;
		msgId = indexCore;

		MessageQ_setMsgId( (MessageQ_Msg)messageQParams->msg[indexCore], msgId);

		/* send the message to the remote processor */
		MessageQ_put(messageQParams->remoteQueueIdCore[indexCore], (MessageQ_Msg)messageQParams->msg[indexCore] );
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_MSG_SEND, "Message sent to core %d\0", indexCore);
#endif
	}
}


void broadcastMessagesToActiveCores(  vlfftMessageQParams_t *messageQParams, const UInt32 maxNumCores, const UInt32 numCoresForFftCompute, const vlfftMode cmd ) {
	UInt16           msgId = 0;
	UInt32           indexCore;

	for(indexCore=1; indexCore<maxNumCores; indexCore++) {
		/*
		 *  Send a message to processor 1
		 */
		if( indexCore < numCoresForFftCompute )
			messageQParams->msg[indexCore]->mode = cmd;
		else
			messageQParams->msg[indexCore]->mode = VLFFT_DO_NOTHING;
		msgId = indexCore;

		MessageQ_setMsgId( (MessageQ_Msg)messageQParams->msg[indexCore], msgId);

		/* send the message to the remote processor */
		MessageQ_put(messageQParams->remoteQueueIdCore[indexCore], (MessageQ_Msg)messageQParams->msg[indexCore] );
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_MSG_SEND, "Message sent to core %d\0", indexCore);
#endif
	}
}

void broadcastMessagesToAllCores(  vlfftMessageQParams_t *messageQParams, const UInt32 maxNumCores, const UInt32 numCoresForFftCompute, const vlfftMode cmd ) {
	UInt16           msgId = 0;
	UInt32           indexCore;

	for(indexCore=1; indexCore<maxNumCores; indexCore++) {
		/*
		 *  Send a message to processor 1
		 */
		messageQParams->msg[indexCore]->mode = cmd;
		msgId = indexCore;

		MessageQ_setMsgId( (MessageQ_Msg)messageQParams->msg[indexCore], msgId);

		/* send the message to the remote processor */
		MessageQ_put(messageQParams->remoteQueueIdCore[indexCore], (MessageQ_Msg)messageQParams->msg[indexCore] );
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_MSG_SEND, "Message sent to core %d\0", indexCore);
#endif
	}
}



/***************************************************/
/*    get all messages                             */
/***************************************************/
Int32 getAllMessages( vlfftMessageQParams_t *messageQParams, const UInt32 maxNumCores, const UInt32 numCoresForFftCompute ) {
	Int              receiveFlag=0, indexCore;
	UInt16           msgId = 0;

	for(indexCore=1; indexCore<numCoresForFftCompute; indexCore++) {
		/* Get a message */
		MessageQ_get( messageQParams->messageQ, (MessageQ_Msg *)&messageQParams->msg[indexCore], MessageQ_FOREVER);
		msgId = MessageQ_getMsgId( (MessageQ_Msg *)messageQParams->msg[indexCore] );
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_MSG_RCV, "Message received from core %d\0", msgId);
#endif
		if( msgId==1 ) receiveFlag |= 0x1;
		if( msgId==2 ) receiveFlag |= 0x2;
		if( msgId==3 ) receiveFlag |= 0x4;
		if( msgId==4 ) receiveFlag |= 0x8;
		if( msgId==5 ) receiveFlag |= 0x10;
		if( msgId==6 ) receiveFlag |= 0x20;
		if( msgId==7 ) receiveFlag |= 0x40;
	}

	return receiveFlag;
}

/***************************************************/
/*    init message Q                               */
/***************************************************/
void initMessageQueues( vlfftMessageQParams_t *messageQParams, const UInt32 maxNumCores  ) {
	Int                status;
	Int                indexCore;

	/* Open the remote message queue. Spin until it is ready. */
	do {
		status = MessageQ_open(core1QueueName, &messageQParams->remoteQueueIdCore[1]);
	} while (status < 0);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg1(pSTMHandle, STM_CHAN_STATUS, "Message Queue opened for core %d\0", 1);
#endif
	do {
		status = MessageQ_open(core2QueueName, &messageQParams->remoteQueueIdCore[2]);
	} while (status < 0);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg1(pSTMHandle, STM_CHAN_STATUS, "Message Queue opened for core %d\0", 2);
#endif
	do {
		status = MessageQ_open(core3QueueName, &messageQParams->remoteQueueIdCore[3]);
	} while (status < 0);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg1(pSTMHandle, STM_CHAN_STATUS, "Message Queue opened for core %d\0", 3);
#endif
#ifdef ENABLE_PRINTF
	System_printf("maxNumCores: %d\n", maxNumCores);
	System_printf("MessageQ opened\n" );
#endif
	if( maxNumCores==8) {
		do {
			status = MessageQ_open(core4QueueName, &messageQParams->remoteQueueIdCore[4]);
		} while (status < 0);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_STATUS, "Message Queue opened for core %d\0", 4);
#endif
		do {
			status = MessageQ_open(core5QueueName, &messageQParams->remoteQueueIdCore[5]);
		} while (status < 0);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_STATUS, "Message Queue opened for core %d\0", 5);
#endif
		do {
			status = MessageQ_open(core6QueueName, &messageQParams->remoteQueueIdCore[6]);
		} while (status < 0);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_STATUS, "Message Queue opened for core %d\0", 6);
#endif
		do {
			status = MessageQ_open(core7QueueName, &messageQParams->remoteQueueIdCore[7]);
		} while (status < 0);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg1(pSTMHandle, STM_CHAN_STATUS, "Message Queue opened for core %d\0", 7);
#endif
	}

	for( indexCore=1; indexCore<maxNumCores; indexCore++ ) {
		/* Allocate a message to be ping-ponged around the processors */
		messageQParams->msg[indexCore] = (vlfftMessageQ_Msg *)MessageQ_alloc(HEAPID, sizeof(vlfftMessageQ_Msg));
#if DEBUG_DISPLAY
		if (messageQParams->msg[indexCore] == NULL) {
			System_abort("MessageQ_alloc failed\n" );
		}
#endif
	}

}



