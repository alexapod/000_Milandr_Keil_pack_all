/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.4
  * @date    30/05/2024
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
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_bkp.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup RST_CLK_CPU_Clock_MDR32F9Q2I RST_CLK_CPU_Clock
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define BLINK_NUM 5
#define BLINK_DELAY 20000

#define LED1            PORT_Pin_0
#define LED2            PORT_Pin_1

/* Private variables ---------------------------------------------------------*/
RST_CLK_FreqTypeDef CLK_FrequencyStructure;
PORT_InitTypeDef PORT_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

void LEDOn(uint32_t LED_Num)
{
    PORT_SetBits(MDR_PORTC, LED_Num);
}

void LEDOff(uint32_t LED_Num)
{
    PORT_ResetBits(MDR_PORTC, LED_Num);
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

    for ( cnt = 0; cnt < num; cnt++)
    {
        LEDOn(LED1);
        Delay(del);
        LEDOff(LED1);
        Delay(del);
    }
}

/**
  * @brief  Indicate error condition with LED3
  * @param  None
  * @retval None
  */
void IndicateError(void)
{
    /* Switch LED3 on and off in case of error */
    LEDOn(LED2);
    Delay(BLINK_DELAY);
    LEDOff(LED2);
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

    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_EEPROM), ENABLE);

    /* Setup internal DUcc voltage regulator work mode based on clock frequency. Added for demonstration, since the same is already done in RST_CLK_DeInit(). */
    BKP_DUccMode(BKP_DUcc_upto_10MHz);

    /* Setup EEPROM access delay to 0 because HSI = 8MHz < 25MHz.
       EEPROM access delay sould be set before the clock frequency increases or
       after the clock frequency decreases. */
    EEPROM_SetLatency(EEPROM_Latency_0);

    PORT_DeInit(MDR_PORTC);

    /* Configure PORTC pins 0,1 for output to switch LEDs on/off */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* Consequently turn all used LEDs on and off */

    LEDOn(LED1);
    Delay(4 * BLINK_DELAY);
    LEDOff(LED1);
    Delay(4 * BLINK_DELAY);
    LEDOn(LED2);
    Delay(4 * BLINK_DELAY);
    LEDOff(LED2);
    Delay(4 * BLINK_DELAY);


    /* Set RST_CLK to default */
    RST_CLK_DeInit(); // Also resets DUcc voltage regulator work mode
    SystemCoreClockUpdate();

    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_EEPROM), ENABLE);

    /* 1. CPU_CLK = HSI clock */

    /* Enable HSI clock source */
    RST_CLK_HSIcmd(ENABLE);
    if (RST_CLK_HSIstatus() == SUCCESS)                     /* Good HSI clock */
    {
        /* Setup internal DUcc voltage regulator work mode based on clock frequency */
        BKP_DUccMode(BKP_DUcc_upto_10MHz);
        /* Setup EEPROM access delay to 0: HSI = 8MHz < 25MHz */
        EEPROM_SetLatency(EEPROM_Latency_0);

        /* Select HSI clock on the CPU clock MUX */
        RST_CLK_CPUclkSelection(RST_CLK_CPUclkHSI);

        SystemCoreClockUpdate();

        /* LED1 blinking with HSI clock as input clock source */
        BlinkLED1(BLINK_NUM, BLINK_DELAY);
    }
    else
    {                                                       /* HSI timeout */
        IndicateError();
    }

    /* 2. CPU_CLK = HSI/2 clock */

    /* Enable HSI clock source */
    RST_CLK_HSIcmd(ENABLE);
    /* Select HSI/2 clock as CPU_C1 input clock source */
    RST_CLK_CPUclkSelectionC1(RST_CLK_CPU_C1srcHSIdiv2);
    if (RST_CLK_HSIstatus() == SUCCESS)                     /* Good HSI clock */
    {
        /* Set CPU_C3_prescaler to 1 */
        RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
        /* Switch CPU_C2_SEL to CPU_C1 clock instead of CPU_PLL output */
        RST_CLK_CPU_PLLuse(DISABLE);
        /* Select CPU_C3 clock on the CPU clock MUX */
        RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

        /* Setup internal DUcc voltage regulator work mode based on clock frequency */
        BKP_DUccMode(BKP_DUcc_upto_10MHz);
        /* Setup EEPROM access delay to 0: HSI/2 = 4MHz < 25MHz */
        EEPROM_SetLatency(EEPROM_Latency_0);

        SystemCoreClockUpdate();

        /* LED1 blinking with HSI/2 clock as input clock source */
        BlinkLED1(BLINK_NUM, BLINK_DELAY);
    }
    else                                                    /* HSI timeout */
    {
        IndicateError();
    }

    /* 3. CPU_CLK = 7*HSE/2 clock */

    /* Enable HSE clock oscillator */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    if (RST_CLK_HSEstatus() == SUCCESS)                     /* Good HSE clock */
    {
        /* Select HSE clock as CPU_PLL input clock source */
        /* Set PLL multiplier to 7                        */
        RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul7);
        /* Enable CPU_PLL */
        RST_CLK_CPU_PLLcmd(ENABLE);
        if (RST_CLK_CPU_PLLstatus() == SUCCESS)             /* Good CPU PLL */
        {
            /* Set CPU_C3_prescaler to 2 */
            RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV2);
            /* Set CPU_C2_SEL to CPU_PLL output instead of CPU_C1 clock */
            RST_CLK_CPU_PLLuse(ENABLE);

            /* Setup internal DUcc voltage regulator work mode based on clock frequency */
            BKP_DUccMode(BKP_DUcc_upto_40MHz);
            /* Setup EEPROM access delay to 1: 7*HSE/2 = 28MHz > 25MHz */
            EEPROM_SetLatency(EEPROM_Latency_1);

            /* Select CPU_C3 clock on the CPU clock MUX */
            RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

            SystemCoreClockUpdate();

            /* LED1 blinking with 7*HSE/2 clock as input clock source */
            BlinkLED1(BLINK_NUM, BLINK_DELAY);
        }
        else                                                /* CPU_PLL timeout */
        {
            IndicateError();
        }
    }
    else                                                    /* HSE timeout */
    {
        IndicateError();
    }

    /* 4. CPU_CLK = LSI clock */

    /* Enable LSI clock source */
    RST_CLK_LSIcmd(ENABLE);
    if (RST_CLK_LSIstatus() == SUCCESS)                     /* Good LSI clock */
    {
        /* Select LSI clock on the CPU clock MUX */
        RST_CLK_CPUclkSelection(RST_CLK_CPUclkLSI);

        /* Setup internal DUcc voltage regulator work mode based on clock frequency */
        BKP_DUccMode(BKP_DUcc_upto_500kHz);
        /* Setup EEPROM access delay to 0: LSI = 32kHz < 25MHz */
        EEPROM_SetLatency(EEPROM_Latency_0);

        /* Disable CPU_PLL which was used on previous step */
        RST_CLK_CPU_PLLcmd(DISABLE);

        SystemCoreClockUpdate();

        /* LED1 blinking with LSI clock as input clock source */
        BlinkLED1(BLINK_NUM, BLINK_DELAY);
    }
    else                                                    /* LSI timeout */
    {
        IndicateError();
    }

    while(1) {}
}

/**
  * @brief  Executes delay loop.
  * @param  nCount: specifies the delay.
  * @retval None.
  */
void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

/**
  * @brief  Reports the source file name, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name.
  * @param  line: assert_param error line source number.
  * @param  expr:
  * @retval None.
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

/** @} */ /* End of group RST_CLK_CPU_Clock_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


