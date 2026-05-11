/**
 *******************************************************************************
 * @file    MDR32VF0xI_iwdg.c
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    16/04/2024
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
#include "MDR32VF0xI_iwdg.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @defgroup IWDG IWDG
 * @{
 */

/** @defgroup IWDG_Exported_Functions IWDG Exported Functions
 * @{
 */

/**
 * @brief  Enable the write access to the IWDG_PR and IWDG_RLR registers.
 * @param  None.
 * @return None.
 */
void IWDG_WriteAccessEnable(void)
{
    MDR_IWDG->KR = IWDG_KR_KEY_WRITE_ENABLE;
}

/**
 * @brief   Set an IWDG prescaler value.
 * @note    IWDG is clocked by the frequency of the LSI generator.
 * @warning With IWDG and LSI enabled, register will be written only when PVU=0 in the SR register.
 * @param   IWDG_PrescalerValue: @ref IWDG_Prescaler_TypeDef - specify the IWDG prescaler value.
 * @return  None.
 */
void IWDG_SetPrescaler(IWDG_Prescaler_TypeDef IWDG_PrescalerValue)
{
    /* Check the parameters. */
    assert_param(IS_IWDG_PRESCALER(IWDG_PrescalerValue));

    MDR_IWDG->PR = (uint32_t)IWDG_PrescalerValue;
}

/**
 * @brief  Get an IWDG prescaler value.
 * @param  None.
 * @return @ref IWDG_Prescaler_TypeDef - the current IWDG prescaler value.
 */
IWDG_Prescaler_TypeDef IWDG_GetPrescaler(void)
{
    return (IWDG_Prescaler_TypeDef)(MDR_IWDG->PR);
}

/**
 * @brief  Set an IWDG reload value.
 * @warning With IWDG and LSI enabled, register will be written only when RVU=0 in the SR register.
 * @param  Reload: Specify an IWDG reload value.
 *         This parameter must be a number from 0 to 0x0FFF.
 * @return None.
 */
void IWDG_SetReload(uint32_t Reload)
{
    /* Check the parameters. */
    assert_param(IS_IWDG_RELOAD(Reload));

    MDR_IWDG->RLR = Reload;
}

/**
 * @brief  Get an IWDG reload value.
 * @note   Reading and writing of this register is allowed only if bit RVU=0 in SR register.
 * @return An IWDG reload value.
 */
uint32_t IWDG_GetReload(void)
{
    return (MDR_IWDG->RLR & IWDG_RLR_RLR_Msk);
}

/**
 * @brief  Reload the IWDG counter with the value defined in the reload register
 *         (write access to IWDG_PR and IWDG_RLR registers is disabled).
 * @param  None.
 * @return None.
 */
void IWDG_ReloadCounter(void)
{
    MDR_IWDG->KR = IWDG_KR_KEY_RELOAD;
}

/**
 * @brief  Enable the IWDG (write access to the IWDG_PR and IWDG_RLR registers is disabled).
 * @param  None.
 * @return None.
 */
void IWDG_Enable(void)
{
    MDR_IWDG->KR = IWDG_KR_KEY_ENABLE;
}

/**
 * @brief  Check whether a specified IWDG flag is set or not.
 * @param  IWDG_Flag: @ref IWDG_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - a state of IWDG_Flag (SET or RESET).
 */
FlagStatus IWDG_GetFlagStatus(IWDG_Flags_TypeDef IWDG_Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_IWDG_FLAG(IWDG_Flag));

    if ((MDR_IWDG->SR & (uint32_t)IWDG_Flag) != RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    /* Return the  flag status. */
    return Status;
}

/** @} */ /* End of the group IWDG_Exported_Functions */

/** @} */ /* End of the group IWDG */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_iwdg.c */

