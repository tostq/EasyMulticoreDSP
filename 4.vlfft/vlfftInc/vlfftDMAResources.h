/*
 * vlfftDMAResources.h
 *
 *    This file contains constants defining DMA resources for multicore FFT
 *    implementation.
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


// core0 EDMA parameters
#define VLFFT_CORE0_IN_DMA_CHANNEL  0
#define VLFFT_CORE0_OUT_DMA_CHANNEL 1
#define VLFFT_CORE0_INTR_NUM        0
#define VLFFT_CORE0_OUT_INTR_NUM    1

#define VLFFT_CORE0_InPaRAM         1
#define VLFFT_CORE0_InPaRAM_PING    2
#define VLFFT_CORE0_InPaRAM_PONG    3

#define VLFFT_CORE0_OutPaRAM        4
#define VLFFT_CORE0_OutPaRAM_PING   5
#define VLFFT_CORE0_OutPaRAM_PONG   6

// core1 EDMA parameters
#define VLFFT_CORE1_IN_DMA_CHANNEL  2
#define VLFFT_CORE1_OUT_DMA_CHANNEL 3
#define VLFFT_CORE1_INTR_NUM        2
#define VLFFT_CORE1_OUT_INTR_NUM    3

#define VLFFT_CORE1_InPaRAM         7
#define VLFFT_CORE1_InPaRAM_PING    8
#define VLFFT_CORE1_InPaRAM_PONG    9

#define VLFFT_CORE1_OutPaRAM        10
#define VLFFT_CORE1_OutPaRAM_PING   11
#define VLFFT_CORE1_OutPaRAM_PONG   12

// core2 EDMA parameters
#define VLFFT_CORE2_IN_DMA_CHANNEL  4
#define VLFFT_CORE2_OUT_DMA_CHANNEL 5
#define VLFFT_CORE2_INTR_NUM        4
#define VLFFT_CORE2_OUT_INTR_NUM    5

#define VLFFT_CORE2_InPaRAM         13
#define VLFFT_CORE2_InPaRAM_PING    14
#define VLFFT_CORE2_InPaRAM_PONG    15

#define VLFFT_CORE2_OutPaRAM        16
#define VLFFT_CORE2_OutPaRAM_PING   17
#define VLFFT_CORE2_OutPaRAM_PONG   18

// core3 EDMA parameters
#define VLFFT_CORE3_IN_DMA_CHANNEL  6
#define VLFFT_CORE3_OUT_DMA_CHANNEL 7
#define VLFFT_CORE3_INTR_NUM        6
#define VLFFT_CORE3_OUT_INTR_NUM    7

#define VLFFT_CORE3_InPaRAM         19
#define VLFFT_CORE3_InPaRAM_PING    20
#define VLFFT_CORE3_InPaRAM_PONG    21

#define VLFFT_CORE3_OutPaRAM        22
#define VLFFT_CORE3_OutPaRAM_PING   23
#define VLFFT_CORE3_OutPaRAM_PONG   24

// core4 EDMA parameters
#define VLFFT_CORE4_IN_DMA_CHANNEL  8
#define VLFFT_CORE4_OUT_DMA_CHANNEL 9
#define VLFFT_CORE4_INTR_NUM        8
#define VLFFT_CORE4_OUT_INTR_NUM    9

#define VLFFT_CORE4_InPaRAM         25
#define VLFFT_CORE4_InPaRAM_PING    26
#define VLFFT_CORE4_InPaRAM_PONG    27

#define VLFFT_CORE4_OutPaRAM        28
#define VLFFT_CORE4_OutPaRAM_PING   29
#define VLFFT_CORE4_OutPaRAM_PONG   30

// core5 EDMA parameters
#define VLFFT_CORE5_IN_DMA_CHANNEL  10
#define VLFFT_CORE5_OUT_DMA_CHANNEL 11
#define VLFFT_CORE5_INTR_NUM        10
#define VLFFT_CORE5_OUT_INTR_NUM    11

#define VLFFT_CORE5_InPaRAM         31
#define VLFFT_CORE5_InPaRAM_PING    32
#define VLFFT_CORE5_InPaRAM_PONG    33

#define VLFFT_CORE5_OutPaRAM        34
#define VLFFT_CORE5_OutPaRAM_PING   35
#define VLFFT_CORE5_OutPaRAM_PONG   36

// core6 EDMA parameters
#define VLFFT_CORE6_IN_DMA_CHANNEL  12
#define VLFFT_CORE6_OUT_DMA_CHANNEL 13
#define VLFFT_CORE6_INTR_NUM        12
#define VLFFT_CORE6_OUT_INTR_NUM    13

#define VLFFT_CORE6_InPaRAM         37
#define VLFFT_CORE6_InPaRAM_PING    38
#define VLFFT_CORE6_InPaRAM_PONG    39

#define VLFFT_CORE6_OutPaRAM        40
#define VLFFT_CORE6_OutPaRAM_PING   41
#define VLFFT_CORE6_OutPaRAM_PONG   42

// core7 EDMA parameters
#define VLFFT_CORE7_IN_DMA_CHANNEL  14
#define VLFFT_CORE7_OUT_DMA_CHANNEL 15
#define VLFFT_CORE7_INTR_NUM        14
#define VLFFT_CORE7_OUT_INTR_NUM    15

#define VLFFT_CORE7_InPaRAM         43
#define VLFFT_CORE7_InPaRAM_PING    44
#define VLFFT_CORE7_InPaRAM_PONG    45

#define VLFFT_CORE7_OutPaRAM        46
#define VLFFT_CORE7_OutPaRAM_PING   47
#define VLFFT_CORE7_OutPaRAM_PONG   48


#define CORE0_L2SRAM_GLOBAL_ADDR_OFFSET 0x10000000
#define CORE1_L2SRAM_GLOBAL_ADDR_OFFSET 0x11000000
#define CORE2_L2SRAM_GLOBAL_ADDR_OFFSET 0x12000000
#define CORE3_L2SRAM_GLOBAL_ADDR_OFFSET 0x13000000
#define CORE4_L2SRAM_GLOBAL_ADDR_OFFSET 0x14000000
#define CORE5_L2SRAM_GLOBAL_ADDR_OFFSET 0x15000000
#define CORE6_L2SRAM_GLOBAL_ADDR_OFFSET 0x16000000
#define CORE7_L2SRAM_GLOBAL_ADDR_OFFSET 0x17000000


#if ENABLE_DMA_TRANSPOSE
// core0 EDMA parameters for transpose0 operation
#define VLFFT_CORE0_TRANSPOSE0_DMA_CHANNEL  16
#define VLFFT_CORE0_TRANSPOSE0_DMA_INTR_NUM 16
#define VLFFT_CORE0_TRANSPOSE0_DMA_PaRAM    49

// core1 EDMA parameters for transpose0 operation
#define VLFFT_CORE1_TRANSPOSE0_DMA_CHANNEL  17
#define VLFFT_CORE1_TRANSPOSE0_DMA_INTR_NUM 17
#define VLFFT_CORE1_TRANSPOSE0_DMA_PaRAM    50

// core2 EDMA parameters for transpose0 operation
#define VLFFT_CORE2_TRANSPOSE0_DMA_CHANNEL  18
#define VLFFT_CORE2_TRANSPOSE0_DMA_INTR_NUM 18
#define VLFFT_CORE2_TRANSPOSE0_DMA_PaRAM    51

// core3 EDMA parameters for transpose0 operation
#define VLFFT_CORE3_TRANSPOSE0_DMA_CHANNEL  19
#define VLFFT_CORE3_TRANSPOSE0_DMA_INTR_NUM 19
#define VLFFT_CORE3_TRANSPOSE0_DMA_PaRAM    52

// core4 EDMA parameters for transpose0 operation
#define VLFFT_CORE4_TRANSPOSE0_DMA_CHANNEL  20
#define VLFFT_CORE4_TRANSPOSE0_DMA_INTR_NUM 20
#define VLFFT_CORE4_TRANSPOSE0_DMA_PaRAM    53

// core5 EDMA parameters for transpose0 operation
#define VLFFT_CORE5_TRANSPOSE0_DMA_CHANNEL  21
#define VLFFT_CORE5_TRANSPOSE0_DMA_INTR_NUM 21
#define VLFFT_CORE5_TRANSPOSE0_DMA_PaRAM    54

// core6 EDMA parameters for transpose0 operation
#define VLFFT_CORE6_TRANSPOSE0_DMA_CHANNEL  22
#define VLFFT_CORE6_TRANSPOSE0_DMA_INTR_NUM 22
#define VLFFT_CORE6_TRANSPOSE0_DMA_PaRAM    55

// core7 EDMA parameters for transpose0 operation
#define VLFFT_CORE7_TRANSPOSE0_DMA_CHANNEL  23
#define VLFFT_CORE7_TRANSPOSE0_DMA_INTR_NUM 23
#define VLFFT_CORE7_TRANSPOSE0_DMA_PaRAM    56


// core0 EDMA parameters for transpose1 operation
#define VLFFT_CORE0_TRANSPOSE1_DMA_CHANNEL  24
#define VLFFT_CORE0_TRANSPOSE1_DMA_INTR_NUM 24
#define VLFFT_CORE0_TRANSPOSE1_DMA_PaRAM    57

// core1 EDMA parameters for transpose1 operation
#define VLFFT_CORE1_TRANSPOSE1_DMA_CHANNEL  25
#define VLFFT_CORE1_TRANSPOSE1_DMA_INTR_NUM 25
#define VLFFT_CORE1_TRANSPOSE1_DMA_PaRAM    58

// core2 EDMA parameters for transpose1 operation
#define VLFFT_CORE2_TRANSPOSE1_DMA_CHANNEL  26
#define VLFFT_CORE2_TRANSPOSE1_DMA_INTR_NUM 26
#define VLFFT_CORE2_TRANSPOSE1_DMA_PaRAM    59

// core3 EDMA parameters for transpose1 operation
#define VLFFT_CORE3_TRANSPOSE1_DMA_CHANNEL  27
#define VLFFT_CORE3_TRANSPOSE1_DMA_INTR_NUM 27
#define VLFFT_CORE3_TRANSPOSE1_DMA_PaRAM    60

// core4 EDMA parameters for transpose1 operation
#define VLFFT_CORE4_TRANSPOSE1_DMA_CHANNEL  28
#define VLFFT_CORE4_TRANSPOSE1_DMA_INTR_NUM 28
#define VLFFT_CORE4_TRANSPOSE1_DMA_PaRAM    61

// core5 EDMA parameters for transpose1 operation
#define VLFFT_CORE5_TRANSPOSE1_DMA_CHANNEL  29
#define VLFFT_CORE5_TRANSPOSE1_DMA_INTR_NUM 29
#define VLFFT_CORE5_TRANSPOSE1_DMA_PaRAM    62

// core6 EDMA parameters for transpose1 operation
#define VLFFT_CORE6_TRANSPOSE1_DMA_CHANNEL  30
#define VLFFT_CORE6_TRANSPOSE1_DMA_INTR_NUM 30
#define VLFFT_CORE6_TRANSPOSE1_DMA_PaRAM    63

// core7 EDMA parameters for transpose1 operation
#define VLFFT_CORE7_TRANSPOSE1_DMA_CHANNEL  31
#define VLFFT_CORE7_TRANSPOSE1_DMA_INTR_NUM 31
#define VLFFT_CORE7_TRANSPOSE1_DMA_PaRAM    64

#endif

#if ENABLE_TRANSPOSE_L1SRAM
// core0 EDMA parameters for transpose0 operation
#define VLFFT_CORE0_TRANSPOSE0_DMA_CHANNEL  16
#define VLFFT_CORE0_TRANSPOSE0_DMA_INTR_NUM 16
#define VLFFT_CORE0_TRANSPOSE0_DMA_PaRAM    49

// core1 EDMA parameters for transpose0 operation
#define VLFFT_CORE1_TRANSPOSE0_DMA_CHANNEL  17
#define VLFFT_CORE1_TRANSPOSE0_DMA_INTR_NUM 17
#define VLFFT_CORE1_TRANSPOSE0_DMA_PaRAM    50

// core2 EDMA parameters for transpose0 operation
#define VLFFT_CORE2_TRANSPOSE0_DMA_CHANNEL  18
#define VLFFT_CORE2_TRANSPOSE0_DMA_INTR_NUM 18
#define VLFFT_CORE2_TRANSPOSE0_DMA_PaRAM    51

// core3 EDMA parameters for transpose0 operation
#define VLFFT_CORE3_TRANSPOSE0_DMA_CHANNEL  19
#define VLFFT_CORE3_TRANSPOSE0_DMA_INTR_NUM 19
#define VLFFT_CORE3_TRANSPOSE0_DMA_PaRAM    52

// core4 EDMA parameters for transpose0 operation
#define VLFFT_CORE4_TRANSPOSE0_DMA_CHANNEL  20
#define VLFFT_CORE4_TRANSPOSE0_DMA_INTR_NUM 20
#define VLFFT_CORE4_TRANSPOSE0_DMA_PaRAM    53

// core5 EDMA parameters for transpose0 operation
#define VLFFT_CORE5_TRANSPOSE0_DMA_CHANNEL  21
#define VLFFT_CORE5_TRANSPOSE0_DMA_INTR_NUM 21
#define VLFFT_CORE5_TRANSPOSE0_DMA_PaRAM    54

// core6 EDMA parameters for transpose0 operation
#define VLFFT_CORE6_TRANSPOSE0_DMA_CHANNEL  22
#define VLFFT_CORE6_TRANSPOSE0_DMA_INTR_NUM 22
#define VLFFT_CORE6_TRANSPOSE0_DMA_PaRAM    55

// core7 EDMA parameters for transpose0 operation
#define VLFFT_CORE7_TRANSPOSE0_DMA_CHANNEL  23
#define VLFFT_CORE7_TRANSPOSE0_DMA_INTR_NUM 23
#define VLFFT_CORE7_TRANSPOSE0_DMA_PaRAM    56


// core0 EDMA parameters for transpose1 operation
#define VLFFT_CORE0_TRANSPOSE1_DMA_CHANNEL  24
#define VLFFT_CORE0_TRANSPOSE1_DMA_INTR_NUM 24
#define VLFFT_CORE0_TRANSPOSE1_DMA_PaRAM    57

// core1 EDMA parameters for transpose1 operation
#define VLFFT_CORE1_TRANSPOSE1_DMA_CHANNEL  25
#define VLFFT_CORE1_TRANSPOSE1_DMA_INTR_NUM 25
#define VLFFT_CORE1_TRANSPOSE1_DMA_PaRAM    58

// core2 EDMA parameters for transpose1 operation
#define VLFFT_CORE2_TRANSPOSE1_DMA_CHANNEL  26
#define VLFFT_CORE2_TRANSPOSE1_DMA_INTR_NUM 26
#define VLFFT_CORE2_TRANSPOSE1_DMA_PaRAM    59

// core3 EDMA parameters for transpose1 operation
#define VLFFT_CORE3_TRANSPOSE1_DMA_CHANNEL  27
#define VLFFT_CORE3_TRANSPOSE1_DMA_INTR_NUM 27
#define VLFFT_CORE3_TRANSPOSE1_DMA_PaRAM    60

// core4 EDMA parameters for transpose1 operation
#define VLFFT_CORE4_TRANSPOSE1_DMA_CHANNEL  28
#define VLFFT_CORE4_TRANSPOSE1_DMA_INTR_NUM 28
#define VLFFT_CORE4_TRANSPOSE1_DMA_PaRAM    61

// core5 EDMA parameters for transpose1 operation
#define VLFFT_CORE5_TRANSPOSE1_DMA_CHANNEL  29
#define VLFFT_CORE5_TRANSPOSE1_DMA_INTR_NUM 29
#define VLFFT_CORE5_TRANSPOSE1_DMA_PaRAM    62

// core6 EDMA parameters for transpose1 operation
#define VLFFT_CORE6_TRANSPOSE1_DMA_CHANNEL  30
#define VLFFT_CORE6_TRANSPOSE1_DMA_INTR_NUM 30
#define VLFFT_CORE6_TRANSPOSE1_DMA_PaRAM    63

// core7 EDMA parameters for transpose1 operation
#define VLFFT_CORE7_TRANSPOSE1_DMA_CHANNEL  31
#define VLFFT_CORE7_TRANSPOSE1_DMA_INTR_NUM 31
#define VLFFT_CORE7_TRANSPOSE1_DMA_PaRAM    64

#endif






