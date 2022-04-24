#ifndef __USART_BASE_H_
#define __USART_BASE_H_

#include "stm32f4xx.h"

/*
 * peripheral register definition structure for USART
 */
typedef struct
{
	__vo uint32 SR;         /*!< TODO,     										Address offset: 0x00 */
	__vo uint32 DR;         /*!< TODO,     										Address offset: 0x04 */
	__vo uint32 BRR;        /*!< TODO,     										Address offset: 0x08 */
	__vo uint32 CR1;        /*!< TODO,     										Address offset: 0x0C */
	__vo uint32 CR2;        /*!< TODO,     										Address offset: 0x10 */
	__vo uint32 CR3;        /*!< TODO,     										Address offset: 0x14 */
	__vo uint32 GTPR;       /*!< TODO,     										Address offset: 0x18 */
} USART_Types;


/*
 * Base addresses of peripherals which are hanging on APB1 bus
 * TODO : Complete for all other peripherals
 */
#define USART2_BASEADDR					(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR					(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR					(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR					(APB1PERIPH_BASEADDR + 0x5000)

#define USART2  						((USART_Types*)USART2_BASEADDR)
#define USART3  						((USART_Types*)USART3_BASEADDR)
#define UART4  							((USART_Types*)UART4_BASEADDR)
#define UART5  							((USART_Types*)UART5_BASEADDR)

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO : Complete for all other peripherals
 */
#define USART1_BASEADDR					(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR					(APB2PERIPH_BASEADDR + 0x1400)

#define USART1  						((USART_Types*)USART1_BASEADDR)
#define USART6  						((USART_Types*)USART6_BASEADDR)


/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10
#define USART_CR3_ONEBIT   				11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9


#endif	/* !(__USART_BASE_H_) */
