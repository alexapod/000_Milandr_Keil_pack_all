/**
 *******************************************************************************
 * @file    MDR32VF0xI_random.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/01/2025
 * @brief   This file contains all the RANDOM firmware functions.
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
#include "MDR32VF0xI_random.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup RANDOM RANDOM
 * @{
 */

/** @defgroup RANDOM_Exported_Functions RANDOM Exported Functions
 * @{
 */

/**
 * @brief  Reset the RANDOM peripheral registers to their default reset values.
 * @param  None.
 * @return None.
 */
void RANDOM_DeInit(void)
{
    MDR_RANDOM->STAT_CTRL = RANDOM_STAT_CTRL_MASK_Msk;
    MDR_RANDOM->INT_CTRL  = 0x00000000;
    MDR_RANDOM->CLK_DIV   = 0x00000007;
    MDR_RANDOM->PAUSE     = 0x00000000;
    MDR_RANDOM->OUTPUT;
}

/**
 * @brief  Initialize the RANDOM peripheral according to the specified
 *         parameters in the RANDOM_InitStruct.
 * @param  RANDOM_InitStruct: The pointer to the @ref RANDOM_InitTypeDef structure
 *         that contains the configuration information for the RANDOM peripheral.
 * @return None.
 */
void RANDOM_Init(const RANDOM_InitTypeDef* RANDOM_InitStruct)
{
    /* Check the parameters. */
    assert_param(IS_RANDOM_WORK_MODE(RANDOM_InitStruct->RANDOM_WorkMode));
    assert_param(IS_RANDOM_GENERATORS(RANDOM_InitStruct->RANDOM_Generators));
    assert_param(IS_FUNCTIONAL_STATE(RANDOM_InitStruct->RANDOM_InterruptEnable));

    MDR_RANDOM->PAUSE     = RANDOM_InitStruct->RANDOM_HotStartPause;
    MDR_RANDOM->CLK_DIV   = (uint32_t)(RANDOM_InitStruct->RANDOM_Prescaler);
    MDR_RANDOM->INT_CTRL  = (uint32_t)(RANDOM_InitStruct->RANDOM_InterruptEnable);
    MDR_RANDOM->STAT_CTRL = ((uint32_t)(RANDOM_InitStruct->RANDOM_WorkMode) |
                             (uint32_t)(RANDOM_InitStruct->RANDOM_Generators));
}

/**
 * @brief  Fill each RANDOM_InitStruct member with its default value.
 * @param  RANDOM_InitStruct: The pointer to the @ref RANDOM_InitTypeDef structure
 *         that is to be initialized.
 * @return None.
 */
void RANDOM_StructInit(RANDOM_InitTypeDef* RANDOM_InitStruct)
{
    RANDOM_InitStruct->RANDOM_WorkMode        = RANDOM_WORK_MODE_STOP;
    RANDOM_InitStruct->RANDOM_Generators      = (RANDOM_GENERATOR_0 | RANDOM_GENERATOR_1);
    RANDOM_InitStruct->RANDOM_InterruptEnable = DISABLE;
    RANDOM_InitStruct->RANDOM_Prescaler       = 7;
    RANDOM_InitStruct->RANDOM_HotStartPause   = 0;
}

/**
 * @brief  Set a work mode.
 * @param  RANDOM_WorkMode: @ref RANDOM_WorkMode_TypeDef - a work mode.
 * @return None.
 */
void RANDOM_SetWorkMode(RANDOM_WorkMode_TypeDef RANDOM_WorkMode)
{
    uint32_t TempReg;

    /* Check the parameters. */
    assert_param(IS_RANDOM_WORK_MODE(RANDOM_WorkMode));

    /* Set a work mode. */
    TempReg = MDR_RANDOM->STAT_CTRL & ~RANDOM_STAT_CTRL_WORK_MODE_Msk;
    TempReg |= (uint32_t)RANDOM_WorkMode;

    MDR_RANDOM->STAT_CTRL = TempReg;
}

/**
 * @brief  Get a work mode.
 * @return @ref RANDOM_WorkMode_TypeDef - a work mode.
 */
RANDOM_WorkMode_TypeDef RANDOM_GetWorkMode(void)
{
    return (RANDOM_WorkMode_TypeDef)(MDR_RANDOM->STAT_CTRL & RANDOM_STAT_CTRL_WORK_MODE_Msk);
}

/**
 * @brief  Set the generators state.
 * @param  RANDOM_Generators: Selected generators.
 *         This parameter can be any combination of @ref RANDOM_Generators_TypeDef.
 * @param  NewState: @ref FunctionalState - a new state of the generators.
 * @return None.
 */
void RANDOM_SetGenerators(uint32_t RANDOM_Generators, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_RANDOM_GENERATORS(RANDOM_Generators));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_RANDOM->STAT_CTRL |= RANDOM_Generators;
    } else {
        MDR_RANDOM->STAT_CTRL &= ~RANDOM_Generators;
    }
}

