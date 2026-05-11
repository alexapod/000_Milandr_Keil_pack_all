  /**
  @addtogroup DMA_UART_RAM_MDR32F1QI DMA_UART_RAM for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.1
  * @date    08/11/2024
  * @brief   Description of the DMA UART Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
  * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
  @endlatexonly
@par Example Description

This example provides a basic communication between UART1 and UART2 using DMA capability.
First, the DMA transfers data from SrcBuf1 buffer to UART1 Transmit data register,
then this data is sent to UART2.
Data received by USART2 is transferred by DMA and stored in DstBuf2 then compared with
the send ones and the result of this comparison is stored in the "TransferStatus2" variable.

In the same time, the DMA transfers data from SrcBuf2 buffer to UART2 Transmit data register,
then this data is sent to UART1. Data received by UART1 is transferred by DMA and stored in
DstBuf1 then compared with the send ones and the result of this comparison is stored in the
"TransferStatus1" variable.

UART1 and UART2 configured as follow:
    - BaudRate = 1200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - FIFO enable
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled


@par Directory contains:

    - main.c           Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.
    - Connect UART1 RXD (PC4) pin (XP19.1) to UART2 TXD (PD14) pin (XP19.6).
    - Connect UART1 TXD (PC3) pin (XP19.4) to UART2 RXD (PD13) pin (XP19.3).
    - HSE oscillator is used so it should be present.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_uart.c
        MDR32FxQI_dma.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


