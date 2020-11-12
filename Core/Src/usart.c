/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* Private defines -----------------------------------------------------------*/
#define DMA_USART2_TX_REQ	0x02 << DMA_CSELR_C7S_Pos

/* USER CODE END 0 */

/* USART2 init function */

void MX_USART2_UART_Init(void)
{
  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**USART2 GPIO Configuration
  PA2   ------> USART2_TX
  PA3   ------> USART2_RX
  */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  USART_InitStruct.BaudRate = 921600;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_8;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_Enable(USART2);

}

/* USER CODE BEGIN 1 */
void __io_putchar(int ch){
#if DEBUG_TO_CONSOLE
	// Wait until all data have been transmitted
	while(!(READ_BIT(USART2->ISR, USART_ISR_TXE)));
	// Write data to transmit register
	WRITE_REG(USART2->TDR, ch);
	// Wait until transmission completed
	while(!(READ_BIT(USART2->ISR, USART_ISR_TC)));
#endif
}

void __io_getchar(void){
	// NOT IMPLEMENTED
}

void startupPrint(void){
	printf("\r\n");
	printf("+==============================================================+\r\n");
	printf("|%62.62s|\r\n", DESCRIPTION);
	printf("+--------------------+--------------------+--------------------+\r\n");
	printf("+ %18.18s | HW: %14.14s | VER.%14.14s |\r\n", "Rafael de la Rosa", HW, FIRM_VERSION);
	printf("+==============================================================+\r\n\r\n");
}

void configureDMA_USART_TX(USART_TypeDef* USARTx, WordLenghtDMA_t wordLength, PriorityDMA_t priority){

	__IO uint32_t temp = 0;
	uint32_t mSize, pSize;

	priority = priority << DMA_CCR_PL_Pos;
	mSize = wordLength << DMA_CCR_MSIZE_Pos;
	pSize = wordLength << DMA_CCR_PSIZE_Pos;

	// DMAx channel configuration
	if(USARTx == USART2){
		/* Enable clock for DMA1 controller */
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

		/* Configure DMA mode transmission in USART_CR3*/
		SET_BIT(USARTx->CR3, USART_CR3_DMAT);

		/* Configure the channel 7 which corresponds to USART2 peripheral */
		SET_BIT(DMA1_CSELR->CSELR, DMA_USART2_TX_REQ);

		/* Clear pending interrupts */
		SET_BIT(DMA1->IFCR, (DMA_IFCR_CGIF7 | DMA_IFCR_CHTIF7 | DMA_IFCR_CTCIF7 | DMA_IFCR_CTEIF7));

		/* Configure DMA transference */
		DMA1_Channel7->CPAR =(__IO uint32_t) &(USART2->TDR);
		temp = priority | mSize | pSize | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE | DMA_CCR_TEIE;
		DMA1_Channel7->CCR = temp;

		NVIC_SetPriority(DMA1_Channel7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
		NVIC_EnableIRQ(DMA1_Channel7_IRQn);
	}
}

void configure_IRQ_USART_RX(){
	// Set RXNEIE to enable the RX interrupt
	SET_BIT(USART2->CR1, USART_CR1_RXNEIE);

	// Enable global interrupt for UART2
	NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	NVIC_EnableIRQ(USART2_IRQn);
}

void DMA1_Channel7_IRQHandler(void){
	/* Check the interrupt source*/
	if(READ_BIT(DMA1->ISR, DMA_ISR_TEIF7)){
		SET_BIT(DMA1->IFCR, DMA_IFCR_CTEIF7);
		while(1);
	}
	if(READ_BIT(DMA1->ISR, DMA_ISR_TCIF7)){
		SET_BIT(DMA1->IFCR, DMA_IFCR_CTCIF7);
		CLEAR_BIT(DMA1_Channel7->CCR, DMA_CCR_EN);
	}
	/* Clear Global interrupt status bit */
	if(READ_BIT(DMA1->ISR, DMA_ISR_GIF7)){
		SET_BIT(DMA1->IFCR, DMA_IFCR_CGIF7);
	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
