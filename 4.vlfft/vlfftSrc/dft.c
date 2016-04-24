/*
 * dft()
 *    a generic implementation for computing DFT
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


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


void dft (int N, float x[], float y[], int N1) {
	int k, i, index;
	const double PI = 3.141592654;
	float *p_x;
	float arg, fx_0, fx_1, fy_0, fy_1, co, si;

	for (k = 0; k < N1; k++)

	{
		p_x = x;

		fy_0 = 0;
		fy_1 = 0;
		for (i = 0; i < N; i++) {
			//fx_0 = p_x[0];
			//fx_1 = p_x[1];
			fx_0 = p_x[1];
			fx_1 = p_x[0];
			p_x += 2;
			index = (i * k) % N;
			arg = 2 * PI * index / N;
			co = cos (arg);
			si = -sin (arg);
			fy_0 += ((fx_0 * co) - (fx_1 * si));
			fy_1 += ((fx_1 * co) + (fx_0 * si));
		}
		//y[2 * k] = fy_0;
		//y[2 * k + 1] = fy_1;
		y[2 * k] = fy_1;
		y[2 * k + 1] = fy_0;
	}
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_fftSPxSP_d.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
