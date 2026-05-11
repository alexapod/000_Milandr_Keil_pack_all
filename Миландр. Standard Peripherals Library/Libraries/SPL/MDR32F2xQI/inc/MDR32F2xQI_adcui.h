/**
 *******************************************************************************
 * @file    MDR32F2xQI_adcui.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    24/05/2023
 * @brief   This file contains all the functions prototypes for the ADCUI
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
#ifndef MDR32F2xQI_ADCUI_H
#define MDR32F2xQI_ADCUI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup ADCUI ADCUI
 * @{
 */

/** @defgroup ADCUI_Exported_Types ADCUI Exported Types
 * @{
 */

/**
 * @brief ADCUI Channels definition.
 */
typedef enum {
    ADCUI_CH_F0_I0 = ADCUI_CTRL1_I0EN,
    ADCUI_CH_F0_V0 = ADCUI_CTRL1_V0EN,
#if defined(USE_MDR32F21QI)
    ADCUI_CH_F1_I1 = ADCUI_CTRL1_I1EN,
    ADCUI_CH_F1_V1 = ADCUI_CTRL1_V1EN,
    ADCUI_CH_F2_I2 = ADCUI_CTRL1_I2EN,
    ADCUI_CH_F2_V2 = ADCUI_CTRL1_V2EN,
#endif
    ADCUI_CH_F0_I3 = ((uint32_t)0x40)
} ADCUI_Channel_TypeDef;

#if defined(USE_MDR32F21QI)

#define IS_ADCUI_CHANNEL(CH) (((CH) == ADCUI_CH_F0_I0) || ((CH) == ADCUI_CH_F0_V0) || \
                              ((CH) == ADCUI_CH_F1_I1) || ((CH) == ADCUI_CH_F1_V1) || \
                              ((CH) == ADCUI_CH_F2_I2) || ((CH) == ADCUI_CH_F2_V2) || \
                              ((CH) == ADCUI_CH_F0_I3))

#elif defined(USE_MDR32F23QI)

#define IS_ADCUI_CHANNEL(CH) (((CH) == ADCUI_CH_F0_I0) || ((CH) == ADCUI_CH_F0_V0) || \
                              ((CH) == ADCUI_CH_F0_I3))

#endif

#define IS_ADCUI_CHANNELS(CHS) (((CHS) <= 0x7F) && ((CHS) >= 0x1))

/**
 * @brief ADCUI Status flags.
 */
typedef enum {
#if defined(USE_MDR32F21QI)

    ADCUI_Fx_VF_EMP   = ADCUI_FxSTAT_FxVF_EMP,
    ADCUI_Fx_VF_FLL   = ADCUI_FxSTAT_FxVF_FLL,
    ADCUI_Fx_VF_OVR   = ADCUI_FxSTAT_FxVF_OVR,
    ADCUI_Fx_IF_EMP   = ADCUI_FxSTAT_FxIF_EMP,
    ADCUI_Fx_IF_FLL   = ADCUI_FxSTAT_FxIF_FLL,
    ADCUI_Fx_IF_OVR   = ADCUI_FxSTAT_FxIF_OVR,
    ADCUI_Fx_SAGF     = ADCUI_FxSTAT_FxSAGF,
    ADCUI_Fx_PEAKVF   = ADCUI_FxSTAT_FxPEAKVF,
    ADCUI_Fx_PEAKIF   = ADCUI_FxSTAT_FxPEAKIF,
    ADCUI_Fx_WATTOVP  = ADCUI_FxSTAT_FxWATTOVP,
    ADCUI_Fx_VAROVP   = ADCUI_FxSTAT_FxVAROVP,
    ADCUI_Fx_VAOV     = ADCUI_FxSTAT_FxVAOV,
    ADCUI_Fx_ZXTOF    = ADCUI_FxSTAT_FxZXTOF,
    ADCUI_Fx_ICHANNEL = ADCUI_FxSTAT_FxICHANNEL,
    ADCUI_Fx_FAULTCON = ADCUI_FxSTAT_FxFAULTCON,
    ADCUI_Fx_APSIGN   = ADCUI_FxSTAT_FxAPSIGN,
    ADCUI_Fx_APNLDFL  = ADCUI_FxSTAT_FxAPNLDFL,
    ADCUI_Fx_VARSIGN  = ADCUI_FxSTAT_FxVARSIGN,
    ADCUI_Fx_VARNLDFL = ADCUI_FxSTAT_FxVARNLDFL,
    ADCUI_Fx_VANLDFL  = ADCUI_FxSTAT_FxVANLDFL,
    ADCUI_Fx_ZEROCRS  = ADCUI_FxSTAT_FxZEROCRS,
    ADCUI_Fx_C3IF_EMP = ADCUI_FxSTAT_C3IF_EMP,
    ADCUI_Fx_C3IF_FLL = ADCUI_FxSTAT_C3IF_FLL,
    ADCUI_Fx_C3IF_OVR = ADCUI_FxSTAT_C3IF_OVR,
    ADCUI_Fx_WATTOVN  = ADCUI_FxSTAT_FxWATTOVN,
    ADCUI_Fx_VAROVN   = ADCUI_FxSTAT_FxVAROVN

#elif defined(USE_MDR32F23QI)

    ADCUI_Fx_VF_EMP   = ADCUI_F0STAT_F0VF_EMP,
    ADCUI_Fx_VF_FLL   = ADCUI_F0STAT_F0VF_FLL,
    ADCUI_Fx_VF_OVR   = ADCUI_F0STAT_F0VF_OVR,
    ADCUI_Fx_IF_EMP   = ADCUI_F0STAT_F0IF_EMP,
    ADCUI_Fx_IF_FLL   = ADCUI_F0STAT_F0IF_FLL,
    ADCUI_Fx_IF_OVR   = ADCUI_F0STAT_F0IF_OVR,
    ADCUI_Fx_SAGF     = ADCUI_F0STAT_F0SAGF,
    ADCUI_Fx_PEAKVF   = ADCUI_F0STAT_F0PEAKVF,
    ADCUI_Fx_PEAKIF   = ADCUI_F0STAT_F0PEAKIF,
    ADCUI_Fx_WATTOVP  = ADCUI_F0STAT_F0WATTOVP,
    ADCUI_Fx_VAROVP   = ADCUI_F0STAT_F0VAROVP,
    ADCUI_Fx_VAOV     = ADCUI_F0STAT_F0VAOV,
    ADCUI_Fx_ZXTOF    = ADCUI_F0STAT_F0ZXTOF,
    ADCUI_Fx_ICHANNEL = ADCUI_F0STAT_F0ICHANNEL,
    ADCUI_Fx_FAULTCON = ADCUI_F0STAT_F0FAULTCON,
    ADCUI_Fx_APSIGN   = ADCUI_F0STAT_F0APSIGN,
    ADCUI_Fx_APNLDFL  = ADCUI_F0STAT_F0APNLDFL,
    ADCUI_Fx_VARSIGN  = ADCUI_F0STAT_F0VARSIGN,
    ADCUI_Fx_VARNLDFL = ADCUI_F0STAT_F0VARNLDFL,
    ADCUI_Fx_VANLDFL  = ADCUI_F0STAT_F0VANLDFL,
    ADCUI_Fx_ZEROCRS  = ADCUI_F0STAT_F0ZEROCRS,
    ADCUI_Fx_C3IF_EMP = ADCUI_F0STAT_C3IF_EMP,
    ADCUI_Fx_C3IF_FLL = ADCUI_F0STAT_C3IF_FLL,
    ADCUI_Fx_C3IF_OVR = ADCUI_F0STAT_C3IF_OVR,
    ADCUI_Fx_WATTOVN  = ADCUI_F0STAT_F0WATTOVN,
    ADCUI_Fx_VAROVN   = ADCUI_F0STAT_F0VAROVN

#endif
} ADCUI_Flags_TypeDef;

