/**
 * Filename     : SPI_HwAccess.h
 * Author       : Nghia Taarabt
 * Create Date  : 18/12/22
 * Brief        : Implement Hardware Access Functions
 */

#ifndef __SPI_HWACCESS_H__
#define __SPI_HWACCESS_H__

#include "SPI_Base.h"
#include "SPI_Type.h"
#include "Systick.h"
#include "RCC.h"

#define SPI_DATA_REG_WRITE(Base,data)   Base->DR=data

typedef enum {
    SPI_FLAG_FRAME_FORMAT_ERROR         = SPI_SR_FRE_SHIFT,
    SPI_FLAG_TRANSFER_BUSY              = SPI_SR_BSY_SHIFT,
    SPI_FLAG_OVERRUN                    = SPI_SR_OVR_SHIFT,
    SPI_FLAG_MODE_FAULT                 = SPI_SR_MODF_SHIFT,
    SPI_FLAG_CRC_ERROR                  = SPI_SR_CRCERR_SHIFT,
    SPI_FLAG_UNDERRUN                   = SPI_SR_UDR_SHIFT,
    SPI_FLAG_CHANNEL_SIDE               = SPI_SR_CHSIDE_SHIFT,
    SPI_FLAG_TX_BUFFER_EMPTY            = SPI_SR_TXE_SHIFT,
    SPI_FLAG_RX_BUFFER_NOT_EMPTY        = SPI_SR_RXNE_SHIFT,
} Spi_StatusFlagType;

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
__STATIC_INLINE void SPI_PeripheralControl(SPI_Type *pSPIx, boolean EnOrDi)
{
    pSPIx->CR1 &= ~SPI_CR1_SPE_MASK;
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= SPI_CR1_SPE(BIT_SET);
    }
}

/**
 * @brief  SPI get status flag
 *
 * This function returns the state of a status flag.
 */
__STATIC_INLINE boolean Spi_GetStatusFlag(const SPI_Type * pSPIx, Spi_StatusFlagType StatusFlag)
{
    boolean RetVal = FALSE;
    if ( ((pSPIx->SR >> (uint32)(StatusFlag)) & 1U) > 0U )
    {
        RetVal = TRUE;
    }
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
 * @fn                - Set Bus Config (Full duplex / Half duplex / Read only)
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
 * @fn                - Set Baudrate - Clock divide
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
    if (SPI_SSM_ENABLE == SPI_SSM)
    {
        pSPIx->CR1 |= SPI_CR1_SSM(BIT_SET);
    }
}

#endif  /* __SPI_HWACCESS_H__ */
