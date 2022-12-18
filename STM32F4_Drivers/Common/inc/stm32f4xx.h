/*
 * stm3f407xx.h
 *
 *  Created on: Jan 29, 2019
 *      Author: admin
 */

#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_

#include "Std_Types.h"
#include "RCC_Base.h"
#include "NVIC_Base.h"

/**********************************START:Processor Specific Details **********************************/

/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR						0x08000000U   		/*!<explain this macro briefly here  */
#define SRAM1_BASEADDR						0x20000000U  		/*!<explain this macro briefly here  */
#define SRAM2_BASEADDR						0x2001C000U 		/*!<explain this macro briefly here  */
#define ROM_BASEADDR						0x1FFF0000U
#define SRAM 								SRAM1_BASEADDR


/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASEADDR 					0x40000000U
#define APB1PERIPH_BASEADDR					PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR					0x40010000U
#define AHB1PERIPH_BASEADDR					0x40020000U
#define AHB2PERIPH_BASEADDR					0x50000000U


/************************************* Register Access ***********************************/
#define REG_WRITE32(address,data)			*(uint32*)address=data
#define REG_READ32(address)					*(uint32*)address

#endif /* INC_STM32F4XX_H_ */
