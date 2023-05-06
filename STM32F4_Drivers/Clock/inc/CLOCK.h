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
 * @return            - None
 * @Note              -
 */
void Clock_PeripheralControl(ClockPeripheralType ClkPer, Bool_Type EnorDi);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_SetSYSCLKFreq
 * @brief             - Set System Clock Frequency
 * @param[in]         - ExpectFreq      - Expected Frequency (x.000.000 MHz)
 * @return            - Output Frequency (It may be different from Expected Frequency)
 * @Note              -
 */
uint32 Clock_SetSYSCLKFreq(uint32 ExpectFreq);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_SetPeripheralFreq
 * @brief             - Set Clock Frequency for Peripheral
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @param[in]         - ExpectFreq      - Expected Frequency (x.000.000 MHz)
 * @return            - Output Frequency (It may be different from Expected Frequency)
 * @Note              -
 */
uint32 Clock_SetPeripheralFreq(ClockPeripheralType ClkPer, uint32 ExpectFreq);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - Clock_GetPeripheralFreq
 * @brief             - Get Clock Frequency from Peripheral
 * @param[in]         - ClkPer 	 - CLOCK_<PERIPHERAL_NAME>
 * @return            - Output Frequency (It may be different from Expected Frequency)
 * @Note              -
 */
uint32 Clock_GetPeripheralFreq(ClockPeripheralType ClkPer);

#endif /* __CLOCK_H__ */
