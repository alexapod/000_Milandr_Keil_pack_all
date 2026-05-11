/**
 ******************************************************************************
 * @file    core_extension_zicntr.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   RISC-V Zicntr Extension Access Layer Header File.
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
#ifndef CORE_EXT_ZICNTR
#define CORE_EXT_ZICNTR

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "core_config.h"
#include "core_types.h"
#include "core_compiler.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(CORE_EXTENSION_ZICNTR)

/** @addtogroup CORE_EXTENSION_ZICNTR Core Zicntr Extension
 * @{
 */

/** @defgroup CORE_EXTENSION_ZICNTR_Exported_Defines Core Zicntr Extension Exported Defines
 * @{
 */

/** @defgroup CORE_EXTENSION_ZICNTR_CSR Zicntr Extension CSR
 * @{
 */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)

#if defined(CORE_PRIVILEGE_LEVEL) && (((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0) || ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0))

/* Machine Trap Setup */
#define CSR_MCOUNTEREN (0x306)

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR || CORE_PRIVILEGE_MODE_USER */

/* Machine Counter Setup */
#define CSR_MCOUNTINHIBIT (0x320)

/* Machine Counter/Timers */
#define CSR_MCYCLE   (0xB00)
#define CSR_MINSTRET (0xB02)

#if (__riscv_xlen == 32)

#define CSR_MCYCLEH   (0xB80)
#define CSR_MINSTRETH (0xB82)

#endif /* __riscv_xlen == 32 */

#endif /* CORE_PRIVILEGE_MODE_MACHINE */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)

/* Supervisor Trap Setup */
#define CSR_SCOUNTEREN (0x106)

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

#if defined(CORE_PRIVILEGE_LEVEL) && (((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0) || ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0) || ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0))

/* Unprivileged Counter/Timers */
#define CSR_CYCLE   (0xC00)
#define CSR_TIME    (0xC01)
#define CSR_INSTRET (0xC02)

#if (__riscv_xlen == 32)

#define CSR_CYCLEH   (0xC80)
#define CSR_TIMEH    (0xC81)
#define CSR_INSTRETH (0xC82)

#endif /* __riscv_xlen == 32 */

#endif /* CORE_PRIVILEGE_MODE_MACHINE || CORE_PRIVILEGE_MODE_SUPERVISOR || CORE_PRIVILEGE_MODE_USER */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)

#if defined(CORE_PRIVILEGE_LEVEL) && (((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0) || ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0))

/** @defgroup CORE_EXTENSION_ZICNTR_CSR_MCOUNTEREN CSR MCOUNTEREN
 * @{
 */

#define CSR_MCOUNTEREN_CY_Pos 0
#define CSR_MCOUNTEREN_CY_Msk (0x1UL << CSR_MCOUNTEREN_CY_Pos)
#define CSR_MCOUNTEREN_CY     CSR_MCOUNTEREN_CY_Msk

#define CSR_MCOUNTEREN_TM_Pos 1
#define CSR_MCOUNTEREN_TM_Msk (0x1UL << CSR_MCOUNTEREN_TM_Pos)
#define CSR_MCOUNTEREN_TM     CSR_MCOUNTEREN_TM_Msk

#define CSR_MCOUNTEREN_IR_Pos 2
#define CSR_MCOUNTEREN_IR_Msk (0x1UL << CSR_MCOUNTEREN_IR_Pos)
#define CSR_MCOUNTEREN_IR     CSR_MCOUNTEREN_IR_Msk

/** @} */ /* End of group CORE_EXTENSION_ZICNTR_CSR_MCOUNTEREN */

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR || CORE_PRIVILEGE_MODE_USER */

/** @defgroup CORE_EXTENSION_ZICNTR_CSR_MCOUNTINHIBIT CSR MCOUNTINHIBIT
 * @{
 */

#define CSR_MCOUNTINHIBIT_CY_Pos 0
#define CSR_MCOUNTINHIBIT_CY_Msk (0x1UL << CSR_MCOUNTINHIBIT_CY_Pos)
#define CSR_MCOUNTINHIBIT_CY     CSR_MCOUNTINHIBIT_CY_Msk

#define CSR_MCOUNTINHIBIT_IR_Pos 2
#define CSR_MCOUNTINHIBIT_IR_Msk (0x1UL << CSR_MCOUNTINHIBIT_IR_Pos)
#define CSR_MCOUNTINHIBIT_IR     CSR_MCOUNTINHIBIT_IR_Msk

/** @} */ /* End of group CORE_EXTENSION_ZICNTR_CSR_MCOUNTINHIBIT */

#endif /* CORE_PRIVILEGE_MODE_MACHINE */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)

/** @defgroup CORE_EXTENSION_ZICNTR_CSR_SCOUNTEREN CSR SCOUNTEREN
 * @{
 */

#define CSR_SCOUNTEREN_CY_Pos 0
#define CSR_SCOUNTEREN_CY_Msk (0x1UL << CSR_SCOUNTEREN_CY_Pos)
#define CSR_SCOUNTEREN_CY     CSR_SCOUNTEREN_CY_Msk

#define CSR_SCOUNTEREN_TM_Pos 1
#define CSR_SCOUNTEREN_TM_Msk (0x1UL << CSR_SCOUNTEREN_TM_Pos)
#define CSR_SCOUNTEREN_TM     CSR_SCOUNTEREN_TM_Msk

#define CSR_SCOUNTEREN_IR_Pos 2
#define CSR_SCOUNTEREN_IR_Msk (0x1UL << CSR_SCOUNTEREN_IR_Pos)
#define CSR_SCOUNTEREN_IR     CSR_SCOUNTEREN_IR_Msk

/** @} */ /* End of group CORE_EXTENSION_ZICNTR_CSR_SCOUNTEREN */

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

/** @} */ /* End of group CORE_EXTENSION_ZICNTR_CSR */

/** @} */ /* End of group CORE_EXTENSION_ZICNTR_Exported_Defines */

/** @} */ /* End of the group CORE_EXTENSION_ZICNTR */

#endif /* CORE_EXTENSION_ZICNTR */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_EXT_ZICNTR */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_extension_zicntr.h */

