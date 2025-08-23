/**
 * Filename		: CLOCK.h
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Clock driver header file
 */

#ifndef __CLOCK_H__
#define __CLOCK_H__

/* STM32F4 use RCC module for configure Clock */
#include "RCC_Base.h"
#include "Clock_Type.h"

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_PeripheralControl
 * @brief             - Enable/Disable Peripheral Clock
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @param[in]         - EnorDi   - Enable/Disable
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_PeripheralControl(ClockPeripheralType ClkPer, Bool_Type EnorDi);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_SetSYSCLKFreq
 * @brief             - Set System Clock Frequency
 * @param[in]         - ExpectFreq      - Expected Frequency (x.000.000 MHz)
 * @param[out]        - pActualFreq     - Pointer to store actual frequency
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_SetSYSCLKFreq(uint32 ExpectFreq, uint32* pActualFreq);

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
ClockErrorType Clock_SetPeripheralFreq(ClockPeripheralType ClkPer, uint32 ExpectFreq, uint32* pActualFreq);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetPeripheralFreq
 * @brief             - Get Clock Frequency from Peripheral
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @param[out]        - pFreq          - Pointer to store frequency
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_GetPeripheralFreq(ClockPeripheralType ClkPer, uint32* pFreq);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_CalculateOptimalPLL
 * @brief             - Calculate optimal PLL parameters for target frequency
 * @param[in]         - targetFreq     - Target frequency in Hz
 * @param[out]        - pResult        - Pointer to PLL configuration result
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_CalculateOptimalPLL(uint32 targetFreq, ClockPLLConfigResult* pResult);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_WaitPLLReady
 * @brief             - Wait for PLL to be ready with timeout
 * @param[in]         - timeout        - Timeout value in loops
 * @return            - ClockErrorType
 * @Note              -
 */
ClockErrorType Clock_WaitPLLReady(uint32 timeout);

#endif /* __CLOCK_H__ */
