/***********************************************************************************************************
 * Module : LCD
 *
 * File name : lcd.c
 *
 * Description : Source file for LCD driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/

#include<util/delay.h>
#include<stdlib.h>
#include"common_macros.h"
#include"gpio.h"
#include"lcd.h"

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
**********************************************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void){

	GPIO_setupPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT_PIN);

	_delay_ms(50);

#if(MODE == 8)
	GPIO_setupPinDirection(LCD_DB0_PORT,LCD_DB0_PIN,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DB1_PORT,LCD_DB1_PIN,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DB2_PORT,LCD_DB2_PIN,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DB3_PORT,LCD_DB3_PIN,OUTPUT_PIN);
#endif
	GPIO_setupPinDirection(LCD_DB4_PORT,LCD_DB4_PIN,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DB5_PORT,LCD_DB5_PIN,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DB6_PORT,LCD_DB6_PIN,OUTPUT_PIN);
	GPIO_setupPinDirection(LCD_DB7_PORT,LCD_DB7_PIN,OUTPUT_PIN);

#if(MODE == 4)
	LCD_sendCommand(LCD_TWO_LINES_4_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_4_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_4_BITS_MODE);
#elif(MODE == 8)
	LCD_sendCommand(LCD_TWO_LINES_8_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR);

}

/*
 * Description :
 * Send the required command to the LCD
 */
void LCD_sendCommand(uint8 command){

	GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, LOW); /*RS = 0 for send command*/
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, HIGH); /* EN = 1 */
	_delay_ms(1);

#if(MODE == 8)

	GPIO_writePin(LCD_DB0_PORT,LCD_DB0_PIN,GET_BIT(command,0));
	GPIO_writePin(LCD_DB1_PORT,LCD_DB1_PIN,GET_BIT(command,1));
	GPIO_writePin(LCD_DB2_PORT,LCD_DB2_PIN,GET_BIT(command,2));
	GPIO_writePin(LCD_DB3_PORT,LCD_DB3_PIN,GET_BIT(command,3));
	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(command,4));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(command,5));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(command,6));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOW); /* EN = 0 */
	_delay_ms(1);

#elif(MODE == 4)

	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(command,4));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(command,5));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(command,6));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOW); /* EN = 0 */
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, HIGH); /* EN = 1 */
	_delay_ms(1);

	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(command,0));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(command,1));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(command,2));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(command,3));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOW); /* EN = 0 */
	_delay_ms(1);

#endif

}

/*
 * Description :
 * Send the required character to the LCD
 */
void LCD_displayCharacter(uint8 character){

	GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, HIGH); /*RS = 1 for send data*/
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, HIGH); /* EN = 1 */
	_delay_ms(1);

#if(MODE == 8)

	GPIO_writePin(LCD_DB0_PORT,LCD_DB0_PIN,GET_BIT(character,0));
	GPIO_writePin(LCD_DB1_PORT,LCD_DB1_PIN,GET_BIT(character,1));
	GPIO_writePin(LCD_DB2_PORT,LCD_DB2_PIN,GET_BIT(character,2));
	GPIO_writePin(LCD_DB3_PORT,LCD_DB3_PIN,GET_BIT(character,3));
	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(character,4));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(character,5));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(character,6));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(character,7));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOW); /* EN = 0 */
	_delay_ms(1);

#elif(MODE == 4)

	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(character,4));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(character,5));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(character,6));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(character,7));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOW); /* EN = 0 */
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, HIGH); /* EN = 1 */
	_delay_ms(1);

	GPIO_writePin(LCD_DB4_PORT,LCD_DB4_PIN,GET_BIT(character,0));
	GPIO_writePin(LCD_DB5_PORT,LCD_DB5_PIN,GET_BIT(character,1));
	GPIO_writePin(LCD_DB6_PORT,LCD_DB6_PIN,GET_BIT(character,2));
	GPIO_writePin(LCD_DB7_PORT,LCD_DB7_PIN,GET_BIT(character,3));

	_delay_ms(1);
	GPIO_writePin(LCD_EN_PORT, LCD_EN_PIN, LOW); /* EN = 0 */
	_delay_ms(1);

