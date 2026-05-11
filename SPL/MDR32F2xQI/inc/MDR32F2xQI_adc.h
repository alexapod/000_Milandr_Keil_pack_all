/**
 *******************************************************************************
 * @file    MDR32F2xQI_adc.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    18/05/2023
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
#ifndef __MDR32F2xQI_ADC_H
#define __MDR32F2xQI_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup ADC ADC
 * @{
 */

/** @defgroup ADC_Exported_Defines ADC Exported Defines
 * @{
 */

/** @defgroup ADC_Int_VRef_Trimming ADC Internal Voltage Reference Trimming
 * @{
 */

#define IS_ADC_VREF_TRIMMING_VALUE(VALUE) (((VALUE) & ~0x1FUL) == 0)

/** @} */ /* End of group ADC_Int_VRef_Trimming */

/** @defgroup ADCx_Channels ADC Channels
 * @{
 */

#define ADC_CH_ADC0_MASK        (((uint32_t)0x1) << 0)  /*!< Selects the ADC channel 0.  */
#define ADC_CH_ADC1_MASK        (((uint32_t)0x1) << 1)  /*!< Selects the ADC channel 1.  */
#define ADC_CH_ADC2_MASK        (((uint32_t)0x1) << 2)  /*!< Selects the ADC channel 2.  */
#define ADC_CH_ADC3_MASK        (((uint32_t)0x1) << 3)  /*!< Selects the ADC channel 3.  */
#define ADC_CH_ADC4_MASK        (((uint32_t)0x1) << 4)  /*!< Selects the ADC channel 4.  */
#define ADC_CH_ADC5_MASK        (((uint32_t)0x1) << 5)  /*!< Selects the ADC channel 5.  */
#define ADC_CH_ADC6_MASK        (((uint32_t)0x1) << 6)  /*!< Selects the ADC channel 6.  */
#define ADC_CH_ADC7_MASK        (((uint32_t)0x1) << 7)  /*!< Selects the ADC channel 7.  */
#define ADC_CH_INT_VREF_MASK    (((uint32_t)0x1) << 30) /*!< Selects the ADC channel 30 (Internal VRef). */
#define ADC_CH_TEMP_SENSOR_MASK (((uint32_t)0x1) << 31) /*!< Selects the ADC channel 31 (Temperature Sensor). */

#define IS_ADC_CH_MASK(MASK)    (((MASK) & ~(ADC_CH_ADC0_MASK | \
                                          ADC_CH_ADC1_MASK |    \
                                          ADC_CH_ADC2_MASK |    \
                                          ADC_CH_ADC3_MASK |    \
                                          ADC_CH_ADC4_MASK |    \
                                          ADC_CH_ADC5_MASK |    \
                                          ADC_CH_ADC6_MASK |    \
                                          ADC_CH_ADC7_MASK)) == 0)

#define IS_ADC1_CH_MASK(MASK) (((MASK) & ~(ADC_CH_ADC0_MASK |     \
                                           ADC_CH_ADC1_MASK |     \
                                           ADC_CH_ADC2_MASK |     \
                                           ADC_CH_ADC3_MASK |     \
                                           ADC_CH_ADC4_MASK |     \
                                           ADC_CH_ADC5_MASK |     \
                                           ADC_CH_ADC6_MASK |     \
                                           ADC_CH_ADC7_MASK |     \
                                           ADC_CH_INT_VREF_MASK | \
                                           ADC_CH_TEMP_SENSOR_MASK)) == 0)

/** @} */ /* End of group ADCx_Channels */

/** @defgroup ADCx_Delay_Go ADC1 start conversion delay
 * @{
 */

#define IS_ADC_DELAY_GO_VALUE(VALUE) (((VALUE) & ~0x7UL) == 0)

/** @} */ /* End of group ADCx_Delay_Go */

/** @} */ /* End of group ADC_Exported_Defines */

/** @defgroup ADC_Exported_Types ADC Exported Types
 * @{
 */

/**
 * @brief ADC1 Temperature Sensor configuration
 */
