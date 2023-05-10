/*************************************************************
 * 
 * Filename: USART.h
 * Description: Header (interface) file of the USART driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __USART_H__
#define __USART_H__
 #include "STD_TYPES.h"
typedef enum 
{
	USART_enuOK,
	USART_enuNOK,
	USART_enuNullPtr,
	USART_enuBUSY,
}USART_ErrorStatus_t;

typedef struct 
{
	u8* Data;
	u32 Size;
	u32 Idx;
	u8 Status;
}TX;

typedef struct
{
	u8* Data;
	u32 Size;
	u32 Idx;
	u8 Status;
}RX;	

typedef enum 
{
	TX_IDLE,
	TX_BUSY,
	RX_IDLE,
	RX_BUSY,
}USART_TX_RX_Status;

#define UCSRA_MPCM 0   
#define UCSRA_U2X  1
#define UCSRA_PE   2
#define UCSRA_DOR  3
#define UCSRA_FE   4
#define UCSRA_UDRE 5
#define UCSRA_TXC  6
#define UCSRA_RXC  7

#define UCSRB_TXB8   0
#define UCSRB_RXB8   1
#define UCSRB_UCSZ2  2
#define UCSRB_TXEN   3
#define UCSRB_RXEN   4
#define UCSRB_UDRIE  5
#define UCSRB_TXCIE  6
#define UCSRB_RXCIE  7

#define UCSRC_UCPOL  0
#define UCSRC_UCSZ0  1
#define UCSRC_UCSZ1  2
#define UCSRC_USBS   3
#define UCSRC_UPM0   4
#define UCSRC_UPM1   5
#define UCSRC_UMSEL  6
#define UCSRC_URSEL  7

#define ENABLE 1
#define DISABLE 0

#define _5_bit 0b000
#define _6_bit 0b001
#define _7_bit 0b010
#define _8_bit 0b011
#define _9_bit 0b111

#define UBRRH_READ_WRITE 0
#define UCSRC_READ_WRITE 1

#define USART_OPERATION_ASYNCH 0
#define USART_OPERATION_SYNCH  1

#define USART_PARITY_DISABLED		  0B00
#define USART_PARITY_ENABLED_EVEN	  0B10
#define USART_PARITY_ENABLED_ODD	  0B11

#define STOP_1_BIT  0
#define STOP_2_BIT  1

#define TX_RISING_EDGE_RX_FALLING_EDGE  0
#define TX_FALLING_EDGE_RX_RISING_EDGE  1

#define CLR_MASK_2BITS 0B11



/*
FlagName:
UCSRA_RXC  // USART Receive Complete
UCSRA_TXC //USART Transmit Complete
UCSRA_UDRE // USART Data Register Empty
UCSRA_FE   //UCSRA_FE
UCSRA_DOR  // Data OverRun
UCSRA_PE  // Parity Error
*/
USART_ErrorStatus_t USART_getFlagStatus(u8 FlagName,u8* FlagValue);
USART_ErrorStatus_t USART_setFlagStatus(u8 FlagName,u8 FlagValue);

/*
InterruptName:
UCSRB_RXCIE //RX Complete Interrupt 
UCSRB_TXCIE	//TX Complete Interrupt
UCSRB_UDRIE	//USART Data Register Empty Interrupt

InterruptValue:
ENABLE  1
DISABLE 0
*/
USART_ErrorStatus_t USART_setInterruptStatus(u8 InterruptName,u8 InterruptValue);

/*
_X:
TX //Transmitter
RX //Receiver
X_Status:
ENABLE  1
DISABLE 0
*/
USART_ErrorStatus_t USART_set_Rx_Tx_Status(u8 UCSRB_XXEN,u8 X_Status);
/*
_5_bit
_6_bit
_7_bit
_8_bit
_9_bit 
*/
USART_ErrorStatus_t USART_setCharSize(u8 X_bit);

USART_ErrorStatus_t USART_getNinthBitReceivedchar(u8* Receivedchar_8bit);
USART_ErrorStatus_t USART_sendNinthBitTransmittedchar(u8 Transmittedchar_8bit);

USART_ErrorStatus_t USART_asyncDoubleTransmissionSpeed();
USART_ErrorStatus_t USART_enableMultiProcessorTransmission();	
USART_ErrorStatus_t USART_getReceivedData(u8* ReceivedData);
USART_ErrorStatus_t USART_sendTransmittedData(u8 TransmittedData);
/*
It is read as one when reading UCSRC. The URSEL must be one when writing the UCSRC.
*/
USART_ErrorStatus_t USART_selectUCSRCRegister();
/*
USART_OPERATION_ASYNCH 
USART_OPERATION_SYNCH 
*/
USART_ErrorStatus_t USART_selectOperationMode(u8 UCSRC_OPERATION_X);

/*
USART_PARITY_DISABLED	
USART_PARITY_ENABLED_EVEN	
USART_PARITY_ENABLED_ODD	
*/
USART_ErrorStatus_t USART_selectParityMode(u8 UCSRC_PARITY_X);

/*
STOP_1_BIT 
STOP_2_BIT 
*/
USART_ErrorStatus_t USART_selectStopBit(u8 STOP_X_BIT);

/*
TX_RISING_EDGE_RX_FALLING_EDGE 
TX_FALLING_EDGE_RX_RISING_EDGE 
*/
USART_ErrorStatus_t USART_selectCLKPolarity(u8 TX_X_EDGE_RX_X_EDGE);
/*
 It is read as zero when reading UBRRH. The URSEL must be zero when writing the UBRRH.
 */
USART_ErrorStatus_t USART_selectUBRRHRegister();	
/*The baud rate value is doubled when writing the U2X bit By 1*/
USART_ErrorStatus_t USART_setBaudRate(); 


USART_ErrorStatus_t USART_sendBuffer(u8* Data, u32 Size);
USART_ErrorStatus_t USART_receiveBuffer(u8* Data, u32 Size);
USART_ErrorStatus_t USART_TX_CallBackFunction(void (*TX_APP_NotifyFunction)(void));
USART_ErrorStatus_t USART_RX_CallBackFunction(void (*RX_APP_NotifyFunction)(void));

#endif /* __USART_H__ */