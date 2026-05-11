/**
  ******************************************************************************
  * @file    MDR1986VK01_it.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    07/04/2022
  * @brief   Main Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/

#include "MDR1986VK01_it.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern DMA_ChannelInitTypeDef DMA_InitStr;
extern DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
extern DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;

void DMA_DONE0_IRQHandler(void)
{
  if((MDR_DMA->CHNL_PRI_ALT_SET &(1<<0)) == (0<<0))
  {
   DMA_CtrlInit(0, DMA_CTRL_DATA_ALTERNATE,  &DMA_AltCtrlStr);
  }
  else if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<0)) == (1<<0))
  {
   DMA_CtrlInit(0, DMA_CTRL_DATA_PRIMARY, &DMA_PriCtrlStr);
  }
}

/******************* (C) COPYRIGHT 2025 Milandr *********/

/* END OF FILE MDR1986VK01_it.c */


