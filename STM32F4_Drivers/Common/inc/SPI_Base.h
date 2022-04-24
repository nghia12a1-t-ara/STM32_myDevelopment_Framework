#ifndef __SPI_BASE_H_
#define __SPI_BASE_H_

#include "stm32f4xx.h"

/*
 * peripheral register definition structure for SPI
 */
typedef struct
{
	__vo uint32 CR1;        /*!< TODO,     										Address offset: 0x00 */
	__vo uint32 CR2;        /*!< TODO,     										Address offset: 0x04 */
	__vo uint32 SR;         /*!< TODO,     										Address offset: 0x08 */
	__vo uint32 DR;         /*!< TODO,     										Address offset: 0x0C */
	__vo uint32 CRCPR;      /*!< TODO,     										Address offset: 0x10 */
	__vo uint32 RXCRCR;     /*!< TODO,     										Address offset: 0x14 */
	__vo uint32 TXCRCR;     /*!< TODO,     										Address offset: 0x18 */
	__vo uint32 I2SCFGR;    /*!< TODO,     										Address offset: 0x1C */
	__vo uint32 I2SPR;      /*!< TODO,     										Address offset: 0x20 */
} SPI_Types;

/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 * TODO : Complete for all other peripherals
 */
#define SPI2_BASEADDR					(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR					(APB1PERIPH_BASEADDR + 0x3C00)

#define SPI2  							((SPI_Types*)SPI2_BASEADDR)
#define SPI3  							((SPI_Types*)SPI3_BASEADDR)
/*
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO : Complete for all other peripherals
 */
#define SPI1_BASEADDR					(APB2PERIPH_BASEADDR + 0x3000)

#define SPI1  							((SPI_Types*)SPI1_BASEADDR)
/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA     				 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     				 2
#define SPI_CR1_BR   					 3
#define SPI_CR1_SPE     				 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     				 8
#define SPI_CR1_SSM      				 9
#define SPI_CR1_RXONLY      		 	10
#define SPI_CR1_DFF     			 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   			 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE      			15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE				 	2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE					7


/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8


#endif 	/* !(__SPI_BASE_H_) */
