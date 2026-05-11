/**
 *******************************************************************************
 * @file    system_MDR32VF0xI_it.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    14/04/2025
 * @brief   This file contains all the IT firmware functions.
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
#include "system_MDR32VF0xI_it.h"

/** @addtogroup DEVICE_SUPPORT Device Support
 * @{
 */

/** @addtogroup MDR32VF0xI_DEVICE MDR32VF0xI
 *  @{
 */

/** @addtogroup MDR32VF0xI_System_IT MDR32VF0xI System IT
 * @{
 */

/** @addtogroup MDR32VF0xI_System_IT_Exported_IRQ_Handlers_Stubs MDR32VF0xI System IT Exported IRQ Handlers Stubs
 * @{
 */

/**
 * @brief  Stub of machine software interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void MSIP_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of machine timer interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void MTIP_IRQHandler(void)
{
    while (1) { }
}

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief  Stub of user software interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void USIP_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of user timer interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void UTIP_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of CLIC software interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void CSIP_IRQHandler(void)
{
    while (1) { }
}
#endif

/**
 * @brief External Interrupt Handlers.
 */

/**
 * @brief  Stub of DMA interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void DMA_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of UART1 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void UART1_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of UART2 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void UART2_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of SSP1 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void SSP1_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of POWER interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void POWER_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of WWDG interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void WWDG_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of TIMER1 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void TIMER1_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of TIMER2 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void TIMER2_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of ADC interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void ADC_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of I2C interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void I2C_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of BKP interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void BKP_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of EXT_INT1 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void EXT_INT1_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of EXT_INT2 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void EXT_INT2_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of EXT_INT3 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void EXT_INT3_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of ADCUI_F1 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void ADCUI_F1_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of ADCUI_F2 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void ADCUI_F2_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of ADCUI_F03 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void ADCUI_F03_IRQHandler(void)
{
    while (1) { }
}

#if defined(USE_MDR32F02)
/**
 * @brief  Stub of L_BLOCK interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void L_BLOCK_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of SENSORS interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void SENSORS_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of CLK_MEASURE interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void CLK_MEASURE_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of OTP interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void OTP_IRQHandler(void)
{
    while (1) { }
}
#endif

/**
 * @brief  Stub of RANDOM interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void RANDOM_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of UART ISO7816 (USART) interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void USART_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of UART3 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void UART3_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of SSP2 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void SSP2_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of SSP3 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void SSP3_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of TIMER3 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void TIMER3_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of TIMER4 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void TIMER4_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of TIMER4 interrupt handler.
 * @param  None.
 * @return None.
 */
__WEAK void UART4_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: instruction address misaligned.
 * @param  None.
 * @return None.
 */
__WEAK void TrapIAM_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: instruction access fault.
 * @param  None.
 * @return None.
 */
__WEAK void TrapIAF_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: illegal instruction.
 * @param  None.
 * @return None.
 */
__WEAK void TrapII_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: breakpoint (EBREAK).
 * @param  None.
 * @return None.
 */
__WEAK void TrapEBREAK_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: load address misaligned.
 * @param  None.
 * @return None.
 */
__WEAK void TrapLAM_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: load access fault.
 * @param  None.
 * @return None.
 */
__WEAK void TrapLAF_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: store/AMO address misaligned.
 * @param  None.
 * @return None.
 */
__WEAK void TrapSAM_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: store/AMO access fault.
 * @param  None.
 * @return None.
 */
__WEAK void TrapSAF_IRQHandler(void)
{
    while (1) { }
}

/**
 * @brief  Stub of exception handler: environment call from M-mode.
 * @param  None.
 * @return None.
 */
__WEAK void TrapECALLM_IRQHandler(void)
{
    while (1) { }
}

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief  Stub of exception handler: environment call from U-mode.
 * @param  None.
 * @return None.
 */
__WEAK void TrapECALLU_IRQHandler(void)
{
    while (1) { }
}
#endif

/**
 * @brief  Stub of unexpected handler.
 * @param  None.
 * @return None.
 */
__WEAK void Unexpected_IRQHandler(void)
{
    while (1) { }
}

