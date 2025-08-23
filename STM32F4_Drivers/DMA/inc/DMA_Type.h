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
	DMA_INSTANCE_MAX			= 3u,  // Added max value for validation
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
	DMA_STREAM_MAX					= 8u,  // Added max value for validation
} DMA_StreamType;

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
} DMA_ChannelType;

/**
 * Define DMA Interrupt Types
 */
typedef enum {
	DMA_INTERRUPT_TC				= 0u,	/**< Transfer Complete */
	DMA_INTERRUPT_HT				= 1u,	/**< Half Transfer */
	DMA_INTERRUPT_TE				= 2u,	/**< Transfer Error */
	DMA_INTERRUPT_DME				= 3u,	/**< Direct Mode Error */
	DMA_INTERRUPT_FE				= 4u,	/**< FIFO Error */
	DMA_INTERRUPT_ALL				= 5u,	/**< All Interrupts */
} DMA_InterruptType;

/**
 * Define DMA Error Types
 */
typedef enum {
	DMA_ERROR_NONE					= 0u,
	DMA_ERROR_TRANSFER				= 1u,
	DMA_ERROR_DIRECT_MODE			= 2u,
	DMA_ERROR_FIFO					= 3u,
	DMA_ERROR_TIMEOUT				= 4u,
} DMA_ErrorType;

/**
 * Define Memory/Peripheral Burst Transfer Configuration
 */
typedef enum {
	DMA_SINGLE_TRANSFER				= 0u,
	DMA_INC_BURST_4_BEAT			= 1u,
	DMA_INC_BURST_8_BEAT			= 2u,
	DMA_INC_BURST_16_BEAT			= 3u,
} DMA_BurstTransferType;

/**
 * Define DMA Priority Level
 */
typedef enum {
	DMA_PRIO_LEVEL_LOW				= 0u,
	DMA_PRIO_LEVEL_MEDIUM			= 1u,
	DMA_PRIO_LEVEL_HIGH				= 2u,
	DMA_PRIO_LEVEL_VERYHIGH			= 3u,
} DMA_PrioLevelType;

/**
 * Define DMA Memory/Peripheral Data Size
 */
typedef enum {
	DMA_DATA_WIDTH_8_BITS			= 0u,
	DMA_DATA_WIDTH_16_BITS			= 1u,
	DMA_DATA_WIDTH_32_BITS			= 2u,
} DMA_DataWidthType;

/**
 * Define DMA Data Transfer Direction
 */
typedef enum {
	DMA_PERIPHERAL_TO_MEMORY		= 0u,
	DMA_MEMORY_TO_PERIPHERAL		= 1u,
	DMA_MEMORY_TO_MEMORY			= 2u,
} DMA_TransferDirectionType;

/**
 * Define DMA Increment Mode
 */
typedef enum {
	DMA_INCREMENT_MODE_DISABLE		= 0u,
	DMA_INCREMENT_MODE_ENABLE		= 1u,
} DMA_IncrementModeType;

/**
 * @brief Driver status type.
 * */
typedef enum
{
    DMA_STATUS_OK                   = 0x00U,  		/**< @brief Success status */
    DMA_STATUS_ERROR                = 0x01U,  		/**< @brief DMA error */
    DMA_STATUS_TIMEOUT				= 0x02U,  		/**< @brief DMA timeout */
    DMA_STATUS_INVALID_PARAM        = 0x03U,        /**< @brief Invalid parameter */
    DMA_STATUS_BUSY                 = 0x04U,        /**< @brief DMA busy */
    DMA_STATUS_NOT_INITIALIZED      = 0x05U,        /**< @brief DMA not initialized */
} DMA_StatusType;

/**
 * @brief Dma Transfer Types - Normal or Circular.
 * */
typedef enum
{
    DMA_TRANSFER_NORMAL				= 0x00U,
    DMA_TRANSFER_CIRCULAR			= 0x01U
} DMA_TransferModeType;

/**
 * @brief DMA Interrupt Flags Types
 * */
typedef enum {
	DMA_FLAG_FEIF					= 0u,	/**< FIFO Error Interrupt Flag */
	DMA_FLAG_DMEIF					= 2u,	/**< Direct Mode Error Interrupt Flag */
	DMA_FLAG_TEIF					= 3u,	/**< Transfer Error Interrupt Flag */
	DMA_FLAG_HTIF					= 4u,	/**< Half Transfer Interrupt Flag */
	DMA_FLAG_TCIF					= 5u,	/**< Transfer Complete Interrupt Flag */
} DMA_StatusFlagType;

/**
 * @brief Callback function type for async operations
 */
typedef void (*DMA_CallbackType)(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_StatusType Status);

/*****************************************************************************/
/**
 * Define DMA User Configuration Type
 */
typedef struct {
	DMA_ChannelType					DMA_Channel;
	DMA_PrioLevelType				DMA_Priority;
	DMA_TransferDirectionType		DMA_Direction;
	DMA_DataWidthType				DMA_SrcDataWidth;
	DMA_DataWidthType				DMA_DesDataWidth;
	DMA_IncrementModeType			DMA_SrcIncMode;
	DMA_IncrementModeType			DMA_DesIncMode;
	DMA_TransferModeType			DMA_TransferMode;  // Added transfer mode
	DMA_BurstTransferType			DMA_SrcBurst;      // Added burst configuration
	DMA_BurstTransferType			DMA_DesBurst;      // Added burst configuration
} DMA_UserStreamConfigType;

/**
 * Define DMA User Configuration Type
 */
typedef struct {
	DMA_StreamType					DMA_Streamx;
	DMA_UserStreamConfigType		*DMA_StreamConfig;
	DMA_CallbackType                DMA_Callback;      // Added callback for async operations
} DMA_UserConfigType;

/**
 * Define DMA Transfer Configuration Type
 */
typedef struct {
	DMA_InstanceType				DMA_Instance;      // Changed to enum type
	DMA_StreamType					DMA_Streamx;
	uint32_t						DMA_srcAddress;    // Added _t suffix for standard types
	uint32_t						DMA_desAddress;    // Added _t suffix for standard types
	uint16_t						DMA_DataSize;      // Added _t suffix for standard types
} DMA_UserTransferType;

#define DMA_INSTANCE_COUNT              2U
#define DMA_STREAM_COUNT                8U
#define DMA_TIMEOUT_DEFAULT_US          1000000U    /* 1 second default timeout */
#define DMA_INVALID_INSTANCE            0xFFU
#define DMA_INVALID_STREAM              0xFFU

#define DMA_FLAG_SHIFT_FEIF             0U
#define DMA_FLAG_SHIFT_DMEIF            2U
#define DMA_FLAG_SHIFT_TEIF             3U
#define DMA_FLAG_SHIFT_HTIF             4U
#define DMA_FLAG_SHIFT_TCIF             5U

#endif 	/* !(__DMA_TYPE_H__) */
