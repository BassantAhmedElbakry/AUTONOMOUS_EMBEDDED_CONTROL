/*************************************************************************************************************
 * Module : PWM
 *
 * File name : pwm.h
 *
 * Description: Source file for the AVR PWM driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#include<avr/io.h>
#include"pwm.h"
#include"gpio.h"

/*************************************************************************************************************
 *                                         Functions Definitions                                             *
*************************************************************************************************************/

void PWM_Timer0_Start(uint8 speed){

	TCNT0 = 0; /*Set Timer Initial value*/

	OCR0  = speed*255.0 / 100; /*Set Compare Value*/

	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	GPIO_setupPinDirection(PORT_B, PIN_3, OUTPUT_PIN);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/64 CS00=1 CS01=1 CS02=0
	 */

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00) | (1<<CS01) ;


}
