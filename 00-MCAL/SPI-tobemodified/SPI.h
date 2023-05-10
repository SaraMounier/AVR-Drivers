/*************************************************************
 * 
 * Filename: SPI.h
 * Description: Header (interface) file of the SPI driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SPI_H__
#define __SPI_H__
#include "STD_TYPES.h"
#include "SPI_Priv.h"
#include "SPI_Cfg.h"  

/*SPCR Register*/
#define SPCR_SPR0   0	 /* SPI Clock Rate Select 1 and 0*/
#define SPCR_SPR1   1	 /* SPI Clock Rate Select 1 and 0*/
#define SPCR_CPHA   2	 /*Clock Phase*/
#define SPCR_CPOL   3	 /* Clock Polarity*/
#define SPCR_MSTR   4	/* Master/Slave Select*/
#define SPCR_DORD   5	/*Data Order*/
#define SPCR_SPE    6	/*SPI Enable*/
#define SPCR_SPIE   7  /* SPI Interrupt Enable*/

/*SPSR Register*/
#define SPSR_SPI2X  0	/*Double SPI Speed Bit*/
#define SPSR_WCOL   6  /*Write COLlision Flag*/
#define SPSR_SPIF   7 /*SPI Interrupt Flag*/

/*SPCR Register*/
#define DORD_MSB   0
#define DORD_LSB   1

#define MSTR_MASTER  1
#define MSTR_SLAVE   0

#define CPOL_L_RISING_T_FALLING   0
#define CPOL_L_FALLING_T_RISING   1

#define CPHA_L_SAMPLE_T_SETUP     0
#define CPHA_L_SETUP_T_SAMPLE     1

#define CLK_DIVBY_4			 0b00
#define CLK_DIVBY_16		 0b01
#define CLK_DIVBY_64		 0b10
#define CLK_DIVBY_128		 0b11
#define CLRMASK_2BITS		 0b11

#define ENABLE  1
#define DISABLE 0
typedef enum 
{
	SPI_enuOK,
	SPI_enuNOK,
	SPI_enuNullPtr,
}SPI_ErrorStatus_t;
								
SPI_ErrorStatus_t SPI_setStatus(u8 SPIStatus );
SPI_ErrorStatus_t SPI_setInterruptStatus(u8 InterruptStatus );
SPI_ErrorStatus_t SPI_setDataOrderStatus(u8 DORD_X );
SPI_ErrorStatus_t SPI_selectMaster_SlaveMode(u8 MSTR_X );
SPI_ErrorStatus_t SPI_setClockPolarity(u8 CPOL_L_X_T_X );
SPI_ErrorStatus_t SPI_setClockPhase(u8 CPHA_L_X_T_X );
SPI_ErrorStatus_t SPI_setClockRate(u8 CLK_DIVBY_X );
SPI_ErrorStatus_t SPI_setDoubleSpeedStatus(u8 SPI2X_Status);
/*
SPSR_SPIF
SPSR_WCOL
*/
SPI_ErrorStatus_t SPI_getFlagValue(u8 SPSR_FlagName,u8* SPIFlagValue );
SPI_ErrorStatus_t SPI_setTransmittedData(u8* TransmittedData , u8 length );
SPI_ErrorStatus_t SPI_getReceivededData(u8* ReceivedData, u8 length );
void SendByte(u8 SendByte);
void ReceiveByte(u8 *ReceiveByte);
SPI_ErrorStatus_t SPI_transceiver(u8 sentData, u8*ReceiveData);
SPI_ErrorStatus_t SPI_setCallBackFunction(void (*SPI_APPNotifyFunction)(void));

void SPI_MasterInit(void);
void SPI_SlaveInit(void);










#endif /* __SPI_H__ */