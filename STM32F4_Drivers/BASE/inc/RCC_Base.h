#ifndef __RCC_BASE_H__
#define __RCC_BASE_H__

#include "stm32f4xx.h"

/**
 * Peripheral register definition structure for RCC
 */
typedef struct
{
  __vo uint32 CR;            /*!< TODO,     					Address offset: 0x00 */
  __vo uint32 PLLCFGR;       /*!< TODO,     					Address offset: 0x04 */
  __vo uint32 CFGR;          /*!< TODO,     					Address offset: 0x08 */
  __vo uint32 CIR;           /*!< TODO,     					Address offset: 0x0C */
  __vo uint32 AHB1RSTR;      /*!< TODO,     					Address offset: 0x10 */
  __vo uint32 AHB2RSTR;      /*!< TODO,     					Address offset: 0x14 */
  __vo uint32 AHB3RSTR;      /*!< TODO,     					Address offset: 0x18 */
  uint32      RESERVED0;     /*!< Reserved, 0x1C                                                  */
  __vo uint32 APB1RSTR;      /*!< TODO,     					Address offset: 0x20 */
  __vo uint32 APB2RSTR;      /*!< TODO,     					Address offset: 0x24 */
  uint32      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                             */
  __vo uint32 AHB1ENR;       /*!< TODO,     					Address offset: 0x30 */
  __vo uint32 AHB2ENR;       /*!< TODO,     					Address offset: 0x34 */
  __vo uint32 AHB3ENR;       /*!< TODO,     					Address offset: 0x38 */
  uint32      RESERVED2;     /*!< Reserved, 0x3C                                                  */
  __vo uint32 APB1ENR;       /*!< TODO,     					Address offset: 0x40 */
  __vo uint32 APB2ENR;       /*!< TODO,     					Address offset: 0x44 */
  uint32      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                             */
  __vo uint32 AHB1LPENR;     /*!< TODO,     					Address offset: 0x50 */
  __vo uint32 AHB2LPENR;     /*!< TODO,     					Address offset: 0x54 */
  __vo uint32 AHB3LPENR;     /*!< TODO,     					Address offset: 0x58 */
  uint32      RESERVED4;     /*!< Reserved, 0x5C                                                  */
  __vo uint32 APB1LPENR;     /*!< TODO,     					Address offset: 0x60 */
  __vo uint32 APB2LPENR;     /*!< RTODO,     					Address offset: 0x64 */
  uint32      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                             */
  __vo uint32 BDCR;          /*!< TODO,     					Address offset: 0x70 */
  __vo uint32 CSR;           /*!< TODO,     					Address offset: 0x74 */
  uint32      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                             */
  __vo uint32 SSCGR;         /*!< TODO,     					Address offset: 0x80 */
  __vo uint32 PLLI2SCFGR;    /*!< TODO,     					Address offset: 0x84 */
  __vo uint32 PLLSAICFGR;    /*!< TODO,     					Address offset: 0x88 */
  __vo uint32 DCKCFGR;       /*!< TODO,     					Address offset: 0x8C */
  __vo uint32 CKGATENR;      /*!< TODO,     					Address offset: 0x90 */
  __vo uint32 DCKCFGR2;      /*!< TODO,     					Address offset: 0x94 */
} RCC_Type;


/**
 * RCC Base Address & Pointer
 */
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)
#define RCC						((RCC_Type*)RCC_BASEADDR)

/***********************************************************************
 *                  RCC Peripheral Access Layer                        *
 ***********************************************************************/
/**
 * RCC clock control register (RCC_CR)
 */
/* Bit 0 HSION: Internal high-speed clock enable */
#define RCC_CR_HSION_MASK       0x1u
#define RCC_CR_HSION_SHIFT      0u
#define RCC_CR_HSION_WIDTH      1u
#define RCC_CR_HSION(x)         (((uint32)(((uint32)(x))<<RCC_CR_HSION_SHIFT))&RCC_CR_HSION_MASK)

