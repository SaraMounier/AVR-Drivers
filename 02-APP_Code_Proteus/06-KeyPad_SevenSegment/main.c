/*
 * KeyPad_Driver.c
 *
 * Created: 1/31/2023 11:30:16 AM
 * Author: Sara Mounier
 */ 

#include <avr/io.h>
#include "STD_TYPES.h"
#include "KEYPAD.h"
#include "KEYPAD_Cfg.h"
#include "Seven_Segment.h"
#include "LED.h"
#include "avr/delay.h"


int main(void)
{
    /* Replace with your application code */
	DIO_Init();
    while (1) 
    {
	 	 u8 Pressed_Key;
		KP_GetPressedKey( & Pressed_Key);
		switch (Pressed_Key)
		{
			case '0':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,ZERO);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
				 
			case '1':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,ONE);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case '2':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,TWO);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case '3':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,THREE);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;

			case '4':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,FOUR);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;																									 

			case '5':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,FIVE);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case '6':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,SIX);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case '7':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,SEVEN);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case '8':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,EIGHT);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case '9':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,NINE);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case 'A':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,TEN);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case 'B':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,ELEVEN);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case 'C':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,THERTEEN);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			
			case 'D':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,FOURTEEN);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;			
			
			case '*':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,FIFTEEN);
			_delay_ms(200);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			/*
			case '#':
			Turn_Group_of_LEDs_ON ( SEV_SEG_PORT,TWO);
			_delay_ms(2000);
			Turn_Port_of_LEDs_OFF(SEV_SEG_PORT);
			break;
			*/
		}

	}
		return 0;

}