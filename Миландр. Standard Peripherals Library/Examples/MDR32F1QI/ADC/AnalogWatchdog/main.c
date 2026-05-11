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
  * <h2><center>&copy; COPYRIGHT 2025 Milandr </center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "MDR32FxQI_config.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_utils.h"
#include "MDR32FxQI_adc.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup ADC_AnalogWatchdog_MDR32F1QI ADC_AnalogWatchdog
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */

/* Private variables ---------------------------------------------------------*/
__IO uint32_t H_Level = 0x900;
__IO uint32_t L_Level = 0x800;
int result;

PORT_InitTypeDef PORT_InitStructure;
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;

/* Private function prototypes -----------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
void ClockConfigure(void);
#endif
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
        PORT_SetBits(MDR_PORTD, PORT_Pin_10);
    }
    else
    {
        /* Turns LED1 Off */
        PORT_ResetBits(MDR_PORTD, PORT_Pin_10);
    }
    result = ADC1_GetResult() & ADC_RESULT_Msk;
    if (result > H_Level)
    {
        /* Turns LED2 On */
        PORT_SetBits(MDR_PORTD, PORT_Pin_11);
    }
    else
    {
        /* Turns LED2 Off */
        PORT_ResetBits(MDR_PORTD, PORT_Pin_11);
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
#if defined (_USE_DEBUG_UART_)
    ErrorStatus Status;
#endif

    RST_CLK_DeInit();

#if defined (_USE_DEBUG_UART_)
    ClockConfigure();
#endif /* #if defined (_USE_DEBUG_UART_) */

    SystemCoreClockUpdate();

#if defined (_USE_DEBUG_UART_)
    Status = STDIO_Init();
    if (Status == ERROR) {
        while (1) {}
    }
#endif /* #if defined (_USE_DEBUG_UART_) */

    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_ADC | RST_CLK_PCLK_PORTD), ENABLE);

    /* Reset PORTD settings */
    PORT_DeInit(MDR_PORTD);

    /* Configure ADC pin: ADC2 */
    /* Configure PORTD pin 9 */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin  = PORT_Pin_9;
    PORT_InitStructure.PORT_OE   = PORT_OE_IN;
    PORT_InitStructure.PORT_MODE = PORT_MODE_ANALOG;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Configure PORTD pins 10, 11 for output to switch LED1,2 on/off */
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_10 | PORT_Pin_11);
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* ADC Configuration */
    /* Reset all ADC settings */
    ADC_DeInit();
    DEBUG_PRINTF("ADC Init...");
    // Inti clock ADC
    RST_CLK_ADCclkSelection(RST_CLK_ADCclkCPU_C1);
    RST_CLK_ADCclkPrescaler(RST_CLK_ADCclkDIV2);
    // Enable clock ADC
    RST_CLK_ADCclkEnable(ENABLE);

    ADC_StructInit(&sADC);
    sADC.ADC_TempSensor           = ADC_TEMP_SENSOR_Enable;
    sADC.ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Enable;
    sADC.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;
    sADC.ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;
    sADC.ADC_IntVRefTrimming      = 0;
    sADC.ADC_IntVRefAmplifier     = ADC_INT_VREF_AMPLIFIER_Enable;
    ADC_Init(&sADC);

    ADCx_StructInit(&sADCx);
    sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;
    sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;
    sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
    sADCx.ADC_ChannelNumber    = ADC_CH_ADC2;
    sADCx.ADC_Channels         = 0;
    sADCx.ADC_LevelControl     = ADC_LEVEL_CONTROL_Enable;
    sADCx.ADC_LowLevel         = L_Level;
    sADCx.ADC_HighLevel        = H_Level;
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
    sADCx.ADC_Prescaler        = ADC_CLK_div_16;
    sADCx.ADC_DelayGo          = 0xF;
    ADC1_Init(&sADCx);

    /* Enable ADC1 EOCIF and AWOIFEN interupts */
    ADC1_ITConfig((ADCx_IT_END_OF_CONVERSION | ADCx_IT_OUT_OF_RANGE), ENABLE);
    NVIC_EnableIRQ(ADC_IRQn);

    /* ADC1 enable */
    ADC1_Cmd(ENABLE);

    while(1) {}
}

#if defined (_USE_DEBUG_UART_)
/**
  * @brief  Configure CPU clock.
  * @param  None
  * @retval None
  */
void ClockConfigure(void)
{
    /* Enable HSE clock */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    /* Wait HSE ready */
    while(RST_CLK_HSEstatus() == ERROR) {}
    /* Select HSE as CPU_C1 source */
    RST_CLK_CPUclkSelectionC1(RST_CLK_CPU_C1srcHSEdiv1);
    /* Select CPU_C1 as CPU_C2 source */
    RST_CLK_CPU_PLLuse(DISABLE);
    /* Select CPU_C2 as CPU_C3 source */
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}
#endif /* #if defined (_USE_DEBUG_UART_) */


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

/** @} */ /* End of group ADC_AnalogWatchdog_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


