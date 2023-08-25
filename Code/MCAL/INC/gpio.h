/*********************************************************************************************************
 * Module: GPIO
 *
 * File name : gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: BASSANT AHMED
 *********************************************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/**********************************************************************************************************
 *                                         Definitions                                                    *
 *********************************************************************************************************/

#define NUM_OF_PORTS 4
#define NUM_OF_PINS_PER_PORT 8

/**********************************************************************************************************
 *                                         Types Deceleration                                             *
 *********************************************************************************************************/

typedef enum{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
}Port;

typedef enum{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7
}Pins;

typedef enum{
	INPUT_PIN,
	OUTPUT_PIN
}GPIO_PinDirection;

typedef enum{
	INPUT_PORT,
	OUTPUT_PORT = 0xFF
}GPIO_PortDirection;

/**********************************************************************************************************
 *                                        Functions Prototypes                                            *
 *********************************************************************************************************/

/*
 *  Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(Port port_num, Pins pin_num , GPIO_PinDirection direction);
/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(Port port_num,GPIO_PortDirection direction);
/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(Port port_num, Pins pin_num , Logic value);
/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(Port port_num, uint8 value);
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
Logic GPIO_readPin(Port port_num, Pins pin_num);
/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(Port port_num);

#endif /* GPIO_H_ */
