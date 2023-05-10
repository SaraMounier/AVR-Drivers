/*************************************************************
 * 
 * Filename: LDR.c
 * Description: Source file of the LDR driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/
#include "LDR.h"
#include "LDR_Cfg.h"

void LDR_vidInit()
{
	DIO_Init();
	adc_Init();
	LCD_vidInit();
}
LDR_enuErrorStatus_t LDR_getLDRResistance(u16 *AddLDRVal)
{
	LDR_enuErrorStatus_t Loc_LDRErrorStatus;
	ADC_enuErrorStatus_t Loc_ADCErrorStatus;
	u16 Loc_LDRVal;
	if(AddLDRVal !=NULL)
	{	
		adc_startConversion();
		Loc_ADCErrorStatus=adc_getDataLeftAdgust_10bits(& Loc_LDRVal);
		if(Loc_ADCErrorStatus == ADC_enuOK)
		{
			*AddLDRVal=(Loc_LDRVal/1023.0)*LDR_Max_Resistance_Value;
		}
		Loc_LDRErrorStatus=LDR_enuOK;
	}
	else
	{
		Loc_LDRErrorStatus=LDR_enuNOK;	
	}
return Loc_LDRErrorStatus;
}