/*
 * adns-2610.c
 *
 *  Created on: Sep 14, 2020
 *      Author: deros
 */

#include "adns-2610.h"

// Private defines
#define FULL_DUPLEX_SPI true
#define GET_SPI_PERIPH(Device, PeriphPtr)	 (PeriphPtr = Device == 0 ? SPI2 : SPI3)
#define GET_DEV_NAME(dev, str)	(str = dev == ADNS2610_RIGHT ? "ADNS2610_RIGHT" : "ADNS2610_LEFT")

// Private static vars
static SPI_TypeDef * SPIx;

// Private function prototypes
void adns2610_resetCOM(Device dev);
void adns2610_config(Device dev);
void adns2610_configureTIM();
void adns2610_configureSPI();
void adns2610_receiveByte(Device dev, uint8_t* value);
void adns2610_sendBytes(Device dev, uint8_t* value, uint8_t length);


void adns2610_init(void){
	// Configure the timer to read the frames continuously
	adns2610_configureTIM();

	// Configure the SPI peripherals for each sensor
	adns2610_configureSPI();

	// Reset communication with ADNS sensors
	adns2610_resetCOM(ADNS2610_RIGHT);

	// Configure sensors
	adns2610_config(ADNS2610_RIGHT);
}

void adns2610_start(void){
	// Enable and start timer
	SET_BIT(TIM1->CR1, TIM_CR1_CEN);
}

void adns2610_processFSM(void){

}

void adns2610_configureSPI(){
	// RX FIFO threshold adjusted to 8-bit word
	SET_BIT(SPI2->CR2, SPI_CR2_FRXTH);
	// Enable SPI
	SET_BIT(SPI2->CR1, SPI_CR1_SPE);
}

void adns2610_configureTIM(){
	// TIM1 prescalers has been configured to count microseconds
	uint32_t temp = TIM1->CR1;

	// Disable update interrupt
	SET_BIT(TIM1->DIER, TIM_DIER_UIE);
	// Modify CR1 register
	MODIFY_REG(temp, ~(TIM_CR1_UDIS), TIM_CR1_URS);
	TIM1->CR1 = temp;
	// Set interrupt interval
	TIM1->ARR = ADNS2610_READ_TIME;
	// Update the prescaler and counter registers
	SET_BIT(TIM1->EGR, TIM_EGR_UG);
	// Clear pending interrupt flag
	CLEAR_BIT(TIM1->SR, TIM_SR_UIF);
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

	printf("Setting the sensor to always awake in %s...\r\n", _(ADNS_2610_CONFIG));
	adns2610_writeRegister(dev, ADNS_2610_CONFIG, CONFIG_C0);

	printf("Checking if %s has been written well... ", _(ADNS_2610_CONFIG));
	if(adns2610_readRegister(dev, ADNS_2610_CONFIG) == CONFIG_C0) printf("OK.\r\n");
	else{ printf("ERROR.\r\n"); while(1);}

	printf("Checking into %s if the sensor is awake... ", _(ADNS_2610_STATUS));
	if(adns2610_readRegister(dev, ADNS_2610_STATUS) == STATUS_AWAKE) printf("OK.\r\n");
	else{ printf("ERROR.\r\n"); while(1);}

	printf("Checking into %s if the sensor responds well... ", _(ADNS_2610_INVERSE_ID));
	if((adns2610_readRegister(dev, ADNS_2610_INVERSE_ID) & INV_PROD)  == INV_PROD) printf("OK.\r\n");
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

void adns2610_sendByte(Device dev, uint8_t* value){

	GET_SPI_PERIPH(dev, SPIx);

	#if FULL_DUPLEX_SPI
	// Check TXE to send data
	while(!(READ_BIT(SPIx->SR, SPI_SR_TXE)));
	// Write DR to send data through SPI
	WRITE_REG(*(__IO uint8_t*) &SPIx->DR, *value);
	// Wait until RXNE is set
	while(!(READ_BIT(SPIx->SR, SPI_SR_RXNE)));
	READ_REG(*(__IO uint8_t*) &SPIx->DR);
	#else	// HALF DUPLEX SPI MODE

	#endif
}

void TIM1_UP_TIM16_IRQHandler(void){
	// If the interrupt flag is enabled
	if(READ_BIT(TIM1->SR, TIM_SR_UIF)){
		// Process FSM
		adns2610_processFSM();
		// Clear pending interrupt flag
		CLEAR_BIT(TIM1->SR, TIM_SR_UIF);
	}
}
