* ======================================================================= *
* DSPF_sp_radix4_fftSPxSP -- Forward FFT with Radix-4 Radix     v          *
*                                                                         *
* Rev 0.0.2                                                               *
*                                                                         *
* ----------------------------------------------------------------------- *
*            Copyright (c) 2010 Texas Instruments, Incorporated.          *
*                           All Rights Reserved.                          *
* ======================================================================= *

             .global DSPF_sp_radix4_fftSPxSP


        .asg	A15, FP
        .asg	B14, DP
        .asg	B15, SP

        .asg            A8,         A_j
        .asg            B9,         B_j
        .asg            B25,        B_fft_jmp
        .asg            A1,         A_h2
        .asg            B24,        B_h2
        .asg            A14,        A_h2_
        .asg            B3,         B_h2_
        .asg            A7,         A_x
        .asg            A9,         A_y
        .asg            B6,         B_w0
        .asg            A3,         A_const16
        .asg            B7,         B_w
        .asg            A4,         A_w
        .asg            A5,         A_co1
        .asg            A4,         A_si1
        .asg            A5,         A_co2
        .asg            A4,         A_si2
        .asg            A5,         A_co3
        .asg            A4,         A_si3
        .asg            B5,         B_co1
        .asg            B4,         B_si1
        .asg            B17,        B_co2
        .asg            B16,        B_si2
        .asg            B29,        B_co3
        .asg            B28,        B_si3
        .asg            B7,         B_x
        .asg            A21,        A_x1
        .asg            A20,        A_x0
        .asg            A29,        A_x_h2p
        .asg            A28,        A_x_h2
        .asg            A19,        A_x_l1p
        .asg            A18,        A_x_l1
        .asg            A5,         A_x_l2p
        .asg            A4,         A_x_l2
        .asg            B23,        B_x1
        .asg            B22,        B_x0
        .asg            B27,        B_x_h2p
        .asg            B26,        B_x_h2
        .asg            B21,        B_x_l1p
        .asg            B20,        B_x_l1
        .asg            B29,        B_x_l2p
        .asg            B28,        B_x_l2
        .asg            A17,        A_xh1
        .asg            A16,        A_xh0
        .asg            A27,        A_xl1
        .asg            A26,        A_xl0
        .asg            A21,        A_xh21
        .asg            A20,        A_xh20
        .asg            A23,        A_xl21
        .asg            A22,        A_xl20
        .asg            B27,        B_xh1
        .asg            B26,        B_xh0
        .asg            B19,        B_xl1
        .asg            B18,        B_xl0
        .asg            B23,        B_xh21
        .asg            B22,        B_xh20
        .asg            B21,        B_xl21
        .asg            B20,        B_xl20
        .asg            B0,         B_2h2
        .asg            A2,         A_predj
        .asg            B8,         B_y_
        .asg            A12,        A_y_
        .asg            A31,        A_sum2
        .asg            A30,        A_sum1
        .asg            A17,        A_yt0
        .asg            A16,        A_xt0
        .asg            A23,        A_prod8
        .asg            A22,        A_prod7
        .asg            A21,        A_prod6
        .asg            A20,        A_prod5
        .asg            A19,        A_sum6
        .asg            A18,        A_sum5
        .asg            A18,        A_xt1
        .asg            A19,        A_yt1
        .asg            A31,        A_prod4
        .asg            A30,        A_prod3
        .asg            A29,        A_prod2
        .asg            A28,        A_prod1
        .asg            A23,        A_sum4
        .asg            A22,        A_sum3
        .asg            A26,        A_xt2
        .asg            A27,        A_yt2
        .asg            A31,        A_prod12
        .asg            A30,        A_prod11
        .asg            A29,        A_prod10
        .asg            A28,        A_prod9
        .asg            A25,        A_sum8
        .asg            A24,        A_sum7
        .asg            B17,        B_sum2
        .asg            B16,        B_sum1
        .asg            B1,         B_yt0
        .asg            B0,         B_xt0
        .asg            B31,        B_prod8
        .asg            B30,        B_prod7
        .asg            B29,        B_prod6
        .asg            B28,        B_prod5
        .asg            B5,         B_sum6
        .asg            B4,         B_sum5
        .asg            B18,        B_xt1
        .asg            B19,        B_yt1
        .asg            B31,        B_prod4
        .asg            B30,        B_prod3
        .asg            B29,        B_prod2
        .asg            B28,        B_prod1
        .asg            B17,        B_sum4
        .asg            B16,        B_sum3
        .asg            B16,        B_xt2
        .asg            B17,        B_yt2
        .asg            B19,        B_prod12
        .asg            B18,        B_prod11
        .asg            B17,        B_prod10
        .asg            B16,        B_prod9
        .asg            B31,        B_sum8
        .asg            B30,        B_sum7
        .asg            B2,         B_predj

        .asg            A28,        A_i

        .asg            A0,         A_radix
        .asg            A11,        A_const48
        .asg            A6,         A_ptr_w
        .asg            A13,        A_ptr_x
        .asg            A15,        A_ptr_y

        .asg            B10,        B_n
        .asg            B11,        B_stride
        .asg            B12,        B_const6
        .asg            B13,        B_tw_offset


        .sect    ".text"

