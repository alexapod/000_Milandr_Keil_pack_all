  /**
  @addtogroup I2C_Transmit_VE92 I2C_Transmit for MDR32F9Q2I evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    11/11/2024
  * @brief   Description of the I2C_Transmit Example.
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

This example shows how to use I2C.
Configure PORTC lines 0,1 as I2C_SCl, I2C_SDA.
Configure I2C on an exchange with 500 Kbit/s rate, 7 bit adress.
Send adress, recive data, send stop.
Use flags.


@par Directory contains:

    - main.c               Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F9Q2I eval board with MDR32F9Q2I microcontroller.
    - HSE oscillator is used so it should be present.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_i2c.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Edit the main.c to set appropriate device adress and number of transfers.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.

 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


