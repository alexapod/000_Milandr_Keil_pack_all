/**
  ******************************************************************************
  * @file    MDR1986VK01_delay.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   Delay functions Header file.
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
  * FILE MDR1986VK01_delay.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_DELAY_H
#define __MDR1986VK01_DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_config.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup Delay Delay
  * @{
  */

/** @defgroup Delay_Exported_Functions Delay Exported Functions
  * @{
  */

void DELAY_Config( void );
RAMFUNC void DELAY_us( uint32_t ulUs );
RAMFUNC void DELAY_ms( uint32_t ulMs );


/** @} */ /* End of group Delay_Exported_Functions */

/** @} */ /* End of group Delay */

/** @} */ /* End of group MDR1986VK01_StdPeriph_Driver */

#endif /* __MDR1986VK01_DELAY_H */

/******************* (C) COPYRIGHT 2025 Milandr *********
*
* END OF FILE MDR1986VK01_delay.h */