#define ADCUI_FLAGS_MASK (ADCUI_Fx_VF_EMP |   \
                          ADCUI_Fx_VF_FLL |   \
                          ADCUI_Fx_VF_OVR |   \
                          ADCUI_Fx_IF_EMP |   \
                          ADCUI_Fx_IF_FLL |   \
                          ADCUI_Fx_IF_OVR |   \
                          ADCUI_Fx_SAGF |     \
                          ADCUI_Fx_PEAKVF |   \
                          ADCUI_Fx_PEAKIF |   \
                          ADCUI_Fx_WATTOVP |  \
                          ADCUI_Fx_VAROVP |   \
                          ADCUI_Fx_VAOV |     \
                          ADCUI_Fx_ZXTOF |    \
                          ADCUI_Fx_ICHANNEL | \
                          ADCUI_Fx_FAULTCON | \
                          ADCUI_Fx_APSIGN |   \
                          ADCUI_Fx_APNLDFL |  \
                          ADCUI_Fx_VARSIGN |  \
                          ADCUI_Fx_VARNLDFL | \
                          ADCUI_Fx_VANLDFL |  \
                          ADCUI_Fx_ZEROCRS |  \
                          ADCUI_Fx_C3IF_EMP | \
                          ADCUI_Fx_C3IF_FLL | \
                          ADCUI_Fx_C3IF_OVR | \
                          ADCUI_Fx_WATTOVN |  \
                          ADCUI_Fx_VAROVN)

#define IS_ADCUI_FLAG(FLAG) (((FLAG) == ADCUI_Fx_VF_EMP) || ((FLAG) == ADCUI_Fx_VF_FLL) ||     \
                             ((FLAG) == ADCUI_Fx_VF_OVR) || ((FLAG) == ADCUI_Fx_IF_EMP) ||     \
                             ((FLAG) == ADCUI_Fx_IF_FLL) || ((FLAG) == ADCUI_Fx_IF_OVR) ||     \
                             ((FLAG) == ADCUI_Fx_SAGF) || ((FLAG) == ADCUI_Fx_PEAKVF) ||       \
                             ((FLAG) == ADCUI_Fx_PEAKIF) || ((FLAG) == ADCUI_Fx_WATTOVP) ||    \
                             ((FLAG) == ADCUI_Fx_VAROVP) || ((FLAG) == ADCUI_Fx_VAOV) ||       \
                             ((FLAG) == ADCUI_Fx_ZXTOF) || ((FLAG) == ADCUI_Fx_ICHANNEL) ||    \
                             ((FLAG) == ADCUI_Fx_FAULTCON) || ((FLAG) == ADCUI_Fx_APSIGN) ||   \
                             ((FLAG) == ADCUI_Fx_APNLDFL) || ((FLAG) == ADCUI_Fx_VARSIGN) ||   \
                             ((FLAG) == ADCUI_Fx_VARNLDFL) || ((FLAG) == ADCUI_Fx_VANLDFL) ||  \
                             ((FLAG) == ADCUI_Fx_ZEROCRS) || ((FLAG) == ADCUI_Fx_C3IF_EMP) ||  \
                             ((FLAG) == ADCUI_Fx_C3IF_FLL) || ((FLAG) == ADCUI_Fx_C3IF_OVR) || \
                             ((FLAG) == ADCUI_Fx_WATTOVN || ((FLAG) == ADCUI_Fx_VAROVN)))

/**
 * @brief ADCUI Data output resolution (RESOL).
 */
typedef enum {
    ADCUI_DATA_RESOL_16BIT = (((uint32_t)0x0) << ADCUI_CTRL1_RESOL_Pos),
    ADCUI_DATA_RESOL_24BIT = (((uint32_t)0x1) << ADCUI_CTRL1_RESOL_Pos)
} ADCUI_DataResol_TypeDef;

#define IS_ADCUI_DATA_RESOL(RESOL) (((RESOL) == ADCUI_DATA_RESOL_16BIT) || \
                                    ((RESOL) == ADCUI_DATA_RESOL_24BIT))

/**
 * @brief ADCUI Zero-cross low pass filter (ZXLPF).
 */
