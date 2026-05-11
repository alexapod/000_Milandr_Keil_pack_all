/**
 *******************************************************************************
 * @file    MDR32VF0xI_flash.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    14/04/2025
 * @brief   This file contains all the functions prototypes for the FLASH
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
#ifndef MDR32VF0xI_FLASH_H
#define MDR32VF0xI_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup FLASH FLASH
 * @{
 */

/** @defgroup FLASH_Exported_Types FLASH Exported Types
 * @{
 */
#if defined(USE_MDR32F02) || defined(USE_MDR1206FI) || defined(USE_MDR1206)
/**
 * @brief FLASH latency cycles.
 */
typedef enum {
    FLASH_LATENCY_CYCLE_0 = FLASH_CMD_DELAY_CYCLE_0, /*!< Select 0 FLASH latency cycle (MCU clock up to: MDR32F02 - 30 MHz, MDR1206FI - 25 MHz). */
    FLASH_LATENCY_CYCLE_1 = FLASH_CMD_DELAY_CYCLE_1  /*!< Select 1 FLASH latency cycle (MCU clock up to: MDR32F02 - 60 MHz, MDR1206FI - 48 MHz). */
} FLASH_Latency_TypeDef;

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_LATENCY_CYCLE_0) || \
                                   ((LATENCY) == FLASH_LATENCY_CYCLE_1))
#endif

/**
 * @brief FLASH memory banks.
 */
typedef enum {
    FLASH_BANK_MAIN = ((uint32_t)0x00), /*!< Select the FLASH main bank. */
    FLASH_BANK_INFO = ((uint32_t)0x01)  /*!< Select the FLASH information bank. */
} FLASH_MemoryBank_TypeDef;

#define IS_FLASH_MEMORY_BANK(BANK) (((BANK) == FLASH_BANK_MAIN) || \
                                    ((BANK) == FLASH_BANK_INFO))

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief FLASH memory protection regions.
 */
typedef enum {
    FLASH_PROTECTION_REGION_0 = ((uint32_t)0x01), /*!< FLASH memory protection for region 0 (0x10000000-0x1000FFFF). */
    FLASH_PROTECTION_REGION_1 = ((uint32_t)0x02), /*!< FLASH memory protection for region 1 (0x10010000-0x1001FFFF). */
    FLASH_PROTECTION_REGION_2 = ((uint32_t)0x04), /*!< FLASH memory protection for region 2 (0x10020000-0x1002FFFF). */
    FLASH_PROTECTION_REGION_3 = ((uint32_t)0x08), /*!< FLASH memory protection for region 3 (0x10030000-0x1003FFFF). */
    FLASH_PROTECTION_REGION_4 = ((uint32_t)0x10), /*!< FLASH memory protection for region 4 (0x10040000-0x1004FFFF). */
    FLASH_PROTECTION_REGION_5 = ((uint32_t)0x20), /*!< FLASH memory protection for region 5 (0x10050000-0x1005FFFF). */
    FLASH_PROTECTION_REGION_6 = ((uint32_t)0x40), /*!< FLASH memory protection for region 6 (0x10060000-0x1006FFFF). */
    FLASH_PROTECTION_REGION_7 = ((uint32_t)0x80)  /*!< FLASH memory protection for region 7 (0x10070000-0x1007FFFF). */
} FLASH_ProtectionRegions_TypeDef;

#define IS_FLASH_PROTECTION_REGIONS(PRGS) (((PRGS) & ~(uint32_t)(FLASH_PROTECTION_REGION_0 | \
                                                                 FLASH_PROTECTION_REGION_1 | \
                                                                 FLASH_PROTECTION_REGION_2 | \
                                                                 FLASH_PROTECTION_REGION_3 | \
                                                                 FLASH_PROTECTION_REGION_4 | \
                                                                 FLASH_PROTECTION_REGION_5 | \
                                                                 FLASH_PROTECTION_REGION_6 | \
                                                                 FLASH_PROTECTION_REGION_7)) == 0)

/**
 * @brief FLASH factory data structure definition.
 */
