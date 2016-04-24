/*
 * vlfftconfig.h
 *
 *    This file contains definitions for configuring multicore FFT computation
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



///////////////////////////////////////////////
// 1) select the maximum number of DSP cores
///////////////////////////////////////////////
#define EIGHT_CORE_DEVICE 1
#define FOUR_CORE_DEVICE  0

///////////////////////////////////////////////
// 2) set the number of cores for fft computation
//      (a)    for 8-core device, options are
//          8, 4, 2, 1
//      (b) for 4-core device, options are
//             4, 2, 1
///////////////////////////////////////////////
#define NUM_CORES_FOR_FFT_COMPUTE    8


//////////////////////////////////////////////
// 3) Select the size of FFT by setting one
//    of the following settings to 1
//////////////////////////////////////////////
#define VLFFT_16K   0
#define VLFFT_32K   0
#define VLFFT_64K   0
#define VLFFT_128K  0
#define VLFFT_256K  0
#define VLFFT_512K  0
#define VLFFT_1024K 1



//////////////////////////////////////////////////////////////
// STOP!  No need to change any of the following settings
//////////////////////////////////////////////////////////////

#define BYTES_PER_COMPLEX_SAMPLE   8

#define SAMPLES_PER_TRANSFER_BLOCK 8
#define LOG2_SAMPLES_PER_TRANSFER_BLOCK 3
#define NUM_FFTS_PER_BLOCK         8
#define LOG2_NUM_FFTS_PER_BLOCK    3



#if EIGHT_CORE_DEVICE
#define MAX_NUMBER_CORES            8
#if NUM_CORES_FOR_FFT_COMPUTE==8
#define LOG2_NUM_CORES_FOR_COMPUTE  3
#endif
#if NUM_CORES_FOR_FFT_COMPUTE==4
#define LOG2_NUM_CORES_FOR_COMPUTE  2
#endif
#if NUM_CORES_FOR_FFT_COMPUTE==2
#define LOG2_NUM_CORES_FOR_COMPUTE  1
#endif
#if NUM_CORES_FOR_FFT_COMPUTE==1
#define LOG2_NUM_CORES_FOR_COMPUTE  0
#endif
#endif



#if FOUR_CORE_DEVICE
#define MAX_NUMBER_CORES            4
#if NUM_CORES_FOR_FFT_COMPUTE==4
#define LOG2_NUM_CORES_FOR_COMPUTE  2
#endif
#if NUM_CORES_FOR_FFT_COMPUTE==2
#define LOG2_NUM_CORES_FOR_COMPUTE  1
#endif
#if NUM_CORES_FOR_FFT_COMPUTE==1
#define LOG2_NUM_CORES_FOR_COMPUTE  0
#endif
#endif


#if VLFFT_4K
#define VLFFT_SIZE         1024*4
#define VLFFT_N1           64
#define RADIX_1stIter      4
#define LOG4N_1stIter      1

#define VLFFT_N2           64
#define RADIX_2ndIter      4
#define LOG4N_2ndIter      1
#endif


#if VLFFT_16K
#define VLFFT_SIZE         1024*16
#define VLFFT_N1           128
#define RADIX_1stIter      2
#define LOG4N_1stIter      0

#define VLFFT_N2           128
#define RADIX_2ndIter      2
#define LOG4N_2ndIter      0
#endif


#if VLFFT_32K
#define VLFFT_SIZE         1024*32
#define VLFFT_N1           256
#define RADIX_1stIter      4
#define LOG4N_1stIter      2

#define VLFFT_N2           128
#define RADIX_2ndIter      2
#define LOG4N_2ndIter      0
#endif


#if VLFFT_64K
#define VLFFT_SIZE         1024*64
#define VLFFT_N1           256
#define RADIX_1stIter      4
#define LOG4N_1stIter      2

#define VLFFT_N2           256
#define RADIX_2ndIter      4
#define LOG4N_2ndIter      2
#endif


#if VLFFT_128K
#define VLFFT_SIZE         1024*128
#define VLFFT_N1           512
#define RADIX_1stIter      2
#define LOG4N_1stIter      0

#define VLFFT_N2           256
#define RADIX_2ndIter      4
#define LOG4N_2ndIter      2
#endif


#if VLFFT_256K
#define VLFFT_SIZE         1024*256
#define VLFFT_N1           512
#define RADIX_1stIter      2
#define LOG4N_1stIter      0

#define VLFFT_N2           512
#define RADIX_2ndIter      2
#define LOG4N_2ndIter      0
#endif

#if VLFFT_512K
#define VLFFT_SIZE         1024*512
#define VLFFT_N1           1024
#define RADIX_1stIter      4
#define LOG4N_1stIter      3

#define VLFFT_N2           512
#define RADIX_2ndIter      2
#define LOG4N_2ndIter      0
#endif


#if VLFFT_1024K
#define VLFFT_SIZE         1024*1024
#define VLFFT_N1           1024
#define RADIX_1stIter      4
#define LOG4N_1stIter      3

#define VLFFT_N2           1024
#define RADIX_2ndIter      4
#define LOG4N_2ndIter      3
#endif





