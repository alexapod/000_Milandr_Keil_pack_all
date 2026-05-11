/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    06/05/2025
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

/** @addtogroup MDR32VF0xI_TIMER_CAP MDR32VF0xI_TIMER_CAP
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_rst_clk.h"
#include "MDR32VF0xI_timer.h"

#include "system_MDR32VF0xI_it.h"

/* Private definitions -------------------------------------------------------*/
#define TIMER                   MDR_TIMER1
#define TIMER_CAP_CH            TIMER_CH1
#define TIMER_PCLK              RST_CLK_PCLK_TIMER1
#define TIMER_PER1_C2           RST_CLK_PER1_C2_TIM1
#define TIMER_IRQ               TIMER1_IRQn
#define TIMER_IRQ_HANDLER       TIMER1_IRQHandler

#define TIMER_CAP_CCR           TIMER_FLAG_CH1_CAP_CCR
#define TIMER_CAP_CCR1          TIMER_FLAG_CH1_CAP_CCR1

#define TIMER_CAP_PIN_PORT      MDR_PORTA
#define TIMER_CAP_PIN           PORT_PIN_0
#define TIMER_CAP_PIN_FUNC      PORT_FUNCTION_MAIN
#define TIMER_CAP_PIN_PORT_PCLK RST_CLK_PCLK_PORTA

#define LED_PORT                MDR_PORTD
#define LED_PORT_CLK            RST_CLK_PCLK_PORTD
#define LED_PIN_1               PORT_PIN_5
#define LED_PIN_2               PORT_PIN_6
#define LED_PIN_3               PORT_PIN_7
#define LED_PIN_4               PORT_PIN_8
#define LED_PINS                (LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4)

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);
void TimerConfig(void);
void TimerPinConfig(void);
void InterruptConfig(void);
void LedConfig(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Timer interrupt handler.
 * @param  None.
 * @return None.
 */
void TIMER_IRQ_HANDLER(void)
{
    PORT_ToggleBit(LED_PORT, LED_PINS);
    TIMER_ClearFlags(TIMER, (TIMER_CAP_CCR | TIMER_CAP_CCR1));
}

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

    LedConfig();
    InterruptConfig();

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
 * @brief  Timer configuration.
 * @param  None.
 * @return None.
 */
void TimerConfig(void)
{
    static const TIMER_CNT_InitTypeDef TimerCAP = {
        .TIMER_CNT_Counter          = 0,
        .TIMER_CNT_Prescaler        = 0,
        .TIMER_CNT_Period           = 0xFFFFFFFF,
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
        .TIMER_CH_Number               = TIMER_CAP_CH,
        .TIMER_CH_Mode                 = TIMER_CH_MODE_CAPTURE,
        .TIMER_CH_UseCCR1              = DISABLE,
        .TIMER_CH_CAP_CCR_EventSource  = TIMER_CH_CAP_CCR_EVNT_SRC_RE,
        .TIMER_CH_CAP_CCR1_EventSource = TIMER_CH_CAP_CCR1_EVNT_SRC_FE,
        .TIMER_CH_CAP_EventPrescaler   = TIMER_CH_CAP_EVNT_PRESCALER_DIV_1,
        .TIMER_CH_CAP_UseEventDelay    = ENABLE,
        .TIMER_CH_CAP_Filter           = TIMER_CH_FILTER_1FF_AT_FDTS,
    };

    RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_CLK_SRC_CPU_C1);
    RST_CLK_PER1_C2_SetPrescaler(TIMER_PER1_C2, RST_CLK_PER1_PRESCALER_DIV_1);
    RST_CLK_PER1_C2_Cmd(TIMER_PER1_C2, ENABLE);

    RST_CLK_PCLKCmd(TIMER_PCLK, ENABLE);

    TIMER_DeInit(TIMER);
    TIMER_CNT_Init(TIMER, &TimerCAP);
    TIMER_CH_Init(TIMER, &TimerChannel);
    TIMER_ITConfig(TIMER, (TIMER_CAP_CCR | TIMER_CAP_CCR1), ENABLE);
}

/**
 * @brief  Timer pin configuration.
 * @param  None.
 * @return None.
 */
void TimerPinConfig(void)
{
    RST_CLK_PCLKCmd(TIMER_CAP_PIN_PORT_PCLK, ENABLE);

    PORT_DeInit(TIMER_CAP_PIN_PORT);
    PORT_InitTypeDef TimerChannelPin = {
        .PORT_Pin       = TIMER_CAP_PIN,
        .PORT_Direction = PORT_DIRECTION_INPUT,
        .PORT_Function  = TIMER_CAP_PIN_FUNC,
        .PORT_Mode      = PORT_MODE_DIGITAL,
        .PORT_Power     = PORT_POWER_NOMINAL_UPTO_2mA,
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
        .PORT_PullUp = PORT_PULL_UP_OFF,
#endif
        .PORT_PullDown = PORT_PULL_DOWN_OFF,
    };
    PORT_Init(TIMER_CAP_PIN_PORT, &TimerChannelPin);
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
}

/**
 * @brief  Interrupt configuration for timer.
 * @param  None.
 * @return None.
 */
void InterruptConfig(void)
{
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    CLIC_IRQ_InitTypeDef CLIC_InitStructIRQ = {
        .CLIC_EnableIRQ        = ENABLE,
        .CLIC_VectorModeIRQ    = DISABLE,
        .CLIC_TriggerIRQ       = CLIC_TRIGGER_IRQ_LEVEL_HIGH,
        .CLIC_PrivilegeModeIRQ = CLIC_PRIVILEGE_MODE_IRQ_M,
        .CLIC_LevelIRQ         = 1,
        .CLIC_PriorityIRQ      = 1,
    };
    CLIC_InitIRQ(TIMER_IRQ, &CLIC_InitStructIRQ);
#elif defined(USE_MDR32F02)
    PLIC_EnableExternalIRQ(PLIC_PRIVILEGE_IRQ_MODE_M);
    PLIC_EnableIRQ(TIMER_IRQ);
#endif
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

/** @} */ /* End of group MDR32VF0xI_TIMER_CAP */

/** @} */ /* End of group TIMER */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


