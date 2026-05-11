/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    20/06/2023
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
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_ebc.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup EXT_BUS_Extern_RAM_MDR32F1QI EXT_BUS_Extern_RAM
  * @{
  */

/* Private variables ---------------------------------------------------------*/
EBC_InitTypeDef EBC_InitStruct;
EBC_MemRegionInitTypeDef EBC_MemRegionInitStruct;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    RST_CLK_DeInit();

    /* Select HSE as CPU_CLK source */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    while(RST_CLK_HSEstatus() == ERROR) {}
    RST_CLK_CPUclkSelectionC1(RST_CLK_CPU_C1srcHSEdiv1);
    RST_CLK_CPU_PLLuse(DISABLE);
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

    SystemCoreClockUpdate();

    /* Enables the HSI clock for EBC control */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EBC, ENABLE);

    /* Initializes EBC_InitStruct by default values*/
    EBC_StructInit(&EBC_InitStruct);

    /* Specifies external bus mode RAM*/
    EBC_InitStruct.EBC_Mode = EBC_MODE_RAM;

    /* Calculates the Wait States number for 8 MHz frequency and time interval = 500 ns */
    EBC_InitStruct.EBC_WaitState = (EBC_Wait_State)EBC_CalcWaitStates(8000, 500);

    /* Initializes the EBC peripheral registers */
    EBC_Init(&EBC_InitStruct);

    /* Initializes the EBC memory region 0õ50000000-0õ5FFFFFFF */
    /* Struct init */
    EBC_MemRegionStructInit(&EBC_MemRegionInitStruct);
    /* Initializes the EBC memory region  */
    EBC_MemRegionInit(&EBC_MemRegionInitStruct, EBC_MEM_REGION_50000000);
    /* Enables the specified EBC memory region settigs. */
    EBC_MemRegionCMD(EBC_MEM_REGION_50000000, ENABLE);

    /* Infinite loop */
    while(1) {}
}

/**
  * @brief  Reports the source file name, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the source file name and line number.
       Ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while(1) {}
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    /* User can add his own implementation to report the source file name, line number and
       expression text.
       Ex: printf("Wrong parameters value (%s): file %s on line %d\r\n", expr, file, line) */

    /* Infinite loop */
    while(1) {}
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group EXT_BUS_Extern_RAM_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