/* Bit 1 HSIRDY: Internal high-speed clock ready flag */
#define RCC_CR_HSIRDY_MASK      0x2u
#define RCC_CR_HSIRDY_SHIFT     1u
#define RCC_CR_HSIRDY_WIDTH     1u
#define RCC_CR_HSIRDY(x)        (((uint32)(((uint32)(x))<<RCC_CR_HSIRDY_SHIFT))&RCC_CR_HSIRDY_MASK)

/* Bit 2 Reserved, must be kept at reset value */

/* Bits 7:3 HSITRIM[4:0]: Internal high-speed clock trimming */
#define RCC_CR_HSITRIM_MASK     0xF8u
#define RCC_CR_HSITRIM_SHIFT    3u
#define RCC_CR_HSITRIM_WIDTH    5u
#define RCC_CR_HSITRIM(x)       (((uint32)(((uint32)(x))<<RCC_CR_HSITRIM_SHIFT))&RCC_CR_HSITRIM_MASK)

/* Bit 16 HSEON: HSE clock enable */
#define RCC_CR_HSEON_MASK       0x10000u
#define RCC_CR_HSEON_SHIFT      16u
#define RCC_CR_HSEON_WIDTH      1u
#define RCC_CR_HSEON(x)         (((uint32)(((uint32)(x))<<RCC_CR_HSEON_SHIFT))&RCC_CR_HSEON_MASK)

/* Bit 17 HSERDY: HSE clock ready flag */
#define RCC_CR_HSERDY_MASK      0x20000u
#define RCC_CR_HSERDY_SHIFT     17u
#define RCC_CR_HSERDY_WIDTH     1u
#define RCC_CR_HSERDY(x)        (((uint32)(((uint32)(x))<<RCC_CR_HSERDY_SHIFT))&RCC_CR_HSERDY_MASK)

/* Bit 18 HSEBYP: HSE clock bypass */
#define RCC_CR_HSEBYP_MASK      0x40000u
#define RCC_CR_HSEBYP_SHIFT     18u
#define RCC_CR_HSEBYP_WIDTH     1u
#define RCC_CR_HSEBYP(x)        (((uint32)(((uint32)(x))<<RCC_CR_HSEBYP_SHIFT))&RCC_CR_HSEBYP_MASK)

/* Bit 24 PLLON: Main PLL (PLL) enable */
#define RCC_CR_PLLON_MASK       0x1000000u
#define RCC_CR_PLLON_SHIFT      24u
#define RCC_CR_PLLON_WIDTH      1u
#define RCC_CR_PLLON(x)         (((uint32)(((uint32)(x))<<RCC_CR_PLLON_SHIFT))&RCC_CR_PLLON_MASK)

/* Bit 25 PLLRDY: Main PLL (PLL) clock ready flag */
#define RCC_CR_PLLRDY_MASK      0x2000000u
#define RCC_CR_PLLRDY_SHIFT     25u
#define RCC_CR_PLLRDY_WIDTH     1u
#define RCC_CR_PLLRDY(x)        (((uint32)(((uint32)(x))<<RCC_CR_PLLRDY_SHIFT))&RCC_CR_PLLRDY_MASK)


/**
 * RCC PLL configuration register (RCC_PLLCFGR)
 */
/* Bits 5:0 PLLM: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock */
#define RCC_PLLCFGR_PLLM_MASK       0x3Fu
#define RCC_PLLCFGR_PLLM_SHIFT      0u
#define RCC_PLLCFGR_PLLM_WIDTH      6u
#define RCC_PLLCFGR_PLLM(x)         (((uint32)(((uint32)(x))<<RCC_CR_PLLRDY_SHIFT))&RCC_CR_PLLRDY_MASK)

/* Bits 14:6 PLLN: Main PLL (PLL) multiplication factor for VCO */
#define RCC_PLLCFGR_PLLN_MASK       0x7FC0u
#define RCC_PLLCFGR_PLLN_SHIFT      6u
#define RCC_PLLCFGR_PLLN_WIDTH      9u
#define RCC_PLLCFGR_PLLN(x)         (((uint32)(((uint32)(x))<<RCC_PLLCFGR_PLLN_SHIFT))&RCC_PLLCFGR_PLLN_MASK)

/* Bits 17:16 PLLP: Main PLL (PLL) division factor for main system clock */
#define RCC_PLLCFGR_PLLP_MASK       0x30000u
#define RCC_PLLCFGR_PLLP_SHIFT      16u
#define RCC_PLLCFGR_PLLP_WIDTH      2u
#define RCC_PLLCFGR_PLLP(x)         (((uint32)(((uint32)(x))<<RCC_PLLCFGR_PLLP_SHIFT))&RCC_PLLCFGR_PLLP_MASK)

/* Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source */
#define RCC_PLLCFGR_PLLSRC_MASK     0x400000u
#define RCC_PLLCFGR_PLLSRC_SHIFT    22u
#define RCC_PLLCFGR_PLLSRC_WIDTH    1u
#define RCC_PLLCFGR_PLLSRC(x)       (((uint32)(((uint32)(x))<<RCC_PLLCFGR_PLLSRC_SHIFT))&RCC_PLLCFGR_PLLSRC_MASK)

/* Bits 27:24 PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks */
#define RCC_PLLCFGR_PLLQ_MASK       0xF000000u
#define RCC_PLLCFGR_PLLQ_SHIFT      24u
#define RCC_PLLCFGR_PLLQ_WIDTH      4u
#define RCC_PLLCFGR_PLLQ(x)         (((uint32)(((uint32)(x))<<RCC_PLLCFGR_PLLQ_SHIFT))&RCC_PLLCFGR_PLLQ_MASK)


/**
 * RCC clock configuration register (RCC_CFGR)
 */
/* Bits 1:0 SW: System clock switch */
#define RCC_CFGR_SW_MASK        0x3u
#define RCC_CFGR_SW_SHIFT       0u
#define RCC_CFGR_SW_WIDTH       2u
#define RCC_CFGR_SW(x)          (((uint32)(((uint32)(x))<<RCC_CFGR_SW_SHIFT))&RCC_CFGR_SW_MASK)

/* Bits 3:2 SWS: System clock switch status */
#define RCC_CFGR_SWS_MASK       0xCu
#define RCC_CFGR_SWS_SHIFT      2u
#define RCC_CFGR_SWS_WIDTH      2u
#define RCC_CFGR_SWS(x)         (((uint32)(((uint32)(x))<<RCC_CFGR_SWS_SHIFT))&RCC_CFGR_SWS_MASK)

/* Bits 7:4 HPRE: AHB prescaler */
#define RCC_CFGR_HPRE_MASK      0xF0u
#define RCC_CFGR_HPRE_SHIFT     4u
#define RCC_CFGR_HPRE_WIDTH     2u
#define RCC_CFGR_HPRE(x)        (((uint32)(((uint32)(x))<<RCC_CFGR_HPRE_SHIFT))&RCC_CFGR_HPRE_MASK)

/* Bits 12:10 PPRE1: APB Low speed prescaler (APB1) */
#define RCC_CFGR_PPRE1_MASK     0x1C00u
#define RCC_CFGR_PPRE1_SHIFT    10u
#define RCC_CFGR_PPRE1_WIDTH    3u
#define RCC_CFGR_PPRE1(x)       (((uint32)(((uint32)(x))<<RCC_CFGR_PPRE1_SHIFT))&RCC_CFGR_PPRE1_MASK)

/* Bits 15:13 PPRE2: APB high-speed prescaler (APB2) */
#define RCC_CFGR_PPRE2_MASK     0xE000u
#define RCC_CFGR_PPRE2_SHIFT    13u
#define RCC_CFGR_PPRE2_WIDTH    3u
#define RCC_CFGR_PPRE2(x)       (((uint32)(((uint32)(x))<<RCC_CFGR_PPRE2_SHIFT))&RCC_CFGR_PPRE2_MASK)

/* Bits 20:16 RTCPRE: HSE division factor for RTC clock */
#define RCC_CFGR_RTCPRE_MASK    0x1F0000u
#define RCC_CFGR_RTCPRE_SHIFT   16u
#define RCC_CFGR_RTCPRE_WIDTH   5u
#define RCC_CFGR_RTCPRE(x)      (((uint32)(((uint32)(x))<<RCC_CFGR_RTCPRE_SHIFT))&RCC_CFGR_RTCPRE_MASK)

