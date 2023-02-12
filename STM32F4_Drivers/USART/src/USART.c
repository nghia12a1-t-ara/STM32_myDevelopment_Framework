/**
 * Filename		: USART.c
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement USART Driver
 */

#include "USART.h"
#include "USART_HwAccess.h"

/*****************************************************************************************/
/************************************ Private Variables **********************************/
/* Pointer to Usart runtime state structure */
static Usart_StateRuntimeType * Usart_StateRuntime_Pointer[USART_INSTANCE_COUNT];

/** @brief User config structure. */
const Usart_UserConfigType * Usart_UserConfig_Pointer[USART_INSTANCE_COUNT];

static USART_Type * const Usart_Base_Pointer[USART_INSTANCE_COUNT] = USART_BASE_PTRS;

/*****************************************************************************************/
/************************************ Private Functions **********************************/
static Usart_StatusType Usart_StartSendDataINT(const uint8 Instance, const uint8 *TxBuff, const uint32 TxSize);
static Usart_StatusType Usart_StartReceiveDataINT(const uint8 Instance, uint8 * RxBuff, const uint32 RxSize);
static void Usart_PutData(const uint8 Instance);
static void Usart_GetData(const uint8 Instance);
static void Usart_StartGetData(const uint8 Instance, uint32 * StartTime, uint32 * ElapsedTicks, uint32 TimeoutTicks);

/* ----------------- Interrupt Handler Functions ----------------- */
static void Usart_RxIrqHandler(const uint8 Instance);
static void Usart_TxEmptyIrqHandler(const uint8 Instance);
static void Usart_TxCompleteIrqHandler(const uint8 Instance);
static void Usart_ErrIrqHandler(const uint8 Instance);

static void Usart_CompleteReceiveDataINT(const uint8 Instance);
static void Usart_CompleteSendDataINT(const uint8 Instance);
static Usart_StatusType Usart_StartSendDataINT(const uint8 Instance, const uint8 *TxBuff, const uint32 TxSize);
static Usart_StatusType Usart_StartReceiveDataINT(const uint8 Instance, uint8 * RxBuff, const uint32 RxSize);

/*****************************************************************************************/
/*********************************************************************
 * @fn      		  - USART_Init
 *
 * @brief             - Initialize USART Driver
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - UserConfig 	- USART User Configuration
 *
 * @return            -
 *
 * @Note              -
 */
void USART_Init(const uint8 Instance, const Usart_UserConfigType * UserConfig)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr;
	uint8 * ClearStructPtr;
	uint8 Index;
	
	/* Assign Config to Static Variables */
	Usart_UserConfig_Pointer[Instance] 		= UserConfig;
	Usart_StateRuntime_Pointer[Instance] 	= UserConfig->StateStruct;
	UartStatePtr = Usart_StateRuntime_Pointer[Instance];
	ClearStructPtr = (uint8 *)UartStatePtr;
	
    /* Clear the state struct for this Instance. */
    for (Index = 0; Index < sizeof(Usart_StateRuntimeType); Index++)
    {
        ClearStructPtr[Index] = 0;
    }	
	
	/* Implement the code to enable the Clock for given USART peripheral */
	USART_PeriClockControl(Base, ENABLE);
	
	/* Enable USART Tx and Rx engines according to the USART_Mode configuration item */
	USART_SetTransferMode(Base, UserConfig->USART_Mode);
	
	/* Implement the code to configure the Word length configuration item */
	USART_SetWordLength(Base, UserConfig->USART_WordLength);
	
	/* Configuration of parity control bit fields */
	USART_SetParity(Base, UserConfig->USART_ParityControl);
	
	/* Implement the code to configure the number of stop bits inserted during USART frame transmission */
	USART_SetStopBits(Base, UserConfig->USART_NoOfStopBits);
	
	/* Configuration of USART hardware flow control */
	USART_SetHWFlowControl(Base, UserConfig->USART_HWFlowControl);
	
	/* ---------------- Setup Baudrate for USART Instance ---------------- */
	Usart_SetBaudRate(Instance, UserConfig->USART_Baud);
	
    /* Initialize last driver operation status */
    UartStatePtr->TransmitStatus = USART_STATUS_SUCCESS;
    UartStatePtr->ReceiveStatus = USART_STATUS_SUCCESS;	
	UartStatePtr->USART_Baud = UserConfig->USART_Baud;
	
	/* ---------------- Enable USART Instance ---------------- */
	USART_PeripheralControl(Base, ENABLE);
}

