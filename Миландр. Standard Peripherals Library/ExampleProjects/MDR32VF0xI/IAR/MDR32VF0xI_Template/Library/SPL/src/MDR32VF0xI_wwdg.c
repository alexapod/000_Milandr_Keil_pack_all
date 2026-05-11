/**
 *******************************************************************************
 * @file    MDR32VF0xI_wwdg.c
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    20/09/2023
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
#include "MDR32VF0xI_wwdg.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @defgroup WWDG WWDG
 * @{
 */

/** @defgroup WWDG_Exported_Functions WWDG Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the WWDG peripheral registers to their default reset values.
 * @param  None.
 * @return None.
 */
void WWDG_DeInit(void)
{
    MDR_WWDG->CR  = 0;
    MDR_WWDG->CFR = 0;
    /* Wait until CR and CFR write is complete. */
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }
    MDR_WWDG->SR = 0;
}

/**
 * @brief  Set a WWDG prescaler.
 * @param  PrescalerValue: @ref WWDG_Prescaler_TypeDef - specify a WWDG prescaler.
 * @return None.
 */
void WWDG_SetPrescaler(WWDG_Prescaler_TypeDef PrescalerValue)
{
    uint32_t TempReg;

    /* Check the parameters. */
    assert_param(IS_WWDG_PRESCALER(PrescalerValue));

    /* Read CFR with cleared WDGTB[1:0] bits. */
    TempReg = MDR_WWDG->CFR & ~WWDG_CFR_WDGTB_Msk;

    /* Set WDGTB[1:0] bits according to PrescalerValue value. */
    TempReg |= (uint32_t)PrescalerValue;

    /* Store a new value. */
    MDR_WWDG->CFR = TempReg;

    /* Wait until CFR write is complete. */
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }
}

/**
 * @brief  Get a WWDG prescaler.
 * @param  None.
 * @return @ref WWDG_Prescaler_TypeDef - a current WWDG prescaler.
 */
WWDG_Prescaler_TypeDef WWDG_GetPrescaler(void)
{
    return (WWDG_Prescaler_TypeDef)(MDR_WWDG->CFR & WWDG_CFR_WDGTB_Msk);
}

/**
 * @brief  Set a WWDG window value.
 * @param  WindowValue: Specify a window value to be compared with the downcounter.
 *         This parameter must be a number from 0x40 to 0x7F.
 * @return None.
 */
void WWDG_SetWindowValue(uint32_t WindowValue)
{
    uint32_t TempReg;

    /* Check the parameters. */
    assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));

    /* Read CFR with cleared W[6:0] bits. */
    TempReg = MDR_WWDG->CFR & (uint32_t)(~WWDG_CFR_W_Msk);

    /* Set W[6:0] bits according to WindowValue value. */
    TempReg |= WindowValue & (uint32_t)WWDG_CFR_W_Msk;

    /* Store a new value. */
    MDR_WWDG->CFR = TempReg;

    /* Wait until CFR write is complete. */
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }
}

/**
 * @brief  Get a WWDG window value.
 * @param  None.
 * @return A current window value.
 */
uint32_t WWDG_GetWindowValue(void)
{
    return (MDR_WWDG->CFR & WWDG_CFR_W_Msk);
}

/**
 * @brief  Enable the WWDG Early Wakeup Interrupt (EWI).
 * @param  None.
 * @return None.
 */
void WWDG_ITEnable(void)
{
    MDR_WWDG->CFR |= WWDG_CFR_EWI;
    /* Wait until CFR write is complete. */
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }
}

/**
 * @brief  Set a WWDG counter value.
 * @param  Counter: Specify a watchdog counter value.
 *         This parameter must be a number from 0x40 to 0x7F.
 * @return None.
 */
void WWDG_SetCounter(uint32_t Counter)
{
    /* Check the parameters. */
    assert_param(IS_WWDG_COUNTER(Counter));

    /* Write to T[6:0] bits to configure a counter value, no need to do
       a read-modify-write; writing a 0 to WDGA bit does nothing. */
    MDR_WWDG->CR = Counter & WWDG_CR_T_Msk;
    /* Wait until CR write is complete. */
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }
}

/**
 * @brief  Get a WWDG counter value.
 * @param  None.
 * @return A current counter value.
 */
uint32_t WWDG_GetCounter(void)
{
    return (MDR_WWDG->CR & WWDG_CR_T_Msk);
}

/**
 * @brief  Enable WWDG and load the counter value.
 * @param  Counter: Specify the watchdog counter value.
 *         This parameter must be a number from 0x40 to 0x7F.
 * @return None.
 */
void WWDG_Enable(uint32_t Counter)
{
    /* Check the parameters. */
    assert_param(IS_WWDG_COUNTER(Counter));

    MDR_WWDG->CR = WWDG_CR_WDGA_Msk | Counter;
    /* Wait until the CR write is completed. */
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }
}

/**
 * @brief  Check whether the Early Wakeup Interrupt flag is set or not.
 * @param  None.
 * @return @ref FlagStatus - a current state of the Early Wakeup Interrupt flag (SET or RESET).
 */
FlagStatus WWDG_GetFlagStatus(void)
{
    return (FlagStatus)(MDR_WWDG->SR);
}

/**
 * @brief  Clear the Early Wakeup Interrupt flag.
 * @param  None.
 * @return None.
 */
void WWDG_ClearFlagStatus(void)
{
    MDR_WWDG->SR = (uint32_t)RESET;
}

/** @} */ /* End of the group WWDG_Exported_Functions */

/** @} */ /* End of the group WWDG */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_wwdg.c */

