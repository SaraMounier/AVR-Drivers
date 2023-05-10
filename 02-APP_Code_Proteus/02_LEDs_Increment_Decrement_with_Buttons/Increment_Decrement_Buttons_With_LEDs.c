#include "STD_TYPES.H"
#include "Increment_Decrement_Buttons_With_LEDs.h"
#include "DIO.h"
#include "LED.h"
#include "SWITCH.h"
#include "SWITCH_Cfg.h"
//#include "SWITCH_Cfg.c" //by3ml multi definition error take care
#include "util/delay.h"
#define F_CPU 1000000UL

void Icrement_Decrement_Buttons(u8 Number_of_Leds, DIO_tenuPorts LEDS_PortNum,LED_tenuLedNumber Start_PinNumber,LED_tenuLedNumber End_PinNumber,u8 ButtonsNumber)
{	DIO_Init();
	SWITCH_Init();
	u8 Increment_Switch_State=0,Decrement_Switch_State=0;
	u8 LED_Current_ON=Start_PinNumber;
	while(1){
		
			// Wait until both buttons are released
			
			while(1) {
				GET_SWITCH_State (Switches_Cfg[Increment_Button].Port_Num ,Switches_Cfg[Increment_Button].Pin_Num, & Increment_Switch_State);
				GET_SWITCH_State (Switches_Cfg[Decrement_Button].Port_Num ,Switches_Cfg[Decrement_Button].Pin_Num, & Decrement_Switch_State);
				if (Increment_Switch_State==0 && Decrement_Switch_State==0) {
					break;	
				}
			}
			
			// Check if one button is pressed
				// If true, increment/decrement, then repeat
		
		
			while(1) {
				GET_SWITCH_State (Switches_Cfg[Increment_Button].Port_Num ,Switches_Cfg[Increment_Button].Pin_Num, & Increment_Switch_State);
				GET_SWITCH_State (Switches_Cfg[Decrement_Button].Port_Num ,Switches_Cfg[Decrement_Button].Pin_Num, & Decrement_Switch_State);
				if (Increment_Switch_State==1) {
					if(LED_Current_ON < Number_of_Leds && LED_Current_ON>=0)
					{
						Turn_LED_ON ( LEDS_PortNum , LED_Current_ON);
						LED_Current_ON ++;
					}
					break;
				} else if (Decrement_Switch_State == 1) {
					if(LED_Current_ON <= Number_of_Leds &&LED_Current_ON>0 )
					{
						Turn_LED_OFF ( LEDS_PortNum , LED_Current_ON-1);
						LED_Current_ON --;
					}
					break;
				}
			}
		}
}
