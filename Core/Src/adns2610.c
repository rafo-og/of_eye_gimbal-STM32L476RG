/*
 * adns-2610.c
 *
 *  Created on: Sep 14, 2020
 *      Author: deros
 */

#include <adns2610.h>

// Private defines
#define FULL_DUPLEX_SPI true

// Global variables declared in adns-2610.h
extern pixelTypeDef pixBuf_adns_right [2][PIXEL_QTY];

// Private macros
#define GET_SPI_PERIPH(Device, PeriphPtr)	 (PeriphPtr = Device == 0 ? SPI2 : SPI3)
#define GET_DEV_NAME(dev, str)	(str = dev == ADNS2610_RIGHT ? "ADNS2610_RIGHT" : "ADNS2610_LEFT")

// Private static variables
static SPI_TypeDef * SPIx;

// Private function prototypes
void adns2610_resetCOM(Device dev);
void adns2610_config(Device dev);
void adns2610_configureSPI(Device dev);

/**
 * @brief Initialize the ADNS2610 sensor
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 */
void adns2610_init(Device dev){
	// Configure the SPI peripherals for each sensor
	adns2610_configureSPI(dev);

	// Reset communication with ADNS sensors
	adns2610_resetCOM(dev);

	// Configure sensors
	adns2610_config(dev);
}
/**
 * @brief Configure the SPI module pointed by Device argument
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 */
void adns2610_configureSPI(Device dev){
	GET_SPI_PERIPH(dev, SPIx);
	// RX FIFO threshold adjusted to 8-bit word
	SET_BIT(SPIx->CR2, SPI_CR2_FRXTH);
	// Enable SPI
	SET_BIT(SPIx->CR1, SPI_CR1_SPE);
}
/**
 * @brief Reset the ADNS2610 serial port. It needs to be done at the beginning to establish the communication
 * 		  correctly
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 */
void adns2610_resetCOM(Device dev){

	GET_SPI_PERIPH(dev, SPIx);

	// Check TXE to send data
	while(!(READ_BIT(SPIx->SR, SPI_SR_TXE)));
	// Write DR to send data through SPI
	WRITE_REG(*(__IO uint8_t*) &SPIx->DR, 0x01);
	// Wait until RXNE is set
	while(!(READ_BIT(SPIx->SR, SPI_SR_RXNE)));
	READ_REG(*(__IO uint8_t*) &SPIx->DR);
	// Wait until end the current transaction
	while((READ_BIT(SPIx->SR, SPI_SR_FTLVL)) | (READ_BIT(SPIx->SR, SPI_SR_FRLVL)) | (READ_BIT(SPIx->SR, SPI_SR_BSY)));
	LL_mDelay(100);
}
/**
 * @brief Configure the ADNS2610 internal register. Set always awake and check the inverse product ID register
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 */
void adns2610_config(Device dev){
	// ADNS-2610 configuration
	char * devName;

	GET_DEV_NAME(dev, devName);

	printf("--------------------------------\r\n--> %s CONFIGURATION \r\n--------------------------------\r\n", devName);

	printf("Setting the sensor to always awake in %s...\r\n", _(ADNS2610_CONFIG));
	adns2610_writeRegister(dev, ADNS2610_CONFIG_REG, ADNS2610_CONFIG_C0);

	printf("Checking if %s has been written well... ", _(ADNS2610_CONFIG));
	if(adns2610_readRegister(dev, ADNS2610_CONFIG_REG) == ADNS2610_CONFIG_C0) printf("OK.\r\n");
	else{ printf("ERROR.\r\n"); while(1);}

	printf("Checking into %s if the sensor is awake... ", _(ADNS2610_STATUS));
	if(adns2610_readRegister(dev, ADNS2610_STATUS_REG) == ADNS2610_STATUS_AWAKE) printf("OK.\r\n");
	else{ printf("ERROR.\r\n"); while(1);}

	printf("Checking into %s if the sensor responds well... ", _(ADNS2610_INVERSE_ID));
	if((adns2610_readRegister(dev, ADNS2610_INVERSE_ID_REG) & ADNS2610_INV_PROD)  == ADNS2610_INV_PROD) printf("OK.\r\n");
	else{ printf("ERROR.\r\n"); while(1);}

	printf("\r\n");
}
/**
 * @brief Read a ADNS2610 internal register by polling
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 * @param reg Internal register ADDRESS, see adns2610.h
 * @return Register value
 */
uint8_t adns2610_readRegister(Device dev, uint8_t reg){

	uint8_t value;

	GET_SPI_PERIPH(dev, SPIx);

	#if FULL_DUPLEX_SPI
	// Check TXE to send data
	while(!(READ_BIT(SPIx->SR, SPI_SR_TXE)));
	// Write DR to send data through SPI
	WRITE_REG(*(__IO uint8_t*) &SPIx->DR, reg);
	// Wait until RXNE is set
	while(!(READ_BIT(SPIx->SR, SPI_SR_RXNE)));
	READ_REG(*(__IO uint8_t*) &SPIx->DR);
	LL_mDelay(1);
	// Write DR to send data through SPI
	WRITE_REG(*(__IO uint8_t*) &SPIx->DR, 0x00);
	// Wait until RXNE is set
	while(!(READ_BIT(SPIx->SR, SPI_SR_RXNE)));
	value = READ_REG(*(__IO uint8_t*) &SPIx->DR);
	// Wait until end the current transaction
	while((READ_BIT(SPIx->SR, SPI_SR_FTLVL)) | (READ_BIT(SPIx->SR, SPI_SR_FRLVL)) | (READ_BIT(SPIx->SR, SPI_SR_BSY)));
	return value;
	#else	// HALF DUPLEX SPI MODE

	#endif
}
/**
 * @brief Write a ADNS2610 internal register by polling
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 * @param reg Internal register ADDRESS, see adns2610.h
 * @param value Value to write in the internal register
 */