DSPF_sp_radix4_fftSPxSP:
       STW     .D2T1   A15,*SP--(8)      ; |16| 
       STDW    .D2T2   B13:B12,*SP--     ; |16| 
       STDW    .D2T2   B11:B10,*SP--     ; |16| 
       STW     .D2T2   B3,*SP--(8)       ; |16| 
       STW     .D2T1   A14,*SP--(8)      ; |16| 
       STDW    .D2T1   A13:A12,*SP--     ; |16| 
       STDW    .D2T1   A11:A10,*SP--     ; |16| 



;       MVK     .S2     n,          B_n
;||     ADDAB   .D1X    DP,         coefs,      A_ptr_w 

;       SHRU    .S1X    B_n,         3,          A_i
;||     ZERO    .L2     B_tw_offset
;||     MVK     .L1     log4n_m1,    A_radix
;||     MVK     .S2     6,           B_const6

;       ADD     .L1     0xffffffff,  A_i,A_i
;||     MV      .L2     B_n,         B_stride



       mv.2    A4,   B_n
       mv.1    B4,   A_ptr_x
       mv.1    B6,   A_ptr_y
;      MVK     .L1     1,    A_radix   ; log4(n) - 2   // 64   FFT
;      MVK     .L1     2,    A_radix   ; log4(n) - 2   // 256  FFT
;      MVK     .L1     3,    A_radix   ; log4(n) - 2   // 1024 FFT
       mv.1    A8,    A_radix


       SHRU    .S1X    B_n,         3,          A_i
||     ZERO    .L2     B_tw_offset
||     MVK     .S2     6,           B_const6

       ADD     .L1     0xffffffff,  A_i,A_i
||     MV      .L2     B_n,         B_stride

OUTER_LOOP:

      SPLOOPD  11
||     MVC     .S2X    A_i, ILC
||     ZERO    .L1     A_j
||     ZERO    .L2     B_j
||     MVK     .S1     48,          A_const48
;||     ADDAB   .D1X    DP,          freq,       A_ptr_y         ;freq. domain


;;;;;;;;;;;;;;;; stage 1 ;;;;;;;;;;;;;;;;;;;;
        SPMASK
||      ADD     .S1     A_j,        A_const48,  A_j             ;[ 1,1]  j += 6
||^     MPY32   .M2     B_const6,   B_stride,   B_fft_jmp
||^     SHRU    .S2     B_stride,   2,          B_h2
;||^     ADDAB   .D1X    DP,         time,       A_ptr_x         ;time domain 

        SPMASK
||^     MVK     .S1     16,          A_const16

        SPMASK
