/**
 * Filename		: RCC_HwAccess.h
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Access to RCC Module Registers
 */

#ifndef __RCC_HWACCESS_H__
#define __RCC_HWACCESS_H__

/* STM32F4 use RCC module for configure Clock */
#include "RCC_Base.h"
#include "CLOCK_Type.h"

/* Private macro -------------------------------------------------------------*/
#define CLOCK_MAX_FREQUENCY         84000000UL
#define CLOCK_HSI_FREQUENCY         16000000UL
#define CLOCK_DEFAULT_FREQUENCY     16000000UL
#define CLOCK_XTAL_FREQUENCY        8000000UL
#define CLOCK_INVALID_FREQUENCY     0UL

/* Type for PLL Configuration */
#define CLOCK_PLLM_MIN              2u
#define CLOCK_PLLM_MAX              63u
#define CLOCK_PLLN_MIN              192u
#define CLOCK_PLLN_MAX              432u
#define CLOCK_PLLP_MIN              2u
#define CLOCK_PLLP_MAX              8u
#define CLOCK_PLLQ_MIN              2u
#define CLOCK_PLLQ_MAX              15u

/**
 * @fn  Config Source for SYSCLK
 */
__STATIC_INLINE void Set_SYSCLKSource(ClockSYSCLKSrcType SYSCLKSource)
{
    /* Clear SW[1:0] bits */
    RCC->CFGR &= ~RCC_CFGR_SW_MASK;

    /* Set Clock Source for SYSCLK */
    RCC->CFGR |= RCC_CFGR_SW((uint8)SYSCLKSource);
}

/**
 * @fn  Get Source of SYSCLK
 */
__STATIC_INLINE ClockSYSCLKSrcType Get_SYSCLKSource(void)
{
    /* Get Clock Source for SYSCLK */
    return ( (RCC->CFGR & RCC_CFGR_SWS_MASK) >> RCC_CFGR_SWS_SHIFT );
}

/**
 * @fn  Set AHB Prescaler from SYSCLK
 */
__STATIC_INLINE void Set_AHBPrescaler(ClockAHBPrescalerType AHBPrescaler)
{
    RCC->CFGR &= ~RCC_CFGR_HPRE_MASK;
    RCC->CFGR |= RCC_CFGR_HPRE((uint8)AHBPrescaler);
}
__STATIC_INLINE uint16 Get_AHBPrescaler(void)
{
    uint16 AHBPrescaler;
    switch ( (RCC->CFGR & RCC_CFGR_HPRE_MASK) >> RCC_CFGR_HPRE_SHIFT )
    {
        case CLOCK_AHB_PRESCALER_1:
            AHBPrescaler = 1u;
            break;
        case CLOCK_AHB_PRESCALER_2:
            AHBPrescaler = 2u;
            break;
        case CLOCK_AHB_PRESCALER_4:
            AHBPrescaler = 4u;
            break;
        case CLOCK_AHB_PRESCALER_8:
            AHBPrescaler = 8u;
            break;
        case CLOCK_AHB_PRESCALER_16:
            AHBPrescaler = 16u;
            break;
        case CLOCK_AHB_PRESCALER_64:
            AHBPrescaler = 64u;
            break;
        case CLOCK_AHB_PRESCALER_128:
            AHBPrescaler = 128u;
            break;
        case CLOCK_AHB_PRESCALER_256:
            AHBPrescaler = 256u;
            break;
        case CLOCK_AHB_PRESCALER_512:
            AHBPrescaler = 512u;
            break;
        default:
            AHBPrescaler = 1;
            break;
    }
    return AHBPrescaler;
}

/**
 * @fn  Set APB1 Prescaler from AHB Bus
 */
__STATIC_INLINE void Set_APB1Prescaler(ClockAPBPrescalerType APBPrecaler)
{
    RCC->CFGR &= ~RCC_CFGR_PPRE1_MASK;
    RCC->CFGR |= RCC_CFGR_PPRE1((uint8)APBPrecaler);
}
__STATIC_INLINE uint8 Get_APB1Prescaler(void)
{
    uint8 APBPrescaler;
    switch ( (RCC->CFGR & RCC_CFGR_PPRE1_MASK) >> RCC_CFGR_PPRE1_SHIFT )
    {
        case CLOCK_APB_PRESCALER_1:
            APBPrescaler = 1;
            break;
        case CLOCK_APB_PRESCALER_2:
            APBPrescaler = 2;
            break;
        case CLOCK_APB_PRESCALER_4:
            APBPrescaler = 4;
            break;
        case CLOCK_APB_PRESCALER_8:
            APBPrescaler = 8;
            break;
        case CLOCK_APB_PRESCALER_16:
            APBPrescaler = 16;
            break;
    }
    return APBPrescaler;
}

