/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    29/04/2025
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

/** @addtogroup CORE CORE
 * @{
 */

/** @addtogroup MDR32VF0xI_CORE_MTIMER MDR32VF0xI_CORE_MTIMER
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_rst_clk.h"
#if defined(USE_MDR32F02_REV_1X)
#include "MDR32VF0xI_bkp.h"
#endif
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
void        ClockConfig(void);
ErrorStatus MachineTimerConfig(void);
void        LedConfig(void);
void        InterruptConfig(void);

/* Private variables ---------------------------------------------------------*/
RST_CLK_Freq_TypeDef Freqs;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Machine timer interrupt handler.
 * @param  None.
 * @return None.
 */
void MTIP_IRQHandler(void)
{
    CLINT_MTIMER_SetCompareTime(CLINT_MTIMER_GetTime() + Freqs.MachineTimer_Frequency);
    PORT_ToggleBit(LED_PORT, LED_PINS);
}

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();

    /* SUCCESS/ERROR check is only valid for MDR32F02 rev 1 and 1.1.
       For MDR1206FI, MDR1206AFI function always returns SUCCESS.
       NOTE: MDR32F02 rev 1 and 1.1 uses LSE as machine timer clock source. MDR1206FI, MDR1206AFI use divided system clock. */
    if (MachineTimerConfig() == ERROR) {
        while (1) { }
    }

    RST_CLK_GetClocksFreq(&Freqs, RST_CLK_CLOCK_FREQ_MACHINE_TIMER);

    LedConfig();

    CLINT_MTIMER_SetCompareTime(CLINT_MTIMER_GetTime() + Freqs.MachineTimer_Frequency);

    InterruptConfig();

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
 * @brief  Machine timer configuration.
 * @param  None.
 * @return @ref ErrorStatus - SUCCESS if machine timer is configured, else ERROR.
 */
ErrorStatus MachineTimerConfig(void)
{
#if defined(USE_MDR32F02_REV_1X)
    RST_CLK_PCLKCmd(RST_CLK_PCLK_BKP, ENABLE);

    BKP_SetRegistersLock(RESET);
    BKP_DeInit();
    /* Take into account MDR32F02 errata 0001 - LSE generator should be used. */
    BKP_LSE_Config(BKP_LSE_BYPASS);
    return BKP_LSI_GetStatus();
#else
    RST_CLK_SystemTimer_SetPrescaler(HSI_FREQUENCY_Hz / LSE_FREQUENCY_Hz);
    return SUCCESS;
#endif
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
 * @brief  Interrupt configuration for machine timer.
 * @param  None.
 * @return None.
 */
void InterruptConfig(void)
{
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    static const CLIC_IRQ_InitTypeDef CLIC_InitStructIRQ = {
        .CLIC_EnableIRQ        = ENABLE,
        .CLIC_VectorModeIRQ    = DISABLE,
        .CLIC_TriggerIRQ       = CLIC_TRIGGER_IRQ_LEVEL_HIGH,
        .CLIC_PrivilegeModeIRQ = CLIC_PRIVILEGE_MODE_IRQ_M,
        .CLIC_LevelIRQ         = 1,
        .CLIC_PriorityIRQ      = 1,
    };
    CLIC_InitIRQ(MTIP_IRQn, &CLIC_InitStructIRQ);
#elif defined(USE_MDR32F02)
    PLIC_EnableMTIMERIRQ(PLIC_PRIVILEGE_IRQ_MODE_M);
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

/** @} */ /* End of group MDR32VF0xI_CORE_MTIMER */

/** @} */ /* End of group CORE */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


