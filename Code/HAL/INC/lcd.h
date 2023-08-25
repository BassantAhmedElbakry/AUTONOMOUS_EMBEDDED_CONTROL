/***********************************************************************************************************
 * Module : LCD
 *
 * File name : lcd.h
 *
 * Description : Header file for LCD driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/**********************************************************************************************************
 *                                         Definitions                                                    *
 *********************************************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define MODE 4

#if( (MODE != 4) && (MODE != 8) )

#error "Number of data bits mode should be equal to 4 or 8"

#endif

/*LCD size 2 for 2*16 ,3 for 2*20, 4 for 4*20, 5 for 4*16 and 6 for 2*32 */
#define LCD_SIZE 6

#if( (LCD_SIZE != 2) && (LCD_SIZE != 3) && (LCD_SIZE != 4) && (LCD_SIZE != 5) && (LCD_SIZE != 6) )

#error "LCD_SIZE should be equal number from 2 --> 6 ONLY !!!"

#endif

/* LCD HW Ports and Pins IDs */
#if(MODE == 8)
#define LCD_DB0_PIN    PIN_0
#define LCD_DB1_PIN    PIN_1
#define LCD_DB2_PIN    PIN_2
#define LCD_DB3_PIN    PIN_3
#endif

#define LCD_DB4_PIN    PIN_4
#define LCD_DB5_PIN    PIN_5
#define LCD_DB6_PIN    PIN_6
#define LCD_DB7_PIN    PIN_7

#define LCD_RS_PIN     PIN_4
#define LCD_EN_PIN     PIN_5

#if(MODE == 8)
#define LCD_DB0_PORT   PORT_A
#define LCD_DB1_PORT   PORT_A
#define LCD_DB2_PORT   PORT_A
#define LCD_DB3_PORT   PORT_A
#endif
#define LCD_DB4_PORT   PORT_A
#define LCD_DB5_PORT   PORT_A
#define LCD_DB6_PORT   PORT_A
#define LCD_DB7_PORT   PORT_A

#define LCD_RS_PORT    PORT_C
#define LCD_EN_PORT    PORT_C

/* LCD Commands */
#define LCD_CLEAR                         0x01
#define LCD_RETURN_HOME                   0x02
#define LCD_DISPLAY_CONTROL               0x0F /*CURSOR_BLINKING*/
#define LCD_STOP_CURSOR_BLINKING          0x0E
#define LCD_CURSOR_OFF                    0x0C
#define LCD_INCREMENT_CURSOR              0x06
#define LCD_DECREMENT_CURSOR              0x04
#define LCD_STOP_DISPLAYING               0x08
#define BOLD_FONT                         0x3C
#define SHIFT_DISPLAY_LEFT                0x07
#define SHIFT_DISPLAY_RIGHT               0x05
#define LCD_TWO_LINES_8_BITS_MODE         0x38
#define LCD_TWO_LINES_4_BITS_MODE         0x28
#define LCD_TWO_LINES_4_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_4_BITS_MODE_INIT2   0x32
#define ONE_LINE_8_BIT                    0x30
#define SET_DDRAM_Address                 0x80 /*SET_CURSOR_LOCATION*/
#define SET_CGRAM_Address                 0x40

/**********************************************************************************************************
 *                                        Functions Prototypes                                            *
 *********************************************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void);
/*
 * Description :
 * Send the required command to the LCD
 */
void LCD_sendCommand(uint8 command);
/*
 * Description :
 * Send the required character to the LCD
 */
void LCD_displayCharacter(uint8 character);

/*
 * Description :
 * Display the required string on the LCD
 */
void LCD_displayString(const char *String);

/*
 * Description :
 * Move the cursor to a specified row and column index on the LCD
 */
void LCD_moveCursor(uint8 row,uint8 column);

/*
 * Description :
 * Display the required string in a specified row and column index on the LCD
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *String);

/*
 * Description :
 * Display the required decimal value on the LCD
 */
void LCD_sendNumbers(uint32 number);

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
