#ifndef __GPIO_TYPE__
#define __GPIO_TYPE__

#include "GPIO_Base.h"

/**
 * GPIO ALternate Functions for STM32F401
 */
typedef enum 
{
	GPIO_INSTANCE_A				= 0u,
	GPIO_INSTANCE_B				= 1u,
	GPIO_INSTANCE_C				= 2u,
	GPIO_INSTANCE_D				= 3u,
	GPIO_INSTANCE_E				= 4u,
	GPIO_INSTANCE_F				= 5u,
	GPIO_INSTANCE_G				= 6u,
	GPIO_INSTANCE_H				= 7u,
	GPIO_INSTANCE_I				= 8u
} GPIO_InstanceType;

/**
 * GPIO Pin Number Type
 */
typedef enum 
{
	GPIO_PIN_NO_0  				= 0u,
	GPIO_PIN_NO_1  				= 1u,
	GPIO_PIN_NO_2  				= 2u,
	GPIO_PIN_NO_3  				= 3u,
	GPIO_PIN_NO_4  				= 4u,
	GPIO_PIN_NO_5  				= 5u,
	GPIO_PIN_NO_6  				= 6u,
	GPIO_PIN_NO_7  				= 7u,
	GPIO_PIN_NO_8  				= 8u,
	GPIO_PIN_NO_9  				= 9u,
	GPIO_PIN_NO_10  			= 10u,
	GPIO_PIN_NO_11 				= 11u,
	GPIO_PIN_NO_12  			= 12u,
	GPIO_PIN_NO_13 				= 13u,
	GPIO_PIN_NO_14 				= 14u,
	GPIO_PIN_NO_15 				= 15u
} GPIO_PinNumberType;

/**
 * GPIO Direction Mode Type
 */
typedef enum 
{
	GPIO_MODE_INPUT				= 0x00u,
	GPIO_MODE_OUTPUT			= 0x01u,
	GPIO_MODE_ALTERNATE			= 0x02u,
	GPIO_MODE_ANALOG			= 0x03u,
	GPIO_MODE_EXTI				= 0x04u
} GPIO_ModeType;

/**
 * GPIO Output Type
 */
typedef enum 
{
	GPIO_OTYPE_PUSHPULL			= 0x00u,
	GPIO_OTYPE_OPENDRAIN		= 0x01u
} GPIO_OutputType;

/**
 * GPIO Output Speed Type
 */
typedef enum 
{
	GPIO_OSPEED_LOW				= 0x00u,
	GPIO_OSPEED_MEDIUM			= 0x01u,
	GPIO_OSPEED_HIGH			= 0x02u,
	GPIO_OSPEED_VERYHIGH		= 0x03u
} GPIO_OutSpeedType;

/**
 * GPIO Input Mode Type
 */
typedef enum 
{
	GPIO_INPUT_FLOATING			= 0x00u,
	GPIO_INPUT_PULLUP			= 0x01u,
	GPIO_INPUT_PULLDOWN			= 0x02u
} GPIO_InputType;

/**
 * GPIO ALternate Functions
 */
typedef enum 
{
	GPIO_ALTERNATE_0  			= 0u,
	GPIO_ALTERNATE_1  			= 1u,
	GPIO_ALTERNATE_2  			= 2u,
	GPIO_ALTERNATE_3  			= 3u,
	GPIO_ALTERNATE_4  			= 4u,
	GPIO_ALTERNATE_5  			= 5u,
	GPIO_ALTERNATE_6  			= 6u,
	GPIO_ALTERNATE_7  			= 7u,
	GPIO_ALTERNATE_8  			= 8u,
	GPIO_ALTERNATE_9  			= 9u,
	GPIO_ALTERNATE_10  			= 10u,
	GPIO_ALTERNATE_11 			= 11u,
	GPIO_ALTERNATE_12  			= 12u,
	GPIO_ALTERNATE_13 			= 13u,
	GPIO_ALTERNATE_14 			= 14u,
	GPIO_ALTERNATE_15 			= 15u
} GPIO_AlternateType;

/**
 * GPIO PinValue
 */
typedef enum 
{
	GPIO_PIN_RESET 				= 0x0u,
	GPIO_PIN_SET 				= 0x1u
} GPIO_PinValue;

/*
 * @EXTI_MODES
 * External Interrupt Modes
 */
typedef enum {
	EXTI_DISABLE				= 0x0u,
	EXTI_FALLING_EDGE			= 0x1u,
	EXTI_RASING_EDGE			= 0x2u,
	EXTI_RASING_FALLING			= 0x3u
} EXTI_ModeType;

/*
 * This is a Configuration structure for a GPIO pin
 */
typedef struct
{
	GPIO_PinNumberType			GPIO_PinNumber;				/*!< Pin Number Type 0 to 15 >*/ 
	GPIO_ModeType				GPIO_PinMode;				/*!< Pin Mode - In/Out or Alternate or Analog >*/ 
	GPIO_OutSpeedType			GPIO_PinSpeed;				/*!< Pin Output Speed >*/
	GPIO_InputType				GPIO_PinInputMode;			/*!< Pin Input Mode (Pull up/down) >*/
	GPIO_OutputType				GPIO_PinOutputMode;			/*!< Pin Output Mode (Pushpull/Opendrain) >*/
	GPIO_AlternateType			GPIO_PinAlternate;			/*!< Pin Alternate Function >*/
	EXTI_ModeType				EXTI_Mode;					/*!< EXTI Mode - Ignore if not support EXTI >*/
} GPIO_PinConfigType;


#endif	/* !(__GPIO_TYPE__) */
