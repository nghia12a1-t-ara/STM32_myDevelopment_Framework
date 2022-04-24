#ifndef __NVIC_BASE_H_
#define __NVIC_BASE_H_

#include "stm32f4xx.h"

/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */

#define NVIC_ISER0          ( (__vo uint32 *)0xE000E100 )
#define NVIC_ISER1          ( (__vo uint32 *)0xE000E104 )
#define NVIC_ISER2          ( (__vo uint32 *)0xE000E108 )
#define NVIC_ISER3          ( (__vo uint32 *)0xE000E10c )


/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0 			((__vo uint32 *)0XE000E180)
#define NVIC_ICER1			((__vo uint32 *)0XE000E184)
#define NVIC_ICER2  		((__vo uint32 *)0XE000E188)
#define NVIC_ICER3			((__vo uint32 *)0XE000E18C)


/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR 	((__vo uint32 *)0xE000E400)

/*
 * ARM Cortex Mx Processor number of priority bits implemented in Priority Register
 */
#define NO_PR_BITS_IMPLEMENTED		4


/*
 * peripheral register definition structure for EXTI
 */
typedef struct
{
	__vo uint32 IMR;    /*!< Give a short description,          	  	    Address offset: 0x00 */
	__vo uint32 EMR;    /*!< TODO,                						Address offset: 0x04 */
	__vo uint32 RTSR;   /*!< TODO,  									     Address offset: 0x08 */
	__vo uint32 FTSR;   /*!< TODO, 										Address offset: 0x0C */
	__vo uint32 SWIER;  /*!< TODO,  									   Address offset: 0x10 */
	__vo uint32 PR;     /*!< TODO,                   					   Address offset: 0x14 */
} EXTI_Types;

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO : Complete for all other peripherals
 */
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)
#define EXTI						((EXTI_Types*)EXTI_BASEADDR)



/*
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0    	0
#define NVIC_IRQ_PRI15    	15

/*
 * IRQ(Interrupt Request) Numbers of STM32F407x MCU
 * NOTE: update these macros with valid values according to your MCU
 * TODO: You may complete this list for other peripherals
 */

#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI9_5 		23
#define IRQ_NO_EXTI15_10 	40
#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2         36
#define IRQ_NO_SPI3         51
#define IRQ_NO_SPI4
#define IRQ_NO_I2C1_EV     	31
#define IRQ_NO_I2C1_ER     	32
#define IRQ_NO_USART1	    37
#define IRQ_NO_USART2	    38
#define IRQ_NO_USART3	    39
#define IRQ_NO_UART4	    52
#define IRQ_NO_UART5	    53
#define IRQ_NO_USART6	    71

#endif	/* !(__NVIC_BASE_H_) */
