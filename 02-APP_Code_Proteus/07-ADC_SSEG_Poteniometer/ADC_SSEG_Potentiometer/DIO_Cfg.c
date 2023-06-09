#include "DIO_Cfg.h"

const DIO_strPinCnfg_t DIO_strPinCnfg [32]=
{
	/*PORTA*//*Pin Direction*/ /*Pull_Up Pull_Down*/
	/*PIN0*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP },
	/*PIN1*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP },
	/*PIN2*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP },
	/*PIN3*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP },
	/*PIN4*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP },
	/*PIN5*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP },
	/*PIN6*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP},
	/*PIN7*/ {DIO_DIR_INPUT,   DIO_INPUT_PULL_UP },

	
	/*PORTB*//*Pin Direction*/ /*Pull_Up Pull_Down*/
	/*PIN8*/ {DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	/*PIN9*/ {DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },
	/*PIN10*/{DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },
	/*PIN11*/{DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },
	/*PIN12*/{DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },
	/*PIN13*/{DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },
	/*PIN14*/{DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },
	/*PIN15*/{DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },

	
	/*PORTC*//*Pin Direction*/ /*Pull_Up Pull_Down*/
	/*PIN16*/{DIO_DIR_OUTPUT,    DIO_INPUT_PULL_UP },
	/*PIN17*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	/*PIN18*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	/*PIN19*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	/*PIN20*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	/*PIN21*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	/*PIN22*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	/*PIN23*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_UP },
	
	/*PORTD*//*Pin Direction*/ /*Pull_Up Pull_Down*/
	/*PIN24*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_DOWN },
	/*PIN25*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_DOWN },
	/*PIN26*/{DIO_DIR_INPUT,    DIO_INPUT_PULL_UP   },
	/*PIN27*/{DIO_DIR_INPUT,    DIO_INPUT_PULL_UP   },
	/*PIN28*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_DOWN },
	/*PIN29*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_DOWN },
	/*PIN30*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_DOWN },
	/*PIN31*/{DIO_DIR_OUTPUT,   DIO_INPUT_PULL_DOWN }
};
