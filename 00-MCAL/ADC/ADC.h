/*************************************************************
 * 
 * Filename: ADC.h
 * Description: Header (interface) file of the ADC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __ADC_H__
#define __ADC_H__
#include "STD_TYPES.h"

/*Reference Voltage Selection*/
#define  REFS_AREF 00
#define  REFS_AVCC 01
#define  REFS_INT_2_56AREF 11

#define ADLAR 5
/* Analog Channel and Gain Selection Bits Selection*/
#define MUX_ADC0 		        00000
#define MUX_ADC1 		        00001
#define MUX_ADC2 		        00010
#define MUX_ADC3 		        00011
#define MUX_ADC4 		        00100
#define MUX_ADC5 		        00101
#define MUX_ADC6 		        00110
#define MUX_ADC7 		        00111

#define MUX_ADC0_ADC0_Gx10      01000
#define MUX_ADC1_ADC0_Gx10      01001

#define MUX_ADC0_ADC0_Gx200     01010
#define MUX_ADC1_ADC0_Gx200 	01011

#define MUX_ADC2_ADC2_Gx10      01100
#define MUX_ADC3_ADC2_Gx10 	    01101

#define MUX_ADC2_ADC2_Gx200     01110
#define MUX_ADC3_ADC2_Gx200     01111

#define MUX_ADC0_ADC1_Gx1       10000
#define MUX_ADC1_ADC1_Gx1       10001
#define MUX_ADC2_ADC1_Gx1       10010
#define MUX_ADC3_ADC1_Gx1       10011
#define MUX_ADC4_ADC1_Gx1       10100
#define MUX_ADC5_ADC1_Gx1       10101
#define MUX_ADC6_ADC1_Gx1       10110
#define MUX_ADC7_ADC1_Gx1       10111

#define MUX_ADC0_ADC2_Gx1       11000
#define MUX_ADC1_ADC2_Gx1       11001
#define MUX_ADC2_ADC2_Gx1       11010
#define MUX_ADC3_ADC2_Gx1       11011
#define MUX_ADC4_ADC2_Gx1       11100
#define MUX_ADC5_ADC2_Gx1       11101

#define MUX_VBG                 11110
#define MUX_GND                 11111

#define  ADLAR_ENABLE  1
#define  ADLAR_DISABLE 0

/* ADCSRA */
#define ADEN  7
#define ADSC  6
#define ADATE 5
#define ADIF  4
#define ADIE  3
#define ADPS0 0 
#define ADC_ENABLE  1
#define ADC_DISABLE 0


#define ADSC_ConversionStarted 1

#define ADATE_ENABLED  1
#define ADATE_DISABLED 0

#define ADIF_ON  1
#define ADIF_OFF 0
#define ADIF_CLEARED 1

#define ADC_INTERRUPTENABLE 1
#define ADC_INTERRUPTDISABLE 0

#define XTALDivBy_002  000
#define XTALDivBy_002_1  001
#define XTALDivBy_004  010
#define XTALDivBy_016  011
#define XTALDivBy_032  100
#define XTALDivBy_064  101
#define XTALDivBy_128  110
#define MASK_XTALPreScaler 0xf8

/*ADCL and ADCH*/

#define L_ADC0 6

/*SFIOR REG*/
#define  ADTS0 5
#define MASK_ADTS 0x1f

#define ADTS_FreeRunningMode				 000
#define ADTS_AnalogComparator                001
#define ADTS_ExternalInterruptRequest0       010
#define ADTS_Timer_Counter0CompareMatch      011
#define ADTS_Timer_Counter0Overflow          100
#define ADTS_Timer_Counter1CompareMatchB     101
#define ADTS_Timer_Counter1Overflow          110
#define ADTS_Timer_Counter1CaptureEvent      111


typedef enum 
{
	ADC_enuOK,
	ADC_enuNOK,
	ADC_enuNullPtr,
	ADC_enuInvalidParameter,
	ADC_enuInvalidConfiguration,
}ADC_enuErrorStatus_t;
	
	
ADC_enuErrorStatus_t adc_Init(void);
	
/*
Description: 
Options:
REFS_AREF ,REFS_AVCC, REFS_INT_2_56AREF
Return type:
*/
ADC_enuErrorStatus_t adc_selectVREF(u8 REFS_);	
/*
Description:
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_selectMUX(u8 MUX_);

/*
Description: 
Options: ADLAR_ENABLE OR ADLAR_ENABLE
Return type:
*/
ADC_enuErrorStatus_t adc_setADLAR(u8 ADLAR_);

 /*
Description:Enable ADC
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_Enable();

  /*
Description:Disable ADC
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_Disable();

/*
Description: Start Conversion 
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_startConversion();

/*
Description:ADATE: ADC Auto Trigger Enable
The trigger source is selected by setting the ADC Trigger Select bits, ADTS in SFIOR.
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_autoTriggerEnable();

/*
Description:ADATE: ADC Auto Trigger Disable
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_autoTriggerDisable();

/*
Description: ADIF: get ADC Interrupt Flag
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_getInterruptFlag(u8* Add_ADCIntFlagStatus);

/*
Description: ADIF: clear ADC Interrupt Flag in polling mode
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_clearInterruptFlag();

/*
Description: ADIE: Interrupt Enable
When this bit is written to one and the I-bit in SREG is set, the ADC Conversion Complete Interrupt is activated.
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_setInterruptEnable();
ADC_enuErrorStatus_t adc_setInterruptDisable();

/*
Description: ADPS2:0: ADC pre-scaler Select Bits 
These bits determine the division factor between the XTAL frequency and the input clock to the ADC.
Options: XTALDivBy_002,XTALDivBy_004,XTALDivBy_008,XTALDivBy_016,XTALDivBy_032,XTALDivBy_064,XTALDivBy_128
Return type:
*/
ADC_enuErrorStatus_t adc_setXTALPreScaler(u8 XTALDivBy_);

/*
Description:Get data. Make sure that ADLAR BIT in ADMUX Reg =0
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_getDataRightAdgust(u16* Add_ADCDataRightAdjust);
/*
Description:Get data. Make sure that ADLAR BIT in ADMUX Reg =1
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_getDataLeftAdgust_8bits(u8* Add_ADCDataLeftAdjust);
/*
Description:Get data. Make sure that ADLAR BIT in ADMUX Reg =1
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_getDataLeftAdgust_10bits(u16* Add_ADCDataLeftAdjust); 

/*
Description:If ADATE(auto trigger) in ADCSRA is written to one, the value of these bits selects which source
 will trigger an ADC conversion.
  If ADATE is cleared, the ADTS2:0 settings will have no effect.
Options:
Return type:
*/
ADC_enuErrorStatus_t adc_selectAutoTriggerSource(u8 ADTS_);


#endif /* __ADC_H__ */



/*
Description: 
Options:
Return type:
*/