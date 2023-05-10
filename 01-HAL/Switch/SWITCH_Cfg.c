#include "SWITCH_Cfg.h"
#include "SWITCH.h"
#include "DIO.h"


 const SWITCH_tstrSwitch_cfg Switches_Cfg [Switches_Number]=
{
	[Increment_Button]={
		.Port_Num= DIO_enuPortB,
		.Pin_Num= DIO_enuPin0,
		.Active_Status= SWITCH_Pull_Up,
		.Initial_State= SWITCH_Released},
	[Decrement_Button]={	
		.Port_Num= DIO_enuPortB,
		.Pin_Num= DIO_enuPin1,
		.Active_Status= SWITCH_Pull_Up,
		.Initial_State= SWITCH_Released}	
	
	};