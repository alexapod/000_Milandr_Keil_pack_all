/**
 *******************************************************************************
 * @file    MDR32F2xQI_eeprom.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
 * @brief   This file contains all the functions prototypes for the EEPROM
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
#ifndef __MDR32F2xQI_EEPROM_H
#define __MDR32F2xQI_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup EEPROM EEPROM
 * @{
 */

/** @defgroup EEPROM_Exported_Types EEPROM Exported Types
 * @{
 */

/**
 * @brief EEPROM Latency Cycles
 */
typedef enum {
    EEPROM_LATENCY_CYCLE_0 = EEPROM_CMD_DELAY_CYCLE_0, /*!< Selects 0 EEPROM latency cycle (MCU Clock up to 18 MHz) */
    EEPROM_LATENCY_CYCLE_1 = EEPROM_CMD_DELAY_CYCLE_1  /*!< Selects 1 EEPROM latency cycle (MCU Clock up to 36 MHz) */
} EEPROM_Latency_TypeDef;

#define IS_EEPROM_LATENCY(LATENCY) (((LATENCY) == EEPROM_LATENCY_CYCLE_0) || \
                                    ((LATENCY) == EEPROM_LATENCY_CYCLE_1))

/**
 * @brief EEPROM Memory Banks
 */
typedef enum {
    EEPROM_BANK_MAIN = ((uint32_t)0x00), /*!< Selects EEPROM Main Bank */
    EEPROM_BANK_INFO = ((uint32_t)0x01), /*!< Selects EEPROM Information Bank */
    EEPROM_BANK_ALL  = ((uint32_t)0x02)  /*!< Selects EEPROM Main and Information Banks (for EEPROM_EraseBlock()) */
} EEPROM_MemoryBank_TypeDef;

#define IS_EEPROM_MEMORY_BANK(BANK) (((BANK) == EEPROM_BANK_MAIN) || \
                                     ((BANK) == EEPROM_BANK_INFO))

#define IS_EEPROM_ERASE_BANK(BANK) (((BANK) == EEPROM_BANK_MAIN) || \
                                    ((BANK) == EEPROM_BANK_ALL))

/** @} */ /* End of group EEPROM_Exported_Types */

/** @addtogroup EEPROM_Exported_Functions EEPROM Exported Functions
 * @{
 */

/** @addtogroup EEPROM_Functions_allowed_to_be_located_in_Flash Functions allowed to be located in Flash
 * @{
 */

void                   EEPROM_SetLatency(EEPROM_Latency_TypeDef Latency);
EEPROM_Latency_TypeDef EEPROM_GetLatency(void);

/** @} */ /* End of group EEPROM_Functions_allowed_to_be_located_in_Flash */

/** @addtogroup EEPROM_Functions_not_allowed_to_be_located_in_Flash Functions not allowed to be located in Flash
 * @{
 */

__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC uint16_t EEPROM_ReadHalfWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC uint8_t  EEPROM_ReadByte(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

__RAMFUNC void EEPROM_ErasePage(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC void EEPROM_EraseBlock(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank, uint32_t Data) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC void EEPROM_ProgramHalfWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank, uint16_t Data) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC void EEPROM_ProgramByte(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank, uint8_t Data) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

__RAMFUNC void EEPROM_UpdateDCache(void) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/** @} */ /* End of group EEPROM_Functions_not_allowed_to_be_located_in_Flash */

/** @} */ /* End of group EEPROM_Exported_Functions */

/** @} */ /* End of group EEPROM */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_EEPROM_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_eeprom.h */

