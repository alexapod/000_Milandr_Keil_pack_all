/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    12/05/2025
 * @brief   Main program body.
 ******************************************************************************
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 */

/** @addtogroup MDR32VF0xI_StdPeriph_Examples MDR32VF0xI StdPeriph Examples
 * @{
 */

/** @addtogroup MDR32VF0xI_MDR1206FI_BOARD MDR1206FI Evaluation Board
 * @{
 */

/** @addtogroup UART UART
 * @{
 */

/** @addtogroup MDR32VF0xI_UART_Loopback MDR32VF0xI_UART_Loopback
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_rst_clk.h"
#include "MDR32VF0xI_uart.h"

/* Private definitions -------------------------------------------------------*/
#define UART           MDR_UART1
#define UART_BAUD      9600
#define UART_WORD      UART_WORD_LENGTH_8BIT
#define UART_STOP_BITS UART_STOP_BITS_1BIT
#define UART_PARITY    UART_PARITY_NONE

#define UART_PCLK      RST_CLK_PCLK_UART1
#define UART_PER1_C2   RST_CLK_PER1_C2_UART1

/* Private variables ---------------------------------------------------------*/

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);
void UART_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();
    UART_Config();

    UART_Cmd(UART, ENABLE);

    while (1) {
        UART_SendData(UART, 42);
        while (UART_GetFlagStatus(UART, UART_FLAG_RXFE) == SET) { }
        if (UART_DATA(UART_ReceiveData(UART)) != 42) {
            while (1) { }
        }
    }
}

/**
 * @brief  Clock configuration.
 * @param  None.
 * @return None.
 */
void ClockConfig(void)
{
    RST_CLK_DeInit();
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_HSI);
#endif
    SystemCoreClockUpdate();
}

/**
 * @brief  UART configuration.
 * @param  None.
 * @return None.
 */
void UART_Config(void)
{
    static const UART_InitTypeDef UART_Loopback = {
        .UART_BaudRate            = UART_BAUD,
        .UART_Mode                = UART_MODE_TX_RX,
        .UART_WordLength          = UART_WORD,
        .UART_StopBits            = UART_STOP_BITS,
        .UART_Parity              = UART_PARITY,
        .UART_HardwareFlowControl = UART_HARDWARE_FLOW_CONTROL_NONE,
        .UART_LoopbackMode        = UART_LOOPBACK_ENABLE,

        .UART_FIFO_Mode        = UART_FIFO_MODE_ENABLE,
        .UART_FIFO_TxThreshold = UART_FIFO_TX_THRESHOLD_2WORD,
        .UART_FIFO_RxThreshold = UART_FIFO_RX_THRESHOLD_2WORD,

        .UART_IRDA_Mode      = UART_IRDA_MODE_DISABLE,
        .UART_IRDA_PowerMode = UART_IRDA_POWER_NORMAL,
    };

    RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_CLK_SRC_CPU_C1);
    RST_CLK_PER1_C2_SetPrescaler(UART_PER1_C2, RST_CLK_PER1_PRESCALER_DIV_1);
    RST_CLK_PER1_C2_Cmd(UART_PER1_C2, ENABLE);

    RST_CLK_PCLKCmd(UART_PCLK, ENABLE);

    UART_DeInit(UART);
    UART_Init(UART, &UART_Loopback);
}

/**
 * @brief  Report the source file name, the source line number and expression
 *         text (if USE_ASSERT_INFO == 2) where the assert_param error has occurred.
 * @param  file: Pointer to the source file name.
 * @param  line: assert_param error line source number.
 * @param  expr: Reported expression text.
 * @return None.
 */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;
    while (1) { }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    (void)file;
    (void)line;
    (void)expr;
    while (1) { }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group MDR32VF0xI_UART_Loopback */

/** @} */ /* End of group UART */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


