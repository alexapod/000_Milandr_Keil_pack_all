/**
 *******************************************************************************
 * @file    MDR32F2xQI_adc.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    18/05/2023
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
#include "MDR32F2xQI_adc.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @defgroup ADC ADC
 * @{
 */

/** @defgroup ADC_Private_Defines ADC Private Defines
 * @{
 */

#define ADC1_STATUS_CLEANABLE (ADC1_STATUS_FLG_REG_OVERWRITE_Msk | \
                               ADC1_STATUS_FLG_REG_AWOIFEN_Msk)

#define ADC1_STATUS_FLAGS (ADC1_STATUS_FLG_REG_OVERWRITE_Msk | \
                           ADC1_STATUS_FLG_REG_AWOIFEN_Msk |   \
                           ADC1_STATUS_FLG_REG_EOCIF_Msk)

/** @} */ /* End of group ADC_Private_Defines */

/** @defgroup ADC_Exported_Functions ADC Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the ADC peripheral registers to their default reset values.
 * @param  None.
 * @retval None.
 */
void ADC_DeInit(void)
{
    MDR_ADC->ADC1_CFG     = 0;
    MDR_ADC->ADC2_CFG     = 0;
    MDR_ADC->ADC1_H_LEVEL = 0;
    MDR_ADC->ADC1_L_LEVEL = 0;
    MDR_ADC->ADC1_RESULT;
    MDR_ADC->ADC1_STATUS = 0;
    MDR_ADC->ADC1_CHSEL  = 0;
    MDR_ADC->ADC1_TRIM   = 0;
}

/**
  * @brief  Initializes the ADC peripheral according to
  *         the specified parameters in the ADC_InitStruct.
  * @param  ADC_InitStruct: pointer to a @ref ADC_InitTypeDef structure that
            contains the configuration information for the specified ADC peripheral.
  * @retval None.
  */
void ADC_Init(const ADC_InitTypeDef* ADC_InitStruct)
{
    uint32_t TempCFG;
    uint32_t TempMask;
    uint32_t TempTRIM;

    /* Check the parameters */
    assert_param(IS_ADC_TEMP_SENSOR_CONFIG(ADC_InitStruct->ADC_TempSensor));
    assert_param(IS_ADC_TEMP_SENSOR_AMP_CONFIG(ADC_InitStruct->ADC_TempSensorAmplifier));
    assert_param(IS_ADC_TEMP_SENSOR_CONVERSION_CONFIG(ADC_InitStruct->ADC_TempSensorConversion));
    assert_param(IS_ADC_VREF_CONVERSION_CONFIG(ADC_InitStruct->ADC_IntVRefConversion));
    assert_param(IS_ADC_VREF_TRIMMING_VALUE(ADC_InitStruct->ADC_IntVRefTrimming));
    assert_param(IS_ADC_INT_VREF_AMPLIFIER(ADC_InitStruct->ADC_IntVRefAmplifier));

    TempCFG = (uint32_t)ADC_InitStruct->ADC_TempSensor |
              (uint32_t)ADC_InitStruct->ADC_TempSensorAmplifier |
              (uint32_t)ADC_InitStruct->ADC_TempSensorConversion |
              (uint32_t)ADC_InitStruct->ADC_IntVRefConversion;

    TempMask = (ADC1_CFG_DELAY_ADC_Msk |
                ADC1_CFG_TS_EN_Msk |
                ADC1_CFG_TS_BUF_EN_Msk |
                ADC1_CFG_SEL_TS_Msk |
                ADC1_CFG_SEL_VREF_Msk);

    TempTRIM = (ADC_InitStruct->ADC_IntVRefTrimming << ADC1_TRIM_TS_TRIM_Pos) |
               (uint32_t)ADC_InitStruct->ADC_IntVRefAmplifier;

    MDR_ADC->ADC1_TRIM = TempTRIM;
    MDR_ADC->ADC1_CFG  = (MDR_ADC->ADC1_CFG & ~TempMask) | TempCFG;
}