typedef enum {
    ADCUI_ZXLPF_FILTER_ENABLE  = (((uint32_t)0x0) << ADCUI_CTRL1_ZXLPF_Pos),
    ADCUI_ZXLPF_FILTER_DISABLE = (((uint32_t)0x1) << ADCUI_CTRL1_ZXLPF_Pos)
} ADCUI_ZeroCrossLowPassFilter_TypeDef;

#define IS_ZXLPF_FILTER(STATE) (((STATE) == ADCUI_ZXLPF_FILTER_ENABLE) || \
                                ((STATE) == ADCUI_ZXLPF_FILTER_DISABLE))

/**
 * @brief ADCUI Period lenght (PER_LENGTH).
 */
typedef enum {
    ADCUI_PER_LENGTH_1   = ADCUI_CTRL1_PER_LENGHT_1,
    ADCUI_PER_LENGTH_2   = ADCUI_CTRL1_PER_LENGHT_2,
    ADCUI_PER_LENGTH_4   = ADCUI_CTRL1_PER_LENGHT_4,
    ADCUI_PER_LENGTH_8   = ADCUI_CTRL1_PER_LENGHT_8,
    ADCUI_PER_LENGTH_16  = ADCUI_CTRL1_PER_LENGHT_16,
    ADCUI_PER_LENGTH_32  = ADCUI_CTRL1_PER_LENGHT_32,
    ADCUI_PER_LENGTH_64  = ADCUI_CTRL1_PER_LENGHT_64,
    ADCUI_PER_LENGTH_128 = ADCUI_CTRL1_PER_LENGHT_128
} ADCUI_PeriodLength_TypeDef;

#define IS_ADCUI_PER_LENGTH(LENGTH) (((LENGTH) == ADCUI_PER_LENGTH_1) ||  \
                                     ((LENGTH) == ADCUI_PER_LENGTH_2) ||  \
                                     ((LENGTH) == ADCUI_PER_LENGTH_4) ||  \
                                     ((LENGTH) == ADCUI_PER_LENGTH_8) ||  \
                                     ((LENGTH) == ADCUI_PER_LENGTH_16) || \
                                     ((LENGTH) == ADCUI_PER_LENGTH_32) || \
                                     ((LENGTH) == ADCUI_PER_LENGTH_64) || \
                                     ((LENGTH) == ADCUI_PER_LENGTH_128))

/**
 * @brief ADCUI "No load" active power calculation mode (APNOLOAD).
 */
typedef enum {
    ADCUI_APNOLOAD_FULL       = ADCUI_CTRL1_APNOLOAD_FULL,
    ADCUI_APNOLOAD_0p012pct   = ADCUI_CTRL1_APNOLOAD_0p012pct,
    ADCUI_APNOLOAD_0p0061pct  = ADCUI_CTRL1_APNOLOAD_0p0061pct,
    ADCUI_APNOLOAD_0p00305pct = ADCUI_CTRL1_APNOLOAD_0p00305pct
} ADCUI_ActivePowerNoLoad_TypeDef;

#define IS_ADCUI_APNOLOAD(LOAD) (((LOAD) == ADCUI_APNOLOAD_FULL) ||      \
                                 ((LOAD) == ADCUI_APNOLOAD_0p012pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0061pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00305pct))
/**
 * @brief ADCUI "No load" reactive power calculation mode (VARNOLOAD).
 */
typedef enum {
    ADCUI_VARNOLOAD_FULL       = ADCUI_CTRL1_VARNOLOAD_FULL,
    ADCUI_VARNOLOAD_0p012pct   = ADCUI_CTRL1_VARNOLOAD_0p012pct,
    ADCUI_VARNOLOAD_0p0061pct  = ADCUI_CTRL1_VARNOLOAD_0p0061pct,
    ADCUI_VARNOLOAD_0p00305pct = ADCUI_CTRL1_VARNOLOAD_0p00305pct
} ADCUI_ReactivePowerNoLoad_TypeDef;

#define IS_ADCUI_VARNOLOAD(LOAD) (((LOAD) == ADCUI_VARNOLOAD_FULL) ||      \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p012pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0061pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00305pct))
/**
 * @brief ADCUI "No load" full power calculation mode (VANOLOAD).
 */
typedef enum {
    ADCUI_VANOLOAD_FULL       = ADCUI_CTRL1_VANOLOAD_FULL,
    ADCUI_VANOLOAD_0p012pct   = ADCUI_CTRL1_VANOLOAD_0p012pct,
    ADCUI_VANOLOAD_0p0061pct  = ADCUI_CTRL1_VANOLOAD_0p0061pct,
    ADCUI_VANOLOAD_0p00305pct = ADCUI_CTRL1_VANOLOAD_0p00305pct
} ADCUI_FullPowerNoLoad_TypeDef;

#define IS_ADCUI_VANOLOAD(LOAD) (((LOAD) == ADCUI_VANOLOAD_FULL) ||      \
                                 ((LOAD) == ADCUI_VANOLOAD_0p012pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0061pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00305pct))

/**
 * @brief ADCUI Reference voltage configuration (VREF_SEL).
 */
typedef enum {
    ADCUI_REFERENCE_VOLTAGE_INTERNAL = !ADCUI_CTRL1_VREF_SEL,
    ADCUI_REFERENCE_VOLTAGE_EXTERNAL = ADCUI_CTRL1_VREF_SEL
} ADCUI_VRefConfig_TypeDef;

#define IS_ADCUI_REFERENCE_VOLTAGE(RV) (((RV) == ADCUI_REFERENCE_VOLTAGE_INTERNAL) || \
                                        ((RV) == ADCUI_REFERENCE_VOLTAGE_EXTERNAL))

/**
 * @brief ADCUI Reference voltage buffering configuration (BUF_BYP).
 */
typedef enum {
    ADCUI_USE_VREF_BUF     = (((uint32_t)0x0) << ADCUI_CTRL1_VREF_SEL_Pos),
    ADCUI_NOT_USE_VREF_BUF = (((uint32_t)0x1) << ADCUI_CTRL1_VREF_SEL_Pos)
} ADCUI_VRefBufUse_TypeDef;

