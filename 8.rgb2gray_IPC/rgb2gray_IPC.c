/* 
 *  ======== rgb2gray_IPC.c ========
 *  这是一个图像彩色转灰度的多核DSP程序
 *  这种程序将图像分为八块，C6678每个核操作其中一块图像
 *  主核（核0）将图像内存读入共享内存，各从核等待主核将内存读入后，开始处理任务
 *  当各从核完成图像块转换后，主核将数据存储，并完成内存释放
 */

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
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/HeapBufMP.h>
#include <xdc/runtime/Memory.h>
#include <ti/ipc/SharedRegion.h>

#define INTERRUPT_LINE  0

/* 定义颜色 */
#define CV_BGR2GRAY 0

/* 定义主核 */
#define masterProc 0
#define BufEVENT 10
#define heapId 0

#define coreNum 8
#define dateNum 16 //12900 16  //8 //
UInt16 recSlvNum = 0; // 表示主核接收到的从核回复次数

UInt16 srcProc, dstProc;
unsigned char *inBuf=NULL;
unsigned char *outBuf=NULL;

String CoreName[8]={"MessageQ_Core0","MessageQ_Core1","MessageQ_Core2","MessageQ_Core3",
		"MessageQ_Core4","MessageQ_Core5","MessageQ_Core6","MessageQ_Core7"};


typedef struct MyMsg {
	MessageQ_MsgHeader header;
	SharedRegion_SRPtr inBuf_SRPtr;
	SharedRegion_SRPtr outBuf_SRPtr;
} MyMsg;

/*
 *  ======== AcCvtColor ========
 *  这是一个图像RGB转换为灰度图像的程序
 *  Image1是RGB图像，每个颜色通道为8位，三个颜色依次排列
 *  Image2是灰度图像
 *  coder表示转换模式，主要为以后扩展.
 */

void AcCvtColor(unsigned char* image1,unsigned char* image2,int coder)
{
	Int red,green,blue,gray;
	Int coreId=MultiProc_self();
	if(coder==CV_BGR2GRAY)
	{
		Int BlockSize=dateNum/coreNum;
		Int i;
		for(i=coreId*BlockSize;i<(coreId+1)*BlockSize;i++)
			{
				red=image1[i*3];
				green=image1[i*3+1];
				blue=image1[i*3+2];
				gray=(red*76+green*150+blue*30)>>8;
				image2[i]=(unsigned char)gray;
			}
	}
}

/*
 *  ======== cbFxn ========
 *  这是Notify模块的注册函数
 *  procId表示激动注册函数的核ID，或者说该事件是从哪个核来的
 */
