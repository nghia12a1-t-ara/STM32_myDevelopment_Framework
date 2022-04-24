#ifndef __GPIO_TYPES_
#define __GPIO_TYPES_

/*
 * This is a Configuration structure for a GPIO pin
 */
typedef struct
{
	uint8 GPIO_PinNumber;
	uint8 GPIO_PinMode;			/*!< possible values from @GPIO_PIN_MODES >*/
	uint8 GPIO_PinSpeed;			/*!< possible values from @GPIO_PIN_SPEED >*/
	uint8 GPIO_PinPuPdControl;
	uint8 GPIO_PinOPType;
	uint8 GPIO_PinAltFunMode;
} GPIO_PinConfig_t;

/*
 * This is a Handle structure for a GPIO pin
 */

typedef struct
{
	GPIO_Types *pGPIOx;       		/*!< This holds the base address of the GPIO port to which the pin belongs >*/
	GPIO_PinConfig_t GPIO_PinConfig;   /*!< This holds GPIO pin configuration settings >*/

} GPIO_Handle_t;


/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0  				0
#define GPIO_PIN_NO_1  				1
#define GPIO_PIN_NO_2  				2
#define GPIO_PIN_NO_3  				3
#define GPIO_PIN_NO_4  				4
#define GPIO_PIN_NO_5  				5
#define GPIO_PIN_NO_6  				6
#define GPIO_PIN_NO_7  				7
#define GPIO_PIN_NO_8  				8
#define GPIO_PIN_NO_9  				9
#define GPIO_PIN_NO_10  			10
#define GPIO_PIN_NO_11 				11
#define GPIO_PIN_NO_12  			12
#define GPIO_PIN_NO_13 				13
#define GPIO_PIN_NO_14 				14
#define GPIO_PIN_NO_15 				15

/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 				0
#define GPIO_MODE_OUT 				1
#define GPIO_MODE_ALTFN 			2
#define GPIO_MODE_ANALOG 			3
#define GPIO_MODE_IT_FT     		4
#define GPIO_MODE_IT_RT     		5
#define GPIO_MODE_IT_RFT    		6

/*
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP   			0
#define GPIO_OP_TYPE_OD   			1

/*
 * @GPIO_PIN_SPEED
 * GPIO pin possible output speeds
 */
#define GPIO_SPEED_LOW				0
#define GPIO_SPEED_MEDIUM			1
#define GPIO_SPEED_FAST				2
#define GPOI_SPEED_HIGH				3

/*
 * GPIO pin pull up AND pull down configuration macros
 */
#define GPIO_NO_PUPD   				0
#define GPIO_PIN_PU					1
#define GPIO_PIN_PD					2


#endif	/* !(__GPIO_TYPES_) */
