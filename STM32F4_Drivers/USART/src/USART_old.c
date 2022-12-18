#include "USART.h"

/************************************ Private Functions **********************************/
static void USART_PeripheralControl(USART_Type *pUSARTx, uint8 Cmd);

/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void USART_SetBaudRate(USART_Type *pUSARTx, uint32 BaudRate)
{
	/* Variable to hold the APB clock */
	uint32 PCLKx;
	uint32 usartdiv;

	/* Variables to hold Mantissa and Fraction values */
	uint32 M_part, F_part;
	uint32 tempreg = 0;

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

	/* Check for OVER8 configuration bit */
	if ( pUSARTx->CR1 & USART_CR1_OVER8_MASK )
	{
		/* OVER8 = 1 , over sampling by 8 */
		usartdiv = ((25 * PCLKx) / (2 * BaudRate));
	}
	else
	{
		/* Over sampling by 16 */
		usartdiv = ((25 * PCLKx) / (4 * BaudRate));
	}

	/* Calculate the Mantissa part */
	M_part = usartdiv/100;

	/* Place the Mantissa part in appropriate bit position . refer USART_BRR */
	tempreg |= M_part << 4;

	/* Extract the fraction part */
	F_part = (usartdiv - (M_part * 100));

	/* Calculate the final fractional */
	if ( pUSARTx->CR1 & USART_CR1_OVER8_MASK )
	{
	  /* OVER8 = 1 , over sampling by 8 */
	  F_part = ((( F_part * 8)+ 50) / 100) & ((uint8)0x07);

	}else
	{
		/* Over sampling by 16 */
		F_part = ((( F_part * 16)+ 50) / 100) & ((uint8)0x0F);
	}

	/* Place the fractional part in appropriate bit position . refer USART_BRR */
	tempreg |= F_part;

	/* Copy the value of tempreg in to BRR register */
	pUSARTx->BRR = tempreg;
}


/*********************************************************************
 * @fn      		  - USART_Init
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void USART_Init(USART_Type * pUSARTx, Usart_ConfigType * pUARTConfig)
{
	/* Temporary variable to write to Register */
	uint32 tempreg = 0;

/******************************** Configuration of CR1******************************************/

	/* Implement the code to enable the Clock for given USART peripheral */
	 USART_PeriClockControl( pUSARTx, ENABLE );

	/* Enable USART Tx and Rx engines according to the USART_Mode configuration item */
	if ( pUARTConfig->USART_Mode == USART_MODE_ONLY_RX )
	{
		/* Implement the code to enable the Receiver bit field */
		tempreg |= USART_CR1_RE(1);
	}
	else if ( pUARTConfig->USART_Mode == USART_MODE_ONLY_TX )
	{
		/* Implement the code to enable the Transmitter bit field */
		tempreg |= USART_CR1_TE(1);

	}
	else if ( pUARTConfig->USART_Mode == USART_MODE_TXRX )
	{
		/* Implement the code to enable the both Transmitter and Receiver bit fields */
		tempreg |= ( USART_CR1_RE(1) | USART_CR1_RE(1) );
	}

    /* Implement the code to configure the Word length configuration item */
	tempreg |= pUARTConfig->USART_WordLength << USART_CR1_M ;


    /* Configuration of parity control bit fields */
	if ( pUARTConfig->USART_ParityControl == USART_PARITY_EN_EVEN )
	{
		/* Implement the code to enable the parity control */
		tempreg |= USART_CR1_PCE(1);

		/*	Implement the code to enable EVEN parity
			Not required because by default EVEN parity will be selected once you enable the parity control */

	}
	else if ( pUARTConfig->USART_ParityControl == USART_PARITY_EN_ODD )
	{
		/* Implement the code to enable the parity control */
	    tempreg |= USART_CR1_PCE(1);

	    /* Implement the code to enable ODD parity */
	    tempreg |= USART_CR1_PS(1);
	}

    /* Program the CR1 register */
	pUSARTx->CR1 = tempreg;

/******************************** Configuration of CR2******************************************/

	tempreg = 0;

	/* Implement the code to configure the number of stop bits inserted during USART frame transmission */
	tempreg |= pUARTConfig->USART_NoOfStopBits << USART_CR2_STOP;

	/* Program the CR2 register */
	pUSARTx->CR2 = tempreg;