#define IS_ADCUI_BUFFER_VREF_USE(USE) (((USE) == ADCUI_USE_VREF_BUF) || \
                                       ((USE) == ADCUI_NOT_USE_VREF_BUF))

/**
 * @brief ADCUI Chopper frequency divider (CHOP_FREQ).
 */
#if defined(USE_MDR32F21QI)

typedef enum {
    ADCUI_CHOPPER_FREQUENCY_DIV_2  = ADCUI_CTRL1_CHOP_FREQ_DIV_2,
    ADCUI_CHOPPER_FREQUENCY_DIV_4  = ADCUI_CTRL1_CHOP_FREQ_DIV_4,
    ADCUI_CHOPPER_FREQUENCY_DIV_8  = ADCUI_CTRL1_CHOP_FREQ_DIV_8,
    ADCUI_CHOPPER_FREQUENCY_DIV_16 = ADCUI_CTRL1_CHOP_FREQ_DIV_16
} ADCUI_ChopperFreqPrescaler_TypeDef;

#define IS_ADCUI_CHOPPER_FREQUENCY_PRESCALER(FD) (((FD) & (~ADCUI_CTRL1_CHOP_FREQ_Msk)) == 0)

#endif

/**
 * @brief ADCUI Zero-cross update RMS value (ZXRMS).
 */
typedef enum {
    ADCUI_REG_CONTINUOUS_UPDATE = (((uint32_t)0x0) << ADCUI_CTRL1_ZXRMS_Pos),
    ADCUI_REG_UPDATE_BY_ZERO    = (((uint32_t)0x1) << ADCUI_CTRL1_ZXRMS_Pos)
} ADCUI_ZeroCrossUpdateRMS_TypeDef;

#define IS_ADCUI_ZXRMS_REG_UPDATE(UPDATE) (((UPDATE) == ADCUI_REG_CONTINUOUS_UPDATE) || \
                                           ((UPDATE) == ADCUI_REG_UPDATE_BY_ZERO))
/**
 * @brief ADCUI Oversampling divider (OSR_CONF).
 */
typedef enum {
    ADCUI_OVERSAMPLING_DIV_256 = (uint32_t)(0x00),
    ADCUI_OVERSAMPLING_DIV_128 = (uint32_t)(0x01),
    ADCUI_OVERSAMPLING_DIV_64  = (uint32_t)(0x02)
} ADCUI_Divider_TypeDef;

#define IS_ADCUI_OSR_COF(COF) (((COF) == ADCUI_OVERSAMPLING_DIV_256) || \
                               ((COF) == ADCUI_OVERSAMPLING_DIV_128) || \
                               ((COF) == ADCUI_OVERSAMPLING_DIV_64))

/**
 * @brief @brief ADCUI Fx integrator state in I channel (FxINTEN).
 */
typedef enum {
    ADCUI_INT_ENABLE  = (uint32_t)(0x00),
    ADCUI_INT_DISABLE = (uint32_t)(0x01)
} ADCUI_IntegratorState_TypeDef;

#define IS_ADCUI_INT_STATE(STATE) (((STATE) == ADCUI_INT_ENABLE) || \
                                   ((STATE) == ADCUI_INT_DISABLE))

/**
 * @brief ADCUI Source selection to store in full energy register VADATA (FxVASEL)
 */
typedef enum {
#if defined(USE_MDR32F21QI)

    ADCUI_FULL_ENERGY = (((uint32_t)0x0) << ADCUI_FxCTR_FxVASEL_Pos),
    ADCUI_RMS_CURRENT = (((uint32_t)0x1) << ADCUI_FxCTR_FxVASEL_Pos)

#elif defined(USE_MDR32F23QI)

    ADCUI_FULL_ENERGY = (((uint32_t)0x0) << ADCUI_F0CTR_F0VASEL_Pos),
    ADCUI_RMS_CURRENT = (((uint32_t)0x1) << ADCUI_F0CTR_F0VASEL_Pos)

#endif
} ADCUI_SourceRegFullPower_TypeDef;

#define IS_ADCUI_VASEL(VASEL) (((VASEL) == ADCUI_FULL_ENERGY) || \
                               ((VASEL) == ADCUI_RMS_CURRENT))

/**
 * @brief ADCUI Fx gain in I/U channel (FxVGAIN, FxIGAIN).
 */
typedef enum {
    ADCUI_GAIN_0dB  = (uint32_t)(0x00),
    ADCUI_GAIN_6dB  = (uint32_t)(0x01),
    ADCUI_GAIN_12dB = (uint32_t)(0x02),
    ADCUI_GAIN_18dB = (uint32_t)(0x03)
} ADCUI_Gain_TypeDef;

#define IS_ADCUI_GAIN(GAIN) (((GAIN) == ADCUI_GAIN_0dB) ||  \
                             ((GAIN) == ADCUI_GAIN_6dB) ||  \
                             ((GAIN) == ADCUI_GAIN_12dB) || \
                             ((GAIN) == ADCUI_GAIN_18dB))

/**
 * @brief ADCUI Fx unit number.
 */
typedef enum {
    ADCUI_F0_UNIT = (uint32_t)(0x00),
#if defined(USE_MDR32F21QI)
    ADCUI_F1_UNIT = (uint32_t)(0x01),
    ADCUI_F2_UNIT = (uint32_t)(0x02)
#endif
} ADCUI_Unit_TypeDef;

#if defined(USE_MDR32F21QI)

#define IS_ADCUI_UNIT(UNIT) (((UNIT) == ADCUI_F0_UNIT) || \
                             ((UNIT) == ADCUI_F1_UNIT) || \
                             ((UNIT) == ADCUI_F2_UNIT))

#elif defined(USE_MDR32F23QI)

#define IS_ADCUI_UNIT(UNIT) ((UNIT) == ADCUI_F0_UNIT)

#endif
/**
 * @brief ADCUI Select signal source for ADCUI_FxVDAT (FxVSEL).
 */