||^     MV      .S1     B_h2,       A_h2
||^     MV      .S2     B_h2, B_h2_

        SPMASK
||^     ADD     .D2X    A_ptr_w,      B_tw_offset, B_w0
||^     MV      .S1     A_h2, A_h2_

        SPMASK
||^     ADD     .L2     B_tw_offset,  B_fft_jmp,   B_tw_offset
||^     SHRU    .S2     B_stride,     2,           B_stride   

        SPMASK
||^     ADD     .L1     A_ptr_x,    -16,         A_x

        SPMASK
||^     ADD     .L1     A_ptr_x,    -16,         A_y

        NOP

        LDDW    .D1T1   *++A_x[2],  A_x1:A_x0                   ;[ 9,1]  Load x1, x0
||      MVD     .M2X    A_x,        B_x                         ;[ 9,1]  x_copy =x

        SUB     .S1X    A_j,        B_fft_jmp,  A_predj         ;[10,1]  predj = j - fft_jmp
||      LDDW    .D1T1   *++A_x[A_h2],           A_x_h2p:A_x_h2  ;[10,1]  Load x_h2p, x_h2  

  [!A_predj]ZERO.S1     A_j                                     ;[11,1]  j=0
||      ROTL    .M2     B_h2,       4,          B_2h2           ;[11,1] 
||      LDDW    .D1T1   *++A_x[A_h2],           A_x_l1p:A_x_l1  ;[11,1]  Load x_l1p, x_l1  
;;;;;;;;;;;;;;;; stage 2 ;;;;;;;;;;;;;;;;;;;;

        NOP             1

        LDDW    .D2T2   *++B_x[3],  B_x1:B_x0                   ;[13,1]  Load x1, x0  

        LDDW    .D2T2   *++B_x[B_h2],           B_x_h2p:B_x_h2  ;[14,1]  Load x_h2p, x_h2  
||      LDDW    .D1T1   *A_x[A_h2], A_x_l2p:A_x_l2              ;[14,1]  Load x_l2p, x_l2          

        SUB     .S1X    A_x,        B_2h2,      A_x             ;[15,1] 
||      LDDW    .D2T2   *++B_x[B_h2],           B_x_l1p:B_x_l1  ;[15,1]  Load x_l1p, x_l1  

        ADD     .L2     B_w0,       B_j,        B_w             ;[16,1] 
||      LDDW    .D2T2   *B_x[B_h2], B_x_l2p:B_x_l2              ;[16,1]  Load x_l2p, x_l2

        DADDSP  .S1     A_x1:A_x0,  A_x_l1p:A_x_l1,         A_xh1:A_xh0 ;[17,1] 

  [!A_predj]ADD .S1X    A_x,        B_fft_jmp,  A_x             ;[18,1]  *x = *x + fft_jmp
||      DSUBSP  .L1     A_x1:A_x0,  A_x_l1p:A_x_l1,         A_xl1:A_xl0 ;[18,1] 

        ADD     .L2X    B_j,        A_const48,  B_j             ;[19,1] 
||      DADDSP  .L1     A_x_h2p:A_x_h2,         A_x_l2p:A_x_l2,         A_xh21:A_xh20   ;[19,1] 
||      LDDW    .D2T2   *B_w[3],    B_co1:B_si1                 ;[19,1]  Load si1, co1
||      MVD     .M1X    B_w,        A_w                         ;[19,1] 

        DADDSP  .S2     B_x1:B_x0,  B_x_l1p:B_x_l1,         B_xh1:B_xh0 ;[20,1] 
||      DSUBSP  .L1     A_x_h2p:A_x_h2,         A_x_l2p:A_x_l2,         A_xl21:A_xl20   ;[20,1] 
||      LDDW    .D2T2   *B_w[4],    B_co2:B_si2                 ;[20,1]  Load si2, co2

        SUB     .S2     B_j,        B_fft_jmp,  B_predj         ;[21,1] 