void adns2610_writeRegister(Device dev, uint8_t reg, uint8_t value){

	GET_SPI_PERIPH(dev, SPIx);

	#if FULL_DUPLEX_SPI
	// RX FIFO threshold adjusted to 16-bit word
	CLEAR_BIT(SPIx->CR2, SPI_CR2_FRXTH);
	// Check TXE to send data
	while(!(READ_BIT(SPIx->SR, SPI_SR_TXE)));
	// Write DR to send data through SPI
	WRITE_REG(SPIx->DR, (value << 8) | (1U << 7 | reg));
	// Wait until RXNE is set
	while(!(READ_BIT(SPIx->SR, SPI_SR_RXNE)));
	READ_REG(SPIx->DR);
	// Wait until end the current transaction
	while((READ_BIT(SPIx->SR, SPI_SR_FTLVL)) | (READ_BIT(SPIx->SR, SPI_SR_FRLVL)) | (READ_BIT(SPIx->SR, SPI_SR_BSY)));
	// Set again RX FIFO threshold adjusted to 8-bit word
	SET_BIT(SPIx->CR2, SPI_CR2_FRXTH);
	#else	// HALF DUPLEX SPI MODE

	#endif
}
/**
 * @brief Receive a byte from ADNS2610 as reply of adns2610_sendByte(Device dev, uint8_t value) function
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 * @param value Pointer to a variable where the received value is stored
 */
void adns2610_receiveByte(Device dev, uint8_t* value){

	GET_SPI_PERIPH(dev, SPIx);

	#if FULL_DUPLEX_SPI
	// Write DR to send data through SPI
	WRITE_REG(*(__IO uint8_t*) &SPIx->DR, 0x00);
	// Wait until RXNE is set
	while(!(READ_BIT(SPIx->SR, SPI_SR_RXNE)));
	*value = READ_REG(*(__IO uint8_t*) &SPIx->DR);
	// Wait until end the current transaction
	while((READ_BIT(SPIx->SR, SPI_SR_FTLVL)) | (READ_BIT(SPIx->SR, SPI_SR_FRLVL)) | (READ_BIT(SPIx->SR, SPI_SR_BSY)));
	#else	// HALF DUPLEX SPI MODE

	#endif
}
/**
 * @brief Send a byte to ADNS2610. It's used to request to ADNS2610 a register value in IT mode
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 * @param value Value of the sent value
 */
void adns2610_sendByte(Device dev, uint8_t value){

	GET_SPI_PERIPH(dev, SPIx);

	#if FULL_DUPLEX_SPI
	// Check TXE to send data
	while(!(READ_BIT(SPIx->SR, SPI_SR_TXE)));
	// Write DR to send data through SPI
	WRITE_REG(*(__IO uint8_t*) &SPIx->DR, value);
	// Wait until RXNE is set
	while(!(READ_BIT(SPIx->SR, SPI_SR_RXNE)));
	READ_REG(*(__IO uint8_t*) &SPIx->DR);
	#else	// HALF DUPLEX SPI MODE

	#endif
}
/**
 * @brief Read a frame from ADNS2610 by polling
 * @param dev Device address, it refers to SPI peripheral where the sensor is connected
 * @param buffer Array where the frame is going to be stored
 */
void adns2610_readFrame(Device dev, pixelTypeDef buffer[]){
	uint16_t idx = 0;

	while(idx < PIXEL_QTY){
		if(!idx){
			adns2610_writeRegister(dev, ADNS2610_PIXEL_DATA_REG, 0x01);
			LL_mDelay(1);
			buffer[idx] = adns2610_readRegister(dev, ADNS2610_PIXEL_DATA_REG);

			if(buffer[idx] & (ADNS2610_PIXEL_VALID | ADNS2610_PIXEL_SOF)){
				idx++;
				continue;
			}
		}

		buffer[idx] = adns2610_readRegister(dev, ADNS2610_PIXEL_DATA_REG);

		if(buffer[idx] & ADNS2610_PIXEL_SOF){
			idx = 0;
			LL_mDelay(1);
			continue;
		}

		if(buffer[idx] & ADNS2610_PIXEL_VALID){
			idx++;
		}
	}
}
/**
 * @brief Check the status of a pixel
 * @param Pixel The PIXEL DATA register value received from ADNS2610
 * @return See PixelStatus
 */
PixelStatus adns2610_checkPixel(pixelTypeDef* Pixel){
	if(*Pixel & ADNS2610_PIXEL_VALID){
		if(*Pixel & ADNS2610_PIXEL_SOF){
			return VALID_SOF;
		}
		return VALID;
	}
	else if(*Pixel & ADNS2610_PIXEL_SOF){
		return NON_VALID_SOF;
	}
	else{
		return NON_VALID;
	}
}
/**
 * @brief Print the received frame values in the console through UART
 * @param frame	The array which contains the pixel values
 */
void adns2610_printImage(pixelTypeDef frame[]){
	uint16_t i = 0;

	printf("=======================================================\r\n||");

	while(i < PIXEL_QTY){
		if(!(i % 18) & (i > 1)){
			printf("||\r\n||");
		}
		printf("%02d ", frame[i] & ADNS2610_PIXEL_DATA);
		i++;
	}

	printf("||\r\n=======================================================\r\n");
}