/******************************** Configuration of CR3******************************************/

	tempreg = 0;

	/* Configuration of USART hardware flow control */
	if ( pUARTConfig->USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS )
	{
		/* Implement the code to enable CTS flow control */
		tempreg |= USART_CR3_CTSE(1);
	}
	else if ( pUARTConfig->USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS )
	{
		/* Implement the code to enable RTS flow control */
		tempreg |= USART_CR3_RTSE(1);
	}
	else if ( pUARTConfig->USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS )
	{
		/* Implement the code to enable both CTS and RTS Flow control */
		tempreg |= USART_CR3_CTSE(1) | USART_CR3_RTSE(1);
	}

	pUSARTx->CR3 = tempreg;

/******************************** Configuration of BRR(Baudrate register)******************************************/

	/* Implement the code to configure the baud rate
	   We will cover this in the lecture. No action required here */
	USART_SetBaudRate(pUSARTx,pUARTConfig->USART_Baud);

/******************************** Enable USART Instance ******************************************/
	USART_PeripheralControl(pUSARTx, ENABLE);
}


/*********************************************************************
 * @fn      		  - USART_EnableOrDisable
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
static void USART_PeripheralControl(USART_Type *pUSARTx, uint8 EnOrDi)
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
 * @fn      		  - I2C_PeriClockControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void USART_PeriClockControl(USART_Type *pUSARTx, uint8 EnorDi)
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
 * @fn      		  - USART_GetFlagStatus
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
uint8 USART_GetFlagStatus(USART_Type *pUSARTx, uint8 StatusFlagName)
{
    if( pUSARTx->SR & StatusFlagName )
    {
    	return SET;
    }

	return RESET;
}

/*********************************************************************
 * @fn      		  - USART_SendData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs

 */
void USART_SendData(USART_Type *pUSARTx, uint8 *pTxBuffer, uint32 Len)
{
	uint16 *pdata;
	uint32 i;

	/* Loop over until "Len" number of bytes are transferred */
	for (i = 0 ; i < Len; i++)
	{
		/* Implement the code to wait until TXE flag is set in the SR */
		while( ! USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) );

		/* Check the USART_WordLength item for 9BIT or 8BIT in a frame */
		if( pUARTConfig->USART_WordLength == USART_WORDLEN_9BITS )
		{
			/* If 9BIT load the DR with 2bytes masking  the bits other than first 9 bits */
			pdata = (uint16 *) pTxBuffer;
			pUSARTx->DR = (*pdata & USART_9BITS_DATA_MASK);

			/* Check for USART_ParityControl */
			if ( pUARTConfig->USART_ParityControl == USART_PARITY_DISABLE )
			{
				/* No parity is used in this transfer , so 9bits of user data will be sent
				   Implement the code to increment pTxBuffer twice */
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				/* Parity bit is used in this transfer . so 8bits of user data will be sent
				   The 9th bit will be replaced by parity bit by the hardware */
				pTxBuffer++;
			}
		}
		else
		{
			/* This is 8bit data transfer */
			pUSARTx->DR = (*pTxBuffer  & USART_8BITS_DATA_MASK);

			/* Implement the code to increment the buffer address */
			pTxBuffer++;
		}
	}

	/* Implement the code to wait till TC flag is set in the SR */
	while( ! USART_GetFlagStatus(pUSARTx,USART_FLAG_TC) );
}


/*********************************************************************
 * @fn      		  - USART_ReceiveData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */

