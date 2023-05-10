/*************************************************************
 * 
 * Filename: TIMER1.c
 * Description: Source file of the TIMER1 driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "TIMER1_Cfg.h"
#include "TIMER1_Priv.h"
#include "TIMER1.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

static void set_2bits_8reg(volatile u8* REG,u8 value,u8 StartShift)
{
	u8 loc_var;
	loc_var = *(REG) & ~(CLR_2BITS_MASK<<StartShift);
	*(REG) = loc_var | (value<<StartShift);
}


// static void set_2bits_16Reg(u16 *REG,u16 value,u8 StartShift)
// {
// 	u16 loc_var;
// 	loc_var = *REG & ~(CLR_2BITS_MASK<<StartShift);
// 	*REG = loc_var | (value<<StartShift);
// }

static void set_3bits(volatile u8 *REG,u8 value,u8 StartShift)
{
	u8 loc_var;
	loc_var = *(REG) & ~(CLR_3BITS_MASK<<StartShift);
	*(REG) = loc_var | (value<<StartShift);
}


TIMER1_enuErrorStatus_t timer1_setCompareOutputMode(u8 CompareOutputMode)
{
	TIMER1_enuErrorStatus_t Loc_TIMER1ErrStatus=TIMER1_enuOK;
	set_2bits_8reg(&T1_TCCR1A,CompareOutputMode, TCCR1A_COM1A0);	
	return Loc_TIMER1ErrStatus;
}

TIMER1_enuErrorStatus_t timer1_setCLKPrescaler(u8 TIMER1_CLK_)
{
	TIMER1_enuErrorStatus_t Loc_TIMER1ErrStatus=TIMER1_enuOK;
	set_3bits(&T1_TCCR1B,TIMER1_CLK_,TCCR1B_CS10);
	return Loc_TIMER1ErrStatus;
}

TIMER1_enuErrorStatus_t timer1_setWaveformGenMode(u8 WaveformGenMode)
{
	TIMER1_enuErrorStatus_t Loc_TIMER1ErrStatus=TIMER1_enuOK;
	set_2bits_8reg(&T1_TCCR1A,(WaveformGenMode & 0b0011),TCCR1A_WGM10);
	set_2bits_8reg(&T1_TCCR1B,(WaveformGenMode>>2),TCCR1B_WGM12 );

	return Loc_TIMER1ErrStatus;	
}

TIMER1_enuErrorStatus_t timer1_setTimerValue(u16 TimerValue)
{
	TIMER1_enuErrorStatus_t Loc_TIMER1ErrStatus=TIMER1_enuOK;
	T1_TCNT1L = TimerValue;
	return Loc_TIMER1ErrStatus;	
}

TIMER1_enuErrorStatus_t timer1_setOutputCompareRegister1AValue(u16 OutputCompareRegisterA)
{
	TIMER1_enuErrorStatus_t Loc_TIMER1ErrStatus=TIMER1_enuOK;	
	T1_OCR1AL=OutputCompareRegisterA;
	return Loc_TIMER1ErrStatus;	
}

TIMER1_enuErrorStatus_t timer1_setOutputCompareRegister1BValue(u16 OutputCompareRegisterB)
{
	TIMER1_enuErrorStatus_t Loc_TIMER1ErrStatus=TIMER1_enuOK;	
	T1_OCR1BL=OutputCompareRegisterB;
	return Loc_TIMER1ErrStatus;	
}

TIMER1_enuErrorStatus_t timer1_setInputCaptureRegisterValue(u16 InputCaptureValue)
{
	TIMER1_enuErrorStatus_t Loc_TIMER1ErrStatus=TIMER1_enuOK;	
	T1_ICR1L =InputCaptureValue;
	return Loc_TIMER1ErrStatus;	
}

