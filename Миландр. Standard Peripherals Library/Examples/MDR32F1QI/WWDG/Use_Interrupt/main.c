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
  * <h2><center>&copy; COPYRIGHT 2025 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_wwdg.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup WWDG_Use_Interrupt_MDR32F1QI WWDG_Use_Interrupt
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define LED1            PORT_Pin_7

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
uint32_t wwdg_flag = RESET;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  WWDG interrupt handler.
  * @param  None
  * @retval None
  */
void WWDG_IRQHandler(void)
{
    /* Clears Early Wakeup interrupt flag */
    WWDG_ClearFlag();

    /* Load counter value */
    WWDG_SetCounter(0x7F);

    wwdg_flag = SET;
}

void LEDOn(uint32_t LED_Num)
{
    PORT_SetBits(MDR_PORTD, LED_Num);
}

void LEDOff(uint32_t LED_Num)
{
    PORT_ResetBits(MDR_PORTD, LED_Num);
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

    for(cnt = 0; cnt < num; cnt++)
    {
        LEDOn(LED1);
        Delay(del);
        LEDOff(LED1);
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

    /* Enables the HSI clock for PORTD */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);

    PORT_DeInit(MDR_PORTD);

    /* Configure PORTD pin 7 for output to switch LEDs on/off */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = PORT_Pin_7;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    BlinkLED1(5, 30000);

    /* Enables the HSI clock for WWDG */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_WWDG, ENABLE);

    NVIC_EnableIRQ(WWDG_IRQn);

    /* Set WWDG Prescaler value*/
    WWDG_SetPrescaler(WWDG_Prescaler_8);

    /* Enable WWDG and load start counter value*/
    WWDG_Enable(0x7F);

    /* Enables the WWDG Early Wakeup interrupt */
    WWDG_EnableIT();

    /* Infinite loop */
    while(1)
    {
        if (wwdg_flag == SET)
        {
            BlinkLED1(1, 30000);
            wwdg_flag = RESET;
        }
    }
}

/**
  * @brief  Executes delay loop.
  * @param  nCount: specifies the delay.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--);
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

/** @} */ /* End of group WWDG_Use_Interrupt_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


