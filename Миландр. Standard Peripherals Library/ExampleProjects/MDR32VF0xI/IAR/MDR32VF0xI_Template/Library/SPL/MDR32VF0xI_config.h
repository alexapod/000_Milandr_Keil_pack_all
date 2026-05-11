/**
 *******************************************************************************
 * @file    MDR32VF0xI_config.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    14/05/2025
 * @brief   Standard Peripherals Library configuration file.
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

/**
 * @mainpage MDR32VF0xI Standard Peripherals Library.
 * MDR32VF0xI Standard Peripherals Library is a package consisting of
 * all standard peripheral device drivers for MDR32F02 and MDR1206 microcontrollers.
 * This library is a firmware package which contains a collection of routines,
 * data structures and macros covering the features of Milandr MDR32VF0xI
 * peripherals. It includes a description of the device drivers plus a set of
 * examples for each peripheral. The firmware library allows any device to be
 * used in the user application without the need for in-depth study of each
 * peripherals specifications. Using the Standard Peripherals Library has two
 * advantages: it saves significant time that would otherwise be spent in
 * coding, while simultaneously reducing application development and
 * integration costs.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MDR32VF0xI_CONFIG_H
#define MDR32VF0xI_CONFIG_H

#if !defined(__ASSEMBLER__) && !defined(__IASMRISCV__)

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/** MDR32VF0xI SPL version numbers - major, minor, patch. */
#define _MDR32VF0xI_SPL_VERSION_MAJOR ((uint32_t)0) /*!< [23:16] - major version. */
#define _MDR32VF0xI_SPL_VERSION_MINOR ((uint32_t)2) /*!< [15:8]  - minor version. */
#define _MDR32VF0xI_SPL_VERSION_PATCH ((uint32_t)0) /*!< [7:0]   - patch version. */

/** MDR32VF0xI SPL version number (combined value). */
#define MDR32VF0xI_SPL_VERSION ((_MDR32VF0xI_SPL_VERSION_MAJOR << 16) | \
                                (_MDR32VF0xI_SPL_VERSION_MINOR << 8) |  \
                                (_MDR32VF0xI_SPL_VERSION_PATCH))

#endif /* !__ASSEMBLER__ && !__IASMRISCV__ */

/** MCU selection.
    USE_MDR32F02_REV_1X: MDR32F02 rev.1.0 and rev.1.1,
    USE_MDR32F02_REV_2:  MDR32F02 rev.2.0,
    USE_MDR1206FI:       MDR1206FI,
    USE_MDR1206AFI:      MDR1206AFI,
    USE_MDR1206:         MDR1206FI or MDR1206AFI (Proper functions which differ in functionality will be selected according to ID). */
// #define USE_MDR32F02_REV_1X
// #define USE_MDR32F02_REV_2
// #define USE_MDR1206FI
// #define USE_MDR1206AFI
#define USE_MDR1206

#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
#undef USE_MDR32F02
#define USE_MDR32F02
#endif

#if !defined(USE_MDR32F02_REV_1X) && !defined(USE_MDR32F02_REV_2) && !defined(USE_MDR1206FI) && !defined(USE_MDR1206AFI) && !defined(USE_MDR1206)
#error "Microcontroller is not selected in MDR32VF0xI_config.h file."
#endif

#if !defined(__ASSEMBLER__) && !defined(__IASMRISCV__)

/** JTAG pins protection.
    Prevents from changing PORT register bits for pins combined with JTAG function when doing PORT registers read-modify-write.
    Commented: PORT pins combined with JTAG are not protected.
    Uncommented: PORT pins combined with JTAG are protected.
    Default: Uncommented (JTAG pins are protected). */
#define USE_JTAG

/** Protection of factory data (located in FLASH memory for MDR1206(A)FI and in OTP memory for MDR32F02).
    Prevents programming (and erasing for MDR1206(A)FI) of factory data located in the FLASH memory bank. For MDR1206(A)FI the entire page is protected from erasure.
    Commented: Factory data is not protected.
    Uncommented: Factory data is protected.
    Default: Uncommented (factory data is protected). */
#define USE_FACTORY_DATA_PROTECTION

/* Target system parameters. */

/* Clock generators frequencies. */
/** HSI clock value [Hz].
    Default: 8000000 (8MHz). */
#define HSI_FREQUENCY_Hz HSI_CLK_FREQUENCY_TYP_Hz
/** HSE clock value [Hz].
    Default: 8000000 (8MHz). */
#define HSE_FREQUENCY_Hz 8000000UL
/** LSI clock value [Hz].
    Default: 31250 (31.25kHz). */
#define LSI_FREQUENCY_Hz (HSI_FREQUENCY_Hz / 256)
/** LSE clock value [Hz].
    Default: 32768 (32.768kHz). */
