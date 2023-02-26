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

#endif /* __SPI_H__ */
