/*
 * eyes.c
 *
 *  Created on: 18 sept. 2020
 *      Author: deros
 */

/* Private includes ----------------------------------------------------------*/
#include "eyes.h"

/* Private macro -------------------------------------------------------------*/
#define SWITCH_FRAME_IDX(current, past)	{uint8_t temp; temp = past; past = current; current = temp;}

/* Private typedefs --------------------------------------------*/
typedef enum adns2610_state{
	SENSOR_RESET,
	TRIGGER_FRAME,
	READING_FRAME,
	REQ_READING_FRAME,
	PROCESSING
} eyes_FSMstate_TypeDef;

/* Private variables -------------------------------------------*/
static eyes_FSMstate_TypeDef FSMstate;
bool initialized = false;

/* Private functions -------------------------------------------*/
void eyes_configureFSM_TIM(void);
void eyes_FSM(void);
__STATIC_INLINE void eyes_waitIT(uint32_t Count250ns);
__STATIC_INLINE void eyes_stopWaitIT();
bool eyes_computeIdxFromStatus(PixelStatus* status1, PixelStatus* status2, uint16_t* idx1,  uint16_t* idx2);

/* Exported variables -------------------------------------------*/
frameStruct frames[2] = {{.header = FRAME_HEADER}, {.header = FRAME_HEADER}};

/** @brief Initialize the
 *
 */
void eyes_init(){
	// Configure the timer to read the frames continuously
	eyes_configureFSM_TIM();

	// Initialize ADNS2610 sensor
	adns2610_init(ADNS2610_RIGHT);
#if SECOND_SENSOR_IMPLEMENTED
	adns2610_init(ADNS2610_LEFT);
#endif

	// Configure DMA to transfer the frameStruct through DMA
	configureDMA_USART_TX(USART2, BYTE, MEDIUM);

	// Giving initial values to variables
	currentFrameIdx = 0;
	lastFrameIdx = 1;

	// Initialization done
	initialized = true;
}

void eyes_start(){

	if(!initialized) eyes_init();

	SET_BIT(TIM1->CR1, TIM_CR1_CEN);
	FSMstate = TRIGGER_FRAME;
}

void eyes_stop(){
	FSMstate = RESET;
}

/* eye FSM states operation ----------------------------------------------------
 * 	-SENSOR_RESET:		The FSM stops. When it is restarted all is reseted.
 *
 * 	-TRIGGER_FRAME:		The frame is taken. It's performed by a write operation
 *   					to PIXEL DATA register.
 *
 *	-REQ_READING_FRAME:	The PIXEL DATA register address is sent. After that it's
 *						needed to wait 100us to get the pixel data. This time is
 *						used to check the last pixel received.
 *
 *	-READING_FRAME:		The pixel data is received and stored after the wait of
 *						100us.
 * ------------------------------------------------------------------------------ */
/** @brief Compute the FSM (Finite State Machine) for control loop
 *
 */
