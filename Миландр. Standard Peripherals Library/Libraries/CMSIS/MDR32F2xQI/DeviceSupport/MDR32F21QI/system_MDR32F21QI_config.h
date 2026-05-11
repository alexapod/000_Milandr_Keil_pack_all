/**
 ******************************************************************************
 * @file    system_MDR32F21QI_config.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    19/05/2023
 * @brief   CMSIS Device Peripheral Access Layer Configuration File for MDR32F21QI.
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

// <<< Use Configuration Wizard in Context Menu >>>

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_MDR32F21QI_CONFIG_H
#define __SYSTEM_MDR32F21QI_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

// <c3> Use the Standard Peripheral Library (SPL)
// <i> The SPL is used to set target system clock parameters.
// <i> Comment out the line below if you will not be using the SPL.
// <i> In which case the code will only be based on direct access to peripheral registers.
#define USE_MDR32F2xQI_SPL
// </c>

#if defined(USE_MDR32F2xQI_SPL)
#include "MDR32F2xQI_config.h"
#else
// <h> Clock generators frequencies if the SPL is not used
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
#endif

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __SYSTEM_MDR32F21QI_CONFIG_H */

/*********************** (C) COPYRIGHT 2023 Milandr ****************************
 *
 * END OF FILE system_MDR32F21QI_config.h */

