/*************************************************************
 * 
 * Filename: TIMER_Priv.h
 * Description: Private header file of the TIMER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __TIMER_PRIV_H__
#define __TIMER_PRIV_H__

#define  TCNT0	(*(volatile u8*)(0x52))
#define  TCCR0	(*(volatile u8*)(0x53))
#define  TIFR	(*(volatile u8*)(0x58))
#define  TIMSK	(*(volatile u8*)(0x59))
#define  OCR0	(*(volatile u8*)(0x5c))


#endif /* __TIMER_PRIV_H__ */