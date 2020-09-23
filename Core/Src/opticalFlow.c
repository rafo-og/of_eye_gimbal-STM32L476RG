/*
 * opticalFlow.c
 *
 *  Created on: 23 sept. 2020
 *      Author: deros
 */

#include "opticalFlow.h"

/* Private constants ----------------------------------------------------------*/
#define int24_t_Mask		0x80FFFFFF
#define bitsOfResolution	5

static int64_t A;
static int64_t B;
static int64_t C;
static int64_t E;
static int64_t F;
static int32_t deltaX;
static int32_t deltaY;
static int32_t deltaT;
static int16_t frameIdx;

void OF_ResetCoefficients(){
	A = B = C= E= F= frameIdx= 0;
}

void OF_ComputeCoefficients(uint8_t currentFrame[], uint8_t lastFrame[], int32_t idx){

	if(fSelect[idx]){
		deltaX = (currentFrame[f2[frameIdx]] & ADNS2610_PIXEL_DATA) - (currentFrame[f1[frameIdx]] & ADNS2610_PIXEL_DATA);
		deltaY = (currentFrame[f4[frameIdx]] & ADNS2610_PIXEL_DATA) - (currentFrame[f3[frameIdx]] & ADNS2610_PIXEL_DATA);
		deltaT = (currentFrame[f0[frameIdx]] & ADNS2610_PIXEL_DATA) - (lastFrame[f0[frameIdx]] & ADNS2610_PIXEL_DATA);

		A += deltaX * deltaX;
		B += deltaY * deltaX;
		C += deltaT * deltaX;
		E += deltaY * deltaY;
		F += deltaT * deltaY;

		frameIdx++;
	}
}

void OF_Compute(int32_t* ofX, int32_t* ofY){
	int64_t temp;

	temp = A * E - B * B;

	A <<= bitsOfResolution;
	B <<= bitsOfResolution;
	C <<= bitsOfResolution;
	E <<= bitsOfResolution;
	F <<= bitsOfResolution;


	if(temp > 0){
		*ofX = ((C*E - B*F) / temp);
		*ofY = ((A*F - C*B) / temp);
	}
	else{
		*ofX = *ofY = 0;
	}

	OF_ResetCoefficients();
}
