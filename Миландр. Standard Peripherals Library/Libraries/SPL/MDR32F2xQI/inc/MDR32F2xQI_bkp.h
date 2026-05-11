/**
 ******************************************************************************
 * @file    MDR32F2xQI_bkp.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    29/05/2023
 * @brief   This file contains all the functions prototypes for the BKP
 *          firmware library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32F2xQI_BKP_H
#define __MDR32F2xQI_BKP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup BKP BKP
 * @{
 */

/** @defgroup BKP_Exported_Types BKP Exported Types
 * @{
 */

/**
 * @brief Data Backup Registers
 */
typedef enum {
    BKP_REG_00 = ((uint32_t)0x00), /*!< Offset register BKP REG_00. */
    BKP_REG_01 = ((uint32_t)0x04), /*!< Offset register BKP REG_01. */
    BKP_REG_02 = ((uint32_t)0x08), /*!< Offset register BKP REG_02. */
    BKP_REG_03 = ((uint32_t)0x0C), /*!< Offset register BKP REG_03. */
    BKP_REG_04 = ((uint32_t)0x10), /*!< Offset register BKP REG_04. */
    BKP_REG_05 = ((uint32_t)0x14), /*!< Offset register BKP REG_05. */
    BKP_REG_06 = ((uint32_t)0x18), /*!< Offset register BKP REG_06. */
    BKP_REG_07 = ((uint32_t)0x1C), /*!< Offset register BKP REG_07. */
    BKP_REG_08 = ((uint32_t)0x20), /*!< Offset register BKP REG_08. */
    BKP_REG_09 = ((uint32_t)0x24), /*!< Offset register BKP REG_09. */
    BKP_REG_0A = ((uint32_t)0x28), /*!< Offset register BKP REG_0A. */
    BKP_REG_0B = ((uint32_t)0x2C), /*!< Offset register BKP REG_0B. */
    BKP_REG_0C = ((uint32_t)0x30), /*!< Offset register BKP REG_0C. */
    BKP_REG_0D = ((uint32_t)0x34), /*!< Offset register BKP REG_0D. */
    BKP_REG_0E = ((uint32_t)0x38), /*!< Offset register BKP REG_0E. */
    BKP_REG_0F = ((uint32_t)0x3C)  /*!< Offset register BKP REG_0F. */
} Data_Backup_Registers_TypeDef;

#define IS_BKP_REG(REG) (((REG) == BKP_REG_00) || ((REG) == BKP_REG_01) || \
                         ((REG) == BKP_REG_02) || ((REG) == BKP_REG_03) || \
                         ((REG) == BKP_REG_04) || ((REG) == BKP_REG_05) || \
                         ((REG) == BKP_REG_06) || ((REG) == BKP_REG_07) || \
                         ((REG) == BKP_REG_08) || ((REG) == BKP_REG_09) || \
                         ((REG) == BKP_REG_0A) || ((REG) == BKP_REG_0B) || \
                         ((REG) == BKP_REG_0C) || ((REG) == BKP_REG_0D) || \
                         ((REG) == BKP_REG_0E) || ((REG) == BKP_REG_0F))

#define IS_USER_BKP_REG(REG) (((REG) == BKP_REG_00) || ((REG) == BKP_REG_01) || \
                              ((REG) == BKP_REG_02) || ((REG) == BKP_REG_03) || \
                              ((REG) == BKP_REG_04) || ((REG) == BKP_REG_05) || \
                              ((REG) == BKP_REG_06) || ((REG) == BKP_REG_07) || \
                              ((REG) == BKP_REG_08) || ((REG) == BKP_REG_09) || \
                              ((REG) == BKP_REG_0A) || ((REG) == BKP_REG_0B) || \
                              ((REG) == BKP_REG_0C) || ((REG) == BKP_REG_0D))

/**
 * @brief BKP DUcc Mode
 */
