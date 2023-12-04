/**
 * Filename		: Bootloader.h
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Bootloader Header File
 */

#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

#include "stm32f4xx.h"
#include "SYSTICK_Base.h"

#define BOOT_RAM_APPLICATION        0x20000004u

void Jump_To_Application(uint32 AppStartAddress);

#endif  /* __BOOTLOADER_H__ */