#define LSE_FREQUENCY_Hz 32768UL

/* Clock generators mode. */
/** Specify if HSE external generator mode is used.
    Commented: HSE is in oscillator mode (external generator mode is not used).
    Uncommented: HSE is in external generator mode.
    Default: Commented (oscillator mode). */
// #define HSE_EXT_GEN_MODE

/** Specify if LSE external generator mode is used.
    Commented: LSE is in oscillator mode (external generator mode is not used).
    Uncommented: LSE is in external generator mode.
    Default: Commented (oscillator mode). */
// #define LSE_EXT_GEN_MODE

/* Clock frequencies startup timeouts settings. */
/** HSI timeout startup value.
    Default: HSIRDY_TIMEOUT_TICK - hardware startup time in ticks. */
#define HSIRDY_TIMEOUT_TICK HSIRDY_TIMEOUT_HARDWARE_TICK
/** LSI timeout startup value.
    Default: LSIRDY_TIMEOUT_TICK - hardware startup time in ticks. */
#define LSIRDY_TIMEOUT_TICK LSIRDY_TIMEOUT_HARDWARE_TICK

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/** HSE timeout user startup value for MDR1206. The start time will depend on the characteristics of the resonator (parameter values ​​are filled in below).
    Commented: The average startup time used is 5 ms (HSERDY_TIMEOUT_MS) - may be changed.
    Uncommented: The startup time depends on the characteristics of the resonator and is calculated in the RST_CLK_HSE_GetStatus() function.
    Default: Commented. */
// #define HSERDY_USER_TIMEOUT_MS

#if defined(HSERDY_USER_TIMEOUT_MS)
/** QUALITY_FACTOR_HSE - quality factor of a quartz resonator. If there is no data in the specification for the resonator, then take it equal to 50000 - 100000.
    Default: 75000. */
#define QUALITY_FACTOR_HSE 75000UL
/** RM_HSE - dynamic resistance of a quartz resonator (Ohm). The meaning of the representation in the documentation for the resonator.
    Default: 250 - meaning for the KX-7T quartz resonator from Geyer (installed on the Milandr demoboard). */
#define RM_HSE 250UL
/** QUARTZ_FREQUENCY_HSE_Hz - quartz resonator frequency (Hz).
    Default: HSE_FREQUENCY_Hz. */
#define QUARTZ_FREQUENCY_HSE_Hz HSE_FREQUENCY_Hz
/** C_LOAD_HSE - load capacitance of a quartz resonator (F). Specified based on the ratings of the capacitors installed on the board.
    Default: 24e-12 - the meaning of load capacitances on the Milandr demoboard. */
#define C_LOAD_HSE ((float)24e-12f)
/** C_SHUNT_HSE - shunt capacitance of a quartz resonator (F). Cs ≈ С0, where C0 is specified in the resonator specification.
    Default: 3.5e-12 - meaning for the KX-7T quartz resonator from Geyer (installed on the Milandr demoboard). */
#define C_SHUNT_HSE ((float)3.5e-12f)
#else
#define HSERDY_TIMEOUT_MS HSERDY_TIMEOUT_TYP_MS
#endif

#elif defined(USE_MDR32F02)
/** HSE timeout startup value for MDR32F02. The average startup time used is HSERDY_TIMEOUT_MS (5 ms - may be changed).
    Default: HSERDY_TIMEOUT_MS.*/
#define HSERDY_TIMEOUT_MS HSERDY_TIMEOUT_TYP_MS
#endif

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/** LSE timeout user startup value for MDR1206. The start time will depend on the characteristics of the resonator (parameter values ​​are filled in below).
    Commented: The average startup time used is 1000 ms (LSERDY_TIMEOUT_MS) - may be changed.
    Uncommented: The startup time depends on the characteristics of the resonator and is calculated in the BKP_LSE_GetStatus() function.
    Default: Commented. */
// #define LSERDY_USER_TIMEOUT_MS

#if defined(LSERDY_USER_TIMEOUT_MS)
/** QUALITY_FACTOR_LSE - quality factor of a quartz resonator. If there is no data in the specification for the resonator, then take it equal to 50000 - 100000.
    Default: 75000. */
#define QUALITY_FACTOR_LSE 75000UL
/** RM_LSE - dynamic resistance of a quartz resonator (Ohm). The meaning of the representation in the documentation for the resonator.
    Default: 40000 - meaning for the KX-327NHT quartz resonator from Geyer (installed on the Milandr demoboard). */
#define RM_LSE 40000UL
/** QUARTZ_FREQUENCY_LSE_Hz - quartz resonator frequency (Hz).
    Default: LSE_FREQUENCY_Hz. */
