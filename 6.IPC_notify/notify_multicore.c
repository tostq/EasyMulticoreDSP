/* 
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 *  ======== notify_multicore.c ========
 *  Single-image version of Notify example
 *
 *  See notify_multicore.k file for expected output.
 */

#include <xdc/std.h>

/*  -----------------------------------XDC.RUNTIME module Headers    */
#include <xdc/runtime/System.h>

/*  ----------------------------------- IPC module Headers           */
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/Notify.h>
#include <ti/ipc/Ipc.h>
/*  ----------------------------------- BIOS6 module Headers         */
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>

/*  ----------------------------------- To get globals from .cfg Header */
#include <xdc/cfg/global.h>

#define INTERRUPT_LINE  0

/* Notify event number that the app uses */
#define EVENTID         10

/* Number of times to run the loop */
#define NUMLOOPS        5

UInt32 times = 0;
UInt16 recvnumes = 0;

#define masterProc 0
#define sloverProc1 1
#define sloverProc2 2
#define sloverNum 2

/*
 *  ======== cbFxn ========
 *  This function was registered with Notify. It is called when any event is
 *  sent to this processor.
 */
Void cbFxn(UInt16 procId, UInt16 lineId,
           UInt32 eventId, UArg arg, UInt32 payload)
{
    /* The payload is a sequence number. */

	if(procId!=masterProc) // 主核注册函数
	{
		recvnumes++;  // 接收从核的数目
    	if(recvnumes==sloverNum) // 当收到全部从核回复的信息
    	{
    		recvnumes=0;
    		Semaphore_post(semHandle);
    	}
	}
	else{
		times = payload; // 执行次数
		Semaphore_post(semHandle);
	}
}


/*
 *  ======== tsk0_func ========
 *  Sends an event to the next processor then pends on a semaphore.
 *  The semaphore is posted by the callback function.
 */
Void tsk0_func(UArg arg0, UArg arg1)
{
    Int i = 1;
    Int status;
    
    if (MultiProc_self() == masterProc) {
        while (i <= NUMLOOPS) {

        	/* 这里可以添加主核需要执行的任务代码*/

            /* Send an event to the next processor */
            status = Notify_sendEvent(sloverProc1, INTERRUPT_LINE, EVENTID, i,
                    TRUE);
            status = Notify_sendEvent(sloverProc2, INTERRUPT_LINE, EVENTID, i,
                                TRUE);

            /* Continue until remote side is up */
            if (status < 0) {
                continue;
            }

            System_printf("MasterCore Sent Event to SloverCores in %d\n", i);

            /* Wait to be released by the cbFxn posting the semaphore */
            Semaphore_pend(semHandle, BIOS_WAIT_FOREVER); // 主核等待所有从核完成其工作返回

            System_printf("MasterCore Received Event from All SloverCores in %d\n",i);

            /* increment for next iteration */
            i++;
        }
    }
    else {
        while (times < NUMLOOPS) {

            /* wait forever on a semaphore, semaphore is posted in callback */
            Semaphore_pend(semHandle, BIOS_WAIT_FOREVER); // 等待主核通知开始执行任务

            System_printf("SloverCore%d Received Event from MasterCore in %d\n", MultiProc_self(),times);

            /* 这里可以添加从核执行的任务*/

            /* Send an event to the next processor */
            status = Notify_sendEvent(masterProc, INTERRUPT_LINE, EVENTID, times,
                    TRUE);
            if (status < 0) {
                System_abort("sendEvent to MasterCore failed\n");
            }

            System_printf("SloverCore%d sent Event from MasterCore in %d\n", MultiProc_self(),times);
        }
    }

    System_printf("Test completed\n");
    BIOS_exit(0);
}

/*
 *  ======== main ========
 *  Synchronizes all processors (in Ipc_start), calls BIOS_start, and registers 
 *  for an incoming event
 */
Int main(Int argc, Char* argv[])
{
    Int status;

    status = Ipc_start();
    if (status < 0) {
        System_abort("Ipc_start failed\n");
    }

    if(MultiProc_self()==masterProc)
    {
    	while(Ipc_attach(sloverProc1)){
    		Task_sleep(1);
    	}// 完成从核1的连接
    	while(Ipc_attach(sloverProc2)){
    	    Task_sleep(1);
    	}// 完成从核2的连接

        status = Notify_registerEvent(sloverProc1, INTERRUPT_LINE, EVENTID,
                                      (Notify_FnNotifyCbck)cbFxn, NULL);
        if (status < 0) {
            System_abort("Notify_registerEvent for sloverCore1 failed\n");
        }// 完成从核1的事件注册

        status = Notify_registerEvent(sloverProc2, INTERRUPT_LINE, EVENTID,
                                      (Notify_FnNotifyCbck)cbFxn, NULL);
        if (status < 0) {
            System_abort("Notify_registerEvent for sloverCore2 failed \n");
        }// 完成从核2的事件注册

    }
    else{

    	while(Ipc_attach(masterProc)){
    	    Task_sleep(1);
    	}// 完成主核0的连接

        status = Notify_registerEvent(masterProc, INTERRUPT_LINE, EVENTID,
                                      (Notify_FnNotifyCbck)cbFxn, NULL);
        if (status < 0) {
            System_abort("Notify_registerEvent for masterCore0 failed\n");
        }// 完成主核0的事件注册

    }

    BIOS_start();
    
    return (0);
}

/*
 */
/*
 *  @(#) ti.sdo.ipc.examples.multicore.evm667x; 1, 0, 0, 0,1; 5-22-2012 16:36:06; /db/vtree/library/trees/ipc/ipc-h32/src/ xlibrary

 */

