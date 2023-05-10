#ifndef _EXTERNAL_INTERRUPT_CFG_H
#define _EXTERNAL_INTERRUPT_CFG_H

/*To set MCUSR*/
#define MASKED_BITS 2
#define CLR_MASK 0b11
#define INT0 0
#define INT1 1
#define INT2 2

#define ENABLED 1
#define DISABLED 0

 /*General Interrupt Control Register – GICR - INITIAL_VALUE 0*/
#define MCUCSR_ISC2 6 

/*General Interrupt Control Register – GICR - INITIAL_VALUE 0*/
#define GICR_INT2 5
#define GICR_INT0 6
#define GICR_INT1 7

/*General Interrupt Flag Register – GIFR- INITIAL_VALUE 0*/
#define GIFR_INTF2 5
#define GIFR_INTF0 6
#define GIFR_INTF1 7
#define GIFR_CLEAR 1


/*EX_INT0_MODES*/
#define EX_INT0_LOW_LEVEL 0b00
#define EX_INT0_ANY_LOGICAL_CHANGE 0b01
#define EX_INT0_FALLING_EDGE 0b10
#define EX_INT0_RISING_EDGE 0b11

/*EX_INT1_MODES*/
#define EX_INT1_LOW_LEVEL 0b00
#define EX_INT1_ANY_LOGICAL_CHANGE 0b01
#define EX_INT1_FALLING_EDGE 0b10
#define EX_INT1_RISING_EDGE 0b11
#define EX_INT1_DISABLE  GICR_INT1

/*EX_INT2_MODES*/
#define EX_INT2_FALLING_EDGE 0b0
#define EX_INT2_RISING_EDGE 0b1
#define EX_INT2_DISABLE GICR_INT2


/*INT0,INT1,INT2 SELECTED MODES*/
#define EX_INT0_MODE EX_INT0_RISING_EDGE
#define EX_INT1_MODE EX_INT1_RISING_EDGE
#define EX_INT2_MODE EX_INT2_RISING_EDGE
#define EX_INT0_CONTROL ENABLED
#define EX_INT1_CONTROL ENABLED
#define EX_INT2_CONTROL ENABLED

#endif /*_EXTERNAL_INTERRUPT_CFG_H*/

/*
• INT1 – Port D, PIN 3
INT1, External Interrupt Source 1: The PD3 pin can serve as an external interrupt source.
• INT0 – Port D, PIN 2
INT0, External Interrupt Source 0: The PD2 pin can serve as an external interrupt source.
INT2 - PORT B, PIN 2
*/