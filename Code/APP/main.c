/************************************************************************************************************
 *
 * Module: Autonomous Car
 *
 * File name : main.c
 *
 *  Created on: ٢٣‏/٠٨‏/٢٠٢٣
 *
 *  Author: BASSANT AHMED
 *
 ***********************************************************************************************************/

#include<avr/io.h>
#include<avr/interrupt.h>
#include"common_macros.h"
#include"std_types.h"
#include"dc.h"
#include"stepper.h"
#include"lcd.h"
#include"uart.h"

/**********************************************************************************************************
 *                                               Globals                                                  *
 *********************************************************************************************************/

//Global variable to store the frame
uint8 frame[8];
//Variables For Timer
uint32 tick = 0;
uint8 second = 0;
uint8 minute = 0;
uint8 hour   = 0;

/*********************************************************************************************************
 *                                             Configurations                                            *
 *********************************************************************************************************/
/*
 * Configuration of UART:
 * Baud Rate = 9600
 * Asynchronous
 * Number of data bits = 8-bits
 * Number of stop bits = 1-bit
 * Parity is Disabled
 */
UART_ConfigType UART_Config  = {9600,Asynchronous,BITS_8,BIT_1,Disabled};

/**********************************************************************************************************
 *                                        Functions Prototypes                                            *
 *********************************************************************************************************/
/*
 * Description :
 * Function to receive the Frame
 */
uint8 receiveFrame(void);

/*
 * Description :
 * Function to Initial Timer2
 */
void Timer2_init(void);

int main(){
	/*****************************************************************************************************
	 *                                          Local Variables                                          *
	 *****************************************************************************************************/

	// Flag to check that frame is correct in general
	uint8 flag = 0;
	// Counter to check that each bit of frame is correct
	uint8 counter = 0;
	// Variable to store Stepper Direction
	char Direction_Stepper;
	// Variable to store Stepper Angle
	uint8 Angle_Stepper;
	// Variable to store DC Direction --> cw or Acw
	char Direction_DC;
	// Variable to store DC speed
	uint8 Speed_DC = 0;
	// Variable to know the sign of Wheels Direction
	uint8 sign;

	/*******************************************************************************************************
	 *                                          Initializations                                            *
	 ******************************************************************************************************/

	/*Enable the global interrupt*/
	SET_BIT(SREG,7);

	/*Initialize LCD*/
	LCD_init();

	/*Initialize DC Motor*/
	DcMotor_init();

	/*Initialize UART*/
	UART_init(&UART_Config);

	/*Initialize Stepper Motor*/
	StepperMotor_init();

	/*Initialize Timer*/
	Timer2_init();

	/*******************************************************************************************************
	 *                                            My System                                                *
	 *******************************************************************************************************/

	while(1){

		do{
			// Counter to check that each bit of frame is correct
			counter = 0;

			// Flag to check that frame is correct in general
			flag = 0;

			// Receive the Frame and check that is 8 bits end with E or e
			flag = receiveFrame();

			/* Check the frame:
			 * First 3-bits  --> Speed of DC Motor [0 --> 100]
			 * Bit_4         --> Direction of DC Motor [F or f or B or b]
			 * Bit_5 & Bit_6 --> Angle of Stepper Motor [0 --> 45]
			 * Bit_7         --> Direction of Stepper Motor [R or r or L or l]
			 * Bit_8         --> End of frame [E or e]
			 */
			if(flag)
			{
				// Check bit_0 of frame (MSB) --> Must be 1 or 0
				if (frame[0] == '1' || frame[0] == '0'){
					counter++;
				}
				else{
					counter = 0;
				}
				// Check bit_1 of frame --> Must be [0 --> 9]
				if (frame[1] >= '0' && frame[1] <= '9'){
					counter++;
				}
				else {
					counter = 0;
				}
				// Check bit_2 of frame --> Must be [0 --> 9]
				if (frame[2] >= '0' && frame[2] <= '9'){
					counter++;
				}
				else{
					counter = 0;
				}
				// Check bit_3 of frame --> Must be [F or f or B or b]
				if (frame[3] == 'f' || frame[3] == 'F' || frame[3] == 'b' || frame[3] == 'B'){
					counter++;
				}
				else{
					counter = 0;
				}
				// Check bit_4 of frame --> Must be [0 --> 4]
				if (frame[4] >= '0' && frame[4] <= '4'){
					counter++;
				}
				else{
					counter = 0;
				}
				// Check bit_5 of frame --> Must be [0 --> 5]
				if (frame[5] >= '0' || frame[5] <= '5'){
					counter++;
				}
				else{
					counter = 0;
				}
				// Check bit_6 of frame --> Must be [L or l or R or r]
				if (frame[6] == 'l' || frame[6] == 'L' || frame[6] == 'R' || frame[6] == 'r'){
					counter++;
				}
				else{
					counter = 0;
				}
			}

		 // Wait for receiving another frame if the previous one is wrong
		} while(counter < 7);

		// Store the DC Speed
		Speed_DC = (frame[0]-'0')*100 + (frame[1]-'0')*10 + (frame[2]-'0');

		// Store DC Direction
		Direction_DC = frame[3];

		// Control the DC Motor ( Speed and Direction )
		if(Direction_DC == 'F' || Direction_DC == 'f'){
			DcMotor_Rotate(Clockwise,Speed_DC);
		}
		else{
			DcMotor_Rotate(Anti_clockwise,Speed_DC);
		}

		// Store the Stepper Angle
		Angle_Stepper = (frame[4]-'0')*10 + frame[5]-'0';

		// Store Stepper Direction
		Direction_Stepper = frame[6];

		// Control the Stepper Motor ( Angle and Direction )
		if(Direction_Stepper == 'R' || Direction_Stepper == 'r'){
			sign = 1;
			StepperMotor_Rotate(Right,Angle_Stepper);
		}
		else{
			sign = 0;
			StepperMotor_Rotate(Left,Angle_Stepper);
		}

		/************************************************* Dash Board *************************************************/

		// Clear the screen to update the new values
		LCD_clearScreen();

		//Display the speed of DC motor
		LCD_displayStringRowColumn(0,0,"Speed: ");
		LCD_moveCursor(0,7);
		LCD_sendNumbers(Speed_DC);
		LCD_moveCursor(0,10);
		LCD_displayCharacter('%');

		// Display the direction of Stepper motor
		LCD_displayStringRowColumn(0,12,"Direction: ");
		LCD_moveCursor(0,23);

		/*Determine the sign of the angle
		 * IF Right --> +ve sign
		 * IF Left  --> -ve sign
		 */
		if(sign){
			LCD_sendNumbers(Angle_Stepper);
		}
		else{
			LCD_sendNumbers(-Angle_Stepper);
		}

	}
	return 0;


}

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
 *********************************************************************************************************/
