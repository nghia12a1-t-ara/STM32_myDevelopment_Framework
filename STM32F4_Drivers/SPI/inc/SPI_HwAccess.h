/**
 * Filename     : SPI_HwAccess.h
 * Author       : Nghia-Taarabt
 * Create Date  : 18/12/22
 * Brief        : Implement Hardware Access Functions
 */

#ifndef __SPI_HWACCESS_H__
#define __SPI_HWACCESS_H__

#include "SPI_Base.h"
#include "SPI_Type.h"
#include "Systick.h"
#include "CLOCK.h"

#define SPI_DATA_REG_WRITE(Base,data)   Base->DR=data
#define SPI_DATA_REG_READ(Base,dest)    dest=Base->DR

/** @brief SPI interrupt configuration structure, default settings are 0 (disabled) */
typedef enum
{
    SPI_INT_TX_DATA_REG_EMPTY           = (uint32)SPI_CR2_TXEIE_SHIFT,        /*!< Transmit data register empty. */
    SPI_INT_ERROR_TRANSACTION           = (uint32)SPI_CR2_ERRIE_SHIFT,         /*!< Transmission complete. */
    SPI_INT_RX_DATA_REG_FULL            = (uint32)SPI_CR2_RXNEIE_SHIFT,       /*!< Receiver data register full. */
} Spi_InterruptType;

/*********************************************************************
 * @fn                - Peripheral Clock Control
 *
 */
__STATIC_INLINE void SPI_PeriClockControl(SPI_Type *pSPIx, uint8 EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
    }
    else
    {
        /* TODO */
    }
}

/*********************************************************************
 * @fn                - Set Enable or Disable Module SPI
 *
 */
__STATIC_INLINE void SPI_PeripheralControl(SPI_Type *pSPIx, Bool_Type EnOrDi)
{
    pSPIx->CR1 &= ~SPI_CR1_SPE_MASK;
    if(ENABLE == EnOrDi)
    {
        pSPIx->CR1 |= SPI_CR1_SPE(BIT_SET);
    }
}

/**
 * @brief  SPI get status flag
 *
 * This function returns the state of a status flag.
 */
__STATIC_INLINE Bool_Type Spi_GetStatusFlag(const SPI_Type * pSPIx, Spi_StatusFlagType StatusFlag)
{
    Bool_Type RetVal = FALSE;
    RetVal = (((pSPIx->SR >> (uint32)(StatusFlag)) & 1U) > 0U);
    return RetVal;
}

/*********************************************************************
 * @fn                - Set Device Mode is Master or Slave
 *
 */
__STATIC_INLINE void SPI_SetDeviceMode(SPI_Type *pSPIx, Spi_DeviceModeType SPI_DeviceMode)
{
    pSPIx->CR1 &= ~SPI_CR1_MSTR_MASK;
    pSPIx->CR1 |= SPI_CR1_MSTR(SPI_DeviceMode);
}

/********************************************************************************
 * @fn                - Set Bus Configuration (Full-duplex / Half-duplex / Read only)
 *
 */
__STATIC_INLINE void SPI_SetBusConfig(SPI_Type *pSPIx, SPI_BusConfigType SPI_BusConfig)
{
    
    pSPIx->CR1 &= ~SPI_CR1_BIDIMODE_MASK;
    pSPIx->CR1 &= ~SPI_CR1_RXONLY_MASK;
    
    if(SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX)
    {
        /* Do Nothing - BIDIMODE = RXONLY = 0 */
    }
    else if (SPI_BusConfig == SPI_BUS_CONFIG_HALF_DUPLEX)
    {
        pSPIx->CR1 |= SPI_CR1_BIDIMODE(BIT_SET);
    }
    else if (SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        pSPIx->CR1 |= SPI_CR1_RXONLY(BIT_SET);
    }
    else
    {
        /* Do Nothing */
    }
}

/*********************************************************************
 * @fn                - Set Baud-rate - Clock divide
 *
 */
__STATIC_INLINE void SPI_SetClockSpeedDivide(SPI_Type *pSPIx, Spi_ClockSpeedDivType SPI_SclkSpeed)
{
    pSPIx->CR1 &= ~SPI_CR1_BR_MASK;
    pSPIx->CR1 |= SPI_CR1_BR(SPI_SclkSpeed);
}

