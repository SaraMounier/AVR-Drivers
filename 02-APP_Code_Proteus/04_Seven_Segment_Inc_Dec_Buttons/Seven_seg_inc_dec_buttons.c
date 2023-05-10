#include "STD_TYPES.H"
#include "Seven_seg_inc_dec_buttons.h"
#include "DIO.h"
#include "LED.h"
#include "LED_Cfg.h"
#include "Seven_Segment.h"
#include "SWITCH.h"
#include "SWITCH_Cfg.h"
#include "util/delay.h"
#define F_CPU 1000000UL


void Seven_Segment_Increment_Decrement(u8 Min_Number,u8 Max_Number){

	u8 Seven_Segment_Values[16]={ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, THERTEEN, FOURTEEN, FIFTEEN};
	u8 Increment_Switch_State=0,Decrement_Switch_State=0;
	u8 Current_Number=Min_Number;

	// Wait until both buttons are released
	while (1) {	
		while(1) {
			Turn_Group_of_LEDs_ON (DIO_enuPortA,Seven_Segment_Values[Current_Number]);
			GET_SWITCH_State (Switches_Cfg[Increment_Button].Port_Num ,Switches_Cfg[Increment_Button].Pin_Num, & Increment_Switch_State);
			GET_SWITCH_State (Switches_Cfg[Decrement_Button].Port_Num ,Switches_Cfg[Decrement_Button].Pin_Num, & Decrement_Switch_State);
			if (Increment_Switch_State==0 && Decrement_Switch_State==0) {
				break;
			}
		}
		
		// Check if one button is pressed
		// If true, increment/decrement, then repeat
		
		
		while(1)
		{
			GET_SWITCH_State (Switches_Cfg[Increment_Button].Port_Num ,Switches_Cfg[Increment_Button].Pin_Num, & Increment_Switch_State);
			GET_SWITCH_State (Switches_Cfg[Decrement_Button].Port_Num ,Switches_Cfg[Decrement_Button].Pin_Num, & Decrement_Switch_State);
			
			if (Increment_Switch_State==1)
			{
				if(Current_Number < Max_Number && Current_Number >= Min_Number)
				{ 
					Turn_Group_of_LEDs_ON (DIO_enuPortA,Seven_Segment_Values[++Current_Number]);
					//i++;
				}
				break;
			}
			else if (Decrement_Switch_State == 1)
			{
				if(Current_Number <= Max_Number && Current_Number > Min_Number)
				{
					Turn_Group_of_LEDs_ON (DIO_enuPortA,Seven_Segment_Values[--Current_Number]);
					//i--;
				}
				break;
			}
		}
	}
}