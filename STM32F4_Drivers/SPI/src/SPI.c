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
    
    /* Implement the code to enable the Clock for given USART peripheral */
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
    boolean IsReturn = FALSE;
    
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
                SPI_DATA_REG_WRITE(Base,*((uint16*)TxBuff));
                SpiStatePtr->TxSize-=2;
                (uint16*)TxBuff++;
            }
            else
            {
                SPI_DATA_REG_WRITE(Base,*TxBuff);
                SpiStatePtr->TxSize--;
                TxBuff++;
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
