/**
 * Filename		: DMA_HwAccess.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: DMA Hardware Access
 */

#ifndef __DMA_HWACCESS_H__
#define __DMA_HWACCESS_H__

#include "DMA_Base.h"
#include "DMA_Type.h"
#include "Systick.h"
#include "CLOCK.h"

#define DMA_FLAG_STREAM_0_SHIFT			0u
#define DMA_FLAG_STREAM_1_SHIFT			6u
#define DMA_FLAG_STREAM_2_SHIFT			16u
#define DMA_FLAG_STREAM_3_SHIFT			22u

#define DMA_FLAG_STREAM_0_MASK			0x3Du
#define DMA_FLAG_STREAM_1_MASK			0xF40u
#define DMA_FLAG_STREAM_2_MASK			0x3D0000u
#define DMA_FLAG_STREAM_3_MASK			0xF400000u

#define DMA_FLAG_FIFO_ERROR_MASK				0x01u
#define DMA_FLAG_DIRECT_MODE_ERROR_MASK			0x04u
#define DMA_FLAG_TRANSFER_ERROR_MASK			0x08u
#define DMA_FLAG_HALF_TRANSFER_MASK				0x10u
#define DMA_FLAG_TRANSFER_COMPLETE_MASK			0x20u

/********************************************************************************
 * 							Funtion to access hardware							*
 ********************************************************************************/

/*********************************************************************
 * @fn      		  - Peripheral Clock Control
 *
 */
__STATIC_INLINE void DMA_PeriClockControl(DMA_Type *pDMAx, uint8 EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pDMAx == DMA1)
		{
			DMA1_PCLK_EN();
		}
		else if (pDMAx == DMA2)
		{
			DMA2_PCLK_EN();
		}
		else
		{
			/* Do Nothing */
		}
	}
	else
	{
		//TODO
	}
}

/**
 * DMA Set Transfer Direction 
 *		DMA_PERIPHERAL_TO_MEMORY
 *		DMA_MEMORY_TO_PERIPHERAL
 *		DMA_MEMORY_TO_MEMORY
 */
__STATIC_INLINE void DMA_SetTransferDirection(DMAStream_Type * pDMAStreamx, Dma_TransferDicrectionType eDirection)
{
	pDMAStreamx->CR &= ~DMA_CR_DIR_MASK;
	pDMAStreamx->CR |= DMA_CR_DIR(eDirection);
}

/**
 * DMA Set Data Size to transfer
 */
__STATIC_INLINE void DMA_SetNumberOfData(DMAStream_Type * pDMAStreamx, uint16 datasize) 
{
	pDMAStreamx->NDTR &= ~DMA_NDTR_NDT_MASK;
	pDMAStreamx->NDTR |= DMA_NDTR_NDT(datasize);
}

/**
 * DMA Get Data Size to transfer
 */
__STATIC_INLINE uint16 DMA_GetNumberOfData(DMAStream_Type * pDMAStreamx) 
{
	return (pDMAStreamx->NDTR & DMA_NDTR_NDT_MASK);
}

/**
 * DMA Set Memory Data Width to transfer
 */
__STATIC_INLINE void DMA_SetMemoryDataWidth(DMAStream_Type * pDMAStreamx, Dma_DataWidthType datawidth) 
{
	pDMAStreamx->CR &= ~DMA_CR_MSIZE_MASK;
	pDMAStreamx->CR |= DMA_CR_MSIZE(datawidth);
}

/**
 * DMA Set Peripheral Data Width to transfer
 */
__STATIC_INLINE void DMA_SetPeripheralDataWidth(DMAStream_Type * pDMAStreamx, Dma_DataWidthType datawidth) 
{
	pDMAStreamx->CR &= ~DMA_CR_PSIZE_MASK;
	pDMAStreamx->CR |= DMA_CR_PSIZE(datawidth);
}

/**
 * DMA Set Select Channel Number
 */
__STATIC_INLINE void DMA_SelectChannel(DMAStream_Type * pDMAStreamx, Dma_ChannelType channel) 
{
	pDMAStreamx->CR &= ~DMA_CR_CHSEL_MASK;
	pDMAStreamx->CR |= DMA_CR_CHSEL(channel);
}

/**
 * DMA Set Peripheral Address
 */
__STATIC_INLINE void DMA_SetPeripheralAddress(DMAStream_Type * pDMAStreamx, uint32 address) 
{
	pDMAStreamx->PAR &= ~DMA_PAR_PAR_MASK;
	pDMAStreamx->PAR |= DMA_PAR_PAR(address);
}

/**
 * DMA Set Memory 0 Address
 */
