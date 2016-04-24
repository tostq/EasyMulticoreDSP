/****************************************************************************/
/*  C6678_unified.cmd                                                       */
/*  Copyright (c) 2011 Texas Instruments Incorporated                       */
/*													                                     						*/
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an C6678              */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

-stack 0x2000
-heap 0x8000

MEMORY
{
  LOCAL_L2_SRAM:  origin = 0x00800000 length = 0x00080000   /* 512kB LOCAL L2/SRAM */
  LOCAL_L1P_SRAM: origin = 0x00E00000 length = 0x00008000   /* 32kB LOCAL L1P/SRAM */
  LOCAL_L1D_SRAM: origin = 0x00F00000 length = 0x00008000   /* 32kB LOCAL L1D/SRAM */
  SHRAM:          origin = 0x0C000000 length = 0x00400000   /* 4MB Multicore shared Memmory */
  
  EMIF16_CS2:     origin = 0x70000000 length = 0x04000000   /* 64MB EMIF16 CS2 Data Memory */
  EMIF16_CS3:     origin = 0x74000000 length = 0x04000000   /* 64MB EMIF16 CS3 Data Memory */
  EMIF16_CS4:     origin = 0x78000000 length = 0x04000000   /* 64MB EMIF16 CS4 Data Memory */
  EMIF16_CS5:     origin = 0x7C000000 length = 0x04000000   /* 64MB EMIF16 CS5 Data Memory */

  DDR3:           origin = 0x80000000 length = 0x80000000   /* 2GB CE0 and CE1 external DDR3 SDRAM */
}
 
SECTIONS
{
	.text          >  SHRAM
	.stack         >  SHRAM
	.bss           >  SHRAM
	.cio           >  SHRAM
	.const         >  SHRAM
	.data          >  SHRAM
	.switch        >  SHRAM
	.sysmem        >  SHRAM
	.far           >  SHRAM
  .args          >  SHRAM
	.ppinfo        >  SHRAM
	.ppdata        >  SHRAM

  /* COFF sections */
	.pinit         >  SHRAM
	.cinit         >  SHRAM

  /* EABI sections */
  .binit         >  SHRAM
	.init_array    >  SHRAM
  .neardata      >  SHRAM
	.fardata       >  SHRAM
	.rodata        >  SHRAM
	.c6xabi.exidx  >  SHRAM
	.c6xabi.extab  >  SHRAM
}
