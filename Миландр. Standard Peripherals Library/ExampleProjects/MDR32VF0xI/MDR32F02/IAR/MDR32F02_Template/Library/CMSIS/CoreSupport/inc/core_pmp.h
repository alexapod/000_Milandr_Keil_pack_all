/**
 ******************************************************************************
 * @file    core_pmp.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    29/04/2025
 * @brief   RISC-V PMP Access Layer Header File.
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
#ifndef CORE_PMP
#define CORE_PMP

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "core_types.h"
#include "core_compiler.h"
#include "core_config.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(PMP_PRESENT)

/** @addtogroup CORE_PMP PMP
 * @{
 */

/** @defgroup CORE_PMP_Configuration PMP Configuration
 * @{
 */

#ifndef PMP_NUM_ENTRIES
#define PMP_NUM_ENTRIES 1
#warning "PMP_NUM_ENTRIES not defined in device header file; using default value: 1."
#endif

#ifndef PMP_GRANULARITY
#define PMP_GRANULARITY 2
#warning "PMP_GRANULARITY not defined in device header file; using default value: 2."
#endif

/** @} */ /* End of group CORE_PMP_Configuration */

/** @defgroup CORE_PMP_Exported_Defines PMP Exported Defines
 * @{
 */

#if (__riscv_xlen == 32)
#define PMP_NUM_ENTRIES_PER_CSR 4
#elif (__riscv_xlen == 64)
#define PMP_NUM_ENTRIES_PER_CSR 8
#endif

#define IS_PMP_ENTRY(ENTRY) ((ENTRY) <= (PMP_NUM_ENTRIES - 1))

/** @} */ /* End of group CORE_PMP_Exported_Defines */

/** @defgroup CORE_PMP_CSR PMP CSR
 * @{
 */

#define CSR_PMPCFG0 (0x3A0)

#if (__riscv_xlen == 32)
#define CSR_PMPCFG1 (0x3A1)
#endif /* __riscv_xlen == 32 */

#define CSR_PMPCFG2 (0x3A2)

#if (__riscv_xlen == 32)
#define CSR_PMPCFG3 (0x3A3)
#endif /* __riscv_xlen == 32 */

#define CSR_PMPADDR0  (0x3B0)
#define CSR_PMPADDR1  (0x3B1)
#define CSR_PMPADDR2  (0x3B2)
#define CSR_PMPADDR3  (0x3B3)
#define CSR_PMPADDR4  (0x3B4)
#define CSR_PMPADDR5  (0x3B5)
#define CSR_PMPADDR6  (0x3B6)
#define CSR_PMPADDR7  (0x3B7)
#define CSR_PMPADDR8  (0x3B8)
#define CSR_PMPADDR9  (0x3B9)
#define CSR_PMPADDR10 (0x3BA)
#define CSR_PMPADDR11 (0x3BB)
#define CSR_PMPADDR12 (0x3BC)
#define CSR_PMPADDR13 (0x3BD)
#define CSR_PMPADDR14 (0x3BE)
#define CSR_PMPADDR15 (0x3BF)

/** @defgroup CORE_PMP_CSR_PMPCFGx PMP CSR PMPCFGx
 * @{
 */

#define CSR_PMPCFGx_PMPx0CFG_Pos 0
#define CSR_PMPCFGx_PMPx0CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx0CFG_Pos)

#define CSR_PMPCFGx_PMPx1CFG_Pos 8
#define CSR_PMPCFGx_PMPx1CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx1CFG_Pos)

#define CSR_PMPCFGx_PMPx2CFG_Pos 16
#define CSR_PMPCFGx_PMPx2CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx2CFG_Pos)

#define CSR_PMPCFGx_PMPx3CFG_Pos 24
#define CSR_PMPCFGx_PMPx3CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx3CFG_Pos)

#if (__riscv_xlen == 64)
#define CSR_PMPCFGx_PMPx4CFG_Pos 32
#define CSR_PMPCFGx_PMPx4CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx4CFG_Pos)

#define CSR_PMPCFGx_PMPx5CFG_Pos 40
#define CSR_PMPCFGx_PMPx5CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx5CFG_Pos)

#define CSR_PMPCFGx_PMPx6CFG_Pos 48
#define CSR_PMPCFGx_PMPx6CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx6CFG_Pos)

#define CSR_PMPCFGx_PMPx7CFG_Pos 56
#define CSR_PMPCFGx_PMPx7CFG_Msk (0xFFUL << CSR_PMPCFGx_PMPx7CFG_Pos)
#endif

