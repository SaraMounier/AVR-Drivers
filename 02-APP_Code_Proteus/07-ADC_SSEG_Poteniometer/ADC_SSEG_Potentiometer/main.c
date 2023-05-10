/*
 * ADC_Driver.c
 *
 * Created: 2/9/2023 8:54:19 AM
 * Author : Sara Mounier
 */ 
#include "SSEG_Potentiometer_ADC.h"
// for Interrupt mode uncommented these lines
/*INT0 mode*/
/*
void ADC_Interrupt_Function(void)
{
	while(1)
	{
		ADC_Potentiometer_SSEG();
	}
}
*/

int main(void)
{ //u8 flag; // for SINGLE CONVERSION mode UNcomment this line
	DIO_Init();
	//SetCallBack( ADC_Interrupt_Function );// for Interrupt mode decomment this line
	//GI_enuInit();
	//EXINT_Init();

    /* Replace with your application code */
    while (1) 
    {
		ADC_Potentiometer_SSEG(); //for free running mode uncomment this line
		
				/*single conversion*/
		/*while (flag==0){adc_getInterruptFlag(&flag);}
		adc_clearInterruptFlag();
	 	adc_selectMUX(MUX_ADC0);
	 	adc_startConversion();*/
    }
}

