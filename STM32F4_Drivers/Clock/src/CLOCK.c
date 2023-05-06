/**
 * Filename		: CLOCK.c
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Clock driver
 */

#include "CLOCK.h"
#include "RCC_HwAccess.h"

/*****************************************************************************************/
/******************************** PRIVATE FUNCTIONS PROTOTYPES ***************************/
static uint32 Clock_GetSYSCLKFrequency(void);
static uint32 Clock_GetAHBFrequency(void);
static uint32 Clock_GetAPB1Frequency(void);
static uint32 Clock_GetAPB2Frequency(void);

/*****************************************************************************************/
/********************************* PRIVATE VARIABLES *************************************/
/*
 * @brief	Function pointer to Clock Bus Peripheral set Enable/Disable
 */
static void (*Set_PeripheralClock[])(ClockPeripheralType, Bool_Type) = {
   [CLOCK_PER_BUS_AHB1] = Set_AHB1Peripheral,
   [CLOCK_PER_BUS_AHB2] = Set_AHB2Peripheral,
   [CLOCK_PER_BUS_APB1] = Set_APB1Peripheral,
   [CLOCK_PER_BUS_APB2] = Set_APB2Peripheral,
};
/*
 * @brief	Function pointer to Get Bus Clock Frequency
 */
static uint32 (*Clock_GetBusFreq[])(void) = {
   [CLOCK_PER_BUS_AHB1] = Clock_GetAHBFrequency,
   [CLOCK_PER_BUS_AHB2] = Clock_GetAHBFrequency,
   [CLOCK_PER_BUS_APB1] = Clock_GetAPB1Frequency,
   [CLOCK_PER_BUS_APB2] = Clock_GetAPB2Frequency,
};

/*
 * @brief	Clock Frequency for all bus
 */
static ClockSourceType s_ClockFreq = {
    .SYSCLK_FREQ    = CLOCK_INVALID_FREQUENCY,
    .HCLK_FREQ      = CLOCK_INVALID_FREQUENCY,
    .PCLK1_FREQ     = CLOCK_INVALID_FREQUENCY,
    .PCLK2_FREQ     = CLOCK_INVALID_FREQUENCY
};

/*****************************************************************************************/

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_PeripheralControl
 * @brief             - Enable/Disable Peripheral Clock
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @param[in]         - EnorDi   - Enable/Disable
 * @return            - None
 * @Note              -
 */
