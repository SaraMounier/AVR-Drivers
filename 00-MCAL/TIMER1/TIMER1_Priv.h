/*************************************************************
 * 
 * Filename: TIMER1_Priv.h
 * Description: Private header file of the TIMER1 driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __TIMER1_PRIV_H__
#define __TIMER1_PRIV_H__

#include "STD_TYPES.h"

#define T1_TCCR1A 	  (*(volatile u8*)(0x4f))
#define T1_TCCR1B	  (*(volatile u8*)(0x4e))
// #define TCNT1H	  (*(volatile u8*)(0x4d))
#define T1_TCNT1L	  (*(volatile u16*)(0x4c))
// #define OCR1AH	  (*(volatile u8*)(0x4b))
#define T1_OCR1AL	  (*(volatile u16*)(0x4a))
// #define OCR1BH	  (*(volatile u8*)(0x49))
#define T1_OCR1BL	  (*(volatile u16*)(0x48))
// #define ICR1H	  (*(volatile u8*)(0x47))
#define T1_ICR1L	  (*(volatile u16*)(0x46))

#define CLR_2BITS_MASK 0B11
#define CLR_3BITS_MASK 0B111

#endif /* __TIMER1_PRIV_H__ */