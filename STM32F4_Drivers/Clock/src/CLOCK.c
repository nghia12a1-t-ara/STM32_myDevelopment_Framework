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
static ClockErrorType Clock_ValidateFrequency(uint32 frequency);
static ClockErrorType Clock_ValidatePrescaler(uint32 prescaler);

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
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_PeripheralControl(ClockPeripheralType ClkPer, Bool_Type EnorDi)
{
    ClockPeripheralBusType BusType;
    
    if (ClkPer >= CLOCK_TIM11 + 1)
    {
        return CLOCK_ERROR_INVALID_PARAM;
    }
    
    /* Get Clock Peripheral Bus Type From ClkPer */
    BusType = Check_PeripheralBus(ClkPer);
    
    /* Set Enable/Disable Peripheral Clock */
    (*Set_PeripheralClock[BusType])(ClkPer, EnorDi);
    
    return CLOCK_OK;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_SetSYSCLKFreq
 * @brief             - Set System Clock Frequency
 * @param[in]         - ExpectFreq      - Expected Frequency (x.000.000 MHz)
 * @param[out]        - pActualFreq     - Pointer to store actual frequency
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_SetSYSCLKFreq(uint32 ExpectFreq, uint32* pActualFreq)
{
    ClockPLLConfigResult pllResult;
    ClockErrorType error;
    uint32 OutSysClk = CLOCK_INVALID_FREQUENCY;
    
    if (pActualFreq == NULL)
    {
        return CLOCK_ERROR_INVALID_PARAM;
    }
    
    error = Clock_ValidateFrequency(ExpectFreq);
    if (error != CLOCK_OK)
    {
        *pActualFreq = CLOCK_INVALID_FREQUENCY;
        return error;
    }
    
    error = Clock_CalculateOptimalPLL(ExpectFreq, &pllResult);
    if (error != CLOCK_OK)
    {
        *pActualFreq = CLOCK_INVALID_FREQUENCY;
        return error;
    }
    
    /* Need use PLL to multiple the frequency - input = HSI */
    Set_SYSCLKSource(CLOCK_SYSCLK_SOURCE_PLL);
    
    Set_PLLConfig(CLOCK_PLL_SOURCE_HSI, pllResult.PLLM, pllResult.PLLN, pllResult.PLLP, CLOCK_PLLQ_MIN);
    
    error = Clock_WaitPLLReady(CLOCK_PLL_TIMEOUT_VALUE);
    if (error != CLOCK_OK)
    {
        *pActualFreq = CLOCK_INVALID_FREQUENCY;
        return error;
    }
    
    /* Get & Verify current SYSCLK Frequency */
    OutSysClk = Get_PLLFrequency();
    
    if (OutSysClk > (ExpectFreq + CLOCK_FREQ_TOLERANCE) || 
        OutSysClk < (ExpectFreq - CLOCK_FREQ_TOLERANCE))
    {
        *pActualFreq = OutSysClk;
        return CLOCK_ERROR_PLL_CONFIG;
    }
    
    /* Get all clock source frequency to private Variable */
    s_ClockFreq = Get_AllClockfromSYSCLK(OutSysClk);
    
    *pActualFreq = OutSysClk;
    return CLOCK_OK;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_SetPeripheralFreq
 * @brief             - Set Clock Frequency for Peripheral
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @param[in]         - ExpectFreq      - Expected Frequency (x.000.000 MHz)
 * @param[out]        - pActualFreq     - Pointer to store actual frequency
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_SetPeripheralFreq(ClockPeripheralType ClkPer, uint32 ExpectFreq, uint32* pActualFreq)
{
    ClockPeripheralBusType BusType;
    uint32 SysClock = Clock_GetSYSCLKFrequency();
    uint8 AHBDiv, APBDiv;
    uint32 AHBFreq;
    uint32 OutPerFreq = CLOCK_INVALID_FREQUENCY;
    ClockErrorType error;
    
    if (pActualFreq == NULL)
    {
        return CLOCK_ERROR_INVALID_PARAM;
    }
    
    /* Check Invalid Parameter - Expected Frequency too big */
    if ( ExpectFreq > SysClock )
    {
        *pActualFreq = CLOCK_INVALID_FREQUENCY;
        return CLOCK_ERROR_INVALID_FREQ;
    }
    
    /* Calculate Prescaler for AHB Bus */
    AHBDiv = SysClock / ExpectFreq;
    
    /* Get Clock Peripheral Bus Type From ClkPer */
    BusType = Check_PeripheralBus(ClkPer);
    
    error = Clock_ValidatePrescaler(AHBDiv);
    if (error != CLOCK_OK)
    {
        *pActualFreq = CLOCK_INVALID_FREQUENCY;
        return error;
    }
    
    /* Calculate Prescaler for APB Bus */
    AHBFreq = Clock_GetAHBFrequency();
    APBDiv = AHBFreq / ExpectFreq;
    
    error = Clock_ValidatePrescaler(APBDiv);
    if (error != CLOCK_OK)
    {
        *pActualFreq = CLOCK_INVALID_FREQUENCY;
        return error;
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
            *pActualFreq = CLOCK_INVALID_FREQUENCY;
            return CLOCK_ERROR_INVALID_PARAM;
    }

    *pActualFreq = OutPerFreq;
    return CLOCK_OK;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetPeripheralFreq
 * @brief             - Get Clock Frequency from Peripheral
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @param[out]        - pFreq          - Pointer to store frequency
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_GetPeripheralFreq(ClockPeripheralType ClkPer, uint32* pFreq)
{
    ClockPeripheralBusType BusType;
    
    if (pFreq == NULL)
    {
        return CLOCK_ERROR_INVALID_PARAM;
    }
    
    if (ClkPer >= CLOCK_TIM11 + 1)
    {
        *pFreq = CLOCK_INVALID_FREQUENCY;
        return CLOCK_ERROR_INVALID_PARAM;
    }
    
    /* Get Clock Peripheral Bus Type From ClkPer */
    BusType = Check_PeripheralBus(ClkPer);
    
    /* Get Frequency from each Bus */
    *pFreq = (*Clock_GetBusFreq[BusType])();
    
    return CLOCK_OK;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_CalculateOptimalPLL
 * @brief             - Calculate optimal PLL parameters for target frequency
 * @param[in]         - targetFreq     - Target frequency in Hz
 * @param[out]        - pResult        - Pointer to PLL configuration result
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_CalculateOptimalPLL(uint32 targetFreq, ClockPLLConfigResult* pResult)
{
    uint32 m, targetMHz;
    
    if (pResult == NULL)
    {
        return CLOCK_ERROR_INVALID_PARAM;
    }
    
    if ((0 != (targetFreq % CLOCK_FREQ_DIVIDER)) || (targetFreq > CLOCK_MAX_FREQUENCY))
    {
        pResult->error = CLOCK_ERROR_INVALID_FREQ;
        return CLOCK_ERROR_INVALID_FREQ;
    }
    
    targetMHz = targetFreq / CLOCK_FREQ_DIVIDER;
    pResult->PLLP = CLOCK_PLLP_MAX;
    
    for (m = CLOCK_PLLM_MIN; m <= CLOCK_PLLM_MAX; m += 2)
    {
        uint32 plln_candidate = targetMHz * (m / 2);
        
        if ((plln_candidate >= (uint32)CLOCK_PLLN_MIN) && 
            (plln_candidate <= (uint32)CLOCK_PLLN_MAX))
        {
            pResult->PLLN = plln_candidate;
            pResult->PLLM = m;
            pResult->actualFreq = targetFreq;
            pResult->error = CLOCK_OK;
            return CLOCK_OK;
        }
    }
    
    pResult->error = CLOCK_ERROR_PLL_CONFIG;
    return CLOCK_ERROR_PLL_CONFIG;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_WaitPLLReady
 * @brief             - Wait for PLL to be ready with timeout
 * @param[in]         - timeout        - Timeout value in loops
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_WaitPLLReady(uint32 timeout)
{
    uint32 timeoutCounter = timeout;
    
    while (!(RCC->CR & RCC_CR_PLLRDY) && timeoutCounter > 0)
    {
        timeoutCounter--;
    }
    
    if (timeoutCounter == 0)
    {
        return CLOCK_ERROR_TIMEOUT;
    }
    
    return CLOCK_OK;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_ValidateFrequency
 * @brief             - Validate input frequency
 * @param[in]         - frequency      - Frequency to validate
 * @return            - ClockErrorType
 * @Note              - @Private Function
 */
static ClockErrorType Clock_ValidateFrequency(uint32 frequency)
{
    if ((0 != (frequency % CLOCK_FREQ_DIVIDER)) || (frequency > CLOCK_MAX_FREQUENCY))
    {
        return CLOCK_ERROR_INVALID_FREQ;
    }
    return CLOCK_OK;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_ValidatePrescaler
 * @brief             - Validate prescaler value (must be power of 2)
 * @param[in]         - prescaler      - Prescaler to validate
 * @return            - ClockErrorType
 * @Note              - @Private Function
 */
static ClockErrorType Clock_ValidatePrescaler(uint32 prescaler)
{
    if (0 != (prescaler & (prescaler - 1)))
    {
        return CLOCK_ERROR_PRESCALER;
    }
    return CLOCK_OK;
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
 * @fn      		  - Clock_GetAHBFrequency
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
