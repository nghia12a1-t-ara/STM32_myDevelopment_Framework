/**
 * Filename		: DMA_HwAccess.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: DMA Hardware Access
 */

#ifndef __DMA_HWACCESS_H__
#define __DMA_HWACCESS_H__

#include "DMA_Type.h"

#define DMA_FLAG_STREAM_0_SHIFT			0U
#define DMA_FLAG_STREAM_1_SHIFT			6U
#define DMA_FLAG_STREAM_2_SHIFT			16U
#define DMA_FLAG_STREAM_3_SHIFT			22U

#define DMA_FLAG_STREAM_0_MASK			0x3DU
#define DMA_FLAG_STREAM_1_MASK			0xF40U
#define DMA_FLAG_STREAM_2_MASK			0x3D0000U
#define DMA_FLAG_STREAM_3_MASK			0xF400000U

#define DMA_FLAG_FEIF_MASK				0x01U	/**< FIFO Error Interrupt Flag */
#define DMA_FLAG_DMEIF_MASK				0x04U	/**< Direct Mode Error Interrupt Flag */
#define DMA_FLAG_TEIF_MASK				0x08U	/**< Transfer Error Interrupt Flag */
#define DMA_FLAG_HTIF_MASK				0x10U	/**< Half Transfer Interrupt Flag */
#define DMA_FLAG_TCIF_MASK				0x20U	/**< Transfer Complete Interrupt Flag */

#define DMA_SxCR_EN						0x00000001U
#define DMA_SxCR_DMEIE					0x00000002U
#define DMA_SxCR_TEIE					0x00000004U
#define DMA_SxCR_HTIE					0x00000008U
#define DMA_SxCR_TCIE					0x00000010U
#define DMA_SxCR_PFCTRL					0x00000020U
#define DMA_SxCR_DIR_Pos				6U
#define DMA_SxCR_DIR_Msk				0x000000C0U
#define DMA_SxCR_CIRC					0x00000100U
#define DMA_SxCR_PINC					0x00000200U
#define DMA_SxCR_MINC					0x00000400U
#define DMA_SxCR_PSIZE_Pos				11U
#define DMA_SxCR_PSIZE_Msk				0x00001800U
#define DMA_SxCR_MSIZE_Pos				13U
#define DMA_SxCR_MSIZE_Msk				0x00006000U
#define DMA_SxCR_PINCOS					0x00008000U
#define DMA_SxCR_PL_Pos					16U
#define DMA_SxCR_PL_Msk					0x00030000U
#define DMA_SxCR_DBM					0x00040000U
#define DMA_SxCR_CT						0x00080000U
#define DMA_SxCR_PBURST_Pos				21U
#define DMA_SxCR_PBURST_Msk				0x00600000U
#define DMA_SxCR_MBURST_Pos				23U
#define DMA_SxCR_MBURST_Msk				0x01800000U
#define DMA_SxCR_CHSEL_Pos				25U
#define DMA_SxCR_CHSEL_Msk				0x0E000000U

#define DMA_SxFCR_FEIE					0x00000080U

/********************************************************************************
 * 							Function to access hardware						*
 ********************************************************************************/

__STATIC_INLINE DMA_StatusType DMA_PeriClockControl(DMA_TypeDef *pDMAx, uint8_t EnorDi)
{
	if (pDMAx == NULL)
	{
		return DMA_STATUS_ERROR;
	}
	
	if (EnorDi == ENABLE)
	{
		if (pDMAx == DMA1)
		{
			RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
		}
		else if (pDMAx == DMA2)
		{
			RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		}
		else
		{
			return DMA_STATUS_INVALID_PARAM;
		}
	}
	else
	{
		if (pDMAx == DMA1)
		{
			RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA1EN;
		}
		else if (pDMAx == DMA2)
		{
			RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
		}
		else
		{
			return DMA_STATUS_INVALID_PARAM;
		}
	}
	
	return DMA_STATUS_OK;
}

