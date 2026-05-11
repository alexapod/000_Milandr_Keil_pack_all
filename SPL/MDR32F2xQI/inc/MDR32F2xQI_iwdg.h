/**
 *******************************************************************************
 * @file    MDR32F2xQI_iwdg.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    16/05/2023
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
#ifndef __MDR32F2xQI_IWDG_H
#define __MDR32F2xQI_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup IWDG
 * @{
 */

/** @defgroup IWDG_Exported_Types IWDG Exported Types
 * @{
 */

/**
 * @brief IWDG prescaler
 */
typedef enum {
    IWDG_PRESCALER_DIV_4   = ((uint32_t)0x0 << IWDG_PR_PR_Pos),
    IWDG_PRESCALER_DIV_8   = ((uint32_t)0x1 << IWDG_PR_PR_Pos),
    IWDG_PRESCALER_DIV_16  = ((uint32_t)0x2 << IWDG_PR_PR_Pos),
    IWDG_PRESCALER_DIV_32  = ((uint32_t)0x3 << IWDG_PR_PR_Pos),
    IWDG_PRESCALER_DIV_64  = ((uint32_t)0x4 << IWDG_PR_PR_Pos),
    IWDG_PRESCALER_DIV_128 = ((uint32_t)0x5 << IWDG_PR_PR_Pos),
    IWDG_PRESCALER_DIV_256 = ((uint32_t)0x6 << IWDG_PR_PR_Pos)
} IWDG_Prescaler_TypeDef;

#define IS_IWDG_PRESCALER(DIV) (((DIV) == IWDG_PRESCALER_DIV_4) ||   \
                                ((DIV) == IWDG_PRESCALER_DIV_8) ||   \
                                ((DIV) == IWDG_PRESCALER_DIV_16) ||  \
                                ((DIV) == IWDG_PRESCALER_DIV_32) ||  \
                                ((DIV) == IWDG_PRESCALER_DIV_64) ||  \
                                ((DIV) == IWDG_PRESCALER_DIV_128) || \
                                ((DIV) == IWDG_PRESCALER_DIV_256))

/**
 * @brief IWDG Flags
 */
typedef enum {
    IWDG_FLAG_PVU = IWDG_SR_PVU_Msk, /*!< Prescaler Value Update on going. */
    IWDG_FLAG_RVU = IWDG_SR_RVU_Msk  /*!< Reload Value Update on going. */
} IWDG_Flags_TypeDef;

#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU))

/** @} */ /* End of group IWDG_Exported_Types */

/** @defgroup IWDG_Exported_Defines IWDG Exported Defines
 * @{
 */

/** @defgroup IWDG_Reload IWDG Reload
 * @{
 */

#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)

/** @} */ /* End of group IWDG_Reload */

/** @} */ /* End of group IWDG_Exported_Defines */

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

/** @} */ /* End of group IWDG_Exported_Functions */

/** @} */ /* End of group IWDG */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_IWDG_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_iwdg.h */

