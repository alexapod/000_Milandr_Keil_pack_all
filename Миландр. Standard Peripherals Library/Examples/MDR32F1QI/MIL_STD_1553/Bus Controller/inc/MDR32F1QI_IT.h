/**
  ******************************************************************************
  * @file    MDR32F1QI_IT.h
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    22/09/2021
  * @brief   This file contains the functions prototypes for the interrupt.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32F1QI_IT_H
#define __MDR32F1QI_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function prototypes -------------------------------------------------------*/
void HardFault_Handler(void);
void MIL_STD_1553B2_IRQHandler(void);
void MIL_STD_1553B1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MDR32F1QI_IT_H */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE MDR32F1QI_IT.h */


