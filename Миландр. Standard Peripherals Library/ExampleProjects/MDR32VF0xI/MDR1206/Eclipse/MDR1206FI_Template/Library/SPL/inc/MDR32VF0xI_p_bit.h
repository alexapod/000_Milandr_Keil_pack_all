/**
 *******************************************************************************
 * @file    MDR32VF0xI_p_bit.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the P_BIT firmware functions.
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
#ifndef MDR32VF0xI_P_BIT_H
#define MDR32VF0xI_P_BIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup P_BIT P_BIT
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup P_BIT_Exported_Defines P_BIT Exported Defines
 * @{
 */

#define IS_P_BIT_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_P_BIT0) || \
                                     ((PERIPH) == MDR_P_BIT1) || \
                                     ((PERIPH) == MDR_P_BIT2) || \
                                     ((PERIPH) == MDR_P_BIT3))

#define IS_P_BIT_BIT_NUMBER(NUMBER) (((NUMBER) & ~((uint32_t)0x7F)) == 0)

/** @} */ /* End of the group P_BIT_Exported_Defines */

/** @defgroup P_BIT_Exported_Functions P_BIT Exported Functions
 * @{
 */

/**
 * @brief  Write data to the specified P_BIT TRANSFORM_0 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BIT_WriteTransform0(MDR_P_BIT_TypeDef* P_Bit, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    P_Bit->TRANSFORM_0 = Data;
}

/**
 * @brief  Read data from the specified P_BIT TRANSFORM_0 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BIT_ReadTransform0(MDR_P_BIT_TypeDef* P_Bit)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    return P_Bit->TRANSFORM_0;
}

/**
 * @brief  Write data to the specified P_BIT TRANSFORM_1 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BIT_WriteTransform1(MDR_P_BIT_TypeDef* P_Bit, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    P_Bit->TRANSFORM_1 = Data;
}

/**
 * @brief  Read data from the specified P_BIT TRANSFORM_1 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BIT_ReadTransform1(MDR_P_BIT_TypeDef* P_Bit)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    return P_Bit->TRANSFORM_1;
}

/**
 * @brief  Write data to the specified P_BIT TRANSFORM_2 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BIT_WriteTransform2(MDR_P_BIT_TypeDef* P_Bit, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    P_Bit->TRANSFORM_2 = Data;
}

/**
 * @brief  Read data from the specified P_BIT TRANSFORM_2 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BIT_ReadTransform2(MDR_P_BIT_TypeDef* P_Bit)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    return P_Bit->TRANSFORM_2;
}

/**
 * @brief  Write data to the specified P_BIT TRANSFORM_3 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BIT_WriteTransform3(MDR_P_BIT_TypeDef* P_Bit, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    P_Bit->TRANSFORM_3 = Data;
}

/**
 * @brief  Read data from the specified P_BIT TRANSFORM_3 register.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BIT_ReadTransform3(MDR_P_BIT_TypeDef* P_Bit)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));

    return P_Bit->TRANSFORM_3;
}

/**
 * @brief  Set transposition IN_SEL -> OUT_SEL for a specified P_BIT peripheral.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @param  InSel: Input bit number.
 * @param  OutSel: Output bit number (transposed).
 * @return None.
 */
__STATIC_INLINE void P_BIT_SetTransposition(MDR_P_BIT_TypeDef* P_Bit, uint8_t InSel, uint8_t OutSel)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));
    assert_param(IS_P_BIT_BIT_NUMBER(InSel));
    assert_param(IS_P_BIT_BIT_NUMBER(OutSel));

    P_Bit->MUX_SET = (uint32_t)InSel | ((uint32_t)OutSel << P_BIT_MUX_SET_OUT_SEL_Pos);
}

/**
 * @brief  Get a transposition number for a specified input bit number for a specified P_BIT peripheral.
 * @param  P_Bit: Select a P_BIT peripheral.
 *         This parameter can be one of the MDR_P_BITx values, where x is a number in the range [0; 3].
 * @param  InputBitNumber: Input bit number.
 * @return A transposition bit number for an input bit number.
 */
__STATIC_INLINE uint8_t P_BIT_GetPermutationNumber(MDR_P_BIT_TypeDef* P_Bit, uint8_t InputBitNumber)
{
    /* Check the parameters. */
    assert_param(IS_P_BIT_ALL_PERIPH(P_Bit));
    assert_param(IS_P_BIT_BIT_NUMBER(InputBitNumber));

    P_Bit->MUX_VAL = ((uint32_t)InputBitNumber << P_BIT_MUX_VAL_SEL_Pos);

    return (uint8_t)(P_Bit->MUX_VAL & P_BIT_MUX_VAL_VAL_Msk);
}

/** @} */ /* End of the group P_BIT_Exported_Functions */

/** @} */ /* End of the group P_BIT */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_P_BIT_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_p_bit.h */

