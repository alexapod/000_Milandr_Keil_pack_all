/**
 ******************************************************************************
 * @file    core_csr.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   RISC-V CSR Access Layer File.
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
#ifndef CORE_CSR
#define CORE_CSR

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "core_compiler.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

/** @addtogroup CORE_BM310S BM-310S Core
 * @{
 */

/** @addtogroup CORE_CSR Core CSR
 * @{
 */

/** @defgroup CORE_CSR_Exported_Defines Core CSR Exported Defines
 * @{
 */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)

/* User Trap Setup */
#define CSR_USTATUS (0x000)
#define CSR_UIE     (0x004)
#define CSR_UTVEC   (0x005)

/* User Trap Handling */
#define CSR_USCRATCH (0x040)
#define CSR_UEPC     (0x041)
#define CSR_UCAUSE   (0x042)
#define CSR_UTVAL    (0x043)
#define CSR_UIP      (0x044)

#endif /* CORE_PRIVILEGE_MODE_USER */

#if defined(FPU_PRESENT) && (FPU_PRESENT > 0)

/* User Floating-Point CSRs */
#define CSR_FFLAGS (0x001)
#define CSR_FRM    (0x002)
#define CSR_FCSR   (0x003)

#endif /* #if defined(FPU_PRESENT) && (FPU_PRESENT > 0) */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)

/* User Counter/Timers */
#define CSR_HPMCOUNTER3  (0xC03)
#define CSR_HPMCOUNTER4  (0xC04)
#define CSR_HPMCOUNTER5  (0xC05)
#define CSR_HPMCOUNTER6  (0xC06)
#define CSR_HPMCOUNTER7  (0xC07)
#define CSR_HPMCOUNTER8  (0xC08)
#define CSR_HPMCOUNTER9  (0xC09)
#define CSR_HPMCOUNTER10 (0xC0A)
#define CSR_HPMCOUNTER11 (0xC0B)
#define CSR_HPMCOUNTER12 (0xC0C)
#define CSR_HPMCOUNTER13 (0xC0D)
#define CSR_HPMCOUNTER14 (0xC0E)
#define CSR_HPMCOUNTER15 (0xC0F)
#define CSR_HPMCOUNTER16 (0xC10)
#define CSR_HPMCOUNTER17 (0xC11)
#define CSR_HPMCOUNTER18 (0xC12)
#define CSR_HPMCOUNTER19 (0xC13)
#define CSR_HPMCOUNTER20 (0xC14)
#define CSR_HPMCOUNTER21 (0xC15)
#define CSR_HPMCOUNTER22 (0xC16)
#define CSR_HPMCOUNTER23 (0xC17)
#define CSR_HPMCOUNTER24 (0xC18)
#define CSR_HPMCOUNTER25 (0xC19)
#define CSR_HPMCOUNTER26 (0xC1A)
#define CSR_HPMCOUNTER27 (0xC1B)
#define CSR_HPMCOUNTER28 (0xC1C)
#define CSR_HPMCOUNTER29 (0xC1D)
#define CSR_HPMCOUNTER30 (0xC1E)
#define CSR_HPMCOUNTER31 (0xC1F)

#if (__riscv_xlen == 32)

