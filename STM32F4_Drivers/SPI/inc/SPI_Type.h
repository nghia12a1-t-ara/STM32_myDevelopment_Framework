/**
 * Filename     : SPI_Type.h
 * Author       : Nghia Taarabt
 * Create Date  : 18/12/22
 * Brief        : SPI definitions and types
 */

#ifndef __SPI_TYPE_H__
#define __SPI_TYPE_H__

/*
 * SPI application states
 */
#define SPI_READY                       0
#define SPI_BUSY_IN_RX                  1
#define SPI_BUSY_IN_TX                  2

/**
 * @brief SPI Device Mode (Master or Slave)
 */
typedef enum {
    SPI_DEVICE_MODE_SLAVE           = 0x0u,
    SPI_DEVICE_MODE_MASTER          = 0x1u,
} Spi_DeviceModeType;

/*
 * @brief SPI_BusConfig
 */
typedef enum {
    SPI_BUS_CONFIG_FULL_DUPLEX      = 0x1u,
    SPI_BUS_CONFIG_HALF_DUPLEX      = 0x2u,
    SPI_BUS_CONFIG_SIMPLEX_RXONLY   = 0x3u,
} SPI_BusConfigType;

/**
 * @brief Clock Speed Divide
 */
typedef enum {
    SPI_SCLK_SPEED_DIV2             = 0x0u,
    SPI_SCLK_SPEED_DIV4             = 0x1u,
    SPI_SCLK_SPEED_DIV8             = 0x2u,
    SPI_SCLK_SPEED_DIV16            = 0x3u,
    SPI_SCLK_SPEED_DIV32            = 0x4u,
    SPI_SCLK_SPEED_DIV64            = 0x5u,
    SPI_SCLK_SPEED_DIV128           = 0x6u,
    SPI_SCLK_SPEED_DIV256           = 0x7u,
} Spi_ClockSpeedDivType;

/**
 * @brief Data Frame Setup
 */
typedef enum {
    SPI_DATA_FRAME_8BITS            = 0x0u,
    SPI_DATA_FRAME_16BITS           = 0x1u,
} Spi_DataFrameType;

/**
 * @brief Clock Polarity
 */
typedef enum {
    SPI_CPOL_LOW                    = 0x0u,
    SPI_CPOL_HIGH                   = 0x1u,
} Spi_ClockPolarityType;

/**
 * @brief Clock Phase
 */
typedef enum {
    SPI_CPHA_LOW                    = 0x0u,
    SPI_CPHA_HIGH                   = 0x1u,
} Spi_ClockPhaseType;

/**
 * @brief Clock Mode (4) - Setup Clock Polarity and Clock Phase
 */
typedef enum {
    SPI_CLOCK_MODE_0                = 0x0u,         /* CPOL = 0, CPHA = 0 */
    SPI_CLOCK_MODE_1                = 0x1u,         /* CPOL = 0, CPHA = 1 */
    SPI_CLOCK_MODE_2                = 0x2u,         /* CPOL = 1, CPHA = 0 */
    SPI_CLOCK_MODE_3                = 0x3u,         /* CPOL = 1, CPHA = 1 */
} Spi_ClockModeType;

/**
 * @brief Software Slave Management
 */
typedef enum {
    SPI_SSM_DISABLE                 = 0x0u,
    SPI_SSM_ENABLE                  = 0x1u,
} Spi_SSMEnaleType;

/**
 * @brief First Bit of Frame MSB or LSB
 */
typedef enum {
    SPI_FIRSTBIT_MSB                = 0x0u,
    SPI_FIRSTBIT_LSB                = 0x1u,
} Spi_FirstBitType;

