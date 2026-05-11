/**
 *******************************************************************************
 * @file    core_types.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    08/04/2025
 * @brief   This file contains all core type definitions.
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
#ifndef CORE_TYPES
#define CORE_TYPES

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

/** @addtogroup CORE_TYPES Core Types
 * @{
 */

/** @defgroup CORE_TYPES_Exported_Defines Core Exported Defines
 * @{
 */

#define CORE_PRIVILEGE_MODE_MACHINE    (1 << 2)
#define CORE_PRIVILEGE_MODE_SUPERVISOR (1 << 1)
#define CORE_PRIVILEGE_MODE_USER       (1 << 0)

#define IS_HART_ID(HARTID)             (((HARTID) & ~0x0FFFUL) == 0x0)

/** @} */ /* End of group CORE_TYPES_Exported_Defines */

/** @defgroup CORE_TYPES_IO_Access_Definitions Core I/O Definitions (Access Restrictions to Peripheral Registers)
 * @{
 */
#ifdef __cplusplus
#define __I volatile /*!< Define 'read only' permissions. */
#else
#define __I volatile const /*!< Define 'read only' permissions. */
#endif
#define __O  volatile /*!< Define 'write only' permissions. */
#define __IO volatile /*!< Define 'read / write' permissions. */

/* Following defines should be used for structure members. */
#define __IM  volatile const /*! Define 'read only' structure member permissions. */
#define __OM  volatile       /*! Define 'write only' structure member permissions. */
#define __IOM volatile       /*! Define 'read / write' structure member permissions. */

/** @} */ /* End of group CORE_TYPES_IO_Access_Definitions */

/** @defgroup CORE_TYPES_Exported_Types Core Exported Types
 * @{
 */

#if (__riscv_xlen == 32)
typedef uint32_t uint_xlen_t;
typedef int32_t  int_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint32_t uint_csr64_t;
#elif (__riscv_xlen == 64)
typedef uint64_t uint_xlen_t;
typedef int64_t  int_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint64_t uint_csr64_t;
#else
#error "Unknown XLEN"
#endif

typedef enum {
    RESET = 0,
    SET   = 1
} FlagStatus,
    ITStatus,
    BitStatus;

#define IS_BIT_STATUS(STATUS) (((STATUS) == RESET) || ((STATUS) == SET))

typedef enum {
    DISABLE = 0,
    ENABLE  = 1
} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {
    ERROR   = 0,
    SUCCESS = 1
} ErrorStatus;

typedef void (*IRQHandler_TypeDef)(void);

/** @} */ /* End of group CORE_TYPES_Exported_Types */

/** @} */ /* End of the group CORE_TYPES */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_TYPES */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_type.h */

