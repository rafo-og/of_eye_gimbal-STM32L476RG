/*
 * adns-2610.h
 *
 *  Created on: Sep 14, 2020
 *      Author: deros
 */

#ifndef INC_ADNS_2610_H_
#define INC_ADNS_2610_H_

#include "main.h"

#define ADNS2610_READ_TIME 	150

typedef enum {
	ADNS2610_RIGHT = 0,
	ADNS2610_LEFT = 1
} Device;

// Internal registers
#define ADNS_2610_CONFIG			0x00
#define ADNS_2610_STATUS			0x01
#define ADNS_2610_SQUAL				0x04
#define ADNS_2610_PIXEL_SUM			0x07
#define ADNS_2610_PIXEL_DATA		0x08
#define ADNS_2610_INVERSE_ID		0x11

// Configuration register bits
#define CONFIG_C0_Pos	(0U)
#define CONFIG_C0_Msk	(0x1U << CONFIG_C0_Pos)
#define CONFIG_C0		CONFIG_C0_Msk
#define CONFIG_C6_Pos	(6U)
#define CONFIG_C6_Msk	(0x1U << CONFIG_C0_Pos)
#define CONFIG_C6		CONFIG_C0_Msk
#define CONFIG_C7_Pos	(7U)
#define CONFIG_C7_Msk	(0x1U << CONFIG_C0_Pos)
#define CONFIG_C7		CONFIG_C0_Msk

// Status register bits
#define STATUS_AWAKE_Pos	(0U)
#define STATUS_AWAKE_Msk	(0x1U << STATUS_AWAKE_Pos)
#define STATUS_AWAKE		STATUS_AWAKE_Msk
#define STATUS_ID_Pos		(5U)
#define STATUS_ID_Msk		(0x7U << STATUS_ID_Pos)
#define STATUS_ID			STATUS_ID_Msk

// Pixel data register bits
#define PIXEL_DATA_Pos		(0U)
#define PIXEL_DATA_Msk		(0x3FU << PIXEL_DATA_Pos)
#define PIXEL_DATA			PIXEL_DATA_Msk
#define PIXEL_VALID_Pos		(6U)
#define PIXEL_VALID_Msk		(0x1U << PIXEL_VALID_Pos)
#define PIXEL_VALID			PIXEL_VALID_Msk
#define PIXEL_SOF_Pos		(7U)
#define PIXEL_SOF_Msk		(0x1U << PIXEL_SOF_Msk)
#define PIXEL_SOF			PIXEL_SOF_Msk

// Inverse product register bits
#define INV_PROD_Pos		(0U)
#define INV_PROD_Msk		(0xFU << INV_PROD_Pos)
#define INV_PROD			INV_PROD_Msk

void adns2610_init(void);
void adns2610_start(void);
uint8_t adns2610_readRegister(Device dev, uint8_t reg);
void adns2610_writeRegister(Device dev, uint8_t reg, uint8_t value);

#endif /* INC_ADNS_2610_H_ */
