/**
 *******************************************************************************
 * @file    MDR32F2xQI_rst_clk.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    19/05/2023
 * @brief   This file contains all the RST_CLK firmware functions.
 *******************************************************************************
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
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_rst_clk.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @defgroup RST_CLK RST_CLK
 * @{
 */

/** @defgroup RST_CLK_Exported_Functions RST_CLK Exported Functions
 * @{
 */

/**
 * @brief  Set the RST_CLK clock configuration to the default reset state.
 * @param  None.
 * @retval None.
 */
void RST_CLK_DeInit(void)
{
    /* Reset all peripheral clock but RST_CLK and BKP_CLK */
    MDR_RST_CLK->PER2_CLOCK = (RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK | RST_CLK_PER2_CLOCK_PCLK_EN_BKP);

    /* Enable HSI in BKP because RST_CLK deinitialization will change HCLK source to HSI */
    MDR_BKP->REG_0F |= BKP_REG_0F_HSI_ON;

    /* Wait HSI ready */
    while ((MDR_BKP->REG_0F & BKP_REG_0F_HSI_RDY) == RESET) { }

    /* Reset CPU_CLOCK bits - HSI is selected as HCLK */
    MDR_RST_CLK->CPU_CLOCK = (uint32_t)0x00000000;

    /* Reset SELECTRI and LOW bits in BKP */
    MDR_BKP->REG_0E &= ~(BKP_REG_0E_SELECTRI_Msk | BKP_REG_0E_LOW_Msk);

    /* Reset all peripheral clock but RST_CLK */
    MDR_RST_CLK->PER2_CLOCK = RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK;

    MDR_RST_CLK->PLL_CONTROL = (uint32_t)0x00000000;
    MDR_RST_CLK->HS_CONTROL  = (uint32_t)0x00000000;
    MDR_RST_CLK->ADC_CLOCK   = (uint32_t)0x00000000;
    MDR_RST_CLK->RTC_CLOCK   = (uint32_t)0x00000000;

#if defined(USE_MDR32F21QI)
    /* Reset all but DMA_EN and DEBUG_EN bits */
    MDR_RST_CLK->PER1_CLOCK = (RST_CLK_PER1_CLOCK_DMA_EN | RST_CLK_PER1_CLOCK_DEBUG_EN);
#elif defined(USE_MDR32F23QI)
    /* Reset all but DEBUG_EN bits */
    MDR_RST_CLK->PER1_CLOCK = RST_CLK_PER1_CLOCK_DEBUG_EN;
#endif

    MDR_RST_CLK->TIM_CLOCK  = (uint32_t)0x00000000;
    MDR_RST_CLK->UART_CLOCK = (uint32_t)0x00000000;
    MDR_RST_CLK->SSP_CLOCK  = (uint32_t)0x00000000;
}

/**
 * @brief  HSE (High Speed External) clock mode and source selection.
 * @param  HSE_Mode - @ref RST_CLK_HSE_Mode_TypeDef - mode selector.
 * @retval None.
 */
void RST_CLK_HSE_Config(RST_CLK_HSE_Mode_TypeDef HSE_Mode)
{
    /* Check the parameters */
    assert_param(IS_RST_CLK_HSE(HSE_Mode));

    /* Reset HSEON and HSEBYP bits before configuring the HSE */
    MDR_RST_CLK->HS_CONTROL &= ~(RST_CLK_HS_CONTROL_HSE_ON | RST_CLK_HS_CONTROL_HSE_BYP);

    MDR_RST_CLK->HS_CONTROL |= (uint32_t)HSE_Mode;
}

/**
 * @brief  Get HSE clock status.
 * @param  None.
 * @retval @ref ErrorStatus - SUCCESS if HSE clock is ready, else ERROR.
 */
ErrorStatus RST_CLK_HSE_GetStatus(void)
{
    __IO uint32_t StartCounter = 0;
    ErrorStatus   State;
    FlagStatus    Flag;

    /* Wait until HSE is ready or time out is occurred */
    do {
        Flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_HSERDY);
        StartCounter++;
    } while ((StartCounter < HSERDY_TIMEOUT_TICK) && (Flag == RESET));

    if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_HSERDY) != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  Configures the CPU_PLL clock source and multiplication factor.
 * @param  PLLCPU_Source - @ref RST_CLK_PLLCPU_Source_TypeDef - specifies the PLL entry clock source.
 * @param  PLLCPU_Multiplier - @ref RST_CLK_PLLCPU_Multiplier_TypeDef - specifies the PLL multiplication factor.
 * @retval None.
 */
void RST_CLK_CPU_PLL_Config(RST_CLK_PLLCPU_Source_TypeDef PLLCPU_Source, uint32_t PLLCPU_Multiplier)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_RST_CLK_PLLCPU_SOURCE(PLLCPU_Source));
    assert_param(IS_RST_CLK_PLLCPU_MUL(PLLCPU_Multiplier));

    /* Select CPUPLL source */
    Temp = MDR_RST_CLK->CPU_CLOCK;
    /* Clear CPU_C1_SEL bits */
    Temp &= ~RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk;
    /* Set the CPU_C1_SEL bits */
    Temp |= PLLCPU_Source;
    /* Store the new value */
    MDR_RST_CLK->CPU_CLOCK = Temp;

    /* Set CPUPLL multiplier */
    Temp = MDR_RST_CLK->PLL_CONTROL;
    /* Clear PLLMUL[3:0] bits */
    Temp &= ~RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk;
    /* Set the PLLMUL[3:0] bits */
    Temp |= (PLLCPU_Multiplier << RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos);
    /* Store the new value */
    MDR_RST_CLK->PLL_CONTROL = Temp;

    /* Reload PLL if it was already in use */
    if ((MDR_RST_CLK->PLL_CONTROL & RST_CLK_PLL_CONTROL_PLL_CPU_ON) != 0) {
        Temp = MDR_RST_CLK->PLL_CONTROL;
        Temp |= RST_CLK_PLL_CONTROL_PLL_CPU_RLD;
        MDR_RST_CLK->PLL_CONTROL = Temp;
        Temp &= ~RST_CLK_PLL_CONTROL_PLL_CPU_RLD;
        MDR_RST_CLK->PLL_CONTROL = Temp;
    }
}

