/**
 *******************************************************************************
 * @file    MDR32VF0xI_l_block.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the functions prototypes for the L_BLOCK
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
#ifndef MDR32VF0xI_L_BLOCK_H
#define MDR32VF0xI_L_BLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup L_BLOCK L_BLOCK
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup L_BLOCK_Exported_Types L_BLOCK Exported Types
 * @{
 */

/**
 * @brief L_BLOCK transform direction.
 */
typedef enum {
    L_BLOCK_TRANSFORM_DIRECTION_DIRECT  = ((uint32_t)0x0) << L_BLOCK_SETUP_SET_L_DIR_Pos, /*!< Direct transform direction. */
    L_BLOCK_TRANSFORM_DIRECTION_INVERSE = ((uint32_t)0x1) << L_BLOCK_SETUP_SET_L_DIR_Pos  /*!< Inverse transform direction. */
} L_BLOCK_Direction_TypeDef;

#define IS_L_BLOCK_DIRECTION(DIR) (((DIR) == L_BLOCK_TRANSFORM_DIRECTION_DIRECT) || \
                                   ((DIR) == L_BLOCK_TRANSFORM_DIRECTION_INVERSE))

/** @} */ /* End of the group L_BLOCK_Exported_Types */

/** @addtogroup L_BLOCK_Exported_Functions L_BLOCK Exported Functions
 * @{
 */

void                      L_BLOCK_SetTransformDirection(L_BLOCK_Direction_TypeDef Direction);
L_BLOCK_Direction_TypeDef L_BLOCK_GetTransformDirection(void);

L_BLOCK_Direction_TypeDef L_BLOCK_GetCurrentTransformDirection(void);

void    L_BLOCK_SetTransformRounds(uint8_t Rounds);
uint8_t L_BLOCK_GetTransformRounds(void);

uint8_t L_BLOCK_GetCurrentTransformRounds(void);

__STATIC_INLINE void     L_BLOCK_WriteTransform0(uint32_t Data) { MDR_L_BLOCK->TRANSFORM_0 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTransform0(void) { return MDR_L_BLOCK->TRANSFORM_0; }

__STATIC_INLINE void     L_BLOCK_WriteTransform1(uint32_t Data) { MDR_L_BLOCK->TRANSFORM_1 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTransform1(void) { return MDR_L_BLOCK->TRANSFORM_1; }

__STATIC_INLINE void     L_BLOCK_WriteTransform2(uint32_t Data) { MDR_L_BLOCK->TRANSFORM_2 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTransform2(void) { return MDR_L_BLOCK->TRANSFORM_2; }

__STATIC_INLINE void     L_BLOCK_WriteTransform3(uint32_t Data) { MDR_L_BLOCK->TRANSFORM_3 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTransform3(void) { return MDR_L_BLOCK->TRANSFORM_3; }

__STATIC_INLINE void     L_BLOCK_WriteTable0(uint32_t Data) { MDR_L_BLOCK->TABLE_CHANGE_0 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTable0(void) { return MDR_L_BLOCK->TABLE_CHANGE_0; }

__STATIC_INLINE void     L_BLOCK_WriteTable1(uint32_t Data) { MDR_L_BLOCK->TABLE_CHANGE_1 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTable1(void) { return MDR_L_BLOCK->TABLE_CHANGE_1; }

__STATIC_INLINE void     L_BLOCK_WriteTable2(uint32_t Data) { MDR_L_BLOCK->TABLE_CHANGE_2 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTable2(void) { return MDR_L_BLOCK->TABLE_CHANGE_2; }

__STATIC_INLINE void     L_BLOCK_WriteTable3(uint32_t Data) { MDR_L_BLOCK->TABLE_CHANGE_3 = Data; }
__STATIC_INLINE uint32_t L_BLOCK_ReadTable3(void) { return MDR_L_BLOCK->TABLE_CHANGE_3; }

/** @} */ /* End of the group L_BLOCK_Exported_Functions */

/** @} */ /* End of the group L_BLOCK */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_L_BLOCK_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_l_block.h */

