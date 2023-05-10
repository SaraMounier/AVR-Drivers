/*
 * 
/*************************************************************
 * 
 * Filename: TIMER0_PWM_LEDIntensity_twoPushButtons.c
 * Description: AppFile.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/
#include "DIO.h"
#include "LCD.h"
#include "LCD_Cfg.h"
#include "SWITCH.h"
#include "TIMER.h"
#include "util\delay.h"
#define F_CPU  1000000UL

#define MAX_TIMER_VALUE    0xFF
void LED_Change_Intensity(void);
static u16 PRELOAD=0;

int main(void)
{
	DIO_Init();	
	LCD_vidInit();
	SWITCH_Init();  

	timer_setWaveformGenMode(WGM_Fast_PWM);
	timer_setCompareMatchOutputMode(OC0_FAST_PWM_NON_INVERTING_MODE);
	timer_selectClockPrescaler(CLK_DivBy8);
	timer_setCounter_TimerCompareValue(0);

    while (1) 
    { 
		LED_Change_Intensity();
		LCD_enuWriteNumber(PRELOAD)	;
		_delay_ms(50);
		LCD_enuSendCommand(LCD_CLR);
    }
}

void LED_Change_Intensity(void)
{
	static u8 INC_SwitchState=SWITCH_Released, DEC_SwitchState=SWITCH_Released;
	GET_SWITCH_State (Switches_Cfg [INC_BUTTON].Port_Num ,Switches_Cfg [INC_BUTTON].Pin_Num,&INC_SwitchState);
	GET_SWITCH_State (Switches_Cfg [DEC_BUTTON].Port_Num ,Switches_Cfg [DEC_BUTTON].Pin_Num,&DEC_SwitchState);

	if(INC_SwitchState == SWITCH_Pressed && PRELOAD < MAX_TIMER_VALUE)
	{
		PRELOAD++;
		timer_setCounter_TimerCompareValue(PRELOAD);
	}
	 else if(DEC_SwitchState == SWITCH_Pressed && PRELOAD > 0)
	{
		PRELOAD--;
		timer_setCounter_TimerCompareValue(PRELOAD);
	}
	else
	{
		timer_setCounter_TimerCompareValue(PRELOAD);
	}
}

					 