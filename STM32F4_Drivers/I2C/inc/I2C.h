/*
 * stm32f4xx_i2c_driver.h
 *
 *  Created on: Feb 20, 2019
 *      Author: admin
 */

#ifndef __I2C_H_
#define __I2C_H_

#include "I2C_Base.h"
#include "I2C_Types.h"

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*
 * Peripheral Clock setup
 */
void I2C_PeriClockControl(I2C_Types *pI2Cx, uint8 EnorDi);

/*
 * Init and De-init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_Types *pI2Cx);


/*
 * Data Send and Receive
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8 *pTxbuffer, uint32 Len, uint8 SlaveAddr,uint8 Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8 *pRxBuffer, uint8 Len, uint8 SlaveAddr,uint8 Sr);
uint8 I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle,uint8 *pTxbuffer, uint32 Len, uint8 SlaveAddr,uint8 Sr);
uint8 I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle,uint8 *pRxBuffer, uint8 Len, uint8 SlaveAddr,uint8 Sr);

void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle);
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle);


void I2C_SlaveSendData(I2C_Types *pI2C,uint8 data);
uint8 I2C_SlaveReceiveData(I2C_Types *pI2C);

/*
 * IRQ Configuration and ISR handling
 */
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

/*
 * Other Peripheral Control APIs
 */
void I2C_PeripheralControl(I2C_Types *pI2Cx, uint8 EnOrDi);
uint8 I2C_GetFlagStatus(I2C_Types *pI2Cx , uint32 FlagName);
void I2C_ManageAcking(I2C_Types *pI2Cx, uint8 EnorDi);
void I2C_GenerateStopCondition(I2C_Types *pI2Cx);

void I2C_SlaveEnableDisableCallbackEvents(I2C_Types *pI2Cx,uint8 EnorDi);

/*
 * Application callback
 */
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8 AppEv);

#endif
