/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.1.0
  * @date    27/06/2023
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
#include "MDR32FxQI_timer.h"
#include "MDR32FxQI_dma.h"
#include "MDR32FxQI_bkp.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
 * @{
 */

/** @addtogroup BKP_SLEEP_MDR32F1QI BKP_SLEEP
 * @{
 */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize button that, when pressed, will put the MCU into sleep mode.
  * @param  None.
  * @retval None.
  */
void BTN_Pin_Init(void)
{
    PORT_InitTypeDef PORT_ButtonInitStructure;

    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);
    PORT_DeInit(MDR_PORTE);

    /* PE9 is connected to SELECT button on evaluation board */
    PORT_StructInit(&PORT_ButtonInitStructure);
    PORT_ButtonInitStructure.PORT_Pin   = (PORT_Pin_9);
    PORT_ButtonInitStructure.PORT_OE    = PORT_OE_IN;
    PORT_ButtonInitStructure.PORT_PD    = PORT_PD_DRIVER;
    PORT_ButtonInitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_ButtonInitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_ButtonInitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTE, &PORT_ButtonInitStructure);
}


/**
  * @brief  Initialize LEDS to indicate MCU state.
  * @param  None.
  * @retval None.
  */
void LED_Pins_Init(void)
{
    PORT_InitTypeDef PORT_InitStructure;

    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
    PORT_DeInit(MDR_PORTD);

    PORT_StructInit(&PORT_InitStructure);

    /* PD8 - VD7 - sleep mode indicator */
    /* PD9 - VD8 - not-sleeping indicator */
    /* PD10 - VD9 - wake switch indicator */
    PORT_InitStructure.PORT_Pin       = (PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10);
    PORT_InitStructure.PORT_OE        = PORT_OE_OUT;
    PORT_InitStructure.PORT_PD        = PORT_PD_DRIVER;
    PORT_InitStructure.PORT_PULL_UP   = PORT_PULL_UP_OFF;
    PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
    PORT_InitStructure.PORT_FUNC      = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE      = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED     = PORT_SPEED_SLOW;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);
}


/**
  * @brief  Initialize a timer, upon interrupt from which the MCU will wake up.
  * @param  None.
  * @retval None.
  */
void TIMER_Init(void)
{
    TIMER_BRGInit(MDR_TIMER1,TIMER_HCLKdiv128);
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);

    TIMER_CntInitTypeDef sTIM_CntInit;

    TIMER_DeInit(MDR_TIMER1);

    sTIM_CntInit.TIMER_IniCounter       = 0x186A0;
    sTIM_CntInit.TIMER_CounterMode      = TIMER_CntMode_ClkFixedDir;
    sTIM_CntInit.TIMER_CounterDirection = TIMER_CntDir_Dn;
    sTIM_CntInit.TIMER_EventSource      = TIMER_EvSrc_TIM_CLK;
    sTIM_CntInit.TIMER_FilterSampling   = TIMER_FDTS_TIMER_CLK_div_1;
    sTIM_CntInit.TIMER_ARR_UpdateMode   = TIMER_ARR_Update_Immediately;
    sTIM_CntInit.TIMER_ETR_FilterConf   = TIMER_Filter_1FF_at_TIMER_CLK;
    sTIM_CntInit.TIMER_ETR_Prescaler    = TIMER_ETR_Prescaler_None;
    sTIM_CntInit.TIMER_ETR_Polarity     = TIMER_ETRPolarity_NonInverted;
    sTIM_CntInit.TIMER_BRK_Polarity     = TIMER_BRKPolarity_NonInverted;
    TIMER_CntInit(MDR_TIMER1, &sTIM_CntInit);

    /* Timer interrupt event config: CNT == 0 */
    TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ZERO, ENABLE);

    NVIC_EnableIRQ(TIMER1_IRQn);
}


/**
  * @brief  TIMER1 interrupt handler.
  * @param  None.
  * @retval None.
  */
void TIMER1_IRQHandler(void)
{
    /* Reset interrupt request */
    TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CNT_ZERO);

    /* Toggle wake switch indicator */
    if (PORT_ReadInputDataBit(MDR_PORTD, PORT_Pin_10) == RESET)
    {
        PORT_SetBits(MDR_PORTD, PORT_Pin_10);
    }
    else
    {
        PORT_ResetBits(MDR_PORTD, PORT_Pin_10);
    }

    /* Re-initialize timer counter value */
    TIMER_SetCounter(MDR_TIMER1, 0x186A0);

    /* Disable timer */
    TIMER_Cmd(MDR_TIMER1, DISABLE);
}

int main(void)
{
    uint32_t i;

    RST_CLK_DeInit();
    SystemCoreClockUpdate();

    BTN_Pin_Init();
    LED_Pins_Init();
    TIMER_Init();

    RST_CLK_PCLKcmd(RST_CLK_PCLK_DMA, ENABLE);
    DMA_DeInit();

    while(1)
    {
        /* Monitor SELECT button (PE9) to put the MCU into sleep mode */
        if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_9) == 0)
        {
            /* Enable TIMER1 from which interrupt MCU will wake up */
            TIMER_Cmd(MDR_TIMER1, ENABLE);
            /* Enable LED on PD8 to indicate MCU is in sleep mode */
            PORT_SetBits(MDR_PORTD, PORT_Pin_8);
            BKP_EnterSLEEPMode();
        }

        /* Reset LED on PD8 to inditate MCU has woken up */
        PORT_ResetBits(MDR_PORTD, PORT_Pin_8);

        /* Continiously toogle LED on PD9 to inditate MCU is working */
        for(i = 0; i < 100000; i++) {}
        PORT_SetBits(MDR_PORTD, PORT_Pin_9);
        for(i = 0; i < 100000; i++) {}
        PORT_ResetBits(MDR_PORTD, PORT_Pin_9);
    }
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

/** @} *//* End of group BKP_SLEEP_MDR32F1QI */

/** @} *//* End of group __MDR32F1QI_EVAL */

/** @} *//* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


