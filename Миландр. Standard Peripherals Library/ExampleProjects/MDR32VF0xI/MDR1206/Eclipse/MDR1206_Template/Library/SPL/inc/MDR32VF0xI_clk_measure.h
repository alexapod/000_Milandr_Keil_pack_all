/**
 *******************************************************************************
 * @file    MDR32VF0xI_clk_measure.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the functions prototypes for the CLK_MEASURE
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
#ifndef MDR32VF0xI_CLK_MEASURE_H
#define MDR32VF0xI_CLK_MEASURE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup CLK_MEASURE CLK_MEASURE
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup CLK_MEASURE_Exported_Types CLK_MEASURE Exported Types
 * @{
 */

/**
 * @brief CLK_MEASURE status flags.
 */
typedef enum {
    CLK_MEASURE_FLAG_INTERRUPT = CLK_MEASURE_CNTR_STAT_INTERRUPT, /*!< CLK_MEASURE interrupt flag. */
    CLK_MEASURE_FLAG_RESET     = CLK_MEASURE_CNTR_STAT_KEY_RESET  /*!< CLK_MEASURE key reset flag. */
} CLK_MEASURE_Flags_TypeDef;

#define IS_CLK_MEASURE_FLAG(FLAG) (((FLAG) == CLK_MEASURE_FLAG_INTERRUPT) || \
                                   ((FLAG) == CLK_MEASURE_FLAG_RESET))

#define IS_CLK_MEASURE_FLAGS(FLAGS) (((FLAGS) & ~((uint32_t)(CLK_MEASURE_FLAG_INTERRUPT | \
                                                             CLK_MEASURE_FLAG_RESET)) == 0)

/**
 * @brief CLK_MEASURE init struct defintion.
 */
typedef struct {
    uint16_t CLK_MEASURE_MAX_SHIFT0_INTERRUPT; /*!< A value of the MAX_SHIFT0 that will cause an interrupt. */
    uint16_t CLK_MEASURE_MAX_SHIFT0_KEY_RESET; /*!< A value of the MAX_SHIFT0 that will cause a key reset. */
    uint16_t CLK_MEASURE_MAX_SHIFT1_INTERRUPT; /*!< A value of the MAX_SHIFT1 that will cause an interrupt. */
    uint16_t CLK_MEASURE_MAX_SHIFT1_KEY_RESET; /*!< A value of the MAX_SHIFT1 that will cause a key reset. */

    uint16_t CLK_MEASURE_PRESCALER_REG0; /*!< Counter 0 base. */
    uint16_t CLK_MEASURE_PRESCALER_REG1; /*!< Counter 1 base. */
    uint16_t CLK_MEASURE_PRESCALER_REG2; /*!< Counter 2 base. */
    uint16_t CLK_MEASURE_PRESCALER_REG3; /*!< Counter 3 base. */
} CLK_MEASURE_InitTypeDef;

/** @} */ /* End of the group CLK_MEASURE_Exported_Types */

/** @defgroup CLK_MEASURE_Exported_Defines CLK_MEASURE Exported Defines
 * @{
 */

#define IS_CLK_MEASURE_PREG(PREG) ((PREG) != 0)

/** @} */ /* End of the group CLK_MEASURE_Exported_Defines */

/** @defgroup CLK_MEASURE_Exported_Functions CLK_MEASURE Exported Functions
 * @{
 */

void CLK_MEASURE_DeInit(void);
void CLK_MEASURE_Init(const CLK_MEASURE_InitTypeDef* CLK_MEASURE_InitStruct);

void CLK_MEASURE_StructInit(CLK_MEASURE_InitTypeDef* CLK_MEASURE_InitStruct);

void            CLK_MEASURE_Cmd(FunctionalState NewState);
FunctionalState CLK_MEASURE_GetCmdState(void);

FlagStatus CLK_MEASURE_GetFlagStatus(CLK_MEASURE_Flags_TypeDef CLK_MEASURE_Flag);
uint32_t   CLK_MEASURE_GetStatus(void);

uint16_t CLK_MEASURE_GetMAXSHIFT0(void);
uint16_t CLK_MEASURE_GetMAXSHIFT1(void);

/** @} */ /* End of the group CLK_MEASURE_Exported_Functions */

/** @} */ /* End of the group CLK_MEASURE */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_CLK_MEASURE_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_clk_measure.h */

