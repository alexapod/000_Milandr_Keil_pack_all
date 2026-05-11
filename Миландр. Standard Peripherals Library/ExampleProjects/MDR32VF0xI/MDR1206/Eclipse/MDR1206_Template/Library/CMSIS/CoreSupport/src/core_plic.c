/**
 *******************************************************************************
 * @file    core_plic.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   RISC-V PLIC Access Layer Source File.
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

/* Includes ------------------------------------------------------------------*/
#include "core_plic.h"
#include "core_csr.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(PLIC_PRESENT)

/** @addtogroup CORE_PLIC PLIC
 * @{
 */

/** @addtogroup CORE_PLIC_Exported_Functions PLIC Exported Functions
 * @{
 */

/**
 * @brief  Enables software interrupt in the PLIC.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void PLIC_EnableSoftwareIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            CSR_SetBits(CSR_MIE, MIE_MSIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            CSR_SetBits(CSR_SIE, SIE_SSIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            CSR_SetBits(CSR_UIE, UIE_USIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }
}

/**
 * @brief  Disables software interrupt in the PLIC.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void PLIC_DisableSoftwareIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            CSR_ClearBits(CSR_MIE, MIE_MSIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            CSR_ClearBits(CSR_SIE, SIE_SSIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            CSR_ClearBits(CSR_UIE, UIE_USIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }
}

/**
 * @brief  Enables MTIMER interrupt in the PLIC.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void PLIC_EnableMTIMERIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            CSR_SetBits(CSR_MIE, MIE_MTIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            CSR_SetBits(CSR_SIE, SIE_STIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            CSR_SetBits(CSR_UIE, UIE_UTIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }
}

/**
 * @brief  Disables MTIMER interrupt in the PLIC.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void PLIC_DisableMTIMERIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            CSR_ClearBits(CSR_MIE, MIE_MTIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            CSR_ClearBits(CSR_SIE, SIE_STIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            CSR_ClearBits(CSR_UIE, UIE_UTIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }
}

/**
 * @brief  Enables all external interrupt in the PLIC.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void PLIC_EnableExternalIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            CSR_SetBits(CSR_MIE, MIE_MEIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            CSR_SetBits(CSR_SIE, SIE_SEIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            CSR_SetBits(CSR_UIE, UIE_UEIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }
}

/**
 * @brief  Disables all external interrupt in the PLIC.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void PLIC_DisableExternalIRQ(PLIC_PrivilegeIRQ_TypeDef Privilege)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            CSR_ClearBits(CSR_MIE, MIE_MEIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            CSR_ClearBits(CSR_SIE, SIE_SEIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            CSR_ClearBits(CSR_UIE, UIE_UEIE);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }
}

/**
 * @brief  Set priority to external interrupt in PLIC.
 * @param  IRQn: @ref IRQn_TypeDef - device specific interrupt number.
 * @param  Priority: @ref PLIC_PriorityIRQ_TypeDef - priority level.
 * @return None.
 */
void PLIC_SetPriorityIRQ(IRQn_TypeDef IRQn, PLIC_PriorityIRQ_TypeDef Priority)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));
    assert_param(IS_PLIC_PRIORITY_IRQ(Priority));

    *(volatile uint32_t*)(PLIC_ISP(IRQn)) = (uint32_t)Priority;
}

/**
 * @brief  Get priority to external interrupt in PLIC.
 * @param  IRQn: @ref IRQn_TypeDef - device specific interrupt number.
 * @return @ref PLIC_PriorityIRQ_TypeDef - priority level.
 */
PLIC_PriorityIRQ_TypeDef PLIC_GetPriorityIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    return (PLIC_PriorityIRQ_TypeDef)(*(volatile uint32_t*)(PLIC_ISP(IRQn)));
}

/**
 * @brief  Get pending bit to external interrupt in PLIC.
 * @param  IRQn: @ref IRQn_TypeDef - device specific interrupt number.
 * @return @ref FlagStatus - the current status flag state (SET or RESET).
 */
FlagStatus PLIC_GetPendingIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    uint8_t TmpReg;
    TmpReg = IRQn;

    if (TmpReg > 32) {
        return (FlagStatus)(*(volatile uint32_t*)(PLIC_IPB + ((TmpReg / 32) * 4)) >> (TmpReg % ((TmpReg / 32) * 32)) & 0x1);
    } else {
        return (FlagStatus)(((*(volatile uint32_t*)PLIC_IPB) >> TmpReg) & 0x1);
    }
}

/**
 * @brief  Enables external interrupt in the PLIC.
 * @param  IRQn: @ref IRQn_TypeDef - device specific interrupt number.
 * @return None.
 */
void PLIC_EnableIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    uint8_t TmpReg;
    TmpReg = IRQn;

    if (TmpReg > 32) {
        (*(volatile uint32_t*)(PLIC_IEB + ((TmpReg / 32) * 4)) |= (1U << (TmpReg % ((TmpReg / 32) * 32))));
    } else {
        *(volatile uint32_t*)(PLIC_IEB) |= (1U << TmpReg);
    }
}

