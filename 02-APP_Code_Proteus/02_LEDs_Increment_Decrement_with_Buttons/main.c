/*
 * DIO_Button_drivers.c
 *
 * Created: 1/21/2023 8:44:06 AM
 * Author : sara Mounier
 */ 

#include "Increment_Decrement_Buttons_With_LEDs.h"
#include "SWITCH.h"
#include "DIO.h"

int main(void)
{
    /* Replace with your application code */
    
	
	while (1) {
	 Icrement_Decrement_Buttons(3, DIO_enuPortA, 0, 2, 2);
   }
}