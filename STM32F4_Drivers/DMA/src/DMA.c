/**
 * Filename		: DMA.c
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: DMA Driver Code
 */

#include "DMA.h"
#include "DMA_HwAccess.h"

/*****************************************************************************************/
/************************************ Private Variables **********************************/
/** @brief User config structure. */
const Dma_UserConfigType * Dma_UserConfig_Pointer[DMA_INSTANCE_COUNT];

static DMA_Type * const Dma_Base_Pointer[DMA_INSTANCE_COUNT] = DMA_BASE_PTRS;

/*****************************************************************************************/
/************************************ Private Functions **********************************/


/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_Init
 *
 * @brief             - Initialize DMA Driver
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - UserConfig 	- DMA User Configuration
 *
 * @return            -
 *
 * @Note              -
 */
void DMA_Init(const uint8 Instance, const Dma_UserConfigType * UserConfig)
{
	DMA_Type 					* Base 				= Dma_Base_Pointer[Instance];
	DMAStream_Type 				* pDMAStreamx		= &(Base->Stream[UserConfig->DMA_Streamx]);
	Dma_UserStreamConfigType 	* UserStreamConfig 	= UserConfig->DMA_StreamConfig;
	/* Assign Config to Static Variables */
	Dma_UserConfig_Pointer[Instance] = UserConfig;
	
	/* Implement the code to enable the Clock for given DMA peripheral */
	DMA_PeriClockControl(Base, ENABLE);
	
	/* DMA Select Channel */
	DMA_SelectChannel(pDMAStreamx, UserStreamConfig->DMA_Channel);
	
	/* DMA Configure DMA Direction */
	DMA_SetTransferDirection(pDMAStreamx, UserStreamConfig->DMA_Direction);
	
	/* DMA Set Priority for Channel */
	DMA_SetPriority(pDMAStreamx, UserStreamConfig->DMA_Priority);
	
	/* DMA Set Data Width to transfer */
	/* DMA Set Increment Mode (ENABLE or DISABLE) */
	switch (UserStreamConfig->DMA_Direction)
	{
		case DMA_PERIPHERAL_TO_MEMORY:
			DMA_SetPeripheralDataWidth(pDMAStreamx, UserStreamConfig->DMA_SrcDataWidth);
			DMA_SetMemoryDataWidth(pDMAStreamx, UserStreamConfig->DMA_DesDataWidth);
			DMA_SetPerIncMode(pDMAStreamx, UserStreamConfig->DMA_SrcIncMode);
			DMA_SetMemIncMode(pDMAStreamx, UserStreamConfig->DMA_DesIncMode);
			break;
		case DMA_MEMORY_TO_PERIPHERAL:
			DMA_SetMemoryDataWidth(pDMAStreamx, UserStreamConfig->DMA_SrcDataWidth);
			DMA_SetPeripheralDataWidth(pDMAStreamx, UserStreamConfig->DMA_DesDataWidth);
			DMA_SetMemIncMode(pDMAStreamx, UserStreamConfig->DMA_SrcIncMode);
			DMA_SetPerIncMode(pDMAStreamx, UserStreamConfig->DMA_DesIncMode);
			break;
		case DMA_MEMORY_TO_MEMORY:
			DMA_SetMemoryDataWidth(pDMAStreamx, UserStreamConfig->DMA_SrcDataWidth);
			DMA_SetMemoryDataWidth(pDMAStreamx, UserStreamConfig->DMA_DesDataWidth);
			DMA_SetMemIncMode(pDMAStreamx, UserStreamConfig->DMA_SrcIncMode);
			DMA_SetMemIncMode(pDMAStreamx, UserStreamConfig->DMA_DesIncMode);
			break;
		default:
			/* @TODO Set an error */
			break;
	}
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_TransferConfig
 *
 * @brief             - Configure Source/Destination to transfer
 *
 * @param[in]         - UserTransferConfig 	- DMA Hardware Instance
 *
 * @return            -
 *
 * @Note              -
 */
void DMA_TransferConfig(const Dma_UserTransferType * UserTransferConfig)
{
	const uint8 	Instance 		= UserTransferConfig->DMA_Instance;
	DMA_Type 		* Base 			= Dma_Base_Pointer[Instance];
	DMAStream_Type 	* pDMAStreamx	= &(Base->Stream[UserTransferConfig->DMA_Streamx]);
	
	Dma_UserStreamConfigType * UserStreamConfig = (Dma_UserConfig_Pointer[Instance])->DMA_StreamConfig;
	
	/* Set Source/Destination Address */
	switch (UserStreamConfig->DMA_Direction)
	{
		case DMA_PERIPHERAL_TO_MEMORY:
		case DMA_MEMORY_TO_MEMORY:
			DMA_SetPeripheralAddress(pDMAStreamx, UserTransferConfig->DMA_srcAddress);
			DMA_SetMemory0Address(pDMAStreamx, UserTransferConfig->DMA_desAddress);
			break;
		case DMA_MEMORY_TO_PERIPHERAL:
			DMA_SetMemory0Address(pDMAStreamx, UserTransferConfig->DMA_srcAddress);
			DMA_SetPeripheralAddress(pDMAStreamx, UserTransferConfig->DMA_desAddress);
			break;
		default:
			/* @TODO Set an error */
			break;
	}
	
	/* Set Number of Data to transfer */
	DMA_SetNumberOfData(pDMAStreamx, UserTransferConfig->DMA_DataSize);
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_GetStatusFlag
 *
 * @brief             - Get Status Flag from interrupt status registers
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Streamx 	- DMA Hardware Stream
 *
 * @return            -
 *
 * @Note              -
 */
uint8 DMA_GetStatusFlag(const uint8 Instance, Dma_StreamType Stream)
{
	DMA_Type 		* Base 			= Dma_Base_Pointer[Instance];
	uint8			StreamStatus;
	
	StreamStatus = DMA_GetStreamStatus(Base, Stream);
	
	return StreamStatus;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_CheckStatusFlag
 *
 * @brief             - Get Status Flag from interrupt status registers
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Streamx 	- DMA Hardware Stream
 *
 * @return            -
 *
 * @Note              -
 */
boolean DMA_CheckStatusFlag(const uint8 Instance, Dma_StreamType Stream, DMA_StatusFlagType FlagType)
{
	uint8 StreamStatus = DMA_GetStatusFlag(Instance, Stream);
	boolean checkFlag = FALSE;
	
	switch (FlagType)
	{
		case DMA_FLAG_FIFO_ERROR_INT:
			checkFlag = (boolean)((StreamStatus << (uint8)FlagType) & DMA_FLAG_FIFO_ERROR_MASK);
			break;
		case DMA_FLAG_DIRECT_MODE_ERROR_INT:
			checkFlag = (boolean)((StreamStatus << (uint8)FlagType) & DMA_FLAG_DIRECT_MODE_ERROR_MASK);
			break;
		case DMA_FLAG_TRANSFER_ERROR_INT:
			checkFlag = (boolean)((StreamStatus << (uint8)FlagType) & DMA_FLAG_TRANSFER_ERROR_MASK);
			break;
		case DMA_FLAG_HALF_TRANSFER_INT:
			checkFlag = (boolean)((StreamStatus << (uint8)FlagType) & DMA_FLAG_HALF_TRANSFER_MASK);
			break;
		case DMA_FLAG_TRANSFER_COMPLETE_INT:
			checkFlag = (boolean)((StreamStatus << (uint8)FlagType) & DMA_FLAG_TRANSFER_COMPLETE_MASK);
			break;
		default:
			break;
	}
	
	return checkFlag;
}

