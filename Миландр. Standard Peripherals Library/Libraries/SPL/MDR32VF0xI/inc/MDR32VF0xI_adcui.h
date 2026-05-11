/**
 *******************************************************************************
 * @file    MDR32VF0xI_adcui.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    20/05/2025
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
#ifndef MDR32VF0xI_ADCUI_H
#define MDR32VF0xI_ADCUI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup ADCUI ADCUI
 * @{
 */

/** @defgroup ADCUI_Exported_Types ADCUI Exported Types
 * @{
 */

/**
 * @brief ADCUI channels definition.
 */
typedef enum {
    ADCUI_CH_F0_I0 = (((uint32_t)0x1) << ADCUI_CTRL1_I0EN_Pos),
    ADCUI_CH_F0_V0 = (((uint32_t)0x1) << ADCUI_CTRL1_V0EN_Pos),
    ADCUI_CH_F1_I1 = (((uint32_t)0x1) << ADCUI_CTRL1_I1EN_Pos),
    ADCUI_CH_F1_V1 = (((uint32_t)0x1) << ADCUI_CTRL1_V1EN_Pos),
    ADCUI_CH_F2_I2 = (((uint32_t)0x1) << ADCUI_CTRL1_I2EN_Pos),
    ADCUI_CH_F2_V2 = (((uint32_t)0x1) << ADCUI_CTRL1_V2EN_Pos),
    ADCUI_CH_F0_I3 = (((uint32_t)0X1) << ADCUI_CTRL1_I3EN_Pos)
} ADCUI_Channel_TypeDef;

#define IS_ADCUI_CHANNEL(CH) (((CH) == ADCUI_CH_F0_I0) || ((CH) == ADCUI_CH_F0_V0) || \
                              ((CH) == ADCUI_CH_F1_I1) || ((CH) == ADCUI_CH_F1_V1) || \
                              ((CH) == ADCUI_CH_F2_I2) || ((CH) == ADCUI_CH_F2_V2) || \
                              ((CH) == ADCUI_CH_F0_I3))

#define IS_ADCUI_CHANNEL_V1_V2(CH) (((CH) == ADCUI_CH_F1_V1) || ((CH) == ADCUI_CH_F2_V2))

#define IS_ADCUI_CHANNEL_NO_I3(CH) (((CH) == ADCUI_CH_F0_I0) || ((CH) == ADCUI_CH_F0_V0) || \
                                    ((CH) == ADCUI_CH_F1_I1) || ((CH) == ADCUI_CH_F1_V1) || \
                                    ((CH) == ADCUI_CH_F2_I2) || ((CH) == ADCUI_CH_F2_V2))

#define IS_ADCUI_CHANNELS(CHS) (((CHS) & ~(uint32_t)(ADCUI_CH_F0_I0 | ADCUI_CH_F0_V0 | \
                                                     ADCUI_CH_F1_I1 | ADCUI_CH_F1_V1 | \
                                                     ADCUI_CH_F2_I2 | ADCUI_CH_F2_V2 | \
                                                     ADCUI_CH_F0_I3)) == 0)

#define IS_ADCUI_CHANNELS_NO_I3(CHS) (((CHS) & ~(ADCUI_CH_F0_I0 | ADCUI_CH_F0_V0 | \
                                                 ADCUI_CH_F1_I1 | ADCUI_CH_F1_V1 | \
                                                 ADCUI_CH_F2_I2 | ADCUI_CH_F2_V2)) == 0)

/**
 * @brief ADCUI status flags.
 */
typedef enum {
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
    ADCUI_Fx_ICHANNEL = ADCUI_F0STAT_F0ICHANNEL,
    ADCUI_Fx_APSIGN   = ADCUI_FxSTAT_FxAPSIGN,
    ADCUI_Fx_APNLDFL  = ADCUI_FxSTAT_FxAPNLDFL,
    ADCUI_Fx_VARSIGN  = ADCUI_FxSTAT_FxVARSIGN,
    ADCUI_Fx_VARNLDFL = ADCUI_FxSTAT_FxVARNLDFL,
    ADCUI_Fx_VANLDFL  = ADCUI_FxSTAT_FxVANLDFL,
    ADCUI_Fx_ZEROCRS  = ADCUI_FxSTAT_FxZEROCRS,
    ADCUI_Fx_C3IF_EMP = ADCUI_F0STAT_C3IF_EMP,
    ADCUI_Fx_C3IF_FLL = ADCUI_F0STAT_C3IF_FLL,
    ADCUI_Fx_C3IF_OVR = ADCUI_F0STAT_C3IF_OVR,
    ADCUI_Fx_WATTOVN  = ADCUI_FxSTAT_FxWATTOVN,
    ADCUI_Fx_VAROVN   = ADCUI_FxSTAT_FxVAROVN
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
                             ((FLAG) == ADCUI_Fx_APSIGN) || ((FLAG) == ADCUI_Fx_APNLDFL) ||    \
                             ((FLAG) == ADCUI_Fx_VARSIGN) || ((FLAG) == ADCUI_Fx_VARNLDFL) ||  \
                             ((FLAG) == ADCUI_Fx_VANLDFL) || ((FLAG) == ADCUI_Fx_ZEROCRS) ||   \
                             ((FLAG) == ADCUI_Fx_C3IF_EMP) || ((FLAG) == ADCUI_Fx_C3IF_FLL) || \
                             ((FLAG) == ADCUI_Fx_C3IF_OVR) || ((FLAG) == ADCUI_Fx_WATTOVN) ||  \
                             ((FLAG) == ADCUI_Fx_VAROVN))

/**
 * @brief ADCUI data output resolution (RESOL).
 */
typedef enum {
    ADCUI_DATA_RESOL_16BIT = (((uint32_t)0x0) << ADCUI_CTRL1_RESOL_Pos),
    ADCUI_DATA_RESOL_24BIT = (((uint32_t)0x1) << ADCUI_CTRL1_RESOL_Pos)
} ADCUI_DataResol_TypeDef;

#define IS_ADCUI_DATA_RESOL(RESOL) (((RESOL) == ADCUI_DATA_RESOL_16BIT) || \
                                    ((RESOL) == ADCUI_DATA_RESOL_24BIT))

/**
 * @brief ADCUI zero-cross low pass filter (ZXLPF).
 */
typedef enum {
    ADCUI_ZXLPF_FILTER_ENABLE  = (((uint32_t)0x0) << ADCUI_CTRL1_ZXLPF_Pos),
    ADCUI_ZXLPF_FILTER_DISABLE = (((uint32_t)0x1) << ADCUI_CTRL1_ZXLPF_Pos)
} ADCUI_ZeroCrossLowPassFilter_TypeDef;

#define IS_ZXLPF_FILTER(STATE) (((STATE) == ADCUI_ZXLPF_FILTER_ENABLE) || \
                                ((STATE) == ADCUI_ZXLPF_FILTER_DISABLE))

