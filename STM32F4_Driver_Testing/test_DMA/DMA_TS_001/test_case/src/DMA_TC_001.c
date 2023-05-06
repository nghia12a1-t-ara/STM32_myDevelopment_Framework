#include "DMA_TC_001.h"
#include "DMA.h"
#include "MPU.h"
#include "result.h"

#define T_REGION 					(1)

#define SRCADDR						0x20016000UL
#define DESTADDR					0x20007F00UL

volatile Bool_Type t_bMpu_ErrorDetected = FALSE;
MPU_ErrorDetailsType t_Mpu_FaultDetails;

Dma_UserStreamConfigType DMA_StreamConfig = {
		DMA_CHANNEL_0,
		DMA_PRIO_LEVEL_HIGH,
		DMA_MEMORY_TO_MEMORY,
		DMA_DATA_WIDTH_8_BITS,
		DMA_DATA_WIDTH_8_BITS,
		DMA_INCREMENT_MODE_ENABLE,
		DMA_INCREMENT_MODE_ENABLE,
};

const Dma_UserConfigType UserConfig = {
		DMA_STREAM_0,
		&DMA_StreamConfig,
};

const Dma_UserTransferType UserTransferConfig = {
		DMA_INSTANCE_2,
		DMA_STREAM_0,
		SRCADDR,
		DESTADDR,
		4,
};

void DMA_TC_001(void)
{
	/* Initialize DMA and MPU */
	DMA_Init(DMA_INSTANCE_2, &UserConfig);
	MPU_Init(&MPU_Config_0);

	/* Write to Source Data - SRAM */
	*(uint32 *)(SRCADDR) = 0xA5A5A5A5;

	/* Set protect for Region 1 by MPU */
	MPU_SetAccessRight(1,MPU_PRIV_R_UNPRIV_R);

	/**************************************************
	 * Try to use DMA Transfer - Successful
	 * Because MPU can not protect transaction by DMA
	 * */
	Dma_StatusType status = DMA_SyncStartTransfer(&UserTransferConfig, 1000);

    CHECK_RESULT(*(uint32 *)DESTADDR, 0x12345678u);
    // CHECK_RESULT(*(uint32 *)DESTADDR, 0x12345628u);
    /**************************************************
     * Perform a write in T_REGION - Fail
     * Because MPU protect transaction by Core
     * */
    *(uint32 *)DESTADDR = 0x12345678;

    /* Loop forever */
	for(;;);
}

void MemManage_Handler(void)
{
	/* Disable MPU */
	MPU->CTRL &= ~(1 << 0);

	/* Get Error Details */
	t_bMpu_ErrorDetected = MPU_GetErrorDetails(&t_Mpu_FaultDetails);
}
