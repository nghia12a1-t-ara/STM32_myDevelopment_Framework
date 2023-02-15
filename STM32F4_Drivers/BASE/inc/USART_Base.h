/**
 * Filename		: USART_Base.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Peripheral Access Layer for USART Driver
 */
 
#ifndef __USART_BASE_H_
#define __USART_BASE_H_

#include "stm32f4xx.h"

/**
 * Number of USART Hardware Instance 
 * ++1 because have no USART0
 */
#define USART_INSTANCE_COUNT			(7U)

/**
 * peripheral register definition structure for USART
 */
typedef struct
{
	__vo uint32 SR;         /*!< TODO,   Address offset: 0x00 */
	__vo uint32 DR;         /*!< TODO,   Address offset: 0x04 */
	__vo uint32 BRR;        /*!< TODO,   Address offset: 0x08 */
	__vo uint32 CR1;        /*!< TODO,   Address offset: 0x0C */
	__vo uint32 CR2;        /*!< TODO,   Address offset: 0x10 */
	__vo uint32 CR3;        /*!< TODO,   Address offset: 0x14 */
	__vo uint32 GTPR;       /*!< TODO,   Address offset: 0x18 */
} USART_Type;


/**
 * Base addresses of peripherals which are hanging on APB1 bus
 * TODO : Complete for all other peripherals
 */
#define USART2_BASEADDR					(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR					(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR					(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR					(APB1PERIPH_BASEADDR + 0x5000)

#define USART2  						((USART_Type*)USART2_BASEADDR)
#define USART3  						((USART_Type*)USART3_BASEADDR)
#define UART4  							((USART_Type*)UART4_BASEADDR)
#define UART5  							((USART_Type*)UART5_BASEADDR)

/**
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO : Complete for all other peripherals
 */
#define USART1_BASEADDR					(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR					(APB2PERIPH_BASEADDR + 0x1400)

#define USART1  						((USART_Type*)USART1_BASEADDR)
#define USART6  						((USART_Type*)USART6_BASEADDR)

#define USART_BASE_PTRS					{ NULL_PTR, USART1, USART2, USART3, UART4, UART5, USART6 }

/**
 * Define Supported Instance of USART
 */
#define UART_INSTANCE_1					(1u)
#define UART_INSTANCE_2					(2u)
#define UART_INSTANCE_3					(3u)
#define UART_INSTANCE_4					(4u)
#define UART_INSTANCE_5					(5u)
#define UART_INSTANCE_6					(6u)

/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/**
 * Bit position definitions USART_CR1
 */
/* USART CR1 - Send Break */
#define USART_CR1_SBK_MASK					0x1u
#define USART_CR1_SBK_SHIFT					0u
#define USART_CR1_SBK_WIDTH					1u
#define USART_CR1_SBK(x)					(((uint32_t)(((uint32_t)(x))<<USART_CR1_SBK_SHIFT))&USART_CR1_SBK_MASK)

/* USART CR1 - Receiver wakeup */
#define USART_CR1_RWU_MASK					0x2u
#define USART_CR1_RWU_SHIFT					1u
#define USART_CR1_RWU_WIDTH					1u
#define USART_CR1_RWU(x)					(((uint32_t)(((uint32_t)(x))<<USART_CR1_RWU_SHIFT))&USART_CR1_RWU_MASK)

/* USART CR1 - Receiver enable */
#define USART_CR1_RE_MASK					0x4u
#define USART_CR1_RE_SHIFT					2u
#define USART_CR1_RE_WIDTH					1u
#define USART_CR1_RE(x)						(((uint32_t)(((uint32_t)(x))<<USART_CR1_RE_SHIFT))&USART_CR1_RE_MASK)

/* USART CR1 - Transmitter enable */
#define USART_CR1_TE_MASK 					0x8u
#define USART_CR1_TE_SHIFT 					3u
#define USART_CR1_TE_WIDTH 					1u
#define USART_CR1_TE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_TE_SHIFT))&USART_CR1_TE_MASK)

/* USART CR1 - IDLE interrupt enable */
#define USART_CR1_IDLEIE_MASK 				0x10u
#define USART_CR1_IDLEIE_SHIFT 				4u
#define USART_CR1_IDLEIE_WIDTH 				1u
#define USART_CR1_IDLEIE(x) 				(((uint32_t)(((uint32_t)(x))<<USART_CR1_IDLEIE_SHIFT))&USART_CR1_IDLEIE_MASK)

/* USART CR1 - RXNE interrupt enable */
#define USART_CR1_RXNEIE_MASK 				0x20u
#define USART_CR1_RXNEIE_SHIFT 				5u
#define USART_CR1_RXNEIE_WIDTH 				1u
#define USART_CR1_RXNEIE(x) 				(((uint32_t)(((uint32_t)(x))<<USART_CR1_RXNEIE_SHIFT))&USART_CR1_RXNEIE_MASK)

