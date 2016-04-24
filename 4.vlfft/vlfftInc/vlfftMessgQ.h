/*
 * vlfftMessgQ.h
 *
 *    This file contains definitions for IPC for multicore FFT computation.
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


#define HEAP_NAME   "myHeapBuf"
#define HEAPID      0
#define NUMLOOPS    10

typedef enum vlfftMode {
  VLFFT_DO_NOTHING = 0,
  VLFFT_PROCESS_1stITER = 1,
  VLFFT_PROCESS_2ndITER = 2,
  VLFFT_EXIT = 3,
  VLFFT_OK = 4
} vlfftMode;


typedef struct vlfftMessageQ_Msg {
	MessageQ_MsgHeader header;
	vlfftMode          mode;
	Int32              fill[7];
} vlfftMessageQ_Msg;



typedef struct {

	MessageQ_Msg     msg1;
	MessageQ_Msg     msg2;
	MessageQ_Msg     msg3;
	MessageQ_Msg     msg4;
	MessageQ_Msg     msg5;
	MessageQ_Msg     msg6;
	MessageQ_Msg     msg7;
	MessageQ_Handle  messageQ;

	MessageQ_QueueId remoteQueueIdCore1;
	MessageQ_QueueId remoteQueueIdCore2;
	MessageQ_QueueId remoteQueueIdCore3;
	MessageQ_QueueId remoteQueueIdCore4;
	MessageQ_QueueId remoteQueueIdCore5;
	MessageQ_QueueId remoteQueueIdCore6;
	MessageQ_QueueId remoteQueueIdCore7;
} messageQParams_t;

typedef struct {

	vlfftMessageQ_Msg     *msg[8];

	MessageQ_Handle   messageQ;

	MessageQ_QueueId remoteQueueIdCore[8];
} vlfftMessageQParams_t;

