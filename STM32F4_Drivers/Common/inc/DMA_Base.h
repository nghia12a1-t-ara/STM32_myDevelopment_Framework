/**
 * Filename		: DMA_Base.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Peripheral Access Layer for DMA Driver
 */

#ifndef __DMA_BASE_H
#define __DMA_BASE_H

#include "stm32f4xx.h"

/** 
 * Define DMA Register 
 */
 
/* Number of DMA Streams */
#define DMA_NUM_OF_STREAM				(8)
 
typedef struct {
	__vo uint32 LISR;			/** DMA Low Interrupt Status Register		Offset = 0x0000 */
	__vo uint32 HISR;			/** DMA High Interrupt Status Register		Offset = 0x0004 */
	__vo uint32 LIFCR;			/** DMA Low Interrupt Flag Clear Register	Offset = 0x0008	*/
	__vo uint32 HIFCR;			/** DMA High Interrupt Flag Clear Register	Offset = 0x000C */
	struct DMAStream_Type {
		__vo uint32 CR;		/** DMA Configuration Register				Offset = 0x0010 + 0x18 × stream number */
		__vo uint32 NDTR;		/** DMA Number of Data Register				Offset = 0x0014 + 0x18 × stream number */
		__vo uint32 PAR;		/** DMA Peripheral Address Register			Offset = 0x0018 + 0x18 × stream number */
		__vo uint32 M0AR;		/** DMA Memory 0 Address Register			Offset = 0x001C + 0x18 × stream number */
		__vo uint32 M1AR;		/** DMA Memory 1 Address Register			Offset = 0x0020 + 0x18 × stream number */
		__vo uint32 FCR;		/** DMA FIFO Control Register				Offset = 0x0024 + 0x18 × stream number */
	} Stream[DMA_NUM_OF_STREAM];
} DMA_Type;

#define DMA1_BASEADDR					(0x40026000UL)
#define DMA1							((DMA_Type *)DMA1_BASEADDR)

#define DMA2_BASEADDR					(0x40026400UL)
#define DMA2							((DMA_Type *)DMA2_BASEADDR)

/**
 * Define DMA Channel
 */
#define	DMA_CHANNEL_0					(0)
#define	DMA_CHANNEL_1					(1)
#define	DMA_CHANNEL_2					(2)
#define	DMA_CHANNEL_3					(3)
#define	DMA_CHANNEL_4					(4)
#define	DMA_CHANNEL_5					(5)
#define	DMA_CHANNEL_6					(6)
#define	DMA_CHANNEL_7					(7)

/**
 * Define Memory/Peripheral Burst Transfer Configuration
 */
#define DMA_SINGLE_TRANSFER				(0)
#define DMA_INC_BURST_4_BEAT			(1)
#define DMA_INC_BURST_8_BEAT			(2)
#define DMA_INC_BURST_16_BEAT			(3)

/**
 * Define DMA Priority Level
 */
#define DMA_PRIO_LEVEL_LOW				(0)
#define DMA_PRIO_LEVEL_MEDIUM			(1)
#define DMA_PRIO_LEVEL_HIGH				(2)
#define DMA_PRIO_LEVEL_VERYHIGH			(3)

/**
 * Define DMA Memory/Peripheral Data Size
 */
#define DMA_MEM_SIZE_8_BITS				(0)
#define DMA_MEM_SIZE_16_BITS			(1)
#define DMA_MEM_SIZE_32_BITS			(2)


/**
 * Define DMA Data Transfer Direction
 */
#define DMA_PERIPHERAL_TO_MEMORY		(0)
#define DMA_MEMORY_TO_PERIPHERAL		(1)
#define DMA_MEMORY_TO_MEMORY			(2)


#endif	/* !(__DMA_BASE_H) */


