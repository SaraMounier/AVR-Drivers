/*************************************************************
 * 
 * Filename: LM35_Cfg.h
 * Description: Configuration header file of the LM35 driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __LM35_CFG_H__
#define __LM35_CFG_H__
#include "STD_TYPES.h"
#define SENSORS_NUMBER 1
#define TEMP_SENSOR 0
#define MAX_VOLTAGE 5
#define RESOLUTION 1023.0
#define VOLTAGE_TO_TEMP_FACTOR (1/0.01)
const extern u8 SensorsChannelsArray[SENSORS_NUMBER];

#endif /* __LM35_CFG_H__ */