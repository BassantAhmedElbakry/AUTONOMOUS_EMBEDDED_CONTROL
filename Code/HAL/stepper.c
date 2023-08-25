/*************************************************************************************************************
 * Module : Stepper MOTOR
 *
 * File name : stepper.c
 *
 * Description: Header file for the AVR Stepper Motor driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/
#include<avr/io.h>
#include <util/delay.h>
#include"common_macros.h"
#include"gpio.h"
#include"stepper.h"

/*****************************************************************************************************
 *                                          Local Variables                                          *
 *****************************************************************************************************/

unsigned char motor_steps_R[FULL_WAVE_STEPS] = {12,6,3,9};
unsigned char motor_steps_L[FULL_WAVE_STEPS] = {9,3,6,12};

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
**********************************************************************************************************/

/*
 * Description:
 * The Function responsible for setup the direction for the 4
 * motor pins through the GPIO driver.
 */
void StepperMotor_init(void){

	 // Set the stepper motor pins as output
	GPIO_setupPinDirection(IN_PORT, IN1_PIN, OUTPUT_PIN);
	GPIO_setupPinDirection(IN_PORT, IN2_PIN, OUTPUT_PIN);
	GPIO_setupPinDirection(IN_PORT, IN3_PIN, OUTPUT_PIN);
	GPIO_setupPinDirection(IN_PORT, IN4_PIN, OUTPUT_PIN);

	// Set the initial state of the stepper motor
	GPIO_writePin(IN_PORT, IN1_PIN,LOW);
	GPIO_writePin(IN_PORT, IN2_PIN,LOW);
	GPIO_writePin(IN_PORT, IN3_PIN,LOW);
	GPIO_writePin(IN_PORT, IN4_PIN,LOW);
}

/*
 * Description:
 * The function responsible for rotate the Stepper Motor R or L
 * based on the state input state value.
 */
void StepperMotor_Rotate(StepperMotor_Direction direction, uint8 angle){

	uint8 counter = 0;

	for(uint8 i = 0 ; i < angle ; i++){

		if(direction == Right){
			PORT = (motor_steps_R[counter] & 0x0F) | (PORT & 0xF0);
			_delay_ms(30);
			counter++;
			if(counter == FULL_WAVE_STEPS){
				// Start from beginning
				counter = 0;
			}
		}

		else if (direction == Left){
			PORT = (motor_steps_L[counter] & 0x0F) | (PORT & 0xF0);
			_delay_ms(30);
			counter++;
			if(counter == FULL_WAVE_STEPS){
				// Start from beginning
				counter = 0;
			}
		}
	}

}