typedef enum {
    BKP_DUCC_CLK_UPTO_10MHz  = (BKP_REG_0E_SELECTRI_LOAD_6k | BKP_REG_0E_LOW_CLK_UPTO_10MHz),    /*!< System clock is up to 10 MHz */
    BKP_DUCC_CLK_UPTO_200kHz = (BKP_REG_0E_SELECTRI_LOAD_270k | BKP_REG_0E_LOW_CLK_UPTO_200kHz), /*!< System clock is up to 200 kHz */
    BKP_DUCC_CLK_UPTO_500kHz = (BKP_REG_0E_SELECTRI_LOAD_90k | BKP_REG_0E_LOW_CLK_UPTO_500kHz),  /*!< System clock is up to 500 kHz */
    BKP_DUCC_CLK_UPTO_1MHz   = (BKP_REG_0E_SELECTRI_LOAD_24k | BKP_REG_0E_LOW_CLK_UPTO_1MHz),    /*!< System clock is up to 1 MHz */
    BKP_DUCC_CLK_OFF         = (BKP_REG_0E_SELECTRI_LOAD_900k | BKP_REG_0E_LOW_CLK_OFF),         /*!< All clocks are switched off */
    BKP_DUCC_CLK_UPTO_40MHz  = (BKP_REG_0E_SELECTRI_LOAD_2k | BKP_REG_0E_LOW_CLK_UPTO_40MHz),    /*!< System clock is up to 40 MHz */
    BKP_DUCC_CLK_UPTO_80MHz  = (BKP_REG_0E_SELECTRI_LOAD_400 | BKP_REG_0E_LOW_CLK_UPTO_80MHz),   /*!< System clock is up to 80 MHz */
    BKP_DUCC_CLK_OVER_80MHz  = (BKP_REG_0E_SELECTRI_LOAD_100 | BKP_REG_0E_LOW_CLK_OVER_80MHz)    /*!< System clock is over 80 MHz */
} BKP_DUСС_Mode_TypeDef;

#define IS_BKP_DUCC_MODE(MODE) (((MODE) == BKP_DUCC_CLK_UPTO_10MHz) ||  \
                                ((MODE) == BKP_DUCC_CLK_UPTO_200kHz) || \
                                ((MODE) == BKP_DUCC_CLK_UPTO_500kHz) || \
                                ((MODE) == BKP_DUCC_CLK_OFF) ||         \
                                ((MODE) == BKP_DUCC_CLK_UPTO_1MHz) ||   \
                                ((MODE) == BKP_DUCC_CLK_UPTO_40MHz) ||  \
                                ((MODE) == BKP_DUCC_CLK_UPTO_80MHz) ||  \
                                ((MODE) == BKP_DUCC_CLK_OVER_80MHz))

/**
 * @brief BKP DUcc Output Voltage Level
 */
typedef enum {
    BKP_DUCC_OUT_VOLTAGE_1p8V = BKP_REG_0E_TRIM43_1p8V, /*!< Output voltage of DUcc is 1.8V */
    BKP_DUCC_OUT_VOLTAGE_1p6V = BKP_REG_0E_TRIM43_1p6V, /*!< Output voltage of DUcc is 1.6V */
    BKP_DUCC_OUT_VOLTAGE_1p4V = BKP_REG_0E_TRIM43_1p4V, /*!< Output voltage of DUcc is 1.4V */
    BKP_DUCC_OUT_VOLTAGE_1p2V = BKP_REG_0E_TRIM43_1p2V  /*!< Output voltage of DUcc is 1.2V */
} BKP_DUCC_OutVoltage_TypeDef;

#define IS_BKP_DUCC_OUT_VOLTAGE(VOLTAGE) (((VOLTAGE) == BKP_DUCC_OUT_VOLTAGE_1p8V) || \
                                          ((VOLTAGE) == BKP_DUCC_OUT_VOLTAGE_1p6V) || \
                                          ((VOLTAGE) == BKP_DUCC_OUT_VOLTAGE_1p4V) || \
                                          ((VOLTAGE) == BKP_DUCC_OUT_VOLTAGE_1p2V))

/**
 * @brief BKP DUcc Trim
 */
