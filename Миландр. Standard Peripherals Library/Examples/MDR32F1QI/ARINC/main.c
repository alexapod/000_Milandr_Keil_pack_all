/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.1.0
  * @date    22/06/2023
  * @brief   This file contains example of use of the interface ARINC429.
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
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_utils.h"
#include "MDR32FxQI_bkp.h"
#include "MDR32FxQI_arinc429r.h"
#include "MDR32FxQI_arinc429t.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup ARINC429_MDR32F1QI ARINC
  * @{
  */

/* Private define ------------------------------------------------------------*/
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

volatile uint32_t ReadBytes = 0;
uint32_t ReadArray[64];

/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void ClockConfigure(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ARINC429R interrupt handler.
  * @param  None
  * @retval None
  */
void ARINC429R_IRQHandler(void)
{
    if (ARINC429R_GetFlagStatus(ARINC429R_CHANNEL1, ARINC429R_FLAG_ERR) == SET)
    {
        /* Error receiving data */
        DEBUG_PRINTF("Error receiving data\r\n");
        PORT_SetBits(MDR_PORTB, PORT_Pin_2);
        ARINC429R_ITConfig(ARINC429R_IT_INT_ER, DISABLE);
        ARINC429R_ChannelCmd(ARINC429R_CHANNEL1, DISABLE);
        ARINC429R_ChannelCmd(ARINC429R_CHANNEL1, ENABLE);
        return;
    }
    else
    {
        ARINC429R_SetChannel(ARINC429R_CHANNEL1);
        while(ARINC429R_GetFlagStatus(ARINC429R_CHANNEL1, ARINC429R_FLAG_DR) == SET)
        {
            ReadArray[ReadBytes++] = ARINC429R_ReceiveData();
        }
    }
}

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
    static ARINC429R_InitChannelTypeDef ARINC429R_InitChannelStruct;
    static ARINC429T_InitChannelTypeDef ARINC429T_InitChanelStruct;
    static uint32_t TestData[64] = {
        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
        0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
        0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
        0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10
    };
    uint32_t i;

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
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTD |
                    RST_CLK_PCLK_ARINC429R | RST_CLK_PCLK_ARINC429T), ENABLE);

    /* Reset PORTB settings */
    PORT_DeInit(MDR_PORTB);
    /* Reset PORTD settings */
    PORT_DeInit(MDR_PORTD);

    /* LEDs Port Init */
    /* Configure PORTB pins 2,3,4,5,6,7 */
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_7  | PORT_Pin_8  | PORT_Pin_9 |
                                     PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 );
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    DEBUG_PRINTF("Init LEDs PORT ... Ok\r\n");

    /* Init ARINC429R */
    /* Configure ARINC429R channel1 pins: IN1+, IN1- */
    /* Configure PORTB pins 0, 1 */
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1);
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_PD    = PORT_PD_DRIVER;
    PORT_Init(MDR_PORTB, &PORT_InitStructure);

    /* Reset all ARINC429R settings */
    ARINC429R_DeInit();

    /* Set the HCLK division factor = 80 for ARINC429R */
    ARINC429R_BRG_Init(80);

    /* ARINC429R channel 1 configuration */
    ARINC429R_InitChannelStruct.ARINC429R_CLK  = ARINC429R_CLK_100_KHz;
    ARINC429R_InitChannelStruct.ARINC429R_SD   = DISABLE;
    ARINC429R_InitChannelStruct.ARINC429R_LB   = DISABLE;
    ARINC429R_InitChannelStruct.ARINC429R_SDI1 = RESET;
    ARINC429R_InitChannelStruct.ARINC429R_SDI2 = RESET;
    ARINC429R_InitChannelStruct.ARINC429R_DIV  = 0;
    ARINC429R_ChannelInit(ARINC429R_CHANNEL1, &ARINC429R_InitChannelStruct);

    /* Enable receiver and errors interrupt */
    ARINC429R_ITConfig((ARINC429R_IT_INT_DR | ARINC429R_IT_INT_ER), ENABLE);
    NVIC_EnableIRQ(ARINC429R_IRQn);

    /* Enables ARINC429R channel 1 */
    ARINC429R_ChannelCmd(ARINC429R_CHANNEL1, ENABLE);
    DEBUG_PRINTF("Init ARINC429R CHANNEL1 ... Ok\r\n");

    /* Init ARINC429T */
    /* Configure ARINC429T channel1 pins: OUT1+, OUT1- */
    /* Configure PORTD pins 13, 14 */
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_13 | PORT_Pin_14);
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_PD    = PORT_PD_DRIVER;
    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Reset all ARINC429T settings */
    ARINC429T_DeInit();

    /* Set the HCLK division factor = 80 for ARINC429T */
    ARINC429T_BRG_Init(80);

    /* ARINC429T channel 1 configuration */
    ARINC429T_InitChanelStruct.ARINC429T_CLK    = ARINC429T_CLK_100_KHz;
    ARINC429T_InitChanelStruct.ARINC429T_DIV    = 0;
    ARINC429T_InitChanelStruct.ARINC429T_EN_PAR = ENABLE;
    ARINC429T_InitChanelStruct.ARINC429T_ODD    = ARINC429T_ODD_ADD_TO_ODD;
    ARINC429T_ChannelInit(ARINC429T_CHANNEL1, &ARINC429T_InitChanelStruct);

    /* Enables ARINC429T channel 1 */
    ARINC429T_ChannelCmd(ARINC429T_CHANNEL1, ENABLE);
    DEBUG_PRINTF("Init ARINC429T CHANNEL1 ... Ok\r\n");

    /* Send data */
    DEBUG_PRINTF("Send data\r\n");
    for(i = 0; i < 64; i++)
    {
        ARINC429T_SendData(ARINC429T_CHANNEL1, TestData[i]);
    }

    /* Wait until all the data do not take */
    while(ReadBytes < 64);

    /* Check the received data */
    for(i = 0; i < 64; i++)
    {
        if (TestData[i] != (ReadArray[i] & 0x7FFFFFFF))
        {
            /* Error in the received data */
            DEBUG_PRINTF("Error in the received data\r\n");
            PORT_SetBits(MDR_PORTD, PORT_Pin_7);
            break;
        }
    }
    /* The data is received correctly */
    DEBUG_PRINTF("The data is received correctly\r\n");
    PORT_SetBits(MDR_PORTD, PORT_Pin_8);

    /* Infinite loop */
    while(1) {}
}

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
    while(RST_CLK_HSEstatus() == ERROR);

    /* Configures the CPU_PLL clock source */
    RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);
    /* Enables the CPU_PLL */
    RST_CLK_CPU_PLLcmd(ENABLE);
    while(RST_CLK_CPU_PLLstatus() == ERROR);

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

/** @} */ /* End of group ARINC429_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI_EVAL*/

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr ********************************
*
* END OF FILE main.c */


