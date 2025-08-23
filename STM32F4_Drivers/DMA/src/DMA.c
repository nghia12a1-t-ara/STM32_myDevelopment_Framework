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
static Bool_Type DMA_ValidateInstance(const uint8 Instance)
{
	return (Instance < DMA_INSTANCE_COUNT) ? TRUE : FALSE;
}

static Bool_Type DMA_ValidateStream(const Dma_StreamType Stream)
{
	return ((uint8)Stream < DMA_STREAM_COUNT) ? TRUE : FALSE;
}

static Bool_Type DMA_ValidatePointer(const void* ptr)
{
	return (ptr != NULL) ? TRUE : FALSE;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_Init
 *
 * @brief             - Initialize DMA Driver
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - UserConfig 	- DMA User Configuration
 *
 * @return            - Dma_StatusType - Operation status
 *
 * @Note              -
 */
Dma_StatusType DMA_Init(const uint8 Instance, const Dma_UserConfigType * UserConfig)
{
	if (!DMA_ValidateInstance(Instance))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	if (!DMA_ValidatePointer(UserConfig) || !DMA_ValidatePointer(UserConfig->DMA_StreamConfig))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	if (!DMA_ValidateStream(UserConfig->DMA_Streamx))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	DMA_Type 					* Base 				= Dma_Base_Pointer[Instance];
	DMAStream_Type 				* pDMAStreamx		= &(Base->Stream[UserConfig->DMA_Streamx]);
	Dma_UserStreamConfigType 	* UserStreamConfig 	= UserConfig->DMA_StreamConfig;
	
	if (DMA_IsStreamEnabled(pDMAStreamx))
	{
		return DMA_STATUS_BUSY;
	}
	
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
	
	return DMA_STATUS_SUCCESS;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_DeInit
 *
 * @brief             - Deinitialize DMA Driver
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 *
 * @return            - Dma_StatusType - Operation status
 *
 * @Note              -
 */
Dma_StatusType DMA_DeInit(const uint8 Instance)
{
	if (!DMA_ValidateInstance(Instance))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	DMA_Type * Base = Dma_Base_Pointer[Instance];
	
	/* Stop all streams */
	for (uint8 stream = 0; stream < DMA_STREAM_COUNT; stream++)
	{
		DMA_HwStopTransfer(&(Base->Stream[stream]));
		
		/* Clear all flags */
		DMA_ClearStreamFlags(Base, (Dma_StreamType)stream, 0x3FU);
		
		/* Reset stream configuration */
		Base->Stream[stream].CR = 0x00000000U;
		Base->Stream[stream].NDTR = 0x00000000U;
		Base->Stream[stream].PAR = 0x00000000U;
		Base->Stream[stream].M0AR = 0x00000000U;
		Base->Stream[stream].M1AR = 0x00000000U;
		Base->Stream[stream].FCR = 0x00000021U;
	}
	
	/* Disable peripheral clock */
	DMA_PeriClockControl(Base, DISABLE);
	
	/* Clear user config pointer */
	Dma_UserConfig_Pointer[Instance] = NULL;
	
	return DMA_STATUS_SUCCESS;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_TransferConfig
 *
 * @brief             - Configure Source/Destination to transfer
 *
 * @param[in]         - UserTransferConfig 	- DMA Hardware Instance
 *
 * @return            - Dma_StatusType - Operation status
 *
 * @Note              -
 */
Dma_StatusType DMA_TransferConfig(const Dma_UserTransferType * UserTransferConfig)
{
	if (!DMA_ValidatePointer(UserTransferConfig))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	const uint8 	Instance 		= UserTransferConfig->DMA_Instance;
	
	if (!DMA_ValidateInstance(Instance) || !DMA_ValidateStream(UserTransferConfig->DMA_Streamx))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	if (Dma_UserConfig_Pointer[Instance] == NULL)
	{
		return DMA_STATUS_NOT_INITIALIZED;
	}
	
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
	
	return DMA_STATUS_SUCCESS;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_SyncStartTransfer
 *
 * @brief             - Configure Param and Start Transfer (Polling Method) - Check Timeout
 *
 * @param[in]         - UserTransferConfig 	- DMA Hardware Instance
 * @param[in]         - Timeout 			- Timeout if data cannot transmit
 * 
 * @param[out]        - Dma_StatusType 		- Dma Transfer Status (SUCCESS or TIMEOUT)
 *
 * @return            -
 *
 * @Note              -
 */
Dma_StatusType DMA_SyncStartTransfer(const Dma_UserTransferType * UserTransferConfig, const uint32 Timeout)
{
	if (!DMA_ValidatePointer(UserTransferConfig))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	const uint8 	Instance 		= UserTransferConfig->DMA_Instance;
	
	if (!DMA_ValidateInstance(Instance) || !DMA_ValidateStream(UserTransferConfig->DMA_Streamx))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	DMA_Type 		* Base 			= Dma_Base_Pointer[Instance];
	DMAStream_Type 	* pDMAStreamx	= &(Base->Stream[UserTransferConfig->DMA_Streamx]);
	Dma_StatusType	Dma_Status		= DMA_STATUS_ERROR;
	
	/* Timeout Setup Variables */
	uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;
	
	/* Configure Source/Destination Address */
	Dma_Status = DMA_TransferConfig(UserTransferConfig);
	if (Dma_Status != DMA_STATUS_SUCCESS)
	{
		return Dma_Status;
	}
	
	/* DMA Start Transfer */
	DMA_HwStartTransfer(pDMAStreamx);
	
	/* Start Timeout - Can using Systick Timer */
    Systick_StartTimeout(&StartTime, &TimeoutTicks, Timeout);
	
	/* Wait transfer successfully or Timeout occurs */
	while ( (!DMA_CheckStatusFlag(Instance, UserTransferConfig->DMA_Streamx, DMA_FLAG_TRANSFER_COMPLETE_INT)) && \
			 !Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) );
	
	/* Check if Timeout occur */
	if ( Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) )
	{
		Dma_Status = DMA_STATUS_TIMEOUT;
		/* Stop transfer on timeout */
		DMA_HwStopTransfer(pDMAStreamx);
	}
	else	/* The transfer process is complete */
	{
		Dma_Status = DMA_STATUS_SUCCESS;
	}
	
	/* Clear transfer complete flag */
	DMA_ClearFlags(Instance, UserTransferConfig->DMA_Streamx, DMA_FLAG_TRANSFER_COMPLETE_INT);
	
	return Dma_Status;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_AsyncStartTransfer
 *
 * @brief             - Configure Param and Start Transfer (Interrupt Method)
 *
 * @param[in]         - UserTransferConfig 	- DMA Hardware Instance
 * 
 * @param[out]        - Dma_StatusType 		- Dma Transfer Status (SUCCESS or ERROR)
 *
 * @return            -
 *
 * @Note              -
 */
Dma_StatusType DMA_AsyncStartTransfer(const Dma_UserTransferType * UserTransferConfig)
{
	if (!DMA_ValidatePointer(UserTransferConfig))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	const uint8 Instance = UserTransferConfig->DMA_Instance;
	
	if (!DMA_ValidateInstance(Instance) || !DMA_ValidateStream(UserTransferConfig->DMA_Streamx))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	if (Dma_UserConfig_Pointer[Instance] == NULL)
	{
		return DMA_STATUS_NOT_INITIALIZED;
	}
	
	DMA_Type * Base = Dma_Base_Pointer[Instance];
	DMAStream_Type * pDMAStreamx = &(Base->Stream[UserTransferConfig->DMA_Streamx]);
	
	/* Configure Source/Destination Address */
	Dma_StatusType status = DMA_TransferConfig(UserTransferConfig);
	if (status != DMA_STATUS_SUCCESS)
	{
		return status;
	}
	
	/* Enable transfer complete interrupt */
	pDMAStreamx->CR |= DMA_CR_TCIE_MASK;
	
	/* Enable error interrupts */
	pDMAStreamx->CR |= DMA_CR_TEIE_MASK | DMA_CR_DMEIE_MASK;
	pDMAStreamx->FCR |= DMA_FCR_FEIE_MASK;
	
	/* Start transfer */
	DMA_HwStartTransfer(pDMAStreamx);
	
	return DMA_STATUS_SUCCESS;
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
 * @return            - uint8 - Stream status
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
 * @return            - Bool_Type - Flag check result
 *
 * @Note              - This function checks if a specific status flag is set in the DMA stream.
 */
Bool_Type DMA_CheckStatusFlag(const uint8 Instance, Dma_StreamType Stream, DMA_StatusFlagType FlagType)
{
	uint8 StreamStatus = DMA_GetStatusFlag(Instance, Stream);
	Bool_Type checkFlag = FALSE;
	
	switch (FlagType)
	{
		case DMA_FLAG_FIFO_ERROR_INT:
			checkFlag = (Bool_Type)((StreamStatus & DMA_FLAG_FIFO_ERROR_MASK) >> (uint8)FlagType);
			break;
		case DMA_FLAG_DIRECT_MODE_ERROR_INT:
			checkFlag = (Bool_Type)((StreamStatus & DMA_FLAG_DIRECT_MODE_ERROR_MASK) >> (uint8)FlagType);
			break;
		case DMA_FLAG_TRANSFER_ERROR_INT:
			checkFlag = (Bool_Type)((StreamStatus & DMA_FLAG_TRANSFER_ERROR_MASK) >> (uint8)FlagType);
			break;
		case DMA_FLAG_HALF_TRANSFER_INT:
			checkFlag = (Bool_Type)((StreamStatus & DMA_FLAG_HALF_TRANSFER_MASK) >> (uint8)FlagType);
			break;
		case DMA_FLAG_TRANSFER_COMPLETE_INT:
			checkFlag = (Bool_Type)((StreamStatus & DMA_FLAG_TRANSFER_COMPLETE_MASK) >> (uint8)FlagType);
			break;
		default:
			break;
	}
	
	return checkFlag;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_Stop
 *
 * @brief             - Stop DMA Transfer
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 *
 * @return            - Dma_StatusType - Operation status
 *
 * @Note              -
 */
Dma_StatusType DMA_Stop(const uint8 Instance, Dma_StreamType Stream)
{
	if (!DMA_ValidateInstance(Instance) || !DMA_ValidateStream(Stream))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	DMA_Type * Base = Dma_Base_Pointer[Instance];
	DMAStream_Type * pDMAStreamx = &(Base->Stream[Stream]);
	
	/* Stop transfer */
	DMA_HwStopTransfer(pDMAStreamx);
	
	/* Wait for stream to be disabled */
	uint32 timeout = 1000;
	while (DMA_IsStreamEnabled(pDMAStreamx) && (timeout-- > 0));
	
	if (timeout == 0)
	{
		return DMA_STATUS_TIMEOUT;
	}
	
	/* Clear all flags */
	DMA_ClearStreamFlags(Base, Stream, 0x3FU);
	
	return DMA_STATUS_SUCCESS;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_ClearFlags
 *
 * @brief             - Clear DMA Status Flags
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 * @param[in]         - FlagType  - Flag type to clear
 *
 * @return            - Dma_StatusType - Operation status
 *
 * @Note              -
 */
Dma_StatusType DMA_ClearFlags(const uint8 Instance, Dma_StreamType Stream, DMA_StatusFlagType FlagType)
{
	if (!DMA_ValidateInstance(Instance) || !DMA_ValidateStream(Stream))
	{
		return DMA_STATUS_INVALID_PARAM;
	}
	
	DMA_Type * Base = Dma_Base_Pointer[Instance];
	uint32 flagMask = 0;
	
	switch (FlagType)
	{
		case DMA_FLAG_FIFO_ERROR_INT:
			flagMask = DMA_FLAG_FIFO_ERROR_MASK;
			break;
		case DMA_FLAG_DIRECT_MODE_ERROR_INT:
			flagMask = DMA_FLAG_DIRECT_MODE_ERROR_MASK;
			break;
		case DMA_FLAG_TRANSFER_ERROR_INT:
			flagMask = DMA_FLAG_TRANSFER_ERROR_MASK;
			break;
		case DMA_FLAG_HALF_TRANSFER_INT:
			flagMask = DMA_FLAG_HALF_TRANSFER_MASK;
			break;
		case DMA_FLAG_TRANSFER_COMPLETE_INT:
			flagMask = DMA_FLAG_TRANSFER_COMPLETE_MASK;
			break;
		default:
			return DMA_STATUS_INVALID_PARAM;
	}
	
	DMA_ClearStreamFlags(Base, Stream, flagMask);
	
	return DMA_STATUS_SUCCESS;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_GetTransferCount
 *
 * @brief             - Get remaining transfer count
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 *
 * @return            - uint16 - Remaining transfer count
 *
 * @Note              -
 */
uint16 DMA_GetTransferCount(const uint8 Instance, Dma_StreamType Stream)
{
	if (!DMA_ValidateInstance(Instance) || !DMA_ValidateStream(Stream))
	{
		return 0;
	}
	
	DMA_Type * Base = Dma_Base_Pointer[Instance];
	DMAStream_Type * pDMAStreamx = &(Base->Stream[Stream]);
	
	return DMA_GetNumberOfData(pDMAStreamx);
}
