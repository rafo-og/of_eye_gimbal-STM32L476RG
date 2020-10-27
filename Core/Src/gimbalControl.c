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

/* Private variables -------------------------------------------*/
char bufferIn[BUFFER_SIZE];
int i = 0;

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

/* Private functions -------------------------------------------*/
cmdTypeDef decodeCmd(char const * cmdString, int length);

/**
 * @brief Setting up all the peripherals (UART and TIMER) needed to control de gimbal position
 */
void gimbalControlInit(void){
	// Configure UART2 interrupt to receive data from PC
	configure_IRQ_USART_RX();

	// Configure TIMER

}

/**
 * @brief Receive a string and decode the command type related to it
 * @param cmdString	The command in string format
 * @param length	The length of the command
 * @return	The command type in cmdTypeDef format
 */
cmdTypeDef decodeCmd(char const * cmdString, int length){
	if(strncmp(cmdString, "UP\n", length) == 0){
		return UP;
	}
	if(strncmp(cmdString, "DW\n", length) == 0){
		return DOWN;
	}
	if(strncmp(cmdString, "LF\n", length) == 0){
		return LEFT;
	}
	if(strncmp(cmdString, "RH\n", length) == 0){
		return RIGHT;
	}
	if(strncmp(cmdString, "CN\n", length) == 0){
		return CENTER;
	}
	if(strncmp(cmdString, "RLF\n", length) == 0){
		return ROTATE_LEFT;
	}
	if(strncmp(cmdString, "RRH\n", length) == 0){
		return ROTATE_RIGHT;
	}
	if(strncmp(cmdString, "TRON\n", length) == 0){
		return TRACKING_ON;
	}
	if(strncmp(cmdString, "TROFF\n", length) == 0){
		return TRACKING_OFF;
	}

	return NA;
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
