/**
 *******************************************************************************
 * @file    MDR32F2xQI_config.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
 * @brief   Library configuration file.
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
 * @mainpage MDR32F2xQI Standard Peripherals Library.
 * MDR32F2xQI Standard Peripherals Library is a package consisting of
 * all standard peripheral device drivers for MDR32F21QI, MDR32F23QI
 * microcontrollers.
 * This library is a firmware package which contains a collection of routines,
 * data structures and macros covering the features of Milandr MDR32F2xQI
 * peripherals. It includes a description of the device drivers plus a set of
 * examples for each peripheral. The firmware library allows any device to be
 * used in the user application without the need for in-depth study of each
 * peripherals specifications. Using the Standard Peripherals Library has two
 * advantages: it saves significant time that would otherwise be spent in
 * coding, while simultaneously reducing application development and
 * integration costs.
 *
 * The MDR32F2xQI Standard Peripherals Library is full CMSIS compliant.
 */

// <<< Use Configuration Wizard in Context Menu >>>

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32F2xQI_CONFIG_H
#define __MDR32F2xQI_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include <RTE_Components.h> // Keil uVision specific inclusion
#include <stdint.h>

/* MDR32F2xQI SPL version numbers - major, minor, patch */
#define _MDR32F2xQI_SPL_VERSION_MAJOR (1U) /*!< [23:16] major version */
#define _MDR32F2xQI_SPL_VERSION_MINOR (0U) /*!< [15:8]  minor version */
#define _MDR32F2xQI_SPL_VERSION_PATCH (0U) /*!< [7:0]   patch version */

/* MDR32F2xQI SPL version number (combined value) */
#define MDR32F2xQI_SPL_VERSION ((_MDR32F2xQI_SPL_VERSION_MAJOR << 16) | \
                                (_MDR32F2xQI_SPL_VERSION_MINOR << 8) |  \
                                (_MDR32F2xQI_SPL_VERSION_PATCH))

/* Uncomment the line corresponding to the target microcontroller */
/* When using Keil uVision, the definition is set automatically
   (when RTE_Components.h included) according to the selected
   microcontroller in "Options for Target->Device" window.*/

// #define USE_MDR32F21QI
// #define USE_MDR32F23QI

/* Select the header file for target microcontroller */
#if defined(USE_MDR32F21QI)
#include "MDR32F21QI.h"
#elif defined(USE_MDR32F23QI)
#include "MDR32F23QI.h"
#else
#error "Microcontroller not selected in MDR32F2xQI_config.h file"
#endif

// <c3> SWD pins protection
// <i> Prevents from setting PORT register bits for pins cpmbined with SWD function when doing PORT register read-modify-write.
// <i> Uncomment the definition below to define used SWD port. Uncommented by default.
// <i> Leave all commented/unchecked if there is no need to protect PORT pins combined with SWD.
#define USE_SWD
// </c>

// <h> Target system parameters
// <h> Clock generators frequencies
// <o> HSI clock value [Hz]
// <i> Default: 8000000 (8MHz)
#define HSI_FREQUENCY_Hz ((uint32_t)8000000)
// <o> HSE clock value [Hz]
// <i> Default: 8000000 (8MHz)
#define HSE_FREQUENCY_Hz ((uint32_t)8000000)
// <o> LSI clock value [Hz]
// <i> Default: 40000 (40kHz)
#define LSI_FREQUENCY_Hz ((uint32_t)40000)
// <o> LSE clock value [Hz]
// <i> Default: 32768 (32.768kHz)
#define LSE_FREQUENCY_Hz ((uint32_t)32768)
// </h>

// <h> Clock frequencies startup timeouts settings
// <o> HSI timeout startup value
// <i> Default: 0x0600
#define HSIRDY_TIMEOUT_TICK ((uint16_t)0x0600)
// <o> HSE timeout startup value
// <i> Default: 0x0600
#define HSERDY_TIMEOUT_TICK ((uint16_t)0x0600)
// <o> LSI timeout startup value
// <i> Default: 0x0600
#define LSIRDY_TIMEOUT_TICK ((uint16_t)0x0600)
// <o> LSE timeout startup value
// <i> Default: 0x0600
#define LSERDY_TIMEOUT_TICK ((uint16_t)0x0600)
// <o> PLLCPU timeout startup value
// <i> Default: 0x0600
#define PLLCPURDY_TIMEOUT_TICK ((uint16_t)0x0600)
// </h>