/**
 * @brief ADCUI period length (PER_LENGTH).
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
    ADCUI_APNOLOAD_FULL = ADCUI_CTRL1_APNOLOAD_FULL,
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_APNOLOAD_0p04914pct = (((uint32_t)0x3F) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04836pct = (((uint32_t)0x3E) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04758pct = (((uint32_t)0x3D) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0468pct  = (((uint32_t)0x3C) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04602pct = (((uint32_t)0x3B) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04524pct = (((uint32_t)0x3A) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04446pct = (((uint32_t)0x39) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04368pct = (((uint32_t)0x38) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0429pct  = (((uint32_t)0x37) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04212pct = (((uint32_t)0x36) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04134pct = (((uint32_t)0x35) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p04056pct = (((uint32_t)0x34) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03978pct = (((uint32_t)0x33) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p039pct   = (((uint32_t)0x32) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03822pct = (((uint32_t)0x31) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03744pct = (((uint32_t)0x30) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03666pct = (((uint32_t)0x2F) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03588pct = (((uint32_t)0x2E) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0351pct  = (((uint32_t)0x2D) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03432pct = (((uint32_t)0x2C) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03354pct = (((uint32_t)0x2B) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03276pct = (((uint32_t)0x2A) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03198ct  = (((uint32_t)0x29) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0312pct  = (((uint32_t)0x28) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p03042pct = (((uint32_t)0x27) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02964pct = (((uint32_t)0x26) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02886pct = (((uint32_t)0x25) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02808pct = (((uint32_t)0x24) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0273pct  = (((uint32_t)0x23) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02652pct = (((uint32_t)0x22) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02574pct = (((uint32_t)0x21) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02496pct = (((uint32_t)0x20) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02418pct = (((uint32_t)0x1F) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0234pct  = (((uint32_t)0x1E) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02262pct = (((uint32_t)0x1D) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02184pct = (((uint32_t)0x1C) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02106pct = (((uint32_t)0x1B) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p02028pct = (((uint32_t)0x1A) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0195pct  = (((uint32_t)0x19) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01872pct = (((uint32_t)0x18) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01794pct = (((uint32_t)0x17) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01716pct = (((uint32_t)0x16) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01638pct = (((uint32_t)0x15) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0156pct  = (((uint32_t)0x14) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01482pct = (((uint32_t)0x13) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01404pct = (((uint32_t)0x12) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01326pct = (((uint32_t)0x11) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01248pct = (((uint32_t)0x10) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0117pct  = (((uint32_t)0x0F) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01092pct = (((uint32_t)0x0E) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p01014pct = (((uint32_t)0x0D) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00936pct = (((uint32_t)0x0C) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00858pct = (((uint32_t)0x0B) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0078pct  = (((uint32_t)0x0A) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00702pct = (((uint32_t)0x09) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00624pct = (((uint32_t)0x08) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00546pct = (((uint32_t)0x07) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00468pct = (((uint32_t)0x06) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p0039pct  = (((uint32_t)0x05) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00312pct = (((uint32_t)0x04) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00234pct = (((uint32_t)0x03) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00156pct = (((uint32_t)0x02) << ADCUI_LOAD_APNOLOAD_Pos),
    ADCUI_APNOLOAD_0p00078pct = (((uint32_t)0x01) << ADCUI_LOAD_APNOLOAD_Pos),
#endif
    ADCUI_APNOLOAD_0p012pct   = ADCUI_CTRL1_APNOLOAD_0p012pct,
    ADCUI_APNOLOAD_0p0061pct  = ADCUI_CTRL1_APNOLOAD_0p0061pct,
    ADCUI_APNOLOAD_0p00305pct = ADCUI_CTRL1_APNOLOAD_0p00305pct
} ADCUI_ActivePowerNoLoad_TypeDef;

#if defined(USE_MDR32F02_REV_1X)
#define IS_ADCUI_APNOLOAD(LOAD) (((LOAD) == ADCUI_APNOLOAD_FULL) ||      \
                                 ((LOAD) == ADCUI_APNOLOAD_0p012pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0061pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00305pct))
#else
#define IS_ADCUI_APNOLOAD(LOAD) (((LOAD) == ADCUI_APNOLOAD_FULL) ||       \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04914pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04836pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04758pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0468pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04602pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04524pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04446pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04368pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0429pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04212pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04134pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p04056pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03978pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p039pct) ||   \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03822pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03744pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03666pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03588pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0351pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03432pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03354pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03276pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03198ct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0312pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p03042pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02964pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02886pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02808pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0273pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02652pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02574pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02496pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02418pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0234pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02262pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02184pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02106pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p02028pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0195pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01872pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01794pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01716pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01638pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0156pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01482pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01404pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01326pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01248pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0117pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01092pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p01014pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00936pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00858pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0078pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00702pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00624pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00546pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00468pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0039pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00312pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00234pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00156pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00078pct) || \
                                 ((LOAD) == ADCUI_APNOLOAD_0p012pct) ||   \
                                 ((LOAD) == ADCUI_APNOLOAD_0p0061pct) ||  \
                                 ((LOAD) == ADCUI_APNOLOAD_0p00305pct))
#endif

/**
 * @brief ADCUI "No load" reactive power calculation mode (VARNOLOAD).
 */