typedef enum {
#if defined(USE_MDR32F21QI)

    ADCUI_Fx_U_VDAT              = ADCUI_FxMD0_FxVSEL_V,
    ADCUI_Fx_ACTIVE_POWER_VDAT   = ADCUI_FxMD0_FxVSEL_ACTIVEPOWER,
    ADCUI_Fx_REACTIVE_POWER_VDAT = ADCUI_FxMD0_FxVSEL_REACTIVEPOWER,
    ADCUI_Fx_FULL_POWER_VDAT     = ADCUI_FxMD0_FxVSEL_FULLPOWER

#elif defined(USE_MDR32F23QI)

    ADCUI_Fx_U_VDAT              = ADCUI_F0MD0_F0VSEL_V,
    ADCUI_Fx_ACTIVE_POWER_VDAT   = ADCUI_F0MD0_F0VSEL_ACTIVEPOWER,
    ADCUI_Fx_REACTIVE_POWER_VDAT = ADCUI_F0MD0_F0VSEL_REACTIVEPOWER,
    ADCUI_Fx_FULL_POWER_VDAT     = ADCUI_F0MD0_F0VSEL_FULLPOWER

#endif
} ADCUI_Fx_SourceVDAT_TypeDef;

#define IS_ADCUI_VDAT_SOURCE(SOURCE) (((SOURCE) == ADCUI_Fx_U_VDAT) ||              \
                                      ((SOURCE) == ADCUI_Fx_ACTIVE_POWER_VDAT) ||   \
                                      ((SOURCE) == ADCUI_Fx_REACTIVE_POWER_VDAT) || \
                                      ((SOURCE) == ADCUI_Fx_FULL_POWER_VDAT))

/**
 * @brief ADCUI Select signal source for ADCUI_FxIDAT (FxISEL).
 */
typedef enum {
#if defined(USE_MDR32F21QI)

    ADCUI_Fx_I_IDAT              = ADCUI_FxMD0_FxISEL_I,
    ADCUI_Fx_ACTIVE_POWER_IDAT   = ADCUI_FxMD0_FxISEL_ACTIVEPOWER,
    ADCUI_Fx_REACTIVE_POWER_IDAT = ADCUI_FxMD0_FxISEL_REACTIVEPOWER,
    ADCUI_Fx_FULL_POWER_IDAT     = ADCUI_FxMD0_FxISEL_FULLPOWER

#elif defined(USE_MDR32F23QI)

    ADCUI_Fx_I_IDAT              = ADCUI_F0MD0_F0ISEL_I,
    ADCUI_Fx_ACTIVE_POWER_IDAT   = ADCUI_F0MD0_F0ISEL_ACTIVEPOWER,
    ADCUI_Fx_REACTIVE_POWER_IDAT = ADCUI_F0MD0_F0ISEL_REACTIVEPOWER,
    ADCUI_Fx_FULL_POWER_IDAT     = ADCUI_F0MD0_F0ISEL_FULLPOWER

#endif
} ADCUI_Fx_SourceIDAT_TypeDef;

#define IS_ADCUI_IDAT_SOURCE(SOURCE) (((SOURCE) == ADCUI_Fx_I_IDAT) ||              \
                                      ((SOURCE) == ADCUI_Fx_ACTIVE_POWER_IDAT) ||   \
                                      ((SOURCE) == ADCUI_Fx_REACTIVE_POWER_IDAT) || \
                                      ((SOURCE) == ADCUI_Fx_FULL_POWER_IDAT))

/**
 * @brief Conversion value to ADCUI_F0I3DAT register before or after filter (F0I3SEL).
 */
typedef enum {
#if defined(USE_MDR32F21QI)

    ADCUI_F0I3SEL_AFTER_FILTER  = (((uint32_t)0x0) << ADCUI_FxMD0_FxI3SEL_Pos),
    ADCUI_F0I3SEL_BEFORE_FILTER = (((uint32_t)0x1) << ADCUI_FxMD0_FxI3SEL_Pos)

#elif defined(USE_MDR32F23QI)

    ADCUI_F0I3SEL_AFTER_FILTER  = (((uint32_t)0x0) << ADCUI_F0MD0_F0I3SEL_Pos),
    ADCUI_F0I3SEL_BEFORE_FILTER = (((uint32_t)0x1) << ADCUI_F0MD0_F0I3SEL_Pos)

#endif
} ADCUI_F0_I3SelectDataFilter_TypeDef;

#define IS_ADCUI_F0I3SEL_SELECT(SELECT) (((SELECT) == ADCUI_F0I3SEL_AFTER_FILTER) || \
                                         ((SELECT) == ADCUI_F0I3SEL_BEFORE_FILTER))

/**
 * @brief Active current channel in block F0 (F0SEL_I_CH).
 */
typedef enum {
    ADCUI_F0_I_CH_AUTO = (uint32_t)(0x00),
    ADCUI_F0_I_CH_I0   = (uint32_t)(0x01),
    ADCUI_F0_I_CH_I3   = (uint32_t)(0x02)
} ADCUI_F0_IChannelSelect_TypeDef;

#define IS_ADCUI_CHANNELI_SELECT(SELECT) (((SELECT) == ADCUI_F0_I_CH_AUTO) || \
                                          ((SELECT) == ADCUI_F0_I_CH_I0) ||   \
                                          ((SELECT) == ADCUI_F0_I_CH_I3))

/**
 * @brief ADCUI Interrupt definition.
 */
