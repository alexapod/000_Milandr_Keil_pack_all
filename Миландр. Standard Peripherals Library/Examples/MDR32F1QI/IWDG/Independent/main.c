/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.1.0
  * @date    22/10/2024
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
#include "MDR32FxQI_iwdg.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup IWDG_INDEPENDENT_MDR32F1QI IWDG_Independent
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define LED1_PIN        PORT_Pin_7
#define LED1_PORT       MDR_PORTD
#define LED1_PORT_PCLK  RST_CLK_PCLK_PORTD

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

void LEDOn(uint32_t LED_Num)
{
    PORT_SetBits(LED1_PORT, LED_Num);
}

void LEDOff(uint32_t LED_Num)
{
    PORT_ResetBits(LED1_PORT, LED_Num);
}

/**
  * @brief  Blink with LED1
  * @param  num - blinks number
  * @param  del - delay
  * @retval None
  */
void BlinkLED1(uint32_t num, uint32_t del)
{
    uint32_t cnt;

    for (cnt = 0; cnt < num; cnt++)
    {
        LEDOn(LED1_PIN);
        Delay(del);
        LEDOff(LED1_PIN);
        Delay(del);
    }
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

    /* Enables the HSI clock for port with LED1 pin */
    RST_CLK_PCLKcmd(LED1_PORT_PCLK, ENABLE);

    PORT_DeInit(LED1_PORT);

    /* Configure LED1 pin for output to switch LED on/off */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = LED1_PIN;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
    PORT_Init(LED1_PORT, &PORT_InitStructure);

    BlinkLED1(5, 30000);

    /* Enables the HSI clock for IWDG */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_IWDG, ENABLE);

    /* Enables write access to IWDG_PR,IWDG_RLR registers */
    IWDG_WriteAccessEnable();

    /* Set IWDG Prescaler value */
    IWDG_SetPrescaler(IWDG_Prescaler_128);

    IWDG_Enable();

    /* Wait when Prescaler Value was updated */
    while(IWDG_GetFlagStatus(IWDG_FLAG_PVU) == SET) {}

    /* Enables write access to IWDG_PR,IWDG_RLR registers */
    IWDG_WriteAccessEnable();

    /* Set IWDG Reload value and reload */
    IWDG_SetReload(0xFFF);
    IWDG_ReloadCounter();

    /* Infinite loop */
    while(1)
    {
        /* Load counter value and blink LED after delay */
        Delay(1000000);
        IWDG_ReloadCounter();
        BlinkLED1(1, 30000);
    }
}

/**
  * @brief  Executes delay loop.
  * @param  nCount: specifies the delay.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--) {}
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

/** @} */ /* End of group IWDG_Independent_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


