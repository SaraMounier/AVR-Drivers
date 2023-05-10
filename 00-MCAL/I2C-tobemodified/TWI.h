/*************************************************************
 * 
 * Filename: TWI.h
 * Description: Header (interface) file of the TWI driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __TWI_H__
#define __TWI_H__
#include "STD_TYPES.h"
#include "TWI_Cfg.h"
#include "TWI_Priv.h"
typedef enum
{
	TWI_enuOK,
	TWI_enuNOK,
	TWI_enuNullPtr,
}TWI_ErrorStatus_t;

#define ENABLE   1
#define DISABLE  0
#define READ  1
#define WRITE 0
#define TWCR_TWIE	0
#define TWCR_TWEN	2
#define TWCR_TWWC	3
#define TWCR_TWSTO  4
#define TWCR_TWSTA  5
#define TWCR_TWEA	6
#define TWCR_TWINT	7


#define TWSR_TWS3 3
#define TWSR_TWPS0 0
#define TWI_PRESCALER_01  0b00
#define TWI_PRESCALER_04  0b01
#define TWI_PRESCALER_16  0b10
#define TWI_PRESCALER_64  0b11

#define TWAR_TWA0  1
#define TWAR_TWGCE 0

#define MASTER_TRANSMITTER	1
#define MASTER_RECEIVER		2
#define SLAVE_TRANSMITTER	3
#define SLAVE_RECEIVER		4
#define SLAVE_NOT_ADDRESSED 5
typedef struct
{
	u8* TWI_TX_Data;
	u32 TWI_TX_Size;
	u32 TWI_TX_Idx;
	u8 TWI_TX_Status;
}TWI_TX;

typedef struct
{
	u8* TWI_RX_Data;
	u32 TWI_RX_Size;
	u32 TWI_RX_Idx;
	u8 TWI_RX_Status;
}TWI_RX;

typedef enum
{
	TWI_TX_IDLE,
	TWI_TX_BUSY,
	TWI_RX_IDLE,
	TWI_RX_BUSY,
}TWI_TX_RX_Status;


TWI_ErrorStatus_t TWI_setBitRate(u8 BitRateValue);

TWI_ErrorStatus_t TWI_getInterruptFlagValue(u8* InterruptFlagValue);

/*
note that clearing this flag starts the operation of the TWI, so all accesses to the TWI Address Register (TWAR),
TWI Status Register (TWSR), and TWI Data Register (TWDR) must be complete before clearing this flag*/
TWI_ErrorStatus_t TWI_clearInterruptFlagValue();

/*
ACK pulse is generated on the TWI bus if the following conditions are met:
1. The device’s own slave address has been received.
2. A general call has been received, while the TWGCE bit in the TWAR is set.
3. A data byte has been received in Master Receiver or Slave Receiver mode.
By writing the TWEA bit to zero, the device can be virtually disconnected from the Two-wire
Serial Bus temporarily. Address recognition can then be resumed by writing the TWEA bit to one
again.*/
TWI_ErrorStatus_t TWI_setAcknowledgeBitStatus(u8 ACK_STATUS);
TWI_ErrorStatus_t TWI_getAcknowledgeBitStatus(u8* ACK_STATUS);
/*
The application writes the TWSTA bit to one when it desires to become a master on the Two?wire Serial Bus.
 The TWI hardware checks if the bus is available, and generates a START con?dition on the bus if it is free.
 However, if the bus is not free, the TWI waits until a STOP condition is detected, and then generates a new START condition to claim 
 the bus Master status. TWSTA must be cleared by software when the START condition has been transmitted.*/
TWI_ErrorStatus_t TWI_setStartBitCondition(u8 StartBitCondition);
/*
When the STOP condition is executed on the bus, the TWSTO bit is cleared automatically. In slave mode, setting the TWSTO bit can be used to recover from an error condition.
This will not generate a STOP condition, but the TWI returns to a well-defined unaddressed
slave mode and releases the SCL and SDA lines to a high impedance state.*/
TWI_ErrorStatus_t TWI_setStopBitCondition(u8 StopBitCondition);

/*
The TWWC bit is set when attempting to write to the TWI Data Register – TWDR when TWINT(Interrupt flag) is
low. This flag is cleared by writing the TWDR Register when TWINT is high*/
TWI_ErrorStatus_t TWI_getWriteCollisionFlagValue(u8* WriteCollisionFlagValue);

/* the TWI takes control over the I/O pins connected to the SCL and SDA pins, enabling the
slew-rate limiters and spike filters. If this bit is written to zero, the TWI is switched off and all TWI
transmissions are terminated, regardless of any ongoing operation.*/
TWI_ErrorStatus_t TWI_enable();
TWI_ErrorStatus_t TWI_disable();

/*When this bit is written to one, and the I-bit in SREG is set, the TWI interrupt request will be activated for as long as the TWINT Flag is high*/
 TWI_ErrorStatus_t TWI_setInterruptStatus(u8 Interrupt_STATUS);
 TWI_ErrorStatus_t TWI_getStatus(u8* TWI_STATUS);
 TWI_ErrorStatus_t TWI_setPrescaler(u8 TWI_PRESCALER_X);

  
TWI_ErrorStatus_t TWI_TXSendBuffer(u8* TransmittedData, u8 Size);
TWI_ErrorStatus_t TWI_RXReceiveBuffer(u8* ReceivedData, u8 Size);


TWI_ErrorStatus_t TWI_setSlaveAddress(u8 TWI_SlaveAddress);

TWI_ErrorStatus_t TWI_setGeneralCallRecognitionStatus(u8 GeneralCallRecogStatus);
TWI_ErrorStatus_t TWI_getGeneralCallRecognitionStatus(u8* GeneralCallRecogStatus);

TWI_ErrorStatus_t TWI_setCallBackFunction(void (*TWI_cbf)(void)) ;

 TWI_ErrorStatus_t TWI_setOperation(u8 R_W);
void TWI_error(void);
 TWI_ErrorStatus_t TWI_sendByte(u8 Data );
 TWI_ErrorStatus_t TWI_receiveByte(u8* Data );
#endif /* __TWI_H__ */