/**
 *******************************************************************************
 * @file    MDR32VF0xI_adc.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    14/02/2025
 * @brief   This file contains all the ADC firmware functions.
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
#include "MDR32VF0xI_adc.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @defgroup ADC ADC
 * @{
 */

/** @defgroup ADC_Private_Defines ADC Private Defines
 * @{
 */

#define ADC1_STATUS_CLEANABLE_MASK (ADC1_STATUS_FLG_REG_OVERWRITE | \
                                    ADC1_STATUS_FLG_REG_AWOIFEN)

#define ADC1_STATUS_FLAGS_MASK (ADC1_STATUS_FLG_REG_OVERWRITE | \
                                ADC1_STATUS_FLG_REG_AWOIFEN |   \
                                ADC1_STATUS_FLG_REG_EOCIF)

/** @} */ /* End of the group ADC_Private_Defines */

/** @defgroup ADC_Exported_Functions ADC Exported Functions
 * @{
 */

/**
 * @brief   Deinitialize the ADC peripheral registers to their default reset values.
 * @warning Also set BG_TRIM to default value (0x10).
 * @param   None.
 * @return  None.
 */
void ADC_DeInit(void)
{
    MDR_ADC->ADC1_CFG     = 0;
    MDR_ADC->ADC1_H_LEVEL = 0;
    MDR_ADC->ADC1_L_LEVEL = 0;
    MDR_ADC->ADC1_RESULT;
    MDR_ADC->ADC1_STATUS = 0;
    MDR_ADC->ADC1_CHSEL  = 0;
    MDR_ADC->ADC_TRIM    = 0x00000020;
}

/**
 * @brief  Initialize the ADC peripheral according to
 *         the specified parameters in the ADC_InitStruct.
 * @param  ADC_InitStruct: The pointer to the @ref ADC_InitTypeDef structure
 *         that contains the configuration information for the ADC peripheral.
 * @return None.
 */
void ADC_Init(const ADC_InitTypeDef* ADC_InitStruct)
{
    uint32_t TempCFG1, TempReg;

    /* Check the parameters. */
    assert_param(IS_ADC_CLOCK_SOURCE_CONFIG(ADC_InitStruct->ADC_ClockSource));
    assert_param(IS_ADC_CLK_DIV_VALUE(ADC_InitStruct->ADC_Prescaler));
    assert_param(IS_ADC_VREF_SOURCE_CONFIG(ADC_InitStruct->ADC_VRefSource));
    assert_param(IS_ADC_SCALE_MAX(ADC_InitStruct->ADC_Scale));
    assert_param(IS_ADC_CH_SWITCHING_CONFIG(ADC_InitStruct->ADC_ChannelSwitching));
    assert_param(IS_ADC_CH_NUM(ADC_InitStruct->ADC_ChannelNumber));
    assert_param((ADC_InitStruct->ADC_ChannelSwitching != ADC_CH_SWITCHING_DISABLE) ? IS_ADC_CH_MASK(ADC_InitStruct->ADC_Channels) : 1);
    assert_param(IS_ADC_SAMPLING_MODE_CONFIG(ADC_InitStruct->ADC_SamplingMode));
    assert_param(IS_ADC_DELAY_GO_VALUE(ADC_InitStruct->ADC_DelayGo));
    assert_param(IS_ADC_LEVEL_CONTROL_CONFIG(ADC_InitStruct->ADC_LevelControl));
    assert_param((ADC_InitStruct->ADC_LevelControl != ADC_LEVEL_CONTROL_DISABLE) ? IS_ADC_VALUE(ADC_InitStruct->ADC_LowLevel) : 1);
    assert_param((ADC_InitStruct->ADC_LevelControl != ADC_LEVEL_CONTROL_DISABLE) ? IS_ADC_VALUE(ADC_InitStruct->ADC_HighLevel) : 1);

    TempReg = MDR_RST_CLK->PER2_CLOCK;
    if ((TempReg & RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI) == 0) {
        MDR_RST_CLK->PER2_CLOCK = TempReg | RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI;
    }

    if (ADC_InitStruct->ADC_VRefSource == ADC_VREF_SOURCE_EXTERNAL) {
        MDR_ADCUI->CTRL1 &= ~ADCUI_CTRL1_VREF_SEL;
    } else {
        MDR_ADCUI->CTRL1 |= ADCUI_CTRL1_VREF_SEL;
    }

    if ((TempReg & RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI) == 0) {
        MDR_RST_CLK->PER2_CLOCK = TempReg;
    }
#if defined(USE_MDR32F02)
    TempCFG1 = (MDR_ADC->ADC1_CFG & ADC1_CFG_EN_NOISE_RNG) | 0x00020000;
#else
    TempCFG1 = 0x00020000;
#endif
    TempCFG1 |= (uint32_t)ADC_InitStruct->ADC_ClockSource |
                (uint32_t)ADC_InitStruct->ADC_SamplingMode |
                (uint32_t)ADC_InitStruct->ADC_ChannelNumber |
                (uint32_t)ADC_InitStruct->ADC_ChannelSwitching |
                (uint32_t)ADC_InitStruct->ADC_LevelControl |
                (uint32_t)ADC_InitStruct->ADC_Scale |
                (uint32_t)ADC_InitStruct->ADC_Prescaler |
                (((uint32_t)ADC_InitStruct->ADC_DelayGo) << ADC1_CFG_DELAY_GO_Pos);

    MDR_ADC->ADC1_L_LEVEL = (uint32_t)ADC_InitStruct->ADC_LowLevel;
    MDR_ADC->ADC1_H_LEVEL = (uint32_t)ADC_InitStruct->ADC_HighLevel;
    MDR_ADC->ADC1_CHSEL   = ADC_InitStruct->ADC_Channels;

    MDR_ADC->ADC1_CFG = TempCFG1;
}