||      DADDSP  .L2     B_x_h2p:B_x_h2,         B_x_l2p:B_x_l2,         B_xh21:B_xh20   ;[21,1] 
||      LDDW    .D2T2   *B_w[5],    B_co3:B_si3                 ;[21,1]  Load si3, co3

        DSUBSP  .L2     B_x_h2p:B_x_h2,         B_x_l2p:B_x_l2,         B_xl21:B_xl20   ;[22,1] 
||      DSUBSP  .S2     B_x1:B_x0,  B_x_l1p:B_x_l1,         B_xl1:B_xl0 ;[22,1] 

;;;;;;;;;;;;;;;; stage 3 ;;;;;;;;;;;;;;;;;;;;


  [!B_predj]ZERO.S2     B_j                                     ;[23,1] 
||      DSUBSP  .L1     A_xh1:A_xh0,            A_xh21:A_xh20,          A_yt0:A_xt0     ;[23,1] 
||      LDDW    .D1T1   *A_w[1],    A_co2:A_si2                 ;[23,1]  Load si2, co2

        DSUBSP  .L2     B_xh1:B_xh0,            B_xh21:B_xh20,          B_yt0:B_xt0     ;[24,1] 
||      SUBSP   .S1     A_xl1,      A_xl20,     A_yt2           ;[24,1]  yt2 = xl1 - xl20
||      DADDSP  .L1     A_xh1:A_xh0,            A_xh21:A_xh20,          A_sum2:A_sum1   ;[24,1] 
||      LDDW    .D1T1   *A_w[2],    A_co3:A_si3                 ;[24,1]  Load si3, co3

        SUBSP   .L2     B_xl1,      B_xl20,     B_yt2           ;[25,1]  yt2 = xl1 + xl20
||      ADDSP   .S1     A_xl0,      A_xl21,     A_xt2           ;[25,1]  xt2 = xl0 + xl21

        ADDSP   .L2     B_xl0,      B_xl21,     B_xt2           ;[26,1]  xt2 = xl0 - xl21
||      ADDSP   .S2     B_xl1,      B_xl20,     B_yt1           ;[26,1]  yt1 = xl1 + xl20
||      SUBSP   .L1     A_xl0,      A_xl21,     A_xt1           ;[26,1]  xt1 = xl0 + xl21
||      MVD     .M1     A_y,        A_y_                        ;[26,1] 
||      MVD     .M2X    A_y,        B_y_                        ;[26,1] 

        CMPYSP  .M2     B_yt0:B_xt0,            B_co2:B_si2,    B31:B30:B29:B28    ; B_prod8:B_prod7:B_prod6:B_prod5 ;[27,1] 
||      ADDSP   .L1     A_xl1,      A_xl20,     A_yt1           ;[27,1]  yt1 = xl1 - xl20
||      LDDW    .D1T1   *A_w[0],    A_co1:A_si1                 ;[27,1]  Load si1, co1

        ADD     .L1     A_y,        A_const16,  A_y             ;[28,1] 
||      SUBSP   .L2     B_xl0,      B_xl21,     B_xt1           ;[28,1]  xt1 = xl0 - xl21
||      DADDSP  .S2     B_xh1:B_xh0,            B_xh21:B_xh20,          B_sum2:B_sum1   ;[28,1] 
||      CMPYSP  .M1     A_yt0:A_xt0,            A_co2:A_si2,    A23:A22:A21:A20    ; A_prod8:A_prod7:A_prod6:A_prod5 ;[28,1] 

        CMPYSP  .M1     A_yt2:A_xt2,            A_co3:A_si3,    A31:A30:A29:A28    ; A_prod12:A_prod11:A_prod10:A_prod9      ;[29,1] 

        STDW    .D1T1   A_sum2:A_sum1,          *++A_y_[2]      ;[30,1] 
||      CMPYSP  .M2     B_yt2:B_xt2,            B_co3:B_si3,    B19:B18:B17:B16    ; B_prod12:B_prod11:B_prod10:B_prod9      ;[30,1] 

  [!B_predj]ADD .S1X    A_y,        B_fft_jmp,  A_y             ;[31,1] 
