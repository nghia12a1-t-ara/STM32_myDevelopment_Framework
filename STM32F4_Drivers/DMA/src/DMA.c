
#include "DMA.h"
#include "stm32f4xx.h"

void DMA_Init (void)
{
	// Clock
	DMA2_PCLK_EN();

	// SElect Channel
	// Default Channel 0

	// Data Direction	 - Mem to Mem
	DMA2->Stream[0].CR |= (1 << 7);
	DMA2->Stream[0].CR &= ~(1 << 6);

	//INcrement
	DMA2->Stream[0].CR |= (1 << 10) | (1 << 9);

	DMA2->Stream[0].CR &= ~(0xF << 11);
}

void DMA_Config (uint32 srcAdd, uint32 destAdd, uint16 datasize)
{
	DMA2->Stream[0].NDTR = datasize;

	DMA2->Stream[0].PAR = srcAdd;

	DMA2->Stream[0].M0AR = destAdd;
}

void Start_Transfer (void)
{
	DMA2->Stream[0].CR |= (1 << 0);

	while ( !(DMA2->LISR & (1 << 5)) );
}