/* USART CR1 - Transmission complete interrupt enable */
#define USART_CR1_TCIE_MASK 				0x40u
#define USART_CR1_TCIE_SHIFT 				6u
#define USART_CR1_TCIE_WIDTH 				1u
#define USART_CR1_TCIE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_TCIE_SHIFT))&USART_CR1_TCIE_MASK)

/* USART CR1 - TXE interrupt enable */
#define USART_CR1_TXEIE_MASK 				0x80
#define USART_CR1_TXEIE_SHIFT 				7u
#define USART_CR1_TXEIE_WIDTH 				1u
#define USART_CR1_TXEIE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_TXEIE_SHIFT))&USART_CR1_TXEIE_MASK)

/* USART CR1 - PE interrupt enable */
#define USART_CR1_PEIE_MASK 				0x100u
#define USART_CR1_PEIE_SHIFT 				8u
#define USART_CR1_PEIE_WIDTH 				1u
#define USART_CR1_PEIE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_PEIE_SHIFT))&USART_CR1_PEIE_MASK)

/* USART CR1 - Parity selection */
#define USART_CR1_PS_MASK 					0x200u
#define USART_CR1_PS_SHIFT 					9u
#define USART_CR1_PS_WIDTH 					1u
#define USART_CR1_PS(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_PS_SHIFT))&USART_CR1_PS_MASK)

/* USART CR1 - Parity control enable */
#define USART_CR1_PCE_MASK 					0x400u
#define USART_CR1_PCE_SHIFT 				10u
#define USART_CR1_PCE_WIDTH 				1u
#define USART_CR1_PCE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_PCE_SHIFT))&USART_CR1_PCE_MASK)

/* USART CR1 - Wakeup method */
#define USART_CR1_WAKE_MASK 				0x800u
#define USART_CR1_WAKE_SHIFT 				11u
#define USART_CR1_WAKE_WIDTH 				1u
#define USART_CR1_WAKE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_WAKE_SHIFT))&USART_CR1_WAKE_MASK)

/* USART CR1 - Word length */
#define USART_CR1_M_MASK 					0x1000u
#define USART_CR1_M_SHIFT 					12u
#define USART_CR1_M_WIDTH 					1u
#define USART_CR1_M(x) 						(((uint32_t)(((uint32_t)(x))<<USART_CR1_M_SHIFT))&USART_CR1_M_MASK)

/* USART CR1 - USART enable */
#define USART_CR1_UE_MASK 					0x2000u
#define USART_CR1_UE_SHIFT 					13u
#define USART_CR1_UE_WIDTH 					1u
#define USART_CR1_UE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_UE_SHIFT))&USART_CR1_UE_MASK)

/* USART CR1 - Oversampling mode */
#define USART_CR1_OVER8_MASK 				0x8000u
#define USART_CR1_OVER8_SHIFT 				15u
#define USART_CR1_OVER8_WIDTH 				1u
#define USART_CR1_OVER8(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR1_OVER8_SHIFT))&USART_CR1_OVER8_MASK)


/*
 * Bit position definitions USART_CR2
 */
/* USART CR2 - Address of the USART node */
#define USART_CR2_ADD_MASK 					0xFu
#define USART_CR2_ADD_SHIFT 				0u
#define USART_CR2_ADD_WIDTH 				4u
#define USART_CR2_ADD(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_ADD_SHIFT))&USART_CR2_ADD_MASK)

/* USART CR2 - lin break detection length */
#define USART_CR2_LBDL_MASK 				0x20u
#define USART_CR2_LBDL_SHIFT 				5u
#define USART_CR2_LBDL_WIDTH 				1u
#define USART_CR2_LBDL(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_LBDL_SHIFT))&USART_CR2_LBDL_MASK)

/* USART CR2 - LIN break detection interrupt enable */
#define USART_CR2_LBDIE_MASK 				0x40u
#define USART_CR2_LBDIE_SHIFT 				6u
#define USART_CR2_LBDIE_WIDTH 				1u
#define USART_CR2_LBDIE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_LBDIE_SHIFT))&USART_CR2_LBDIE_MASK)

/* USART CR2 - Last bit clock pulse */
#define USART_CR2_LBCL_MASK 				0x100u
#define USART_CR2_LBCL_SHIFT 				8u
#define USART_CR2_LBCL_WIDTH 				1u
#define USART_CR2_LBCL(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_LBCL_SHIFT))&USART_CR2_LBCL_MASK)

/* USART CR2 - Clock phase */
#define USART_CR2_CPHA_MASK 				0x200u
#define USART_CR2_CPHA_SHIFT 				9u
#define USART_CR2_CPHA_WIDTH 				1u
#define USART_CR2_CPHA(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_CPHA_SHIFT))&USART_CR2_CPHA_MASK)

