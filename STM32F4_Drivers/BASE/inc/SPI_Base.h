/**
 * Filename     : SPI_Base.h
 * Author       : Nghia Taarabt
 * Create Date  : 18/12/22
 * Brief        : Peripheral Access Layer for SPI Driver
 */

#ifndef __SPI_BASE_H__
#define __SPI_BASE_H__

#include "stm32f4xx.h"

/**
 * Number of SPI Hardware Instance 
 * ++1 because have no SPI0
 */
#define SPI_INSTANCE_COUNT          (5U)

/*
 * Peripheral register definition structure for SPI
 */
typedef struct
{
    __vo uint32 CR1;        /*!< TODO, SPI Control 1 Register           - Address offset: 0x00 */
    __vo uint32 CR2;        /*!< TODO, SPI Control 2 Register           - Address offset: 0x04 */
    __vo uint32 SR;         /*!< TODO, Status Register                  - Address offset: 0x08 */
    __vo uint32 DR;         /*!< TODO, Data Register                    - Address offset: 0x0C */
    __vo uint32 CRCPR;      /*!< TODO, SPI CRC polynomial register      - Address offset: 0x10 */
    __vo uint32 RXCRCR;     /*!< TODO, SPI RX CRC register              - Address offset: 0x14 */
    __vo uint32 TXCRCR;     /*!< TODO, SPI TX CRC register              - Address offset: 0x18 */
    __vo uint32 I2SCFGR;    /*!< TODO, SPI_I2S configuration register   - Address offset: 0x1C */
    __vo uint32 I2SPR;      /*!< TODO, SPI_I2S prescaler register       - Address offset: 0x20 */
} SPI_Type;

/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 * TODO : Complete for all other peripherals
 */
#define SPI2_BASEADDR                   (0x40003800UL)
#define SPI2                            ((SPI_Type*)SPI2_BASEADDR)

#define SPI3_BASEADDR                   (0x40003C00UL)
#define SPI3                            ((SPI_Type*)SPI3_BASEADDR)

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 * TODO : Complete for all other peripherals
 */
#define SPI1_BASEADDR                   (0x40013000UL)
#define SPI1                            ((SPI_Type*)SPI1_BASEADDR)

#define SPI4_BASEADDR                   (0x40013400UL)
#define SPI4                            ((SPI_Type*)SPI4_BASEADDR)

#define SPI_BASE_PTRS                   { NULL_PTR, SPI1, SPI2, SPI3, SPI4 }

/**
 * Define Supported Instance of SPI
 */
#define SPI_INSTANCE_1                  (1u)
#define SPI_INSTANCE_2                  (2u)
#define SPI_INSTANCE_3                  (3u)
#define SPI_INSTANCE_4                  (4u)

/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
/* SPI CR1 - Clock phase */
#define SPI_CR1_CPHA_MASK               0x1u
#define SPI_CR1_CPHA_SHIFT              0u
#define SPI_CR1_CPHA_WIDTH              1u
#define SPI_CR1_CPHA(x)                 (((uint32)(((uint32)(x))<<SPI_CR1_CPHA_SHIFT))&SPI_CR1_CPHA_MASK)

/* SPI CR1 - Clock polarity */
#define SPI_CR1_CPOL_MASK               0x2u
#define SPI_CR1_CPOL_SHIFT              1u
#define SPI_CR1_CPOL_WIDTH              1u
#define SPI_CR1_CPOL(x)                 (((uint32)(((uint32)(x))<<SPI_CR1_CPOL_SHIFT))&SPI_CR1_CPOL_MASK)

/* Add Define for CPOL & CPHA - CLock Mode */
#define SPI_CR1_CLKMODE_MASK            0x3u
#define SPI_CR1_CLKMODE_SHIFT           0u
#define SPI_CR1_CLKMODE_WIDTH           2u
#define SPI_CR1_CLKMODE(x)              (((uint32)(((uint32)(x))<<SPI_CR1_CLKMODE_SHIFT))&SPI_CR1_CLKMODE_MASK)

