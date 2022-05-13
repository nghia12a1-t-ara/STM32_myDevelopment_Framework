
#include "FLASH.h"

/***************************************************************************************
***************************************************************************************/
static FLASH_Status FLASH_GetStatus(void);
static FLASH_Status FLASH_WaitForLastOperation(void);
static uint32 		FLASH_GetPSize(uint8 VoltageRange);

/***************************************************************************************
***************************************************************************************/

/**
 * Flash Unlock Sequence to Unlock FLASH_CR
 */
void FLASH_Unlock(void)
{
	/* Check LOCK bit in FLASH_CR */
	if ( (FLASH->CR & FLASH_CR_LOCK) == 1 )
	{
		/* Write Sequence to Unlock	FLASH_CR */
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;
	}
}

/**
 * Flash Lock FLASH_CR
 */
void FLASH_Lock(void)
{
	/* Set the LOCK Bit to lock the FLASH Registers access */
	FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Erases a specified FLASH Sector.
  *
  * @note   If an erase and a program operations are requested simustaneously,    
  *         the erase operation is performed before the program one.
  *   
  * @param  FLASH_Sector: The Sector number to be erased.
  *          For STM32F40xx/41xx devices this parameter can be a value between  
  *          FLASH_Sector_0 and FLASH_Sector_11.        
  *    
  * @param  VoltageRange: The device voltage range which defines the erase parallelism.  
  *          This parameter can be one of the following values:
  *            @arg VoltageRange_1: when the device voltage range is 1.8V to 2.1V, 
  *                                  the operation will be done by byte (8-bit) 
  *            @arg VoltageRange_2: when the device voltage range is 2.1V to 2.7V,
  *                                  the operation will be done by half word (16-bit)
  *            @arg VoltageRange_3: when the device voltage range is 2.7V to 3.6V,
  *                                  the operation will be done by word (32-bit)
  *            @arg VoltageRange_4: when the device voltage range is 2.7V to 3.6V + External Vpp, 
  *                                  the operation will be done by double word (64-bit)
  *       
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseSector(uint32 FLASH_Sector, uint8 VoltageRange)
{
	uint32 tmp_psize = 0x0;
	FLASH_Status status = FLASH_COMPLETE;	
	
	/* Check Voltage Range to Config PSIZE */
	tmp_psize = FLASH_GetPSize(VoltageRange);
	
	/* Check AHB bus no Busy = BSY bit */
	status = FLASH_WaitForLastOperation();
	
	if ( status == FLASH_COMPLETE )
	{ 
		/* if the previous operation is completed, proceed to erase the sector */
		FLASH->CR &= FLASH_CR_PSIZE_MASK;
		FLASH->CR |= tmp_psize;
		FLASH->CR &= FLASH_CR_SECTOR_MASK;
		FLASH->CR |= FLASH_CR_SER | FLASH_Sector;
		FLASH->CR |= FLASH_CR_STRT;

		/* Wait for last operation to be completed */
		status = FLASH_WaitForLastOperation();

		/* If the Erase Operation is completed, Disable the SER Bit */
		FLASH->CR &= (~FLASH_CR_SER);
		FLASH->CR &= FLASH_CR_SECTOR_MASK;
	}
	/* Return the Erase Status */
	return status;
}

/**
  * @brief  Erases all FLASH Sectors - Mass Erase
  *
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseAllSectors(uint8 VoltageRange)
{
	uint32 tmp_psize = 0x0;
	FLASH_Status status = FLASH_COMPLETE;	
	
	/* Check Voltage Range to Config PSIZE */
	tmp_psize = FLASH_GetPSize(VoltageRange);
	
	/* Check AHB bus no Busy = BSY bit */
	status = FLASH_WaitForLastOperation();
	
	if ( status == FLASH_COMPLETE )
	{ 
		/* If the previous operation is completed, proceed to Erase All Sector */
		FLASH->CR &= FLASH_CR_PSIZE_MASK;
		FLASH->CR |= tmp_psize;
		FLASH->CR |= FLASH_CR_MER;
		FLASH->CR |= FLASH_CR_STRT;

		/* Wait for last operation to be completed */
		status = FLASH_WaitForLastOperation();

		/* If the Erase Operation is completed, Disable the MER Bit */
		FLASH->CR &= (~FLASH_CR_MER);
	}
	/* Return the Erase Status */
	return status;
}

FLASH_Status FLASH_ProgramDoubleWord(uint32 Address, uint64 Data)
{
	
}

FLASH_Status FLASH_ProgramWord(uint32 Address, uint32 Data)
{
	
}

FLASH_Status FLASH_ProgramHalfWord(uint32 Address, uint16 Data)
{
	
}

FLASH_Status FLASH_ProgramByte(uint32 Address, uint8 Data)
{
	
}

/***************************************************************************************
***************************************************************************************/
/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
static FLASH_Status FLASH_GetStatus(void)
{
	FLASH_Status flashstatus = FLASH_COMPLETE;

	if ( (FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY ) 
	{
		flashstatus = FLASH_BUSY;
	}
	else 
	{  
		if((FLASH->SR & FLASH_FLAG_WRPERR) != (uint32)0x00)
		{ 
			flashstatus = FLASH_ERROR_WRP;
		}
		else
		{
			if((FLASH->SR & (uint32)0xEF) != (uint32)0x00)
			{
				flashstatus = FLASH_ERROR_PROGRAM; 
			}
			else
			{
				if((FLASH->SR & FLASH_FLAG_OPERR) != (uint32)0x00)
				{
					flashstatus = FLASH_ERROR_OPERATION;
				}
				else
				{
					flashstatus = FLASH_COMPLETE;
				}
			}
		}
	}
	
	/* Return the FLASH Status */
	return flashstatus;
}

/**
  * @brief  Waits for a FLASH operation to complete.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
static FLASH_Status FLASH_WaitForLastOperation(void)
{ 
	__vo FLASH_Status status = FLASH_COMPLETE;

	/* Check for the FLASH Status & Wait BUSY Flag is Reset */
	do {
		status = FLASH_GetStatus();
	} while ( status == FLASH_BUSY );

	/* Return the operation status */
	return status;
}

/**
 * Check Voltage Range to Config PSIZE 
 */
static uint32 FLASH_GetPSize(uint8 VoltageRange)
{
	uint32 tmp_psize = 0x0;
	
	/* Check Voltage Range to Config PSIZE */
	if ( VoltageRange == VoltageRange_1 )
	{
		tmp_psize = FLASH_PSIZE_BYTE;
	}
	else if ( VoltageRange == VoltageRange_2 )
	{
		tmp_psize = FLASH_PSIZE_HALF_WORD;
	}
	else if ( VoltageRange == VoltageRange_3 )
	{
		tmp_psize = FLASH_PSIZE_WORD;
	}
	else
	{
		tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
	}
	
	return tmp_psize;
}
