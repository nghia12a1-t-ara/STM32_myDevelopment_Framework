#ifndef __USART_HWACCESS_H__
#define __USART_HWACCESS_H__

#include "USART_Base.h"
#include "USART_Types.h"


/*! @brief LPUART interrupt configuration structure, default settings are 0 (disabled) */
typedef enum
{
    USART_INT_TX_DATA_REG_EMPTY = (uint32)USART_CR1_TXEIE_SHIFT,		/*!< Transmit data register empty. */
    USART_INT_TX_COMPLETE       = (uint32)USART_CR1_TCIE_SHIFT,			/*!< Transmission complete. */
    USART_INT_RX_DATA_REG_FULL  = (uint32)USART_CR1_RXNEIE_SHIFT,     	/*!< Receiver data register full. */
    USART_INT_FRAME_ERR_FLAG    = (uint32)USART_CR1_IDLEIE_SHIFT,    	/*!< IDLE error flag. */
    USART_INT_PARITY_ERR_FLAG   = (uint32)USART_CR1_PEIE_SHIFT,    		/*!< Parity error flag. */
} Usart_InterruptType;


/*********************************************************************
 * @fn      		  - Get Clock Value for each USART instance 
 *
 */
__STATIC_INLINE uint32 RCC_GetClockValue(USART_Type * pUSARTx)
{
	/* Get the value of APB bus clock in to the variable PCLKx */
	if ( (pUSARTx == USART1) || (pUSARTx == USART6) )
	{
		//USART1 and USART6 are hanging on APB2 bus
		PCLKx = RCC_GetPCLK2Value();
	}
	else	/* pUSARTx == USART2 */
	{
		PCLKx = RCC_GetPCLK1Value();
	}
}

/*********************************************************************
 * @fn      		  - Enable or Disable USART Instance
 *
 */
__STATIC_INLINE void USART_PeripheralControl(USART_Type *pUSARTx, uint8 EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pUSARTx->CR1 |= USART_CR1_UE_MASK;
	}
	else
	{
		pUSARTx->CR1 &= ~USART_CR1_UE_MASK;
	}
}

/*********************************************************************
 * @fn      		  - Setting Transfer Mode for USART Instance (TX, RX or both)
 *
 */
__STATIC_INLINE void USART_SetTransferMode(USART_Type *pUSARTx, Usart_TransferModeType USART_Mode)
{
	/* Enable USART Tx and Rx engines according to the USART_Mode configuration item */
	if ( USART_Mode == USART_MODE_ONLY_RX )
	{
		/* Implement the code to enable the Receiver bit field */
		pUSARTx->CR1 |= USART_CR1_RE(1);
	}
	else if ( USART_Mode == USART_MODE_ONLY_TX )
	{
		/* Implement the code to enable the Transmitter bit field */
		pUSARTx->CR1 |= USART_CR1_TE(1);

	}
	else if ( USART_Mode == USART_MODE_TXRX )
	{
		/* Implement the code to enable the both Transmitter and Receiver bit fields */
		pUSARTx->CR1 |= ( USART_CR1_RE(1) | USART_CR1_RE(1) );
	}
	else
	{
		/* TODO */
	}
}

/*********************************************************************
 * @fn      		  - Setting Word Length for USART Instance (8 or 9)
 *
 */
__STATIC_INLINE void USART_SetWordLength(USART_Type *pUSARTx, Usart_WordLenType WordLen)
{
	/* Clear bit M of CR1 before write - Default is 8 bits */
	pUSARTx->CR1 &= ~USART_CR1_M_MASK;
	if ( WordLen == USART_WORDLEN_9BITS )
	{
		pUSARTx->CR1 |= USART_CR1_M(1);
	}
	else
	{
		/* TODO */
	}
}

/*********************************************************************
 * @fn      		  - Setting Parity for USART Instance (8 or 9)
 *
 */