/**
 * @brief  Enables or disables the CPU_PLL.
 * @param  NewState - @ref FunctionalState - new state of the CPU_PLL.
 * @retval None.
 */
void RST_CLK_CPU_PLL_Cmd(FunctionalState NewState)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    Temp = MDR_RST_CLK->PLL_CONTROL;

    if (NewState != DISABLE) {
        Temp |= RST_CLK_PLL_CONTROL_PLL_CPU_ON;
    } else {
        Temp &= ~RST_CLK_PLL_CONTROL_PLL_CPU_ON;
    }

    MDR_RST_CLK->PLL_CONTROL = Temp;
}

/**
 * @brief  Get CPU_PLL status.
 * @param  None.
 * @retval @ref ErrorStatus - SUCCESS if CPU_PLL output clock is ready, else ERROR.
 */
ErrorStatus RST_CLK_CPU_PLL_GetStatus(void)
{
    __IO uint32_t StartCounter = 0;
    ErrorStatus   State;
    FlagStatus    Flag;

    /* Wait until CPUPLL is ready or time out is occurred */
    do {
        Flag = RST_CLK_GetFlagStatus(RST_CLK_FLAG_PLLCPURDY);
        StartCounter++;
    } while ((StartCounter < PLLCPURDY_TIMEOUT_TICK) && (Flag == RESET));

    if (RST_CLK_GetFlagStatus(RST_CLK_FLAG_PLLCPURDY) != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  Select the CPU_C1 clock source.
 * @param  CPU_C1_Source - @ref RST_CLK_CPU_C1_Source_TypeDef - specifies the CPU_C1 clock source.
 * @retval None.
 */
void RST_CLK_CPU_C1_ClkSelection(RST_CLK_CPU_C1_Source_TypeDef CPU_C1_Source)
{
    uint32_t Temp = 0;

    /* Check the parameters */
    assert_param(IS_RST_CLK_CPU_C1_SOURCE(CPU_C1_Source));

    Temp = MDR_RST_CLK->CPU_CLOCK;

    /* Clear CPU_C3_SEL bits */
    Temp &= ~RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk;

    /* Set the CPU_C3_SEL bits */
    Temp |= (uint32_t)CPU_C1_Source;

    /* Store the new value */
    MDR_RST_CLK->CPU_CLOCK = Temp;
}

/**
 * @brief  Select the CPU_C2 clock source.
 * @param  CPU_C2_Source - @ref RST_CLK_CPU_C2_Source_TypeDef - specifies CPU_C2 clock source.
 * @retval None.
 */
void RST_CLK_CPU_C2_ClkSelection(RST_CLK_CPU_C2_Source_TypeDef CPU_C2_Source)
{
    uint32_t Temp = 0;

    /* Check the parameters */
    assert_param(IS_RST_CLK_CPU_C2_SOURCE(CPU_C2_Source));

    Temp = MDR_RST_CLK->CPU_CLOCK;
    Temp &= ~RST_CLK_CPU_CLOCK_CPU_C2_SEL_Msk;
    Temp |= (uint32_t)CPU_C2_Source;

    /* Configure CPU_CLOCK register with new value */
    MDR_RST_CLK->CPU_CLOCK = Temp;
}

/**
 * @brief  Сonfigures the CPU_C3_SEL division factor switch.
 * @param  CPU_CLK_DivValue - @ref RST_CLK_CPU_C3_Prescaler_TypeDef - specifies the CPU_PLL clock division factor.
 * @retval None.
 */
void RST_CLK_CPU_C3_SetPrescaler(RST_CLK_CPU_C3_Prescaler_TypeDef CPU_CLK_DivValue)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_RST_CLK_CPU_C3_DIV(CPU_CLK_DivValue));

    Temp = MDR_RST_CLK->CPU_CLOCK;

    /* Clear CPU_C3_SEL bits */
    Temp &= ~RST_CLK_CPU_CLOCK_CPU_C3_SEL_Msk;

    /* Set the CPU_C3_SEL bits */
    Temp |= (uint32_t)CPU_CLK_DivValue;

    /* Store the new value */
    MDR_RST_CLK->CPU_CLOCK = Temp;
}

/**
 * @brief  Select the HCLK clock source.
 * @param  CPU_HCLK_Source - @ref RST_CLK_HCLK_Source_TypeDef - specifies the HCLK clock source.
 * @retval None.
 */
void RST_CLK_HCLK_ClkSelection(RST_CLK_HCLK_Source_TypeDef CPU_HCLK_Source)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_RST_CLK_HCLK_SOURCE(CPU_HCLK_Source));

    Temp = MDR_RST_CLK->CPU_CLOCK;

    /* Clear CPU_C3_SEL bits */
    Temp &= ~RST_CLK_CPU_CLOCK_HCLK_SEL_Msk;

    /* Set the CPU_C3_SEL bits */
    Temp |= (uint32_t)CPU_HCLK_Source;

    /* Store the new value */
    MDR_RST_CLK->CPU_CLOCK = Temp;
}

/**
 * @brief  Select the ADC clock source.
 * @param  ADC_CLK_Source - @ref RST_CLK_ADC_Source_TypeDef - specifies the ADC_C2 clock source.
 * @retval None.
 */
