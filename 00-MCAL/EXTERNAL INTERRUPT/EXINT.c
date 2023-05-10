
#include "STD_TYPES.h"
#include "EXINT.h"
#include "EXINT_Cfg.h"
#include "EXINT_piv.h"
#include "GINT_piv.h"
#include "GINT.h"
#include "BIT_MATH.h"

#define Set_MCUCR_INTx(MCUCR_reg, EXINTxMode, INTx) \
do {\
	char temp_var= MCUCR_reg;\
	temp_var= MCUCR_reg & ~(CLR_MASK <<(INTx*MASKED_BITS));\
	MCUCR_reg= temp_var | (EXINTxMode<<(INTx*MASKED_BITS));\
} while(0)



#define Set_MCUCSR_INT2(MCUCSR_reg, EXINT2Mode) \
do{\
if (EXINT2Mode == EX_INT2_RISING_EDGE)\
	{\
	SET_BIT(MCUCSR_reg,MCUCSR_ISC2);\
	}\
else if (EXINT2Mode == EX_INT2_FALLING_EDGE)\
	{\
	CLR_BIT(MCUCSR_reg,MCUCSR_ISC2);\
	}}\
	while(0)


EXINT_tenuErrorStatus EXINT_Init(void)
{	
	EXINT_tenuErrorStatus Loc_EXINTenuErrorState = EXINT_enuOK;
	GI_tenuErrorStatus Loc_GIenuErrorState =  GI_enuEnable();
	
	#if EX_INT0_MODE == EX_INT0_LOW_LEVEL	
		Set_MCUCR_INTx(MCUCR,EX_INT0_LOW_LEVEL, INT0);
	#elif EX_INT0_MODE == EX_INT0_ANY_LOGICAL_CHANGE
		Set_MCUCR_INTx(MCUCR,EX_INT0_ANY_LOGICAL_CHANGE, INT0);
	#elif EX_INT0_MODE == EX_INT0_FALLING_EDGE
		Set_MCUCR_INTx(MCUCR,EX_INT0_FALLING_EDGE, INT0);
	#elif EX_INT0_MODE == EX_INT0_RISING_EDGE
		Set_MCUCR_INTx(MCUCR,EX_INT0_RISING_EDGE, INT0);
	#else
		Loc_EXINTenuErrorState = EXINT_enuInvalidINT0_Cfg;
	#endif

	
	#if EX_INT0_CONTROL == ENABLED
		SET_BIT(GICR, GICR_INT0);	
	#elif EX_INT0_CONTROL == DISABLED
		CLR_BIT(GICR, GICR_INT0);	
	#endif
	
	
	#if EX_INT1_MODE == EX_INT1_LOW_LEVEL	
		Set_MCUCR_INTx(MCUCR,EX_INT1_LOW_LEVEL, INT1);
	#elif EX_INT1_MODE == EX_INT1_ANY_LOGICAL_CHANGE
		Set_MCUCR_INTx(MCUCR,EX_INT1_ANY_LOGICAL_CHANGE, INT1);
	#elif EX_INT1_MODE == EX_INT1_FALLING_EDGE
		Set_MCUCR_INTx(MCUCR,EX_INT1_FALLING_EDGE, INT1);
	#elif EX_INT1_MODE == EX_INT1_RISING_EDGE
		Set_MCUCR_INTx(MCUCR,EX_INT1_RISING_EDGE, INT1);
	#else
		Loc_EXINTenuErrorState = EXINT_enuInvalidINT1_Cfg;		
	#endif
	
	
	#if EX_INT1_CONTROL == ENABLED
	SET_BIT(GICR, GICR_INT1);
	#elif EX_INT1_CONTROL == DISABLED
	CLR_BIT(GICR, GICR_INT1);
	#endif

	#if EX_INT2_MODE == EX_INT2_FALLING_EDGE
		Set_MCUCSR_INT2(MCUCSR,EX_INT2_FALLING_EDGE);
	#elif EX_INT2_MODE == EX_INT2_RISING_EDGE
		Set_MCUCSR_INT2(MCUCSR,EX_INT2_RISING_EDGE);
	#else
		Loc_EXINTenuErrorState = EXINT_enuInvalidINT2_Cfg;
	#endif
	
	
	#if EX_INT2_CONTROL == ENABLED
	SET_BIT(GICR, GICR_INT2);
	#elif EX_INT2_CONTROL == DISABLED
	CLR_BIT(GICR, GICR_INT2);
	#endif

return Loc_EXINTenuErrorState;
}