typedef enum {
    ADC_TEMP_SENSOR_DISABLE = (((uint32_t)0x0) << ADC1_CFG_TS_EN_Pos), /*!< Disables Temperature Sensor. */
    ADC_TEMP_SENSOR_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_TS_EN_Pos)  /*!< Enables Temperature Sensor. */
} ADC_TempSensor_TypeDef;

#define IS_ADC_TEMP_SENSOR_CONFIG(CONFIG) (((CONFIG) == ADC_TEMP_SENSOR_DISABLE) || \
                                           ((CONFIG) == ADC_TEMP_SENSOR_ENABLE))

/**
 * @brief ADC Temperature Sensor Amplifier configuration
 */
typedef enum {
    ADC_TEMP_SENSOR_AMPLIFIER_DISABLE = (((uint32_t)0x0) << ADC1_CFG_TS_BUF_EN_Pos), /*!< Disables Temperature Sensor Amplifier. */
    ADC_TEMP_SENSOR_AMPLIFIER_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_TS_BUF_EN_Pos)  /*!< Enables Temperature Sensor Amplifier. */
} ADC_TempSensorAmplifier_TypeDef;

#define IS_ADC_TEMP_SENSOR_AMP_CONFIG(CONFIG) (((CONFIG) == ADC_TEMP_SENSOR_AMPLIFIER_DISABLE) || \
                                               ((CONFIG) == ADC_TEMP_SENSOR_AMPLIFIER_ENABLE))

/**
 * @brief ADC Temperature Sensor Conversion configuration
 */
typedef enum {
    ADC_TEMP_SENSOR_CONVERSION_DISABLE = (((uint32_t)0x0) << ADC1_CFG_SEL_TS_Pos), /*!< Disables Temperature Sensor Conversion. */
    ADC_TEMP_SENSOR_CONVERSION_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_SEL_TS_Pos)  /*!< Enables Temperature Sensor Conversion. */
} ADC_TempSensorConversion_TypeDef;

#define IS_ADC_TEMP_SENSOR_CONVERSION_CONFIG(CONFIG) (((CONFIG) == ADC_TEMP_SENSOR_CONVERSION_DISABLE) || \
                                                      ((CONFIG) == ADC_TEMP_SENSOR_CONVERSION_ENABLE))

/**
 * @brief ADC Internal Voltage Reference Conversion configuration
 */
typedef enum {
    ADC_VREF_CONVERSION_DISABLE = (((uint32_t)0x0) << ADC1_CFG_SEL_VREF_Pos), /*!< Disables Internal Voltage Reference Conversion. */
    ADC_VREF_CONVERSION_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_SEL_VREF_Pos)  /*!< Enables Internal Voltage Reference Conversion. */
} ADC_IntVRefConversion_TypeDef;

#define IS_ADC_VREF_CONVERSION_CONFIG(CONFIG) (((CONFIG) == ADC_VREF_CONVERSION_DISABLE) || \
                                               ((CONFIG) == ADC_VREF_CONVERSION_ENABLE))

/**
 * @brief ADC1 Clock Source configuration
 */
typedef enum {
    ADC_CLOCK_SOURCE_CPU = (((uint32_t)0x0) << ADC1_CFG_REG_CLKS_Pos), /*!< Selects CPU_CLK as ADC clock. */
    ADC_CLOCK_SOURCE_ADC = (((uint32_t)0x1) << ADC1_CFG_REG_CLKS_Pos)  /*!< Selects ADC_CLK as ADC clock. */
} ADCx_ClockSource_TypeDef;

#define IS_ADC_CLOCK_SOURCE_CONFIG(CONFIG) (((CONFIG) == ADC_CLOCK_SOURCE_ADC) || \
                                            ((CONFIG) == ADC_CLOCK_SOURCE_CPU))

/**
 * @brief ADC Sampling Mode configuration
 */
typedef enum {
    ADC_SAMPLING_MODE_SINGLE_CONV = (((uint32_t)0x0) << ADC1_CFG_REG_SAMPLE_Pos), /*!< Selects ADC single mode operation. */
    ADC_SAMPLING_MODE_CYCLIC_CONV = (((uint32_t)0x1) << ADC1_CFG_REG_SAMPLE_Pos)  /*!< Selects ADC cyclic mode operation. */
} ADCx_SamplingMode_TypeDef;

