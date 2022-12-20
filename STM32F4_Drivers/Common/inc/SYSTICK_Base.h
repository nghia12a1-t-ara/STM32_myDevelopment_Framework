/**
 * Filename		: SYSTICK_Base.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Peripheral Access Layer for System Timer
 */

/* Prevention from multiple including the same memory map */
#if !defined(__SYSTICK_BASE_H__)  /* Check if memory map has not been already included */
#define __SYSTICK_BASE_H__

#include "Std_Types.h"

/* ----------------------------------------------------------------------------
   -- SysTick Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/** SysTick - Size of Registers Arrays */

/** SysTick - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSRr;                               /**< SysTick Control and Status Register, offset: 0x0 */
  __IO uint32_t RVR;                               /**< SysTick Reload Value Register, offset: 0x4 */
  __IO uint32_t CVR;                               /**< SysTick Current Value Register, offset: 0x8 */
  __I  uint32_t CALIB;                             /**< SysTick Calibration Value Register, offset: 0xC */
} SysTick_Type;

/** Number of instances of the SysTick module. */
#define SYSTICK_INSTANCE_COUNT               (1u)


/* SysTick - Peripheral instance base addresses */
/** Peripheral SysTick base address */
#define SYSTICK_BASE                         (0xE000E010u)
/** Peripheral SysTick base pointer */
#define SYSTICK                              ((SysTick_Type *)SYSTICK_BASE)
/** Array initializer of SysTick peripheral base addresses */
#define SYSTICK_BASE_ADDRS                   { SYSTICK_BASE }
/** Array initializer of SysTick peripheral base pointers */
#define SYSTICK_BASE_PTRS                    { SYSTICK }
 /** Number of interrupt vector arrays for the SysTick module. */
#define SYSTICK_IRQS_ARR_COUNT               (1u)
 /** Number of interrupt channels for the SysTick module. */
#define SYSTICK_IRQS_CH_COUNT                (1u)
/** Interrupt vectors for the SysTick peripheral type */
#define SYSTICK_IRQS                         { SysTick_IRQn }

/* ----------------------------------------------------------------------------
   -- SysTick Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Masks SysTick Register Masks
 * @{
 */

/* CSR Bit Fields */
#define SYSTICK_CSR_ENABLE_MASK              0x1u
#define SYSTICK_CSR_ENABLE_SHIFT             0u
#define SYSTICK_CSR_ENABLE_WIDTH             1u
#define SYSTICK_CSR_ENABLE(x)                (((uint32_t)(((uint32_t)(x))<<SYSTICK_CSR_ENABLE_SHIFT))&SYSTICK_CSR_ENABLE_MASK)
#define SYSTICK_CSR_TICKINT_MASK             0x2u
#define SYSTICK_CSR_TICKINT_SHIFT            1u
#define SYSTICK_CSR_TICKINT_WIDTH            1u
#define SYSTICK_CSR_TICKINT(x)               (((uint32_t)(((uint32_t)(x))<<SYSTICK_CSR_TICKINT_SHIFT))&SYSTICK_CSR_TICKINT_MASK)
#define SYSTICK_CSR_CLKSOURCE_MASK           0x4u
#define SYSTICK_CSR_CLKSOURCE_SHIFT          2u
#define SYSTICK_CSR_CLKSOURCE_WIDTH          1u
#define SYSTICK_CSR_CLKSOURCE(x)             (((uint32_t)(((uint32_t)(x))<<SYSTICK_CSR_CLKSOURCE_SHIFT))&SYSTICK_CSR_CLKSOURCE_MASK)
#define SYSTICK_CSR_COUNTFLAG_MASK           0x10000u
#define SYSTICK_CSR_COUNTFLAG_SHIFT          16u
#define SYSTICK_CSR_COUNTFLAG_WIDTH          1u
#define SYSTICK_CSR_COUNTFLAG(x)             (((uint32_t)(((uint32_t)(x))<<SYSTICK_CSR_COUNTFLAG_SHIFT))&SYSTICK_CSR_COUNTFLAG_MASK)
/* RVR Bit Fields */
#define SYSTICK_RVR_RELOAD_MASK              0xFFFFFFu
#define SYSTICK_RVR_RELOAD_SHIFT             0u
#define SYSTICK_RVR_RELOAD_WIDTH             24u
#define SYSTICK_RVR_RELOAD(x)                (((uint32_t)(((uint32_t)(x))<<SYSTICK_RVR_RELOAD_SHIFT))&SYSTICK_RVR_RELOAD_MASK)
/* CVR Bit Fields */
#define SYSTICK_CVR_CURRENT_MASK             0xFFFFFFu
#define SYSTICK_CVR_CURRENT_SHIFT            0u
#define SYSTICK_CVR_CURRENT_WIDTH            24u
#define SYSTICK_CVR_CURRENT(x)               (((uint32_t)(((uint32_t)(x))<<SYSTICK_CVR_CURRENT_SHIFT))&SYSTICK_CVR_CURRENT_MASK)
/* CALIB Bit Fields */
#define SYSTICK_CALIB_TENMS_MASK             0xFFFFFFu
#define SYSTICK_CALIB_TENMS_SHIFT            0u
#define SYSTICK_CALIB_TENMS_WIDTH            24u
#define SYSTICK_CALIB_TENMS(x)               (((uint32_t)(((uint32_t)(x))<<SYSTICK_CALIB_TENMS_SHIFT))&SYSTICK_CALIB_TENMS_MASK)
#define SYSTICK_CALIB_SKEW_MASK              0x40000000u
#define SYSTICK_CALIB_SKEW_SHIFT             30u
#define SYSTICK_CALIB_SKEW_WIDTH
#define SYSTICK_CALIB_SKEW(x)                (((uint32_t)(((uint32_t)(x))<<SYSTICK_CALIB_SKEW_SHIFT))&SYSTICK_CALIB_SKEW_MASK)
#define SYSTICK_CALIB_NOREF_MASK             0x80000000u
#define SYSTICK_CALIB_NOREF_SHIFT            31u
#define SYSTICK_CALIB_NOREF_WIDTH            1u
#define SYSTICK_CALIB_NOREF(x)               (((uint32_t)(((uint32_t)(x))<<SYSTICK_CALIB_NOREF_SHIFT))&SYSTICK_CALIB_NOREF_MASK)

#endif  /* #if !defined(__SYSTICK_BASE_H__) */
