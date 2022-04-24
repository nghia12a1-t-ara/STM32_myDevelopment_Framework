/*
 * stm32f4xx_gpio_driver.c
 *
 *  Created on: Jan 29, 2019
 *      Author: admin
 */

#include "GPIO.h"

/**************************************************************************************
 * 						APIs supported by the driver
 * 		For more information about the APIs check the function definitions
 **************************************************************************************/
/*
 * @func	GPIO_PeriClockControl
 * @brief	Enable/Disable Peripheral GPIO Clock
 * @param	Base address of GPIO
 * 			ENABLE or DISABLE macros
 * @reval	none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pGPIOx == GPIOA)
		{
			RCC->AHB1ENR |= (1 << 0);
		}
		else if (pGPIOx == GPIOB)
		{
			RCC->AHB1ENR |= (1 << 1);
		}
		else if (pGPIOx == GPIOC)
		{
			RCC->AHB1ENR |= (1 << 2);
		}
		else if (pGPIOx == GPIOD)
		{
			RCC->AHB1ENR |= (1 << 3);
		}
		else if (pGPIOx == GPIOE)
		{
			RCC->AHB1ENR |= (1 << 4);
		}
		else if (pGPIOx == GPIOH)
		{
			RCC->AHB1ENR |= (1 << 7);
		}
	}
	else
	{
		/* TODO */
	}
}


/*
 * @func	GPIO_Init
 * @brief	Configure Mode for GPIO
 * @param	pGPIOHandle - Struct contains Mode for GPIO
 * @reval	none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;

	/* 1. Configure the mode of GPIO pin */

	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x03 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);	/* Clearing 2 bits */
		pGPIOHandle->pGPIOx->MODER |= temp;			/* Setting 2 bits */
	}
	else
	{
		/* Interrupt Mode Configuration */
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			/* 1. Configure for Falling Trigger */
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			/* Clear the corresponding RTSR bit */
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			/* 1. Configure for Raising Trigger */
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			/* Clear the corresponding FTSR bit */
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			/* 1. Configure for both Raising & Falling Trigger */
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		/* 2. Configure the GPIO port selection in SYSCFG_EXTICR */
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

		/* 3. Enable the Exti Interrupt delivery using IMR */
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	/* 2. Configure the speed */

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x03 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);	/* Clearing 2 bits */
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;			/* Setting 2 bits */

	temp = 0;

	/* 3. Configure the pull-up/pull-down settings */

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x03 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);	/* Clearing 2 bits */
	pGPIOHandle->pGPIOx->PUPDR |= temp;			/* Setting 2 bits */

	temp = 0;

	/* 4. Configure the output type (optype) */

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x03 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);	/* Clearing 2 bits */
	pGPIOHandle->pGPIOx->OTYPER |= temp;			/* Setting 2 bits */

	temp = 0;

	/* 5. Configure the alternate function */
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		/* Configure the Alternate Function Register */
		uint32_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
	}
}


/*
 * @func	GPIO_DeInit
 * @brief	Disable Peripheral GPIO Clock
 * @param	GPIOx
 * @reval	none
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if (pGPIOx == GPIOA)
	{
		RCC->AHB1ENR &= ~(1 << 0);
	}
	else if (pGPIOx == GPIOB)
	{
		RCC->AHB1ENR &= ~(1 << 1);
	}
	else if (pGPIOx == GPIOC)
	{
		RCC->AHB1ENR &= ~(1 << 2);
	}
	else if (pGPIOx == GPIOD)
	{
		RCC->AHB1ENR &= ~(1 << 3);
	}
	else if (pGPIOx == GPIOE)
	{
		RCC->AHB1ENR &= ~(1 << 4);
	}
	else if (pGPIOx == GPIOH)
	{
		RCC->AHB1ENR &= ~(1 << 7);
	}
}

/*
 * @func	GPIO_ReadFromInputPin
 * @brief	Read logic level from input pin
 * @param	GPIO port number
 * 			GPIO pin number
 * @reval	logic level of gpio pin
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;

	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);

	return value;
}

/*
 * @func	GPIO_ReadFromInputPort
 * @brief	Read value from input port
 * @param	GPIO port number
 * @reval	value of gpio port
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;

	value = (uint16_t)pGPIOx->IDR;

	return value;
}

/*
 * @func	GPIO_WriteToOutputPin
 * @brief	write logic level to output pin
 * @param	GPIOx - GPIO port number
 * 			PinNumber - GPIO pin number
 * 			Value - logic level
 * @reval	none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else /*!< Value == GPIO_PIN_RESET >*/
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}


/*
 * @func	GPIO_WriteToOutputPort
 * @brief	write value to output port
 * @param	GPIOx - GPIO port number
 * 			Value - logic level
 * @reval	none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}


/*
 * @func	GPIO_ToggleOutputPin
 * @brief	Toggle logic level of output pin
 * @param	GPIOx - GPIO port number
 * 			Value - logic level
 * @reval	none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);	/* XOR logic to toggle logic level */
}