#define QUARTZ_FREQUENCY_LSE_Hz LSE_FREQUENCY_Hz
/** C_LOAD_LSE - load capacitance of a quartz resonator (F). Specified based on the ratings of the capacitors installed on the board.
    Default: 12e-12 - the meaning of load capacitances on the Milandr demoboard. */
#define C_LOAD_LSE ((float)12e-12f)
/** C_SHUNT_LSE - shunt capacitance of a quartz resonator (F). Cs ≈ С0, where C0 is specified in the resonator specification.
    Default: 3.5e-12 - meaning for the KX-327NHT quartz resonator from Geyer (installed on the Milandr demoboard). */
#define C_SHUNT_LSE ((float)1.6e-12f)
#else
#define LSERDY_TIMEOUT_MS LSERDY_TIMEOUT_TYP_MS
#endif

#elif defined(USE_MDR32F02)
/** LSE timeout startup value for MDR32F02. The average startup time used is LSERDY_TIMEOUT_MS (1000 ms - may be changed).
    Default: LSERDY_TIMEOUT_MS.*/
#define LSERDY_TIMEOUT_MS LSERDY_TIMEOUT_TYP_MS
#endif

/** PLLCPU timeout startup value for MDR1206 and MDR32F02.
    Default: PLLCPURDY_TIMEOUT_US - hardware startup time in us. */
#define PLLCPURDY_TIMEOUT_US PLLCPURDY_TIMEOUT_HARDWARE_US

/* DMA configuration parameters. */
/** Alternate control data structure usage:
    Commented: DMA alternate channels are not configured and not used in software.
    Uncommented: DMA alternate channels are configured and/or used in software.
    Default: Uncommented (alternate channels are configured and/or used). */
#define DMA_ALTERNATE_DATA

#if !defined(DMA_ALTERNATE_DATA)
/** Number of DMA channels main structure to use.
    Specifies size of structure table for channels in range [0; DMA_CHANNELS_NUMBER-1] where 0 is channel 0.
    Could be changed only if DMA_ALTERNATE_DATA is not defined to reduce RAM usage.
    If DMA_ALTERNATE_DATA is defined, 32 channels for main structure are always used.
    This parameter is in range [1; 32].
    Default: 32 */
#define DMA_CHANNELS_NUMBER 32

#if (DMA_CHANNELS_NUMBER < 1) || (DMA_CHANNELS_NUMBER > 32)
#error "DMA_CHANNELS_NUMBER should be in range [1; 32]."
#endif

#endif

#if defined(DMA_ALTERNATE_DATA)
/** Number of DMA channels alternate structure to use.
    Specifies size of structure table for channels in range [0; 32 + DMA_CHANNELS_NUMBER-1] where 0 is channel 0.
    Could be changed only if DMA_ALTERNATE_DATA is not defined to reduce RAM usage.
    If DMA_ALTERNATE_DATA is defined, 32 channels for main structure are always used.
    This parameter is in range [1; 32].
    Default: 32 */
#define DMA_CHANNELS_NUMBER 32

#if (DMA_CHANNELS_NUMBER < 1) || (DMA_CHANNELS_NUMBER > 32)
#error "DMA_CHANNELS_NUMBER should be in range [1; 32]."
#endif

#endif

#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
/* PLIC configuration parameters. */
/** Initialize PLIC for regarding the removal of a pending request from the DMA in SystemInit() (called before entering main()).
    Commented: PLIC is not initialized;
    Uncommented: PLIC is initialized for regarding the removal of a pending request from the DMA.
    Default: Uncommented (PLIC is initialized). */
#define PLIC_SYSTEM_INIT

#endif

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/* CLIC configuration parameters. */
/** Preemption for non-vectored interrupts in machine mode (Trap_IRQHandler()).
    Commented: Non-vectored interrupts and exceptions in machine mode are executed without preemption.
    Uncommented: Enable preemption for non-vectored interrupts in machine mode, exceptions in machine mode are executed without preemption.
    Default: Commented (without preemption). */
// #define CLIC_TRAP_MACHINE_PREEMPTIBLE

/** Initialize CLIC for all interrupts in SystemInit() (called before entering main()).
    Commented: CLIC is not initialized;
    Uncommented: CLIC is initialized according to the parameters below.
    Default: Uncommented (CLIC is initialized). */
#define CLIC_SYSTEM_INIT

#if defined(CLIC_SYSTEM_INIT)
/** Enable or disable vector mode for interrupts.
    Commented: Disable vector mode for interrupts;
    Uncommented: Enable vector mode for interrupts.
    Default: Uncommented (enable vector mode for interrupts). */
