/*
 * gimbalControl.h
 *
 *  Created on: 27 oct. 2020
 *      Author: deros
 */

#ifndef INC_GIMBALCONTROL_H_
#define INC_GIMBALCONTROL_H_

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "string.h"
#include "commonTypes.h"
#include <stdlib.h>

/* Exported types ------------------------------------------------------------*/
typedef enum ControlLawMode{
	LEFT_ONLY,
	RIGHT_ONLY,
	ALL
} ControlLawModeTypeDef;

/* Exported functions --------------------------------------------------------*/
void gimbalControlInit(void);
void applyControlLaw(frameStruct * frame, ControlLawModeTypeDef mode);
bool IsTrackingEnable();

#endif /* INC_GIMBALCONTROL_H_ */
