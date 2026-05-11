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

/** @addtogroup MDR32VF0xI_MDR32F02_BOARD MDR32F02 Evaluation Board
 * @{
 */

/** @addtogroup OTP OTP
 * @{
 */

/** @addtogroup MDR32F02_OTP_Word MDR32F02_OTP_Word
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_otp.h"
#include "MDR32VF0xI_utils.h"
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_rst_clk.h"

/* Private definitions -------------------------------------------------------*/
#define LED_PORT     MDR_PORTD
#define LED_PORT_CLK RST_CLK_PCLK_PORTD
#define LED_PIN_1    PORT_PIN_0
#define LED_PIN_2    PORT_PIN_1
#define LED_PIN_3    PORT_PIN_2
#define LED_PIN_4    PORT_PIN_3
#define LED_PINS     (LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4)

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);
void LedConfig(void);
void OTP_Config(void);
void IndicateInvalid(void);
void IndicateValid(void);

/* Private variables ---------------------------------------------------------*/
volatile uint32_t ReadWord;
const uint32_t    WriteWord            = 0xF1402D73;
const uint32_t    OTP_ReadWriteAddress = (uintptr_t)OTP_SPECIAL_FIELDS - 128;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();
    LedConfig();
    OTP_Config();

    /* Read word from OTP. */
    ReadWord = OTP_ReadWord(OTP_ReadWriteAddress);

    /* If read word address is clear - program OTP word. */
    if (ReadWord == 0x00000000) {
        OTP_ProgramWord(OTP_ReadWriteAddress, WriteWord);
    }

    /* Read word from OTP again for validation. */
    ReadWord = OTP_ReadWord(OTP_ReadWriteAddress);

    /* Indicate validation. */
    if (ReadWord != WriteWord) {
        IndicateInvalid();
    } else {
        IndicateValid();
    }
}

/**
 * @brief  OTP configuration.
 * @param  None.
 * @return None.
 */
void OTP_Config(void)
{
    OTP_RegDelays_InitTypeDef OTP_Delays;
    /* Setup OTP register access delays. */
    OTP_RegAccessDelaysStructConfig(&OTP_Delays, HSE_FREQUENCY_Hz);
    OTP_RegAccessDelaysConfig(&OTP_Delays);

    /* Setup OTP AHB delay - not necessary on 8 MHz, used for demonstration purposes. */
    OTP_SetAHBDelay(OTP_AHB_DELAY_CYCLE_1);
}

/**
 * @brief  Clock configuration.
 * @param  None.
 * @return None.
 */
void ClockConfig(void)
{
    RST_CLK_DeInit();
    SystemCoreClockUpdate();

    RST_CLK_HSE_Config(RST_CLK_HSE_ON);
    while (RST_CLK_HSE_GetStatus() != SUCCESS) { }

    RST_CLK_CPU_C1_ClkSelection(RST_CLK_CPU_C1_CLK_SRC_HSE);
    RST_CLK_CPU_C2_ClkSelection(RST_CLK_CPU_C2_CLK_SRC_CPU_C1);
    RST_CLK_CPU_C3_SetPrescaler(RST_CLK_CPU_C3_PRESCALER_DIV_1);
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_CPU_C3);
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
    PORT_WriteBit(LED_PORT, LED_PINS, SET);
}

/**
 * @brief  Invalid result indication.
 * @param  None.
 * @return None.
 */
void IndicateInvalid(void)
{
    DELAY_Init(DELAY_MODE_CYCLE_COUNTER);
    while (1) {
        DELAY_WaitMs(500);
        PORT_ToggleBit(LED_PORT, (LED_PIN_3 | LED_PIN_4));
    }
}

/**
 * @brief  Valid result indication.
 * @param  None.
 * @return None.
 */
void IndicateValid(void)
{
    DELAY_Init(DELAY_MODE_CYCLE_COUNTER);
    while (1) {
        DELAY_WaitMs(500);
        PORT_ToggleBit(LED_PORT, (LED_PIN_1 | LED_PIN_2));
    }
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

/** @} */ /* End of group MDR32F02_OTP_Word */

/** @} */ /* End of group OTP */

/** @} */ /* End of group MDR32VF0xI_MDR32F02_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


