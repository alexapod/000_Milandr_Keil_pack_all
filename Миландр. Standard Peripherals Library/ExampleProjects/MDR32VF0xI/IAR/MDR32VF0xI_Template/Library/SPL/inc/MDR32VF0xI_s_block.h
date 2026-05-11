/**
 *******************************************************************************
 * @file    MDR32VF0xI_s_block.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the functions prototypes for the S_BLOCK
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
#ifndef MDR32VF0xI_S_BLOCK_H
#define MDR32VF0xI_S_BLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup S_BLOCK S_BLOCK
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @addtogroup S_BLOCK_Exported_Types S_BLOCK Exported Types
 * @{
 */

#define IS_S_BLOCK_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_S_BLOCK0) || \
                                       ((PERIPH) == MDR_S_BLOCK1) || \
                                       ((PERIPH) == MDR_S_BLOCK2) || \
                                       ((PERIPH) == MDR_S_BLOCK3) || \
                                       ((PERIPH) == MDR_S_BLOCK4) || \
                                       ((PERIPH) == MDR_S_BLOCK5) || \
                                       ((PERIPH) == MDR_S_BLOCK6) || \
                                       ((PERIPH) == MDR_S_BLOCK7))

/** @} */ /* End of the group S_BLOCK_Exported_Types */

/** @addtogroup S_BLOCK_Exported_Functions S_BLOCK Exported Functions
 * @{
 */

/**
 * @brief  Write the data to the specified S_BLOCK TRANSFORM_0 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform0(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_0 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_0 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform0(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_0;
}

/**
 * @brief  Write the data to the specified S_BLOCK TRANSFORM_1 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform1(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_1 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_1 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform1(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_1;
}

/**
 * @brief  Write the  data to the specified S_BLOCK TRANSFORM_2 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform2(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_2 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_2 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform2(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_2;
}

/**
 * @brief  Write the data to the specified S_BLOCK TRANSFORM_3 register.
 * @param  S_Block: Select an  S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform3(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_3 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_3 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform3(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_3;
}

/**
 * @brief  Write the data to the specified S_BLOCK TRANSFORM_4 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform4(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_4 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_4 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform4(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_4;
}

/**
 * @brief  Write the data to the specified S_BLOCK TRANSFORM_5 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform5(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_5 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_5 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform5(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_5;
}

/**
 * @brief  Write the data to the specified S_BLOCK TRANSFORM_6 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform6(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_6 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_6 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform6(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_6;
}

/**
 * @brief  Write the data to the specified S_BLOCK TRANSFORM_7 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTransform7(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TRANSFORM_7 = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TRANSFORM_7 register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTransform7(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TRANSFORM_7;
}

/**
 * @brief  Write the data to the specified S_BLOCK TABLE_CHANGE register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  Data: Input data.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_WriteTable(MDR_S_BLOCK_TypeDef* S_Block, uint32_t Data)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    S_Block->TABLE_CHANGE = Data;
}

/**
 * @brief  Read the data from the specified S_BLOCK TABLE_CHANGE register.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @return Read data.
 */
__STATIC_INLINE uint32_t S_BLOCK_ReadTable(MDR_S_BLOCK_TypeDef* S_Block)
{
    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    return S_Block->TABLE_CHANGE;
}

/**
 * @brief  Initialize the 8-bit substitution table of the specified S_BLOCK.
 * @param  S_Block: Select an S_BLOCK peripheral.
 *         This parameter can be one of the MDR_S_BLOCKx values, where x is a number in the range [0; 7].
 * @param  PtrTable: The pointer to the array with substitutions, where an index is treated as the input byte, a value - as the output byte.
 * @return None.
 */
__STATIC_INLINE void S_BLOCK_InitSubstitutionTable(MDR_S_BLOCK_TypeDef* S_Block, const uint8_t* PtrTable)
{
    uint32_t Index;

    /* Check the parameters. */
    assert_param(IS_S_BLOCK_ALL_PERIPH(S_Block));

    for (Index = 0; Index < 256; Index++) {
        S_Block->TRANSFORM_0 = ((uint8_t)Index << 24) |
                               ((uint8_t)Index << 16) |
                               ((uint8_t)Index << 8) |
                               ((uint8_t)Index << 0);
        S_Block->TABLE_CHANGE = (PtrTable[Index] << 24) |
                                (PtrTable[Index] << 16) |
                                (PtrTable[Index] << 8) |
                                (PtrTable[Index] << 0);
    }
}

/** @} */ /* End of the group S_BLOCK_Exported_Functions */

/** @} */ /* End of the group S_BLOCK */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_S_BLOCK_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_s_block.h */

