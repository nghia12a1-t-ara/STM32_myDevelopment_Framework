/**
 * Filename		: DMA_Base.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Peripheral Access Layer for DMA Driver
 */

#ifndef __DMA_BASE_H
#define __DMA_BASE_H

#include "stm32f4xx.h"
#include "Std_Type.h"

/** 
 * Define DMA Register 
 */
 
/**
 * Number of DMA Hardware Instance 
 * ++1 because have no DMA0
 */
#define DMA_INSTANCE_COUNT				(3U)
 
/* Number of DMA Streams */
#define DMA_NUM_OF_STREAM				(8U)
 
typedef struct {
	__vo uint32 LISR;			/** DMA Low Interrupt Status Register		Offset = 0x0000 */
	__vo uint32 HISR;			/** DMA High Interrupt Status Register		Offset = 0x0004 */
	__vo uint32 LIFCR;			/** DMA Low Interrupt Flag Clear Register	Offset = 0x0008	*/
	__vo uint32 HIFCR;			/** DMA High Interrupt Flag Clear Register	Offset = 0x000C */
	struct DMAStream_Type {
		__vo uint32 CR;			/** DMA Configuration Register				Offset = 0x0010 + 0x18 × stream number */
		__vo uint32 NDTR;		/** DMA Number of Data Register				Offset = 0x0014 + 0x18 × stream number */
		__vo uint32 PAR;		/** DMA Peripheral Address Register			Offset = 0x0018 + 0x18 × stream number */
		__vo uint32 M0AR;		/** DMA Memory 0 Address Register			Offset = 0x001C + 0x18 × stream number */
		__vo uint32 M1AR;		/** DMA Memory 1 Address Register			Offset = 0x0020 + 0x18 × stream number */
		__vo uint32 FCR;		/** DMA FIFO Control Register				Offset = 0x0024 + 0x18 × stream number */
	} Stream[DMA_NUM_OF_STREAM];
} DMA_Type;

typedef struct DMAStream_Type DMAStream_Type;

#define DMA1_BASEADDR					(0x40026000UL)
#define DMA1							((DMA_Type *)DMA1_BASEADDR)

#define DMA2_BASEADDR					(0x40026400UL)
#define DMA2							((DMA_Type *)DMA2_BASEADDR)

#define DMA_BASE_PTRS					{NULL_PTR, DMA1, DMA2}


#define DMA_MAX_DATA_SIZE				(65535u)


/******************************************************************************************
 *Bit position definitions of DMA peripheral
 ******************************************************************************************/

/**
 * Bit position definitions DMA_SxCR
 */

/* Bit 0 - Stream Enable /flag stream ready when read low */
#define DMA_CR_EN_MASK						0x1u
#define DMA_CR_EN_SHIFT						0u
#define DMA_CR_EN_WIDTH						1u
#define DMA_CR_EN(x)						(((uint32)(((uint32)(x))<<DMA_CR_EN_SHIFT))&DMA_CR_EN_MASK)

/* Bit 1 - Direct mode error interrupt enable */
#define DMA_CR_DMEIE_MASK					0x2u
#define DMA_CR_DMEIE_SHIFT					1u
#define DMA_CR_DMEIE_WIDTH					1u
#define DMA_CR_DMEIE(x)						(((uint32)(((uint32)(x))<<DMA_CR_DMEIE_SHIFT))&DMA_CR_DMEIE_MASK)

/* Bit 2 - Transfer error interrupt enable */
#define DMA_CR_TEIE_MASK					0x4u
#define DMA_CR_TEIE_SHIFT					2u
#define DMA_CR_TEIE_WIDTH					1u
#define DMA_CR_TEIE(x)						(((uint32)(((uint32)(x))<<DMA_CR_TEIE_SHIFT))&DMA_CR_TEIE_MASK)

/* Bit 3 - Half transfer interrupt enable */
#define DMA_CR_HTIE_MASK					0x8u
#define DMA_CR_HTIE_SHIFT					3u
#define DMA_CR_HTIE_WIDTH					1u
#define DMA_CR_HTIE(x)						(((uint32)(((uint32)(x))<<DMA_CR_HTIE_SHIFT))&DMA_CR_HTIE_MASK)

