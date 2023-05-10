#include "STD_TYPES.h"
#include "GINT.h"
#include "GINT_piv.h"
#include "BIT_MATH.h"

GI_tenuErrorStatus GI_enuInit(void)
{
	GI_tenuErrorStatus Loc_enuErrorStatus = GI_enuOK;
	SET_BIT(SREG,GI_PIN);
	u8 Loc_GIPinStatus=GET_BIT(SREG,GI_PIN);
	if(Loc_GIPinStatus==GI_DISABLED)
	{
		Loc_enuErrorStatus=GI_enuNOK;
	}
	else if (Loc_GIPinStatus==GI_ENABLED)
	{
		Loc_enuErrorStatus=GI_enuOK;
	}
	return Loc_enuErrorStatus;	
}
GI_tenuErrorStatus GI_enuEnable(void)
{
	GI_tenuErrorStatus Loc_enuErrorStatus = GI_enuOK;
	SET_BIT(SREG,GI_PIN);
	u8 Loc_GIPinStatus=GET_BIT(SREG,GI_PIN);
	if(Loc_GIPinStatus==GI_DISABLED)
	{
		Loc_enuErrorStatus=GI_enuNOK;
	}
	else if (Loc_GIPinStatus==GI_ENABLED)
	{
		Loc_enuErrorStatus=GI_enuOK;
	}
	return Loc_enuErrorStatus;	
}

GI_tenuErrorStatus GI_enuDisable(void)
{
	GI_tenuErrorStatus Loc_enuErrorStatus = GI_enuOK;
	CLR_BIT(SREG,GI_PIN);
	u8 Loc_GIPinStatus=GET_BIT(SREG,GI_PIN);
	if(Loc_GIPinStatus==GI_ENABLED)
	{
		Loc_enuErrorStatus=GI_enuNOK;
	}
	else if (Loc_GIPinStatus==GI_DISABLED)
	{
		Loc_enuErrorStatus=GI_enuOK;
	}
	return Loc_enuErrorStatus;
}