#define IS_ADC_SAMPLING_MODE_CONFIG(CONFIG) (((CONFIG) == ADC_SAMPLING_MODE_SINGLE_CONV) || \
                                             ((CONFIG) == ADC_SAMPLING_MODE_CYCLIC_CONV))

/**
 * @brief ADC Channel Swithing configuration
 */
typedef enum {
    ADC_CH_SWITCHING_DISABLE = (((uint32_t)0x0) << ADC1_CFG_REG_CHCH_Pos), /*!< Disables Channel Swithing. */
    ADC_CH_SWITCHING_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_REG_CHCH_Pos)  /*!< Enables Channel Swithing. */
} ADCx_ChannelSwitching_TypeDef;

#define IS_ADC_CH_SWITCHING_CONFIG(CONFIG) (((CONFIG) == ADC_CH_SWITCHING_DISABLE) || \
                                            ((CONFIG) == ADC_CH_SWITCHING_ENABLE))

/**
 * @brief ADC Channel Number
 */
typedef enum {
    ADC_CH_ADC0        = ((uint32_t)0x00 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 0.  */
    ADC_CH_ADC1        = ((uint32_t)0x01 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 1.  */
    ADC_CH_ADC2        = ((uint32_t)0x02 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 2.  */
    ADC_CH_ADC3        = ((uint32_t)0x03 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 3.  */
    ADC_CH_ADC4        = ((uint32_t)0x04 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 4.  */
    ADC_CH_ADC5        = ((uint32_t)0x05 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 5.  */
    ADC_CH_ADC6        = ((uint32_t)0x06 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 6.  */
    ADC_CH_ADC7        = ((uint32_t)0x07 << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 7.  */
    ADC_CH_INT_VREF    = ((uint32_t)0x1E << ADC1_CFG_REG_CHS_Pos), /*!< Specifies the ADC channel 30 (Internal VRef). */
    ADC_CH_TEMP_SENSOR = ((uint32_t)0x1F << ADC1_CFG_REG_CHS_Pos)  /*!< Specifies the ADC channel 31 (Temperature Sensor). */
} ADCx_ChannelNumber_TypeDef;

#define IS_ADC_CH_NUM(NUM) (((NUM) == ADC_CH_ADC0) || \
                            ((NUM) == ADC_CH_ADC1) || \
                            ((NUM) == ADC_CH_ADC2) || \
                            ((NUM) == ADC_CH_ADC3) || \
                            ((NUM) == ADC_CH_ADC4) || \
                            ((NUM) == ADC_CH_ADC5) || \
                            ((NUM) == ADC_CH_ADC6) || \
                            ((NUM) == ADC_CH_ADC7))

#define IS_ADC1_CH_NUM(NUM) ((IS_ADC_CH_NUM(NUM)) ||       \
                             ((NUM) == ADC_CH_INT_VREF) || \
                             ((NUM) == ADC_CH_TEMP_SENSOR))

/**
 * @brief ADC Level Control configuration
 */
typedef enum {
    ADC_LEVEL_CONTROL_DISABLE = (((uint32_t)0x0) << ADC1_CFG_REG_RNGC_Pos), /*!< Disables Level Control. */
    ADC_LEVEL_CONTROL_ENABLE  = (((uint32_t)0x1) << ADC1_CFG_REG_RNGC_Pos)  /*!< Enables Level Control. */
} ADCx_LevelControl_TypeDef;

#define IS_ADC_LEVEL_CONTROL_CONFIG(CONFIG) (((CONFIG) == ADC_LEVEL_CONTROL_DISABLE) || \
                                             ((CONFIG) == ADC_LEVEL_CONTROL_ENABLE))

#define IS_ADC_VALUE(VALUE) (((VALUE) & ~0x0FFFUL) == 0)

/**
 * @brief ADC Voltage Reference Source configuration
 */
typedef enum {
    ADC_VREF_SOURCE_INTERNAL = (((uint32_t)0x0) << ADC1_CFG_M_REF_Pos), /*!< Selects Internal Voltage Reference. */
    ADC_VREF_SOURCE_EXTERNAL = (((uint32_t)0x1) << ADC1_CFG_M_REF_Pos)  /*!< Selects External Voltage Reference. */
} ADCx_VRefSource_TypeDef;

#define IS_ADC_VREF_SOURCE_CONFIG(CONFIG) (((CONFIG) == ADC_VREF_SOURCE_INTERNAL) || \
                                           ((CONFIG) == ADC_VREF_SOURCE_EXTERNAL))

/**
 * @brief ADC Internal Voltage Reference Source configuration
 */
typedef enum {
    ADC_INT_VREF_SOURCE_INEXACT = ((uint32_t)0x0), /*!< Selects inexact Internal Voltage Reference. */
    ADC_INT_VREF_SOURCE_EXACT   = ((uint32_t)0x1)  /*!< Selects exact Internal Voltage Reference (from Temperature Sensor). */
} ADCx_IntVRefSource_TypeDef;

#define IS_ADC_INT_VREF_SOURCE_CONFIG(CONFIG) (((CONFIG) == ADC_INT_VREF_SOURCE_INEXACT) || \
                                               ((CONFIG) == ADC_INT_VREF_SOURCE_EXACT))

/**
 * @brief ADC Clock Prescaler
 */
typedef enum {
    ADC_PRESCALER_DIV_1    = (((uint32_t)0x0) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 1. */
    ADC_PRESCALER_DIV_2    = (((uint32_t)0x1) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 2. */
    ADC_PRESCALER_DIV_4    = (((uint32_t)0x2) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 4. */
    ADC_PRESCALER_DIV_8    = (((uint32_t)0x3) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 8. */
    ADC_PRESCALER_DIV_16   = (((uint32_t)0x4) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 16. */
    ADC_PRESCALER_DIV_32   = (((uint32_t)0x5) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 32. */
    ADC_PRESCALER_DIV_64   = (((uint32_t)0x6) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 64. */
    ADC_PRESCALER_DIV_128  = (((uint32_t)0x7) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 128. */
    ADC_PRESCALER_DIV_256  = (((uint32_t)0x8) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 256. */
    ADC_PRESCALER_DIV_512  = (((uint32_t)0x9) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 512. */
    ADC_PRESCALER_DIV_1024 = (((uint32_t)0xA) << ADC1_CFG_REG_DIVCLK_Pos), /*!< The input ADC clock devided by 1024. */
    ADC_PRESCALER_DIV_2048 = (((uint32_t)0xB) << ADC1_CFG_REG_DIVCLK_Pos)  /*!< The input ADC clock devided by 2048. */
} ADCx_Prescaler_TypeDef;

#define IS_ADC_CLK_DIV_VALUE(VALUE) (((VALUE) == ADC_PRESCALER_DIV_1) ||    \
                                     ((VALUE) == ADC_PRESCALER_DIV_2) ||    \
                                     ((VALUE) == ADC_PRESCALER_DIV_4) ||    \
                                     ((VALUE) == ADC_PRESCALER_DIV_8) ||    \
                                     ((VALUE) == ADC_PRESCALER_DIV_16) ||   \
                                     ((VALUE) == ADC_PRESCALER_DIV_32) ||   \
                                     ((VALUE) == ADC_PRESCALER_DIV_64) ||   \
                                     ((VALUE) == ADC_PRESCALER_DIV_128) ||  \
                                     ((VALUE) == ADC_PRESCALER_DIV_256) ||  \
                                     ((VALUE) == ADC_PRESCALER_DIV_512) ||  \
                                     ((VALUE) == ADC_PRESCALER_DIV_1024) || \
                                     ((VALUE) == ADC_PRESCALER_DIV_2048))

/**
 * @brief ADC1 Flags
 */
typedef enum {
    ADC1_FLAG_OVERWRITE         = ADC1_STATUS_FLG_REG_OVERWRITE_Msk, /*!< The previous ADC1 measured value was overwritten. */
    ADC1_FLAG_OUT_OF_RANGE      = ADC1_STATUS_FLG_REG_AWOIFEN_Msk,   /*!< The ADC1 measured value is out of range. */
    ADC1_FLAG_END_OF_CONVERSION = ADC1_STATUS_FLG_REG_EOCIF_Msk      /*!< The ADC1 conversion finished. */
} ADC1_Flags_TypeDef;

#define IS_ADC_STATUS_FLAG(FLAG) (((FLAG) == ADC1_FLAG_OVERWRITE) ||    \
                                  ((FLAG) == ADC1_FLAG_OUT_OF_RANGE) || \
                                  ((FLAG) == ADC1_FLAG_END_OF_CONVERSION))

#define IS_ADC_STATUS_FLAG_CLR(FLAG) (((FLAG) == ADC1_FLAG_OVERWRITE) || \
                                      ((FLAG) == ADC1_FLAG_OUT_OF_RANGE))

#define IS_ADC_STATUS_FLAGS_CLR(FLAG) (((FLAG) & ~(ADC1_FLAG_OVERWRITE | \
                                                   ADC1_FLAG_OUT_OF_RANGE)) == 0)

/**
 * @brief ADC1 Interrupt definition
 */
typedef enum {
    ADC1_IT_OUT_OF_RANGE      = ADC1_STATUS_FLG_REG_AWOIFEN_Msk,
    ADC1_IT_END_OF_CONVERSION = ADC1_STATUS_FLG_REG_EOCIF_Msk
} ADC1_IT_TypeDef;

#define IS_ADC_CONFIG_IT(IT) (((IT) & ~(ADC1_IT_OUT_OF_RANGE | ADC1_IT_END_OF_CONVERSION)) == 0)

/**
 * @brief ADC Int_VRef Amplifier
 */
typedef enum {
    ADC_INT_VREF_AMPLIFIER_DISABLE = (((uint32_t)0x0) << ADC1_TRIM_SEL_VREF_BUF_Pos),
    ADC_INT_VREF_AMPLIFIER_ENABLE  = (((uint32_t)0x1) << ADC1_TRIM_SEL_VREF_BUF_Pos)
} ADC_IntVRefAmplState_TypeDef;

#define IS_ADC_INT_VREF_AMPLIFIER(AMPLIFIER) (((AMPLIFIER) == ADC_INT_VREF_AMPLIFIER_DISABLE) || \
                                              ((AMPLIFIER) == ADC_INT_VREF_AMPLIFIER_ENABLE))

/**
 * @brief ADC Init structure definition
 */
typedef struct
{
    ADC_TempSensor_TypeDef ADC_TempSensor;                     /*!< Enables or disables the temperature sensor and internal voltage reference.
                                                                    This parameter can be a value of @ref ADC_TempSensor_TypeDef */
    ADC_TempSensorAmplifier_TypeDef ADC_TempSensorAmplifier;   /*!< Enables or disables the temperature sensor and internal voltage reference amplifier.
                                                                    This parameter can be a value of @ref ADC_TempSensorAmplifier_TypeDef */
    ADC_TempSensorConversion_TypeDef ADC_TempSensorConversion; /*!< Enables or disables the temperature sensor conversion.
                                                                    This parameter can be a value of @ref ADC_TempSensorConversion_TypeDef */
    ADC_IntVRefConversion_TypeDef ADC_IntVRefConversion;       /*!< Enables or disables the internal voltage reference conversion.
                                                                    This parameter can be a value of @ref ADC_IntVRefConversion_TypeDef */
    uint32_t ADC_IntVRefTrimming;                              /*!< Configures the internal voltage reference trimming.
                                                                    This parameter can be a number between 0 and 31 */
    ADC_IntVRefAmplState_TypeDef ADC_IntVRefAmplifier;         /*!< Enable or disable the internal voltage reference amplifier.
                                                                    This parameter can be a value of @ref ADC_IntVRefAmplState_TypeDef */
} ADC_InitTypeDef;

/**
 * @brief ADC1 Init structure definition
 */
typedef struct {
    ADCx_ClockSource_TypeDef ADC_ClockSource;           /*!< Specifies the ADC1 clock source.
                                                             This parameter can be a value of @ref ADCx_ClockSource_TypeDef */
    ADCx_SamplingMode_TypeDef ADC_SamplingMode;         /*!< Specifies the ADC1 sampling mode.
                                                             This parameter can be a value of @ref ADCx_SamplingMode_TypeDef */
    ADCx_ChannelSwitching_TypeDef ADC_ChannelSwitching; /*!< Enables or disables the ADC1 channel switching.
                                                             This parameter can be a value of @ref ADCx_ChannelSwitching_TypeDef */
    ADCx_ChannelNumber_TypeDef ADC_ChannelNumber;       /*!< Specifies the ADC1 channel number.
                                                             This parameter can be a value of @ref ADCx_ChannelNumber_TypeDef */
    uint32_t ADC_Channels;                              /*!< Specifies the ADC1 channels mask.
                                                             This parameter can be a value of @ref ADCx_Channels */
    ADCx_LevelControl_TypeDef ADC_LevelControl;         /*!< Enables or disables the ADC1 level control.
                                                             This parameter can be a value of @ref ADCx_LevelControl_TypeDef */
    uint16_t ADC_LowLevel;                              /*!< Specifies the ADC1 value low level.
                                                             This parameter can be a number between 0x0000 and 0x0FFF. */
    uint16_t ADC_HighLevel;                             /*!< Specifies the ADC1 value high level.
                                                             This parameter can be a number between 0x0000 and 0x0FFF. */
    ADCx_VRefSource_TypeDef ADC_VRefSource;             /*!< Specifies the ADC1 voltage reference source (internal or external).
                                                             This parameter can be a value of @ref ADCx_VRefSource_TypeDef */
    ADCx_IntVRefSource_TypeDef ADC_IntVRefSource;       /*!< Specifies the ADC1 internal voltage reference source (inexact or exact).
                                                             This parameter can be a value of @ref ADCx_IntVRefSource_TypeDef */
    ADCx_Prescaler_TypeDef ADC_Prescaler;               /*!< Specifies the ADC1 Prescaler configuration.
                                                             This parameter can be a value of @ref ADCx_Prescaler_TypeDef */
    uint32_t ADC_DelayGo;                               /*!< Specifies the ADC1 start conversion delay at sequential conversion mode.
                                                             This parameter can be a number between 0 and 7. */
} ADCx_InitTypeDef;

/** @} */ /* End of group ADC_Exported_Types */

/** @defgroup ADC_Exported_Functions ADC Exported Functions
 * @{
 */

void ADC_DeInit(void);

void ADC_Init(const ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);

void ADC_SetTrim(uint32_t Trim);

void ADC1_Init(const ADCx_InitTypeDef* ADCx_InitStruct);
void ADCx_StructInit(ADCx_InitTypeDef* ADCx_InitStruct);

void ADC1_Cmd(FunctionalState NewState);

void ADC1_SetChannel(ADCx_ChannelNumber_TypeDef Channel);
void ADC1_SetChannels(uint32_t ChannelMask);

void ADC1_OperationModeConfig(ADCx_SamplingMode_TypeDef SamplingMode, ADCx_ChannelSwitching_TypeDef SwitchingMode);
void ADC1_SamplingModeConfig(ADCx_SamplingMode_TypeDef SamplingMode);
void ADC1_ChannelSwithingConfig(ADCx_ChannelSwitching_TypeDef SwitchingMode);

void ADC1_LevelsConfig(uint32_t LowLevel, uint32_t HighLevel, ADCx_LevelControl_TypeDef NewState);
void ADC1_SetLowLevel(uint32_t LowLevel);
void ADC1_SetHighLevel(uint32_t HighLevel);

void ADC1_Start(void);

uint32_t ADC1_GetResult(void);

FlagStatus ADC1_GetFlagStatus(ADC1_Flags_TypeDef Flag);
uint32_t   ADC1_GetStatus(void);
void       ADC1_ClearFlags(uint32_t Flags);

void     ADC1_ITConfig(uint32_t ADC_IT, FunctionalState NewState);
ITStatus ADC1_GetITFlagStatus(ADC1_IT_TypeDef ADC_IT);
uint32_t ADC1_GetITStatus(void);

/**
 * @brief  Clears ADC1 interrupt requests.
 * @param  ITFlags: specifies the ADC interrupt request to clear.
 *         This parameter can be any combination of @ref ADC1_IT_TypeDef values.
 * @retval None.
 */
#define ADC1_ClearITFlags(ITFlags) ADC1_ClearFlags(ITFlags)

/** @} */ /* End of group ADC_Exported_Functions */

/** @} */ /* End of group ADC */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_ADC_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_adc.h */

