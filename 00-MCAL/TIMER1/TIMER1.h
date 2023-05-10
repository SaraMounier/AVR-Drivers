/*************************************************************
 * 
 * Filename: TIMER1.h
 * Description: Header (interface) file of the TIMER1 driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __TIMER1_H__
#define __TIMER1_H__
#include "STD_TYPES.h"
#include "TIMER1_Cfg.h"
#include "TIMER1_Priv.h"

#define TCCR1A_COM1A1  7
#define TCCR1A_COM1A0  6
#define TCCR1A_COM1B1  5
#define TCCR1A_COM1B0  4

/*OC1A/OC1B Modes*/
#define OC1A_OC1B_NON_INVERTING_MODE 0B10

/*Waveform Generation Mode BitS*/
#define TCCR1A_WGM10 0
#define TCCR1A_WGM11 1
#define TCCR1B_WGM12 3
#define TCCR1B_WGM13 4

#define WGM_Fast_PWM_TOP_ICR1  0b1110
#define WGM_Fast_PWM_TOP_OCR1A 0b1111

/*Clock Pre-Scaler Select */
#define TCCR1B_CS10 0
#define TCCR1B_CS11 1
#define TCCR1B_CS12 2

#define TIMER1_CLK_NO_PRESCALER 0B001
#define TIMER1_CLK_DIV_BY_8 0B010


#define Fast_PWM_NonInverting  0b10
typedef enum 
{
	TIMER1_enuOK,
	TIMER1_enuNOK,
	TIMER1_enuInvalidParameters,
	
}TIMER1_enuErrorStatus_t;

TIMER1_enuErrorStatus_t timer1_setCompareOutputMode(u8 CompareOutputMode);

TIMER1_enuErrorStatus_t timer1_setCLKPrescaler(u8 TIMER1_CLK_);

TIMER1_enuErrorStatus_t timer1_setWaveformGenMode(u8 WaveformGenMode);

TIMER1_enuErrorStatus_t timer1_setTimerValue(u16 TimerValue);

TIMER1_enuErrorStatus_t timer1_setOutputCompareRegister1AValue(u16 OutputCompareRegisterA);

TIMER1_enuErrorStatus_t timer1_setOutputCompareRegister1BValue(u16 OutputCompareRegisterB);

TIMER1_enuErrorStatus_t timer1_setInputCaptureRegisterValue(u16 InputCaptureValue);


#endif /* __TIMER1_H__ */