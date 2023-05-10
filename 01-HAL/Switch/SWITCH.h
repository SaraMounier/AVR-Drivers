#ifndef SWITCH_H
#define SWITCH_H

#include "DIO.h"
#include "STD_TYPES.h"
typedef enum {
	SWITCH_enuOK=0,
	SWITCH_enuNOK,
	SWITCH_enuNullPtr
} SWITCH_tenuErrorStatus;

typedef enum
{
	SWITCH_0=0,
	SWITCH_1,
	SWITCH_2,
	SWITCH_3,
	SWITCH_4,
	SWITCH_5,
	SWITCH_6,
	SWITCH_7
}SWITCH_tenuSwitchNumber;


typedef enum
{   SWITCH_Pull_Down=0,
	SWITCH_Pull_Up=1
} SWITCH_tenuActiveState;


typedef enum
{	
	SWITCH_Released=0,
	SWITCH_Pressed=1
} SWITCH_tenuInitialState;


SWITCH_tenuErrorStatus SWITCH_Init (void);
SWITCH_tenuErrorStatus GET_SWITCH_State (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber, DIO_tenuPinValue *Add_u8ptrSwitchState);

#endif //SWITCH_H