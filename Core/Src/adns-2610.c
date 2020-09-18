/*
 * adns-2610.c
 *
 *  Created on: Sep 14, 2020
 *      Author: deros
 */

#include "adns-2610.h"

// Private defines
#define FULL_DUPLEX_SPI true

// Global variables declared in adns-2610.h
extern pixelTypeDef pixBuf_adns_right [2][PIXEL_QTY];
extern uint8_t currentFrame;
extern uint8_t pastFrame;

// Private macros
#define GET_SPI_PERIPH(Device, PeriphPtr)	 (PeriphPtr = Device == 0 ? SPI2 : SPI3)
#define GET_DEV_NAME(dev, str)	(str = dev == ADNS2610_RIGHT ? "ADNS2610_RIGHT" : "ADNS2610_LEFT")
#define SWITCH_FRAME(current, past)	{uint8_t temp; temp = past; past = current; current = temp;}

// Private variables
typedef enum adns2610_state{
	SENSOR_RESET,
	TRIGGER_FRAME,
	READING_FRAME,
	REQ_READING_FRAME,
	PROCESSING
} adns2610_state_TypeDef;

// Private static variables
static SPI_TypeDef * SPIx;
static adns2610_state_TypeDef FSM_state;

// Private function prototypes
void adns2610_resetCOM(Device dev);
void adns2610_config(Device dev);
void adns2610_configureTIM();
void adns2610_configureSPI(Device dev);
void adns2610_receiveByte(Device dev, uint8_t* value);
void adns2610_sendByte(Device dev, uint8_t value);
void adns2610_checkPixel(pixelTypeDef* Pixel, uint16_t* idx);
void printImage(pixelTypeDef frame[]);

__STATIC_INLINE void adns2610_wait(uint32_t useconds);
__STATIC_INLINE void adns2610_stopWait(void);

/**
 * @brief Initialize the ADNS-2610
 */
void adns2610_init(Device dev){
	// Configure the timer to read the frames continuously
	adns2610_configureTIM();

	// Configure the SPI peripherals for each sensor
	adns2610_configureSPI(dev);

	// Reset communication with ADNS sensors
	adns2610_resetCOM(dev);

	// Configure sensors
	adns2610_config(dev);

	FSM_state = RESET;
	currentFrame = 0;
	pastFrame = 1;
}

__STATIC_INLINE void adns2610_wait(uint32_t useconds){
	// Disable update interrupt generation
	SET_BIT(TIM1->CR1, TIM_CR1_URS);
	// Set time to wait
	TIM1->ARR = useconds;
	// Update the prescaler and counter registers
	SET_BIT(TIM1->EGR, TIM_EGR_UG);
	// Enable update interrupt generation
	CLEAR_BIT(TIM1->CR1, TIM_CR1_URS);
	// Enable and start timer
	SET_BIT(TIM1->CR1, TIM_CR1_CEN);
}

__STATIC_INLINE void adns2610_stopWait(void){
	// Enable and start timer
	CLEAR_BIT(TIM1->CR1, TIM_CR1_CEN);
}

void adns2610_start(void){
	if(FSM_state == SENSOR_RESET){
		FSM_state = TRIGGER_FRAME;
		adns2610_wait(1);
	}
}

void adns2610_stop(void){
	if(FSM_state != SENSOR_RESET){
		FSM_state = SENSOR_RESET;
		adns2610_wait(UINT32_MAX);
	}
}

