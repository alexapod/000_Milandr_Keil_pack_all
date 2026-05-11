/**
 ******************************************************************************
 * @file    MDR32VF0xI_utils.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    30/04/2025
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
#ifndef MDR32VF0xI_UTILS_H
#define MDR32VF0xI_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"
#include "MDR32VF0xI_rst_clk.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup UTILS UTILS
 * @{
 */

/** @defgroup UTILS_Exported_Types UTILS Exported Types
 * @{
 */

/**
 * @brief Delay mode.
 */
typedef enum {
    DELAY_MODE_PROGRAM       = ((uint32_t)0x0), /*!< Select the delay module mode based on the program cycle. */
    DELAY_MODE_MACHINE_TIMER = ((uint32_t)0x1), /*!< Select the delay module mode based on the RISC-V machine timer. */
    DELAY_MODE_CYCLE_COUNTER = ((uint32_t)0x2)  /*!< Select the delay module mode based on the RISC-V cycle counter. */
} DELAY_Mode_TypeDef;

#define IS_DELAY_MODE(MODE) (((MODE) == DELAY_MODE_PROGRAM) ||       \
                             ((MODE) == DELAY_MODE_MACHINE_TIMER) || \
                             ((MODE) == DELAY_MODE_CYCLE_COUNTER))

/** @} */ /* End of the group UTILS_Exported_Types */

/** @defgroup UTILS_Exported_Defines UTILS Exported Defines
 * @{
 */

/**
 * @brief Program delay constansts (CLK max = 64 MHz).
 */
#define DELAY_PROGRAM_LOOP_CYCLES       ((uint32_t)2)

#define DELAY_PROGRAM_GET_CONST_US(CLK) (((CLK) / DELAY_PROGRAM_LOOP_CYCLES) * (uint32_t)67 + rv_mulhu(((CLK) / DELAY_PROGRAM_LOOP_CYCLES), (uint32_t)467567319))
#define DELAY_PROGRAM_GET_CONST_MS(CLK) (((CLK) / DELAY_PROGRAM_LOOP_CYCLES) * (uint32_t)65 + rv_mulhu(((CLK) / DELAY_PROGRAM_LOOP_CYCLES), (uint32_t)2302102471))

/**
 * @brief Machine timer delay constants (CLK max = 64 MHz).
 */
#define DELAY_MACHINE_TIMER_GET_CONST_US(CLK) ((CLK) * (uint32_t)67 + rv_mulhu((CLK), (uint32_t)467567319))
#define DELAY_MACHINE_TIMER_GET_CONST_MS(CLK) ((CLK) * (uint32_t)65 + rv_mulhu((CLK), (uint32_t)2302102471))

/**
 * @brief Cycle counter delay constants (CLK max = 64 MHz).
 */
#define DELAY_CYCLE_COUNTER_GET_CONST_US(CLK) ((CLK) * (uint32_t)67 + rv_mulhu((CLK), (uint32_t)467567319))
#define DELAY_CYCLE_COUNTER_GET_CONST_MS(CLK) ((CLK) * (uint32_t)65 + rv_mulhu((CLK), (uint32_t)2302102471))

/**
 * @brief Delay ticks.
 */
#define DELAY_GET_TICKS_US(N, CONST) (rv_mulhu((N) << 6, (CONST)))
#define DELAY_GET_TICKS_MS(N, CONST) (rv_mulhu((N) << 14, (CONST)) << 2)

/** @} */ /* End of the group UTILS_Exported_Defines */

/** @addtogroup UTILS_Exported_Functions UTILS Exported Functions
 * @{
 */

ErrorStatus DELAY_Init(DELAY_Mode_TypeDef Mode);
void        DELAY_WaitUs(uint32_t Us);
void        DELAY_WaitMs(uint32_t Ms);

__RAM_TEXT_NOINLINE void DELAY_PROGRAM_WaitLoopsAsm(uint32_t Loops);
__RAM_TEXT_NOINLINE void DELAY_CycleCounter_WaitTicksAsm(uint32_t Ticks);

ErrorStatus FactoryDataTrimInit(void);

#if defined(USE_MDR1206FI)
#define GetChipID() ((uint8_t)CHIP_ID_MDR1206FI)
#elif defined(USE_MDR1206AFI)
#define GetChipID() ((uint8_t)CHIP_ID_MDR1206AFI)
#elif defined(USE_MDR1206)
uint8_t GetChipID(void);
#endif

__NO_RETURN void WWDG_SystemReset(RST_CLK_WWDG_C2_ClockSource_TypeDef WWDG_C2_Source);

/** @} */ /* End of the group UTILS_Exported_Functions */

/** @} */ /* End of the group UTILS */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_UTILS_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_utils.h */

