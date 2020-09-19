/*
 * eyes.h
 *
 *  Created on: 18 sept. 2020
 *      Author: deros
 */

#ifndef INC_EYES_H_
#define INC_EYES_H_

#include "adns2610.h"

#define	SECOND_SENSOR_IMPLEMENTED	false

/* Exported types ------------------------------------------------------------*/
typedef struct __attribute__((__packed__)){
	int x;
	int y;
	int tetha;
} opticalFlowStruct;

typedef struct __attribute__((__packed__)){ 	/* payload -> 		2*324 + 3*3*4 = 684 bytes  */
	const uint8_t header = 0xFF;				/* total length -> 	685 bytes */
	pixelTypeDef frame [2][PIXEL_QTY];
	opticalFlowStruct oFRight;
	opticalFlowStruct oFLeft;
	opticalFlowStruct oFFused;
} frameStruct;

/* Exported constants --------------------------------------------------------*/
#define FRAME_STUCT_LENGTH	684  // bytes

/* Exported variables ---------------------------------------------------------*/
frameStruct frames[2];
uint8_t currentFrameIdx;
uint8_t lastFrameIdx;

/* Exported functions --------------------------------------------------------*/
void eyes_init();
void eyes_start();
void eyes_stop();

#endif /* INC_EYES_H_ */