#define CLIC_SYSTEM_INIT_VECTOR_MODE_IRQ
/** Specify the maximum number of interrupt levels:
    CLIC_MAX_LEVELS_1:  1 interrupt level and 16 interrupt priorities;
    CLIC_MAX_LEVELS_2:  2 interrupt levels and 8 interrupt priorities;
    CLIC_MAX_LEVELS_4:  4 interrupt levels and 4 interrupt priorities;
    CLIC_MAX_LEVELS_8:  8 interrupt levels and 2 interrupt priorities;
    CLIC_MAX_LEVELS_16: 16 interrupt levels and 1 interrupt priorities.
    Default: CLIC_MAX_LEVELS_4. */
#define CLIC_SYSTEM_INIT_MAX_LEVELS CLIC_MAX_LEVELS_4
/** Specify the trigger type and polarity for interrupts:
    CLIC_TRIGGER_IRQ_LEVEL_HIGH:   High trigger level;
    CLIC_TRIGGER_IRQ_EDGE_RISING:  Rising edge triggering;
    CLIC_TRIGGER_IRQ_LEVEL_LOW:    Low trigger level;
    CLIC_TRIGGER_IRQ_EDGE_FALLING: Falling edge triggering.
    Default: CLIC_TRIGGER_IRQ_LEVEL_HIGH.
    All peripheral controllers, except DMA, generate high-level interrupts, so it is recommended to use CLIC_TRIGGER_IRQ_LEVEL_HIGH
    or CLIC_TRIGGER_IRQ_EDGE_RISING. For DMA this parameter is forced to CLIC_TRIGGER_IRQ_EDGE_RISING. */
#define CLIC_SYSTEM_INIT_TRIGGER_IRQ CLIC_TRIGGER_IRQ_LEVEL_HIGH
/** Specify available privilege levels for interrupts:
    CLIC_PRIVILEGE_LEVELS_M:  M-mode is available for interrupts;
    CLIC_PRIVILEGE_LEVELS_MU: M-mode and U-mode are available for interrupts.
    Default: CLIC_PRIVILEGE_LEVELS_M. */
#define CLIC_SYSTEM_INIT_PRIVILEGE_LEVELS CLIC_PRIVILEGE_LEVELS_M
/** Specify the privilege mode for interrupts:
    CLIC_PRIVILEGE_MODE_IRQ_M: Interrupts operate in M-mode;
    CLIC_PRIVILEGE_MODE_IRQ_U: Interrupts operate in U-mode.
    Default: CLIC_PRIVILEGE_MODE_IRQ_M. */
#define CLIC_SYSTEM_INIT_PRIVILEGE_MODE_IRQ CLIC_PRIVILEGE_MODE_IRQ_M
#endif
#endif

/* Factory data trim configuration parameters. */
/** Initialize trim values from factory data in SystemInit() (called before entering main()).
    Commented: Trim values are not initialized.
    Uncommented: Trim values are initialized from factory data (for MDR1206(A)FI - initialize to recommended values if factory data CRC does not match).
    Note: Bootloader for MDR1206(A)FI initializes trim values by default.
    Default: Commented (Trim values are not initialized). */
// #define FACTORY_DATA_SYSTEM_INIT

/* Known errors workaround control. */
/** MDR1206(A)FI, MDR1215LGI Errata Notice, MDR32F02 datasheet: BLDO operation error if power rising edge is less 10 us or more 10 ms.
    Commented: Workaround is not applied.
    Uncommented: Workaround is applied in SystemInit() using PVD and BKP.
    Note: Default bootloader for MDR1206(A)FI has build-in implementation of workaround. For MDR1215LGI workaround is not applicable.
    Default: Commented (Workaround is not applied). */
// #define WORKAROUND_ERROR_BLDO_NOT_OPERATED

/* Parameter run-time check support. */
/** Parameter checking level:
    0: No parameter checks ("assert_param" macro is disabled)
    1: Check enabled, source file ID and line number are available
    2: Check enabled, source file ID, line number and checking expression (as string) are available (increased code size)
    Default: 0 ("assert_param" macro is disabled) */
#define USE_ASSERT_INFO 0

/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @note   That function should not return. If expr is true, nothing is done.
 * @param  expr: If expr is false, it calls assert_failed user's function which
 *         reports the name of the source file, source line number
 *         and expression text (if USE_ASSERT_INFO == 2) of the call that failed.
 * @return None.
 */
#if (USE_ASSERT_INFO == 0)
#define assert_param(expr) ((void)0)
#elif (USE_ASSERT_INFO == 1)
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t*)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#elif (USE_ASSERT_INFO == 2)
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t*)__FILE__, __LINE__, (const uint8_t*)#expr))
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr);
#else
#error "Unsupported USE_ASSERT_INFO level."
#endif /* USE_ASSERT_INFO */

// </h>

#if defined(USE_MDR32F02) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#include "system_MDR32VF0xI_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* !__ASSEMBLER__ && !__IASMRISCV__ */

#endif /* MDR32VF0xI_CONFIG_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_config.h */

