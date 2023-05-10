/*************************************************************
 * 
 * Filename: LCD.c
 * Description: Source file of the LCD driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/
#include "LCD.h"
#include "LCD_Cfg.h"
#include "LCD_Priv.h"
#include "DIO.h"
#include "util/delay.h"

void LCD_vidInit()
{
	_delay_ms(35);
	LCD_enuSendCommand(SELECTED_FUNCTION_SET);
	_delay_ms(1);
	LCD_enuSendCommand(LCD_CLR);
	_delay_ms(1);
	LCD_enuSendCommand(SELECTED_DISPLAY_ON_OFF_CONTROL);
	_delay_ms(1);
	LCD_enuSendCommand(SELECTED_ENTRY_MODE_SET);
	_delay_ms(1);
}
static u8 LCD_getBusyFlag(void)
{
	u8 BusyFlag=0;
	//DIO_SetPinVal(Arr_LCD_strConfig[LCD_RS_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RS_PIN].LCD_PinNum, LOW);
	//DIO_SetPinVal(Arr_LCD_strConfig[LCD_RW_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RW_PIN].LCD_PinNum, High);
	//DIO_GetPinVal(Arr_LCD_strConfig[LCD_D7_PIN].LCD_PortNum,Arr_LCD_strConfig[LCD_D7_PIN].LCD_PinNum,&BusyFlag);
	 return BusyFlag;	
}

static void LCD_StaticSendData(u8 u8Loc_Data)
{
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_RS_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RS_PIN].LCD_PinNum, High);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_RW_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RW_PIN].LCD_PinNum, LOW);
	_delay_ms(2);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, High);
	DIO_SetPORTVal(LCD_DATA_PORT,u8Loc_Data);
	_delay_ms(2);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, LOW);
	_delay_ms(2);
}
static void LCD_StaticWriteCommand(u8 u8Command)
{
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_RS_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RS_PIN].LCD_PinNum, LOW);
		_delay_ms(2);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_RW_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RW_PIN].LCD_PinNum, LOW);
		_delay_ms(2);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, High);
	_delay_ms(2);
	DIO_SetPORTVal(LCD_DATA_PORT,u8Command);
		_delay_ms(10);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, LOW);
}
LCD_enuErrorStatus LCD_enuSendData(u8 Copy_u8Data)
{
		LCD_enuErrorStatus Loc_LCDenuReturnErrStatus;
	if(!LCD_getBusyFlag())
	{		
		LCD_StaticSendData( Copy_u8Data);
		Loc_LCDenuReturnErrStatus=LCD_enuOK;
	}
	else 
	{
		Loc_LCDenuReturnErrStatus=LCD_enuBusyFlag;
	}
 return Loc_LCDenuReturnErrStatus;
}

LCD_enuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number)
{
	LCD_enuErrorStatus Loc_LCDenuReturnErrStatus;
	if(!LCD_getBusyFlag() && Copy_u16Number>0)
	{	u8 perres,i=0,j=0;
		u8 Loc_ArrNumbers[5]={0};
		while(Copy_u16Number !=0 )
		{  perres=Copy_u16Number%10;
			Copy_u16Number/=10;
			Loc_ArrNumbers[i]=perres + ZERO_ASCII;
			i++;
		}
		for(j=0;j<i;j++)
		{
			LCD_StaticSendData(Loc_ArrNumbers[i-j-1]);
		}
		Loc_LCDenuReturnErrStatus=LCD_enuOK;
	}
	else if(!LCD_getBusyFlag() && Copy_u16Number==0)
	{
			 LCD_StaticSendData(Copy_u16Number+ZERO_ASCII);
			 Loc_LCDenuReturnErrStatus=LCD_enuOK;
	}
	else
	{
		Loc_LCDenuReturnErrStatus=LCD_enuBusyFlag;
	}
	return Loc_LCDenuReturnErrStatus;
}

LCD_enuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command)
{
	LCD_enuErrorStatus Loc_LCDenuReturnErrStatus;
	if(!LCD_getBusyFlag())
	{
		LCD_StaticWriteCommand(Copy_u8Command);
	}
	else
	{
		Loc_LCDenuReturnErrStatus=LCD_enuBusyFlag;
	}	 
return Loc_LCDenuReturnErrStatus;	
}

LCD_enuErrorStatus LCD_enuWriteString (char* Add_pchString)
{			
	LCD_enuErrorStatus Loc_LCDenuReturnErrStatus;
	if (!LCD_getBusyFlag())
	{
		while (* Add_pchString != '\0' && !LCD_getBusyFlag())
		{
			LCD_StaticSendData(* Add_pchString);
			_delay_ms(2);
			Add_pchString++;
			Loc_LCDenuReturnErrStatus=LCD_enuOK;
		}
	}
	else 
	{
		Loc_LCDenuReturnErrStatus=LCD_enuBusyFlag;
	}
	return Loc_LCDenuReturnErrStatus;
}

LCD_enuErrorStatus LCD_enuGotoXY (u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	LCD_enuErrorStatus Loc_LCDenuReturnErrStatus=LCD_enuNOK;
	u8 LocCommand=0;
	if (Copy_u8XPos>=0 && Copy_u8XPos<=LCD_VISABLERANGE && (Copy_u8YPos==FIRST_LINE || Copy_u8YPos==SECOND_LINE))
	{
		if(Copy_u8YPos== FIRST_LINE)
		{
			LocCommand=FIRST_LINE+Copy_u8XPos;
			LCD_StaticWriteCommand(MASK_DDRAM | LocCommand);
			Loc_LCDenuReturnErrStatus=LCD_enuOK;
		}
		else if(Copy_u8YPos== SECOND_LINE)
		{
			LocCommand=SECOND_LINE + Copy_u8XPos;
			LCD_StaticWriteCommand(MASK_DDRAM | LocCommand);
			Loc_LCDenuReturnErrStatus=LCD_enuOK;
		}
	}
	else
	{
		Loc_LCDenuReturnErrStatus=LCD_enuInvalidParameter;
	}
	return Loc_LCDenuReturnErrStatus;
	}

LCD_enuErrorStatus LCD_enuWriteSpecialPattern  (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	LCD_enuErrorStatus Loc_LCDenuReturnErrStatus=LCD_enuNOK;
	u8 CGRAM_Add=Copy_u8BlockNum*CGRAM_BlockSize;
	u8 iterator=0;
	if(Add_pu8Pattern !=NULL)
	{
		if(Copy_u8BlockNum>=0 && Copy_u8BlockNum<=CGRAM_BlockSize &&(Copy_u8XPos>=0 && Copy_u8XPos<=LCD_VISABLERANGE && (Copy_u8YPos==FIRST_LINE || Copy_u8YPos==SECOND_LINE)))
		{
			LCD_StaticWriteCommand(MASK_CGRAM | CGRAM_Add);
			for(iterator=0;iterator<CGRAM_BlockSize;iterator++)
			{
				LCD_StaticSendData(Add_pu8Pattern[iterator]);
			}
			LCD_enuGotoXY(Copy_u8XPos,Copy_u8YPos);
			Loc_LCDenuReturnErrStatus=LCD_enuOK;
			LCD_StaticSendData(Copy_u8BlockNum);
		}
		else
		{
			Loc_LCDenuReturnErrStatus=LCD_enuInvalidParameter;
		}
	}
	else
	{
		Loc_LCDenuReturnErrStatus=LCD_enuNullPtr;
	}
	return Loc_LCDenuReturnErrStatus;
}
	

	/*send command
	Copy_u8CommandDIO_SetPinVal(Arr_LCD_strConfig[LCD_RS_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RS_PIN].LCD_PinNum, LOW);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_RW_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RW_PIN].LCD_PinNum, LOW);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, High);
	_delay_ms(2);
	DIO_SetPORTVal(LCD_DATA_PORT,Copy_u8Command);
	DIO_SetPinVal(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, LOW);
	Loc_LCDenuReturnErrStatus=LCD_enuOK;*/