/*********************************************************************
 * @fn      		  - Usart_SyncSendData
 *
 * @brief             - Synchronus Send Data - Wait to send ok or timeout
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - TxBuff 		- Buffer to transmission
 * @param[in]         - TxSize 		- Size of Buffer to transmission
 * @param[in]         - Timeout 	- Timeout if data cannot transmit
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_SyncSendData(const uint8 Instance,
									const uint8 *TxBuff,
									const uint32 TxSize,
									const uint32 Timeout)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
	Usart_StatusType RetVal = USART_STATUS_SUCCESS;
	boolean IsReturn = FALSE;
	
	/* Timeout Setup Variables */
	uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    /* Check driver is not busy transmitting data from a previous asynchronous call */
    if (UartStatePtr->IsTxBusy)
    {
        RetVal = USART_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        UartStatePtr->IsTxBusy = TRUE;
        UartStatePtr->TxBuff = TxBuff;
        UartStatePtr->TxSize = TxSize;

        UartStatePtr->TransmitStatus = USART_STATUS_BUSY;

        /* Disble Tx data register empty and transmission complete interrupt */
        Usart_SetIntMode(Base, USART_INT_TX_DATA_REG_EMPTY, DISABLE);
        Usart_SetIntMode(Base, USART_INT_TX_COMPLETE, DISABLE);

        /* Enable the USART transmitter */
        Usart_SetTransmitterCmd(Base, TRUE);
		
		/* Start Timeout - Can using Systick Timer */
        Usart_StartTimeout(&StartTime, &TimeoutTicks, Timeout);
		
		/* Wait transfer successfully or Timeout occurs */
        while ( (UartStatePtr->TxSize > 0U) && \
                !Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) )
        {
            Usart_PutData(Instance);
            while ( !Usart_GetStatusFlag(Base, USART_FLAG_TX_DATA_REG_EMPTY)  && \
                    !Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) );
        }

        /* Disable the USART transmitter */
        Usart_SetTransmitterCmd(Base, DISABLE);

        /* Check if Timeout occur */
        if ( Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) )
        {
            UartStatePtr->TransmitStatus = USART_STATUS_TIMEOUT;
        }
		else	/* The transmit process is complete */
        {
            UartStatePtr->TransmitStatus = USART_STATUS_SUCCESS;
        }
        UartStatePtr->IsTxBusy = FALSE;
        RetVal = UartStatePtr->TransmitStatus;
    }
    return RetVal;
}


/*********************************************************************
 * @fn      		  - Usart_AsyncSendData
 *
 * @brief             - Asynchronus Send Data - Send Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - TxBuff 		- Buffer to transmission
 * @param[in]         - TxSize 		- Size of Buffer to transmission
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_AsyncSendData(const uint8 Instance,
									const uint8 *TxBuff,
									const uint32 TxSize)
{
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	Usart_StatusType RetVal = USART_STATUS_SUCCESS;
	boolean IsReturn = FALSE;
	
	if (UartStatePtr->IsTxBusy)
    {
        RetVal = USART_STATUS_BUSY;
        IsReturn = TRUE;
    }
	if (!IsReturn)
    {
        UartStatePtr->IsTxBusy = TRUE;

        if (USART_USING_INTERRUPTS == UartUserCfg->USART_Transfer)
        {
            /* Start the transmission process using interrupts */
            RetVal = Usart_StartSendDataINT(Instance, TxBuff, TxSize);
        }
#if (USART_DMA_ENABLED == ON)
        else
        {
            /* Start the transmission process using DMA */
            /*RetVal = Usart_StartSendDataDMA(Instance, TxBuff, TxSize);*/
        }
