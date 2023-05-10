/*
 * SSEG_Potentiometer_ADC.c
 * Created: 2/9/2023 6:11:12 PM
 *  Author: Sara Mounier
 */ 
#include <math.h>
#include "SSEG_Potentiometer_ADC.h"


void SSEG_Output(DIO_tenuPorts Cpy_enuPortNumber,u8 Num)
{
	switch(Num)
	{
		case 0:
		 Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,ZERO);
		 break;
		case 1:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,ONE);
		break;		
		case 2:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,TWO);
		break;
		case 3:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,THREE);
		break;
		case 4:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,FOUR);
		break;
		case 5:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,FIVE);
		break;
		case 6:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,SIX);
		break;
		case 7:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,SEVEN);
		break;
		case 8:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,EIGHT);
		break;
		case 9:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,NINE);
		break;		
	}
}
 void ADC_Potentiometer_SSEG()
 {
	 u16 CurrentResistanceValue=0;
	 u16 ADC_OutputData=0;
	 u8 ones_SSEG,tens_SSEG;
	adc_selectVREF(REFS_AVCC);
	//adc_selectVREF(REFS_INT_2_56AREF);
	adc_setADLAR(ADLAR_ENABLE);
	//adc_setADLAR(ADLAR_DISABLE);
	adc_Enable();
	adc_autoTriggerEnable();
	adc_setInterruptEnable();
	adc_selectMUX(MUX_ADC0);
	
	/*free running mode*/
	adc_selectAutoTriggerSource(ADTS_FreeRunningMode); // for free running mode uncommented these line
	/*Interrupt mode*/
	//adc_selectAutoTriggerSource(ADTS_ExternalInterruptRequest0); // for Interrupt mode uncommented these line

	adc_startConversion();
	
	/*10 bits read :ok*/ //don't forget to enable adlar
	adc_getDataLeftAdgust_10bits(& ADC_OutputData);
	CurrentResistanceValue=(u16)ceil((ADC_OutputData/1023.0)*99);
	

                /*8 bits read:Done right*/ //don't forget to enable adlar
/*
	adc_getDataLeftAdgust_8bits(& ADC_OutputData);
	CurrentResistanceValue=ceil((ADC_OutputData/255.0)*99);
*/
				/*10 bits read:ok right*/ //don't forget to disable adlar
/*
	adc_getDataRightAdgust(& ADC_OutputData);
	CurrentResistanceValue=ceil((ADC_OutputData/1023.0)*99);
*/

	if(CurrentResistanceValue >= 99.0)
	{		
		Turn_Group_of_LEDs_ON ( DIO_enuPortB, NINE);
		Turn_Group_of_LEDs_ON ( DIO_enuPortC, NINE);
	}
	
	else
	{
		ones_SSEG=CurrentResistanceValue %10;
		tens_SSEG=CurrentResistanceValue /10;
		SSEG_Output( DIO_enuPortB,ones_SSEG );
		SSEG_Output( DIO_enuPortC,tens_SSEG );	
	}

 }