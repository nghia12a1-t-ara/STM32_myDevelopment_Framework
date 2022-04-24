/*
 * stm32f4xx_gpio_driver.h
 *
 *  Created on: Jan 29, 2019
 *      Author: admin
 */

#ifndef __GPIO_H_
#define __GPIO_H_

#include "GPIO_Base.h"
#include "GPIO_Types.h"

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/

/*
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_Types *pGPIOx, uint8 EnorDi);

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_Types *pGPIOx);

/*
 * Data read and write
 */
uint8 GPIO_ReadFromInputPin(GPIO_Types *pGPIOx, uint8 PinNumber);
uint16 GPIO_ReadFromInputPort(GPIO_Types *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_Types *pGPIOx, uint8 PinNumber, uint8 Value);
void GPIO_WriteToOutputPort(GPIO_Types *pGPIOx, uint16 Value);
void GPIO_ToggleOutputPin(GPIO_Types *pGPIOx, uint8 PinNumber);


#endif /* __GPIO_H_ */