/* SPI CR1 - Master selection */
#define SPI_CR1_MSTR_MASK               0x4u
#define SPI_CR1_MSTR_SHIFT              2u
#define SPI_CR1_MSTR_WIDTH              1u
#define SPI_CR1_MSTR(x)                 (((uint32)(((uint32)(x))<<SPI_CR1_MSTR_SHIFT))&SPI_CR1_MSTR_MASK)

/* SPI CR1 - Baud rate control */
#define SPI_CR1_BR_MASK                 0x28u
#define SPI_CR1_BR_SHIFT                3u
#define SPI_CR1_BR_WIDTH                3u
#define SPI_CR1_BR(x)                   (((uint32)(((uint32)(x))<<SPI_CR1_BR_SHIFT))&SPI_CR1_BR_MASK)

/* SPI CR1 - SPI enable */
#define SPI_CR1_SPE_MASK                0x40u
#define SPI_CR1_SPE_SHIFT               6u
#define SPI_CR1_SPE_WIDTH               1u
#define SPI_CR1_SPE(x)                  (((uint32)(((uint32)(x))<<SPI_CR1_SPE_SHIFT))&SPI_CR1_SPE_MASK)

/* SPI CR1 - Frame format */
#define SPI_CR1_LSBFIRST_MASK           0x80u
#define SPI_CR1_LSBFIRST_SHIFT          7u
#define SPI_CR1_LSBFIRST_WIDTH          1u
#define SPI_CR1_LSBFIRST(x)             (((uint32)(((uint32)(x))<<SPI_CR1_LSBFIRST_SHIFT))&SPI_CR1_LSBFIRST_MASK)

/* SPI CR1 - Internal slave select */
#define SPI_CR1_SSI_MASK                0x100u
#define SPI_CR1_SSI_SHIFT               8u
#define SPI_CR1_SSI_WIDTH               1u
#define SPI_CR1_SSI(x)                  (((uint32)(((uint32)(x))<<SPI_CR1_SSI_SHIFT))&SPI_CR1_SSI_MASK)

/* SPI CR1 - Software slave management */
#define SPI_CR1_SSM_MASK                0x200u
#define SPI_CR1_SSM_SHIFT               9u
#define SPI_CR1_SSM_WIDTH               1u
#define SPI_CR1_SSM(x)                  (((uint32)(((uint32)(x))<<SPI_CR1_SSM_SHIFT))&SPI_CR1_SSM_MASK)

/* SPI CR1 - Receive only */
#define SPI_CR1_RXONLY_MASK             0x400u
#define SPI_CR1_RXONLY_SHIFT            10u
#define SPI_CR1_RXONLY_WIDTH            1u
#define SPI_CR1_RXONLY(x)               (((uint32)(((uint32)(x))<<SPI_CR1_RXONLY_SHIFT))&SPI_CR1_RXONLY_MASK)

/* SPI CR1 - Data frame format */
#define SPI_CR1_DFF_MASK                0x800u
#define SPI_CR1_DFF_SHIFT               11u
#define SPI_CR1_DFF_WIDTH               1u
#define SPI_CR1_DFF(x)                  (((uint32)(((uint32)(x))<<SPI_CR1_DFF_SHIFT))&SPI_CR1_DFF_MASK)

/* SPI CR1 - CRC transfer next */
#define SPI_CR1_CRCNEXT_MASK            0x1000u
#define SPI_CR1_CRCNEXT_SHIFT           12u
#define SPI_CR1_CRCNEXT_WIDTH           1u
#define SPI_CR1_CRCNEXT(x)              (((uint32)(((uint32)(x))<<SPI_CR1_CRCNEXT_SHIFT))&SPI_CR1_CRCNEXT_MASK)

/* SPI CR1 - Hardware CRC calculation enable */
#define SPI_CR1_CRCEN_MASK              0x2000u
#define SPI_CR1_CRCEN_SHIFT             13u
#define SPI_CR1_CRCEN_WIDTH             1u
#define SPI_CR1_CRCEN(x)                (((uint32)(((uint32)(x))<<SPI_CR1_CRCEN_SHIFT))&SPI_CR1_CRCEN_MASK)