void eyes_FSM(void){
	static uint16_t pixelIdx[2] = { 0 };
	static PixelStatus pixelStatus [2] = { 0 };
	static bool firstPixelRead = true;
	static bool firstFrameRead = true;

	static uint8_t collisionFlag = 0;
	static uint16_t errorCounter = 0;
	static uint8_t seqTemp;

	switch(FSMstate){
	/* SENSOR_RESET state --------------------------------------------------------- */
	case SENSOR_RESET:
//		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		pixelIdx[ADNS2610_RIGHT] = 0;
#if SECOND_SENSOR_IMPLEMENTED
		pixelIdx[ADNS2610_RIGHT] = 0;
#endif
		/* Stop the interrupt timer and reset all the relevant values */
		eyes_stopWaitIT();
		pixelIdx[0] = pixelIdx[1] = 0;
		pixelStatus[0] = pixelIdx[1] = 0;
		firstPixelRead = true;
		firstFrameRead = true;
		seqTemp = 0;
		initialized = false;
		collisionFlag = 0;
		return;
	/* TRIGGER_FRAME state --------------------------------------------------------- */
	case TRIGGER_FRAME:
		eyes_stopWaitIT();
		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		/* Write pixel data register to reset the HW */
		adns2610_writeRegister(ADNS2610_RIGHT, ADNS2610_PIXEL_DATA_REG, 0x01);
#if SECOND_SENSOR_IMPLEMENTED
		adns2610_writeRegister(ADNS2610_LEFT, ADNS2610_PIXEL_DATA_REG, 0x01);
#endif
		/* While it waits the needed delay it's performed some tasks:
		 * 	- Increasing the SEQ number
		 * 	- Transfer all data by means of DMA
		 * 	*/
		eyes_waitIT(ADNS2610_TIM_BTW_WR);
		firstPixelRead = true;
		FSMstate = REQ_READING_FRAME;
		pixelIdx[ADNS2610_RIGHT] = 0;
#if SECOND_SENSOR_IMPLEMENTED
		pixelIdx[ADNS2610_LEFT] = 0;
#endif
		if(!firstFrameRead){
			frames[lastFrameIdx].seq = (seqTemp++) & 0x7F;
			transferDMA_USART2_TX((uint32_t) &(frames[lastFrameIdx].header), FRAME_STUCT_LENGTH);
			OF_ResetCoefficients();
		}
		collisionFlag = 0;
		errorCounter = 0;
		return;
	/* REQ_READING_FRAME state --------------------------------------------------------- */
	case REQ_READING_FRAME:
		eyes_stopWaitIT();
		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		/* Send a pixel data read request */
		adns2610_sendByte(ADNS2610_RIGHT, ADNS2610_PIXEL_DATA_REG);
#if SECOND_SENSOR_IMPLEMENTED
		adns2610_sendByte(ADNS2610_LEFT, ADNS2610_PIXEL_DATA_REG);
#endif
		/* While it waits the needed delay it's performed some tasks:
		 * 	- Check the last received pixel status and take decision related to it
		 * 	- Compute OF coefficients when it was possible
		 * 	*/
		eyes_waitIT(ADNS2610_TIM_TO_RD);
		if(!firstPixelRead){
			pixelStatus[ADNS2610_RIGHT] = adns2610_checkPixel(&frames[currentFrameIdx].frame[ADNS2610_RIGHT][pixelIdx[ADNS2610_RIGHT]]);
	#if SECOND_SENSOR_IMPLEMENTED
			pixelStatus[ADNS2610_LEFT] = adns2610_checkPixel(&frames[currentFrameIdx].frame[ADNS2610_LEFT][pixelIdx[ADNS2610_LEFT]]);
	#endif
			if(eyes_computeIdxFromStatus(&pixelStatus[ADNS2610_RIGHT], &pixelStatus[ADNS2610_LEFT], &pixelIdx[ADNS2610_RIGHT], &pixelIdx[ADNS2610_LEFT])){
				FSMstate = READING_FRAME;
				if((pixelStatus[ADNS2610_RIGHT] == NON_VALID) || (pixelStatus[ADNS2610_RIGHT] == NON_VALID_SOF)){
					errorCounter++;
				}
				if(!firstFrameRead){
					OF_ComputeCoefficients(ADNS2610_RIGHT, frames[currentFrameIdx].frame[ADNS2610_RIGHT], frames[lastFrameIdx].frame[ADNS2610_RIGHT], pixelIdx[ADNS2610_RIGHT]);
#if SECOND_SENSOR_IMPLEMENTED
					OF_ComputeCoefficients(ADNS2610_LEFT, frames[currentFrameIdx].frame[ADNS2610_RIGHT], frames[lastFrameIdx].frame[ADNS2610_RIGHT], pixelIdx[ADNS2610_RIGHT]);
#endif
				}
			}
			else{
				eyes_stopWaitIT();
				FSMstate = TRIGGER_FRAME;
				eyes_waitIT(ADNS2610_TIM_BTW_WR);
			}
		}
		else{
			firstPixelRead = false;
			FSMstate = READING_FRAME;
		}
		collisionFlag = 0;
		return;
	/* READING_FRAME state ---------------------------------------------------------------- */
	case READING_FRAME:
		eyes_stopWaitIT();
		if(collisionFlag) goto collisionError; else collisionFlag = 1;
		/* Read pixel data register */
		adns2610_receiveByte(ADNS2610_RIGHT, &frames[currentFrameIdx].frame[ADNS2610_RIGHT][pixelIdx[ADNS2610_RIGHT]]);
		/* Check the last pixel status. This is done because if all is good, the next state is PROCESSING, not REQ_READING_FRAME state */
#if SECOND_SENSOR_IMPLEMENTED
		adns2610_receiveByte(ADNS2610_LEFT, &frames[currentFrameIdx].frame[ADNS2610_LEFT][pixelIdx[ADNS2610_LEFT]]);

		if((pixelIdx[ADNS2610_RIGHT] == PIXEL_QTY-1) && pixelIdx[ADNS2610_LEFT] == PIXEL_QTY-1){
			if(eyes_computeIdxFromStatus(&pixelStatus[ADNS2610_RIGHT], &pixelStatus[ADNS2610_LEFT], &pixelIdx[ADNS2610_RIGHT], &pixelIdx[ADNS2610_LEFT])){
				FSMstate = PROCESSING;
			}
		}
		else{
			FSMstate = REQ_READING_FRAME;
		}
#else
		if(pixelIdx[ADNS2610_RIGHT] == PIXEL_QTY-1){
			if(eyes_computeIdxFromStatus(&pixelStatus[ADNS2610_RIGHT], &pixelStatus[ADNS2610_LEFT], &pixelIdx[ADNS2610_RIGHT], &pixelIdx[ADNS2610_LEFT])){
				FSMstate = PROCESSING;
			}
		}
		else{
			// It only waits for the next state when it is REQ_READING_FRAME. If not, it continues directly to PROCESSING state.
			FSMstate = REQ_READING_FRAME;
			eyes_waitIT(ADNS2610_TIM_BTW_RD);
			collisionFlag = 0;
			return;
		}
#endif
		collisionFlag = 0;
	/* PROCESSING state ---------------------------------------------------------------- */
	case PROCESSING:
		/* Check if it's the first frame read */
		if(firstFrameRead){
			firstFrameRead = false;
		}
		else{
			/* Compute the Optical Flow from the previous computed coefficients */
			OF_Compute(ADNS2610_RIGHT, &(frames[currentFrameIdx].oFRight.x), &(frames[currentFrameIdx].oFRight.y));
#if SECOND_SENSOR_IMPLEMENTED
			OF_Compute(ADNS2610_LEFT, &(frames[currentFrameIdx].oFRight.x), &(frames[currentFrameIdx].oFRight.y));
#endif
		}
		/* Switch the frame structures to store the new frame in the "oldest" data buffer */
		SWITCH_FRAME_IDX(currentFrameIdx, lastFrameIdx);
		FSMstate = TRIGGER_FRAME;
		eyes_waitIT(ADNS2610_TIM_BTW_RD);
		return;
	}

	// Check for collisions between interrupts callings
	collisionError:
		printf("COLISSION ERROR!!\r\n");
		eyes_stopWaitIT();
		while(1);
}

