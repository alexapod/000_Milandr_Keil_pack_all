/**
 *******************************************************************************
 * @file    MDR32VF0xI_asm.S
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    10/04/2025
 * @brief   This file contains assembler functions.
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

#if defined ( __IASMRISCV__ ) /* IAR RISCV compiler. */
    SECTION `.ram_text`:CODE:NOROOT(2)
#endif

;/**
;  * @brief   Perform a blocking program delay in loops.
;  * @note    Register a0 is not stored on the stack because it is non preserved register (saved by caller).
;  * @param   Loops: Specify the delay time in loops.
;  * @return  None.
;  */
#if defined ( __GNUC__ ) /* GCC compiler. */
    .section .ram_text.DELAY_PROGRAM_WaitLoopsAsm, "ax"
    .type DELAY_PROGRAM_WaitLoopsAsm, @function
    .globl DELAY_PROGRAM_WaitLoopsAsm
#elif defined ( __IASMRISCV__ )  /* IAR RISCV compiler. */
    PUBLIC DELAY_PROGRAM_WaitLoopsAsm
#endif
DELAY_PROGRAM_WaitLoopsAsm:
    beqz a0, DELAY_PROGRAM_Exit
DELAY_PROGRAM_Loop:
    addi a0, a0, -1
    bnez a0, DELAY_PROGRAM_Loop
DELAY_PROGRAM_Exit:
    ret

;/**
;  * @brief   Perform a blocking delay with a cycle counter, in ticks.
;  * @note    Registers a0-a2 are not stored on the stack because it is non preserved register (saved by caller).
;  * @param   Ticks: Specify the delay time in ticks.
;  * @return  None.
;  */
#if defined ( __GNUC__ ) /* GCC compiler. */
    .section .ram_text.DELAY_CycleCounter_WaitTicksAsm, "ax"
    .type DELAY_CycleCounter_WaitTicksAsm, @function
    .globl DELAY_CycleCounter_WaitTicksAsm
#elif defined ( __IASMRISCV__ )  /* IAR RISCV compiler. */
    PUBLIC DELAY_CycleCounter_WaitTicksAsm
#endif
DELAY_CycleCounter_WaitTicksAsm:
    rdcycle a1
DELAY_CycleCounter_Loop:
    rdcycle a2
    sub     a2, a2, a1
    bltu    a2, a0, DELAY_CycleCounter_Loop
    ret

#if defined ( __IASMRISCV__ )  /* IAR RISCV compiler. */
    END
#endif