/**
 * @fn  Set APB2 Prescaler from AHB Bus
 */
__STATIC_INLINE void Set_APB2Prescaler(ClockAPBPrescalerType APBPrecaler)
{
    RCC->CFGR &= ~RCC_CFGR_PPRE2_MASK;
    RCC->CFGR |= RCC_CFGR_PPRE2((uint8)APBPrecaler);
}
__STATIC_INLINE uint8 Get_APB2Prescaler(void)
{
    uint8 APBPrescaler;
    switch ( (RCC->CFGR & RCC_CFGR_PPRE2_MASK) >> RCC_CFGR_PPRE2_SHIFT )
    {
        case CLOCK_APB_PRESCALER_1:
            APBPrescaler = 1;
            break;
        case CLOCK_APB_PRESCALER_2:
            APBPrescaler = 2;
            break;
        case CLOCK_APB_PRESCALER_4:
            APBPrescaler = 4;
            break;
        case CLOCK_APB_PRESCALER_8:
            APBPrescaler = 8;
            break;
        case CLOCK_APB_PRESCALER_16:
            APBPrescaler = 16;
            break;
    }
    return APBPrescaler;
}

/**
 * @fn  Convert integer to Prescaler Enum
 */
__STATIC_INLINE ClockAHBPrescalerType Integer2AHBPrescaler(uint16 PresNum)
{
    ClockAHBPrescalerType AHBPrescaler;
    switch (PresNum)
    {
        case 1:
            AHBPrescaler = CLOCK_AHB_PRESCALER_1;
            break;
        case 2:
            AHBPrescaler = CLOCK_AHB_PRESCALER_2;
            break;
        case 4:
            AHBPrescaler = CLOCK_AHB_PRESCALER_4;
            break;
        case 8:
            AHBPrescaler = CLOCK_AHB_PRESCALER_8;
            break;
        case 16:
            AHBPrescaler = CLOCK_AHB_PRESCALER_16;
            break;
        case 64:
            AHBPrescaler = CLOCK_AHB_PRESCALER_64;
            break;
        case 128:
            AHBPrescaler = CLOCK_AHB_PRESCALER_128;
            break;
        case 256:
            AHBPrescaler = CLOCK_AHB_PRESCALER_256;
            break;
        default:
            AHBPrescaler = CLOCK_AHB_PRESCALER_1;
            break;
    }
    return AHBPrescaler;
}
__STATIC_INLINE ClockAPBPrescalerType Integer2APBPrescaler(uint8 PresNum)
{
    ClockAPBPrescalerType APBPrescaler;
    switch (PresNum)
    {
        case 1:
            APBPrescaler = CLOCK_APB_PRESCALER_1;
            break;
        case 2:
            APBPrescaler = CLOCK_APB_PRESCALER_2;
            break;
        case 4:
            APBPrescaler = CLOCK_APB_PRESCALER_4;
            break;
        case 8:
            APBPrescaler = CLOCK_APB_PRESCALER_8;
            break;
        case 16:
            APBPrescaler = CLOCK_APB_PRESCALER_16;
            break;
        default:
            APBPrescaler = CLOCK_APB_PRESCALER_1;
            break;
    }
    return APBPrescaler;
}

/**
 * @fn  Get all bus clock frequency from SYSCLK
 */
__STATIC_INLINE ClockSourceType Get_AllClockfromSYSCLK(uint32 sysclk)
{
    ClockSourceType AllClock;
    AllClock.SYSCLK_FREQ    = sysclk;
    AllClock.HCLK_FREQ      = sysclk / Get_AHBPrescaler();
    AllClock.PCLK1_FREQ     = AllClock.HCLK_FREQ / Get_APB1Prescaler();
    AllClock.PCLK2_FREQ     = AllClock.PCLK1_FREQ / Get_APB2Prescaler();
    return AllClock;
}

/**
 * @fn  Set PLL Clock Configuration
 */
