/**
 * Filename     : SPI.c
 * Author       : Nghia-Taarabt
 * Create Date  : 18/12/22
 * Brief        : SPI Driver APIs
 */

#include "SPI.h"
#include "SPI_HwAccess.h"

/*****************************************************************************************/
/************************************ Private Variables **********************************/
/* Pointer to SPI Runtime State Structure */
static Spi_StateRuntimeType * Spi_StateRuntime_Pointer[SPI_INSTANCE_COUNT];

/** @brief User Configuration Structure. */
const Spi_UserConfigType * Spi_UserConfig_Pointer[SPI_INSTANCE_COUNT];

static SPI_Type * const Spi_Base_Pointer[SPI_INSTANCE_COUNT] = SPI_BASE_PTRS;

/*****************************************************************************************/
/************************************ Private Functions **********************************/
static void SPI_DeInit(const uint8 Instance);
static Spi_StatusType Spi_StartSendDataINT(const uint8 Instance,
                                           const uint8 *TxBuff,
                                           const uint32 TxSize);
static Spi_StatusType Spi_StartReceiveDataINT(const uint8 Instance,
                                              uint8 * RxBuff,
                                              const uint32 RxSize);

/* ----------------- Interrupt Handler Functions ----------------- */


/*****************************************************************************************/
/*********************************************************************
 * @fn                - SPI_Init
 *
 * @brief             - Initialize SPI Driver
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - UserConfig  - SPI User Configuration
 *
 * @return            -
 *
 * @Note              -
 */
void SPI_Init(const uint8 Instance, const Spi_UserConfigType * UserConfig)
{
    SPI_Type * Base = Spi_Base_Pointer[Instance];
    Spi_StateRuntimeType * SpiStatePtr;
    
    /* Assign Configuration to Static Variables */
    Spi_UserConfig_Pointer[Instance]    = UserConfig;
    Spi_StateRuntime_Pointer[Instance]  = UserConfig->StateStruct;
    SpiStatePtr                         = Spi_StateRuntime_Pointer[Instance];
    
    /* De-Initialize module before setup  */
    SPI_DeInit(Instance);
    
    /* Implement the code to enable the Clock for given SPI peripheral */
    SPI_PeriClockControl(Base, ENABLE);
    
    /* Set Device Mode is Master or Slave */
    SPI_SetDeviceMode(Base, UserConfig->SPI_DeviceMode);

    /* Configure the Bus Configuration - FD/HD/RXONLY */
    SPI_SetBusConfig(Base, UserConfig->SPI_BusConfig);

    /* Configure the SPI serial clock speed (baud-rate) */
    SPI_SetClockSpeedDivide(Base, UserConfig->SPI_ClockSpeed);

    /* Configure DataFrame - 8 or 16 bits */
    SPI_SetDataFrame(Base, UserConfig->SPI_DataFrame);
    
    /* Configure First Bit is MSB or LSB */
    SPI_SetFirstBit(Base, UserConfig->SPI_FirstBit);

    /* Configure CPOL/CPHA */
    SPI_SetClockMode(Base, UserConfig->SPI_ClockMode);

    /* Set Enable or Disable Software Slave Management */
    SPI_SetSWSlaveManage(Base, UserConfig->SPI_SSM);
    if ( SPI_DEVICE_MODE_MASTER == UserConfig->SPI_DeviceMode )
    {
        SPI_SetSSIEnable(Base, ENABLE);
    }
    
    /* Initialize last driver operation status */
    SpiStatePtr->TransmitStatus = SPI_STATUS_SUCCESS;
    SpiStatePtr->ReceiveStatus = SPI_STATUS_SUCCESS;
}

/*****************************************************************************************/
/*********************************************************************
 * @fn                - SPI_DeInit
 *
 * @brief             - De-Initialize SPI Driver
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 *
 * @return            -
 *
 * @Note              -
 */
static void SPI_DeInit(const uint8 Instance)
{
    SPI_Type * Base = Spi_Base_Pointer[Instance];
    Spi_StateRuntimeType * SpiStatePtr;
    uint8 * ClearStructPtr;
    uint8 Index;

    /* Assign Configuration to Static Variables */
    SpiStatePtr = Spi_StateRuntime_Pointer[Instance];
    ClearStructPtr = (uint8 *)SpiStatePtr;

    /* Disable SPI Instance */
    SPI_PeripheralControl(Base, DISABLE);

    /* Disable Clock for SPI Instance */
    SPI_PeriClockControl(Base, DISABLE);

    /* Clear the state structure for this Instance. */
    for (Index = 0; Index < sizeof(Spi_StateRuntimeType); Index++)
    {
        ClearStructPtr[Index] = 0;
    }
}

