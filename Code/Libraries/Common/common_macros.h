/***********************************************************************************************************
 * Module: Common - Macros
 *
 * File Name : common_macros.h
 *
 * Description: Commonly used Macros
 *
 *  Author: BASSANT AHMED
 **********************************************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT)      ( REG |= (1 << BIT) )

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT)    ( REG &= (~(1 << BIT)) )

/* Get a certain bit in any register */
#define GET_BIT(REG,BIT)      ( (REG >> BIT) & 1 )

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT)   ( REG ^= (1 << BIT) )

/* Check if the bit is set */
#define BIT_IS_SET(REG,BIT)   ( REG & (1 << BIT) )

/* Check if the bit is clear */
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1 << BIT) ))

/*Rotate the register right by specific value */
#define ROR(REG,num)          ( REG = (REG >> num) | (REG << (8 - num)) )

/*Rotate the register left by specific value */
#define ROL(REG,num)          ( REG = (REG << num) | (REG >> (8 - num)) )

#endif /* COMMON_MACROS_H_ */
