#ifndef __NVIC_BASE_H_
#define __NVIC_BASE_H_

#include "Std_Type.h"

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
  \brief      Type definitions for the NVIC Registers
  @{
 */

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IO uint32 ISER[8U];					/*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32 RESERVED0[24U];
  __IO uint32 ICER[8U];					/*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32 RESERVED1[24U];
  __IO uint32 ISPR[8U];					/*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32 RESERVED2[24U];
  __IO uint32 ICPR[8U];					/*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32 RESERVED3[24U];
  __IO uint32 IABR[8U];					/*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32 RESERVED4[56U];
  __IO uint8  IP[240U];					/*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32 RESERVED5[644U];
  __O  uint32 STIR;					/*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
} NVIC_Type;

/*!< NVIC Base Address */
#define NVIC_BASE           (0xE000E100UL)

/*!< NVIC configuration struct */
#define NVIC                ((NVIC_Type *) NVIC_BASE)

#endif	/* !(__NVIC_BASE_H_) */