/** @} */ /* End of the group MDR32VF0xI_System_IT_Exported_IRQ_Handlers_Stubs */

/** @addtogroup MDR32VF0xI_System_IT_Exported_Variables MDR32VF0xI System IT Exported Variables
 * @{
 */

/**
 * @brief IT exception vector table.
 */
IRQHandler_TypeDef ExceptionVectorTable[] = {
    TrapIAM_IRQHandler,    // 0:  Instruction address misaligned
    TrapIAF_IRQHandler,    // 1:  Instruction access fault
    TrapII_IRQHandler,     // 2:  Illegal instruction
    TrapEBREAK_IRQHandler, // 3:  Breakpoint (EBREAK)
    TrapLAM_IRQHandler,    // 4:  Load address misaligned
    TrapLAF_IRQHandler,    // 5:  Load access fault
    TrapSAM_IRQHandler,    // 6:  Store address misaligned
    TrapSAF_IRQHandler,    // 7:  Store access fault
    Unexpected_IRQHandler, // 8:  Environment call from U-mode
    Unexpected_IRQHandler, // 9:  Environment call from S-mode
    Unexpected_IRQHandler, // 10: Reserved
    TrapECALLM_IRQHandler, // 11: Environment call from M-mode (ECALL)
    Unexpected_IRQHandler, // 12: Instruction page fault
    Unexpected_IRQHandler, // 13: Load page fault
    Unexpected_IRQHandler, // 14: Reserved
    Unexpected_IRQHandler  // 15: Store page fault
};

/**
 * @brief IT interrupt vector table.
 */
#if defined(USE_MDR32F02)
IRQHandler_TypeDef InterruptVectorTable[] = {
    Unexpected_IRQHandler, // 0: Reserved
    Unexpected_IRQHandler, // 1: Reserved
    Unexpected_IRQHandler, // 2: Reserved
    MSIP_IRQHandler,       // 3: Machine Software Interrupt
    Unexpected_IRQHandler, // 4: Reserved
    Unexpected_IRQHandler, // 5: Reserved
    Unexpected_IRQHandler, // 6: Reserved
    MTIP_IRQHandler        // 7: Machine Timer Interrupt
};
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
__VECTOR_TABLE_ALIGNED IRQHandler_TypeDef InterruptVectorTable[] = {
    USIP_IRQHandler,       // 0:  User Software Interrupt (software request using pending bit)
    Unexpected_IRQHandler, // 1:  Reserved
    Unexpected_IRQHandler, // 2:  Reserved
    MSIP_IRQHandler,       // 3:  Machine Software Interrupt
    UTIP_IRQHandler,       // 4:  User Timer Interrupt
    Unexpected_IRQHandler, // 5:  Reserved
    Unexpected_IRQHandler, // 6:  Reserved
    MTIP_IRQHandler,       // 7:  Machine Timer Interrupt
    Unexpected_IRQHandler, // 8:  Reserved
    Unexpected_IRQHandler, // 9:  Reserved
    Unexpected_IRQHandler, // 10: Reserved
    Unexpected_IRQHandler, // 11: Reserved
    CSIP_IRQHandler,       // 12: CLIC Software Interrupt (software request using pending bit)
    Unexpected_IRQHandler, // 13: Reserved
    Unexpected_IRQHandler, // 14: Reserved
    Unexpected_IRQHandler, // 15: Reserved
    DMA_IRQHandler,        // 16: DMA Handler
    UART1_IRQHandler,      // 17: UART1 Handler
    UART2_IRQHandler,      // 18: UART2 Handler
    SSP1_IRQHandler,       // 19: SSP1 Handler
    POWER_IRQHandler,      // 20: POWER Handler
    WWDG_IRQHandler,       // 21: WWDG Handler
    TIMER1_IRQHandler,     // 22: TIMER1 Handler
    TIMER2_IRQHandler,     // 23: TIMER2 Handler
    ADC_IRQHandler,        // 24: ADC Handler
    I2C_IRQHandler,        // 25: I2C Handler
    BKP_IRQHandler,        // 26: BKP and RTC Handler
    EXT_INT1_IRQHandler,   // 27: EXT_INT1 Handler
    EXT_INT2_IRQHandler,   // 28: EXT_INT2 Handler
    EXT_INT3_IRQHandler,   // 29: EXT_INT3 Handler
    ADCUI_F03_IRQHandler,  // 30: ADCUI_F03 Handler
    ADCUI_F1_IRQHandler,   // 31: ADCUI_F1 Handler
    ADCUI_F2_IRQHandler,   // 32: ADCUI_F2 Handler
    Unexpected_IRQHandler, // 33: Reserved
    Unexpected_IRQHandler, // 34: Reserved
    Unexpected_IRQHandler, // 35: Reserved
    Unexpected_IRQHandler, // 36: Reserved
    RANDOM_IRQHandler,     // 37: RANDOM Handler
    USART_IRQHandler,      // 38: UART ISO7816 (USART) Handler
    UART3_IRQHandler,      // 39: UART3 Handler
    SSP2_IRQHandler,       // 40: SSP2 Handler
    SSP3_IRQHandler,       // 41: SSP3 Handler
    TIMER3_IRQHandler,     // 42: TIMER3 Handler
    TIMER4_IRQHandler,     // 43: TIMER4 Handler
    UART4_IRQHandler       // 44: UART4 Handler
};
#endif