||      DADDSP  .L2     B_prod8:B_prod7,        B_prod6:B_prod5,        B_sum6:B_sum5   ;[31,1] 

        CMPYSP  .M2     B_yt1:B_xt1,            B_co1:B_si1,    B31:B30:B29:B28    ; B_prod4:B_prod3:B_prod2:B_prod1 ;[32,1] 
||      CMPYSP  .M1     A_yt1:A_xt1,            A_co1:A_si1,    A31:A30:A29:A28    ; A_prod4:A_prod3:A_prod2:A_prod1 ;[32,1] 
||      DADDSP  .L1     A_prod8:A_prod7,        A_prod6:A_prod5,        A_sum6:A_sum5   ;[32,1] 

        STDW    .D2T2   B_sum2:B_sum1,          *++B_y_[3]      ;[33,1] 
||      DADDSP  .L1     A_prod12:A_prod11,      A_prod10:A_prod9,       A_sum8:A_sum7   ;[33,1] 

;;;;;;;;;;;;;;;; stage 4 ;;;;;;;;;;;;;;;;;;;;

        STDW    .D2T2   B_sum6:B_sum5,          *++B_y_[B_h2_]  ;[34,1] 
||      DADDSP  .L2     B_prod12:B_prod11,      B_prod10:B_prod9,       B_sum8:B_sum7   ;[34,1] 

        NOP             1

        DADDSP  .S2     B_prod4:B_prod3,        B_prod2:B_prod1,        B_sum4:B_sum3   ;[36,1] 
||      DADDSP  .L1     A_prod4:A_prod3,        A_prod2:A_prod1,        A_sum4:A_sum3   ;[36,1] 

        STDW    .D1T1   A_sum6:A_sum5,          *++A_y_[A_h2_]  ;[37,1] 

        NOP             1

        STDW    .D2T2   B_sum4:B_sum3,          *++B_y_[B_h2_]  ;[39,1] 
||      STDW    .D1T1   A_sum4:A_sum3,          *++A_y_[A_h2_]  ;[39,1] 

        STDW    .D2T2   B_sum8:B_sum7,          *B_y_[B_h2_]    ;[40,1] 
||      STDW    .D1T1   A_sum8:A_sum7,          *A_y_[A_h2_]    ;[40,1] 

        NOP             2
        NOP             1

      SPKERNEL 2,5
        NOP

 [A_radix] BDEC .S1     OUTER_LOOP,       A_radix

       MV      .D1X    B_n,          A_const16           ;  A_const16 for A_ptr_lx1 for later part of the code
       SHRU    .S1X    B_n,          3,           A_i
       ADD     .L1     0xffffffff,   A_i,         A_i
       NOP 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
