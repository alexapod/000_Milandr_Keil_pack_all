;/**
; ******************************************************************************
; * @file    startup_MDR32F21QI.S
; * @author  Milandr Application Team
; * @version V1.0.0
; * @date    26/05/2023
; * @brief   CMSIS Device Startup File for MDR32F21QI.
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

;//--------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts - MDR32F21QI Specific
                DCD     DMA_IRQHandler            ; 0:  DMA Handler
                DCD     UART0_IRQHandler          ; 1:  UART0 Handler
                DCD     UART1_IRQHandler          ; 2:  UART1 Handler
                DCD     SSP_IRQHandler            ; 3:  SSP Handler
                DCD     POWER_IRQHandler          ; 4:  Power Detector Handler
                DCD     WWDG_IRQHandler           ; 5:  WWDG Handler
                DCD     TIMER0_IRQHandler         ; 6:  TIMER0 Handler
                DCD     TIMER1_IRQHandler         ; 7:  TIMER1 Handler
                DCD     ADC_IRQHandler            ; 8:  ADC Handler
                DCD     0                         ; 9:  Reserved
                DCD     BKP_RTC_IRQHandler        ; 10: BKP RTC Handler
                DCD     EXT_INT0_IRQHandler       ; 11: EXT_INT0 Handler
                DCD     EXT_INT1_IRQHandler       ; 12: EXT_INT1 Handler
                DCD     EXT_INT2_IRQHandler       ; 13: EXT_INT2 Handler
                DCD     ADCUI_F0_IRQHandler       ; 14: ADCUI_F0 Handler
                DCD     ADCUI_F1_IRQHandler       ; 15: ADCUI_F1 Handler
                DCD     ADCUI_F2_IRQHandler       ; 16: ADCUI_F2 Handler
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)
NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP

HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP

SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP

PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP

SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

; External Interrupts
DMA_IRQHandler  PROC
                EXPORT  DMA_IRQHandler            [WEAK]
                B       .
                ENDP

UART0_IRQHandler\
                PROC
                EXPORT  UART0_IRQHandler          [WEAK]
                B       .
                ENDP

UART1_IRQHandler\
                PROC
                EXPORT  UART1_IRQHandler          [WEAK]
                B       .
                ENDP

SSP_IRQHandler  PROC
                EXPORT  SSP_IRQHandler            [WEAK]
                B       .
                ENDP

POWER_IRQHandler\
                PROC
                EXPORT  POWER_IRQHandler          [WEAK]
                B       .
                ENDP

WWDG_IRQHandler PROC
                EXPORT  WWDG_IRQHandler           [WEAK]
                B       .
                ENDP

TIMER0_IRQHandler\
                PROC
                EXPORT  TIMER0_IRQHandler         [WEAK]
                B       .
                ENDP

TIMER1_IRQHandler\
                PROC
                EXPORT  TIMER1_IRQHandler         [WEAK]
                B       .
                ENDP

ADC_IRQHandler  PROC
                EXPORT  ADC_IRQHandler            [WEAK]
                B       .
                ENDP

BKP_RTC_IRQHandler\
                PROC
                EXPORT  BKP_RTC_IRQHandler        [WEAK]
                B       .
                ENDP

EXT_INT0_IRQHandler\
                PROC
                EXPORT  EXT_INT0_IRQHandler       [WEAK]
                B       .
                ENDP

EXT_INT1_IRQHandler\
                PROC
                EXPORT  EXT_INT1_IRQHandler       [WEAK]
                B       .
                ENDP

EXT_INT2_IRQHandler\
                PROC
                EXPORT  EXT_INT2_IRQHandler       [WEAK]
                B       .
                ENDP

ADCUI_F0_IRQHandler\
                PROC
                EXPORT  ADCUI_F0_IRQHandler       [WEAK]
                B       .
                ENDP

ADCUI_F1_IRQHandler\
                PROC
                EXPORT  ADCUI_F1_IRQHandler       [WEAK]
                B       .
                ENDP

ADCUI_F2_IRQHandler\
                PROC
                EXPORT  ADCUI_F2_IRQHandler       [WEAK]
                B       .
                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap

                LDR     R0, = Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem + Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END

;/*********************** (C) COPYRIGHT 2025 Milandr ****************************
; *
; * END OF FILE startup_MDR32F21QI.S */


