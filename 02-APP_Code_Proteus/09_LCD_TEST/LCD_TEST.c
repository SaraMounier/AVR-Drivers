/*
 * LDC_Driver.c
 *
 * Created: 2/10/2023 3:57:00 PM
 * Author : Sara Mounier
 */ 
#include "LCD.h"
#include "LCD_Cfg.h"
#include "avr/delay.h"
int main(void)

{
	DIO_Init();
	LCD_vidInit();
	
	u8 i=0;
	while(i<16)
	{ 	
		LCD_enuGotoXY(0,FIRST_LINE);	
		LCD_enuWriteString("Hello Asteroids ITI-43 !");
		LCD_enuGotoXY(0,SECOND_LINE);
		LCD_enuWriteString("Look At My Special Characters !");
		LCD_enuSendCommand(SHIFT_DISPLAY_RIGHT_CURSOR_FOLLOWS);
		i++;
	}
	 
	LCD_enuSendCommand(LCD_CLR);
	LCD_enuWriteSpecialPattern  (Human      , LCD_SPECIALCHAR1, LCD_POSITION01, FIRST_LINE);
	LCD_enuWriteSpecialPattern  (Cat        , LCD_SPECIALCHAR2, LCD_POSITION02, FIRST_LINE);
	LCD_enuWriteSpecialPattern  (Paw        , LCD_SPECIALCHAR3, LCD_POSITION03, FIRST_LINE);
	LCD_enuWriteSpecialPattern  (Silent     , LCD_SPECIALCHAR4, LCD_POSITION04, FIRST_LINE);
	LCD_enuWriteSpecialPattern  (Music      , LCD_SPECIALCHAR5, LCD_POSITION05, SECOND_LINE);
	LCD_enuWriteSpecialPattern  (Plug       , LCD_SPECIALCHAR6, LCD_POSITION06, SECOND_LINE);
	LCD_enuWriteSpecialPattern  (Face       , LCD_SPECIALCHAR7, LCD_POSITION07, SECOND_LINE);
	LCD_enuWriteSpecialPattern  (FilledHeart, LCD_SPECIALCHAR8, LCD_POSITION08, SECOND_LINE);

    while (1);

}