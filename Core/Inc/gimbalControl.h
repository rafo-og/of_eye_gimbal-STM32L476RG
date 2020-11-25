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
#include <stdlib.h>

/* Exported functions --------------------------------------------------------*/
void gimbalControlInit(void);
void applyControlLaw(int x, int y, int rotation);
bool IsTrackingEnable();

#endif /* INC_GIMBALCONTROL_H_ */
