/**
 ******************************************************************************
 * @file    system_MDR32VF0xI_sections.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    25/03/2025
 * @brief   This file contains all the macros for placing objects in sections.
 ******************************************************************************
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
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SYSTEM_MDR32VF0xI_SECTIONS_H
#define SYSTEM_MDR32VF0xI_SECTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DEVICE_SUPPORT Device Support
 * @{
 */

/** @addtogroup MDR32VF0xI_DEVICE MDR32VF0xI
 *  @{
 */

/** @addtogroup MDR32VF0xI_System_Sections MDR32VF0xI System Sections
 * @{
 */

/** @defgroup MDR32VF0xI_System_Sections_Exported_Defines MDR32VF0xI System Sections Exported Defines
 * @{
 */

/**
 * @brief Section attribute macros.
 */
#if defined(__GNUC__) /* GCC compiler. */
#define __GET_COUNTER_STRING(COUNTER)    #COUNTER
#define __GET_COUNTER(COUNTER)           __GET_COUNTER_STRING(COUNTER)
#define __ATTR_SECTION(SECTION)          __attribute__((section(SECTION "." __GET_COUNTER(__COUNTER__))))
#define __ATTR_SECTION_NOINLINE(SECTION) __attribute__((noipa, section(SECTION "." __GET_COUNTER(__COUNTER__))))
#elif defined(__ICCRISCV__) /* IAR RISC-V compiler. */
#define __ATTR_SECTION(SECTION)          __attribute__((section(SECTION)))
#define __ATTR_SECTION_NOINLINE(SECTION) __attribute__((noinline, section(SECTION)))
#endif

/**
 * @brief   Section attribute macro for placing a function in RAM TCM memory.
 * @warning Function with __RAM_TEXT may be inlined, in which case the placement will be determined by the function in which the inlining was performed.
 *          To force placement in RAM TCM memory use __RAM_TEXT_NOINLINE.
 */
#define __RAM_TEXT __ATTR_SECTION(".ram_text")

/**
 * @brief Section attribute macro to force function placement in RAM TCM memory.
 * @note  The macro contains an attribute that prevents the function from being considered for inlining.
 */
#define __RAM_TEXT_NOINLINE __ATTR_SECTION_NOINLINE(".ram_text")

/**
 * @brief Section attribute macro for placing initialized data (non-zero) in RAM TCM memory.
 * @note  __RAM_DATA and __RAM_TEXT/__RAM_TEXT_NOINLINE place objects in different areas of RAM TCM memory (TCMA/TCMB),
 *        which will provide the highest performance when executing function with __RAM_TEXT/__RAM_TEXT_NOINLINE and simultaneously accessing data with __RAM_DATA.
 */
#define __RAM_DATA __ATTR_SECTION(".ram_data")

/**
 * @brief Section attribute macro for placing zero-initialized data in RAM TCM memory.
 * @note  __RAM_BSS and __RAM_TEXT/__RAM_TEXT_NOINLINE place objects in different areas of RAM TCM memory (TCMA/TCMB),
 *        which will provide the highest performance when executing function with __RAM_TEXT/__RAM_TEXT_NOINLINE and simultaneously accessing data with __RAM_BSS.
 */
#define __RAM_BSS __ATTR_SECTION(".ram_bss")

/**
 * @brief   Section attribute macro for placing a function in RAM AHB memory.
 * @warning Function with __RAM_AHB_TEXT may be inlined, in which case the placement will be determined by the function in which the inlining was performed.
 *          To force placement in RAM AHB memory use __RAM_AHB_TEXT_NOINLINE.
 */
#define __RAM_AHB_TEXT __ATTR_SECTION(".ram_ahb_text")

/**
 * @brief Section attribute macro to force function placement in RAM AHB memory.
 * @note  The macro contains an attribute that prevents the function from being considered for inlining.
 */
#define __RAM_AHB_TEXT_NOINLINE __ATTR_SECTION_NOINLINE(".ram_ahb_text")

/**
 * @brief Section attribute macro for placing initialized data (non-zero) in RAM AHB memory.
 */
#define __RAM_AHB_DATA __ATTR_SECTION(".ram_ahb_data")

/**
 * @brief Section attribute macro for placing zero-initialized data in RAM AHB memory.
 */
#define __RAM_AHB_BSS __ATTR_SECTION(".ram_ahb_bss")

/** @} */ /* End of group MDR32VF0xI_System_Sections_Exported_Defines */

/** @} */ /* End of group MDR32VF0xI_System_Sections */

/** @} */ /* End of group MDR32VF0xI_DEVICE */

/** @} */ /* End of group DEVICE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* SYSTEM_MDR32VF0xI_SECTIONS_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE system_MDR32VF0xI_sections.h */

