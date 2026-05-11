/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    07/05/2025
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

/** @addtogroup ADCUI ADCUI
 * @{
 */

/** @addtogroup MDR32VF0xI_ADCUI MDR32VF0xI_ADCUI
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_adcui.h"
#include "MDR32VF0xI_rst_clk.h"

/* Private definitions -------------------------------------------------------*/
#define SAMPLES_AMOUNT 256

/* Private variables ---------------------------------------------------------*/
uint32_t DataADCUI[SAMPLES_AMOUNT];
uint32_t SamplesCounter;

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);
void ADCUI_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();
    ADCUI_Config();

    while (1) {
        SamplesCounter = 0;
        while (SamplesCounter < SAMPLES_AMOUNT) {
            if (ADCUI_GetFlagStatus(ADCUI_F0_UNIT, ADCUI_Fx_VF_EMP) == RESET) {
                DataADCUI[SamplesCounter] = ADCUI_GetResult(ADCUI_CH_F0_V0);
                SamplesCounter++;
            }
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

    RST_CLK_HSE_Cmd(ENABLE);
    while (RST_CLK_HSE_GetStatus() != SUCCESS) { }

    RST_CLK_CPU_C1_ClkSelection(RST_CLK_CPU_C1_CLK_SRC_HSE);
    RST_CLK_CPU_C3_SetPrescaler(RST_CLK_CPU_C3_PRESCALER_DIV_1);
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_CPU_C3);
    SystemCoreClockUpdate();
}

/**
 * @brief  ADCUI configuration.
 * @param  None.
 * @return None.
 */
void ADCUI_Config(void)
{
    static const ADCUI_InitTypeDef ADCUI = {
        .ADCUI_DataResol              = ADCUI_DATA_RESOL_16BIT,
        .ADCUI_ZeroCrossLowPassFilter = ADCUI_ZXLPF_FILTER_DISABLE,
        .ADCUI_PeriodLength           = ADCUI_PER_LENGTH_1,
        .ADCUI_ActivePowerNoLoad      = ADCUI_APNOLOAD_FULL,
        .ADCUI_ReactivePowerNoLoad    = ADCUI_VARNOLOAD_FULL,
        .ADCUI_FullPowerNoLoad        = ADCUI_VANOLOAD_FULL,
        .ADCUI_FreqVEnable            = DISABLE,
        .ADCUI_VRefConfig             = ADCUI_REFERENCE_VOLTAGE_INTERNAL,
        .ADCUI_ZeroCrossUpdateRMS     = ADCUI_REG_CONTINUOUS_UPDATE,
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
        .ADCUI_ClockFrequency = ADCUI_CLK_FREQUENCY_4MHz,
        .ADCUI_ChopperPeriod  = ADCUI_CHOPPER_PERIOD_256,
#endif
        .ADCUI_Divider               = ADCUI_OVERSAMPLING_DIV_256,
        .ADCUI_VoltageDropLevel      = 0,
        .ADCUI_VoltageHalfCyclesDrop = 0,
        .ADCUI_ZeroCrossTimeOut      = 0,
    };

    RST_CLK_ADCUI_ClkDeInit();
    RST_CLK_ADCUI_ClkCmd(ENABLE);

    RST_CLK_PCLKCmd(RST_CLK_PCLK_ADCUI, ENABLE);

    ADCUI_DeInit();
    ADCUI_Init(&ADCUI);
    ADCUI_ChannelConfig(ADCUI_CH_F0_V0, ENABLE);
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

/** @} */ /* End of group MDR32VF0xI_ADCUI */

/** @} */ /* End of group ADCUI */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


