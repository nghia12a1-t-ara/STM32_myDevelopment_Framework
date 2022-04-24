#ifndef __SYSCFG_BASE_H_
#define __SYSCFG_BASE_H_

#include "stm32f4xx.h"

/*
 * peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32 MEMRMP;       /*!< Give a short description,                    Address offset: 0x00      */
	__vo uint32 PMC;          /*!< TODO,     									  Address offset: 0x04      */
	__vo uint32 EXTICR[4];    /*!< TODO , 									  Address offset: 0x08-0x14 */
	uint32      RESERVED1[2];  /*!< TODO          							  Reserved, 0x18-0x1C    	*/
	__vo uint32 CMPCR;        /*!< TODO         								  Address offset: 0x20      */
	uint32      RESERVED2[2];  /*!<                                             Reserved, 0x24-0x28 	    */
	__vo uint32 CFGR;         /*!< TODO                                         Address offset: 0x2C   	*/
} SYSCFG_Types;

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO : Complete for all other peripherals
 */
#define SYSCFG_BASEADDR					(APB2PERIPH_BASEADDR + 0x3800)
#define SYSCFG							((SYSCFG_Types*)SYSCFG_BASEADDR)


#endif	/* !(__SYSCFG_BASE_H_) */