typedef enum {
    BKP_DUCC_TRIM_PLUS_100mV  = BKP_REG_0E_TRIM20_PLUS_100mV,  /*!< Trim DUcc with + 100mV */
    BKP_DUCC_TRIM_PLUS_060mV  = BKP_REG_0E_TRIM20_PLUS_060mV,  /*!< Trim DUcc with + 060mV */
    BKP_DUCC_TRIM_PLUS_040mV  = BKP_REG_0E_TRIM20_PLUS_040mV,  /*!< Trim DUcc with + 040mV */
    BKP_DUCC_TRIM_PLUS_010mV  = BKP_REG_0E_TRIM20_PLUS_010mV,  /*!< Trim DUcc with + 010mV */
    BKP_DUCC_TRIM_MINUS_010mV = BKP_REG_0E_TRIM20_MINUS_010mV, /*!< Trim DUcc with - 010mV */
    BKP_DUCC_TRIM_MINUS_040mV = BKP_REG_0E_TRIM20_MINUS_040mV, /*!< Trim DUcc with - 040mV */
    BKP_DUCC_TRIM_MINUS_060mV = BKP_REG_0E_TRIM20_MINUS_060mV, /*!< Trim DUcc with - 060mV */
    BKP_DUCC_TRIM_MINUS_100mV = BKP_REG_0E_TRIM20_MINUS_100mV  /*!< Trim DUcc with - 100mV */
} BKP_DUСС_Trim_TypeDef;

#define IS_BKP_DUCC_TRIM(TRIM) (((TRIM) == BKP_DUCC_TRIM_PLUS_100mV) ||  \
                                ((TRIM) == BKP_DUCC_TRIM_PLUS_060mV) ||  \
                                ((TRIM) == BKP_DUCC_TRIM_PLUS_040mV) ||  \
                                ((TRIM) == BKP_DUCC_TRIM_PLUS_010mV) ||  \
                                ((TRIM) == BKP_DUCC_TRIM_MINUS_010mV) || \
                                ((TRIM) == BKP_DUCC_TRIM_MINUS_040mV) || \
                                ((TRIM) == BKP_DUCC_TRIM_MINUS_060mV) || \
                                ((TRIM) == BKP_DUCC_TRIM_MINUS_100mV))

/**
 * @brief BKP LSE (Low Speed External) clock mode and source selection constants
 */
typedef enum {
    BKP_LSE_OFF    = ((uint32_t)0x00),                        /*!< Switch off LSE clock generator. */
    BKP_LSE_ON     = BKP_REG_0F_LSE_ON,                       /*!< Switch on LSE clock generator. */
    BKP_LSE_BYPASS = (BKP_REG_0F_LSE_ON | BKP_REG_0F_LSE_BYP) /*!< Use external clock source. */
} BKP_LSE_Mode_TypeDef;

#define IS_BKP_LSE(LSE) (((LSE) == BKP_LSE_OFF) || \
                         ((LSE) == BKP_LSE_ON) ||  \
                         ((LSE) == BKP_LSE_BYPASS))

/**
 * @brief BKP Clock sources ready flags
 */
typedef enum {
    BKP_FLAG_HSIRDY = BKP_REG_0F_HSI_RDY, /*!< Flag for entering the operating mode of HSI clock generator */
    BKP_FLAG_LSIRDY = BKP_REG_0F_LSI_RDY, /*!< Flag for entering the operating mode of LSI clock generator */
    BKP_FLAG_LSERDY = BKP_REG_0F_LSE_RDY  /*!< Flag for entering the operating mode of LSE clock generator */
} BKP_CLK_Flags_TypeDef;

#define IS_BKP_CLK_FLAG(FLAG) (((FLAG) == BKP_FLAG_HSIRDY) || \
                               ((FLAG) == BKP_FLAG_LSIRDY) || \
                               ((FLAG) == BKP_FLAG_LSERDY))

/**
 * @brief BKP RTC Clock source
 */
typedef enum {
    BKP_RTC_LSI_CLK = BKP_REG_0F_RTC_SEL_LSI,     /*!< LSI oscillator clock is selected as RTC clock source. */
    BKP_RTC_LSE_CLK = BKP_REG_0F_RTC_SEL_LSE,     /*!< LSE oscillator clock is selected as RTC clock source. */
    BKP_RTC_HSI_CLK = BKP_REG_0F_RTC_SEL_HSI_RTC, /*!< HSI oscillator clock is selected as RTC clock source. */
    BKP_RTC_HSE_CLK = BKP_REG_0F_RTC_SEL_HSE_RTC  /*!< HSE oscillator clock is selected as RTC clock source. */
} BKP_RTC_CLK_TypeDef;

