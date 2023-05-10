/* LED configuration file  */

#ifndef LED_CFG_H
#define LED_CFG_H

#include "DIO.h"

typedef enum
{
	LED_0=0,
	LED_1,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
	Number_of_Leds
}LED_tenuLedNumber;

typedef enum
{
	LED_Initially_Low=0,
	LED_Initially_High=1
}LED_tenuInitialState;



#endif /*LED_CGF_H*/