__STATIC_INLINE void Set_PLLConfig(ClockPLLSrcType RCC_PLLSource, uint32 PLLM, uint32 PLLN, uint32 PLLP, uint32 PLLQ)
{
    /* SYSCLK = (HSE_VALUE or HSI_VALUE) / PLLM * PLLN / PLLP */ 
    RCC->PLLCFGR = (PLLM << RCC_PLLCFGR_PLLM_SHIFT)
                 | (PLLN << RCC_PLLCFGR_PLLN_SHIFT)
                 | (((PLLP >> 1) - 1) << RCC_PLLCFGR_PLLP_SHIFT)
                 | (PLLQ << RCC_PLLCFGR_PLLQ_SHIFT)
                 | ((uint8)RCC_PLLSource << RCC_PLLCFGR_PLLSRC_SHIFT);
}

/**
 * @fn  Get PLL Clock Frequency
 */
__STATIC_INLINE uint32 Get_PLLFrequency(void)
{
    /*  PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
     *  SYSCLK = PLL_VCO / PLLP
     */ 
    uint32 pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;
    pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_MASK) ? CLOCK_XTAL_FREQUENCY : CLOCK_HSI_FREQUENCY;
    pllm = (RCC->PLLCFGR & RCC_PLLCFGR_PLLM_MASK) >> RCC_PLLCFGR_PLLM_SHIFT;
    pllvco = (pllsource * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN_MASK) >> RCC_PLLCFGR_PLLN_SHIFT)) / pllm;
    pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP_MASK) >> RCC_PLLCFGR_PLLP_SHIFT) + 1 ) << 1;
    return (pllvco/pllp);
}

/**************************************************************************/
/************************ Clock for Peripherals ***************************/
/**************************************************************************/
/**
 * @fn  Enable/Disable Clock for AHB1 Peripherals
 */
__STATIC_INLINE ClockPeripheralBusType Check_PeripheralBus(ClockPeripheralType ClkPer)
{
    ClockPeripheralBusType ClockBusType;
    
    if ( (ClkPer >= 0) && (ClkPer <= 31) )
    {
        ClockBusType = CLOCK_PER_BUS_AHB1;
    }
    else if ( (ClkPer >= 32) && (ClkPer <= 63) )
    {
        ClockBusType = CLOCK_PER_BUS_AHB2;
    }
    else if ( (ClkPer >= 64) && (ClkPer <= 95) )
    {
        ClockBusType = CLOCK_PER_BUS_APB1;
    }
    else
    {
        ClockBusType = CLOCK_PER_BUS_APB2;
    }
    return ClockBusType;
}

/**
 * @fn  Enable/Disable Clock for AHB1 Peripherals
 */
__STATIC_INLINE void Set_AHB1Peripheral(ClockPeripheralType ClkPer, Bool_Type EnorDi)
{
    uint8 bitpos = (uint8)ClkPer - CLOCK_AHB1_POSITION_OFFSET;
    
    if (ENABLE == EnorDi)
    {
        RCC->AHB1ENR |= (1 << bitpos);
    }
    else
    {
        RCC->AHB1RSTR |= (1 << bitpos);
    }
}
/**
 * @fn  Enable/Disable Clock for AHB2 Peripherals
 */
__STATIC_INLINE void Set_AHB2Peripheral(ClockPeripheralType ClkPer, Bool_Type EnorDi)
{
    uint8 bitpos = (uint8)ClkPer - CLOCK_AHB2_POSITION_OFFSET;
    
    if (ENABLE == EnorDi)
    {
        RCC->AHB2ENR |= (1 << bitpos);
    }
    else
    {
        RCC->AHB2RSTR |= (1 << bitpos);
    }
}
/**
 * @fn  Enable/Disable Clock for APB1 Peripherals
 */
__STATIC_INLINE void Set_APB1Peripheral(ClockPeripheralType ClkPer, Bool_Type EnorDi)
{
    uint8 bitpos = (uint8)ClkPer - CLOCK_APB1_POSITION_OFFSET;
    
    if (ENABLE == EnorDi)
    {
        RCC->APB1ENR |= (1 << bitpos);
    }
    else
    {
        RCC->APB1RSTR |= (1 << bitpos);
    }
}
/**
 * @fn  Enable/Disable Clock for APB2 Peripherals
 */
__STATIC_INLINE void Set_APB2Peripheral(ClockPeripheralType ClkPer, Bool_Type EnorDi)
{
    uint8 bitpos = (uint8)ClkPer - CLOCK_APB2_POSITION_OFFSET;
    
    if (ENABLE == EnorDi)
    {
        RCC->APB2ENR |= (1 << bitpos);
    }
    else
    {
        RCC->APB2RSTR |= (1 << bitpos);
    }
}

#endif /* __RCC_HWACCESS_H__ */
