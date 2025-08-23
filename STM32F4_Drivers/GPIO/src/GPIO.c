/**
 * Filename		: GPIO.c
 * Author		: Nghia Taarabt
 * Create Date 	: 01/01/23
 * Brief		: GPIO driver function
 */

#include "GPIO.h"
#include "GPIO_HwAccess.h"

/*****************************************************************************************/
/************************************ Private Variables **********************************/
/** @brief User pin config structure. */
/* const GPIO_PinConfigType * Gpio_PinConfig_Pointer[GPIO_INSTANCE_COUNT]; */

static GPIO_Type * const Gpio_Base_Pointer[GPIO_INSTANCE_COUNT] = GPIO_BASE_PTRS;

/*****************************************************************************************/
/************************************ Private Functions **********************************/

/*
 * @func	GPIO_IsValidInstance
 * @brief	Check if GPIO instance is valid
 * @param	Instance - GPIO instance to check
 * @reval	bool - true if valid, false otherwise
 */
bool GPIO_IsValidInstance(GPIO_InstanceType Instance)
{
	return (Instance < GPIO_INSTANCE_COUNT);
}

/*
 * @func	GPIO_IsValidPin
 * @brief	Check if GPIO pin number is valid
 * @param	PinNum - GPIO pin number to check
 * @reval	bool - true if valid, false otherwise
 */
bool GPIO_IsValidPin(GPIO_PinNumberType PinNum)
{
	return (PinNum <= GPIO_MAX_PIN_NUMBER);
}

/**************************************************************************************
 * 						APIs supported by the driver
 * 		For more information about the APIs check the function definitions
 **************************************************************************************/
/*
 * @func	GPIO_Init
 * @brief	Configure Mode for GPIO
 * @param	Instance - number of GPIO instance
 * @param	UserConfig - Struct contains Mode for GPIO
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_Init(GPIO_InstanceType Instance, const GPIO_PinConfigType * UserConfig)
{
	if (UserConfig == NULL)
	{
		return GPIO_ERROR_NULL_POINTER;
	}
	
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	if (!GPIO_IsValidPin(UserConfig->GPIO_PinNumber))
	{
		return GPIO_ERROR_INVALID_PIN;
	}
	
	GPIO_Type 			*Base 		= Gpio_Base_Pointer[Instance];
	GPIO_PinNumberType 	PinNum 		= UserConfig->GPIO_PinNumber;
	GPIO_ModeType 		PinMode		= UserConfig->GPIO_PinMode;
	GPIO_OutSpeedType	PinSpeed 	= UserConfig->GPIO_PinSpeed;
	GPIO_InputType		PinPull		= UserConfig->GPIO_PinInputMode;
	GPIO_OutputType 	PinOutMode	= UserConfig->GPIO_PinOutputMode;
	GPIO_AlternateType 	PinAFMode	= UserConfig->GPIO_PinAlternate;
	EXTI_ModeType		ExtiMode	= UserConfig->EXTI_Mode;
	
    /* Enable Clock for GPIO Instance */
    GPIO_PeriClockControl(Base, ENABLE);
    
	if ( GPIO_MODE_EXTI == PinMode )
	{
		if (ExtiMode == EXTI_DISABLE)
		{
			return GPIO_ERROR_EXTI_CONFIG;
		}
		
		/* Configure External Interrupt */
		EXTI_SetMode(PinNum, ExtiMode);
		
		/* Select the source input for the EXTIx external interrupt */
		EXTI_SetSrcInput(Instance, PinNum);

		/* Enable the Exti Interrupt delivery using IMR */
		EXTI_SetControl(PinNum, ENABLE);
	}
	else
	{
		/* Configure the mode of GPIO pin */
		GPIO_SetPinMode(Base, PinNum, PinMode);
	}

	/* Configure the pull-up/pull-down settings */
	GPIO_SetInputMode(Base, PinNum, PinPull);
	
	/* Configure the output speed */
	GPIO_SetOutSpeed(Base, PinNum, PinSpeed);
	
	/* Configure the output type (optype) */
	GPIO_SetOutputMode(Base, PinNum, PinOutMode);	

	if (PinMode == GPIO_MODE_ANALOG)
	{
		/* Pull Disable with Analog Mode */
		GPIO_SetInputMode(Base, PinNum, GPIO_INPUT_FLOATING);
	}
	
	if (PinMode == GPIO_MODE_ALTERNATE)
	{
		/* Configure the Alternate Function Register */
		GPIO_SetAlternateMode(Base, PinNum, PinAFMode);
	}
	
	return GPIO_OK;
}