#endif

}

/*
 * Description :
 * Display the required string on the LCD
 */
void LCD_displayString(const char *String){

	uint8 i = 0;

	while(String[i] != '\0'){
		LCD_displayCharacter(String[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the LCD
 */
void LCD_moveCursor(uint8 row,uint8 column){

#if(LCD_SIZE == 2)
	if( (row == 0 || row == 1) && (column >= 0 && column <= 15) )
			LCD_sendCommand(SET_DDRAM_Address + column + row*64);
#elif(LCD_SIZE == 3)
	if( (row == 0 || row == 1) && (column >= 0 && column <= 19) )
			LCD_sendCommand(SET_DDRAM_Address + column + row*64);
#elif(LCD_SIZE == 4)

	if( (row == 0 || row == 1) && (column >= 0 && column <= 19) )
		LCD_sendCommand(SET_DDRAM_Address + column + row*64);
	else if( (row == 2 ) && (column >= 0 && column <= 19) )
		LCD_sendCommand(SET_DDRAM_Address + (column + 20) ); //row = 0
	else if ( (row == 3 ) && (column >= 0 && column <= 19) )
		LCD_sendCommand(SET_DDRAM_Address + (column + 20) + 64); //row = 1

#elif(LCD_SIZE == 5)

	if( (row == 0 || row == 1) && (column >= 0 && column <= 15) )
		LCD_sendCommand(SET_DDRAM_Address + column + row*64);
	else if( (row == 2 ) && (column >= 0 && column <= 15) )
		LCD_sendCommand(SET_DDRAM_Address + (column + 16) ); //row = 0
	else if ( (row == 3 ) && (column >= 0 && column <= 15) )
		LCD_sendCommand(SET_DDRAM_Address + (column + 16) + 64); //row = 1

#elif(LCD_SIZE == 6)

	if( (row == 0 || row == 1) && (column >= 0 && column <= 31) )
			LCD_sendCommand(SET_DDRAM_Address + column + row*64);

#endif
		else
			return;

		_delay_ms(3);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the LCD
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *String)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(String); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the LCD
 */
void LCD_sendNumbers(uint32 number)
{
   char buffer[16]; /* String to hold the ASCII result */
   itoa((uint32)number,buffer,10); /* Use itoa C function to convert the number to its corresponding ASCII value, 10 for decimal (Base 10)*/
   LCD_displayString(buffer); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR); /* Send clear display command */
}

/**********************************************************************************************************

 LCD_displayCharacter(0b00000); //ب
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b11111);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b01100);
 LCD_displayCharacter(0b00000);

 LCD_displayCharacter( 0b00000); //س
 LCD_displayCharacter( 0b10101);
 LCD_displayCharacter( 0b10101);
 LCD_displayCharacter( 0b10101);
 LCD_displayCharacter( 0b11111);
 LCD_displayCharacter( 0b00000);
 LCD_displayCharacter( 0b00000);
 LCD_displayCharacter( 0b00000);

 LCD_displayCharacter(0b01000);//ن
 LCD_displayCharacter(0b00010);
 LCD_displayCharacter(0b00010);
 LCD_displayCharacter(0b00010);
 LCD_displayCharacter(0b11111);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);

 LCD_displayCharacter(0b01100);//ت
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b10010);
 LCD_displayCharacter(0b10010);
 LCD_displayCharacter(0b11111);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);

 LCD_displayCharacter(0b00000); //مسافه
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);

 LCD_displayCharacter(0b00000);// قلب
 LCD_displayCharacter(0b01010);
 LCD_displayCharacter(0b10101);
 LCD_displayCharacter(0b10001);
 LCD_displayCharacter(0b01010);
 LCD_displayCharacter(0b00100);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);

 LCD_displayCharacter(0x00); // اسود ملون قلب
 LCD_displayCharacter(0x0A);
 LCD_displayCharacter(0x1F);
 LCD_displayCharacter(0x1F);
 LCD_displayCharacter(0x0E);
 LCD_displayCharacter(0x04);
 LCD_displayCharacter(0x00);
 LCD_displayCharacter(0x00);

LCD_displayCharacter(0x01); //سماعة
LCD_displayCharacter(0x03);
LCD_displayCharacter(0x07);
LCD_displayCharacter(0x1F);
LCD_displayCharacter(0x1F);
LCD_displayCharacter(0x07);
LCD_displayCharacter(0x03);
LCD_displayCharacter(0x01);

LCD_displayCharacter(0x01);// الموسيقى علامة
LCD_displayCharacter(0x03);
LCD_displayCharacter(0x05);
LCD_displayCharacter(0x09);
LCD_displayCharacter(0x09);
LCD_displayCharacter(0x0B);
LCD_displayCharacter(0x1B);
LCD_displayCharacter(0x18);

LCD_displayCharacter(0x00);// Smile
LCD_displayCharacter(0x00);
LCD_displayCharacter(0x0A);
LCD_displayCharacter(0x00);
LCD_displayCharacter(0x04);
LCD_displayCharacter(0x11);
LCD_displayCharacter(0x0E);
LCD_displayCharacter(0x00);

 LCD_displayCharacter(0b00100);//ن
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b11111);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);

 LCD_displayCharacter(0b00000); // ي
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b11111);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b01010);
 LCD_displayCharacter(0b00000);

LCD_displayCharacter(0b10000); // ا
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b11111);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);

LCD_displayCharacter(0b00000); // ز
LCD_displayCharacter(0b01000);
LCD_displayCharacter(0b00001);
LCD_displayCharacter(0b00001);
LCD_displayCharacter(0b00001);
LCD_displayCharacter(0b00100);
LCD_displayCharacter(0b01000);
LCD_displayCharacter(0b10000);

LCD_displayCharacter(0b00000); // ى
LCD_displayCharacter(0b00110);
LCD_displayCharacter(0b01001);
LCD_displayCharacter(0b00100);
LCD_displayCharacter(0b00010);
LCD_displayCharacter(0b10001);
LCD_displayCharacter(0b01110);
LCD_displayCharacter(0b10000);

LCD_displayCharacter(0b10000); // ا
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);

 LCD_displayCharacter(0b00000); // ي
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b00001);
 LCD_displayCharacter(0b11111);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b01010);
 LCD_displayCharacter(0b00000);

 LCD_displayCharacter(0b00000); // م
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00110);
 LCD_displayCharacter(0b01001);
 LCD_displayCharacter(0b11110);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);
 LCD_displayCharacter(0b00000);

LCD_displayCharacter(0b10000); // ا
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b10000);
LCD_displayCharacter(0b11111);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);

LCD_displayCharacter(0b00000); // ن
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00100);
LCD_displayCharacter(0b10001);
LCD_displayCharacter(0b10001);
LCD_displayCharacter(0b10001);
LCD_displayCharacter(0b01110);
LCD_displayCharacter(0b00000);

LCD_displayCharacter(0b01000); // ط
LCD_displayCharacter(0b01000);
LCD_displayCharacter(0b01111);
LCD_displayCharacter(0b01001);
LCD_displayCharacter(0b11111);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);

LCD_displayCharacter(0b00000); // ر
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00001);
LCD_displayCharacter(0b00001);
LCD_displayCharacter(0b00001);
LCD_displayCharacter(0b00100);
LCD_displayCharacter(0b01000);
LCD_displayCharacter(0b10000);

LCD_displayCharacter(0b00101); // ق
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00111);
LCD_displayCharacter(0b00101);
LCD_displayCharacter(0b00111);
LCD_displayCharacter(0b10001);
LCD_displayCharacter(0b01110);
LCD_displayCharacter(0b00000);

LCD_displayCharacter(0b01010); // ة
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b11111);
LCD_displayCharacter(0b10001);
LCD_displayCharacter(0b11111);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);
LCD_displayCharacter(0b00000);

 *********************************************************************************************************/
