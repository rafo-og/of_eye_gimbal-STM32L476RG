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


/* Exported functions --------------------------------------------------------*/
void OF_ResetCoefficients();
void OF_ComputeCoefficients(Device dev, uint8_t currentFrame[], uint8_t lastFrame[], int32_t idx);
void OF_Compute(Device dev, int32_t* ofX, int32_t* ofY);

#endif /* INC_OPTICALFLOW_H_ */
