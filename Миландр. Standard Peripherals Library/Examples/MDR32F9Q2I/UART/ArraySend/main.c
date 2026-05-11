/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    14/06/2023
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

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup UART_ArraySend_MDR32F9Q2I UART_ArraySend
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
    uint8_t DataByte=0x01;
    static uint8_t ReciveByte[16];
    uint32_t i;

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

    /* Enables peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTD |
                    RST_CLK_PCLK_UART1 | RST_CLK_PCLK_UART2), ENABLE);

    PORT_DeInit(MDR_PORTB);
    PORT_DeInit(MDR_PORTD);

    /* Configure PORTB pins 5 (UART1_TX) as output */
    PORT_StructInit(&PortInit);
    PortInit.PORT_Pin   = PORT_Pin_5;
    PortInit.PORT_FUNC = PORT_FUNC_ALTER;
    PortInit.PORT_SPEED = PORT_SPEED_MAXFAST;
    PortInit.PORT_MODE = PORT_MODE_DIGITAL;
    PortInit.PORT_OE    = PORT_OE_OUT;
    PORT_Init(MDR_PORTB, &PortInit);

    /* Configure PORTB pins 6 (UART1_RX) as input */
    PortInit.PORT_Pin = PORT_Pin_6;
    PortInit.PORT_OE = PORT_OE_IN;
    PORT_Init(MDR_PORTB, &PortInit);

    /* Configure PORTD pins 1 (UART2_TX) as output */
    PortInit.PORT_Pin = PORT_Pin_1;
    PortInit.PORT_OE = PORT_OE_OUT;
    PORT_Init(MDR_PORTD, &PortInit);

    /* Configure PORTD pins 0 (UART1_RX) as input */
    PortInit.PORT_Pin = PORT_Pin_0;
    PortInit.PORT_OE = PORT_OE_IN;
    PORT_Init(MDR_PORTD, &PortInit);

    UART_DeInit(MDR_UART1);
    UART_DeInit(MDR_UART2);

    /* Set the HCLK division factor = 1 for UART1,UART2 */
    UART_BRGInit(MDR_UART1, UART_HCLKdiv1);
    UART_BRGInit(MDR_UART2, UART_HCLKdiv1);

    /* Initialize UART_InitStructure */
    UART_InitStructure.UART_BaudRate            = 115000;
    UART_InitStructure.UART_WordLength          = UART_WordLength8b;
    UART_InitStructure.UART_StopBits            = UART_StopBits1;
    UART_InitStructure.UART_Parity              = UART_Parity_No;
    UART_InitStructure.UART_FIFOMode            = UART_FIFO_ON;
    UART_InitStructure.UART_HardwareFlowControl = (UART_HardwareFlowControl_RXE |
                                                    UART_HardwareFlowControl_TXE);

    /* Configure UART1 parameters */
    UART_Init(MDR_UART1, &UART_InitStructure);

    /* Configure DMA for UART1 */
    UART_DMAConfig(MDR_UART1, UART_IT_FIFO_LVL_12words, UART_IT_FIFO_LVL_12words);
    UART_DMACmd(MDR_UART1, (UART_DMA_TXE | UART_DMA_RXE | UART_DMA_ONERR), ENABLE);

    /* Enables UART1 peripheral */
    UART_Cmd(MDR_UART1, ENABLE);

    /* Configure UART2 parameters */
    UART_Init(MDR_UART2, &UART_InitStructure);

    /* Configure DMA for UART2 */
    UART_DMAConfig(MDR_UART2, UART_IT_FIFO_LVL_12words, UART_IT_FIFO_LVL_12words);
    UART_DMACmd(MDR_UART2, (UART_DMA_TXE | UART_DMA_RXE | UART_DMA_ONERR), ENABLE);

    /* Enables UART2 peripheral */
    UART_Cmd(MDR_UART2, ENABLE);

    while (1)
    {
        /* Check TXFE flag */
        while (UART_GetFlagStatus(MDR_UART1, UART_FLAG_TXFE) != SET) {}

        /* Send Data from UART1 */
        for (i = 0; i < 16; i++)
        {
            UART_SendData(MDR_UART1, (uint16_t)(i + 16 * DataByte));
        }

        /* Check RXFF flag */
        while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_RXFF) != SET) {}

        /* Recive data */
        for (i=0;i<16;i++)
        {
            ReciveByte[i] = UART_ReceiveData(MDR_UART2);
        }

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

/** @} */ /* End of group UART_ArraySend_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


