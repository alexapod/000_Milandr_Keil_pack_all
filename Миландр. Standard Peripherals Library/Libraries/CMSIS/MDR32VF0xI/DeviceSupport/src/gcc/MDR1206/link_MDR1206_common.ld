/**
 *******************************************************************************
 * @file    link_MDR1206_common.ld
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    24/06/2025
 * @brief   Common part of the linker script file for MDR1206.
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

/* It defines following symbols, which code can use without definition:
 * __flash_start
 * __flash_end
 * __boot_ram_start
 * __boot_ram_end
 * __init_start
 * __init_end
 * __text_load_start
 * __text_start
 * __text_end
 * __data_load_start
 * __data_start
 * __data_end
 * __data_aux_load_start
 * __data_aux_start
 * __data_aux_end
 * __bss_start
 * __bss_end
 * __bss_aux_start
 * __bss_aux_end
 * __ram_bss_start
 * __ram_bss_end
 * __global_pointer$
 * __ram_text_load_start
 * __ram_text_start
 * __ram_text_end
 * __ram_ahb_data_load_start
 * __ram_ahb_data_start
 * __ram_ahb_data_end
 * __ram_ahb_bss_start
 * __ram_ahb_bss_end
 * __ram_ahb_text_load_start
 * __ram_ahb_text_start
 * __ram_ahb_text_end
 * __heap_top
 * __heap_limit
 * end
 * __stack_top
 * __stack_limit
 * __freertos_irq_stack_top
 * __firmware_end
 * __preinit_array_start
 * __preinit_array_end
 * __init_array_start
 * __init_array_end
 * __fini_array_start
 * __fini_array_end
 */

/* Define output sections: */
/* ">vma_region"   - VMA (virtual memory address),
   "AT>lma_region" - LMA (load memory address). */

/* Define symbols for flash memory start and size. */
__flash_start = ORIGIN(FLASH);
__flash_end   = ORIGIN(FLASH) + LENGTH(FLASH);

/* Define symbols for boot RAM memory start and size. */
__boot_ram_start = ORIGIN(BOOT_RAM);
__boot_ram_end   = ORIGIN(BOOT_RAM) + LENGTH(BOOT_RAM);

