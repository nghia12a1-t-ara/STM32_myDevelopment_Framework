/**
 * Filename		: USART_HwAccess.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement Hardware Access Functions
 */

#ifndef __USART_HWACCESS_H__
#define __USART_HWACCESS_H__

#include "USART_Base.h"
#include "USART_Types.h"
#include "Systick.h"
#include "RCC.h"


/** @brief LPUART interrupt configuration structure, default settings are 0 (disabled) */
typedef enum
{
    USART_INT_TX_DATA_REG_EMPTY = (uint32)USART_CR1_TXEIE_SHIFT,		/*!< Transmit data register empty. */
    USART_INT_TX_COMPLETE       = (uint32)USART_CR1_TCIE_SHIFT,			/*!< Transmission complete. */
    USART_INT_RX_DATA_REG_FULL  = (uint32)USART_CR1_RXNEIE_SHIFT,     	/*!< Receiver data register full. */
    USART_INT_FRAME_ERR_FLAG    = (uint32)USART_CR1_IDLEIE_SHIFT,    	/*!< IDLE error flag. */
    USART_INT_PARITY_ERR_FLAG   = (uint32)USART_CR1_PEIE_SHIFT,    		/*!< Parity error flag. */
} Usart_InterruptType;

/**
 * @brief LPUART status flags.
 * This provides constants for the LPUART status flags for use in the UART functions.
 */
typedef enum
{
    USART_FLAG_TX_DATA_REG_EMPTY 	= (uint32)USART_SR_TXE_SHIFT,
                                                /*!< Tx data register empty flag, sets when Tx buffer is empty */
    USART_FLAG_TX_COMPLETE			= (uint32)USART_SR_TC_SHIFT,
                                                /*!< Transmission complete flag, sets when transmission activity complete */
    USART_FLAG_RX_DATA_REG_FULL		= (uint32)USART_SR_RXNE_SHIFT,
                                                /*!< Rx data register full flag, sets when the receive data buffer is full */
    USART_FLAG_RX_OVERRUN			= (uint32)USART_SR_ORE_SHIFT,
                                                /*!< Rx Overrun sets if new data is received before data is read */
    USART_FLAG_NOISE_DETECT			= (uint32)USART_SR_NE_SHIFT,
                                                /*!< Rx takes 3 samples of each received bit. If these differ, the flag sets */
    USART_FLAG_FRAME_ERR			= (uint32)USART_SR_FE_SHIFT,
                                                /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    USART_FLAG_PARITY_ERR			= (uint32)USART_SR_PE_SHIFT
} Usart_StatusFlagType;

/*********************************************************************
 * @fn      		  - Get Clock Value for each USART instance 
 *
 */
__STATIC_INLINE uint32 RCC_GetClockValue(USART_Type * pUSARTx)
{
	uint32 PCLKx = 0u;

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

	return PCLKx;
}

/*********************************************************************
 * @fn      		  - Peripheral Clock Control
 *
 */
__STATIC_INLINE void USART_PeriClockControl(USART_Type *pUSARTx, uint8 EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pUSARTx == USART1)
		{
			USART1_PCLK_EN();
		}
		else if (pUSARTx == USART2)
		{
			USART2_PCLK_EN();
		}
		else if (pUSARTx == USART3)
		{
			USART3_PCLK_EN();
		}
		else if (pUSARTx == UART4)
		{
			USART4_PCLK_EN();
		}
	}
	else
	{
		//TODO
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
    pUSARTx->CR1 = (pUSARTx->CR1 & ~USART_CR1_TE_MASK) | ((EnorDir ? ENABLE : DISABLE) << USART_CR1_TE_SHIFT);
}
__STATIC_INLINE void Usart_SetReceiveCmd(USART_Type * pUSARTx, boolean EnorDir)
{
    pUSARTx->CR1 = (pUSARTx->CR1 & ~USART_CR1_RE_MASK) | ((EnorDir ? ENABLE : DISABLE) << USART_CR1_RE_SHIFT);
}

/*********************************************************************
 * @fn      		  - Config USART Interrupt with source
 *
 */
__STATIC_INLINE void Usart_SetIntMode(USART_Type * pUSARTx, Usart_InterruptType IntSrc, boolean EnorDir)
{
	pUSARTx->CR1 = (pUSARTx->CR1 & ~(1UL << (uint32)IntSrc)) | ((EnorDir ? ENABLE : DISABLE) << (uint32)IntSrc);
}
__STATIC_INLINE boolean Usart_GetIntMode(const USART_Type * pUSARTx, Usart_InterruptType IntSrc)
{
    boolean RetVal = FALSE;
    RetVal = (((pUSARTx->CR1 >> (uint32)(IntSrc)) & 1U) > 0U);
    return RetVal;
}

