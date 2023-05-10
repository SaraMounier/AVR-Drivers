/*
 * LCD_PingPongGame.c
 *
 * Created: 3/1/2023 3:55:12 AM
 * Author : Sara Mounier
 */ 
#include "Ping_Pong.h"
#include "SWITCH.h"
#include "LCD.h"
#include "DIO.h"
#define Max_Score  (10U)


int main(void)
{
	DIO_Init();
	SWITCH_Init();
	LCD_vidInit();
	Ping_Pong_Game(Max_Score);
}


