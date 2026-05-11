/**
 *******************************************************************************
 * @file    MDR32VF0xI_l_block.c
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the L_BLOCK firmware functions.
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
#include "MDR32VF0xI_l_block.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup L_BLOCK L_BLOCK
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup L_BLOCK_Private_Defines L_BLOCK Private Defines
 * @{
 */

#define IS_L_BLOCK_R_COUNT(R) (((R) & ~(L_BLOCK_SETUP_SET_R_COUNT_Msk >> L_BLOCK_SETUP_SET_R_COUNT_Pos)) == 0)

/** @} */ /* End of the group L_BLOCK_Private_Defines */

/** @addtogroup L_BLOCK_Exported_Functions L_BLOCK Exported Functions
 * @{
 */

/**
 * @brief  Set L_BLOCK transform direction.
 * @param  Direction: @ref L_BLOCK_Direction_TypeDef - a transform direction.
 * @return None.
 */
void L_BLOCK_SetTransformDirection(L_BLOCK_Direction_TypeDef Direction)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_L_BLOCK_DIRECTION(Direction));

    TmpReg = MDR_L_BLOCK->SETUP & ~L_BLOCK_SETUP_SET_L_DIR;
    TmpReg |= (uint32_t)Direction;
    MDR_L_BLOCK->SETUP = TmpReg;
}

/**
 * @brief  Get a selected L_BLOCK transform direction.
 * @param  None.
 * @return @ref L_BLOCK_Direction_TypeDef - a selected transform direction.
 */
L_BLOCK_Direction_TypeDef L_BLOCK_GetTransformDirection(void)
{
    if (MDR_L_BLOCK->SETUP & L_BLOCK_SETUP_SET_L_DIR) {
        return L_BLOCK_TRANSFORM_DIRECTION_INVERSE;
    } else {
        return L_BLOCK_TRANSFORM_DIRECTION_DIRECT;
    }
}

/**
 * @brief  Get the current L_BLOCK transform direction.
 * @param  None.
 * @return @ref L_BLOCK_Direction_TypeDef - the current transform direction.
 */
L_BLOCK_Direction_TypeDef L_BLOCK_GetCurrentTransformDirection(void)
{
    if (MDR_L_BLOCK->SETUP & L_BLOCK_SETUP_CURR_L_DIR) {
        return L_BLOCK_TRANSFORM_DIRECTION_INVERSE;
    } else {
        return L_BLOCK_TRANSFORM_DIRECTION_DIRECT;
    }
}

/**
 * @brief  Set a number of L_BLOCK transform rounds.
 * @param  Rounds: A number of transform rounds.
 *         This parameter can be a value in the range [0; 0x1F].
 * @return None.
 */
void L_BLOCK_SetTransformRounds(uint8_t Rounds)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_L_BLOCK_R_COUNT(Rounds));

    TmpReg = MDR_L_BLOCK->SETUP & ~L_BLOCK_SETUP_SET_R_COUNT_Msk;
    TmpReg |= ((uint32_t)Rounds << L_BLOCK_SETUP_SET_R_COUNT_Pos);
    MDR_L_BLOCK->SETUP = TmpReg;
}

/**
 * @brief  Get a selected number of L_BLOCK rounds.
 * @param  None.
 * @return A selected rounds number.
 */
uint8_t L_BLOCK_GetTransformRounds(void)
{
    return (uint8_t)((MDR_L_BLOCK->SETUP & L_BLOCK_SETUP_SET_R_COUNT_Msk) >> L_BLOCK_SETUP_SET_R_COUNT_Pos);
}

/**
 * @brief  Get the current number of remaining L_BLOCK rounds.
 * @param  None.
 * @return A number of the remaining rounds.
 */
uint8_t L_BLOCK_GetCurrentTransformRounds(void)
{
    return (uint8_t)((MDR_L_BLOCK->SETUP & L_BLOCK_SETUP_CURR_R_COUNT_Msk) >> L_BLOCK_SETUP_CURR_R_COUNT_Pos);
}

/** @} */ /* End of the group L_BLOCK_Exported_Functions */

/** @} */ /* End of the group L_BLOCK */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_l_block.c */

