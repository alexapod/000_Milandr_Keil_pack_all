/**
 ******************************************************************************
 * @file    system_MDR32F23QI.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    22/05/2023
 * @brief   CMSIS Device Peripheral Access Layer System Header File for MDR32F23QI.
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
#ifndef __SYSTEM_MDR32F23QI_H
#define __SYSTEM_MDR32F23QI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup CMSIS CMSIS
 * @{
 */

/** @addtogroup MDR32F23QI MDR32F23QI
 *  @{
 */

/** @addtogroup MDR32F23QI_System MDR32F23QI System
 * @{
 */

/** @defgroup MDR32F23QI_System_Exported_Variables MDR32F23QI System Exported Variables
 * @{
 */

extern uint32_t SystemCoreClock; /*!< System Clock Frequency (Core Clock) default value */

/** @} */ /* End of group MDR32F23QI_System_Exported_Variables */

/** @defgroup MDR32F23QI_System_Exported_Functions MDR32F23QI System Exported Functions
 * @{
 */

void SystemInit(void);
void SystemCoreClockUpdate(void);

/** @} */ /* End of group MDR32F23QI_System_Exported_Functions */

/** @} */ /* End of group MDR32F23QI_System */

/** @} */ /* End of group MDR32F23QI */

/** @} */ /* End of group CMSIS */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /*__SYSTEM_MDR32F23QI_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE system_MDR32F23QI.h */

