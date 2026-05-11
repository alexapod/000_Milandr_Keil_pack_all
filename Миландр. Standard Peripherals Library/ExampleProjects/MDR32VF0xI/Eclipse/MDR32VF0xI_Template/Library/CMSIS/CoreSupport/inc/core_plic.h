/**
 ******************************************************************************
 * @file    core_plic.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    03/04/2025
 * @brief   RISC-V PLIC Access Layer Header File.
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
#ifndef CORE_PLIC
#define CORE_PLIC

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

#if defined(PLIC_PRESENT)

/** @addtogroup CORE_PLIC PLIC
 * @{
 */

/** @defgroup CORE_PLIC_Configuration PLIC Configuration
 * @{
 */

#ifndef PLIC_NUM_INTERRUPTS
#define PLIC_NUM_INTERRUPTS 32
#warning "PLIC_NUM_INTERRUPTS not defined in device header file; using default value: 32."
#endif

#ifndef PLIC_xTVEC_ALIGN
#define PLIC_xTVEC_ALIGN 2
#warning "PLIC_xTVEC_ALIGN not defined in device header file; using default value: 2."
#endif

/** @} */ /* End of group CORE_PLIC_Configuration */

/** @defgroup CORE_PLIC_Exported_Defines Core PLIC Exported Defines
 * @{
 */

#define PLIC_VECTOR_MASK             ((0xFFFFFFFFUL >> PLIC_xTVEC_ALIGN) << PLIC_xTVEC_ALIGN)
#define PLIC_VECTOR_ALIGN            (1 << PLIC_xTVEC_ALIGN)

#define IS_PLIC_xTVEC_ALIGNED(xTVEC) (((uint32_t)(xTVEC) & ~PLIC_VECTOR_MASK) == 0)
#define IS_PLIC_xTVT_ALIGNED(xTVT)      (((uint32_t)(xTVT) & ~PLIC_VECTOR_MASK)) == 0)
#if defined(__GNUC__)
#define __TRAP_HANDLER_ALIGNED __attribute__((aligned(PLIC_VECTOR_ALIGN)))
#elif defined(__ICCRISCV__)
#define __TRAP_HANDLER_ALIGNED
#endif

#define PLIC_ISP(IRQn) (PLIC_BASE + ((IRQn) * 4)) /*!< PLIC Interrupt Source Priority. */
#define PLIC_IPB       (PLIC_BASE + 0x1000)       /*!< PLIC Interrupt Pending Bits. */
#define PLIC_IEB       (PLIC_BASE + 0x2000)       /*!< PLIC Interrupt Enable Bits. */
#define PLIC_PTHR      (PLIC_BASE + 0x200000)     /*!< PLIC Priority Threshold. */
#define PLIC_ICR       (PLIC_BASE + 0x200004)     /*!< PLIC Interrupt Claim Register and Interrupt Completion. */

/** @} */ /* End of group CORE_PLIC_Exported_Defines */

/** @defgroup CORE_PLIC_CSR_MCAUSE PLIC CSR MCAUSE
 * @{
 */

#define CSR_MCAUSE_EXCCODE_Pos     0
#define CSR_MCAUSE_EXCCODE_Msk     (0x7FFFFFFFUL << CSR_MCAUSE_EXCCODE_Pos)

#define CSR_MCAUSE_EXCCODE_MEI_Pos CSR_MCAUSE_EXCCODE_Pos
#define CSR_MCAUSE_EXCCODE_MEI_Msk (0xBUL << CSR_MCAUSE_EXCCODE_MEI_Pos)
#define CSR_MCAUSE_EXCCODE_MEI     CSR_MCAUSE_EXCCODE_MEI_Msk

#define CSR_MCAUSE_INTERRUPT_Pos   31
#define CSR_MCAUSE_INTERRUPT_Msk   (0x1UL << CSR_MCAUSE_INTERRUPT_Pos)
#define CSR_MCAUSE_INTERRUPT       CSR_MCAUSE_INTERRUPT_Msk

