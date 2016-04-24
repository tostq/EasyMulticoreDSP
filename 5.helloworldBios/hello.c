/*
 *  ======== hello.c ========
 *  The hello example serves as a basic sanity check program for SYS/BIOS. It
 *  demonstrates how to print the string "hello world" to stdout. 
 */

#include <xdc/std.h>
#include <ti/sysbios/knl/Swi.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <ti/sysbios/knl/Clock.h>

Swi_Handle swi0;
Semaphore_Handle sem0;
void func_tsk0(void);
void func_tsk1(void);
void func_swi0(void);
void func_clk(UArg arg0);
/*
 *  ======== main ========
 */
Void main()
{ 
    System_printf("hello world\n");


    Swi_Params swiParams;
    Swi_Params_init(&swiParams);
    swiParams.priority = 2;
    swiParams.trigger = 2;

    swi0 = Swi_create(func_swi0, &swiParams, NULL);


    Clock_Params clkParams;
    Clock_Params_init(&clkParams);
    clkParams.period = 5;
    clkParams.startFlag = TRUE;
    Clock_create(func_clk, 5, &clkParams, NULL);

    sem0 = Semaphore_create(0, NULL, NULL);

    BIOS_start();
}

void func_clk(UArg arg0)
{
	UInt32 time;

	time = Clock_getTicks();
	System_printf("System time in func_clk = %lu\n", (ULong)time);
    if(time>20)
    	BIOS_exit(0);
}

void func_swi0(void)
{
	static Int count = 0;
	Log_info1("Swi0 is doing %d\n",count);
	count++;
	Semaphore_post(sem0);
}

void func_tsk0(void)
{
	Int count = 0;
    while(1){
    //while(count<10){
    	Semaphore_pend(sem0, BIOS_WAIT_FOREVER);
        Log_info1("Task0 is doing %d\n",count);
        Swi_dec(swi0);
        Task_yield();
        count++;
    }
    //BIOS_exit(0);
}

void func_tsk1(void)
{
    Int count = 0;
    while(1){
    //while(count<10){
    	Log_info1("Task1 is doing %d\n",count);
    	Swi_dec(swi0);
    	Task_yield();
    	count++;
    }
    //BIOS_exit(0);
}