__STATIC_INLINE void DMA_SetTransferDirection(DMA_Stream_TypeDef * pDMAStreamx, DMA_TransferDirectionType eDirection)
{
	pDMAStreamx->CR &= ~DMA_SxCR_DIR_Msk;
	pDMAStreamx->CR |= ((uint32_t)eDirection << DMA_SxCR_DIR_Pos);
}

__STATIC_INLINE void DMA_SetNumberOfData(DMA_Stream_TypeDef * pDMAStreamx, uint16_t datasize) 
{
	pDMAStreamx->NDTR = datasize;
}

__STATIC_INLINE uint16_t DMA_GetNumberOfData(DMA_Stream_TypeDef * pDMAStreamx) 
{
	return (uint16_t)(pDMAStreamx->NDTR & 0xFFFFU);
}

__STATIC_INLINE void DMA_SetMemoryDataWidth(DMA_Stream_TypeDef * pDMAStreamx, DMA_DataWidthType datawidth) 
{
	pDMAStreamx->CR &= ~DMA_SxCR_MSIZE_Msk;
	pDMAStreamx->CR |= ((uint32_t)datawidth << DMA_SxCR_MSIZE_Pos);
}

__STATIC_INLINE void DMA_SetPeripheralDataWidth(DMA_Stream_TypeDef * pDMAStreamx, DMA_DataWidthType datawidth) 
{
	pDMAStreamx->CR &= ~DMA_SxCR_PSIZE_Msk;
	pDMAStreamx->CR |= ((uint32_t)datawidth << DMA_SxCR_PSIZE_Pos);
}

__STATIC_INLINE void DMA_SelectChannel(DMA_Stream_TypeDef * pDMAStreamx, DMA_ChannelType channel) 
{
	pDMAStreamx->CR &= ~DMA_SxCR_CHSEL_Msk;
	pDMAStreamx->CR |= ((uint32_t)channel << DMA_SxCR_CHSEL_Pos);
}

__STATIC_INLINE void DMA_SetPeripheralAddress(DMA_Stream_TypeDef * pDMAStreamx, uint32_t address) 
{
	pDMAStreamx->PAR = address;
}

__STATIC_INLINE void DMA_SetMemory0Address(DMA_Stream_TypeDef * pDMAStreamx, uint32_t address) 
{
	pDMAStreamx->M0AR = address;
}

__STATIC_INLINE void DMA_SetMemory1Address(DMA_Stream_TypeDef * pDMAStreamx, uint32_t address) 
{
	pDMAStreamx->M1AR = address;
}

__STATIC_INLINE void DMA_SetMemIncMode(DMA_Stream_TypeDef * pDMAStreamx, DMA_IncrementModeType EnorDi)
{
	if (DMA_INCREMENT_MODE_ENABLE == EnorDi)
	{
		pDMAStreamx->CR |= DMA_SxCR_MINC;
	}
	else
	{
		pDMAStreamx->CR &= ~DMA_SxCR_MINC;
	}
}

__STATIC_INLINE void DMA_SetPerIncMode(DMA_Stream_TypeDef * pDMAStreamx, DMA_IncrementModeType EnorDi)
{
	if (DMA_INCREMENT_MODE_ENABLE == EnorDi)
	{
		pDMAStreamx->CR |= DMA_SxCR_PINC;
	}
	else
	{
		pDMAStreamx->CR &= ~DMA_SxCR_PINC;
	}
}

__STATIC_INLINE void DMA_SetPriority(DMA_Stream_TypeDef * pDMAStreamx, DMA_PrioLevelType PrioLevel)
{
	pDMAStreamx->CR &= ~DMA_SxCR_PL_Msk;
	pDMAStreamx->CR |= ((uint32_t)PrioLevel << DMA_SxCR_PL_Pos);
}

