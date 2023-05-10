/*************************************************************
 * 
 * Filename: KEYPAD.h
 * Description: Header (interface) file of the KEYPAD driver.
 * Author: Sara Mounier
 * Github:
 * 
 *************************************************************/

#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#define COL_BGN 0
#define COL_END 4
#define ROW_BGN 4
#define ROW_END 8

typedef enum
{
	KeyPad_enuOK = 0,
	KeyPad_enuNOK ,
	KeyPad_enuNullPtr,
	
}KeyPad_tenuErrorStatus;

KeyPad_tenuErrorStatus KP_GetPressedKey(u8 *Add_Pressed_Key);

#endif /* __KEYPAD_H__ */