/* SPI CR1 - Output enable in bidirectional mode */
#define SPI_CR1_BIDIOE_MASK             0x4000u
#define SPI_CR1_BIDIOE_SHIFT            14u
#define SPI_CR1_BIDIOE_WIDTH            1u
#define SPI_CR1_BIDIOE(x)               (((uint32)(((uint32)(x))<<SPI_CR1_BIDIOE_SHIFT))&SPI_CR1_BIDIOE_MASK)

/* SPI CR1 - Bidirectional data mode enable */
#define SPI_CR1_BIDIMODE_MASK           0x8000u
#define SPI_CR1_BIDIMODE_SHIFT          15u
#define SPI_CR1_BIDIMODE_WIDTH          1u
#define SPI_CR1_BIDIMODE(x)             (((uint32)(((uint32)(x))<<SPI_CR1_BIDIMODE_SHIFT))&SPI_CR1_BIDIMODE_MASK)


/*
 * Bit position definitions SPI_CR2
 */
/* SPI CR2 - Rx buffer DMA enable */
#define SPI_CR2_RXDMAEN_MASK            0x1u
#define SPI_CR2_RXDMAEN_SHIFT           0u
#define SPI_CR2_RXDMAEN_WIDTH           1u
#define SPI_CR2_RXDMAEN(x)              (((uint32)(((uint32)(x))<<SPI_CR2_RXDMAEN_SHIFT))&SPI_CR2_RXDMAEN_MASK)

/* SPI CR2 - Tx buffer DMA enable */
#define SPI_CR2_TXDMAEN_MASK            0x2u
#define SPI_CR2_TXDMAEN_SHIFT           1u
#define SPI_CR2_TXDMAEN_WIDTH           1u
#define SPI_CR2_TXDMAEN(x)              (((uint32)(((uint32)(x))<<SPI_CR2_TXDMAEN_SHIFT))&SPI_CR2_TXDMAEN_MASK)

/* SPI CR2 - SS output enable */
#define SPI_CR2_SSOE_MASK               0x4u
#define SPI_CR2_SSOE_SHIFT              2u
#define SPI_CR2_SSOE_WIDTH              1u
#define SPI_CR2_SSOE(x)                 (((uint32)(((uint32)(x))<<SPI_CR2_SSOE_SHIFT))&SPI_CR2_SSOE_MASK)

/* SPI CR2 - Frame format */
#define SPI_CR2_FRF_MASK             0x10u
#define SPI_CR2_FRF_SHIFT               4u
#define SPI_CR2_FRF_WIDTH               1u
#define SPI_CR2_FRF(x)                  (((uint32)(((uint32)(x))<<SPI_CR2_FRF_SHIFT))&SPI_CR2_FRF_MASK)

/* SPI CR2 - Error interrupt enable */
#define SPI_CR2_ERRIE_MASK              0x20u
#define SPI_CR2_ERRIE_SHIFT             5u
#define SPI_CR2_ERRIE_WIDTH             1u
#define SPI_CR2_ERRIE(x)                (((uint32)(((uint32)(x))<<SPI_CR2_ERRIE_SHIFT))&SPI_CR2_ERRIE_MASK)

/* SPI CR2 - RX buffer not empty interrupt enable */
#define SPI_CR2_RXNEIE_MASK             0x40u
#define SPI_CR2_RXNEIE_SHIFT            6u
#define SPI_CR2_RXNEIE_WIDTH            1u
#define SPI_CR2_RXNEIE(x)               (((uint32)(((uint32)(x))<<SPI_CR2_RXNEIE_SHIFT))&SPI_CR2_RXNEIE_MASK)

/* SPI CR2 - Tx buffer empty interrupt enable */
#define SPI_CR2_TXEIE_MASK              0x80u
#define SPI_CR2_TXEIE_SHIFT             7u
#define SPI_CR2_TXEIE_WIDTH             1u
#define SPI_CR2_TXEIE(x)                (((uint32)(((uint32)(x))<<SPI_CR2_TXEIE_SHIFT))&SPI_CR2_TXEIE_MASK)


