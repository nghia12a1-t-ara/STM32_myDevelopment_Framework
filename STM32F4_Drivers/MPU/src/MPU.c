/*
 * MPU.c
 *
 *  Created on: Mar 29, 2022
 *      Author: Admin
 */

/*==================================================================================================
==================================================================================================*/

/**
*   @file MPU.c
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "MPU.h"

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

void MPU_Init(const MPU_ConfigType * pConfig);

void MPU_SetRegionConfig(uint8_t u8RegionNum,
                                          const MPU_RegionConfigType * const pUserConfigPtr
                                         );

void MPU_Deinit(void);

void MPU_EnableRegion(uint8_t u8RegionNum, boolean bEnable);

void MPU_SetAccessRight(uint8_t u8RegionNum, MPU_AccessRightsType eRights);

static uint8_t MPU_GetDRegion(MPU_Type const * const base);

static uint32_t MPU_CalculateRegionSize(uint32_t u32StartAddr, uint32_t u32EndAddr);

static void MPU_SetMemoryType(uint32_t * pRegionAttr, MPU_MemoryType eType);

static void MPU_ComputeAccessRights(uint32_t * pRegionAttr, MPU_AccessRightsType eAccessRights);

void MPU_GetErrorRegisters(uint32_t * pMmfsr, uint32_t * pAddress);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/*!
 *  @brief Get Memory regions
 *
 *  @param[in] base The MPU peripheral base address.
 *  @return Number of regions supported by MPU ,if 0 MPU is not supported by core.
 *
 */
static uint8_t MPU_GetDRegion(MPU_Type const * const base)
{
    return (uint8_t)((base->TYPE & MPU_TYPE_DREGION_MASK)>>MPU_TYPE_DREGION_SHIFT) & 0xFFU;
}

/*!
 * @brief Calculate log2(n) size for a specific region
 *
 * @param[in] u32StartAddr Region Start address
 * @param[in] u32EndAddr   Region End address
 *
 * @return Region size as a power of 2
 */
static uint32_t MPU_CalculateRegionSize(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
    uint32_t finalSize = 0UL;
    uint32_t u32Size = 0UL;

    u32Size = u32EndAddr - u32StartAddr;
    while (u32Size > 0U)
    {
        finalSize++;
        u32Size >>= 1U;
    }

    return finalSize;
}

/*!
 * @brief Configure memory type
 *
 * @param[out] pRegionAttr RASR register where to save the attributes
 * @param[in]  eType       Memory type
 *
 * @return void
 */
static void MPU_SetMemoryType(uint32_t * pRegionAttr, MPU_MemoryType eType)
{
    /* 7-6, 5-3, 2, 1, 0 bit S always clear to not influence previous setting
     *      Res, TEX, S, C, B */
    switch(eType)
    {
        case MPU_MEM_STRONG_ORDER:								/* 0b00000000,  MPU_MEMORY_TYPE_STRONG_ORDER  */
            break;
        case MPU_MEM_DEVICE_SHARED:
            *pRegionAttr |= ((uint32_t)0x01U << MPU_A_RASR_B_SHIFT);	/* 0b00000001,  MPU_MEMORY_TYPE_DEVICE_SHARED */
            break;
        case MPU_MEM_NORMAL_IO_WR_THROUGH:
            *pRegionAttr |= ((uint32_t)0x02U << MPU_A_RASR_B_SHIFT);	/* 0b00000010,  MPU_MEMORY_TYPE_NORMAL_IN_OUT_WRITE_THROUGH */
            break;
        case MPU_MEM_NORMAL_IO_WR_BACK1:
            *pRegionAttr |= ((uint32_t)0x03U << MPU_A_RASR_B_SHIFT);	/* 0b00000011,  MPU_MEMORY_TYPE_NORMAL_IN_OUT_WRITE_BACK1 */
            break;
        case MPU_MEM_NORMAL_IO_NO_CACHE:
            *pRegionAttr |= ((uint32_t)0x08U << MPU_A_RASR_B_SHIFT);	/* 0b00001000,  MPU_MEMORY_TYPE_NORMAL_IN_OUT_NO_CACHE */
            break;
        case MPU_MEM_NORMAL_IO_WR_BACK2:
            *pRegionAttr |= ((uint32_t)0x0BU << MPU_A_RASR_B_SHIFT);	/* 0b00001011,  MPU_MEMORY_TYPE_NORMAL_IN_OUT_WRITE_BACK2 */
            break;
        case MPU_MEM_DEVICE_NOSHARE:
            *pRegionAttr |= ((uint32_t)0x10U << MPU_A_RASR_B_SHIFT);	/* 0b00010000,  MPU_MEMORY_TYPE_DEVICE_NOSHARE */
            break;
        case MPU_MEM_NORMAL_CACHEABLE:
            *pRegionAttr |= ((uint32_t)0x20U << MPU_A_RASR_B_SHIFT);	/* 0b00100000   MPU_MEMORY_TYPE_NORMAL_CACHEABLE */
            break;
        default:
            break;
    }

}