#if defined(USE_MDR32F02)
/**
 * @brief IT external interrupt vector table.
 */
IRQHandler_TypeDef ExtInterruptVectorTable[] = {
    Unexpected_IRQHandler,  // 0:  Unexpected Handler
    DMA_IRQHandler,         // 1:  DMA Handler
    UART1_IRQHandler,       // 2:  UART1 Handler
    UART2_IRQHandler,       // 3:  UART2 Handler
    SSP1_IRQHandler,        // 4:  SSP1 Handler
    POWER_IRQHandler,       // 5:  POWER Handler
    WWDG_IRQHandler,        // 6:  WWDG Handler
    TIMER1_IRQHandler,      // 7:  TIMER1 Handler
    TIMER2_IRQHandler,      // 8:  TIMER2 Handler
    ADC_IRQHandler,         // 9:  ADC Handler
    I2C_IRQHandler,         // 10: I2C Handler
    BKP_IRQHandler,         // 11: BKP Handler
    EXT_INT1_IRQHandler,    // 12: EXT_INT1 Handler
    EXT_INT2_IRQHandler,    // 13: EXT_INT2 Handler
    EXT_INT3_IRQHandler,    // 14: EXT_INT3 Handler
    ADCUI_F03_IRQHandler,   // 15: ADCUI_F03 Handler
    ADCUI_F1_IRQHandler,    // 16: ADCUI_F1 Handler
    ADCUI_F2_IRQHandler,    // 17: ADCUI_F2 Handler
    L_BLOCK_IRQHandler,     // 18: L_BLOCK Handler
    Unexpected_IRQHandler,  // 19: Reserved
    SENSORS_IRQHandler,     // 20: SENSORS Handler
    CLK_MEASURE_IRQHandler, // 21: CLK_MEASURE Handler
    RANDOM_IRQHandler,      // 22: RANDOM Handler
    USART_IRQHandler,       // 23: USART ISO7816 (USART) Handler
    UART3_IRQHandler,       // 24: UART3 Handler
    SSP2_IRQHandler,        // 25: SSP2 Handler
    SSP3_IRQHandler,        // 26: SSP3 Handler
    TIMER3_IRQHandler,      // 27: TIMER3 Handler
    TIMER4_IRQHandler,      // 28: TIMER4 Handler
    UART4_IRQHandler,       // 29: UART4 Handler
    OTP_IRQHandler          // 30: OTP Handler
};
#endif

/** @} */ /* End of the group MDR32VF0xI_System_IT_Exported_Variables */

/** @addtogroup MDR32VF0xI_System_IT_Exported_Trap_Handlers MDR32VF0xI System IT Exported Trap Handlers
 * @{
 */

#if defined(USE_MDR32F02)
/**
 * @brief  PLIC service routine for interrupts and exceptions.
 * @param  None.
 * @return None.
 */