#define CSR_HPMCOUNTER3H  (0xC83)
#define CSR_HPMCOUNTER4H  (0xC84)
#define CSR_HPMCOUNTER5H  (0xC85)
#define CSR_HPMCOUNTER6H  (0xC86)
#define CSR_HPMCOUNTER7H  (0xC87)
#define CSR_HPMCOUNTER8H  (0xC88)
#define CSR_HPMCOUNTER9H  (0xC89)
#define CSR_HPMCOUNTER10H (0xC8A)
#define CSR_HPMCOUNTER11H (0xC8B)
#define CSR_HPMCOUNTER12H (0xC8C)
#define CSR_HPMCOUNTER13H (0xC8D)
#define CSR_HPMCOUNTER14H (0xC8E)
#define CSR_HPMCOUNTER15H (0xC8F)
#define CSR_HPMCOUNTER16H (0xC90)
#define CSR_HPMCOUNTER17H (0xC91)
#define CSR_HPMCOUNTER18H (0xC92)
#define CSR_HPMCOUNTER19H (0xC93)
#define CSR_HPMCOUNTER20H (0xC94)
#define CSR_HPMCOUNTER21H (0xC95)
#define CSR_HPMCOUNTER22H (0xC96)
#define CSR_HPMCOUNTER23H (0xC97)
#define CSR_HPMCOUNTER24H (0xC98)
#define CSR_HPMCOUNTER25H (0xC99)
#define CSR_HPMCOUNTER26H (0xC9A)
#define CSR_HPMCOUNTER27H (0xC9B)
#define CSR_HPMCOUNTER28H (0xC9C)
#define CSR_HPMCOUNTER29H (0xC9D)
#define CSR_HPMCOUNTER30H (0xC9E)
#define CSR_HPMCOUNTER31H (0xC9F)

#endif /* __riscv_xlen == 32 */

#endif /* CORE_PRIVILEGE_MODE_USER */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)

/* Supervisor Trap Setup */
#define CSR_SSTATUS (0x100)
#define CSR_SEDELEG (0x102)
#define CSR_SIDELEG (0x103)
#define CSR_SIE     (0x104)
#define CSR_STVEC   (0x105)

/* Supervisor Trap Handling */
#define CSR_SSCRATCH (0x140)
#define CSR_SEPC     (0x141)
#define CSR_SCAUSE   (0x142)
#define CSR_STVAL    (0x143)
#define CSR_SIP      (0x144)

/* Supervisor Protection and Translation */
#define CSR_SATP (0x180)

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)

/* Machine Information Registers */
#define CSR_MVENDORID (0xF11)
#define CSR_MARCHID   (0xF12)
#define CSR_MIMPID    (0xF13)
#define CSR_MHARTID   (0xF14)

/* Machine Trap Setup */
#define CSR_MSTATUS (0x300)
#define CSR_MISA    (0x301)
#define CSR_MEDELEG (0x302)
#define CSR_MIDELEG (0x303)
#define CSR_MIE     (0x304)
#define CSR_MTVEC   (0x305)

/* Machine Trap Handling */
#define CSR_MSCRATCH (0x340)
#define CSR_MEPC     (0x341)
#define CSR_MCAUSE   (0x342)
#define CSR_MTVAL    (0x343)
#define CSR_MIP      (0x344)

/* Machine Counter/Timers */
#define CSR_MHPMCOUNTER3  (0xB03)
#define CSR_MHPMCOUNTER4  (0xB04)
#define CSR_MHPMCOUNTER5  (0xB05)
#define CSR_MHPMCOUNTER6  (0xB06)
#define CSR_MHPMCOUNTER7  (0xB07)
#define CSR_MHPMCOUNTER8  (0xB08)
#define CSR_MHPMCOUNTER9  (0xB09)
#define CSR_MHPMCOUNTER10 (0xB0A)
#define CSR_MHPMCOUNTER11 (0xB0B)
#define CSR_MHPMCOUNTER12 (0xB0C)
#define CSR_MHPMCOUNTER13 (0xB0D)
#define CSR_MHPMCOUNTER14 (0xB0E)
#define CSR_MHPMCOUNTER15 (0xB0F)
#define CSR_MHPMCOUNTER16 (0xB10)
#define CSR_MHPMCOUNTER17 (0xB11)
#define CSR_MHPMCOUNTER18 (0xB12)
#define CSR_MHPMCOUNTER19 (0xB13)
#define CSR_MHPMCOUNTER20 (0xB14)
#define CSR_MHPMCOUNTER21 (0xB15)
#define CSR_MHPMCOUNTER22 (0xB16)
#define CSR_MHPMCOUNTER23 (0xB17)
#define CSR_MHPMCOUNTER24 (0xB18)
#define CSR_MHPMCOUNTER25 (0xB19)
#define CSR_MHPMCOUNTER26 (0xB1A)
#define CSR_MHPMCOUNTER27 (0xB1B)
#define CSR_MHPMCOUNTER28 (0xB1C)
#define CSR_MHPMCOUNTER29 (0xB1D)
#define CSR_MHPMCOUNTER30 (0xB1E)
#define CSR_MHPMCOUNTER31 (0xB1F)