#endif
    }
    return RetVal;
}

/*********************************************************************
 * @fn      		  - Usart_SyncReceiveData
 *
 * @brief             - Synchronus Receive Data - Wait to Receive ok or timeout
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - RxBuff 		- Buffer to Receive
 * @param[in]         - RxSize 		- Size of Buffer to Receive
 * @param[in]         - Timeout 	- Timeout if data cannot Receive
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_SyncReceiveData(const uint8 Instance,
                                       uint8 *RxBuff,
                                       const uint32 RxSize,
                                       const uint32 Timeout)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
	Usart_StatusType RetVal = USART_STATUS_SUCCESS;
	boolean IsReturn = FALSE;
	
	/* Timeout Setup Variables */
	uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    /* Check driver is not busy receiving data from a previous asynchronous call */
    if (UartStatePtr->IsRxBusy)
    {
        RetVal = USART_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        UartStatePtr->IsRxBusy = TRUE;
        UartStatePtr->RxBuff = RxBuff;
        UartStatePtr->RxSize = RxSize;
        UartStatePtr->ReceiveStatus = USART_STATUS_BUSY;

        /* Disble Rx data register full */
        Usart_SetIntMode(Base, USART_INT_RX_DATA_REG_FULL, DISABLE);
        /* Enable the USART receiver */
        Usart_SetReceiveCmd((USART_Type *)Base, DISABLE);

        Usart_StartTimeout(&StartTime, &TimeoutTicks, Timeout);

        Usart_StartGetData(Instance, &StartTime, &ElapsedTicks, TimeoutTicks);

        /* Check if Timeout occur */
        if (Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks))
        {
            UartStatePtr->ReceiveStatus = USART_STATUS_TIMEOUT;
        }

        /* Check other success receiving case*/
        if (USART_STATUS_BUSY == UartStatePtr->ReceiveStatus)
        {
            UartStatePtr->ReceiveStatus = USART_STATUS_SUCCESS;
        }

        if ((0U == UartStatePtr->RxSize) && (USART_STATUS_RX_OVERRUN == UartStatePtr->ReceiveStatus))
        {
            UartStatePtr->ReceiveStatus = USART_STATUS_SUCCESS;
        }

        /* Disable the LPUART receiver */
        Usart_SetReceiveCmd((USART_Type *)Base, DISABLE);

        UartStatePtr->IsRxBusy = FALSE;

        /* Read dummy to clear RDRF flag */
        (void)Usart_Getchar(Base);

        RetVal = UartStatePtr->ReceiveStatus;
    }
    return RetVal;
}


/*********************************************************************
 * @fn      		  - Usart_AsyncReceiveData
 *
 * @brief             - Asynchronus Receive Data - Receive Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- USART Hardware Instance
 * @param[in]         - RxBuff 		- Buffer to Receive
 * @param[in]         - RxSize 		- Size of Buffer to Receive
 *
 * @return            - Usart_StatusType
 *
 * @Note              -
 */
Usart_StatusType Usart_AsyncReceiveData(const uint8 Instance,
                                        uint8 * RxBuff,
                                        const uint32 RxSize)
{
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];	
	Usart_StatusType RetVal = USART_STATUS_SUCCESS;
	boolean IsReturn = FALSE;
	
    /* Check it's not busy receiving data from a previous function call */
    if (UartStatePtr->IsRxBusy)
    {
        RetVal = USART_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        UartStatePtr->IsRxBusy = TRUE;

        if (USART_USING_INTERRUPTS == UartUserCfg->USART_Transfer)
        {
            /* Start the reception process using interrupts */
            RetVal = Usart_StartReceiveDataINT(Instance, RxBuff, RxSize);
        }
#if (USART_DMA_ENABLED == ON)
        else
        {
            /* Start the transmission process using DMA */
            /*RetVal = Usart_StartReceiveDataDMA(Instance, RxBuff, RxSize);*/
        }
#endif
    }
    return RetVal;
}

