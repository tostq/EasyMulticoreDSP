/* ======================================================================= */
/* DSPF_sp_fftSPxSP_d.c -- Complex Forward FFT with Mixed Radix            */
/*                Driver code; tests kernel and reports result in stdout   */
/*                                                                         */
/* Rev 0.0.3                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/*  vlfft local define */
#include "../vlfftInc/vlfftDebug.h"
#include "../vlfftInc/vlfftconfig.h"

void multTwiddle_vec_sa( float *pInTwiddle, float wStepRe, float wStepIm, int fftSize);


void multTwiddle_vec(float *pInTwiddle, float wStepRe, float wStepIm, int fftSize) {
	int  k1;
	float w_cos, w_sin, x_real, x_imag;
	float twiddleRe, twiddleIm;

	twiddleRe = wStepRe;
	twiddleIm =-wStepIm;

	for(k1=0; k1<fftSize; k1++) {
		w_cos = twiddleRe*wStepRe - twiddleIm*wStepIm;
		w_sin = twiddleIm*wStepRe + twiddleRe*wStepIm;
		twiddleRe = w_cos;
		twiddleIm = w_sin;

		x_real = pInTwiddle[2*k1+1]*w_cos - pInTwiddle[2*k1]*w_sin;
		x_imag = pInTwiddle[2*k1+1]*w_sin + pInTwiddle[2*k1]*w_cos;
		pInTwiddle[2*k1+1] = x_real;
		pInTwiddle[2*k1  ] = x_imag;
	}
}


void multTwiddle_vec_1(float *pInTwiddle, float wStepRe, float wStepIm, int fftSize) {
	int  k1;
	float w_cos, w_sin;
	float x_real0, x_imag0, x_real1, x_imag1;
	float y_real0, y_imag0, y_real1, y_imag1;
	float twiddleRe0, twiddleIm0;
	float twiddleRe1, twiddleIm1;
	float wStepRe2, wStepIm2;

	wStepRe2 = wStepRe*wStepRe - wStepIm*wStepIm;
	wStepIm2 = wStepRe*wStepIm + wStepIm*wStepRe;

	twiddleRe0 = wStepRe2;
	twiddleIm0 =-wStepIm2;

	twiddleRe1 = wStepRe;
	twiddleIm1 =-wStepIm;

	for(k1=0; k1<fftSize>>1; k1++) {
		w_cos = twiddleRe0*wStepRe2 - twiddleIm0*wStepIm2;
		w_sin = twiddleIm0*wStepRe2 + twiddleRe0*wStepIm2;
		twiddleRe0 = w_cos;
		twiddleIm0 = w_sin;

		x_real0= pInTwiddle[4*k1+1];
		x_imag0= pInTwiddle[4*k1  ];
		y_real0= x_real0*w_cos - x_imag0*w_sin;
		y_imag0= x_real0*w_sin + x_imag0*w_cos;

		pInTwiddle[4*k1+1] = y_real0;
		pInTwiddle[4*k1  ] = y_imag0;


		w_cos = twiddleRe1*wStepRe2 - twiddleIm1*wStepIm2;
		w_sin = twiddleIm1*wStepRe2 + twiddleRe1*wStepIm2;
		twiddleRe1 = w_cos;
		twiddleIm1 = w_sin;

		x_real1= pInTwiddle[4*k1+3];
		x_imag1= pInTwiddle[4*k1+2];
		y_real1= x_real1*w_cos - x_imag1*w_sin;
		y_imag1= x_real1*w_sin + x_imag1*w_cos;

		pInTwiddle[4*k1+3] = y_real1;
		pInTwiddle[4*k1+2] = y_imag1;
	}
}



void genTwiddle(float *pTwiddle, int numFFTsPerCore, int coreNum) {
	int  n2, n2_start, n;

	double theta;
	const double PI = 3.141592654;

	n2_start = numFFTsPerCore*coreNum;
	n = VLFFT_SIZE;

	for(n2=n2_start; n2<n2_start+numFFTsPerCore; n2++) {
		theta = 2 * PI * n2 / n;
		pTwiddle[2*(n2-n2_start)  ] = ((float)  cos (theta)  );
		pTwiddle[2*(n2-n2_start)+1] = ((float)(-sin (theta)) );
	}

}

