#ifndef _GLOBAL_INTERRUPT_H
#define _GLOBAL_INTERRUPT_H
#define GI_PIN 7
#define GI_ENABLED 1
#define GI_DISABLED 0

typedef enum
{
	GI_enuOK = 0,
	GI_enuNOK ,
	GI_enuNullPtr
}GI_tenuErrorStatus;

GI_tenuErrorStatus GI_enuInit(void);
GI_tenuErrorStatus GI_enuEnable(void);
GI_tenuErrorStatus GI_enuDisable(void);

#endif /*_GLOBAL_INTERRUPT_*/