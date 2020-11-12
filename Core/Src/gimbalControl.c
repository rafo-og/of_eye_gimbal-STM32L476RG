/*
 * gimbalControl.c
 *
 *  Created on: 27 oct. 2020
 *      Author: deros
 */

/* Includes ------------------------------------------------------------------*/
#include "gimbalControl.h"

/* Private macro -------------------------------------------------------------*/
#define TAIL_CHAR	'\n'
#define BUFFER_SIZE	10

/* DC PWM default and range values in CNT format*/
#define MIN_POS		999			// 1 ms
#define CENTER_POS	1499		// 1.5 ms
#define MAX_POS		1999		// 2 ms
#define DELTA_POS	2			// 5us

/* Private typedefs --------------------------------------------*/
typedef enum commandEnum{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	CENTER,
	TRACKING_ON,
	TRACKING_OFF,
	NA
} cmdTypeDef;

typedef struct{
	uint16_t pitchPos;
	uint16_t rollPos;
	uint16_t yawPos;
}motorPosTypeDef;

/* Private variables -------------------------------------------*/
char bufferIn[BUFFER_SIZE];
int i = 0;
motorPosTypeDef motorPos = { .pitchPos = CENTER_POS, .rollPos = CENTER_POS, .yawPos = CENTER_POS};
bool pwmEn;
bool trackingEn;

/* Private functions -------------------------------------------*/
cmdTypeDef decodeCmd(char const * cmdString, int length);
void enablePWM();
void disablePWM();

/**
 * @brief Setting up all the peripherals (UART and TIMER) needed to control de gimbal position
 */
void gimbalControlInit(void){
	// Configure UART2 interrupt to receive data from PC
	configure_IRQ_USART_RX();

	// Flag to know PWM signal state
	pwmEn = false;

	// Flag to know if tracking function is enable/disable
	trackingEn = false;
}

/* --------------------------------------------------
 * PWM OUTPUTS:
 * 		- RC-1: Pith	-->		TIM3->CH1	-->	PA7
 * 		- RC-2: Roll	-->		TIM3->CH2	-->	PA6
 * 		- RC-3: Yaw		-->		TIM3->CH4	-->	PB1
 * --------------------------------------------------
 */
/**
 * @brief Receive a string and decode the command type related to it
 * @param cmdString	The command in string format
 * @param length	The length of the command
 * @return	The command type in cmdTypeDef format
 */
cmdTypeDef decodeCmd(char const * cmdString, int length){

	// Enable PWM if it was disabled
	if(!pwmEn)	enablePWM();

	// Tracking enable command
	if(strncmp(cmdString, "TRON\n", length) == 0){
		trackingEn = true;
		return TRACKING_ON;
	}
	if(strncmp(cmdString, "TROFF\n", length) == 0){
		trackingEn = false;
		return TRACKING_OFF;
	}

	// Tracking enable so It isn't able to perform any command
	if(trackingEn) return NA;

	// Center command
	if(strncmp(cmdString, "CN\n", length) == 0){

		motorPos.pitchPos = CENTER_POS;
		motorPos.rollPos = CENTER_POS;
		motorPos.yawPos = CENTER_POS;

		TIM3->CCR1 = motorPos.pitchPos;
		TIM3->CCR2 = motorPos.rollPos;
		TIM3->CCR4 = motorPos.yawPos;

		return CENTER;
	}

	// Up command
	if(strncmp(cmdString, "UP\n", length) == 0){
		if(motorPos.pitchPos > MIN_POS) motorPos.pitchPos -= DELTA_POS;
		TIM3->CCR2 = motorPos.pitchPos;
		return UP;
	}
	// Down command
	if(strncmp(cmdString, "DW\n", length) == 0){
		if(motorPos.pitchPos < MAX_POS) motorPos.pitchPos += DELTA_POS;
		TIM3->CCR2 = motorPos.pitchPos;
		return DOWN;
	}
	// Left command
	if(strncmp(cmdString, "LF\n", length) == 0){
		if(motorPos.yawPos > MIN_POS) motorPos.yawPos -= DELTA_POS;
		TIM3->CCR4 = motorPos.yawPos;
		return LEFT;
	}
	// Right command
	if(strncmp(cmdString, "RH\n", length) == 0){
		if(motorPos.yawPos < MAX_POS) motorPos.yawPos += DELTA_POS;
		TIM3->CCR4 = motorPos.yawPos;
		return RIGHT;
	}

	// Rotate left command
	if(strncmp(cmdString, "RLF\n", length) == 0){
		if(motorPos.rollPos < MAX_POS) motorPos.rollPos += DELTA_POS;
		TIM3->CCR1 = motorPos.rollPos;
		return ROTATE_LEFT;
	}
	// Rotate right command
	if(strncmp(cmdString, "RRH\n", length) == 0){
		if(motorPos.rollPos > MIN_POS) motorPos.rollPos -= DELTA_POS;
		TIM3->CCR1 = motorPos.rollPos;
		return ROTATE_RIGHT;
	}
	return NA;
}

void applyControlLaw(int x, int y, int rotation){

	if(!trackingEn) return;

	if(motorPos.yawPos < MAX_POS && motorPos.yawPos > MIN_POS) motorPos.yawPos += x >> 4;
	TIM3->CCR4 = motorPos.yawPos;
}

bool IsTrackingEnable(){
	return trackingEn;
}

void enablePWM(){
	// Enable output compare OCx channels
	//SET_BIT(TIM3->CCER, TIM_CCER_CC4E);
	MODIFY_REG(TIM3->CCER, ~(TIM_CCER_CC1NE | TIM_CCER_CC2NE),
			(TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC4E));

	// Enable master output
	MODIFY_REG(TIM3->BDTR, ~(TIM_BDTR_OSSI | TIM_BDTR_OSSR), TIM_BDTR_MOE);

	// Enable counter
	SET_BIT(TIM3->CR1, TIM_CR1_CEN);

	pwmEn = true;
}

void disablePWM(){
	// Disable output
	//CLEAR_BIT(TIM3->CCER, TIM_CCER_CC4E);
	CLEAR_BIT(TIM3->CCER, (TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC4E));

	// Disable master output
	CLEAR_BIT(TIM3->BDTR, TIM_BDTR_MOE);

	// Disable counter
	CLEAR_BIT(TIM3->CR1, TIM_CR1_CEN);

	// Reset motor position struct to initial values
	motorPos.pitchPos = CENTER_POS;
	motorPos.rollPos = CENTER_POS;
	motorPos.yawPos = CENTER_POS;

	pwmEn = false;
}

void USART2_IRQHandler(void){
	if(READ_BIT(USART2->ISR, USART_ISR_ORE)){
		SET_BIT(USART2->ICR, USART_ICR_ORECF);
		// Flush all data in USART RX
		SET_BIT(USART2->RQR, USART_RQR_RXFRQ);
	}
	if(READ_BIT(USART2->ISR, USART_ISR_RXNE)){
		bufferIn[i] = READ_REG(USART2->RDR);

		if(bufferIn[i] == TAIL_CHAR){
			i++;
			decodeCmd(bufferIn, i);
			i = 0;
		}
		else if(i ==  BUFFER_SIZE){
			i = 0;
		}
		else{
			i++;
		}
	}

}
