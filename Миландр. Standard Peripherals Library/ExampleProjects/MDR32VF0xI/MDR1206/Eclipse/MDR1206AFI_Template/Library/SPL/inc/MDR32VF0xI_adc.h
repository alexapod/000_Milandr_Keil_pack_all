/**
 *******************************************************************************
 * @file    MDR32VF0xI_adc.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    14/02/2024
 * @brief   This file contains all the functions prototypes for the ADC
 *          firmware library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MDR32VF0xI_ADC_H
#define MDR32VF0xI_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup ADC ADC
 * @{
 */

/** @defgroup ADC_Exported_Types ADC Exported Types
 * @{
 */

/**
 * @brief ADC voltage reference selection, specified in the ADCUI.
 */
typedef enum {
    ADC_VREF_SOURCE_EXTERNAL = (((uint32_t)0x0) << ADCUI_CTRL1_VREF_SEL_Pos), /*!< External voltage selected as a reference. */
    ADC_VREF_SOURCE_INTERNAL = (((uint32_t)0x1) << ADCUI_CTRL1_VREF_SEL_Pos)  /*!< Internal voltage 2.4V selected as a reference.*/
} ADC_VRefSource_TypeDef;

#define IS_ADC_VREF_SOURCE_CONFIG(SRC) (((SRC) == ADC_VREF_SOURCE_EXTERNAL) || \
                                        ((SRC) == ADC_VREF_SOURCE_INTERNAL))

/**
 * @brief ADC scale configuration.
 */
typedef enum {
    ADC_SCALE_MAX_UCCA = (((uint32_t)0x0) << ADC1_CFG_M_REF_Pos), /*!< ADC scale is from 0V to UCCA. */
    ADC_SCALE_MAX_VREF = (((uint32_t)0x1) << ADC1_CFG_M_REF_Pos)  /*!< ADC scale is from 0V to VREF. */
} ADC_Scale_TypeDef;

#define IS_ADC_SCALE_MAX(SCALE) (((SCALE) == ADC_SCALE_MAX_UCCA) || \
                                 ((SCALE) == ADC_SCALE_MAX_VREF))

/**
 * @brief ADC clock source configuration.
 */
typedef enum {
    ADC_CLOCK_SOURCE_PCLKd   = (((uint32_t)0x0) << ADC1_CFG_REG_CLKS_Pos), /*!< Select CPU_CLK as the ADC clock. */
    ADC_CLOCK_SOURCE_ADC_CLK = (((uint32_t)0x1) << ADC1_CFG_REG_CLKS_Pos)  /*!< Select ADC_CLK as the ADC clock. */
} ADC_ClockSource_TypeDef;

#define IS_ADC_CLOCK_SOURCE_CONFIG(CONFIG) (((CONFIG) == ADC_CLOCK_SOURCE_PCLKd) || \
                                            ((CONFIG) == ADC_CLOCK_SOURCE_ADC_CLK))

/**
 * @brief ADC PCLKd divider constants.
 */
