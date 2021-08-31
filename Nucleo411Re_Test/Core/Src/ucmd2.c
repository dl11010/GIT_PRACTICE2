/*
 * ucmd2.c
 *
 *  Created on: 2021. 8. 11.
 *      Author: gyuho
 */


#include "ucmd2.h"

UART_TX_PACKET g_struTxPacket;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
	uint16_t size;

	if(huart->Instance == USART2)
	{
		g_struTxPacket.outputPtr += huart->TxXferSize;

		if(g_struTxPacket.outputPtr >= TX_BUFFER_SIZE)
		{
			g_struTxPacket.outputPtr -= TX_BUFFER_SIZE;
		}

		if(g_struTxPacket.inputPtr != g_struTxPacket.outputPtr)
		{
			if(g_struTxPacket.inputPtr > g_struTxPacket.outputPtr)
			{
				size = g_struTxPacket.inputPtr - g_struTxPacket.outputPtr;
			}
			else
			{
				size = TX_BUFFER_SIZE - g_struTxPacket.outputPtr;
			}

			HAL_UART_Transmit_IT(&huart2, &g_struTxPacket.buffer[g_struTxPacket.outputPtr], size);
		}
	}
}

void UartTxPacketInit(void)
{
	g_struTxPacket.inputPtr		= 0;
	g_struTxPacket.outputPtr	= 0;
}

void UartTxPutchar(uint8_t *data, int len)
{
	uint16_t size = len;
	uint32_t reg = READ_REG(huart2.Instance->CR1);

	__HAL_UART_DISABLE_IT(&huart2, UART_IT_TXE);
	__HAL_UART_DISABLE_IT(&huart2, UART_IT_TC);

	if((g_struTxPacket.inputPtr + len) >= TX_BUFFER_SIZE)
	{
		size = TX_BUFFER_SIZE - g_struTxPacket.inputPtr;
		memcpy(&g_struTxPacket.buffer[g_struTxPacket.inputPtr], data, size);
		memcpy(&g_struTxPacket.buffer[0], &data[size], len - size);
		g_struTxPacket.inputPtr = len - size;
	}
	else
	{
		memcpy(&g_struTxPacket.buffer[g_struTxPacket.inputPtr], data, size);
		g_struTxPacket.inputPtr += size;
	}

	WRITE_REG(huart2.Instance->CR1, reg);
	HAL_UART_Transmit_IT(&huart2, &g_struTxPacket.buffer[g_struTxPacket.outputPtr], size);
}
