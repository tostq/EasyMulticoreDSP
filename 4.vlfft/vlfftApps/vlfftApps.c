/*
 * vlfftApps.c
 *
 * This file contains a multi-thread multi-core implementation of computing
 * very large size signle precision float point FFT.
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


#include <c6x.h>
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
#ifdef ENABLE_SYSTEM_TRACE_LOGS
#include <system_trace.h>
#endif

/* vlfft.h */
#include "../vlfftInc/vlfftDebug.h"
#include "../vlfftInc/vlfftMessgQ.h"
#include "../vlfftInc/vlfft.h"
#include "../vlfftInc/vlfftconfig.h"

#ifdef ENABLE_SYSTEM_TRACE_LOGS
extern STMHandle *pSTMHandle;
#endif

#define NUM_FFT_TO_COMPUTE    10

void     genFFTTestData( float *inData );
void     TSC_enable();
unsigned long long TSC_read();
void     dft(Uint32 fftSize, float *pIn, float *pOut, Uint32 numSamplesToCompare);
Uint32   compare_float( Uint32 n, float *pIn0, float *pIn1 );



Char localQueueName[6];
Char nextQueueName[6];

Char core0QueueName[6];
Char core1QueueName[6];
Char core2QueueName[6];
Char core3QueueName[6];
Char core4QueueName[6];
Char core5QueueName[6];
Char core6QueueName[6];
Char core7QueueName[6];




#pragma DATA_ALIGN(workBuf0Internal, 8);
#pragma DATA_SECTION(workBuf0Internal, ".internalMEM");
float workBuf0Internal[1024*2*8];
//float workBuf0Internal[512*2*8];

#pragma DATA_ALIGN(fftInBuf, 8);
#pragma DATA_SECTION(fftInBuf, ".internalMEM");
float fftInBuf[1024*2];
//float fftInBuf[512*2];

#pragma DATA_ALIGN(fftOutBuf, 8);
#pragma DATA_SECTION(fftOutBuf, ".internalMEM");
float fftOutBuf[1024*2];
//float fftOutBuf[512*2];


#pragma DATA_ALIGN(inData, 8);
#pragma DATA_SECTION(inData, ".externalMEM");
float inData[VLFFT_N1*VLFFT_N2*2];

#pragma DATA_ALIGN(outData, 8);
#pragma DATA_SECTION(outData, ".externalMEM");
float outData[VLFFT_N1*VLFFT_N2*2];


#pragma DATA_ALIGN(workBufExternal, 8);
#pragma DATA_SECTION(workBufExternal, ".externalMEM");
float workBufExternal[VLFFT_N1*VLFFT_N2*2];

#pragma DATA_ALIGN(testData, 8);
#pragma DATA_SECTION(testData, ".externalMEM");
float testData[VLFFT_N1*VLFFT_N2*2];



#pragma DATA_ALIGN(vlfft_w1, 8);
#pragma DATA_SECTION(vlfft_w1, ".internalMEM");
float vlfft_w1[2*VLFFT_N1];

#pragma DATA_ALIGN(vlfft_w2, 8);
#pragma DATA_SECTION(vlfft_w2, ".internalMEM");
float vlfft_w2[2*VLFFT_N2];

#pragma DATA_SECTION(vlfft_twiddle, ".internalMEM");
float vlfft_twiddle[2*VLFFT_N2];

#pragma DATA_ALIGN(inBuf, 8);
#pragma DATA_SECTION(inBuf, ".internalMEM");
float inBuf[1024*2*8*2];
//float inBuf[512*2*8*2];

#pragma DATA_ALIGN(outBuf, 8);
#pragma DATA_SECTION(outBuf, ".internalMEM");
float outBuf[1024*2*8*2];
//float outBuf[512*2*8*2];




#if !FUNCTIONAL_SIMULATOR
#define KICK0     0x02620038
#define KICK1     0x0262003C

#define SECR      0x02701040
#define SECRH     0x02701044
#define EMCR      0x02700308
#define EMCRH     0x0270030C


void clearRegisters(Int phase)

