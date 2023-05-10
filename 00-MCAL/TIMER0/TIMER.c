/*************************************************************
 * 
 * Filename: TIMER.c
 * Description: Source file of the TIMER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/


#include "TIMER.h"
#include "STD_TYPES.h"
  /*Call Back Functions*/
 static void (*TIMER0_OverFlowCallBackFunction) (void)=NULL;
 static void (*TIMER0_OutputCompareMatchCallBackFunction) (void)=NULL; 
 /**************/
 
 void timer0_VidInit(void)
 {
	timer_setWaveformGenMode(WAVE_FORM_GEN_MODE_CGF);
	timer_setCompareMatchOutputMode(OUTUT_COMPARE_MATCH_MODE_CFG);
 }

TIMER_enuErrorStatus_t timer_setForceOutputCompare(void)
{
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus;
	TCCR0 |= 1<<FOC0;
	Loc_enuTimerErrorStatus=TIMER_enuOk;
	return Loc_enuTimerErrorStatus;
}

TIMER_enuErrorStatus_t timer_clearForceOutputCompare(void)
{
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus;
	TCCR0 &= ~(1<<FOC0);
	Loc_enuTimerErrorStatus=TIMER_enuOk;
	return Loc_enuTimerErrorStatus;
}

TIMER_enuErrorStatus_t timer_setWaveformGenMode(u8 WGM_)
{
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus;
	if(WGM_==WGM_NORMAL || WGM_== WGM_PWM_PHASE_CORRECT || WGM_== WGM_CTC || WGM_== WGM_Fast_PWM) 
	{
		if(WGM_==WGM_PWM_PHASE_CORRECT || WGM_==WGM_Fast_PWM)
		{
			 timer_clearForceOutputCompare();
		}
		u8 Loc_RegCpy=TCCR0 & WGM_CLR_MASK;
		Loc_RegCpy |=	WGM_;
		TCCR0 =Loc_RegCpy;
		Loc_enuTimerErrorStatus=TIMER_enuOk;
	}
	else
	{
		Loc_enuTimerErrorStatus=TIMER_enuInvalidParameters;
	}
	return Loc_enuTimerErrorStatus;
}

TIMER_enuErrorStatus_t timer_setCompareMatchOutputMode(u8 OC0_)
{
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus;
	/*check if the waveform mode is not PWM*/
	if (((TCCR0>>WGM00) & 0x01) == NON_PWM_MODE)
	{
		if(OC0_== OC0_NON_PWM_DISCONNECTED || OC0_== OC0_NON_PWM_TOGGLE_ON_COMPARE_MATCH ||
		OC0_== OC0_NON_PWM_CLEAR_ON_COMPARE_MATCH || OC0_== OC0_NON_PWM_SET_ON_COMPARE_MATCH )
		{
			u8 Loc_RegCpy=TCCR0 & ~(_2BIT_CLR_MASK <<COM00);
			Loc_RegCpy |= 	OC0_ <<	COM00 ;
			TCCR0 =	Loc_RegCpy;
			Loc_enuTimerErrorStatus=TIMER_enuOk;
		}
		else
		{
			Loc_enuTimerErrorStatus=TIMER_enuInvalidParameters;
		}
	}
		/*check if the waveform mode is PWM*/
	else if (((TCCR0>>WGM00) & 0x01) == PWM_MODE)
	{
		if( OC0_== OC0_FAST_PWM_DISCONNECTED || OC0_==OC0_FAST_PWM_NON_INVERTING_MODE || OC0_==OC0_FAST_PWM_INVERTING_MODE
		    || OC0_==OC0_PHASE_COR_PWM_DISCONNECTED || OC0_==OC0_PHASE_COR_PWM_CLEAR_ON_COMP_MATCH_UP_CNT || OC0_==OC0_PHASE_COR_PWM_SET_ON_COMP_MATCH_DOWN_CNT
		    || OC0_==OC0_PHASE_COR_PWM_SET_ON_COMP_MATCH_UP_CNT || OC0_==OC0_PHASE_COR_PWM_CLEAR_ON_COMP_MATCH_DOWN_CNT )
		{
			u8 Loc_RegCpy = TCCR0 & ~(_2BIT_CLR_MASK <<COM00);
			Loc_RegCpy |= OC0_ << COM00 ;
			TCCR0 =	Loc_RegCpy;
			Loc_enuTimerErrorStatus=TIMER_enuOk;
		}
		else
		{
			Loc_enuTimerErrorStatus=TIMER_enuInvalidParameters;
		}
	}
	else
	{
		Loc_enuTimerErrorStatus=TIMER_enuInvalidParametersWithMode;
	}	
	return 	Loc_enuTimerErrorStatus;
}
	
