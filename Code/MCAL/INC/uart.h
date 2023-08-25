/***********************************************************************************************************
 * Module : UART
 *
 * File name : uart.h
 *
 * Description : Header file for the UART AVR driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/


#ifndef UART_H_
#define UART_H_

#include"std_types.h"

/**********************************************************************************************************
 *                                             Globals                                                    *
 *********************************************************************************************************/

extern volatile uint8 receive_data;
extern volatile uint8 IN_FLAG ;

/**********************************************************************************************************
 *                                         Definitions                                                    *
 *********************************************************************************************************/

#define END_SYMBOL_FOR_RECEIVING_STRING_1 'E'
#define END_SYMBOL_FOR_RECEIVING_STRING_2 'e'


/*0 --> For Polling for receiving & 1 --> For Interrupt for receiving */
#define EN_INTERRUPT_RXC 0

#if( (EN_INTERRUPT_RXC != 0) && (EN_INTERRUPT_RXC != 1) )

#error "EN_INTERRUPT should be equal to 0 or 1"

#endif

//#define CLOCK_POLARITY
#define UCPOL_VALUE 0

typedef enum{
	Asynchronous,
	synchronous
}UART_ModeSelect;

typedef enum{
	BITS_5,
	BITS_6,
	BITS_7,
	BITS_8,
	BITS_9 = 7
}UART_CharacterSize;

typedef enum{
	BIT_1,
	BIT_2
}UART_StopBits;

typedef enum{
	Disabled,
	Reserved,
	Even_Parity,
	Odd_Parity
}UART_ParityMode;

typedef struct{
	uint32 baud_rate;
	UART_ModeSelect mode_select;
	UART_CharacterSize ch_size;
	UART_StopBits num_stopBits;
	UART_ParityMode parity_mode;
}UART_ConfigType;

/**********************************************************************************************************
 *                                        Functions Prototypes                                            *
 *********************************************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void  UART_sendByte(uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Functional responsible for send string to another UART device.
 */
void UART_sendString(const uint8 *String);

/*
 * Description :
 * Receive the required string until the specific symbol through UART from the other UART device.
 */
uint8 UART_receiveString(uint8 *String); // Receive until specific symbol


#endif /* UART_H_ */
