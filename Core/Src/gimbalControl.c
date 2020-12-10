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
#define MIN_POS		3199		// 1 ms
#define CENTER_POS	4799		// 1.5 ms
#define MAX_POS		6399		// 2 ms
#define DELTA_POS		70
#define CALDELTA_POS	10

/* PID parameters*/
// PITCH
#define PITCH_P	0
#define PITCH_I	0
#define PITCH_D	0
// ROLL
#define ROLL_P	0
#define ROLL_I	0
#define ROLL_D	0
// YAW
#define YAW_P	0.25
#define YAW_I	0
#define YAW_D	0

#define DELTALIMIT 		30

#define PITCH_WINDUP	300
#define ROLL_WINDUP 	300
#define YAW_WINDUP 		300

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
	CALIBRATION_MODE_ON,
	CALIBRATION_MODE_OFF,
	NA
} cmdTypeDef;

typedef struct{
	uint16_t pitchPos;
	uint16_t rollPos;
	uint16_t yawPos;
}motorPosTypeDef;

/* Private variables -------------------------------------------*/
motorPosTypeDef motorPos = { .pitchPos = CENTER_POS, .rollPos = CENTER_POS, .yawPos = CENTER_POS};
bool pwmEn;
bool trackingEn;
bool calibrationEn;

static int xSum = 0, ySum = 0, rotationSum = 0;
static int xLast = 0, yLast = 0, rotationLast = 0;

/* Private functions -------------------------------------------*/
cmdTypeDef decodeCmd(char const * cmdString, int length);
void enablePWM();
void disablePWM();
__STATIC_INLINE void NormalizeRange(int value, int MaxRange, int MinRange);
__STATIC_INLINE void RemoveNoise(int * x, int *y, int * rotation);

/**
 * @brief Setting up all the peripherals (UART and TIMER) needed
 * to control the gimbal position
 */
void gimbalControlInit(void){
	// Configure UART2 interrupt to receive data from PC
	configure_IRQ_USART_RX();

	// Flag to know PWM signal state
	pwmEn = false;

	// Flag to know if tracking function is enable/disable
	trackingEn = false;

	// Calibration not active
	calibrationEn = false;
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

	if(strncmp(cmdString, "CALON\n", length) == 0){
		calibrationEn = true;
		return CALIBRATION_MODE_ON;
	}

	if(strncmp(cmdString, "CALOFF\n", length) == 0){
		calibrationEn = false;
		return CALIBRATION_MODE_OFF;
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

		if(!calibrationEn) motorPos.pitchPos -= DELTA_POS;
		else motorPos.pitchPos -= CALDELTA_POS;

		NormalizeRange(motorPos.pitchPos, MAX_POS, MIN_POS);
		TIM3->CCR2 = motorPos.pitchPos;
		return UP;
	}
	// Down command
	if(strncmp(cmdString, "DW\n", length) == 0){

		if(!calibrationEn) motorPos.pitchPos += DELTA_POS;
		else	motorPos.pitchPos += CALDELTA_POS;

		NormalizeRange(motorPos.pitchPos, MAX_POS, MIN_POS);
		TIM3->CCR2 = motorPos.pitchPos;
		return DOWN;
	}
	// Left command
	if(strncmp(cmdString, "LF\n", length) == 0){

		if(!calibrationEn) motorPos.yawPos -= DELTA_POS;
		else motorPos.yawPos -= CALDELTA_POS;

		NormalizeRange(motorPos.yawPos, MAX_POS, MIN_POS);
		TIM3->CCR4 = motorPos.yawPos;
		return LEFT;
	}
	// Right command
	if(strncmp(cmdString, "RH\n", length) == 0){

		if(!calibrationEn) motorPos.yawPos += DELTA_POS;
		else motorPos.yawPos += CALDELTA_POS;

		NormalizeRange(motorPos.yawPos, MAX_POS, MIN_POS);
		TIM3->CCR4 = motorPos.yawPos;
		return RIGHT;
	}

	// Rotate left command
	if(strncmp(cmdString, "RLF\n", length) == 0){

		if(!calibrationEn) motorPos.rollPos += DELTA_POS;
		else motorPos.rollPos += CALDELTA_POS;

		NormalizeRange(motorPos.rollPos, MAX_POS, MIN_POS);
		TIM3->CCR1 = motorPos.rollPos;
		return ROTATE_LEFT;
	}
	// Rotate right command
	if(strncmp(cmdString, "RRH\n", length) == 0){

		if(!calibrationEn) motorPos.rollPos -= DELTA_POS;
		else motorPos.rollPos -= CALDELTA_POS;

		NormalizeRange(motorPos.rollPos, MAX_POS, MIN_POS);
		TIM3->CCR1 = motorPos.rollPos;
		return ROTATE_RIGHT;
	}
	return NA;
}