/*********************************************************************
 * @fn      		  - Send Data - 8 bits
 *
 */
__STATIC_INLINE void Usart_Putchar(USART_Type * pUSARTx, uint8 Data)
{
    volatile uint8 * DataRegBytes = (volatile uint8 *)(&(pUSARTx->DR));
    DataRegBytes[0] = Data;
}

/*********************************************************************
 * @fn      		  - Send Data - 9 bits
 *
 */
__STATIC_INLINE void Usart_Putchar9(USART_Type * pUSARTx, uint16 Data)
{
    uint8 NinthDataBit;
    volatile uint8 * DataRegBytes = (volatile uint8 *)(&(pUSARTx->DR));

    NinthDataBit = (uint8)((Data >> 8U) & 0x1U);

    /* write 8-bits to the data register*/
    DataRegBytes[0] = (uint8)NinthDataBit;
}

/*********************************************************************
 * @fn      		  - Receive Data - 8 bits
 *
 */
__STATIC_INLINE uint8 Usart_Getchar(const USART_Type * pUSARTx)
{
    return (uint8)(pUSARTx->DR & USART_8BITS_DATA_MASK);
}

/*********************************************************************
 * @fn      		  - Receive Data - 9 bits
 *
 */
__STATIC_INLINE uint16 Usart_Getchar9(const USART_Type * pUSARTx)
{
    uint16 ReadData;

    /* get ninth bit from lpuart data register - @TODO */
    ReadData = (uint16)(((pUSARTx->DR) & 1U) << 8);
	
    return ReadData;
}

/**
 * @brief  USART get status flag
 *
 * This function returns the state of a status flag.
 */
__STATIC_INLINE boolean Usart_GetStatusFlag(const USART_Type * pUSARTx, Usart_StatusFlagType StatusFlag)
{
    boolean RetVal = FALSE;
    RetVal = (((pUSARTx->SR >> (uint32)(StatusFlag)) & 1U) > 0U);
    return RetVal;
}


/**
 * @brief  Clears the error flags treated by the driver
 *
 * This function clears the error flags treated by the driver.
 * *
 * @param Base USART Base pointer
 */
static inline void Usart_ClearErrorFlags(USART_Type * pUSARTx)
{
    uint32 Mask = USART_SR_PE_MASK | \
                  USART_SR_FE_MASK | \
                  USART_SR_NE_MASK | \
                  USART_SR_ORE_MASK;

    pUSARTx->SR &= ~USART_SR_REG_FLAGS_MASK;
    pUSARTx->SR |= Mask;
}

/**
 * @brief USART clears an individual status flag.
 *
 * This function clears an individual status flag
 *
 * @param Base USART base pointer
 * @param StatusFlag  Desired USART status flag to clear
 * @return USART_STATUS_SUCCESS if successful or STATUS_ERROR if an error occured
 */
static inline void Usart_ClearStatusFlag(USART_Type * pUSARTx, Usart_StatusFlagType StatusFlag)
{
	pUSARTx->SR &= ~USART_SR_REG_FLAGS_MASK;

    switch(StatusFlag)
    {
        case USART_FLAG_RX_OVERRUN:
            pUSARTx->SR |= USART_SR_ORE_MASK;
            break;

        case USART_FLAG_NOISE_DETECT:
            pUSARTx->SR |= USART_SR_NE_MASK;
            break;

        case USART_FLAG_FRAME_ERR:
			pUSARTx->SR |= USART_SR_FE_MASK;
            break;

        case USART_FLAG_PARITY_ERR:
        	pUSARTx->SR |= USART_SR_PE_MASK;
            break;
        default:
            /* Dummy code */
            break;
    }
}


/******************************************************************************/
/****************************** TIMEOUT FUNCTIONS *****************************/
/**
 * @brief   : Prepare for timeout checking
 * @
 * @return  : None
 */
__STATIC_INLINE void Usart_StartTimeout(uint32 * StartTimeOut, uint32 *TimeoutTicksOut, uint32 TimeoutUs)
{
    *StartTimeOut    = Systick_GetCounter();
    *TimeoutTicksOut = Systick_MicrosToTicks(TimeoutUs);
}

/**
 * @brief   : Checks for timeout condition
 * @
 * @return  TRUE     Timeout occurs
 *          FALSE    Timeout does not occur
 */
__STATIC_INLINE boolean Usart_CheckTimeout(uint32 * StartTime, uint32 * ElapsedTicks, uint32 TimeoutTicks)
{
    uint32 CurrentElapsedTicks = Systick_GetElapsed(StartTime);
    *ElapsedTicks += CurrentElapsedTicks;
    return ((*ElapsedTicks >= TimeoutTicks) ? TRUE : FALSE);
}

#endif	/* __USART_HWACCESS_H__ */