void RST_CLK_ADC_ClkSelection(RST_CLK_ADC_Source_TypeDef ADC_CLK_Source)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_RST_CLK_ADC_CLK_SOURCE(ADC_CLK_Source));

    /* Select ADC_CLK source */
    Temp = MDR_RST_CLK->ADC_CLOCK;

    /* Clear ADC_C1,C2 SEL bits */
    Temp &= ~(RST_CLK_ADC_CLOCK_ADC_C1_SEL_Msk);

    /* Set the ADC_C1, SEL bits */
    Temp |= (uint32_t)ADC_CLK_Source;

    /* Store the new value */
    MDR_RST_CLK->ADC_CLOCK = Temp;
}

/**
 * @brief  Сonfigures the ADC_C3_SEL division factor switch.
 * @param  ADC_CLK_DivValue - @ref RST_CLK_ADC_C3_Divisor_TypeDef - specifies the ADC_C2 clock division factor.
 * @retval None.
 */
void RST_CLK_ADC_SetPrescaler(RST_CLK_ADC_C3_Prescaler_TypeDef ADC_CLK_DivValue)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_RST_CLK_ADC_C3_DIV(ADC_CLK_DivValue));

    Temp = MDR_RST_CLK->ADC_CLOCK;

    /* Clear ADC_C3_SEL bits */
    Temp &= ~RST_CLK_ADC_CLOCK_ADC_C3_SEL_Msk;

    /* Set the ADC_C3_SEL bits */
    Temp |= (uint32_t)ADC_CLK_DivValue;

    /* Store the new value */
    MDR_RST_CLK->ADC_CLOCK = Temp;
}

/**
 * @brief  Enables or disables the ADC_CLK clock.
 * @param  NewState - @ref FunctionalState - new state of the ADC_CLK.
 * @retval None.
 */
void RST_CLK_ADC_ClkCmd(FunctionalState NewState)
{
    uint32_t Temp = 0;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    Temp = MDR_RST_CLK->ADC_CLOCK;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the ADC CLK by setting the ADC_CLK_EN bit in the ADC_CLOCK register */
        Temp |= RST_CLK_ADC_CLOCK_ADC_CLK_EN;
    } else {
        /* Disable the ADC CLK by resetting the ADC_CLK_EN bit in the ADC_CLOCK register */
        Temp &= ~RST_CLK_ADC_CLOCK_ADC_CLK_EN;
    }

    /* Configure CPU_CLOCK register with new value */
    MDR_RST_CLK->ADC_CLOCK = Temp;
}

/**
 * @brief  Set the RST_CLK_ADCUI clock configuration to the default reset state.
 * @param  None.
 * @retval None.
 */
void RST_CLK_ADCUI_ClkDeInit(void)
{
    MDR_RST_CLK->ADC_CLOCK &= ~(RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Msk |
                                RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Msk |
                                RST_CLK_ADC_CLOCK_ADCUI_CLK_EN);
}

/**
 * @brief  Select the ADCUI clock source.
 * @param  ADCUI_CLK_C1_Source - @ref RST_CLK_ADCUI_Source_TypeDef - specifies the ADCUI_C1 clock source.
 * @retval None.
 */
void RST_CLK_ADCUI_ClkSelection(RST_CLK_ADCUI_Source_TypeDef ADCUI_CLK_C1_Source)
{
    uint32_t Temp = 0;

    /* Check the parameters */
    assert_param(IS_RST_CLK_ADCUI_CLK_SOURCE(ADCUI_CLK_C1_Source));

    /* Select ADC_CLK source */
    Temp = MDR_RST_CLK->ADC_CLOCK;

    /* Clear ADCUI_C1,C2 SEL bits */
    Temp &= ~RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Msk;

    /* Set the ADCUI_C1 SEL bits */
    Temp |= (uint32_t)ADCUI_CLK_C1_Source;

    /* Store the new value */
    MDR_RST_CLK->ADC_CLOCK = Temp;
}

/**
 * @brief  Configures the ADCUI_C3_SEL division factor switch.
 * @param  ADCUI_CLK_DivValue - @ref RST_CLK_ADCUI_C3_Prescaler_TypeDef - specifies the ADCUI clock division factor.
 * @retval None.
 */
void RST_CLK_ADCUI_SetPrescaler(RST_CLK_ADCUI_C3_Prescaler_TypeDef ADCUI_CLK_DivValue)
{
    uint32_t Temp = 0;

    /* Check the parameters */
    assert_param(IS_RST_CLK_ADCUI_C3_DIV(ADCUI_CLK_DivValue));

    Temp = MDR_RST_CLK->ADC_CLOCK;

    /* Clear ADCUI_C3_SEL bits */
    Temp &= ~RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Msk;

    /* Set the ADCUI_C3_SEL bits */
    Temp |= (uint32_t)ADCUI_CLK_DivValue;

    /* Store the new value */
    MDR_RST_CLK->ADC_CLOCK = Temp;
}

/**
 * @brief  Enables or disables the ADCUI clk.
 * @param  NewState - @ref FunctionalState - new state of the ADCUI clk.
 * @retval None.
 */
void RST_CLK_ADCUI_ClkCmd(FunctionalState NewState)
{
    uint32_t Temp = 0;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    Temp = MDR_RST_CLK->ADC_CLOCK;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable ADCUI clk by setting the ADCUI_CLK_EN bit in the ADC_CLOCK register */
        Temp |= RST_CLK_ADC_CLOCK_ADCUI_CLK_EN;
    } else {
        /* Disable ADCUI clk by resetting the ADCUI_CLK_EN bit in the ADC_CLOCK register */
        Temp &= ~RST_CLK_ADC_CLOCK_ADCUI_CLK_EN;
    }

    /* Configure ADC_CLOCK register with new value */
    MDR_RST_CLK->ADC_CLOCK = Temp;
}

/**
 * @brief  Configures the HSI_C1_SEL division factor switch.
 * @param  HSI_CLK_DivValue - @ref RST_CLK_HSI_C1_Prescaler_TypeDef - specifies the HSI clock division factor.
 * @retval None.
 */
