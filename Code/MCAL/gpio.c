/**********************************************************************************************************
 * Module: GPIO
 *
 * File name : gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: BASSANT AHMED
 *********************************************************************************************************/
#include "gpio.h"
#include "common_macros.h"
#include "avr/io.h"

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
 *********************************************************************************************************/


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(Port port_num, Pins pin_num , GPIO_PinDirection direction){

	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORT_A:
			if(direction == OUTPUT_PIN)
				SET_BIT(DDRA,pin_num);
			else
				CLEAR_BIT(DDRA,pin_num);
			break;
		case PORT_B:
			if(direction == OUTPUT_PIN)
				SET_BIT(DDRB,pin_num);
			else
				CLEAR_BIT(DDRB,pin_num);
			break;
		case PORT_C:
			if(direction == OUTPUT_PIN)
				SET_BIT(DDRC,pin_num);
			else
				CLEAR_BIT(DDRC,pin_num);
			break;
		case PORT_D:
			if(direction == OUTPUT_PIN)
				SET_BIT(DDRD,pin_num);
			else
				CLEAR_BIT(DDRD,pin_num);
			break;
		}

	}

}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(Port port_num,GPIO_PortDirection direction){

	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORT_A:
			DDRA = direction;
			break;
		case PORT_B:
			DDRB = direction;
			break;
		case PORT_C:
			DDRC = direction;
			break;
		case PORT_D:
			DDRD = direction;
			break;
		}
	}

}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(Port port_num, Pins pin_num , Logic value){

	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORT_A:
			if(value == HIGH)
				SET_BIT(PORTA,pin_num);
			else
				CLEAR_BIT(PORTA,pin_num);
			break;
		case PORT_B:
			if(value == HIGH)
				SET_BIT(PORTB,pin_num);
			else
				CLEAR_BIT(PORTB,pin_num);
			break;
		case PORT_C:
			if(value == HIGH)
				SET_BIT(PORTC,pin_num);
			else
				CLEAR_BIT(PORTC,pin_num);
			break;
		case PORT_D:
			if(value == HIGH)
				SET_BIT(PORTD,pin_num);
			else
				CLEAR_BIT(PORTD,pin_num);
			break;
		}

	}

}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(Port port_num, uint8 value){

	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORT_A:
			PORTA = value;
			break;
		case PORT_B:
			PORTB = value;
			break;
		case PORT_C:
			PORTC = value;
			break;
		case PORT_D:
			PORTD = value;
			break;
		}
	}

}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
Logic GPIO_readPin(Port port_num, Pins pin_num){

	Logic pin_value = LOW ;


	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(port_num)
		{

		case PORT_A :
			pin_value = GET_BIT(PINA,pin_num);
			break;

		case PORT_B :
			pin_value = GET_BIT(PINB,pin_num);
			break;

		case PORT_C :
			pin_value = GET_BIT(PINC,pin_num);
			break;

		case PORT_D :
			pin_value = GET_BIT(PIND,pin_num);
			break;

		}
	}

	return pin_value;
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(Port port_num){

	uint8 port_value = LOW ;

	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(port_num)
		{

		case PORT_A :
			port_value = PINA;
			break;

		case PORT_B :
			port_value = PINB;
			break;

		case PORT_C :
			port_value = PINC;
			break;

		case PORT_D :
			port_value = PIND;
			break;

		}
	}

	return port_value;
}
