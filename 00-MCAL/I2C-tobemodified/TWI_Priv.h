/*************************************************************
 * 
 * Filename: TWI_Priv.h
 * Description: Private header file of the TWI driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __TWI_PRIV_H__
#define __TWI_PRIV_H__

#define TWI_TWBR (*(volatile u8*)(0x20))
#define TWI_TWCR (*(volatile u8*)(0x56))
#define TWI_TWSR (*(volatile u8*)(0x21))
#define TWI_TWDR (*(volatile u8*)(0x23))
#define TWI_TWAR (*(volatile u8*)(0x22))




#endif /* __TWI_PRIV_H__ */