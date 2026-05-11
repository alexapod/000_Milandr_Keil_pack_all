;/**
; ******************************************************************************
; * @file    MDR32F9Qx_asm.S
; * @author  Milandr Application Team
; * @version V1.0.0
; * @date    18/05/2022
; * @brief   This file contains assembler functions.
; ******************************************************************************
; * <br><br>
; *
; * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
; * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
; * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
; * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
; * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
; * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
; *
; * <h2><center>&copy; COPYRIGHT 2025 Milandr</center></h2>
; ******************************************************************************
; */

#if defined ( __CC_ARM ) || (( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )) /* Arm Compiler 4/5 || Arm Compiler 6 */
        #define CODESECT        AREA    |EXECUTABLE_MEMORY_SECTION|, CODE, READONLY, ALIGN=2
        #define CODESECT_TYPE

#elif defined ( __IASMARM__ )  /* IAR */
        #define SHT_PROGBITS    0x1
        #define SHF_WRITE       0x1
        #define SHF_EXECINSTR   0x4

        #define CODESECT        SECTION .textrw:CODE:NOROOT(2)
        #define CODESECT_TYPE   SECTION_TYPE SHT_PROGBITS, SHF_WRITE | SHF_EXECINSTR
        #define ALIGN           ALIGNRAM 2
        #define PROC
        #define ENDP
        #define EXPORT          PUBLIC
#endif

        CODESECT
        CODESECT_TYPE
        THUMB

;/**
;  * @brief   Performs a blocking program delay in loops.
;  * @note    Register r0 is not stored on the stack because it is non preserved register.
;  * @param   Loops: specifies the delay time in loops.
;  * @retval  None.
;  */
DELAY_PROGRAM_WaitLoopsAsm\
        PROC
        EXPORT  DELAY_PROGRAM_WaitLoopsAsm

        CMP   r0,#0x00
        BEQ   DELAY_PROGRAM_Exit

DELAY_PROGRAM_Loop
        SUBS  r0,r0,#1
        BNE   DELAY_PROGRAM_Loop

DELAY_PROGRAM_Exit
        BX    LR
        ENDP

        END


