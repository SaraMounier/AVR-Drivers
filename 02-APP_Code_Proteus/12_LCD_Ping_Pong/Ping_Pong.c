/*
 * Ping_Pong.c
 *
 * Created: 3/1/2023 4:07:02 AM
 *  Author: Sara Mounier
 */ 
#include <stdlib.h>
#include "LCD.h"
#include "SWITCH.h"
#include "util/delay.h"

u8 generate_random(int l, int r) { //this will generate random number in range l and r
	u8 rand_num = (rand() % (r - l + 1)) + l;
	return rand_num;
}

u8 Ball_Y_Position=FIRST_LINE, Ball_X_Position=0;	
u8 L_RacketPosition=FIRST_LINE, R_RacketPosition=FIRST_LINE;
u8 Score_R=0,Score_L=0;
void Ping_Pong_Game(u8 Max_Score)
{
	u8 UpButtonR_SwitchState=1,UpButtonL_SwitchState=1,DownButtonR_SwitchState=1,DownButtonL_SwitchState=1;
	/*Initial screen of the game*/
	 Ball_X_Position= (generate_random(LCD_POSITION02, LCD_POSITION15));
	 LCD_enuWriteSpecialPattern  (racketL, LCD_SPECIALCHAR1, LCD_POSITION01, L_RacketPosition);
	 LCD_enuWriteSpecialPattern  (racketR, LCD_SPECIALCHAR2, LCD_POSITION16, R_RacketPosition);
	 LCD_enuWriteSpecialPattern  (Ball,    LCD_SPECIALCHAR3, Ball_X_Position , Ball_Y_Position);

/*switches control*/
while(1)
{
	LCD_enuGotoXY(LCD_POSITION07,FIRST_LINE);
	LCD_enuWriteNumber(Score_L);
	LCD_enuSendData(':');
	LCD_enuWriteNumber(Score_R);
	
	GET_SWITCH_State ( Switches_Cfg [UP_BUTTON_R].Port_Num ,  Switches_Cfg [UP_BUTTON_R].Pin_Num ,   &UpButtonR_SwitchState);
	GET_SWITCH_State ( Switches_Cfg [DOWN_BUTTON_R].Port_Num ,Switches_Cfg [DOWN_BUTTON_R].Pin_Num , &DownButtonR_SwitchState);
	GET_SWITCH_State ( Switches_Cfg [UP_BUTTON_L].Port_Num ,  Switches_Cfg [UP_BUTTON_L].Pin_Num ,   &UpButtonL_SwitchState);
	GET_SWITCH_State ( Switches_Cfg [DOWN_BUTTON_L].Port_Num ,Switches_Cfg [DOWN_BUTTON_L].Pin_Num , &DownButtonL_SwitchState);
	 
	 _delay_ms(200);
	LCD_enuSendCommand(LCD_CLR);
	if(UpButtonR_SwitchState== SWITCH_Pressed && R_RacketPosition==SECOND_LINE)
	{
		R_RacketPosition=FIRST_LINE;
	}
	else if(DownButtonR_SwitchState== SWITCH_Pressed && R_RacketPosition==FIRST_LINE)
	{
		R_RacketPosition=SECOND_LINE;
	}

    if(UpButtonL_SwitchState== SWITCH_Pressed && L_RacketPosition==SECOND_LINE)
	{
		L_RacketPosition=FIRST_LINE;
	}
	else if(DownButtonL_SwitchState== SWITCH_Pressed && L_RacketPosition==FIRST_LINE )
	{
		L_RacketPosition=SECOND_LINE;
	}
	
		
	if(Ball_Y_Position==SECOND_LINE )
	{
		Ball_Y_Position=FIRST_LINE;
		if(R_RacketPosition==FIRST_LINE && L_RacketPosition==FIRST_LINE)
		{
			Ball_X_Position = generate_random(LCD_POSITION02, LCD_POSITION15);
		}
		else if(R_RacketPosition==FIRST_LINE &&L_RacketPosition==SECOND_LINE)
		{
			Ball_X_Position = generate_random(LCD_POSITION01, LCD_POSITION15);
		}
		else if(R_RacketPosition==SECOND_LINE &&L_RacketPosition==FIRST_LINE)
		{
			Ball_X_Position= generate_random(LCD_POSITION02, LCD_POSITION16);
		}
		else if(R_RacketPosition==SECOND_LINE && L_RacketPosition==SECOND_LINE)
		{
			Ball_X_Position = generate_random(LCD_POSITION01, LCD_POSITION16);
		}
	}
	else if (Ball_Y_Position==FIRST_LINE)
	{
		Ball_Y_Position=SECOND_LINE;
		if(R_RacketPosition==FIRST_LINE && L_RacketPosition==FIRST_LINE)
		{
			Ball_X_Position = generate_random(LCD_POSITION01, LCD_POSITION16);
		}
		else if(R_RacketPosition==FIRST_LINE &&L_RacketPosition==SECOND_LINE)
		{
			Ball_X_Position=generate_random(LCD_POSITION02, LCD_POSITION16);
		}
		else if(R_RacketPosition==SECOND_LINE &&L_RacketPosition==FIRST_LINE)
		{
			Ball_X_Position=generate_random(LCD_POSITION01, LCD_POSITION15);
		}
		else if(R_RacketPosition==SECOND_LINE && L_RacketPosition==SECOND_LINE)
		{
			Ball_X_Position = generate_random(LCD_POSITION02, LCD_POSITION15);
		}
	}

	LCD_enuWriteSpecialPattern  (racketR , LCD_SPECIALCHAR2 , LCD_POSITION16, R_RacketPosition);
	LCD_enuWriteSpecialPattern  (racketL, LCD_SPECIALCHAR1, LCD_POSITION01, L_RacketPosition);
	LCD_enuWriteSpecialPattern  (Ball, LCD_SPECIALCHAR3, Ball_X_Position , Ball_Y_Position);

	/*Game Algorithm*/ 
	if((R_RacketPosition==FIRST_LINE && Ball_Y_Position==SECOND_LINE && Ball_X_Position==LCD_POSITION16)||
	   (R_RacketPosition==SECOND_LINE && Ball_Y_Position==FIRST_LINE && Ball_X_Position==LCD_POSITION16) )
	{
		LCD_enuGotoXY(LCD_POSITION08,FIRST_LINE);
		LCD_enuSendData(':');
		LCD_enuWriteNumber (++Score_R);
		if (Score_R==Max_Score)
		{
			LCD_enuSendCommand(LCD_CLR);
			LCD_enuGotoXY(LCD_POSITION07,FIRST_LINE);
			LCD_enuWriteNumber(Score_L);
			LCD_enuSendData(':');
			LCD_enuWriteNumber(Score_R);
			LCD_enuGotoXY(LCD_POSITION01,SECOND_LINE);
			LCD_enuWriteString("Left User Won!");
			break;
		}
	}
	
	if((L_RacketPosition==FIRST_LINE && Ball_Y_Position==SECOND_LINE && Ball_X_Position==LCD_POSITION01)|| 
	   (L_RacketPosition==SECOND_LINE && Ball_Y_Position==FIRST_LINE && Ball_X_Position==LCD_POSITION01) )
	{
		LCD_enuGotoXY(LCD_POSITION07,FIRST_LINE);
		LCD_enuWriteNumber (++Score_L);
		LCD_enuSendData(':');
		if (Score_L==Max_Score)
		{			
			LCD_enuSendCommand(LCD_CLR);
			LCD_enuGotoXY(LCD_POSITION07,FIRST_LINE);
			LCD_enuWriteNumber(Score_L);
			LCD_enuSendData(':');
			LCD_enuWriteNumber(Score_R);
			LCD_enuGotoXY(LCD_POSITION01,SECOND_LINE);
			LCD_enuWriteString("Right User Won!");
			break;
		}
	}
}

}
