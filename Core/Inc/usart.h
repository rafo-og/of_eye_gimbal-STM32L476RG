/**
  ******************************************************************************
  * File Name          : USART.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
 /* Private typedefs --------------------------------------------------------*/
 typedef enum{
	 BYTE = 0x00,
	 HALF_WORD = 0x01,
	 WORD = 0x02
 } WordLenghtDMA_t;

 typedef enum{
 	 LOW = 00,
 	 MEDIUM = 0x01,
 	 HIGH = 0x02,
	 VERY_HIGH = 0x03
  } PriorityDMA_t;
/* USER CODE END Private defines */

void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void configureDMA_USART_TX(USART_TypeDef* USARTx, WordLenghtDMA_t wordLength, PriorityDMA_t priority);

__STATIC_INLINE void transferDMA_USART2_TX(uint32_t fromAddress, uint16_t dataLength){

	__IO uint32_t temp = 0;

	DMA1_Channel7->CMAR = (__IO uint32_t) fromAddress;
	DMA1_Channel7->CNDTR = dataLength;
	temp = DMA1_Channel7->CCR;
	SET_BIT(temp, DMA_CCR_EN);
	DMA1_Channel7->CCR = temp;
}

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
