/**
 *******************************************************************************
 * @file    core_clint.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    03/04/2025
 * @brief   This file contains all RISC-V CLINT firmware functions.
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
#include "core_clint.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(CLINT_PRESENT)

/** @addtogroup CORE_CLINT CLINT
 * @{
 */

/** @defgroup CLINT_Exported_Functions CLINT Exported Functions
 * @{
 */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_MACHINE) != 0)

/**
 * @brief  Set the machine interrupt request.
 * @param  IRQStatus: @ref ITStatus - set or reset interrupt request.
 * @param  HartIndex: Hart ID number.
 * @return None.
 */
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
void CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus)
#elif defined(HARTS_AMOUNT)
void CLINT_SetSoftwareMachineIRQ(ITStatus IRQStatus, uint32_t HartIndex)
#endif
{
    /* Check the parameters. */
    assert_param(IS_BIT_STATUS(IRQStatus));
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT != 1)
    assert_param(IS_HART_ID(HartIndex));

    CLINT_MSWI->MSIP[HartIndex] = (uint32_t)IRQStatus;
#elif defined(HARTS_AMOUNT)
    CLINT_MSWI->MSIP[0] = (uint32_t)IRQStatus;
#endif
}

/**
 * @brief  Get the machine interrupt request.
 * @param  HartIndex: Hart ID number.
 * @return @ref IRQStatus - current interrupt request status.
 */
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
ITStatus CLINT_GetSoftwareMachineIRQ(void)
#elif defined(HARTS_AMOUNT)
ITStatus CLINT_GetSoftwareMachineIRQ(uint32_t HartIndex)
#endif
{
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT != 1)
    /* Check the parameters. */
    assert_param(IS_HART_ID(HartIndex));

    return (ITStatus)(CLINT_MSWI->MSIP[HartIndex]);
#elif defined(HARTS_AMOUNT)
    return (ITStatus)(CLINT_MSWI->MSIP[0]);
#endif
}

/**
 * @brief  Set a machine timer compare value.
 * @param  HartIndex: Hart ID number.
 * @param  MTIMECMPValue: A new machine timer compare value.
 * @return None.
 */
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
void CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue)
#elif defined(HARTS_AMOUNT)
void CLINT_MTIMER_SetCompareTime(uint64_t MTIMECMPValue, uint32_t HartIndex)
#endif
{
    uint32_t Hart;

#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT != 1)
    /* Check the parameters. */
    assert_param(IS_HART_ID(HartIndex));

    Hart = HartIndex;
#elif defined(HARTS_AMOUNT)
    Hart = 0;
#endif

#if (__riscv_xlen == 32)
    /* Set a new compare value with 2 writes of 32-bit words. */
    /* First set an unachievable value for mtimecmp_hi to prevent spurious interrupts. */
    CLINT_MTIMER_MTIMECMP->MTIMECMP[Hart][1] = 0xFFFFFFFFUL;
    /* Set mtimecmp_lo. */
    CLINT_MTIMER_MTIMECMP->MTIMECMP[Hart][0] = (uint32_t)(MTIMECMPValue & 0xFFFFFFFFUL);
    /* Set correct mtimecmp_hi. */
    CLINT_MTIMER_MTIMECMP->MTIMECMP[Hart][1] = (uint32_t)(MTIMECMPValue >> 32);
#else
    /* Single bus access. */
    CLINT_MTIMER_MTIMECMP->MTIMECMP[Hart] = MTIMECMPValue;
#endif
}

/**
 * @brief  Get machine timer compare value.
 * @param  HartIndex: Hart ID number.
 * @return Machine timer compare value.
 */
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
uint64_t CLINT_MTIMER_GetCompareTime(void)
#elif defined(HARTS_AMOUNT)
uint64_t CLINT_MTIMER_GetCompareTime(uint32_t HartIndex)
#endif
{
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
    return *(volatile uint64_t*)(CLINT_MTIMER_MTIMECMP->MTIMECMP[0]);
#elif defined(HARTS_AMOUNT)
    return *(volatile uint64_t*)(CLINT_MTIMER_MTIMECMP->MTIMECMP[HartIndex]);
#endif
}

/**
 * @brief  Set a machine timer value.
 * @param  MTIMEValue: A new machine timer value.
 * @return None.
 */