/*
 * @func	GPIO_DeInit
 * @brief	Reset GPIO configuration and disable peripheral clock
 * @param	Instance - GPIO instance number
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_DeInit(GPIO_InstanceType Instance)
{
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];
    
    GPIO_ResetPort(Base);
    
    /* Disable Clock for GPIO Instance */
	GPIO_PeriClockControl(Base, DISABLE);
	
	return GPIO_OK;
}

/*
 * @func	GPIO_ReadFromInputPin
 * @brief	Read logic level from input pin
 * @param	Instance - GPIO instance
 * @param	PinNum - GPIO pin number
 * @param	PinValue - Pointer to store pin value
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ReadFromInputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum, GPIO_PinValue *PinValue)
{
	if (PinValue == NULL)
	{
		return GPIO_ERROR_NULL_POINTER;
	}
	
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	if (!GPIO_IsValidPin(PinNum))
	{
		return GPIO_ERROR_INVALID_PIN;
	}
	
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];
	
	/* Read logic level from pin */
	*PinValue = GPIO_ReadPin(Base, PinNum);
	
	return GPIO_OK;
}

/*
 * @func	GPIO_ReadFromInputPort
 * @brief	Read value from input port
 * @param	Instance - GPIO instance
 * @param	PortValue - Pointer to store port value
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ReadFromInputPort(GPIO_InstanceType Instance, uint16 *PortValue)
{
	if (PortValue == NULL)
	{
		return GPIO_ERROR_NULL_POINTER;
	}
	
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];

	/* Read port value */
	*PortValue = GPIO_ReadPort(Base);
	
	return GPIO_OK;
}

/*
 * @func	GPIO_WriteOutputPin
 * @brief	write logic level to output pin
 * @param	Instance - GPIO instance
 * @param	PinNum - GPIO pin number
 * @param	PinValue - logic level
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_WriteOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum, GPIO_PinValue PinValue)
{
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	if (!GPIO_IsValidPin(PinNum))
	{
		return GPIO_ERROR_INVALID_PIN;
	}
	
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];
	
	/* Write logic level to a Pin */
	GPIO_WritePin(Base, PinNum, PinValue);
	
	return GPIO_OK;
}

/*
 * @func	GPIO_ToggleOutputPin
 * @brief	Toggle logic level of output pin
 * @param	Instance - GPIO instance
 * @param	PinNum - GPIO pin number
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ToggleOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum)
{
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	if (!GPIO_IsValidPin(PinNum))
	{
		return GPIO_ERROR_INVALID_PIN;
	}
	
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];
	
	if ( GPIO_PIN_RESET == GPIO_ReadPin(Base, PinNum) )
	{
		GPIO_WritePin(Base, PinNum, GPIO_PIN_SET);
	}
	else	/* current status = GPIO_PIN_SET */
	{
		GPIO_WritePin(Base, PinNum, GPIO_PIN_RESET);
	}
	
	return GPIO_OK;
}

/*
 * @func	GPIO_SetOutputPort
 * @brief	Set value to output port (Set all Pins)
 * @param	Instance - GPIO instance
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_SetOutputPort(GPIO_InstanceType Instance)
{
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];
	
	/* Set all pin in port to 1 logic */
	GPIO_SetPort(Base);
	
	return GPIO_OK;
}

/*
 * @func	GPIO_ClearOutputPort
 * @brief	Clear value to output port (Clear all Pins)
 * @param	Instance - GPIO instance
 * @reval	GPIO_ErrorType - Error status
 */
GPIO_ErrorType GPIO_ClearOutputPort(GPIO_InstanceType Instance)
{
	if (!GPIO_IsValidInstance(Instance))
	{
		return GPIO_ERROR_INVALID_INSTANCE;
	}
	
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];
	
	/* Clear all pin in port to 0 logic */
	GPIO_ClearPort(Base);
	
	return GPIO_OK;
}