void RST_CLK_HSI_C1_SetPrescaler(RST_CLK_HSI_C1_Prescaler_TypeDef HSI_CLK_DivValue)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_RST_CLK_HSI_CLK_DIV(HSI_CLK_DivValue));

    Temp = MDR_RST_CLK->RTC_CLOCK;

    /* Clear HSI_SEL bits */
    Temp &= ~RST_CLK_RTC_CLOCK_HSI_SEL_Msk;

    /* Set the HSI_SEL bits */
    Temp |= (uint32_t)HSI_CLK_DivValue;

    /* Store the new value */
    MDR_RST_CLK->RTC_CLOCK = Temp;
}

/**
 * @brief  Enables or disables the RTCHSI clock.
 * @param  NewState - @ref FunctionalState - new state of the HSI_RTC_EN.
 * @retval None.
 */
void RST_CLK_RTC_HSI_ClkCmd(FunctionalState NewState)
{
    uint32_t Temp = 0;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    Temp = MDR_RST_CLK->RTC_CLOCK;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable HSI RTC clk by setting the HSE_RTC_EN bit in the RTC_CLOCK register */
        Temp |= RST_CLK_RTC_CLOCK_HSI_RTC_EN;
    } else {
        /* Disable HSI RTC clk by resetting the HSE_RTC_EN bit in the RTC_CLOCK register */
        Temp &= ~RST_CLK_RTC_CLOCK_HSI_RTC_EN;
    }

    /* Configure RTC_CLOCK register with new value */
    MDR_RST_CLK->RTC_CLOCK = Temp;
}

/**
 * @brief  Configures the HSE_C1_SEL division factor switch.
 * @param  HSE_CLK_DivValue - @ref RST_CLK_HSE_C1_Prescaler_TypeDef - specifies the HSE clock division factor.
 * @retval None.
 */
void RST_CLK_HSE_C1_SetPrescaler(RST_CLK_HSE_C1_Prescaler_TypeDef HSE_CLK_DivValue)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_RST_CLK_HSE_CLK_DIV(HSE_CLK_DivValue));

    Temp = MDR_RST_CLK->RTC_CLOCK;

    /* Clear HSE_SEL bits */
    Temp &= ~RST_CLK_RTC_CLOCK_HSE_SEL_Msk;

    /* Set the HSE_SEL bits */
    Temp |= (uint32_t)HSE_CLK_DivValue;

    /* Store the new value */
    MDR_RST_CLK->RTC_CLOCK = Temp;
}

/**
 * @brief  Enables or disables the RTCHSE clock.
 * @param  NewState - @ref FunctionalState - new state of the HSE_RTC_EN.
 * @retval None.
 */
void RST_CLK_RTC_HSE_ClkCmd(FunctionalState NewState)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    Temp = MDR_RST_CLK->RTC_CLOCK;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable HSI RTC clk by setting the HSE_RTC_EN bit in the RTC_CLOCK register */
        Temp |= RST_CLK_RTC_CLOCK_HSE_RTC_EN;
    } else {
        /* Disable HSI RTC clk by resetting the HSE_RTC_EN bit in the RTC_CLOCK register */
        Temp &= ~RST_CLK_RTC_CLOCK_HSE_RTC_EN;
    }

    /* Configure RTC_CLOCK register with new value */
    MDR_RST_CLK->RTC_CLOCK = Temp;
}

/**
 * @brief  Select the clock source for PER1_C1.
 * @param  PER1_C1_Source - @ref RST_CLK_PER1_C1_TypeDef - specifies the PER1_C1 clock source.
 * @retval None.
 */
void RST_CLK_PER1_C1_ClkSelection(RST_CLK_PER1_C1_TypeDef PER1_C1_Source)
{
    /* Check the parameters */
    assert_param(IS_RST_CLK_PER1_C1_CLK_SOURCE(PER1_C1_Source));

    /* Clear old clock source and set new one */
    MDR_RST_CLK->PER1_CLOCK = (MDR_RST_CLK->PER1_CLOCK & (~RST_CLK_PER1_CLOCK_C1_SEL_Msk)) | (uint32_t)PER1_C1_Source;
}

#if defined(USE_MDR32F21QI)
/**
 * @brief  Select the clock source for PER1_C2.
 * @param  PER1_C2_Source - @ref RST_CLK_PER1_C2_TypeDef - specifies the PER1_C2 clock source.
 * @retval None.
 */
void RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_TypeDef PER1_C2_Source)
{
    /* Check the parameters */
    assert_param(IS_RST_CLK_PER1_C2_CLK_SOURCE(PER1_C2_Source));

    MDR_RST_CLK->PER1_CLOCK = (MDR_RST_CLK->PER1_CLOCK & (~RST_CLK_PER1_CLOCK_C2_SEL_Msk)) |
                              ((uint32_t)PER1_C2_Source << RST_CLK_PER1_CLOCK_C2_SEL_Pos);
}

#elif defined(USE_MDR32F23QI)
/**
 * @brief  Select the clock source for PER1_C2_X.
 * @param  PER1_CLK - @ref RST_CLK_PER1_C2_X_TypeDef - peripheral selection.
 * @param  PER1_C2_Source - @ref RST_CLK_PER1_C2_TypeDef - specifies the PER1_C2 clock source.
 * @retval None.
 */
void RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_X_TypeDef PER1_CLK, RST_CLK_PER1_C2_TypeDef PER1_C2_Source)
{
    /* Check the parameters */
    assert_param(IS_RST_CLK_PER1_CLK(PER1_CLK));
    assert_param(IS_RST_CLK_PER1_C2_CLK_SOURCE(PER1_C2_Source));

    switch (PER1_CLK) {
        case RST_CLK_PER1_C2_TIM0:
            MDR_RST_CLK->PER1_CLOCK = (MDR_RST_CLK->PER1_CLOCK & (~RST_CLK_PER1_CLOCK_TIM0_C2_SEL_Msk)) |
                                      ((uint32_t)PER1_C2_Source << RST_CLK_PER1_CLOCK_TIM0_C2_SEL_Pos);
            break;
        case RST_CLK_PER1_C2_TIM1:
            MDR_RST_CLK->PER1_CLOCK = (MDR_RST_CLK->PER1_CLOCK & (~RST_CLK_PER1_CLOCK_TIM1_C2_SEL_Msk)) |
                                      ((uint32_t)PER1_C2_Source << RST_CLK_PER1_CLOCK_TIM1_C2_SEL_Pos);
            break;
        case RST_CLK_PER1_C2_UART0:
            MDR_RST_CLK->PER1_CLOCK = (MDR_RST_CLK->PER1_CLOCK & (~RST_CLK_PER1_CLOCK_UART0_C2_SEL_Msk)) |
                                      ((uint32_t)PER1_C2_Source << RST_CLK_PER1_CLOCK_UART0_C2_SEL_Pos);
            break;
        case RST_CLK_PER1_C2_UART1:
            MDR_RST_CLK->PER1_CLOCK = (MDR_RST_CLK->PER1_CLOCK & (~RST_CLK_PER1_CLOCK_UART1_C2_SEL_Msk)) |
                                      ((uint32_t)PER1_C2_Source << RST_CLK_PER1_CLOCK_UART1_C2_SEL_Pos);
            break;
        case RST_CLK_PER1_C2_SSP:
            MDR_RST_CLK->PER1_CLOCK = (MDR_RST_CLK->PER1_CLOCK & (~RST_CLK_PER1_CLOCK_SSP_C2_SEL_Msk)) |
                                      ((uint32_t)PER1_C2_Source << RST_CLK_PER1_CLOCK_SSP_C2_SEL_Pos);
            break;
    }
}
#endif

/**
 * @brief  Configures division factor switch for @ref RST_CLK_PER1_C2_X_TypeDef peripheral.
 * @param  PER1_CLK - @ref RST_CLK_PER1_C2_X_TypeDef - peripheral selection.
 * @param  PER1_C2_DivValue - @ref RST_CLK_PER1_C2_Prescaler_TypeDef - specifies prescaler.
 * @retval None.
 */
void RST_CLK_PER1_C2_SetPrescaler(RST_CLK_PER1_C2_X_TypeDef PER1_CLK, RST_CLK_PER1_C2_Prescaler_TypeDef PER1_C2_DivValue)
{
    /* Check the parameters */
    assert_param(IS_RST_CLK_PER1_CLK(PER1_CLK));
    assert_param(IS_RST_CLK_PER1_C2_DIV(PER1_C2_DivValue));

    switch (PER1_CLK) {
        case RST_CLK_PER1_C2_TIM0:
            MDR_RST_CLK->TIM_CLOCK = (MDR_RST_CLK->TIM_CLOCK & (~RST_CLK_TIM_CLOCK_TIM0_BRG_Msk)) |
                                     ((uint32_t)PER1_C2_DivValue << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos);
            break;
        case RST_CLK_PER1_C2_TIM1:
            MDR_RST_CLK->TIM_CLOCK = (MDR_RST_CLK->TIM_CLOCK & (~RST_CLK_TIM_CLOCK_TIM1_BRG_Msk)) |
                                     ((uint32_t)PER1_C2_DivValue << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos);
            break;
        case RST_CLK_PER1_C2_UART0:
            MDR_RST_CLK->UART_CLOCK = (MDR_RST_CLK->UART_CLOCK & (~RST_CLK_UART_CLOCK_UART0_BRG_Msk)) |
                                      ((uint32_t)PER1_C2_DivValue << RST_CLK_UART_CLOCK_UART0_BRG_Pos);
            break;
        case RST_CLK_PER1_C2_UART1:
            MDR_RST_CLK->UART_CLOCK = (MDR_RST_CLK->UART_CLOCK & (~RST_CLK_UART_CLOCK_UART1_BRG_Msk)) |
                                      ((uint32_t)PER1_C2_DivValue << RST_CLK_UART_CLOCK_UART1_BRG_Pos);
            break;
        case RST_CLK_PER1_C2_SSP:
            MDR_RST_CLK->SSP_CLOCK = (MDR_RST_CLK->SSP_CLOCK & (~RST_CLK_SSP_CLOCK_SSP_BRG_Msk)) |
                                     ((uint32_t)PER1_C2_DivValue << RST_CLK_SSP_CLOCK_SSP_BRG_Pos);
            break;
    }
}

/**
 * @brief  Enables or disables @ref RST_CLK_PER1_C2_X_TypeDef peripheral clock.
 * @param  PER1_CLK - @ref RST_CLK_PER1_C2_X_TypeDef - peripheral selection.
 * @param  NewState - @ref FunctionalState - new state of the peripheral clock.
 * @retval None.
 */
void RST_CLK_PER1_C2_Cmd(RST_CLK_PER1_C2_X_TypeDef PER1_CLK, FunctionalState NewState)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    switch (PER1_CLK) {
        case RST_CLK_PER1_C2_TIM0:
            Temp = (MDR_RST_CLK->TIM_CLOCK & (~RST_CLK_TIM_CLOCK_TIM0_CLK_EN_Msk));
            Temp |= ((uint32_t)NewState << RST_CLK_TIM_CLOCK_TIM0_CLK_EN_Pos);
            MDR_RST_CLK->TIM_CLOCK = Temp;
            break;
        case RST_CLK_PER1_C2_TIM1:
            Temp = (MDR_RST_CLK->TIM_CLOCK & (~RST_CLK_TIM_CLOCK_TIM1_CLK_EN_Msk));
            Temp |= ((uint32_t)NewState << RST_CLK_TIM_CLOCK_TIM1_CLK_EN_Pos);
            MDR_RST_CLK->TIM_CLOCK = Temp;
            break;
        case RST_CLK_PER1_C2_UART0:
            Temp = (MDR_RST_CLK->UART_CLOCK & (~RST_CLK_UART_CLOCK_UART0_CLK_EN_Msk));
            Temp |= ((uint32_t)NewState << RST_CLK_UART_CLOCK_UART0_CLK_EN_Pos);
            MDR_RST_CLK->UART_CLOCK = Temp;
            break;
        case RST_CLK_PER1_C2_UART1:
            Temp = (MDR_RST_CLK->UART_CLOCK & (~RST_CLK_UART_CLOCK_UART1_CLK_EN_Msk));
            Temp |= ((uint32_t)NewState << RST_CLK_UART_CLOCK_UART1_CLK_EN_Pos);
            MDR_RST_CLK->UART_CLOCK = Temp;
            break;
        case RST_CLK_PER1_C2_SSP:
            Temp = (MDR_RST_CLK->SSP_CLOCK & (~RST_CLK_SSP_CLOCK_SSP_CLK_EN_Msk));
            Temp |= ((uint32_t)NewState << RST_CLK_SSP_CLOCK_SSP_CLK_EN_Pos);
            MDR_RST_CLK->SSP_CLOCK = Temp;
            break;
    }
}

#if defined(USE_MDR32F21QI)
/**
 * @brief  Set the DMA clock state.
 * @param  NewState - @ref FunctionalState - new state of the DMA clock.
 * @retval None.
 */
void RST_CLK_DMACmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_RST_CLK->PER1_CLOCK |= RST_CLK_PER1_CLOCK_DMA_EN;
    } else {
        MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER1_CLOCK_DMA_EN;
    }
}

/**
 * @brief  Get the DMA clock state.
 * @param  None.
 * @retval @ref FunctionalState - the state of the DMA clock.
 */
FunctionalState RST_CLK_DMAState(void)
{
    FunctionalState dma_state;

    if (MDR_RST_CLK->PER1_CLOCK & RST_CLK_PER1_CLOCK_DMA_EN) {
        dma_state = ENABLE;
    } else {
        dma_state = DISABLE;
    }

    return (FunctionalState)dma_state;
}
#endif

/**
 * @brief  Set the DEBUG clock state.
 * @param  NewState - @ref FunctionalState - new state of the DEBUG clock.
 * @retval None.
 */
void RST_CLK_DEBUGCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_RST_CLK->PER1_CLOCK |= RST_CLK_PER1_CLOCK_DEBUG_EN;
    } else {
        MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER1_CLOCK_DEBUG_EN;
    }
}

/**
 * @brief  Get the DEBUG clock state.
 * @param  None.
 * @retval @ref FunctionalState - the state of the DEBUG clock.
 */
FunctionalState RST_CLK_DEBUGState(void)
{
    FunctionalState DebugState;

    if (MDR_RST_CLK->PER1_CLOCK & RST_CLK_PER1_CLOCK_DEBUG_EN) {
        DebugState = ENABLE;
    } else {
        DebugState = DISABLE;
    }

    return (FunctionalState)DebugState;
}

/**
 * @brief  Enables or disables clock of peripherals.
 * @param  RST_CLK_PCLK: specifies the peripheral to gates its clock.
 *         This parameter can be any combination of the @ref RST_CLK_PCLK_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the specified peripheral clock.
 * @retval None.
 */
void RST_CLK_PCLKCmd(uint32_t RST_CLK_PCLK, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_RST_CLK_PCLK(RST_CLK_PCLK));

    if (NewState != DISABLE) {
        MDR_RST_CLK->PER2_CLOCK |= RST_CLK_PCLK;
    } else {
        MDR_RST_CLK->PER2_CLOCK &= ~RST_CLK_PCLK;
    }
}

/**
 * @brief  Put the frequencies of different on chip clocks in *RST_CLK_Clocks structure.
 * @param  RST_CLK_Clocks: pointer to a @ref RST_CLK_Freq_TypeDef structure that will hold
 *         the clocks frequencies.
 * @retval None.
 */
void RST_CLK_GetClocksFreq(RST_CLK_Freq_TypeDef* RST_CLK_Clocks)
{
    uint32_t CPU_C1_Freq = 0, CPU_C2_Freq = 0, CPU_C3_Freq = 0;
    uint32_t ADC_C1_Freq = 0, ADC_C3_Freq = 0;
    uint32_t ADCUI_C1_Freq = 0, ADCUI_C3_Freq = 0;
    uint32_t HSI_C1_Freq = 0, HSE_C1_Freq = 0;
    uint32_t PER_C1_Freq = 0, PER_C2_Freq = 0;
    uint32_t PLL_Mult = 0;
    uint32_t Temp     = 0;
#if defined(USE_MDR32F23QI)
    uint8_t  i           = 0;
    uint32_t PerMasks[]  = { RST_CLK_PER1_CLOCK_TIM0_C2_SEL_Msk, RST_CLK_PER1_CLOCK_TIM1_C2_SEL_Msk,
                             RST_CLK_PER1_CLOCK_UART0_C2_SEL_Msk, RST_CLK_PER1_CLOCK_UART1_C2_SEL_Msk,
                             RST_CLK_PER1_CLOCK_SSP_C2_SEL_Msk };
    uint32_t PerShifts[] = { RST_CLK_PER1_CLOCK_TIM0_C2_SEL_Pos, RST_CLK_PER1_CLOCK_TIM1_C2_SEL_Pos,
                             RST_CLK_PER1_CLOCK_UART0_C2_SEL_Pos, RST_CLK_PER1_CLOCK_UART1_C2_SEL_Pos,
                             RST_CLK_PER1_CLOCK_SSP_C2_SEL_Pos };
#endif

    /* Check the parameter */
    assert_param(RST_CLK_Clocks != 0);

    /* Compute CPU_CLK, ADC_CLK, ADCUI_CLK, RTCHSI, RTCHSE clocks frequencies */

    /* Compute CPU_CLK frequency */

    Temp = MDR_RST_CLK->CPU_CLOCK;

    /* Determine CPU_C1 frequency */
    switch (Temp & RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk) {
        case RST_CLK_CPU_C1_SRC_HSI:
            CPU_C1_Freq = HSI_FREQUENCY_Hz;
            break;
        case RST_CLK_CPU_C1_SRC_HSI_DIV_2:
            CPU_C1_Freq = HSI_FREQUENCY_Hz / 2;
            break;
        case RST_CLK_CPU_C1_SRC_HSE:
            CPU_C1_Freq = HSE_FREQUENCY_Hz;
            break;
        case RST_CLK_CPU_C1_SRC_HSE_DIV_2:
            CPU_C1_Freq = HSE_FREQUENCY_Hz / 2;
            break;
    }

    /* Determine CPU_C2 frequency */
    CPU_C2_Freq = CPU_C1_Freq;

    /* Determine CPU PLL output frequency */
    PLL_Mult = ((MDR_RST_CLK->PLL_CONTROL & RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk) >> RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos) + 1;

    if (Temp & RST_CLK_CPU_CLOCK_CPU_C2_SEL_Msk) {
        CPU_C2_Freq *= PLL_Mult;
    }

    /* Select CPU_CLK from HSI, CPU_C3, LSE, LSI cases */
    switch (Temp & RST_CLK_CPU_CLOCK_HCLK_SEL_Msk) {
        case RST_CLK_CPU_CLK_HSI:
            RST_CLK_Clocks->CPU_CLK_Frequency = HSI_FREQUENCY_Hz;
            break;
        case RST_CLK_CPU_CLK_CPU_C3:
            /* Determine CPU_C3 frequency */
            Temp = ((Temp & RST_CLK_CPU_CLOCK_CPU_C3_SEL_Msk) >> RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos);
            if ((Temp & 0x8U) == 0x00) {
                CPU_C3_Freq = CPU_C2_Freq;
            } else {
                CPU_C3_Freq = CPU_C2_Freq >> ((Temp & 0x7U) + 1);
            }
            RST_CLK_Clocks->CPU_CLK_Frequency = CPU_C3_Freq;
            break;
        case RST_CLK_CPU_CLK_LSE:
            RST_CLK_Clocks->CPU_CLK_Frequency = LSE_FREQUENCY_Hz;
            break;
        case RST_CLK_CPU_CLK_LSI:
            RST_CLK_Clocks->CPU_CLK_Frequency = LSI_FREQUENCY_Hz;
            break;
    }

    /* Compute RTCHSE_CLK frequency */
    Temp = MDR_RST_CLK->RTC_CLOCK;
    if ((Temp & 0x8U) == 0) {
        HSE_C1_Freq = HSE_FREQUENCY_Hz;
    } else {
        HSE_C1_Freq = HSE_FREQUENCY_Hz >> ((Temp & 0x7U) + 1);
    }
    RST_CLK_Clocks->RTCHSE_Frequency = HSE_C1_Freq;

    /* Compute RTCHSI_CLK frequency */
    Temp >>= RST_CLK_RTC_CLOCK_HSI_SEL_Pos;
    if ((Temp & 0x8U) == 0) {
        HSI_C1_Freq = HSI_FREQUENCY_Hz;
    } else {
        HSI_C1_Freq = HSI_FREQUENCY_Hz >> ((Temp & 0x7U) + 1);
    }
    RST_CLK_Clocks->RTCHSI_Frequency = HSI_C1_Freq;

    /* Determine clock frequency per_c1 */
    Temp = MDR_RST_CLK->PER1_CLOCK;
    switch (Temp & RST_CLK_PER1_CLOCK_C1_SEL_Msk) {
        case RST_CLK_PER1_C1_CLK_SRC_LSI:
            PER_C1_Freq = LSI_FREQUENCY_Hz;
            break;
        case RST_CLK_PER1_C1_CLK_SRC_LSI_DIV_2:
            PER_C1_Freq = LSI_FREQUENCY_Hz / 2;
            break;
        case RST_CLK_PER1_C1_CLK_SRC_LSE:
            PER_C1_Freq = LSE_FREQUENCY_Hz;
            break;
        case RST_CLK_PER1_C1_CLK_SRC_LSE_DIV_2:
            PER_C1_Freq = LSE_FREQUENCY_Hz / 2;
            break;
    }
#if defined(USE_MDR32F21QI)
    /* Determine clock frequency per_c2 */
    switch ((Temp & RST_CLK_PER1_CLOCK_C2_SEL_Msk) >> RST_CLK_PER1_CLOCK_C2_SEL_Pos) {
        case RST_CLK_PER1_C2_CLK_SRC_CPU_C1:
            PER_C2_Freq = CPU_C1_Freq;
            break;
        case RST_CLK_PER1_C2_CLK_SRC_PER1_C1:
            PER_C2_Freq = PER_C1_Freq;
            break;
        case RST_CLK_PER1_C2_CLK_SRC_PLLCPU:
            PER_C2_Freq = CPU_C1_Freq * PLL_Mult;
            break;
        case RST_CLK_PER1_C2_CLK_SRC_HSI_CLK:
            PER_C2_Freq = HSI_FREQUENCY_Hz;
            break;
    }

    RST_CLK_Clocks->TIMER_Frequency[0] = PER_C2_Freq;
    RST_CLK_Clocks->TIMER_Frequency[1] = PER_C2_Freq;
    RST_CLK_Clocks->UART_Frequency[0]  = PER_C2_Freq;
    RST_CLK_Clocks->UART_Frequency[1]  = PER_C2_Freq;
    RST_CLK_Clocks->SSP_Frequency      = PER_C2_Freq;

#elif defined(USE_MDR32F23QI)
    for (i = 0; i < 5; i++) {
        /* Determine clock frequency c2 for TIMERx, UARTx or SSP */
        switch ((Temp & PerMasks[i]) >> PerShifts[i]) {
            case RST_CLK_PER1_C2_CLK_SRC_CPU_C1:
                PER_C2_Freq = CPU_C1_Freq;
                break;
            case RST_CLK_PER1_C2_CLK_SRC_PER1_C1:
                PER_C2_Freq = PER_C1_Freq;
                break;
            case RST_CLK_PER1_C2_CLK_SRC_PLLCPU:
                PER_C2_Freq = CPU_C1_Freq * PLL_Mult;
                break;
            case RST_CLK_PER1_C2_CLK_SRC_HSI_CLK:
                PER_C2_Freq = HSI_FREQUENCY_Hz;
                break;
        }

        switch ((RST_CLK_PER1_C2_X_TypeDef)i) {
            case RST_CLK_PER1_C2_TIM0:
                RST_CLK_Clocks->TIMER_Frequency[0] = PER_C2_Freq >>
                                                     ((MDR_RST_CLK->TIM_CLOCK & RST_CLK_TIM_CLOCK_TIM0_BRG_Msk) >> RST_CLK_TIM_CLOCK_TIM0_BRG_Pos);
                break;
            case RST_CLK_PER1_C2_TIM1:
                RST_CLK_Clocks->TIMER_Frequency[1] = PER_C2_Freq >>
                                                     ((MDR_RST_CLK->TIM_CLOCK & RST_CLK_TIM_CLOCK_TIM1_BRG_Msk) >> RST_CLK_TIM_CLOCK_TIM1_BRG_Pos);
                break;
            case RST_CLK_PER1_C2_UART0:
                RST_CLK_Clocks->UART_Frequency[0] = PER_C2_Freq >>
                                                    ((MDR_RST_CLK->UART_CLOCK & RST_CLK_UART_CLOCK_UART0_BRG_Msk) >> RST_CLK_UART_CLOCK_UART0_BRG_Pos);
                break;
            case RST_CLK_PER1_C2_UART1:
                RST_CLK_Clocks->UART_Frequency[1] = PER_C2_Freq >>
                                                    ((MDR_RST_CLK->UART_CLOCK & RST_CLK_UART_CLOCK_UART1_BRG_Msk) >> RST_CLK_UART_CLOCK_UART1_BRG_Pos);
                break;
            case RST_CLK_PER1_C2_SSP:
                RST_CLK_Clocks->SSP_Frequency = PER_C2_Freq >>
                                                ((MDR_RST_CLK->SSP_CLOCK & RST_CLK_SSP_CLOCK_SSP_BRG_Msk) >> RST_CLK_SSP_CLOCK_SSP_BRG_Pos);
                break;
        }
    }
#endif

    /* Compute ADC_CLK frequency */
    Temp = MDR_RST_CLK->ADC_CLOCK;
    /* Select ADC_C1 from cpu_c1, PER_C1_Freq, CPU_C2_Freq, HSI_C1 cases */
    switch ((Temp & RST_CLK_ADC_CLOCK_ADC_C1_SEL_Msk) >> RST_CLK_ADC_CLOCK_ADC_C1_SEL_Pos) {
        case RST_CLK_ADC_CLK_CPU_C1:
            ADC_C1_Freq = CPU_C1_Freq;
            break;
        case RST_CLK_ADC_CLK_PER1_C1:
            ADC_C1_Freq = PER_C1_Freq;
            break;
        case RST_CLK_ADC_CLK_PLLCPU:
            ADC_C1_Freq = CPU_C2_Freq;
            break;
        case RST_CLK_ADC_CLK_HSI_CLK:
            ADC_C1_Freq = HSI_FREQUENCY_Hz;
            break;
    }
    /* Compute ADC_CLK divisor */
    if (((Temp >> RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos) & 0x8U) == 0) {
        ADC_C3_Freq = ADC_C1_Freq;
    } else {
        ADC_C3_Freq = ADC_C1_Freq >> (((Temp >> RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos) & 0x7U) + 1);
    }

    RST_CLK_Clocks->ADC_Frequency = ADC_C3_Freq;

    /* Compute ADCUI_CLK frequency */

    /* Select ADCUI_C1 from cpu_c1, PER_C1_Freq, CPU_C2_Freq, HSI_C1 cases */
    switch (Temp & RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Msk) {
        case RST_CLK_ADCUI_CLK_CPU_C1:
            ADCUI_C1_Freq = CPU_C1_Freq;
            break;
        case RST_CLK_ADCUI_CLK_PER1_C1:
            ADCUI_C1_Freq = PER_C1_Freq;
            break;
        case RST_CLK_ADCUI_CLK_PLLCPU:
            ADCUI_C1_Freq = CPU_C2_Freq;
            break;
        case RST_CLK_ADCUI_CLK_HSI_CLK:
            ADCUI_C1_Freq = HSI_FREQUENCY_Hz;
            break;
    }

    if (((Temp >> RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos) & 0x8U) == 0) {
        ADCUI_C3_Freq = ADCUI_C1_Freq;
    } else {
        ADCUI_C3_Freq = ADCUI_C1_Freq >> (((Temp >> RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos) & 0x7U) + 1);
    }

    RST_CLK_Clocks->ADCUI_Frequency = ADCUI_C3_Freq;
}

/**
 * @brief  Checks whether the specified RST flag is set or not.
 * @param  RST_CLK_Flag - @ref RST_CLK_Flags_TypeDef - specifies the flag to check.
 * @retval @ref FlagStatus - The state of RST_FLAG (SET or RESET).
 */
FlagStatus RST_CLK_GetFlagStatus(RST_CLK_Flags_TypeDef RST_CLK_Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_RST_CLK_FLAG(RST_CLK_Flag));

    /* Get the flag status on proper position */
    if ((MDR_RST_CLK->CLOCK_STATUS & (uint32_t)RST_CLK_Flag) != RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    /* Return the flag status */
    return Status;
}

/** @} */ /* End of group RST_CLK_Exported_Functions */

/** @} */ /* End of group RST_CLK */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_rst_clk.c */

