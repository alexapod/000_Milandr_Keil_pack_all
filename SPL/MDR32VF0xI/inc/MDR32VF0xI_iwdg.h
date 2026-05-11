/**
 *******************************************************************************
 * @file    MDR32VF0xI_iwdg.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    22/03/2024
 * @brief   This file contains all the functions prototypes for the IWDG
 *          firmware library.
 *******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2025 Milandr</center></h2>
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MDR32VF0xI_IWDG_H
#define MDR32VF0xI_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup IWDG IWDG
 * @{
 */

/** @defgroup IWDG_Exported_Types IWDG Exported Types
 * @{
 */

/**
 * @brief IWDG prescaler.
 */
typedef enum {
    IWDG_PRESCALER_DIV_4   = IWDG_PR_PR_DIV_4,   /*!< Frequency divided by 4. */
    IWDG_PRESCALER_DIV_8   = IWDG_PR_PR_DIV_8,   /*!< Frequency divided by 8. */
    IWDG_PRESCALER_DIV_16  = IWDG_PR_PR_DIV_16,  /*!< Frequency divided by 16. */
    IWDG_PRESCALER_DIV_32  = IWDG_PR_PR_DIV_32,  /*!< Frequency divided by 32. */
    IWDG_PRESCALER_DIV_64  = IWDG_PR_PR_DIV_64,  /*!< Frequency divided by 64. */
    IWDG_PRESCALER_DIV_128 = IWDG_PR_PR_DIV_128, /*!< Frequency divided by 128. */
    IWDG_PRESCALER_DIV_256 = IWDG_PR_PR_DIV_256  /*!< Frequency divided by 256. */
} IWDG_Prescaler_TypeDef;

#define IS_IWDG_PRESCALER(DIV) (((DIV) == IWDG_PRESCALER_DIV_4) ||   \
                                ((DIV) == IWDG_PRESCALER_DIV_8) ||   \
                                ((DIV) == IWDG_PRESCALER_DIV_16) ||  \
                                ((DIV) == IWDG_PRESCALER_DIV_32) ||  \
                                ((DIV) == IWDG_PRESCALER_DIV_64) ||  \
                                ((DIV) == IWDG_PRESCALER_DIV_128) || \
                                ((DIV) == IWDG_PRESCALER_DIV_256))

/**
 * @brief IWDG flags.
 */
typedef enum {
    IWDG_FLAG_PVU = IWDG_SR_PVU_Msk, /*!< Prescaler value updating flag. */
    IWDG_FLAG_RVU = IWDG_SR_RVU_Msk  /*!< Reload value updating flag. */
} IWDG_Flags_TypeDef;

#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || \
                            ((FLAG) == IWDG_FLAG_RVU))

/** @} */ /* End of the group IWDG_Exported_Types */

/** @defgroup IWDG_Exported_Defines IWDG Exported Defines
 * @{
 */

/** @defgroup IWDG_Reload IWDG Reload
 * @{
 */

#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= ((uint32_t)0xFFF))

/** @} */ /* End of the group IWDG_Reload */

/** @} */ /* End of the group IWDG_Exported_Defines */

/** @defgroup IWDG_Exported_Functions IWDG Exported Functions
 * @{
 */

void                   IWDG_WriteAccessEnable(void);
void                   IWDG_SetPrescaler(IWDG_Prescaler_TypeDef IWDG_PrescalerValue);
IWDG_Prescaler_TypeDef IWDG_GetPrescaler(void);
void                   IWDG_SetReload(uint32_t Reload);
uint32_t               IWDG_GetReload(void);
void                   IWDG_ReloadCounter(void);
void                   IWDG_Enable(void);
FlagStatus             IWDG_GetFlagStatus(IWDG_Flags_TypeDef IWDG_Flag);

/** @} */ /* End of the group IWDG_Exported_Functions */

/** @} */ /* End of the group IWDG */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_IWDG_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_iwdg.h */