typedef struct {
    uint32_t UniqueID[5];
    uint8_t  TrimHSI;
    uint8_t  TrimBG;
    uint8_t  TrimLDO;
    uint8_t  TrimTS;
} FLASH_FactoryData_TypeDef;
#endif

/** @} */ /* End of the group FLASH_Exported_Types */

/** @defgroup FLASH_Exported_Defines FLASH Exported Defines
 * @{
 */

/**
 * @brief FLASH parameters with a safe margin of ~7% (HSI spread).
 */
#if defined(USE_MDR32F02) || defined(USE_MDR1206FI) || defined(USE_MDR1206)
#define FLASH_TNVS_US   (5 + 1)
#define FLASH_TNVH_US   (5 + 1)
#define FLASH_TNVH1_US  (100 + 7)
#define FLASH_TPGS_US   (10 + 1)
#define FLASH_TRCV_US   (10 + 1)
#define FLASH_THV_US    (16000 + 0)

#define FLASH_TPROG_US  (20 + 10)
#define FLASH_TERASE_US (20000 + 10000)
#define FLASH_TME_US    (20000 + 10000)
#endif

#if defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define FLASH_TNVS_PROGRAM_US        (20 + 2)
#define FLASH_TRCV_PROGRAM_US        (50 + 4)
#define FLASH_TRW_PROGRAM_US         (1 + 0)
#define FLASH_TADH_PROGRAM_US        (1 + 0)
#define FLASH_TADS_PROGRAM_US        (1 + 0)
#define FLASH_TPGH_PROGRAM_US        (1 + 0)
#define FLASH_TPGS_PROGRAM_US        (50 + 4)
#define FLASH_TPROG_PROGRAM_US       (5 + 0)

#define FLASH_TNVS_SECTOR_ERASE_US   (20 + 2)
#define FLASH_TRCV_SECTOR_ERASE_US   (50 + 4)
#define FLASH_TRW_SECTOR_ERASE_US    (1 + 0)
#define FLASH_TERASE_SECTOR_ERASE_US (2000 + 500)

#define FLASH_TNVS_CHIP_ERASE_US     (80 + 6)
#define FLASH_TRCV_CHIP_ERASE_US     (200 + 14)
#define FLASH_TRW_CHIP_ERASE_US      (10 + 1)
#define FLASH_TERASE_CHIP_ERASE_US   (30000 + 5000)
#endif

/**
 * @brief FLASH address alignment.
 */
#define FLASH_ADDR_TWO_BYTE_ALIGN_MASK        ((uint32_t)0x1)
#define FLASH_ADDR_FOUR_BYTE_ALIGN_MASK       ((uint32_t)0x3)

#define IS_FLASH_ADDR_TWO_BYTE_ALIGNED(ADDR)  (((ADDR) & FLASH_ADDR_TWO_BYTE_ALIGN_MASK) == 0)
#define IS_FLASH_ADDR_FOUR_BYTE_ALIGNED(ADDR) (((ADDR) & FLASH_ADDR_FOUR_BYTE_ALIGN_MASK) == 0)

/** @} */ /* End of the group FLASH_Exported_Defines */

/** @addtogroup FLASH_Exported_Functions FLASH Exported Functions
 * @{
 */

/** @addtogroup FLASH_Exported_Functions_Allowed_to_Be_Located_in_FLASH Functions Allowed to Be Located in the FLASH
 * @{
 */

/** @addtogroup FLASH_Exported_Control_Functions_Allowed_to_Be_Located_in_FLASH FLASH Control Functions
 * @{
 */

void       FLASH_SetRegistersLock(FlagStatus LockState);
FlagStatus FLASH_GetRegistersLock(void);

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
uint8_t FLASH_GetChipID(void);
#endif

/** @} */ /* End of the group FLASH_Exported_Control_Functions_Allowed_to_Be_Located_in_FLASH */

/** @addtogroup FLASH_Exported_Special_Fields_Control_Functions_Allowed_to_Be_Located_in_FLASH FLASH Special Fields Control Functions
 * @{
 */

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void     FLASH_ProgramProtection(uint32_t ProtectionRegions);
uint32_t FLASH_ReadProtection(void);

void        FLASH_ProgramFactoryData(const FLASH_FactoryData_TypeDef* FactoryData);
ErrorStatus FLASH_ReadFactoryData(FLASH_FactoryData_TypeDef* FactoryData);
#endif