__STATIC_INLINE void DMA_SetMemory0Address(DMAStream_Type * pDMAStreamx, uint32 address) 
{
	pDMAStreamx->M0AR &= ~DMA_M0AR_M0A_MASK;
	pDMAStreamx->M0AR |= DMA_M0AR_M0A(address);
}

/**
 * DMA Set Memory 1 Address
 */
__STATIC_INLINE void DMA_SetMemory1Address(DMAStream_Type * pDMAStreamx, uint32 address) 
{
	pDMAStreamx->M1AR &= ~DMA_M1AR_M1A_MASK;
	pDMAStreamx->M1AR |= DMA_M1AR_M1A(address);
}

/**
 * DMA Set Memory Increment Mode
 */
__STATIC_INLINE void DMA_SetMemIncMode(DMAStream_Type * pDMAStreamx, Dma_IncrementModeType EnorDi)
{
	pDMAStreamx->CR &= ~DMA_CR_MINC_MASK;
	if (DMA_INCREMENT_MODE_ENABLE == EnorDi)
	{
		pDMAStreamx->CR |= DMA_CR_MINC(BIT_SET);
	}
}

/**
 * DMA Set Peripheral Increment Mode
 */
__STATIC_INLINE void DMA_SetPerIncMode(DMAStream_Type * pDMAStreamx, Dma_IncrementModeType EnorDi)
{
	pDMAStreamx->CR &= ~DMA_CR_PINC_MASK;
	if (DMA_INCREMENT_MODE_ENABLE == EnorDi)
	{
		pDMAStreamx->CR |= DMA_CR_PINC(BIT_SET);
	}
}

/**
 * DMA Set DMA Priority
 */
__STATIC_INLINE void DMA_SetPriority(DMAStream_Type * pDMAStreamx, Dma_PrioLevelType PrioLevel)
{
	pDMAStreamx->CR &= ~DMA_CR_PL_MASK;
	pDMAStreamx->CR |= DMA_CR_PL(PrioLevel);
}

/**
 * DMA Start Transfer
 */
__STATIC_INLINE void DMA_HwStartTransfer(DMAStream_Type * pDMAStreamx)
{
	pDMAStreamx->CR |= DMA_CR_EN(BIT_SET);
}

/**
 * DMA Get Status Flags
 */
__STATIC_INLINE uint8 DMA_GetStreamStatus(DMA_Type * pDMAx, Dma_StreamType Stream)
{
	uint32 	readReg = 0u;
	uint8	Status  = 0u;
	
	/* if Stream = 0..3 => Use LISR register */
	if ( ((uint8)Stream >= 0) && ((uint8)Stream <= 3) )
	{
		readReg = pDMAx->LISR;
	}
	else	/* if Stream = 4..7 => Use LISR register */
	{
		readReg = pDMAx->HISR;
	}
	
	switch (Stream % 4)
	{
		case 0u:
			Status = (readReg << DMA_FLAG_STREAM_0_SHIFT) & DMA_FLAG_STREAM_0_MASK;
			break;
		case 1u:
			Status = (readReg << DMA_FLAG_STREAM_1_SHIFT) & DMA_FLAG_STREAM_1_MASK;
			break;
		case 2u:
			Status = (readReg << DMA_FLAG_STREAM_2_SHIFT) & DMA_FLAG_STREAM_2_MASK;
			break;
		case 3u:
			Status = (readReg << DMA_FLAG_STREAM_3_SHIFT) & DMA_FLAG_STREAM_3_MASK;
			break;
		default:
			break;
	}
	
	return Status;
}


/******************************************************************************/
/****************************** TIMEOUT FUNCTIONS *****************************/
/**
 * @brief   : Prepare for timeout checking
 * @
 * @return  : None
 */
__STATIC_INLINE void Systick_StartTimeout(uint32 * StartTimeOut, uint32 *TimeoutTicksOut, uint32 TimeoutUs)
{
    *StartTimeOut    = Systick_GetCounter();
    *TimeoutTicksOut = Systick_MicrosToTicks(TimeoutUs);
}

/**
 * @brief   : Checks for timeout condition
 * @
 * @return  TRUE     Timeout occurs
 *          FALSE    Timeout does not occur
 */
__STATIC_INLINE Bool_Type Systick_CheckTimeout(uint32 * StartTime, uint32 * ElapsedTicks, uint32 TimeoutTicks)
{
    uint32 CurrentElapsedTicks = Systick_GetElapsed(StartTime);
    *ElapsedTicks += CurrentElapsedTicks;
    return ((*ElapsedTicks >= TimeoutTicks) ? TRUE : FALSE);
}

#endif 	/* !(__DMA_HWACCESS_H__) */