/* USART CR2 - Clock polarity */
#define USART_CR2_CPOL_MASK 				0x400u
#define USART_CR2_CPOL_SHIFT 				10u
#define USART_CR2_CPOL_WIDTH 				0u
#define USART_CR2_CPOL(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_CPOL_SHIFT))&USART_CR2_CPOL_MASK)

/* USART CR2 - Clock enable */
#define USART_CR2_CLKEN_MASK 				0x800u
#define USART_CR2_CLKEN_SHIFT 				11u
#define USART_CR2_CLKEN_WIDTH 				1u
#define USART_CR2_CLKEN(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_CLKEN_SHIFT))&USART_CR2_CLKEN_MASK)

/* USART CR2 - STOP bits */
#define USART_CR2_STOP_MASK 				0x3000u
#define USART_CR2_STOP_SHIFT 				12u
#define USART_CR2_STOP_WIDTH 				2u
#define USART_CR2_STOP(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_STOP_SHIFT))&USART_CR2_STOP_MASK)

/* USART CR2 - LIN mode enable */
#define USART_CR2_LINEN_MASK 				0x4000u
#define USART_CR2_LINEN_SHIFT 				14u
#define USART_CR2_LINEN_WIDTH 				1u
#define USART_CR2_LINEN(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR2_LINEN_SHIFT))&USART_CR2_LINEN_MASK)


/*
 * Bit position definitions USART_CR3
 */
/* USART CR3 - Error interrupt enable */
#define USART_CR3_EIE_MASK 					0x1u
#define USART_CR3_EIE_SHIFT 				0u
#define USART_CR3_EIE_WIDTH 				1u
#define USART_CR3_EIE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_EIE_SHIFT))&USART_CR3_EIE_MASK)

/* USART CR3 - IrDA mode enable */
#define USART_CR3_IREN_MASK 				0x2u
#define USART_CR3_IREN_SHIFT 				1u
#define USART_CR3_IREN_WIDTH 				1u
#define USART_CR3_IREN(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_IREN_SHIFT))&USART_CR3_IREN_MASK)

/* USART CR3 - IrDA low-power */
#define USART_CR3_IRLP_MASK 				0x4u
#define USART_CR3_IRLP_SHIFT 				3u
#define USART_CR3_IRLP_WIDTH 				1u
#define USART_CR3_IRLP(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_IRLP_SHIFT))&USART_CR3_IRLP_MASK)

/* USART CR3 - Half-duplex selection */
#define USART_CR3_HDSEL_MASK 				0x8u
#define USART_CR3_HDSEL_SHIFT 				3u
#define USART_CR3_HDSEL_WIDTH 				1u
#define USART_CR3_HDSEL(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_HDSEL_SHIFT))&USART_CR3_HDSEL_MASK)

/* USART CR3 - Smartcard NACK enable */
#define USART_CR3_NACK_MASK 				0x10u
#define USART_CR3_NACK_SHIFT 				4u
#define USART_CR3_NACK_WIDTH 				1u
#define USART_CR3_NACK(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_NACK_SHIFT))&USART_CR3_NACK_MASK)

/* USART CR3 - Smartcard mode enable */
#define USART_CR3_SCEN_MASK 				0x20u
#define USART_CR3_SCEN_SHIFT 				5u
#define USART_CR3_SCEN_WIDTH 				1u
#define USART_CR3_SCEN(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_SCEN_SHIFT))&USART_CR3_SCEN_MASK)

/* USART CR3 - DMA enable receiver */
#define USART_CR3_DMAR_MASK 				0x40u
#define USART_CR3_DMAR_SHIFT 				6u
#define USART_CR3_DMAR_WIDTH 				1u
#define USART_CR3_DMAR(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_DMAR_SHIFT))&USART_CR3_DMAR_MASK)

/* USART CR3 - DMA enable transmitter */
#define USART_CR3_DMAT_MASK 				0x80u
#define USART_CR3_DMAT_SHIFT 				7u
#define USART_CR3_DMAT_WIDTH 				1u
#define USART_CR3_DMAT(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_DMAT_SHIFT))&USART_CR3_DMAT_MASK)

/* USART CR3 - RTS enable */
#define USART_CR3_RTSE_MASK 				0x100u
#define USART_CR3_RTSE_SHIFT 				8u
#define USART_CR3_RTSE_WIDTH 				1u
#define USART_CR3_RTSE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_RTSE_SHIFT))&USART_CR3_RTSE_MASK)

