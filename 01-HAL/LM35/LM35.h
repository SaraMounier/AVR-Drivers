/*************************************************************
 * 
 * Filename: LM35.h
 * Description: Header (interface) file of the LM35 driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __LM35_H__
#define __LM35_H__

#include "STD_TYPES.h"

typedef enum
{
	LM_enuOK,
	LM_enuNOK,
	LM_enuInvalidParameter,
	LM_enuNullPtr,
} LM_enuErrorStatus_t;

LM_enuErrorStatus_t LM_Init(void);
LM_enuErrorStatus_t LM_readTemp(u8 SensorMUX_,u16* Add_LMReading);


#endif /* __LM35_H__ */