#define IS_BKP_RTC_CLK_SOURCE(CLK) (((CLK) == BKP_RTC_LSI_CLK) || \
                                    ((CLK) == BKP_RTC_LSE_CLK) || \
                                    ((CLK) == BKP_RTC_HSI_CLK) || \
                                    ((CLK) == BKP_RTC_HSE_CLK))

/**
 * @brief BKP RTC Interrupt definition
 */
typedef enum {
    BKP_RTC_IT_OWF  = BKP_RTC_CS_OWF,  /*!< Overflow interrupt. */
    BKP_RTC_IT_SECF = BKP_RTC_CS_SECF, /*!< Second interrupt. */
    BKP_RTC_IT_ALRF = BKP_RTC_CS_ALRF  /*!< Alarm interrupt. */
} BKP_RTC_IT_TypeDef;

#define IS_BKP_RTC_CONFIG_IT(IT) (((IT) == BKP_RTC_IT_OWF) ||  \
                                  ((IT) == BKP_RTC_IT_SECF) || \
                                  ((IT) == BKP_RTC_IT_ALRF))

#define IS_BKP_RTC_CONFIG_ITS(ITS) (((ITS) & ~(uint32_t)(BKP_RTC_IT_OWF |  \
                                                         BKP_RTC_IT_SECF | \
                                                         BKP_RTC_IT_ALRF)) == 0)

/**
 * @brief BKP RTC Flags
 */
typedef enum {
    BKP_RTC_FLAG_OWF  = BKP_RTC_CS_OWF,  /*!< Overflow flag */
    BKP_RTC_FLAG_SECF = BKP_RTC_CS_SECF, /*!< Second flag */
    BKP_RTC_FLAG_ALRF = BKP_RTC_CS_ALRF, /*!< Alarm flag */
    BKP_RTC_FLAG_WEC  = BKP_RTC_CS_WEC   /*!< RTC Write operation flag */
} BKP_RTC_Flags_TypeDef;

#define IS_BKP_RTC_FLAG(FLAG) (((FLAG) == BKP_RTC_FLAG_OWF) ||  \
                               ((FLAG) == BKP_RTC_FLAG_SECF) || \
                               ((FLAG) == BKP_RTC_FLAG_ALRF) || \
                               ((FLAG) == BKP_RTC_FLAG_WEC))

#define IS_BKP_RTC_FLAG_CLR(FLAG) (((FLAG) == BKP_RTC_FLAG_OWF) ||  \
                                   ((FLAG) == BKP_RTC_FLAG_SECF) || \
                                   ((FLAG) == BKP_RTC_FLAG_ALRF))

#define IS_BKP_RTC_FLAGS_CLR(FLAGS) (((FLAGS) & ~(uint32_t)(BKP_RTC_FLAG_OWF |  \
                                                            BKP_RTC_FLAG_SECF | \
                                                            BKP_RTC_FLAG_ALRF)) == 0)

/** @} */ /* End of group BKP_Exported_Types */

/** @defgroup BKP_Exported_Defines BKP Exported Defines
 * @{
 */

/** @defgroup BKP_HSI_Trim BKP HSI Trimming
 * @{
 */

#define IS_BKP_HSI_TRIM_VALUE(TRIM) (((TRIM) & ~0x3FUL) == 0)

/** @} */ /* End of group BKP_HSI_Trim */

/** @defgroup BKP_LSI_Trim BKP LSI Trimming
 * @{
 */

#define IS_BKP_LSI_TRIM_VALUE(TRIM) (((TRIM) & ~0x1FUL) == 0)

/** @} */ /* End of group BKP_LSI_Trim */

/** @defgroup BKP_RTC_Prescaler_Counter_Value BKP RTC Prescaler Counter Value
 * @{
 */

#define IS_BKP_RTC_PRESCALER_COUNTER_VALUE(VAL) (((VAL) & ~0x000FFFFFUL) == 0)

/** @} */ /* End of group BKP_RTC_Prescaler_Counter_Value */

/** @defgroup BKP_RTC_Prescaler_Value BKP RTC Prescaler Value
 * @{
 */

