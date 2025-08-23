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
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_Init(GPIO_InstanceType Instance, const GPIO_PinConfigType * UserConfig);

/*
 * @func	GPIO_DeInit
 * @brief	Reset GPIO configuration and disable peripheral clock
 * @param	Instance - GPIO instance number
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_DeInit(GPIO_InstanceType Instance);

/*
 * @func	GPIO_ReadFromInputPin
 * @brief	Read logic level from input pin
 * @param	Instance - GPIO instance
 * @param	PinNum - GPIO pin number
 * @param	PinValue - Pointer to store pin value
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ReadFromInputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum, GPIO_PinValue *PinValue);

/*
 * @func	GPIO_ReadFromInputPort
 * @brief	Read value from input port
 * @param	Instance - GPIO instance
 * @param	PortValue - Pointer to store port value
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ReadFromInputPort(GPIO_InstanceType Instance, uint16 *PortValue);

/*
 * @func	GPIO_WriteOutputPin
 * @brief	write logic level to output pin
 * @param	Instance - GPIO instance
 * @param	PinNum - GPIO pin number
 * @param	PinValue - logic level
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_WriteOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum, GPIO_PinValue PinValue);

/*
 * @func	GPIO_ToggleOutputPin
 * @brief	Toggle logic level of output pin
 * @param	Instance - GPIO instance
 * @param	PinNum - GPIO pin number
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ToggleOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum);

/*
 * @func	GPIO_SetOutputPort
 * @brief	Set value to output port (Set all Pins)
 * @param	Instance - GPIO instance
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_SetOutputPort(GPIO_InstanceType Instance);

/*
 * @func	GPIO_ClearOutputPort
 * @brief	Clear value to output port (Clear all Pins)
 * @param	Instance - GPIO instance
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ClearOutputPort(GPIO_InstanceType Instance);

/*
 * @func	GPIO_IsValidInstance
 * @brief	Check if GPIO instance is valid
 * @param	Instance - GPIO instance to check
 * @reval	bool - true if valid, false otherwise
 */
bool GPIO_IsValidInstance(GPIO_InstanceType Instance);

/*
 * @func	GPIO_IsValidPin
 * @brief	Check if GPIO pin number is valid
 * @param	PinNum - GPIO pin number to check
 * @reval	bool - true if valid, false otherwise
 */
bool GPIO_IsValidPin(GPIO_PinNumberType PinNum);

#endif /* __GPIO_H__ */