void CLINT_MTIMER_SetTime(uint64_t MTIMEValue)
{
#if (__riscv_xlen == 32)
    /* Set a new value with 2 writes of 32-bit words. */
    volatile uint32_t* MTimeLow  = (volatile uint32_t*)(CLINT_BASE + CLINT_MTIMER_MTIME_OFFSET);
    volatile uint32_t* MTimeHigh = (volatile uint32_t*)(CLINT_BASE + CLINT_MTIMER_MTIME_OFFSET + 4);

    *MTimeLow = 0x00000000;
    /* Set mtime_hi. */
    *MTimeHigh = (uint32_t)(MTIMEValue >> 32);
    /* Set mtime_lo. */
    *MTimeLow = (uint32_t)(MTIMEValue & 0xFFFFFFFFUL);
#else
    /* Single bus access. */
    volatile uint64_t* MTime = (volatile uint64_t*)(CLINT_BASE + CLINT_MTIMER_MTIME_OFFSET);
    *MTime                   = MTIMEValue;
#endif
}

/**
 * @brief  Get a machine timer value.
 * @param  None.
 * @return A machine timer value.
 */
uint64_t CLINT_MTIMER_GetTime(void)
{
#if (__riscv_xlen == 32)
    volatile uint32_t* MTimeLow  = (volatile uint32_t*)(CLINT_BASE + CLINT_MTIMER_MTIME_OFFSET);
    volatile uint32_t* MTimeHigh = (volatile uint32_t*)(CLINT_BASE + CLINT_MTIMER_MTIME_OFFSET + 4);
    uint32_t           MTimeHighValue;
    uint32_t           MTimeLowValue;

    /* Safe read of a timer value. */
    do {
        MTimeHighValue = *MTimeHigh;
        MTimeLowValue  = *MTimeLow;
    } while (MTimeHighValue != *MTimeHigh);

    return (uint64_t)((((uint64_t)MTimeHighValue) << 32) | MTimeLowValue);
#else
    /* Single bus access. */
    volatile uint64_t* MTime = (volatile uint64_t*)(CLINT_BASE + CLINT_MTIMER_MTIME_OFFSET);
    return *MTime;
#endif
}

#endif /* CORE_PRIVILEGE_MODE_MACHINE */

#if defined(CORE_PRIVILEGE_LEVEL) && ((CORE_PRIVILEGE_LEVEL & CORE_PRIVILEGE_MODE_SUPERVISOR) != 0)

/**
 * @brief  Set the supervisor interrupt request.
 * @param  IRQStatus: @ref ITStatus - set or reset interrupt request.
 * @param  HartIndex: Hart ID number.
 * @return None.
 */
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
void CLINT_SetSoftwareSupervisorIRQ(ITStatus IRQStatus)
#elif defined(HARTS_AMOUNT)
void CLINT_SetSoftwareSupervisorIRQ(ITStatus IRQStatus, uint32_t HartIndex)
#endif
{
    /* Check the parameters. */
    assert_param(IS_BIT_STATUS(IRQStatus));
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT != 1)
    assert_param(IS_HART_ID(HartIndex));

    CLINT_SSWI->SETSSIP[HartIndex] = (uint32_t)IRQStatus;
#elif defined(HARTS_AMOUNT)
    CLINT_SSWI->SETSSIP[0] = (uint32_t)IRQStatus;
#endif
}

/**
 * @brief  Get the supervisor interrupt request.
 * @param  HartIndex: Hart ID number.
 * @return @ref IRQStatus - current interrupt request status.
 */
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT == 1)
ITStatus CLINT_GetSoftwareSupervisorIRQ(void)
#elif defined(HARTS_AMOUNT)
ITStatus CLINT_GetSoftwareSupervisorIRQ(uint32_t HartIndex)
#endif
{
#if defined(HARTS_AMOUNT) && (HARTS_AMOUNT != 1)
    /* Check the parameters. */
    assert_param(IS_HART_ID(HartIndex));

    return (ITStatus)(CLINT_SSWI->SETSSIP[HartIndex]);
#elif defined(HARTS_AMOUNT)
    return (ITStatus)(CLINT_SSWI->SETSSIP[0]);
#endif
}

#endif /* CORE_PRIVILEGE_MODE_SUPERVISOR */

/** @} */ /* End of the group CLINT_Exported_Functions */

/** @} */ /* End of the group CORE_CLINT */

#endif /* CLINT_PRESENT */

/** @} */ /* End of the group CORE_SUPPORT */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_clint.c */

