/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    30/04/2025
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

/** @addtogroup TIMER TIMER
 * @{
 */

/** @addtogroup MDR32VF0xI_TIMER_PWM MDR32VF0xI_TIMER_PWM
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_rst_clk.h"
#include "MDR32VF0xI_timer.h"

/* Private definitions -------------------------------------------------------*/
#define TIMER                   MDR_TIMER3
#define TIMER_PWM_CH            TIMER_CH1
#define TIMER_PCLK              RST_CLK_PCLK_TIMER3
#define TIMER_PER1_C2           RST_CLK_PER1_C2_TIM3

#define TIMER_PWM_PIN_PORT      MDR_PORTB
#define TIMER_PWM_PIN           PORT_PIN_0
#define TIMER_PWM_PIN_FUNC      PORT_FUNCTION_OVERRIDDEN
#define TIMER_PWM_PIN_PORT_PCLK RST_CLK_PCLK_PORTB

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);
void TimerConfig(void);
void TimerPinConfig(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();

    TimerConfig();
    TimerPinConfig();

    TIMER_CNT_Cmd(TIMER, ENABLE);

    while (1) { }
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
 * @brief  Timer configuration as PWM.
 * @param  None.
 * @return None.
 */
void TimerConfig(void)
{
    static const TIMER_CNT_InitTypeDef TimerPWM = {
        .TIMER_CNT_Counter          = 0,
        .TIMER_CNT_Prescaler        = (8 - 1),
        .TIMER_CNT_Period           = (2 - 1),
        .TIMER_CNT_EventSource      = TIMER_CNT_EVNT_SRC_TIM_CLK,
        .TIMER_CNT_Mode             = TIMER_CNT_MODE_CLK_FIXED_DIR,
        .TIMER_CNT_Direction        = TIMER_CNT_DIR_UP,
        .TIMER_CNT_PeriodUpdateMode = TIMER_CNT_PERIOD_UPD_IMMEDIATELY,
        .TIMER_FDTS_Prescaler       = TIMER_FDTS_PRESCALER_DIV_1,
        .TIMER_ETR_Filter           = TIMER_ETR_FILTER_1FF_AT_FDTS,
        .TIMER_ETR_Prescaler        = TIMER_ETR_PRESCALER_DIV_1,
        .TIMER_ETR_Polarity         = TIMER_ETR_POLARITY_NON_INV,
        .TIMER_BRK_Polarity         = TIMER_BRK_POLARITY_NON_INV,
    };
    static const TIMER_CH_InitTypeDef TimerChannel = {
        .TIMER_CH_Number                = TIMER_PWM_CH,
        .TIMER_CH_Mode                  = TIMER_CH_MODE_PWM,
        .TIMER_CH_UseCCR1               = DISABLE,
        .TIMER_CH_PWM_REF_Format        = TIMER_CH_PWM_REF_FORMAT_6,
        .TIMER_CH_PWM_CCR_UpdateMode    = TIMER_CH_PWM_CCR_UPD_IMMEDIATELY,
        .TIMER_CH_PWM_DTG_ClockSource   = TIMER_CH_PWM_DTG_CLK_SRC_TIM_CLK,
        .TIMER_CH_PWM_DTG_MainPrescaler = 0,
        .TIMER_CH_PWM_DTG_AuxPrescaler  = 0,
        .TIMER_CH_PWM_ETR_UseReset      = DISABLE,
        .TIMER_CH_PWM_BRK_UseReset      = DISABLE,
    };
    static const TIMER_CH_OUT_InitTypeDef TimerChannelOut = {
        .TIMER_CH_Number        = TIMER_PWM_CH,
        .TIMER_CH_OUTP_Polarity = TIMER_CH_OUTP_POLARITY_NON_INV,
        .TIMER_CH_OUTP_Source   = TIMER_CH_OUTP_SRC_REF,
        .TIMER_CH_OUTP_Mode     = TIMER_CH_OUTP_MODE_OUT,
        .TIMER_CH_OUTN_Polarity = TIMER_CH_OUTN_POLARITY_NON_INV,
        .TIMER_CH_OUTN_Source   = TIMER_CH_OUTN_SRC_0,
        .TIMER_CH_OUTN_Mode     = TIMER_CH_OUTN_MODE_IN,
    };

    RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_CLK_SRC_CPU_C1);
    RST_CLK_PER1_C2_SetPrescaler(TIMER_PER1_C2, RST_CLK_PER1_PRESCALER_DIV_1);
    RST_CLK_PER1_C2_Cmd(TIMER_PER1_C2, ENABLE);

    RST_CLK_PCLKCmd(TIMER_PCLK, ENABLE);

    TIMER_DeInit(TIMER);
    TIMER_CNT_Init(TIMER, &TimerPWM);
    TIMER_CH_Init(TIMER, &TimerChannel);
    TIMER_CH_PWM_SetCompare(TIMER, TIMER_PWM_CH, (TimerPWM.TIMER_CNT_Period + 1) / 2);
    TIMER_CH_OUT_Init(TIMER, &TimerChannelOut);
}

/**
 * @brief  Timer PWM pin configuration.
 * @param  None.
 * @return None.
 */
void TimerPinConfig(void)
{
    RST_CLK_PCLKCmd(TIMER_PWM_PIN_PORT_PCLK, ENABLE);

    PORT_DeInit(TIMER_PWM_PIN_PORT);
    PORT_InitTypeDef TimerChannelPin = {
        .PORT_Pin       = TIMER_PWM_PIN,
        .PORT_Direction = PORT_DIRECTION_OUTPUT,
        .PORT_Function  = TIMER_PWM_PIN_FUNC,
        .PORT_Mode      = PORT_MODE_DIGITAL,
        .PORT_Power     = PORT_POWER_NOMINAL_UPTO_2mA,
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
        .PORT_PullUp = PORT_PULL_UP_OFF,
#endif
        .PORT_PullDown = PORT_PULL_DOWN_OFF,
    };
    PORT_Init(TIMER_PWM_PIN_PORT, &TimerChannelPin);
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

/** @} */ /* End of group MDR32VF0xI_TIMER_PWM */

/** @} */ /* End of group TIMER */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


