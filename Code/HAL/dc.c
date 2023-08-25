/*************************************************************************************************************
 * Module : DC MOTOR
 *
 * File name : dc.c
 *
 * Description: Source file for the AVR DC Motor driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#include"common_macros.h"
#include"gpio.h"
#include"dc.h"
#include"pwm.h"

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
**********************************************************************************************************/

/*
 * Description:
 * The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver
 */
void DcMotor_init(void){

	GPIO_setupPinDirection(IN1_PORT, IN1_PIN, OUTPUT_PIN);
	GPIO_setupPinDirection(IN2_PORT, IN2_PIN, OUTPUT_PIN);

	/*Stop at first*/
	GPIO_writePin(IN1_PORT, IN1_PIN, LOW);
	GPIO_writePin(IN2_PORT, IN2_PIN, LOW);

}

/*
 * Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
 * required speed value
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed){

	PWM_Timer0_Start(speed);

	if(state == Stop){
		GPIO_writePin(IN1_PORT, IN1_PIN, LOW);
		GPIO_writePin(IN2_PORT, IN2_PIN, LOW);
	}
	else if(state == Clockwise){
		GPIO_writePin(IN1_PORT, IN1_PIN, LOW);
		GPIO_writePin(IN2_PORT, IN2_PIN, HIGH);
	}
	else if(state == Anti_clockwise){
		GPIO_writePin(IN1_PORT, IN1_PIN, HIGH);
		GPIO_writePin(IN2_PORT, IN2_PIN, LOW);
	}

}
