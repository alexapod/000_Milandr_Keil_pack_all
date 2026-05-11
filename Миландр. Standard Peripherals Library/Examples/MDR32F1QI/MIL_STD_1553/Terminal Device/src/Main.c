/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    20/06/2023
  * @brief   This file contains example of use of the interface MIL_STD_1553.
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
#include "stdio.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_bkp.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_mil_std_1553.h"
#include "MDR32FxQI_utils.h"
#include "MDR32FxQI_timer.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Terminal_Device_IT MIL_STD_1553 Terminal Device
 *  @{
 */

/* Private define ------------------------------------------------------------*/
#define MY_MIL_STD_1553                 MDR_MIL_STD_15531

#define ONE_WORD_TIME_RECEIVING_mkS     20

/* Private macro -------------------------------------------------------------*/
#if defined (_USE_DEBUG_UART_)
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...)
#endif /* #if defined _USE_DEBUG_UART_ */


/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;
static MIL_STD_1553_InitTypeDef MIL_STD_1553InitStructure;
static TIMER_CntInitTypeDef TIMER1_CntInitStructure;
static RST_CLK_FreqTypeDef RST_CLK_FreqStructure;

/* Private function prototypes -----------------------------------------------*/
void ClockConfigure(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
#if defined (_USE_DEBUG_UART_)
    ErrorStatus Status;
#endif

    /* Configure CPU clock */
    ClockConfigure();
    SystemCoreClockUpdate();

#if defined (_USE_DEBUG_UART_)
    Status = STDIO_Init();
    if (Status == ERROR) {
        while (1) {}
    }
#endif /* #if defined (_USE_DEBUG_UART_) */

    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_MIL_STD_15532 | RST_CLK_PCLK_MIL_STD_15531 |
                    RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD |
                    RST_CLK_PCLK_PORTB) , ENABLE);

    PORT_DeInit(MDR_PORTB);
    PORT_DeInit(MDR_PORTC);
    PORT_DeInit(MDR_PORTD);

    /* LEDs Port Init */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10 |
                                     PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14);
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;

    PORT_Init(MDR_PORTD, &PORT_InitStructure);
    DEBUG_PRINTF("Init LEDs PORT ... Ok\r\n");

    /* Configure PORTC pins 13, 14, 15 */
    PORT_InitStructure.PORT_Pin = (PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15);
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_MAIN;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* Configure PORTD pin 0 */
    PORT_InitStructure.PORT_Pin = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 |
                                   PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6);
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Reset all MIL_STD_15531 settings */
    MIL_STD_1553_DeInit(MY_MIL_STD_1553);

    MIL_STD_1553_BRGInit(MIL_STD_1553_HCLKdiv1);

    /* MIL_STD_15531 configuration*/
    /* Initialize MIL_STD_1553_InitStructure */
    MIL_STD_1553xStructInit(&MIL_STD_1553InitStructure);
    MIL_STD_1553InitStructure.MIL_STD_1553_Mode = MIL_STD_1553_ModeTerminal;
    MIL_STD_1553InitStructure.MIL_STD_1553_RERR = ENABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_DIV  = 80;
    MIL_STD_1553InitStructure.MIL_STD_1553_RTA  = MIL_STD_1553_TERMINAL_ADDRESS;
    MIL_STD_1553InitStructure.MIL_STD_1553_TRA  = ENABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_TRB  = ENABLE;

    /* Configure MIL_STD_15532 parameters*/
    MIL_STD_1553_Init(MY_MIL_STD_1553, &MIL_STD_1553InitStructure);

    MIL_STD_1553_ITConfig(MY_MIL_STD_1553, (MIL_STD_1553_IT_ERRIE |
                        MIL_STD_1553_IT_VALMESSIE | MIL_STD_1553_IT_RFLAGNIE),
                        ENABLE);

    NVIC_EnableIRQ(MIL_STD_1553B2_IRQn);
    NVIC_EnableIRQ(MIL_STD_1553B1_IRQn);

    /* Init TIMER1 */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);

    TIMER_DeInit(MDR_TIMER1);

    TIMER_CntStructInit(&TIMER1_CntInitStructure);

    TIMER_BRGInit(MDR_TIMER1, TIMER_HCLKdiv1);

    RST_CLK_GetClocksFreq(&RST_CLK_FreqStructure);

    TIMER1_CntInitStructure.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
    TIMER1_CntInitStructure.TIMER_Period      = (RST_CLK_FreqStructure.CPU_CLK_Frequency / 1000000
                                                * ONE_WORD_TIME_RECEIVING_mkS);

    TIMER_CntInit(MDR_TIMER1, &TIMER1_CntInitStructure);

    TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ARR, ENABLE);

    NVIC_EnableIRQ(TIMER1_IRQn);

    /* Enables MIL_STD_15531 peripheral */
    MIL_STD_1553_Cmd(MY_MIL_STD_1553, ENABLE);

    DEBUG_PRINTF("Init MIL_STD_15531 ... Ok\r\n");

    /* Infinity loop */
    while(1) {}
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure CPU clock.
  * @param  None
  * @retval None
  */
void ClockConfigure(void)
{
    RST_CLK_DeInit();

    /* Enable HSE (High Speed External) clock */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    while(RST_CLK_HSEstatus() == ERROR) {}

    /* Configures the CPU_PLL clock source */
    RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);

    /* Enables the CPU_PLL */
    RST_CLK_CPU_PLLcmd(ENABLE);
    while(RST_CLK_CPU_PLLstatus() == ERROR) {}

    /* Select the CPU_PLL output as input for CPU_C3_SEL */
    RST_CLK_CPU_PLLuse(ENABLE);
    /* Set CPUClk Prescaler */
    RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

    /* Enables the RST_CLK_PCLK_EEPROM */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
    /* Sets the code latency value */
    EEPROM_SetLatency(EEPROM_Latency_3);

    /* Setup internal DUcc voltage regulator work mode based on clock frequency */
    BKP_DUccMode(BKP_DUcc_upto_80MHz);

    /* Select the CPU clock source */
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
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

/** @} */ /* Enf of group MIL_STD_1553_Terminal_Device */

/** @} */ /* End of group __MDR32F1QI_EVAL MDR32F1QI Evaluation Board */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr ********************************
*
* END OF FILE main.c */


