/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.1.0
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
#include "MDR32FxQI_adc.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup ADC_AnalogWatchdog_MDR32F9Q2I ADC_AnalogWatchdog
  * @{
  */

/* Private variables ---------------------------------------------------------*/
__IO uint32_t H_Level = 0x900;
__IO uint32_t L_Level = 0x800;
volatile int result;

PORT_InitTypeDef PORT_InitStructure;
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ADC interrupt handler.
  * @param  None
  * @retval None
  */
void ADC_IRQHandler(void)
{
    if (ADC1_GetFlagStatus(ADCx_FLAG_OUT_OF_RANGE) == SET)
    {
        /* Turns LED1 On */
        PORT_SetBits(MDR_PORTC, PORT_Pin_0);
    }
    else
    {
        /* Turns LED1 Off */
        PORT_ResetBits(MDR_PORTC, PORT_Pin_0);
    }

    result = ADC1_GetResult() & ADC_RESULT_Msk;

    if (result > H_Level)
    {
        /* Turns LED2 On */
        PORT_SetBits(MDR_PORTC, PORT_Pin_1);
    }
    else
    {
        /* Turns LED2 Off */
        PORT_ResetBits(MDR_PORTC, PORT_Pin_1);
    }

    /* Clear ADC1 OUT_OF_RANGE interrupt bit */
    ADC1_ClearOutOfRangeFlag();
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    RST_CLK_DeInit();
    SystemCoreClockUpdate();

    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_ADC |
                    RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD), ENABLE);

    /* Reset PORTD settings */
    PORT_DeInit(MDR_PORTD);

    /* Reset PORTC settings */
    PORT_DeInit(MDR_PORTC);

    /* Configure ADC pins: ADC7 */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = PORT_Pin_7;
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_ANALOG;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Configure PORTC pins 0, 1 for output to switch LED1,2 on/off */
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1);
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* ADC Configuration */
    /* Reset all ADC settings */
    ADC_DeInit();
    ADC_StructInit(&sADC);
    ADC_Init(&sADC);

    ADCx_StructInit(&sADCx);
    sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;
    sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;
    sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
    sADCx.ADC_ChannelNumber    = ADC_CH_ADC7;
    sADCx.ADC_Channels         = 0;
    sADCx.ADC_LevelControl     = ADC_LEVEL_CONTROL_Enable;
    sADCx.ADC_LowLevel         = L_Level;
    sADCx.ADC_HighLevel        = H_Level;
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
    sADCx.ADC_Prescaler        = ADC_CLK_div_2048;
    sADCx.ADC_DelayGo          = 0xF;
    ADC1_Init(&sADCx);

    /* Enable ADC1 EOCIF and AWOIFEN interrupts */
    ADC1_ITConfig((ADC1_IT_END_OF_CONVERSION | ADC1_IT_OUT_OF_RANGE), ENABLE);

    /* Enable ADC interrupt */
    NVIC_EnableIRQ(ADC_IRQn);

    /* ADC1 enable */
    ADC1_Cmd(ENABLE);

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

/** @} */ /* End of group ADC_AnalogWatchdog_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


