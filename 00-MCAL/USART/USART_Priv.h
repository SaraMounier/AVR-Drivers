/*************************************************************
 * 
 * Filename: USART_Priv.h
 * Description: Private header file of the USART driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __USART_PRIV_H__
#define __USART_PRIV_H__

#define USART_UDR   (*(volatile u8*)(0x2C))
#define USART_UCSRA (*(volatile u8*)(0x2B))
#define USART_UCSRB (*(volatile u8*)(0x2A))
#define USART_UCSRC (*(volatile u8*)(0x40))
#define USART_UBRRL (*(volatile u8*)(0x29))
#define USART_UBRRH (*(volatile u8*)(0x40))
#endif /* __USART_PRIV_H__ */