/*********************************************************************
 * @fn                - Spi_SyncSendData
 *
 * @brief             - Synchronous Send Data - Wait to send done or timeout
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - TxBuff      - Buffer to transmission
 * @param[in]         - TxSize      - Size of Buffer to transmission
 * @param[in]         - Timeout     - Timeout if data cannot transmit
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_SyncSendData(const uint8 Instance,
                                const uint8 *TxBuff,
                                const uint32 TxSize,
                                const uint32 Timeout)
{
    SPI_Type * Base = Spi_Base_Pointer[Instance];
    Spi_StateRuntimeType * SpiStatePtr = Spi_StateRuntime_Pointer[Instance];
    const Spi_UserConfigType * SpiUserConfig = Spi_UserConfig_Pointer[Instance];
    Spi_StatusType RetVal = SPI_STATUS_SUCCESS;
    Bool_Type IsReturn = FALSE;
    
    /* Timeout Setup Variables */
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    /* Check driver is not busy transmitting data from a previous asynchronous call */
    if (SpiStatePtr->IsTxBusy)
    {
        RetVal = SPI_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        SpiStatePtr->IsTxBusy   = TRUE;
        SpiStatePtr->pTxBuffer  = TxBuff;
        SpiStatePtr->TxSize     = TxSize;

        SpiStatePtr->TransmitStatus = SPI_STATUS_BUSY;
        
        /* Disable TX data interrupt */
        
        /* Start Timeout - Can using Sys-tick Timer and Start Transfer by Enable SPI Instance */
        Systick_StartTimeout(&StartTime, &TimeoutTicks, Timeout);
        SPI_PeripheralControl(Base, ENABLE);
        
        /* Wait transfer successfully or Timeout occurs */
        while ( (SpiStatePtr->TxSize > 0U) && \
                !Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) )
        {
            /* Wait for TX Buffer Register Empty or Timeout */
            while ( !Spi_GetStatusFlag(Base, SPI_FLAG_TX_BUFFER_EMPTY)  && \
                    !Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) );
                    
            /* Send data with each data frame - 8 or 16 bits */
            if( SPI_DATA_FRAME_16BITS == SpiUserConfig->SPI_DataFrame )
            {
                SPI_DATA_REG_WRITE(Base,*((uint16*)(SpiStatePtr->pTxBuffer)));
                SpiStatePtr->TxSize-=2;
                (uint16*)(SpiStatePtr->pTxBuffer)++;
            }
            else
            {
                SPI_DATA_REG_WRITE(Base,*(SpiStatePtr->pTxBuffer));
                SpiStatePtr->TxSize--;
                (SpiStatePtr->pTxBuffer)++;
            }
        }
        
        /* Stop transfer by disable SPI Instance */
        SPI_PeripheralControl(Base, DISABLE);
        
        /* Check if Timeout occur */
        if ( Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) )
        {
            SpiStatePtr->TransmitStatus = SPI_STATUS_TIMEOUT;
        }
        else
        {
            /* The transmit process is complete */
            SpiStatePtr->TransmitStatus = SPI_STATUS_SUCCESS;
        }
        SpiStatePtr->IsTxBusy = FALSE;
        RetVal = SpiStatePtr->TransmitStatus;
    }
    return RetVal;
}


/*********************************************************************
 * @fn      		  - Spi_AsyncSendData
 *
 * @brief             - Asynchronous Send Data - Send Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- SPI Hardware Instance
 * @param[in]         - TxBuff 		- Buffer to transmission
 * @param[in]         - TxSize 		- Size of Buffer to transmission
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_AsyncSendData(const uint8 Instance,
								 const uint8 *TxBuff,
								 const uint32 TxSize)
{
	Spi_StateRuntimeType * SpiStatePtr = Spi_StateRuntime_Pointer[Instance];
	const Spi_UserConfigType * SpiUserCfg = Spi_UserConfig_Pointer[Instance];
	Spi_StatusType RetVal = SPI_STATUS_SUCCESS;
	Bool_Type IsReturn = FALSE;
	
	if (SpiStatePtr->IsTxBusy)
    {
        RetVal = SPI_STATUS_BUSY;
        IsReturn = TRUE;
    }
	if (!IsReturn)
    {
        SpiStatePtr->IsTxBusy = TRUE;

        if (SPI_USING_INTERRUPTS == SpiUserCfg->SPI_Transfer)
        {
            /* Start the transmission process using interrupts */
            RetVal = Spi_StartSendDataINT(Instance, TxBuff, TxSize);
        }
