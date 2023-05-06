/**
 * Filename		: CLOCK_Type.h
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Clock driver Typedef
 */

#ifndef __CLOCK_TYPE_H__
#define __CLOCK_TYPE_H__

/* STM32F4 use RCC module for configure Clock */
#include "RCC_Base.h"

/** @fn
 * @{   Source Clock for SYSCLK 
 */
typedef enum
{
    CLOCK_PLL_SOURCE_HSI            = 0u,
    CLOCK_PLL_SOURCE_HSE            = 1u,
} ClockPLLSrcType;

/** @fn
 * @{   Source Clock for SYSCLK 
 */
typedef enum
{
    CLOCK_SYSCLK_SOURCE_HSI         = 0u,
    CLOCK_SYSCLK_SOURCE_HSE         = 1u,
    CLOCK_SYSCLK_SOURCE_PLL         = 2u,
} ClockSYSCLKSrcType;

/** @fn
 * @{   Clock Divide for SYSCLK - Source for AHB Prescaler
 */
typedef enum
{
    CLOCK_AHB_PRESCALER_1           = 0x0u,
    CLOCK_AHB_PRESCALER_2           = 0x8u,
    CLOCK_AHB_PRESCALER_4           = 0x9u,
    CLOCK_AHB_PRESCALER_8           = 0xAu,
    CLOCK_AHB_PRESCALER_16          = 0xBu,
    CLOCK_AHB_PRESCALER_64          = 0xCu,
    CLOCK_AHB_PRESCALER_128         = 0xDu,
    CLOCK_AHB_PRESCALER_256         = 0xEu,
    CLOCK_AHB_PRESCALER_512         = 0xFu,
} ClockAHBPrescalerType;

/** @fn
 * @{   Clock Divide for AHB Bus - Source for APB Prescaler
 */
typedef enum
{
    CLOCK_APB_PRESCALER_1           = 0x0u,
    CLOCK_APB_PRESCALER_2           = 0x4u,
    CLOCK_APB_PRESCALER_4           = 0x5u,
    CLOCK_APB_PRESCALER_8           = 0x6u,
    CLOCK_APB_PRESCALER_16          = 0x7u,
} ClockAPBPrescalerType;

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32 SYSCLK_FREQ;    /*!<  SYSCLK clock frequency expressed in Hz */
  uint32 HCLK_FREQ;      /*!<  HCLK clock frequency expressed in Hz   */
  uint32 PCLK1_FREQ;     /*!<  PCLK1 clock frequency expressed in Hz  */
  uint32 PCLK2_FREQ;     /*!<  PCLK2 clock frequency expressed in Hz  */
} ClockSourceType;

/**************************************************************************/
/************************ Clock for Peripherals ***************************/
/**************************************************************************/
/**
 * @fn  Define Types of Peripherals Bus
 */
typedef enum
{
    CLOCK_PER_BUS_AHB1          = 0u,   /* 00 - 31 */
    CLOCK_PER_BUS_AHB2          = 1u,   /* 32 - 63 */
    CLOCK_PER_BUS_APB1          = 2u,   /* 64 - 95 */
    CLOCK_PER_BUS_APB2          = 3u,   /* >= 96 */
} ClockPeripheralBusType;

/**
 * @fn  Define Position of Peripherals Clock in RCC Registers
 */
#define CLOCK_AHB1_POSITION_OFFSET      (0u)
#define CLOCK_AHB2_POSITION_OFFSET      (32u)
#define CLOCK_APB1_POSITION_OFFSET      (64u)
#define CLOCK_APB2_POSITION_OFFSET      (96u)

typedef enum
{
    /* AHB1 Clock Position */
    CLOCK_GPIOA     = 0u,
    CLOCK_GPIOB     = 1u,
    CLOCK_GPIOC     = 2u,
    CLOCK_GPIOD     = 3u,
    CLOCK_GPIOE     = 4u,
    CLOCK_GPIOH     = 7u,
    CLOCK_CRC       = 12u,
    CLOCK_DMA1      = 21u,
    CLOCK_DMA2      = 22u,
    /* AHB2 Clock Position + 32 */
    CLOCK_USB_OTGFS = 39u,
    /* APB1 Clock Position + 64 */
    CLOCK_TIM2      = 64u,
    CLOCK_TIM3      = 65u,
    CLOCK_TIM4      = 66u,
    CLOCK_TIM5      = 67u,
    CLOCK_WWDG      = 75u,
    CLOCK_SPI2      = 78u,
    CLOCK_SPI3      = 79u,
    CLOCK_USART2    = 81u,
    CLOCK_I2C1      = 85u,
    CLOCK_I2C2      = 86u,
    CLOCK_I2C3      = 87u,
    CLOCK_PWR       = 92u,
    /* APB2 Clock Position + 96 */
    CLOCK_TIM1      = 96u,
    CLOCK_USART1    = 100u,
    CLOCK_USART6    = 101u,
    CLOCK_ADC1      = 104u,
    CLOCK_SDIO      = 107u,
    CLOCK_SPI1      = 108u,
    CLOCK_SPI4      = 109u,
    CLOCK_SYSCFG    = 110u,
    CLOCK_TIM9      = 112u,
    CLOCK_TIM10     = 113u,
    CLOCK_TIM11     = 114u,
} ClockPeripheralType;

#endif /* __CLOCK_TYPE_H__ */