typedef enum {
    ADC_PRESCALER_DIV_1    = (((uint32_t)0x0) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK. */
    ADC_PRESCALER_DIV_2    = (((uint32_t)0x1) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/2. */
    ADC_PRESCALER_DIV_4    = (((uint32_t)0x2) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/4. */
    ADC_PRESCALER_DIV_8    = (((uint32_t)0x3) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/8. */
    ADC_PRESCALER_DIV_16   = (((uint32_t)0x4) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/16. */
    ADC_PRESCALER_DIV_32   = (((uint32_t)0x5) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/32. */
    ADC_PRESCALER_DIV_64   = (((uint32_t)0x6) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/64. */
    ADC_PRESCALER_DIV_128  = (((uint32_t)0x7) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/128. */
    ADC_PRESCALER_DIV_256  = (((uint32_t)0x8) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/256. */
    ADC_PRESCALER_DIV_512  = (((uint32_t)0x9) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/512. */
    ADC_PRESCALER_DIV_1024 = (((uint32_t)0xA) << ADC1_CFG_REG_DIVCLK_Pos), /*!< PCLKd = PCLK/1024. */
    ADC_PRESCALER_DIV_2048 = (((uint32_t)0xB) << ADC1_CFG_REG_DIVCLK_Pos)  /*!< PCLKd = PCLK/2048. */
} ADC_Prescaler_TypeDef;

#define IS_ADC_CLK_DIV_VALUE(DIV) (((DIV) == ADC_PRESCALER_DIV_1) ||    \
                                   ((DIV) == ADC_PRESCALER_DIV_2) ||    \
                                   ((DIV) == ADC_PRESCALER_DIV_4) ||    \
                                   ((DIV) == ADC_PRESCALER_DIV_8) ||    \
                                   ((DIV) == ADC_PRESCALER_DIV_16) ||   \
                                   ((DIV) == ADC_PRESCALER_DIV_32) ||   \
                                   ((DIV) == ADC_PRESCALER_DIV_64) ||   \
                                   ((DIV) == ADC_PRESCALER_DIV_128) ||  \
                                   ((DIV) == ADC_PRESCALER_DIV_256) ||  \
                                   ((DIV) == ADC_PRESCALER_DIV_512) ||  \
                                   ((DIV) == ADC_PRESCALER_DIV_1024) || \
                                   ((DIV) == ADC_PRESCALER_DIV_2048))

/**
 * @brief ADC sampling mode configuration.
 */
typedef enum {
    ADC_SAMPLING_MODE_SINGLE_CONV = (((uint32_t)0x0) << ADC1_CFG_REG_SAMPLE_Pos), /*!< Select ADC single mode operation. */
    ADC_SAMPLING_MODE_CYCLIC_CONV = (((uint32_t)0x1) << ADC1_CFG_REG_SAMPLE_Pos)  /*!< Select ADC cyclic mode operation. */
} ADC_SamplingMode_TypeDef;

#define IS_ADC_SAMPLING_MODE_CONFIG(CONFIG) (((CONFIG) == ADC_SAMPLING_MODE_SINGLE_CONV) || \
                                             ((CONFIG) == ADC_SAMPLING_MODE_CYCLIC_CONV))

/**
 * @brief ADC channel switching configuration.
 */
typedef enum {
    ADC_CH_SWITCHING_DISABLE = (((uint32_t)0x0) << ADC1_CFG_REG_CHCH_Pos), /*!< Disable channel switching. */
    ADC_CH_SWITCHING_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_REG_CHCH_Pos)  /*!< Enable channel switching. */
} ADC_ChannelSwitching_TypeDef;

#define IS_ADC_CH_SWITCHING_CONFIG(CONFIG) (((CONFIG) == ADC_CH_SWITCHING_DISABLE) || \
                                            ((CONFIG) == ADC_CH_SWITCHING_ENABLE))

/**
 * @brief ADC channel number.
 */
typedef enum {
    ADC_CH_ADC0_TEMP_SENSOR = (((uint32_t)0x7) << ADC1_CFG_REG_CHS_Pos), /*!< Specify the ADC channel 0 (temperature sensor). */
    ADC_CH_ADC1_SAR_AIN1    = (((uint32_t)0x6) << ADC1_CFG_REG_CHS_Pos), /*!< Specify the ADC channel 1 (SAR_AIN1). */
    ADC_CH_ADC2_SAR_AIN2    = (((uint32_t)0x5) << ADC1_CFG_REG_CHS_Pos), /*!< Specify the ADC channel 2 (SAR_AIN2). */
    ADC_CH_ADC3_SAR_AIN3    = (((uint32_t)0x4) << ADC1_CFG_REG_CHS_Pos), /*!< Specify the ADC channel 3 (SAR_AIN3). */
    ADC_CH_ADC5_VDD_BG      = (((uint32_t)0x2) << ADC1_CFG_REG_CHS_Pos), /*!< Specify the ADC channel 5 (VDD_BG). */
    ADC_CH_ADC6_VREF        = (((uint32_t)0x1) << ADC1_CFG_REG_CHS_Pos)  /*!< Specify the ADC channel 6 (VREF). */
} ADC_ChannelNumber_TypeDef;

#define IS_ADC_CH_NUM(NUM) (((NUM) == ADC_CH_ADC0_TEMP_SENSOR) || \
                            ((NUM) == ADC_CH_ADC1_SAR_AIN1) ||    \
                            ((NUM) == ADC_CH_ADC2_SAR_AIN2) ||    \
                            ((NUM) == ADC_CH_ADC3_SAR_AIN3) ||    \
                            ((NUM) == ADC_CH_ADC5_VDD_BG) ||      \
                            ((NUM) == ADC_CH_ADC6_VREF))

/**
 * @brief ADC level control configuration.
 */
typedef enum {
    ADC_LEVEL_CONTROL_DISABLE = (((uint32_t)0x0) << ADC1_CFG_REG_RNGC_Pos), /*!< Disable level control. */
    ADC_LEVEL_CONTROL_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_REG_RNGC_Pos)  /*!< Enable level control. */
} ADC_LevelControl_TypeDef;

#define IS_ADC_LEVEL_CONTROL_CONFIG(CONFIG) (((CONFIG) == ADC_LEVEL_CONTROL_DISABLE) || \
                                             ((CONFIG) == ADC_LEVEL_CONTROL_ENABLE))

/**
 * @brief ADC flags.
 */
typedef enum {
    ADC_FLAG_OVERWRITE         = ADC1_STATUS_FLG_REG_OVERWRITE_Msk, /*!< Previously measured ADC value was overwritten. */
    ADC_FLAG_OUT_OF_RANGE      = ADC1_STATUS_FLG_REG_AWOIFEN_Msk,   /*!< The measured ADC value is out of the range. */
    ADC_FLAG_END_OF_CONVERSION = ADC1_STATUS_FLG_REG_EOCIF_Msk      /*!< The ADC conversion finished. */
} ADC_Flags_TypeDef;

#define IS_ADC_STATUS_FLAG(FLAG) (((FLAG) == ADC_FLAG_OVERWRITE) ||    \
                                  ((FLAG) == ADC_FLAG_OUT_OF_RANGE) || \
                                  ((FLAG) == ADC_FLAG_END_OF_CONVERSION))

#define IS_ADC_STATUS_FLAG_CLR(FLAG) (((FLAG) == ADC_FLAG_OVERWRITE) || \
                                      ((FLAG) == ADC_FLAG_OUT_OF_RANGE))

#define IS_ADC_STATUS_FLAGS_CLR(FLAG) (((FLAG) & ~((uint32_t)(ADC_FLAG_OVERWRITE | \
                                                              ADC_FLAG_OUT_OF_RANGE))) == 0)

