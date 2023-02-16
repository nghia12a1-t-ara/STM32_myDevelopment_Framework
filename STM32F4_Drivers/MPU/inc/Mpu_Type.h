/**
 * Filename		: Mpu_Type.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/2/22
 * Brief		: Typedef for MPU Driver
 */
 
#ifndef __MPU_TYPE_H__
#define __MPU_TYPE_H__

#include "MPU_Base.h"

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/
#define MPU_MIN_REGION_SIZE 							(32U)
#define MPU_MIN_REGION_SIZE_WITH_SUBREGION 				(256U)
#define MPU_EXECUTE_RIGHT_MASK 							(16U)
#define MPU_SCB_CFSR_MMFSR_MASK_WITHOUT_VALID 			(59U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
/**
* @brief          Enumeration listing the outer and inner cache policies when RASR[TEX] == 0x1XX
*/
/* @implements     MPU_CachePolicyType_enum */
typedef enum
{
    MPU_CACHE_POLICY_NO_CACHE                = 0UL,  /* Non-cacheable */
    MPU_CACHE_POLICY_W_BACK_WR_ALLOCATE      = 1UL,  /* Write-back, write and read allocate */
    MPU_CACHE_POLICY_W_THROUGH_NO_W_ALLOCATE = 2UL,  /* Write-through, no write allocate */
    MPU_CACHE_POLICY_W_BACK_NO_W_ALLOCATE    = 3UL   /* Write-back, no write allocate */
} MPU_CachePolicyType;

/**
* @brief          Enumeration listing the memory and cache attributes when RASR[TEX] == 0x0XX
*/
/* @implements    MPU_MemoryType_enum */
typedef enum
{
    MPU_MEM_STRONG_ORDER                 = 0U,  /* Strongly ordered */
    MPU_MEM_DEVICE_SHARED                = 1U,  /* Shared device */
    MPU_MEM_NORMAL_IO_WR_THROUGH         = 2U,  /* Outer and inner write-through, no write allocate */
    MPU_MEM_NORMAL_IO_WR_BACK1           = 3U,  /* Outer and inner write-back, no write allocate */
    MPU_MEM_NORMAL_IO_NO_CACHE           = 4U,  /* Outer and inner Non-cacheable */
    MPU_MEM_NORMAL_IO_WR_BACK2           = 5U,  /* Outer and inner write-back; write and read allocate */
    MPU_MEM_DEVICE_NOSHARE               = 6U,  /* Non-shared device */
    MPU_MEM_NORMAL_CACHEABLE             = 7U,  /* Normal Memory Cache policy enabled */
    MPU_MEM_NO
} MPU_MemoryType;


/**
* @brief          Enumeration listing access permisions
*/
/* @implements    MPU_AccessRightsType_enum */
typedef enum
{
    /* Format: X_R_APP
     * X  = 1 bit : Execute Allow or not
     * R  = 1 bit : Reserved
     *APP = 3 bit : Define Privileged & Uprivileged Access Right
     */
    MPU_PRIV_UNPRIV_NONE        = 0x00U,    /* 0b00000000U : ---|--- */
    MPU_PRIV_RW_UNPRIV_NONE     = 0x01U,    /* 0b00000001U : rw-|--- */
    MPU_PRIV_RWX_UNPRIV_NONE    = 0x11U,    /* 0b00010001U : rwx|--- */
    MPU_PRIV_RW_UNPRIV_R        = 0x02U,    /* 0b00000010U : rw-|r-- */
    MPU_PRIV_RWX_UNPRIV_RX      = 0x12U,    /* 0b00010010U : rwx|r-x */
    MPU_PRIV_RW_UNPRIV_RW       = 0x03U,    /* 0b00000011U : rw-|rw- */
    MPU_PRIV_RWX_UNPRIV_RWX     = 0x13U,    /* 0b00010011U : rwx|rwx */
    MPU_PRIV_R_UNPRIV_NONE      = 0x05U,    /* 0b00000101U : r--|--- */
    MPU_PRIV_RX_UNPRIV_NONE     = 0x15U,    /* 0b00010101U : r-x|--- */
    MPU_PRIV_R_UNPRIV_R         = 0x06U,    /* 0b00000110U : r--|r-- */
    MPU_PRIV_RX_UNPRIV_RX       = 0x16U,    /* 0b00010110U : r-x|r-x */
} MPU_AccessRightsType;

/**
* @brief          Enumeration listing the possible access errors
*/
/* @implements    MPU_ErrorType_enum */
typedef enum
{
    MPU_MEMMAN_ERROR_INSTRUCTION_ACCESS,  /*! IACCVIOL  Instruction access violation */
    MPU_MEMMAN_ERROR_DATA_ACCESS,         /*! DACCVIOL  Data access violation */
    MPU_MEMMAN_ERROR_STACK,               /*! MUNSTKERR MemManage fault on unstacking for a return from exception */
    MPU_MEMMAN_ERROR_UNSTACK,             /*! MSTKERR   MemManage fault on stacking for exception entry*/
    MPU_MEMMAN_ERROR_FLOATING_POINT,      /*! MLSPERR   MemManage fault during floating point lazy state preservation*/
    MPU_MEMMAN_ERROR_MULTIPLE,            /*! MemManage fault Multiple Errors detected */
    MPU_MEMMAN_ERROR_NONE
} MPU_ErrorType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          Configuration structure containing the region configuration
*/
/* @implements    MPU_RegionConfigType_struct */
typedef struct
{
    uint8                       u8RegionNum;          /* Region number                    */
    uint32                      u32StartAddr;         /* Memory region start address      */
    uint32                      u32EndAddr;           /* Memory region end address        */
    MPU_MemoryType        		eMemType;             	  /* Memory Type for region           */
    MPU_AccessRightsType  		eAccessRight;         	  /* Access permission for region     */
} MPU_RegionConfigType;


/**
* @brief          IP configuration structure
*/
/* @implements     MPU_ConfigType_struct */
typedef struct
{
    boolean bDefaultMapEn;                                           /* Enables the default memory map background region */
    boolean bEnableRunHFNMI;                                         /* Enables use of the MPU when in the hard fault, non-maskable interrupt, and FAULTMASK escalated handlers  */
    boolean bEnMemManageInterrupt;                                   /* Enable Memory Manage Fault Exception Handler */
    uint8 u8RegionCnt;                                               /* Region Count */
    const MPU_RegionConfigType * pRegionConfigArr;             		 /* Region configuration array */
} MPU_ConfigType;

/**
* @brief          Structure used to retrieve violation details
*/
/* @implements     MPU_ErrorDetailsType_struct */
typedef struct
{
    uint32 u32Address;			/* Violation address */
    MPU_ErrorType eType;			/* Type of violation */
} MPU_ErrorDetailsType;

#endif /* __MPU_TYPE_H__ */