/**
 * @brief  Get active generators.
 * @return A combined value of the active RANDOM generators (@ref RANDOM_Generators_TypeDef).
 */
uint32_t RANDOM_GetGenerators(void)
{
    return MDR_RANDOM->STAT_CTRL & RANDOM_STAT_CTRL_MASK_Msk;
}

/**
 * @brief  Get the number of remaining bits to gather a random number.
 * @return Remaining bits counter.
 */
uint8_t RANDOM_GetRemainingBits(void)
{
    return (uint8_t)((MDR_RANDOM->STAT_CTRL & RANDOM_STAT_CTRL_BIT_CNT_Msk) >> RANDOM_STAT_CTRL_BIT_CNT_Pos);
}

/**
 * @brief  Set a generators clock divider.
 * @param  RANDOM_Prescaler: Generators clock divider.
 * @note   CLK = PCLK / (2 * (RANDOM_Prescaler + 1)).
 * @return None.
 */
void RANDOM_SetPrescaler(uint16_t RANDOM_Prescaler)
{
    MDR_RANDOM->CLK_DIV = (uint32_t)RANDOM_Prescaler;
}

/**
 * @brief  Get a generators clock divider.
 * @return Generators clock divider.
 */
uint16_t RANDOM_GetPrescaler(void)
{
    return (uint16_t)(MDR_RANDOM->CLK_DIV);
}

/**
 * @brief  Set a gathering pause after generators enabled/disabled.
 * @param  RANDOM_HotStartPause: Gathering pause.
 * @return None.
 */
void RANDOM_SetPause(uint32_t RANDOM_HotStartPause)
{
    MDR_RANDOM->PAUSE = RANDOM_HotStartPause;
}

/**
 * @brief  Set a gathering pause after generators enabled/disabled.
 * @return Gathering pause.
 */
uint32_t RANDOM_GetPause(void)
{
    return MDR_RANDOM->PAUSE;
}

/**
 * @brief  Get a 32-bit random value.
 * @return Last gathered 32-bit random value.
 */
uint32_t RANDOM_GetData(void)
{
    return MDR_RANDOM->OUTPUT;
}

/**
 * @brief  Get the current random value while gathering.
 * @return The current random value while gathering.
 */
uint32_t RANDOM_GetTempData(void)
{
    return MDR_RANDOM->TEMP;
}

/**
 * @brief  Get the current value of the pause counter.
 * @return The current value of the pause counter.
 */
uint32_t RANDOM_GetCurrentPause(void)
{
    return MDR_RANDOM->PAUSE_CNT;
}

/**
 * @brief  Check whether a specified RANDOM status flag is set or not.
 * @param  RANDOM_Flag: @ref RANDOM_Flags_TypeDef - specify the flag to check.
 * @return @ref FlagStatus - a current state of the status flag (SET or RESET).
 */
FlagStatus RANDOM_GetFlagStatus(RANDOM_Flags_TypeDef RANDOM_Flag)
{
    FlagStatus Flag;

    /* Check the parameters. */
    assert_param(IS_RANDOM_FLAG(RANDOM_Flag));

    if ((MDR_RANDOM->STAT_CTRL & (uint32_t)RANDOM_Flag) != 0) {
        Flag = SET;
    } else {
        Flag = RESET;
    }

    return (Flag);
}

/**
 * @brief  Return a combined value of the RANDOM status flags.
 * @param  None.
 * @return A combined value of RANDOM status flags (@ref RANDOM_Flags_TypeDef).
 */
uint32_t RANDOM_GetStatus(void)
{
    return MDR_RANDOM->STAT_CTRL & (RANDOM_STAT_CTRL_EN_STATE |
                                    RANDOM_STAT_CTRL_BUSY | RANDOM_STAT_CTRL_UNREAD_DATA);
}

/**
 * @brief  Enable or disable the RANDOM interrupt.
 * @param  NewState: @ref FunctionalState - a new state of the RANDOM interrupt.
 * @return None.
 */
void RANDOM_ITConfig(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    MDR_RANDOM->INT_CTRL = (uint32_t)NewState;
}

/**
 * @brief  Check whether the RANDOM interrupts have occurred or not.
 * @return @ref ITStatus - A status of a currently active interrupt flag.
 */
ITStatus RANDOM_GetITStatus(void)
{
    if (MDR_RANDOM->INT_CTRL == (RANDOM_INT_CTRL_INT_EN | RANDOM_INT_CTRL_UNREAD_DATA)) {
        return SET;
    } else {
        return RESET;
    }
}

/** @} */ /* End of the group RANDOM_Exported_Functions */

/** @} */ /* End of the group RANDOM */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_random.c */

