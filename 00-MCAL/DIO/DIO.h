/*DIO  file*/
#ifndef DIO_H
#define DIO_H
#include "STD_TYPES.h"
typedef enum {
	DIO_enuOK=0,
	DIO_enuNOK,
	DIO_InvalidPortNumber,
	DIO_InvalidPinNumber,
    DIO_enuInvalidPinDirection,
	DIO_enuInvalidPinValue,
	DIO_enuInvalidPortDirection,
	DIO_enuInvalidPortValue,
	DIO_enuNullPtr
} DIO_tenuErrorStatus;

typedef enum {
	DIO_enuPortA=0,
	DIO_enuPortB,
	DIO_enuPortC,
	DIO_enuPortD,
	DIO_enuPortsNumber
}DIO_tenuPorts;

typedef enum {
	DIO_enuPin0=0,
	DIO_enuPin1,
	DIO_enuPin2,
	DIO_enuPin3,
	DIO_enuPin4,
	DIO_enuPin5,
	DIO_enuPin6,
	DIO_enuPin7,
	DIO_enuPinsNumber
}DIO_tenuPins;

typedef enum {
	DIO_enuLow=0x00,
	DIO_enuHigh=0x01,
	DIO_enuMaxPortValue=0xFF,
	DIO_enuMinPortValue=0x00
	
} DIO_tenuPinValue;

typedef enum {
	DIO_enuInput=0x00,
	DIO_enuOutput=0x01,
	DIO_enuMaxPortDirection=0xFF,
	DIO_enuMinPortDirection=0x00

} DIO_tenuPortDirection;

/*
INIT FUNCTION WHY?
*/
DIO_tenuErrorStatus DIO_Init (void);
/*
SET BIT DIRECTION FUNCTION INPUT OR OUTPUT
 DDR-  0:INPUT OR 1:OUTPUT
*/
DIO_tenuErrorStatus DIO_SetPinDir (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber,DIO_tenuPortDirection Cpy_enuPinDirection);

/*
Enable Pin Pull Up Resistance Function
PORT-  1:ENABLE PULL UP 0:DISABLE PULL UP
*/
DIO_tenuErrorStatus DIO_EnablePinPullUp (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber);

/*
Get Pin Value from PIN register 
read it and send it to the upper layer using pointer
*/
DIO_tenuErrorStatus DIO_GetPinVal (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber, u8 *Add_pu8PinValue);

/*
Toggle Pin Value msh 3arfa htoggle el PORT reg wla a ?
PORT_  1: OutputHigh 0:OutputLow
*/
DIO_tenuErrorStatus DIO_TogPinValue (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber);

/*
SET PIN VALUE FUNCTION
PIN VALUE(PORT-)  1:HIGH OR O:LOW
*/
DIO_tenuErrorStatus DIO_SetPinVal (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber, DIO_tenuPinValue Cpy_enuPinValue);

/*
SET PORT DIRECTION FUNCTION
M DDR- 0x00:Input 0xFF: Output or compination
*/
DIO_tenuErrorStatus DIO_SetPORTDir (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPortDirection Cpy_enuPortDirection);

/*
SET PORT VALUE FUNCTION
MSH 3ARFA HSET port- 0x00:outputlow 0xFF: outputhigh or compination
*/
DIO_tenuErrorStatus DIO_SetPORTVal (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPinValue Cpy_enuPortValue);
/*clear port*/


DIO_tenuErrorStatus DIO_ClearPORTVal (DIO_tenuPorts Cpy_enuPortNumber);


#endif /*DIO_H*/