void eyes_configureFSM_TIM(void){
	// TIM1 prescalers has been configured to count microseconds
	uint32_t temp = TIM1->CR1;

	// Disable update interrupt
	CLEAR_BIT(TIM1->DIER, TIM_DIER_UIE);
	// Modify CR1 register
	MODIFY_REG(temp, ~(TIM_CR1_UDIS), TIM_CR1_URS);
	TIM1->CR1 = temp;
	// Set interrupt interval
	TIM1->ARR = ADNS2610_TIM_TO_RD;
	// Update the prescaler and counter registers
	SET_BIT(TIM1->EGR, TIM_EGR_UG);
	// Clear pending interrupt flag
	CLEAR_BIT(TIM1->SR, TIM_SR_UIF);
	// Enable update interrupt generation
	CLEAR_BIT(TIM1->CR1, TIM_CR1_URS);
	// Enable update interrupt
	SET_BIT(TIM1->DIER, TIM_DIER_UIE);
	// Configure NVIC to handle TIM1 update interrupt
	NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0);
	NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
}

void eyes_waitIT(uint32_t Count250ns){
	// Disable update interrupt generation
	SET_BIT(TIM1->CR1, TIM_CR1_URS);
	// Set time to wait
	TIM1->ARR = Count250ns;
	// Update the prescaler and counter registers
	SET_BIT(TIM1->EGR, TIM_EGR_UG);
	// Enable update interrupt generation
	CLEAR_BIT(TIM1->CR1, TIM_CR1_URS);
	// Enable and start timer
	SET_BIT(TIM1->CR1, TIM_CR1_CEN);
}

void eyes_stopWaitIT(){
	// Disable and start timer
	CLEAR_BIT(TIM1->CR1, TIM_CR1_CEN);
}

bool eyes_computeIdxFromStatus(PixelStatus* status1, PixelStatus* status2, uint16_t* idx1,  uint16_t* idx2){

	if((*status1 == VALID_SOF) && (*idx1 == 0)){
		(*idx1)++;
	}
	else if((*status1 == VALID) && (*idx1 != 0) && (*idx1 < PIXEL_QTY-1)){
		(*idx1)++;
	}
	else if ((*status1 == VALID_SOF) && (*idx1 != 0)){
		*idx1 = *idx2 = 0;
		return false;
	}
#if SECOND_SENSOR_IMPLEMENTED
	if((*status2 == VALID_SOF) && (*idx2 == 0)){
		(*idx2)++;
	}
	else if((*status2 == VALID) && (*idx2 != 0) && (*idx2 < PIXEL_QTY-1)){
		(*idx2)++;
	}
	else if((*status2 == VALID_SOF) && (*idx2 != 0)){
		(*idx1) = (*idx2) = 0;
		return false;
	}
#endif
	return true;
}

void TIM1_UP_TIM16_IRQHandler(void){
	// If the interrupt flag is enabled
	if(READ_BIT(TIM1->SR, TIM_SR_UIF)){
		// Clear pending interrupt flag
		CLEAR_BIT(TIM1->SR, TIM_SR_UIF);
		// Process FSM
		eyes_FSM();
	}
}