EARLY:
        .asg            A5,         A_lj
        .asg            B9,         B_lj
        .asg            A1,         A_ptr_lx0
        .asg            B7,         B_ptr_lx0
        .asg            A3,         A_ptr_lx1
        .asg            B8,         B_ptr_lx1
        .asg            A7,         A_ly0
        .asg            B3,         B_ly0
        .asg            A8,         A_ll0
        .asg            B2,         B_ll0
        .asg            B4,         B_lnmax
        .asg            A9,         A_lnmax
        .asg            A6,         A_ltemp1
        .asg            A4,         A_lk
        .asg            A0,         A_ly1
        .asg            B10,        B_ltemp1
        .asg            B5,         B_lk
        .asg            B6,         B_ly1
        .asg            A21,        A_lx1
        .asg            A20,        A_lx0
        .asg            A17,        A_lx3
        .asg            A16,        A_lx2
        .asg            A11,        A_lx5
        .asg            A10,        A_lx4
        .asg            A13,        A_lx7
        .asg            A12,        A_lx6
        .asg            B17,        B_lx1
        .asg            B16,        B_lx0
        .asg            B27,        B_lx3
        .asg            B26,        B_lx2
        .asg            B19,        B_lx5
        .asg            B18,        B_lx4
        .asg            B17,        B_lx7
        .asg            B16,        B_lx6
        .asg            A23,        A_lxh1_0
        .asg            A22,        A_lxh0_0
        .asg            A29,        A_lxh1_1
        .asg            A28,        A_lxh0_1
        .asg            B19,        B_lxh1_0
        .asg            B18,        B_lxh0_0
        .asg            B27,        B_lxh1_1
        .asg            B26,        B_lxh0_1
        .asg            A19,        A_lyt1
        .asg            A18,        A_lyt0
        .asg            A15,        A_lyt5
        .asg            A14,        A_lyt4
        .asg            A31,        A_lxl1_0
        .asg            A30,        A_lxl0_0
        .asg            A25,        A_lxl1_1
        .asg            A24,        A_lxl0_1
        .asg            B25,        B_lyt1
        .asg            B24,        B_lyt0
        .asg            B29,        B_lyt5
        .asg            B28,        B_lyt4
        .asg            B1,         B_lxl1_0
        .asg            B0,         B_lxl0_0
        .asg            B23,        B_lxl1_1
        .asg            B22,        B_lxl0_1
        .asg            A20,        A_lyt2
        .asg            A21,        A_lyt3
        .asg            A26,        A_lyt6
        .asg            A27,        A_lyt7
        .asg            B20,        B_lyt2
        .asg            B21,        B_lyt3
        .asg            B30,        B_lyt6
        .asg            B31,        B_lyt7

        .asg            A2,         A_lctr


        SHR     .S1X    B_n,   3,   A_lctr
||      MV      .L1     A_ptr_x,    A_ptr_lx0
||      ADD     .L2X    A_ptr_x, 8, B_ptr_lx0

        MV      .D1X    B_n,        A_ptr_lx1

        SUB     .S1     A_lctr,1,   A_lctr
||      ADDAW   .D1     A_ptr_x,    A_ptr_lx1,  A_ptr_lx1
||      NORM    .L1X    B_n,   A_ll0

        SPLOOPD  8
||      MVC     .S2X    A_lctr, ILC
||      ADD     .L1     A_ll0, 3,   A_ll0

;;;;;;;;;;;;;;;;;  stage 1 ;;;;;;;;;;;;;;;;;;;;;;;;

        SPMASK
||      LDDW    .D1T2   *A_ptr_lx1++[2],        B_lx1:B_lx0     ;[ 1,1]  load ptr_x0[0], ptr_x0[1] 
||      LDDW    .D2T1   *B_ptr_lx0++[2],        A_lx3:A_lx2     ;[ 1,1]  load ptr_x0[2], ptr_x0[3]  
||^     ADD     .L2X    A_ptr_lx1,8,B_ptr_lx1  

        SPMASK
||^     MV      .L2X    A_ll0,      B_ll0

        SPMASK
||      LDDW    .D1T2   *A_ptr_lx1++[2],        B_lx5:B_lx4     ;[ 3,1]  load ptr_x0[4], ptr_x0[5] 
||      LDDW    .D2T1   *B_ptr_lx0++[2],        A_lx7:A_lx6     ;[ 3,1]  load ptr_x0[4], ptr_x0[5] 
||^     ZERO    .S1     A_lj
||^     SHR     .S2     B_n,  3,    B_lj

        LDDW    .D2T2   *B_ptr_lx1++[2],        B_lx3:B_lx2     ;[ 4,1]  load ptr_x0[2], ptr_x0[3]  
||      LDDW    .D1T1   *A_ptr_lx0++[2],        A_lx1:A_lx0     ;[ 4,1]  load ptr_x0[0], ptr_x0[1] 

        LDDW    .D2T2   *B_ptr_lx1++[2],        B_lx7:B_lx6     ;[ 5,1]  load ptr_x0[4], ptr_x0[5] 
