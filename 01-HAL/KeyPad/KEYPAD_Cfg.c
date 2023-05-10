/*************************************************************
 * 
 * Filename: KEYPAD_Cfg.c
 * Description: Configuration source file of the KEYPAD driver.
 * Author: Sara Mounier
 * Github:
 * 
 *************************************************************/

#include "STD_TYPES.h"
#include "KEYPAD_Cfg.h"


 const u8 u8_KeyPadArray [KP_ROW_SIZE][KP_COL_SIZE] 
	={
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'}  
	};