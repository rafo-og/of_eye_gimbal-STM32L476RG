/*
 * adns-2610.c
 *
 *  Created on: Sep 14, 2020
 *      Author: deros
 */

#include "adns-2610.h"

void adns2610_init(void){
	// TIM1 prescalers has been configured to count microseconds
	uint32_t temp = TIM1->CR1;
	MODIFY_REG(temp, ~(TIM_CR1_UDIS), TIM_CR1_URS);
	TIM1->CR1 = temp;
	// Set interrupt interval
	TIM1->ARR = ADNS2610_READ_TIME;
	// Enable update interrupt
	SET_BIT(TIM1->DIER, TIM_DIER_UIE);
	// Update the prescaler and counter registers
	SET_BIT(TIM1->EGR, TIM_EGR_UG);
	// Configure NVIC to handle TIM1 update interrupt
	NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0);
	NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

}

void adns2610_start(void){
	// Enable and start timer
	SET_BIT(TIM1->CR1, TIM_CR1_CEN);
}

void adns2610_processFSM(void){

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
