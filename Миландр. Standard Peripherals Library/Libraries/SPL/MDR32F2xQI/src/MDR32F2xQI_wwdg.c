/**
 *******************************************************************************
 * @file    MDR32F2xQI_wwdg.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    19/05/2023
 * @brief   This file contains all the WWDG firmware functions.
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
#include "MDR32F2xQI_wwdg.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @defgroup WWDG WWDG
 * @{
 */

/** @defgroup WWDG_Exported_Functions WWDG Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
 * @param  None.
 * @retval None.
 */
void WWDG_DeInit(void)
{
    MDR_WWDG->CR  = 0;
    MDR_WWDG->CFR = 0;
    MDR_WWDG->SR  = 0;
}

/**
 * @brief  Sets the WWDG Prescaler.
 * @param  PrescalerValue - @ref WWDG_Prescaler_TypeDef - specifies the WWDG Prescaler.
 * @retval None.
 */
void WWDG_SetPrescaler(WWDG_Prescaler_TypeDef PrescalerValue)
{
    uint32_t TempReg;

    /* Check the parameters */
    assert_param(IS_WWDG_PRESCALER(PrescalerValue));

    /* Clear WDGTB[1:0] bits */
    TempReg = MDR_WWDG->CFR & ~WWDG_CFR_WGTB_Msk;

    /* Set WDGTB[1:0] bits according to PrescalerValue value */
    TempReg |= (uint32_t)PrescalerValue;

    /* Store the new value */
    MDR_WWDG->CFR = TempReg;
}

/**
 * @brief  Gets the WWDG Prescaler.
 * @param  None.
 * @retval @ref WWDG_Prescaler_TypeDef - Current WWDG prescaler.
 */
WWDG_Prescaler_TypeDef WWDG_GetPrescaler(void)
{
    return (WWDG_Prescaler_TypeDef)(MDR_WWDG->CFR & WWDG_CFR_WGTB_Msk);
}

/**
 * @brief  Sets the WWDG window value.
 * @param  WindowValue: specifies the window value to be compared to the downcounter.
 *         This parameter must be a number between 0x40 and 0x7F.
 * @retval None.
 */
void WWDG_SetWindowValue(uint32_t WindowValue)
{
    uint32_t TempReg;

    /* Check the parameters */
    assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));

    /* Clear W[6:0] bits */
    TempReg = MDR_WWDG->CFR & (uint32_t)(~WWDG_CFR_W_Msk);

    /* Set W[6:0] bits according to WindowValue value */
    TempReg |= WindowValue & (uint32_t)WWDG_CFR_W_Msk;

    /* Store the new value */
    MDR_WWDG->CFR = TempReg;
}

/**
 * @brief  Gets the WWDG window value.
 * @param  None.
 * @retval Current window value.
 */
uint32_t WWDG_GetWindowValue(void)
{
    return (MDR_WWDG->CFR & WWDG_CFR_W_Msk);
}

/**
 * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
 * @param  None.
 * @retval None.
 */
void WWDG_ITEnable(void)
{
    MDR_WWDG->CFR |= WWDG_CFR_EWI;
}

/**
 * @brief  Sets the WWDG counter value.
 * @param  Counter: specifies the watchdog counter value.
 *         This parameter must be a number between 0x40 and 0x7F.
 * @retval None.
 */
void WWDG_SetCounter(uint32_t Counter)
{
    /* Check the parameters */
    assert_param(IS_WWDG_COUNTER(Counter));

    /* Write to T[6:0] bits to configure the counter value, no need to do
       a read-modify-write; writing a 0 to WDGA bit does nothing */
    MDR_WWDG->CR = Counter & WWDG_CR_T_Msk;
}

/**
 * @brief  Gets the WWDG counter value.
 * @param  None.
 * @retval Current counter value.
 */
uint32_t WWDG_GetCounter(void)
{
    return (MDR_WWDG->CR & WWDG_CR_T_Msk);
}

/**
 * @brief  Enables WWDG and load the counter value.
 * @param  Counter: specifies the watchdog counter value.
 *         This parameter must be a number between 0x40 and 0x7F.
 * @retval None.
 */
void WWDG_Enable(uint32_t Counter)
{
    /* Check the parameters */
    assert_param(IS_WWDG_COUNTER(Counter));

    MDR_WWDG->CR = WWDG_CR_WDGA_Msk | Counter;
}

/**
 * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
 * @param  None.
 * @retval @ref FlagStatus - Current state of the Early Wakeup interrupt flag (SET or RESET).
 */
FlagStatus WWDG_GetFlagStatus(void)
{
    return (FlagStatus)(MDR_WWDG->SR);
}

/**
 * @brief  Clears Early Wakeup interrupt flag.
 * @param  None.
 * @retval None.
 */
void WWDG_ClearFlagStatus(void)
{
    MDR_WWDG->SR = (uint32_t)RESET;
}

/** @} */ /* End of group WWDG_Exported_Functions */

/** @} */ /* End of group WWDG */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_wwdg.c */