/**
 * @brief ADC interrupt definition.
 */
typedef enum {
    ADC_IT_OUT_OF_RANGE      = ADC1_STATUS_FLG_REG_AWOIFEN_Msk,
    ADC_IT_END_OF_CONVERSION = ADC1_STATUS_FLG_REG_EOCIF_Msk
} ADC_IT_TypeDef;

#define IS_ADC_CONFIG_IT(IT) (((IT) & ~((uint32_t)(ADC_IT_OUT_OF_RANGE | \
                                                   ADC_IT_END_OF_CONVERSION))) == 0)

/**
 * @brief ADC init structure definition.
 */
typedef struct {
    ADC_ClockSource_TypeDef ADC_ClockSource;           /*!< Specify the ADC clock source.
                                                            This parameter can be a value of @ref ADC_ClockSource_TypeDef */
    ADC_Prescaler_TypeDef ADC_Prescaler;               /*!< Specify the ADC Prescaler configuration.
                                                            This parameter can be a value of @ref ADC_Prescaler_TypeDef */
    ADC_VRefSource_TypeDef ADC_VRefSource;             /*!< Specify the ADC voltage reference source (internal or external).
                                                            This parameter can be a value of @ref ADC_VRefSource_TypeDef */
    ADC_Scale_TypeDef ADC_Scale;                       /*!< Specify the ADC scale (0V to UCCA or 0V to VREF).
                                                            This parameter can be a value of @ref ADC_Scale_TypeDef */
    ADC_ChannelSwitching_TypeDef ADC_ChannelSwitching; /*!< Enable or disable the ADC channel switching.
                                                            When ADC_CH_SWITCHING_ENABLE value is used, the start of the ADC conversion is controlled by hardware.
                                                            This parameter can be a value of @ref ADC_ChannelSwitching_TypeDef */
    ADC_ChannelNumber_TypeDef ADC_ChannelNumber;       /*!< Specify the ADC channel number (if ADC_ChannelSwitching == ADC_CH_SWITCHING_DISABLE).
                                                            This parameter can be a value of @ref ADC_ChannelNumber_TypeDef */
    uint32_t ADC_Channels;                             /*!< Specify the ADC channels mask (if ADC_ChannelSwitching == ADC_CH_SWITCHING_ENABLE).
                                                            This parameter can be a value of @ref ADC_Channels */
    ADC_SamplingMode_TypeDef ADC_SamplingMode;         /*!< Specify the ADC sampling mode.
                                                            This parameter can be a value of @ref ADC_SamplingMode_TypeDef */
    uint32_t ADC_DelayGo;                              /*!< Specify the ADC start conversion delay at sequential conversion mode.
                                                            Used by hardware only if (ADC_SamplingMode == ADC_SAMPLING_MODE_CYCLIC_CONV).
                                                            This parameter can be a number from 0 to 7. */
    ADC_LevelControl_TypeDef ADC_LevelControl;         /*!< Enable or disable the ADC level control.
                                                            This parameter can be a value of @ref ADC_LevelControl_TypeDef */
    uint16_t ADC_LowLevel;                             /*!< Specify the ADC value low level (if ADC_LevelControl == ADC_LEVEL_CONTROL_ENABLE).
                                                            This parameter can be a number from 0x0000 to 0x03FF. */
    uint16_t ADC_HighLevel;                            /*!< Specify the ADC value high level (if ADC_LevelControl == ADC_LEVEL_CONTROL_ENABLE).
                                                            This parameter can be a number from 0x0000 to 0x03FF. */
} ADC_InitTypeDef;

