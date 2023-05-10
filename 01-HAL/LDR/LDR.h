/*************************************************************
 * 
 * Filename: LDR.h
 * Description: Header (interface) file of the LDR driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/
#ifndef __LDR_H__
#define __LDR_H__
#include "STD_TYPES.h"
#include "LDR_Priv.h"
#include "ADC.h"
#include "DIO.h"
#include "LCD.h"

typedef enum{
	LDR_enuOK,
	LDR_enuNOK,
	
	}LDR_enuErrorStatus_t;
	
void LDR_vidInit();
LDR_enuErrorStatus_t LDR_getLDRResistance(u16 *AddLDRVal);

#endif /* __LDR_H__ */