/*!
 * @brief Set access rights
 *
 * @param[out] pRegionAttr   RASR register where to save the attributes
 * @param[in]  eAccessRights Region access rights
 *
 * @return void
 */
static void MPU_ComputeAccessRights(uint32_t * pRegionAttr, MPU_AccessRightsType eAccessRights)
{
    *pRegionAttr &= ~(MPU_RASR_AP_MASK | MPU_RASR_XN_MASK);
    *pRegionAttr |= MPU_RASR_AP(eAccessRights);
    if (((uint8_t)eAccessRights & (uint8_t)MPU_EXECUTE_RIGHT_MASK) == (uint8_t)0U)
    {
        *pRegionAttr |= MPU_RASR_XN(1UL);
    }
    else
    {
        *pRegionAttr &= ~MPU_RASR_XN(1UL);
    }

}

/*!
 * @brief Retrieve fault information from SCB
 *
 * @param[out] pMmfsr   SCB->MMFSR register contents
 * @param[out] pAddress Address of the violation
 *
 * @return void
 */
void MPU_GetErrorRegisters(uint32_t * pMmfsr, uint32_t * pAddress)
{
    *pMmfsr = SCB->CFSR & (uint32_t)MPU_SCB_CFSR_MMFSR_MASK_WITHOUT_VALID;
    if (((SCB->CFSR & (uint32_t)SCB_CFSR_MMFSR_MMARVALID_MASK) >> (uint32_t)SCB_CFSR_MMFSR_MMARVALID_SHIFT) == (uint32_t)1UL)
    {
        *pAddress = (uint32_t)SCB->MMFAR;
    }
    else
    {
        *pAddress = 0xFFFFFFFFUL;
    }
}

/**
 * @brief         Initializes the Memory Protection Unit general parameters and
 *                region configurations
 *
 * @details       This function is non-reentrant
 *
 * @param[in]     pConfig: pointer to configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 */
void MPU_Init(const MPU_ConfigType * pConfig)
{
    uint8_t region;
    const MPU_RegionConfigType * regionCfg;
    MPU_Type * base = MPU;

    /* Reset the peripheral to the default settings */
    MPU_Deinit();

    /* Configure MPU general settings */
    if (pConfig->bDefaultMapEn == TRUE)
    {
        base->CTRL |= MPU_CTRL_PRIVDEFENA_MASK;
    }
    else
    {
        base->CTRL &= (~((uint32_t)MPU_CTRL_PRIVDEFENA_MASK));
    }

    if (pConfig->bEnableRunHFNMI == TRUE)
    {
        base->CTRL |=MPU_CTRL_HFNMIENA_MASK;
    }
    else
    {
        base->CTRL &= (~((uint32_t)MPU_CTRL_HFNMIENA_MASK));
    }

    if (pConfig->bEnMemManageInterrupt == TRUE)
    {
        SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_MASK;
    }
    else
    {
        SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_MASK;
    }

    for (region = 0U; region < pConfig->u8RegionCnt; region++)
    {
        regionCfg = &pConfig->pRegionConfigArr[region];
        MPU_SetRegionConfig((pConfig->pRegionConfigArr[region]).u8RegionNum, regionCfg);
    }

    base->CTRL |= MPU_CTRL_ENABLE(1U);
}

/**
 * @brief         Configures the region selected by u8RegionNum with the data from pUserConfigPtr
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum:    region number
 * @param[in]     pUserConfigPtr: pointer to the region configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 */
void MPU_SetRegionConfig(uint8_t u8RegionNum,
                                          const MPU_RegionConfigType * const pUserConfigPtr
                                         )
{
    MPU_Type * base = MPU;
    uint32_t regionSize;
    uint32_t regionAttributes = 0UL;

    /* Calculate log2(region) */
    regionSize = MPU_CalculateRegionSize(pUserConfigPtr->u32StartAddr, pUserConfigPtr->u32EndAddr);

    /* Set the region number */
    base->RNR = u8RegionNum;
    /* Set the region base address */
    base->RBAR = pUserConfigPtr->u32StartAddr;
    /* Set the region size */
    regionAttributes |= MPU_RASR_SIZE(regionSize - 1UL);

    /* Set memory attributes and cacheability options */
    if (pUserConfigPtr->eMemType != MPU_MEM_NORMAL_CACHEABLE)
    {
        MPU_SetMemoryType(&regionAttributes, pUserConfigPtr->eMemType);
    }
    else
    {
        //MPU_SetCachePolicies(&regionAttributes, pUserConfigPtr->eInnerCachePolicy, pUserConfigPtr->eOuterCachePolicy);
    }

    /* Compute access rights */
    MPU_ComputeAccessRights(&regionAttributes, pUserConfigPtr->eAccessRight);

    /* Enable Region */
    regionAttributes |= MPU_RASR_ENABLE(1UL);

    /* Write final values */
    base->RASR = regionAttributes;
}

