/*************************************************************
 * 
 * Filename: KEYPAD.c
 * Description: Source file of the KEYPAD driver.
 * Author: Sara Mounier
 * Github: 
 * 
 *************************************************************/

#include "avr/delay.h"
#include "STD_TYPES.h"
#include "KEYPAD.h"
#include "KEYPAD_Cfg.h"
#include "DIO.h"

KeyPad_tenuErrorStatus KP_GetPressedKey(u8 *Add_Pressed_Key){
	u8 Loc_u8RowPinNum=0 ,Loc_u8ColPinNum=0 ;
	u8 Loc_u8CurrentRowPinVal,Loc_u8PrevRowPinVal;
	u8 Debouncing_Iterator=0;
	KeyPad_tenuErrorStatus Loc_enuKPErrorStatus = KeyPad_enuOK;
	DIO_tenuErrorStatus Loc_enuDIOErrorStatus = DIO_enuOK;
	//for(u8 Pin=COL_BGN;Pin<COL_END;Pin++) { DIO_SetPinVal(KEYPAD_PORT,Pin,DIO_enuHigh);}
	while(1)
	{	
	for(Loc_u8ColPinNum=COL_BGN;(Loc_u8ColPinNum< COL_END && Loc_enuDIOErrorStatus==DIO_enuOK) ;Loc_u8ColPinNum++)
	{
		Loc_enuDIOErrorStatus = DIO_SetPinVal(KEYPAD_PORT,Loc_u8ColPinNum,DIO_enuLow);


		for(Loc_u8RowPinNum=ROW_BGN;Loc_u8RowPinNum< ROW_END;Loc_u8RowPinNum++)
		{
			Loc_enuDIOErrorStatus =	DIO_GetPinVal(KEYPAD_PORT,Loc_u8RowPinNum,&Loc_u8PrevRowPinVal);
		
			while(Debouncing_Iterator < Debouncing_Cycles)
			{
				Loc_enuDIOErrorStatus = DIO_GetPinVal(KEYPAD_PORT,Loc_u8RowPinNum,&Loc_u8CurrentRowPinVal);
		
				if(Loc_u8PrevRowPinVal==Loc_u8CurrentRowPinVal==DIO_enuLow)
				{
					Debouncing_Iterator++;
					_delay_ms(Debouncing_Time);
				}
				else
				{
					//Debouncing_Iterator=0;
					break;
				}
				Loc_u8PrevRowPinVal=Loc_u8CurrentRowPinVal;
			}
			
			if(Loc_u8CurrentRowPinVal==DIO_enuLow)
			{
				*Add_Pressed_Key= u8_KeyPadArray[Loc_u8RowPinNum-ROW_BGN][Loc_u8ColPinNum];
			}
	    
		}
				DIO_SetPinVal(KEYPAD_PORT,Loc_u8ColPinNum,DIO_enuHigh);

		}
		
return (Loc_enuKPErrorStatus | Loc_enuDIOErrorStatus) ;
}
	}
// what can I test to change KP error status?