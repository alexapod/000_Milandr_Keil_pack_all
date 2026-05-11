/**
 *******************************************************************************
 * @file    link_BOOT.ld
 * @author  Milandr Application Team
 * @version V1.1.0
 * @date    10/04/2025
 * @brief   Linker script file for MDR1206.
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
 * __boot_ram_size
 * __heap_size
 * __stack_size
 */

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

/* __stack_size - total stack size. */
PROVIDE(__stack_size    = 0x0800);
/* __heap_size - total heap size. */
PROVIDE(__heap_size     = 0x0000);
/* __boot_ram_size - size of virtual area, used in common bootloader projects. */
PROVIDE(__boot_ram_size = 0x2000);

/* Specify the memory areas. */
MEMORY
{
    BOOT      (rx)      : ORIGIN = 0x00020000, LENGTH = 15K
    FLASH     (rx)      : ORIGIN = 0x10000000, LENGTH = 512K
    RAM_TCMA  (xrw)     : ORIGIN = 0x40000000, LENGTH = 64K
    RAM_TCMB  (xrw)     : ORIGIN = 0x40010000, LENGTH = 32K
    RAM_AHB   (xrw)     : ORIGIN = 0x20000000, LENGTH = 16K
    /* Virtual area, used in common bootloader project. */
    BOOT_RAM  (xrw)     : ORIGIN = ORIGIN(RAM_TCMB) + LENGTH(RAM_TCMB) - __boot_ram_size, LENGTH = __boot_ram_size
}

/* Description of regions:
- REGION_LOAD       - region where the program is stored,
- REGION_TEXT       - region where the code is located,
- REGION_DATA       - region where initialized and zero-initialized data, stack and heap are located,
- REGION_TEXT_DATA  - region where code, initialized and zero-initialized data are located. */


/* ---------------------- */
/* LOAD AND RUN FROM BOOT */
/* ---------------------- */

REGION_ALIAS("REGION_LOAD",       BOOT);
REGION_ALIAS("REGION_TEXT",       BOOT);
REGION_ALIAS("REGION_DATA",       BOOT_RAM);
REGION_ALIAS("REGION_TEXT_DATA",  BOOT_RAM);


/* ----------------------- */
/* LOAD AND RUN FROM FLASH */
/* ----------------------- */
/*
REGION_ALIAS("REGION_LOAD",       FLASH);
REGION_ALIAS("REGION_TEXT",       FLASH);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_TEXT_DATA",  RAM_TCMB);
*/

/* ------------------------- */
/* LOAD AND RUN FROM RAM TCM */
/* ------------------------- */
/*
REGION_ALIAS("REGION_LOAD",       RAM_TCMA);
REGION_ALIAS("REGION_TEXT",       RAM_TCMA);
REGION_ALIAS("REGION_DATA",       RAM_TCMB);
REGION_ALIAS("REGION_TEXT_DATA",  RAM_TCMA);
*/

/* ------------------------- */
/* LOAD AND RUN FROM RAM AHB */
/* ------------------------- */
/*
REGION_ALIAS("REGION_LOAD",       RAM_AHB);
REGION_ALIAS("REGION_TEXT",       RAM_AHB);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_TEXT_DATA",  RAM_TCMB);
*/

/* ------------------------------------------ */
/* LOAD FROM FLASH TO RAM TCM, RUN IN RAM TCM */
/* ------------------------------------------ */
/*
REGION_ALIAS("REGION_LOAD",       FLASH);
REGION_ALIAS("REGION_TEXT",       RAM_TCMA);
REGION_ALIAS("REGION_DATA",       RAM_TCMB);
REGION_ALIAS("REGION_TEXT_DATA",  RAM_TCMA);
*/

/* ------------------------------------------ */
/* LOAD FROM FLASH TO RAM AHB, RUN IN RAM AHB */
/* ------------------------------------------ */
/*
REGION_ALIAS("REGION_LOAD",       FLASH);
REGION_ALIAS("REGION_TEXT",       RAM_AHB);
REGION_ALIAS("REGION_DATA",       RAM_TCMA);
REGION_ALIAS("REGION_TEXT_DATA",  RAM_TCMB);
*/

/* Description for USER CODE and USER DATA:
- Default area memory for user code: BOOT. For user data: BOOT_RAM. Attention: area memories may be changed.
- Section for user code named ".user_text". For user data named ".user_data".
- Example, a developer wants to place a function at address 0x00022000. The address must be in the REGION_USER_TEXT range, 
definition __user_text_start = 0x00022000 and the function has the following attribute: __attribute__((section(".user_text"))) 
- Example, a developer wants to place a variable at address 0x40017000. The address must be in the REGION_USER_DATA range, 
definition __user_data_start = 0x40017000 and the function has the following attribute: __attribute__((section(".user_data"))) */

/* ----------------------- */
/* USER CODE AND USER DATA */
/* ----------------------- */

PROVIDE(__user_text_start = 0x00022000); 
REGION_ALIAS("REGION_USER_TEXT", BOOT);

PROVIDE(__user_data_start = 0x40017000); 
REGION_ALIAS("REGION_USER_DATA", BOOT_RAM); 

INCLUDE link_MDR1206_common.ld