||      LDDW    .D1T1   *A_ptr_lx0++[2],        A_lx5:A_lx4     ;[ 5,1]  load ptr_x0[4], ptr_x0[5] 
||      BITR    .M2     B_lj,       B_ltemp1                    ;[ 5,1] 
||      BITR    .M1     A_lj,       A_ltemp1                    ;[ 5,1] 

        SPMASK
||^     MV      .L2X    A_ptr_y,    B_ly0
||^     SHR     .S2     B_n,   2,   B_lnmax
||^     MV      .L1     A_ptr_y,    A_ly0
||^     SHR     .S1X    B_n,   2,   A_lnmax

        SPMASK
||      ADD     .L2     B_lj,       1,          B_lj            ;[ 7,1]  j = j+1

        DADDSP  .L2     B_lx1:B_lx0,            B_lx5:B_lx4,            B_lxh1_0:B_lxh0_0       ;[ 8,1]  xh0_0 = x0 + x4, xh1_0 = x1 + x5

;;;;;;;;;;;;;;;;;  stage 2 ;;;;;;;;;;;;;;;;;;;;;;;;

        ADD     .L1     A_lj,       1,          A_lj            ;[ 9,1]  j = j+1
||      DSUBSP  .L2     B_lx1:B_lx0,            B_lx5:B_lx4,            B_lxl1_0:B_lxl0_0       ;[ 9,1]  xl0_0 = x0 - x4, xl1_0 = x1 - x5
||      DADDSP  .S1     A_lx3:A_lx2,            A_lx7:A_lx6,            A_lxh1_1:A_lxh0_1       ;[ 9,1]  xh0_1 = x2 + x6, xh1_1 = x3 + x7

        DSUBSP  .S1     A_lx1:A_lx0,            A_lx5:A_lx4,            A_lxl1_0:A_lxl0_0       ;[10,1]  xl0_0 = x0 - x4, xl1_0 = x1 - x5
||      DADDSP  .S2     B_lx3:B_lx2,            B_lx7:B_lx6,            B_lxh1_1:B_lxh0_1       ;[10,1]  xh0_1 = x2 + x6, xh1_1 = x3 + x7
||      DADDSP  .L1     A_lx1:A_lx0,            A_lx5:A_lx4,            A_lxh1_0:A_lxh0_0       ;[10,1]  xh0_0 = x0 + x4, xh1_0 = x1 + x5

        DSUBSP  .S2     B_lx3:B_lx2,            B_lx7:B_lx6,            B_lxl1_1:B_lxl0_1       ;[11,1]  xl0_1 = x2 - x6, xl1_1 = x3 - x7
||      DSUBSP  .L1     A_lx3:A_lx2,            A_lx7:A_lx6,            A_lxl1_1:A_lxl0_1       ;[11,1]  xl0_1 = x2 - x6, xl1_1 = x3 - x7, 

        NOP             1

        DADDSP  .S2     B_lxh1_0:B_lxh0_0,      B_lxh1_1:B_lxh0_1,      B_lyt1:B_lyt0   ;[13,1]  yt0 =xh0_0 + xh0_1, yt1 =xh1_0 + xh1_1

        SHRU    .S2     B_ltemp1,   B_ll0,      B_lk            ;[14,1] 
||      SHRU    .S1     A_ltemp1,   A_ll0,      A_lk            ;[14,1] 
||      DSUBSP  .L2     B_lxh1_0:B_lxh0_0,      B_lxh1_1:B_lxh0_1,      B_lyt5:B_lyt4   ;[14,1]  yt4 =xh0_0 - xh0_1, yt5 =xh1_0 - xh1_1

        SUBSP   .S2     B_lxl0_0,   B_lxl1_1,   B_lyt2          ;[15,1]  yt2 = xl0_0 + xl1_1 
