#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "DIO_piv.h"
#include "DIO_Cfg.h"

/*
INIT FUNCTION WHY?
*/
DIO_tenuErrorStatus DIO_Init (void){
	
	u8 i;
	u8 Loc_u8PortNumber = 0;
	u8 Loc_u8PinNumber = 0;
	
	for(i = 0; i < DIO_enuPinsNumber; i++)
	{
		Loc_u8PortNumber = i/8;
		Loc_u8PinNumber = i%8;
		
		switch(Loc_u8PortNumber)
		{
			case(DIO_enuPortA):
			if(DIO_strPinCnfg[i].DIO_PinDirection == DIO_DIR_OUTPUT)
			{
				SET_BIT(DDRA,Loc_u8PinNumber);
			}
			else
			{
				CLR_BIT(DDRA,Loc_u8PinNumber);
				if(DIO_strPinCnfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
				{
					SET_BIT(PORTA,Loc_u8PinNumber);
				}
			}
			break;
			
			case(DIO_enuPortB):
			if(DIO_strPinCnfg[i].DIO_PinDirection == DIO_DIR_OUTPUT)
			{
				SET_BIT(DDRB,Loc_u8PinNumber);
			}
			else
			{
				CLR_BIT(DDRB,Loc_u8PinNumber);
				if(DIO_strPinCnfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
				{
					SET_BIT(PORTB,Loc_u8PinNumber);
				}
			}
			break;
			
			case(DIO_enuPortC):
			if(DIO_strPinCnfg[i].DIO_PinDirection == DIO_DIR_OUTPUT)
			{
				SET_BIT(DDRC,Loc_u8PinNumber);
			}
			else
			{
				CLR_BIT(DDRC,Loc_u8PinNumber);
				if(DIO_strPinCnfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
				{
					SET_BIT(PORTC,Loc_u8PinNumber);
				}
			}
			break;
			
			case(DIO_enuPortD):
			if(DIO_strPinCnfg[i].DIO_PinDirection == DIO_DIR_OUTPUT)
			{
				SET_BIT(DDRD,Loc_u8PinNumber);
			}
			else
			{
				CLR_BIT(DDRD,Loc_u8PinNumber);
				if(DIO_strPinCnfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
				{
					SET_BIT(PORTD,Loc_u8PinNumber);
				}
			}
			break;
			
		}
	}
	return DIO_enuOK ;	
}
/*
SET BIT DIRECTION FUNCTION INPUT OR OUTPUT
 DDR-  0:INPUT OR 1:OUTPUT
*/

DIO_tenuErrorStatus DIO_SetPinDir (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber,/*check!!*/DIO_tenuPortDirection Cpy_enuPinDirection)
	{
	  DIO_tenuErrorStatus Loc_enuReturn;

	    if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	     {
		    if(Cpy_enuPinNumber < DIO_enuPinsNumber)
		     {
        		if(Cpy_enuPinDirection==DIO_enuOutput || Cpy_enuPinDirection==DIO_enuInput){
					Loc_enuReturn= DIO_enuOK;
					switch (Cpy_enuPortNumber)
					{
						case DIO_enuPortA:
						  if(Cpy_enuPinDirection == DIO_enuOutput)
							SET_BIT(DDRA,Cpy_enuPinNumber);
						  else if(Cpy_enuPinDirection == DIO_enuInput)
							CLR_BIT(DDRA,Cpy_enuPinNumber);
						  break;

						case DIO_enuPortB:
						  if(Cpy_enuPinDirection == DIO_enuOutput)
							SET_BIT(DDRB,Cpy_enuPinNumber);
						  else if(Cpy_enuPinDirection == DIO_enuInput)
							CLR_BIT(DDRB,Cpy_enuPinNumber);
						  break;

						case DIO_enuPortC:
						  if(Cpy_enuPinDirection == DIO_enuOutput)
							SET_BIT(DDRC,Cpy_enuPinNumber);
						  else if(Cpy_enuPinDirection == DIO_enuInput)
							CLR_BIT(DDRC,Cpy_enuPinNumber);
						  break;

						case DIO_enuPortD:
						  if(Cpy_enuPinDirection == DIO_enuOutput)
							SET_BIT(DDRD,Cpy_enuPinNumber);
						  else if(Cpy_enuPinDirection == DIO_enuInput)
							CLR_BIT(DDRD,Cpy_enuPinNumber);
						  break;
				}}
				else
				    {
					 Loc_enuReturn= DIO_enuInvalidPinDirection;
				    }
			 }
		     
		    else
			  {
				Loc_enuReturn= DIO_InvalidPinNumber;
			  }
	     }
	    else
		  {
		    Loc_enuReturn= DIO_InvalidPortNumber;
		  }

	  return 	Loc_enuReturn;

    }

/*
Enable Pin Pull Up Resistance Function
PORT-  1:ENABLE PULL UP 0:DISABLE PULL UP
*/
DIO_tenuErrorStatus DIO_EnablePinPullUp (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber)
{
DIO_tenuErrorStatus Loc_enuReturn;
 if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	{
	 if(Cpy_enuPinNumber < DIO_enuPinsNumber)
		{

		 Loc_enuReturn= DIO_enuOK;
		 switch(Cpy_enuPortNumber)
		  {
		   case DIO_enuPortA:
				if(GET_BIT(DDRA,Cpy_enuPinNumber)==DIO_enuInput)
					{
					SET_BIT(PORTA,Cpy_enuPinNumber);
					}
				else 
					{ 
					Loc_enuReturn =DIO_enuInvalidPinDirection;
					}
				break;			
		   case DIO_enuPortB:
				if(GET_BIT(DDRB,Cpy_enuPinNumber)==DIO_enuInput)
					{
					SET_BIT(PORTB,Cpy_enuPinNumber);
					}
				else 
					{ 
					Loc_enuReturn =DIO_enuInvalidPinDirection; 
					}		
				break;
		   case DIO_enuPortC:
				if(GET_BIT(DDRC,Cpy_enuPinNumber)==DIO_enuInput)
					{
					SET_BIT(PORTC,Cpy_enuPinNumber);
					}
				else 
					{
					Loc_enuReturn =DIO_enuInvalidPinDirection; 
					}
				break;
		   case DIO_enuPortD:
				if(GET_BIT(DDRD,Cpy_enuPinNumber)==DIO_enuInput)
					{
					SET_BIT(PORTD,Cpy_enuPinNumber);
					}
				else 
					{
					Loc_enuReturn =DIO_enuInvalidPinDirection; 
					}
				break;
		  }
		 }
	 else
		{
		 Loc_enuReturn= DIO_InvalidPinNumber;
		}
	}
 else
	{
	 Loc_enuReturn= DIO_InvalidPortNumber;
	}
return Loc_enuReturn;
}

/*
Get Pin Value from PIN register
read it and send it to the upper layer using pointer
*/
DIO_tenuErrorStatus DIO_GetPinVal (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber, u8 *Add_pu8PinValue)
{
 DIO_tenuErrorStatus Loc_enuReturn;
 if ( Add_pu8PinValue == NULL ) /*(void*)0*/
 {
	 if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	{
	 if(Cpy_enuPinNumber < DIO_enuPinsNumber)
		{

		 Loc_enuReturn= DIO_enuOK;
		 switch(Cpy_enuPortNumber)
		  {
		   case DIO_enuPortA:
				if(GET_BIT(DDRA,Cpy_enuPinNumber)==DIO_enuInput)
					{
					*Add_pu8PinValue=GET_BIT(PINA,Cpy_enuPinNumber);
					}
				else 
					{ 
					Loc_enuReturn =DIO_enuInvalidPinDirection;
					}
				break;			
		   case DIO_enuPortB:
				if(GET_BIT(DDRB,Cpy_enuPinNumber)==DIO_enuInput)
					{
					*Add_pu8PinValue=GET_BIT(PINB,Cpy_enuPinNumber);
					}
				else 
					{ 
					Loc_enuReturn =DIO_enuInvalidPinDirection; 
					}		
				break;
		   case DIO_enuPortC:
				if(GET_BIT(DDRC,Cpy_enuPinNumber)==DIO_enuInput)
					{
					*Add_pu8PinValue=GET_BIT(PINC,Cpy_enuPinNumber);
					}
				else 
					{
					Loc_enuReturn =DIO_enuInvalidPinDirection; 
					}
				break;
		   case DIO_enuPortD:
				if(GET_BIT(DDRD,Cpy_enuPinNumber)==DIO_enuInput)
					{
					*Add_pu8PinValue=GET_BIT(PIND,Cpy_enuPinNumber);
					}
				else 
					{
					Loc_enuReturn =DIO_enuInvalidPinDirection; 
					}
				break;
		  }
		 }
	 else
		{
		 Loc_enuReturn= DIO_InvalidPinNumber;
		}
	}
 else
	{
	 Loc_enuReturn= DIO_InvalidPortNumber;
	}
 }
 else
 {
	Loc_enuReturn=DIO_enuNullPtr;
 }
    
return Loc_enuReturn;

	
	
}

/*
Toggle Pin Value msh 3arfa htoggle el PORT reg wla a ?
PORT_  1: OutputHigh 0:OutputLow
*/
DIO_tenuErrorStatus DIO_TogPinValue (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber)
{
 DIO_tenuErrorStatus Loc_enuReturn;
 if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	{
	 if(Cpy_enuPinNumber < DIO_enuPinsNumber)
		{
		 Loc_enuReturn= DIO_enuOK;
		 switch(Cpy_enuPortNumber)
		  {
		   case DIO_enuPortA:
			TOG_BIT(PORTA,Cpy_enuPinNumber);
			break;
		   case DIO_enuPortB:
			TOG_BIT(PORTB,Cpy_enuPinNumber);
			break;
		   case DIO_enuPortC:
			TOG_BIT(PORTC,Cpy_enuPinNumber);
			break;
		   case DIO_enuPortD:
			TOG_BIT(PORTD,Cpy_enuPinNumber);
			break;
		  }
		 }
	 else
		{
		 Loc_enuReturn= DIO_InvalidPinNumber;
		}
	}
 else
	{
	 Loc_enuReturn= DIO_InvalidPortNumber;
	}
return Loc_enuReturn;
}

/*
SET PIN VALUE FUNCTION
PIN VALUE(PORT-)  1:HIGH OR O:LOW
*/
DIO_tenuErrorStatus DIO_SetPinVal (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPins Cpy_enuPinNumber, DIO_tenuPinValue Cpy_enuPinValue)
{
    DIO_tenuErrorStatus Loc_enuReturn;

	if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	    {
		 if(Cpy_enuPinNumber < DIO_enuPinsNumber)
		    {
             if(Cpy_enuPinValue==DIO_enuHigh || Cpy_enuPinValue==DIO_enuLow)
			 {
		     Loc_enuReturn= DIO_enuOK;
			 if(Cpy_enuPinValue==DIO_enuHigh)
				{
				 switch(Cpy_enuPortNumber)
				 {
				   case DIO_enuPortA:
				    SET_BIT(PORTA,Cpy_enuPinNumber);
					break;
				   case DIO_enuPortB:
				    SET_BIT(PORTB,Cpy_enuPinNumber);
					break;
				   case DIO_enuPortC:
				    SET_BIT(PORTC,Cpy_enuPinNumber);
					break;
				   case DIO_enuPortD:
				    SET_BIT(PORTD,Cpy_enuPinNumber);
					break;
				 }
				}
			 else if(Cpy_enuPinValue==DIO_enuLow)
				{
				 switch(Cpy_enuPortNumber)
				 {
				   case DIO_enuPortA:
				    CLR_BIT(PORTA,Cpy_enuPinNumber);
					break;
				   case DIO_enuPortB:
				    CLR_BIT(PORTB,Cpy_enuPinNumber);
					break;
				   case DIO_enuPortC:
				    CLR_BIT(PORTC,Cpy_enuPinNumber);
					break;
				   case DIO_enuPortD:
				    CLR_BIT(PORTD,Cpy_enuPinNumber);
					break;
				 }
				}
		     }
		     else
			 {
			  Loc_enuReturn= DIO_enuInvalidPinValue;
			 }
		     }
		 else
			{
			 Loc_enuReturn= DIO_InvalidPinNumber;
			}
	    }
	else
	    {
		 Loc_enuReturn= DIO_InvalidPortNumber;
        }
return Loc_enuReturn;
}



/*
SET PORT DIRECTION FUNCTION
M DDR- 0x00:Input 0xFF: Output or compination
*/
DIO_tenuErrorStatus DIO_SetPORTDir (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPortDirection Cpy_enuPortDirection)
{
  DIO_tenuErrorStatus Loc_enuReturn;
  if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	{
	
	 if(Cpy_enuPortDirection >= DIO_enuMinPortDirection && Cpy_enuPortDirection <= DIO_enuMaxPortDirection)
	 {
	 Loc_enuReturn= DIO_enuOK;
	 switch(Cpy_enuPortNumber)
	 {
		case DIO_enuPortA:
		DDRA=Cpy_enuPortDirection;
			break;			
		case DIO_enuPortB:
		DDRB=Cpy_enuPortDirection;
			break;
		case DIO_enuPortC:
		DDRC=Cpy_enuPortDirection;
			break;
		case DIO_enuPortD:
		DDRD=Cpy_enuPortDirection;
			break;
	 }
	 }
	 else
	 {
	  Loc_enuReturn= DIO_enuInvalidPortDirection;
	 }
	}
  else
 	{
	 Loc_enuReturn= DIO_InvalidPortNumber;
	}

  return Loc_enuReturn;
  }


/*
SET PORT VALUE FUNCTION
MSH 3ARFA HSET port- 0x00:outputlow 0xFF: outputhigh or compination
*/
DIO_tenuErrorStatus DIO_SetPORTVal (DIO_tenuPorts Cpy_enuPortNumber ,DIO_tenuPinValue Cpy_enuPortValue)
{
  DIO_tenuErrorStatus Loc_enuReturn;
  if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	{
	
	 if(Cpy_enuPortValue >= DIO_enuMinPortValue && Cpy_enuPortValue <= DIO_enuMaxPortValue)
	 {
	 Loc_enuReturn= DIO_enuOK;
	 switch(Cpy_enuPortNumber)
	 {
		case DIO_enuPortA:
		PORTA=Cpy_enuPortValue;
			break;			
		case DIO_enuPortB:
		PORTB=Cpy_enuPortValue;
			break;
		case DIO_enuPortC:
		PORTC=Cpy_enuPortValue;
			break;
		case DIO_enuPortD:
		PORTD=Cpy_enuPortValue;
			break;
	 }
	 }
	 else
	 {
	  Loc_enuReturn= DIO_enuInvalidPortValue;
	 }
	}
  else
 	{
	 Loc_enuReturn= DIO_InvalidPortNumber;
	}

  return Loc_enuReturn;
	
}
 DIO_tenuErrorStatus DIO_ClearPORTVal (DIO_tenuPorts Cpy_enuPortNumber )
 {
  DIO_tenuErrorStatus Loc_enuReturn;
	 Loc_enuReturn= DIO_enuOK;
	 switch(Cpy_enuPortNumber)
	 {
		case DIO_enuPortA:
		PORTA=0x00;
			break;			
		case DIO_enuPortB:
		PORTB=0x00;
			break;
		case DIO_enuPortC:
		PORTC=0x00;
			break;
		case DIO_enuPortD:
		PORTD=0x00;
			break;
	 }

  return Loc_enuReturn;
	
}

/*
    DIO_tenuErrorStatus Loc_enuReturn;

	if(Cpy_enuPortNumber < DIO_enuPortsNumber)
	    {
		 if(Cpy_enuPinNumber < DIO_enuPinsNumber)
		    {
             if(Cpy_enuPinDirection==DIO_enuOutput || Cpy_enuPinDirection==DIO_enuInput)
			 {
		     Loc_enuReturn= DIO_enuOK;





		     }
		     else
			 {
			  Loc_enuReturn= DIO_enuInvalidPinDirection;
			 }



		     }
		 else
			{
			 Loc_enuReturn= DIO_InvalidPinNumber;
			}
	    }
	else
	    {
		 Loc_enuReturn= DIO_InvalidPortNumber;
        }

return Loc_enuReturn;
}

*/