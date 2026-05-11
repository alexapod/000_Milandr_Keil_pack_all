/**
 *******************************************************************************
 * @file    MDR32F2xQI_iwdg.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    16/05/2023
 * @brief   This file contains all the IWDG firmware functions.
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

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_iwdg.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @defgroup IWDG IWDG
 * @{
 */

/** @defgroup IWDG_Private_Defines IWDG Private Defines
 * @{
 */

#define KR_KEY_RELOAD       ((uint32_t)0xAAAA)
#define KR_KEY_ENABLE       ((uint32_t)0xCCCC)
#define KR_KEY_WRITE_ENABLE ((uint32_t)0x5555)

/** @} */ /* End of group IWDG_Private_Defines */

/** @defgroup IWDG_Exported_Functions IWDG Exported Functions
 * @{
 */

/**
 * @brief  Enables write access to IWDG_PR and IWDG_RLR registers.
 * @param  None.
 * @retval None.
 */
void IWDG_WriteAccessEnable(void)
{
    MDR_IWDG->KR = KR_KEY_WRITE_ENABLE;
}

/**
 * @brief  Sets IWDG Prescaler value.
 * @note   Watchdog timer IWDG is clocked by the frequency of the LSI generator.
 *         Reading and writing of this register is allowed only if bit PVU=0 in SR register.
 * @param  IWDG_PrescalerValue - @ref IWDG_Prescaler_TypeDef - specifies the IWDG Prescaler value.
 * @retval None.
 */
void IWDG_SetPrescaler(IWDG_Prescaler_TypeDef IWDG_PrescalerValue)
{
    /* Check the parameters */
    assert_param(IS_IWDG_PRESCALER(IWDG_PrescalerValue));

    MDR_IWDG->PR = (uint32_t)IWDG_PrescalerValue;
}

/**
 * @brief  Gets IWDG Prescaler value.
 * @note   Reading and writing of this register is allowed only if bit PVU=0 in SR register.
 * @param  None.
 * @retval @ref IWDG_Prescaler_TypeDef - Current IWDG Prescaler value.
 */
IWDG_Prescaler_TypeDef IWDG_GetPrescaler(void)
{
    return (IWDG_Prescaler_TypeDef)(MDR_IWDG->PR);
}

/**
 * @brief  Sets IWDG Reload value.
 * @note   Reading and writing of this register is allowed only if bit RVU=0 in SR register.
 * @param  Reload: specifies the IWDG Reload value.
 *         This parameter must be a number between 0 and 0x0FFF.
 * @retval None.
 */
void IWDG_SetReload(uint32_t Reload)
{
    /* Check the parameters */
    assert_param(IS_IWDG_RELOAD(Reload));

    MDR_IWDG->RLR = Reload;
}

/**
 * @brief  Gets IWDG Reload value.
 * @note   Reading and writing of this register is allowed only if bit RVU=0 in SR register.
 * @retval IWDG Reload value.
 */
uint32_t IWDG_GetReload(void)
{
    return (MDR_IWDG->RLR & IWDG_RLR_RLR_Msk);
}

/**
 * @brief  Reloads IWDG counter with value defined in the reload register
 *         (write access to IWDG_PR and IWDG_RLR registers disabled).
 * @param  None.
 * @retval None.
 */
void IWDG_ReloadCounter(void)
{
    MDR_IWDG->KR = KR_KEY_RELOAD;
}

/**
 * @brief  Enables IWDG (write access to IWDG_PR and IWDG_RLR registers disabled).
 * @param  None.
 * @retval None.
 */
void IWDG_Enable(void)
{
    MDR_IWDG->KR = KR_KEY_ENABLE;
}

/**
 * @brief  Checks whether the specified IWDG flag is set or not.
 * @param  IWDG_Flag - @ref IWDG_Flags_TypeDef - specifies the flag to check.
 * @retval @ref FlagStatus - The state of IWDG_Flag (SET or RESET).
 */
FlagStatus IWDG_GetFlagStatus(IWDG_Flags_TypeDef IWDG_Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_IWDG_FLAG(IWDG_Flag));

    if ((MDR_IWDG->SR & (uint32_t)IWDG_Flag) != RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    /* Return the flag status */
    return Status;
}

/** @} */ /* End of group IWDG_Exported_Functions */

/** @} */ /* End of group IWDG */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_iwdg.c */

