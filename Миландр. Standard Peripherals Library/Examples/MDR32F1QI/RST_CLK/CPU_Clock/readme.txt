  /**
  @addtogroup RST_CLK_CPU_Clock_MDR32F1QI RST_CLK_CPU_Clock for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    08/11/2024
  * @brief   Description of the RST_CLK Example.
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

This example shows how to use RST_CLK module functions to choose particular
CPU_CLK frequency. That action includes the following steps:
    - RST_CLK module deinitialization;
    - RST_CLK module initialization;
        - enable PORTD clock;
        - enable BKP clock;
    - RST_CLK module initialization;
    - Set CPU_CLK = HSI clock and blink with LED1 using this clock;
    - Set CPU_CLK = HSI/2 clock and blink with LED1 using this clock;
    - Set CPU_CLK = 7*HSE/2 clock and blink with LED1 using this clock;
    - Set CPU_CLK = LSI clock and blink with LED1 using this clock.

With each frequency initialization, the operation mode of the DUcc voltage
regulator and the EEPROM memory access delay are adjusted.

LED1 is used for frequency indication;
LED2 - for new frequensy setting up indication;
LED3 - for frequensy setting error.


@par Directory contains:

    - main.c           Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.
    - VD7 (LED1), VD8 (LED2), VD9 (LED3) are connected to
      PD.7, PD.8, PD.9 pins, respectively.
    - HSE oscillator is used so it should be present.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_eeprom.c
        MDR32FxQI_utils.c
        MDR32FxQI_bkp.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Edit the main.c to set appropriate LEDs blink count and rate.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


