#include "FLASH_REG.h"

void Flash_Unlock(void)
{
	if ( (FLASH->CR & (1 << 31)) != 0 )
	{
		FLASH->KEYR = 0x45670123;
		FLASH->KEYR =  0xCDEF89AB;
	}
}

void Flash_Lock(void)
{
	FLASH->CR |= (1 << 31);
}

void Flash_EraseSector(uint32_t Sector)
{
	Flash_Unlock();

	while (FLASH->SR & (1 << 16) == 1);

	FLASH->CR |= (1 << 1) | (Sector << 3);

	FLASH->CR |= (1 << 16);

	while (FLASH->SR & (1 << 16) == 1);

	FLASH->CR &= ~(1 << 1);

	Flash_Lock();
}

void Flash_ProgramWord(uint32_t Address, uint32_t Data)
{
	Flash_Unlock();

	while (FLASH->SR & (1 << 16) == 1);

	FLASH->CR |= (1 << 0);

	FLASH->CR |= (0x2 << 8);

	*(uint32_t *) Address = Data;

	while (FLASH->SR & (1 << 16) == 1);

	FLASH->CR &= ~(1 << 0);

	Flash_Lock();
}
