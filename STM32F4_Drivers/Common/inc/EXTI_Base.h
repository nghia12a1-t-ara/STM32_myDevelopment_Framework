#ifndef __EXTI_BASE_H_
#define __EXTI_BASE_H_

#include "stm32f4xx.h"

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

#define EXTI_BASEADDR				0x40013C00UL
#define EXTI						((EXTI_Types*)EXTI_BASEADDR)

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO : Complete for all other peripherals
 */


#endif	/* !(__SYSCFG_BASE_H_) */
