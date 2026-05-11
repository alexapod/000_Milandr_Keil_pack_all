  /**
  @addtogroup BKP_SLEEP_MDR32F1QI BKP_SLEEP for MDR32F1QI evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.1.0
  * @date    26/06/2023
  * @brief   Description of the BKP SLEEP Example.
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

This example shows how to use MCU SLEEP mode.
Program includes the following steps:
    - Configure PE9 as SELECT button;
    - Configure PD9 as non-sleeping state LED indicator, PD8 as SLEEP mode LED indicator,
      PD10 as wake switch indicator;
    - Initialize TIMER1 to generate interrupts to wake MCU;
    - Monitor SELECT button to enable TIMER1, enable SPEEP mode LED and enter SLEEP mode;
    - Periodicaly switch non-sleeping state LED indicator.


@par Directory contains:

    - main.c                      Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F1QI eval board with MDR32F1QI microcontroller.
    - SELECT button is connected to PE9.
    - VD7 led is connected to PD.8 pin, VD8 led ti PD.9, VD9 led ti PD.10.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_timer.c
        MDR32FxQI_dma.c
        MDR32FxQI_bkp.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.


 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


