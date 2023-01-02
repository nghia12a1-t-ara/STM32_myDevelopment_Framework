#ifndef __I2C_BASE_H_
#define __I2C_BASE_H_

#include "stm32f4xx.h"

/*
 * peripheral register definition structure for I2C
 */
typedef struct
{
  __vo uint32 CR1;        /*!< TODO,     										Address offset: 0x00 */
  __vo uint32 CR2;        /*!< TODO,     										Address offset: 0x04 */
  __vo uint32 OAR1;       /*!< TODO,     										Address offset: 0x08 */
  __vo uint32 OAR2;       /*!< TODO,     										Address offset: 0x0C */
  __vo uint32 DR;         /*!< TODO,     										Address offset: 0x10 */
  __vo uint32 SR1;        /*!< TODO,     										Address offset: 0x14 */
  __vo uint32 SR2;        /*!< TODO,     										Address offset: 0x18 */
  __vo uint32 CCR;        /*!< TODO,     										Address offset: 0x1C */
  __vo uint32 TRISE;      /*!< TODO,     										Address offset: 0x20 */
  __vo uint32 FLTR;       /*!< TODO,     										Address offset: 0x24 */
} I2C_Type;

/*
 * Base addresses of peripherals which are hanging on APB1 bus
 * TODO : Complete for all other peripherals
 */
#define I2C1_BASEADDR					(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR					(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR					(APB1PERIPH_BASEADDR + 0x5C00)

#define I2C1  							((I2C_Type*)I2C1_BASEADDR)
#define I2C2  							((I2C_Type*)I2C2_BASEADDR)
#define I2C3  							((I2C_Type*)I2C3_BASEADDR)


/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 					8
#define I2C_CR1_STOP  				 	9
#define I2C_CR1_ACK 				 	10
#define I2C_CR1_SWRST  				 	15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ				 	0
#define I2C_CR2_ITERREN				 	8
#define I2C_CR2_ITEVTEN				 	9
#define I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			 	15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15


#endif 	/* !(__I2C_BASE_H_) */
