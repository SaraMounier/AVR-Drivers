#ifndef _EXTERNAL_INTERRUPT_PIV_H
#define _EXTERNAL_INTERRUPT_PIV_H
#include "STD_TYPES.h"

#define MCUCR 	(*(volatile u8*)(0x55))
#define MCUCSR  (*(volatile u8*)(0x54))
#define GICR    (*(volatile u8*)(0x5B))
#define GIFR    (*(volatile u8*)(0x5A))

#endif /*_EXTERNAL_INTERRUPT_PIV_H*/


