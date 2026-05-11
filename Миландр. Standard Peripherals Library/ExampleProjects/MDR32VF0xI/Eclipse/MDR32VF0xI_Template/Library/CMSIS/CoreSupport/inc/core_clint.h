/**
 ******************************************************************************
 * @file    core_clint.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    03/04/2025
 * @brief   This file contains all the functions prototypes for RISC-V CLINT.
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
#ifndef CORE_CLINT
#define CORE_CLINT

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "core_types.h"
#include "core_config.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(CLINT_PRESENT)

/** @addtogroup CORE_CLINT CLINT
 * @{
 */

/** @defgroup CORE_CLINT_Configuration CLINT Configuration
 * @{
 */

#ifndef HARTS_AMOUNT
#error "HARTS_AMOUNT not defined in device header file!"
#endif

#ifndef CLINT_BASE
#error "CLINT_BASE not defined in device header file!"
#endif

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
#ifndef CLINT_SSWI_OFFSET
#error "CLINT_SSWI_OFFSET not defined in device header file!"
#endif
#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
#ifndef CLINT_MSWI_OFFSET
#error "CLINT_MSWI_OFFSET not defined in device header file!"
#endif

#ifndef CLINT_MTIMER_MTIMECMP_OFFSET
#error "CLINT_MTIMER_MTIMECMP_OFFSET not defined in device header file!"
#endif

#ifndef CLINT_MTIMER_MTIME_OFFSET
#error "CLINT_MTIMER_MTIME_OFFSET not defined in device header file!"
#endif
#endif /* CORE_PRIVILEGE_MODE_MACHINE */

/** @} */ /* End of group CORE_CLINT_Configuration */

/** @addtogroup CORE_CLINT_Exported_Defines CLINT Exported Defines
 * @{
 */

#define CLINT_MTIMECMP_OFFSET(HART_ID) ((HART_ID) * 4 * 2)
#define CLINT_MSIP_OFFSET(HART_ID)     ((HART_ID) * 4)

/** @addtogroup CORE_CLINT_Registers_Abstraction_Layer CLINT Register Abstraction Layer
 * @{
 */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
/**
 * @brief CLINT MSWI register structure.
 */
typedef struct {
    __IO uint_xlen_t MSIP[HARTS_AMOUNT]; /*!<CLINT MSWI MSIP Register */
} CLINT_MSWI_TypeDef;

/**
 * @brief CLINT MTIMER register structure.
 */
#if (__riscv_xlen == 32)
typedef struct {
    __IO uint32_t MTIMECMP[HARTS_AMOUNT][2]; /*!<CLINT MSWI MSIP Register */
} CLINT_MTIMER_MTIMECMP_TypeDef;
#elif (__riscv_xlen == 64)
typedef struct {
    __IO uint64_t MTIMECMP[HARTS_AMOUNT]; /*!<CLINT MSWI MSIP Register */
} CLINT_MTIMER_MTIMECMP_TypeDef;
#endif

#endif /* CORE_PRIVILEGE_MODE_MACHINE */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
/**
 * @brief CLINT SSWI register structure.
 */
typedef struct {
    __IO uint_xlen_t SETSSIP[HARTS_AMOUNT]; /*!<CLINT SSWI SETSSIP Register */
} CLINT_SSWI_TypeDef;

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

/** @} */ /* End of group CORE_CLINT_Registers_Abstraction_Layer */

/** @defgroup CORE_CLINT_Declaration CLINT Declaration
 * @{
 */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)

#define CLINT_MSWI            ((CLINT_MSWI_TypeDef*)(CLINT_BASE + CLINT_MSWI_OFFSET))
#define CLINT_MTIMER_MTIMECMP ((CLINT_MTIMER_MTIMECMP_TypeDef*)(CLINT_BASE + CLINT_MTIMER_MTIMECMP_OFFSET))

#endif /* CORE_PRIVILEGE_MODE_MACHINE */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)

#define CLINT_SSWI ((CLINT_SSWI_TypeDef*)(CLINT_BASE + CLINT_SSWI_OFFSET))

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

/** @} */ /* End of group CORE_CLINT_Declaration */

/** @} */ /* End of group CORE_CLINT_Exported_Defines */

/** @defgroup CLINT_Exported_Functions CLINT Exported Functions
 * @{
 */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)

#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
void     CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus);
ITStatus CLINT_GetSoftwareMachineIRQ(void);

void     CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue);
uint64_t CLINT_MTIMER_GetCompareTime(void);
#elif defined(HARTS_AMOUNT)
void     CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus, uint32_t HartIndex);
ITStatus CLINT_GetSoftwareMachineIRQ(uint32_t HartIndex);

void     CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue, uint32_t HartIndex);
uint64_t CLINT_MTIMER_GetCompareTime(uint32_t HartIndex);
#endif

void     CLINT_MTIMER_SetTime(uint64_t MTIMEValue);
uint64_t CLINT_MTIMER_GetTime(void);

#endif /* CORE_PRIVILEGE_MODE_MACHINE */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)

#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
void     CLINT_SetSoftwareSupervisorIRQ(ITStatus IRQStatus);
ITStatus CLINT_GetSoftwareSupervisorIRQ(void);
#elif defined(HARTS_AMOUNT)
void     CLINT_SetSoftwareSupervisorIRQ(ITStatus IRQStatus, uint32_t HartIndex);
ITStatus CLINT_GetSoftwareSupervisorIRQ(uint32_t HartIndex);
#endif /* HARTS_AMOUNT */

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

/** @} */ /* End of the group CLINT_Exported_Functions */

/** @} */ /* End of the group CORE_CLINT */

#endif /* CLINT_PRESENT */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_CLINT */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_clint.h */

