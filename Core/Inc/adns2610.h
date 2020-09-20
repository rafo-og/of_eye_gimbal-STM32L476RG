/*
 * adns-2610.h
 *
 *  Created on: Sep 14, 2020
 *      Author: deros
 */

#ifndef INC_ADNS2610_H_
#define INC_ADNS2610_H_

#include "main.h"

/* Exported constants --------------------------------------------------------*/
/** @defgroup ADNS2610 constants
 *  @{
 */

/** @defgroup ADNS2610 transference times defined in base of 250ns counter
 * @{
 */
/* Times defined in data sheet with some additional tolerance -------------*/
//#define ADNS2610_TIM_BTW_RD 		500/250					// 500ns
//#define ADNS2610_TIM_BTW_WR 		150000/250				// 150us
//#define ADNS2610_TIM_TO_RD 		150000/250				// 150us

/* Times adjusted by hand to reduce the errors in the frame transference -*/
/* Time to acquire a frame (50 + 600) * (324 pixels) + 700 = 211.3ms -> 5 GPS roughly*/
#define ADNS2610_TIM_BTW_RD 		50000/250				// 50us
#define ADNS2610_TIM_BTW_WR 		700000/250				// 300us
#define ADNS2610_TIM_TO_RD 			600000/250				// 300us
/**
 * @}
 */

/** @defgroup ADNS2610 internal registers and constants
 * @{
 */
// Pixel quantity in an ADNS2610 frame
#define PIXEL_QTY		324

/** @defgroup ADNS2610 internal registers addresses
 * @{
 */
#define ADNS2610_CONFIG_REG				0x00
#define ADNS2610_STATUS_REG				0x01
#define ADNS2610_SQUAL_REG				0x04
#define ADNS2610_PIXEL_SUM_REG			0x07
#define ADNS2610_PIXEL_DATA_REG			0x08
#define ADNS2610_INVERSE_ID_REG			0x11
/**
 * @}
 */
/** @defgroup ADNS2610 CONFIGURATION register bit definitions
 *
 */
#define ADNS2610_CONFIG_C0_Pos		(0U)
#define ADNS2610_CONFIG_C0_Msk		(0x1U << ADNS2610_CONFIG_C0_Pos)
#define ADNS2610_CONFIG_C0			ADNS2610_CONFIG_C0_Msk
#define ADNS2610_CONFIG_C6_Pos		(6U)
#define ADNS2610_CONFIG_C6_Msk		(0x1U << ADNS2610_CONFIG_C0_Pos)
#define ADNS2610_CONFIG_C6			ADNS2610_CONFIG_C0_Msk
#define ADNS2610_CONFIG_C7_Pos		(7U)
#define ADNS2610_CONFIG_C7_Msk		(0x1U << ADNS2610_CONFIG_C0_Pos)
#define ADNS2610_CONFIG_C7			ADNS2610_CONFIG_C0_Msk
/**
 * @}
 */
/** @defgroup ADNS2610 STATUS register bit definitions
 * @{
 */
#define ADNS2610_STATUS_AWAKE_Pos	(0U)
#define ADNS2610_STATUS_AWAKE_Msk	(0x1U << ADNS2610_STATUS_AWAKE_Pos)
#define ADNS2610_STATUS_AWAKE		ADNS2610_STATUS_AWAKE_Msk
#define ADNS2610_STATUS_ID_Pos		(5U)
#define ADNS2610_STATUS_ID_Msk		(0x7U << STATUS_ID_Pos)
#define ADNS2610_STATUS_ID			STATUS_ID_Msk
/**
 * @}
 */
/** @defgroup ADNS2610 PIXEL DATA register bit definitions
 * @{
 */
#define ADNS2610_PIXEL_DATA_Pos		(0U)
#define ADNS2610_PIXEL_DATA_Msk		(0x3FU << ADNS2610_PIXEL_DATA_Pos)
#define ADNS2610_PIXEL_DATA			ADNS2610_PIXEL_DATA_Msk
#define ADNS2610_PIXEL_VALID_Pos	(6U)
#define ADNS2610_PIXEL_VALID_Msk	(0x1U << ADNS2610_PIXEL_VALID_Pos)
#define ADNS2610_PIXEL_VALID		ADNS2610_PIXEL_VALID_Msk
#define ADNS2610_PIXEL_SOF_Pos		(7U)
#define ADNS2610_PIXEL_SOF_Msk		(0x1U << ADNS2610_PIXEL_SOF_Pos)
#define ADNS2610_PIXEL_SOF			ADNS2610_PIXEL_SOF_Msk
/**
 * @}
 */
/** @defgroup ADNS2610 INVERSE PRODUCT register bit definitions
 * @{
 */
#define ADNS2610_INV_PROD_Pos		(0U)
#define ADNS2610_INV_PROD_Msk		(0xFU << ADNS2610_INV_PROD_Pos)
#define ADNS2610_INV_PROD			ADNS2610_INV_PROD_Msk
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/
typedef enum {
	ADNS2610_RIGHT = 0,//!< ADNS2610_RIGHT
	ADNS2610_LEFT = 1  //!< ADNS2610_LEFT
} Device;

typedef enum{
	VALID_SOF,		   	//!< VALID_SOF: VALID bit and SOF bit are set
	NON_VALID_SOF,		//!< NON_VALID_SOF: VALID bit is cleared and SOF is set
	VALID,				//!< VALID: VALID bit is set
	NON_VALID			//!< NON_VALID: VALID bit is cleared
} PixelStatus;

typedef uint8_t pixelTypeDef;

/* Exported variables ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void adns2610_init(Device dev);
uint8_t adns2610_readRegister(Device dev, uint8_t reg);
void adns2610_writeRegister(Device dev, uint8_t reg, uint8_t value);
void adns2610_readFrame(Device dev, pixelTypeDef buffer[]);
void adns2610_receiveByte(Device dev, uint8_t* value);
void adns2610_sendByte(Device dev, uint8_t value);
void adns2610_printImage(pixelTypeDef frame[]);
PixelStatus adns2610_checkPixel(pixelTypeDef* Pixel);

#endif /* INC_ADNS2610_H_ */