#if (SPI_DMA_ENABLED == ON)
        else
        {
            /* Start the transmission process using DMA */
            /* RetVal = Spi_StartSendDataDMA(Instance, TxBuff, TxSize);*/
        }
#endif
    }
    return RetVal;
}

/*********************************************************************
 * @fn                - Spi_StartSendDataINT
 *
 * @brief             - Initiate (start) a transmit by beginning the process of
 *                      sending data and enabling the interrupt.
 */
static Spi_StatusType Spi_StartSendDataINT(const uint8 Instance,
                                           const uint8 *TxBuff,
                                           const uint32 TxSize)
{
    SPI_Type * Base = Spi_Base_Pointer[Instance];
    Spi_StateRuntimeType * SpiStatePtr = Spi_StateRuntime_Pointer[Instance];	

    /* Initialize state structure */
    SpiStatePtr->pTxBuffer = TxBuff;
    SpiStatePtr->TxSize = TxSize;
    SpiStatePtr->TransmitStatus = SPI_STATUS_BUSY;

    /* Enable the SPI Transmitter */
    SPI_PeripheralControl(Base, ENABLE);

    /* Enable TX Empty Interrupt */
    Spi_SetIntMode(Base, SPI_INT_TX_DATA_REG_EMPTY, ENABLE);

    return SPI_STATUS_SUCCESS;
}

/*********************************************************************
 * @fn                - Spi_SyncReceiveData
 *
 * @brief             - Synchronous Receive Data - Wait to receive done or timeout
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - RxBuff      - Buffer to Receive
 * @param[in]         - RxSize      - Size of Buffer to Receive
 * @param[in]         - Timeout     - Timeout if data cannot Receive (us)
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_SyncReceiveData(const uint8 Instance,
                                   		 uint8 *RxBuff,
                                   const uint32 RxSize,
                                   const uint32 Timeout)
{
    SPI_Type * Base = Spi_Base_Pointer[Instance];
    Spi_StateRuntimeType * SpiStatePtr = Spi_StateRuntime_Pointer[Instance];
    const Spi_UserConfigType * SpiUserConfig = Spi_UserConfig_Pointer[Instance];
    Spi_StatusType RetVal = SPI_STATUS_SUCCESS;
    Bool_Type IsReturn = FALSE;
    
    /* Timeout Setup Variables */
    uint32 StartTime;
    uint32 TimeoutTicks;
    uint32 ElapsedTicks = 0;

    /* Check driver is not busy transmitting data from a previous asynchronous call */
    if (SpiStatePtr->IsRxBusy)
    {
        RetVal = SPI_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        SpiStatePtr->IsRxBusy   = TRUE;
        SpiStatePtr->pRxBuffer  = RxBuff;
        SpiStatePtr->RxSize     = RxSize;

        SpiStatePtr->ReceiveStatus = SPI_STATUS_BUSY;
        
        /* Disable TX data interrupt */
        
        /* Start Timeout - Can using Sys-tick Timer and Start Receive by Enable SPI Instance */
        Systick_StartTimeout(&StartTime, &TimeoutTicks, Timeout);
        SPI_PeripheralControl(Base, ENABLE);
        
        /* Start Receive Data */
		/* 1. Wait until RXNE == 1 */
        /* Wait transfer successfully or Timeout occurs */
        while ( (SpiStatePtr->RxSize > 0U) && \
                !Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) )
        {
            /* Wait for RX Buffer Register Empty or Timeout */
            while ( !Spi_GetStatusFlag(Base, SPI_FLAG_RX_BUFFER_NOT_EMPTY)  && \
                    !Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) );

            /* Get data with each data frame - 8 or 16 bits */
            if( SPI_DATA_FRAME_16BITS == SpiUserConfig->SPI_DataFrame )
            {
                SPI_DATA_REG_READ(Base,*((uint16*)(SpiStatePtr->pRxBuffer)));
                SpiStatePtr->RxSize-=2;
                (uint16*)(SpiStatePtr->pRxBuffer)++;
            }
            else
            {
                SPI_DATA_REG_READ(Base,*(SpiStatePtr->pRxBuffer));
                SpiStatePtr->RxSize--;
                (SpiStatePtr->pRxBuffer)++;
            }
        }
        
        /* Stop transfer by disable SPI Instance */
        SPI_PeripheralControl(Base, DISABLE);
        
        /* Check if Timeout occur */
        if ( Systick_CheckTimeout(&StartTime, &ElapsedTicks, TimeoutTicks) )
        {
            SpiStatePtr->ReceiveStatus = SPI_STATUS_TIMEOUT;
        }
        else
        {
            /* The transmit process is complete */
            SpiStatePtr->ReceiveStatus = SPI_STATUS_SUCCESS;
        }
        SpiStatePtr->IsRxBusy = FALSE;
        RetVal = SpiStatePtr->ReceiveStatus;
    }
    return RetVal;
}