/**
 * @brief ADC result structure definition.
 */
typedef struct {
    ADC_ChannelNumber_TypeDef ADC_ResultChannel; /*!< ADC conversion result channel.
                                                      This element is a value of the @ref DMA_DataStructSelection_TypeDef. */
    uint16_t ADC_Result : 10;                    /*!< ADC conversion result.
                                                      This element is a number from 0 to 1023. */
} ADC_Result_TypeDef;

/** @} */ /* End of the group ADC_Exported_Types */

/** @defgroup ADC_Exported_Defines ADC Exported Defines
 * @{
 */

/** @defgroup ADC_Int_BG_Trimming ADC Internal Voltage Bandgap Trimming
 * @{
 */

#define IS_ADC_BG_TRIM(TRIM) (((TRIM) & ~((uint32_t)0x01F)) == 0)

/** @} */ /* End of the group ADC_Int_BG_Trimming */

/** @defgroup ADC_Channels ADC Channels
 * @{
 */

#define ADC_CH_ADC0_TEMP_SENSOR_MASK (((uint32_t)0x1) << 7) /*!< Select ADC channel 0. */
#define ADC_CH_ADC1_SAR_AIN1_MASK    (((uint32_t)0x1) << 6) /*!< Select ADC channel 1. */
#define ADC_CH_ADC2_SAR_AIN2_MASK    (((uint32_t)0x1) << 5) /*!< Select ADC channel 2. */
#define ADC_CH_ADC3_SAR_AIN3_MASK    (((uint32_t)0x1) << 4) /*!< Select ADC channel 3. */
#define ADC_CH_ADC5_VDD_BG_MASK      (((uint32_t)0x1) << 2) /*!< Select ADC channel 5. */
#define ADC_CH_ADC6_VREF_MASK        (((uint32_t)0x1) << 1) /*!< Select ADC channel 6. */

