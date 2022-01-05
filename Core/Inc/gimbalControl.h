/*
 * gimbalControl.h
 *
 *  Created on: 27 oct. 2020
 *      Author: Rafael de la Rosa Vidal
 * 
 *  This code is licensed under the GNU v2.0 license
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
bool IsCalibrationModeEnable();

#endif /* INC_GIMBALCONTROL_H_ */
