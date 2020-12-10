/*
 * commonTypes.h
 *
 *  Created on: 10 dic. 2020
 *      Author: deros
 */

#ifndef INC_COMMONTYPES_H_
#define INC_COMMONTYPES_H_

/* Exported constants --------------------------------------------------------*/
// Pixel quantity in an ADNS2610 frame
#define PIXEL_QTY		324

/* Exported typedefs ----------------------------------------------------------*/
typedef uint8_t pixelTypeDef;


typedef struct __attribute__((__packed__)){
	int32_t x;
	int32_t y;
} optical2DFlowStruct;

typedef struct __attribute__((__packed__)){
	int32_t x;
	int32_t y;
	int32_t theta;
} optical2DandRotateFlowStruct;

typedef struct __attribute__((__packed__)){ 	/* payload -> 		2*324 + 2*2*4 + 3*4 = 676 bytes  */
	const uint32_t header;						/* total length (logic + payload) -> 	681 bytes */
	uint8_t seq;
	pixelTypeDef frame [2][PIXEL_QTY];
	optical2DFlowStruct oFRight;
	optical2DFlowStruct oFLeft;
	optical2DandRotateFlowStruct oFFused;
} frameStruct;

#endif /* INC_COMMONTYPES_H_ */