/**
 * @brief  Fills each ADC_InitStruct member with its default value.
 * @param  ADC_InitStruct: pointer to a @ref ADC_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
 */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
    ADC_InitStruct->ADC_TempSensor           = ADC_TEMP_SENSOR_DISABLE;
    ADC_InitStruct->ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_DISABLE;
    ADC_InitStruct->ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_DISABLE;
    ADC_InitStruct->ADC_IntVRefConversion    = ADC_VREF_CONVERSION_DISABLE;
    ADC_InitStruct->ADC_IntVRefTrimming      = 0;
    ADC_InitStruct->ADC_IntVRefAmplifier     = ADC_INT_VREF_AMPLIFIER_DISABLE;
}

/**
 * @brief  Sets the Internal Voltage Reference trimming.
 * @param  Trim: trimming value in range 0..31.
 * @retval None.
 */
void ADC_SetTrim(uint32_t Trim)
{
    uint32_t TempTRIM;

    /* Check the parameters */
    assert_param(IS_ADC_VREF_TRIMMING_VALUE(Trim));

    TempTRIM = MDR_ADC->ADC1_TRIM;
    TempTRIM &= ~ADC1_TRIM_TS_TRIM_Msk;
    TempTRIM |= (Trim << ADC1_TRIM_TS_TRIM_Pos);

    MDR_ADC->ADC1_TRIM = TempTRIM;
}

/**
 * @brief  Initializes the ADC1 peripheral according to
 *         the specified parameters in the ADCx_InitStruct.
 * @param  ADCx_InitStruct: pointer to a @ref ADCx_InitTypeDef structure
 *         that contains the configuration information for the ADC1 peripheral.
 * @retval None.
 */
void ADC1_Init(const ADCx_InitTypeDef* ADCx_InitStruct)
{
    uint32_t TempCFG1;
    uint32_t TempCFG2;

    /* Check the parameters */
    assert_param(IS_ADC_CLOCK_SOURCE_CONFIG(ADCx_InitStruct->ADC_ClockSource));
    assert_param(IS_ADC_SAMPLING_MODE_CONFIG(ADCx_InitStruct->ADC_SamplingMode));
    assert_param(IS_ADC_CH_SWITCHING_CONFIG(ADCx_InitStruct->ADC_ChannelSwitching));
    assert_param(IS_ADC1_CH_NUM(ADCx_InitStruct->ADC_ChannelNumber));
    assert_param(IS_ADC1_CH_MASK(ADCx_InitStruct->ADC_Channels));
    assert_param(IS_ADC_LEVEL_CONTROL_CONFIG(ADCx_InitStruct->ADC_LevelControl));
    assert_param(IS_ADC_VALUE(ADCx_InitStruct->ADC_LowLevel));
    assert_param(IS_ADC_VALUE(ADCx_InitStruct->ADC_HighLevel));
    assert_param(IS_ADC_VREF_SOURCE_CONFIG(ADCx_InitStruct->ADC_VRefSource));
    assert_param(IS_ADC_INT_VREF_SOURCE_CONFIG(ADCx_InitStruct->ADC_IntVRefSource));
    assert_param(IS_ADC_CLK_DIV_VALUE(ADCx_InitStruct->ADC_Prescaler));
    assert_param(IS_ADC_DELAY_GO_VALUE(ADCx_InitStruct->ADC_DelayGo));

    TempCFG1 = MDR_ADC->ADC1_CFG;

    TempCFG1 &= ~(ADC1_CFG_REG_CLKS_Msk |
                  ADC1_CFG_REG_SAMPLE_Msk |
                  ADC1_CFG_REG_CHCH_Msk |
                  ADC1_CFG_REG_CHS_Msk |
                  ADC1_CFG_REG_RNGC_Msk |
                  ADC1_CFG_M_REF_Msk |
                  ADC1_CFG_REG_DIVCLK_Msk |
                  ADC1_CFG_DELAY_GO_Msk);

    TempCFG1 |= (uint32_t)ADCx_InitStruct->ADC_ClockSource |
                (uint32_t)ADCx_InitStruct->ADC_SamplingMode |
                (uint32_t)ADCx_InitStruct->ADC_ChannelSwitching |
                (uint32_t)ADCx_InitStruct->ADC_ChannelNumber |
                (uint32_t)ADCx_InitStruct->ADC_LevelControl |
                (uint32_t)ADCx_InitStruct->ADC_VRefSource |
                (uint32_t)ADCx_InitStruct->ADC_Prescaler |
                (((uint32_t)ADCx_InitStruct->ADC_DelayGo) << ADC1_CFG_DELAY_GO_Pos);

    TempCFG2 = MDR_ADC->ADC2_CFG;
    TempCFG2 &= ~ADC2_CFG_ADC1_OP_Msk;
    TempCFG2 |= ((uint32_t)ADCx_InitStruct->ADC_IntVRefSource << ADC2_CFG_ADC1_OP_Pos);

    MDR_ADC->ADC1_L_LEVEL = (uint32_t)ADCx_InitStruct->ADC_LowLevel;
    MDR_ADC->ADC1_H_LEVEL = (uint32_t)ADCx_InitStruct->ADC_HighLevel;
    MDR_ADC->ADC1_CHSEL   = ADCx_InitStruct->ADC_Channels;

    MDR_ADC->ADC1_CFG = TempCFG1;
    MDR_ADC->ADC2_CFG = TempCFG2;
}

