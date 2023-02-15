/*
** ###################################################################
**     Processor:           STM32
**     Reference manual:    Cortex - M4 Device Generic User Guide
**     Author:              Taarabt
**/

/* Prevention from multiple including the same memory map */
#if !defined(STM32_MPU_H_)  /* Check if memory map has not been already included */
#define STM32_MPU_H_

/* ----------------------------------------------------------------------------
   -- MPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */
#include "Std_Type.h"

/*!
 * @addtogroup MPU_Peripheral_Access_Layer MPU Peripheral Access Layer
 */
/** MPU - Size of Registers Arrays */
#define MPU_A_COUNT                          (3u)

/** MPU - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[3472];
  __I  uint32_t TYPE;                              /* MPU Type Register, offset: 0xD90 */
  __IO uint32_t CTRL;                              /* MPU Control Register, offset: 0xD94 */
  __IO uint32_t RNR;                               /* MPU Region Number Register, offset: 0xD98 */
  __IO uint32_t RBAR;                              /* MPU Region Base Address Register, offset: 0xD9C */
  __IO uint32_t RASR;                              /* MPU Region Attribute and Size Register, offset: 0xDA0 */
  struct {                                         /* offset: 0xDA4, array step: 0x8 */
    __IO uint32_t RBAR;                              /* Alias of RBAR0..Alias of RBAR2, array offset: 0xDA4, array step: 0x8 */
    __IO uint32_t RASR;                              /* Alias of RASR0..Alias of RASR2, array offset: 0xDA8, array step: 0x8 */
  } A[MPU_A_COUNT];
} MPU_Type, *MPU_MemMapPtr;

 /** Number of instances of the MPU module. */
#define MPU_INSTANCE_COUNT                   (1u)

/* MPU - Peripheral instance base addresses */
/** Peripheral MPU base address */
#define MPU_BASE                             (0xE000E000u)
/** Peripheral MPU base pointer */
#define MPU                                  ((MPU_Type *)MPU_BASE)
/** Array initializer of MPU peripheral base addresses */
#define MPU_BASE_ADDRS                       { MPU_BASE }
/** Array initializer of MPU peripheral base pointers */
#define MPU_BASE_PTRS                        { MPU }

/* ----------------------------------------------------------------------------
   -- MPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MPU_Register_Masks MPU Register Masks
 * @{
 */