/**
 * @brief         Disables the module and resets all region configurations
 *
 * @details       This function is Reentrant
 *
 * @return        void
 *
 * @api
 *
 * @pre
 */
void MPU_Deinit(void)
{
    uint8_t region;
    MPU_Type * base = MPU;

    base->CTRL &= ~(MPU_CTRL_PRIVDEFENA_MASK | MPU_CTRL_HFNMIENA_MASK | MPU_CTRL_ENABLE_MASK);

    for (region = 0U; region < MPU_GetDRegion(base); region++)
    {
        base->RNR = (uint32_t)region;
        base->RASR = 0UL;
        base->RBAR = 0UL;
    }
}

/**
 * @brief         Enables or disabled a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     bEnable  : Specifies whether the region is enabled or disabled
 * @return        void
 *
 * @api
 *
 * @pre
 *
 */
void MPU_EnableRegion(uint8_t u8RegionNum, boolean bEnable)
{
    MPU_Type * base = MPU;

    base->RNR = (uint32_t)u8RegionNum;
    if (bEnable == TRUE)
    {
        base->RASR |= MPU_RASR_ENABLE(1UL);
    }
    else
    {
        base->RASR &= ~MPU_RASR_ENABLE(1UL);
    }
}

/**
 * @brief         Modify the access rights for a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     eRights     : Specifies the new access rights
 * @return        void
 *
 * @api
 *
 * @pre
 *
 */
void MPU_SetAccessRight(uint8_t u8RegionNum, MPU_AccessRightsType eRights)
{
    uint32_t regionAttributes;
    MPU_Type * base = MPU;

    base->RNR = (uint32_t)u8RegionNum;
    regionAttributes = base->RASR;
    MPU_ComputeAccessRights(&regionAttributes, eRights);

    base->RASR = regionAttributes;
}

/**
 * @brief         Retrieve error details
 * @implements    MPU_GetErrorDetails_Activity
 */
boolean MPU_GetErrorDetails(MPU_ErrorDetailsType * pErrorDetails)
{
    boolean result = FALSE;
    uint32_t  mmfsr;
    uint32_t  mmfsrCopy;
    uint32_t  errorAddress;
    uint8_t   errorCount = 0U;

    MPU_GetErrorRegisters(&mmfsr, &errorAddress);

    mmfsrCopy = mmfsr;
    while (mmfsr != 0U)
    {
        errorCount += (uint8_t)(mmfsr & 1UL);
        mmfsr >>= 1UL;
    }

    if (errorCount > 1U)
    {
        pErrorDetails->eType = MPU_MEMMAN_ERROR_MULTIPLE;
    }
    else
    {
        mmfsr = mmfsrCopy;
        switch(mmfsr)
        {
            case (1U << SCB_CFSR_MMFSR_IACCVIOL_SHIFT):
                pErrorDetails->eType = MPU_MEMMAN_ERROR_INSTRUCTION_ACCESS;
                break;
            case (1U << SCB_CFSR_MMFSR_DACCVIOL_SHIFT):
                pErrorDetails->eType = MPU_MEMMAN_ERROR_DATA_ACCESS;
                break;
            case (1U << SCB_CFSR_MMFSR_MUNSTKERR_SHIFT):
                pErrorDetails->eType = MPU_MEMMAN_ERROR_UNSTACK;
                break;
            case (1U << SCB_CFSR_MMFSR_MSTKERR_SHIFT):
                pErrorDetails->eType = MPU_MEMMAN_ERROR_STACK;
                break;
            case (1U << SCB_CFSR_MMFSR_MLSPERR_SHIFT):
                pErrorDetails->eType = MPU_MEMMAN_ERROR_FLOATING_POINT;
                break;
            default:
                pErrorDetails->eType = MPU_MEMMAN_ERROR_NONE;
                break;
        }
    }

    pErrorDetails->u32Address = errorAddress;

    if (errorCount > 0U)
    {
        result = TRUE;
    }

    return result;
}

/** @} */

