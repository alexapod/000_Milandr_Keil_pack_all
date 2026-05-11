/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    20/02/2023
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
#include "MDR32FxQI_uart.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
 * @{
 */

/** @addtogroup UART_WordSend_MDR32F1QI UART_WordSend
 * @{
 */

/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PortInit;
static UART_InitTypeDef UART_InitStructure;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
    uint8_t DataByte = 0x00;
    static uint8_t ReciveByte = 0x00;

    RST_CLK_DeInit();

    /* Enable HSE clock */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    /* Wait HSE ready */
    while(RST_CLK_HSEstatus() == ERROR) {}
    /* Select HSE as CPU_C1 source */
    RST_CLK_CPUclkSelectionC1(RST_CLK_CPU_C1srcHSEdiv1);
    /* Select CPU_C1 as CPU_C2 source */
    RST_CLK_CPU_PLLuse(DISABLE);
    /* Select CPU_C2 as CPU_C3 source */
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

    SystemCoreClockUpdate();

    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD |
                    RST_CLK_PCLK_UART1 | RST_CLK_PCLK_UART2), ENABLE);

    PORT_DeInit(MDR_PORTC);
    PORT_DeInit(MDR_PORTD);

    /* Configure PORTC pins 3 (UART1_TX) as output */
    PORT_StructInit(&PortInit);
    PortInit.PORT_Pin   = PORT_Pin_3;
    PortInit.PORT_OE    = PORT_OE_OUT;
    PortInit.PORT_FUNC  = PORT_FUNC_MAIN;
    PortInit.PORT_MODE  = PORT_MODE_DIGITAL;
    PortInit.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_Init(MDR_PORTC, &PortInit);

    /* Configure PORTC pins 4 (UART1_RX) as input */
    PortInit.PORT_Pin = PORT_Pin_4;
    PortInit.PORT_OE  = PORT_OE_IN;
    PORT_Init(MDR_PORTC, &PortInit);

    /* Configure PORTD pins 13 (UART2_TX) as output */
    PortInit.PORT_Pin = PORT_Pin_13;
    PortInit.PORT_OE  = PORT_OE_OUT;
    PORT_Init(MDR_PORTD, &PortInit);

    /* Configure PORTD pins 14 (UART2_RX) as input */
    PortInit.PORT_Pin = PORT_Pin_14;
    PortInit.PORT_OE  = PORT_OE_IN;
    PORT_Init(MDR_PORTD, &PortInit);

    UART_DeInit(MDR_UART1);
    UART_DeInit(MDR_UART2);

    /* Set the HCLK division factor = 1 for UART1,UART2*/
    UART_BRGInit(MDR_UART1, UART_HCLKdiv1);
    UART_BRGInit(MDR_UART2, UART_HCLKdiv1);

    /* Initialize UART_InitStructure */
    UART_InitStructure.UART_BaudRate            = 9600;
    UART_InitStructure.UART_WordLength          = UART_WordLength8b;
    UART_InitStructure.UART_StopBits            = UART_StopBits2;
    UART_InitStructure.UART_Parity              = UART_Parity_Even;
    UART_InitStructure.UART_FIFOMode            = UART_FIFO_OFF;
    UART_InitStructure.UART_HardwareFlowControl = (UART_HardwareFlowControl_RXE |
                                                    UART_HardwareFlowControl_TXE);

    /* Configure UART1 parameters*/
    UART_Init(MDR_UART1, &UART_InitStructure);

    /* Enables UART1 peripheral */
    UART_Cmd(MDR_UART1, ENABLE);
    /* Configure UART2 parameters*/
    UART_Init(MDR_UART2, &UART_InitStructure);
    /* Enables UART2 peripheral */
    UART_Cmd(MDR_UART2, ENABLE);

    while(1)
    {
        /* Check TXFE flag */
        while(UART_GetFlagStatus(MDR_UART2, UART_FLAG_TXFE) != SET) {}

        /* Send Data from UART2 */
        UART_SendData(MDR_UART2, DataByte);

        /* Check RXFF flag */
        while(UART_GetFlagStatus(MDR_UART1, UART_FLAG_RXFF) != SET) {}

        /* Recive data*/
        ReciveByte = UART_ReceiveData(MDR_UART1);

        /* Increment Data */
        DataByte++;
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

/** @} *//* End of group UART_WordSend_MDR32F1QI */

/** @} *//* End of group __MDR32F1QI_EVAL */

/** @} *//* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


