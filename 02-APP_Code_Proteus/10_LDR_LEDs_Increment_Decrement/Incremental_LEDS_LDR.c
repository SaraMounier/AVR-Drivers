/*************************************************************
 * 
 * Filename: Incremental_LEDS_LDR.c
 * Description: Incremental LEDS Function using LDR.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/
#include "Incremental_LEDS_LDR.h "


void Incremental_LEDS_LDR(u16 Maximum_Resistance_Value,u8 Connected_LED_Port)
{
	u16 LDR_Sensor_Value=0;
	LDR_vidInit();
	while (1)
	{
		LDR_getLDRResistance(&LDR_Sensor_Value);
		LCD_enuWriteNumber(LDR_Sensor_Value);
		LCD_enuSendCommand(LCD_CLR);
	
		if((LDR_Sensor_Value < 0.9*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.8*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_OFF (Connected_LED_Port ,LED_1);
			Turn_LED_OFF (Connected_LED_Port ,LED_2);
			Turn_LED_OFF (Connected_LED_Port ,LED_3);
			Turn_LED_OFF (Connected_LED_Port ,LED_4);
			Turn_LED_OFF (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.8*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.7*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_OFF (Connected_LED_Port ,LED_2);
			Turn_LED_OFF (Connected_LED_Port ,LED_3);
			Turn_LED_OFF (Connected_LED_Port ,LED_4);
			Turn_LED_OFF (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.7*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.6*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_ON  (Connected_LED_Port ,LED_2);
			Turn_LED_OFF (Connected_LED_Port ,LED_3);
			Turn_LED_OFF (Connected_LED_Port ,LED_4);
			Turn_LED_OFF (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.6*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.5*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_ON  (Connected_LED_Port ,LED_2);
			Turn_LED_ON  (Connected_LED_Port ,LED_3);
			Turn_LED_OFF (Connected_LED_Port ,LED_4);
			Turn_LED_OFF (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.5*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.4*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_ON  (Connected_LED_Port ,LED_2);
			Turn_LED_ON  (Connected_LED_Port ,LED_3);
			Turn_LED_OFF (Connected_LED_Port ,LED_4);
			Turn_LED_OFF (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.4*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.3*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_ON  (Connected_LED_Port ,LED_2);
			Turn_LED_ON  (Connected_LED_Port ,LED_3);
			Turn_LED_ON  (Connected_LED_Port ,LED_4);
			Turn_LED_OFF (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.3*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.2*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_ON  (Connected_LED_Port ,LED_2);
			Turn_LED_ON  (Connected_LED_Port ,LED_3);
			Turn_LED_ON  (Connected_LED_Port ,LED_4);
			Turn_LED_ON  (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.2*Maximum_Resistance_Value) && (LDR_Sensor_Value >= 0.1*Maximum_Resistance_Value) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_ON  (Connected_LED_Port ,LED_2);
			Turn_LED_ON  (Connected_LED_Port ,LED_3);
			Turn_LED_ON  (Connected_LED_Port ,LED_4);
			Turn_LED_ON  (Connected_LED_Port ,LED_5);
			Turn_LED_ON  (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
		else if((LDR_Sensor_Value < 0.1*Maximum_Resistance_Value) && (LDR_Sensor_Value > 0) )
		{
			Turn_LED_ON  (Connected_LED_Port ,LED_0);
			Turn_LED_ON  (Connected_LED_Port ,LED_1);
			Turn_LED_ON  (Connected_LED_Port ,LED_2);
			Turn_LED_ON  (Connected_LED_Port ,LED_3);
			Turn_LED_ON  (Connected_LED_Port ,LED_4);
			Turn_LED_ON  (Connected_LED_Port ,LED_5);
			Turn_LED_ON  (Connected_LED_Port ,LED_6);
			Turn_LED_ON  (Connected_LED_Port ,LED_7);
		}
		else
		{
			Turn_LED_OFF (Connected_LED_Port ,LED_0);
			Turn_LED_OFF (Connected_LED_Port ,LED_1);
			Turn_LED_OFF (Connected_LED_Port ,LED_2);
			Turn_LED_OFF (Connected_LED_Port ,LED_3);
			Turn_LED_OFF (Connected_LED_Port ,LED_4);
			Turn_LED_OFF (Connected_LED_Port ,LED_5);
			Turn_LED_OFF (Connected_LED_Port ,LED_6);
			Turn_LED_OFF (Connected_LED_Port ,LED_7);
		}
	}
}