
#ifndef LED_H
#define LED_H

#include "DIO.h"

typedef enum {
	LED_enuOK=0,
	LED_enuNOK,
	LED_enuNullPtr
} LED_tenuErrorStatus;

LED_tenuErrorStatus LED_Init (void);
LED_tenuErrorStatus Turn_LED_ON (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber);
LED_tenuErrorStatus Turn_LED_OFF (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber);
LED_tenuErrorStatus Turn_Group_of_LEDs_ON (DIO_tenuPorts Cpy_enuPortNumber,u8 LEDs_Pattern);
LED_tenuErrorStatus Turn_Port_of_LEDs_OFF(DIO_tenuPorts Cpy_enuPortNumber);



#endif /*LED_H.h*/