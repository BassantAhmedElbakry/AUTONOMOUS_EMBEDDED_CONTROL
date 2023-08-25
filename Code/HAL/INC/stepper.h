/*************************************************************************************************************
 * Module : Stepper MOTOR
 *
 * File name : stepper.h
 *
 * Description: Header file for the AVR Stepper Motor driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#ifndef STEPPER_H_
#define STEPPER_H_

#include "std_types.h"
#include<avr/io.h>

/************************************************************************************************************
 *                                           Definitions                                                    *
 ***********************************************************************************************************/
#define FULL_WAVE_STEPS 4

#define IN_PORT    PORT_A
#define PORT       PORTA

#define IN1_PIN    PIN_0
#define IN2_PIN    PIN_1
#define IN3_PIN    PIN_2
#define IN4_PIN    PIN_3

typedef enum{
	Right,
	Left
}StepperMotor_Direction;

/************************************************************************************************************
 *                                        Functions Prototypes                                              *
 ***********************************************************************************************************/

/*
 * Description:
 * The Function responsible for setup the direction for the 4
 * motor pins through the GPIO driver.
 */
void StepperMotor_init(void);

/*
 * Description:
 * The function responsible for rotate the Stepper Motor R or L
 * based on the state input state value.
 */
void StepperMotor_Rotate(StepperMotor_Direction direction, uint8 angle);


#endif /* STEPPER_H_ */
