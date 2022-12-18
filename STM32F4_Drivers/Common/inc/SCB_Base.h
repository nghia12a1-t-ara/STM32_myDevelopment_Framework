/*
 * SCB_Address.h
 *
 *  Created on: Mar 29, 2022
 *      Author: Admin
 */

/*
** ###################################################################
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#if !defined(SCB_ADDRESS_H_)  /* Check if memory map has not been already included */
#define SCB_ADDRESS_H_

/* ----------------------------------------------------------------------------
   -- SCB Peripheral Access Layer
   ---------------------------------------------------------------------------- */
#include "Std_Types.h"

/*!
 * @addtogroup SCB_Peripheral_Access_Layer SCB Peripheral Access Layer
 * @{
 */

/** SCB - Size of Registers Arrays */
#define SCB_ID_MMFR_COUNT                    4u
#define SCB_ID_ISAR_COUNT                    5u
#define SCB_PID_COUNT                        8u
#define SCB_CID_COUNT                        4u

/** SCB - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[8];
  __IO uint32_t ACTLR;                             /**< Auxiliary Control Register, offset: 0x8 */
       uint8_t RESERVED_1[3316];
  __I  uint32_t CPUID;                             /**< CPUID Base Register, offset: 0xD00 */
  __IO uint32_t ICSR;                              /**< Interrupt Control and State Register, offset: 0xD04 */
  __IO uint32_t VTOR;                              /**< Vector Table Offset Register, offset: 0xD08 */
  __IO uint32_t AIRCR;                             /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  __IO uint32_t SCR;                               /**< System Control Register, offset: 0xD10 */
  __IO uint32_t CCR;                               /**< Configuration and Control Register, offset: 0xD14 */
  __IO uint32_t SHPR1;                             /**< System Handler Priority Register 1, offset: 0xD18 */
  __IO uint32_t SHPR2;                             /**< System Handler Priority Register 2, offset: 0xD1C */
  __IO uint32_t SHPR3;                             /**< System Handler Priority Register 3, offset: 0xD20 */
  __IO uint32_t SHCSR;                             /**< System Handler Control and State Register, offset: 0xD24 */
  __IO uint32_t CFSR;                              /**< Configurable Fault Status Registers, offset: 0xD28 */
  __IO uint32_t HFSR;                              /**< HardFault Status Register, offset: 0xD2C */
  __IO uint32_t DFSR;                              /**< Debug Fault Status Register, offset: 0xD30 */
  __IO uint32_t MMFAR;                             /**< Memanage Fault Address Register, offset: 0xD34 */
  __IO uint32_t BFAR;                              /**< BusFault Address Registerd, offset: 0xD38 */
  __IO uint32_t AFSR;                              /**< Auxiliary Fault Status Register, offset: 0xD3C */
  __I  uint32_t ID_PFR0;                           /**< Processor Feature Register 0, offset: 0xD40 */
  __I  uint32_t ID_PFR1;                           /**< Processor Feature Register 1, offset: 0xD44 */
  __I  uint32_t ID_DFR0;                           /**< Debug Feature Register 0, offset: 0xD48 */
  __I  uint32_t ID_AFR0;                           /**< Auxiliary Feature Register 0, offset: 0xD4C */
  __I  uint32_t ID_MMFR[SCB_ID_MMFR_COUNT];    /**< Memory Model Feature Register 0..Memory Model Feature Register 3, array offset: 0xD50, array step: 0x4 */
  __I  uint32_t ID_ISAR[SCB_ID_ISAR_COUNT];    /**< Instruction Set Attributes Register 0..Instruction Set Attributes Register 4, array offset: 0xD60, array step: 0x4 */
       uint8_t RESERVED_2[4];
  __I  uint32_t CLIDR;                             /**< Cache Level ID Register, offset: 0xD78 */
  __I  uint32_t CTR;                               /**< Cache Type Register, offset: 0xD7C */
  __I  uint32_t CCSIDR;                            /**< Cache Size ID Register, offset: 0xD80 */
  __IO uint32_t CSSELR;                            /**< Cache Size Selection Register, offset: 0xD84 */
  __IO uint32_t CPACR;                             /**< Coprocessor Access Control Register, offset: 0xD88 */
       uint8_t RESERVED_3[372];
  __O  uint32_t STIR;                              /**< Software Triggered Interrupt Register, offset: 0xF00 */
       uint8_t RESERVED_4[48];
  __IO uint32_t FPCCR;                             /**< Floating-point Context Control Register, offset: 0xF34 */
  __IO uint32_t FPCAR;                             /**< Floating-point Context Address Register, offset: 0xF38 */
  __IO uint32_t FPDSCR;                            /**< Floating-point Default Status Control Register, offset: 0xF3C */
       uint8_t RESERVED_5[16];
  __O  uint32_t ICIALLU;                           /**< Instruction cache invalidate all to Point of Unification (PoU), offset: 0xF50 */
       uint8_t RESERVED_6[4];
  __O  uint32_t ICIMVAU;                           /**< Instruction cache invalidate by address to PoU, offset: 0xF58 */
  __O  uint32_t DCIMVAC;                           /**< Data cache invalidate by address to Point of Coherency (PoC), offset: 0xF5C */
  __O  uint32_t DCISW;                             /**< Data cache invalidate by set/way, offset: 0xF60 */
  __O  uint32_t DCCMVAU;                           /**< Data cache by address to PoU, offset: 0xF64 */
  __O  uint32_t DCCMVAC;                           /**< Data cache clean by address to PoC, offset: 0xF68 */
  __O  uint32_t DCCSW;                             /**< Data cache clean by set/way, offset: 0xF6C */
  __O  uint32_t DCCIMVAC;                          /**< Data cache clean and invalidate by address to PoC, offset: 0xF70 */
  __O  uint32_t DCCISW;                            /**< Data cache clean and invalidate by set/way, offset: 0xF74 */
  __I  uint32_t BPIALL;                            /**< Not implemented - RAZ/WI, offset: 0xF78 */
       uint8_t RESERVED_7[20];
  __IO uint32_t ITCMCR;                            /**< Instruction Tightly-Coupled Memory Control Register, offset: 0xF90 */
  __IO uint32_t DTCMCR;                            /**< Data Tightly-Coupled Memory Control Register, offset: 0xF94 */
  __IO uint32_t AHBPCR;                            /**< AHBP control register, offset: 0xF98 */
  __IO uint32_t CACR;                              /**< L1 Cache Control Register, offset: 0xF9C */
  __IO uint32_t AHBSCR;                            /**< AHB Slave Control Register, offset: 0xFA0 */
       uint8_t RESERVED_8[4];
  __IO uint32_t ABFSR;                             /**< Asynchronous Bus Fault Status Register, offset: 0xFA8 */
       uint8_t RESERVED_9[4];
  __IO uint32_t IEBR0;                             /**< Instruction Error bank Register 0, offset: 0xFB0 */
  __IO uint32_t IEBR1h;                            /**< Instruction Error bank Register 1, offset: 0xFB4 */
  __IO uint32_t DEBR0h;                            /**< Data Error bank Register 0, offset: 0xFB8 */
  __IO uint32_t DEBR1h;                            /**< Data Error bank Register 1, offset: 0xFBC */
       uint8_t RESERVED_10[16];
  __I  uint32_t PID[SCB_PID_COUNT];            /**< Peripheral identification register 0..Peripheral identification register 7, array offset: 0xFD0, array step: 0x4 */
  __I  uint32_t CID[SCB_CID_COUNT];            /**< Component identification register 0..Component identification register 3, array offset: 0xFF0, array step: 0x4 */
} SCB_Type, *SCB_MemMapPtr;

 /** Number of instances of the SCB module. */