/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *
 * @brief             - Setting Baudrate for USART Driver
 *
 * @param[in]         - Instance - number of Hardware Instance
 * @param[in]         - BaudRate
 *
 * @return            -
 *
 * @Note              -
 */
void Usart_SetBaudRate(const uint8 Instance, Usart_BaudrateType BaudRate)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	
	/* Variable to hold the APB clock */
	uint32 PCLKx;
	uint32 usartdiv;

	/* Variables to hold Mantissa and Fraction values */
	uint32 M_part, F_part;
	uint32 tempreg = 0;

	PCLKx = RCC_GetClockValue(Base);

	/* Check for OVER8 configuration bit */
	if ( Base->CR1 & USART_CR1_OVER8_MASK )
	{
		/* OVER8 = 1 , over sampling by 8 */
		usartdiv = ((25 * PCLKx) / (2 * (uint32)BaudRate));
	}
	else
	{
		/* Over sampling by 16 */
		usartdiv = ((25 * PCLKx) / (4 * (uint32)BaudRate));
	}

	/* Calculate the Mantissa part */
	M_part = usartdiv/100;

	/* Place the Mantissa part in appropriate bit position . refer USART_BRR */
	tempreg |= M_part << 4;

	/* Extract the fraction part */
	F_part = (usartdiv - (M_part * 100));

	/* Calculate the final fractional */
	if ( Base->CR1 & USART_CR1_OVER8_MASK )
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
	Base->BRR = tempreg;
}

/*******************************************************************************
 *
 * Function Name : Usart_IrqHandler
 * Description   : Interrupt handler for USART.
 * This handler uses the buffers stored in the Usart_StateStructureType structs to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *****************************************************************************/
void Usart_IrqHandler(const uint8 Instance)
{
    USART_Type * Base = Usart_Base_Pointer[Instance];
	const Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];	
    boolean IsReturn = FALSE;

    /* Case of spurious interrupt when driver is not at all initialized or it is not in transmit/receive process*/
    if (NULL_PTR == UartStatePtr)
    {
        /* Read dummy to clear RDRF flag if it is set*/
        (void)Usart_Getchar(Base);
        /* Clear all the error flags */
        Usart_ClearErrorFlags(Base);
        /* Transmit flags can not be cleared, return to exit */
    }
    else
    {
        Usart_ErrIrqHandler(Instance);
        /* Handle receive data full interrupt */
        if (Usart_GetStatusFlag(Base, USART_FLAG_RX_DATA_REG_FULL))
        {
            if (Usart_GetIntMode(Base, USART_INT_RX_DATA_REG_FULL))
            {
                Usart_RxIrqHandler(Instance);
            }
            /* Case of spurious interrupt when the interupt enable flag is not set and respective interrupt status flag is set */
            else
            {
                /* Read dummy to clear RDRF flag */
                (void)Usart_Getchar(Base);
            }
            IsReturn = TRUE;
        }
        /* Handle transmitter data register empty interrupt */
        if (Usart_GetStatusFlag(Base, USART_FLAG_TX_DATA_REG_EMPTY) && (FALSE == IsReturn))
        {
            if (Usart_GetIntMode(Base, USART_INT_TX_DATA_REG_EMPTY))
            {
                Usart_TxEmptyIrqHandler(Instance);
                IsReturn = TRUE;
            }
            /* Case of spurious interrupt when the interupt enable flag is not set and respective interrupt status flag is set */
            else
            {
                /* Do nothing, because TDRE can not clear without affecting to normal operation*/
            }
        }
        /* Handle transmission complete interrupt */
        if (Usart_GetStatusFlag(Base, USART_FLAG_TX_COMPLETE) && (FALSE == IsReturn))
        {
            if (Usart_GetIntMode(Base, USART_INT_TX_COMPLETE))
            {
                Usart_TxCompleteIrqHandler(Instance);
            }
            /* Case of spurious interrupt when the interupt enable flag is not set and respective interrupt status flag is set */
            else
            {
                /* Do nothing, because TC can not clear without affecting to normal operation*/
            }
        }
    }
}