/*********************************************************************
 * @fn                - Set DataFrame (8 or 16 bits)
 *
 */
__STATIC_INLINE void SPI_SetDataFrame(SPI_Type *pSPIx, Spi_DataFrameType SPI_DataFrame)
{
    pSPIx->CR1 &= ~SPI_CR1_DFF_MASK;
    if (SPI_DATA_FRAME_16BITS == SPI_DataFrame)
    {
        pSPIx->CR1 |= SPI_CR1_DFF(BIT_SET);
    }
}

/*********************************************************************
 * @fn                - Set First Bit MSB or LSB
 *
 */
__STATIC_INLINE void SPI_SetFirstBit(SPI_Type *pSPIx, Spi_FirstBitType SPI_FirstBit)
{
    pSPIx->CR1 &= ~SPI_CR1_LSBFIRST_MASK;
    if (SPI_FIRSTBIT_LSB == SPI_FirstBit)
    {
        pSPIx->CR1 |= SPI_CR1_LSBFIRST(BIT_SET);
    }
}

/*********************************************************************
 * @fn                - Set Clock Mode with CPOL and CPHA
 *
 */
__STATIC_INLINE void SPI_SetClockMode(SPI_Type *pSPIx, Spi_ClockModeType SPI_ClockMode)
{
    pSPIx->CR1 &= ~SPI_CR1_CLKMODE_MASK;
    pSPIx->CR1 |= SPI_CR1_CLKMODE(SPI_ClockMode);
}

/*********************************************************************
 * @fn                - Set Enable or Disable Software Slave Management
 *
 */
__STATIC_INLINE void SPI_SetSWSlaveManage(SPI_Type *pSPIx, Spi_SSMEnaleType SPI_SSM)
{
    pSPIx->CR1 &= ~SPI_CR1_SSM_MASK;
    if (SPI_SSM_NSS_SOFT == SPI_SSM)
    {
        pSPIx->CR1 |= SPI_CR1_SSM(BIT_SET);
    }
}

/*********************************************************************
 * @fn                - Set Enable or Disable SSI Pin
 *
 */
__STATIC_INLINE void SPI_SetSSIEnable(SPI_Type *pSPIx, Bool_Type EnorDi)
{
    pSPIx->CR1 &= ~SPI_CR1_SSI_MASK;
    if (TRUE == EnorDi)
    {
        pSPIx->CR1 |= SPI_CR1_SSI(BIT_SET);
    }
}

/*********************************************************************
 * @fn                - Config SPI Interrupt with source
 *
 */
__STATIC_INLINE void Spi_SetIntMode(SPI_Type *pSPIx, Spi_InterruptType IntSrc, Bool_Type EnorDir)
{
    pSPIx->CR2 = (pSPIx->CR2 & ~(1UL << (uint32)IntSrc)) | ((EnorDir ? ENABLE : DISABLE) << (uint32)IntSrc);
}
__STATIC_INLINE Bool_Type Spi_GetIntMode(const SPI_Type *pSPIx, Spi_InterruptType IntSrc)
{
    Bool_Type RetVal = FALSE;
    RetVal = (((pSPIx->CR2 >> (uint32)(IntSrc)) & 1U) > 0U);
    return RetVal;
}

/**
 * @brief  Clears the error flags treated by the driver
 *
 * This function clears the error flags treated by the driver.
 * *
 * @param Base SPI Base pointer
 */
__STATIC_INLINE void Spi_ClearErrorFlags(SPI_Type *pSPIx)
{
    uint32 Mask = SPI_SR_FRE_MASK | \
                  SPI_SR_BSY_MASK | \
                  SPI_SR_OVR_MASK | \
                  SPI_SR_UDR_MASK | \
                  SPI_SR_CRCERR_MASK | \
                  SPI_SR_MODF_MASK;

    pSPIx->SR &= ~SPI_SR_REG_FLAGS_MASK;
    pSPIx->SR |= Mask;
}

#endif  /* __SPI_HWACCESS_H__ */
