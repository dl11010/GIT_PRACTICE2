/*
 * ucmd.c
 *
 *  Created on: Aug 7, 2021
 *      Author: gyuho
 */

#include "ucmd.h"

uint8_t rxData;
uint8_t rxBuffer[100];
uint16_t bufferSize;


void PrintChar(uint8_t rxChar)
{
	HAL_UART_Transmit(&huart1, &rxChar, 1, HAL_MAX_DELAY);
}

void PrintStr(uint8_t* str, uint16_t size)
{
	HAL_UART_Transmit(&huart1, str, size, HAL_MAX_DELAY);
}

int _write(int32_t file, uint8_t *ptr, int32_t len) {
    for(int32_t i = 0; i < len; ++i) { ITM_SendChar(*ptr++); }
    return len;
}

void UART1_RX_Process(uint8_t uartRxData)
{
	switch(uartRxData)
	{
	case BACKSPACE:
		Print1Str("\b \b");

		if(bufferSize == 0)
			bufferSize = 0;
		else
			bufferSize--;
		break;
	case ENTER:
		Print1Str("\r\n");
		bufferSize = 0;
		memset(rxBuffer, 0, sizeof(rxBuffer));
		break;
	case ESC:
		bufferSize = 0;
		memset(rxBuffer, 0, sizeof(rxBuffer));
		Print1Str("\033[2J");
		Print1Str("\033[1;1H");
		break;
	default:
		rxBuffer[bufferSize++] = uartRxData;
		PrintChar(uartRxData);
		break;
	}
}