/*******************************************************************************
 *
 * Function Name : Usart_RxIrqHandler
 * Description   : Rx Interrupt handler for USART.
 * This function treats the rx full interrupt.
 *
 *****************************************************************************/
static void Usart_RxIrqHandler(const uint8 Instance)
{
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	const Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];

    /* Get data and put in receive buffer  */
    Usart_GetData(Instance);

    /* Check if this was the last byte in the current buffer */
    if (0U == UartStatePtr->RxSize)
    {
        /* Invoke callback if there is one (callback may reset the rx buffer for continuous reception) */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, USART_EVENT_RX_FULL, UartUserCfg->CallbackParam);
        }
    }

    /* Finish reception if this was the last byte received */
    if (0U == UartStatePtr->RxSize)
    {
        /* Complete transfer (disable rx logic) */
        Usart_CompleteReceiveDataINT(Instance);

        /* Invoke callback if there is one */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, USART_EVENT_END_TRANSFER, UartUserCfg->CallbackParam);
        }
    }
}

/*******************************************************************************
 *
 * Function Name : Usart_TxEmptyIrqHandler
 * Description   : Tx Empty Interrupt handler for USART.
 * This function treats the tx empty interrupt.
 *
 *****************************************************************************/
static void Usart_TxEmptyIrqHandler(const uint8 Instance)
{
    USART_Type * Base = Usart_Base_Pointer[Instance];
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	const Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];

    /* Check if there are any more bytes to send */
    if (UartStatePtr->TxSize > 0U)
    {
        /* Transmit the data */
        Usart_PutData(Instance);

        /* Check if this was the last byte in the current buffer */
        if ((0U == UartStatePtr->TxSize) && (UartUserCfg->Callback != NULL_PTR))
        {
            /* Invoke callback if there is one (callback may reset the tx buffer for continuous transmission)*/
            UartUserCfg->Callback(Instance, USART_EVENT_TX_EMPTY, UartUserCfg->CallbackParam);
        }
        /* If there's no new data, disable tx empty interrupt and enable transmission complete interrupt */
        if (0U == UartStatePtr->TxSize)
        {
            Usart_SetIntMode(Base, USART_INT_TX_DATA_REG_EMPTY, DISABLE);
            Usart_SetIntMode(Base, USART_INT_TX_COMPLETE, ENABLE);
        }
    }
}

/*******************************************************************************
 *
 * Function Name : Usart_TxCompleteIrqHandler
 * Description   : Tx Complete Interrupt handler for USART.
 * This function treats the tx complete interrupt.
 *
 *****************************************************************************/
static void Usart_TxCompleteIrqHandler(const uint8 Instance)
{
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	const Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];

    if (0U == UartStatePtr->TxSize)
    {
        if (USART_USING_INTERRUPTS == UartUserCfg->USART_Transfer)
        {
            /* Complete the interrupt based transfer */
            Usart_CompleteSendDataINT(Instance);
        }
        /* Invoke callback if there is one */
        if (UartUserCfg->Callback != NULL_PTR)
        {
            UartUserCfg->Callback(Instance, USART_EVENT_END_TRANSFER, UartUserCfg->CallbackParam);
        }
    }
}

/*******************************************************************************
 *
 * Function Name : Usart_ErrIrqHandler
 * Description   : Error Interrupt handler for USART.
 * This function treats the error interrupts.
 *
 *****************************************************************************/
