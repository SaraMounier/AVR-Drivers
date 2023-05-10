#ifndef _EXTINT_H
#define _EXTINT_H

#include "STD_TYPES.h"

typedef enum
{
	EXINT_enuOK = 0,
	EXINT_enuNOK ,
	EXINT_enuNullPtr,
	EXINT_enuInvalidINT0_Cfg,
	EXINT_enuInvalidINT1_Cfg,
	EXINT_enuInvalidINT2_Cfg,
	EXINT_enuGIDisabled,
	EXINT_enuInvalidGICR_PIN,
	EXINT_enuInvalidGIFR_PIN

}EXINT_tenuErrorStatus;

EXINT_tenuErrorStatus EXINT_Init(void);
//EXINT_tenuErrorStatus Set_MCUCR_INTx(u8 EX_INTx_MODE,u8 INTx);
//EXINT_tenuErrorStatus Set_MCUCSR_INT2(u8 EX_INT2_MODE);
EXINT_tenuErrorStatus GICR_ENABLE_Request(u8 INTx);
EXINT_tenuErrorStatus GICR_DISBLE_Request(u8 INTx);
EXINT_tenuErrorStatus GIFR_Clear(u8 INTx);
EXINT_tenuErrorStatus GIFR_GET_STATUS(u8 INTx,u8 *GIFR_status);

#endif /*_EXTINT_*/