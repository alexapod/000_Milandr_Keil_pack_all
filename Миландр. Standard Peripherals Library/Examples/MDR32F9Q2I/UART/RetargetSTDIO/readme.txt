  /**
  @addtogroup UART_Retarget_STDIO UART_Retarget_STDIO for MDR32F9Q2I evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ***********************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    11/11/2024
  * @brief   Description of the UART_Retarget_STDIO Example.
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

This example shows how to redirect standard I/O (STDIO) to UART using the MDR32FxQI_utils module.
UART parameters are set in MDR32FxQI_config.h, _USE_DEBUG_UART_ block. The default parameters are:
- UART peripheral: UART2;
- baud rate: 115200 baud;
- data size: 8 bits;
- stop bits: 1 bit;
- parity: no;
- GPIO peripheral: PF0 as UART2_RXD, PF1 as UART2_TXD.


@par Directory contains:

    - main.c                       Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F9Q2I evaluation board with MDR32F9Q2I microcontroller.
    - UART2_RXD and UART2_TXD lines of MCU are connected on evaluation board to the RS-232 transceiver.
    - Connect USB-RS232 cable between PC and evaluation board (DB9 connector XP11) to display data on a terminal (for example PuTTY).
    - HSE oscillator is used so it should be present.


@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - For the IAR EW in the project settings "General options -> Library Configuration -> Library" you must set the "Full" parameter.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_rst_clk.c
        MDR32FxQI_port.c
        MDR32FxQI_bkp.c
        MDR32FxQI_eeprom.c
        MDR32FxQI_uart.c
        MDR32FxQI_utils.c
        MDR32FxQI_asm.S
  - Be sure to uncomment _USE_DEBUG_UART_ macro defined in MDR32FxQI_config.h.
  - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