static void Usart_ErrIrqHandler(const uint8 Instance)
{
    USART_Type * Base = Usart_Base_Pointer[Instance];
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
    boolean IsError = FALSE;
    boolean IsReturn = FALSE;

    /* Handle receive overrun interrupt */
    if (Usart_GetStatusFlag(Base, USART_FLAG_RX_OVERRUN))
    {
        /* Clear the flag */
        Usart_ClearStatusFlag(Base, USART_FLAG_RX_OVERRUN);
        /* Case of spurious interrupt when interrupt enable bit is not set*/
#ifdef USART_INT_RX_OVERRUN
        if (!Usart_GetIntMode(Base, USART_INT_RX_OVERRUN))
#else
        if (0)
#endif
        {
            IsReturn = TRUE;
        }
        else
        {
            /* Update the status */
            IsError = TRUE;
            UartStatePtr->ReceiveStatus = USART_STATUS_RX_OVERRUN;
        }
    }
    /* Handle framing error interrupt */
    if (Usart_GetStatusFlag(Base, USART_FLAG_FRAME_ERR) && (FALSE == IsReturn))
    {
        /* Clear the flag */
        Usart_ClearStatusFlag(Base, USART_FLAG_FRAME_ERR);
        /* Case of spurious interrupt when interrupt enable bit is not set*/
        if (!Usart_GetIntMode(Base, USART_INT_FRAME_ERR_FLAG))
        {
            IsReturn = TRUE;
        }
        else
        {
            /* Update the status */
            IsError = TRUE;
            UartStatePtr->ReceiveStatus = USART_STATUS_FRAMING_ERROR;
        }
    }
    /* Handle parity error interrupt */
    if (Usart_GetStatusFlag(Base, USART_FLAG_PARITY_ERR) && (FALSE == IsReturn))
    {
        /* Clear the flag */
        Usart_ClearStatusFlag(Base, USART_FLAG_PARITY_ERR);
        /* Case of spurious interrupt when interrupt enable bit is not set*/
        if (!Usart_GetIntMode(Base, USART_INT_PARITY_ERR_FLAG))
        {
            IsReturn = TRUE;
        }
        else
        {
            /* Update the status */
            IsError = TRUE;
            UartStatePtr->ReceiveStatus = USART_STATUS_PARITY_ERROR;
        }
    }
    /* Handle noise error interrupt */
	// if (Usart_GetStatusFlag(Base, USART_FLAG_NOISE_DETECT) && (FALSE == IsReturn))
    // {
        // /* Clear the flag */
        // Usart_ClearStatusFlag(Base, USART_FLAG_NOISE_DETECT);
        // /* Case of spurious interrupt when interrupt enable bit is not set*/
        // if (!Usart_GetIntMode(Base, USART_INT_NOISE_ERR_FLAG))
        // {
            // IsReturn = TRUE;
        // }
        // else
        // {
            // /* Update the internal status */
            // IsError = TRUE;
            // UartStatePtr->ReceiveStatus = USART_STATUS_NOISE_ERROR;
        // }
    // }
    if (FALSE == IsReturn)
    {
        if (TRUE == IsError)
        {
            if (USART_USING_INTERRUPTS == UartUserCfg->USART_Transfer)
            {
                /* Complete the transfer (disable rx logic) */
                Usart_CompleteReceiveDataINT(Instance);
            }
#if (USART_DMA_ENABLED == ON)
            else
            {
                /* Complete the transfer (stop DMA channel) */
                /*(void)Dma_Ip_SetLogicChannelCommand(UartUserCfg->RxDMAChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
                Usart_CompleteReceiveUsingDma(Instance);*/
            }
#endif
            /* Invoke callback if there is one */
            if (UartUserCfg->Callback != NULL_PTR)
            {
                UartUserCfg->Callback(Instance, USART_EVENT_ERROR, UartUserCfg->CallbackParam);
            }
        }
    }
}


/*******************************************************************************
 *
 * Function Name : Usart_CompleteReceiveDataINT
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 *
 ******************************************************************************/
static void Usart_CompleteReceiveDataINT(const uint8 Instance)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];

    /* Disable all error interrupts */
    /* Usart_SetIntMode(Base, USART_INT_RX_OVERRUN, DISABLE);
       Usart_SetIntMode(Base, USART_INT_NOISE_ERR_FLAG, DISABLE); */
    Usart_SetIntMode(Base, USART_INT_PARITY_ERR_FLAG, DISABLE);
    Usart_SetIntMode(Base, USART_INT_FRAME_ERR_FLAG, DISABLE);

    /* Disable receive data full and rx overrun interrupt. */
    Usart_SetIntMode(Base, USART_INT_RX_DATA_REG_FULL, DISABLE);

    /* Disable receiver */
    Usart_SetReceiveCmd(Base, DISABLE);

    /* Read dummy to clear RDRF flag */
    (void)Usart_Getchar(Base);

    /* Update the information of the module driver state */
    UartStatePtr->IsRxBusy = FALSE;

    if (USART_STATUS_BUSY == UartStatePtr->ReceiveStatus)
    {
        UartStatePtr->ReceiveStatus = USART_STATUS_SUCCESS;
    }
}

