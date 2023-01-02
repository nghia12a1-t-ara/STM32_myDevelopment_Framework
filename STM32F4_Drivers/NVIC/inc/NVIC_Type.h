#ifndef __NVIC_TYPE_H__
#define __NVIC_TYPE_H__

/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR 			((__vo uint32 *)0xE000E400)

/*
 * ARM Cortex Mx Processor number of priority bits implemented in Priority Register
 */
#define NO_PR_BITS_IMPLEMENTED		4

#define __NVIC_PRIO_BITS          	4U

/*
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0    			0
#define NVIC_IRQ_PRI15    			15

/*
 * IRQ(Interrupt Request) Numbers of STM32F407x MCU
 * NOTE: update these macros with valid values according to your MCU
 * TODO: You may complete this list for other peripherals
 */

#define IRQ_NO_EXTI0 				6
#define IRQ_NO_EXTI1 				7
#define IRQ_NO_EXTI2 				8
#define IRQ_NO_EXTI3 				9
#define IRQ_NO_EXTI4 				10
#define IRQ_NO_EXTI9_5 				23
#define IRQ_NO_EXTI15_10 			40
#define IRQ_NO_SPI1					35
#define IRQ_NO_SPI2         		36
#define IRQ_NO_SPI3         		51
#define IRQ_NO_SPI4
#define IRQ_NO_I2C1_EV     			31
#define IRQ_NO_I2C1_ER     			32
#define IRQ_NO_USART1	    		37
#define IRQ_NO_USART2	    		38
#define IRQ_NO_USART3	    		39
#define IRQ_NO_UART4	    		52
#define IRQ_NO_UART5	    		53
#define IRQ_NO_USART6	    		71

#endif	/* !(__NVIC_TYPE_H__) */
