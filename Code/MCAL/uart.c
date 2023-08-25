/***********************************************************************************************************
 * Module : UART
 *
 * File name : uart.c
 *
 * Description : Source file for the UART AVR driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/

#include<avr/io.h>
#include <avr/interrupt.h>
#include"uart.h"
#include"common_macros.h"
#include"gpio.h"

volatile uint8 receive_data = 0 ;
volatile uint8 IN_FLAG = 0 ;

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
 *********************************************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr){

	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA |= (1 << U2X);

	/*
	 * RXEN  = 1 Receiver Enable
     */
	UCSRB |= (1 << RXEN) | (1 << TXEN);

	/*Setup the Interrupt Mode*/
#if(EN_INTERRUPT_RXC == 1)
	SET_BIT(UCSRB,RXCIE);
#endif

	                  /********************Setup Baud Rate**********************/

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)( ((F_CPU / ( (Config_Ptr->baud_rate) * 8UL ) )) - 1 );

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value >> 8;
	UBRRL = ubrr_value;

	/* URSEL   = 1 The URSEL must be one when writing the UCSRC at every time I try to access it*/


	/*Setup Mode Select*/
	if(Config_Ptr ->mode_select == Asynchronous){
		CLEAR_BIT(UCSRC,UMSEL);
		CLEAR_BIT(UCSRC,UCPOL);/*This bit is = 0 with Asynchronous mode*/
	}
	else if(Config_Ptr ->mode_select == synchronous){
		UCSRC |= (1<<URSEL) | (1<<UMSEL);

		/*Setup Clock Polarity*/
#ifdef CLOCK_POLARITY

#if(UCPOL_VALUE == 0)
		CLEAR_BIT(UCSRC,UCPOL);
#elif(UCPOL_VALUE == 1)
		SET_BIT(UCSRC,UCPOL);
#endif

#endif
	}


	/*Setup Character size*/
	if(Config_Ptr ->ch_size != BITS_9){
		//UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
		UCSRC |= (1 << URSEL) | ( (UCSRC & 0xF9) | ((Config_Ptr ->ch_size) << 1)) ;
	}
	else {
		UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
		SET_BIT(UCSRB,UCSZ2);
	}


	/*Setup Number of Stop Bits*/
	if(Config_Ptr ->num_stopBits == BIT_1){
		CLEAR_BIT(UCSRC,USBS);
	}
	else if(Config_Ptr ->num_stopBits == BIT_2){
		UCSRC |= (1 << URSEL) | (1 << USBS);
	}


	/*Setup Parity Mode*/
	UCSRC |= (1 << URSEL) | ((UCSRC & 0xCF) | ((Config_Ptr ->parity_mode) << 4)) ;


}
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void  UART_sendByte(uint8 data){

	/*
		 * UDRE flag is set when the TX buffer (UDR) is empty and ready for
		 * transmitting a new byte so wait until this flag is set to one
		 */
	while(BIT_IS_CLEAR(UCSRA,UDRE));

	    /*
		 * Put the required data in the UDR register and it also clear the UDRE flag as
		 * the UDR register is not empty now
		 */
	UDR = data;
	/********************************** Another Method ************************************
		UDR = data;
		while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
		SET_BIT(UCSRA,TXC); // Clear the TXC flag
	***************************************************************************************/
}

#if(EN_INTERRUPT_RXC == 0)
/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void){


	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC));

	    /*
		 * Read the received data from the Rx buffer (UDR)
		 * The RXC flag will be cleared after read the data
		 */
	return UDR;

}
#endif

/*
 * Description :
 * Functional responsible for send string to another UART device.
 */
void  UART_sendString(const uint8 *String){

	/*Send the string*/
	while(*String != '\0'){
		UART_sendByte(*String);
		String++;
	}

}

#if(EN_INTERRUPT_RXC == 0)
/*
 * Description :
 * Receive the required string until the specific symbol through UART from the other UART device.
 */
uint8 UART_receiveString(uint8 *String){

	uint8 i = 0;

	/*Receive the first byte*/
	String[i] = UART_receiveByte();

	/*Receive the string*/
	while(String[i] != END_SYMBOL_FOR_RECEIVING_STRING_1 && String[i] != END_SYMBOL_FOR_RECEIVING_STRING_2){
		i++;
		String[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the specific symbol, replace this specific symbol with '\0' */
	String[i] = '\0';

	return i ;

}
#endif

/**********************************************************************************************************
 *                                     ISR's Definitions                                                  *
 *********************************************************************************************************/
/*
 * Description : Interrupt for receive byte
 */
#if(EN_INTERRUPT_RXC == 1)
ISR(USART_RXC_vect){
	receive_data = UDR;
	IN_FLAG = 1;
	//UART_sendByte(receive_data);
}
#endif
