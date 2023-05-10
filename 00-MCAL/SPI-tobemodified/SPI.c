/*************************************************************
 * 
 * Filename: SPI.c
 * Description: Source file of the SPI driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "SPI_Cfg.h"
#include "SPI_Priv.h"
#include "SPI.h"
#include "DIO.h"
u8* Buffer;
u8 Buffer_length;
u8 Idx=0;


SPI_ErrorStatus_t SPI_setStatus(u8 SPIStatus )
{
   SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
   if(SPIStatus == ENABLE)
   {
	   SPI_SPCR	|= 1<< SPCR_SPE;
   }
   else if(SPIStatus == DISABLE)
   {
	   SPI_SPCR	&= ~(1<< SPCR_SPE);
   }
   else
   {
	  SPI_Loc_ErrorStatus=SPI_enuNOK; 
   }
   return SPI_Loc_ErrorStatus; 
}
SPI_ErrorStatus_t SPI_setInterruptStatus(u8 InterruptStatus )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(InterruptStatus==ENABLE)
	{
		SPI_SPCR |= 1<< SPCR_SPIE;
	}
	else if(InterruptStatus==DISABLE)
	{
		SPI_SPCR &= ~(1<< SPCR_SPIE);
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNOK;
	}
	return SPI_Loc_ErrorStatus;
}
SPI_ErrorStatus_t SPI_setDataOrderStatus(u8 DORD_X )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(DORD_X==DORD_LSB)
	{
		SPI_SPCR |= 1<< SPCR_DORD;
	}
	else if(DORD_X==DORD_MSB)
	{
		SPI_SPCR &= ~(1<< SPCR_DORD);
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNOK;
	}
	return SPI_Loc_ErrorStatus;
}
SPI_ErrorStatus_t SPI_selectMaster_SlaveMode(u8 MSTR_X )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(MSTR_X==MSTR_MASTER)
	{
		SPI_SPCR |= 1<< SPCR_MSTR;
	}
	else if(MSTR_X==MSTR_SLAVE)
	{
		SPI_SPCR &= ~(1<< SPCR_MSTR);
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNOK;
	}
	return SPI_Loc_ErrorStatus;
}
SPI_ErrorStatus_t SPI_setClockPolarity(u8 CPOL_L_X_T_X )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(CPOL_L_X_T_X==CPOL_L_FALLING_T_RISING)
	{
		SPI_SPCR |= 1<< SPCR_CPOL;
	}
	else if(CPOL_L_X_T_X==CPOL_L_RISING_T_FALLING)
	{
		SPI_SPCR &= ~(1<< SPCR_CPOL);
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNOK;
	}
	return SPI_Loc_ErrorStatus;
}
SPI_ErrorStatus_t SPI_setClockPhase(u8 CPHA_L_X_T_X )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(CPHA_L_X_T_X == CPHA_L_SETUP_T_SAMPLE)
	{
		SPI_SPCR |= 1<< SPCR_CPHA  ;
	}
	else if(CPHA_L_X_T_X==CPHA_L_SAMPLE_T_SETUP)
	{
		SPI_SPCR &= ~(1<< SPCR_CPHA);
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNOK;
	}
	return SPI_Loc_ErrorStatus;
}
SPI_ErrorStatus_t SPI_setDoubleSpeedStatus(u8 SPI2X_Status)
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(SPI2X_Status==ENABLE)
	{
		SPI_SPSR |= 1<< SPSR_SPI2X;
	}
	else if(SPI2X_Status==DISABLE)
	{
		SPI_SPSR &= ~(1<< SPSR_SPI2X);
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNOK;
	}
	return SPI_Loc_ErrorStatus;
}

SPI_ErrorStatus_t SPI_setClockRate(u8 CLK_DIVBY_X )
{	
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(CLK_DIVBY_X==CLK_DIVBY_4 || CLK_DIVBY_X==CLK_DIVBY_16 || CLK_DIVBY_X==CLK_DIVBY_64 || CLK_DIVBY_X==CLK_DIVBY_128 )
	{
		u8 TempVar =SPI_SPCR & ~(CLRMASK_2BITS);
   		SPI_SPCR = TempVar | CLK_DIVBY_X;
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNOK;
	}
	return SPI_Loc_ErrorStatus;

}								


/*
SPSR_SPIF
SPSR_WCOL
*/
SPI_ErrorStatus_t SPI_getFlagValue(u8 SPSR_FlagName,u8* SPIFlagValue )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	*SPIFlagValue= (SPI_SPSR >>SPSR_FlagName)& 0x01;
	return SPI_Loc_ErrorStatus;

}


static void SPI_clearInterruptFlag(void) {
	volatile u8 dummy;
	dummy = SPI_SPSR;
	dummy = SPI_SPDR;
}

SPI_ErrorStatus_t SPI_setTransmittedData(u8* TransmittedData , u8 length )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	Buffer_length=length;
	
	for(Idx=0;Idx<length;Idx++)
	{
		SPI_SPDR =TransmittedData[Idx];
		while (((SPI_SPSR >> SPSR_SPIF) & 0x01 )==0);
		Buffer[Idx]=SPI_SPDR;

	}

	return SPI_Loc_ErrorStatus;	
}
SPI_ErrorStatus_t SPI_getReceivededData(u8* ReceivedData, u8 length )
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
// 	u8 counter=0;
// 	for(counter=0;counter<length;counter++)
// 	{
		 while (((SPI_SPSR >> SPSR_SPIF) & 0x01 )==0);
		*(ReceivedData/*+counter*/)=SPI_SPDR ;
		Buffer[Idx]=SPI_SPDR; 
// 	}
	return SPI_Loc_ErrorStatus;
}

void SendByte(u8 SendByte)
{
	SPI_SPDR=SendByte;
}
void ReceiveByte(u8 *ReceiveByte)
{
	u8 DummyData='A';
	SPI_SPDR=DummyData;
	while (((SPI_SPSR >> SPSR_SPIF) & 0x01 )==0);
	*ReceiveByte=SPI_SPDR;
}

SPI_ErrorStatus_t SPI_transceiver(u8 sentData, u8*ReceiveData)
{
		SPI_SPDR=sentData;
		while (((SPI_SPSR >> SPSR_SPIF) & 0x01 )==0);

		*ReceiveData=SPI_SPDR;
}
void (*SPI_NotifyFunction)(void)=NULL;
SPI_ErrorStatus_t SPI_setCallBackFunction(void (*SPI_APPNotifyFunction)(void))
{
	SPI_ErrorStatus_t SPI_Loc_ErrorStatus=SPI_enuOK;
	if(SPI_APPNotifyFunction !=NULL)
	{
		 SPI_NotifyFunction=SPI_APPNotifyFunction;
	}
	else
	{
		SPI_Loc_ErrorStatus=SPI_enuNullPtr;
	}
	return SPI_Loc_ErrorStatus;
}

void __vector_12 (void) __attribute__ ((signal));
void __vector_12 (void)
{
	if(SPI_NotifyFunction !=NULL)
	{	
		SPI_NotifyFunction();
	} 	

}