/** @} */ /* End of group CORE_PMP_CSR_PMPCFGx */

/** @defgroup CORE_PMP_CSR_PMPxCFG PMP CSR PMPxCFG
 * @{
 */

#define CSR_PMPxCFG_R_Pos    0
#define CSR_PMPxCFG_R_Msk    (0x1UL << CSR_PMPxCFG_R_Pos)
#define CSR_PMPxCFG_R        CSR_PMPxCFG_R_Msk

#define CSR_PMPxCFG_W_Pos    1
#define CSR_PMPxCFG_W_Msk    (0x1UL << CSR_PMPxCFG_W_Pos)
#define CSR_PMPxCFG_W        CSR_PMPxCFG_W_Msk

#define CSR_PMPxCFG_X_Pos    2
#define CSR_PMPxCFG_X_Msk    (0x1UL << CSR_PMPxCFG_X_Pos)
#define CSR_PMPxCFG_X        CSR_PMPxCFG_X_Msk

#define CSR_PMPxCFG_A_Pos    3
#define CSR_PMPxCFG_A_Msk    (0x3UL << CSR_PMPxCFG_A_Pos)
#define CSR_PMPxCFG_A_OFF    (0x0UL << CSR_PMPxCFG_A_Pos)
#define CSR_PMPxCFG_A_TOR    (0x1UL << CSR_PMPxCFG_A_Pos)
#define CSR_PMPxCFG_A_NA4    (0x2UL << CSR_PMPxCFG_A_Pos)
#define CSR_PMPxCFG_A_NAPOT  (0x3UL << CSR_PMPxCFG_A_Pos)

#define CSR_PMPxCFG_L_Pos    7
#define CSR_PMPxCFG_L_Msk    (0x1UL << CSR_PMPxCFG_L_Pos)
#define CSR_PMPxCFG_L        CSR_PMPxCFG_L_Msk
#define CSR_PMPxCFG_L_UNLOCK (0x0UL << CSR_PMPxCFG_L_Pos)
#define CSR_PMPxCFG_L_LOCK   (0x1UL << CSR_PMPxCFG_L_Pos)

/** @} */ /* End of group CORE_PMP_CSR_PMPxCFG */

/** @defgroup CORE_PMP_CSR_PMPADDRx PMP CSR PMPADDRx
 * @{
 */

#if (__riscv_xlen == 32)
#define CSR_PMPADDRx_ADDRESS_Pos 0
#define CSR_PMPADDRx_ADDRESS_Msk (0xFFFFFFFFUL << CSR_PMPADDRx_ADDRESS_Pos)
#elif (__riscv_xlen == 64)
#define CSR_PMPADDRx_ADDRESS_Pos 0
#define CSR_PMPADDRx_ADDRESS_Msk (0x3FFFFFFFFFFFFFULL << CSR_PMPADDRx_ADDRESS_Pos)
#endif

/** @} */ /* End of group CORE_PMP_CSR_PMPxCFG */

/** @} */ /* End of group CORE_PMP_CSR */

/** @addtogroup CORE_PMP_Hardware_Abstraction_Layer PMP Hardware Abstraction Layer
 * @{
 */

/** @defgroup CORE_PMP_Exported_Types PMP Exported Types
 * @{
 */

/**
 * @brief PMP entry mode.
 */
typedef enum {
    PMP_MODE_OFF,              /*!< PMP entry is disabled and matches no addresses. */
    PMP_MODE_TOP_OF_RANGE,     /*!< Select a top-of-range entry mode: top of range - current PMP address register, base of range - previous PMP address register. */
    PMP_MODE_NATURALLY_ALIGNED /*!< Select a naturally-aligned entry mode: four-byte entry (NA4) or power-of-two entry (NAPOT). */
} PMP_Mode_TypeDef;

#define IS_PMP_MODE(MODE) (((MODE) == PMP_MODE_OFF) ||          \
                           ((MODE) == PMP_MODE_TOP_OF_RANGE) || \
                           ((MODE) == PMP_MODE_NATURALLY_ALIGNED))

/**
 * @brief PMP access permissions.
 */