/** @} */ /* End of the group FLASH_Exported_Special_Fields_Control_Functions_Allowed_to_Be_Located_in_FLASH */

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/** @addtogroup FLASH_Exported_JTAG_Locking_Functions_Allowed_to_Be_Located_in_FLASH FLASH JTAG Locking Functions
 * @{
 */

void       FLASH_JTAG_SetRegistersLock(FlagStatus LockState);
FlagStatus FLASH_JTAG_GetRegistersLock(void);

void       FLASH_JTAG_SetLockForever(void);
FlagStatus FLASH_JTAG_GetLockStatus(void);

/** @} */ /* End of the group FLASH_Exported_JTAG_Locking_Functions_Allowed_to_Be_Located_in_FLASH */
#endif

/** @addtogroup FLASH_Exported_Register_Access_Functions_Allowed_to_Be_Located_in_FLASH FLASH Register Access Functions
 * @{
 */

uint32_t FLASH_GetPageAddress(uint32_t PageNumber, FLASH_MemoryBank_TypeDef Bank);

/** @} */ /* End of the group FLASH_Exported_Register_Access_Functions_Allowed_to_Be_Located_in_FLASH */

/** @} */ /* End of the group FLASH_Exported_Functions_Allowed_to_Be_Located_in_FLASH */

/** @addtogroup FLASH_Exported_Functions_Not_Allowed_to_Be_Located_in_FLASH Functions Not Allowed to Be Located in the FLASH
 * @{
 */

#if defined(USE_MDR32F02) || defined(USE_MDR1206FI) || defined(USE_MDR1206)
/** @addtogroup FLASH_Exported_Control_Functions_Not_Allowed_to_Be_Located_in_FLASH FLASH Control Functions
 * @{
 */

__RAM_TEXT_NOINLINE void                  FLASH_SetLatency(FLASH_Latency_TypeDef Latency);
__RAM_TEXT_NOINLINE FLASH_Latency_TypeDef FLASH_GetLatency(void);

/** @} */ /* End of the group FLASH_Exported_Control_Functions_Not_Allowed_to_Be_Located_in_FLASH */
#endif

/** @addtogroup FLASH_Exported_Register_Access_Functions_Not_Allowed_to_Be_Located_in_FLASH FLASH Register Access Functions
 * @{
 */

__RAM_TEXT_NOINLINE uint8_t  FLASH_ReadByte(uint32_t Address, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE uint16_t FLASH_ReadHalfWord(uint32_t Address, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE uint32_t FLASH_ReadWord(uint32_t Address, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void     FLASH_ReadWordBurst(uint32_t Address, uint32_t* PtrDataArray, uint32_t ArraySize, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void     FLASH_ReadWordArrayBurst(const uint32_t* PtrAddressArray, uint32_t* PtrDataArray, uint32_t ArraySize, FLASH_MemoryBank_TypeDef Bank);

__RAM_TEXT_NOINLINE void FLASH_ErasePage(uint32_t Address, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void FLASH_EraseAllPages(FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void FLASH_EraseAllBanks(void);

__RAM_TEXT_NOINLINE void FLASH_ProgramByte(uint32_t Address, uint8_t Data, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void FLASH_ProgramWord(uint32_t Address, uint32_t Data, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void FLASH_ProgramWordBurst(uint32_t Address, const uint32_t* PtrDataArray, uint32_t ArraySize, FLASH_MemoryBank_TypeDef Bank);
__RAM_TEXT_NOINLINE void FLASH_ProgramWordArrayBurst(const uint32_t* PtrAddressArray, const uint32_t* PtrDataArray, uint32_t ArraySize, FLASH_MemoryBank_TypeDef Bank);

/** @} */ /* End of the group FLASH_Exported_Register_Access_Functions_Not_Allowed_to_Be_Located_in_FLASH */

/** @} */ /* End of the group FLASH_Exported_Functions_Not_Allowed_to_Be_Located_in_FLASH */

/** @} */ /* End of the group FLASH_Exported_Functions */

/** @} */ /* End of the group FLASH */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_FLASH_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_flash.h */