typedef enum {
    ADCUI_VARNOLOAD_FULL = ADCUI_CTRL1_VARNOLOAD_FULL,
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_VARNOLOAD_0p04914pct = (((uint32_t)0x3F) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04836pct = (((uint32_t)0x3E) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04758pct = (((uint32_t)0x3D) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0468pct  = (((uint32_t)0x3C) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04602pct = (((uint32_t)0x3B) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04524pct = (((uint32_t)0x3A) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04446pct = (((uint32_t)0x39) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04368pct = (((uint32_t)0x38) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0429pct  = (((uint32_t)0x37) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04212pct = (((uint32_t)0x36) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04134pct = (((uint32_t)0x35) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p04056pct = (((uint32_t)0x34) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03978pct = (((uint32_t)0x33) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p039pct   = (((uint32_t)0x32) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03822pct = (((uint32_t)0x31) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03744pct = (((uint32_t)0x30) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03666pct = (((uint32_t)0x2F) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03588pct = (((uint32_t)0x2E) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0351pct  = (((uint32_t)0x2D) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03432pct = (((uint32_t)0x2C) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03354pct = (((uint32_t)0x2B) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03276pct = (((uint32_t)0x2A) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03198ct  = (((uint32_t)0x29) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0312pct  = (((uint32_t)0x28) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p03042pct = (((uint32_t)0x27) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02964pct = (((uint32_t)0x26) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02886pct = (((uint32_t)0x25) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02808pct = (((uint32_t)0x24) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0273pct  = (((uint32_t)0x23) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02652pct = (((uint32_t)0x22) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02574pct = (((uint32_t)0x21) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02496pct = (((uint32_t)0x20) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02418pct = (((uint32_t)0x1F) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0234pct  = (((uint32_t)0x1E) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02262pct = (((uint32_t)0x1D) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02184pct = (((uint32_t)0x1C) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02106pct = (((uint32_t)0x1B) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p02028pct = (((uint32_t)0x1A) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0195pct  = (((uint32_t)0x19) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01872pct = (((uint32_t)0x18) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01794pct = (((uint32_t)0x17) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01716pct = (((uint32_t)0x16) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01638pct = (((uint32_t)0x15) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0156pct  = (((uint32_t)0x14) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01482pct = (((uint32_t)0x13) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01404pct = (((uint32_t)0x12) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01326pct = (((uint32_t)0x11) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01248pct = (((uint32_t)0x10) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0117pct  = (((uint32_t)0x0F) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01092pct = (((uint32_t)0x0E) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p01014pct = (((uint32_t)0x0D) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00936pct = (((uint32_t)0x0C) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00858pct = (((uint32_t)0x0B) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0078pct  = (((uint32_t)0x0A) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00702pct = (((uint32_t)0x09) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00624pct = (((uint32_t)0x08) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00546pct = (((uint32_t)0x07) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00468pct = (((uint32_t)0x06) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p0039pct  = (((uint32_t)0x05) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00312pct = (((uint32_t)0x04) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00234pct = (((uint32_t)0x03) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00156pct = (((uint32_t)0x02) << ADCUI_LOAD_VARNOLOAD_Pos),
    ADCUI_VARNOLOAD_0p00078pct = (((uint32_t)0x01) << ADCUI_LOAD_VARNOLOAD_Pos),
#endif
    ADCUI_VARNOLOAD_0p012pct   = ADCUI_CTRL1_VARNOLOAD_0p012pct,
    ADCUI_VARNOLOAD_0p0061pct  = ADCUI_CTRL1_VARNOLOAD_0p0061pct,
    ADCUI_VARNOLOAD_0p00305pct = ADCUI_CTRL1_VARNOLOAD_0p00305pct
} ADCUI_ReactivePowerNoLoad_TypeDef;

#if defined(USE_MDR32F02_REV_1X)
#define IS_ADCUI_VARNOLOAD(LOAD) (((LOAD) == ADCUI_VARNOLOAD_FULL) ||      \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p012pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0061pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00305pct))
#else
#define IS_ADCUI_VARNOLOAD(LOAD) (((LOAD) == ADCUI_VARNOLOAD_FULL) ||       \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04914pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04836pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04758pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0468pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04602pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04524pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04446pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04368pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0429pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04212pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04134pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p04056pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03978pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p039pct) ||   \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03822pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03744pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03666pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03588pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0351pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03432pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03354pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03276pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03198ct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0312pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p03042pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02964pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02886pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02808pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0273pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02652pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02574pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02496pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02418pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0234pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02262pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02184pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02106pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p02028pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0195pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01872pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01794pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01716pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01638pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0156pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01482pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01404pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01326pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01248pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0117pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01092pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p01014pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00936pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00858pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0078pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00702pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00624pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00546pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00468pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0039pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00312pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00234pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00156pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00078pct) || \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p012pct) ||   \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p0061pct) ||  \
                                  ((LOAD) == ADCUI_VARNOLOAD_0p00305pct))
#endif

/**
 * @brief ADCUI "No load" full power calculation mode (VANOLOAD).
 */
typedef enum {
    ADCUI_VANOLOAD_FULL = ADCUI_CTRL1_VANOLOAD_FULL,
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_VANOLOAD_0p09828pct = (((uint32_t)0x3F) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p09672pct = (((uint32_t)0x3E) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p09516pct = (((uint32_t)0x3D) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0936pct  = (((uint32_t)0x3C) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p09204pct = (((uint32_t)0x3B) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p09048pct = (((uint32_t)0x3A) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p08892pct = (((uint32_t)0x39) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p08736pct = (((uint32_t)0x38) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0858pct  = (((uint32_t)0x37) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p08424pct = (((uint32_t)0x36) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p08268pct = (((uint32_t)0x35) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p08112pct = (((uint32_t)0x34) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p07956pct = (((uint32_t)0x33) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p078pct   = (((uint32_t)0x32) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p07644pct = (((uint32_t)0x31) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p07488pct = (((uint32_t)0x30) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p07332pct = (((uint32_t)0x2F) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p07176pct = (((uint32_t)0x2E) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0702pct  = (((uint32_t)0x2D) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p06864pct = (((uint32_t)0x2C) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p06708pct = (((uint32_t)0x2B) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p06552pct = (((uint32_t)0x2A) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p06396pct = (((uint32_t)0x29) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0624pct  = (((uint32_t)0x28) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p06084pct = (((uint32_t)0x27) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p05928pct = (((uint32_t)0x26) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p05772pct = (((uint32_t)0x25) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p05616pct = (((uint32_t)0x24) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0546pct  = (((uint32_t)0x23) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p05304pct = (((uint32_t)0x22) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p05148pct = (((uint32_t)0x21) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p04992pct = (((uint32_t)0x20) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p04836pct = (((uint32_t)0x1F) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0468pct  = (((uint32_t)0x1E) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p04524pct = (((uint32_t)0x1D) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p04368pct = (((uint32_t)0x1C) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p04212pct = (((uint32_t)0x1B) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p04056pct = (((uint32_t)0x1A) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p039pct   = (((uint32_t)0x19) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p03744pct = (((uint32_t)0x18) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p03588pct = (((uint32_t)0x17) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p03432pct = (((uint32_t)0x16) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p03276pct = (((uint32_t)0x15) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0312pct  = (((uint32_t)0x14) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p02964pct = (((uint32_t)0x13) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p02808pct = (((uint32_t)0x12) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p02652pct = (((uint32_t)0x11) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p02496pct = (((uint32_t)0x10) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0234pct  = (((uint32_t)0x0F) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p02184pct = (((uint32_t)0x0E) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p02028pct = (((uint32_t)0x0D) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p01872pct = (((uint32_t)0x0C) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p01716pct = (((uint32_t)0x0B) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0156pct  = (((uint32_t)0x0A) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p01404pct = (((uint32_t)0x09) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p01248pct = (((uint32_t)0x08) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p01092pct = (((uint32_t)0x07) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p00936pct = (((uint32_t)0x06) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p0078pct  = (((uint32_t)0x05) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p00624pct = (((uint32_t)0x04) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p00468pct = (((uint32_t)0x03) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p00312pct = (((uint32_t)0x02) << ADCUI_LOAD_VANOLOAD_Pos),
    ADCUI_VANOLOAD_0p00156pct = (((uint32_t)0x01) << ADCUI_LOAD_VANOLOAD_Pos),
#endif
    ADCUI_VANOLOAD_0p012pct   = ADCUI_CTRL1_VANOLOAD_0p012pct,
    ADCUI_VANOLOAD_0p0061pct  = ADCUI_CTRL1_VANOLOAD_0p0061pct,
    ADCUI_VANOLOAD_0p00305pct = ADCUI_CTRL1_VANOLOAD_0p00305pct
} ADCUI_FullPowerNoLoad_TypeDef;

#if defined(USE_MDR32F02_REV_1X)
#define IS_ADCUI_VANOLOAD(LOAD) (((LOAD) == ADCUI_VANOLOAD_FULL) ||      \
                                 ((LOAD) == ADCUI_VANOLOAD_0p012pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0061pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00305pct))
#else
#define IS_ADCUI_VANOLOAD(LOAD) (((LOAD) == ADCUI_VANOLOAD_FULL) ||       \
                                 ((LOAD) == ADCUI_VANOLOAD_0p09828pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p09672pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p09516pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0936pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p09204pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p09048pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p08892pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p08736pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0858pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p08424pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p08268pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p08112pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p07956pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p078pct) ||   \
                                 ((LOAD) == ADCUI_VANOLOAD_0p07644pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p07488pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p07332pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p07176pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0702pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p06864pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p06708pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p06552pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p06396pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0624pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p06084pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p05928pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p05772pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p05616pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0546pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p05304pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p05148pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p04992pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p04836pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0468pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p04524pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p04368pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p04212pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p04056pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p039pct) ||   \
                                 ((LOAD) == ADCUI_VANOLOAD_0p03744pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p03588pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p03432pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p03276pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0312pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p02964pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p02808pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p02652pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p02496pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0234pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p02184pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p02028pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p01872pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p01716pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0156pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p01404pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p01248pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p01092pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00936pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0078pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00624pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00468pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00312pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00156pct) || \
                                 ((LOAD) == ADCUI_VANOLOAD_0p012pct) ||   \
                                 ((LOAD) == ADCUI_VANOLOAD_0p0061pct) ||  \
                                 ((LOAD) == ADCUI_VANOLOAD_0p00305pct))
#endif

/**
 * @brief ADCUI reference voltage configuration (VREF_SEL).
 */
typedef enum {
    ADCUI_REFERENCE_VOLTAGE_INTERNAL = (((uint32_t)0x1) << ADCUI_CTRL1_VREF_SEL_Pos),
    ADCUI_REFERENCE_VOLTAGE_EXTERNAL = (((uint32_t)0x0) << ADCUI_CTRL1_VREF_SEL_Pos)
} ADCUI_VRefConfig_TypeDef;

#define IS_ADCUI_REFERENCE_VOLTAGE(RV) (((RV) == ADCUI_REFERENCE_VOLTAGE_INTERNAL) || \
                                        ((RV) == ADCUI_REFERENCE_VOLTAGE_EXTERNAL))

/**
 * @brief ADCUI zero-cross update RMS value (ZXRMS).
 */
typedef enum {
    ADCUI_REG_CONTINUOUS_UPDATE = (((uint32_t)0x0) << ADCUI_CTRL1_ZXRMS_Pos),
    ADCUI_REG_UPDATE_BY_ZERO    = (((uint32_t)0x1) << ADCUI_CTRL1_ZXRMS_Pos)
} ADCUI_ZeroCrossUpdateRMS_TypeDef;

#define IS_ADCUI_ZXRMS_REG_UPDATE(UPDATE) (((UPDATE) == ADCUI_REG_CONTINUOUS_UPDATE) || \
                                           ((UPDATE) == ADCUI_REG_UPDATE_BY_ZERO))
/**
 * @brief ADCUI oversampling divider (OSR_CONF).
 */
typedef enum {
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_OVERSAMPLING_DIV_1024 = ((uint32_t)(0x00) << ADCUI_CTRL1_OSR_CONF_Pos),     /*!< Frequency ADCUI divider (depends on the CLC_ADC_CFG setting). */
    ADCUI_OVERSAMPLING_DIV_512  = ((uint32_t)(0x01) << ADCUI_CTRL1_OSR_CONF_Pos),     /*!< Frequency ADCUI divider (depends on the CLC_ADC_CFG setting). */
    ADCUI_OVERSAMPLING_DIV_256  = (int)((uint32_t)(0x02) << ADCUI_CTRL1_OSR_CONF_Pos) /*!< Frequency ADCUI divider (depends on the CLC_ADC_CFG setting). */
#endif

#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
    ADCUI_OVERSAMPLING_DIV_256 = ((uint32_t)(0x00) << ADCUI_CTRL1_OSR_CONF_Pos),     /*!< Sampling frequency 4kHz. */
    ADCUI_OVERSAMPLING_DIV_128 = ((uint32_t)(0x01) << ADCUI_CTRL1_OSR_CONF_Pos),     /*!< Sampling frequency 8kHz. */
    ADCUI_OVERSAMPLING_DIV_64  = (int)((uint32_t)(0x02) << ADCUI_CTRL1_OSR_CONF_Pos) /*!< Sampling frequency 16kHz. */
#endif
} ADCUI_Divider_TypeDef;

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define IS_ADCUI_OSR_COF(COF) (((COF) == ADCUI_OVERSAMPLING_DIV_1024) || \
                               ((COF) == ADCUI_OVERSAMPLING_DIV_512) ||  \
                               ((COF) == ADCUI_OVERSAMPLING_DIV_256))
#endif

#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
#define IS_ADCUI_OSR_COF(COF) (((COF) == ADCUI_OVERSAMPLING_DIV_256) || \
                               ((COF) == ADCUI_OVERSAMPLING_DIV_128) || \
                               ((COF) == ADCUI_OVERSAMPLING_DIV_64))
#endif

/**
 * @brief ADCUI clock frequency (CLC_ADC_CFG).
 */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
typedef enum {
    ADCUI_CLK_FREQUENCY_4MHz = ((uint32_t)(0x00) << ADCUI_CLKPHASE1_CLC_ADC_CFG_Pos),
    ADCUI_CLK_FREQUENCY_2MHz = ((uint32_t)(0x01) << ADCUI_CLKPHASE1_CLC_ADC_CFG_Pos),
    ADCUI_CLK_FREQUENCY_1MHz = (int)((uint32_t)(0x02) << ADCUI_CLKPHASE1_CLC_ADC_CFG_Pos)
} ADCUI_ClockFrequency_TypeDef;

#define IS_ADCUI_CLK_FREQUENCY(FREQ) (((FREQ) == ADCUI_CLK_FREQUENCY_4MHz) || \
                                      ((FREQ) == ADCUI_CLK_FREQUENCY_2MHz) || \
                                      ((FREQ) == ADCUI_CLK_FREQUENCY_1MHz))
#endif

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define IS_ADCUI_CLK_OSR_VALID(FREQ, COF) ((((FREQ) == ADCUI_CLK_FREQUENCY_1MHz) && ((COF) == ADCUI_OVERSAMPLING_DIV_256)) || \
                                           (((FREQ) == ADCUI_CLK_FREQUENCY_2MHz) && ((COF) == ADCUI_OVERSAMPLING_DIV_256)) || \
                                           (((FREQ) == ADCUI_CLK_FREQUENCY_2MHz) && ((COF) == ADCUI_OVERSAMPLING_DIV_512)) || \
                                           (((FREQ) == ADCUI_CLK_FREQUENCY_4MHz) && ((COF) == ADCUI_OVERSAMPLING_DIV_256)) || \
                                           (((FREQ) == ADCUI_CLK_FREQUENCY_4MHz) && ((COF) == ADCUI_OVERSAMPLING_DIV_512)) || \
                                           (((FREQ) == ADCUI_CLK_FREQUENCY_4MHz) && ((COF) == ADCUI_OVERSAMPLING_DIV_1024)))
#endif

/**
 * @brief ADCUI chopper period setting (CHP_ADC_CFG).
 */

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
typedef enum {
    ADCUI_CHOPPER_PERIOD_256  = ((uint32_t)(0x00) << ADCUI_FILTERCFG_CHP_ADC_CFG_Pos), /*!< The chopper period is 256 periods of the ADC clock signal (recommended for OSR_CONF = 256) */
    ADCUI_CHOPPER_PERIOD_512  = ((uint32_t)(0x01) << ADCUI_FILTERCFG_CHP_ADC_CFG_Pos), /*!< The chopper period is 512 periods of the ADC clock signal (recommended for OSR_CONF = 512) */
    ADCUI_CHOPPER_PERIOD_1024 = ((uint32_t)(0x02) << ADCUI_FILTERCFG_CHP_ADC_CFG_Pos)  /*!< The chopper period is 1024 periods of the ADC clock signal (recommended for OSR_CONF = 1024) */
} ADCUI_ChopperPeriod_TypeDef;

#define IS_ADCUI_CHOPPER_PERIOD(PERIOD) (((PERIOD) == ADCUI_CHOPPER_PERIOD_256) || \
                                         ((PERIOD) == ADCUI_CHOPPER_PERIOD_512) || \
                                         ((PERIOD) == ADCUI_CHOPPER_PERIOD_1024))
#endif

/**
 * @brief ADCUI Fx integrator state in the I channel (FxINTEN).
 */
typedef enum {
    ADCUI_INT_ENABLE  = (uint32_t)(0x00),
    ADCUI_INT_DISABLE = (uint32_t)(0x01)
} ADCUI_IntegratorState_TypeDef;

#define IS_ADCUI_INT_STATE(STATE) (((STATE) == ADCUI_INT_ENABLE) || \
                                   ((STATE) == ADCUI_INT_DISABLE))

/**
 * @brief ADCUI source selection to store in full energy register VADATA (FxVASEL).
 */
typedef enum {
    ADCUI_FULL_ENERGY = (((uint32_t)0x0) << ADCUI_FxCTR_FxVASEL_Pos),
    ADCUI_RMS_CURRENT = (((uint32_t)0x1) << ADCUI_FxCTR_FxVASEL_Pos)
} ADCUI_SourceRegFullPower_TypeDef;

#define IS_ADCUI_VASEL(VASEL) (((VASEL) == ADCUI_FULL_ENERGY) || \
                               ((VASEL) == ADCUI_RMS_CURRENT))

/**
 * @brief ADCUI Fx gain in V channel (FxVGAIN).
 */
typedef enum {
    ADCUI_VGAIN_0dB  = (uint32_t)(0x00),
    ADCUI_VGAIN_6dB  = (uint32_t)(0x01),
    ADCUI_VGAIN_12dB = (uint32_t)(0x02),
    ADCUI_VGAIN_18dB = (uint32_t)(0x03)
} ADCUI_VGain_TypeDef;

#define IS_ADCUI_VGAIN(VGAIN) (((VGAIN) == ADCUI_VGAIN_0dB) ||  \
                               ((VGAIN) == ADCUI_VGAIN_6dB) ||  \
                               ((VGAIN) == ADCUI_VGAIN_12dB) || \
                               ((VGAIN) == ADCUI_VGAIN_18dB))

/**
 * @brief ADCUI Fx gain in I channel (FxIGAIN).
 */
typedef enum {
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_IGAIN_6dB  = (uint32_t)(0x00),
    ADCUI_IGAIN_12dB = (uint32_t)(0x01),
    ADCUI_IGAIN_18dB = (uint32_t)(0x02),
    ADCUI_IGAIN_24dB = (uint32_t)(0x03)
#endif

#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
        ADCUI_IGAIN_0dB = (uint32_t)(0x00),
    ADCUI_IGAIN_6dB     = (uint32_t)(0x01),
    ADCUI_IGAIN_12dB    = (uint32_t)(0x02),
    ADCUI_IGAIN_18dB    = (uint32_t)(0x03)
#endif
} ADCUI_IGain_TypeDef;

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define IS_ADCUI_IGAIN(IGAIN) (((IGAIN) == ADCUI_IGAIN_6dB) ||  \
                               ((IGAIN) == ADCUI_IGAIN_12dB) || \
                               ((IGAIN) == ADCUI_IGAIN_18dB) || \
                               ((IGAIN) == ADCUI_IGAIN_24dB))
#endif

#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
#define IS_ADCUI_IGAIN(IGAIN) (((IGAIN) == ADCUI_IGAIN_0dB) ||  \
                               ((IGAIN) == ADCUI_IGAIN_6dB) ||  \
                               ((IGAIN) == ADCUI_IGAIN_12dB) || \
                               ((IGAIN) == ADCUI_IGAIN_18dB))
#endif

/**
 * @brief ADCUI Fx unit number.
 */
typedef enum {
    ADCUI_F0_UNIT = (uint32_t)(0x00),
    ADCUI_F1_UNIT = (uint32_t)(0x01),
    ADCUI_F2_UNIT = (uint32_t)(0x02)
} ADCUI_Unit_TypeDef;

#define IS_ADCUI_UNIT(UNIT) (((UNIT) == ADCUI_F0_UNIT) || \
                             ((UNIT) == ADCUI_F1_UNIT) || \
                             ((UNIT) == ADCUI_F2_UNIT))

/**
 * @brief ADCUI power type.
 */
typedef enum {
    ADCUI_POWER_ACTIVE   = (uint32_t)(0x00),
    ADCUI_POWER_REACTIVE = (uint32_t)(0x01),
    ADCUI_POWER_FULL     = (uint32_t)(0x02)
} ADCUI_Power_TypeDef;

#define IS_ADCUI_POWER(PWR) (((PWR) == ADCUI_POWER_ACTIVE) ||   \
                             ((PWR) == ADCUI_POWER_REACTIVE) || \
                             ((PWR) == ADCUI_POWER_FULL))

#define IS_ADCUI_POWERS(PWRS) (((PWRS) & ~(uint32_t)(ADCUI_POWER_ACTIVE |   \
                                                     ADCUI_POWER_REACTIVE | \
                                                     ADCUI_POWER_FULL)) == 0)

/**
 * @brief ADCUI select a signal source for the ADCUI_FxVDAT (FxVSEL).
 */
typedef enum {
    ADCUI_Fx_VDAT_U_BEFORE_HPF   = ((uint32_t)(0x00) << ADCUI_FxMD0_FxVSEL_Pos),
    ADCUI_Fx_VDAT_ACTIVE_POWER   = ((uint32_t)(0x01) << ADCUI_FxMD0_FxVSEL_Pos),
    ADCUI_Fx_VDAT_REACTIVE_POWER = ((uint32_t)(0x02) << ADCUI_FxMD0_FxVSEL_Pos),
    ADCUI_Fx_VDAT_U_AFTER_HPF    = ((uint32_t)(0x03) << ADCUI_FxMD0_FxVSEL_Pos)
} ADCUI_Fx_SourceVDAT_TypeDef;

#define IS_ADCUI_VDAT_SOURCE(SOURCE) (((SOURCE) == ADCUI_Fx_VDAT_U_BEFORE_HPF) ||   \
                                      ((SOURCE) == ADCUI_Fx_VDAT_ACTIVE_POWER) ||   \
                                      ((SOURCE) == ADCUI_Fx_VDAT_REACTIVE_POWER) || \
                                      ((SOURCE) == ADCUI_Fx_VDAT_U_AFTER_HPF))

/**
 * @brief ADCUI select a signal source for the ADCUI_FxIDAT (FxISEL).
 */
typedef enum {
    ADCUI_Fx_IDAT_I              = ((uint32_t)(0x00) << ADCUI_FxMD0_FxISEL_Pos),
    ADCUI_Fx_IDAT_ACTIVE_POWER   = ((uint32_t)(0x01) << ADCUI_FxMD0_FxISEL_Pos),
    ADCUI_Fx_IDAT_REACTIVE_POWER = ((uint32_t)(0x02) << ADCUI_FxMD0_FxISEL_Pos),
    ADCUI_Fx_IDAT_FULL_POWER     = ((uint32_t)(0x03) << ADCUI_FxMD0_FxISEL_Pos)
} ADCUI_Fx_SourceIDAT_TypeDef;

#define IS_ADCUI_IDAT_SOURCE(SOURCE) (((SOURCE) == ADCUI_Fx_IDAT_I) ||              \
                                      ((SOURCE) == ADCUI_Fx_IDAT_ACTIVE_POWER) ||   \
                                      ((SOURCE) == ADCUI_Fx_IDAT_REACTIVE_POWER) || \
                                      ((SOURCE) == ADCUI_Fx_IDAT_FULL_POWER))

/**
 * @brief Specify the data (before or after the HPF filter) to be written into the ADCUI_F0I3DAT register in the F0I3SEL.
 */
typedef enum {
    ADCUI_F0I3SEL_AFTER_HPF  = (((uint32_t)0x0) << ADCUI_F0AC_F0I3SEL_Pos),
    ADCUI_F0I3SEL_BEFORE_HPF = (((uint32_t)0x1) << ADCUI_F0AC_F0I3SEL_Pos)
} ADCUI_F0_I3SelectDataFilter_TypeDef;

#define IS_ADCUI_F0I3SEL_SELECT(SELECT) (((SELECT) == ADCUI_F0I3SEL_AFTER_HPF) || \
                                         ((SELECT) == ADCUI_F0I3SEL_BEFORE_HPF))

/**
 * @brief Specify the data (before or after the HPF filter) to be written into the ADCUI_FxIDAT register.
 */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
typedef enum {
    ADCUI_FxISEL_BEFORE_HPF = ((uint32_t)0x0),
    ADCUI_FxISEL_AFTER_HPF  = ((uint32_t)0x1)
} ADCUI_Fx_ISelectDataFilter_TypeDef;

#define IS_ADCUI_FxISEL_SELECT(SELECT) (((SELECT) == ADCUI_FxISEL_BEFORE_HPF) || \
                                        ((SELECT) == ADCUI_FxISEL_AFTER_HPF))
#endif

/**
 * @brief Active current channel in the unit F0 (F0SEL_I_CH).
 */
typedef enum {
    ADCUI_F0_I_CH_AUTO = ((uint32_t)(0x00) << ADCUI_F0MD0_F0SEL_I_CH_Pos),
    ADCUI_F0_I_CH_I0   = ((uint32_t)(0x01) << ADCUI_F0MD0_F0SEL_I_CH_Pos),
    ADCUI_F0_I_CH_I3   = (int)((uint32_t)(0x02) << ADCUI_F0MD0_F0SEL_I_CH_Pos)
} ADCUI_F0_IChannelSelect_TypeDef;

#define IS_ADCUI_CHANNELI_SELECT(SELECT) (((SELECT) == ADCUI_F0_I_CH_AUTO) || \
                                          ((SELECT) == ADCUI_F0_I_CH_I0) ||   \
                                          ((SELECT) == ADCUI_F0_I_CH_I3))

/**
 * @brief Selecting DMA operating mode (single or block transactions).
 */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
typedef enum {
    ADCUI_DMA_TRANSACTIONS_SINGLE = ((uint32_t)0x0),
    ADCUI_DMA_TRANSACTIONS_BLOCK  = ((uint32_t)0x1)
} ADCUI_DmaTransMode_TypeDef;

#define IS_ADCUI_DMA_TRANSACTIONS_MODE(MODE) (((MODE) == ADCUI_DMA_TRANSACTIONS_SINGLE) || \
                                              ((MODE) == ADCUI_DMA_TRANSACTIONS_BLOCK))
#endif

/**
 * @brief ADCUI interrupt definition.
 */
typedef enum {
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
    ADCUI_Fx_IT_APSIGN   = ADCUI_FxSTAT_FxAPSIGN,
    ADCUI_Fx_IT_APNLDFL  = ADCUI_FxSTAT_FxAPNLDFL,
    ADCUI_Fx_IT_VARSIGN  = ADCUI_FxSTAT_FxVARSIGN,
    ADCUI_Fx_IT_VARNLDFL = ADCUI_FxSTAT_FxVARNLDFL,
    ADCUI_Fx_IT_VANLDFL  = ADCUI_FxSTAT_FxVANLDFL,
    ADCUI_Fx_IT_ZEROCRS  = ADCUI_FxSTAT_FxZEROCRS,
    ADCUI_Fx_IT_C3IF_EMP = ADCUI_F0STAT_C3IF_EMP,
    ADCUI_Fx_IT_C3IF_FLL = ADCUI_F0STAT_C3IF_FLL,
    ADCUI_Fx_IT_C3IF_OVR = ADCUI_F0STAT_C3IF_OVR,
    ADCUI_Fx_IT_WATTOVN  = ADCUI_FxSTAT_FxWATTOVN,
    ADCUI_Fx_IT_VAROVN   = ADCUI_FxSTAT_FxVAROVN
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

#define IS_ADCUI_ITS(IT)       (((IT) & (~(uint32_t)ADCUI_IT_MASK)) == 0)

#define IS_ADCUI_CONFIG_IT(IT) (((IT) == ADCUI_Fx_IT_VF_EMP) || ((IT) == ADCUI_Fx_IT_VF_FLL) ||     \
                                ((IT) == ADCUI_Fx_IT_VF_OVR) || ((IT) == ADCUI_Fx_IT_IF_EMP) ||     \
                                ((IT) == ADCUI_Fx_IT_IF_FLL) || ((IT) == ADCUI_Fx_IT_IF_OVR) ||     \
                                ((IT) == ADCUI_Fx_IT_SAGF) || ((IT) == ADCUI_Fx_IT_PEAKVF) ||       \
                                ((IT) == ADCUI_Fx_IT_PEAKIF) || ((IT) == ADCUI_Fx_IT_WATTOVP) ||    \
                                ((IT) == ADCUI_Fx_IT_VAROVP) || ((IT) == ADCUI_Fx_IT_VAOV) ||       \
                                ((IT) == ADCUI_Fx_IT_ZXTOF) || ((IT) == ADCUI_Fx_IT_APSIGN) ||      \
                                ((IT) == ADCUI_Fx_IT_APNLDFL) || ((IT) == ADCUI_Fx_IT_VARSIGN) ||   \
                                ((IT) == ADCUI_Fx_IT_VARNLDFL) || ((IT) == ADCUI_Fx_IT_VANLDFL) ||  \
                                ((IT) == ADCUI_Fx_IT_ZEROCRS) || ((IT) == ADCUI_Fx_IT_C3IF_EMP) ||  \
                                ((IT) == ADCUI_Fx_IT_C3IF_FLL) || ((IT) == ADCUI_Fx_IT_C3IF_OVR) || \
                                ((IT) == ADCUI_Fx_IT_WATTOVN) || ((IT) == ADCUI_Fx_IT_VAROVN))

/**
 * @brief ADCUI init structure definition.
 */
typedef struct {
    ADCUI_DataResol_TypeDef ADCUI_DataResol;                           /*!< Output data resolution.
                                                                            This parameter can be a value of the @ref ADCUI_DataResol_TypeDef. */
    ADCUI_ZeroCrossLowPassFilter_TypeDef ADCUI_ZeroCrossLowPassFilter; /*!< The state of the ZXLPF filter.
                                                                            This parameter can be a value of the @ref ADCUI_ZeroCrossLowPassFilter_TypeDef. */
    ADCUI_PeriodLength_TypeDef ADCUI_PeriodLength;                     /*!< Period and phase shift the calculation range.
                                                                            This parameter can be a value of the @ref ADCUI_PeriodLength_TypeDef. */
    ADCUI_ActivePowerNoLoad_TypeDef ADCUI_ActivePowerNoLoad;           /*!< No-load mode for the active energy calculation.
                                                                            This parameter can be a value of the @ref ADCUI_ActivePowerNoLoad_TypeDef. */
    ADCUI_ReactivePowerNoLoad_TypeDef ADCUI_ReactivePowerNoLoad;       /*!< No-load mode for the reactive energy calculation.
                                                                            This parameter can be a value of the @ref ADCUI_ReactivePowerNoLoad_TypeDef. */
    ADCUI_FullPowerNoLoad_TypeDef ADCUI_FullPowerNoLoad;               /*!< No-load mode for the total energy calculation.
                                                                            This parameter can be a value of the @ref ADCUI_FullPowerNoLoad_TypeDef. */
    FunctionalState ADCUI_FreqVEnable;                                 /*!< Permission to calculate a period in the voltage channels (FREQSEL).
                                                                            This parameter can be a value of the @ref FunctionalState. */
    ADCUI_VRefConfig_TypeDef ADCUI_VRefConfig;                         /*!< Selection of the reference voltage for the ADC and ADCUI.
                                                                            This parameter can be a value of the @ref ADCUI_VRefConfig_TypeDef. */
    ADCUI_ZeroCrossUpdateRMS_TypeDef ADCUI_ZeroCrossUpdateRMS;         /*!< RMS Register Update Controls.
                                                                            This parameter can be a value of the @ref ADCUI_ZeroCrossUpdateRMS_TypeDef. */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_ClockFrequency_TypeDef ADCUI_ClockFrequency; /*!< Selecting the ADC clock frequency.
                                                This parameter can be a value of the @ref ADCUI_ClockFrequency_TypeDef. */
    ADCUI_ChopperPeriod_TypeDef ADCUI_ChopperPeriod;   /*!< Setting the ADC chopper period of all channels.
                                                This parameter can be a value of the @ref ADCUI_ChopperPeriod_TypeDef. */
#endif
    ADCUI_Divider_TypeDef ADCUI_Divider; /*!< Selection of the oversampling factor.
                                              This parameter can be a value of the @ref ADCUI_Divider_TypeDef. */
    uint16_t ADCUI_VoltageDropLevel;     /*!< Permitted voltage drop level.
                                              This parameter is an even number from 0 to 65536. */
    uint8_t ADCUI_VoltageHalfCyclesDrop; /*!< The number of half-cycles of voltage to calculate the drawdown of the voltage level.
                                              This parameter is an even number from 0 to 255. */
    uint16_t ADCUI_ZeroCrossTimeOut;     /*!< The value of the time-out register which sets this value when the voltage signal crosses V0.
                                                                                                                  This parameter is an even number from 0 to 4095. */
} ADCUI_InitTypeDef;

/**
 * @brief ADCUI Fx unit structure.
 */
typedef struct {
    ADCUI_IntegratorState_TypeDef ADCUI_Fx_IntegratorEnable;         /*!< The state of the integrator in the I channel.
                                                                          This parameter can be a value of the @ref ADCUI_IntegratorState_TypeDef */
    ADCUI_IntegratorState_TypeDef ADCUI_F0_I3IntegratorEnable;       /*!< The state of the integrator in the I3 channel in the F0 unit.
                                                                          This parameter can be a value of the @ref ADCUI_IntegratorState_TypeDef */
    ADCUI_SourceRegFullPower_TypeDef ADCUI_SourceRegFullPower;       /*!< Enable or disable the DMA request when there is data in the FIFO.
                                                                          This parameter can be a value of the @ref ADCUI_SourceRegFullPower_TypeDef */
    ADCUI_IGain_TypeDef ADCUI_Fx_IGain;                              /*!< Specifies the level of the analog gain for I.
                                                                         This parameter can be a value of the @ref ADCUI_Gain_TypeDef */
    ADCUI_VGain_TypeDef ADCUI_Fx_VGain;                              /*!< Specifies the level of the analog gain for U.
                                                                         This parameter can be a value of the @ref ADCUI_Gain_TypeDef */
    int8_t ADCUI_Fx_PhaseShift;                                      /*!< Phase shift of the voltage channel relative to the current channel.
                                                                          This parameter is an even number from 0 to 255. */
    ADCUI_IGain_TypeDef ADCUI_F0_I3Gain;                             /*!< Specifies the level of the analog gain for I in the F0 unit.
                                                                         This parameter can be a value of the @ref ADCUI_Gain_TypeDef */
    uint16_t ADCUI_Fx_IRMSCalibration;                               /*!< Calibration of the RMS current calculator.
                                                                          This parameter is an even number from 0 to 4095. */
    uint16_t ADCUI_Fx_VRMSCalibration;                               /*!< Calibration of the RMS voltage calculator.
                                                                          This parameter is an even number from 0 to 4095. */
    ADCUI_Fx_SourceVDAT_TypeDef ADCUI_Fx_SourceVDAT;                 /*!< Selection of a signal source for the ADCUI_FxVDAT register.
                                                                          This parameter can be a value of the @ref ADCUI_Fx_SourceVDAT_TypeDef */
    ADCUI_Fx_SourceIDAT_TypeDef ADCUI_Fx_SourceIDAT;                 /*!< Selection of a signal source for the ADCUI_FxI0DAT register.
                                                                          This parameter can be a value of the @ref ADCUI_Fx_SourceIDAT_TypeDef */
    FunctionalState ADCUI_Fx_6dBIGainEnable;                         /*!< Gain 6 dB in the Ix channel.
                                                                          This parameter can be a value of the @ref FunctionalState. */
    FunctionalState ADCUI_Fx_6dBVGainEnable;                         /*!< Gain 6 dB in the U channel.
                                                                          This parameter can be a value of the @ref FunctionalState. */
    FunctionalState ADCUI_F0_6dBI3GainEnable;                        /*!< Gain 6 dB in the I3 channel, only for the F0.
                                                                          This parameter can be a value of the @ref FunctionalState. */
    ADCUI_F0_I3SelectDataFilter_TypeDef ADCUI_F0_I3SelectDataFilter; /*!< Selection of a signal source for the ADCUI_F0I3DAT register.
                                                                          This parameter can be a value of the @ref ADCUI_F0_I3SelectDataFilter_TypeDef */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_Fx_ISelectDataFilter_TypeDef ADCUI_Fx_ISelectDataFilter; /*!< Selection of a signal source for the ADCUI_FxIDAT register.
                                                                    This parameter can be a value of the @ref ADCUI_Fx_ISelectDataFilter_TypeDef */
#endif
    ADCUI_F0_IChannelSelect_TypeDef ADCUI_F0_IChannelSelect; /*!< Selection of an active current channel for the power characteristics calculation.
                                                                  This parameter can be a value of the @ref ADCUI_F0_IChannelSelect_TypeDef */
    uint16_t ADCUI_Fx_ActivePowerOffsetCalibration;          /*!< Active power offset calibration.
                                                                  This parameter is a number from 0x0 to 0xFFFF. */
    uint16_t ADCUI_Fx_ActivePowerGainCalibration;            /*!< Active power gain calibration.
                                                                  This parameter is a number from 0x0 to 0xFFF. */
    uint16_t ADCUI_Fx_ReactivePowerOffsetCalibration;        /*!< Reactive power offset calibration.
                                                                  This parameter is a number from 0x0 to 0xFFFF. */
    uint16_t ADCUI_Fx_ReactivePowerGainCalibration;          /*!< Reactive power gain calibration.
                                                                  This parameter is a number from 0x0 to 0xFFF. */
    uint16_t ADCUI_Fx_FullPowerGainCalibration;              /*!< Full power gain calibration.
                                                                  This parameter is a number from 0x0 to 0xFFF. */
    uint16_t ADCUI_Fx_VPeakLevel;                            /*!< Permitted maximum voltage level.
                                                                  This parameter is a number from 0x0 to 0xFFFF. */
    uint16_t ADCUI_Fx_IPeakLevel;                            /*!< Permitted maximum current level.
                                                                  This parameter is a number from 0x0 to 0xFFFF. */
    uint16_t ADCUI_Fx_IGainCalibration;                      /*!< Current calibration value for the Fx unit.
                                                                  This parameter is a number from 0x0 to 0xFFF (in rev.1 MDR32F02) or to 0xFFFF (in rev.2 MDR32F02 and MDR1206). */
    uint16_t ADCUI_Fx_VGainCalibration;                      /*!< Voltage calibration value for the Fx unit.
                                                                  This parameter is a number from 0x0 to 0xFFF (in rev.1 MDR32F02) or to 0xFFFF (in rev.2 MDR32F02 and MDR1206). */
    uint16_t ADCUI_F0_I3GainCalibration;                     /*!< Current calibration value in the I3 channel, only for the F0.
                                                                  This parameter is a number from 0x0 to 0xFFF (in rev.1 MDR32F02) or to 0xFFFF (in rev.2 MDR32F02 and MDR1206). */
} ADCUI_FxUnit_InitTypeDef;

/** @} */ /* End of the group ADCUI_Exported_Types */

/** @defgroup ADCUI_Exported_Functions ADCUI Exported Functions
 * @{
 */

void ADCUI_DeInit(void);
void ADCUI_Init(const ADCUI_InitTypeDef* ADCUI_InitStruct);
void ADCUI_StructInit(ADCUI_InitTypeDef* ADCUI_InitStruct);
void ADCUI_ResetDigital(FunctionalState NewState);

void ADCUI_Fx_Init(ADCUI_Unit_TypeDef UnitNumber, const ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct);
void ADCUI_Fx_StructInit(ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct);
void ADCUI_ChannelConfig(uint32_t Channels, FunctionalState NewState);

void ADCUI_Fx_ClearPowerCounter(ADCUI_Unit_TypeDef UnitNumber, ADCUI_Power_TypeDef PowerCounter);

uint32_t ADCUI_GetResult(ADCUI_Channel_TypeDef ChannelNumber);

uint64_t ADCUI_GetPowerAccumulator(ADCUI_Unit_TypeDef UnitNumber, ADCUI_Power_TypeDef PowerAccumulator, FunctionalState ReturnNegative);

uint32_t ADCUI_GetPeakValue(ADCUI_Channel_TypeDef ChannelNumber);
void     ADCUI_ClearPeakValue(ADCUI_Channel_TypeDef ChannelNumber);

uint32_t ADCUI_GetRMS(ADCUI_Channel_TypeDef ChannelNumber);
uint32_t ADCUI_GetRMS2(ADCUI_Channel_TypeDef ChannelNumber);

uint32_t ADCUI_GetVPhaseShiftRelativeV0(ADCUI_Channel_TypeDef ChannelNumber);

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
uint32_t ADCUI_GetVoltageTrueRMS(ADCUI_Unit_TypeDef UnitNumber);
#endif

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void ADCUI_DMAConfig(uint32_t Channels, ADCUI_DmaTransMode_TypeDef Mode, FunctionalState NewState);
void ADCUI_ChopperConfig(ADCUI_Channel_TypeDef ChannelNumber, FunctionalState NewState);
#endif

void       ADCUI_ClearFlags(ADCUI_Unit_TypeDef UnitNumber, uint32_t Flags);
FlagStatus ADCUI_GetFlagStatus(ADCUI_Unit_TypeDef UnitNumber, ADCUI_Flags_TypeDef ADCUI_Flag);
uint32_t   ADCUI_GetStatus(ADCUI_Unit_TypeDef UnitNumber);

void ADCUI_ITConfig(ADCUI_Unit_TypeDef UnitNumber, uint32_t ADCUI_IT, FunctionalState NewState);

/** @} */ /* End of the group ADCUI_Exported_Functions */

/** @} */ /* End of the group ADCUI */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_ADCUI_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_adcui.h */

