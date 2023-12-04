/*
 * Middle.c
 *
 *  Created on: Sep 24, 2023
 *      Author: WIN 10
 */

#include "main.h"

const uint8 TxBuff[] = "EFGHI";
uint8 RxBuff[5];
extern void ReceiveDatafromPC(void);

Usart_StateRuntimeType StateStruct;

const Usart_UserConfigType User_UART1_Config = {
		.USART_Mode				= USART_MODE_TXRX,
		.USART_Baud				= USART_STD_BAUD_9600,
		.USART_NoOfStopBits		= USART_STOPBITS_1,
		.USART_WordLength		= USART_WORDLEN_8BITS,
		.USART_ParityControl 	= USART_PARITY_DISABLE,
		.USART_HWFlowControl	= USART_HW_FLOW_CTRL_NONE,
		.USART_Transfer			= USART_USING_INTERRUPTS,
		.Callback				= &ReceiveDatafromPC,
		.StateStruct			= &StateStruct,
};

const  GPIO_PinConfigType User_UART1_TX_PinConfig = {
		USART1_TX_PIN,
		GPIO_MODE_ALTERNATE,
		GPIO_OSPEED_HIGH,
		GPIO_INPUT_PULLUP,
		GPIO_OTYPE_PUSHPULL,
		GPIO_ALTERNATE_USART1_2,
		EXTI_DISABLE
};


const  GPIO_PinConfigType User_UART1_RX_PinConfig = {
		USART1_RX_PIN,
		GPIO_MODE_ALTERNATE,
		GPIO_OSPEED_HIGH,
		GPIO_INPUT_PULLUP,
		GPIO_OTYPE_PUSHPULL,
		GPIO_ALTERNATE_USART1_2,
		EXTI_DISABLE
};

const GPIO_PinConfigType User_LedConfig = {
		GPIO_PIN_NO_5,
		GPIO_MODE_OUTPUT,
		GPIO_OSPEED_HIGH,
		GPIO_INPUT_FLOATING,
		GPIO_OTYPE_PUSHPULL,
		GPIO_ALTERNATE_REVERSED1,
		EXTI_DISABLE
};

void Application_Init(void)
{
	GPIO_Init(USART1_RX_PORT_INS, &User_UART1_RX_PinConfig);
	GPIO_Init(USART1_TX_PORT_INS, &User_UART1_TX_PinConfig);

	USART_Init(UART_INSTANCE_1, &User_UART1_Config);
}

void Delay(uint32 utime)
{
	while (utime--)
	{
		for (uint32 i = 0; i < 1000; i++);
	}
}
