/**
 * Filename		: GPIO.h
 * Author		: Nghia Taarabt
 * Create Date 	: 01/01/23
 * Brief		: GPIO driver header file
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "GPIO_Base.h"
#include "GPIO_Type.h"

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/

/*
 * @func	GPIO_Init
 * @brief	Configure Mode for GPIO
 * @param	Instance - number of GPIO instance
 * @param	UserConfig - Struct contains Mode for GPIO
 * @reval	none
 */
void GPIO_Init(GPIO_InstanceType Instance, const GPIO_PinConfigType * UserConfig);

/*
 * @func	GPIO_DeInit
 * @brief	Disable Peripheral GPIO Clock
 * @param	GPIOx
 * @reval	none
 */
void GPIO_DeInit(GPIO_InstanceType Instance);

/*
 * @func	GPIO_ReadFromInputPin
 * @brief	Read logic level from input pin
 * @param	GPIO Instance
 * 			GPIO pin number
 * @reval	logic level of gpio pin
 */
GPIO_PinValue GPIO_ReadFromInputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum);

/*
 * @func	GPIO_ReadFromInputPort
 * @brief	Read value from input port
 * @param	GPIO Instance
 * @reval	value of gpio port
 */
uint16 GPIO_ReadFromInputPort(GPIO_InstanceType Instance);

/*
 * @func	GPIO_WriteOutputPin
 * @brief	write logic level to output pin
 * @param	GPIOx - GPIO Instance
 * 			PinNumber - GPIO pin number
 * 			Value - logic level
 * @reval	none
 */
void GPIO_WriteOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum, GPIO_PinValue PinValue);

/*
 * @func	GPIO_ToggleOutputPin
 * @brief	Toggle logic level of output pin
 * @param	GPIOx - GPIO Instance
 * 			Value - logic level
 * @reval	none
 */
void GPIO_ToggleOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum);

/*
 * @func	GPIO_SetOutputPort
 * @brief	Set value to output port (Set all Pins)
 * @param	GPIOx - GPIO Instance
 * 			Value - logic level
 * @reval	none
 */
void GPIO_SetOutputPort(GPIO_InstanceType Instance);

/*
 * @func	GPIO_ClearOutputPort
 * @brief	Clear value to output port (Clear all Pins)
 * @param	GPIOx - GPIO Instance
 * 			Value - logic level
 * @reval	none
 */
void GPIO_ClearOutputPort(GPIO_InstanceType Instance);

#endif /* __GPIO_H__ */