#if (__riscv_xlen == 32)

#define CSR_MHPMCOUNTER3H  (0xB83)
#define CSR_MHPMCOUNTER4H  (0xB84)
#define CSR_MHPMCOUNTER5H  (0xB85)
#define CSR_MHPMCOUNTER6H  (0xB86)
#define CSR_MHPMCOUNTER7H  (0xB87)
#define CSR_MHPMCOUNTER8H  (0xB88)
#define CSR_MHPMCOUNTER9H  (0xB89)
#define CSR_MHPMCOUNTER10H (0xB8A)
#define CSR_MHPMCOUNTER11H (0xB8B)
#define CSR_MHPMCOUNTER12H (0xB8C)
#define CSR_MHPMCOUNTER13H (0xB8D)
#define CSR_MHPMCOUNTER14H (0xB8E)
#define CSR_MHPMCOUNTER15H (0xB8F)
#define CSR_MHPMCOUNTER16H (0xB90)
#define CSR_MHPMCOUNTER17H (0xB91)
#define CSR_MHPMCOUNTER18H (0xB92)
#define CSR_MHPMCOUNTER19H (0xB93)
#define CSR_MHPMCOUNTER20H (0xB94)
#define CSR_MHPMCOUNTER21H (0xB95)
#define CSR_MHPMCOUNTER22H (0xB96)
#define CSR_MHPMCOUNTER23H (0xB97)
#define CSR_MHPMCOUNTER24H (0xB98)
#define CSR_MHPMCOUNTER25H (0xB99)
#define CSR_MHPMCOUNTER26H (0xB9A)
#define CSR_MHPMCOUNTER27H (0xB9B)
#define CSR_MHPMCOUNTER28H (0xB9C)
#define CSR_MHPMCOUNTER29H (0xB9D)
#define CSR_MHPMCOUNTER30H (0xB9E)
#define CSR_MHPMCOUNTER31H (0xB9F)

#endif /* __riscv_xlen == 32 */

/* Machine Counter Setup */
#define CSR_MHPMEVENT3  (0x323)
#define CSR_MHPMEVENT4  (0x324)
#define CSR_MHPMEVENT5  (0x325)
#define CSR_MHPMEVENT6  (0x326)
#define CSR_MHPMEVENT7  (0x327)
#define CSR_MHPMEVENT8  (0x328)
#define CSR_MHPMEVENT9  (0x329)
#define CSR_MHPMEVENT10 (0x32A)
#define CSR_MHPMEVENT11 (0x32B)
#define CSR_MHPMEVENT12 (0x32C)
#define CSR_MHPMEVENT13 (0x32D)
#define CSR_MHPMEVENT14 (0x32E)
#define CSR_MHPMEVENT15 (0x32F)
#define CSR_MHPMEVENT16 (0x330)
#define CSR_MHPMEVENT17 (0x331)
#define CSR_MHPMEVENT18 (0x332)
#define CSR_MHPMEVENT19 (0x333)
#define CSR_MHPMEVENT20 (0x334)
#define CSR_MHPMEVENT21 (0x335)
#define CSR_MHPMEVENT22 (0x336)
#define CSR_MHPMEVENT23 (0x337)
#define CSR_MHPMEVENT24 (0x338)
#define CSR_MHPMEVENT25 (0x339)
#define CSR_MHPMEVENT26 (0x33A)
#define CSR_MHPMEVENT27 (0x33B)
#define CSR_MHPMEVENT28 (0x33C)
#define CSR_MHPMEVENT29 (0x33D)
#define CSR_MHPMEVENT30 (0x33E)
#define CSR_MHPMEVENT31 (0x33F)

