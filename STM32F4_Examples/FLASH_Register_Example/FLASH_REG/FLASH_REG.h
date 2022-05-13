/*
 * FLASH_REG.h
 *
 *  Created on: Apr 26, 2022
 *      Author: Admin
 */

#ifndef FLASH_REG_H_
#define FLASH_REG_H_

#include <stdint.h>

typedef struct {
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;
} Flash_Types;

#define FLASH_BASEADDR			0x40023C00UL
#define FLASH					((Flash_Types *) FLASH_BASEADDR)


void Flash_Unlock(void);
void Flash_Lock(void);
void Flash_EraseSector(uint32_t Sector);
void Flash_ProgramWord(uint32_t Address, uint32_t Data);

#endif /* FLASH_REG_H_ */
