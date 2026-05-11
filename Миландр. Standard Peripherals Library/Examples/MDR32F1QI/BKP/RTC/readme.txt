  /**
  @addtogroup BKP_RTC_MDR32F1QI BKP_RTC for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    08/11/2024
  * @brief   Description of the BKP_RTC Example.
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

This example shows how to use BKP module functions.
That action includes the following steps:
    - Configure PORTD line 10,11 as output LED;
    - Configure RTC clock source;
    - Enable RTC interrupts;
    - Set RTC counter,prescaller and alarm values;
    - Enable RTC;
    - Switch On\Off LED1 when SECF Flag is set;
    - Switch On LED2 when ALRF is set.


@par Directory contains:

    - main.c                     Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.
    - VD7 (LED1), VD8 (LED2) are connected to PD.10, PD.11 pins, respectively.
    - If using LSE, then jumper XP5, XP6 should be set to OSC_IN32 and OS_OUT32.
    - Depending on the configuration, HSE or LSE oscillators are used so they should be present.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_bkp.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


