#ifndef __NVIC_BASE_H_
#define __NVIC_BASE_H_

#include "Std_Types.h"

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
  \brief      Type definitions for the NVIC Registers
  @{
 */

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IO uint32 ISER[8U];					/*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32 RESERVED0[24U];
  __IO uint32 ICER[8U];					/*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32 RESERVED1[24U];
  __IO uint32 ISPR[8U];					/*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32 RESERVED2[24U];
  __IO uint32 ICPR[8U];					/*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32 RESERVED3[24U];
  __IO uint32 IABR[8U];					/*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32 RESERVED4[56U];
  __IO uint8  IP[240U];					/*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  __O  uint32_t STIR;					/*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
} NVIC_Types;

/*!< NVIC Base Address */
#define NVIC_BASE           (0xE000E100UL)

/*!< NVIC configuration struct */
#define NVIC                ((NVIC_Types *) NVIC_BASE)

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
