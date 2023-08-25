/*************************************************************************************************************
 * Module : DC MOTOR
 *
 * File name : dc.h
 *
 * Description: Header file for the AVR DC Motor driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#ifndef DC_H_
#define DC_H_

/************************************************************************************************************
 *                                           Definitions                                                    *
 ***********************************************************************************************************/

#define IN1_PORT   PORT_C
#define IN2_PORT   PORT_C

#define IN1_PIN    PIN_0
#define IN2_PIN    PIN_1

typedef enum{
	Stop,
	Clockwise,
	Anti_clockwise
}DcMotor_State;

/************************************************************************************************************
 *                                        Functions Prototypes                                              *
 ***********************************************************************************************************/

/*
 * Description:
 * The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver
 */
void DcMotor_init(void);

/*
 * Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
 * required speed value
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_H_ */
