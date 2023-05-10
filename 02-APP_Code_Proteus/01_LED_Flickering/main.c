/*
 * DIO_Driver_Application_01.c
 *
 * Created: 1/19/2023 4:43:03 AM
 * Author: Sara Mounier
 */ 
# define F_CPU 1000000UL
#define Number_of_Leds 8
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "LED.h"


int main(void)
{     u8 Loc_enu_Init_ReturnFunction=0;  
	  s8 LED_Number;
    Loc_enu_Init_ReturnFunction=DIO_Init();
	   while(1)
    {
	if(Loc_enu_Init_ReturnFunction==DIO_enuOK){

	LED_tenuErrorStatus Loc_enuReturnFunction=0;
    
		for(LED_Number=0;LED_Number<Number_of_Leds;LED_Number++)
    {
	   Loc_enuReturnFunction= Turn_LED_OFF ( DIO_enuPortA , LED_Number);
    }
 
	    for(LED_Number=0;LED_Number<Number_of_Leds;LED_Number++)
	    {
		   Loc_enuReturnFunction= Turn_LED_ON( DIO_enuPortA , LED_Number);
		   if(Loc_enuReturnFunction==LED_enuOK){ _delay_ms(500);}
			 
		    Loc_enuReturnFunction=Turn_LED_OFF( DIO_enuPortA , LED_Number);
			if(Loc_enuReturnFunction==LED_enuOK){ _delay_ms(500);}
		}
		
	    for(LED_Number=Number_of_Leds-1;LED_Number>=0;LED_Number--)
	    {
		   Loc_enuReturnFunction= Turn_LED_ON( DIO_enuPortA , LED_Number);
			if(Loc_enuReturnFunction==LED_enuOK){_delay_ms(500);}

			Loc_enuReturnFunction=Turn_LED_OFF( DIO_enuPortA , LED_Number);
			if(Loc_enuReturnFunction==LED_enuOK){_delay_ms(500);}
			
		}
			
		}
		}
		}