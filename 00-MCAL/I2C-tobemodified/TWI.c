/*************************************************************
 * 
 * Filename: TWI.c
 * Description: Source file of the TWI driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "TWI_Cfg.h"
#include "TWI_Priv.h"
#include "TWI.h"
TWI_TX TX ={.TWI_TX_Status=TWI_TX_IDLE, .TWI_TX_Idx=0};
TWI_RX RX ={.TWI_RX_Status=TWI_RX_IDLE , .TWI_RX_Idx=0};
static u8 i=0,j=0,Mode=MODE,TWSR_Status=0,Slave_Status=0,Slave_Ack_Status=0,Address_R_W=0x10;


TWI_ErrorStatus_t TWI_setBitRate(u8 BitRateValue)
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;	
	TWI_TWBR |=BitRateValue;
	return TWI_LocErrorStatus;
}

TWI_ErrorStatus_t TWI_getInterruptFlagValue(u8* InterruptFlagValue)
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	*InterruptFlagValue=(TWI_TWCR >> TWCR_TWINT) & 0X01; 
	return TWI_LocErrorStatus;
}
TWI_ErrorStatus_t TWI_clearInterruptFlagValue()
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	TWI_TWCR |= 1 << TWCR_TWINT;
	return TWI_LocErrorStatus;
}

TWI_ErrorStatus_t TWI_setAcknowledgeBitStatus(u8 ACK_STATUS)
{
   	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	if(ACK_STATUS==ENABLE)
	{
		TWI_TWCR |= (1 << TWCR_TWEA);
	}
	else if(ACK_STATUS==DISABLE)
	{
		TWI_TWCR &= ~(1 << TWCR_TWEA);
	}
	else
	{
		 TWI_LocErrorStatus=TWI_enuNOK;
	}
   	return TWI_LocErrorStatus;
}


TWI_ErrorStatus_t TWI_getAcknowledgeBitStatus(u8* ACK_STATUS)
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	*ACK_STATUS = (TWI_TWCR >> TWCR_TWEA)& 0x01;
    return TWI_LocErrorStatus;
}

TWI_ErrorStatus_t TWI_setStartBitCondition(u8 StartBitCondition)
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	if(StartBitCondition==ENABLE)
	{
		TWI_TWCR |= (1 << TWCR_TWSTA);
	}
	else if(StartBitCondition==DISABLE)
	{
		TWI_TWCR &= ~(1 << TWCR_TWSTA);
	}
	else
	{
		TWI_LocErrorStatus=TWI_enuNOK;
	}
	return TWI_LocErrorStatus;
}

TWI_ErrorStatus_t TWI_setStopBitCondition(u8 StopBitCondition)
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	if(StopBitCondition==ENABLE)
	{
		TWI_TWCR |= (1 << TWCR_TWSTO);
	}
	else if(StopBitCondition==DISABLE)
	{
		TWI_TWCR &= ~(1 << TWCR_TWSTO);
	}
	else
	{
		TWI_LocErrorStatus=TWI_enuNOK;
	}
	return TWI_LocErrorStatus;
}

TWI_ErrorStatus_t TWI_getWriteCollisionFlagValue(u8* WriteCollisionFlagValue)
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	*WriteCollisionFlagValue=(TWI_TWCR >> TWCR_TWWC) & 0X01;
	return TWI_LocErrorStatus;
}


TWI_ErrorStatus_t TWI_enable()
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
		TWI_TWCR |= (1 << TWCR_TWEN);
	return TWI_LocErrorStatus;
}
TWI_ErrorStatus_t TWI_disable()
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	TWI_TWCR &= ~(1 << TWCR_TWEN);
	return TWI_LocErrorStatus;
}

 TWI_ErrorStatus_t TWI_setInterruptStatus(u8 Interrupt_STATUS)
 {
	 TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	 if(Interrupt_STATUS==ENABLE)
	 {
		 TWI_TWCR |= (1 << TWCR_TWIE);
	 }
	 else if(Interrupt_STATUS==DISABLE)
	 {
		 TWI_TWCR &= ~(1 << TWCR_TWIE);
	 }
	 else
	 {
		 TWI_LocErrorStatus=TWI_enuNOK;
	 }
	 return TWI_LocErrorStatus;
 }

 TWI_ErrorStatus_t TWI_getStatus(u8* TWI_STATUS)
 {
	 TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	 u8 TempVar=(TWI_TWSR >>TWSR_TWS3) & 0b11111;
	 *TWI_STATUS= TempVar;
	return TWI_LocErrorStatus;
 }
 
  TWI_ErrorStatus_t TWI_setPrescaler(u8 TWI_PRESCALER_X)
  {
	 TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	 u8 TempVar=TWI_TWSR & ~(0B11<<TWSR_TWPS0);
	 TWI_TWSR = TempVar | (TWI_PRESCALER_X	<< TWSR_TWPS0)	;
	 return TWI_LocErrorStatus;	  
  }
  
TWI_ErrorStatus_t TWI_TXSendBuffer(u8* TransmittedData, u8 Size)
{
	 TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	 if (TX.TWI_TX_Status==TWI_TX_IDLE)
	 {
		TX.TWI_TX_Data= TransmittedData;
		TX.TWI_TX_Size=Size;
		TX.TWI_TX_Idx=0;
		TX.TWI_TX_Status=TWI_TX_BUSY;
		TWI_setInterruptStatus(ENABLE);
//		TWI_TWDR=TX.TWI_TX_Data[TX.TWI_TX_Idx];
	 }				 
	 return TWI_LocErrorStatus;	
}
TWI_ErrorStatus_t TWI_RXReceiveBuffer(u8* ReceivedData, u8 Size)
{
	 TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	 if (RX.TWI_RX_Status==TWI_RX_IDLE)
	 {
		RX.TWI_RX_Data= ReceivedData;
		RX.TWI_RX_Size=Size;
		RX.TWI_RX_Idx=0;
		RX.TWI_RX_Status=TWI_RX_BUSY;
		TWI_setInterruptStatus(ENABLE);
//		RX.TWI_RX_Data[TX.TWI_TX_Idx]= TWI_TWDR;
	 }
	 return TWI_LocErrorStatus;	
}

TWI_ErrorStatus_t TWI_setSlaveAddress(u8 TWI_SlaveAddress)
{
	 TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	 u8 TempVar=TWI_TWAR & ~(0B1111111<< TWAR_TWA0);
	 TWI_TWAR = TempVar | (TWI_SlaveAddress	<< TWAR_TWA0)	;
	 return TWI_LocErrorStatus;
}

TWI_ErrorStatus_t TWI_setGeneralCallRecognitionStatus(u8 GeneralCallRecogStatus)
 {
	 TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	 if(GeneralCallRecogStatus == ENABLE)
	 {
		 TWI_TWAR |= (1 << TWAR_TWGCE);
	 }
	 else if(GeneralCallRecogStatus == DISABLE)
	 {
		 TWI_TWAR &= ~(1 << TWAR_TWGCE);
	 }
	 else
	 {
		 TWI_LocErrorStatus=TWI_enuNOK;
	 }
	 return TWI_LocErrorStatus;
 }
TWI_ErrorStatus_t TWI_getGeneralCallRecognitionStatus(u8* GeneralCallRecogStatus)
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	*GeneralCallRecogStatus=(TWI_TWAR >> TWAR_TWGCE) & 0X01;
	return TWI_LocErrorStatus;
}

void (*TWI_NotifyApp)(void)=NULL;
TWI_ErrorStatus_t TWI_setCallBackFunction(void (*TWI_cbf)(void)) 
{
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	if(TWI_cbf !=NULL)
	{
		TWI_NotifyApp=TWI_cbf;	
	}
	else
	{
		TWI_LocErrorStatus=TWI_enuNullPtr;
	}
	return TWI_LocErrorStatus;
}


 TWI_ErrorStatus_t TWI_sendByte(u8 Data )
 {
	  TWI_ErrorStatus_t	TWI_LocErrorStatus=TWI_enuOK;
	  TWI_TWDR=Data;
	  return TWI_LocErrorStatus;
 }
 TWI_ErrorStatus_t TWI_receiveByte(u8* Data )
 {
	 TWI_ErrorStatus_t	TWI_LocErrorStatus=TWI_enuOK;
	 *Data=TWI_TWDR;
	 return TWI_LocErrorStatus;
 }
 TWI_ErrorStatus_t TWI_setOperation(u8 R_W)
 {
	TWI_ErrorStatus_t TWI_LocErrorStatus=TWI_enuOK;
	if(R_W==READ)
	{
		TWI_TWDR |= (1 <<0);
	}
	else if(R_W==WRITE)
	{
		TWI_TWDR &= ~(1 <<0);
	}
	else
	{
		TWI_LocErrorStatus=TWI_enuNOK;
	}
	return TWI_LocErrorStatus;	 
 }
 void TWI_error(void)
 {
	 if(TWSR_Status==0x68 ||TWSR_Status==0x78)
	 {
		 Mode=SLAVE_RECEIVER;
		 j=0;
	 }
	 if(TWSR_Status==0xC8 || TWSR_Status==0xC0 || TWSR_Status==0x98 ||TWSR_Status==0x88)
	 {
		 Mode= SLAVE_NOT_ADDRESSED;
		j=0;
	 } 
	 if(TWSR_Status==0x38)
	 {
		 Mode= SLAVE_NOT_ADDRESSED;
		 i=0;		 
	 }
	if(TWSR_Status==0x48 || TWSR_Status==0x58)
	{
		Mode= MASTER_RECEIVER;
		i=0;
	}
	if(TWSR_Status==0x20 || TWSR_Status==0x30 )
	{
		/*getstop w get start w nkrr bs off*/
		Mode= MASTER_TRANSMITTER;
		i=0;
	}
	TWI_clearInterruptFlagValue();
 

 }