EXINT_tenuErrorStatus GICR_ENABLE_Request(u8 INTx)
{ 
EXINT_tenuErrorStatus Loc_EXINTenuErrorState=EXINT_enuOK;
	if(GET_BIT(SREG,GI_PIN)==ENABLED)
	{
		if (INTx==INT0)
			{
			SET_BIT(GICR,GICR_INT0);
			}
		else if (INTx==INT1)
			{
			SET_BIT(GICR,GICR_INT1);
			}
		else if (INTx==INT2)
			{
			SET_BIT(GICR,GICR_INT2);
			}
	}
	else if(GET_BIT(SREG,GI_PIN)==DISABLED)
	{
		Loc_EXINTenuErrorState=EXINT_enuGIDisabled;
	}
return Loc_EXINTenuErrorState;
}

EXINT_tenuErrorStatus GICR_DISBLE_Request(u8 INTx)
{
EXINT_tenuErrorStatus Loc_EXINTenuErrorState=EXINT_enuOK;
if (INTx==INT0)
	{
	CLR_BIT(GICR,GICR_INT0);
	}
else if (INTx==INT1)
	{
	CLR_BIT(GICR,GICR_INT1);
	}
else if (INTx==INT2)
	{
	CLR_BIT(GICR,GICR_INT2);
	}
else
	{
	Loc_EXINTenuErrorState=EXINT_enuInvalidGICR_PIN;	
	}
return Loc_EXINTenuErrorState;
}


EXINT_tenuErrorStatus GIFR_Clear(u8 INTx)
{
EXINT_tenuErrorStatus Loc_EXINTenuErrorState=EXINT_enuOK;
if (INTx==INT0)
	{
	SET_BIT(GIFR,GICR_INT0);
	}
else if (INTx==INT1)
	{
	SET_BIT(GIFR,GICR_INT1);
	}
else if (INTx==INT2)
	{
	SET_BIT(GIFR,GICR_INT2);
	}
else
	{
	Loc_EXINTenuErrorState=EXINT_enuInvalidGIFR_PIN;	
	}
return Loc_EXINTenuErrorState;	
}

EXINT_tenuErrorStatus GIFR_GET_STATUS(u8 INTx,u8 *GIFR_status)
{
EXINT_tenuErrorStatus Loc_EXINTenuErrorState=EXINT_enuOK;
if (INTx==INT0)
	{
	*GIFR_status=GET_BIT(GIFR,GICR_INT0);
	}
else if (INTx==INT1)
	{
	*GIFR_status=GET_BIT(GIFR,GICR_INT1);
	}
else if (INTx==INT2)
	{
	*GIFR_status=GET_BIT(GIFR,GICR_INT2);
	}
else
	{
	Loc_EXINTenuErrorState=EXINT_enuInvalidGIFR_PIN;	
	}
return Loc_EXINTenuErrorState;
}


/*
EXINT_tenuErrorStatus Set_MCUCR_INTx(u8 EXINTxMode,u8 INTx)
{	
	
	EXINT_tenuErrorStatus Loc_EXINTenuErrorState = EXINT_enuOK;
	u8 temp_var=MCUCR;
	temp_var=MCUCR & (~(CLR_MASK<<(INTx*MASKED_BITS)));
	MCUCR=temp_var | (EXINTxMode<<(INTx*MASKED_BITS));
	
	return Loc_EXINTenuErrorState;
}
*/

/*TO ENABLE THE INTERRUPT:CLEAR GISR THEN CHANGE MCUCSR*/
/*
EXINT_tenuErrorStatus Set_MCUCSR_INT2(u8 EXINT2Mode)
{
	EXINT_tenuErrorStatus Loc_EXINTenuErrorState = EXINT_enuOK;
if (EXINT2Mode == EX_INT2_RISING_EDGE)
	{
	SET_BIT(MCUCSR,MCUCSR_ISC2);
	}
else if (EXINT2Mode == EX_INT2_FALLING_EDGE)
	{
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
	}
else 
	{
	Loc_EXINTenuErrorState=	EXINT_enuInvalidINT2_Cfg;
	}
	return Loc_EXINTenuErrorState;
}
*/