||      SUBSP   .L1     A_lxl0_0,   A_lxl1_1,   A_lyt2          ;[15,1]  yt2 = xl0_0 + xl1_1 
||      DADDSP  .S1     A_lxh1_0:A_lxh0_0,      A_lxh1_1:A_lxh0_1,      A_lyt1:A_lyt0   ;[15,1]  yt0 =xh0_0 + xh0_1; yt1 =xh1_0 + xh1_1

        SHL     .S1     A_lk,       2,          A_lk            ;[16,1] 
||      ADDSP   .S2     B_lxl0_0,   B_lxl1_1,   B_lyt6          ;[16,1]  yt6 = xl0_0 - xl1_1   
||      ADDSP   .L1     A_lxl1_0,   A_lxl0_1,   A_lyt3          ;[16,1]  yt3 = xl1_0 - xl0_1 

;;;;;;;;;;;;;;;;;  stage 3 ;;;;;;;;;;;;;;;;;;;;;;;;

        SHL     .S2     B_lk,       2,          B_lk            ;[17,1] 

        SUBSP   .L2     B_lxl1_0,   B_lxl0_1,   B_lyt7          ;[18,1]  yt7 = xl1_0 + xl0_1 

        ADDSP   .L2     B_lxl1_0,   B_lxl0_1,   B_lyt3          ;[19,1]  yt3 = xl1_0 - xl0_1 
||      DSUBSP  .S1     A_lxh1_0:A_lxh0_0,      A_lxh1_1:A_lxh0_1,      A_lyt5:A_lyt4   ;[19,1]  yt4 =xh0_0 - xh0_1, yt5 =xh1_0 - xh1_1

        ADD     .L2     B_ly0,      B_lk,       B_ly1           ;[20,1]  *y1 = *y0 + k 
||      SUBSP   .L1     A_lxl1_0,   A_lxl0_1,   A_lyt7          ;[20,1]  yt7 = xl1_0 + xl0_1
||      ADDSP   .S1     A_lxl0_0,   A_lxl1_1,   A_lyt6          ;[20,1]  yt6 = xl0_0 - xl1_1   

        NOP             1

        STDW    .D2T2   B_lyt1:B_lyt0,          *B_ly1++[B_lnmax]       ;[22,1] 
||      ADD     .L1     A_ly0,      A_lk,       A_ly1           ;[22,1]  *y1 = *y0 + k 

        STDW    .D2T2   B_lyt3:B_lyt2,          *B_ly1++[B_lnmax]       ;[23,1] 
||      STDW    .D1T1   A_lyt1:A_lyt0,          *A_ly1++[A_lnmax]       ;[23,1] 

        STDW    .D2T2   B_lyt5:B_lyt4,          *B_ly1++[B_lnmax]       ;[24,1] 
||      STDW    .D1T1   A_lyt3:A_lyt2,          *A_ly1++[A_lnmax]       ;[24,1] 

;;;;;;;;;;;;;;;;;  stage 4 ;;;;;;;;;;;;;;;;;;;;;;;;
* =========================== PIPE LOOP KERNEL ============================ *
LOOP:
        NOP             1

        STDW    .D2T2   B_lyt7:B_lyt6,          *B_ly1          ;[26,1] 
||      STDW    .D1T1   A_lyt5:A_lyt4,          *A_ly1++[A_lnmax]       ;[26,1] 

        NOP             3

        STDW    .D1T1   A_lyt7:A_lyt6,          *A_ly1          ;[30,1] 

        NOP             1

        SPKERNEL 3,0


           LDDW    .D2T1   *++SP,A11:A10
           LDDW    .D2T1   *++SP,A13:A12
           LDW     .D2T1   *++SP(8),A14
           LDW     .D2T2   *++SP(8),B3
           NOP             1
           LDDW    .D2T2   *++SP,B11:B10
           LDDW    .D2T2   *++SP,B13:B12
           LDW     .D2T1   *++SP(8),A15      ; |429| 
           RETNOP  .S2     B3,5






              .end

******************************************************************************
* end of fft99.asm
******************************************************************************



