/*************************************************************
 * 
 * Filename: TIMER.h
 * Description: Header (interface) file of the TIMER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__
#include "STD_TYPES.h"
#include "TIMER_Cfg.h"
#include "TIMER_Priv.h"


typedef enum
{
	TIMER_enuOk,
	TIMER_enuNOk,
	TIMER_enuNullPtr,
	TIMER_enuInvalidParameters,
	TIMER_enuInvalidParametersWithMode,
	TIMER_enuInvalidMode,
}TIMER_enuErrorStatus_t;

typedef enum
{
	CS00,
	CS01,
	CS02,
	WGM01,
	COM00,
	COM01,
	WGM00,
	FOC0,
}TCCR0_Bits;

  /*timer_setWaveformGenMode Input Parameters*/
#define WGM_NORMAL				0b00000000
#define WGM_PWM_PHASE_CORRECT	0b01000000
#define WGM_CTC					0b00001000
#define WGM_Fast_PWM			0b01001000

#define WGM_CLR_MASK			0b10110111


/*timer_setWaveformGenMode Input Parameters  */
#define NON_PWM_MODE 0
#define PWM_MODE 1
#define _2BIT_CLR_MASK 0b11

#define OC0_NON_PWM_DISCONNECTED			0b00
#define OC0_NON_PWM_TOGGLE_ON_COMPARE_MATCH	0b01
#define OC0_NON_PWM_CLEAR_ON_COMPARE_MATCH	0b10
#define OC0_NON_PWM_SET_ON_COMPARE_MATCH	0b11

#define OC0_FAST_PWM_DISCONNECTED			0b00
#define OC0_FAST_PWM_NON_INVERTING_MODE		0b10
#define OC0_FAST_PWM_INVERTING_MODE			0b11

#define OC0_PHASE_COR_PWM_DISCONNECTED					0b00
#define OC0_PHASE_COR_PWM_CLEAR_ON_COMP_MATCH_UP_CNT	0b10
#define OC0_PHASE_COR_PWM_SET_ON_COMP_MATCH_DOWN_CNT	0b10

#define OC0_PHASE_COR_PWM_SET_ON_COMP_MATCH_UP_CNT		0b11
#define OC0_PHASE_COR_PWM_CLEAR_ON_COMP_MATCH_DOWN_CNT	0b11

#define _3BIT_CLR_MASK		 (0b111)
#define	NO_CLK_STOP			 0b000
#define	CLK_NO_PRESCALER	 0b001
#define CLK_DivBy8			 0b010
#define CLK_DivBy64			 0b011
#define CLK_DivBy256		 0b100
#define CLK_DivBy1024		 0b101
#define CLK_EXT_FALLING_EDGE 0b110
#define CLK_EXT_RISING_EDGE  0b111

#define INTERRUPT_ON_COMPARE_MATCH 1
#define INTERRUPT_ON_OVERFLOW      0


void timer0_VidInit(void);
/*
Note: The FOC0 bit is only active when the WGM00 bit specifies a non-PWM mode.
	  When writing a logical one to the FOC0 bit, an immediate compare match is forced on the Waveform Generation unit.
      The value present in the COM01:0 bits that determines the effect of the forced compare.
*/
TIMER_enuErrorStatus_t timer_setForceOutputCompare(void);
TIMER_enuErrorStatus_t timer_clearForceOutputCompare(void);

/*
Description: Control the counting sequence of the counter.
Input Parameters:WGM_NORMAL, WGM_PWM_PHASE_CORRECT, WGM_CTC, WGM_Fast_PWM
*/
TIMER_enuErrorStatus_t timer_setWaveformGenMode(u8 WGM_);


/*
Description: control the Output Compare pin (OC0) behavior. 
Input Parameters: 
Compare Output Mode, non-PWM Mode: OC0_DISCONNECTED, OC0_TOGGLE_ON_COMPARE_MATCH, OC0_CLEAR_ON_COMPARE_MATCH, OC0_SET_ON_COMPARE_MATCH
Compare Output Mode, Fast PWM Mode:	OC0_FAST_PWM_DISCONNECTED, OC0_FAST_PWM_NON_INVERTING_MODE, OC0_FAST_PWM_INVERTING_MODE
Compare Output Mode, Phase Correct PWM Mode: OC0_PHASE_COR_PWM_DISCONNECTED, OC0_PHASE_COR_PWM_CLEAR_ON_COMP_MATCH_UP_CNT, 
OC0_PHASE_COR_PWM_SET_ON_COMP_MATCH_DOWN_CNT, OC0_PHASE_COR_PWM_SET_ON_COMP_MATCH_UP_CNT, OC0_PHASE_COR_PWM_CLEAR_ON_COMP_MATCH_DOWN_CNT
*/
TIMER_enuErrorStatus_t timer_setCompareMatchOutputMode(u8 OC0_);

/*
Description:Select the Clock source to be used by the Timer/Counter.
Options: NO_CLK_STOP, CLK_NO_PRESCALER, CLK_DivBy8,CLK_DivBy64, CLK_DivBy256, CLK_DivBy1024 ,
		 CLK_EXT_FALLING_EDGE, CLK_EXT_RISING_EDGE.
*/
TIMER_enuErrorStatus_t timer_selectClockPrescaler(u8 CLK_);

/*
 Description:Set Counter/Timer Value 
 Note: Writing to the TCNT0 Register blocks (removes) the compare
 match on the following timer clock. Modifying the counter (TCNT0) while the counter is running,
 introduces a risk of missing a compare match between TCNT0 and the OCR0 Register.
 Input Parameters : Output Counter/Timer value you want
*/
TIMER_enuErrorStatus_t timer_setCounter_TimerValue(u8 Counter_Timer_Value);

/*
 Description:The Output Compare Register contains an 8-bit value that is continuously compared with the counter value (TCNT0).
 A match can be used to generate an output compare interrupt, or to generate a waveform output on the OC0 pin.
 Input Parameters : Output Compare value  you want
*/
TIMER_enuErrorStatus_t timer_setCounter_TimerCompareValue(u8 OutputCompareValue);

/*
 The corresponding interrupt is executed if a compare match in Timer/Counter0 occurs, that is, when the OCF0 bit is set in the Timer/Counter Interrupt Flag Register – TIFR.
 The corresponding interrupt is executed if an overflow in Timer/Counter0 occurs, that is, when the TOV0 bit is set in the Timer/Counter Interrupt Flag Register – TIFR.
 Options: INTERRUPT_ON_COMPARE_MATCH, INTERRUPT_ON_OVERFLOW 
*/								   /*check the corresponding flag */
TIMER_enuErrorStatus_t timer_enableInterrupt(u8 INTERRUPT_ON_);

/**/
TIMER_enuErrorStatus_t timer_setTime(u32 time_millisecs, u32* No_OverFlows, u32 *preload);



#endif /* __TIMER_H__ */