/* Debug/Trace Registers (shared with Debug Mode) */
#define CSR_TSELECT (0x7A0)
#define CSR_TDATA1  (0x7A1)
#define CSR_TDATA2  (0x7A2)
#define CSR_TDATA3  (0x7A3)

/* Debug Mode Registers */
#define CSR_DCSR     (0x7B0)
#define CSR_DPC      (0x7B1)
#define CSR_DSCRATCH (0x7B2)

#endif /* CORE_PRIVILEGE_MODE_MACHINE */

#if !defined(__ASSEMBLER__) && !defined(__IASMRISCV__)

/**
 * @brief  Read specified CSR register.
 * @param  reg: CSR register number.
 * @return CSR register value.
 */
#define CSR_Read(reg) __extension__({ \
    uint_xlen_t tmp; \
    __ASM volatile ("csrr %0, %1" : "=r"(tmp) : "i"(reg) ); \
    tmp; })

/**
 * @brief  Write value to specified CSR register.
 * @param  reg: CSR register number.
 * @param  val: Value to write into CSR.
 * @return None.
 */
#define CSR_Write(reg, val)                                 \
    {                                                       \
        __ASM volatile("csrw %0, %1" ::"i"(reg), "r"(val)); \
    }

/**
 * @brief  Read previous value from specified CSR register and write new value to this register.
 * @param  reg: CSR register number.
 * @param  val: Value to write into CSR.
 * @return CSR register value before write.
 */
#define CSR_ReadWrite(reg, val) __extension__({ \
    uint_xlen_t tmp; \
    __ASM volatile ("csrrw %0, %1, %2" : "=r"(tmp) : "i"(reg), "r"(val)); \
    tmp; })

/**
 * @brief  Set bits by mask for specified CSR register.
 * @param  reg: CSR register number.
 * @param  mask: Bit mask.
 * @return None.
 */
#define CSR_SetBits(reg, mask)                                      \
    {                                                               \
        __ASM volatile("csrrs zero, %0, %1" ::"i"(reg), "r"(mask)); \
    }

/**
 * @brief  Read previous value from specified CSR register and set bits by mask for this register.
 * @param  reg: CSR register number.
 * @param  mask: Bit mask.
 * @return CSR register value before write.
 */
#define CSR_ReadSetBits(reg, mask) __extension__({ \
    uint_xlen_t tmp; \
    __ASM volatile ("csrrs %0, %1, %2" : "=r"(tmp) :  "i"(reg), "r"(mask)); \
    tmp; })

/**
 * @brief  Clear bits by mask for specified CSR register.
 * @param  reg: CSR register number.
 * @param  mask: Bit mask.
 * @return None.
 */
#define CSR_ClearBits(reg, mask)                                    \
    {                                                               \
        __ASM volatile("csrrc zero, %0, %1" ::"i"(reg), "r"(mask)); \
    }

/**
 * @brief  Read previous value from specified CSR register and clear bits by mask for this register.
 * @param  reg: CSR register number.
 * @param  mask: Bit mask.
 * @return CSR register value before write.
 */
#define CSR_ReadClearBits(reg, mask) __extension__({ \
    uint_xlen_t tmp; \
    __ASM volatile ("csrrc %0, %1, %2" : "=r"(tmp) : "i"(reg), "r"(mask)); \
    tmp; })

/** @} */ /* End of group CORE_CSR_Exported_Defines */

/** @} */ /* End of the group CORE_CSR */

/** @} */ /* End of the group CORE_BM310S */

/** @} */ /* End of the group CORE_SUPPORT */

#endif /* !__ASSEMBLER__ && !__IASMRISCV__ */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_CSR */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_csr.h */

