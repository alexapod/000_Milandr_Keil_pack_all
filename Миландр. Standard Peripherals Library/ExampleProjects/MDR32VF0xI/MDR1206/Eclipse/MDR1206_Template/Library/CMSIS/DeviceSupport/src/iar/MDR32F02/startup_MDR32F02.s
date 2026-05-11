/**
 *******************************************************************************
 * @file    startup_MDR32F02.s
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    15/04/2025
 * @brief   Core device startup file for MDR32F02.
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

#if defined (__IASMRISCV__) /* IAR RISCV compiler. */

#include "iarMacros.m"
#include "iarCfi.m"

#include "system_MDR32VF0xI_config.h"

#if defined (USE_MDR32F02) /* MCU definition. */

        MODULE  ?cstartup

        PUBWEAK  __iar_program_start

        SECTION CSTACK:DATA:NOROOT(4)

        SECTION `.cstartup`:CODE:NOROOT(2)
        CfiCom  ra,1,0
        CfiCom  ra,1,1
        CfiCom  ra,1,2
        CfiCom  ra,1,3

        CfiBlk 0,__iar_program_start
        CALL_GRAPH_ROOT __iar_program_start, "Reset"
        CODE

__iar_program_start:
        REQUIRE ?cstart_init_sp
        cfi ?RET Undefined
        nop                    // Avoid an empty section.
        CfiEnd  0

// Init gp (required in by the linker config file, if applicable).
        SECTION `.cstartup`:CODE:NOROOT(1)
        CfiBlk 1,__iar_program_start
        CODE
        PUBLIC __iar_cstart_init_gp
__iar_cstart_init_gp:
        cfi ?RET Undefined
        EXTERN  __iar_static_base$$GPREL
        .option push
        .option norelax
        la      gp, __iar_static_base$$GPREL
        .option pop
        REQUIRE ?cstart_init_sp

        CfiEnd  1

/* Init sp, note that this MAY be gp relaxed! (since if gp relaxations
   are allowed, __iar_cstart_init_gp is already done. */
        SECTION `.cstartup`:CODE:NOROOT(1)
        REQUIRE call_low_level_init
        CfiBlk 2,__iar_program_start
        CODE
?cstart_init_sp:
        cfi ?RET Undefined
        la      a0, SFE(CSTACK)
        andi    sp, a0, -16

        CfiEnd  2

        SECTION `.cstartup`:CODE:NOROOT(1)
        CfiBlk 3,__iar_program_start
        CODE
        EXTERN  __low_level_init
        EXTERN  __iar_data_init2
call_low_level_init:
        cfi ?RET Undefined
        CfiCall __low_level_init
        call    __low_level_init
        beq     a0, zero, ?cstart_call_main

        CfiCall __iar_data_init2
        call    __iar_data_init2

?cstart_call_main:
        EXTERN  SystemInit
        CfiCall SystemInit
        call    SystemInit

        EXTERN  main
        CfiCall main
        call    main
        j       $
        CfiEnd  3

        END

#endif /* USE_MDR1206FI || USE_MDR1206AFI || USE_MDR1206 */
#endif /* __IASMRISCV__ */