{

    volatile UInt32 *kick0 = (volatile UInt32 *)KICK0;

    volatile UInt32 *kick1 = (volatile UInt32 *)KICK1;

    volatile UInt32 *secr = (volatile UInt32 *)SECR;

    volatile UInt32 *secrh= (volatile UInt32 *)SECRH;
 
    volatile UInt32 *emcr = (volatile UInt32 *)EMCR;

    volatile UInt32 *emcrh = (volatile UInt32 *)EMCRH;


    /* unlock the KICK mechanism in the Bootcfg MMRs if defined */
    kick0[0] = 0x83e70b13;      /* must be written with this value */

    kick1[0] = 0x95a4f1e0;      /* must be written with this value */

    secr[0] = 0xffffffff;
    secrh[0] = 0xffffffff;
    emcr[0] = 0xffffffff;
    emcrh[0] = 0xffffffff;

    /* The ROM bootloader sets the IE04 bit for IPC interrupt.
     * This needs to be cleared for IPC.
    */
    /* Clear interrupt enable register at startup */
//  IER = 0;
}
#endif


/*
 *  ======== setMyId ========
 *  This function is run by xdc.runtime.Startup and is executed before main().
 *  The local MultiProc id is set based on the value read from the DNUM
 *  register.
 */
Void setMyId() 
{
    extern cregister volatile UInt DNUM;
    UInt16 procId;
    Char procName[6];

    /* Determine the procName from DNUM */
    System_sprintf(procName, "CORE%d", DNUM);

    /* Translate from a procName to a procId */
    procId = MultiProc_getId(procName);
    
    /* Set the local ID */
    MultiProc_setLocalId(procId);
}


/*
 *  ======== tsk0_func ========
 *  This function is executed only on CORE0.
 *  It allocates a message and ping-pongs the message around the processors.
 *  A local message queue is created and a remote message queue is opened.
 *  Messages are sent to the remote message queue and retrieved from the
 *  local MessageQ.
 */
