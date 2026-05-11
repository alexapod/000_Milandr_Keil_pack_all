  /**
  @page MDR32F02_OTP_Word example readme for MDR32F02 demo board
  @latexonly
  @verbatim
  ******************** (C) COPYRIGHT 2025 Milandr ******************************
  * @file    readme.txt
  * @author  Milandr Application Team
  * @version V0.2.0
  * @date    07/05/2025
  * @brief   Description of the MDR32F02_OTP_Word Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
  @endlatexonly

@par Example Description

This example shows OTP memory read and program using register access:
Read OTP memory word at address [(uintptr_t)OTP_SPECIAL_FIELDS - 128].
If address is clear, perform programming.
After that read OTP word again.
If read word == target word, LED1 and LED2 blink continuously.
If read word != target word, LED3 and LED4 blink continuously.

@par Directory contains:
    - src           Program sources.
    - Library       SPL library.
    - svd           Peripherals memory-mapped registers definitions.
    - launch_cfg    Debug configurations.

@par Hardware and Software environment:
    - This example is intended to run on MDR32F02 demo board with MDR32F02 microcontroller.
    - "3V3 to LED" connector should be installed on demoboard to show visual indication.
    - Project uses xPack GNU RISC-V Embedded GCC (riscv-none-elf-gcc) toolchain and custom OpenOCD with MDR32F02 support.


@par How to use.
To launch the example, you must do the following:
    - Configure Eclipse IDE with RISC-V toolchain
    - Import this project: File -> Import... -> Existing Projects into Workspace
    - Create launch configuration or use exising one
    - Build and Run the example
    - Check on-board LED indication

 * <h3><center>&copy; COPYRIGHT 2025 Milandr</center></h3>
 */


