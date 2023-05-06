/**
 * Filename     : SPI.h
 * Author       : Nghia Taarabt
 * Create Date  : 18/12/22
 * Brief        : SPI Function Prototypes
 */

#ifndef __SPI_H__
#define __SPI_H__

#include "SPI_Base.h"
#include "SPI_Type.h"

/******************************************************************************************
 *                          APIs supported by this driver
 *      For more information about the APIs check the function definitions
 ******************************************************************************************/
 
/*****************************************************************************************/
/*********************************************************************
 * @fn                - SPI_Init
 *
 * @brief             - Initialize SPI Driver
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - UserConfig  - SPI User Configuration
 *
 * @return            -
 *
 * @Note              -
 */
void SPI_Init(const uint8 Instance, const Spi_UserConfigType * UserConfig);

/*********************************************************************
 * @fn                - Spi_SyncSendData
 *
 * @brief             - Synchronous Send Data - Wait to send done or timeout
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - TxBuff      - uffer to transmission
 * @param[in]         - TxSize      - Size of Buffer to transmission
 * @param[in]         - Timeout     - Timeout if data cannot transmit
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_SyncSendData(const uint8 Instance,
                                const uint8 *TxBuff,
                                const uint32 TxSize,
                                const uint32 Timeout);

/*********************************************************************
 * @fn      		  - Spi_AsyncSendData
 *
 * @brief             - Asynchronous Send Data - Send Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- SPI Hardware Instance
 * @param[in]         - TxBuff 		- Buffer to transmission
 * @param[in]         - TxSize 		- Size of Buffer to transmission
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_AsyncSendData(const uint8 Instance,
								 const uint8 *TxBuff,
								 const uint32 TxSize);

/*********************************************************************
 * @fn                - Spi_SyncReceiveData
 *
 * @brief             - Synchronous Receive Data - Wait to receive done or timeout
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - RxBuff      - Buffer to Receive
 * @param[in]         - RxSize      - Size of Buffer to Receive
 * @param[in]         - Timeout     - Timeout if data cannot Receive (us)
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_SyncReceiveData(const uint8 Instance,
                                         uint8 *RxBuff,
                                   const uint32 RxSize,
                                   const uint32 Timeout);

/*********************************************************************
 * @fn      		  - Spi_AsyncReceiveData
 *
 * @brief             - Asynchronous Receive Data - Receive Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- SPI Hardware Instance
 * @param[in]         - RxBuff 		- Buffer to Receive
 * @param[in]         - RxSize 		- Size of Buffer to Receive
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_AsyncReceiveData(const uint8 Instance,
                                    uint8 * RxBuff,
                                    const uint32 RxSize);

/*********************************************************************
 * @fn                - SPI_GetStatus
 *
 * @brief             - Get Status Flag
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - StatusFlag  - Status Flag
 *
 * @return            - TRUE or FALSE
 *
 * @Note              -
 */
Bool_Type SPI_GetStatus(const uint8 Instance, Spi_StatusFlagType StatusFlag);

#endif /* __SPI_H__ */