Void vlfft_master(UArg arg0, UArg arg1)
{
    vlfftMessageQParams_t messageQParams;


    Uint32           fftLoop;

    VLFFTparams_t    VLFFTparams;
    DMAparams_t      DMAparams;
    VLFFTbuffers_t   VLFFTbuffers;
    float            *ptrIn, *ptrOut;
 

    double           fftTime;
    unsigned long long timer0, timer1;


    /*****************************************************/
    /*         VLFFT param init                          */
    /*****************************************************/
    vlfftParamsInit( &VLFFTparams, vlfft_w1, vlfft_w2, vlfft_twiddle, 0 );
    vlfftBuffersInit( &VLFFTbuffers, inBuf,      outBuf,      workBuf0Internal, fftInBuf, fftOutBuf);
    DMAparamInit( &DMAparams, &VLFFTparams, 0 );
    vlfftEdmaInit( &DMAparams);
#ifdef ENABLE_PRINTF
    System_printf("pass init 1\n");
#endif

    /******************************************************/
    /*         init EDMA                                  */
    /******************************************************/
    //dmaInitVLFFT( &DMAparams, 0, VLFFTparams.numCoresForFftCompute );   // edma_lld
#ifdef ENABLE_PRINTF
	System_printf("pass init 2\n");

	System_printf("pass init 3\n");
	System_printf("max num of cores: %d\n", VLFFTparams.maxNumCores );
	System_printf("num of working cores: %d\n", VLFFTparams.numCoresForFftCompute );
	System_printf("total size FFT: %d\n", VLFFTparams.N );
	System_printf("1st iter FFT: %d\n", VLFFTparams.N1);
	System_printf("2nd iter FFT: %d\n", VLFFTparams.N2);
#endif

#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg1(pSTMHandle, STM_CHAN_DEFAULT, "Maximum number of cores: %d\0", VLFFTparams.maxNumCores);
	STMXport_logMsg1(pSTMHandle, STM_CHAN_DEFAULT, "Number of cores used: %d\0", VLFFTparams.numCoresForFftCompute);
	STMXport_logMsg1(pSTMHandle, STM_CHAN_DEFAULT, "FFT Size: %d\0", VLFFTparams.N);
	STMXport_logMsg1(pSTMHandle, STM_CHAN_DEFAULT, "First Pass Size: %d\0", VLFFTparams.N1);
	STMXport_logMsg1(pSTMHandle, STM_CHAN_DEFAULT, "Second Pass Size: %d\0", VLFFTparams.N2);
#endif

    /******************************************************/
    /*         init message Q                             */
    /******************************************************/
    /* Create the local message queue */
    messageQParams.messageQ = MessageQ_create(localQueueName, NULL);    
//System_printf("Msg Q created! \n");

    if (messageQParams.messageQ == NULL) {
        System_abort("MessageQ_create failed\n" );
    }
    initMessageQueues( &messageQParams, VLFFTparams.maxNumCores );

//System_printf("Ques initiated! \n");


    // initializing data
#ifdef ENABLE_PRINTF
    System_printf("Core0 start initializing data array\n");
#endif
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg(pSTMHandle, STM_CHAN_STATUS, "Begin Initializing Data Array\0");
#endif
    genFFTTestData( inData );
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg(pSTMHandle, STM_CHAN_STATUS, "Finish Initializing Data Array\0");
#endif
#ifdef ENABLE_PRINTF
    System_printf("Core0 finish initializing data array\n");
#endif





    /*******************************************************/
    /*    send messages to the rest of the cores to sync up*/
    /*******************************************************/
#ifdef ENABLE_PRINTF
    System_printf("Sync up all the cores \n");
#endif
    broadcastMessages(  &messageQParams, VLFFTparams.maxNumCores, VLFFTparams.maxNumCores, VLFFT_DO_NOTHING );


    /******************************************************/
    /*         receive messages from other cores          */
    /******************************************************/
    getAllMessages( &messageQParams, VLFFTparams.maxNumCores, VLFFTparams.maxNumCores );


#ifdef ENABLE_PRINTF
    System_printf("The test is starting! \n");
#endif

fftTime = 0.0;
//for(fftLoop=0; fftLoop<NUM_FFT_TO_COMPUTE; fftLoop++)
for(fftLoop=0; fftLoop<1; fftLoop++)
   {
#ifdef ENABLE_PRINTF
    System_printf("   start of loop: %d \n", fftLoop);
#endif
    /***********************************/
    /*    VLFFT computation start      */
    /***********************************/
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		STMXport_logMsg(pSTMHandle, STM_CHAN_BENCHMARK, "Start Processing FFT\0");
#endif

#if ENABLE_BENCHMARKING
    TSC_enable();
    timer0 = TSC_read();
#endif

    /********************************************************************/
    /*    send messages to others cores to start 1st iteration of ffts  */
    /********************************************************************/
    if( VLFFTparams.numCoresForFftCompute > 1 )
        broadcastMessages(  &messageQParams, VLFFTparams.numCoresForFftCompute, VLFFTparams.numCoresForFftCompute, VLFFT_PROCESS_1stITER );

    /***************************/
    /* 1st iter of FFT         */
    /***************************/
#if ENABLE_VLFFT_PROCESSING
    vlfftEdmaConfig_1stIter( &DMAparams);

    ptrIn  = inData;
    ptrOut = workBufExternal;
    VLFFT_1stIter( ptrIn, ptrOut, &VLFFTparams, &VLFFTbuffers, &DMAparams, 0);
#endif // #if ENABLE_VLFFT_PROCESSIN

    /******************************************************/
    /*         receive messages from other cores          */
    /******************************************************/
    if( VLFFTparams.numCoresForFftCompute > 1 )
        getAllMessages( &messageQParams, VLFFTparams.numCoresForFftCompute, VLFFTparams.numCoresForFftCompute );


    /**************************************************************/
    /*    send messages to others cores to start 2nd iteration    */
    /**************************************************************/
    if( VLFFTparams.numCoresForFftCompute > 1 )
        broadcastMessages(  &messageQParams, VLFFTparams.numCoresForFftCompute, VLFFTparams.numCoresForFftCompute, VLFFT_PROCESS_2ndITER );

    /***************************/
    /* 2nd iter of FFT         */
    /***************************/
#if ENABLE_VLFFT_PROCESSING
    vlfftEdmaConfig_2ndIter( &DMAparams);

    ptrIn  = workBufExternal;
    ptrOut = outData;
    VLFFT_2ndIter( ptrIn, ptrOut, &VLFFTparams, &VLFFTbuffers, &DMAparams, 0);
#endif  // #if ENABLE_VLFFT_PROCESSING

    if( VLFFTparams.numCoresForFftCompute > 1 )
        getAllMessages( &messageQParams, VLFFTparams.numCoresForFftCompute, VLFFTparams.numCoresForFftCompute );

#if ENABLE_BENCHMARKING
    timer1 = TSC_read();
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg(pSTMHandle, STM_CHAN_BENCHMARK, "End Processing FFT\0");
#endif
#endif


    fftTime     += (double)(timer1 - timer0)/1000000.0;

   }    //end of fftLoop

    /**************************************************************/
    /*    send messages to others cores to exit fft               */
    /**************************************************************/
    broadcastMessages(  &messageQParams, VLFFTparams.maxNumCores, VLFFTparams.maxNumCores, VLFFT_EXIT );


    /***********************************/
    /*                                 */
    /*    VLFFT computation finish     */
    /*                                 */
    /***********************************/
#ifdef ENABLE_PRINTF
    System_printf("The test is complete\n");
#endif
    printf("  Avg timer per fft  =    %f ms \n",  fftTime  );


    // compare vlfft result
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg(pSTMHandle, STM_CHAN_BENCHMARK, "Begin Library FFT for Comparison\0");
#endif
    dft(VLFFT_SIZE, inData, testData, 20);
#ifdef ENABLE_SYSTEM_TRACE_LOGS
	STMXport_logMsg(pSTMHandle, STM_CHAN_BENCHMARK, "End Library FFT for Comparison\0");
#endif
    if( compare_float( 20*2, outData, testData) == 0 ){
#ifdef ENABLE_PRINTF
         System_printf("   Success!!!   \n\n\n"  );
#endif
    }else{
#ifdef ENABLE_PRINTF
         System_printf("   Fail!!!   \n\n\n"  );
#endif
    }

    System_exit(0);

}





