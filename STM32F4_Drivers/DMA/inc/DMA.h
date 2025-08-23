/**
 * Filename		: DMA.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: DMA Driver Header File
 */

#ifndef _DMA_H_
#define _DMA_H_

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
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_Init(DMA_InstanceType Instance, const DMA_UserConfigType * UserConfig);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_DeInit
 *
 * @brief             - Deinitialize DMA Driver
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 *
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_DeInit(DMA_InstanceType Instance);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_TransferConfig
 *
 * @brief             - Configure Source/Destination to transfer
 *
 * @param[in]         - UserTransferConfig 	- DMA Transfer Configuration
 *
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_TransferConfig(const DMA_UserTransferType * UserTransferConfig);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_SyncStartTransfer
 *
 * @brief             - Start DMA Transfer Synchronously
 *
 * @param[in]         - UserTransferConfig 	- DMA Transfer Configuration
 * @param[in]         - Timeout 			- Timeout for transfer completion
 * 
 * @return            - DMA_StatusType - DMA Transfer Status
 *
 * @Note              - 
 */
DMA_StatusType DMA_SyncStartTransfer(const DMA_UserTransferType * UserTransferConfig, uint32_t Timeout);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_AsyncStartTransfer
 *
 * @brief             - Configure Parameters and Start DMA Transfer Asynchronously (Interrupt Method)
 *
 * @param[in]         - UserTransferConfig 	- DMA Transfer Configuration
 * 
 * @return            - DMA_StatusType - DMA Transfer Status
 *
 * @Note              - 
 */
DMA_StatusType DMA_AsyncStartTransfer(const DMA_UserTransferType * UserTransferConfig);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_Stop
 *
 * @brief             - Stop DMA Transfer
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 *
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_Stop(DMA_InstanceType Instance, DMA_StreamType Stream);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_GetStatusFlag
 *
 * @brief             - Get Status Flag from interrupt status registers
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream 	- DMA Hardware Stream
 *
 * @return            - uint32_t - Status flags
 *
 * @Note              - 
 */
uint32_t DMA_GetStatusFlag(DMA_InstanceType Instance, DMA_StreamType Stream);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_CheckStatusFlag
 *
 * @brief             - Check specific Status Flag from interrupt status registers
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream 	- DMA Hardware Stream
 * @param[in]         - FlagType  - Flag type to check
 *
 * @return            - uint8_t - Flag status (0 or 1)
 *
 * @Note              - 
 */
uint8_t DMA_CheckStatusFlag(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_StatusFlagType FlagType);

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
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_ClearFlags(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_StatusFlagType FlagType);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_GetTransferCount
 *
 * @brief             - Get Remaining Transfer Count
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 *
 * @return            - uint16_t - Remaining transfer count
 *
 * @Note              - 
 */
uint16_t DMA_GetTransferCount(DMA_InstanceType Instance, DMA_StreamType Stream);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_EnableInterrupt
 *
 * @brief             - Enable DMA Stream Interrupt
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 * @param[in]         - InterruptType - Type of interrupt to enable
 *
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_EnableInterrupt(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_InterruptType InterruptType);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_DisableInterrupt
 *
 * @brief             - Disable DMA Stream Interrupt
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 * @param[in]         - InterruptType - Type of interrupt to disable
 *
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_DisableInterrupt(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_InterruptType InterruptType);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - DMA_RegisterCallback
 *
 * @brief             - Register callback function for DMA events
 *
 * @param[in]         - Instance 	- DMA Hardware Instance
 * @param[in]         - Stream    - DMA Stream
 * @param[in]         - Callback  - Callback function pointer
 *
 * @return            - DMA_StatusType - Operation status
 *
 * @Note              - 
 */
DMA_StatusType DMA_RegisterCallback(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_CallbackType Callback);

#endif	/* !(_DMA_H_) */