/* USART CR3 - CTS enable */
#define USART_CR3_CTSE_MASK 				0x200u
#define USART_CR3_CTSE_SHIFT 				9u
#define USART_CR3_CTSE_WIDTH 				1u
#define USART_CR3_CTSE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_CTSE_SHIFT))&USART_CR3_CTSE_MASK)

/* USART CR3 - CTS interrupt enable */
#define USART_CR3_CTSIE_MASK 				0x400u
#define USART_CR3_CTSIE_SHIFT 				10u
#define USART_CR3_CTSIE_WIDTH 				1u
#define USART_CR3_CTSIE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_CR3_CTSIE_SHIFT))&USART_CR3_CTSIE_MASK)

/* USART CR3 - One sample bit method enable */
#define USART_CR3_ONEBIT_MASK 				0x800u
#define USART_CR3_ONEBIT_SHIFT 				11u
#define USART_CR3_ONEBIT_WIDTH 				1u
#define USART_CR3_ONEBIT(x) 				(((uint32_t)(((uint32_t)(x))<<USART_CR3_ONEBIT_SHIFT))&USART_CR3_ONEBIT_MASK)

/*
 * Bit position definitions USART_SR
 */
/* USART SR - Parity error */
#define USART_SR_PE_MASK 					0x1u
#define USART_SR_PE_SHIFT 					0u
#define USART_SR_PE_WIDTH 					1u
#define USART_SR_PE(x) 						(((uint32_t)(((uint32_t)(x))<<USART_SR_PE_SHIFT))&USART_SR_PE_MASK)

/* USART SR - Framing error */
#define USART_SR_FE_MASK 					0x2u
#define USART_SR_FE_SHIFT 					1u
#define USART_SR_FE_WIDTH 					1u
#define USART_SR_FE(x) 						(((uint32_t)(((uint32_t)(x))<<USART_SR_FE_SHIFT))&USART_SR_FE_MASK)

/* USART SR - Noise detected flag */
#define USART_SR_NE_MASK 					0x4u
#define USART_SR_NE_SHIFT 					2u
#define USART_SR_NE_WIDTH 					1u
#define USART_SR_NE(x) 						(((uint32_t)(((uint32_t)(x))<<USART_SR_NE_SHIFT))&USART_SR_NE_MASK)

/* USART SR - Overrun error */
#define USART_SR_ORE_MASK 					0x8u
#define USART_SR_ORE_SHIFT 					3u
#define USART_SR_ORE_WIDTH 					1u
#define USART_SR_ORE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_SR_ORE_SHIFT))&USART_SR_ORE_MASK)

/* USART SR - IDLE line detected */
#define USART_SR_IDLE_MASK 					0x10u
#define USART_SR_IDLE_SHIFT 				4u
#define USART_SR_IDLE_WIDTH 				1u
#define USART_SR_IDLE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_SR_IDLE_SHIFT))&USART_SR_IDLE_MASK)

/* USART SR - Read data register not empty */
#define USART_SR_RXNE_MASK 					0x20u
#define USART_SR_RXNE_SHIFT 				5u
#define USART_SR_RXNE_WIDTH 				1u
#define USART_SR_RXNE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_SR_RXNE_SHIFT))&USART_SR_RXNE_MASK)

/* USART SR - Transmission complete */
#define USART_SR_TC_MASK 					0x40u
#define USART_SR_TC_SHIFT 					6u
#define USART_SR_TC_WIDTH 					1u
#define USART_SR_TC(x) 						(((uint32_t)(((uint32_t)(x))<<USART_SR_TC_SHIFT))&USART_SR_TC_MASK)

/* USART SR - Transmit data register empty */
#define USART_SR_TXE_MASK 					0x80u
#define USART_SR_TXE_SHIFT 					7u
#define USART_SR_TXE_WIDTH 					1u
#define USART_SR_TXE(x) 					(((uint32_t)(((uint32_t)(x))<<USART_SR_TXE_SHIFT))&USART_SR_TXE_MASK)

/* USART SR - LIN break detection flag */
#define USART_SR_LBD_MASK 					0x100u
#define USART_SR_LBD_SHIFT 					8u
#define USART_SR_LBD_WIDTH 					1u
#define USART_SR_LBD(x) 					(((uint32_t)(((uint32_t)(x))<<USART_SR_LBD_SHIFT))&USART_SR_LBD_MASK)

/* USART SR - CTS flag */
#define USART_SR_CTS_MASK 					0x200u
#define USART_SR_CTS_SHIFT 					9u
#define USART_SR_CTS_WIDTH 					1u
#define USART_SR_CTS(x) 					(((uint32_t)(((uint32_t)(x))<<USART_SR_CTS_SHIFT))&USART_SR_CTS_MASK)

/* Mask for all Error Flags */
#define USART_SR_REG_FLAGS_MASK				0x1FFu

#endif	/* !(__USART_BASE_H_) */