/** @} */ /* End of group CORE_PLIC_CSR_MCAUSE */

/** @defgroup CORE_PLIC_CSR_SCAUSE PLIC CSR SCAUSE
 * @{
 */

#define CSR_SCAUSE_EXCCODE_Pos     0
#define CSR_SCAUSE_EXCCODE_Msk     (0x7FFFFFFFUL << CSR_SCAUSE_EXCCODE_Pos)

#define CSR_SCAUSE_EXCCODE_MEI_Pos 11
#define CSR_SCAUSE_EXCCODE_MEI_Msk (0xBUL << CSR_SCAUSE_EXCCODE_MEI_Pos)
#define CSR_SCAUSE_EXCCODE_MEI     CSR_SCAUSE_EXCCODE_MEI_Msk

#define CSR_SCAUSE_INTERRUPT_Pos   31
#define CSR_SCAUSE_INTERRUPT_Msk   (0x1UL << CSR_SCAUSE_INTERRUPT_Pos)
#define CSR_SCAUSE_INTERRUPT       CSR_SCAUSE_INTERRUPT_Msk

/** @} */ /* End of group CORE_PLIC_CSR_SCAUSE */

/** @defgroup CORE_PLIC_CSR_UCAUSE PLIC CSR UCAUSE
 * @{
 */

#define CSR_UCAUSE_EXCCODE_Pos     0
#define CSR_UCAUSE_EXCCODE_Msk     (0x7FFFFFFFUL << CSR_UCAUSE_EXCCODE_Pos)

#define CSR_UCAUSE_EXCCODE_MEI_Pos 11
#define CSR_UCAUSE_EXCCODE_MEI_Msk (0xBUL << CSR_UCAUSE_EXCCODE_MEI_Pos)
#define CSR_UCAUSE_EXCCODE_MEI     CSR_UCAUSE_EXCCODE_MEI_Msk

#define CSR_UCAUSE_INTERRUPT_Pos   31
#define CSR_UCAUSE_INTERRUPT_Msk   (0x1UL << CSR_UCAUSE_INTERRUPT_Pos)
#define CSR_UCAUSE_INTERRUPT       CSR_UCAUSE_INTERRUPT_Msk

/** @} */ /* End of group CORE_PLIC_CSR_UCAUSE */

/** @defgroup CORE_PLIC_CSR_xTVEC PLIC CSR xTVEC
 * @{
 */

#define CSR_xTVEC_NBASE_Pos PLIC_xTVEC_ALIGN
#define CSR_xTVEC_NBASE_Msk PLIC_VECTOR_MASK

/** @} */ /* End of group CORE_PLIC_CSR_xTVEC */

/** @defgroup CORE_PLIC_CSR_MIE PLIC CSR MIE
 * @{
 */

#define MIE_MSIE_Pos 3
#define MIE_MSIE_Msk (0x1UL << MIE_MSIE_Pos)
#define MIE_MSIE     MIE_MSIE_Msk

#define MIE_MTIE_Pos 7
#define MIE_MTIE_Msk (0x1UL << MIE_MTIE_Pos)
#define MIE_MTIE     MIE_MTIE_Msk

#define MIE_MEIE_Pos 11
#define MIE_MEIE_Msk (0x1UL << MIE_MEIE_Pos)
#define MIE_MEIE     MIE_MEIE_Msk

/** @} */ /* End of group CORE_PLIC_CSR_MIE */

/** @defgroup CORE_PLIC_CSR_MIP PLIC CSR MIP
 * @{
 */

#define MIP_MSIP_Pos 3
#define MIP_MSIP_Msk (0x1UL << MIP_MSIP_Pos)
#define MIP_MSIP     MIP_MSIP_Msk

#define MIP_MTIP_Pos 7
#define MIP_MTIP_Msk (0x1UL << MIP_MTIP_Pos)
#define MIP_MTIP     MIP_MTIP_Msk

