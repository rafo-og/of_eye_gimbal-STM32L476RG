/*
 * adns-2610.h
 *
 *  Created on: Sep 14, 2020
 *      Author: deros
 */

#ifndef INC_ADNS_2610_H_
#define INC_ADNS_2610_H_

#include "main.h"

#define ADNS2610_TIM_BTW_RD 		1		// 250 ns
#define ADNS2610_TIM_BTW_WR 		400		// 400 * 250ns = 100us
#define ADNS2610_TIM_TO_RD 			400		// 400 * 250ns = 100us

#define PIXEL_QTY		324

// Internal registers
#define ADNS2610_CONFIG_REG				0x00
#define ADNS2610_STATUS_REG				0x01
#define ADNS2610_SQUAL_REG				0x04
#define ADNS2610_PIXEL_SUM_REG			0x07
#define ADNS2610_PIXEL_DATA_REG			0x08
#define ADNS2610_INVERSE_ID_REG			0x11

// Configuration register bits
#define ADNS2610_CONFIG_C0_Pos		(0U)
#define ADNS2610_CONFIG_C0_Msk		(0x1U << ADNS2610_CONFIG_C0_Pos)
#define ADNS2610_CONFIG_C0			ADNS2610_CONFIG_C0_Msk
#define ADNS2610_CONFIG_C6_Pos		(6U)
#define ADNS2610_CONFIG_C6_Msk		(0x1U << ADNS2610_CONFIG_C0_Pos)
#define ADNS2610_CONFIG_C6			ADNS2610_CONFIG_C0_Msk
#define ADNS2610_CONFIG_C7_Pos		(7U)
#define ADNS2610_CONFIG_C7_Msk		(0x1U << ADNS2610_CONFIG_C0_Pos)
#define ADNS2610_CONFIG_C7			ADNS2610_CONFIG_C0_Msk

// Status register bits
#define ADNS2610_STATUS_AWAKE_Pos	(0U)
#define ADNS2610_STATUS_AWAKE_Msk	(0x1U << ADNS2610_STATUS_AWAKE_Pos)
#define ADNS2610_STATUS_AWAKE		ADNS2610_STATUS_AWAKE_Msk
#define ADNS2610_STATUS_ID_Pos		(5U)
#define ADNS2610_STATUS_ID_Msk		(0x7U << STATUS_ID_Pos)
#define ADNS2610_STATUS_ID			STATUS_ID_Msk

// Pixel data register bits
#define ADNS2610_PIXEL_DATA_Pos		(0U)
#define ADNS2610_PIXEL_DATA_Msk		(0x3FU << ADNS2610_PIXEL_DATA_Pos)
#define ADNS2610_PIXEL_DATA			ADNS2610_PIXEL_DATA_Msk
#define ADNS2610_PIXEL_VALID_Pos	(6U)
#define ADNS2610_PIXEL_VALID_Msk	(0x1U << ADNS2610_PIXEL_VALID_Pos)
#define ADNS2610_PIXEL_VALID		ADNS2610_PIXEL_VALID_Msk
#define ADNS2610_PIXEL_SOF_Pos		(7U)
#define ADNS2610_PIXEL_SOF_Msk		(0x1U << ADNS2610_PIXEL_SOF_Pos)
#define ADNS2610_PIXEL_SOF			ADNS2610_PIXEL_SOF_Msk

// Inverse product register bits
#define ADNS2610_INV_PROD_Pos		(0U)
#define ADNS2610_INV_PROD_Msk		(0xFU << ADNS2610_INV_PROD_Pos)
#define ADNS2610_INV_PROD			ADNS2610_INV_PROD_Msk

// Public typedefs
typedef enum {
	ADNS2610_RIGHT = 0,
	ADNS2610_LEFT = 1
} Device;

typedef uint8_t pixelTypeDef;

// Public global variables
pixelTypeDef pixBuf_adns_right [2][324];
uint8_t currentFrame;
uint8_t pastFrame;

// Public functions prototypes
void adns2610_init(Device dev);
void adns2610_start(void);
void adns2610_stop(void);
uint8_t adns2610_readRegister(Device dev, uint8_t reg);
void adns2610_writeRegister(Device dev, uint8_t reg, uint8_t value);
void adns2610_readFrameSync(Device dev, pixelTypeDef buffer[]);

#endif /* INC_ADNS_2610_H_ */
