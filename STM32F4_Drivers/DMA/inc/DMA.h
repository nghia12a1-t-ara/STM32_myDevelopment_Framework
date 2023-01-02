#ifndef _DMA_H_
#define _DMA_H_

#include "DMA_Base.h"
#include "DMA_Type.h"

/**
 * Function Prototypes
 */
void DMA_Init (void);
void DMA_Config (uint32 srcAdd, uint32 destAdd, uint16 datasize);
void Start_Transfer (void);

#endif	/* !(_DMA_H_) */