/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG                    ( 1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG                   ( 1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG                   ( 1 << SPI_SR_BSY)

/**
 * @brief Type of Event when Transfer
 */
typedef enum
{
    SPI_EVENT_TX_CMPLT              = 0x01U,        /**< @brief Tx Transfer is completed */
    SPI_EVENT_RX_CMPLT              = 0x02U,        /**< @brief Rx Transfer is completed */
    SPI_EVENT_OVR_ERR               = 0x03U,        /**< @brief SPI Overrun Error */
    SPI_EVENT_CRC_ERR               = 0x04U,        /**< @brief SPI CRC Calculate Error */
} Spi_EventType;

/**
 * @brief Type of SPI transfer (based on interrupts or DMA).
 */
typedef enum
{
    SPI_USING_DMA                   = 0U,           /**< @brief The driver will use DMA to perform SPI transfer */
    SPI_USING_INTERRUPTS            = 1U,           /**< @brief The driver will use interrupts to perform SPI transfer */
} Spi_TransferType;

/**
 * @brief Driver status type.
 * */
typedef enum
{
    SPI_STATUS_SUCCESS              = 0x00U,        /**< @brief Success status */
    SPI_STATUS_ERROR                = 0x01U,        /**< @brief Failure status */
    SPI_STATUS_BUSY                 = 0x02U,        /**< @brief Busy status */
    SPI_STATUS_TIMEOUT              = 0x03U,        /**< @brief Timeout status */
    SPI_STATUS_TX_UNDERRUN          = 0x04U,        /**< @brief TX underrun error */
    SPI_STATUS_RX_OVERRUN           = 0x05U,        /**< @brief RX overrun error */
    SPI_STATUS_DMA_ERROR            = 0x10U,        /**< @brief DMA error */
} Spi_StatusType;

/**
 * @brief Callback for all peripherals which support SPI features
 */
typedef void (*Spi_CallbackType)(const uint8 HwInstance,
                                 const Spi_EventType Event,
                                 void *UserData);
                                            
/****************************************************************************************/
/******************************* Data Structure SPI ***********************************/

/**
 * @Spi_StateRuntimeType - Runtime States of SPI Driver
 */
typedef struct
{
    const uint8                     * pTxBuffer;                    /**< @brief The buffer of Sent Data */
    uint8                           * pRxBuffer;                    /**< @brief The buffer of Received Data */
    volatile uint32                 TxSize;                         /**< @brief The remaining number of bytes to be transmitted. */
    volatile uint32                 RxSize;                         /**< @brief The remaining number of bytes to be received. */
    volatile boolean                IsTxBusy;                       /**< @brief True if there is an active transmit.*/
    volatile boolean                IsRxBusy;                       /**< @brief True if there is an active receive.*/
    volatile Spi_StatusType         TransmitStatus;                 /**< @brief Status of last driver transmit operation */
    volatile Spi_StatusType         ReceiveStatus;                  /**< @brief Status of last driver receive operation */
} Spi_StateRuntimeType;

/**
 * @Spi_UserConfigType - Used when Initialize SPI Peripheral
 */
typedef struct
{
    Spi_DeviceModeType              SPI_DeviceMode;                 /*!< @brief SPI Device Mode (Master or Slave) */
    Spi_ClockSpeedDivType           SPI_ClockSpeed;                 /*!< @brief Clock Speed Divivde */
    SPI_BusConfigType               SPI_BusConfig;                  /*!< @brief SPI Bus Configure Transfer */
    Spi_DataFrameType               SPI_DataFrame;                  /*!< @brief SPI Data Frame (8 or 16 bits) */
    Spi_ClockModeType               SPI_ClockMode;                  /*!< @brief SPI Clock Polarity & SPI Clock Phase */
    Spi_FirstBitType                SPI_FirstBit;                   /*!< @brief SPI First Bit Configure MSB or LSB */
    Spi_SSMEnaleType                SPI_SSM;                        /*!< @brief SPI Software Slave Management */
    
    Spi_TransferType                SPI_Transfer;                   /*!< @brief of USART transfer (interrupt/dma based) */
    Spi_CallbackType                Callback;                       /**< @brief Callback to invoke for handle spi event */
    void                            * CallbackParam;                /**< @brief User callback parameter pointer.*/
#if (USART_DMA_ENABLE == STD_ON)
    uint32                          RxDMAChannel;                   /**< @brief DMA channel number for DMA-based rx. */
    uint32                          TxDMAChannel;                   /**< @brief DMA channel number for DMA-based tx. */
#endif
    Spi_StateRuntimeType            * StateStruct;
} Spi_UserConfigType;

#endif  /* !(__SPI_TYPE_H__) */
