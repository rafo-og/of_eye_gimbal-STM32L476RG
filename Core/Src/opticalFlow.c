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
static int64_t D[2];
static int64_t E[2];
static int32_t deltaX;
static int32_t deltaY;
static int32_t deltaT;
static int16_t frameIdx;

/**
 * @brief Reset the coefficient values and the frame's pixel index to zero
 */
void OF_ResetCoefficients(){
	A[0] = B[0] = C[0] = D[0] = E[0] = 0;
	A[1] = B[1] = C[1] = D[1] = E[1] = 0;
	frameIdx = 0;
}

/**
 * @brief It computes the optical flow coefficients related to a certain pixel if the needed data is available
 * @param dev	The device where the frames from
 * @param currentFrame	The current frame to process the optical flow
 * @param lastFrame		The reference frame to process the optical flow
 * @param idx			The frame's pixel index which is going to be processed
 */
void OF_ComputeCoefficients(Device dev, uint8_t currentFrame[], uint8_t lastFrame[], int32_t idx){

	if(fSelect[idx]){
		deltaX = (lastFrame[f2[frameIdx]] & ADNS2610_PIXEL_DATA) - (lastFrame[f1[frameIdx]] & ADNS2610_PIXEL_DATA);
		deltaY = (lastFrame[f4[frameIdx]] & ADNS2610_PIXEL_DATA) - (lastFrame[f3[frameIdx]] & ADNS2610_PIXEL_DATA);
		deltaT = (currentFrame[f0[frameIdx]] & ADNS2610_PIXEL_DATA) - (lastFrame[f0[frameIdx]] & ADNS2610_PIXEL_DATA);

		A[dev] += deltaX * deltaX;
		B[dev] += deltaY * deltaX;
		C[dev] += deltaT * deltaX;
		D[dev] += deltaY * deltaY;
		E[dev] += deltaT * deltaY;

		frameIdx++;
	}
}

/**
 * @brief It computes the optical flow value from the coefficients computed in the last iterations
 * @param dev	The device where the frames from
 * @param ofX	Pointer to the variable where the optical flow value in X direction is going to be stored
 * @param ofY	Pointer to the variable where the optical flow value in Y direction is going to be stored
 */
void OF_Compute(Device dev, int32_t* ofX, int32_t* ofY){
	int64_t num, den;

	den = A[dev] * D[dev] - B[dev] * B[dev];

	if(den != 0){
		num = (C[dev]*D[dev]) - (B[dev]*E[dev]);
		*ofX = (num << bitsOfResolution)  / den;
		num = (A[dev]*E[dev]) - (B[dev]*C[dev]);
		*ofY = (num << bitsOfResolution) / den;
	}
	else{
		*ofX = *ofY = 0;
	}
}

/**
 * @brief It computes the optical flow fusion from the optical flow values computed for the two connected devices
 * @param right	Pointer to the struct which contains the optical flow values computed from the right positioned device
 * @param left	Pointer to the struct which contains the optical flow values computed from the left positioned device
 * @param fused	Pointer to the struct where the fused values are going to be stored
 */
void OF_ComputeFused(optical2DFlowStruct* right, optical2DFlowStruct* left, optical2DandRotateFlowStruct* fused){
	fused->x = (right->x + left->x) >> 1;
	fused->y = (right->y + left->y) >> 1;
	if((right->y < 0 && left->y > 0) || (right->y > 0 && left->y < 0))
		fused->theta = (right->y - left->y);
}
