/*
 * External_Interrupt.c
 *
 * Created: 1/30/2023 3:39:50 PM
 * Author : Sara Mounier
 */ 
#include "GINT_piv.h"
#include "GINT.h"
#include "EXINT.h"
#include "LED.h"
#include "DIO_piv.h"
#include "EXINT_Cfg.h"
#include<avr/interrupt.h>
#include<util/delay.h>
#define F_CPU 1000000ul

ISR (INT0_vect)          //External interrupt_zero ISR
{
	
	Turn_LED_ON (DIO_enuPortA , DIO_enuPin0);
	_delay_ms(2000);
	Turn_LED_OFF (DIO_enuPortA , DIO_enuPin0);

}
ISR (INT1_vect)        //External interrupt_one ISR
{
	
	Turn_LED_ON (DIO_enuPortA , DIO_enuPin1);
	_delay_ms(2000);
	Turn_LED_OFF (DIO_enuPortA , DIO_enuPin1);

}
ISR (INT2_vect)        //External interrupt_two ISR
{
	Turn_LED_ON (DIO_enuPortA , DIO_enuPin2);
	_delay_ms(2000);
	Turn_LED_OFF (DIO_enuPortA , DIO_enuPin2);

}

int main (void){
DIO_Init();
GI_enuInit();
EXINT_Init();
while (1)
{
}
return 0;
}
