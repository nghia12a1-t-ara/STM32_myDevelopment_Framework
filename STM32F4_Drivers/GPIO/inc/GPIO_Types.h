#ifndef __GPIO_TYPES_
#define __GPIO_TYPES_

#include "GPIO_Base.h"

/**
 * GPIO Pin Number Types
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
} GPIO_PinNumberTypes;

/**
 * GPIO Direction Mode Types
 */
typedef enum 
{
	GPIO_MODE_INPUT				= 0x00u,
	GPIO_MODE_OUTPUT			= 0x01u,
	GPIO_MODE_ALTERNATE			= 0x02u,
	GPIO_MODE_ANALOG			= 0x03u
} GPIO_ModeTypes;

/**
 * GPIO Output Types
 */
typedef enum 
{
	GPIO_OTYPE_PUSHPULL			= 0x00u,
	GPIO_OTYPE_OPENDRAIN		= 0x01u
} GPIO_OutputTypes;

/**
 * GPIO Output Speed Types
 */
typedef enum 
{
	GPIO_OSPEED_LOW				= 0x00u,
	GPIO_OSPEED_MEDIUM			= 0x01u,
	GPIO_OSPEED_HIGH			= 0x02u,
	GPIO_OSPEED_VERYHIGH		= 0x03u
} GPIO_OutSpeedTypes;

/**
 * GPIO Input Mode Types
 */
typedef enum 
{
	GPIO_INPUT_PULLDISABLE		= 0x00u,
	GPIO_INPUT_PULLUP			= 0x01u,
	GPIO_INPUT_PULLDOWN			= 0x02u
} GPIO_InputTypes;

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
} GPIO_AlternateTypes;


/*
 * This is a Configuration structure for a GPIO pin
 */
typedef struct
{
	GPIO_PinNumberTypes			GPIO_PinNumber;				/*!< Pin Number Types 0 to 15 >*/ 
	GPIO_ModeTypes				GPIO_PinMode;				/*!< Pin Mode - In/Out or Alternate or Analog >*/ 
	GPIO_OutSpeedTypes			GPIO_PinSpeed;				/*!< Pin Output Speed >*/
	GPIO_InputTypes				GPIO_PinInputMode;			/*!< Pin Input Mode (Pull up/down) >*/
	GPIO_OutputTypes			GPIO_PinOutputMode;			/*!< Pin Output Mode (Pushpull/Opendrain) >*/
	GPIO_AlternateTypes			GPIO_PinAlternate;			/*!< Pin Alternate Function >*/
} GPIO_PinConfigType;

/*
 * This is a Handle structure for a GPIO pin
 */

typedef struct
{
	GPIO_Types 					*pGPIOx;       				/*!< GPIO Pointer to Base Instance >*/
	GPIO_PinConfigType 			GPIO_PinConfig;   			/*!< This holds GPIO pin configuration settings >*/
} GPIO_UserConfigType;


/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IT_FT     		4
#define GPIO_MODE_IT_RT     		5
#define GPIO_MODE_IT_RFT    		6


#endif	/* !(__GPIO_TYPES_) */