void USART_ReceiveData(USART_Type *pUSARTx, uint8 *pRxBuffer, uint32 Len)
{
	uint32 i;
	
	/* Loop over until "Len" number of bytes are transferred */
	for(uint32 i = 0 ; i < Len; i++)
	{
		/* Implement the code to wait until RXNE flag is set in the SR */
		while( ! USART_GetFlagStatus(pUSARTx,USART_FLAG_RXNE) );

		/* Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit */
		if ( pUARTConfig->USART_WordLength == USART_WORDLEN_9BITS )
		{
			/* We are going to receive 9bit data in a frame */

			/* Now, check are we using USART_ParityControl control or not */
			if ( pUARTConfig->USART_ParityControl == USART_PARITY_DISABLE )
			{
				/* No parity is used , so all 9bits will be of user data */

				/* Read only first 9 bits so mask the DR with 0x01FF */
				*((uint16*) pRxBuffer) = (pUSARTx->DR  & USART_9BITS_DATA_MASK);

				/* Now increment the pRxBuffer two times */
				pRxBuffer++;
				pRxBuffer++;
			}
			else
			{
				/*Parity is used, so 8bits will be of user data and 1 bit is parity */
				*pRxBuffer = (pUSARTx->DR  & USART_8BITS_DATA_MASK);
				pRxBuffer++;
			}
		}
		else
		{
			/* We are going to receive 8bit data in a frame */

			/* Now, check are we using USART_ParityControl control or not */
			if ( pUARTConfig->USART_ParityControl == USART_PARITY_DISABLE )
			{
				/* No parity is used , so all 8bits will be of user data */

				/* Read 8 bits from DR */
				*pRxBuffer = (uint8) (pUSARTx->DR  & USART_8BITS_DATA_MASK);
			}
			else
			{
				/* Parity is used, so , 7 bits will be of user data and 1 bit is parity */
				
				/* read only 7 bits , hence mask the DR with 0X7F */
				*pRxBuffer = (uint8) (pUSARTx->DR  & USART_7BITS_DATA_MASK);
			}

			/* Now , increment the pRxBuffer */
			pRxBuffer++;
		}
	}

}

/*********************************************************************
 * @fn      		  - USART_SendDataWithIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
uint8 USART_SendDataIT(USART_Type *pUSARTx,uint8 *pTxBuffer, uint32 Len)
{
	uint8 txstate = TxBusyState;

	if ( txstate != USART_BUSY_IN_TX )
	{
		TxLen = Len;
		pTxBuffer = pTxBuffer;
		TxBusyState = USART_BUSY_IN_TX;

		/* Implement the code to enable interrupt for TXE and TC */
		pUSARTx->CR1 |= USART_CR1_TXEIE(1) | USART_CR1_TCIE(1);
	}

	return txstate;
}


/*********************************************************************
 * @fn      		  - USART_ReceiveDataWithIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
uint8 USART_ReceiveDataIT(USART_Type *pUSARTx,uint8 *pRxBuffer, uint32 Len)
{
	uint8 rxstate = RxBusyState;

	if ( rxstate != USART_BUSY_IN_RX )
	{
		RxLen = Len;
		pRxBuffer = pRxBuffer;
		RxBusyState = USART_BUSY_IN_RX;

		(void)pUSARTx->DR;

		//Implement the code to enable interrupt for RXNE
		pUSARTx->CR1 |= USART_CR1_RXNEIE(1);
	}

	return rxstate;
}


/*********************************************************************
 * @fn      		  - USART_ClearFlag
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Applicable to only USART_CTS_FLAG , USART_LBD_FLAG
 * USART_TC_FLAG,USART_TC_FLAG flags
 *

 */

void USART_ClearFlag(USART_Type *pUSARTx, uint16 StatusFlagName)
{
	pUSARTx->SR &= ~(StatusFlagName);
}

/*********************************************************************
 * @fn      		  - USART_IRQHandler
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void USART_IRQHandling(USART_Type *pUSARTx)
{

	uint32 temp1 , temp2, temp3;

	uint16 *pdata;

/*************************Check for TC flag ********************************************/

    /* Implement the code to check the state of TC bit in the SR */
	temp1 = pUSARTx->SR & USART_SR_TC_MASK;

	/* Implement the code to check the state of TCEIE bit */
	temp2 = pUSARTx->CR1 & USART_CR1_TCIE_MASK;

	if ( temp1 && temp2 )
	{
		/* This interrupt is because of TC */

		/* Close transmission and call application callback if TxLen is zero */
		if ( TxBusyState == USART_BUSY_IN_TX )
		{
			/* Check the TxLen . If it is zero then close the data transmission */
			if ( ! TxLen )
			{
				/* Implement the code to clear the TC flag */
				pUSARTx->SR &= ~USART_SR_TC_MASK;

				/* Implement the code to clear the TCIE control bit */

				/* Reset the application state */
				TxBusyState = USART_READY;

				/* Reset Buffer address to NULL */
				pTxBuffer = NULL;

				/* Reset the length to zero */
				TxLen = 0;

				/* Call the application call back with event USART_EVENT_TX_CMPLT */
				USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_TX_CMPLT);
			}
		}
	}