/* Bit 4 - Transfer complete interrupt enable */
#define DMA_CR_TCIE_MASK					0x10u
#define DMA_CR_TCIE_SHIFT					4u
#define DMA_CR_TCIE_WIDTH					1u
#define DMA_CR_TCIE(x)						(((uint32)(((uint32)(x))<<DMA_CR_TCIE_SHIFT))&DMA_CR_TCIE_MASK)

/* Bit 5 - Peripheral flow controller */
#define DMA_CR_PFCTRL_MASK					0x20u
#define DMA_CR_PFCTRL_SHIFT					5u
#define DMA_CR_PFCTRL_WIDTH					1u
#define DMA_CR_PFCTRL(x)					(((uint32)(((uint32)(x))<<DMA_CR_PFCTRL_SHIFT))&DMA_CR_PFCTRL_MASK)

/* Bit 6-7 - Data transfer direction */
#define DMA_CR_DIR_MASK						0xC0u
#define DMA_CR_DIR_SHIFT					6u
#define DMA_CR_DIR_WIDTH					2u
#define DMA_CR_DIR(x)						(((uint32)(((uint32)(x))<<DMA_CR_DIR_SHIFT))&DMA_CR_DIR_MASK)

/* Bit 8 - Circular mode */
#define DMA_CR_CIRC_MASK					0x100u
#define DMA_CR_CIRC_SHIFT					8u
#define DMA_CR_CIRC_WIDTH					1u
#define DMA_CR_CIRC(x)						(((uint32)(((uint32)(x))<<DMA_CR_CIRC_SHIFT))&DMA_CR_CIRC_MASK)

/* Bit 9 - Peripheral increment mode */
#define DMA_CR_PINC_MASK					0x200u
#define DMA_CR_PINC_SHIFT					9u
#define DMA_CR_PINC_WIDTH					1u
#define DMA_CR_PINC(x)						(((uint32)(((uint32)(x))<<DMA_CR_PINC_SHIFT))&DMA_CR_PINC_MASK)

/* Bit 10 - Memory increment mode */
#define DMA_CR_MINC_MASK					0x400u
#define DMA_CR_MINC_SHIFT					10u
#define DMA_CR_MINC_WIDTH					1u
#define DMA_CR_MINC(x)						(((uint32)(((uint32)(x))<<DMA_CR_MINC_SHIFT))&DMA_CR_MINC_MASK)

/* Bit 11-12 - Peripheral data size */
#define DMA_CR_PSIZE_MASK					0x1800u
#define DMA_CR_PSIZE_SHIFT					11u
#define DMA_CR_PSIZE_WIDTH					2u
#define DMA_CR_PSIZE(x)						(((uint32)(((uint32)(x))<<DMA_CR_PSIZE_SHIFT))&DMA_CR_PSIZE_MASK)

/* Bit 13-14 - Memory data size */
#define DMA_CR_MSIZE_MASK					0x6000u
#define DMA_CR_MSIZE_SHIFT					13u
#define DMA_CR_MSIZE_WIDTH					2u
#define DMA_CR_MSIZE(x)						(((uint32)(((uint32)(x))<<DMA_CR_MSIZE_SHIFT))&DMA_CR_MSIZE_MASK)

/* Bit 15 - Peripheral increment offset size */
#define DMA_CR_PINCOS_MASK					0x8000u
#define DMA_CR_PINCOS_SHIFT					15u
#define DMA_CR_PINCOS_WIDTH					1u
#define DMA_CR_PINCOS(x)					(((uint32)(((uint32)(x))<<DMA_CR_PINCOS_SHIFT))&DMA_CR_PINCOS_MASK)

/* Bit 16-17 - Priority level */
#define DMA_CR_PL_MASK						0x30000u
#define DMA_CR_PL_SHIFT						16u
#define DMA_CR_PL_WIDTH						2u
#define DMA_CR_PL(x)						(((uint32)(((uint32)(x))<<DMA_CR_PL_SHIFT))&DMA_CR_PL_MASK)