#define IS_BKP_RTC_PRESCALER_VALUE(VAL) (((VAL) & ~0x000FFFFFUL) == 0)

/** @} */ /* End of group BKP_RTC_Prescaler_Value */

/** @} */ /* End of group BKP_Exported_Defines */

/** @addtogroup BKP_Exported_Functions BKP Exported Functions
 * @{
 */

/** @addtogroup BKP_Control_Functions BKP control functions
 * @{
 */

void BKP_DeInit(void);

void BKP_SWDCmd(FunctionalState NewState);
void BKP_EnterSTANDBYMode(void);

void BKP_DUcc_SetMode(BKP_DUСС_Mode_TypeDef DUccMode);
void BKP_DUcc_SetOutVoltage(BKP_DUCC_OutVoltage_TypeDef OutVoltage);
void BKP_DUcc_SetTrim(BKP_DUСС_Trim_TypeDef DUccTrim);
void BKP_DUcc_CurrentLimitProtectionCmd(FunctionalState NewState);

void       BKP_SetFlagPOR(void);
FlagStatus BKP_GetFlagPOR(void);

void       BKP_SetFlagCOVDET(void);
FlagStatus BKP_GetFlagCOVDET(void);

/** @} */ /* End of group BKP_Control_Functions */

/** @addtogroup BKP_Clock_Source_Control_Functions BKP clock source control functions
 * @{
 */

void        BKP_HSI_Cmd(FunctionalState NewState);
void        BKP_HSI_Adjust(uint32_t HSITrimValue);
ErrorStatus BKP_HSI_GetStatus(void);

void        BKP_LSI_Cmd(FunctionalState NewState);
void        BKP_LSI_Adjust(uint32_t LSITrimValue);
ErrorStatus BKP_LSI_GetStatus(void);

void        BKP_LSE_Config(BKP_LSE_Mode_TypeDef LSEMode);
ErrorStatus BKP_LSE_GetStatus(void);

FlagStatus BKP_CLK_GetFlagStatus(BKP_CLK_Flags_TypeDef Flag);

/** @} */ /* End of group BKP_Clock_Source_Control_Functions */

/** @addtogroup BKP_RTC_Control_Functions BKP RTC control functions
 * @{
 */

void BKP_RTC_Cmd(FunctionalState NewState);
void BKP_RTC_Reset(FunctionalState NewState);

void BKP_RTC_SetClkSource(BKP_RTC_CLK_TypeDef Clk);
void BKP_RTC_SetClkCalibration(uint8_t Calibration);

void BKP_RTC_WaitForUpdate(void);

void     BKP_RTC_SetCounter(uint32_t CounterValue);
uint32_t BKP_RTC_GetCounter(void);

void     BKP_RTC_SetAlarm(uint32_t AlarmValue);
uint32_t BKP_RTC_GetAlarm(void);

void     BKP_RTC_SetPrescaler(uint32_t PrescalerValue);
uint32_t BKP_RTC_GetPrescaler(void);

void     BKP_RTC_SetPrescalerCounter(uint32_t PrescalerCounterValue);
uint32_t BKP_RTC_GetPrescalerCounter(void);

void       BKP_RTC_ClearFlags(uint32_t Flags);
FlagStatus BKP_RTC_GetFlagStatus(BKP_RTC_Flags_TypeDef Flag);
uint32_t   BKP_RTC_GetStatus(void);

void     BKP_RTC_ITConfig(uint32_t ITs, FunctionalState NewState);
ITStatus BKP_RTC_GetITFlagStatus(BKP_RTC_IT_TypeDef IT);
uint32_t BKP_RTC_GetITStatus(void);

/**
 * @brief  Clears RTC interrupt requests.
 * @param  ITs: specifies the RTC interrupt requests to clear.
 *         This parameter can be any combination of @ref BKP_RTC_IT_TypeDef values.
 * @retval None.
 */
#define BKP_RTC_ClearITFlags(ITs) BKP_RTC_ClearFlags(ITs)

/** @} */ /* End of group BKP_RTC_Control_Functions */

/** @} */ /* End of group BKP_Exported_Functions */

/** @} */ /* End of group BKP */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_BKP_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_bkp.h */