/*************************Check for TXE flag ********************************************/

	/* Implement the code to check the state of TXE bit in the SR */
	temp1 = pUSARTx->SR & USART_SR_TXE_MASK;

	/* Implement the code to check the state of TXEIE bit in CR1 */
	temp2 = pUSARTx->CR1 & USART_CR1_TXEIE_MASK;


	if ( temp1 && temp2 )
	{
		/* This interrupt is because of TXE */

		if ( TxBusyState == USART_BUSY_IN_TX )
		{
			/* Keep sending data until Txlen reaches to zero */
			if ( TxLen > 0 )
			{
				/* Check the USART_WordLength item for 9BIT or 8BIT in a frame */
				if ( pUARTConfig->USART_WordLength == USART_WORDLEN_9BITS )
				{
					/* If 9BIT load the DR with 2bytes masking  the bits other than first 9 bits */
					pdata = (uint16*) pTxBuffer;
					pUSARTx->DR = (*pdata & USART_9BITS_DATA_MASK);

					/* Check for USART_ParityControl */
					if ( pUARTConfig->USART_ParityControl == USART_PARITY_DISABLE )
					{
						/* No parity is used in this transfer , so 9bits of user data will be sent
						   Implement the code to increment pTxBuffer twice */
						pTxBuffer++;
						pTxBuffer++;
						TxLen -= 2;
					}
					else
					{
						/* Parity bit is used in this transfer . so 8bits of user data will be sent
						   The 9th bit will be replaced by parity bit by the hardware */
						pTxBuffer++;
						TxLen -= 1;
					}
				}
				else
				{
					/* This is 8bit data transfer */
					pUSARTx->DR = (*pTxBuffer  & USART_8BITS_DATA_MASK);

					/* Implement the code to increment the buffer address */
					pTxBuffer++;
					TxLen -= 1;
				}

			}
			if ( TxLen == 0 )
			{
				/* TxLen is zero
				   Implement the code to clear the TXEIE bit (disable interrupt for TXE flag ) */
				pUSARTx->CR1 &= ~USART_CR1_TXEIE_MASK;
			}
		}
	}

/*************************Check for RXNE flag ********************************************/

	temp1 = pUSARTx->SR & USART_SR_RXNE_MASK;
	temp2 = pUSARTx->CR1 & USART_CR1_RXNEIE_MASK;

	if ( temp1 && temp2 )
	{
		/* This interrupt is because of rxne */
		if ( RxBusyState == USART_BUSY_IN_RX )
		{
			if ( RxLen > 0 )
			{
				/* Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit */
				if ( pUARTConfig->USART_WordLength == USART_WORDLEN_9BITS )
				{
					/* We are going to receive 9bit data in a frame */

					/* Now, check are we using USART_ParityControl control or not */
					if ( pUARTConfig->USART_ParityControl == USART_PARITY_DISABLE )
					{
						/* No parity is used , so all 9bits will be of user data */

						/* Read only first 9 bits so mask the DR with 0x01FF */
						*((uint16*) pRxBuffer) = (pUSARTx->DR  & USART_9BITS_DATA_MASK);

						/* Now increment the pRxBuffer two times */
						pRxBuffer++;
						pRxBuffer++;
						RxLen -= 2;
					}
					else
					{
						/* Parity is used, so 8bits will be of user data and 1 bit is parity */
						*pRxBuffer = (pUSARTx->DR  & USART_8BITS_DATA_MASK);
						pRxBuffer++;
						RxLen -= 1;
					}
				}
				else
				{
					/* We are going to receive 8bit data in a frame */

					/* Now, check are we using USART_ParityControl control or not */
					if ( pUARTConfig->USART_ParityControl == USART_PARITY_DISABLE )
					{
						/* No parity is used , so all 8bits will be of user data */

						/* Read 8 bits from DR */
						*pRxBuffer = (uint8) (pUSARTx->DR  & USART_8BITS_DATA_MASK);
					}
					else
					{
						/* Parity is used, so , 7 bits will be of user data and 1 bit is parity */

						/* read only 7 bits , hence mask the DR with 0X7F */
						*pRxBuffer = (uint8) (pUSARTx->DR  & USART_7BITS_DATA_MASK);
					}

					/* Now , increment the pRxBuffer */
					pRxBuffer++;
					RxLen -= 1;
				}
			}	/* if of >0 */
			
			if ( ! RxLen )
			{
				/* Disable the rxne */
				pUSARTx->CR1 &= ~USART_CR1_RXNEIE_MASK;
				RxBusyState = USART_READY;
				USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_RX_CMPLT);
			}
		}
	}


