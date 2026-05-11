/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    22/06/2023
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
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_comp.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup COMP_Internal_Scale_MDR32F9Q2I COMP_Internal_Scale for MDR32F9Q2I evaluation board
  * @{
  */

/* Private define ------------------------------------------------------------*/
//#define USE_INVERSION

#define SCALE       COMP_CVREF_SCALE_8_div_32;

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
COMP_InitTypeDef COMP_InitStructure;
COMP_CVRefInitTypeDef COMP_CVRefInitStructure;

volatile uint32_t CompRezAs = 0;
volatile uint32_t CompRezSy = 0;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    RST_CLK_DeInit();
    SystemCoreClockUpdate();

    /* Enables the HSI clock on PORTE */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);

    /* Deinit unused PORT pins */
    PORT_DeInit(MDR_PORTE);

    /* Configure PORTE pins 2 (COMP_IN1) */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin = PORT_Pin_2;
    PORT_InitStructure.PORT_OE  = PORT_OE_IN;
    PORT_Init(MDR_PORTE, &PORT_InitStructure);

    /* Enables the HSI clock for COMP control */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_COMP, ENABLE);

    /* Initialize COMP_InitStructure */
    COMP_StructInit(&COMP_InitStructure);
    COMP_InitStructure.COMP_PlusInputSource  = COMP_PlusInput_CVREF;
    COMP_InitStructure.COMP_MinusInputSource = COMP_MinusInput_IN1;
#ifdef USE_INVERSION
    COMP_InitStructure.COMP_OutInversion = COMP_OUT_INV_Enable;
#endif

    /* Configure COMP */
    COMP_Init(&COMP_InitStructure);

    /* Fills each COMP_CVRefInitStructure member with its default value */
    COMP_CVRefStructInit(&COMP_CVRefInitStructure);

    /* Initialize COMP_CVRefInitStructure */
    COMP_CVRefInitStructure.COMP_CVRefSource = COMP_CVREF_SOURCE_AVdd;
    COMP_CVRefInitStructure.COMP_CVRefScale  = SCALE;

    /* Configure COMP CVRef */
    COMP_CVRefInit(&COMP_CVRefInitStructure);

    /* Enables COMP peripheral */
    COMP_Cmd(ENABLE);

    /* Check READY flag */
    while(COMP_GetCfgFlagStatus(COMP_CFG_FLAG_READY) != SET);

    /* Enables COMP CVRef */
    COMP_CVRefCmd(ENABLE);

    /* Infinite loop */
    while(1)
    {
        CompRezAs = COMP_GetFlagStatus(COMP_STATUS_FLAG_AS);
        CompRezSy = COMP_GetFlagStatus(COMP_STATUS_FLAG_SY);
    }
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

/** @} */ /* End of group COMP_Internal_Scale_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


