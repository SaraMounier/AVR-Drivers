/*************************************************************
 * 
 * Filename: USART.c
 * Description: Source file of the USART driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "USART_Cfg.h"
#include "USART_Priv.h"
#include "USART.h"

static TX Send={.Status=TX_IDLE};
static RX Receive={.Status=RX_IDLE};

USART_ErrorStatus_t USART_getFlagStatus(u8 FlagName,u8* FlagValue)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	if(FlagValue ==NULL)
	{
		  Loc_USART_ErrorStatus=USART_enuNullPtr;
	}
	else
	{
	   	if( FlagName== UCSRA_RXC || FlagName== UCSRA_TXC || FlagName== UCSRA_UDRE || FlagName== UCSRA_FE || FlagName== UCSRA_DOR || FlagName== UCSRA_PE )
		{
			 *FlagValue	= (USART_UCSRA >> FlagName) & 0x01;
			 Loc_USART_ErrorStatus=USART_enuOK;
		}
		else
		{
			 Loc_USART_ErrorStatus=USART_enuNOK;			
		}
	}
   return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_setFlagStatus(u8 FlagName,u8 FlagValue)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	  	if( FlagName== UCSRA_RXC || FlagName== UCSRA_TXC || FlagName== UCSRA_UDRE || FlagName== UCSRA_FE || FlagName== UCSRA_DOR || FlagName== UCSRA_PE )
	  	{
			if(FlagValue==ENABLE) 
			{
				 USART_UCSRA |= 1<< FlagName ;

			} 
			else if(FlagValue==DISABLE)
			{
				USART_UCSRA &= ~(1<< FlagName) ;

			}
		  	Loc_USART_ErrorStatus=USART_enuOK;
	  	}
	  	else
	  	{
		  	Loc_USART_ErrorStatus=USART_enuNOK;
	  	}
		  return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_setInterruptStatus(u8 InterruptName,u8 InterruptValue)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	if( InterruptName== UCSRB_RXCIE || InterruptName== UCSRB_TXCIE || InterruptName== UCSRB_UDRIE )
	{
		if(InterruptValue==ENABLE)
		{
			USART_UCSRB |= (1 << InterruptName);
		 	Loc_USART_ErrorStatus=USART_enuOK;
		}
		else if(InterruptValue==DISABLE)
		{
			USART_UCSRB &= ~(1 << InterruptName);
			Loc_USART_ErrorStatus=USART_enuOK;
		}
		else
		{
			Loc_USART_ErrorStatus=USART_enuNOK;				
		}
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK;
	}
	return Loc_USART_ErrorStatus;	
}

USART_ErrorStatus_t USART_set_Rx_Tx_Status(u8 UCSRB_XXEN,u8 X_Status)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	if( UCSRB_XXEN == UCSRB_TXEN || UCSRB_XXEN == UCSRB_RXEN )
	{
		if(X_Status==ENABLE)
		{
			USART_UCSRB |= (1 << UCSRB_XXEN);
			Loc_USART_ErrorStatus=USART_enuOK;
		}
		else if(X_Status==DISABLE)
		{
			USART_UCSRB &= ~(1 << UCSRB_XXEN);
			Loc_USART_ErrorStatus=USART_enuOK;
		}
		else
		{
			Loc_USART_ErrorStatus=USART_enuNOK;
		}
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK;
	}
	return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_setCharSize(u8 X_bit)
{
	u8 TempVar;
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;	
	if( X_bit== _5_bit || X_bit== _6_bit || X_bit== _6_bit || X_bit== _7_bit || X_bit== _8_bit || X_bit== _9_bit )
	{
		if(( X_bit>>2 )==1)
		{
			USART_UCSRB |= ( 1<< UCSRB_UCSZ2);
		}
		else
		{
			USART_UCSRB &= ~( 1<< UCSRB_UCSZ2);
		}
		TempVar = USART_UCSRC & (CLR_MASK_2BITS << UCSRC_UCSZ0);
		USART_UCSRC = TempVar | ((X_bit & 0B11)  << UCSRC_UCSZ0);
	}
	else
	{
		 Loc_USART_ErrorStatus=USART_enuNOK;	
	}
	return Loc_USART_ErrorStatus;
}  

USART_ErrorStatus_t USART_getNinthBitReceivedchar(u8* Receivedchar_8bit)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;	
	u8 TempVar;
	TempVar=(USART_UCSRB >>UCSRB_UCSZ2 )& 0B01;
	TempVar =TempVar << 2;
	TempVar |= ((USART_UCSRC >>UCSRC_UCSZ0 ) & 0B11);
	if(Receivedchar_8bit !=NULL)
	{
		if(TempVar==_9_bit)
		{
		 *Receivedchar_8bit= (USART_UCSRB >>UCSRB_RXB8 )& 0B01;
		}
		else
		{
			Loc_USART_ErrorStatus=USART_enuNOK;
		}
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNullPtr;	
	}
	return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_sendNinthBitTransmittedchar(u8 Transmittedchar_8bit)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	u8 TempVar;
	TempVar=(USART_UCSRB >>UCSRB_UCSZ2 )& 0B01;
	TempVar =TempVar << 2;
	TempVar |= ((USART_UCSRC >>UCSRC_UCSZ0 ) & 0B11);
	if(TempVar==_9_bit)
	{	 
		if(Transmittedchar_8bit==1)
		{
			USART_UCSRB |= ( 1<< UCSRB_TXB8 );	
		}
		else if(Transmittedchar_8bit==0)
		{
			USART_UCSRB &= ~( 1<< UCSRB_TXB8 );
		}
		else
		{
			Loc_USART_ErrorStatus=USART_enuNOK;
		}		
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK;
	}
	return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_asyncDoubleTransmissionSpeed()
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;	
	u8 USART_operationMode = (USART_UCSRC >>UCSRC_UMSEL) & 0x01;
	if(USART_operationMode ==USART_OPERATION_ASYNCH)
	{
		USART_UCSRA |= (1<<UCSRA_U2X) ;
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK;
	}
	return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_enableMultiProcessorTransmission()
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	USART_UCSRA |= (1<<UCSRA_MPCM) ;
	return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_getReceivedData(u8* ReceivedData)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	if(ReceivedData !=NULL)
	{
		*ReceivedData=USART_UDR;	
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNullPtr;
	}
	return Loc_USART_ErrorStatus;
}
USART_ErrorStatus_t USART_sendTransmittedData(u8 TransmittedData)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	USART_UDR=TransmittedData;
	return Loc_USART_ErrorStatus;	
}

USART_ErrorStatus_t USART_selectUCSRCRegister()
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	USART_UCSRC |= (1<<UCSRC_URSEL) ;
	return Loc_USART_ErrorStatus;	
}

USART_ErrorStatus_t USART_selectOperationMode(u8 UCSRC_OPERATION_X)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	if(UCSRC_OPERATION_X==USART_OPERATION_SYNCH)
	{
	  	USART_UCSRC |= (1<<UCSRC_UMSEL) ;
	}
	else if(UCSRC_OPERATION_X==USART_OPERATION_ASYNCH)
	{
		USART_UCSRC &= ~(1<<UCSRC_UMSEL) ;
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK;
	}
	return Loc_USART_ErrorStatus;	
}

USART_ErrorStatus_t USART_selectParityMode(u8 UCSRC_PARITY_X)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	u8 TempVar = USART_UCSRC | (CLR_MASK_2BITS << UCSRC_UPM0);
	USART_UCSRC = TempVar | (UCSRC_PARITY_X << UCSRC_UPM0);
	return Loc_USART_ErrorStatus;	
}

USART_ErrorStatus_t USART_selectStopBit(u8 STOP_X_BIT)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	if(STOP_X_BIT==STOP_2_BIT)
	{
		USART_UCSRC |= (1 << UCSRC_USBS);	
	}
	else if(STOP_X_BIT==STOP_1_BIT)
	{
		USART_UCSRC &= ~(1 << UCSRC_USBS);
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK;
	}
	return Loc_USART_ErrorStatus;	
}

USART_ErrorStatus_t USART_selectCLKPolarity(u8 TX_X_EDGE_RX_X_EDGE)
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	if(TX_X_EDGE_RX_X_EDGE == TX_FALLING_EDGE_RX_RISING_EDGE)
	{
		USART_UCSRC |= (1 << UCSRC_USBS);
	}
	else if(TX_X_EDGE_RX_X_EDGE == TX_RISING_EDGE_RX_FALLING_EDGE)
	{
		USART_UCSRC &= ~(1 << UCSRC_USBS);
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK;
	}
	return Loc_USART_ErrorStatus;
}						 

USART_ErrorStatus_t USART_selectUBRRHRegister()
{
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK;
	USART_UCSRC &= ~(1<<UCSRC_URSEL) ;
	return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_setBaudRate()
{	
	USART_ErrorStatus_t	 Loc_USART_ErrorStatus=USART_enuOK; 
	u16 BaudRate= SELECTED_BAUD_RATE_VALUE ;
	
	if( (( USART_UBRRH >> UCSRC_URSEL) & 0x01) == 0 )
	{
		USART_UBRRL = BaudRate & 0xff ;
		USART_UBRRH |= (BaudRate >> 0xff) ;	
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNOK; 
	}
	return Loc_USART_ErrorStatus;

}

USART_ErrorStatus_t USART_sendBuffer(u8* Data, u32 Size)
{
	USART_ErrorStatus_t  Loc_USART_ErrorStatus=USART_enuOK;
	u8 flagVAl=0;
	if (Send.Status==TX_IDLE)
	{
		Send.Data=Data;
		Send.Size=Size;
		Send.Status=TX_BUSY;
		Send.Idx=0;	
		USART_setInterruptStatus(UCSRB_TXCIE,ENABLE);
		USART_getFlagStatus(UCSRA_UDRE,&flagVAl);
		if(flagVAl == 1)
		{
			USART_sendTransmittedData(Send.Data[Send.Idx]);
		}
		Send.Idx++;
		USART_setInterruptStatus(UCSRB_UDRIE,ENABLE);

		Loc_USART_ErrorStatus=USART_enuOK;
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuBUSY;		
	}
	return Loc_USART_ErrorStatus;
}

USART_ErrorStatus_t USART_receiveBuffer(u8* Data, u32 Size)
{
	USART_ErrorStatus_t  Loc_USART_ErrorStatus=USART_enuOK;
	if (Receive.Status==RX_IDLE )
	{
		Receive.Data=Data;
		Receive.Size=Size;
		Receive.Status=RX_BUSY;
		Receive.Idx=0;
		USART_setInterruptStatus(UCSRB_RXCIE,ENABLE);

		Loc_USART_ErrorStatus=USART_enuOK;
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuBUSY;
	}
	return Loc_USART_ErrorStatus;
}


void (*TX_NotifyFunction)(void)=NULL;
 USART_ErrorStatus_t USART_TX_CallBackFunction(void (*TX_APP_NotifyFunction)(void))
 {
	USART_ErrorStatus_t   Loc_USART_ErrorStatus=USART_enuOK;
// 	u8 FlagValue,Flag2Value;
// 	USART_getFlagStatus(UCSRA_TXC,& FlagValue);
// 	USART_getFlagStatus(UCSRA_UDRE,& Flag2Value);
// 
 	if(TX_APP_NotifyFunction !=NULL)
	 {
// 		if((/*FlagValue==1 || */ Flag2Value==1 ) && Send.Idx < Send.Size && Send.Status == TX_BUSY) 
// 		{
// 			USART_sendTransmittedData(Send.Data[Send.Idx]);
// 			Send.Idx ++;
// 			USART_UCSRA |= 1<< UCSRA_TXC;
// 			USART_UCSRA |= 1<< UCSRA_UDRE;
// 		}
// 		else
// 		{
// 			Send.Status=TX_IDLE;
			TX_NotifyFunction=TX_APP_NotifyFunction; 