/* Bit 18 - Double buffer mode */
#define DMA_CR_DBM_MASK						0x40000u
#define DMA_CR_DBM_SHIFT					18u
#define DMA_CR_DBM_WIDTH					1u
#define DMA_CR_DBM(x)						(((uint32)(((uint32)(x))<<DMA_CR_DBM_SHIFT))&DMA_CR_DBM_MASK)

/* Bit 19 - Current target (only in double buffer mode) */
#define DMA_CR_CT_MASK						0x40000u
#define DMA_CR_CT_SHIFT						19u
#define DMA_CR_CT_WIDTH						1u
#define DMA_CR_CT(x)						(((uint32)(((uint32)(x))<<DMA_CR_CT_SHIFT))&DMA_CR_CT_MASK)

/* Bit 20 - Reserved */

/* Bit 21-22 - Peripheral burst transfer configuration */
#define DMA_CR_PBURST_MASK					0x300000u
#define DMA_CR_PBURST_SHIFT					21u
#define DMA_CR_PBURST_WIDTH					2u
#define DMA_CR_PBURST(x)					(((uint32)(((uint32)(x))<<DMA_CR_PBURST_SHIFT))&DMA_CR_PBURST_MASK)

/* Bit 23-24 - Memory burst transfer configuration */
#define DMA_CR_MBURST_MASK					0x1800000u
#define DMA_CR_MBURST_SHIFT					23u
#define DMA_CR_MBURST_WIDTH					2u
#define DMA_CR_MBURST(x)					(((uint32)(((uint32)(x))<<DMA_CR_MBURST_SHIFT))&DMA_CR_MBURST_MASK)

/* Bit 25-27 - Channel selection */
#define DMA_CR_CHSEL_MASK					0xE000000u
#define DMA_CR_CHSEL_SHIFT					25u
#define DMA_CR_CHSEL_WIDTH					3u
#define DMA_CR_CHSEL(x)						(((uint32)(((uint32)(x))<<DMA_CR_CHSEL_SHIFT))&DMA_CR_CHSEL_MASK)

/* Bit 28-31 - Reserved */


/**
 * Bit position definitions DMA_SxNDTR
 * DMA stream x number of data register (DMA_SxNDTR) (x = 0..7)
 */
/* Bit 0-15 - Number of data items to transfer */
#define DMA_NDTR_NDT_MASK					0xFFFFu
#define DMA_NDTR_NDT_SHIFT					0u
#define DMA_NDTR_NDT_WIDTH					16u
#define DMA_NDTR_NDT(x)						(((uint32)(((uint32)(x))<<DMA_NDTR_NDT_SHIFT))&DMA_NDTR_NDT_MASK)


/**
 * Bit position definitions DMA_SxPAR
 * DMA stream x peripheral address register (DMA_SxPAR) (x = 0..7)
 */
/* Bit 0-31 - Peripheral address */
#define DMA_PAR_PAR_MASK					0xFFFFFFFFu
#define DMA_PAR_PAR_SHIFT					0u
#define DMA_PAR_PAR_WIDTH					32u
#define DMA_PAR_PAR(x)						(((uint32)(((uint32)(x))<<DMA_PAR_PAR_SHIFT))&DMA_PAR_PAR_MASK)


/**
 * Bit position definitions DMA_SxM0AR
 * DMA stream x memory 0 address register (DMA_SxM0AR) (x = 0..7)
 */
/* Bit 0-31 - Memory 0 address */
#define DMA_M0AR_M0A_MASK					0xFFFFFFFFu
#define DMA_M0AR_M0A_SHIFT					0u
#define DMA_M0AR_M0A_WIDTH					32u
#define DMA_M0AR_M0A(x)						(((uint32)(((uint32)(x))<<DMA_M0AR_M0A_SHIFT))&DMA_M0AR_M0A_MASK)


/**
 * Bit position definitions DMA_SxM1AR
 * DMA stream x memory 1 address register (DMA_SxM1AR) (x = 0..7)
 */