void Clock_PeripheralControl(ClockPeripheralType ClkPer, Bool_Type EnorDi)
{
    ClockPeripheralBusType BusType;
    
    /* Get Clock Peripheral Bus Type From ClkPer */
    BusType = Check_PeripheralBus(ClkPer);
    
    /* Set Enable/Disable Peripheral Clock */
    (*Set_PeripheralClock[BusType])(ClkPer, EnorDi);
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_SetSYSCLKFreq
 * @brief             - Set System Clock Frequency
 * @param[in]         - ExpectFreq      - Expected Frequency (x.000.000 MHz)
 * @return            - Output Frequency (It may be different from Expected Frequency)
 * @Note              -
 */
uint32 Clock_SetSYSCLKFreq(uint32 ExpectFreq)
{
    uint32 PLLM, m, PLLN, PLLP;
    uint32 OutSysClk = CLOCK_INVALID_FREQUENCY;
    
    if ( (0 == (ExpectFreq % 1000000UL)) &&
         (ExpectFreq <= CLOCK_MAX_FREQUENCY) )
    {
        /* Need use PLL to multiple the frequency - input = HSI
         * SYSCLK = (HSI_VALUE) / PLLM * PLLN / PLLP
         */
        Set_SYSCLKSource(CLOCK_SYSCLK_SOURCE_PLL);
        
        /* ExpectFreq/1000000 = 20 = SYSCLK = (16) / PLLM * 400 / 8
         * Freq * PLLM / 2 = PLLN
         */
        ExpectFreq /= 1000000UL;
        PLLP = CLOCK_PLLP_MAX;
        for (m = CLOCK_PLLM_MIN; m <= CLOCK_PLLM_MAX; m+=2)
        {
            if ( ((ExpectFreq * (m / 2)) >= (uint32)CLOCK_PLLN_MIN) &&
                 ((ExpectFreq * (m / 2)) <= (uint32)CLOCK_PLLN_MAX) )
            {
                PLLN = ExpectFreq * (m / 2);
                PLLM = m;
                break;
            }
        }
        
        Set_PLLConfig(CLOCK_PLL_SOURCE_HSI, PLLM, PLLN, PLLP, CLOCK_PLLQ_MIN);
        
        /* Get & Verify current SYSCLK Frequency */
        OutSysClk = Get_PLLFrequency();
        /* Get all clock source frequency to private Variable */
        s_ClockFreq = Get_AllClockfromSYSCLK(OutSysClk);
    }
    else
    {
        OutSysClk = CLOCK_INVALID_FREQUENCY;
    }
    
    return OutSysClk;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_SetPeripheralFreq
 * @brief             - Set Clock Frequency for Peripheral
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @param[in]         - ExpectFreq      - Expected Frequency (x.000.000 MHz)
 * @return            - Output Frequency (It may be different from Expected Frequency)
 * @Note              -
 */
uint32 Clock_SetPeripheralFreq(ClockPeripheralType ClkPer, uint32 ExpectFreq)
{
    ClockPeripheralBusType BusType;
    uint32 SysClock = Clock_GetSYSCLKFrequency();
    uint8 AHBDiv, APBDiv;
    uint32 AHBFreq;
    uint32 OutPerFreq = CLOCK_INVALID_FREQUENCY;
    
    /* Check Invalid Parameter - Expected Frequency too big */
    if ( ExpectFreq > SysClock )
    {
        return CLOCK_INVALID_FREQUENCY;
    }
    else
    {
        /* Calculate Prescaler for AHB Bus */
        AHBDiv = SysClock / ExpectFreq;
    }
    
    /* Get Clock Peripheral Bus Type From ClkPer */
    BusType = Check_PeripheralBus(ClkPer);
    
    /* Check if prescaler is not power of 2 */
    if ( 0 != (AHBDiv & (AHBDiv - 1)) )
    {
        return CLOCK_INVALID_FREQUENCY;
    }
    else
    {
        /* Calculate Prescaler for APB Bus */
        AHBFreq = Clock_GetAHBFrequency();
        APBDiv = AHBFreq / ExpectFreq;
    }
    
    /* Check if prescaler is not power of 2 */
    if ( 0 != (APBDiv & (APBDiv - 1)) )
    {
        return CLOCK_INVALID_FREQUENCY;
    }
    
    /* Setting Prescaler for calculate Frequency */
    switch (BusType)
    {
        case CLOCK_PER_BUS_AHB1:
        case CLOCK_PER_BUS_AHB2:
            Set_AHBPrescaler(Integer2AHBPrescaler(AHBDiv));
            OutPerFreq = SysClock / Get_AHBPrescaler();
            s_ClockFreq.HCLK_FREQ = OutPerFreq;
            break;
        case CLOCK_PER_BUS_APB1:
            Set_APB1Prescaler(Integer2APBPrescaler(APBDiv));
            OutPerFreq = AHBFreq / Get_APB1Prescaler();
            s_ClockFreq.PCLK1_FREQ = OutPerFreq;
            break;
        case CLOCK_PER_BUS_APB2:
            Set_APB2Prescaler(Integer2APBPrescaler(APBDiv));
            OutPerFreq = AHBFreq / Get_APB2Prescaler();
            s_ClockFreq.PCLK2_FREQ = OutPerFreq;
            break;
        default:
            break;
    }

    return OutPerFreq;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetPeripheralFreq
 * @brief             - Get Clock Frequency from Peripheral
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @return            - Output Frequency (It may be different from Expected Frequency)
 * @Note              -
 */
uint32 Clock_GetPeripheralFreq(ClockPeripheralType ClkPer)
{
    ClockPeripheralBusType BusType;
    uint32 OutPerFreq = CLOCK_INVALID_FREQUENCY;
    
    /* Get Clock Peripheral Bus Type From ClkPer */
    BusType = Check_PeripheralBus(ClkPer);
    
    /* Get Frequency from each Bus */
    OutPerFreq = (*Clock_GetBusFreq[BusType])();
    
    return OutPerFreq;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetSYSCLKFrequency
 * @brief             - Get System Clock Frequency
 * @param[in]         - N/A
 * @return            - SYSCLK Frequency
 * @Note              - @Private Function
 */
static uint32 Clock_GetSYSCLKFrequency(void)
{
    /* Follow Private Variable if it's valid */
    if ( CLOCK_INVALID_FREQUENCY != s_ClockFreq.SYSCLK_FREQ )
    {
        return s_ClockFreq.SYSCLK_FREQ;
    }
    
    uint32 SYSCLKFreq = CLOCK_HSI_FREQUENCY;
    ClockSYSCLKSrcType SYSCLKSource = Get_SYSCLKSource();
    switch (SYSCLKSource)
    {
        case CLOCK_SYSCLK_SOURCE_HSI:
            SYSCLKFreq = CLOCK_HSI_FREQUENCY;
            break;
        case CLOCK_SYSCLK_SOURCE_HSE:
            SYSCLKFreq = CLOCK_XTAL_FREQUENCY;
            break;
        case CLOCK_SYSCLK_SOURCE_PLL:
            SYSCLKFreq = Get_PLLFrequency();
            break;
        default:
            break;
    }
    
    /* Get all clock source frequency to private Variable */
    s_ClockFreq = Get_AllClockfromSYSCLK(SYSCLKFreq);
    
    return SYSCLKFreq;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetAHB1Frequency
 * @brief             - Get AHB Clock Frequency
 * @param[in]         - N/A
 * @return            - AHB Bus Frequency
 * @Note              - @Private Function
 */
static uint32 Clock_GetAHBFrequency(void)
{
    uint32 SysClk = Clock_GetSYSCLKFrequency();
    uint32 Hclk;
    
    /* Follow Private Variable if it's valid */
    if ( CLOCK_INVALID_FREQUENCY != s_ClockFreq.HCLK_FREQ )
    {
        Hclk = s_ClockFreq.HCLK_FREQ;
    }
    else
    {
        Hclk = SysClk / Get_AHBPrescaler();
        s_ClockFreq.HCLK_FREQ = Hclk;
    }
    return Hclk;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetAPB1Frequency
 * @brief             - Get APB1 Clock Frequency
 * @param[in]         - N/A
 * @return            - AHB1 Bus Frequency
 * @Note              - @Private Function
 */
static uint32 Clock_GetAPB1Frequency(void)
{
    uint32 Hclk = Clock_GetAHBFrequency();
    uint32 APB1Freq;
    
    /* Follow Private Variable if it's valid */
    if ( CLOCK_INVALID_FREQUENCY != s_ClockFreq.PCLK1_FREQ )
    {
        APB1Freq = s_ClockFreq.PCLK1_FREQ;
    }
    else
    {
        APB1Freq = Hclk / Get_APB1Prescaler();
        s_ClockFreq.PCLK1_FREQ = APB1Freq;
    }
    return APB1Freq;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetAPB2Frequency
 * @brief             - Get APB2 Clock Frequency
 * @param[in]         - N/A
 * @return            - AHB2 Bus Frequency
 * @Note              - @Private Function
 */
static uint32 Clock_GetAPB2Frequency(void)
{
    uint32 Hclk = Clock_GetAHBFrequency();
    uint32 APB2Freq;
    
    /* Follow Private Variable if it's valid */
    if ( CLOCK_INVALID_FREQUENCY != s_ClockFreq.PCLK2_FREQ )
    {
        APB2Freq = s_ClockFreq.PCLK2_FREQ;
    }
    else
    {
        APB2Freq = Hclk / Get_APB2Prescaler();
        s_ClockFreq.PCLK2_FREQ = APB2Freq;
    }
    return APB2Freq;
}
