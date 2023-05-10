/*************************************************************
 * 
 * Filename: Incremental_LEDS_LDR.h
 * Description:Header file of Incremental LEDS Function using LDR.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef INCREMENTAL_LEDS_LDR_H_
#define INCREMENTAL_LEDS_LDR_H_

#include "STD_TYPES.h"
#include "LDR.h"
#include "LDR_Cfg.h"
#include "LCD.h"
#include "LED.h"
#include "LED_Cfg.h"

void Incremental_LEDS_LDR(u16 Maximum_Resistance_Value,u8 Connected_LED_Port);

#endif /* INCREMENTAL_LEDS_LDR_H_ */