/*************************Check for CTS flag ********************************************/
/* Note : CTS feature is not applicable for UART4 and UART5 */

	/* Implement the code to check the status of CTS bit in the SR */
	temp1 = pUSARTx->SR & USART_SR_CTS_MASK;

	/* Implement the code to check the state of CTSE bit in CR1 */
	temp2 = pUSARTx->CR3 & USART_CR3_CTSE_MASK;

	/* Implement the code to check the state of CTSIE bit in CR3 (This bit is not available for UART4 & UART5.) */
	temp3 = pUSARTx->CR3 & USART_CR3_CTSIE_MASK;

	if ( temp1 && temp2 )
	{
		/* Implement the code to clear the CTS flag in SR */
		pUSARTx->SR &=  ~USART_SR_CTS_MASK;

		/* This interrupt is because of cts */
		USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_CTS);
	}

/*************************Check for IDLE detection flag ********************************************/

	/* Implement the code to check the status of IDLE flag bit in the SR */
	temp1 = pUSARTx->SR & USART_SR_IDLE_MASK;

	/* Implement the code to check the state of IDLEIE bit in CR1 */
	temp2 = pUSARTx->CR1 & USART_CR1_IDLEIE_MASK;

	if ( temp1 && temp2)
	{
		/* Implement the code to clear the IDLE flag. Refer to the RM to understand the clear sequence */
		temp1 = pUSARTx->SR &= ~USART_SR_IDLE_MASK;

		/* This interrupt is because of idle */
		USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_IDLE);
	}

/*************************Check for Overrun detection flag ********************************************/

	/* Implement the code to check the status of ORE flag  in the SR */
	temp1 = pUSARTx->SR & USART_SR_ORE_MASK;

	/* Implement the code to check the status of RXNEIE  bit in the CR1 */
	temp2 = pUSARTx->CR1 & USART_CR1_RXNEIE_MASK;

	if ( temp1  && temp2 )
	{
		/* Need not to clear the ORE flag here, instead give an api for the application to clear the ORE flag */

		/* This interrupt is because of Overrun error */
		USART_ApplicationEventCallback(pUSARTHandle, USART_ERR_ORE);
	}



/*************************Check for Error Flag ********************************************/

/*	Noise Flag, Overrun error and Framing Error in multibuffer communication
	We dont discuss multibuffer communication in this course. please refer to the RM
	The blow code will get executed in only if multibuffer mode is used. */

	temp2 = pUSARTx->CR3 & USART_CR3_EIE_MASK;

	if ( temp2 )
	{
		temp1 = pUSARTx->SR;
		if ( temp1 & USART_SR_FE_MASK )
		{
			/*
				This bit is set by hardware when a de-synchronization, excessive noise or a break character
				is detected. It is cleared by a software sequence (an read to the USART_SR register
				followed by a read to the USART_DR register).
			*/
			USART_ApplicationEventCallback(pUSARTHandle, USART_ERR_FE);
		}

		if ( temp1 & USART_SR_NE_MASK )
		{
			/*
				This bit is set by hardware when noise is detected on a received frame. It is cleared by a
				software sequence (an read to the USART_SR register followed by a read to the
				USART_DR register).
			*/
			USART_ApplicationEventCallback(pUSARTHandle, USART_ERR_NE);
		}

		if ( temp1 & USART_SR_ORE_MASK )
		{
			USART_ApplicationEventCallback(pUSARTHandle, USART_ERR_ORE);
		}
	}
}



/*********************************************************************
 * @fn      		  - USART_ApplicationEventCallback
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
__weak void USART_ApplicationEventCallback(USART_Type *pUSARTx, uint8 event)
{
	/* Default function to avoid compiler warning */
	DEFAULT_FUNCTION(pUSARTx);
}