/**
 * @brief  Fill each ADC_InitStruct member with its default value.
 * @param  ADC_InitStruct: The pointer to the @ref ADC_InitTypeDef structure
 *         which will be initialized.
 * @return None.
 */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
    ADC_InitStruct->ADC_ClockSource      = ADC_CLOCK_SOURCE_PCLKd;
    ADC_InitStruct->ADC_Prescaler        = ADC_PRESCALER_DIV_1;
    ADC_InitStruct->ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
    ADC_InitStruct->ADC_Scale            = ADC_SCALE_MAX_UCCA;
    ADC_InitStruct->ADC_ChannelSwitching = ADC_CH_SWITCHING_DISABLE;
    ADC_InitStruct->ADC_ChannelNumber    = ADC_CH_ADC0_TEMP_SENSOR;
    ADC_InitStruct->ADC_Channels         = 0;
    ADC_InitStruct->ADC_SamplingMode     = ADC_SAMPLING_MODE_SINGLE_CONV;
    ADC_InitStruct->ADC_DelayGo          = 0;
    ADC_InitStruct->ADC_LevelControl     = ADC_LEVEL_CONTROL_DISABLE;
    ADC_InitStruct->ADC_LowLevel         = 0;
    ADC_InitStruct->ADC_HighLevel        = 0;
}

/**
 * @brief  Enable or disable the ADC peripheral.
 * @note   Enabling ADC with the ADC_CH_SWITCHING_ENABLE configuration
 *         will automatically start the ADC conversion.
 * @param  NewState: @ref FunctionalState - a new state of the ADC peripheral.
 * @return None.
 */
void ADC_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Enable ADC by setting the Cfg_REG_ADON bit in the ADC1_CFG register. */
        MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_ADON;
    } else {
        /* Disable ADC by resetting the Cfg_REG_ADON bit in the ADC1_CFG register. */
        MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_ADON;
    }
}

/**
 * @brief  Get the ADC peripheral work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the ADC peripheral.
 */
FunctionalState ADC_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_ADC->ADC1_CFG & ADC1_CFG_REG_ADON) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

#if defined(USE_MDR32F02)

/**
 * @brief  Enable or disable power noise RNG.
 * @note   This function can be used only for MDR32F02 microcontroller.
 * @param  NewState: @ref FunctionalState - a new state of power noise RNG.
 * @return None.
 */
void ADC_NoiseRNGCmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Enable power noise RNG by setting the en_noise_rng bit in the ADC1_CFG register. */
        MDR_ADC->ADC1_CFG |= ADC1_CFG_EN_NOISE_RNG;
    } else {
        /* Disable power noise RNG by resetting the en_noise_rng bit in the ADC1_CFG register. */
        MDR_ADC->ADC1_CFG &= ~ADC1_CFG_EN_NOISE_RNG;
    }
}

/**
 * @brief  Get the power noise RNG work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the power noise RNG.
 */
