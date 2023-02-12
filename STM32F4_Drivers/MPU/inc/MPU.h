/**
 * Filename		: MPU.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/2/22
 * Brief		: Header MPU Driver
 */

#ifndef __MPU_H__
#define __MPU_H__

#include "MPU_Type.h"
#include "Std_Type.h"
#include "MPU_Config.h"
#include "MPU_Base.h"
#include "SCB_Base.h"

/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/

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
 * */
void MPU_Init(const MPU_ConfigType * pConfig);

/**
 * @brief         Configures the region selected by u8RegionNum with the data from pUserConfigPtr
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum      Region number
 * @param[in]     pUserConfigPtr   Pointer to the region configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void MPU_SetRegionConfig(uint8_t u8RegionNum, const MPU_RegionConfigType * const pUserConfigPtr);

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
 * */
void MPU_Deinit(void);

/**
 * @brief         Enables or disabled a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     bEnable  : Specifies wheter the region is enabled or disabled
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void MPU_EnableRegion(uint8_t u8RegionNum, boolean bEnable);

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
 * */
void MPU_SetAccessRight(uint8_t u8RegionNum, MPU_AccessRightsType eRights);

/**
 * @brief         Retrieve error details
 *
 * @details       This function is Reentrant
 *
 * @param[out]    pErrorDetails : Storage where the data will be saved
 *
 * @return        boolean
 * @retval        TRUE       if an error was present
 * @retval        FALSE      otherwise
 *
 * @api
 *
 * @pre
 *
 * */
boolean MPU_GetErrorDetails(MPU_ErrorDetailsType * pErrorDetails);

/*!
 * @brief Retrieve fault information from SCB
 *
 * @param[out] pMmfsr   SCB->MMFSR register contents
 * @param[out] pAddress Address of the violation
 *
 * @return void
 */
void MPU_GetErrorRegisters(uint32_t * pMmfsr, uint32_t * pAddress);

#endif /* __MPU_H__ */
