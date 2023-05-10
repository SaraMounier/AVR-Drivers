#include "STD_TYPES.h"
#include "DIO.h"
#include "DIO_piv.h"
#include "DIO_cfg.h"
#include "LED.h"
#include "LED_Cfg.h"
#include "Seven_Segment.h"
#include "avr/delay.h"
void Seven_Segment_Increment(u8 Min_Number,u8 Max_Number){
	if(Min_Number >=0 && Max_Number <= 15){
u8 Seven_Segment_Values[16]={ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,NINE,TEN,ELEVEN,TWELVE,THERTEEN,FOURTEEN,FIFTEEN};
u8 i;
for(i=Min_Number;i<Max_Number+1;i++){
	Turn_Group_of_LEDs_ON (DIO_enuPortA,Seven_Segment_Values[i]);
	_delay_ms(500);
	Turn_Port_of_LEDs_OFF(DIO_enuPortA);
	_delay_ms(50);
}
}
else {Turn_Port_of_LEDs_OFF(DIO_enuPortA);
}
}