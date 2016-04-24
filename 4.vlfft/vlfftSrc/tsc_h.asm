* ========================================================================= *
*                                                                           *
*   TEXAS INSTRUMENTS, INC.                                                 *
*                                                                           *
*   NAME                                                                    *
*       tsc                                                                 *
*                                                                           *
*   PLATFORM                                                                *
*       C64xPLUS                                                            *
*S                                                                          *
*S                                                                          *
*S  REVISION HISTORY                                                        *
*S      30-Mar-2004 Initial version  . . . . . . . . . . .  Oliver Sohm     *
*                                                                           *
*   USAGE                                                                   *
*       These routines are C callable, and have the following C prototypes: *
*                                                                           *
*           void TSC_enable();                                              *
*           long long TSC_read();                                           *
*                                                                           *
*   DESCRIPTION                                                             *
*       TSC_enable: Enables the Time Stamp Counter                          *
*       TSC_read:   Reads the Time Stamp Counter and returns 64-bit count   *
*                                                                           *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2004 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *

* ------------------------------------------------------------------------- *
*  TSC_enable                                                               *
* ------------------------------------------------------------------------- *
	.global TSC_enable
	
TSC_enable: 

    RETNOP  B3, 4

    MVC     B4, TSCL     ; writing any value enables timer

    
* ------------------------------------------------------------------------- *
*  TSC_read                                                                 *
* ------------------------------------------------------------------------- *
	.global TSC_read

TSC_read: 

    RETNOP  B3, 2
    
    DINT               ; don't strictily need DINT/RINT because of branch 
||  MVC TSCL,   B4     ; Read the low half first; high half copied to TSCH

    MVC TSCH,   B5     ; Read the snapshot of the high half
||  RINT
||  MV  B4,  A4
    
    MV  B5,  A5
    
* ========================================================================= *
*   End of file:  tsc                                                       *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2004 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *
