/**
 ******************************************************************************
 * @file    system_MDR32F21QI.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    22/05/2023
 * @brief   CMSIS Device Peripheral Access Layer System Source File for MDR32F21QI.
 ******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2025 Milandr</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F21QI.h"
#include "system_MDR32F21QI.h"
#include "system_MDR32F21QI_config.h"

/** @addtogroup CMSIS CMSIS
 * @{
 */

/** @addtogroup MDR32F21QI MDR32F21QI
 *  @{
 */

/** @addtogroup MDR32F21QI_System MDR32F21QI System
 * @{
 */

/** @defgroup MDR32F21QI_System_Exported_Variables MDR32F21QI System Exported Variables
 * @{
 */

/*******************************************************************************
 *  Clock Definitions
 *******************************************************************************/
uint32_t SystemCoreClock = (uint32_t)HSI_FREQUENCY_Hz; /*!< System Clock Frequency (Core Clock)
                                                        *   default value */

/** @} */ /* End of group MDR32F21QI_System_Exported_Variables */

/** @defgroup MDR32F21QI_System_Exported_Functions MDR32F21QI System Exported Functions
 * @{
 */

/**
 * @brief  Update SystemCoreClock according to Clock Register Values.
 * @param  None.
 * @retval None.
 */
void SystemCoreClockUpdate(void)
{
    uint32_t CPU_C1_Freq = HSI_FREQUENCY_Hz, CPU_C2_Freq, CPU_C3_Freq;
    uint32_t PLLMult;
    uint32_t Temp;

    /* Compute CPU_CLK frequency */
    Temp = MDR_RST_CLK->CPU_CLOCK;
    /* Select CPU_CLK from HSI, CPU_C3, LSE, LSI cases */
    switch (Temp & RST_CLK_CPU_CLOCK_HCLK_SEL_Msk) {
        case RST_CLK_CPU_CLOCK_HCLK_SEL_HSI:
            SystemCoreClock = HSI_FREQUENCY_Hz;
            break;
        case RST_CLK_CPU_CLOCK_HCLK_SEL_CPU_C3:
            /* Determine CPU_C1 frequency */
            switch (Temp & RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk) {
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSI:
                    CPU_C1_Freq = HSI_FREQUENCY_Hz;
                    break;
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSIdiv2:
                    CPU_C1_Freq = HSI_FREQUENCY_Hz / 2;
                    break;
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSE:
                    CPU_C1_Freq = HSE_FREQUENCY_Hz;
                    break;
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSEdiv2:
                    CPU_C1_Freq = HSE_FREQUENCY_Hz / 2;
                    break;
            }
            /* Determine CPU_C2 frequency */
            CPU_C2_Freq = CPU_C1_Freq;
            if (Temp & RST_CLK_CPU_CLOCK_CPU_C2_SEL) {
                /* Determine CPU PLL output frequency */
                PLLMult = ((MDR_RST_CLK->PLL_CONTROL & RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk) >>
                           RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos) + 1;
                CPU_C2_Freq *= PLLMult;
            }
            /* Determine CPU_C3 frequency */
            Temp = ((Temp & RST_CLK_CPU_CLOCK_CPU_C3_SEL_Msk) >> RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos);
            if ((Temp & 0x8U) == 0x00) {
                CPU_C3_Freq = CPU_C2_Freq;
            } else {
                CPU_C3_Freq = CPU_C2_Freq >> ((Temp & 0x7U) + 1);
            }
            SystemCoreClock = CPU_C3_Freq;
            break;
        case RST_CLK_CPU_CLOCK_HCLK_SEL_LSE:
            SystemCoreClock = LSE_FREQUENCY_Hz;
            break;
        case RST_CLK_CPU_CLOCK_HCLK_SEL_LSI:
            SystemCoreClock = LSI_FREQUENCY_Hz;
            break;
    }
}

/**
 * @brief  Setup the microcontroller system RST clock configuration
 *         to the default reset state. Setup SystemCoreClock variable.
 * @note   This function should be used only after reset.
 * @param  None.
 * @retval None.
 */
void SystemInit(void)
{
    /* Reset the RST clock configuration to the default reset state */

    /* Reset all clock but DMA_EN, DEBUG_EN and RST_CLK bits */
    MDR_RST_CLK->PER1_CLOCK = RST_CLK_PER1_CLOCK_DMA_EN | RST_CLK_PER1_CLOCK_DEBUG_EN;
    MDR_RST_CLK->PER2_CLOCK = RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK;

    /* Reset CPU_CLOCK bits */
    MDR_RST_CLK->CPU_CLOCK = (uint32_t)0x00000000;

    /* Reset PLL_CONTROL bits */
    MDR_RST_CLK->PLL_CONTROL = (uint32_t)0x00000000;

    /* Reset HSEON and HSEBYP bits */
    MDR_RST_CLK->HS_CONTROL = (uint32_t)0x00000000;

    /* Reset ADC_CLOCK bits */
    MDR_RST_CLK->ADC_CLOCK = (uint32_t)0x00000000;

    /* Reset RTC_CLOCK bits */
    MDR_RST_CLK->RTC_CLOCK = (uint32_t)0x00000000;

    /* Reset TIM_CLOCK bits */
    MDR_RST_CLK->TIM_CLOCK = (uint32_t)0x00000000;

    /* Reset UART_CLOCK bits */
    MDR_RST_CLK->UART_CLOCK = (uint32_t)0x00000000;

    /* Reset SSP_CLOCK bits */
    MDR_RST_CLK->SSP_CLOCK = (uint32_t)0x00000000;

    SystemCoreClockUpdate();
}

/** @} */ /* End of group MDR32F21QI_System_Exported_Functions */

/** @} */ /* End of group MDR32F21QI_System */

/** @} */ /* End of group MDR32F21QI */

/** @} */ /* End of group CMSIS */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE system_MDR32F21QI.c */

