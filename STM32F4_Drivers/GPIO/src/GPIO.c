/**
 * Filename		: GPIO.c
 * Author		: Nghia Taarabt
 * Create Date 	: 01/01/23
 * Brief		: GPIO driver function
 */

#include "GPIO.h"

/*****************************************************************************************/
/************************************ Private Variables **********************************/
/** @brief User pin config structure. */
/* const GPIO_PinConfigType * Gpio_PinConfig_Pointer[GPIO_INSTANCE_COUNT]; */

static GPIO_Type * const Gpio_Base_Pointer[GPIO_INSTANCE_COUNT] = GPIO_BASE_PTRS;

/*****************************************************************************************/
/************************************ Private Functions **********************************/

/**************************************************************************************
 * 						APIs supported by the driver
 * 		For more information about the APIs check the function definitions
 **************************************************************************************/
/*
 * @func	GPIO_Init
 * @brief	Configure Mode for GPIO
 * @param	Instance - number of GPIO instance
 * @param	UserConfig - Struct contains Mode for GPIO
 * @reval	none
 */
void GPIO_Init(GPIO_InstanceType Instance, const GPIO_PinConfigType * UserConfig)
{
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
}


/*
 * @func	GPIO_DeInit
 * @brief	Disable Peripheral GPIO Clock
 * @param	GPIOx
 * @reval	none
 */
void GPIO_DeInit(GPIO_InstanceType Instance)
{
	GPIO_Type *Base = Gpio_Base_Pointer[Instance];
    
    /* Disable Clock for GPIO Instance */
	GPIO_PeriClockControl(Base, DISABLE);
}

/*
 * @func	GPIO_ReadFromInputPin
 * @brief	Read logic level from input pin
 * @param	GPIO Instance
 * 			GPIO pin number
 * @reval	logic level of gpio pin
 */
GPIO_PinValue GPIO_ReadFromInputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum)
{
	GPIO_Type 			*Base 		= Gpio_Base_Pointer[Instance];
	GPIO_PinValue		pinValue 	= 0u;
	
	/* Check Invalid Input */
	
	/* Read logic level from pin */
	pinValue = GPIO_ReadPin(Base, PinNum);
	return pinValue;
}

/*
 * @func	GPIO_ReadFromInputPort
 * @brief	Read value from input port
 * @param	GPIO Instance
 * @reval	value of gpio port
 */
uint16 GPIO_ReadFromInputPort(GPIO_InstanceType Instance)
{
	GPIO_Type 			*Base 		= Gpio_Base_Pointer[Instance];
	uint16				portValue	= 0u;

	/* Check Invalid Input */

	/* Read port value */
	portValue = GPIO_ReadPort(Base);
	return portValue;
}

/*
 * @func	GPIO_WriteOutputPin
 * @brief	write logic level to output pin
 * @param	GPIOx - GPIO Instance
 * 			PinNumber - GPIO pin number
 * 			Value - logic level
 * @reval	none
 */
void GPIO_WriteOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum, GPIO_PinValue PinValue)
{
	GPIO_Type 			*Base 		= Gpio_Base_Pointer[Instance];
	
	/* Check Invalid Input */
	
	/* Write logic level to a Pin */
	GPIO_WritePin(Base, PinNum, PinValue);
}

/*
 * @func	GPIO_ToggleOutputPin
 * @brief	Toggle logic level of output pin
 * @param	GPIOx - GPIO Instance
 * 			Value - logic level
 * @reval	none
 */
void GPIO_ToggleOutputPin(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum)
{
	GPIO_Type 			*Base 		= Gpio_Base_Pointer[Instance];
	
	/* Check Invalid Input */
	
	if ( GPIO_PIN_RESET == GPIO_ReadPin(Base, PinNum) )
	{
		GPIO_WritePin(Base, PinNum, GPIO_PIN_SET);
	}
	else	/* current status = GPIO_PIN_SET */
	{
		GPIO_WritePin(Base, PinNum, GPIO_PIN_RESET);
	}
}

/*
 * @func	GPIO_SetOutputPort
 * @brief	Set value to output port (Set all Pins)
 * @param	GPIOx - GPIO Instance
 * 			Value - logic level
 * @reval	none
 */
void GPIO_SetOutputPort(GPIO_InstanceType Instance)
{
	GPIO_Type 			*Base 		= Gpio_Base_Pointer[Instance];
	
	/* Set all pin in port to 1 logic */
	GPIO_SetPort(Base);
}

/*
 * @func	GPIO_ClearOutputPort
 * @brief	Clear value to output port (Clear all Pins)
 * @param	GPIOx - GPIO Instance
 * 			Value - logic level
 * @reval	none
 */
void GPIO_ClearOutputPort(GPIO_InstanceType Instance)
{
	GPIO_Type 			*Base 		= Gpio_Base_Pointer[Instance];
	
	/* Set all pin in port to 1 logic */
	GPIO_ClearPort(Base);
}
