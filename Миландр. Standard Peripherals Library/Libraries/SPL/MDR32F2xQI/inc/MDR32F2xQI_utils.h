/**
 ******************************************************************************
 * @file    MDR32F2xQI_utils.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
 * @brief   This file contains all prototypes of the firmware library
 *          utility functions.
 ******************************************************************************
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
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32F2xQI_UTILS_H
#define __MDR32F2xQI_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup UTILS UTILS
 * @{
 */

/** @defgroup UTILS_Exported_Types UTILS Exported Types
 * @{
 */

/** @defgroup UTILS_LOW_POWER_Exported_Types UTILS LOW POWER
 * @{
 */

/**
 * @brief LOW POWER Sleep Mode
 */
typedef enum {
    LOW_POWER_MODE_SLEEP     = ((uint32_t)0x00), /*!< Sleep mode */
    LOW_POWER_MODE_SLEEPDEEP = ((uint32_t)0x01)  /*!< Deep sleep mode */
} LOW_POWER_Mode_TypeDef;

#define IS_LOW_POWER_MODE(MODE) (((MODE) == LOW_POWER_MODE_SLEEP) || \
                                 ((MODE) == LOW_POWER_MODE_SLEEPDEEP))

/**
 * @brief LOW POWER Entering sleep mode
 */
typedef enum {
    LOW_POWER_MODE_ENTRY_WFE = ((uint32_t)0x00), /*!< Enter sleep mode with WFE instruction */
    LOW_POWER_MODE_ENTRY_WFI = ((uint32_t)0x01)  /*!< Enter sleep mode with WFI instruction */
} LOW_POWER_Mode_Entry_TypeDef;

#define IS_LOW_POWER_MODE_ENTRY(MODE) (((MODE) == LOW_POWER_MODE_ENTRY_WFE) || \
                                       ((MODE) == LOW_POWER_MODE_ENTRY_WFI))

/** @} */ /* End of group UTILS_LOW_POWER_Exported_Types */

/** @defgroup UTILS_DELAY_Exported_Types UTILS DELAY
 * @{
 */

/**
 * @brief DELAY Mode
 */
typedef enum {
    DELAY_MODE_PROGRAM = ((uint32_t)0x0), /*!< Selects the delay module mode based on the program cycle. */
    DELAY_MODE_SYSTICK = ((uint32_t)0x1)  /*!< Selects the delay module mode based on the System Tick Timer (SysTick). */
} DELAY_Mode_TypeDef;

#define IS_DELAY_MODE(MODE) (((MODE) == DELAY_MODE_PROGRAM) || \
                             ((MODE) == DELAY_MODE_SYSTICK))

/** @} */ /* End of group UTILS_DELAY_Exported_Types */

/** @} */ /* End of group UTILS_Exported_Types */

/** @defgroup UTILS_Exported_Defines UTILS Exported Defines
 * @{
 */

/** @defgroup UTILS_DELAY_Exported_Defines UTILS DELAY
 * @{
 */

/** @defgroup UTILS_DELAY_Program_Mode_Defines UTILS DELAY Program Mode Defines
 * @{
 */

#define DELAY_PROGRAM_LOOP_CYCLES            (4UL)

#define DELAY_PROGRAM_GET_CONST_US(CLK)      (((CLK) / DELAY_PROGRAM_LOOP_CYCLES) / ((1000000UL / 1024UL) + 1UL))
#define DELAY_PROGRAM_GET_CONST_MS(CLK)      (((CLK) / DELAY_PROGRAM_LOOP_CYCLES) / 1000UL)

#define DELAY_PROGRAM_GET_US_LOOPS(N, CONST) (((N) * (CONST)) / 1024UL)
#define DELAY_PROGRAM_GET_MS_LOOPS(N, CONST) ((N) * (CONST))

/** @} */ /* End of group UTILS_DELAY_Program_Mode_Defines */

/** @defgroup UTILS_DELAY_SysTick_Mode_Defines UTILS DELAY SysTick Mode Defines
 * @{
 */

#define DELAY_SYSTICK_GET_CONST_US(CLK)   ((CLK) / 1000000UL)
#define DELAY_SYSTICK_GET_CONST_MS(CLK)   ((CLK) / 1000UL)

#define DELAY_SYSTICK_GET_TICKS(N, CONST) (((N) * (CONST)))

/** @} */ /* End of group UTILS_DELAY_SysTick_Mode_Defines */

/** @} */ /* End of group UTILS_DELAY_Exported_Defines */

/** @} */ /* End of group UTILS_Exported_Defines */

/** @addtogroup UTILS_Exported_Functions UTILS Exported Functions
 * @{
 */

/** @addtogroup UTILS_LOW_POWER_Exported_Functions UTILS LOW POWER
 * @{
 */

void LOW_POWER_EnterSLEEPMode(LOW_POWER_Mode_TypeDef SleepMode, LOW_POWER_Mode_Entry_TypeDef EntryMode);
void LOW_POWER_SleepOnExit(FunctionalState NewState);
void LOW_POWER_SEVOnPend(FunctionalState NewState);

/** @} */ /* End of group UTILS_LOW_POWER_Exported_Functions */

/** @addtogroup UTILS_DELAY_Exported_Functions UTILS DELAY
 * @{
 */

void DELAY_Init(DELAY_Mode_TypeDef Mode);
void DELAY_WaitUs(uint32_t Us);
void DELAY_WaitMs(uint32_t Ms);

__RAMFUNC void DELAY_PROGRAM_WaitLoopsAsm(uint32_t Loops) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/** @} */ /* End of group UTILS_DELAY_Exported_Functions */

/** @addtogroup UTILS_STDIO_Exported_Functions UTILS STDIO
 * @{
 */

#if (USE_STDIO_RETARGET != 0)
ErrorStatus STDIO_Init(void);
#endif

/** @} */ /* End of group UTILS_STDIO_Exported_Functions */

/** @} */ /* End of group UTILS_Exported_Functions */

/** @} */ /* End of group UTILS */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_UTILS_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_utils.h */