/*
 *  ======== tsk1_func ========
 *  This function is executed on every processor except on CORE0.
 *  It opens the heap created by CORE0 and registers it.
 *  A local message queue is created and a remote message queue is opened.
 *  Messages are sent to the remote message queue and retrieved from the
 *  local MessageQ.
 */
Void vlfft_slave(UArg arg0, UArg arg1)
{

    vlfftMessageQ_Msg     *msg;

    MessageQ_Handle  messageQ;
    MessageQ_QueueId core0QueueId;
    HeapBufMP_Handle heapHandle;
    Int              status;
    Uint32           mode;


    Uint32           coreNum;

    float            *ptrIn, *ptrOut;

    VLFFTparams_t    VLFFTparams;
    VLFFTbuffers_t   VLFFTbuffers;
    DMAparams_t      DMAparams;


    if (MultiProc_self() == 1) coreNum = 1;
    if (MultiProc_self() == 2) coreNum = 2;
    if (MultiProc_self() == 3) coreNum = 3;
    if (MultiProc_self() == 4) coreNum = 4;
    if (MultiProc_self() == 5) coreNum = 5;
    if (MultiProc_self() == 6) coreNum = 6;
    if (MultiProc_self() == 7) coreNum = 7;
    
    /******************************************************/
    /*         para init                                  */
    /******************************************************/
    vlfftParamsInit( &VLFFTparams, vlfft_w1, vlfft_w2, vlfft_twiddle, coreNum );
    vlfftBuffersInit( &VLFFTbuffers, inBuf,      outBuf,      workBuf0Internal, fftInBuf, fftOutBuf);
    DMAparamInit( &DMAparams, &VLFFTparams, coreNum );
    vlfftEdmaInit( &DMAparams);
//System_printf("Init done! \n");


    /**************************************************/
    /*                                                */
    /*         init message Q                         */
    /*                                                */
    /**************************************************/
    /* Open the heap created by the other processor. Loop until opened. */
    do {
        status = HeapBufMP_open(HEAP_NAME, &heapHandle);
    } while (status < 0);

//System_printf("Opened remote heap! \n");

    /* Register this heap with MessageQ */
    MessageQ_registerHeap((IHeap_Handle)heapHandle, HEAPID);

//System_printf("register newly opened heap! \n");

    /* Create the local message queue */
    messageQ = MessageQ_create(localQueueName, NULL);
//System_printf("Create the local msg Q! \n");

    if (messageQ == NULL) {
        System_abort("MessageQ_create failed\n" );
    }    
     
    /* Open the remote message queue. Spin until it is ready. */
    do {
        status = MessageQ_open(core0QueueName, &core0QueueId);        
    } while (status < 0);
//System_printf("Open the remote msg Q! \n");

    /* Allocate a message to be ping-ponged around the processors */
    msg = (vlfftMessageQ_Msg *)MessageQ_alloc(HEAPID, sizeof(vlfftMessageQ_Msg));
//System_printf("allocate a msg Q! \n");

#if DEBUG_DISPLAY
    if (msg == NULL) {
       System_abort("MessageQ_alloc failed\n" );
    }
#endif


#ifdef ENABLE_PRINTF
    System_printf("The test start!\n");
#endif
while(1)
    {
    /*
     *  Wait for a message from core0
     */
    status = MessageQ_get(messageQ, (MessageQ_Msg *)&msg, MessageQ_FOREVER);
#if DEBUG_DISPLAY
    if (status < 0) {
       System_abort("This should not happen since timeout is forever\n");
    }
    System_printf( "Receive 1st message from core0\n" );
#endif
//  MessageQ_getMsgId( (MessageQ_Msg *)msg );
    mode = msg->mode;



    // idle mode
    if(mode == VLFFT_DO_NOTHING)
    {
         msg->mode = VLFFT_PROCESS_1stITER;//VLFFT_OK;
#ifdef ENABLE_SYSTEM_TRACE_LOGS
         STMXport_logMsg(pSTMHandle, STM_CHAN_STATUS, "Initial Sync\0");
#endif
#ifdef ENABLE_PRINTF
         System_printf("vlfft initial sync\n"  );
#endif
      }

    // 1st iteration processing
    if(mode == VLFFT_PROCESS_1stITER)
      {
#if ENABLE_VLFFT_PROCESSING
            /******************************************************/
            /*      configure EDMA for 1st iteration of FFTs      */
            /******************************************************/
            vlfftEdmaConfig_1stIter( &DMAparams);

            ptrIn  = inData;
            ptrOut = workBufExternal;
            VLFFT_1stIter( ptrIn, ptrOut, &VLFFTparams, &VLFFTbuffers, &DMAparams, coreNum);
#endif 
            msg->mode = VLFFT_OK;
       }  // if(msg.mode == VLFFT_PROCESS_1stITER)


    // 2nd iteration processing
    if(mode == VLFFT_PROCESS_2ndITER)
      {
           /******************************************************/
           /*      configure EDMA for 2nd iteration of FFTs      */
           /******************************************************/
#if ENABLE_VLFFT_PROCESSING
            vlfftEdmaConfig_2ndIter( &DMAparams);

            ptrIn  = workBufExternal;
            ptrOut = outData;
            VLFFT_2ndIter( ptrIn, ptrOut, &VLFFTparams, &VLFFTbuffers, &DMAparams, coreNum);
#endif
            msg->mode = VLFFT_OK;
     }  // if(msg.mode == VLFFT_PROCESS_2ndITER)


    if(mode == VLFFT_EXIT){
#ifdef ENABLE_PRINTF
            System_printf("The test is complete!\n");
//          System_printf("\n\n");
#endif
#ifdef ENABLE_SYSTEM_TRACE_LOGS
    	STMXport_logMsg(pSTMHandle, STM_CHAN_STATUS, "Test Complete\0");
#endif
            System_exit(0);
      }
    /*********************************************/
    /* send the message to the remote processor  */
    /*********************************************/

#if DEBUG_DISPLAY
    System_printf( "    Sending a message to core0\n" );
#endif
    status = MessageQ_put(core0QueueId, (MessageQ_Msg)msg);
#if DEBUG_DISPLAY
    if (status < 0) {
       System_abort("MessageQ_put had a failure/error\n");
    }
#endif

  }  // while(1)



}


