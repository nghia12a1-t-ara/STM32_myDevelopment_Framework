/*
 * stm32f4xx_rcc_driver.h
 *
 *  Created on: Mar 29, 2019
 *      Author: admin
 */

#ifndef __RCC_H_
#define __RCC_H_

#include "RCC_Base.h"

/* This returns the APB1 clock value */
uint32 RCC_GetPCLK1Value(void);

/* This returns the APB2 clock value */
uint32 RCC_GetPCLK2Value(void);

/* This returns the APB2 clock value */
uint32  RCC_GetPLLOutputClock(void);

#endif /* __RCC_H_ */