typedef enum {
#if defined(USE_MDR32F21QI)

    ADCUI_Fx_IT_VF_EMP   = ADCUI_FxSTAT_FxVF_EMP,
    ADCUI_Fx_IT_VF_FLL   = ADCUI_FxSTAT_FxVF_FLL,
    ADCUI_Fx_IT_VF_OVR   = ADCUI_FxSTAT_FxVF_OVR,
    ADCUI_Fx_IT_IF_EMP   = ADCUI_FxSTAT_FxIF_EMP,
    ADCUI_Fx_IT_IF_FLL   = ADCUI_FxSTAT_FxIF_FLL,
    ADCUI_Fx_IT_IF_OVR   = ADCUI_FxSTAT_FxIF_OVR,
    ADCUI_Fx_IT_SAGF     = ADCUI_FxSTAT_FxSAGF,
    ADCUI_Fx_IT_PEAKVF   = ADCUI_FxSTAT_FxPEAKVF,
    ADCUI_Fx_IT_PEAKIF   = ADCUI_FxSTAT_FxPEAKIF,
    ADCUI_Fx_IT_WATTOVP  = ADCUI_FxSTAT_FxWATTOVP,
    ADCUI_Fx_IT_VAROVP   = ADCUI_FxSTAT_FxVAROVP,
    ADCUI_Fx_IT_VAOV     = ADCUI_FxSTAT_FxVAOV,
    ADCUI_Fx_IT_ZXTOF    = ADCUI_FxSTAT_FxZXTOF,
    ADCUI_Fx_IT_FAULTCON = ADCUI_FxSTAT_FxFAULTCON,
    ADCUI_Fx_IT_APSIGN   = ADCUI_FxSTAT_FxAPSIGN,
    ADCUI_Fx_IT_APNLDFL  = ADCUI_FxSTAT_FxAPNLDFL,
    ADCUI_Fx_IT_VARSIGN  = ADCUI_FxSTAT_FxVARSIGN,
    ADCUI_Fx_IT_VARNLDFL = ADCUI_FxSTAT_FxVARNLDFL,
    ADCUI_Fx_IT_VANLDFL  = ADCUI_FxSTAT_FxVANLDFL,
    ADCUI_Fx_IT_ZEROCRS  = ADCUI_FxSTAT_FxZEROCRS,
    ADCUI_Fx_IT_C3IF_EMP = ADCUI_FxSTAT_C3IF_EMP,
    ADCUI_Fx_IT_C3IF_FLL = ADCUI_FxSTAT_C3IF_FLL,
    ADCUI_Fx_IT_C3IF_OVR = ADCUI_FxSTAT_C3IF_OVR,
    ADCUI_Fx_IT_WATTOVN  = ADCUI_FxSTAT_FxWATTOVN,
    ADCUI_Fx_IT_VAROVN   = ADCUI_FxSTAT_FxVAROVN

#elif defined(USE_MDR32F23QI)

    ADCUI_Fx_IT_VF_EMP   = ADCUI_F0STAT_F0VF_EMP,
    ADCUI_Fx_IT_VF_FLL   = ADCUI_F0STAT_F0VF_FLL,
    ADCUI_Fx_IT_VF_OVR   = ADCUI_F0STAT_F0VF_OVR,
    ADCUI_Fx_IT_IF_EMP   = ADCUI_F0STAT_F0IF_EMP,
    ADCUI_Fx_IT_IF_FLL   = ADCUI_F0STAT_F0IF_FLL,
    ADCUI_Fx_IT_IF_OVR   = ADCUI_F0STAT_F0IF_OVR,
    ADCUI_Fx_IT_SAGF     = ADCUI_F0STAT_F0SAGF,
    ADCUI_Fx_IT_PEAKVF   = ADCUI_F0STAT_F0PEAKVF,
    ADCUI_Fx_IT_PEAKIF   = ADCUI_F0STAT_F0PEAKIF,
    ADCUI_Fx_IT_WATTOVP  = ADCUI_F0STAT_F0WATTOVP,
    ADCUI_Fx_IT_VAROVP   = ADCUI_F0STAT_F0VAROVP,
    ADCUI_Fx_IT_VAOV     = ADCUI_F0STAT_F0VAOV,
    ADCUI_Fx_IT_ZXTOF    = ADCUI_F0STAT_F0ZXTOF,
    ADCUI_Fx_IT_FAULTCON = ADCUI_F0STAT_F0FAULTCON,
    ADCUI_Fx_IT_APSIGN   = ADCUI_F0STAT_F0APSIGN,
    ADCUI_Fx_IT_APNLDFL  = ADCUI_F0STAT_F0APNLDFL,
    ADCUI_Fx_IT_VARSIGN  = ADCUI_F0STAT_F0VARSIGN,
    ADCUI_Fx_IT_VARNLDFL = ADCUI_F0STAT_F0VARNLDFL,
    ADCUI_Fx_IT_VANLDFL  = ADCUI_F0STAT_F0VANLDFL,
    ADCUI_Fx_IT_ZEROCRS  = ADCUI_F0STAT_F0ZEROCRS,
    ADCUI_Fx_IT_C3IF_EMP = ADCUI_F0STAT_C3IF_EMP,
    ADCUI_Fx_IT_C3IF_FLL = ADCUI_F0STAT_C3IF_FLL,
    ADCUI_Fx_IT_C3IF_OVR = ADCUI_F0STAT_C3IF_OVR,
    ADCUI_Fx_IT_WATTOVN  = ADCUI_F0STAT_F0WATTOVN,
    ADCUI_Fx_IT_VAROVN   = ADCUI_F0STAT_F0VAROVN

#endif
} ADCUI_IT_TypeDef;

#define ADCUI_IT_MASK (ADCUI_Fx_IT_VF_EMP |   \
                       ADCUI_Fx_IT_VF_FLL |   \
                       ADCUI_Fx_IT_VF_OVR |   \
                       ADCUI_Fx_IT_IF_EMP |   \
                       ADCUI_Fx_IT_IF_FLL |   \
                       ADCUI_Fx_IT_IF_OVR |   \
                       ADCUI_Fx_IT_SAGF |     \
                       ADCUI_Fx_IT_PEAKVF |   \
                       ADCUI_Fx_IT_PEAKIF |   \
                       ADCUI_Fx_IT_WATTOVP |  \
                       ADCUI_Fx_IT_VAROVP |   \
                       ADCUI_Fx_IT_VAOV |     \
                       ADCUI_Fx_IT_ZXTOF |    \
                       ADCUI_Fx_IT_FAULTCON | \
                       ADCUI_Fx_IT_APSIGN |   \
                       ADCUI_Fx_IT_APNLDFL |  \
                       ADCUI_Fx_IT_VARSIGN |  \
                       ADCUI_Fx_IT_VARNLDFL | \
                       ADCUI_Fx_IT_VANLDFL |  \
                       ADCUI_Fx_IT_ZEROCRS |  \
                       ADCUI_Fx_IT_C3IF_EMP | \
                       ADCUI_Fx_IT_C3IF_FLL | \
                       ADCUI_Fx_IT_C3IF_OVR | \
                       ADCUI_Fx_IT_WATTOVN |  \
                       ADCUI_Fx_IT_VAROVN)