void vlfft_system_reset(void)
{
	/* The ROM bootloader sets the IE04 bit for IPC interrupt.
	 * This needs to be cleared for IPC.
	 */

	/* Clear interrupt enable register at startup */
    IER = 0;
}


/*
 *  ======== main ========
 *  Synchronizes all processors.
 *  CORE0 creates a HeapBufMP and registers it with MessageQ.
 *  Create the Task to send and receive messages.
 */
Int main(Int argc, Char* argv[])
{
    HeapBufMP_Handle              heapHandle;
    HeapBufMP_Params              heapBufParams;
    Task_Params      params;

    /* The ROM bootloader sets the IE04 bit for IPC interrupt.
     * This needs to be cleared for IPC.
    */
    /* Clear interrupt enable register at startup */
//  IER = 0;
#ifdef ENABLE_SYSTEM_TRACE_LOGS
		initializeSTM();
#endif
    /*  
     *  Ipc_start() calls Ipc_attach() to synchronize all remote processors
     *  because 'Ipc.procSync' is set to 'Ipc.ProcSync_ALL' in *.cfg
     */
    Ipc_start();

    if (MultiProc_self() == 0) {
#ifdef ENABLE_SYSTEM_TRACE_LOGS
    	STMXport_logMsg(pSTMHandle, STM_CHAN_DEFAULT, "BackToBackMsg\0");
		STMXport_logMsg(pSTMHandle, STM_CHAN_DEFAULT, "BackToBackMsg\0");
		STMXport_logMsg(pSTMHandle, STM_CHAN_DEFAULT, "BackToBackMsg\0");
#endif

#if !FUNCTIONAL_SIMULATOR
        clearRegisters(0);
#endif

        /* 
         *  Create the heap that will be used to allocate messages.
         */     
        HeapBufMP_Params_init(&heapBufParams);
        heapBufParams.regionId       = 0;
        heapBufParams.name           = HEAP_NAME;
        heapBufParams.numBlocks      = 24;
        heapBufParams.align          = 128;
        heapBufParams.blockSize      = sizeof(vlfftMessageQ_Msg);
        heapHandle = HeapBufMP_create(&heapBufParams);
        if (heapHandle == NULL) {
            System_abort("HeapBufMP_create failed\n" );
        }
        
        /* Register this heap with MessageQ */
        MessageQ_registerHeap((IHeap_Handle)heapHandle, HEAPID);
    }
    
    /* Generate queue names based on own proc ID and total number of procs */
    System_sprintf(localQueueName, "CORE%d", MultiProc_self());
    System_sprintf(core0QueueName, "CORE%d", 0               );
    System_sprintf(core1QueueName, "CORE%d", 1               );
    System_sprintf(core2QueueName, "CORE%d", 2               );
    System_sprintf(core3QueueName, "CORE%d", 3               );
    System_sprintf(core4QueueName, "CORE%d", 4               );
    System_sprintf(core5QueueName, "CORE%d", 5               );
    System_sprintf(core6QueueName, "CORE%d", 6               );
    System_sprintf(core7QueueName, "CORE%d", 7               );

    /* Create a unique 'master' Task if on proc 0 */
    Task_Params_init(&params);
    params.stackSize = 0x2000;
    if (MultiProc_self() == 0) {
      //Task_create(tsk0_func, NULL, NULL);
        Task_create(vlfft_master, &params, NULL);
    }
    else {
      //Task_create(tsk1_func, NULL, NULL);
        Task_create(vlfft_slave, &params, NULL);
    }
 
    BIOS_start();
    return (0);
}
/*
 *  @(#) ti.sdo.ipc.examples.multicore.c6474; 1, 0, 0, 0,93; 5-28-2010 14:20:04; /db/vtree/library/trees/ipc/ipc-e14x/dmaInSrc/
 */

