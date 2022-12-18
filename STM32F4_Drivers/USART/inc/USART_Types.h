#ifndef __USART_Type_H_
#define __USART_Type_H_

/*
 * USART flags
 */

#define USART_FLAG_TXE 						( 1 << USART_SR_TXE )
#define USART_FLAG_RXNE 					( 1 << USART_SR_RXNE )
#define USART_FLAG_TC 						( 1 << USART_SR_TC )

#define USART_9BITS_DATA_MASK				(uint16)0x01FFu
#define USART_8BITS_DATA_MASK				(uint8)0xFFu
#define USART_7BITS_DATA_MASK				(uint8)0x7Fu

/*
 * Application states
 */
#define USART_READY 	 					0U
#define USART_BUSY_IN_RX 					1U
#define USART_BUSY_IN_TX 					2U

#define	USART_ERR_FE     					5U
#define	USART_ERR_NE    					6U
#define	USART_ERR_ORE    					7U

/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
typedef enum
{
	USART_MODE_ONLY_TX 		= 0u,
	USART_MODE_ONLY_RX		= 1u,
	USART_MODE_TXRX			= 2u
} Usart_TransferModeType;

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
typedef enum
{ 
	USART_WORDLEN_8BITS 	= 0u,
	USART_WORDLEN_9BITS		= 1u
} Usart_WordLenType;

/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
typedef enum
{ 
	USART_STD_BAUD_1200		= 1200,
	USART_STD_BAUD_2400		= 2400,
	USART_STD_BAUD_9600		= 9600,
	USART_STD_BAUD_19200 	= 19200,
	USART_STD_BAUD_38400 	= 38400,
	USART_STD_BAUD_57600 	= 57600,
	USART_STD_BAUD_115200 	= 115200,
	USART_STD_BAUD_230400 	= 230400,
	USART_STD_BAUD_460800 	= 460800,
	USART_STD_BAUD_921600 	= 921600,
	USART_STD_BAUD_2M 		= 2000000,
	USART_STD_BAUD_3M 		= 3000000
} Usart_BaudrateType;

/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
typedef enum
{
	USART_PARITY_DISABLE 	= 0u,
	USART_PARITY_EN_EVEN	= 1u,
	USART_PARITY_EN_ODD		= 2u
} Usart_ParityType;

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
typedef enum
{
	USART_STOPBITS_1 		= 0u,
	USART_STOPBITS_0_5		= 1u,
	USART_STOPBITS_2		= 2u,
	USART_STOPBITS_1_5		= 3u
} Usart_StopBitsType;

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
typedef enum
{
	USART_HW_FLOW_CTRL_NONE 	= 0u,
	USART_HW_FLOW_CTRL_CTS  	= 1u,
	USART_HW_FLOW_CTRL_RTS		= 2u,
	USART_HW_FLOW_CTRL_CTS_RTS	= 3u
} Usart_HardwareFlowType;

/**
 * @brief Type of Event when Transfer
 */
typedef enum
{
	USART_EVENT_TX_CMPLT   	= 0U,
	USART_EVENT_RX_CMPLT   	= 1U,
	USART_EVENT_IDLE      	= 2U,
	USART_EVENT_CTS       	= 3U,
	USART_EVENT_PE        	= 4U
} Usart_EventType;

/**
 * @brief Type of UART transfer (based on interrupts or DMA).
 */
typedef enum
{
    USART_USING_DMA         = 0U,    /**< @brief The driver will use DMA to perform UART transfer */
    USART_USING_INTERRUPTS  = 1U     /**< @brief The driver will use interrupts to perform UART transfer */
} Usart_TransferType;

/**
 * Driver status type.
 * */
typedef enum
{
    USART_STATUS_SUCCESS                    = 0x00U,  		/**< @brief Success status */
    USART_STATUS_ERROR                      = 0x01U,  		/**< @brief Failure status */
    USART_STATUS_BUSY                       = 0x02U,  		/**< @brief Busy status */
    USART_STATUS_TIMEOUT                    = 0x03U,  		/**< @brief Timeout status */
    USART_STATUS_TX_UNDERRUN                = 0x04U,  		/**< @brief TX underrun error */
    USART_STATUS_RX_OVERRUN                 = 0x05U,  		/**< @brief RX overrun error */
    USART_STATUS_DMA_ERROR                  = 0x06U  		/**< @brief DMA error */
} Usart_StatusType;

/**
 * @brief Callback for all peripherals which support UART features
 *
 *
 */
typedef void (*Usart_CallbackType)(const uint8 HwInstance,
                                            const Usart_EventType Event,
                                            void *UserData);

/****************************************************************************************/
/******************************* Data Structure USART ***********************************/

/*
 * Usart_StateRuntimeType - Runtime States of USART Driver
 */
typedef struct
{
	Usart_BaudrateType				USART_Baud;						/*!< @brief Baudrate */
    const uint8 					* TxBuff;						/**< @brief The buffer of Sent Data */
    uint8 							* RxBuff;						/**< @brief The buffer of Received Data.*/
    volatile uint32 				TxSize;							/**< @brief The remaining number of bytes to be transmitted. */
    volatile uint32 				RxSize;							/**< @brief The remaining number of bytes to be received. */
    volatile boolean 				IsTxBusy;                       /**< @brief True if there is an active transmit.*/
    volatile boolean 				IsRxBusy;                       /**< @brief True if there is an active receive.*/
    volatile Usart_StatusType 		TransmitStatus;     			/**< @brief Status of last driver transmit operation */
    volatile Usart_StatusType 		ReceiveStatus;      			/**< @brief Status of last driver receive operation */
} Usart_StateRuntimeType;

/*
 * Usart_UserConfigType - Used when Initialize USART Peripheral
 */
typedef struct
{
	Usart_TransferModeType			USART_Mode;						/*!< @brief Transfer Mode (TX or RX or both) */
	Usart_BaudrateType				USART_Baud;						/*!< @brief Baudrate */
	Usart_StopBitsType				USART_NoOfStopBits;				/*!< @brief Number of Stop Bits (1, 1.5, 2) */
	Usart_WordLenType 				USART_WordLength;				/*!< @brief Length of Transfer Words (7, 8, 9) */
	Usart_ParityType				USART_ParityControl;			/*!< @brief Types of Parity (Even, Odd, None) */
	Usart_HardwareFlowType			USART_HWFlowControl;			/*!< @brief Hardware Flow Control */
	
    Usart_TransferType 				USART_Transfer;            	/*!< @brief of USART transfer (interrupt/dma based) */
    Usart_CallbackType			 	Callback;             			/**< @brief Callback to invoke for handle uart event */
    void 							* CallbackParam;					/**< @brief User callback parameter pointer.*/
#if (USART_DMA_ENABLE == STD_ON)
    uint32 							RxDMAChannel;					/**< @brief DMA channel number for DMA-based rx. */
    uint32 							TxDMAChannel;					/**< @brief DMA channel number for DMA-based tx. */
#endif
    Usart_StateRuntimeType 			* StateStruct;
} Usart_UserConfigType;

#endif 	/* !(__USART_Type_H_) */
