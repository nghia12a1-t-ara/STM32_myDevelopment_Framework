/**
 * Filename		: USART.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: USART Function Prototypes
 */

#ifndef __USART_H_
#define __USART_H_

#include "USART_Base.h"
#include "USART_Type.h"

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*********************************************************************
 * @fn      		  - USART_Init
 *
 * @brief             - Initialize USART Driver
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - UserConfig 	- USART User Configuration
 *
 * @return            -
 *
 * @Note              -
 */
void USART_Init(const uint8 Instance, const Usart_UserConfigType * UserConfig);

/*********************************************************************
 * @fn      		  - Usart_SyncSendData
 *
 * @brief             - Synchronus Send Data - Wait to send ok or timeout
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - TxBuff 		- Buffer to transmission
 * @param[in]         - TxSize 		- Size of Buffer to transmission
 * @param[in]         - Timeout 	- Timeout if data cannot transmit
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_SyncSendData(const uint8 Instance,
									const uint8 *TxBuff,
									const uint32 TxSize,
									const uint32 Timeout);

/*********************************************************************
 * @fn      		  - Usart_AsyncSendData
 *
 * @brief             - Asynchronus Send Data - Send Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - TxBuff 		- Buffer to transmission
 * @param[in]         - TxSize 		- Size of Buffer to transmission
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_AsyncSendData(const uint8 Instance,
									const uint8 *TxBuff,
									const uint32 TxSize);
									
/*********************************************************************
 * @fn      		  - Usart_SyncReceiveData
 *
 * @brief             - Synchronus Receive Data - Wait to Receive ok or timeout
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - RxBuff 		- Buffer to Receive
 * @param[in]         - RxSize 		- Size of Buffer to Receive
 * @param[in]         - Timeout 	- Timeout if data cannot Receive
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_SyncReceiveData(const uint8 Instance,
                                       uint8 *RxBuff,
                                       const uint32 RxSize,
                                       const uint32 Timeout);
									   
/*********************************************************************
 * @fn      		  - Usart_AsyncReceiveData
 *
 * @brief             - Asynchronus Receive Data - Receive Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - RxBuff 		- Buffer to Receive
 * @param[in]         - RxSize 		- Size of Buffer to Receive
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_AsyncReceiveData(const uint8 Instance,
                                        uint8 * RxBuff,
                                        const uint32 RxSize);

/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *
 * @brief             - Setting Baudrate for USART Driver
 *
 * @param[in]         - Instance - number of Hardware Instance
 * @param[in]         - BaudRate
 *
 * @return            -
 *
 * @Note              -
 */
void Usart_SetBaudRate(const uint8 Instance, Usart_BaudrateType BaudRate);

/*******************************************************************************
 *
 * Function Name : Usart_IrqHandler
 * Description   : Interrupt handler for USART.
 * This handler uses the buffers stored in the Usart_StateStructureType structs to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *****************************************************************************/
void Usart_IrqHandler(const uint8 Instance);


#endif /* __USART_H_ */