#define IS_ADC_CH_MASK(MASK)         (((MASK) & ~((uint32_t)(ADC_CH_ADC0_TEMP_SENSOR_MASK | \
                                                     ADC_CH_ADC1_SAR_AIN1_MASK |            \
                                                     ADC_CH_ADC2_SAR_AIN2_MASK |            \
                                                     ADC_CH_ADC3_SAR_AIN3_MASK |            \
                                                     ADC_CH_ADC5_VDD_BG_MASK |              \
                                                     ADC_CH_ADC6_VREF_MASK))) == 0)

/** @} */ /* End of the group ADC_Channels */

/** @defgroup ADC_Delay_Go ADC Start Conversion Delay
 * @{
 */

#define IS_ADC_DELAY_GO_VALUE(VALUE) (((VALUE) & ~((uint32_t)0x7)) == 0)

/** @} */ /* End of the group ADC_Delay_Go */

/** @defgroup ADC_Value ADC value
 * @{
 */

#define IS_ADC_VALUE(VALUE) (((VALUE) & ~ADC1_RESULT_RESULT_Msk) == 0)

/** @} */ /* End of the group ADC_Value */

/** @defgroup ADC_Temperature ADC result to temperature macro definition
 * @{
 */

#define ADC_RESULT_TO_TEMPERATURE(FULLSCALE_ADC_VOLTAGE, RESULT) (25 - (((float)((FULLSCALE_ADC_VOLTAGE) * (int)(RESULT)) / 1024) - (float)1.403) / (float)0.0037)

/** @} */ /* End of the group ADC_Temperature */

/** @} */ /* End of the group ADC_Exported_Defines */

/** @defgroup ADC_Exported_Functions ADC Exported Functions
 * @{
 */

void ADC_DeInit(void);

void ADC_Init(const ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);

void            ADC_Cmd(FunctionalState NewState);
FunctionalState ADC_GetCmdState(void);

#if defined(USE_MDR32F02)
void            ADC_NoiseRNGCmd(FunctionalState NewState);
FunctionalState ADC_GetNoiseRNGCmdState(void);
#endif

void ADC_SetChannel(ADC_ChannelNumber_TypeDef Channel);
void ADC_SetChannels(uint32_t ChannelMask);

void ADC_OperationModeConfig(ADC_SamplingMode_TypeDef SamplingMode, ADC_ChannelSwitching_TypeDef SwitchingMode);
void ADC_SamplingModeConfig(ADC_SamplingMode_TypeDef SamplingMode);
void ADC_ChannelSwitchingConfig(ADC_ChannelSwitching_TypeDef SwitchingMode);

void ADC_LevelsConfig(uint32_t LowLevel, uint32_t HighLevel, ADC_LevelControl_TypeDef NewState);
void ADC_SetLowLevel(uint32_t LowLevel);
void ADC_SetHighLevel(uint32_t HighLevel);

void ADC_Start(void);

uint32_t ADC_GetResult(void);
void     ADC_GetResultStruct(ADC_Result_TypeDef* ADC_Result);

FlagStatus ADC_GetFlagStatus(ADC_Flags_TypeDef Flag);
uint32_t   ADC_GetStatus(void);
void       ADC_ClearFlags(uint32_t Flags);

void ADC_ITConfig(uint32_t ADC_IT, FunctionalState NewState);

void ADC_SetTrim(uint8_t Trim);

/** @} */ /* End of the group ADC_Exported_Functions */

/** @} */ /* End of the group ADC */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_ADC_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_adc.h */

