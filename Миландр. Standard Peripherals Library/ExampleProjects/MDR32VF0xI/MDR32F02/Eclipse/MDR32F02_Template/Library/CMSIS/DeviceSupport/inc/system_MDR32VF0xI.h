/**
 ******************************************************************************
 * @file    system_MDR32VF0xI.h
 * @author  Milandr Application Team
 * @version V0.1.1
 * @date    25/03/2025
 * @brief   Device Peripheral Access Layer System Header File for MDR32VF0xI.
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
#ifndef SYSTEM_MDR32VF0xI_H
#define SYSTEM_MDR32VF0xI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "system_MDR32VF0xI_config.h"

/** @addtogroup DEVICE_SUPPORT Device Support
 * @{
 */

/** @addtogroup MDR32VF0xI_DEVICE MDR32VF0xI
 *  @{
 */

/** @addtogroup MDR32VF0xI_System MDR32VF0xI System
 * @{
 */

/** @defgroup MDR32VF0xI_System_Exported_Variables MDR32VF0xI System Exported Variables
 * @{
 */

extern uint32_t SystemCoreClock; /*!< System Clock Frequency (Core Clock) default value. */

/** @} */ /* End of group MDR32VF0xI_System_Exported_Variables */

/** @defgroup MDR32VF0xI_System_Exported_Functions MDR32VF0xI System Exported Functions
 * @{
 */

void SystemInit(void);
void SystemCoreClockUpdate(void);

/** @} */ /* End of group MDR32VF0xI_System_Exported_Functions */

/** @} */ /* End of group MDR32VF0xI_System */

/** @} */ /* End of group MDR32VF0xI_DEVICE */

/** @} */ /* End of group DEVICE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* SYSTEM_MDR32VF0xI_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE system_MDR32VF0xI.h */

