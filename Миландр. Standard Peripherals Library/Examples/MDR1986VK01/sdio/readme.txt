/**
  \addtogroup sdio readme
  @{
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    14/04/2022
  * @brief   Description of the sdio Example.
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

This example shows how to use SDIO.
In this demo, using the FATFS library, the free space on the SD card is determined and then the file write/read test is performed.
For this test user, you need to install the XS1 SD card on the demo board. The user can check the test execution result in debug mode.

@par Directory contains:

  - main.c              Main program
  - FatFs/              Generic FAT Filesystem Module library and SD_SDIO driver

@par Hardware and Software environment:

  - This example is intended to run on MDR1986VK01 demo board with MDR1986VK01
  microcontroller.

@par How to use.

To launch the example, you must do the following:
  - Create a project and setup all project configurations.
  - Add main.c file.
  - Add the required files from "Libraries" folder:
        MDR1986VK01_port.h
        MDR1986VK01_clk.h
        MDR1986VK01_sdio.h
        sdio.h
        adc.h
        
  - Edit the MDR1986VK01_config.h to set appropriate run-time parameter checking level.
  - Compile and link together all .c files and load your image into the target board.
  - Run the example.

 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */

