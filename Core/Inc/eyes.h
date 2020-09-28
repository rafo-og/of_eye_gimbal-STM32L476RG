/*
 * eyes.h
 *
 *  Created on: 18 sept. 2020
 *      Author: deros
 */

#ifndef INC_EYES_H_
#define INC_EYES_H_

#include "usart.h"
#include "adns2610.h"
#include "opticalFlow.h"

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

/* Exported types ------------------------------------------------------------*/
typedef struct __attribute__((__packed__)){ 	/* payload -> 		2*324 + 2*2*4 + 3*4 = 676 bytes  */
	const uint32_t header;						/* total length (logic + payload) -> 	681 bytes */
	uint8_t seq;
	pixelTypeDef frame [2][PIXEL_QTY];
	optical2DFlowStruct oFRight;
	optical2DFlowStruct oFLeft;
	optical2DandRotateFlowStruct oFFused;
} frameStruct;


/* Exported variables ---------------------------------------------------------*/
extern frameStruct frames[2];
uint8_t currentFrameIdx;
uint8_t lastFrameIdx;

/* Exported functions --------------------------------------------------------*/
void eyes_init();
void eyes_start();
void eyes_stop();

#endif /* INC_EYES_H_ */
