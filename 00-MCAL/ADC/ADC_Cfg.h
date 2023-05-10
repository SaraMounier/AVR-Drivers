/*************************************************************
 * 
 * Filename: ADC_Cfg.h
 * Description: Configuration header file of the ADC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __ADC_CFG_H__
#define __ADC_CFG_H__
#include "STD_TYPES.h"
#define BASE_ADDRESS 0x24
#define SFIOR (*(volatile u8 *)(0x50))
typedef struct {
	u8 ADCL;
	u8 ADCH;
	u8 ADCSRA;
	u8 ADMUX;
	}ADC_Registers;
	
#define Selected_ADC_EN_DIS				ADC_ENABLE
#define Selected_REFS					REFS_AVCC
#define Selected_channel				MUX_ADC0 
#define Selected_ADLAR_EN_DIS			ADLAR_ENABLE
#define Selected_ADATE_EN_DIS			ADATE_ENABLED
#define Selected_Interrupt_EN_DIS		ADC_INTERRUPTENABLE
#define Selected_XTAL					XTALDivBy_002
#define Selected_ADTS_MODE				ADTS_FreeRunningMode


#endif /* __ADC_CFG_H__ */