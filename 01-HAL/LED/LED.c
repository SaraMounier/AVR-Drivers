#include "LED.h"
#include "DIO.h"
#include "LED_Cfg.h"
#include "STD_TYPES.h"


LED_tenuErrorStatus Turn_LED_ON (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber)
{
    LED_tenuErrorStatus Loc_enuReturnLed = 0;
	DIO_tenuErrorStatus Loc_u8ReturnDio_Dir = 0;
	DIO_tenuErrorStatus Loc_u8ReturnDio_Val = 0;

	Loc_u8ReturnDio_Dir = DIO_SetPinDir (Cpy_enuPortNumber , Cpy_enuPinNumber,DIO_enuOutput);
	Loc_u8ReturnDio_Val = DIO_SetPinVal (Cpy_enuPortNumber , Cpy_enuPinNumber, DIO_enuHigh);
	if(Loc_u8ReturnDio_Dir == DIO_enuOK && Loc_u8ReturnDio_Val == DIO_enuOK )
	{
		Loc_enuReturnLed= LED_enuOK;
	}
	else
	{
		Loc_enuReturnLed= LED_enuNOK;

	}
	return Loc_enuReturnLed;
}

LED_tenuErrorStatus Turn_LED_OFF (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber)
{
	LED_tenuErrorStatus Loc_enuReturnLed = 0;
	DIO_tenuErrorStatus Loc_u8ReturnDio_Dir = 0;
	DIO_tenuErrorStatus Loc_u8ReturnDio_Val = 0;

	Loc_u8ReturnDio_Dir = DIO_SetPinDir (Cpy_enuPortNumber , Cpy_enuPinNumber,DIO_enuOutput);
	Loc_u8ReturnDio_Val = DIO_SetPinVal (Cpy_enuPortNumber , Cpy_enuPinNumber, DIO_enuLow);
	if(Loc_u8ReturnDio_Dir == DIO_enuOK && Loc_u8ReturnDio_Val == DIO_enuOK )
	{
		Loc_enuReturnLed= LED_enuOK;
	}
	else
	{
		Loc_enuReturnLed= LED_enuNOK;

	}
	return Loc_enuReturnLed;
}



LED_tenuErrorStatus Turn_Group_of_LEDs_ON (DIO_tenuPorts Cpy_enuPortNumber,u8 LEDs_Pattern)
{
	LED_tenuErrorStatus Loc_enuReturnLed = LED_enuOK;
	DIO_tenuErrorStatus Loc_u8ReturnDio_Dir = 0;
	DIO_tenuErrorStatus Loc_u8ReturnDio_Val = 0;
	Loc_u8ReturnDio_Dir = DIO_SetPORTDir (Cpy_enuPortNumber ,DIO_enuMaxPortDirection);
	Loc_u8ReturnDio_Val = DIO_SetPORTVal ( Cpy_enuPortNumber ,LEDs_Pattern);
	return Loc_enuReturnLed;
}


LED_tenuErrorStatus Turn_Port_of_LEDs_OFF(DIO_tenuPorts Cpy_enuPortNumber)
{
	LED_tenuErrorStatus	Loc_enuReturnLed = LED_enuOK;
	DIO_tenuErrorStatus Loc_u8ReturnDio_Val = 0;
	Loc_u8ReturnDio_Val = DIO_ClearPORTVal ( Cpy_enuPortNumber );
	return Loc_enuReturnLed;
}