/******************************************************************************
 *
 * Function Name : Usart_CompleteSendDataINT
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 *
 ******************************************************************************/
static void Usart_CompleteSendDataINT(const uint8 Instance)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    if (USART_STATUS_BUSY != UartStatePtr->TransmitStatus)
    {
        /* If the transfer is aborted or timed out, disable tx empty interrupt */
        Usart_SetIntMode(Base, USART_INT_TX_DATA_REG_EMPTY, FALSE);
    }

    /* Disable transmission complete interrupt */
    Usart_SetIntMode(Base, USART_INT_TX_COMPLETE, FALSE);

    Usart_StartTimeout(&StartTime, &TimeoutTicks, USART_TIMEOUT_VALUE_US);
    /* Wait until the data is completely shifted out of shift register */
    while (!Usart_GetStatusFlag(Base, USART_FLAG_TX_COMPLETE) && \
           !Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks))
    {}

    if (Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks))
    {
        /* In case timeout occur */
        UartStatePtr->TransmitStatus = USART_STATUS_TIMEOUT;
    }
    /* Disable transmitter */
    Usart_SetTransmitterCmd(Base, DISABLE);

    if (USART_STATUS_BUSY == UartStatePtr->TransmitStatus)
    {
        /* If the transfer is completed, update the transmit status */
        UartStatePtr->TransmitStatus = USART_STATUS_SUCCESS;
    }

    /* Update the internal busy flag */
    UartStatePtr->IsTxBusy = FALSE;
}

/*********************************************************************
 * @fn      		  - Usart_StartSendDataINT
 *
 * @brief             - Initiate (start) a transmit by beginning the process of
 * 						sending data and enabling the interrupt.
 */
static Usart_StatusType Usart_StartSendDataINT(const uint8 Instance,
                                               const uint8 *TxBuff,
                                               const uint32 TxSize)
{
    USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];	

    /* Initialize state structure */
    UartStatePtr->TxBuff = TxBuff;
    UartStatePtr->TxSize = TxSize;
    UartStatePtr->TransmitStatus = USART_STATUS_BUSY;

    /* Enable the USART Transmitter */
    Usart_SetTransmitterCmd(Base, ENABLE);

    /* Enable TX Empty Interrupt */
    Usart_SetIntMode(Base, USART_INT_TX_DATA_REG_EMPTY, ENABLE);

    return USART_STATUS_SUCCESS;
}

/*********************************************************************
 * @fn      		  - Usart_StartReceiveDataINT
 *
 * @brief             - Initiate (start) a transmit by beginning the process of
 * 						sending data and enabling the interrupt.
 */
static Usart_StatusType Usart_StartReceiveDataINT(const uint8 Instance,
                                                  uint8 * RxBuff,
                                                  const uint32 RxSize)
{
    USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];	

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data. */
    UartStatePtr->IsRxBusy = TRUE;
    UartStatePtr->RxBuff = RxBuff;
    UartStatePtr->RxSize = RxSize;
    UartStatePtr->ReceiveStatus = USART_STATUS_BUSY;

    /* Clear all the error flags */
    Usart_ClearErrorFlags(Base);

    /* Enable the receiver */
    Usart_SetReceiveCmd(Base, TRUE);

    /* Enable error interrupts */
    /* Usart_SetIntMode(Base, USART_INT_RX_OVERRUN, TRUE);
	   Usart_SetIntMode(Base, USART_INT_NOISE_ERR_FLAG, TRUE); */
    Usart_SetIntMode(Base, USART_INT_PARITY_ERR_FLAG, TRUE);
    Usart_SetIntMode(Base, USART_INT_FRAME_ERR_FLAG, TRUE);

    /* Enable receive data full interrupt */
    Usart_SetIntMode(Base, USART_INT_RX_DATA_REG_FULL, TRUE);

    return USART_STATUS_SUCCESS;
}


