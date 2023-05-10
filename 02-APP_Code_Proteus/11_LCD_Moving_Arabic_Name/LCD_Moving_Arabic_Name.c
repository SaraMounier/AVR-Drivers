/*
 * LCD_MovingName_BB.c
 *
 * Created: 2/24/2023 11:22:00 PM
 * Author : Sara Mounier
 */ 

#include <util/delay.h>
#include "STD_TYPES.h"
#include "LCD.h"
#include "DIO.h"
#include "SWITCH.h"

int main(void)
{
	u8 LCD_X_POSITION=LCD_POSITION01,LCD_Y_POSITION=FIRST_LINE;
	u8 Up_Button_state=0,Down_Button_state=0,Left_Button_state=0,Right_Button_state=0;    /* Replace with your application code */
	DIO_Init();
	LCD_vidInit();
	SWITCH_Init();
    while (1) 
    {
		
		GET_SWITCH_State (Switches_Cfg[UP_BUTTON].Port_Num,Switches_Cfg[UP_BUTTON].Pin_Num ,     &Up_Button_state);
		GET_SWITCH_State (Switches_Cfg[DOWN_BUTTON].Port_Num,Switches_Cfg[DOWN_BUTTON].Pin_Num,  &Down_Button_state);
		GET_SWITCH_State (Switches_Cfg[LEFT_BUTTON].Port_Num,Switches_Cfg[LEFT_BUTTON].Pin_Num,  &Left_Button_state);
		GET_SWITCH_State (Switches_Cfg[RIGHT_BUTTON].Port_Num,Switches_Cfg[RIGHT_BUTTON].Pin_Num, &Right_Button_state);
				
			if(Up_Button_state ==SWITCH_Pressed  && LCD_Y_POSITION == SECOND_LINE) 
			{
				LCD_Y_POSITION=FIRST_LINE;
			}
			else if(Down_Button_state==SWITCH_Pressed && LCD_Y_POSITION == FIRST_LINE)
			{
				LCD_Y_POSITION=SECOND_LINE;
			}
			 if(Right_Button_state==SWITCH_Pressed && (LCD_X_POSITION) <= (LCD_POSITION16 - 4))
			{ 
				 ++LCD_X_POSITION;
			}
			else if(Left_Button_state==SWITCH_Pressed && (LCD_X_POSITION) >= (LCD_POSITION01 +1))
			{  
				-- LCD_X_POSITION;
			}
			
			LCD_enuGotoXY(LCD_X_POSITION, LCD_Y_POSITION);
			LCD_enuWriteSpecialPattern  (S,  LCD_SPECIALCHAR1, LCD_X_POSITION+3, LCD_Y_POSITION);
			LCD_enuWriteSpecialPattern  (A,  LCD_SPECIALCHAR2, LCD_X_POSITION+2, LCD_Y_POSITION);
			LCD_enuWriteSpecialPattern  (R,  LCD_SPECIALCHAR3, LCD_X_POSITION+1, LCD_Y_POSITION);
			LCD_enuWriteSpecialPattern  (H,  LCD_SPECIALCHAR4, LCD_X_POSITION,   LCD_Y_POSITION);	 			
			_delay_ms(100);
			LCD_enuSendCommand(LCD_CLR);			
    }
	return 0;
}

