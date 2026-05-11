/**
 ******************************************************************************
 * @file    core_compiler.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    13/05/2025
 * @brief   CMSIS compiler specific macros, functions, instructions.
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
#ifndef CORE_COMPILER
#define CORE_COMPILER

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

/** @addtogroup CORE_BM310S BM-310S Core
 * @{
 */

/** @addtogroup CORE_COMPILER Core Compiler
 * @{
 */

/* CMSIS compiler specific defines. */
#ifndef __ASM
#define __ASM __asm
#endif
#ifndef __NOP
#define __NOP() __ASM volatile("nop");
#endif
#ifndef __WFI
#define __WFI() __ASM volatile("wfi");
#endif
#ifndef __INLINE
#define __INLINE inline
#endif
#ifndef __FORCEINLINE
#define __FORCEINLINE __attribute__((always_inline)) inline
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#endif
#ifndef __NO_RETURN
#define __NO_RETURN __attribute__((__noreturn__))
#endif
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#endif

#if defined(__GNUC__) /* GCC compiler. */
#ifndef __INTERRUPT_MACHINE
#define __INTERRUPT_MACHINE __attribute__((interrupt("machine")))
#endif
#ifndef __INTERRUPT_SUPERVISOR
#define __INTERRUPT_SUPERVISOR __attribute__((interrupt("supervisor")))
#endif
#ifndef __INTERRUPT_USER
#define __INTERRUPT_USER __attribute__((interrupt("user")))
#endif
#elif defined(__ICCRISCV__) /* IAR RISC-V compiler. */
#ifndef __INTERRUPT_MACHINE
#define __INTERRUPT_MACHINE __interrupt __machine
#endif
#ifndef __INTERRUPT_SUPERVISOR
#define __INTERRUPT_SUPERVISOR __interrupt __supervisor
#endif
#ifndef __INTERRUPT_USER
#define __INTERRUPT_USER __interrupt __user
#endif
#else
#error "Unsupported compiler is used."
#endif

/** @} */ /* End of the group CORE_COMPILER */

/** @} */ /* End of the group CORE_BM310S */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_CSR */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_compiler.h */

