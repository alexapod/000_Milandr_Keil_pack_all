/**
 *******************************************************************************
 * @file    startup_MDR1206.S
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    24/06/2025
 * @brief   Core device startup file for MDR1206.
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

#if defined ( __GNUC__ ) /* GCC compiler. */

#include "system_MDR32VF0xI_config.h"

#if defined (USE_MDR1206FI) || defined (USE_MDR1206AFI) || defined (USE_MDR1206) /* MCU definition. */

#if (__riscv_xlen == 64)
    #define LREG           ld
    #define SREG           sd
    #define REGBYTES       8
    #define LOG2_REGBYTES  3
    #define XWORD          .dword
#else
    #define LREG           lw
    #define SREG           sw
    #define REGBYTES       4
    #define LOG2_REGBYTES  2
    #define XWORD          .word
#endif

.section .init
.globl _start

_start:
//    /* Only first hart runs. */
//    csrr s10, mhartid
//    beqz s10, 1f
//    j .
//1:

    /* Zeroing registers. */
    li  x1, 0
    li  x2, 0
    li  x3, 0
    li  x4, 0
    li  x5, 0
    li  x6, 0
    li  x7, 0
    li  x8, 0
    li  x9, 0
    li  x10,0
    li  x11,0
    li  x12,0
    li  x13,0
    li  x14,0
    li  x15,0
    li  x16,0
    li  x17,0
    li  x18,0
    li  x19,0
    li  x20,0
    li  x21,0
    li  x22,0
    li  x23,0
    li  x24,0
    li  x25,0
    li  x26,0
    li  x27,0
    li  x28,0
    li  x29,0
    li  x30,0
    li  x31,0

    /* Global pointer (gp) allows using more effective gp-relative addressing instead of
       abosulte/pc-relative for arbitrary 4KiB memory range. For the optimisation to be effective,
       it should cover the most intensely used RAM area. For standard newlib apps, this is the
       area where the .sdata section is located. The linker uses the (!) __global_pointer$ symbol
       definition to compare the memory addresses and, if within range, it replaces
       absolute/pc-relative addressing with gp-relative addressing, which makes the code more
       efficient. This process is also called relaxing, and can be disabled by -Wl,--no-relax.
       The gp register should be loaded during startup and should not be changed later. */
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    /* Set stack pointer. */
    la sp, __stack_top

    /* Copy text and data to RAM. */
    la a3, __table_text_data_load_start
    la a4, __table_text_data_start
    la a5, __table_text_data_end
    mv a6, a4
1:
    LREG a0, (a3)
    LREG a1, (a4)
    beq  a0, a1, 3f
    LREG a2, (a5)
    bgeu a1, a2, 3f
2:
    LREG t0, (a0)
    SREG t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 2b
3:
    addi a3, a3, 4
    addi a4, a4, 4
    addi a5, a5, 4
    bne  a3, a6, 1b

    /* Zeroing bss. */
    la a2, __table_bss_start
    la a3, __table_bss_end
    mv a4, a3
1:
    LREG a0, (a2)
    LREG a1, (a3)
    bgeu a0, a1, 3f
2:
    SREG zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 2b
3:
    addi a2, a2, 4
    addi a3, a3, 4
    bne  a2, a4, 1b

    /* Call static constructors. */
    call __libc_init_array

    /* Call system initialization. */
    call SystemInit

    /* Call main. */
    call main

    /* Call static destructors. */
    call __libc_fini_array

    /* Get main return code and stop. */
    mv t0, a0
    j .

.section .init.section_table, "a"
.align REGBYTES
__table_text_data_load_start:
    XWORD __text_load_start
    XWORD __data_load_start
    XWORD __data_aux_load_start
    XWORD __ram_text_load_start
    XWORD __ram_ahb_text_load_start
    XWORD __ram_ahb_data_load_start
    XWORD __rodata_load_start
    XWORD __user_data_load_start

__table_text_data_start:
    XWORD __text_start
    XWORD __data_start
    XWORD __data_aux_start
    XWORD __ram_text_start
    XWORD __ram_ahb_text_start
    XWORD __ram_ahb_data_start
    XWORD __rodata_start
    XWORD __user_data_start

__table_text_data_end:
    XWORD __text_end
    XWORD __data_end
    XWORD __data_aux_end
    XWORD __ram_text_end
    XWORD __ram_ahb_text_end
    XWORD __ram_ahb_data_end
    XWORD __rodata_end
    XWORD __user_data_end

__table_bss_start:
    XWORD __bss_start
    XWORD __bss_aux_start
    XWORD __ram_bss_start
    XWORD __ram_ahb_bss_start

__table_bss_end:
    XWORD __bss_end
    XWORD __bss_aux_end
    XWORD __ram_bss_end
    XWORD __ram_ahb_bss_end

#endif /* USE_MDR1206FI || USE_MDR1206AFI || USE_MDR1206 */
#endif /* __GNUC__ */


