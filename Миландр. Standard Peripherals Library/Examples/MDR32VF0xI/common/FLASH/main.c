/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    29/04/2025
 * @brief   Main program body.
 ******************************************************************************
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 */

/** @addtogroup MDR32VF0xI_StdPeriph_Examples MDR32VF0xI StdPeriph Examples
 * @{
 */

/** @addtogroup MDR32VF0xI_MDR1206FI_BOARD MDR1206FI Evaluation Board
 * @{
 */

/** @addtogroup FLASH FLASH
 * @{
 */

/** @addtogroup MDR32VF0xI_FLASH MDR32VF0xI_FLASH
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_rst_clk.h"
#include "MDR32VF0xI_flash.h"

/* Private definitions -------------------------------------------------------*/
#define ADDR (FLASH_BASE + FLASH_SIZE - 4) /* Last word of main memory Flash bank. */
#define DATA 0x8555AAA1

/* Private variables ---------------------------------------------------------*/
uint32_t Data;

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();

    RST_CLK_PCLKCmd(RST_CLK_PCLK_FLASH, ENABLE);
    FLASH_SetRegistersLock(RESET);

    /* Erase page if specified address is not clear. */
    if (FLASH_ReadWord(ADDR, FLASH_BANK_MAIN) != 0xFFFFFFFF) {
        FLASH_ErasePage(ADDR, FLASH_BANK_MAIN);
    }

    FLASH_ProgramWord(ADDR, DATA, FLASH_BANK_MAIN);

    Data = FLASH_ReadWord(ADDR, FLASH_BANK_MAIN);

    if (Data != DATA) {
        while (1) { }
    }

    while (1) { }
}

/**
 * @brief  Clock configuration.
 * @param  None.
 * @return None.
 */
void ClockConfig(void)
{
    RST_CLK_DeInit();
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_HSI);
#endif
    SystemCoreClockUpdate();
}

/**
 * @brief  Report the source file name, the source line number and expression
 *         text (if USE_ASSERT_INFO == 2) where the assert_param error has occurred.
 * @param  file: Pointer to the source file name.
 * @param  line: assert_param error line source number.
 * @param  expr: Reported expression text.
 * @return None.
 */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;
    while (1) { }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    (void)file;
    (void)line;
    (void)expr;
    while (1) { }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group MDR32VF0xI_FLASH */

/** @} */ /* End of group FLASH */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


