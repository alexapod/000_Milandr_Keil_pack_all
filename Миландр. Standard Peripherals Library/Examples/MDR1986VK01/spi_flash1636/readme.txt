/**
  \addtogroup spi_flash1636 readme
  @{
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    14/04/2022
  * @brief   Description of the spi_flash1636 Example.
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

This example shows, how to use SPI.
In this demo there are SPI initialisation function and SPI test function, which write data to 1636 flash and read it back. 
User can validate communication with rtrn value of memcmp function of SPI test function in debug mode.
For this test 1636 flash external module needs to be installed with XS6 on demo board.

@par Directory contains:

  - main.c              Main program
  - MDR1986VK01_it.c     Main Interrupt Service Routines
  - MDR1986VK01_it.h     Functions prototypes for the interrupt

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VK01 demo board with MDR1986VK01
  microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR1986VK01_port.h
        MDR1986VK01_ssp.h
        MDR1986VK01_clk.h
        spi.h
        
  - Edit the MDR1986VK01_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */

