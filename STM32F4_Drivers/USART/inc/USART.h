/*
 * STM32F4x_gpio_driver.h
 *
 *  Created on: 27-Nov-2018
 *      Author: kiran
 */

#ifndef __USART_H_
#define __USART_H_

#include "USART_Base.h"
#include "USART_Types.h"


/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_Types *pUSARTx, uint8 EnOrDi);

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_Handle_t *pUSARTHandle);

/*
 * Data Send and Receive
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8 *pTxBuffer, uint32 Len);
void  USART_ReceiveData(USART_Handle_t *pUSARTHandle,uint8 *pRxBuffer, uint32 Len);
uint8 USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8 *pTxBuffer, uint32 Len);
uint8 USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle,uint8 *pRxBuffer, uint32 Len);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQHandling(USART_Handle_t *pUSARTHandle);

/*
 * Other Peripheral Control APIs
 */

uint8 USART_GetFlagStatus(USART_Types *pUSARTx, uint8 StatusFlagName);
void USART_ClearFlag(USART_Types *pUSARTx, uint16 StatusFlagName);
void USART_PeripheralControl(USART_Types *pUSARTx, uint8 EnOrDi);
void USART_SetBaudRate(USART_Types *pUSARTx, uint32 BaudRate);


/*
 * Application Callbacks
 */
void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8 ApEv);


#endif /* __USART_H_ */



