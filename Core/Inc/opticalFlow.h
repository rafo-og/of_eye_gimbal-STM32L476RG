/*
 * opticalFlow.h
 *
 *  Created on: 23 sept. 2020
 *      Author: deros
 */

#ifndef INC_OPTICALFLOW_H_
#define INC_OPTICALFLOW_H_

#include <stdio.h>
#include "framesIndexers.h"
#include "adns2610.h"

/* Private constant ----------------------------------------------------------*/

/* Exported typedefs ----------------------------------------------------------*/
typedef struct __attribute__((__packed__)){
	int32_t x;
	int32_t y;
} optical2DFlowStruct;

typedef struct __attribute__((__packed__)){
	int32_t x;
	int32_t y;
	int32_t theta;
} optical2DandRotateFlowStruct;

/* Exported functions --------------------------------------------------------*/
void OF_ResetCoefficients();
void OF_ComputeCoefficients(Device dev, uint8_t currentFrame[], uint8_t lastFrame[], int32_t idx);
void OF_Compute(Device dev, int32_t* ofX, int32_t* ofY);
void OF_ComputeFused(optical2DFlowStruct* right, optical2DFlowStruct* left, optical2DandRotateFlowStruct* fused);

#endif /* INC_OPTICALFLOW_H_ */