/**
 * @brief  Disables external interrupt in the PLIC.
 * @param  IRQn: @ref IRQn_TypeDef - device specific interrupt number.
 * @return None.
 */
void PLIC_DisableIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    uint8_t TmpReg;
    TmpReg = IRQn;

    if (TmpReg > 32) {
        (*(volatile uint32_t*)(PLIC_IEB + ((TmpReg / 32) * 4)) &= ~(1U << (TmpReg % ((TmpReg / 32) * 32))));
    } else {
        *(volatile uint32_t*)(PLIC_IEB) &= ~(1U << TmpReg);
    }
}

/**
 * @brief  Set threshold level for external interrupts PLIC.
 * @param  Threshold: @ref PLIC_ThresholdIRQ_TypeDef - threshold level.
 * @return None.
 */
void PLIC_SetThresholdIRQ(PLIC_ThresholdIRQ_TypeDef Threshold)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_THRESHOLD_IRQ(Threshold));

    *(volatile uint32_t*)(PLIC_PTHR) = (uint32_t)Threshold;
}

/**
 * @brief  Get threshold level for external interrupts PLIC.
 * @param  None.
 * @return @ref PLIC_ThresholdIRQ_TypeDef - threshold level.
 */
PLIC_ThresholdIRQ_TypeDef PLIC_GetThresholdIRQ(void)
{
    return (PLIC_ThresholdIRQ_TypeDef)(*(volatile uint32_t*)(PLIC_PTHR));
}

/**
 * @brief  Take an external interrupt in the PLIC for processing.
 * @param  None.
 * @return @ref IRQn_TypeDef - device specific interrupt number.
 */
IRQn_TypeDef PLIC_ClaimIRQ(void)
{
    return (IRQn_TypeDef)(*(volatile uint32_t*)(PLIC_ICR));
}

/**
 * @brief  End external interrupt processing in the PLIC.
 * @param  IRQn: @ref IRQn_TypeDef - device specific interrupt number.
 * @return None.
 */
void PLIC_CompleteIRQ(IRQn_TypeDef IRQn)
{
    /* Check the parameters. */
    assert_param(IS_IRQ(IRQn));

    uint8_t TmpReg;
    TmpReg = IRQn;

    *(volatile uint32_t*)(PLIC_ICR) = TmpReg;
}

/**
 * @brief  Set trap vector.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @param  TrapVector: @ref IRQHandler_TypeDef - trap vector.
 * @return None.
 */
void PLIC_SetTrapVector(PLIC_PrivilegeIRQ_TypeDef Privilege, IRQHandler_TypeDef TrapVector)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));
    assert_param(IS_PLIC_xTVEC_ALIGNED(TrapVector));

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            CSR_ClearBits(CSR_MTVEC, CSR_xTVEC_NBASE_Msk);
            CSR_SetBits(CSR_MTVEC, (uint32_t)TrapVector & CSR_xTVEC_NBASE_Msk);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            CSR_ClearBits(CSR_STVEC, CSR_xTVEC_NBASE_Msk);
            CSR_SetBits(CSR_STVEC, (uint32_t)TrapVector & CSR_xTVEC_NBASE_Msk);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            CSR_ClearBits(CSR_UTVEC, CSR_xTVEC_NBASE_Msk);
            CSR_SetBits(CSR_UTVEC, (uint32_t)TrapVector & CSR_xTVEC_NBASE_Msk);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }

#if defined(CORE_EXTENSION_ZIFENCEI)
    rv_fence_i();
#endif
}

/**
 * @brief  Get trap vector.
 * @param  Privilege: @ref PLIC_PrivilegeIRQ_TypeDef - interrupt privilege mode.
 * @return @ref IRQHandler_TypeDef - trap vector.
 */
IRQHandler_TypeDef PLIC_GetTrapVector(PLIC_PrivilegeIRQ_TypeDef Privilege)
{
    /* Check the parameters. */
    assert_param(IS_PLIC_PRIVILEGE_IRQ(Privilege));

    IRQHandler_TypeDef TrapVector = (IRQHandler_TypeDef)0;

    switch (Privilege) {
#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_M:
            TrapVector = (IRQHandler_TypeDef)(CSR_Read(CSR_MTVEC) & CSR_xTVEC_NBASE_Msk);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_MACHINE */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_S:
            TrapVector = (IRQHandler_TypeDef)(CSR_Read(CSR_STVEC) & CSR_xTVEC_NBASE_Msk);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_SUPERVISOR */

#if defined(PLIC_PRIVILEGE_LEVEL) && ((PLIC_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_USER) != 0)
        case PLIC_PRIVILEGE_IRQ_MODE_U:
            TrapVector = (IRQHandler_TypeDef)(CSR_Read(CSR_UTVEC) & CSR_xTVEC_NBASE_Msk);
            break;
#endif /* CORE_PRIVILEGE_LEVEL_USER */
    }

    return TrapVector;
}

/** @} */ /* End of group CORE_PLIC_Exported_Functions */

/** @} */ /* End of group CORE_PLIC */

#endif /* PLIC_PRESENT */

/** @} */ /* End of group CORE_SUPPORT */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_plic.c */

