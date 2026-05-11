/**
 *******************************************************************************
 * @file    MDR32VF0xI_clk_measure.c
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the CLK_MEASURE firmware functions.
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
#include "MDR32VF0xI_clk_measure.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup CLK_MEASURE CLK_MEASURE
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup CLK_MEASURE_Exported_Functions CLK_MEASURE Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the CLK_MEASURE peripheral registers to their default reset values.
 * @param  None.
 * @return None.
 */
void CLK_MEASURE_DeInit(void)
{
    MDR_CLK_MEASURE->CNTR_STAT       = 0x00000000;
    MDR_CLK_MEASURE->ALARM_SHIFT_RST = 0x00000000;
    MDR_CLK_MEASURE->ALARM_SHIFT_INT = 0x00000000;
    MDR_CLK_MEASURE->ALARM_PREG_0    = 0x00000000;
    MDR_CLK_MEASURE->ALARM_PREG_1    = 0x00000000;
}

/**
 * @brief  Initialize the CLK_MEASURE peripheral according to the specified
 *         parameters in the CLK_MEASURE_InitStruct.
 * @param  CLK_MEASURE_InitStruct: The pointer to the @ref CLK_MEASURE_InitTypeDef structure
 *         that contains the configuration information for the CLK_MEASURE peripheral.
 * @return None.
 */
void CLK_MEASURE_Init(const CLK_MEASURE_InitTypeDef* CLK_MEASURE_InitStruct)
{
    /* Check the parameters. */
    assert_param(IS_CLK_MEASURE_PREG(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG0));
    assert_param(IS_CLK_MEASURE_PREG(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG1));
    assert_param(IS_CLK_MEASURE_PREG(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG2));
    assert_param(IS_CLK_MEASURE_PREG(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG3));

    MDR_CLK_MEASURE->ALARM_SHIFT_RST = (uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT1_KEY_RESET) |
                                       ((uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT0_KEY_RESET) << CLK_MEASURE_ALARM_SHIFT_RST_BASE_REG2_Pos);
    MDR_CLK_MEASURE->ALARM_SHIFT_INT = (uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT1_INTERRUPT) |
                                       ((uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT0_INTERRUPT) << CLK_MEASURE_ALARM_SHIFT_INT_BASE_REG3_Pos);

    MDR_CLK_MEASURE->ALARM_PREG_0 = (uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG1) |
                                    ((uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG0) << CLK_MEASURE_ALARM_PREG_0_PREG0_Pos);
    MDR_CLK_MEASURE->ALARM_PREG_1 = (uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG3) |
                                    ((uint32_t)(CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG2) << CLK_MEASURE_ALARM_PREG_1_PREG2_Pos);
}

/**
 * @brief  Fill each CLK_MEASURE_InitStruct member with its default value.
 * @param  CLK_MEASURE_InitStruct: The pointer to the @ref CLK_MEASURE_InitTypeDef structure
 *         that is to be initialized.
 * @return None.
 */
void CLK_MEASURE_StructInit(CLK_MEASURE_InitTypeDef* CLK_MEASURE_InitStruct)
{
    CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT0_INTERRUPT = 0;
    CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT0_KEY_RESET = 0;
    CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT1_INTERRUPT = 0;
    CLK_MEASURE_InitStruct->CLK_MEASURE_MAX_SHIFT1_KEY_RESET = 0;
    CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG0       = 1;
    CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG1       = 1;
    CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG2       = 1;
    CLK_MEASURE_InitStruct->CLK_MEASURE_PRESCALER_REG3       = 1;
}

/**
 * @brief  Enable or disable CLK_MEASURE peripheral.
 * @param  NewState: @ref FunctionalState - a new state of the CLK_MEASURE peripheral.
 * @return None.
 */
void CLK_MEASURE_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_CLK_MEASURE->CNTR_STAT = CLK_MEASURE_CNTR_STAT_EN;
    } else {
        MDR_CLK_MEASURE->CNTR_STAT = 0x00000000;
    }
}

/**
 * @brief  Get the CLK_MEASURE peripheral work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the CLK_MEASURE peripheral.
 */
FunctionalState CLK_MEASURE_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_CLK_MEASURE->CNTR_STAT & CLK_MEASURE_CNTR_STAT_EN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Check whether a specified CLK_MEASURE status flag is set or not.
 * @param  CLK_MEASURE_Flag: @ref CLK_MEASURE_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - the current state of the status flag (SET or RESET).
 */
FlagStatus CLK_MEASURE_GetFlagStatus(CLK_MEASURE_Flags_TypeDef CLK_MEASURE_Flag)
{
    FlagStatus Flag;

    /* Check the parameters. */
    assert_param(IS_CLK_MEASURE_FLAG(CLK_MEASURE_Flag));

    if (MDR_CLK_MEASURE->CNTR_STAT & (uint32_t)CLK_MEASURE_Flag) {
        Flag = SET;
    } else {
        Flag = RESET;
    }

    return (Flag);
}

/**
 * @brief  Return a combined value of the CLK_MEASURE status flags.
 * @param  None.
 * @return A combined value of CLK_MEASURE status flags (@ref CLK_MEASURE_Flags_TypeDef).
 */
uint32_t CLK_MEASURE_GetStatus(void)
{
    return (MDR_CLK_MEASURE->CNTR_STAT & (CLK_MEASURE_CNTR_STAT_INTERRUPT | CLK_MEASURE_CNTR_STAT_KEY_RESET));
}

/**
 * @brief  Get the MAXSHIFT0 value.
 * @return MAXSHIFT0 value.
 */
uint16_t CLK_MEASURE_GetMAXSHIFT0(void)
{
    return (uint16_t)(MDR_CLK_MEASURE->STAT >> CLK_MEASURE_STAT_MAX_SHIFT0_Pos);
}

/**
 * @brief  Get the MAXSHIFT1 value.
 * @return MAXSHIFT1 value.
 */
uint16_t CLK_MEASURE_GetMAXSHIFT1(void)
{
    return (uint16_t)(MDR_CLK_MEASURE->STAT);
}

/** @} */ /* End of the group CLK_MEASURE_Exported_Functions */

/** @} */ /* End of the group CLK_MEASURE */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_clk_measure.c */

