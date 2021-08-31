/*
 * ucmd2.h
 *
 *  Created on: 2021. 8. 11.
 *      Author: gyuho
 */

#ifndef INC_UCMD2_H_
#define INC_UCMD2_H_

#include "main.h"
#include "usart.h"

#define	TX_BUFFER_SIZE	1024

typedef struct uart_hal_tx_type{
	uint8_t buffer[TX_BUFFER_SIZE];
	volatile uint16_t inputPtr;
	volatile uint16_t outputPtr;
} __attribute__((packed)) UART_TX_PACKET;

extern UART_TX_PACKET g_struTxPacket;

/* FUNCTION PROTOTYPE */
void UartTxPacketInit(void);
void UartTxPutchar(uint8_t *data, int len);

#endif /* INC_UCMD2_H_ */
