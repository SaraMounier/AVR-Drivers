/*
 * SSEG_Potentiometer_ADC.h
 *
 * Created: 2/9/2023 8:15:34 PM
 *  Author: Sara Mounier
 */ 


#ifndef SSEG_POTENTIOMETER_ADC_H_
#define SSEG_POTENTIOMETER_ADC_H_

#include "STD_TYPES.h"
#include "DIO.h"
#include "ADC.h"
#include "Seven_Segment.h"
#include "LED.h"

void SSEG_Output(DIO_tenuPorts Cpy_enuPortNumber,u8 Num);
void ADC_Potentiometer_SSEG();




#endif /* SSEG_POTENTIOMETER_ADC_H_ */