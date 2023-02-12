/**
 * Filename		: DMA_Type.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: DMA definitions and types
 */

#ifndef __DMA_TYPE_H__
#define __DMA_TYPE_H__

/**
 * DMA Instances for STM32F401
 */
typedef enum
{
	DMA_INSTANCE_1				= 1u,
	DMA_INSTANCE_2				= 2u,
} DMA_InstanceType;

/**
 * Define DMA Stream
 */
typedef enum {
	DMA_STREAM_0					= 0u,
	DMA_STREAM_1					= 1u,
	DMA_STREAM_2					= 2u,
	DMA_STREAM_3					= 3u,
	DMA_STREAM_4					= 4u,
	DMA_STREAM_5					= 5u,
	DMA_STREAM_6					= 6u,
	DMA_STREAM_7					= 7u,
} Dma_StreamType;

/**
 * Define DMA Channel
 */
typedef enum {
	DMA_CHANNEL_0					= 0u,
	DMA_CHANNEL_1					= 1u,
	DMA_CHANNEL_2					= 2u,
	DMA_CHANNEL_3					= 3u,
	DMA_CHANNEL_4					= 4u,
	DMA_CHANNEL_5					= 5u,
	DMA_CHANNEL_6					= 6u,
	DMA_CHANNEL_7					= 7u,
} Dma_ChannelType;

/**
 * Define Memory/Peripheral Burst Transfer Configuration
 */
typedef enum {
	DMA_SINGLE_TRANSFER				= 0u,
	DMA_INC_BURST_4_BEAT			= 1u,
	DMA_INC_BURST_8_BEAT			= 2u,
	DMA_INC_BURST_16_BEAT			= 3u,
} Dma_BurstTransferType;

/**
 * Define DMA Priority Level
 */
typedef enum {
	DMA_PRIO_LEVEL_LOW				= 0u,
	DMA_PRIO_LEVEL_MEDIUM			= 1u,
	DMA_PRIO_LEVEL_HIGH				= 2u,
	DMA_PRIO_LEVEL_VERYHIGH			= 3u,
} Dma_PrioLevelType;
/**
 * Define DMA Memory/Peripheral Data Size
 */
typedef enum {
	DMA_DATA_WIDTH_8_BITS			= 0u,
	DMA_DATA_WIDTH_16_BITS			= 1u,
	DMA_DATA_WIDTH_32_BITS			= 2u,
} Dma_DataWidthType;

/**
 * Define DMA Data Transfer Direction
 */
typedef enum {
	DMA_PERIPHERAL_TO_MEMORY		= 0u,
	DMA_MEMORY_TO_PERIPHERAL		= 1u,
	DMA_MEMORY_TO_MEMORY			= 2u,
} Dma_TransferDicrectionType;

/**
 * Define DMA Increment Mode
 */
typedef enum {
	DMA_INCREMENT_MODE_DISABLE		= FALSE,
	DMA_INCREMENT_MODE_ENABLE		= TRUE,
} Dma_IncrementModeType;

/**
 * @brief Driver status type.
 * */
typedef enum
{
    DMA_STATUS_SUCCESS              = 0x00U,  		/**< @brief Success status */
    DMA_STATUS_ERROR                = 0x01U  		/**< @brief DMA error */
} Dma_StatusType;

/*****************************************************************************/
/**
 * Define DMA User Configuration Type
 */
typedef struct {
	Dma_ChannelType					DMA_Channel;
	Dma_PrioLevelType				DMA_Priority;
	Dma_TransferDicrectionType		DMA_Direction;
	Dma_DataWidthType				DMA_SrcDataWidth;
	Dma_DataWidthType				DMA_DesDataWidth;
	Dma_IncrementModeType			DMA_SrcIncMode;
	Dma_IncrementModeType			DMA_DesIncMode;
} Dma_UserStreamConfigType;

/**
 * Define DMA User Configuration Type
 */
typedef struct {
	Dma_StreamType					DMA_Streamx;
	Dma_UserStreamConfigType		*DMA_StreamConfig;
} Dma_UserConfigType;

/**
 * Define DMA Transfer Configuration Type
 */
typedef struct {
	uint8							DMA_Instance;
	Dma_StreamType					DMA_Streamx;
	uint32							DMA_srcAddress;
	uint32							DMA_desAddress;
	uint16							DMA_DataSize;
} Dma_UserTransferType;



#endif 	/* !(__DMA_TYPE_H__) */
