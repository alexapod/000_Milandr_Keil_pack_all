/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    02/06/2025
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

/** @addtogroup BKP BKP
 * @{
 */

/** @addtogroup MDR32VF0xI_BKP_TAMPER MDR32VF0xI_BKP_TAMPER
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_bkp.h"
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_rst_clk.h"
#include "MDR32VF0xI_utils.h"
#include "system_MDR32VF0xI_it.h"

/* Private definitions -------------------------------------------------------*/
#define LED_PORT     MDR_PORTD
#define LED_PORT_CLK RST_CLK_PCLK_PORTD
#define LED_PIN_1    PORT_PIN_5
#define LED_PIN_2    PORT_PIN_6
#define LED_PIN_3    PORT_PIN_7
#define LED_PIN_4    PORT_PIN_8
#define LED_PINS     (LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4)

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);
void LedConfig(void);
void BKP_TAMPER_Config(void);
void InterruptConfig(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  BKP TAMPER interrupt handler.
 * @param  None.
 * @return None.
 */
void BKP_IRQHandler(void)
{
    if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_TAMPER_W1) == SET) {
        PORT_ToggleBit(LED_PORT, LED_PIN_1);
    }
    if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_TAMPER_W2) == SET) {
        PORT_ToggleBit(LED_PORT, LED_PIN_2);
    }
    if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_TAMPER_W3) == SET) {
        PORT_ToggleBit(LED_PORT, LED_PIN_3);
    }
    DELAY_WaitMs(100);
    BKP_RTC_ClearFlags(BKP_RTC_FLAG_TAMPER);
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

    BKP_TAMPER_Config();

    InterruptConfig();

    DELAY_Init(DELAY_MODE_CYCLE_COUNTER);

    while (1) {
        PORT_ToggleBit(LED_PORT, LED_PIN_4);
        DELAY_WaitMs(100);
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
}

/**
 * @brief  BKP TAMPER configuration.
 * @param  None.
 * @return None.
 */
void BKP_TAMPER_Config(void)
{
    RST_CLK_PCLKCmd(RST_CLK_PCLK_BKP, ENABLE);

    BKP_SetRegistersLock(RESET);
    BKP_DeInit(BKP_ALL);

    /* BKP TAMPER logic is clocked by RTC. */
    BKP_LSI_Cmd(ENABLE);
    while (BKP_LSI_GetStatus() == ERROR) { }
    BKP_RTC_SetClkSource(BKP_RTC_CLK_SRC_LSI);
    BKP_RTC_WaitClkSwitch(BKP_RTC_CLK_SRC_LSI);

    BKP_RTC_TAMPER_SetEvent(BKP_RTC_TAMPER_W1, BKP_RTC_TAMPER_EVNT_EDGE_FALLING_LEVEL_LOW);
    BKP_RTC_TAMPER_SetEvent(BKP_RTC_TAMPER_W2, BKP_RTC_TAMPER_EVNT_EDGE_FALLING_LEVEL_LOW);
    BKP_RTC_TAMPER_SetEvent(BKP_RTC_TAMPER_W3, BKP_RTC_TAMPER_EVNT_EDGE_FALLING_LEVEL_LOW);
    BKP_RTC_TAMPER_Cmd(BKP_RTC_TAMPER_ALL, ENABLE);
    BKP_RTC_ClearFlags(BKP_RTC_FLAG_TAMPER);
    BKP_RTC_ITConfig(BKP_RTC_IT_TAMPER, ENABLE);
}

/**
 * @brief  Interrupt configuration for BKP tampers.
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
    CLIC_InitIRQ(BKP_IRQn, &CLIC_InitStructIRQ);
#elif defined(USE_MDR32F02)
    PLIC_EnableIRQ(BKP_IRQn);
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

/** @} */ /* End of group MDR32VF0xI_BKP_TAMPER */

/** @} */ /* End of group BKP */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