#define MIP_MEIP_Pos 11
#define MIP_MEIP_Msk (0x1UL << MIP_MEIP_Pos)
#define MIP_MEIP     MIP_MEIP_Msk

/** @} */ /* End of group CORE_PLIC_CSR_MIP */

/** @defgroup CORE_PLIC_CSR_SIE PLIC CSR SIE
 * @{
 */

#define SIE_SSIE_Pos 1
#define SIE_SSIE_Msk (0x1UL << SIE_SSIE_Pos)
#define SIE_SSIE     SIE_SSIE_Msk

#define SIE_STIE_Pos 5
#define SIE_STIE_Msk (0x1UL << SIE_STIE_Pos)
#define SIE_STIE     SIE_STIE_Msk

#define SIE_SEIE_Pos 9
#define SIE_SEIE_Msk (0x1UL << SIE_SEIE_Pos)
#define SIE_SEIE     SIE_SEIE_Msk

/** @} */ /* End of group CORE_PLIC_CSR_SIE */

/** @defgroup CORE_PLIC_CSR_SIP PLIC CSR SIP
 * @{
 */

#define SIP_SSIP_Pos 1
#define SIP_SSIP_Msk (0x1UL << SIP_SSIP_Pos)
#define SIE_SSIP     SIP_SSIP_Msk

#define SIP_STIP_Pos 5
#define SIP_STIP_Msk (0x1UL << SIP_STIP_Pos)
#define SIP_STIP     SIP_STIP_Msk

#define SIP_SEIP_Pos 9
#define SIP_SEIP_Msk (0x1UL << SIP_SEIP_Pos)
#define SIP_SEIP     SIP_SEIP_Msk

/** @} */ /* End of group CORE_PLIC_CSR_SIP */

/** @defgroup CORE_PLIC_CSR_UIE PLIC CSR UIE
 * @{
 */

#define UIE_USIE_Pos 0
#define UIE_USIE_Msk (0x1UL << UIE_USIE_Pos)
#define UIE_USIE     UIE_USIE_Msk

#define UIE_UTIE_Pos 4
#define UIE_UTIE_Msk (0x1UL << UIE_UTIE_Pos)
#define UIE_UTIE     UIE_UTIE_Msk

#define UIE_UEIE_Pos 8
#define UIE_UEIE_Msk (0x1UL << UIE_UEIE_Pos)
#define UIE_UEIE     UIE_UEIE_Msk

/** @} */ /* End of group CORE_PLIC_CSR_UIE */

/** @defgroup CORE_PLIC_CSR_UIP PLIC CSR UIP
 * @{
 */

#define UIP_USIP_Pos 0
#define UIP_USIP_Msk (0x1UL << UIP_USIP_Pos)
#define UIP_USIP     UIP_USIP_Msk

#define UIP_UTIP_Pos 4
#define UIP_UTIP_Msk (0x1UL << UIP_UTIP_Pos)
#define UIP_UTIP     UIP_UTIP_Msk

#define UIP_UEIP_Pos 8
#define UIP_UEIP_Msk (0x1UL << UIP_UEIP_Pos)
#define UIP_UEIP     UIP_UEIP_Msk

/** @} */ /* End of group CORE_PLIC_CSR_UIP */

/** @defgroup CORE_PLIC_ISP PLIC ISP
 * @{
 */

#define PLIC_ISP_PRIORITY_Pos 0
#define PLIC_ISP_PRIORITY_Msk (0x7UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_0   (0x0UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_1   (0x1UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_2   (0x2UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_3   (0x3UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_4   (0x4UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_5   (0x5UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_6   (0x6UL << PLIC_ISP_PRIORITY_Pos)
#define PLIC_ISP_PRIORITY_7   (0x7UL << PLIC_ISP_PRIORITY_Pos)

/** @} */ /* End of group CORE_PLIC_ISP */

/** @defgroup CORE_PLIC_THR PLIC THR
 * @{
 */