/* TYPE Bit Fields */
#define MPU_TYPE_SEPARATE_MASK               0x1u
#define MPU_TYPE_SEPARATE_SHIFT              0u
#define MPU_TYPE_SEPARATE_WIDTH              1u
#define MPU_TYPE_SEPARATE(x)                 (((uint32_t)(((uint32_t)(x))<<MPU_TYPE_SEPARATE_SHIFT))&MPU_TYPE_SEPARATE_MASK)
#define MPU_TYPE_DREGION_MASK                0xFF00u
#define MPU_TYPE_DREGION_SHIFT               8u
#define MPU_TYPE_DREGION_WIDTH               8u
#define MPU_TYPE_DREGION(x)                  (((uint32_t)(((uint32_t)(x))<<MPU_TYPE_DREGION_SHIFT))&MPU_TYPE_DREGION_MASK)
#define MPU_TYPE_IREGION_MASK                0xFF0000u
#define MPU_TYPE_IREGION_SHIFT               16u
#define MPU_TYPE_IREGION_WIDTH               8u
#define MPU_TYPE_IREGION(x)                  (((uint32_t)(((uint32_t)(x))<<MPU_TYPE_IREGION_SHIFT))&MPU_TYPE_IREGION_MASK)
/* CTRL Bit Fields */
#define MPU_CTRL_ENABLE_MASK                 0x1u
#define MPU_CTRL_ENABLE_SHIFT                0u
#define MPU_CTRL_ENABLE_WIDTH                1u
#define MPU_CTRL_ENABLE(x)                   (((uint32_t)(((uint32_t)(x))<<MPU_CTRL_ENABLE_SHIFT))&MPU_CTRL_ENABLE_MASK)
#define MPU_CTRL_HFNMIENA_MASK               0x2u
#define MPU_CTRL_HFNMIENA_SHIFT              1u
#define MPU_CTRL_HFNMIENA_WIDTH              1u
#define MPU_CTRL_HFNMIENA(x)                 (((uint32_t)(((uint32_t)(x))<<MPU_CTRL_HFNMIENA_SHIFT))&MPU_CTRL_HFNMIENA_MASK)
#define MPU_CTRL_PRIVDEFENA_MASK             0x4u
#define MPU_CTRL_PRIVDEFENA_SHIFT            2u
#define MPU_CTRL_PRIVDEFENA_WIDTH            1u
#define MPU_CTRL_PRIVDEFENA(x)               (((uint32_t)(((uint32_t)(x))<<MPU_CTRL_PRIVDEFENA_SHIFT))&MPU_CTRL_PRIVDEFENA_MASK)
/* RNR Bit Fields */
#define MPU_RNR_REGION_MASK                  0xFFu
#define MPU_RNR_REGION_SHIFT                 0u
#define MPU_RNR_REGION_WIDTH                 8u
#define MPU_RNR_REGION(x)                    (((uint32_t)(((uint32_t)(x))<<MPU_RNR_REGION_SHIFT))&MPU_RNR_REGION_MASK)
/* RBAR Bit Fields */
#define MPU_RBAR_REGION_MASK                 0xFu
#define MPU_RBAR_REGION_SHIFT                0u
#define MPU_RBAR_REGION_WIDTH                4u
#define MPU_RBAR_REGION(x)                   (((uint32_t)(((uint32_t)(x))<<MPU_RBAR_REGION_SHIFT))&MPU_RBAR_REGION_MASK)
#define MPU_RBAR_VALID_MASK                  0x10u
#define MPU_RBAR_VALID_SHIFT                 4u
#define MPU_RBAR_VALID_WIDTH                 1u
#define MPU_RBAR_VALID(x)                    (((uint32_t)(((uint32_t)(x))<<MPU_RBAR_VALID_SHIFT))&MPU_RBAR_VALID_MASK)
#define MPU_RBAR_ADDR_MASK                   0xFFFFFFE0u
#define MPU_RBAR_ADDR_SHIFT                  5u
#define MPU_RBAR_ADDR_WIDTH                  27u
#define MPU_RBAR_ADDR(x)                     (((uint32_t)(((uint32_t)(x))<<MPU_RBAR_ADDR_SHIFT))&MPU_RBAR_ADDR_MASK)
/* RASR Bit Fields */
#define MPU_RASR_ENABLE_MASK                 0x1u
#define MPU_RASR_ENABLE_SHIFT                0u
#define MPU_RASR_ENABLE_WIDTH                1u
#define MPU_RASR_ENABLE(x)                   (((uint32_t)(((uint32_t)(x))<<MPU_RASR_ENABLE_SHIFT))&MPU_RASR_ENABLE_MASK)
#define MPU_RASR_SIZE_MASK                   0x3Eu
#define MPU_RASR_SIZE_SHIFT                  1u
#define MPU_RASR_SIZE_WIDTH                  5u
#define MPU_RASR_SIZE(x)                     (((uint32_t)(((uint32_t)(x))<<MPU_RASR_SIZE_SHIFT))&MPU_RASR_SIZE_MASK)
#define MPU_RASR_SRD_MASK                    0xFF00u
#define MPU_RASR_SRD_SHIFT                   8u
#define MPU_RASR_SRD_WIDTH                   8u
#define MPU_RASR_SRD(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_RASR_SRD_SHIFT))&MPU_RASR_SRD_MASK)
#define MPU_RASR_B_MASK                      0x10000u
#define MPU_RASR_B_SHIFT                     16u
#define MPU_RASR_B_WIDTH                     1u
#define MPU_RASR_B(x)                        (((uint32_t)(((uint32_t)(x))<<MPU_RASR_B_SHIFT))&MPU_RASR_B_MASK)
#define MPU_RASR_C_MASK                      0x20000u
#define MPU_RASR_C_SHIFT                     17u
#define MPU_RASR_C_WIDTH                     1u
#define MPU_RASR_C(x)                        (((uint32_t)(((uint32_t)(x))<<MPU_RASR_C_SHIFT))&MPU_RASR_C_MASK)
#define MPU_RASR_S_MASK                      0x40000u
#define MPU_RASR_S_SHIFT                     18u
#define MPU_RASR_S_WIDTH                     1u
#define MPU_RASR_S(x)                        (((uint32_t)(((uint32_t)(x))<<MPU_RASR_S_SHIFT))&MPU_RASR_S_MASK)
#define MPU_RASR_TEX_MASK                    0x380000u
#define MPU_RASR_TEX_SHIFT                   19u
#define MPU_RASR_TEX_WIDTH                   3u
#define MPU_RASR_TEX(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_RASR_TEX_SHIFT))&MPU_RASR_TEX_MASK)
#define MPU_RASR_AP_MASK                     0x7000000u
#define MPU_RASR_AP_SHIFT                    24u
#define MPU_RASR_AP_WIDTH                    3u
#define MPU_RASR_AP(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RASR_AP_SHIFT))&MPU_RASR_AP_MASK)
#define MPU_RASR_XN_MASK                     0x10000000u
#define MPU_RASR_XN_SHIFT                    28u
#define MPU_RASR_XN_WIDTH                    1u
#define MPU_RASR_XN(x)                       (((uint32_t)(((uint32_t)(x))<<MPU_RASR_XN_SHIFT))&MPU_RASR_XN_MASK)
/* A_RBAR Bit Fields */
#define MPU_A_RBAR_REGION_MASK               0xFu
#define MPU_A_RBAR_REGION_SHIFT              0u
#define MPU_A_RBAR_REGION_WIDTH              4u
#define MPU_A_RBAR_REGION(x)                 (((uint32_t)(((uint32_t)(x))<<MPU_A_RBAR_REGION_SHIFT))&MPU_A_RBAR_REGION_MASK)
#define MPU_A_RBAR_VALID_MASK                0x10u
#define MPU_A_RBAR_VALID_SHIFT               4u
#define MPU_A_RBAR_VALID_WIDTH               1u
#define MPU_A_RBAR_VALID(x)                  (((uint32_t)(((uint32_t)(x))<<MPU_A_RBAR_VALID_SHIFT))&MPU_A_RBAR_VALID_MASK)
#define MPU_A_RBAR_ADDR_MASK                 0xFFFFFFE0u
#define MPU_A_RBAR_ADDR_SHIFT                5u
#define MPU_A_RBAR_ADDR_WIDTH                27u
#define MPU_A_RBAR_ADDR(x)                   (((uint32_t)(((uint32_t)(x))<<MPU_A_RBAR_ADDR_SHIFT))&MPU_A_RBAR_ADDR_MASK)
/* A_RASR Bit Fields */
#define MPU_A_RASR_ENABLE_MASK               0x1u
#define MPU_A_RASR_ENABLE_SHIFT              0u
#define MPU_A_RASR_ENABLE_WIDTH              1u
#define MPU_A_RASR_ENABLE(x)                 (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_ENABLE_SHIFT))&MPU_A_RASR_ENABLE_MASK)
#define MPU_A_RASR_SIZE_MASK                 0x3Eu
#define MPU_A_RASR_SIZE_SHIFT                1u
#define MPU_A_RASR_SIZE_WIDTH                5u
#define MPU_A_RASR_SIZE(x)                   (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_SIZE_SHIFT))&MPU_A_RASR_SIZE_MASK)
#define MPU_A_RASR_SRD_MASK                  0xFF00u
#define MPU_A_RASR_SRD_SHIFT                 8u
#define MPU_A_RASR_SRD_WIDTH                 8u
#define MPU_A_RASR_SRD(x)                    (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_SRD_SHIFT))&MPU_A_RASR_SRD_MASK)
#define MPU_A_RASR_B_MASK                    0x10000u
#define MPU_A_RASR_B_SHIFT                   16u
#define MPU_A_RASR_B_WIDTH                   1u
#define MPU_A_RASR_B(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_B_SHIFT))&MPU_A_RASR_B_MASK)
#define MPU_A_RASR_C_MASK                    0x20000u
#define MPU_A_RASR_C_SHIFT                   17u
#define MPU_A_RASR_C_WIDTH                   1u
#define MPU_A_RASR_C(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_C_SHIFT))&MPU_A_RASR_C_MASK)
#define MPU_A_RASR_S_MASK                    0x40000u
#define MPU_A_RASR_S_SHIFT                   18u
#define MPU_A_RASR_S_WIDTH                   1u
#define MPU_A_RASR_S(x)                      (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_S_SHIFT))&MPU_A_RASR_S_MASK)
#define MPU_A_RASR_TEX_MASK                  0x380000u
#define MPU_A_RASR_TEX_SHIFT                 19u
#define MPU_A_RASR_TEX_WIDTH                 3u
#define MPU_A_RASR_TEX(x)                    (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_TEX_SHIFT))&MPU_A_RASR_TEX_MASK)
#define MPU_A_RASR_AP_MASK                   0x7000000u
#define MPU_A_RASR_AP_SHIFT                  24u
#define MPU_A_RASR_AP_WIDTH                  3u
#define MPU_A_RASR_AP(x)                     (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_AP_SHIFT))&MPU_A_RASR_AP_MASK)
#define MPU_A_RASR_XN_MASK                   0x10000000u
#define MPU_A_RASR_XN_SHIFT                  28u
#define MPU_A_RASR_XN_WIDTH                  1u
#define MPU_A_RASR_XN(x)                     (((uint32_t)(((uint32_t)(x))<<MPU_A_RASR_XN_SHIFT))&MPU_A_RASR_XN_MASK)

/*!
 * @}
 */ /* end of group MPU_Register_Masks */

/*!
 * @}
 */ /* end of group MPU_Peripheral_Access_Layer */

#endif  /* #if !defined(STM32_MPU_H_) */
