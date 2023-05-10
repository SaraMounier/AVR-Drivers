/*************************************************************
 * 
 * Filename: LM35_Cfg.c
 * Description: Configuration source file of the LM35 driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "LM35_Cfg.h"
#include "STD_TYPES.h"
#include "ADC.h"
const u8 SensorsChannelsArray[SENSORS_NUMBER]={[TEMP_SENSOR]=MUX_ADC0};