#define IS_ADCUI_ITS(IT)       (((IT) & (~ADCUI_IT_MASK)) == 0)

#define IS_ADCUI_CONFIG_IT(IT) (((IT) == ADCUI_Fx_IT_VF_EMP) || ((IT) == ADCUI_Fx_IT_VF_FLL) ||     \
                                ((IT) == ADCUI_Fx_IT_VF_OVR) || ((IT) == ADCUI_Fx_IT_IF_EMP) ||     \
                                ((IT) == ADCUI_Fx_IT_IF_FLL) || ((IT) == ADCUI_Fx_IT_IF_OVR) ||     \
                                ((IT) == ADCUI_Fx_IT_SAGF) || ((IT) == ADCUI_Fx_IT_PEAKVF) ||       \
                                ((IT) == ADCUI_Fx_IT_PEAKIF) || ((IT) == ADCUI_Fx_IT_WATTOVP) ||    \
                                ((IT) == ADCUI_Fx_IT_VAROVP) || ((IT) == ADCUI_Fx_IT_VAOV) ||       \
                                ((IT) == ADCUI_Fx_IT_ZXTOF) || ((IT) == ADCUI_Fx_IT_FAULTCON) ||    \
                                ((IT) == ADCUI_Fx_IT_APSIGN) || ((IT) == ADCUI_Fx_IT_APNLDFL) ||    \
                                ((IT) == ADCUI_Fx_IT_VARSIGN) || ((IT) == ADCUI_Fx_IT_VARNLDFL) ||  \
                                ((IT) == ADCUI_Fx_IT_VANLDFL) || ((IT) == ADCUI_Fx_IT_ZEROCRS) ||   \
                                ((IT) == ADCUI_Fx_IT_C3IF_EMP) || ((IT) == ADCUI_Fx_IT_C3IF_FLL) || \
                                ((IT) == ADCUI_Fx_IT_C3IF_OVR) || ((IT) == ADCUI_Fx_IT_WATTOVN) ||  \
                                ((IT) == ADCUI_Fx_IT_VAROVN))

/**
 * @brief ADCUI Init structure defintion
 */
typedef struct
{
    ADCUI_DataResol_TypeDef ADCUI_DataResol;                           /*!< Output data resolution.
                                                                            This parameter can be a value of @ref ADCUI_DataResol_TypeDef. */
    ADCUI_ZeroCrossLowPassFilter_TypeDef ADCUI_ZeroCrossLowPassFilter; /*!< The state of the ZXLPF filter.
                                                                            This parameter can be a value of @ref ADCUI_ZeroCrossLowPassFilter_TypeDef. */
    ADCUI_PeriodLength_TypeDef ADCUI_PeriodLength;                     /*!< Period and phase shift calculation range.
                                                                            This parameter can be a value of @ref ADCUI_PeriodLength_TypeDef. */
    ADCUI_ActivePowerNoLoad_TypeDef ADCUI_ActivePowerNoLoad;           /*!< No-load mode for active energy calculation.
                                                                            This parameter can be a value of @ref ADCUI_ActivePowerNoLoad_TypeDef. */
    ADCUI_ReactivePowerNoLoad_TypeDef ADCUI_ReactivePowerNoLoad;       /*!< No-load mode for reactive energy calculation.
                                                                            This parameter can be a value of @ref ADCUI_ReactivePowerNoLoad_TypeDef. */
    ADCUI_FullPowerNoLoad_TypeDef ADCUI_FullPowerNoLoad;               /*!< No load mode when calculating apparent energy.
                                                                            This parameter can be a value of @ref ADCUI_FullPowerNoLoad_TypeDef. */
    FunctionalState ADCUI_FreqVEnable;                                 /*!< Permission to calculate period duration in voltage channels.
                                                                            This parameter can be a value of @ref FunctionalState. */
    ADCUI_VRefConfig_TypeDef ADCUI_VRefConfig;                         /*!< Selecting the reference voltage for the ADC.
                                                                            This parameter can be a value of @ref ADCUI_VRefConfig_TypeDef. */
    ADCUI_VRefBufUse_TypeDef ADCUI_VRefBufUse;                         /*!< Reference voltage buffering.
                                                                            This parameter can be a value of @ref ADCUI_VRefBufUse_TypeDef. */
#if defined(USE_MDR32F21QI)
    FunctionalState ADCUI_ChopEnable;                                  /*!< The state of the chopper ADC I3  channel.
                                                                            This parameter can be a value of @ref FunctionalState. */
    ADCUI_ChopperFreqPrescaler_TypeDef ADCUI_ChopperFreqPrescaler;     /*!< Chopper frequency.
                                                                            This parameter can be a value of @ref ADCUI_ChopperFreqPrescaler_TypeDef. */
#endif
    ADCUI_ZeroCrossUpdateRMS_TypeDef ADCUI_ZeroCrossUpdateRMS;         /*!< RMS Register Update Controls.
                                                                            This parameter can be a value of @ref ADCUI_ZeroCrossUpdateRMS_TypeDef. */
    FunctionalState ADCUI_IBoostEnable;                                /*!< ADC current increase.
                                                                            This parameter can be a value of @ref FunctionalState. */
    ADCUI_Divider_TypeDef ADCUI_Divider;                               /*!< Selecting the oversampling factor.
                                                                            This parameter can be a value of @ref ADCUI_Divider_TypeDef. */
    uint16_t ADCUI_VoltageDropLevel;                                   /*!< Allowed voltage drop level.
                                                                            This parameter is an even number from 0 to 65536. */
    uint8_t ADCUI_VoltageHalfCyclesDrop;                               /*!< The number of half-cycles of voltage to calculate the drawdown of the voltage level.
                                                                            This parameter is an even number from 0 to 255. */
    uint16_t ADCUI_ZeroCrossTimeOut;                                   /*!< The value of the time-out register that sets this value when the voltage signal crosses V0.
                                                                            This parameter is an even number from 0 to 4095. */
} ADCUI_InitTypeDef;

