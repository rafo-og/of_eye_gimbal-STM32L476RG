/*
 * opticalFlow.c
 *
 *  Created on: 23 sept. 2020
 *      Author: deros
 */

#include "opticalFlow.h"

/* Private constants ----------------------------------------------------------*/
#define int24_t_Mask		0x80FFFFFF
#define bitsOfResolution	9

static int64_t A[2];
static int64_t B[2];
static int64_t C[2];
static int64_t E[2];
static int64_t F[2];
static int32_t deltaX;
static int32_t deltaY;
static int32_t deltaT;
static int16_t frameIdx;

void OF_ResetCoefficients(){
	A[0] = B[0] = C[0] = E[0] = F[0] = 0;
	A[1] = B[1] = C[1] = E[1] = F[1] = 0;
	frameIdx = 0;
}

void OF_ComputeCoefficients(Device dev, uint8_t currentFrame[], uint8_t lastFrame[], int32_t idx){

	if(fSelect[idx]){
		deltaX = (lastFrame[f2[frameIdx]] & ADNS2610_PIXEL_DATA) - (lastFrame[f1[frameIdx]] & ADNS2610_PIXEL_DATA);
		deltaY = (lastFrame[f4[frameIdx]] & ADNS2610_PIXEL_DATA) - (lastFrame[f3[frameIdx]] & ADNS2610_PIXEL_DATA);
		deltaT = (currentFrame[f0[frameIdx]] & ADNS2610_PIXEL_DATA) - (lastFrame[f0[frameIdx]] & ADNS2610_PIXEL_DATA);

		A[dev] += deltaX * deltaX;
		B[dev] += deltaY * deltaX;
		C[dev] += deltaT * deltaX;
		E[dev] += deltaY * deltaY;
		F[dev] += deltaT * deltaY;

		frameIdx++;
	}
}

void OF_Compute(Device dev, int32_t* ofX, int32_t* ofY){
	int64_t num, den;

	den = A[dev] * E[dev] - B[dev] * B[dev];

	if(den > 0){
		num = (C[dev]*E[dev]) - (B[dev]*F[dev]);
		*ofX = (num << bitsOfResolution)  / den;
		num = (A[dev]*F[dev]) - (C[dev]*B[dev]);
		*ofY = (num << bitsOfResolution) / den;
	}
	else{
		*ofX = *ofY = 0;
	}
}

void OF_ComputeFused(optical2DFlowStruct* right, optical2DFlowStruct* left, optical2DandRotateFlowStruct* fused){
	fused->x = (right->x + left->x) >> 2;
	fused->y = (right->y + left->y) >> 2;
	fused->theta = (right->y - left->y);
}
