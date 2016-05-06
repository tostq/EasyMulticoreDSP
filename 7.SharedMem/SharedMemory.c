#include<xdc/std.h>
#include<stdio.h>
#include<stdlib.h>

/*  -----------------------------------XDC.RUNTIME module Headers    */
#include <xdc/runtime/System.h>
#include <ti/sysbios/hal/Cache.h>

/*  ----------------------------------- IPC module Headers           */
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/Notify.h>
#include <xdc/runtime/IHeap.h>
#include <ti/ipc/Ipc.h>
/*  ----------------------------------- BIOS6 module Headers         */
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>

/*  ----------------------------------- To get globals from .cfg Header */
#include <xdc/cfg/global.h>
#include <xdc/runtime/Memory.h>
#include <ti/ipc/SharedRegion.h>

#define INTERRUPT_LINE  0
#define BufEVENT 10

#define dateNum 8 //76800

unsigned char *inBuf=NULL;
SharedRegion_SRPtr inBuf_srptr;

/*
 *  ======== cbFxn ========
 *  这是Notify模块的注册函数
 *  procId表示激动注册函数的核ID，或者说该事件是从哪个核来的
 */
Void cbFxn(UInt16 procId, UInt16 lineId,
           UInt32 eventId, UArg arg, UInt32 payload)
{
	inBuf_srptr=(SharedRegion_SRPtr)payload;
	Semaphore_post(semHandle);
}

/*
 *  ======== tsk0_func ========
 *  Sends an event to the next processor then pends on a semaphore.
 *  The semaphore is posted by the callback function.
 */
Void tsk0_func(UArg arg0, UArg arg1)
{
    Int status;
    Int i;

    int coreId=MultiProc_self();

    // 分配内存
    if (coreId == 0) {

    	inBuf = (unsigned char*)Memory_alloc(SharedRegion_getHeap(0), dateNum, 128, NULL);

    	if(inBuf==NULL)
    	{
    		System_printf("malloc Buf failed\n");
    		BIOS_exit(0);
    	}

    	for(i=0;i<dateNum;i++){  // 写入数据
    		inBuf[i]=i*3+5;
    	}

    	inBuf_srptr = SharedRegion_getSRPtr(inBuf, 0);

    	System_printf("inBuf address 0x%x\n",inBuf);
    	System_printf("outBuf date is ");
    	for(i=0;i<dateNum;i++)
    		System_printf("%d ",inBuf[i]);
    	System_printf("\n");

    	Cache_wbAll();// Write back all caches();

    	for(i=1;i<8;i++)
    		status = Notify_sendEvent(i, INTERRUPT_LINE, BufEVENT, (UInt32)inBuf_srptr, TRUE);



    }else{

    	Semaphore_pend(semHandle, BIOS_WAIT_FOREVER); // 等待从核完成全部任务

    	Cache_disable(Cache_Type_ALL);

    	inBuf=SharedRegion_getPtr(inBuf_srptr);
    	System_printf("inBuf address 0x%x\n",inBuf);
    	System_printf("regionId is %d\n",SharedRegion_getId(inBuf));  // 打印当前共享区域ID
    	System_printf("outBuf date is ");
    	for(i=0;i<dateNum;i++)
    		System_printf("%d ",inBuf[i]);
    	System_printf("\n");
    }
    // 各核完成任务后可以退出了
    System_printf("SharedMem is finished\n");
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

    /*
     *  Ipc_start() calls Ipc_attach() to synchronize all remote processors
     *  because 'Ipc.procSync' is set to 'Ipc.ProcSync_ALL' in *.cfg
     */
    status = Ipc_start();
    if (status < 0) {
        System_abort("Ipc_start failed\n");
    }

    if (MultiProc_self() == 0) {
    	Int i;
    	for(i=1;i<8;i++)
    		status = Notify_registerEvent(i, INTERRUPT_LINE, BufEVENT,
    	    	    				(Notify_FnNotifyCbck)cbFxn, NULL);
    }else{
    	// 从核完成事件注册
    	status = Notify_registerEvent(0, INTERRUPT_LINE, BufEVENT,
    	    				(Notify_FnNotifyCbck)cbFxn, NULL);
    }

    BIOS_start();

    return (0);
}

/*
 */
/*
 *  @(#) ti.sdo.ipc.examples.multicore.evm667x; 1, 0, 0, 0,1; 5-22-2012 16:36:06; /db/vtree/library/trees/ipc/ipc-h32/src/ xlibrary

 */
