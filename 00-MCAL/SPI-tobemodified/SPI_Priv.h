/*************************************************************
 * 
 * Filename: SPI_Priv.h
 * Description: Private header file of the SPI driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SPI_PRIV_H__
#define __SPI_PRIV_H__

#include "STD_TYPES.h"
#define SPI_SPCR  (*(volatile u8*)(0x2D))
#define SPI_SPSR  (*(volatile u8*)(0x2E))
#define SPI_SPDR  (*(volatile u8*)(0x2F))


#endif /* __SPI_PRIV_H__ */