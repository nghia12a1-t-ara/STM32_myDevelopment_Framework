#ifndef __GPIO_BASE_H_
#define __GPIO_BASE_H_

#include "stm32f4xx.h"

/**
 * Number of GPIO Hardware Instance
 */
#define GPIO_INSTANCE_COUNT				(9U)

/*
 * peripheral register definition structure for GPIO
 */
typedef struct
{
	__vo uint32 MODER;                  /*!< GPIO port mode register,                   Address offset: 0x00 */
	__vo uint32 OTYPER;                 /*!< GPIO Output Types 							Address offset: 0x04 */
	__vo uint32 OSPEEDR;				/*!< GPIO Output Speed 							Address offset: 0x08 */
	__vo uint32 PUPDR;					/*!< GPIO Pull Input Setup						Address offset: 0x0C */
	__vo uint32 IDR;					/*!< GPIO Input Data Register					Address offset: 0x10 */
	__vo uint32 ODR;					/*!< GPIO Output Data Register					Address offset: 0x14 */
	__vo uint32 BSRR;					/*!< GPIO Bit Set/Reset Register 				Address offset: 0x18 */
	__vo uint32 LCKR;					/*!< GPIO Lock Register							Address offset: 0x1C */
	__vo uint32 AFR[2];					/*!< AFR[0] : GPIO alternate function low register, AF[1] : GPIO alternate function high register Address offset: 0x20-0x24 */
} GPIO_Type;


/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 * TODO : Complete for all other peripherals
 */
#define GPIOA_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x2000)

/*
 * peripheral definitions ( Peripheral base addresses typecasted to xxx_RegDef_t)
 */

#define GPIOA  							((GPIO_Type*)GPIOA_BASEADDR)
#define GPIOB  							((GPIO_Type*)GPIOB_BASEADDR)
#define GPIOC  							((GPIO_Type*)GPIOC_BASEADDR)
#define GPIOD  							((GPIO_Type*)GPIOD_BASEADDR)
#define GPIOE  							((GPIO_Type*)GPIOE_BASEADDR)
#define GPIOF  							((GPIO_Type*)GPIOF_BASEADDR)
#define GPIOG  							((GPIO_Type*)GPIOG_BASEADDR)
#define GPIOH  							((GPIO_Type*)GPIOH_BASEADDR)
#define GPIOI  							((GPIO_Type*)GPIOI_BASEADDR)

/**
 * Define Array of GPIO Instances
 */
#define GPIO_BASE_PTRS					{ GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI }

/**
 * Define Register Mask for each Pins
 */
#define GPIO_MODER_PIN_MASK				0x03u
#define GPIO_OSPEED_PIN_MASK			0x03u
#define GPIO_PULL_PIN_MASK				0x03u
#define GPIO_OTYPE_PIN_MASK				0x01u
#define GPIO_ALTERNATE_PIN_MASK			0x0Fu
/*
 *  Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)
#define GPIOI_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8)); }while(0)
	
/*
 * This macro returns a code( between 0 to 7) for a given GPIO base address(x)
 */
#define GPIO_BASEADDR_TO_CODE(x)      ( (x == GPIOA)?0:\
										(x == GPIOB)?1:\
										(x == GPIOC)?2:\
										(x == GPIOD)?3:\
								        (x == GPIOE)?4:\
								        (x == GPIOF)?5:\
								        (x == GPIOG)?6:\
								        (x == GPIOH)?7: \
								        (x == GPIOI)?8:0)


#endif	/* !(__GPIO_BASE_H_) */