#define PLIC_THR_THRESHOLD_Pos 0
#define PLIC_THR_THRESHOLD_Msk (0x7UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_0   (0x0UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_1   (0x1UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_2   (0x2UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_3   (0x3UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_4   (0x4UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_5   (0x5UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_6   (0x6UL << PLIC_THR_THRESHOLD_Pos)
#define PLIC_THR_THRESHOLD_7   (0x7UL << PLIC_THR_THRESHOLD_Pos)

/** @} */ /* End of group CORE_PLIC_THR */

/** @addtogroup CORE_PLIC_Hardware_Abstraction_Layer PLIC Hardware Abstraction Layer
 * @{
 */

/** @defgroup CORE_PLIC_Exported_Types PLIC Exported Types
 * @{
 */

/**
 * @brief PLIC priority level for interrupts.
 */
typedef enum {
    PLIC_PRIORITY_OFF           = PLIC_ISP_PRIORITY_0,
    PLIC_PRIORITY_LOWEST        = PLIC_ISP_PRIORITY_1,
    PLIC_PRIORITY_LOW           = PLIC_ISP_PRIORITY_2,
    PLIC_PRIORITY_BELOW_AVERAGE = PLIC_ISP_PRIORITY_3,
    PLIC_PRIORITY_AVERAGE       = PLIC_ISP_PRIORITY_4,
    PLIC_PRIORITY_ABOVE_AVERAGE = PLIC_ISP_PRIORITY_5,
    PLIC_PRIORITY_HIGH          = PLIC_ISP_PRIORITY_6,
    PLIC_PRIORITY_HIGHEST       = PLIC_ISP_PRIORITY_7
} PLIC_PriorityIRQ_TypeDef;

#define IS_PLIC_PRIORITY_IRQ(PRIORITY_IRQ) (((PRIORITY_IRQ) == PLIC_PRIORITY_OFF) ||           \
                                            ((PRIORITY_IRQ) == PLIC_PRIORITY_LOWEST) ||        \
                                            ((PRIORITY_IRQ) == PLIC_PRIORITY_LOW) ||           \
                                            ((PRIORITY_IRQ) == PLIC_PRIORITY_BELOW_AVERAGE) || \
                                            ((PRIORITY_IRQ) == PLIC_PRIORITY_AVERAGE) ||       \
                                            ((PRIORITY_IRQ) == PLIC_PRIORITY_ABOVE_AVERAGE) || \
                                            ((PRIORITY_IRQ) == PLIC_PRIORITY_HIGH) ||          \
                                            ((PRIORITY_IRQ) == PLIC_PRIORITY_HIGHEST))

/**
 * @brief PLIC threshold level for interrupts.
 */
typedef enum {
    PLIC_THRESHOLD_0_ENABLE_ALL  = PLIC_THR_THRESHOLD_0,
    PLIC_THRESHOLD_1             = PLIC_THR_THRESHOLD_1,
    PLIC_THRESHOLD_2             = PLIC_THR_THRESHOLD_2,
    PLIC_THRESHOLD_3             = PLIC_THR_THRESHOLD_3,
    PLIC_THRESHOLD_4             = PLIC_THR_THRESHOLD_4,
    PLIC_THRESHOLD_5             = PLIC_THR_THRESHOLD_5,
    PLIC_THRESHOLD_6             = PLIC_THR_THRESHOLD_6,
    PLIC_THRESHOLD_7_DISABLE_ALL = PLIC_THR_THRESHOLD_7
} PLIC_ThresholdIRQ_TypeDef;

