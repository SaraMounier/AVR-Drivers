#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SWITCH.h"
#include "SWITCH_Cfg.h"
#include "DIO_piv.h"
#include "DIO.h"
#include "util/delay.h"
#define F_CPU 1000000UL
# define DEBOUNCING_CYCLES_NUMEBER 5


SWITCH_tenuErrorStatus SWITCH_Init (void){
	u8 i;
	SWITCH_tenuErrorStatus Loc_enuReturnSwitch ;
	for(i=0;i< Switches_Number;i++)
	{
		if(Switches_Cfg[i].Port_Num < DIO_enuPortsNumber)
		{
			if(Switches_Cfg[i].Pin_Num < DIO_enuPinsNumber)
		{Loc_enuReturnSwitch =DIO_enuOK;
			switch(Switches_Cfg[i].Port_Num)
			{ 
				case DIO_enuPortA:
				if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Up)
				{
					DIO_EnablePinPullUp(DIO_enuPortA,Switches_Cfg[i].Pin_Num);
				}
				else if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Down)
				{
					CLR_BIT(PORTA,Switches_Cfg[i].Pin_Num);	
				}
				else {/*error in pull up or pull down value*/}
				break;
				
				case DIO_enuPortB:
				if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Up)
				{
					DIO_EnablePinPullUp(DIO_enuPortB,Switches_Cfg[i].Pin_Num);
				}
				else if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Down)
				{
					CLR_BIT(PORTB,Switches_Cfg[i].Pin_Num);	
				}
				else {/*error in pull up or pull down value*/}

				break;
			
				case DIO_enuPortC:
				if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Up)
				{
					DIO_EnablePinPullUp(DIO_enuPortC,Switches_Cfg[i].Pin_Num);
				}
				else if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Down)
				{
					CLR_BIT(PORTC,Switches_Cfg[i].Pin_Num);	
				}
				else {/*error in pull up or pull down value*/}
				
				break;
				
				case DIO_enuPortD:
				if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Up)
				{
					DIO_EnablePinPullUp(DIO_enuPortD,Switches_Cfg[i].Pin_Num);
				}
				else if(Switches_Cfg[i].Active_Status==SWITCH_Pull_Down)
				{
					CLR_BIT(PORTD,Switches_Cfg[i].Pin_Num);	
				}	
				else {/*error in pull up or pull down value*/}
				
				break;
			}
		}
		else 
		{
			Loc_enuReturnSwitch=DIO_InvalidPinNumber;
		}
			
		}else 
		{
			Loc_enuReturnSwitch=DIO_InvalidPortNumber;
		}
		
				}
				
return Loc_enuReturnSwitch; 	
}

SWITCH_tenuErrorStatus GET_SWITCH_State (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber, DIO_tenuPinValue *Add_u8ptrSwitchState)
{   
	SWITCH_tenuErrorStatus Loc_enuReturnSwitch ;
	u8 Loc_Switch_Current_PinValue=SWITCH_Released;
	u8 Loc_Switch_Prev_PinValue=SWITCH_Released;
	u8 Debouncing_Iterator=0;
	//u8 Loc_uPinNumberIterator;
	
	    //for (Loc_uPinNumberIterator = 0; Loc_uPinNumberIterator < SwitchesNumber; Loc_uPinNumberIterator++) {
		if(Switches_Cfg[Cpy_enuPinNumber].Port_Num == Cpy_enuPortNumber)
		{
			if(Switches_Cfg[Cpy_enuPinNumber].Pin_Num == Cpy_enuPinNumber)
			{
				Loc_enuReturnSwitch=DIO_enuOK;
				
				Loc_enuReturnSwitch=DIO_GetPinVal ( Cpy_enuPortNumber , Cpy_enuPinNumber, & Loc_Switch_Prev_PinValue);

					while(Debouncing_Iterator<DEBOUNCING_CYCLES_NUMEBER)
					{
					_delay_ms(5);
					Loc_enuReturnSwitch=DIO_GetPinVal ( Cpy_enuPortNumber , Cpy_enuPinNumber, & Loc_Switch_Current_PinValue);
					if(Loc_Switch_Current_PinValue == Loc_Switch_Prev_PinValue)
					{
						Debouncing_Iterator ++;
					}
					else
					{
						Debouncing_Iterator= 0;
					}
					Loc_Switch_Prev_PinValue=Loc_Switch_Current_PinValue;

					}
					*Add_u8ptrSwitchState = Loc_Switch_Current_PinValue  ^  Switches_Cfg[Cpy_enuPinNumber].Active_Status;
				}
		else 
		{
			Loc_enuReturnSwitch=DIO_InvalidPinNumber;
		}
			
		}
		else 
		{
			Loc_enuReturnSwitch=DIO_InvalidPortNumber;
		}
		
		return Loc_enuReturnSwitch; 	
	
	}


/*
SWITCH_tenuErrorStatus GET_SWITCH_State (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber, DIO_tenuPinValue* Add_u8ptrSwitchState)
{
SWITCH_tenuErrorStatus Loc_enuReturnSwitch = SWITCH_enuOK;
  DIO_tenuPinValue Loc_getPinValue;
  DIO_GetPinVal ( Cpy_enuPortNumber , Cpy_enuPinNumber,  & Loc_getPinValue);
  * Add_u8ptrSwitchState=  Loc_getPinValue  ^  Switches_Cfg[Cpy_enuPinNumber].Active_Status;
  return Loc_enuReturnSwitch;
}
*/