__STATIC_INLINE void USART_SetParity(USART_Type *pUSARTx, Usart_ParityType Parity)
{
	/* Clear bit PCE and PS */
	pUSARTx->CR1 &= ~(USART_CR1_PCE_MASK | USART_CR1_PS_MASK);
	
	/* If Parity is enable - even or odd */
	if ( Parity == USART_PARITY_EN_EVEN )
	{
		/* Set enable parity by PCE bit, default even by PS = 0 */
		pUSARTx->CR1 |= USART_CR1_PCE(1);
	}
	else if ( Parity == USART_PARITY_EN_EVEN )
	{
		pUSARTx->CR1 |= USART_CR1_PCE(1);
		pUSARTx->CR1 |= USART_CR1_PS(1);
	}
	else
	{
		/* TODO */
	}
}

/*********************************************************************
 * @fn      		  - Setting Number of Stop Bits for USART Instance
 *
 */
__STATIC_INLINE void USART_SetStopBits(USART_Type *pUSARTx, Usart_StopBitsType StopBits)
{
	/* Clear Stop bits field of USART_CR2 */
	pUSARTx->CR2 &= ~(USART_CR2_STOP_MASK);
	pUSARTx->CR2 |= USART_CR2_STOP(StopBits);
}

/*********************************************************************
 * @fn      		  - Setting Hardware Flow Control for USART Instance
 *
 */
__STATIC_INLINE void USART_SetHWFlowControl(USART_Type *pUSARTx, Usart_HardwareFlowType HWFlow)
{
	/* Configuration of USART hardware flow control */
	if ( HWFlow == USART_HW_FLOW_CTRL_CTS )
	{
		/* Implement the code to enable CTS flow control */
		pUSARTx->CR3 |= USART_CR3_CTSE(1);
	}
	else if ( HWFlow == USART_HW_FLOW_CTRL_RTS )
	{
		/* Implement the code to enable RTS flow control */
		pUSARTx->CR3 |= USART_CR3_RTSE(1);
	}
	else if ( HWFlow == USART_HW_FLOW_CTRL_CTS_RTS )
	{
		/* Implement the code to enable both CTS and RTS Flow control */
		pUSARTx->CR3 |= USART_CR3_CTSE(1) | USART_CR3_RTSE(1);
	}
	else
	{
		/* TODO */
	}
}

/*********************************************************************
 * @fn      		  - Setting Transmit or Receive for USART Instance
 *
 */
__STATIC_INLINE void Usart_SetTransmitterCmd(USART_Type * pUSARTx, boolean EnorDir)
{
    pUSARTx->CR1 = (pUSARTx->CR1 & ~USART_CR1_TE_MASK) | ((EnorDir ? ENABLE : DISABLE) << USART_CR1_TE_MASK);
}

/*********************************************************************
 * @fn      		  - Config USART Interrupt with source
 *
 */
__STATIC_INLINE void Usart_SetIntMode(USART_Type * pUSARTx, Usart_InterruptType IntSrc, boolean EnorDir)
{
	pUSARTx->CR1 = (pUSARTx->CR1 & ~(1UL << (uint32)IntSrc)) | ((EnorDir ? ENABLE : DISABLE) << (uint32)IntSrc);
}

/*********************************************************************
 * @fn      		  - Send Data - 8 bits
 *
 */
static inline void Usart_Putchar(USART_Type * pUSARTx, uint8 Data)
{
    volatile uint8 * DataRegBytes = (volatile uint8 *)(&(pUSARTx->DR));
    DataRegBytes[0] = Data;
}

/*********************************************************************
 * @fn      		  - Send Data - 9 bits
 *
 */
static inline void Usart_Putchar9(USART_Type * pUSARTx, uint16 Data)
{
    uint8 NinthDataBit;
    volatile uint8 * DataRegBytes = (volatile uint8 *)(&(pUSARTx->DR));


    NinthDataBit = (uint8)((Data >> 8U) & 0x1U);

    /* write 8-bits to the data register*/
    DataRegBytes[0] = (uint8)Data;
}

#endif	/* __USART_HWACCESS_H__ */
