/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    20/06/2023
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
#include "stdio.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_bkp.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_mil_std_1553.h"
#include "MDR32FxQI_utils.h"
#include "MIL_STD_1553_BusController.h"


/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Bus_Controller_MDR32F1QI MIL_STD_1553 Bus Controller
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

/* Varibles ------------------------------------------------------------------*/
uint32_t MIL_STD_1553_LastRequest = 0;
extern uint32_t MIL_STD_1553_LastRequest;
MIL_STD_1553_CommandWordTypeDef CommandWord = {0};

/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;
static MIL_STD_1553_InitTypeDef MIL_STD_1553InitStructure;

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
    uint8_t CMDkey = 0;
    uint32_t i;
    static uint32_t TestData[32];

    /* Configure CPU clock */
    ClockConfigure();
    SystemCoreClockUpdate();

#if defined(_USE_DEBUG_UART_)
    Status = STDIO_Init();
    if (Status == ERROR) {
        while (1) {}
    }
#endif /* #if defined (_USE_DEBUG_UART_) */

    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_MIL_STD_15531 | RST_CLK_PCLK_PORTB |
                    RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD), ENABLE);

    PORT_DeInit(MDR_PORTB);
    PORT_DeInit(MDR_PORTC);
    PORT_DeInit(MDR_PORTD);

    /* LEDs Port Init */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 |
                                     PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7);
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;

    PORT_Init(MDR_PORTB, &PORT_InitStructure);

    DEBUG_PRINTF("Init LEDs PORT ... Ok\r\n");

    /* MIL_STD_15531 port configuration */
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15);
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_MAIN;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* Configure PORTD pin 0 */
    PORT_InitStructure.PORT_Pin = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 |
                                   PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6);
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Reset all MIL_STD_15531 settings */
    MIL_STD_1553_DeInit(MY_MIL_STD_1553);
    MIL_STD_1553_BRGInit(MIL_STD_1553_HCLKdiv1);

    /* MIL_STD_15531 configuration */
    /* Initialize MIL_STD_1553_InitStructure */
    MIL_STD_1553xStructInit(&MIL_STD_1553InitStructure);
    MIL_STD_1553InitStructure.MIL_STD_1553_Mode = MIL_STD_1553_ModeBusController;
    MIL_STD_1553InitStructure.MIL_STD_1553_RERR = ENABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_DIV  = 80;
    MIL_STD_1553InitStructure.MIL_STD_1553_RTA  = 0;
    MIL_STD_1553InitStructure.MIL_STD_1553_TRA  = ENABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_TRB  = DISABLE;

    /* Configure MIL_STD_15531 parameters*/
    MIL_STD_1553_Init(MY_MIL_STD_1553, &MIL_STD_1553InitStructure);

    MIL_STD_1553_ITConfig(MY_MIL_STD_1553, (MIL_STD_1553_IT_ERRIE | MIL_STD_1553_IT_VALMESSIE), ENABLE);

    NVIC_EnableIRQ(MIL_STD_1553B1_IRQn);

    /* Enables MIL_STD_15531 peripheral */
    MIL_STD_1553_Cmd(MY_MIL_STD_1553, ENABLE);

    DEBUG_PRINTF("Init MIL_STD_15531 ... Ok\r\n");

    /* Infinity loop */
    CMDkey = 0x34;
    while(1)
    {
        DEBUG_PRINTF("\r\nEnter test type:\r\n"
                     "1 - Write data to terminal device\r\n"
                     "2 - Read data from terminal device\r\n"
                     "3 - Get status word\r\n"
                     "4 - Get last command word\r\n");
        while(1)
        {
            scanf("%c",&CMDkey);
            if ((CMDkey > 0x30) && (CMDkey < 0x35))
            {
                break;
            }
        }
        PORT_ResetBits(MDR_PORTB, (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 |
                                   PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6));
        DEBUG_PRINTF("\r\nStarted test number : %c\r\n", CMDkey);

        CommandWord.CommandWord = 0;

        switch (CMDkey)
        {
            case 0x31:
                CommandWord.Fields.ReadWriteBit = MIL_STD_1553_BC_TO_TD;
                CommandWord.Fields.Data         = 0;
                CommandWord.Fields.Subaddress   = 30;
                /* Fill the data */
                for(i = 0; i < 32; i++)
                {
                    TestData[i] = i;
                }
                /* Write data to transmiter buffer */
                MIL_STD_1553_WriteDataToSendBuffer(MDR_MIL_STD_15531, 30, 32, &TestData[0]);
                MIL_STD_1553_LastRequest = WRITE_DATA;
                break;
            case 0x32:
                CommandWord.Fields.ReadWriteBit = MIL_STD_1553_TD_TO_BC;
                CommandWord.Fields.Data         = 0;
                CommandWord.Fields.Subaddress   = 30;
                MIL_STD_1553_LastRequest = READ_DATA;
                break;
            case 0x33:
                CommandWord.Fields.ReadWriteBit = MIL_STD_1553_TD_TO_BC;
                CommandWord.Fields.Data         = 2;
                CommandWord.Fields.Subaddress   = 0x1F;
                MIL_STD_1553_LastRequest = REQUEST_STATUS_WORD;
                break;
            case 0x34:
                CommandWord.Fields.ReadWriteBit = MIL_STD_1553_TD_TO_BC;
                CommandWord.Fields.Data         = 18;
                CommandWord.Fields.Subaddress   = 0x1F;
                MIL_STD_1553_LastRequest = REQUEST_LAST_COMMAND;
                break;
        }
        CommandWord.Fields.TerminalDeviceAddress = MIL_STD_1553_TERMINAL_ADDRESS;
        /* Set Command Word */
        MIL_STD_1553_SetCommandWord(MDR_MIL_STD_15531, MIL_STD_1553_COMMAND_WORD1, &CommandWord);
        /* Start transmision */
        MIL_STD_1553_StartTransmission(MDR_MIL_STD_15531);
        /* Enable interrups */
        MIL_STD_1553_ITConfig(MY_MIL_STD_1553, (MIL_STD_1553_IT_ERRIE |
                              MIL_STD_1553_IT_VALMESSIE), ENABLE);

        while(MIL_STD_1553_GetFlagStatus(MDR_MIL_STD_15531, MIL_STD_1553_FLAG_IDLE) != SET);
    }
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

/** @} */ /* End of group MIL_STD_1553_Bus_Controller */

/** @} */ /* End of group __MDR32F1QI_EVAL MDR32F1QI Evaluation Board */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr ********************************
*
* END OF FILE main.c */


