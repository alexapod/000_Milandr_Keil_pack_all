/**
  ******************************************************************************
  * @file    system_MDR1986VK01.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   CMSIS Cortex-M4F Device Peripheral Access Layer System Header File.
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

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @defgroup MDR1986VK01 MDR1986VK01
 *  @{
 */

/** @defgroup __MDR1986VK01 MDR1986VK01 System
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_MDR1986VK01_H
#define __SYSTEM_MDR1986VK01_H

#ifdef __cplusplus
extern "C" {
#endif

/* Standard types inclusion --------------------------------------------------*/
#include <stdint.h>

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock) */


extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_MDR1986VK01_H */

/** @} */ /* End of group __MDR1986VK01 */

/** @} */ /* End of group MDR1986VK01 */

/** @} */ /* End of group __CMSIS */

/******************* (C) COPYRIGHT 2025 Milandr ********************************
*
* END OF FILE system_MDR1986VK01.h */