void adns2610_processFSM(void){
	static uint16_t frameIdx = 0;
//	static uint8_t collisionFlag = 0;

	switch(FSM_state){
	case SENSOR_RESET:
//		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		frameIdx = 0;
		adns2610_stopWait();
//		collisionFlag = 0;
		return;
	case TRIGGER_FRAME:
		adns2610_stopWait();
		frameIdx = 0;
//		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		FSM_state = REQ_READING_FRAME;
		adns2610_writeRegister(ADNS2610_RIGHT, ADNS2610_PIXEL_DATA_REG, 0x01);
//		collisionFlag = 0;
		adns2610_wait(ADNS2610_TIM_BTW_WR);
		return;
	case REQ_READING_FRAME:
		adns2610_stopWait();
//		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		FSM_state = READING_FRAME;
		adns2610_sendByte(ADNS2610_RIGHT, ADNS2610_PIXEL_DATA_REG);
//		collisionFlag = 0;
		adns2610_wait(ADNS2610_TIM_TO_RD);
		return;
	case READING_FRAME:
		adns2610_stopWait();
//		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		adns2610_receiveByte(ADNS2610_RIGHT, &(pixBuf_adns_right[currentFrame][frameIdx]));

		adns2610_checkPixel(&(pixBuf_adns_right[currentFrame][frameIdx]), &frameIdx);

		if(frameIdx == 324){
			FSM_state = PROCESSING;
			frameIdx = 0;
		}
		else{
			FSM_state = REQ_READING_FRAME;
		}
//		collisionFlag = 0;
		adns2610_wait(ADNS2610_TIM_BTW_RD);
		return;
	case PROCESSING:
		adns2610_stopWait();
//		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		FSM_state = TRIGGER_FRAME;
		printImage(pixBuf_adns_right[currentFrame]);
		SWITCH_FRAME(currentFrame, pastFrame);
//		collisionFlag = 0;
		printf("PROCESSING\r\n");
		adns2610_wait(1);
		return;
	}

//	collisionError:
//		printf("COLISSION ERROR!!\r\n");
//		adns2610_stopWait();
//		while(1);
}

void adns2610_configureSPI(Device dev){
	GET_SPI_PERIPH(dev, SPIx);
	// RX FIFO threshold adjusted to 8-bit word
	SET_BIT(SPIx->CR2, SPI_CR2_FRXTH);
	// Enable SPI
	SET_BIT(SPIx->CR1, SPI_CR1_SPE);
}

void adns2610_configureTIM(){
	// TIM1 prescalers has been configured to count microseconds
	uint32_t temp = TIM1->CR1;

	// Disable update interrupt
	CLEAR_BIT(TIM1->DIER, TIM_DIER_UIE);
	// Modify CR1 register
	MODIFY_REG(temp, ~(TIM_CR1_UDIS), TIM_CR1_URS);
	TIM1->CR1 = temp;
	// Set interrupt interval
	TIM1->ARR = ADNS2610_TIM_TO_RD;
	// Update the prescaler and counter registers
	SET_BIT(TIM1->EGR, TIM_EGR_UG);
	// Clear pending interrupt flag
	CLEAR_BIT(TIM1->SR, TIM_SR_UIF);
	// Enable update interrupt generation
	CLEAR_BIT(TIM1->CR1, TIM_CR1_URS);
	// Enable update interrupt
	SET_BIT(TIM1->DIER, TIM_DIER_UIE);
	// Configure NVIC to handle TIM1 update interrupt
	NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0);
	NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
}

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

void adns2610_readFrameSync(Device dev, pixelTypeDef buffer[]){
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

void adns2610_checkPixel(pixelTypeDef* Pixel, uint16_t* idx){
	if(*Pixel & ADNS2610_PIXEL_VALID){
		if((!*idx) & (*Pixel & ADNS2610_PIXEL_SOF)){
			(*idx)++;
		}
		else if(*idx & !(*Pixel & ADNS2610_PIXEL_SOF)){
			(*idx)++;
		}
		else{
			FSM_state = TRIGGER_FRAME;
		}
	}
//	if(!*idx){
//		if(*Pixel & (PIXEL_VALID | PIXEL_SOF)){
//			(*idx)++;
//		}
//		else{
//			(*idx) = 0;
//		}
//	}
//	else if (*Pixel & PIXEL_VALID){
//		(*idx)++;
//	}
}

void printImage(pixelTypeDef frame[]){
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

void TIM1_UP_TIM16_IRQHandler(void){
	// If the interrupt flag is enabled
	if(READ_BIT(TIM1->SR, TIM_SR_UIF)){
		// Clear pending interrupt flag
		CLEAR_BIT(TIM1->SR, TIM_SR_UIF);
		// Process FSM
		adns2610_processFSM();
	}
}