typedef enum {
    PMP_ACCESS_DISABLE,                                                           /*!< Read, write and execute access is disabled. */
    PMP_ACCESS_READ               = CSR_PMPxCFG_R,                                /*!< Read access is enabled. */
    PMP_ACCESS_EXECUTE            = CSR_PMPxCFG_X,                                /*!< Execute access is enabled. */
    PMP_ACCESS_READ_WRITE         = CSR_PMPxCFG_R | CSR_PMPxCFG_W,                /*!< Read and write access is enabled. */
    PMP_ACCESS_READ_EXECUTE       = CSR_PMPxCFG_R | CSR_PMPxCFG_X,                /*!< Read and execute access is enabled. */
    PMP_ACCESS_READ_WRITE_EXECUTE = CSR_PMPxCFG_R | CSR_PMPxCFG_W | CSR_PMPxCFG_X /*!< Read, write and execute access is enabled. */
} PMP_Access_TypeDef;

#define IS_PMP_ACCESS(ACCESS) (((ACCESS) == PMP_ACCESS_DISABLE) ||      \
                               ((ACCESS) == PMP_ACCESS_READ) ||         \
                               ((ACCESS) == PMP_ACCESS_EXECUTE) ||      \
                               ((ACCESS) == PMP_ACCESS_READ_WRITE) ||   \
                               ((ACCESS) == PMP_ACCESS_READ_EXECUTE) || \
                               ((ACCESS) == PMP_ACCESS_READ_WRITE_EXECUTE))

/**
 * @brief PMP entry init structure definition.
 */
typedef struct {
    PMP_Mode_TypeDef PMP_Mode;     /*!< PMP entry mode.
                                        This parameter can be a value of @ref PMP_Mode_TypeDef. */
    uint_xlen_t PMP_Address;       /*!< Base address of the PMP entry.
                                        The available values for this parameter depend on PMP_Mode:
                                            - PMP_MODE_OFF: PMP_Address can be any value (writes to the PMPADDRx register with left shift of 2);
                                            - PMP_MODE_TOP_OF_RANGE:
                                                - Entry == 0: PMP_Address must be 0;
                                                - Entry != 0: PMP_Address can be any value aligned to 2^PMP_GRANULARITY;
                                            - PMP_MODE_NATURALLY_ALIGNED: PMP_Address can be any value aligned to PMP_Size, but not less than 2^PMP_GRANULARITY. */
    uint_xlen_t PMP_Size;          /*!< Size of the PMP entry in bytes.
                                        The available values for this parameter depend on PMP_Mode:
                                            - PMP_MODE_OFF: PMP_Size can be any value (not used);
                                            - PMP_MODE_TOP_OF_RANGE: PMP_Size can be any value that is a multiple of 2^PMP_GRANULARITY;
                                            - PMP_MODE_NATURALLY_ALIGNED: PMP_Size can be any value 2^N, where N=[PMP_GRANULARITY;31] for RV32 and N=[PMP_GRANULARITY;54] for RV64. */
    PMP_Access_TypeDef PMP_Access; /*!< Read, write and execute access permissions for the PMP entry.
                                        This parameter can be a value of @ref PMP_Access_TypeDef. */
    FunctionalState PMP_Lock;      /*!< Enable or not enable the PMP entry locking.
                                        This parameter can be a value of @ref FunctionalState.
                                        Warning: after locking the specified PMP entry remains locked until reset. */
} PMP_Entry_InitTypeDef;

/** @} */ /* End of group CORE_PMP_Exported_Types */

/** @addtogroup CORE_PMP_Exported_Functions PMP Exported Functions
 * @{
 */

ErrorStatus PMP_DeInit(void);

ErrorStatus PMP_EntryInit(uint32_t Entry, const PMP_Entry_InitTypeDef* PMP_EntryInitStruct);
void        PMP_EntryGetConfig(uint32_t Entry, PMP_Entry_InitTypeDef* PMP_EntryInitStruct);

void PMP_EntryStructInit(PMP_Entry_InitTypeDef* PMP_EntryInitStruct);

ErrorStatus PMP_SetModeRange(uint32_t Entry, PMP_Mode_TypeDef Mode, uint_xlen_t Address, uint_xlen_t Size);
void        PMP_GetModeRange(uint32_t Entry, PMP_Mode_TypeDef* Mode, uint_xlen_t* Address, uint_xlen_t* Size);

ErrorStatus        PMP_SetAccess(uint32_t Entry, PMP_Access_TypeDef Access);
PMP_Access_TypeDef PMP_GetAccess(uint32_t Entry);

void            PMP_SetLock(uint32_t Entry);
FunctionalState PMP_GetLock(uint32_t Entry);

/** @} */ /* End of the group CORE_PMP_Exported_Functions */

/** @} */ /* End of group CORE_PMP_Hardware_Abstraction_Layer */

/** @} */ /* End of the group CORE_PMP */

#endif /* PMP_PRESENT */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_PMP */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_pmp.h */