/* Bit 0-31 - Memory 1 address */
#define DMA_M1AR_M1A_MASK					0xFFFFFFFFu
#define DMA_M1AR_M1A_SHIFT					0u
#define DMA_M1AR_M1A_WIDTH					32u
#define DMA_M1AR_M1A(x)						(((uint32)(((uint32)(x))<<DMA_M1AR_M1A_SHIFT))&DMA_M1AR_M1A_MASK)


/**
 * Bit position definitions DMA_LISR
 * DMA low interrupt status register (DMA_LISR)
 */
/* Bit  22, 16, 6, 0 - Stream x FIFO error interrupt flag (x=3..0) */
#define DMA_LISR_FEIF_SHIFT(x)				(((uint32)x<<3)-(((uint32)x%2)>>1))
#define DMA_LISR_FEIF_WIDTH					1u
#define DMA_LISR_FEIF_MASK(x)				((uint32)1u<<(((uint32)x<<3)-(((uint32)x%2)>>1)))

/* Bit 23, 17, 7, 1 - Reserved */

/* Bit 24, 18, 8, 2 - Stream x direct mode error interrupt flag (x=3..0) */
#define DMA_LISR_DMEIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+2u)
#define DMA_LISR_DMEIF_WIDTH				1u
#define DMA_LISR_DMEIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+2u)

/* Bit 25, 19, 9, 3 - Stream x transfer error interrupt flag (x=3..0) */
#define DMA_LISR_TEIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+3u)
#define DMA_LISR_TEIF_WIDTH					1u
#define DMA_LISR_TEIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+3u)

/* Bit 26, 20, 10, 4 - Stream x half transfer interrupt flag (x=3..0) */
#define DMA_LISR_HTIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+4u)
#define DMA_LISR_HTIF_WIDTH					1u
#define DMA_LISR_HTIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+4u)

/* Bit 27, 21, 11, 5 - Stream x transfer complete interrupt flag (x = 3..0) */
#define DMA_LISR_TCIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+5u)
#define DMA_LISR_TCIF_WIDTH					1u
#define DMA_LISR_TCIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+5u)


/**
 * Bit position definitions DMA_HISR
 * DMA high interrupt status register (DMA_HISR)
 */
/* Bit  22, 16, 6, 0 - Stream x FIFO error interrupt flag (x=7..4) */
#define DMA_LISR_FEIF_SHIFT(x)				(((uint32)x<<3)-(((uint32)x%2)>>1))
#define DMA_LISR_FEIF_WIDTH					1u
#define DMA_LISR_FEIF_MASK(x)				((uint32)1u<<(((uint32)x<<3)-(((uint32)x%2)>>1)))

/* Bit 23, 17, 7, 1 - Reserved */

/* Bit 24, 18, 8, 2 - Stream x direct mode error interrupt flag (x=7..4) */
#define DMA_LISR_DMEIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+2u)
#define DMA_LISR_DMEIF_WIDTH				1u
#define DMA_LISR_DMEIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+2u)

/* Bit 25, 19, 9, 3 - Stream x transfer error interrupt flag (x=7..4) */
#define DMA_LISR_TEIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+3u)
#define DMA_LISR_TEIF_WIDTH					1u
#define DMA_LISR_TEIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+3u)

/* Bit 26, 20, 10, 4 - Stream x half transfer interrupt flag (x=7..4) */
#define DMA_LISR_HTIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+4u)
#define DMA_LISR_HTIF_WIDTH					1u
#define DMA_LISR_HTIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+4u)

/* Bit 27, 21, 11, 5 - Stream x transfer complete interrupt flag (x = 7..4) */
#define DMA_LISR_TCIF_SHIFT(x)				((((uint32)x<<3)-(((uint32)x%2)>>1))+5u)
#define DMA_LISR_TCIF_WIDTH					1u
#define DMA_LISR_TCIF_MASK(x)				((uint32)1u<<((((uint32)x<<3)-(((uint32)x%2)>>1)))+5u)

/**
 * Bit position definitions DMA_SxFCR
 * DMA stream x FIFO control register (DMA_SxFCR) (x = 0..7)
 */


#endif	/* !(__DMA_BASE_H) */