/* Bits 22:21 MCO1: Microcontroller clock output 1 */
#define RCC_CFGR_MCO1_MASK      0x600000u
#define RCC_CFGR_MCO1_SHIFT     21u
#define RCC_CFGR_MCO1_WIDTH     2u
#define RCC_CFGR_MCO1(x)        (((uint32)(((uint32)(x))<<RCC_CFGR_MCO1_SHIFT))&RCC_CFGR_MCO1_MASK)

/* Bit 23 I2SSRC: I2S clock selection */
#define RCC_CFGR_I2SSRC_MASK    0x800000u
#define RCC_CFGR_I2SSRC_SHIFT   23u
#define RCC_CFGR_I2SSRC_WIDTH   1u
#define RCC_CFGR_I2SSRC(x)      (((uint32)(((uint32)(x))<<RCC_CFGR_I2SSRC_SHIFT))&RCC_CFGR_I2SSRC_MASK)

/* Bits 26:24 MCO1PRE: MCO1 prescaler */
#define RCC_CFGR_MCO1PRE_MASK   0x7000000u
#define RCC_CFGR_MCO1PRE_SHIFT  24u
#define RCC_CFGR_MCO1PRE_WIDTH  3u
#define RCC_CFGR_MCO1PRE(x)     (((uint32)(((uint32)(x))<<RCC_CFGR_MCO1PRE_SHIFT))&RCC_CFGR_MCO1PRE_MASK)

/* Bits 29:27 MCO2PRE: MCO2 prescaler */
#define RCC_CFGR_MCO2PRE_MASK   0x38000000u
#define RCC_CFGR_MCO2PRE_SHIFT  27u
#define RCC_CFGR_MCO2PRE_WIDTH  3u
#define RCC_CFGR_MCO2PRE(x)     (((uint32)(((uint32)(x))<<RCC_CFGR_MCO2PRE_SHIFT))&RCC_CFGR_MCO2PRE_MASK)

/* Bits 31:30 MCO2[1:0]: Microcontroller clock output 2 */
#define RCC_CFGR_MCO2_MASK      0xC0000000u
#define RCC_CFGR_MCO2_SHIFT     30u
#define RCC_CFGR_MCO2_WIDTH     2u
#define RCC_CFGR_MCO2(x)        (((uint32)(((uint32)(x))<<RCC_CFGR_MCO2_SHIFT))&RCC_CFGR_MCO2_MASK)


/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()    		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()			(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()			(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()			(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()			(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()			(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()			(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()			(RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()			(RCC->AHB1ENR |= (1 << 8))


/*
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN() 			(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN() 			(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN() 			(RCC->APB1ENR |= (1 << 23))


/*
 * Clock Enable Macros for SPIx peripheralsbu
 */
#define SPI1_PCLK_EN() 			(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN() 			(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN() 			(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN() 			(RCC->APB2ENR |= (1 << 13))


/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN() 		(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN() 		(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN() 		(RCC->APB1ENR |= (1 << 18))
#define USART4_PCLK_EN()  		(RCC->APB1ENR |= (1 << 19))
#define USART5_PCLK_EN()  		(RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN() 		(RCC->APB1ENR |= (1 << 5))

/*
 * Clock Enable Macros for DMAx peripherals
 */
#define DMA1_CLOCK_MASK			(21) 
#define DMA2_CLOCK_MASK			(22) 
#define DMA1_PCLK_EN() 			(RCC->AHB1ENR |= (1 << DMA1_CLOCK_MASK))
#define DMA2_PCLK_EN() 			(RCC->AHB1ENR |= (1 << DMA2_CLOCK_MASK))

/*
 * Clock Enable Macros for SYSCFG peripheral
 */
#define SYSCFG_PCLK_EN() 		(RCC->APB2ENR |= (1 << 14))


#endif	/* !(__RCC_BASE_H__) */
