/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    12/05/2025
 * @brief   Main program body.
 ******************************************************************************
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 */

/** @addtogroup MDR32VF0xI_StdPeriph_Examples MDR32VF0xI StdPeriph Examples
 * @{
 */

/** @addtogroup MDR32VF0xI_MDR1206FI_BOARD MDR1206FI Evaluation Board
 * @{
 */

/** @addtogroup ADC ADC
 * @{
 */

/** @addtogroup MDR32VF0xI_ADC MDR32VF0xI_ADC
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_adc.h"
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_rst_clk.h"
#include "system_MDR32VF0xI_it.h"

#include "math.h"

/* Private definitions -------------------------------------------------------*/
#define LED_PORT                 MDR_PORTD
#define LED_PORT_CLK             RST_CLK_PCLK_PORTD
#define LED_PIN_1                PORT_PIN_5
#define LED_PIN_2                PORT_PIN_6
#define LED_PIN_3                PORT_PIN_7
#define LED_PIN_4                PORT_PIN_8
#define LED_PINS                 (LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4)

#define TEMP_TO_ADC_RESULT(TEMP) ((int)(((25.0 - (TEMP)) * 0.0037 + 1.403) * 1024.0 / 3.3 + 0.5))

#define MIN(a, b)                ((a) < (b) ? (a) : (b))
#define MAX(a, b)                ((a) > (b) ? (a) : (b))

/* Private variables ---------------------------------------------------------*/
ADC_Result_TypeDef ADC_ConversionResult;
float              Temperature;

/* Private functions prototypes ----------------------------------------------*/
void ADC_Config(void);
void ClockConfig(void);
void LedConfig(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  ADC interrupt handler.
 * @param  None.
 * @return None.
 */
void ADC_IRQHandler(void)
{
    ADC_GetResultStruct(&ADC_ConversionResult);
    Temperature = ADC_RESULT_TO_TEMPERATURE(3.3, ADC_ConversionResult.ADC_Result);
    PORT_ToggleBit(LED_PORT, LED_PIN_1);

    if (ADC_GetFlagStatus(ADC_FLAG_OUT_OF_RANGE) == SET) {
        ADC_ClearFlags(ADC_FLAG_OUT_OF_RANGE);
        PORT_WriteBit(LED_PORT, LED_PIN_2, !(BitStatus)(ADC_ConversionResult.ADC_Result < MDR_ADC->ADC1_L_LEVEL));
        PORT_WriteBit(LED_PORT, LED_PIN_3, !(BitStatus)(ADC_ConversionResult.ADC_Result > MDR_ADC->ADC1_H_LEVEL));
    } else {
        PORT_SetBits(LED_PORT, (LED_PIN_2 | LED_PIN_3));
    }
}

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();
    LedConfig();
    ADC_Config();

    ADC_Cmd(ENABLE);

    while (1) {
        while (ADC_GetFlagStatus(ADC_FLAG_END_OF_CONVERSION) != SET) { }
        ADC_GetResultStruct(&ADC_ConversionResult);
        Temperature = ADC_RESULT_TO_TEMPERATURE(3.3, ADC_ConversionResult.ADC_Result);

        if (ADC_GetFlagStatus(ADC_FLAG_OUT_OF_RANGE) == SET) {
            ADC_ClearFlags(ADC_FLAG_OUT_OF_RANGE);
            /* LED1, LED2 - Temperature is under lower bound. */
            PORT_WriteBit(LED_PORT, (LED_PIN_1 | LED_PIN_2), !(BitStatus)(ADC_ConversionResult.ADC_Result > MDR_ADC->ADC1_H_LEVEL));
            /* LED3, LED4 - Temperature is above upper bound. */
            PORT_WriteBit(LED_PORT, (LED_PIN_3 | LED_PIN_4), !(BitStatus)(ADC_ConversionResult.ADC_Result < MDR_ADC->ADC1_L_LEVEL));
        } else {
            PORT_SetBits(LED_PORT, LED_PINS);
        }
    }
}

/**
 * @brief  Clock configuration.
 * @param  None.
 * @return None.
 */
void ClockConfig(void)
{
    RST_CLK_DeInit();
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_HSI);
#endif
    SystemCoreClockUpdate();
}

/**
 * @brief  LEDs configuration.
 * @param  None.
 * @return None.
 */
void LedConfig(void)
{
    static const PORT_InitTypeDef LedPins = {
        .PORT_Pin       = LED_PINS,
        .PORT_Mode      = PORT_MODE_DIGITAL,
        .PORT_Direction = PORT_DIRECTION_OUTPUT,
        .PORT_Function  = PORT_FUNCTION_PORT,
        .PORT_Power     = PORT_POWER_NOMINAL_UPTO_2mA,
#if !defined(USE_MDR32F02_REV_1X)
        .PORT_PullUp = PORT_PULL_UP_OFF,
#endif
        .PORT_PullDown = PORT_PULL_DOWN_OFF,
    };

    RST_CLK_PCLKCmd(LED_PORT_CLK, ENABLE);
    PORT_Init(LED_PORT, &LedPins);
    PORT_SetBits(LED_PORT, LED_PINS);
}

/**
 * @brief  ADC configuration.
 * @param  None.
 * @return None.
 */
void ADC_Config(void)
{
    static const ADC_InitTypeDef ADC_TemperatureMeas = {
        .ADC_ClockSource      = ADC_CLOCK_SOURCE_ADC_CLK,
        .ADC_Prescaler        = ADC_PRESCALER_DIV_1,
        .ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL,
        .ADC_Scale            = ADC_SCALE_MAX_UCCA,
        .ADC_ChannelSwitching = ADC_CH_SWITCHING_DISABLE,
        .ADC_ChannelNumber    = ADC_CH_ADC0_TEMP_SENSOR,
        .ADC_Channels         = 0,
        .ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV,
        .ADC_DelayGo          = 7,
        .ADC_LevelControl     = ADC_LEVEL_CONTROL_ENABLE,
        .ADC_LowLevel         = MIN(TEMP_TO_ADC_RESULT(23.0), TEMP_TO_ADC_RESULT(25.0)),
        .ADC_HighLevel        = MAX(TEMP_TO_ADC_RESULT(23.0), TEMP_TO_ADC_RESULT(25.0))
    };

    RST_CLK_ADC_ClkSelection(RST_CLK_ADC_CLK_SRC_CPU_C1);
    RST_CLK_ADC_SetPrescaler(RST_CLK_ADC_PRESCALER_DIV_8);
    RST_CLK_ADC_ClkCmd(ENABLE);

    RST_CLK_PCLKCmd(RST_CLK_PCLK_ADC, ENABLE);

    ADC_DeInit();
    ADC_Init(&ADC_TemperatureMeas);
}

/**
 * @brief  Report the source file name, the source line number and expression
 *         text (if USE_ASSERT_INFO == 2) where the assert_param error has occurred.
 * @param  file: Pointer to the source file name.
 * @param  line: assert_param error line source number.
 * @param  expr: Reported expression text.
 * @return None.
 */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;
    while (1) { }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    (void)file;
    (void)line;
    (void)expr;
    while (1) { }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group MDR32VF0xI_ADC */

/** @} */ /* End of group ADC */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


