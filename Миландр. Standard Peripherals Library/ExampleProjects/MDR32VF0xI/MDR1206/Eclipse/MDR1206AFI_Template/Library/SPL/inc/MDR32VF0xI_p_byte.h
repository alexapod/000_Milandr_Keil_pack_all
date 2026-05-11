/**
 *******************************************************************************
 * @file    MDR32VF0xI_p_byte.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the P_BYTE firmware functions.
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
#ifndef MDR32VF0xI_P_BYTE_H
#define MDR32VF0xI_P_BYTE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup P_BYTE P_BYTE
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup P_BYTE_Exported_Defines P_BYTE Exported Defines
 * @{
 */

#define IS_P_BYTE_BYTE_NUMBER(NUMBER) (((NUMBER) & ~((uint32_t)0x3F)) == 0)

/** @} */ /* End of the group P_BYTE_Exported_Defines */

/** @addtogroup P_BYTE_Exported_Functions P_BYTE Exported Functions
 * @{
 */

/**
 * @brief  Write data to the P_BYTE TRANSFORM_0 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform0(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_0 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_0 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform0(void)
{
    return MDR_P_BYTE->TRANSFORM_0;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_1 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform1(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_1 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_1 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform1(void)
{
    return MDR_P_BYTE->TRANSFORM_1;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_2 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform2(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_2 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_2 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform2(void)
{
    return MDR_P_BYTE->TRANSFORM_2;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_3 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform3(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_3 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_3 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform3(void)
{
    return MDR_P_BYTE->TRANSFORM_3;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_4 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform4(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_4 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_4 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform4(void)
{
    return MDR_P_BYTE->TRANSFORM_4;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_5 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform5(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_5 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_5 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform5(void)
{
    return MDR_P_BYTE->TRANSFORM_5;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_6 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform6(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_6 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_6 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform6(void)
{
    return MDR_P_BYTE->TRANSFORM_6;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_7 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform7(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_7 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_7 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform7(void)
{
    return MDR_P_BYTE->TRANSFORM_7;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_8 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform8(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_8 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_8 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform8(void)
{
    return MDR_P_BYTE->TRANSFORM_8;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_9 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform9(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_9 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_9 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform9(void)
{
    return MDR_P_BYTE->TRANSFORM_9;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_10 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform10(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_10 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_10 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform10(void)
{
    return MDR_P_BYTE->TRANSFORM_10;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_11 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform11(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_11 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_11 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform11(void)
{
    return MDR_P_BYTE->TRANSFORM_11;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_12 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform12(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_12 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_12 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform12(void)
{
    return MDR_P_BYTE->TRANSFORM_12;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_13 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform13(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_13 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_13 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform13(void)
{
    return MDR_P_BYTE->TRANSFORM_13;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_14 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform14(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_14 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_14 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform14(void)
{
    return MDR_P_BYTE->TRANSFORM_14;
}

/**
 * @brief  Write data to the P_BYTE TRANSFORM_15 register.
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void P_BYTE_WriteTransform15(uint32_t Data)
{
    MDR_P_BYTE->TRANSFORM_15 = Data;
}

/**
 * @brief  Read data from the P_BYTE TRANSFORM_15 register.
 * @return Read data.
 */
__STATIC_INLINE uint32_t P_BYTE_ReadTransform15(void)
{
    return MDR_P_BYTE->TRANSFORM_15;
}

/**
 * @brief  Set transposition IN_SEL -> OUT_SEL for a specified P_BYTE peripheral.
 * @param  InSel: Input byte number.
 * @param  OutSel: Output byte number (transposed).
 * @return None.
 */
__STATIC_INLINE void P_BYTE_SetTransposition(uint8_t InSel, uint8_t OutSel)
{
    /* Check the parameters. */
    assert_param(IS_P_BYTE_BYTE_NUMBER(InSel));
    assert_param(IS_P_BYTE_BYTE_NUMBER(OutSel));

    MDR_P_BYTE->MUX_SET = (uint32_t)InSel | ((uint32_t)OutSel << P_BYTE_MUX_SET_OUT_SEL_Pos);
}

/**
 * @brief  Get a transposition number for a specified input byte number for a specified P_BYTE peripheral.
 * @param  InputByteNumber: Input byte number.
 * @return A transposition byte number for an input byte number.
 */
__STATIC_INLINE uint8_t P_BYTE_GetPermutationNumber(uint8_t InputByteNumber)
{
    /* Check the parameters. */
    assert_param(IS_P_BYTE_BYTE_NUMBER(InputByteNumber));

    MDR_P_BYTE->MUX_VAL = ((uint32_t)InputByteNumber << P_BYTE_MUX_VAL_SEL_Pos);

    return (uint8_t)(MDR_P_BYTE->MUX_VAL & P_BYTE_MUX_VAL_VAL_Msk);
}

/** @} */ /* End of the group P_BYTE_Exported_Functions */

/** @} */ /* End of the group P_BYTE */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_P_BYTE_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_p_byte.h */