__WEAK __RAM_TEXT __INTERRUPT_MACHINE __TRAP_HANDLER_ALIGNED void Trap_IRQHandler(void)
{
    IRQn_TypeDef ExtInterrupt;
    uint32_t     MCause;

    MCause = CSR_Read(CSR_MCAUSE);
    if ((MCause & CSR_MCAUSE_INTERRUPT) != 0) {
        if (MCause == (CSR_MCAUSE_EXCCODE_MEI | CSR_MCAUSE_INTERRUPT)) {
            ExtInterrupt = PLIC_ClaimIRQ();
            while (ExtInterrupt) {
                if (ExtInterrupt == DMA_IRQn) {
                    PLIC_CompleteIRQ(ExtInterrupt);
                }
                ExtInterruptVectorTable[(uint32_t)ExtInterrupt]();
                if (ExtInterrupt != DMA_IRQn) {
                    PLIC_CompleteIRQ(ExtInterrupt);
                }
                ExtInterrupt = PLIC_ClaimIRQ();
            }
        } else {
            InterruptVectorTable[MCause & CSR_MCAUSE_EXCCODE_Msk]();
        }
    } else {
        ExceptionVectorTable[MCause]();
    }
}

#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#if defined(CLIC_TRAP_MACHINE_PREEMPTIBLE)
/**
 * @brief   CLIC service routine for non-vectored interrupts and exceptions.
 *          Non-vectored interrupts are executed with preemption, exceptions are executed without preemption.
 * @warning Only safe for horizontal interrupts.
 * @param   None.
 * @return  None.
 */
__WEAK __RAM_TEXT __INTERRUPT_MACHINE __TRAP_HANDLER_ALIGNED void Trap_IRQHandler(void)
{
    uint32_t            MCause, MEpc;
    IRQHandler_TypeDef* IT_IRQHandler;

    MCause = CSR_Read(CSR_MCAUSE);
    if ((MCause & CSR_MCAUSE_INTERRUPT) != 0) {
        MEpc          = CSR_Read(CSR_MCAUSE);
        IT_IRQHandler = (IRQHandler_TypeDef*)CSR_ReadSetBits(CSR_MNXTI, CSR_MSTATUS_MIE);
        while (IT_IRQHandler) {
            (*IT_IRQHandler)();
            IT_IRQHandler = (IRQHandler_TypeDef*)CSR_ReadSetBits(CSR_MNXTI, CSR_MSTATUS_MIE);
        }
        CSR_ClearBits(CSR_MSTATUS, CSR_MSTATUS_MIE);
        CSR_Write(CSR_MEPC, MEpc);
        CSR_Write(CSR_MCAUSE, MCause);
    } else {
        ExceptionVectorTable[MCause & CSR_MCAUSE_EXCCODE_Msk]();
    }
}
#else
/**
 * @brief  CLIC service routine for non-vectored interrupts and exceptions without preemption.
 * @param  None.
 * @return None.
 */
__WEAK __RAM_TEXT __INTERRUPT_MACHINE __TRAP_HANDLER_ALIGNED void Trap_IRQHandler(void)
{
    uint32_t            MCause;
    IRQHandler_TypeDef* IT_IRQHandler;

    MCause = CSR_Read(CSR_MCAUSE);
    if ((MCause & CSR_MCAUSE_INTERRUPT) != 0) {
        IT_IRQHandler = (IRQHandler_TypeDef*)CSR_ReadClearBits(CSR_MNXTI, CSR_MSTATUS_MIE);
        while (IT_IRQHandler) {
            (*IT_IRQHandler)();
            IT_IRQHandler = (IRQHandler_TypeDef*)CSR_ReadClearBits(CSR_MNXTI, CSR_MSTATUS_MIE);
        }
    } else {
        ExceptionVectorTable[MCause & CSR_MCAUSE_EXCCODE_Msk]();
    }
}
#endif
#endif

/** @} */ /* End of the group MDR32VF0xI_System_IT_Exported_Trap_Handlers */

/** @addtogroup MDR32VF0xI_System_IT_Exported_Functions MDR32VF0xI System IT Exported Functions
 * @{
 */