#if defined(USE_MDR32F21QI)
// <h> DMA configuration parameters

// <o> Alternate Control Data Structure Usage
//   <0=> 0: DMA_ALTERNATE_DATA_DISABLED
//   <1=> 1: DMA_ALTERNATE_DATA_ENABLED
// <i> Default: 1 (DMA_ALTERNATE_DATA_ENABLED)
#define DMA_ALTERNATE_DATA 1

#if (DMA_ALTERNATE_DATA != 0) && (DMA_ALTERNATE_DATA != 1)
#error "DMA_ALTERNATE_DATA  should be 0 (DMA_ALTERNATE_DATA_DISABLED) or 1 (DMA_ALTERNATE_DATA_ENABLED)"
#endif

#if (DMA_ALTERNATE_DATA == 0)
// <o.0..5> Number of DMA channels to use.
// <i> Specifies size of structure table for channels in range [0; DMA_CHANNELS_NUMBER-1] where 0 is channel 0.
// <i> Could be changed only if DMA_ALTERNATE_DATA = 0 to reduce RAM usage.
// <i> If DMA_ALTERNATE_DATA = 1, 32 channels are always used.
// <i> This parameter is in range [1; 32]
// <i> Default: 32
#define DMA_CHANNELS_NUMBER 32

#if (DMA_CHANNELS_NUMBER < 1) || (DMA_CHANNELS_NUMBER > 32)
#error "DMA_CHANNELS_NUMBER should be in range [1; 32]"
#endif

#endif

// </h>
#endif

// <h> Retarget standard input/output (STDIO)

// <o> Select retarget STDIN and STDOUT
//   <0=> 0: Retarget STDIO disabled
//   <1=> 1: Retarget STDIO via UART
// <i> Default: 0 (Retarget STDIO disabled)
#define USE_STDIO_RETARGET 0

#if (USE_STDIO_RETARGET == 1)
#define STDIO_UART             MDR_UART0
#define STDIO_UART_BAUD_RATE   115200
#define STDIO_UART_WORD_LENGTH UART_WORD_LENGTH_8BIT
#define STDIO_UART_STOP_BITS   UART_STOP_BITS_1BIT
#define STDIO_UART_PARITY      UART_PARITY_NONE
#define STDIO_UART_CLK_SRC     RST_CLK_PER1_C2_CLK_SRC_PLLCPU
#elif (USE_STDIO_RETARGET != 0)
#error "Unsupported USE_STDIO_RETARGET paramater"
#endif /* USE_STDIO_RETARGET */

// </h>

// <h> Parameter run-time check support

// <o> Paramater checking level
//   <0=> 0: no parameter checks ("assert_param" macro is disabled)
//   <1=> 1: check enabled, source file ID and line number are available
//   <2=> 2: check enabled, source file ID, line number and checking expression (as string) are available (increased code size)
// <i> Default: 0 ("assert_param" macro is disabled)
#define USE_ASSERT_INFO 0

/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr: If expr is false, it calls assert_failed user's function which
 *         reports the name of the source file, source line number
 *         and expression text (if USE_ASSERT_INFO == 2) of the call that failed.
 *         That function should not return. If expr is true, nothing is done.
 * @retval None
 */
#if (USE_ASSERT_INFO == 0)
#define assert_param(expr) ((void)0U)
#elif (USE_ASSERT_INFO == 1)
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t*)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#elif (USE_ASSERT_INFO == 2)
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t*)__FILE__, __LINE__, (const uint8_t*)#expr))
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr);
#else
#error "Unsupported USE_ASSERT_INFO level"
#endif /* USE_ASSERT_INFO */

// </h>

#if defined(__ICCARM__) /* IAR Compiler */
#define __attribute__(name_section)
#define __RAMFUNC __ramfunc
#endif
#if defined(__CMCARM__) /* Phyton CMC-ARM Compiler */
#define __attribute__(name_section)
#define __RAMFUNC __ramfunc
#endif
#if defined(__ARMCC_VERSION) /* ARM Compiler */
#define __RAMFUNC
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MDR32F2xQI_CONFIG_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_config.h */