/**
 * @brief  Fills each ADCx_InitStruct member with its default value.
 * @param  ADCx_InitStruct: pointer to a @ref ADCx_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
 */
void ADCx_StructInit(ADCx_InitTypeDef* ADCx_InitStruct)
{
    ADCx_InitStruct->ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;
    ADCx_InitStruct->ADC_SamplingMode     = ADC_SAMPLING_MODE_SINGLE_CONV;
    ADCx_InitStruct->ADC_ChannelSwitching = ADC_CH_SWITCHING_DISABLE;
    ADCx_InitStruct->ADC_ChannelNumber    = ADC_CH_ADC0;
    ADCx_InitStruct->ADC_Channels         = 0;
    ADCx_InitStruct->ADC_LevelControl     = ADC_LEVEL_CONTROL_DISABLE;
    ADCx_InitStruct->ADC_LowLevel         = 0;
    ADCx_InitStruct->ADC_HighLevel        = 0;
    ADCx_InitStruct->ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;
    ADCx_InitStruct->ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;
    ADCx_InitStruct->ADC_Prescaler        = ADC_PRESCALER_DIV_1;
    ADCx_InitStruct->ADC_DelayGo          = 0;
}

/**
 * @brief  Enables or disables the ADC1 peripheral.
 * @param  NewState - @ref FunctionalState - new state of the ADC1 peripheral.
 * @retval None.
 */
void ADC1_Cmd(FunctionalState NewState)
{
    uint32_t TempCFG;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TempCFG = MDR_ADC->ADC1_CFG;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable ADC1 by setting the Cfg_REG_ADON bit in the ADC1_CFG register */
        TempCFG |= ADC1_CFG_REG_ADON;
    } else {
        /* Disable ADC1 by resetting the Cfg_REG_ADON bit in the ADC1_CFG register */
        TempCFG &= ~ADC1_CFG_REG_ADON;
    }

    /* Configure ADC1_CFG register with new value */
    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Selects the ADC1 Channel number for Single Channel Mode conversion.
 * @param  Channel - @ref ADCx_ChannelNumber_TypeDef - specifies the ADC Channel number.
 * @retval None.
 */