#define SCB_INSTANCE_COUNT                   (1u)

/* SCB - Peripheral instance base addresses */
/** Peripheral SCB base address */
#define SCB_BASE                             (0xE000E000u)
/** Peripheral SCB base pointer */
#define SCB                                  ((SCB_Type *)SCB_BASE)
/** Array initializer of SCB peripheral base addresses */
#define SCB_BASE_ADDRS                       { SCB_BASE }
/** Array initializer of SCB peripheral base pointers */
#define SCB_BASE_PTRS                        { SCB }

/* ----------------------------------------------------------------------------
   -- SCB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Masks SCB Register Masks
 * @{
 */

/* ACTLR Bit Fields */
#define SCB_ACTLR_ACTLR_MASK                 0xFFFFFFFFu
#define SCB_ACTLR_ACTLR_SHIFT                0u
#define SCB_ACTLR_ACTLR_WIDTH                32u
#define SCB_ACTLR_ACTLR(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_ACTLR_ACTLR_SHIFT))&SCB_ACTLR_ACTLR_MASK)
/* CPUID Bit Fields */
#define SCB_CPUID_REVISION_MASK              0xFu
#define SCB_CPUID_REVISION_SHIFT             0u
#define SCB_CPUID_REVISION_WIDTH             4u
#define SCB_CPUID_REVISION(x)                (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_REVISION_SHIFT))&SCB_CPUID_REVISION_MASK)
#define SCB_CPUID_PARTNO_MASK                0xFFF0u
#define SCB_CPUID_PARTNO_SHIFT               4u
#define SCB_CPUID_PARTNO_WIDTH               12u
#define SCB_CPUID_PARTNO(x)                  (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_PARTNO_SHIFT))&SCB_CPUID_PARTNO_MASK)
#define SCB_CPUID_VARIANT_MASK               0xF00000u
#define SCB_CPUID_VARIANT_SHIFT              20u
#define SCB_CPUID_VARIANT_WIDTH              4u
#define SCB_CPUID_VARIANT(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_VARIANT_SHIFT))&SCB_CPUID_VARIANT_MASK)
#define SCB_CPUID_IMPLEMENTER_MASK           0xFF000000u
#define SCB_CPUID_IMPLEMENTER_SHIFT          24u
#define SCB_CPUID_IMPLEMENTER_WIDTH          8u
#define SCB_CPUID_IMPLEMENTER(x)             (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_IMPLEMENTER_SHIFT))&SCB_CPUID_IMPLEMENTER_MASK)
/* ICSR Bit Fields */
#define SCB_ICSR_VECTACTIVE_MASK             0x1FFu
#define SCB_ICSR_VECTACTIVE_SHIFT            0u
#define SCB_ICSR_VECTACTIVE_WIDTH            9u
#define SCB_ICSR_VECTACTIVE(x)               (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_VECTACTIVE_SHIFT))&SCB_ICSR_VECTACTIVE_MASK)
#define SCB_ICSR_RETTOBASE_MASK              0x800u
#define SCB_ICSR_RETTOBASE_SHIFT             11u
#define SCB_ICSR_RETTOBASE_WIDTH             1u
#define SCB_ICSR_RETTOBASE(x)                (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_RETTOBASE_SHIFT))&SCB_ICSR_RETTOBASE_MASK)
#define SCB_ICSR_VECTPENDING_MASK            0x3F000u
#define SCB_ICSR_VECTPENDING_SHIFT           12u
#define SCB_ICSR_VECTPENDING_WIDTH           6u
#define SCB_ICSR_VECTPENDING(x)              (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_VECTPENDING_SHIFT))&SCB_ICSR_VECTPENDING_MASK)
#define SCB_ICSR_ISRPENDING_MASK             0x400000u
#define SCB_ICSR_ISRPENDING_SHIFT            22u
#define SCB_ICSR_ISRPENDING_WIDTH            1u
#define SCB_ICSR_ISRPENDING(x)               (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_ISRPENDING_SHIFT))&SCB_ICSR_ISRPENDING_MASK)
#define SCB_ICSR_ISRPREEMPT_MASK             0x800000u
#define SCB_ICSR_ISRPREEMPT_SHIFT            23u
#define SCB_ICSR_ISRPREEMPT_WIDTH            1u
#define SCB_ICSR_ISRPREEMPT(x)               (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_ISRPREEMPT_SHIFT))&SCB_ICSR_ISRPREEMPT_MASK)
#define SCB_ICSR_PENDSTCLR_MASK              0x2000000u
#define SCB_ICSR_PENDSTCLR_SHIFT             25u
#define SCB_ICSR_PENDSTCLR_WIDTH             1u
#define SCB_ICSR_PENDSTCLR(x)                (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSTCLR_SHIFT))&SCB_ICSR_PENDSTCLR_MASK)
#define SCB_ICSR_PENDSTSET_MASK              0x4000000u
#define SCB_ICSR_PENDSTSET_SHIFT             26u
#define SCB_ICSR_PENDSTSET_WIDTH             1u
#define SCB_ICSR_PENDSTSET(x)                (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSTSET_SHIFT))&SCB_ICSR_PENDSTSET_MASK)
#define SCB_ICSR_PENDSVCLR_MASK              0x8000000u
#define SCB_ICSR_PENDSVCLR_SHIFT             27u
#define SCB_ICSR_PENDSVCLR_WIDTH             1u
#define SCB_ICSR_PENDSVCLR(x)                (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSVCLR_SHIFT))&SCB_ICSR_PENDSVCLR_MASK)
#define SCB_ICSR_PENDSVSET_MASK              0x10000000u
#define SCB_ICSR_PENDSVSET_SHIFT             28u
#define SCB_ICSR_PENDSVSET_WIDTH             1u
#define SCB_ICSR_PENDSVSET(x)                (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSVSET_SHIFT))&SCB_ICSR_PENDSVSET_MASK)
#define SCB_ICSR_NMIPENDSET_MASK             0x80000000u
#define SCB_ICSR_NMIPENDSET_SHIFT            31u
#define SCB_ICSR_NMIPENDSET_WIDTH            1u
#define SCB_ICSR_NMIPENDSET(x)               (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_NMIPENDSET_SHIFT))&SCB_ICSR_NMIPENDSET_MASK)
/* VTOR Bit Fields */
#define SCB_VTOR_TBLOFF_MASK                 0xFFFFFF80u
#define SCB_VTOR_TBLOFF_SHIFT                7u
#define SCB_VTOR_TBLOFF_WIDTH                25u
#define SCB_VTOR_TBLOFF(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_VTOR_TBLOFF_SHIFT))&SCB_VTOR_TBLOFF_MASK)
/* AIRCR Bit Fields */
#define SCB_AIRCR_AIRCR_MASK                 0xFFFFFFFFu
#define SCB_AIRCR_AIRCR_SHIFT                0u
#define SCB_AIRCR_AIRCR_WIDTH                32u
#define SCB_AIRCR_AIRCR(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_AIRCR_SHIFT))&SCB_AIRCR_AIRCR_MASK)
/* SCR Bit Fields */
#define SCB_SCR_SLEEPONEXIT_MASK             0x2u
#define SCB_SCR_SLEEPONEXIT_SHIFT            1u
#define SCB_SCR_SLEEPONEXIT_WIDTH            1u
#define SCB_SCR_SLEEPONEXIT(x)               (((uint32_t)(((uint32_t)(x))<<SCB_SCR_SLEEPONEXIT_SHIFT))&SCB_SCR_SLEEPONEXIT_MASK)
#define SCB_SCR_SLEEPDEEP_MASK               0x4u
#define SCB_SCR_SLEEPDEEP_SHIFT              2u
#define SCB_SCR_SLEEPDEEP_WIDTH              1u
#define SCB_SCR_SLEEPDEEP(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_SCR_SLEEPDEEP_SHIFT))&SCB_SCR_SLEEPDEEP_MASK)
#define SCB_SCR_SEVONPEND_MASK               0x10u
#define SCB_SCR_SEVONPEND_SHIFT              4u
#define SCB_SCR_SEVONPEND_WIDTH              1u
#define SCB_SCR_SEVONPEND(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_SCR_SEVONPEND_SHIFT))&SCB_SCR_SEVONPEND_MASK)
/* CCR Bit Fields */
#define SCB_CCR_CCR_MASK                     0xFFFFFFFFu
#define SCB_CCR_CCR_SHIFT                    0u
#define SCB_CCR_CCR_WIDTH                    32u
#define SCB_CCR_CCR(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_CCR_CCR_SHIFT))&SCB_CCR_CCR_MASK)
/* SHPR1 Bit Fields */
#define SCB_SHPR1_SHPR1_MASK                 0xFFFFFFFFu
#define SCB_SHPR1_SHPR1_SHIFT                0u
#define SCB_SHPR1_SHPR1_WIDTH                32u
#define SCB_SHPR1_SHPR1(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_SHPR1_SHPR1_SHIFT))&SCB_SHPR1_SHPR1_MASK)
/* SHPR2 Bit Fields */
#define SCB_SHPR2_SHPR2_MASK                 0xFFFFFFFFu
#define SCB_SHPR2_SHPR2_SHIFT                0u
#define SCB_SHPR2_SHPR2_WIDTH                32u
#define SCB_SHPR2_SHPR2(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_SHPR2_SHPR2_SHIFT))&SCB_SHPR2_SHPR2_MASK)
/* SHPR3 Bit Fields */
#define SCB_SHPR3_SHPR3_MASK                 0xFFFFFFFFu
#define SCB_SHPR3_SHPR3_SHIFT                0u
#define SCB_SHPR3_SHPR3_WIDTH                32u
#define SCB_SHPR3_SHPR3(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_SHPR3_SHIFT))&SCB_SHPR3_SHPR3_MASK)
/* SHCSR Bit Fields */
#define SCB_SHCSR_MEMFAULTACT_MASK           0x1u
#define SCB_SHCSR_MEMFAULTACT_SHIFT          0u
#define SCB_SHCSR_MEMFAULTACT_WIDTH          1u
#define SCB_SHCSR_MEMFAULTACT(x)             (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_MEMFAULTACT_SHIFT))&SCB_SHCSR_MEMFAULTACT_MASK)
#define SCB_SHCSR_BUSFAULTACT_MASK           0x2u
#define SCB_SHCSR_BUSFAULTACT_SHIFT          1u
#define SCB_SHCSR_BUSFAULTACT_WIDTH          1u
#define SCB_SHCSR_BUSFAULTACT(x)             (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_BUSFAULTACT_SHIFT))&SCB_SHCSR_BUSFAULTACT_MASK)
#define SCB_SHCSR_USGFAULTACT_MASK           0x8u
#define SCB_SHCSR_USGFAULTACT_SHIFT          3u
#define SCB_SHCSR_USGFAULTACT_WIDTH          1u
#define SCB_SHCSR_USGFAULTACT(x)             (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_USGFAULTACT_SHIFT))&SCB_SHCSR_USGFAULTACT_MASK)
#define SCB_SHCSR_SVCALLACT_MASK             0x80u
#define SCB_SHCSR_SVCALLACT_SHIFT            7u
#define SCB_SHCSR_SVCALLACT_WIDTH            1u
#define SCB_SHCSR_SVCALLACT(x)               (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_SVCALLACT_SHIFT))&SCB_SHCSR_SVCALLACT_MASK)
#define SCB_SHCSR_MONITORACT_MASK            0x100u
#define SCB_SHCSR_MONITORACT_SHIFT           8u
#define SCB_SHCSR_MONITORACT_WIDTH           1u
#define SCB_SHCSR_MONITORACT(x)              (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_MONITORACT_SHIFT))&SCB_SHCSR_MONITORACT_MASK)
#define SCB_SHCSR_PENDSVACT_MASK             0x400u
#define SCB_SHCSR_PENDSVACT_SHIFT            10u
#define SCB_SHCSR_PENDSVACT_WIDTH            1u
#define SCB_SHCSR_PENDSVACT(x)               (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_PENDSVACT_SHIFT))&SCB_SHCSR_PENDSVACT_MASK)
#define SCB_SHCSR_SYSTICKACT_MASK            0x800u
#define SCB_SHCSR_SYSTICKACT_SHIFT           11u
#define SCB_SHCSR_SYSTICKACT_WIDTH           1u
#define SCB_SHCSR_SYSTICKACT(x)              (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_SYSTICKACT_SHIFT))&SCB_SHCSR_SYSTICKACT_MASK)
#define SCB_SHCSR_USGFAULTPENDED_MASK        0x1000u
#define SCB_SHCSR_USGFAULTPENDED_SHIFT       12u
#define SCB_SHCSR_USGFAULTPENDED_WIDTH       1u
#define SCB_SHCSR_USGFAULTPENDED(x)          (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_USGFAULTPENDED_SHIFT))&SCB_SHCSR_USGFAULTPENDED_MASK)
#define SCB_SHCSR_MEMFAULTPENDED_MASK        0x2000u
#define SCB_SHCSR_MEMFAULTPENDED_SHIFT       13u
#define SCB_SHCSR_MEMFAULTPENDED_WIDTH       1u
#define SCB_SHCSR_MEMFAULTPENDED(x)          (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_MEMFAULTPENDED_SHIFT))&SCB_SHCSR_MEMFAULTPENDED_MASK)
#define SCB_SHCSR_BUSFAULTPENDED_MASK        0x4000u
#define SCB_SHCSR_BUSFAULTPENDED_SHIFT       14u
#define SCB_SHCSR_BUSFAULTPENDED_WIDTH       1u
#define SCB_SHCSR_BUSFAULTPENDED(x)          (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_BUSFAULTPENDED_SHIFT))&SCB_SHCSR_BUSFAULTPENDED_MASK)
#define SCB_SHCSR_SVCALLPENDED_MASK          0x8000u
#define SCB_SHCSR_SVCALLPENDED_SHIFT         15u
#define SCB_SHCSR_SVCALLPENDED_WIDTH         1u
#define SCB_SHCSR_SVCALLPENDED(x)            (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_SVCALLPENDED_SHIFT))&SCB_SHCSR_SVCALLPENDED_MASK)
#define SCB_SHCSR_MEMFAULTENA_MASK           0x10000u
#define SCB_SHCSR_MEMFAULTENA_SHIFT          16u
#define SCB_SHCSR_MEMFAULTENA_WIDTH          1u
#define SCB_SHCSR_MEMFAULTENA(x)             (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_MEMFAULTENA_SHIFT))&SCB_SHCSR_MEMFAULTENA_MASK)
#define SCB_SHCSR_BUSFAULTENA_MASK           0x20000u
#define SCB_SHCSR_BUSFAULTENA_SHIFT          17u
#define SCB_SHCSR_BUSFAULTENA_WIDTH          1u
#define SCB_SHCSR_BUSFAULTENA(x)             (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_BUSFAULTENA_SHIFT))&SCB_SHCSR_BUSFAULTENA_MASK)
#define SCB_SHCSR_USGFAULTENA_MASK           0x40000u
#define SCB_SHCSR_USGFAULTENA_SHIFT          18u
#define SCB_SHCSR_USGFAULTENA_WIDTH          1u
#define SCB_SHCSR_USGFAULTENA(x)             (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_USGFAULTENA_SHIFT))&SCB_SHCSR_USGFAULTENA_MASK)
/* CFSR Bit Fields */
#define SCB_CFSR_MMFSR_IACCVIOL_MASK         0x1u
#define SCB_CFSR_MMFSR_IACCVIOL_SHIFT        0u
#define SCB_CFSR_MMFSR_IACCVIOL_WIDTH        1u
#define SCB_CFSR_MMFSR_IACCVIOL(x)           (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_MMFSR_IACCVIOL_SHIFT))&SCB_CFSR_MMFSR_IACCVIOL_MASK)
#define SCB_CFSR_MMFSR_DACCVIOL_MASK         0x2u
#define SCB_CFSR_MMFSR_DACCVIOL_SHIFT        1u
#define SCB_CFSR_MMFSR_DACCVIOL_WIDTH        1u
#define SCB_CFSR_MMFSR_DACCVIOL(x)           (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_MMFSR_DACCVIOL_SHIFT))&SCB_CFSR_MMFSR_DACCVIOL_MASK)
#define SCB_CFSR_MMFSR_MUNSTKERR_MASK        0x8u
#define SCB_CFSR_MMFSR_MUNSTKERR_SHIFT       3u
#define SCB_CFSR_MMFSR_MUNSTKERR_WIDTH       1u
#define SCB_CFSR_MMFSR_MUNSTKERR(x)          (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_MMFSR_MUNSTKERR_SHIFT))&SCB_CFSR_MMFSR_MUNSTKERR_MASK)
#define SCB_CFSR_MMFSR_MSTKERR_MASK          0x10u
#define SCB_CFSR_MMFSR_MSTKERR_SHIFT         4u
#define SCB_CFSR_MMFSR_MSTKERR_WIDTH         1u
#define SCB_CFSR_MMFSR_MSTKERR(x)            (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_MMFSR_MSTKERR_SHIFT))&SCB_CFSR_MMFSR_MSTKERR_MASK)
#define SCB_CFSR_MMFSR_MLSPERR_MASK          0x20u
#define SCB_CFSR_MMFSR_MLSPERR_SHIFT         5u
#define SCB_CFSR_MMFSR_MLSPERR_WIDTH         1u
#define SCB_CFSR_MMFSR_MLSPERR(x)            (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_MMFSR_MLSPERR_SHIFT))&SCB_CFSR_MMFSR_MLSPERR_MASK)
#define SCB_CFSR_MMFSR_MMARVALID_MASK        0x80u
#define SCB_CFSR_MMFSR_MMARVALID_SHIFT       7u
#define SCB_CFSR_MMFSR_MMARVALID_WIDTH       1u
#define SCB_CFSR_MMFSR_MMARVALID(x)          (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_MMFSR_MMARVALID_SHIFT))&SCB_CFSR_MMFSR_MMARVALID_MASK)
#define SCB_CFSR_BFSR_IBUSERR_MASK           0x100u
#define SCB_CFSR_BFSR_IBUSERR_SHIFT          8u
#define SCB_CFSR_BFSR_IBUSERR_WIDTH          1u
#define SCB_CFSR_BFSR_IBUSERR(x)             (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_BFSR_IBUSERR_SHIFT))&SCB_CFSR_BFSR_IBUSERR_MASK)
#define SCB_CFSR_BFSR_PRECISERR_MASK         0x200u
#define SCB_CFSR_BFSR_PRECISERR_SHIFT        9u
#define SCB_CFSR_BFSR_PRECISERR_WIDTH        1u
#define SCB_CFSR_BFSR_PRECISERR(x)           (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_BFSR_PRECISERR_SHIFT))&SCB_CFSR_BFSR_PRECISERR_MASK)
#define SCB_CFSR_BFSR_IMPRECISERR_MASK       0x400u
#define SCB_CFSR_BFSR_IMPRECISERR_SHIFT      10u
#define SCB_CFSR_BFSR_IMPRECISERR_WIDTH      1u
#define SCB_CFSR_BFSR_IMPRECISERR(x)         (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_BFSR_IMPRECISERR_SHIFT))&SCB_CFSR_BFSR_IMPRECISERR_MASK)
#define SCB_CFSR_BFSR_UNSTKERR_MASK          0x800u
#define SCB_CFSR_BFSR_UNSTKERR_SHIFT         11u
#define SCB_CFSR_BFSR_UNSTKERR_WIDTH         1u
#define SCB_CFSR_BFSR_UNSTKERR(x)            (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_BFSR_UNSTKERR_SHIFT))&SCB_CFSR_BFSR_UNSTKERR_MASK)
#define SCB_CFSR_BFSR_STKERR_MASK            0x1000u
#define SCB_CFSR_BFSR_STKERR_SHIFT           12u
#define SCB_CFSR_BFSR_STKERR_WIDTH           1u
#define SCB_CFSR_BFSR_STKERR(x)              (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_BFSR_STKERR_SHIFT))&SCB_CFSR_BFSR_STKERR_MASK)
#define SCB_CFSR_BFSR_LSPERR_MASK            0x2000u
#define SCB_CFSR_BFSR_LSPERR_SHIFT           13u
#define SCB_CFSR_BFSR_LSPERR_WIDTH           1u
#define SCB_CFSR_BFSR_LSPERR(x)              (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_BFSR_LSPERR_SHIFT))&SCB_CFSR_BFSR_LSPERR_MASK)
#define SCB_CFSR_BFSR_BFARVALID_MASK         0x8000u
#define SCB_CFSR_BFSR_BFARVALID_SHIFT        15u
#define SCB_CFSR_BFSR_BFARVALID_WIDTH        1u
#define SCB_CFSR_BFSR_BFARVALID(x)           (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_BFSR_BFARVALID_SHIFT))&SCB_CFSR_BFSR_BFARVALID_MASK)
#define SCB_CFSR_UFSR_UNDEFINSTR_MASK        0x10000u
#define SCB_CFSR_UFSR_UNDEFINSTR_SHIFT       16u
#define SCB_CFSR_UFSR_UNDEFINSTR_WIDTH       1u
#define SCB_CFSR_UFSR_UNDEFINSTR(x)          (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_UFSR_UNDEFINSTR_SHIFT))&SCB_CFSR_UFSR_UNDEFINSTR_MASK)
#define SCB_CFSR_UFSR_INVSTATE_MASK          0x20000u
#define SCB_CFSR_UFSR_INVSTATE_SHIFT         17u
#define SCB_CFSR_UFSR_INVSTATE_WIDTH         1u
#define SCB_CFSR_UFSR_INVSTATE(x)            (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_UFSR_INVSTATE_SHIFT))&SCB_CFSR_UFSR_INVSTATE_MASK)
#define SCB_CFSR_UFSR_INVPC_MASK             0x40000u
#define SCB_CFSR_UFSR_INVPC_SHIFT            18u
#define SCB_CFSR_UFSR_INVPC_WIDTH            1u
#define SCB_CFSR_UFSR_INVPC(x)               (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_UFSR_INVPC_SHIFT))&SCB_CFSR_UFSR_INVPC_MASK)
#define SCB_CFSR_UFSR_NOCP_MASK              0x80000u
#define SCB_CFSR_UFSR_NOCP_SHIFT             19u
#define SCB_CFSR_UFSR_NOCP_WIDTH             1u
#define SCB_CFSR_UFSR_NOCP(x)                (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_UFSR_NOCP_SHIFT))&SCB_CFSR_UFSR_NOCP_MASK)
#define SCB_CFSR_UFSR_UNALIGNED_MASK         0x1000000u
#define SCB_CFSR_UFSR_UNALIGNED_SHIFT        24u
#define SCB_CFSR_UFSR_UNALIGNED_WIDTH        1u
#define SCB_CFSR_UFSR_UNALIGNED(x)           (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_UFSR_UNALIGNED_SHIFT))&SCB_CFSR_UFSR_UNALIGNED_MASK)
#define SCB_CFSR_UFSR_DIVBYZERO_MASK         0x2000000u
#define SCB_CFSR_UFSR_DIVBYZERO_SHIFT        25u
#define SCB_CFSR_UFSR_DIVBYZERO_WIDTH        1u
#define SCB_CFSR_UFSR_DIVBYZERO(x)           (((uint32_t)(((uint32_t)(x))<<SCB_CFSR_UFSR_DIVBYZERO_SHIFT))&SCB_CFSR_UFSR_DIVBYZERO_MASK)
/* HFSR Bit Fields */
#define SCB_HFSR_HFSR_MASK                   0xFFFFFFFFu
#define SCB_HFSR_HFSR_SHIFT                  0u
#define SCB_HFSR_HFSR_WIDTH                  32u
#define SCB_HFSR_HFSR(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_HFSR_HFSR_SHIFT))&SCB_HFSR_HFSR_MASK)
/* DFSR Bit Fields */
#define SCB_DFSR_DFSR_MASK                   0xFFFFFFFFu
#define SCB_DFSR_DFSR_SHIFT                  0u
#define SCB_DFSR_DFSR_WIDTH                  32u
#define SCB_DFSR_DFSR(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_DFSR_DFSR_SHIFT))&SCB_DFSR_DFSR_MASK)
/* MMFAR Bit Fields */
#define SCB_MMFAR_MMFAR_MASK                 0xFFFFFFFFu
#define SCB_MMFAR_MMFAR_SHIFT                0u
#define SCB_MMFAR_MMFAR_WIDTH                32u
#define SCB_MMFAR_MMFAR(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_MMFAR_MMFAR_SHIFT))&SCB_MMFAR_MMFAR_MASK)
/* BFAR Bit Fields */
#define SCB_BFAR_BFAR_MASK                   0xFFFFFFFFu
#define SCB_BFAR_BFAR_SHIFT                  0u
#define SCB_BFAR_BFAR_WIDTH                  32u
#define SCB_BFAR_BFAR(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_BFAR_BFAR_SHIFT))&SCB_BFAR_BFAR_MASK)
/* AFSR Bit Fields */
#define SCB_AFSR_AFSR_MASK                   0xFFFFFFFFu
#define SCB_AFSR_AFSR_SHIFT                  0u
#define SCB_AFSR_AFSR_WIDTH                  32u
#define SCB_AFSR_AFSR(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_AFSR_AFSR_SHIFT))&SCB_AFSR_AFSR_MASK)
/* ID_PFR0 Bit Fields */
#define SCB_ID_PFR0_ID_PFR0_MASK             0xFFFFFFFFu
#define SCB_ID_PFR0_ID_PFR0_SHIFT            0u
#define SCB_ID_PFR0_ID_PFR0_WIDTH            32u
#define SCB_ID_PFR0_ID_PFR0(x)               (((uint32_t)(((uint32_t)(x))<<SCB_ID_PFR0_ID_PFR0_SHIFT))&SCB_ID_PFR0_ID_PFR0_MASK)

/*!
 * @}
 */ /* end of group SCB_Register_Masks */

/*!
 * @}
 */ /* end of group SCB_Peripheral_Access_Layer */

#endif  /* #if !defined(SCB_ADDRESS_H_) */