FunctionalState ADC_GetNoiseRNGCmdState(void)
{
    FunctionalState State;

    if ((MDR_ADC->ADC1_CFG & ADC1_CFG_EN_NOISE_RNG) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

#endif

/**
 * @brief  Select the ADC channel number for single channel mode conversion.
 * @param  Channel: @ref ADC_ChannelNumber_TypeDef - specify the ADC channel number.
 * @return None.
 */
void ADC_SetChannel(ADC_ChannelNumber_TypeDef Channel)
{
    uint32_t TempCFG;

    /* Check the parameters. */
    assert_param(IS_ADC_CH_NUM(Channel));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~ADC1_CFG_REG_CHS_Msk;
    TempCFG |= (uint32_t)Channel;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Select the ADC channels for conversion with channels switching.
 * @param  ChannelMask: Specify the ADC channels mask.
 *         This parameter can be any combination of the @ref ADC_ChannelNumber_TypeDef values.
 * @return None.
 */
void ADC_SetChannels(uint32_t ChannelMask)
{
    /* Check the parameters. */
    assert_param(IS_ADC_CH_MASK(ChannelMask));

    MDR_ADC->ADC1_CHSEL = ChannelMask;
}

/**
 * @brief  Set the ADC operation mode.
 * @param  SamplingMode: @ref ADC_SamplingMode_TypeDef - specify the ADC sampling.
 * @param  SwitchingMode: @ref ADC_ChannelSwitching_TypeDef - specify the ADC channel switching.
 * @return None.
 */
void ADC_OperationModeConfig(ADC_SamplingMode_TypeDef SamplingMode, ADC_ChannelSwitching_TypeDef SwitchingMode)
{
    uint32_t TempCFG;

    /* Check the parameters. */
    assert_param(IS_ADC_SAMPLING_MODE_CONFIG(SamplingMode));
    assert_param(IS_ADC_CH_SWITCHING_CONFIG(SwitchingMode));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~(ADC1_CFG_REG_SAMPLE | ADC1_CFG_REG_CHCH);
    TempCFG |= (uint32_t)SamplingMode | (uint32_t)SwitchingMode;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Set the ADC sampling mode.
 * @param  SamplingMode: @ref ADC_SamplingMode_TypeDef - specify the ADC sampling mode.
 * @return None.
 */
void ADC_SamplingModeConfig(ADC_SamplingMode_TypeDef SamplingMode)
{
    uint32_t TempCFG;

    /* Check the parameters. */
    assert_param(IS_ADC_SAMPLING_MODE_CONFIG(SamplingMode));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~ADC1_CFG_REG_SAMPLE;
    TempCFG |= (uint32_t)SamplingMode;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Set the ADC channel switching mode.
 * @param  SwitchingMode: @ref ADC_ChannelSwitching_TypeDef - specify the ADC channel switching mode.
 * @return None.
 */
void ADC_ChannelSwitchingConfig(ADC_ChannelSwitching_TypeDef SwitchingMode)
{
    uint32_t TempCFG;

    /* Check the parameters. */
    assert_param(IS_ADC_CH_SWITCHING_CONFIG(SwitchingMode));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~ADC1_CFG_REG_CHCH;
    TempCFG |= (uint32_t)SwitchingMode;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Configure the ADC threshold levels.
 * @param  LowLevel: Specify the ADC low level value.
 *         This parameter can be a number from 0x0000 to 0x03FF.
 * @param  HighLevel: Specify the ADC high level value.
 *         This parameter can be a number from 0x0000 to 0x03FF.
 * @param  NewState: @ref ADC_LevelControl_TypeDef - enable or disable levels control.
 * @return None.
 */
void ADC_LevelsConfig(uint32_t LowLevel, uint32_t HighLevel, ADC_LevelControl_TypeDef NewState)
{
    /* Check the parameters. */
    assert_param(IS_ADC_LEVEL_CONTROL_CONFIG(NewState));
    assert_param(IS_ADC_VALUE(LowLevel));
    assert_param(IS_ADC_VALUE(HighLevel));

    if (NewState != ADC_LEVEL_CONTROL_DISABLE) {
        MDR_ADC->ADC1_L_LEVEL = LowLevel;
        MDR_ADC->ADC1_H_LEVEL = HighLevel;
        MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_RNGC;
    } else {
        MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_RNGC;
        MDR_ADC->ADC1_L_LEVEL = LowLevel;
        MDR_ADC->ADC1_H_LEVEL = HighLevel;
    }
}

/**
 * @brief  Set the ADC low level.
 * @param  LowLevel: Specify the ADC low level value.
 *         This parameter can be a number from 0x0000 to 0x03FF.
 * @return None.
 */
void ADC_SetLowLevel(uint32_t LowLevel)
{
    /* Check the parameters. */
    assert_param(IS_ADC_VALUE(LowLevel));

    MDR_ADC->ADC1_L_LEVEL = LowLevel;
}

/**
 * @brief  Set the ADC high level.
 * @param  HighLevel: Specify the ADC high level value.
 *         This parameter can be a number from 0x0000 to 0x03FF.
 * @return None.
 */
void ADC_SetHighLevel(uint32_t HighLevel)
{
    /* Check the parameters. */
    assert_param(IS_ADC_VALUE(HighLevel));

    MDR_ADC->ADC1_H_LEVEL = HighLevel;
}

/**
 * @brief   Start the ADC conversion.
 * @warning If ADC is configured with ADC_CH_SWITCHING_ENABLE, this function will
 *          do nothing if ADC is enabled, because the start of the ADC conversion
 *          is controlled by hardware.
 * @param   None.
 * @return  None.
 */
void ADC_Start(void)
{
    MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_GO;
}

/**
 * @brief  Return the ADC conversion result.
 * @param  None.
 * @return ADC result register value.
 */
uint32_t ADC_GetResult(void)
{
    return MDR_ADC->ADC1_RESULT;
}

/**
 * @brief  Return the ADC conversion result placed into structure.
 * @param  ADC_Result: The pointer to the @ref ADC_Result_TypeDef structure
 *         which will hold ADC conversion result.
 * @return None.
 */
void ADC_GetResultStruct(ADC_Result_TypeDef* ADC_Result)
{
    uint32_t Result = MDR_ADC->ADC1_RESULT;

    ADC_Result->ADC_Result        = (uint16_t)(Result & ADC1_RESULT_RESULT_Msk);
    ADC_Result->ADC_ResultChannel = (ADC_ChannelNumber_TypeDef)((Result >> ADC1_RESULT_CHANNEL_Pos) << ADC1_CFG_REG_CHS_Pos);
}

/**
 * @brief  Check whether the specified ADC status flag is set or not.
 * @param  Flag: @ref ADC_Flags_TypeDef - specify the flag to check.
 * @return @ref FlagStatus - the current status flag state (SET or RESET).
 */
FlagStatus ADC_GetFlagStatus(ADC_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_ADC_STATUS_FLAG(Flag));

    if ((MDR_ADC->ADC1_STATUS & (uint32_t)Flag) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Return a combined value of the ADC status flags.
 * @param  None.
 * @return The ADC status flags combined value.
 */
uint32_t ADC_GetStatus(void)
{
    return MDR_ADC->ADC1_STATUS & ADC1_STATUS_FLAGS_MASK;
}

/**
 * @brief  Clear the ADC status flags.
 * @param  Flags: ADC flag to clear.
 *         This parameter can be any combination of the following values:
 *               @arg ADC_FLAG_OVERWRITE: The flag designates the previous measured value of the ADC has been overwritten.
 *               @arg ADC_FLAG_OUT_OF_RANGE: The flag designates the measured value of the ADC is out of the range.
 * @return None.
 */
void ADC_ClearFlags(uint32_t Flags)
{
    /* Check the parameters. */
    assert_param(IS_ADC_STATUS_FLAGS_CLR(Flags));

    MDR_ADC->ADC1_STATUS = (MDR_ADC->ADC1_STATUS | ADC1_STATUS_CLEANABLE_MASK) & ~Flags;
}

/**
 * @brief  Enable or disable the ADC interrupts.
 * @param  ADC_IT: Specify the ADC interrupts sources to be enabled or disabled.
 *         This parameter can be any combination of the @ref ADC_IT_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the ADC interrupts.
 * @return None.
 */
void ADC_ITConfig(uint32_t ADC_IT, FunctionalState NewState)
{
    uint32_t TempIE;

    /* Check the parameters. */
    assert_param(IS_ADC_CONFIG_IT(ADC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TempIE = (MDR_ADC->ADC1_STATUS | ADC1_STATUS_CLEANABLE_MASK);

    /* Form new value. */
    if (NewState != DISABLE) {
        /* Enable the ADC Interrupt requests by setting bits in the ADC1_STATUS register. */
        TempIE |= (ADC_IT << 2);
    } else {
        /* Disable the ADC Interrupt requests by clearing bits in the ADC1_STATUS register. */
        TempIE &= ~(ADC_IT << 2);
    }

    /* Configure ADC1_STATUS registers with new value. */
    MDR_ADC->ADC1_STATUS = TempIE;
}

/**
 * @brief  Set trimming of the internal reference voltage.
 * @param  Trim: Trimming value in the range [0; 31].
 * @return None.
 */
void ADC_SetTrim(uint8_t Trim)
{
    uint32_t TempTRIM;

    /* Check the parameters. */
    assert_param(IS_ADC_BG_TRIM(Trim));

    TempTRIM = MDR_ADC->ADC_TRIM;
    TempTRIM &= ~ADC_TRIM_BG_TRIM_Msk;
    TempTRIM |= ((uint32_t)Trim << ADC_TRIM_BG_TRIM_Pos);

    MDR_ADC->ADC_TRIM = TempTRIM;
}

/** @} */ /* End of the group ADC_Exported_Functions */

/** @} */ /* End of the group ADC */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_adc.c */