void ADC1_SetChannel(ADCx_ChannelNumber_TypeDef Channel)
{
    uint32_t TempCFG;

    /* Check the parameters */
    assert_param(IS_ADC1_CH_NUM(Channel));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~ADC1_CFG_REG_CHS_Msk;
    TempCFG |= (uint32_t)Channel;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Selects the ADC1 Channels for conversion with Channels switching.
 * @param  ChannelMask: specifies the ADC Channels Mask.
 *         This parameter can be any combination of @ref ADCx_ChannelNumber_TypeDef values.
 * @retval None.
 */
void ADC1_SetChannels(uint32_t ChannelMask)
{
    /* Check the parameters */
    assert_param(IS_ADC1_CH_MASK(ChannelMask));

    MDR_ADC->ADC1_CHSEL = ChannelMask;
}

/**
 * @brief  Sets the ADC1 operation mode.
 * @param  SamplingMode - @ref ADCx_SamplingMode_TypeDef - specifies the ADC1 sampling.
 * @param  SwitchingMode - @ref ADCx_ChannelSwitching_TypeDef - specifies the ADC1 channel switching.
 * @retval None.
 */
void ADC1_OperationModeConfig(ADCx_SamplingMode_TypeDef SamplingMode, ADCx_ChannelSwitching_TypeDef SwitchingMode)
{
    uint32_t TempCFG;

    /* Check the parameters */
    assert_param(IS_ADC_SAMPLING_MODE_CONFIG(SamplingMode));
    assert_param(IS_ADC_CH_SWITCHING_CONFIG(SwitchingMode));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~(ADC1_CFG_REG_SAMPLE | ADC1_CFG_REG_CHCH);
    TempCFG |= (uint32_t)SamplingMode | (uint32_t)SwitchingMode;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Sets the ADC1 sampling mode.
 * @param  SamplingMode - @ref ADCx_SamplingMode_TypeDef - specifies the ADC1 sampling.
 * @retval None.
 */
void ADC1_SamplingModeConfig(ADCx_SamplingMode_TypeDef SamplingMode)
{
    uint32_t TempCFG;

    /* Check the parameters */
    assert_param(IS_ADC_SAMPLING_MODE_CONFIG(SamplingMode));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~ADC1_CFG_REG_SAMPLE;
    TempCFG |= (uint32_t)SamplingMode;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Sets the ADC1 channel switching mode.
 * @param  SwitchingMode - @ref ADCx_ChannelSwitching_TypeDef - specifies the ADC1 channel switching.
 * @retval None.
 */
void ADC1_ChannelSwithingConfig(ADCx_ChannelSwitching_TypeDef SwitchingMode)
{
    uint32_t TempCFG;

    /* Check the parameters */
    assert_param(IS_ADC_CH_SWITCHING_CONFIG(SwitchingMode));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~ADC1_CFG_REG_CHCH;
    TempCFG |= (uint32_t)SwitchingMode;

    MDR_ADC->ADC1_CFG = TempCFG;
}

/**
 * @brief  Configures the ADC1 threshould levels.
 * @param  LowLevel: specifies the ADC1 low level value.
 *         This parameter can be a number between 0x0000 and 0x0FFF.
 * @param  HighLevel: specifies the ADC1 high level value.
 *         This parameter can be a number between 0x0000 and 0x0FFF.
 * @param  NewState - @ref ADCx_LevelControl_TypeDef - enables or disables levels control.
 * @retval None.
 */
void ADC1_LevelsConfig(uint32_t LowLevel, uint32_t HighLevel, ADCx_LevelControl_TypeDef NewState)
{
    uint32_t TempCFG;

    /* Check the parameters */
    assert_param(IS_ADC_LEVEL_CONTROL_CONFIG(NewState));
    assert_param(IS_ADC_VALUE(LowLevel));
    assert_param(IS_ADC_VALUE(HighLevel));

    TempCFG = MDR_ADC->ADC1_CFG;
    TempCFG &= ~ADC1_CFG_REG_RNGC;
    TempCFG |= (uint32_t)NewState;

    MDR_ADC->ADC1_CFG = TempCFG;

    MDR_ADC->ADC1_L_LEVEL = LowLevel;
    MDR_ADC->ADC1_H_LEVEL = HighLevel;
}

/**
 * @brief  Sets the ADC1 low level.
 * @param  LowLevel: specifies the ADC1 low level value.
 *         This parameter can be a number between 0x0000 and 0x0FFF.
 * @retval None.
 */
void ADC1_SetLowLevel(uint32_t LowLevel)
{
    /* Check the parameters */
    assert_param(IS_ADC_VALUE(LowLevel));

    MDR_ADC->ADC1_L_LEVEL = LowLevel;
}

/**
 * @brief  Sets the ADC1 high level.
 * @param  HighLevel: specifies the ADC1 high level value.
 *         This parameter can be a number between 0x0000 and 0x0FFF.
 * @retval None.
 */
void ADC1_SetHighLevel(uint32_t HighLevel)
{
    /* Check the parameters */
    assert_param(IS_ADC_VALUE(HighLevel));

    MDR_ADC->ADC1_H_LEVEL = HighLevel;
}

/**
 * @brief  Starts the ADC1 conversion.
 * @param  None.
 * @retval None.
 */
void ADC1_Start(void)
{
    MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_GO;
}

/**
 * @brief  Returns the ADC1 result.
 * @param  None.
 * @retval ADC1 Result Register value.
 */
uint32_t ADC1_GetResult(void)
{
    return MDR_ADC->ADC1_RESULT;
}

/**
 * @brief  Checks whether the specified ADC1 Status flag is set or not.
 * @param  Flag: specifies the flag to check.
 *         This parameter can be one of @ref ADC1_Flags_TypeDef values.
 * @retval @ref FlagStatus - Current Status flag state (SET or RESET).
 */
FlagStatus ADC1_GetFlagStatus(ADC1_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_ADC_STATUS_FLAG(Flag));

    if ((MDR_ADC->ADC1_STATUS & Flag) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Returns the ADC1 Status Flags combined value.
 * @param  None.
 * @retval The ADC1 Status Flags combined value.
 */
uint32_t ADC1_GetStatus(void)
{
    return MDR_ADC->ADC1_STATUS & ADC1_STATUS_FLAGS;
}

/**
 * @brief  Clears the ADC1 Status flags.
 * @param  Flags: ADC flag to clear.
 *         This parameter can be any combination of @ref ADC1_Flags_TypeDef values.
 * @retval None.
 */
void ADC1_ClearFlags(uint32_t Flags)
{
    /* Check the parameters */
    assert_param(IS_ADC_STATUS_FLAGS_CLR(Flags));

    MDR_ADC->ADC1_STATUS = (MDR_ADC->ADC1_STATUS | ADC1_STATUS_CLEANABLE) & ~Flags;
}

/**
 * @brief  Enables or disables the ADC1 interrupts.
 * @param  ADC_IT: specifies the ADC1 interrupts sources to be enabled or disabled.
 *         This parameter can be any combination of @ref ADC1_IT_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the ADC1 interrupts.
 * @retval None.
 */
void ADC1_ITConfig(uint32_t ADC_IT, FunctionalState NewState)
{
    uint32_t TempIE;

    /* Check the parameters */
    assert_param(IS_ADC_CONFIG_IT(ADC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TempIE = (MDR_ADC->ADC1_STATUS | ADC1_STATUS_CLEANABLE);

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the ADC Interrupt requests by setting bits in the ADC1_STATUS register */
        TempIE |= (ADC_IT << 2);
    } else {
        /* Disable the ADC Interrupt requests by clearing bits in the ADC1_STATUS register */
        TempIE &= ~(ADC_IT << 2);
    }

    /* Configure ADC1_STATUS registers with new value */
    MDR_ADC->ADC1_STATUS = TempIE;
}

/**
 * @brief  Checks whether the ADC1 interrupt has occurred or not.
 * @param  ADC_IT - @ref ADC1_IT_TypeDef - specifies the ADC interrupt source to check.
 * @retval @ref ITStatus - The state of the ADC_IT (SET or RESET).
 */
ITStatus ADC1_GetITFlagStatus(ADC1_IT_TypeDef ADC_IT)
{
    ITStatus Status;
    uint32_t TempIT, FlagState, FlagEnable;

    /* Check the parameters */
    assert_param(IS_ADC_CONFIG_IT(ADC_IT));

    TempIT = MDR_ADC->ADC1_STATUS;

    FlagState = TempIT & (uint32_t)ADC_IT;

    FlagEnable = TempIT & (ADC1_STATUS_AWOIF_IE_Msk | ADC1_STATUS_ECOIF_IE_Msk);
    FlagEnable >>= (ADC1_STATUS_AWOIF_IE_Pos - ADC1_STATUS_FLG_REG_AWOIFEN_Pos);

    if ((FlagState & FlagEnable) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Checks whether the ADC1 interrupts has occurred or not.
 * @param  None.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref ADC1_IT_TypeDef.
 */
uint32_t ADC1_GetITStatus(void)
{
    uint32_t TempIT, FlagsState, FlagsEnable;

    TempIT = MDR_ADC->ADC1_STATUS;

    FlagsState = TempIT & (ADC1_STATUS_FLG_REG_AWOIFEN_Msk | ADC1_STATUS_FLG_REG_EOCIF_Msk);

    FlagsEnable = TempIT & (ADC1_STATUS_AWOIF_IE_Msk | ADC1_STATUS_ECOIF_IE_Msk);
    FlagsEnable >>= (ADC1_STATUS_AWOIF_IE_Pos - ADC1_STATUS_FLG_REG_AWOIFEN_Pos);

    return (FlagsState & FlagsEnable);
}

/** @} */ /* End of group ADC_Exported_Functions */

/** @} */ /* End of group ADC */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_adc.c */

