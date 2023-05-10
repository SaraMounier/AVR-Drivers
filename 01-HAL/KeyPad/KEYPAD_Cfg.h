/*************************************************************
 * 
 * Filename: KEYPAD_Cfg.h
 * Description: Configuration header file of the KEYPAD driver.
 * Author: Sara Mounier
 * Github:
 * 
 *************************************************************/

#ifndef __KEYPAD_CFG_H__
#define __KEYPAD_CFG_H__

#include "STD_TYPES.h"
#include "DIO.h"

#define KEYPAD_PORT DIO_enuPortA
#define Debouncing_Time 5
#define Debouncing_Cycles 5

#define KP_ROW_SIZE 4
#define KP_COL_SIZE 4
extern const  u8 u8_KeyPadArray [KP_ROW_SIZE][KP_COL_SIZE];
 

#endif /* __KEYPAD_CFG_H__ */