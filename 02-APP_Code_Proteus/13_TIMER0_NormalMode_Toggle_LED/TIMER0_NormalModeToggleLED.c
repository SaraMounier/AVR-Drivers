/*
 * File Name: main.c
 * Description: Try APIs of the TIMER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 *
 */
#include "STD_TYPES.h"
#include "DIO.h"
#include "GINT.h"
#include "TIMER.h"
#include "LED.h"
#include "LCD.h"
#include "util/delay.h"

  void Timer0_overflow(void);
  

 u32 NO_OVER_FLOWS, PRELOAD;
 u32 TIME_INMILLI_SECS=2000;
 u8 cpypreload;

int main(void)
{
	DIO_Init();
	GI_enuInit();
	LCD_vidInit();

	timer_setWaveformGenMode(WGM_NORMAL);
	timer_setCompareMatchOutputMode(OC0_NON_PWM_DISCONNECTED); 
	timer_selectClockPrescaler(CLK_DivBy8); 
	timer_enableInterrupt(INTERRUPT_ON_OVERFLOW);
	timer_setTime(TIME_INMILLI_SECS, &NO_OVER_FLOWS, &PRELOAD);
	cpypreload=PRELOAD;
	timer0_setOverflowCallBackFun(Timer0_overflow);

    while (1)
	{
		LCD_enuWriteNumber(NO_OVER_FLOWS) ;
		_delay_ms(2000);
		LCD_enuSendCommand(LCD_CLR)	 ;
		LCD_enuWriteNumber(PRELOAD);
		_delay_ms(2000);
		LCD_enuSendCommand(LCD_CLR)	 ;
	} 
}

void Timer0_overflow(void)
{
	static int counter;
	static int LedState=0;
	if(counter<NO_OVER_FLOWS)
	{
		counter++;
	}
	else if(counter==NO_OVER_FLOWS)
	{
		LedState ^=1;
		if(LedState==1)  
		{
			Turn_LED_ON ( DIO_enuPortC , DIO_enuPin0);
		}
		if(LedState==0)
		{
			Turn_LED_OFF ( DIO_enuPortC , DIO_enuPin0);
		}	
		counter=0;
		//timer_setCounter_TimerValue( cpypreload);
		timer_setCounter_TimerCompareValue(cpypreload);
	}
}