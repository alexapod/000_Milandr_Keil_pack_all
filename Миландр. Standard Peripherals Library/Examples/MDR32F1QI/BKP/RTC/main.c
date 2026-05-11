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
#include "MDR32FxQI_config.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_bkp.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup BKP_RTC_MDR32F1QI BKP_RTC
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define RTC_LSE_CLK

#define COUNT_VALUE     0
#define ALARM_VALUE     60
#define PRESC_VALUE_HS  1000000
#define PRESC_VALUE_LSI 32000
#define PRESC_VALUE_LSE 32768
#define RTCHSI_PRESC    RST_CLK_HSIclkDIV8
#define RTCHSE_PRESC    RST_CLK_HSEclkDIV8

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  BKP interrupt handler.
  * @param  None
  * @retval None
  */
void BKP_IRQHandler(void)
{
    if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_SECF) == SET)
    {
        if (PORT_ReadInputDataBit(MDR_PORTD, PORT_Pin_10) == 0)
        {
            PORT_SetBits(MDR_PORTD, PORT_Pin_10);
        }
        else
        {
            PORT_ResetBits(MDR_PORTD, PORT_Pin_10);
        }
    }
    if (BKP_RTC_GetFlagStatus(BKP_RTC_FLAG_ALRF) == SET)
    {
        PORT_SetBits(MDR_PORTD, PORT_Pin_11);
    }
    BKP_RTC_ClearFlagStatus(BKP_RTC_FLAG_SECF | BKP_RTC_FLAG_ALRF);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Deinit RST_CLK */
    RST_CLK_DeInit();
    SystemCoreClockUpdate();

    /* Enables the HSI clock on PORTD */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);

    /* Deinit PORTD pins */
    PORT_DeInit(MDR_PORTD);

    /* Configure PORTD pins 10..11 for output to switch LEDs on/off */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_10 | PORT_Pin_11);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Enables the HSI clock for BKP control */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_BKP, ENABLE);

    /* Deinit BKP */
    BKP_DeInit();

    /* RTC reset */
    BKP_RTC_Reset(ENABLE);
    BKP_RTC_Reset(DISABLE);

#ifdef RTC_HSI_CLK
    /* Configure RTCHSI as RTC clock source */
    RST_CLK_HSIadjust(25);
    RST_CLK_RTC_HSIclkEnable(ENABLE);
    RST_CLK_HSIclkPrescaler(RTCHSI_PRESC);
    BKP_RTCclkSource(BKP_RTC_HSIclk);
#endif
#ifdef RTC_HSE_CLK
    /* Configure RTCHSE as RTC clock source */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    while(RST_CLK_HSEstatus() != SUCCESS);
    RST_CLK_RTC_HSEclkEnable(ENABLE);
    RST_CLK_HSEclkPrescaler(RTCHSE_PRESC);
    BKP_RTCclkSource(BKP_RTC_HSEclk);
#endif
#ifdef RTC_LSI_CLK
    /* Configure LSI as RTC clock source */
    RST_CLK_LSIadjust(12);
    BKP_RTCclkSource(BKP_RTC_LSIclk);
    while(RST_CLK_LSIstatus() != SUCCESS);
#endif
#ifdef RTC_LSE_CLK
    /* Configure LSE as RTC clock source */
    RST_CLK_LSEconfig(RST_CLK_LSE_ON);
    while(RST_CLK_LSEstatus() != SUCCESS);
    BKP_RTCclkSource(BKP_RTC_LSEclk);
#endif

    /* Set the RTC prescaler value */
    BKP_RTC_WaitForUpdate();
#ifdef RTC_HSI_CLK
    BKP_RTC_SetPrescaler(PRESC_VALUE_HS - 1);
#endif
#ifdef RTC_HSE_CLK
    BKP_RTC_SetPrescaler(PRESC_VALUE_HS - 1);
#endif
#ifdef RTC_LSI_CLK
    BKP_RTC_SetPrescaler(PRESC_VALUE_LSI - 1);
#endif
#ifdef RTC_LSE_CLK
    BKP_RTC_SetPrescaler(PRESC_VALUE_LSE - 1);
#endif

    /* Set the RTC alarm value */
    BKP_RTC_WaitForUpdate();
    BKP_RTC_SetAlarm(ALARM_VALUE - 1);

    /* Set the RTC counter value */
    BKP_RTC_WaitForUpdate();
    BKP_RTC_SetCounter(COUNT_VALUE);

    /* Enable all RTC interrupts */
    BKP_RTC_ITConfig((BKP_RTC_IT_ALRF | BKP_RTC_IT_SECF | BKP_RTC_IT_OWF), ENABLE);
    NVIC_EnableIRQ(BKP_IRQn);

    /* RTC enable */
    BKP_RTC_WaitForUpdate();
    BKP_RTC_WorkPermit(ENABLE);

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

/** @} */ /* End of group BKP_RTC_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