static UInt16 recCoreNum=0;
Void cbFxn(UInt16 procId, UInt16 lineId,
           UInt32 eventId, UArg arg, UInt32 payload)
{
	if(procId!=0)
	{
		recCoreNum++;
		if(recCoreNum==7)
			Semaphore_post(semHandle);
	}else{
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
    MyMsg     *msg;            // 消息
    MessageQ_Handle  messageQ;       // 消息队列句柄
    MessageQ_Params  messageQParams; // 消息队列参数

    HeapBufMP_Handle heapHandle;  // 堆句柄
    HeapBufMP_Params heapBufParams;  // 堆参数

    SharedRegion_SRPtr inBuf_srptr;  // 输入缓冲区在共享区域的指针
    SharedRegion_SRPtr outBuf_srptr; // 输出缓冲区在共享区域的指针


    int coreId=MultiProc_self();

    if (coreId != 0){  // 从核，创建消息队列
    	MessageQ_Params_init(&messageQParams);
    	messageQ = MessageQ_create(CoreName[coreId], &messageQParams);
    	if(messageQ==NULL)
    		System_printf("MessageQ core%d create is failed \n",coreId);
    	System_printf("MessageQ core%d create is finished \n",coreId);
    }else{
    	// 创建堆，给消息分配空间
        HeapBufMP_Params_init(&heapBufParams);
        heapBufParams.regionId       = 0;
        heapBufParams.name           = "Msg_Heap";
        heapBufParams.numBlocks      = 1;             // 1个块
        heapBufParams.blockSize      = sizeof(MyMsg); // 块的大小刚好是一个消息长度
        heapHandle = HeapBufMP_create(&heapBufParams);
        if (heapHandle == NULL) {
            System_abort("HeapBufMP_create failed\n" );
        }

        int status = MessageQ_registerHeap(heapHandle,heapId);
        if (status == MessageQ_E_ALREADYEXISTS){
        	System_abort("heap already exists with heapId\n" );
        }
	    System_printf("MessageQ registerHeap finished\n");
        msg = (MyMsg*)MessageQ_alloc(heapId, sizeof(MyMsg));
        if (msg == NULL) {
        	System_abort("MessageQ_alloc failed\n");
        }
        System_printf("MessageQ alloc finished\n");
    }
    // 分配内存
    if (MultiProc_self() == 0) {

    	Int i;

    	inBuf = (unsigned char*)Memory_alloc(SharedRegion_getHeap(0), dateNum*3, 0, NULL);
    	outBuf = (unsigned char*)Memory_alloc(SharedRegion_getHeap(0), dateNum, 0, NULL);

    	if(inBuf==NULL||outBuf==NULL)
    	{
    		System_printf("malloc Buf failed\n");
    		BIOS_exit(0);
    	}


    	// 打开文件
    	/*
    	FILE  *fp=NULL;
    	fp=fopen("E:\\Code\\CCS\\workspace_v5_2\\rgb2gray_IPC\\test.rgb","rb");
    	if(fp==NULL)
    		printf("open file failed\n");
    	fread(inBuf,dateNum*3,1,fp); // 将图像数据读入输入缓冲区
*/


    	for(i=0;i<dateNum;i++){  // 这里dateNum=16
    		inBuf[i*3]=i*10+10;
    		inBuf[i*3+1]=i*10+30;
    		inBuf[i*3+2]=i*10+50;
    	}


    	inBuf_srptr = SharedRegion_getSRPtr(inBuf, 0);
    	outBuf_srptr = SharedRegion_getSRPtr(outBuf, 0);

    	msg->inBuf_SRPtr = inBuf_srptr;  // 消息打包
    	msg->outBuf_SRPtr = outBuf_srptr;

    	Cache_wbAll();// Write back all caches();

    	//System_printf("finish msg config\n");

    	System_printf("core%d inBuf address 0x%x\n",coreId,inBuf);
    	System_printf("core%d outBuf address 0x%x\n",coreId,outBuf);

    	for(i=1;i<8;i++){  // 7个消息队列都需要发送消息
    	    MessageQ_QueueId* sloverCoreQueueId;
    	    int status;
    	    do{ // 等待，直到打开MessageQ
    	    	status= MessageQ_open(CoreName[i], sloverCoreQueueId);
    	    	if (status < 0)
    	    	    Task_sleep(1);
    	    }while (status < 0);
    	    status = MessageQ_put(*sloverCoreQueueId, (MessageQ_Msg)msg);
    	    if (status < 0)
    	    	System_abort("MessageQ_put was not successful\n");

    	    do{ // 等待，直到关闭MessageQ
    	        status= MessageQ_close(sloverCoreQueueId);
    	        if (status < 0)
    	        	Task_sleep(1);
    	    }while (status < 0);
    	}

    	Cache_disable(Cache_Type_ALL);

    	AcCvtColor(inBuf,outBuf,CV_BGR2GRAY); // 分核完成图像灰度转换任务

    	Cache_wbAll(); // Write back all caches();

    	Semaphore_pend(semHandle, BIOS_WAIT_FOREVER); // 等待从核完成全部任务

    	Cache_inv(outBuf,sizeof(outBuf),Cache_Type_ALL,TRUE);
    	Cache_wait();

    	System_printf("outBuf date is ");
    	for(i=0;i<dateNum;i++)
    		System_printf("%d ",outBuf[i]);
    	System_printf("\n");

/* 写入图像数据
    	// 保存输出图像
    	FILE  *fq=NULL;
    	fq=fopen("E:\\Code\\CCS\\workspace_v5_2\\rgb2gray_IPC\\test.rgb","wb");
    	if(fq==NULL)
    		printf("write file failed\n");
    	fwrite(outBuf,sizeof(outBuf),1,fq);
    	*/

    	for(i=1;i<8;i++)
    		Notify_sendEvent(i, INTERRUPT_LINE, BufEVENT, 0, TRUE);


    }else{

    	int status = MessageQ_get(messageQ, (MessageQ_Msg *)&msg, MessageQ_FOREVER);
    	if (status < 0)
    		System_abort("This should not happen since timeout is forever\n");
    	inBuf_srptr = msg->inBuf_SRPtr;
    	outBuf_srptr = msg->outBuf_SRPtr;

    	System_printf("MessageQ get is finished \n");

    	Cache_disable(Cache_Type_ALL);

    	/*
    	status = MessageQ_free((MessageQ_Msg)msg);
    	if (status < 0)
    		System_abort("Message free failed\n");

    	System_printf("MessageQ free is finished \n");
    	*/

    	/*
    	status = MessageQ_delete(&messageQ);
    	if (status < 0)
    		System_abort("MessageQ delete failed\n");

    	System_printf("MessageQ delete is finished \n");
    	*/

    	inBuf = SharedRegion_getPtr(inBuf_srptr);
    	outBuf = SharedRegion_getPtr(outBuf_srptr);

    	//System_printf("core%d inBuf address 0x%x\n",coreId,inBuf);
    	//System_printf("core%d outBuf address 0x%x\n",coreId,outBuf);

    	AcCvtColor(inBuf,outBuf,CV_BGR2GRAY); // 分核完成图像灰度转换任务

    	Cache_wbAll(); // Write back all caches();

    	//System_printf("core%d : indate is %d,outdate is %d\n",coreId,inBuf[coreId*3],outBuf[coreId]);

    	// Write back all caches();
    	status = Notify_sendEvent(0, INTERRUPT_LINE, BufEVENT, 0, TRUE);

    	//System_printf("core%d sendEvent finished,status is %d\n",coreId,status);
        if (status < 0) {
            System_abort("sendEvent to MasterCore failed\n");
        }

        Semaphore_pend(semHandle, BIOS_WAIT_FOREVER); // 等待从核完成全部任务
    }
    // 各核完成任务后可以退出了
    System_printf("Rgb2Gray is finished\n");
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

    	System_printf("registerEvent status is %d\n",status);

    }

    BIOS_start();

    return (0);
}

/*
 */
/*
 *  @(#) ti.sdo.ipc.examples.multicore.evm667x; 1, 0, 0, 0,1; 5-22-2012 16:36:06; /db/vtree/library/trees/ipc/ipc-h32/src/ xlibrary

 */