__STATIC_INLINE void DMA_SetTransferMode(DMA_Stream_TypeDef * pDMAStreamx, DMA_TransferModeType mode)
{
	if (mode == DMA_TRANSFER_CIRCULAR)
	{
		pDMAStreamx->CR |= DMA_SxCR_CIRC;
	}
	else
	{
		pDMAStreamx->CR &= ~DMA_SxCR_CIRC;
	}
}

__STATIC_INLINE void DMA_HwStartTransfer(DMA_Stream_TypeDef * pDMAStreamx)
{
	pDMAStreamx->CR |= DMA_SxCR_EN;
}

__STATIC_INLINE void DMA_HwStopTransfer(DMA_Stream_TypeDef * pDMAStreamx)
{
	pDMAStreamx->CR &= ~DMA_SxCR_EN;
}

__STATIC_INLINE uint8_t DMA_IsStreamEnabled(DMA_Stream_TypeDef * pDMAStreamx)
{
	return ((pDMAStreamx->CR & DMA_SxCR_EN) != 0U) ? 1U : 0U;
}

__STATIC_INLINE uint32_t DMA_GetStreamStatus(DMA_TypeDef * pDMAx, DMA_StreamType Stream)
{
	uint32_t readReg = 0U;
	uint32_t Status = 0U;
	
	/* if Stream = 0..3 => Use LISR register */
	if (Stream <= DMA_STREAM_3)
	{
		readReg = pDMAx->LISR;
	}
	else	/* if Stream = 4..7 => Use HISR register */
	{
		readReg = pDMAx->HISR;
	}
	
	switch (Stream % 4U)
	{
		case 0U:
			Status = (readReg >> DMA_FLAG_STREAM_0_SHIFT) & 0x3DU;
			break;
		case 1U:
			Status = (readReg >> DMA_FLAG_STREAM_1_SHIFT) & 0x3DU;
			break;
		case 2U:
			Status = (readReg >> DMA_FLAG_STREAM_2_SHIFT) & 0x3DU;
			break;
		case 3U:
			Status = (readReg >> DMA_FLAG_STREAM_3_SHIFT) & 0x3DU;
			break;
		default:
			break;
	}
	
	return Status;
}

__STATIC_INLINE void DMA_ClearStreamFlags(DMA_TypeDef * pDMAx, DMA_StreamType Stream, uint32_t FlagMask)
{
	uint32_t clearMask = 0U;
	
	switch (Stream % 4U)
	{
		case 0U:
			clearMask = FlagMask << DMA_FLAG_STREAM_0_SHIFT;
			break;
		case 1U:
			clearMask = FlagMask << DMA_FLAG_STREAM_1_SHIFT;
			break;
		case 2U:
			clearMask = FlagMask << DMA_FLAG_STREAM_2_SHIFT;
			break;
		case 3U:
			clearMask = FlagMask << DMA_FLAG_STREAM_3_SHIFT;
			break;
		default:
			return;
	}
	
	if (Stream <= DMA_STREAM_3)
	{
		pDMAx->LIFCR = clearMask;
	}
	else
	{
		pDMAx->HIFCR = clearMask;
	}
}

__STATIC_INLINE DMA_TypeDef* DMA_GetInstance(DMA_InstanceType Instance)
{
	switch (Instance)
	{
		case DMA_INSTANCE_1:
			return DMA1;
		case DMA_INSTANCE_2:
			return DMA2;
		default:
			return NULL;
	}
}

__STATIC_INLINE DMA_Stream_TypeDef* DMA_GetStreamInstance(DMA_InstanceType Instance, DMA_StreamType Stream)
{
	DMA_TypeDef* dmaBase = DMA_GetInstance(Instance);
	if (dmaBase == NULL || Stream >= DMA_STREAM_MAX)
	{
		return NULL;
	}
	
	return &(dmaBase->Stream[Stream]);
}

#endif 	/* !(__DMA_HWACCESS_H__) */