/**
 * \brief Implements the control law from the optical flow received as
 * arguments
 * @param x	Optical flow value in horizontal direction
 * @param y Optical flow value in vertical direction
 * @param rotation	Optical flow value which indicates the rotation
 */
void applyControlLaw(frameStruct * frame, ControlLawModeTypeDef mode){
	int x, y, rotation;
	int deltaPitch, deltaRoll, deltaYaw;

	if(!trackingEn) return;

	// Integrate values
	switch(mode){
	case LEFT_ONLY:
		x = frame->oFLeft.x;
		y = frame->oFLeft.y;
		rotation = 0;
		break;
	case RIGHT_ONLY:
		x = frame->oFRight.x;
		y = frame->oFRight.y;
		rotation = 0;
		break;
	case ALL:
		x = frame->oFFused.x;
		y = frame->oFFused.y;
		rotation = frame->oFFused.theta;
		break;
	}

	RemoveNoise(&x, &y, &rotation);

	xSum += x;
	ySum += y;
	rotationSum += rotation;

	// Integral windup
	if(abs(ySum) > PITCH_WINDUP) ySum = 0;
	if(abs(rotationSum) > ROLL_WINDUP) rotationSum = 0;
	if(abs(xSum) > YAW_WINDUP) xSum = 0;

	// PID implementation
	deltaYaw = (float)(x * YAW_P) + (float)(xSum * YAW_I) + (float)((x - xLast) * YAW_D);
	deltaPitch = y * PITCH_P + ySum * PITCH_I + (y - yLast) * PITCH_D;
	deltaRoll = rotation * ROLL_P + rotationSum *  ROLL_I +
			(rotation - rotationLast) * ROLL_D;

	// Avoid small changes in computed values
//	if(abs(deltaYaw)>=DELTALIMIT) motorPos.yawPos +=deltaYaw;
//	if(abs(deltaPitch)>=DELTALIMIT) motorPos.pitchPos +=deltaPitch;
//	if(abs(deltaRoll)>=DELTALIMIT) motorPos.rollPos +=deltaRoll;
	motorPos.yawPos +=deltaYaw;
	motorPos.pitchPos +=deltaPitch;
	motorPos.rollPos +=deltaRoll;

	// Check the signals are in the proper range
	NormalizeRange(motorPos.pitchPos, MAX_POS, MIN_POS);
	NormalizeRange(motorPos.rollPos, MAX_POS, MIN_POS);
	NormalizeRange(motorPos.yawPos, MAX_POS, MIN_POS);

	// RC control signals generation
	TIM3->CCR1 = motorPos.rollPos;
	TIM3->CCR2 = motorPos.pitchPos;
	TIM3->CCR4 = motorPos.yawPos;

	// Save values to differentiation
	xLast = x;
	yLast = y;
	rotationLast = rotation;
}

/**
 * @brief	Check if tracking function is enable/disable
 * @return	True if the tracking function is enable, False if it is disable
 */
bool IsTrackingEnable(){
	return trackingEn;
}

/**
 * @brief	Enable RC (PWM) signal generation
 */
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

/**
 * @brief	Disable RC (PWM) signal generation
 */
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

/**
 * @brief	Avoid out of range values in RC signals
 * @param value	Current value of signal
 * @param MaxRange	Maximum value for signal
 * @param MinRange	Minimum value for signal
 */
void NormalizeRange(int value, int MaxRange, int MinRange){
	if(value > MaxRange){
		value = MaxRange;
	}
	else if(value < MinRange){
		value = MinRange;
	}
}

/**
 * Remove signal noise in OF signal
 * @param y
 * @param y
 * @param rotation
 */
void RemoveNoise(int * x, int *y, int * rotation){
	if(abs(*x)<=DELTALIMIT) *x=0;
	if(abs(*y)<=DELTALIMIT) *y=0;
	if(abs(*rotation)<=DELTALIMIT) *rotation=0;
}

void USART2_IRQHandler(void){
	static char bufferIn[BUFFER_SIZE];
	static int i = 0;

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
