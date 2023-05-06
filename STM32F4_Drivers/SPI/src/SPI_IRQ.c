/**
 * Filename     : SPI_IRQ.c
 * Author       : Nghia-Taarabt
 * Create Date  : 18/12/22
 * Brief        : SPI Driver APIs for Interrupt Handler
 */

#include "SPI.h"
#include "SPI_HwAccess.h"

/**
 * Function Pointer to Callback Function
 */
void (* SPI_ISR_Callback[])(void)
{
    [SPI_INT_TX_DATA_REG_EMPTY] = Spi_Tx_Callback,
    [SPI_INT_RX_DATA_REG_FULL]  = Spi_Rx_Callback,
    [SPI_INT_ERROR_TRANSACTION] = Spi_Err_Callback,
};

__weak void Spi_Tx_Callback(void)
{
    DEFAULT_FUNCTION(Spi_Tx_Callback);
}

__weak void Spi_Rx_Callback(void)
{
    DEFAULT_FUNCTION(Spi_Rx_Callback);
}

__weak void Spi_Err_Callback(void)
{
    DEFAULT_FUNCTION(Spi_Err_Callback);
}

/*******************************************************************************
 *
 * Function Name : Spi_IrqHandler
 * Description   : Interrupt handler for USART.
 * This handler uses the buffers stored in the Usart_StateStructureType structs to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *****************************************************************************/

void Spi_IrqHandler(SPI_Type *pSPIx)
{
    
}

void SPI1_IRQHandler(void)
{
    Spi_IrqHandler(SPI1);
}
void SPI2_IRQHandler(void)
{
    Spi_IrqHandler(SPI2);
}
void SPI3_IRQHandler(void)
{
    Spi_IrqHandler(SPI3);
}
void SPI4_IRQHandler(void)
{
    Spi_IrqHandler(SPI4);
}
