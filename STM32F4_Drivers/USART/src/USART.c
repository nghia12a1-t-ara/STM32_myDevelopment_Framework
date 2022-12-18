/**
 * Filename		: USART.c
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Implement USART Driver
 */

#include "USART.h"
#include "USART_HwAccess.h"

/************************************ Private Variables **********************************/
/* Pointer to lpuart runtime state structure */
static Usart_StateRuntimeType * Usart_StateRuntime_Pointer[USART_INSTANCE_COUNT];

/** @brief User config structure. */
const Usart_UserConfigType * Usart_UserConfig_Pointer[USART_INSTANCE_COUNT];

static USART_Type * const Usart_Base_Pointer[USART_INSTANCE_COUNT] = USART_BASE_PTRS;

/************************************ Private Functions **********************************/
static Usart_StatusType Usart_StartSendDataINT(const uint8 Instance, const uint8 *TxBuff, const uint32 TxSize);
static void Usart_PutData(const uint8 Instance);

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
	USART_SetBaudRate(Base, UserConfig->USART_Baud);
	
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
	Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
	Usart_StatusType RetVal = USART_STATUS_SUCCESS;
	boolean IsReturn = FALSE;

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
        // USART_StartTimeout(&StartTime, &TimeoutTicks, Timeout, USART_TIMEOUT_TYPE);
		/* Start Timeout - Can using Systick Timer */

        while ((UartStatePtr->TxSize > 0U) && \
                !Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, USART_TIMEOUT_TYPE))
        {
            Usart_PutData(Instance);
            while (!USART_GetStatusFlag(Base, USART_TX_DATA_REG_EMPTY)  && \
                   !Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, USART_TIMEOUT_TYPE));
        }

        /* Disable the USART transmitter */
        Usart_SetTransmitterCmd(Base, DISABLE);

        /* Check if Timeout occur */
        if (Usart_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks, USART_TIMEOUT_TYPE))
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
 * @brief             - Asynchronus Send Data - Send Data and no wait
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
	USART_Type * Base = Usart_Base_Pointer[Instance];
	Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
	Usart_StateRuntimeType * UartStatePtr = Usart_StateRuntime_Pointer[Instance];
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
            RetVal = Usart_StartSendDataDMA(Instance, TxBuff, TxSize);
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
void USART_SetBaudRate(const uint8 Instance, Usart_BaudrateType BaudRate)
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
	if ( pUSARTx->CR1 & USART_CR1_OVER8_MASK )
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
	Usart_UserConfigType * UartUserCfg = Usart_UserConfig_Pointer[Instance];
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

    if ( USART_WORDLEN_8BITS == UartUserCfg->USART_WordLength) )
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
		if ( USART_WORDLEN_9BITS == UartUserCfg->USART_WordLength) )
        {
            Usart_Putchar9(Base, Data16b);
        }
		else
		{
			/* TODO - 10 bits */
		}
    }
}