#define IS_PLIC_THRESHOLD_IRQ(THRESHOLD_IRQ) (((THRESHOLD_IRQ) == PLIC_THRESHOLD_0_ENABLE_ALL) || \
                                              ((THRESHOLD_IRQ) == PLIC_THRESHOLD_1) ||            \
                                              ((THRESHOLD_IRQ) == PLIC_THRESHOLD_2) ||            \
                                              ((THRESHOLD_IRQ) == PLIC_THRESHOLD_3) ||            \
                                              ((THRESHOLD_IRQ) == PLIC_THRESHOLD_4) ||            \
                                              ((THRESHOLD_IRQ) == PLIC_THRESHOLD_5) ||            \
                                              ((THRESHOLD_IRQ) == PLIC_THRESHOLD_6) ||            \
                                              ((THRESHOLD_IRQ) == PLIC_THRESHOLD_7_DISABLE_ALL))

/**
 * @brief PLIC interrupt privilege modes.
 */
typedef enum {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
    PLIC_PRIVILEGE_IRQ_MODE_M = CORE_PRIVILEGE_MODE_MACHINE, /*!< Select a M-mode for interrupt. */
#endif                                                       /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
    PLIC_PRIVILEGE_IRQ_MODE_S = CORE_PRIVILEGE_MODE_SUPERVISOR, /*!< Select a S-mode for interrupt. */
#endif                                                          /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
    PLIC_PRIVILEGE_IRQ_MODE_U = CORE_PRIVILEGE_MODE_USER, /*!< Select a U-mode for interrupt. */
#endif                                                    /* CORE_PRIVILEGE_LEVEL_USER */
} PLIC_PrivilegeIRQ_TypeDef;

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
#define IS_PLIC_PRIVILEGE_IRQ(PRIVILEGE) ((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_M)
#elif defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
#define IS_PLIC_PRIVILEGE_IRQ(PRIVILEGE) (((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_M) || \
                                          ((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_S))
#elif defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
#define IS_PLIC_PRIVILEGE_IRQ(PRIVILEGE) (((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_M) || \
                                          ((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_U))
#elif defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
#define IS_PLIC_PRIVILEGE_IRQ(PRIVILEGE) (((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_M) || \
                                          ((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_S) || \
                                          ((PRIVILEGE) == PLIC_PRIVILEGE_IRQ_MODE_U))
#endif

/** @} */ /* End of group CORE_PLIC_Exported_Types */

/** @addtogroup CORE_PLIC_Exported_Functions PLIC Exported Functions
 * @{
 */

void PLIC_EnableSoftwareIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege);
void PLIC_DisableSoftwareIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege);

void PLIC_EnableMTIMERIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege);
void PLIC_DisableMTIMERIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege);

void PLIC_EnableExternalIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege);
void PLIC_DisableExternalIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege);

void PLIC_EnableIRQ(IRQn_TypeDef IRQn);
void PLIC_DisableIRQ(IRQn_TypeDef IRQn);

void                     PLIC_SetPriorityIRQ(IRQn_TypeDef IRQn, PLIC_PriorityIRQ_TypeDef Priority);
PLIC_PriorityIRQ_TypeDef PLIC_GetPriorityIRQ(IRQn_TypeDef IRQn);

FlagStatus PLIC_GetPendingIRQ(IRQn_TypeDef IRQn);

void                      PLIC_SetThresholdIRQ(PLIC_ThresholdIRQ_TypeDef Threshold);
PLIC_ThresholdIRQ_TypeDef PLIC_GetThresholdIRQ(void);

IRQn_TypeDef PLIC_ClaimIRQ(void);
void         PLIC_CompleteIRQ(IRQn_TypeDef IRQn);

void               PLIC_SetTrapVector(PLIC_PrivilegeIRQ_TypeDef Privilege, IRQHandler_TypeDef TrapVector);
IRQHandler_TypeDef PLIC_GetTrapVector(PLIC_PrivilegeIRQ_TypeDef Privilege);

/** @} */ /* End of the group CORE_PLIC_Exported_Functions */

/** @} */ /* End of group CORE_PLIC_Hardware_Abstraction_Layer */

/** @} */ /* End of the group CORE_PLIC */

#endif /* PLIC_PRESENT */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_PLIC */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_plic.h */