//		}
	 }
	 else
	 {
		 Loc_USART_ErrorStatus=USART_enuNullPtr;
	 }
	 return Loc_USART_ErrorStatus;
}

void (*RX_NotifyFunction)(void)=NULL;
USART_ErrorStatus_t USART_RX_CallBackFunction(void (*RX_APP_NotifyFunction)(void))
{
	USART_ErrorStatus_t   Loc_USART_ErrorStatus=USART_enuOK;
// 	u8 	FlagValue,Flag2Value;
// 		USART_getFlagStatus(UCSRA_UDRE,& Flag2Value);
// 		USART_getFlagStatus(UCSRA_RXC,& FlagValue);

	if(RX_APP_NotifyFunction !=NULL)
	{
// 		if((FlagValue==1 || Flag2Value==0) && Receive.Idx <= Receive.Size && Receive.Status==RX_BUSY)
// 		{
// 			USART_getReceivedData(& Receive.Data[Receive.Idx]);
// 			Receive.Idx ++;
// 			USART_UCSRA |= 1<< UCSRA_RXC;
// 		}
// 		else
// 		{
			RX_NotifyFunction=RX_APP_NotifyFunction;
// 			Receive.Status=RX_IDLE;
// 		}	
	}
	else
	{
		Loc_USART_ErrorStatus=USART_enuNullPtr;
	}
	return Loc_USART_ErrorStatus;
}

 
void __vector_13 (void) __attribute__ ((signal));
void __vector_13 (void)
{
u8 	FlagValue;
USART_getFlagStatus(UCSRA_RXC,& FlagValue);
//	 while (!(USART_UCSRA & (1<<UCSRA_RXC)) );
	if((FlagValue==1 ) && Receive.Idx <= Receive.Size && Receive.Status==RX_BUSY)
	{
		USART_getReceivedData(& Receive.Data[Receive.Idx]);
		Receive.Idx ++;
		USART_UCSRA |= 1<< UCSRA_RXC;
	}
	else
	{
		Receive.Status=RX_IDLE;	
		RX_NotifyFunction();
		USART_setInterruptStatus(UCSRB_RXCIE,DISABLE);
	}
}

void __vector_14 (void) __attribute__ ((signal));
void __vector_14 (void)
{
	
	u8 FlagValue;
	USART_getFlagStatus(UCSRA_UDRE,& FlagValue);
//	while((USART_UCSRA & 1<<UCSRA_UDRE) !=1);
	if(( FlagValue==1 ) && Send.Idx < Send.Size && Send.Status == TX_BUSY)
	{
		USART_sendTransmittedData(Send.Data[Send.Idx]);
		USART_UCSRA |= 1<< UCSRA_UDRE; 
		Send.Idx ++;
	}
	else
	{
		Send.Status=TX_IDLE;
		TX_NotifyFunction();
		USART_setInterruptStatus(UCSRB_UDRIE,DISABLE);
	}
}

