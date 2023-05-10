/*************************************************************
 * 
 * Filename: LCD_Cfg.h
 * Description: Configuration header file of the LCD driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __LCD_CFG_H__
#define __LCD_CFG_H__

#include "STD_TYPES.h"
#define ZERO_ASCII 48

#define LCD_GND 	00
#define LCD_VDD 	01
#define LCD_VO  	02
#define LCD_RS_PIN 	03
#define LCD_RW_PIN 	04
#define LCD_EN_PIN 	05
#define LCD_D0_PIN 	06
#define LCD_D1_PIN 	07
#define LCD_D2_PIN 	8
#define LCD_D3_PIN 	9
#define LCD_D4_PIN 	10
#define LCD_D5_PIN 	11
#define LCD_D6_PIN 	12
#define LCD_D7_PIN 	13
#define LCD_BLA_PIN	14
#define LCD_BLK_PIN	15
#define LCD_PINS_NUMBER 16
#define LCD_CONTROL_PORT DIO_enuPortA
#define LCD_DATA_PORT DIO_enuPortB

#define High 1
#define LOW 0

#define CGRAM_BlockSize 8
#define LCD_VISABLERANGE 15
typedef struct  
{
	u8 LCD_PortNum;
	u8 LCD_PinNum;
	u8 LCD_Initial_Value;

} LCD_tstrConfig_t;

extern const  LCD_tstrConfig_t Arr_LCD_strConfig [LCD_PINS_NUMBER];
extern u8 UnFilledHeart[8];
extern u8 Mobile[8];
extern u8 Bell[8];
extern u8 Silent[8];
extern u8 Music[8];
extern u8 Plug[8];
extern u8 Face[8];
extern u8 FilledHeart[8];
extern u8 YogaHuman[8];
extern u8 Human[8];
extern u8 Cat[8];
extern u8 Paw[8] ;
#endif /* __LCD_CFG_H__ */