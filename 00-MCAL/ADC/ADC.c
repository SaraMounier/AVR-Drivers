/*************************************************************
 * 
 * Filename: ADC.c
 * Description: Source file of the ADC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "ADC_Cfg.h"
#include "ADC_Priv.h"
#include "ADC.h"

volatile ADC_Registers * const ADC = (volatile ADC_Registers * const) BASE_ADDRESS;


static void ADMUX_SetBits(u8 MASK_Bits,u8 OPTION,u8 Start_Bits)
{
	u8 TempVar= (ADC->ADMUX) & MASK_Bits ;
	(ADC->ADMUX)= TempVar | (OPTION) <<(Start_Bits);	
}

ADC_enuErrorStatus_t adc_Init(void)
{
	#define Selected_XTAL					XTALDivBy_002
	
	#if Selected_ADC_EN_DIS	== ADC_ENABLE
		adc_Enable();
	#elif  Selected_ADC_EN_DIS	== ADC_DISABLE
		adc_Disable();
	#endif
	
	adc_selectVREF(Selected_REFS);
	adc_selectMUX(Selected_channel);
	adc_setADLAR(Selected_ADLAR_EN_DIS);
	
	#if Selected_ADATE_EN_DIS==ADATE_ENABLED
		adc_autoTriggerEnable();
		adc_selectAutoTriggerSource(Selected_ADTS_MODE);

	#elif Selected_ADATE_EN_DIS	==ADATE_DISABLED
		adc_autoTriggerDisable();
	#endif
	
	#if Selected_Interrupt_EN_DIS	== ADC_INTERRUPTENABLE
		adc_setInterruptEnable();
	#elif  Selected_Interrupt_EN_DIS	== ADC_INTERRUPTDISABLE
		adc_setInterruptDisable();
	#endif
	
	adc_setXTALPreScaler(XTALDivBy_002);
}

ADC_enuErrorStatus_t adc_selectVREF(u8 REFS_)
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	if (REFS_ == REFS_AREF || REFS_ == REFS_AVCC || REFS_ == REFS_INT_2_56AREF)
	{
		ADMUX_SetBits(MASK_REFS,REFS_,Start_Bits_REFS);
		Loc_ADCenuErrorStatus= ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus= ADC_enuInvalidParameter;
	}
	
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_selectMUX(u8 MUX_)
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	if (MUX_ >= MUX_ADC0 && MUX_ <= MUX_GND)
	{
		ADMUX_SetBits(MASK_MUX,MUX_,Start_Bits_MUX);
		Loc_ADCenuErrorStatus= ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus= ADC_enuInvalidParameter;
	}
	
	return Loc_ADCenuErrorStatus;
}


ADC_enuErrorStatus_t adc_setADLAR(u8 ADLAR_)
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	if(ADLAR_==ADLAR_ENABLE || ADLAR_==ADLAR_DISABLE)
	{
		ADMUX_SetBits(MASK_ADLAR, ADLAR_, Start_Bits_ADLAR);
		Loc_ADCenuErrorStatus= ADC_enuOK;
	}
	else 
	{
		Loc_ADCenuErrorStatus= ADC_enuInvalidParameter;		
	}
	
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_Enable()
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	(ADC->ADCSRA) |= 1<<ADEN ;
	if((((ADC->ADCSRA)>>ADEN ) & 0x01) == ADC_ENABLE)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;		
	}
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_Disable()
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	(ADC->ADCSRA) &= ~(1<<ADEN) ;
	if((((ADC->ADCSRA)>>ADEN ) & 0x01) == ADC_DISABLE)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;

}

ADC_enuErrorStatus_t adc_startConversion()
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	(ADC->ADCSRA) |= (1<<ADSC) ;
	if((((ADC->ADCSRA)>> ADSC ) & 0x01) == ADSC_ConversionStarted)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;

}

ADC_enuErrorStatus_t adc_autoTriggerEnable()
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	(ADC->ADCSRA) |= (1<<ADATE) ;
	if((((ADC->ADCSRA)>> ADATE ) & 0x01) == ADATE_ENABLED)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_autoTriggerDisable()
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	(ADC->ADCSRA) &= ~(1<<ADATE) ;
	if((((ADC->ADCSRA)>> ADATE ) & 0x01) == ADATE_DISABLED)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;	
}

ADC_enuErrorStatus_t adc_getInterruptFlag(u8* Add_ADCIntFlagStatus)
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	if((((ADC->ADCSRA)>> ADIF) & 0x01)== ADIF_ON)
	{
		*Add_ADCIntFlagStatus=ADIF_ON;
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else if((((ADC->ADCSRA)>> ADIF) & 0x01)== ADIF_OFF)
	{
		*Add_ADCIntFlagStatus=ADIF_OFF;
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_clearInterruptFlag() // should I check if the auto-trigger mode is off ? to ensure using this function in polling mode
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	 (ADC->ADCSRA) |= (1<< ADIF);
	 if((((ADC->ADCSRA)>> ADIF) & 0x01) == ADIF_CLEARED)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_setInterruptEnable()
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	(ADC->ADCSRA) |= 1<<ADIE ;
	if((((ADC->ADCSRA)>>ADIE ) & 0x01) == ADC_INTERRUPTENABLE)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_setInterruptDisable()
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	(ADC->ADCSRA) &= ~(1<<ADIE) ;
	if((((ADC->ADCSRA)>>ADIE ) & 0x01) == ADC_INTERRUPTDISABLE)
	{
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuNOK;
	}
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_setXTALPreScaler(u8 XTALDivBy_)
{ 
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	if(XTALDivBy_ >= XTALDivBy_002 && XTALDivBy_ <= XTALDivBy_128 )
	{
		u8 TempVar= (ADC->ADCSRA) & MASK_XTALPreScaler ;
		(ADC->ADCSRA)= TempVar | (XTALDivBy_);
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuInvalidParameter;
	}
	
	return Loc_ADCenuErrorStatus;
	}

ADC_enuErrorStatus_t adc_getDataRightAdgust(u16* Add_ADCDataRightAdjust)
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	u16 LocADCL=0,LocADCH=0;
	if((((ADC->ADMUX)>> ADLAR ) & 0x01) == ADLAR_DISABLE)
	{
		LocADCL = ADC->ADCL;
		LocADCH = ADC->ADCH;
		*Add_ADCDataRightAdjust= LocADCL;
		*Add_ADCDataRightAdjust |= LocADCH <<8;	
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuInvalidConfiguration;
	}
	
	return Loc_ADCenuErrorStatus; 
}

ADC_enuErrorStatus_t adc_getDataLeftAdgust_8bits(u8* Add_ADCDataLeftAdjust)
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	if((((ADC->ADMUX)>>ADLAR ) & 0x01) == ADLAR_ENABLE)
	{
		*Add_ADCDataLeftAdjust= ADC->ADCH;
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuInvalidConfiguration;
	}

	return Loc_ADCenuErrorStatus;	
	
}

ADC_enuErrorStatus_t adc_getDataLeftAdgust_10bits(u16* Add_ADCDataLeftAdjust)
{
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus;
	u16 LocADCL=0,LocADCH=0;
	if((((ADC->ADMUX)>>ADLAR ) & 0x01) == ADLAR_ENABLE)
	{
		LocADCL = (ADC->ADCL >> L_ADC0) ;
		LocADCH = ADC->ADCH;
		*Add_ADCDataLeftAdjust= LocADCL;
		*Add_ADCDataLeftAdjust |= LocADCH <<2;
		Loc_ADCenuErrorStatus=ADC_enuOK;
	}
	else
	{
		Loc_ADCenuErrorStatus=ADC_enuInvalidConfiguration;
	}
	
	return Loc_ADCenuErrorStatus;
}

ADC_enuErrorStatus_t adc_selectAutoTriggerSource(u8 ADTS_)
{ 
	ADC_enuErrorStatus_t Loc_ADCenuErrorStatus=ADC_enuOK;
	if (((ADC->ADCSRA >>ADATE) &0x01) == ADATE_ENABLED)
	{
		if((ADTS_ >= ADTS_FreeRunningMode) && (ADTS_ <= ADTS_Timer_Counter1CaptureEvent))
		{
			u8 TempVar= (SFIOR) & MASK_ADTS ;
			(SFIOR)= TempVar | (ADTS_ <<ADTS0);
			Loc_ADCenuErrorStatus=ADC_enuOK;
		}
		else
		{
			Loc_ADCenuErrorStatus=ADC_enuInvalidParameter;
		}
	}
	
	else if(((ADC->ADCSRA >>ADATE) &0x01) == ADATE_DISABLED)
	{
		Loc_ADCenuErrorStatus=ADC_enuInvalidConfiguration;
	}
	
	return Loc_ADCenuErrorStatus;
}