/*********************************************************************
 * @fn      		  - Usart_PutData
 *
 * @brief             - Initiate (start) a transmit by beginning the process of
 * 						sending data and enabling the interrupt.
 */
static void Usart_PutData(const uint8 Instance)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
    uint16 Data16b;
    uint8 Data8b;

    if ( USART_WORDLEN_8BITS == UartUserCfg->USART_WordLength )
    {
        Data8b = *(UartStatePtr->TxBuff);
        /* Update the state structure */
        ++UartStatePtr->TxBuff;
        --UartStatePtr->TxSize;
        /* Transmit the data */
        Usart_Putchar(Base, Data8b);
    }
    else
    {
        Data16b = (uint16)(*UartStatePtr->TxBuff);
        /* Update the state structure */
        if (1U == UartStatePtr->TxSize)
        {
            ++UartStatePtr->TxBuff;
            --UartStatePtr->TxSize;
        }
        else
        {
            ++UartStatePtr->TxBuff;
            Data16b |= (uint16)(((uint16)(*UartStatePtr->TxBuff)) << 8U);

            ++UartStatePtr->TxBuff;
            UartStatePtr->TxSize -= 2U;
        }

        /* Transmit the data */
		if ( USART_WORDLEN_9BITS == UartUserCfg->USART_WordLength )
        {
            Usart_Putchar9(Base, Data16b);
        }
		else
		{
			/* TODO - 10 bits */
		}
    }
}

/*********************************************************************
 * @fn      		  - Usart_GetData
 *
 * @brief             - Get Data From RX Transfer
 */
static void Usart_GetData(const uint8 Instance)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	const Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
    uint16 Data16b;

    if ( USART_WORDLEN_8BITS == UartUserCfg->USART_WordLength )
    {
        /* Receive the data */
        *(UartStatePtr->RxBuff) = Usart_Getchar(Base);
        /* Update the state structure */
        ++UartStatePtr->RxBuff;
        --UartStatePtr->RxSize;
    }
    else
    {
        if ( USART_WORDLEN_9BITS == UartUserCfg->USART_WordLength )
        {
            Data16b = Usart_Getchar9(Base);
        }
        else
        {
            /* TODO - 10 bits */
        }
        /* Get the data and update state structure */
        if (1U == UartStatePtr->RxSize)
        {
            *(UartStatePtr->RxBuff) = (uint8)Data16b;
            ++UartStatePtr->RxBuff;
            --UartStatePtr->RxSize;
        }
        else
        {
            /* Write the least significant bits to the receive buffer */
            *(UartStatePtr->RxBuff) = (uint8)(Data16b & 0xFFU);
            ++UartStatePtr->RxBuff;
            /* Write the ninth bit to the subsequent byte in the rx buffer */
            *UartStatePtr->RxBuff = (uint8)(Data16b >> 8U);
            ++UartStatePtr->RxBuff;
            UartStatePtr->RxSize -= 2U;
        }
    }
}

/**************************************************************************
 *
 * Function Name : Usart_StartGetData
 * Description   : Start Getting Data in SyncReceive mode
 *
 ***************************************************************************/
static void Usart_StartGetData(const uint8 Instance, uint32 * StartTime, uint32 * ElapsedTicks, uint32 TimeoutTicks)
{
	USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
	
	while ((UartStatePtr->RxSize > 0U) && \
			!Usart_CheckTimeout(StartTime, ElapsedTicks, TimeoutTicks))
	{
		/* Wait until data reception flag is set or timeout occurs if there is an error during reception */
		while (!Usart_GetStatusFlag((const USART_Type*)Base, USART_FLAG_RX_DATA_REG_FULL) && \
			   !Usart_CheckTimeout(StartTime, ElapsedTicks, TimeoutTicks))
		{}
		/* Check for errors on received data */
		/* @TODO */
		
		/* Get received data */
		Usart_GetData(Instance);
	}
}
