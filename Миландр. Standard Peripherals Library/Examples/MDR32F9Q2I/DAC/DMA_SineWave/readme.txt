  /**
  @addtogroup DAC_DMA_SineWave_MDR32F9Q2I DAC_DMA_SineWave for MDR32F9Q2I evaluation board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V2.0.1
  * @date    01/03/2023
  * @brief   Description of the DAC_DMA_SineWave Example.
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

This example describes how to use DAC with DMA to generate sine waves on DAC channel output.
Configure PORTE line 0 as DAC2_OUT.
DMA channel10 is configured to transfer ping-pong mode, word by word, a 32-word buffer to DAC register DAC2_DATA.
The transfered 32 buffer is made to have a sine wave generation on DAC channel output. DAC channel2 is enabled.
Once TIM1 is enabled, each TIM1 CNT_ARR_EVENT generate a DMA request which transfer data to the  DAC2_DATA register and DAC conversion is started. The sine waves can be visualized by connecting DAC_OUT jack to an oscilloscope.


@par Directory contains:

    - main.c                          Main program


@par Hardware and Software environment:

    - This example is intended to run on MDR32F9Q2I eval board with MDR32F9Q2I microcontroller.
    - DAC_OUT_SEL jamper must be switched into a state EXT_CON.


@par How to use.

To launch the example, you must do the following:
    - Create a project and setup all project configurations.
    - Add main.c file.
    - Add the required files from "Libraries" folder:
        MDR32FxQI_config.h
        MDR32FxQI_port.c
        MDR32FxQI_rst_clk.c
        MDR32FxQI_dac.c
        MDR32FxQI_timer.c
        MDR32FxQI_dma.c
    - Edit the MDR32FxQI_config.h to set appropriate run-time parameter checking level.
    - Compile and link together all .c files and load your image into the target board.
    - Run the example.

 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


