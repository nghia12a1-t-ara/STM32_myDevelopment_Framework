/**
 * Filename		: GPIO_HwAccess.h
 * Author		: Nghia Taarabt
 * Create Date 	: 01/01/23
 * Brief		: GPIO Hardware Access Specific for each Platform
 */

#ifndef __GPIO_HWACCESS_H__
#define __GPIO_HWACCESS_H__

#include "GPIO_Base.h"
#include "EXTI_Base.h"
#include "GPIO_Type.h"
#include "RCC.h"

/**
 * GPIO ALternate Functions for STM32F401
 */
typedef enum 
{
	GPIO_ALTERNATE_SYSTEM				= GPIO_ALTERNATE_0,
	GPIO_ALTERNATE_TIMER1_2				= GPIO_ALTERNATE_1,
	GPIO_ALTERNATE_TIMER3_5				= GPIO_ALTERNATE_2,
	GPIO_ALTERNATE_TIMER9_11			= GPIO_ALTERNATE_3,
	GPIO_ALTERNATE_I2C1_3				= GPIO_ALTERNATE_4,
	GPIO_ALTERNATE_SPI1_4				= GPIO_ALTERNATE_5,
	GPIO_ALTERNATE_SPI3					= GPIO_ALTERNATE_6,
	GPIO_ALTERNATE_USART1_2				= GPIO_ALTERNATE_7,
	GPIO_ALTERNATE_USART_6				= GPIO_ALTERNATE_8,
	GPIO_ALTERNATE_I2C2_3				= GPIO_ALTERNATE_9,
	GPIO_ALTERNATE_OTG_FS				= GPIO_ALTERNATE_10,
	GPIO_ALTERNATE_REVERSED1			= GPIO_ALTERNATE_11,
	GPIO_ALTERNATE_SDIO					= GPIO_ALTERNATE_12,
	GPIO_ALTERNATE_REVERSED2			= GPIO_ALTERNATE_13,
	GPIO_ALTERNATE_REVERSED3			= GPIO_ALTERNATE_14,
	GPIO_ALTERNATE_EVENTOUT				= GPIO_ALTERNATE_15
} GPIO_AFSpecType;


/*
 * @func	GPIO_PeriClockControl
 * @brief	Enable/Disable Peripheral GPIO Clock
 * @param	Base address of GPIO
 * 			ENABLE or DISABLE macros
 * @reval	none
 */
__STATIC_INLINE void GPIO_PeriClockControl(GPIO_Type *pGPIOx, uint8 EnorDi)
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

/**
 * @fn 		GPIO_SetPinMode
 * @brief 	GPIO Set Pin Moder
 */
__STATIC_INLINE void GPIO_SetPinMode(GPIO_Type * Base, GPIO_PinNumberType PinNum, GPIO_ModeType PinMode)
{
	Base->MODER &= ~(GPIO_MODER_PIN_MASK << ((uint8)PinNum << 1));
	Base->MODER |= (PinMode << ((uint8)PinNum << 1));
}

/**
 * @fn 		GPIO_SetOutSpeed
 * @brief 	GPIO Set Output Speed
 */
__STATIC_INLINE void GPIO_SetOutSpeed(GPIO_Type * Base, GPIO_PinNumberType PinNum, GPIO_OutSpeedType PinSpeed)
{
	Base->OSPEEDR &= ~(GPIO_OSPEED_PIN_MASK << ((uint8)PinNum << 1));
	Base->OSPEEDR |= (PinSpeed << ((uint8)PinNum << 1));
}

/**
 * @fn 		GPIO_SetInputMode
 * @brief 	GPIO Set Input Mode
 */
__STATIC_INLINE void GPIO_SetInputMode(GPIO_Type * Base, GPIO_PinNumberType PinNum, GPIO_InputType PinPull)
{
	Base->PUPDR &= ~(GPIO_PULL_PIN_MASK << ((uint8)PinNum << 1));
	Base->PUPDR |= (PinPull << ((uint8)PinNum << 1));
}

/**
 * @fn 		GPIO_SetOutputMode
 * @brief 	GPIO Set Output Mode
 */
__STATIC_INLINE void GPIO_SetOutputMode(GPIO_Type * Base, GPIO_PinNumberType PinNum, GPIO_OutputType PinOutMode)
{
	Base->OTYPER &= ~(GPIO_OTYPE_PIN_MASK << (uint8)PinNum);
	Base->OTYPER |= (PinOutMode << (uint8)PinNum);
}

/**
 * @fn 		GPIO_SetAlternateMode
 * @brief 	GPIO Set Alternate Mode
 */
__STATIC_INLINE void GPIO_SetAlternateMode(GPIO_Type * Base, GPIO_PinNumberType PinNum, GPIO_AlternateType PinAFMode)
{
	uint8 AFShift = (PinNum % 8) << 2;
	Base->AFR[PinNum >> 3] &= ~(GPIO_ALTERNATE_PIN_MASK << AFShift);
	Base->AFR[PinNum >> 3] |= (PinAFMode << AFShift);
}

/**
 * @fn 		GPIO_ReadPin
 * @brief 	GPIO Read a Pin Number
 */
__STATIC_INLINE GPIO_PinValue GPIO_ReadPin(GPIO_Type * Base, GPIO_PinNumberType PinNum)
{
	GPIO_PinValue retVal = GPIO_PIN_RESET;
	
	if ( 1u == (uint8)((Base->IDR >> PinNum) & 0x00000001) )
	{
		retVal = GPIO_PIN_SET;
	}
	
	return retVal;
}

/**
 * @fn 		GPIO_ReadPort
 * @brief 	GPIO Read a Pin Number
 */
__STATIC_INLINE uint16 GPIO_ReadPort(GPIO_Type * Base)
{
	return (uint16)(Base->IDR);
}

/**
 * @fn 		GPIO_WritePin
 * @brief 	GPIO Read a Pin Number
 */
__STATIC_INLINE void GPIO_WritePin(GPIO_Type * Base, GPIO_PinNumberType PinNum, GPIO_PinValue PinValue)
{
	/* Access to BSRR pin
		- bit 00-15 to set bit		- Default - SET PIN
		- bit 16-31 to clear bit 	- If RESET PIN
	*/
	uint8	GPIO_BSRR_PinShift	= PinNum;
	
	/* Set PinNum again if Pin Reset */
	if (PinValue == GPIO_PIN_RESET)
	{
		GPIO_BSRR_PinShift = PinNum + 16;
	}
	Base->BSRR |= (1 << GPIO_BSRR_PinShift);
}

/**
 * @fn 		GPIO_SetPort
 * @brief 	GPIO Set all Pins in a Port
 */
__STATIC_INLINE void GPIO_SetPort(GPIO_Type * Base)
{
	Base->ODR |= 0xFFFF;
}

/**
 * @fn 		GPIO_ClearPort
 * @brief 	GPIO Set all Pins in a Port
 */
__STATIC_INLINE void GPIO_ClearPort(GPIO_Type * Base)
{
	Base->ODR &= ~0xFFFF;
}

/**
 *******************************************************************************************
 **************************** External Interrupt Hardware Access ***************************
 *******************************************************************************************
 */

/**
 * @fn 		EXTI_SetMode
 * @brief 	EXTI Set Edge Mode
 */
__STATIC_INLINE void EXTI_SetMode(GPIO_PinNumberType PinNum, EXTI_ModeType ExtiMode)
{
	switch (ExtiMode)
	{
		case EXTI_FALLING_EDGE:
			/* Configure for Falling Trigger */
			EXTI->FTSR |= (1 << PinNum);
			/* Clear the corresponding RTSR bit */
			EXTI->RTSR &= ~(1 << PinNum);
			break;
		case EXTI_RASING_EDGE:
			/* Configure for Raising Trigger */
			EXTI->RTSR |= (1 << PinNum);
			/* Clear the corresponding FTSR bit */
			EXTI->FTSR &= ~(1 << PinNum);
			break;
		case EXTI_RASING_FALLING:
			/* Configure for both Raising & Falling Trigger */
			EXTI->RTSR |= (1 << PinNum);
			EXTI->FTSR |= (1 << PinNum);
			break;
		default:
			break;
	}
}

/**
 * @fn 		EXTI_SetSrcInput
 * @brief 	Set Source Input (Port) for External Interrupt
 */
__STATIC_INLINE void EXTI_SetSrcInput(GPIO_InstanceType Instance, GPIO_PinNumberType PinNum)
{
	uint8 Exti_Control_Shift = (PinNum % 4) << 2;
	
	/* Enable Clock for SYSCFG Module */
	SYSCFG_PCLK_EN();
	
	/* Select the source input for the EXTIx external interrupt */
	SYSCFG->EXTICR[PinNum >> 2] = Instance << (Exti_Control_Shift);
}

/**
 * @fn 		EXTI_SetControl
 * @brief 	Enable or Disable External Interrupt
 */
__STATIC_INLINE void EXTI_SetControl(GPIO_PinNumberType PinNum, uint8 EnorDi)
{
	if ( ENABLE == EnorDi )
	{
		EXTI->IMR |= (1 << PinNum);
	}
	else	/* DISABLE == EnorDi */
	{
		EXTI->IMR &= ~(1 << PinNum);
	}
}

#endif	/* __GPIO_HWACCESS_H__ */
