  /**
  @addtogroup MIL_STD_1553_Terminal_Device_IT MIL_STD_1553 Terminal Device for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    08/11/2024
  * @brief   Description work of MIL_STD_1553 in Terminal Device mode.
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

This example provides a description of how to use MIL STD 1553 in Terminal Device
mode.


@par Directory contains:

    - src/main.c                         Main program
    - src/MDR32F1QI_IT.c               Main Interrupt Service Routines
    - src/MIL_STD_1553_IT_Handler.c      Main function for processing MIL_STD_1553 interrupt.
    - inc/MDR32F1QI_IT.h               Functions prototypes for the interrupt.
    - inc/MIL_STD_1553_BusController.h   Functions prototypes.
    - inc/MIL_STD_1553_IT_Handler.h      Functions prototypes for the MIL_STD_1553 interrupt.


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.
    - HSE oscillator is used so it should be present.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_timer.c
        MDR32FxQI_mil_std_1553.c
        MDR32FxQI_eeprom.c
        MDR32FxQI_utils.c
        MDR32FxQI_bkp.c
        MDR32FxQI_uart.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