/**
 * @brief ADCUI Fx unit structure
 */
typedef struct
{
    ADCUI_IntegratorState_TypeDef ADCUI_Fx_IntegratorEnable;         /*!< The state of integrator in I channel.
                                                                          This parameter can be a value of @ref ADCUI_IntegratorState_TypeDef */
    ADCUI_IntegratorState_TypeDef ADCUI_F0_I3IntegratorEnable;       /*!< The state of integrator in I3 channel in F0 unit.
                                                                          This parameter can be a value of @ref ADCUI_IntegratorState_TypeDef */
    ADCUI_SourceRegFullPower_TypeDef ADCUI_SourceRegFullPower;       /*!< Enable or disable dma request when there is data in the FIFO.
                                                                          This parameter can be a value of @ref ADCUI_SourceRegFullPower_TypeDef */
    ADCUI_Gain_TypeDef ADCUI_Fx_IGain;                               /*!< Specifies the level of analog gain I.
                                                                          This parameter can be a value of @ref ADCUI_Gain_TypeDef */
    ADCUI_Gain_TypeDef ADCUI_Fx_VGain;                               /*!< Specifies the level of analog gain U.
                                                                          This parameter can be a value of @ref ADCUI_Gain_TypeDef */
    uint8_t ADCUI_Fx_PhaseShift;                                     /*!< Phase shift of the voltage channel relative to the current channel.
                                                                          This parameter is an even number from 0 to 255. */
    ADCUI_Gain_TypeDef ADCUI_F0_I3Gain;                              /*!< Specifies the level of analog gain I in F0 unit.
                                                                          This parameter can be a value of @ref ADCUI_Gain_TypeDef */
    uint16_t ADCUI_Fx_IRMSCalibration;                               /*!< Calibration of the rms current calculator.
                                                                          This parameter is an even number from 0 to 4095. */
    ADCUI_Fx_SourceVDAT_TypeDef ADCUI_Fx_SourceVDAT;                 /*!< Selecting a signal source for the ADCUI_FxVDAT register.
                                                                          This parameter can be a value of @ref ADCUI_Fx_SourceVDAT_TypeDef */
    ADCUI_Fx_SourceIDAT_TypeDef ADCUI_Fx_SourceIDAT;                 /*!< Selecting a signal source for the ADCUI_FxI0DAT register.
                                                                          This parameter can be a value of @ref ADCUI_Fx_SourceIDAT_TypeDef */
    FunctionalState ADCUI_Fx_6dBIGainEnable;                         /*!< Gain 6 dB in Ix channel.
                                                                          This parameter can be a value of @ref FunctionalState. */
    FunctionalState ADCUI_Fx_6dBVGainEnable;                         /*!< Gain 6 dB in U channel.
                                                                          This parameter can be a value of @ref FunctionalState. */
    FunctionalState ADCUI_F0_6dBI3GainEnable;                        /*!< Gain 6 dB in I3 channel, only for F0.
                                                                          This parameter can be a value of @ref FunctionalState. */
    ADCUI_F0_I3SelectDataFilter_TypeDef ADCUI_F0_I3SelectDataFilter; /*!< Selecting the signal source for the ADCUI_F0I3DAT register.
                                                                          This parameter can be a value of @ref ADCUI_F0_I3SelectDataFilter_TypeDef */
    ADCUI_F0_IChannelSelect_TypeDef ADCUI_F0_IChannelSelect;         /*!< Selecting the active current channel for calculating power characteristics.
                                                                          This parameter can be a value of @ref ADCUI_F0_IChannelSelect_TypeDef */
} ADCUI_FxUnit_InitTypeDef;

/** @} */ /* End of group ADCUI_Exported_Types */

/** @defgroup ADCUI_Exported_Functions ADCUI Exported Functions
 * @{
 */

void ADCUI_DeInit(void);
void ADCUI_Init(ADCUI_InitTypeDef* ADCUI_InitStruct);
void ADCUI_StructInit(ADCUI_InitTypeDef* ADCUI_InitStruct);
void ADCUI_ChannelConfig(uint32_t Channels, FunctionalState NewState);
void ADCUI_ResetDigital(FunctionalState NewState);

void ADCUI_Fx_Init(ADCUI_Unit_TypeDef UnitNumber, ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct);
void ADCUI_Fx_StructInit(ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct);

uint32_t   ADCUI_GetResult(ADCUI_Channel_TypeDef ChannelNumber);
void       ADCUI_ClearFlags(ADCUI_Unit_TypeDef UnitNumber, uint32_t Flags);
FlagStatus ADCUI_GetFlagStatus(ADCUI_Unit_TypeDef UnitNumber, ADCUI_Flags_TypeDef ADCUI_Flag);
uint32_t   ADCUI_GetStatus(ADCUI_Unit_TypeDef UnitNumber);

void       ADCUI_ITConfig(ADCUI_Unit_TypeDef UnitNumber, uint32_t ADCUI_IT, FunctionalState NewState);
void       ADCUI_ClearITFlags(ADCUI_Unit_TypeDef UnitNumber, uint32_t ITFlags);
FlagStatus ADCUI_GetITFlagStatus(ADCUI_Unit_TypeDef UnitNumber, ADCUI_IT_TypeDef ADCUI_ITFlag);
uint32_t   ADCUI_GetITStatus(ADCUI_Unit_TypeDef UnitNumber);

/** @} */ /* End of group ADCUI_Exported_Functions */

/** @} */ /* End of group ADCUI */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32F2xQI_ADCUI_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_adcui.h */