/*
 * Bit position definitions SPI_SR
 */
/* SPI SR - Transmit buffer empty */
#define SPI_SR_RXNE_MASK                0x1u
#define SPI_SR_RXNE_SHIFT               0u
#define SPI_SR_RXNE_WIDTH               1u
#define SPI_SR_RXNE(x)                  (((uint32)(((uint32)(x))<<SPI_CR2_RXNE_SHIFT))&SPI_CR2_RXNE_MASK)

/* SPI SR - Transmit buffer empty */
#define SPI_SR_TXE_MASK                 0x2u
#define SPI_SR_TXE_SHIFT                1u
#define SPI_SR_TXE_WIDTH                1u
#define SPI_SR_TXE(x)                   (((uint32)(((uint32)(x))<<SPI_CR2_TXE_SHIFT))&SPI_CR2_TXE_MASK)

/* SPI SR - Channel side */
#define SPI_SR_CHSIDE_MASK              0x4u
#define SPI_SR_CHSIDE_SHIFT             2u
#define SPI_SR_CHSIDE_WIDTH             1u
#define SPI_SR_CHSIDE(x)                (((uint32)(((uint32)(x))<<SPI_CR2_SSOE_SHIFT))&SPI_CR2_SSOE_MASK)

/* SPI SR - Underrun flag */
#define SPI_SR_UDR_MASK                 0x8u
#define SPI_SR_UDR_SHIFT                3u
#define SPI_SR_UDR_WIDTH                1u
#define SPI_SR_UDR(x)                   (((uint32)(((uint32)(x))<<SPI_CR2_UDR_SHIFT))&SPI_CR2_UDR_MASK)

/* SPI SR - CRC error flag */
#define SPI_SR_CRCERR_MASK              0x10u
#define SPI_SR_CRCERR_SHIFT             4u
#define SPI_SR_CRCERR_WIDTH             1u
#define SPI_SR_CRCERR(x)                (((uint32)(((uint32)(x))<<SPI_CR2_CRCERR_SHIFT))&SPI_CR2_CRCERR_MASK)

/* SPI SR - Mode fault */
#define SPI_SR_MODF_MASK                0x20u
#define SPI_SR_MODF_SHIFT               5u
#define SPI_SR_MODF_WIDTH               1u
#define SPI_SR_MODF(x)                  (((uint32)(((uint32)(x))<<SPI_CR2_MODF_SHIFT))&SPI_CR2_MODF_MASK)

/* SPI SR - Overrun flag */
#define SPI_SR_OVR_MASK                 0x40u
#define SPI_SR_OVR_SHIFT                6u
#define SPI_SR_OVR_WIDTH                1u
#define SPI_SR_OVR(x)                   (((uint32)(((uint32)(x))<<SPI_CR2_OVR_SHIFT))&SPI_CR2_OVR_MASK)

/* SPI SR - Busy flag */
#define SPI_SR_BSY_MASK                 0x80u
#define SPI_SR_BSY_SHIFT                7u
#define SPI_SR_BSY_WIDTH                1u
#define SPI_SR_BSY(x)                   (((uint32)(((uint32)(x))<<SPI_CR2_BSY_SHIFT))&SPI_CR2_BSY_MASK)

/* SPI SR - Frame format error */
#define SPI_SR_FRE_MASK                 0x100u
#define SPI_SR_FRE_SHIFT                8u
#define SPI_SR_FRE_WIDTH                1u
#define SPI_SR_FRE(x)                   (((uint32)(((uint32)(x))<<SPI_CR2_FRE_SHIFT))&SPI_CR2_FRE_MASK)


/*
 * Bit position definitions SPI_DR
 */
/* SPI DR - Data Register */
#define SPI_DR_DR_MASK                  0xFFFFu
#define SPI_DR_DR_SHIFT                 0u
#define SPI_DR_DR_WIDTH                 16u
#define SPI_DR_DR(x)                    (((uint32)(((uint32)(x))<<SPI_CR2_RXNE_SHIFT))&SPI_CR2_RXNE_MASK)

#endif 	/* !(__SPI_BASE_H__) */
