#ifndef __NVIC_H_
#define __NVIC_H_

#include "NVIC_Base.h"
#include "NVIC_Types.h"

/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8 IRQNumber, uint8 EnorDi);
void GPIO_IRQPriorityConfig(uint8 IRQNumber, uint32 IRQPriority);
void GPIO_IRQHandling(uint8 PinNumber);

/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8 IRQNumber, uint8 EnorDi);
void SPI_IRQPriorityConfig(uint8 IRQNumber, uint32 IRQPriority);

/*
 * IRQ Configuration and ISR handling
 */
void I2C_IRQInterruptConfig(uint8 IRQNumber, uint8 EnorDi);
void I2C_IRQPriorityConfig(uint8 IRQNumber, uint32 IRQPriority);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQInterruptConfig(uint8 IRQNumber, uint8 EnorDi);
void USART_IRQPriorityConfig(uint8 IRQNumber, uint32 IRQPriority);


#endif 	/* !(__NVIC_H_) */
