#ifndef __FLASH_H__
#define __FLASH_H__

#include "FLASH_Base.h"
#include "FLASH_Type.h"

/* FLASH Memory Programming functions *****************************************/   
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_EraseSector(uint32 FLASH_Sector);
FLASH_Status FLASH_EraseAllSectors(uint8 VoltageRange);
FLASH_Status FLASH_ProgramDoubleWord(uint32 Address, uint64 Data);
FLASH_Status FLASH_ProgramWord(uint32 Address, uint32 Data);
FLASH_Status FLASH_ProgramHalfWord(uint32 Address, uint16 Data);
FLASH_Status FLASH_ProgramByte(uint32 Address, uint8 Data);

#endif	/* !(__FLASH_H__) */