#if defined(USE_MDR32F02)
/**
 * @brief  Global enable interrupt for machine privilege mode.
 * @param  None.
 * @return None.
 */
void IT_GlobalEnableIRQ(void)
{
    CSR_SetBits(CSR_MSTATUS, CSR_MSTATUS_MIE);
}

/**
 * @brief  Global disable interrupt for machine privilege mode.
 * @param  None.
 * @return None.
 */
void IT_GlobalDisableIRQ(void)
{
    CSR_ClearBits(CSR_MSTATUS, CSR_MSTATUS_MIE);
}

/**
 * @brief  Get the global enable interrupt status for machine privilege mode.
 * @param  None.
 * @return Global enable interrupt status for machine privilege mode.
 */
FlagStatus IT_GetGlobalEnableIRQ(void)
{
    FlagStatus Status;
    uint32_t   MStatus;

    MStatus = CSR_Read(CSR_MSTATUS);

    if (MStatus & CSR_MSTATUS_MIE) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief  Global enable interrupt for specified interrupt privilege mode.
 * @param  PrivilegeModeIRQ: @ref IT_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void IT_GlobalEnableIRQ(IT_PrivilegeModeIRQ_TypeDef PrivilegeModeIRQ)
{
    /* Check the parameters. */
    assert_param(IS_IT_PRIVILEGE_MODE_IRQ(PrivilegeModeIRQ));

    if (PrivilegeModeIRQ == IT_PRIVILEGE_MODE_IRQ_M) {
        CSR_SetBits(CSR_MSTATUS, CSR_MSTATUS_MIE);
    } else { /* (PrivilegeModeIRQ == IT_PRIVILEGE_MODE_IRQ_U) */
        CSR_SetBits(CSR_USTATUS, CSR_MSTATUS_UIE);
    }
}

/**
 * @brief  Global disable interrupt for specified interrupt privilege mode.
 * @param  PrivilegeModeIRQ: @ref IT_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @return None.
 */
void IT_GlobalDisableIRQ(IT_PrivilegeModeIRQ_TypeDef PrivilegeModeIRQ)
{
    /* Check the parameters. */
    assert_param(IS_IT_PRIVILEGE_MODE_IRQ(PrivilegeModeIRQ));

    if (PrivilegeModeIRQ == IT_PRIVILEGE_MODE_IRQ_M) {
        CSR_ClearBits(CSR_MSTATUS, CSR_MSTATUS_MIE);
    } else { /* (PrivilegeModeIRQ == IT_PRIVILEGE_MODE_IRQ_U) */
        CSR_ClearBits(CSR_USTATUS, CSR_USTATUS_UIE);
    }
}

/**
 * @brief  Get the global enable interrupt status for specified interrupt privilege mode.
 * @param  PrivilegeModeIRQ: @ref IT_PrivilegeModeIRQ_TypeDef - interrupt privilege mode.
 * @return Global enable interrupt status for specified interrupt privilege mode.
 */
FlagStatus IT_GetGlobalEnableIRQ(IT_PrivilegeModeIRQ_TypeDef PrivilegeModeIRQ)
{
    FlagStatus Status;
    uint32_t   xStatus = 0, xIE = 0;

    /* Check the parameters. */
    assert_param(IS_IT_PRIVILEGE_MODE_IRQ(PrivilegeModeIRQ));

    if (PrivilegeModeIRQ == IT_PRIVILEGE_MODE_IRQ_M) {
        xStatus = CSR_Read(CSR_MSTATUS);
        xIE     = CSR_MSTATUS_MIE;
    } else { /* (PrivilegeModeIRQ == IT_PRIVILEGE_MODE_IRQ_U) */
        xStatus = CSR_Read(CSR_USTATUS);
        xIE     = CSR_USTATUS_UIE;
    }

    if (xStatus & xIE) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}
#endif

/** @} */ /* End of the group MDR32VF0xI_System_IT_Exported_Functions */

/** @} */ /* End of the group MDR32VF0xI_System_IT */

/** @} */ /* End of the group MDR32VF0xI_DEVICE */

/** @} */ /* End of the group DEVICE_SUPPORT */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE system_MDR32VF0xI_it.c */

