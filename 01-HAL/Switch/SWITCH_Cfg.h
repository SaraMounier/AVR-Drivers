#ifndef SWITCH_Cfg_H
#define SWITCH_Cfg_H

#include "STD_TYPES.h"

#define Switches_Number 2
#define Increment_Button 0
#define Decrement_Button 1


typedef struct
{
	u8 Port_Num;
	u8 Pin_Num;
	u8 Active_Status;
	u8 Initial_State;	
} SWITCH_tstrSwitch_cfg;

extern const SWITCH_tstrSwitch_cfg Switches_Cfg [Switches_Number];
#endif //SWITCH_Cfg_H