/*
 * Description :
 * Function to receive the Frame
 */
uint8 receiveFrame(void){

	uint8 Num_of_Bits = 0;

	// Check that frame is 8 bits ending with E or e
	do{
		Num_of_Bits = UART_receiveString(frame);
	} while(Num_of_Bits != 7);

	return 1;
}

/*
 * Description :
 * Function to Initial Timer2
 */
void Timer2_init(void){
	/* Configure timer control register TCCR2
	 * 1. Non PWM mode FOC2 = 1
	 * 2. CTC Mode WGM21 = 1 & WGM20 = 0
	 * 3. clock = F_CPU/256 CS20=0 CS21=1 CS22=1
	 */
	TCCR2 = (1 << FOC2) | (1 << WGM21) | (1 << CS21) | (1 << CS22);
	/* Set timer2 initial count to zero */
	TCNT2 = 0;
	/* Set the Compare value to 250*/
	OCR2 = 250;
	/* Enable Timer2 Interrupt */
	TIMSK |= (1 << OCIE2);
}

/**********************************************************************************************************
 *                                                      ISR                                               *
 *********************************************************************************************************/

ISR(TIMER2_COMP_vect){

	// Variable to count one second
	tick++;

	// After 125 count we reach to one second at Freq = 8M Hz and Pre_scaler = 256 and compare value = 250
	if(tick == 125){

		second++;

		// Start count again
		tick = 0;

		// At seconds = 60 ,now we have one minute
		if (second == 60){
			minute++;
			second = 0;
		}
		// At minutes = 60 ,now we have one hour
		if (minute == 60){
			hour++;
			minute = 0;
		}

		// Display the time
		LCD_displayStringRowColumn(1,0,"Time: ");
		LCD_moveCursor(1,6);
		LCD_displayCharacter((hour/10 + '0'));
		LCD_displayCharacter((hour%10 + '0'));
		LCD_displayCharacter(':');
		LCD_displayCharacter((minute/10 + '0'));
		LCD_displayCharacter((minute%10 + '0'));
		LCD_displayCharacter(':');
		LCD_displayCharacter((second/10 + '0'));
		LCD_displayCharacter((second%10 + '0'));

		// After 12 hours time will be PM
		if (hour >= 12){
			LCD_displayString(" PM");
		}

		else{
			LCD_displayString(" AM");
		}

	}
}


