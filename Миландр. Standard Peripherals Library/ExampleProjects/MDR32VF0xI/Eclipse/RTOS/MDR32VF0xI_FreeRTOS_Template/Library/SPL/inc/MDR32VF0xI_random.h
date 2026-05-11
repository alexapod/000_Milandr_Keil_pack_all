/**
 *******************************************************************************
 * @file    MDR32VF0xI_random.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    26/03/2024
 * @brief   This file contains all the functions prototypes for the RANDOM
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
#ifndef MDR32VF0xI_RANDOM_H
#define MDR32VF0xI_RANDOM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup RANDOM RANDOM
 * @{
 */

/** @defgroup RANDOM_Exported_Types RANDOM Exported Types
 * @{
 */

/**
 * @brief RANDOM numbers gathering mode.
 */
typedef enum {
    RANDOM_WORK_MODE_STOP          = RANDOM_STAT_CTRL_WORK_MODE_STOP,          /*!< Random number gathering is stopped. */
    RANDOM_WORK_MODE_SINGLE        = RANDOM_STAT_CTRL_WORK_MODE_SINGLE,        /*!< Single random word gathering. */
    RANDOM_WORK_MODE_START_ON_READ = RANDOM_STAT_CTRL_WORK_MODE_START_ON_READ, /*!< Gather a random number if there are no unread numbers. */
    RANDOM_WORK_MODE_CONTINUOUS    = RANDOM_STAT_CTRL_WORK_MODE_CONTINUOUS     /*!< A continuous gathering of random numbers. */
} RANDOM_WorkMode_TypeDef;

#define IS_RANDOM_WORK_MODE(MODE) (((MODE) == RANDOM_WORK_MODE_STOP) ||          \
                                   ((MODE) == RANDOM_WORK_MODE_SINGLE) ||        \
                                   ((MODE) == RANDOM_WORK_MODE_START_ON_READ) || \
                                   ((MODE) == RANDOM_WORK_MODE_CONTINUOUS))

/**
 * @brief RANDOM generators enumeration.
 */
typedef enum {
    RANDOM_GENERATOR_0 = RANDOM_STAT_CTRL_MASK_GEN0, /*!< Generator 0. */
    RANDOM_GENERATOR_1 = RANDOM_STAT_CTRL_MASK_GEN1, /*!< Generator 1. */
} RANDOM_Generators_TypeDef;

#define IS_RANDOM_GENERATOR(GEN) (((GEN) == RANDOM_GENERATOR_0) || \
                                  ((GEN) == RANDOM_GENERATOR_1))

#define IS_RANDOM_GENERATORS(GENS) (((GENS) & ~((uint32_t)(RANDOM_GENERATOR_0 | \
                                                           RANDOM_GENERATOR_1))) == 0)

/**
 * @brief RANDOM flags enumeration.
 */
typedef enum {
    RANDOM_FLAG_EN_STATE    = RANDOM_STAT_CTRL_EN_STATE,   /*!< Generators enabled flags. */
    RANDOM_FLAG_BUSY        = RANDOM_STAT_CTRL_BUSY,       /*!< Number gathering flag. */
    RANDOM_FLAG_UNREAD_DATA = RANDOM_STAT_CTRL_UNREAD_DATA /*!< Unread data flag. */
} RANDOM_Flags_TypeDef;

#define IS_RANDOM_FLAG(FLAG) (((FLAG) == RANDOM_FLAG_EN_STATE) || \
                              ((FLAG) == RANDOM_FLAG_BUSY) ||     \
                              ((FLAG) == RANDOM_FLAG_UNREAD_DATA))

#define IS_RANDOM_FLAGS(FLAGS) (((FLAGS) & ~((uint32_t)(RANDOM_FLAG_EN_STATE | \
                                                        RANDOM_FLAG_BUSY |     \
                                                        RANDOM_FLAG_UNREAD_DATA))) == 0)

/**
 * @brief RANDOM init struct definition.
 */
typedef struct {
    RANDOM_WorkMode_TypeDef RANDOM_WorkMode; /*!< Random numbers gathering mode.
                                                  This parameter can be a value of the @ref RANDOM_WorkMode_TypeDef. */
    uint16_t RANDOM_Generators;              /*!< Used random number generators.
                                                  This parameter can be any combination of the @ref RANDOM_Generators_TypeDef values. */
    uint16_t RANDOM_Prescaler;               /*!< Generators clock divider. Input clock is divided by [2 * (RANDOM_Prescaler + 1)]:
                                                  CLK = PCLK / (2 * (RANDOM_Prescaler + 1)). */
    uint32_t        RANDOM_HotStartPause;    /*!< Pause before number gathering after generators have been enabled/disabled. */
    FunctionalState RANDOM_InterruptEnable;  /*!< Enable or disable interrupt generation when (UNREAD_DATA == 1).
                                                  This parameter can be a value of the @ref FunctionalState. */
} RANDOM_InitTypeDef;

/** @} */ /* End of the group RANDOM_Exported_Types */

/** @defgroup RANDOM_Exported_Functions RANDOM Exported Functions
 * @{
 */

void RANDOM_DeInit(void);
void RANDOM_Init(const RANDOM_InitTypeDef* RANDOM_InitStruct);
void RANDOM_StructInit(RANDOM_InitTypeDef* RANDOM_InitStruct);

void                    RANDOM_SetWorkMode(RANDOM_WorkMode_TypeDef RANDOM_WorkMode);
RANDOM_WorkMode_TypeDef RANDOM_GetWorkMode(void);

void     RANDOM_SetGenerators(uint32_t RANDOM_Generators, FunctionalState NewState);
uint32_t RANDOM_GetGenerators(void);

uint8_t RANDOM_GetRemainingBits(void);

void     RANDOM_SetPrescaler(uint16_t RANDOM_Prescaler);
uint16_t RANDOM_GetPrescaler(void);

void     RANDOM_SetPause(uint32_t RANDOM_HotStartPause);
uint32_t RANDOM_GetPause(void);

uint32_t RANDOM_GetData(void);
uint32_t RANDOM_GetTempData(void);

uint32_t RANDOM_GetCurrentPause(void);

FlagStatus RANDOM_GetFlagStatus(RANDOM_Flags_TypeDef RANDOM_Flag);
uint32_t   RANDOM_GetStatus(void);

void     RANDOM_ITConfig(FunctionalState NewState);
ITStatus RANDOM_GetITStatus(void);

/** @} */ /* End of the group RANDOM_Exported_Functions */

/** @} */ /* End of the group RANDOM */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_RANDOM_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_random.h */

