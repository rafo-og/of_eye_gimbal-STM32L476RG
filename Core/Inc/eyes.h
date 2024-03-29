/*
 * eyes.h
 *
 *  Created on: 18 sept. 2020
 *      Author: Rafael de la Rosa Vidal
 * 
 *  This code is licensed under the GNU v2.0 license
 */

#ifndef INC_EYES_H_
#define INC_EYES_H_

#include "usart.h"
#include "adns2610.h"
#include "opticalFlow.h"
#include "gimbalControl.h"
#include "commonTypes.h"

/** @defgroup Eyes constants
 *  @{
 */

/* Exported constants --------------------------------------------------------*/
#define FRAME_STUCT_LENGTH	681  // bytes
#define FRAME_HEADER		0xBFAABFAA
#define	SECOND_SENSOR_IMPLEMENTED	true
/**
 * @}
 */

/* Exported variables ---------------------------------------------------------*/
extern frameStruct frames[2];
uint8_t currentFrameIdx;
uint8_t lastFrameIdx;

/* Exported functions --------------------------------------------------------*/
void eyes_init();
void eyes_start();
void eyes_stop();

#endif /* INC_EYES_H_ */
