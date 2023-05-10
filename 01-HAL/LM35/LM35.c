/*************************************************************
 * 
 * Filename: LM35.c
 * Description: Source file of the LM35 driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include <math.h>
#include "STD_TYPES.h"
#include "LM35_Cfg.h"
#include "LM35_Priv.h"
#include "LM35.h"
#include "ADC.h"
#include "ADC_Cfg.h"
#include "ADC_Priv.h"
#include "DIO.h"

void LM_vidInit(void)
{
	DIO_Init();
	adc_vidInit();
}

LM_enuErrorStatus_t LM_readTemp(u8 SensorMUX_,u16 *Add_LMReading)
{	
	u16 LocADCreading=0;
	LM_enuErrorStatus_t Loc_LMenuErrorStatus;
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	if(Add_LMReading!=NULL)
	{
		Loc_ADCenuErrorStatus=adc_selectMUX(SensorMUX_);
		if(Loc_ADCenuErrorStatus==ADC_enuOK)
		{
			adc_startConversion();
			adc_getDataRightAdgust(&LocADCreading);
		}
		*Add_LMReading=(u16)((LocADCreading/RESOLUTION)*(VOLTAGE_TO_TEMP_FACTOR*MAX_VOLTAGE));
		Loc_LMenuErrorStatus=LM_enuOK;
	}
	else
	{
		Loc_LMenuErrorStatus=LM_enuNullPtr;
	}
	return Loc_LMenuErrorStatus;
}
