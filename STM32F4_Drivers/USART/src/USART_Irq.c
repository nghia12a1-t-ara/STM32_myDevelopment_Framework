/**
 * Filename		: USART_Irq.c
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement USART IRQ Handler
 */

#include "USART.h"

void USART1_IRQHandler(void)
{
    Usart_IrqHandler(UART_INSTANCE_1);
}

void USART2_IRQHandler(void)
{
    Usart_IrqHandler(UART_INSTANCE_2);
}

void USART6_IRQHandler(void)
{
    Usart_IrqHandler(UART_INSTANCE_6);
}