TIMER_enuErrorStatus_t timer_selectClockPrescaler(u8 CLK_)
{
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus;
	if( CLK_== NO_CLK_STOP || CLK_== CLK_NO_PRESCALER || CLK_== CLK_DivBy8 || CLK_== CLK_DivBy64 
		|| CLK_== CLK_DivBy256 || CLK_== CLK_DivBy1024 || CLK_== CLK_EXT_FALLING_EDGE || CLK_== CLK_EXT_RISING_EDGE )
	{
		u8 Loc_RegCpy = TCCR0 & ~(_3BIT_CLR_MASK << CS00);
		Loc_RegCpy |= CLK_ << CS00;
		TCCR0 =	Loc_RegCpy;
		Loc_enuTimerErrorStatus=TIMER_enuOk;
	}
	else
	{
		Loc_enuTimerErrorStatus=TIMER_enuInvalidParameters;		
	}
	return Loc_enuTimerErrorStatus;	
}

TIMER_enuErrorStatus_t timer_setCounter_TimerValue(u8 Counter_Timer_Value)
{
	TIMER_enuErrorStatus_t 	Loc_enuTimerErrorStatus=TIMER_enuNOk;
	TCNT0= Counter_Timer_Value;
	return Loc_enuTimerErrorStatus;
}

TIMER_enuErrorStatus_t timer_setCounter_TimerCompareValue(u8 OutputCompareValue)
{
	TIMER_enuErrorStatus_t 	Loc_enuTimerErrorStatus=TIMER_enuNOk;
	OCR0=  OutputCompareValue;
	return Loc_enuTimerErrorStatus;

}

TIMER_enuErrorStatus_t timer_enableInterrupt(u8 INTERRUPT_ON_)
{			   
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus;
	if(INTERRUPT_ON_ == INTERRUPT_ON_COMPARE_MATCH || INTERRUPT_ON_ == INTERRUPT_ON_OVERFLOW)
	{
	   TIMSK &= ~(1<<INTERRUPT_ON_) ;
	   TIMSK |= (1<<INTERRUPT_ON_) ;
	   Loc_enuTimerErrorStatus=TIMER_enuOk;
	}
	else
	{
		Loc_enuTimerErrorStatus=TIMER_enuInvalidParameters;
	}
		return Loc_enuTimerErrorStatus;
}

TIMER_enuErrorStatus_t timer_disableInterrupt(u8 INTERRUPT_ON_)
{
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus;
	if(INTERRUPT_ON_ == INTERRUPT_ON_COMPARE_MATCH || INTERRUPT_ON_ == INTERRUPT_ON_OVERFLOW)
	{
		TIMSK &= ~(1<<INTERRUPT_ON_) ;
		Loc_enuTimerErrorStatus=TIMER_enuOk;
	}
	else
	{
		Loc_enuTimerErrorStatus=TIMER_enuInvalidParameters;
	}
	return Loc_enuTimerErrorStatus;
	
}

TIMER_enuErrorStatus_t timer_setTime(u32 time_millisecs, u32* No_OverFlows, u32 *preload)
{
	TIMER_enuErrorStatus_t Loc_enuTimerErrorStatus=TIMER_enuOk;
	if( (((TCCR0 >>WGM01) & 0b01) ==0) && (((TCCR0>>WGM00) & 0b01) ==0) )
	{
		u32 prescaler= SELECTED_PRESCALER;
		switch (prescaler){
			case (CLK_NO_PRESCALER):
			prescaler=1;
			break;
			case (CLK_DivBy8):
			prescaler=8;
			break;
			case (CLK_DivBy64):
			prescaler=64;
			break;
			case (CLK_DivBy256):
			prescaler=256;
			break;
			case (CLK_DivBy1024):
			prescaler=1024;
			break;
			case (CLK_EXT_FALLING_EDGE):
			case (CLK_EXT_RISING_EDGE):
			prescaler=1;
			break;		
		}
		f64 timer_clk_frequency = (256.0*1000)/(MC_frequency/(prescaler)) ;
		f32 Loc_NoOverFlows= time_millisecs /timer_clk_frequency ;
		u32 novint_helper =	 Loc_NoOverFlows;
		f32 preload_helper= (1 - (Loc_NoOverFlows - novint_helper)) * 255;
		*No_OverFlows= novint_helper;
		*preload=preload_helper;
		TCNT0=255-(*preload);
	}
	else{Loc_enuTimerErrorStatus=TIMER_enuInvalidMode;}
	
	return Loc_enuTimerErrorStatus;
}

void timer0_setOverflowCallBackFun(void (*CpyTimer0CallBackFun)(void))
{
	if(CpyTimer0CallBackFun !=NULL)
	{
		TIMER0_OverFlowCallBackFunction=CpyTimer0CallBackFun;
	}
}
  
void timer0_setOutputCompareMatchCallBackFun(void (*CpyTimer0CallBackFun)(void))
{
	if(CpyTimer0CallBackFun !=NULL)
	{
		TIMER0_OutputCompareMatchCallBackFunction=CpyTimer0CallBackFun;
	}
}

 void __vector_11 (void) __attribute__ ((signal));
 
 void __vector_11 (void)
 {
	if(TIMER0_OverFlowCallBackFunction!=NULL)
	{
		TIMER0_OverFlowCallBackFunction();
	}
}


void __vector_10 (void) __attribute__ ((signal));

void __vector_10 (void)
{
	 if(TIMER0_OutputCompareMatchCallBackFunction!=NULL)
	 {
		 TIMER0_OutputCompareMatchCallBackFunction();
	 }
}
