/*************************************************************
 * 
 * Filename: ADC_Priv.h
 * Description: Private header file of the ADC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __ADC_PRIV_H__
#define __ADC_PRIV_H__
 
#define  MASK_REFS  0x3f
#define  MASK_MUX   0xe0
#define  MASK_ADLAR 0xdf

#define  Start_Bits_REFS   6
#define  Start_Bits_MUX    0
#define  Start_Bits_ADLAR  5



static void ADMUX_SetBits(u8 MASK_Bits,u8 OPTION,u8 Start_Bits);

#endif /* __ADC_PRIV_H__ */