void __vector_19 (void) __attribute__ ((signal)) ;
void __vector_19 (void)
{
	/*Master Send Byte
	 In order to enter a Master mode, a START condition must be transmitted. */
	if ( Mode == MASTER_TRANSMITTER || Mode == MASTER_RECEIVER )
	{
// 			if (i==0)
// 			{
// 				TWI_enable();
// 				TWI_setStartBitCondition(ENABLE);
// 				TWI_clearInterruptFlagValue();
// 				i++;
// 			}
	TWI_setStartBitCondition(DISABLE);
	TWI_getStatus(& TWSR_Status);
		    if(i==0)
			{
				TWI_getStatus(& TWSR_Status);
				if(TWSR_Status==0x08 || TWSR_Status==0x10)
				{
					TWI_clearInterruptFlagValue();
					i++;	
				}
				else
				{
					TWI_error();
				}
			}
			else if(i==1)
			{
				TWI_sendByte(SLAVE_ADDRESS);
				TWI_enable();
				i++;
				TWI_clearInterruptFlagValue();
			}
			else if(i==2)
			{
				TWI_getStatus(& TWSR_Status);
				if(TWSR_Status==0x18 || TWSR_Status==0x40)
				{
					i++;
					TWI_clearInterruptFlagValue();
				}
		
				else
				{
					TWI_error();
				}		
			}
			else if (i==3)
			{
				if(TWSR_Status==0x18 )
				{
					if(TX.TWI_TX_Idx < TX.TWI_TX_Size)
					{
						TWI_sendByte(TX .TWI_TX_Data[TX.TWI_TX_Idx]);
						TX.TWI_TX_Idx++;
						TWI_enable();
						TWI_clearInterruptFlagValue();
					}
				}
				else if(TWSR_Status==0x40)
				{
					if(RX.TWI_RX_Idx < RX.TWI_RX_Size)
					{
						TWI_receiveByte( & RX.TWI_RX_Data[RX.TWI_RX_Idx]);
						RX.TWI_RX_Idx++;
						TWI_enable();
						TWI_clearInterruptFlagValue();
					}	
				}
	
				i++;	
			}
			else if(i==4)
			{
				TWI_getStatus(& TWSR_Status);
				if(TWSR_Status==0x28)
				{
					if(TX.TWI_TX_Idx < TX.TWI_TX_Size)
					{
						i=1;
					}
					else
					{
						i++;
					}
 					TWI_clearInterruptFlagValue();
				}
				if(TWSR_Status==0x20 || TWSR_Status==0x30 )
				{
					if(TX.TWI_TX_Idx < TX.TWI_TX_Size)
					{
						if(((TWI_TWCR>>TWCR_TWSTA)& 0b1)==0)	/*check if start bit =0*/
						{
							TWI_sendByte(TX.TWI_TX_Data[TX.TWI_TX_Idx]);
						}
					}
					TWI_error();
				}
				else if(TWSR_Status==0x50)
				{
					if(RX.TWI_RX_Idx < RX.TWI_RX_Size)
					{
						i=1;
					}
					else
					{
						i++;
					}
					TWI_clearInterruptFlagValue();
				}
				else
				{
					TWI_error();
				}
			}
			else if (i==5 && ((TX.TWI_TX_Idx==TX.TWI_TX_Size)||(RX.TWI_RX_Idx == RX.TWI_RX_Size)))
			{
				TWI_setStopBitCondition(ENABLE);
				TWI_enable();
				i=0;
				TWI_clearInterruptFlagValue();
			}	
			}	
	else if (Mode==SLAVE_TRANSMITTER || Mode==SLAVE_RECEIVER)
	{
		if(j==0)
		{
			TWI_setSlaveAddress(SLAVE_ADDRESS);
			TWI_setGeneralCallRecognitionStatus(ENABLE);
			TWI_enable();
			TWI_setAcknowledgeBitStatus(ENABLE);
			TWI_setStartBitCondition(DISABLE);
			TWI_setStopBitCondition(DISABLE);
			TWI_receiveByte(& Address_R_W);
			if(((Address_R_W >>1)==SLAVE_ADDRESS)&& ((Address_R_W & 1)==0))
			{
				Mode= SLAVE_RECEIVER;
			}
			else if(((Address_R_W >>1)==SLAVE_ADDRESS)&& ((Address_R_W & 1)==1))
			{
				Mode= SLAVE_TRANSMITTER;
			}
			j++;
			TWI_clearInterruptFlagValue();
			
		}
		else if (j==1)
		{
			TWI_getStatus(& Slave_Status);
			if(Mode== SLAVE_RECEIVER)
			{
				if(Slave_Status==0x60 || Slave_Status==0x70)
				{
					TWI_receiveByte(& RX.TWI_RX_Data[RX.TWI_RX_Idx]);
					RX.TWI_RX_Idx ++;
					j++;
					TWI_clearInterruptFlagValue();
				}
			}
			else if(Mode== SLAVE_TRANSMITTER)
			{
				if(Slave_Status==0xA8 || Slave_Status==0xB0)
				{
					TWI_sendByte(TX.TWI_TX_Data[TX.TWI_TX_Idx]);
					TX.TWI_TX_Idx++;
					j++;
					TWI_clearInterruptFlagValue();
				}
			}
			else
			{
				TWI_error();
			}
		
		}
		else if(j==2)
		{
			TWI_getAcknowledgeBitStatus(& Slave_Ack_Status);
			TWI_getStatus(& Slave_Status);
			if(Mode== SLAVE_RECEIVER)
			{
				if(Slave_Status==0x80 || Slave_Status==0x90)
				{			
					if(RX.TWI_RX_Idx < RX.TWI_RX_Size)
					{	
						TWI_receiveByte(& RX.TWI_RX_Data[RX.TWI_RX_Idx]);
						RX.TWI_RX_Idx ++;
						j=0;
						TWI_clearInterruptFlagValue();
					}
					else
					{
						j++;
					}
				}
				else if(Slave_Status==0x88 || Slave_Status==0x98)
				{
					TWI_receiveByte(& RX.TWI_RX_Data[RX.TWI_RX_Idx]);
					TWI_clearInterruptFlagValue();
					TWI_error();	
				}
			}
			else if(Mode== SLAVE_TRANSMITTER)
			{
				if(Slave_Status==0xB8 )
				{
					
					if(TX.TWI_TX_Idx < TX.TWI_TX_Size)
					{	
						TWI_sendByte(TX.TWI_TX_Data[TX.TWI_TX_Idx]);
						TX.TWI_TX_Idx ++;
						j=0;
						TWI_clearInterruptFlagValue();
					}
					else
					{
						j++;
						TWI_clearInterruptFlagValue();
					}
				}
			else
			{
				TWI_error();
			}
	}
	}
	else if(j==3)
	{
		TWI_getStatus(& Slave_Status);
		if(Slave_Status==0xA0)
		{
			j=0;
			Mode= SLAVE_NOT_ADDRESSED;
			TWI_clearInterruptFlagValue();				
		}
	}
	}
	if(TWI_NotifyApp !=NULL)			  
	{
		TWI_NotifyApp();	
	}	
	}


