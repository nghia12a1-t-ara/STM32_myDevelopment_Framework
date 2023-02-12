/**
 * Filename		: DMA.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: DMA Driver Header File
 */

#ifndef _DMA_H_
#define _DMA_H_

#include "DMA_Base.h"
#include "DMA_Type.h"

/**
 * Function Prototypes
 */
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
void DMA_Init(const uint8 Instance, const Dma_UserConfigType * UserConfig);

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
void DMA_TransferConfig(const Dma_UserTransferType * UserTransferConfig);

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
uint8 DMA_GetStatusFlag(const uint8 Instance, Dma_StreamType Stream);

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
boolean DMA_CheckStatusFlag(const uint8 Instance, Dma_StreamType Stream, DMA_StatusFlagType FlagType);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_SyncStartTransfer
 *
 * @brief             - Get Status Flag from interrupt status registers
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
Dma_StatusType DMA_SyncStartTransfer(const Dma_UserTransferType * UserTransferConfig, const uint32 Timeout);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_AsyncStartTransfer
 *
 * @brief             - Configure Param and Start Transfer (Interrupt Method)
 *
 * @param[in]         - UserTransferConfig 	- DMA Hardware Instance
 * 
 * @param[out]        - Dma_StatusType 		- Dma Transfer Status (SUCCESS or TIMEOUT)
 *
 * @return            -
 *
 * @Note              -
 */
Dma_StatusType DMA_AsyncStartTransfer(const Dma_UserTransferType * UserTransferConfig);

#endif	/* !(_DMA_H_) */
