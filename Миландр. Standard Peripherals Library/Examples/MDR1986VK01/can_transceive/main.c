/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    07/04/2022
  * @brief   Main program body.
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
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "can.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup can_transceive can_transceive
 *  @{
 */

uint32_t TData0 = 0x89ABCDEF, TData1 = 0x01234567;
uint32_t RData0 = 0, RData1 = 0;
uint32_t tries;

/**
  * @brief	Init clock.
  * @param	None
  * @retval None
  */
void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;

    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

    CLK_SetSystemClock( MAX_CLK_HSE0 );
}

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main()
{
    ClockInit();
    
    InitCan(10000000);
    tries = CanTest(TData0, TData1, &RData0, &RData1);
    DeinitCan();
    
    while(1)
    {
    
    }
    
}

/** @} */ /* End of group can_transceive */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *********/

/* END OF FILE main.c */


