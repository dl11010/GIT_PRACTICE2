/*
 * ucmd.h
 *
 *  Created on: Aug 7, 2021
 *      Author: gyuho
 */

#ifndef INC_UCMD_H_
#define INC_UCMD_H_

#include "usart.h"
#include "main.h"
#include "string.h"

#define	Print1Str(x)	PrintStr((uint8_t*)x, sizeof(x))

#define	BACKSPACE	8
#define	TAB			9
#define	ENTER		13
#define	ESC			27
#define	SPACE		32

extern uint8_t rxData;
extern uint8_t rxBuffer[100];
extern uint16_t bufferSize;

/* FUNCTION PROTOTYPE */
void PrintChar(uint8_t rxChar);
void PrintStr(uint8_t* str, uint16_t size);
void UART1_RX_Process(uint8_t uartRxData);
#endif /* INC_UCMD_H_ */
