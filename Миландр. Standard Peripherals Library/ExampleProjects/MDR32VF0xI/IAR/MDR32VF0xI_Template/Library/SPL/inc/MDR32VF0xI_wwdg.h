/**
 *******************************************************************************
 * @file    MDR32VF0xI_wwdg.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    22/03/2024
 * @brief   This file contains all the functions prototypes for the WWDG
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
#ifndef MDR32VF0xI_WWDG_H
#define MDR32VF0xI_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup WWDG WWDG
 * @{
 */

/** @defgroup WWDG_Exported_Types WWDG Exported Types
 * @{
 */

/**
 *  @brief WWDG prescaler.
 */
typedef enum {
    WWDG_PRESCALER_DIV_1 = WWDG_CFR_WDGTB_DIV_1, /*!< WWDG counter clock = (WDG_CLK/4096)/1 */
    WWDG_PRESCALER_DIV_2 = WWDG_CFR_WDGTB_DIV_2, /*!< WWDG counter clock = (WDG_CLK/4096)/2 */
    WWDG_PRESCALER_DIV_4 = WWDG_CFR_WDGTB_DIV_4, /*!< WWDG counter clock = (WDG_CLK/4096)/4 */
    WWDG_PRESCALER_DIV_8 = WWDG_CFR_WDGTB_DIV_8  /*!< WWDG counter clock = (WDG_CLK/4096)/8 */
} WWDG_Prescaler_TypeDef;

#define IS_WWDG_PRESCALER(DIV) (((DIV) == WWDG_PRESCALER_DIV_1) || \
                                ((DIV) == WWDG_PRESCALER_DIV_2) || \
                                ((DIV) == WWDG_PRESCALER_DIV_4) || \
                                ((DIV) == WWDG_PRESCALER_DIV_8))

/** @} */ /* End of the group WWDG_Exported_Types */

/** @defgroup WWDG_Exported_Defines WWDG Exported Defines
 * @{
 */

/** @defgroup WWDG_Window_Value WWDG Window Value
 * @{
 */
#define IS_WWDG_WINDOW_VALUE(VALUE) (((VALUE) >= ((uint32_t)0x40)) && ((VALUE) <= ((uint32_t)0x7F)))

/** @} */ /* End of the group WWDG_Window_Value */

/** @defgroup WWDG_Counter WWDG Counter
 * @{
 */
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= ((uint32_t)0x40)) && ((COUNTER) <= ((uint32_t)0x7F)))

/** @} */ /* End of the group WWDG_Counter */

/** @} */ /* End of the group WWDG_Exported_Defines */

/** @defgroup WWDG_Exported_Functions WWDG Exported Functions
 * @{
 */

void                   WWDG_DeInit(void);
void                   WWDG_SetPrescaler(WWDG_Prescaler_TypeDef PrescalerValue);
WWDG_Prescaler_TypeDef WWDG_GetPrescaler(void);
void                   WWDG_SetWindowValue(uint32_t WindowValue);
uint32_t               WWDG_GetWindowValue(void);
void                   WWDG_ITEnable(void);
void                   WWDG_SetCounter(uint32_t Counter);
uint32_t               WWDG_GetCounter(void);
void                   WWDG_Enable(uint32_t Counter);
FlagStatus             WWDG_GetFlagStatus(void);
void                   WWDG_ClearFlagStatus(void);

/** @} */ /* End of the group WWDG_Exported_Functions */

/** @} */ /* End of the group WWDG */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_WWDG_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_wwdg.h */

