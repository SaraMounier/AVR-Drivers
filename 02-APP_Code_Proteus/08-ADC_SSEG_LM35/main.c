/*
 * LM_Driver.c
 *
 * Created: 2/15/2023 9:45:20 AM
 * Author : saram
 */ 


#include "ADC.h"
#include "LM35.h"
#include "LM35_Cfg.h"
#include "DIO.h"
#include "LED.h"
#include "Seven_Segment.h"
#include "LCD.h"
#include "util/delay.h"

void SSEG_Output(DIO_tenuPorts Cpy_enuPortNumber,u8 Num);
#define ONES_PORT DIO_enuPortD
#define TENS_PORT DIO_enuPortB
int main(void)
{
	LM_vidInit();	
	LCD_vidInit();
	u16 Loc_LMReading=0;	
	u8 ones_SSEG=0,tens_SSEG=0;	
    while (1) 
    {			
		LM_readTemp(SensorsChannelsArray[TEMP_SENSOR],& Loc_LMReading);
		LCD_enuWriteNumber(Loc_LMReading);
		tens_SSEG=(Loc_LMReading) /10;
		ones_SSEG=(Loc_LMReading) %10;
		LCD_enuSendCommand(LCD_CLR);
		_delay_ms(10);
		SSEG_Output( ONES_PORT,ones_SSEG );
		SSEG_Output( TENS_PORT,tens_SSEG );

    }
	return 0;
}

void SSEG_Output(DIO_tenuPorts Cpy_enuPortNumber,u8 Num)
{
	switch(Num)
	{
		case 0:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,ZERO);
		break;
		case 1:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,ONE);
		break;
		case 2:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,TWO);
		break;
		case 3:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,THREE);
		break;
		case 4:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,FOUR);
		break;
		case 5:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,FIVE);
		break;
		case 6:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,SIX);
		break;
		case 7:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,SEVEN);
		break;
		case 8:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,EIGHT);
		break;
		case 9:
		Turn_Group_of_LEDs_ON ( Cpy_enuPortNumber,NINE);
		break;
	}
}