SECTIONS
{
    /* The .init section contains startup code. */
    .init : ALIGN(4)
    {
        *(.init.header)
        *(.init)
        *(.init.section_table)
        . = ALIGN(4);
    } >REGION_LOAD
    __init_start = ADDR(.init);
    __init_end   = ADDR(.init) + SIZEOF(.init);

    /* The .text section contains program code that is copied from REGION_LOAD to REGION_TEXT in the startup code (if necessary). */
    .text : ALIGN(4)
    {
        *(.text*)
        . = ALIGN(4);
    } >REGION_TEXT AT>REGION_LOAD
    __text_load_start = LOADADDR(.text);
    __text_start      = ADDR(.text);
    __text_end        = ADDR(.text) + SIZEOF(.text);

    /* The .heap section. Doesn't contains any symbols.
       It is only used for linker to calculate size of heap sections, and assign values to heap symbols. */
    .heap : ALIGN(16) { . += __heap_size; } >REGION_DATA
    __heap_top   = ADDR(.heap);
    __heap_limit = ADDR(.heap) + SIZEOF(.heap);
    PROVIDE(end  = __heap_top);

    /* The .stack section. Doesn't contains any symbols.
       It is only used for linker to calculate size of stack sections, and assign values to stack symbols. */
    .stack : ALIGN(16) { . += __stack_size; } >REGION_DATA
    __stack_limit = ADDR(.stack);
    __stack_top   = ADDR(.stack) + SIZEOF(.stack);
    __freertos_irq_stack_top = __stack_top;

    /* The .rodata section contains read-only data. */
    .rodata : ALIGN(4)
    {
        *(.rodata*)
        *(.srodata*)
        . = ALIGN(4);
    } >REGION_TEXT AT >REGION_LOAD
    __rodata_load_start = LOADADDR(.rodata);
    __rodata_start      = ADDR(.rodata);
    __rodata_end        = ADDR(.rodata) + SIZEOF(.rodata);

    /* The .preinit_array section contains function pointers executed before static constructors (early initialization). */
    .preinit_array : {
        HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        HIDDEN (__preinit_array_end = .);
    } >REGION_LOAD

    /* The .init_array section holds static constructor pointers, called before main() (global object initialization). */   
    .init_array : {
        HIDDEN (__init_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        KEEP (*(.init_array))
        HIDDEN (__init_array_end = .);
    } >REGION_LOAD

    /* The .fini_array section holds static destructor pointers, called after main() (global object cleanup). */
    .fini_array : {
        HIDDEN (__fini_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*)))
        KEEP (*(.fini_array))
        HIDDEN (__fini_array_end = .);
    } >REGION_LOAD

    /* The .ram_data section contains zero-initialized data that is initialized in REGION_DATA in the startup code (if necessary). */
    .ram_bss (NOLOAD) : ALIGN(4)
    {
        *(.ram_bss*)
        . = ALIGN(4);
    } >REGION_DATA
    __ram_bss_start = ADDR(.ram_bss);
    __ram_bss_end   = ADDR(.ram_bss) + SIZEOF(.ram_bss);

    /* The .data section contains initialized data that is copied from REGION_LOAD to REGION_DATA in the startup code (if necessary). */
    .data : ALIGN(4)
    {
        *(.ram_data*)
        *(.data*)
        . = ALIGN(4);
        __sdata_start = .;
        *(.sdata*)
        . = ALIGN(4);
    } >REGION_DATA AT>REGION_LOAD
    __data_load_start = LOADADDR(.data);
    __data_start      = ADDR(.data);
    __data_end        = ADDR(.data) + SIZEOF(.data);

    /* The .bss section contains zero-initialized data that is initialized in REGION_DATA in the startup code (if necessary). */
    .bss : ALIGN(4)
    {
        *(.sbss*)
        *(.scommon)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
    } >REGION_DATA
    __bss_start = ADDR(.bss);
    __bss_end   = ADDR(.bss) + SIZEOF(.bss);

    /* The linker uses the __global_pointer$ symbol definition to compare the memory addresses and,
       if within range, it replaces absolute/pc-relative addressing with gp-relative addressing, which makes the code more efficient. */
    __global_pointer$ = MIN(__sdata_start + 0x800, MAX(__data_start + 0x800, __bss_end - 0x800));
    __global_pointer$ = MIN(__global_pointer$, ORIGIN(REGION_DATA) + LENGTH(REGION_DATA) - 0x800);

    /* The .data_aux section contains initialized data that is copied from REGION_LOAD to REGION_TEXT_DATA in the startup code (if necessary). */
    .data_aux : ALIGN(4)
    {
        *(.ram_data*)
        *(.data*)
        *(.sdata*)
        . = ALIGN(4);
    } >REGION_TEXT_DATA AT>REGION_LOAD
    __data_aux_load_start = LOADADDR(.data_aux);
    __data_aux_start      = ADDR(.data_aux);
    __data_aux_end        = ADDR(.data_aux) + SIZEOF(.data_aux);

    /* The .bss_aux section contains zero-initialized data that is initialized in REGION_TEXT_DATA in the startup code (if necessary). */
    .bss_aux (NOLOAD) : ALIGN(4)
    {
        *(.ram_bss*)
        *(.sbss*)
        *(.scommon)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
    } >REGION_TEXT_DATA
    __bss_aux_start = ADDR(.bss_aux);
    __bss_aux_end   = ADDR(.bss_aux) + SIZEOF(.bss_aux);

    /* The .ram_text_gap section separates data and code. */
    .ram_text_gap : { . += 4; } >REGION_LOAD

    /* The .ram_text section contains program code that is copied from REGION_LOAD to REGION_TEXT_DATA in the startup code (if necessary). */
    .ram_text : ALIGN(4)
    {
        *(.ram_text*)
        . = ALIGN(4);
    } >REGION_TEXT_DATA AT>REGION_LOAD
    __ram_text_load_start = LOADADDR(.ram_text);
    __ram_text_start      = ADDR(.ram_text);
    __ram_text_end        = ADDR(.ram_text) + SIZEOF(.ram_text);

    /* The .ram_ahb_data section contains initialized data that is copied from REGION_LOAD to RAM_AHB in the startup code (if necessary). */
    .ram_ahb_data : ALIGN(4)
    {
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.ram_ahb_data*)))
        . = ALIGN(4);
    } >RAM_AHB AT>REGION_LOAD
    __ram_ahb_data_load_start = LOADADDR(.ram_ahb_data);
    __ram_ahb_data_start      = ADDR(.ram_ahb_data);
    __ram_ahb_data_end        = ADDR(.ram_ahb_data) + SIZEOF(.ram_ahb_data);

    /* The .ram_ahb_bss section contains zero-initialized data that is initialized in RAM_AHB in the startup code (if necessary). */
    .ram_ahb_bss (NOLOAD) : ALIGN(4)
    {
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.ram_ahb_bss*)))
        . = ALIGN(4);
    } >RAM_AHB
    __ram_ahb_bss_start = ADDR(.ram_ahb_bss);
    __ram_ahb_bss_end   = ADDR(.ram_ahb_bss) + SIZEOF(.ram_ahb_bss);

    /* The .ram_ahb_text_gap section separates data and code. */
    .ram_ahb_text_gap : { . += 4; } >REGION_LOAD

    /* The .ram_ahb_text section contains program code that is copied from REGION_LOAD to RAM_AHB in the startup code (if necessary). */
    .ram_ahb_text : ALIGN(4)
    {
        *(.ram_ahb_text*)
        . = ALIGN(4);
    } >RAM_AHB AT>REGION_LOAD
    __ram_ahb_text_load_start = LOADADDR(.ram_ahb_text);
    __ram_ahb_text_start      = ADDR(.ram_ahb_text);
    __ram_ahb_text_end        = ADDR(.ram_ahb_text) + SIZEOF(.ram_ahb_text);

    /* Dummy section to get last LMA. */
    __firmware_end = LOADADDR(.trailer);
    .trailer : { KEEP(.trailer*) } >REGION_LOAD

    /* The .user_text section contains user program code. */
    .user_text __user_text_start : ALIGN(4)
    {
        *(.user_text*)
        . = ALIGN(4);
    } >REGION_USER_TEXT

    /* The .user_data section contains user initialized data that is copied from REGION_LOAD to REGION_USER_DATA in the startup code (if necessary). */
    .user_data __user_data_start : ALIGN(4)
    {
        *(.user_data*)
        . = ALIGN(4);
    } >REGION_USER_DATA AT> REGION_LOAD
    __user_data_load_start = LOADADDR(.user_data);
    __user_data_end        = ADDR(.user_data) + SIZEOF(.user_data);

    /* Relocation data sections. */
    .rela.init         0 : { *(.rela.init) }
    .rela.text         0 : { *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*) }
    .rela.rodata       0 : { *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*) }
    .rela.data         0 : { *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*) }
    .rela.sdata        0 : { *(.rela.sdata .rela.sdata.* .rela.gnu.linkonce.s.*) }
    .rela.sbss         0 : { *(.rela.sbss .rela.sbss.* .rela.gnu.linkonce.sb.*) }
    .rela.bss          0 : { *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*) }
    /* Stabs debugging sections. */
    .stab              0 : { *(.stab) }
    .stabstr           0 : { *(.stabstr) }
    .stab.excl         0 : { *(.stab.excl) }
    .stab.exclstr      0 : { *(.stab.exclstr) }
    .stab.index        0 : { *(.stab.index) }
    .stab.indexstr     0 : { *(.stab.indexstr) }
    .comment           0 (INFO) : { *(.comment); LINKER_VERSION; }
    /* DWARF debug sections.
       Symbols in the DWARF debugging sections are relative to the beginning
       of the section so we begin them at 0. */
    /* DWARF 1. */
    .debug             0 : { *(.debug) }
    .line              0 : { *(.line) }
    /* GNU DWARF 1 extensions. */
    .debug_srcinfo     0 : { *(.debug_srcinfo) }
    .debug_sfnames     0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2. */
    .debug_aranges     0 : { *(.debug_aranges) }
    .debug_pubnames    0 : { *(.debug_pubnames) }
    /* DWARF 2. */
    .debug_info        0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev      0 : { *(.debug_abbrev) }
    .debug_line        0 : { *(.debug_line .debug_line.* .debug_line_end) }
    .debug_frame       0 : { *(.debug_frame) }
    .debug_str         0 : { *(.debug_str) }
    .debug_loc         0 : { *(.debug_loc) }
    .debug_macinfo     0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions. */
    .debug_weaknames   0 : { *(.debug_weaknames) }
    .debug_funcnames   0 : { *(.debug_funcnames) }
    .debug_typenames   0 : { *(.debug_typenames) }
    .debug_varnames    0 : { *(.debug_varnames) }
    /* DWARF 3. */
    .debug_pubtypes    0 : { *(.debug_pubtypes) }
    .debug_ranges      0 : { *(.debug_ranges) }
    /* DWARF 5. */
    .debug_addr        0 : { *(.debug_addr) }
    .debug_line_str    0 : { *(.debug_line_str) }
    .debug_loclists    0 : { *(.debug_loclists) }
    .debug_macro       0 : { *(.debug_macro) }
    .debug_names       0 : { *(.debug_names) }
    .debug_rnglists    0 : { *(.debug_rnglists) }
    .debug_str_offsets 0 : { *(.debug_str_offsets) }
    .debug_sup         0 : { *(.debug_sup) }
    .gnu.attributes    0 : { KEEP (*(.gnu.attributes)) }
    .riscv.attributes  0 : { KEEP (*(.riscv.attributes)) }
    /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}

