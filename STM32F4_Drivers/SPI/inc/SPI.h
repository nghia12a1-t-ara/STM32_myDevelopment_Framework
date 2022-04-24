/*
 * stm32f4xx_spi_driver.h
 *
 *  Created on: Feb 9, 2019
 *      Author: admin
 */

#ifndef __SPI_H_
#define __SPI_H_

#include "SPI_Base.h"
#include "SPI_Types.h"

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*
 * Peripheral Clock setup
 */
void SPI_PeriClockControl(SPI_Types *pSPIx, uint8 EnorDi);

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Types *pSPIx);


/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_Types *pSPIx,uint8 *pTxBuffer, uint32 Len);
void SPI_ReceiveData(SPI_Types *pSPIx, uint8 *pRxBuffer, uint32 Len);

uint8 SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8 *pTxBuffer, uint32 Len);
uint8 SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8 *pRxBuffer, uint32 Len);

/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQHandling(SPI_Handle_t *pHandle);

/*
 * Other Peripheral Control APIs
 */
void SPI_PeripheralControl(SPI_Types *pSPIx, uint8 EnOrDi);
void SPI_SSIConfig(SPI_Types *pSPIx, uint8 EnOrDi);
void SPI_SSOEConfig(SPI_Types *pSPIx, uint8 EnOrDi);
uint8 SPI_GetFlagStatus(SPI_Types *pSPIx , uint32 FlagName);
void SPI_ClearOVRFlag(SPI_Types *pSPIx);
void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);
uint8 I2C_DeviceMode(I2C_Types *I2Cx);

/*
 * Application callback
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8 AppEv);

#endif /* __SPI_H_ */