/*********************************************************************
 * @fn      		  - Spi_AsyncReceiveData
 *
 * @brief             - Asynchronous Receive Data - Receive Data and no wait (Interrupt or DMA)
 *
 * @param[in]         - Instance 	- SPI Hardware Instance
 * @param[in]         - RxBuff 		- Buffer to Receive
 * @param[in]         - RxSize 		- Size of Buffer to Receive
 *
 * @return            - Spi_StatusType
 *
 * @Note              -
 */
Spi_StatusType Spi_AsyncReceiveData(const uint8 Instance,
                                    uint8 * RxBuff,
                                    const uint32 RxSize)
{
	const Spi_UserConfigType * SpiUserCfg = Spi_UserConfig_Pointer[Instance];
	Spi_StateRuntimeType * SpiStatePtr = Spi_StateRuntime_Pointer[Instance];	
	Spi_StatusType RetVal = SPI_STATUS_SUCCESS;
	Bool_Type IsReturn = FALSE;
	
    /* Check it's not busy receiving data from a previous function call */
    if (SpiStatePtr->IsRxBusy)
    {
        RetVal = SPI_STATUS_BUSY;
        IsReturn = TRUE;
    }
    if (!IsReturn)
    {
        SpiStatePtr->IsRxBusy = TRUE;

        if (SPI_USING_INTERRUPTS == SpiUserCfg->SPI_Transfer)
        {
            /* Start the reception process using interrupts */
            RetVal = Spi_StartReceiveDataINT(Instance, RxBuff, RxSize);
        }
#if (SPI_DMA_ENABLED == ON)
        else
        {
            /* Start the transmission process using DMA */
            /* RetVal = Spi_StartReceiveDataDMA(Instance, RxBuff, RxSize);*/
        }
#endif
    }
    return RetVal;
}

/*********************************************************************
 * @fn                - Spi_StartReceiveDataINT
 *
 * @brief             - Initiate (start) a transmit by beginning the process of
 *                      sending data and enabling the interrupt.
 */
static Spi_StatusType Spi_StartReceiveDataINT(const uint8 Instance,
                                              uint8 * RxBuff,
                                              const uint32 RxSize)
{
    SPI_Type * Base = Spi_Base_Pointer[Instance];
    Spi_StateRuntimeType * SpiStatePtr = Spi_StateRuntime_Pointer[Instance];

    /* Initialize the module driver state structure to indicate transfer in progress
     * and with the buffer and byte count data. */
    SpiStatePtr->IsRxBusy = TRUE;
    SpiStatePtr->pRxBuffer = RxBuff;
    SpiStatePtr->RxSize = RxSize;
    SpiStatePtr->ReceiveStatus = SPI_STATUS_BUSY;

    /* Clear all the error flags */
    Spi_ClearErrorFlags(Base);

    /* Enable the receiver */
    SPI_PeripheralControl(Base, ENABLE);

    /* Enable error interrupts */
    Spi_SetIntMode(Base, SPI_INT_ERROR_TRANSACTION, TRUE);
    /* Enable receive data full interrupt */
    Spi_SetIntMode(Base, SPI_INT_RX_DATA_REG_FULL, TRUE);

    return SPI_STATUS_SUCCESS;
}

/*********************************************************************
 * @fn                - SPI_GetStatus
 *
 * @brief             - Get Status Flag
 *
 * @param[in]         - Instance    - SPI Hardware Instance
 * @param[in]         - StatusFlag  - Status Flag
 *
 * @return            - TRUE or FALSE
 *
 * @Note              -
 */
Bool_Type SPI_GetStatus(const uint8 Instance, Spi_StatusFlagType StatusFlag)
{
    SPI_Type * Base = Spi_Base_Pointer[Instance];
    return Spi_GetStatusFlag(Base, StatusFlag);
}
