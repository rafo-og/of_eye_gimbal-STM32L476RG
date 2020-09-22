/*
 * eyes.h
 *
 *  Created on: 18 sept. 2020
 *      Author: deros
 */

#ifndef INC_EYES_H_
#define INC_EYES_H_

#include "adns2610.h"
#include "usart.h"

#define	SECOND_SENSOR_IMPLEMENTED	false

/* Exported types ------------------------------------------------------------*/
typedef struct __attribute__((__packed__)){
	int x;
	int y;
} optical2DFlowStruct;

typedef struct __attribute__((__packed__)){
	int x;
	int y;
	int theta;
} optical2DandRotateFlowStruct;

typedef struct __attribute__((__packed__)){ 	/* payload -> 		2*324 + 2*2*4 + 3*4 = 677 bytes  */
	const uint8_t header;						/* total length -> 	688 bytes */
	uint8_t seq;
	pixelTypeDef frame [2][PIXEL_QTY];
	optical2DFlowStruct oFRight;
	optical2DFlowStruct oFLeft;
	optical2DandRotateFlowStruct oFFused;
} frameStruct;

/* Exported constants --------------------------------------------------------*/
#define FRAME_STUCT_LENGTH	677  // bytes

/* Exported variables ---------------------------------------------------------*/
extern frameStruct frames[2];
uint8_t currentFrameIdx;
uint8_t lastFrameIdx;

/* Exported functions --------------------------------------------------------*/
void eyes_init();
void eyes_start();
void eyes_stop();

#endif /* INC_EYES_H_ */
