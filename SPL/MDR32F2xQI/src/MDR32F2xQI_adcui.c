/**
 *******************************************************************************
 * @file    MDR32F2xQI_adcui.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    24/05/2023
 * @brief   This file contains all the ADCUI firmware functions.
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
#include "MDR32F2xQI_adcui.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup ADCUI ADCUI
 * @{
 */

/** @defgroup ADCUI_Private_Defines ADCUI Private Defines
 * @{
 */
#define IS_ADCUI_SAGLVL(SAGLVL)      ((SAGLVL) <= 0xFFF)
#define IS_ADCUI_SAGCYC(SAGCYC)      ((SAGCYC) <= 0xFF)
#define IS_ADCUI_ZXTOUT(ZXTOUT)      ((ZXTOUT) <= 0xFFF)

#define IS_ADCUI_FXPHASE(PHASE)      ((PHASE) <= 0xFF)
#define IS_ADCUI_FXIRMSOS(RMSOS)     ((RMSOS) <= 0xFFF)
#define IS_ADCUI_FXPER_FREQ_DIV(DIV) ((DIV) <= 0x1FFFF)

#define IS_ADCUI_FXIPKLVL(DIV)       ((LVL) <= 0xFFFF)
#define IS_ADCUI_FXVPKLVL(DIV)       ((LVL) <= 0xFFFF)

#if defined(USE_MDR32F21QI)

#define DEINIT_FLAGS (ADCUI_FxSTAT_FxVF_OVR |   \
                      ADCUI_FxSTAT_FxIF_OVR |   \
                      ADCUI_FxSTAT_FxSAGF |     \
                      ADCUI_FxSTAT_FxPEAKVF |   \
                      ADCUI_FxSTAT_FxPEAKIF |   \
                      ADCUI_FxSTAT_FxWATTOVP |  \
                      ADCUI_FxSTAT_FxVAROVP |   \
                      ADCUI_FxSTAT_FxVAOV |     \
                      ADCUI_FxSTAT_FxZXTOF |    \
                      ADCUI_FxSTAT_FxFAULTCON | \
                      ADCUI_FxSTAT_FxAPSIGN |   \
                      ADCUI_FxSTAT_FxVARSIGN |  \
                      ADCUI_FxSTAT_FxZEROCRS |  \
                      ADCUI_FxSTAT_C3IF_OVR |   \
                      ADCUI_FxSTAT_FxWATTOVN |  \
                      ADCUI_FxSTAT_FxVAROVN)

#elif defined(USE_MDR32F23QI)

#define DEINIT_FLAGS (ADCUI_F0STAT_F0VF_OVR |   \
                      ADCUI_F0STAT_F0IF_OVR |   \
                      ADCUI_F0STAT_F0SAGF |     \
                      ADCUI_F0STAT_F0PEAKVF |   \
                      ADCUI_F0STAT_F0PEAKIF |   \
                      ADCUI_F0STAT_F0WATTOVP |  \
                      ADCUI_F0STAT_F0VAROVP |   \
                      ADCUI_F0STAT_F0VAOV |     \
                      ADCUI_F0STAT_F0ZXTOF |    \
                      ADCUI_F0STAT_F0FAULTCON | \
                      ADCUI_F0STAT_F0APSIGN |   \
                      ADCUI_F0STAT_F0VARSIGN |  \
                      ADCUI_F0STAT_F0ZEROCRS |  \
                      ADCUI_F0STAT_C3IF_OVR |   \
                      ADCUI_F0STAT_F0WATTOVN |  \
                      ADCUI_F0STAT_F0VAROVN)

#endif

/** @} */ /* End of group ADCUI_Private_Defines */

/** @defgroup ADCUI_Exported_Functions ADCUI Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the ADCUI peripheral registers to their default reset values.
 * @param  None.
 * @retval None.
 */
void ADCUI_DeInit(void)
{
    MDR_ADCUI->CTRL1   = 0;
    MDR_ADCUI->CTRL2   = 0;
    MDR_ADCUI->CTRL3   = 0;
    MDR_ADCUI->F0CTR   = 0;
    MDR_ADCUI->F0WC    = 0;
    MDR_ADCUI->F0VC    = 0;
    MDR_ADCUI->F0AC    = 0;
    MDR_ADCUI->F0MD0   = 0;
    MDR_ADCUI->F0MD1   = 0;
    MDR_ADCUI->F0VPEAK = 0;
    MDR_ADCUI->F0IPEAK = 0;
    MDR_ADCUI->F0STAT  = DEINIT_FLAGS;
    MDR_ADCUI->F0MASK  = 0;
    MDR_ADCUI->CCAL1   = 0;
    MDR_ADCUI->CCAL4   = 0;

#if defined(USE_MDR32F21QI)

    MDR_ADCUI->F1CTR   = 0;
    MDR_ADCUI->F1WC    = 0;
    MDR_ADCUI->F1VC    = 0;
    MDR_ADCUI->F1AC    = 0;
    MDR_ADCUI->F1MD0   = 0;
    MDR_ADCUI->F1MD1   = 0;
    MDR_ADCUI->F1VPEAK = 0;
    MDR_ADCUI->F1IPEAK = 0;
    MDR_ADCUI->F1STAT  = DEINIT_FLAGS;
    MDR_ADCUI->F1MASK  = 0;
    MDR_ADCUI->F2CTR   = 0;
    MDR_ADCUI->F2WC    = 0;
    MDR_ADCUI->F2VC    = 0;
    MDR_ADCUI->F2AC    = 0;
    MDR_ADCUI->F2MD0   = 0;
    MDR_ADCUI->F2MD1   = 0;
    MDR_ADCUI->F2VPEAK = 0;
    MDR_ADCUI->F2IPEAK = 0;
    MDR_ADCUI->F2STAT  = DEINIT_FLAGS;
    MDR_ADCUI->F2MASK  = 0;
    MDR_ADCUI->CCAL2   = 0;
    MDR_ADCUI->CCAL3   = 0;

#endif
}

/**
 * @brief  Fills each ADCUI_InitStruct member with its default value.
 * @param  ADCUI_InitStruct: pointer to a @ref ADCUI_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
 */
void ADCUI_StructInit(ADCUI_InitTypeDef* ADCUI_InitStruct)
{
    ADCUI_InitStruct->ADCUI_DataResol              = ADCUI_DATA_RESOL_24BIT;
    ADCUI_InitStruct->ADCUI_ZeroCrossLowPassFilter = ADCUI_ZXLPF_FILTER_DISABLE;
    ADCUI_InitStruct->ADCUI_PeriodLength           = ADCUI_PER_LENGTH_1;
    ADCUI_InitStruct->ADCUI_ActivePowerNoLoad      = ADCUI_APNOLOAD_FULL;
    ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad    = ADCUI_VARNOLOAD_FULL;
    ADCUI_InitStruct->ADCUI_FullPowerNoLoad        = ADCUI_VANOLOAD_FULL;
    ADCUI_InitStruct->ADCUI_FreqVEnable            = DISABLE;
    ADCUI_InitStruct->ADCUI_VRefConfig             = ADCUI_REFERENCE_VOLTAGE_INTERNAL;
    ADCUI_InitStruct->ADCUI_VRefBufUse             = ADCUI_USE_VREF_BUF;
#if defined(USE_MDR32F21QI)
    ADCUI_InitStruct->ADCUI_ChopEnable           = DISABLE;
    ADCUI_InitStruct->ADCUI_ChopperFreqPrescaler = ADCUI_CHOPPER_FREQUENCY_DIV_2;
#endif
    ADCUI_InitStruct->ADCUI_ZeroCrossUpdateRMS    = ADCUI_REG_CONTINUOUS_UPDATE;
    ADCUI_InitStruct->ADCUI_IBoostEnable          = DISABLE;
    ADCUI_InitStruct->ADCUI_Divider               = ADCUI_OVERSAMPLING_DIV_256;
    ADCUI_InitStruct->ADCUI_VoltageDropLevel      = 0;
    ADCUI_InitStruct->ADCUI_VoltageHalfCyclesDrop = 0;
    ADCUI_InitStruct->ADCUI_ZeroCrossTimeOut      = 0;
}

/**
 * @brief  Initializes the ADCUI peripheral according to
 *         the specified parameters in the ADCUI_InitStruct.
 * @param  ADCUI_InitStruct: pointer to a @ref ADCUI_InitTypeDef structure that
 *         contains the configuration information for the specified ADCUI peripheral.
 * @retval None.
 */
void ADCUI_Init(ADCUI_InitTypeDef* ADCUI_InitStruct)
{
    uint32_t TempCTRL1, TempCTRL2, TempCTRL3;

    /* Check the parameters */

    assert_param(IS_ADCUI_DATA_RESOL(ADCUI_InitStruct->ADCUI_DataResol));
    assert_param(IS_ZXLPF_FILTER(ADCUI_InitStruct->ADCUI_ZeroCrossLowPassFilter));
    assert_param(IS_ADCUI_PER_LENGTH(ADCUI_InitStruct->ADCUI_PeriodLength));
    assert_param(IS_ADCUI_APNOLOAD(ADCUI_InitStruct->ADCUI_ActivePowerNoLoad));
    assert_param(IS_ADCUI_VARNOLOAD(ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad));
    assert_param(IS_ADCUI_VANOLOAD(ADCUI_InitStruct->ADCUI_FullPowerNoLoad));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_InitStruct->ADCUI_FreqVEnable));
    assert_param(IS_ADCUI_REFERENCE_VOLTAGE(ADCUI_InitStruct->ADCUI_VRefConfig));
    assert_param(IS_ADCUI_BUFFER_VREF_USE(ADCUI_InitStruct->ADCUI_VRefBufUse));
    assert_param(IS_ADCUI_ZXRMS_REG_UPDATE(ADCUI_InitStruct->ADCUI_ZeroCrossUpdateRMS));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_InitStruct->ADCUI_IBoostEnable));
    assert_param(IS_ADCUI_OSR_COF(ADCUI_InitStruct->ADCUI_Divider));
    assert_param(IS_ADCUI_SAGLVL(ADCUI_InitStruct->ADCUI_VoltageDropLevel));
    assert_param(IS_ADCUI_SAGCYC(ADCUI_InitStruct->ADCUI_VoltageHalfCyclesDrop));
    assert_param(IS_ADCUI_ZXTOUT(ADCUI_InitStruct->ADCUI_ZeroCrossTimeOut));
#if defined(USE_MDR32F21QI)
    assert_param(IS_ADCUI_CHOPPER_FREQUENCY_PRESCALER(ADCUI_InitStruct->ADCUI_ChopperFreqPrescaler));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_InitStruct->ADCUI_ChopEnable));
#endif

    /* Config the ADCUI control1 register */

    TempCTRL1 = ((uint32_t)ADCUI_InitStruct->ADCUI_DataResol) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_ZeroCrossLowPassFilter) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_PeriodLength) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_ActivePowerNoLoad) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_FullPowerNoLoad) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_FreqVEnable << ADCUI_CTRL1_FREQSEL_Pos) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_VRefConfig) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_VRefBufUse) |
#if defined(USE_MDR32F21QI)
                ((uint32_t)ADCUI_InitStruct->ADCUI_ChopEnable << ADCUI_CTRL1_CHOP_EN_Pos) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_ChopperFreqPrescaler) |
#endif
                ((uint32_t)ADCUI_InitStruct->ADCUI_ZeroCrossUpdateRMS) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_IBoostEnable << ADCUI_CTRL1_IBOOST_Pos) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_Divider << ADCUI_CTRL1_OSR_CONF_Pos);

    /* Write to ADCUI control1 register */
    MDR_ADCUI->CTRL1 = TempCTRL1;

    /* Config the ADCUI control2 register */
    TempCTRL2 = ((uint32_t)ADCUI_InitStruct->ADCUI_VoltageDropLevel << ADCUI_CTRL2_SAGLVL_Pos) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_VoltageHalfCyclesDrop << ADCUI_CTRL2_SAGCYC_Pos);

    /* Write to ADCUI control2 register */
    MDR_ADCUI->CTRL2 = TempCTRL2;

    TempCTRL3 = ((uint32_t)ADCUI_InitStruct->ADCUI_ZeroCrossTimeOut << ADCUI_CTRL3_ZXTOUT_Pos);

    /* Write to ADCUI control3 register */
    MDR_ADCUI->CTRL3 = TempCTRL3;
}

/**
 * @brief  Resetting the digital part of the ADC blocks.
 * @param  NewState: new state of the ADC digital part.
 *         This parameter can be a value of @ref FunctionalState.
 * @retval None.
 */
void ADCUI_ResetDigital(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == ENABLE) {
        MDR_ADCUI->CTRL1 |= ADCUI_CTRL1_RESET_DIG;
    } else {
        MDR_ADCUI->CTRL1 &= ~ADCUI_CTRL1_RESET_DIG;
    }
}

/**
 * @brief Initializes the ADCUI unit Fx peripheral according to
 *        the specified parameters in the ADCUI_FxUnitInitStruct.
 * @param UnitNumber - @ref ADCUI_Unit_TypeDef - the number of the initialized channel.
 * @param ADCUI_FxUnitInitStruct: pointer to a @ref ADCUI_FxUnit_InitTypeDef
 *        structure that contains the configuration information.
 * @retval None.
 */
void ADCUI_Fx_Init(ADCUI_Unit_TypeDef UnitNumber, ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct)
{
    uint32_t TempFxCTR, TempFxMD0;

    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_INT_STATE(ADCUI_FxUnitInitStruct->ADCUI_Fx_IntegratorEnable));
    assert_param(IS_ADCUI_INT_STATE(ADCUI_FxUnitInitStruct->ADCUI_F0_I3IntegratorEnable));
    assert_param(IS_ADCUI_VASEL(ADCUI_FxUnitInitStruct->ADCUI_SourceRegFullPower));
    assert_param(IS_ADCUI_GAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain));
    assert_param(IS_ADCUI_GAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain));
    assert_param(IS_ADCUI_FXPHASE(ADCUI_FxUnitInitStruct->ADCUI_Fx_PhaseShift));
    assert_param(IS_ADCUI_GAIN(ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain));
    assert_param(IS_ADCUI_FXIRMSOS(ADCUI_FxUnitInitStruct->ADCUI_Fx_IRMSCalibration));
    assert_param(IS_ADCUI_VDAT_SOURCE(ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceVDAT));
    assert_param(IS_ADCUI_IDAT_SOURCE(ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceIDAT));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBIGainEnable));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBVGainEnable));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_FxUnitInitStruct->ADCUI_F0_6dBI3GainEnable));
    assert_param(IS_ADCUI_F0I3SEL_SELECT(ADCUI_FxUnitInitStruct->ADCUI_F0_I3SelectDataFilter));
    assert_param(IS_ADCUI_CHANNELI_SELECT(ADCUI_FxUnitInitStruct->ADCUI_F0_IChannelSelect));

#if defined(USE_MDR32F21QI)

    TempFxCTR = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IntegratorEnable << ADCUI_FxCTR_FxI0NTEN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3IntegratorEnable << ADCUI_FxCTR_FxI3NTEN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_SourceRegFullPower) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain << ADCUI_FxCTR_FxIGAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain << ADCUI_FxCTR_FxVGAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_PhaseShift << ADCUI_FxCTR_FxVPHASE_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain << ADCUI_FxCTR_FxI3GAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IRMSCalibration << ADCUI_FxCTR_FxIRMSOS_Pos);

    TempFxMD0 = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceVDAT) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceIDAT << ADCUI_FxMD0_FxISEL_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBIGainEnable << ADCUI_FxMD0_IxGAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBVGainEnable << ADCUI_FxMD0_VxGAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_6dBI3GainEnable << ADCUI_FxMD0_I3GAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3SelectDataFilter) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_IChannelSelect << ADCUI_FxMD0_FxSEL_I_CH_Pos);

#elif defined(USE_MDR32F23QI)

    TempFxCTR = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IntegratorEnable << ADCUI_F0CTR_F0I0NTEN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3IntegratorEnable << ADCUI_F0CTR_F0I3NTEN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_SourceRegFullPower) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain << ADCUI_F0CTR_F0I0GAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain << ADCUI_F0CTR_F0VGAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_PhaseShift << ADCUI_F0CTR_F0VPHASE_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain << ADCUI_F0CTR_F0I3GAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IRMSCalibration << ADCUI_F0CTR_F0IRMSOS_Pos);

    TempFxMD0 = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceVDAT) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceIDAT << ADCUI_F0MD0_F0ISEL_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBIGainEnable << ADCUI_F0MD0_I0GAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBVGainEnable << ADCUI_F0MD0_V0GAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_6dBI3GainEnable << ADCUI_F0MD0_I3GAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3SelectDataFilter) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_IChannelSelect << ADCUI_F0MD0_F0SEL_I_CH_Pos);

#endif

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            MDR_ADCUI->F0CTR = TempFxCTR;
            MDR_ADCUI->F0MD0 = TempFxMD0;
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            MDR_ADCUI->F1CTR = TempFxCTR;
            MDR_ADCUI->F1MD0 = TempFxMD0;
            break;
        case ADCUI_F2_UNIT:
            MDR_ADCUI->F2CTR = TempFxCTR;
            MDR_ADCUI->F2MD0 = TempFxMD0;
            break;
#endif
    }
}

/**
 * @brief Fills each ADCUI_FxUnitInitStruct member with its default value.
 * @param ADCUI_FxUnitInitStruct: pointer to a @ref ADCUI_FxUnit_InitTypeDef
 *        structure which will be initialized.
 * @retval None.
 */
void ADCUI_Fx_StructInit(ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct)
{
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IntegratorEnable   = ADCUI_INT_DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3IntegratorEnable = ADCUI_INT_DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_SourceRegFullPower    = ADCUI_FULL_ENERGY;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain              = ADCUI_GAIN_0dB;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain              = ADCUI_GAIN_0dB;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_PhaseShift         = 0;
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain             = ADCUI_GAIN_0dB;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IRMSCalibration    = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceVDAT         = ADCUI_Fx_U_VDAT;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceIDAT         = ADCUI_Fx_I_IDAT;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBIGainEnable     = DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBVGainEnable     = DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_F0_6dBI3GainEnable    = DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3SelectDataFilter = ADCUI_F0I3SEL_AFTER_FILTER;
    ADCUI_FxUnitInitStruct->ADCUI_F0_IChannelSelect     = ADCUI_F0_I_CH_AUTO;
}

/**
 * @brief  ADCUI Channel configuaration.
 * @param  Channels: specifies the ADCUI channel to be enabled or disabled.
 *         This parameter can be any combination of @ref ADCUI_Channel_TypeDef values.
 * @param  NewState: new state of the specified ADCUI Channels.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None.
 */
void ADCUI_ChannelConfig(uint32_t Channels, FunctionalState NewState)
{
    /* Check the parameters */

    assert_param(IS_ADCUI_CHANNELS(Channels));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_ADCUI->CTRL1 |= Channels;
    } else {
        MDR_ADCUI->CTRL1 &= ~Channels;
    }
}

/**
 * @brief  Returns the ADCUI result of specific channel.
 * @param  ChannelNumber - @ref ADCUI_Channel_TypeDef - the channel number.
 * @retval ADCUI Result Register value for the specified channel.
 */
uint32_t ADCUI_GetResult(ADCUI_Channel_TypeDef ChannelNumber)
{
    uint32_t ResultChannel;

    /* Check the parameters */
    assert_param(IS_ADCUI_CHANNEL(ChannelNumber));

    switch (ChannelNumber) {
        case ADCUI_CH_F0_I0:
            ResultChannel = MDR_ADCUI->F0I0DAT;
            break;
        case ADCUI_CH_F0_V0:
            ResultChannel = MDR_ADCUI->F0VDAT;
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_CH_F1_I1:
            ResultChannel = MDR_ADCUI->F1IDAT;
            break;
        case ADCUI_CH_F1_V1:
            ResultChannel = MDR_ADCUI->F1VDAT;
            break;
        case ADCUI_CH_F2_I2:
            ResultChannel = MDR_ADCUI->F2IDAT;
            break;
        case ADCUI_CH_F2_V2:
            ResultChannel = MDR_ADCUI->F2VDAT;
            break;
#endif
        case ADCUI_CH_F0_I3:
            ResultChannel = MDR_ADCUI->F0I3DAT;
            break;
    }
    return (ResultChannel);
}

/**
 * @brief  Reset certain flags in one of the ADCUI blocks.
 * @param  UnitNumber: Select the Fx unit.
 *         This parameter can be one of the following values @ref ADCUI_Unit_TypeDef.
 * @param  Flags: specifies the flags to clear.
 *         This parameter can be one of the @ref ADCUI_Flags_TypeDef values.
 * @retval None
 */
void ADCUI_ClearFlags(ADCUI_Unit_TypeDef UnitNumber, uint32_t Flags)
{
    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_FLAG(Flags));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            MDR_ADCUI->F0STAT = MDR_ADCUI->F0STAT & ~Flags;
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            MDR_ADCUI->F1STAT = MDR_ADCUI->F1STAT & ~Flags;
            break;
        case ADCUI_F2_UNIT:
            MDR_ADCUI->F2STAT = MDR_ADCUI->F0STAT & ~Flags;
            break;
#endif
    }
}

/**
 * @brief  Checks whether the specified ADCUI flag is set or not.
 * @param  UnitNumber: Select the Fx unit.
 *         This parameter can be one of the following values @ref ADCUI_Unit_TypeDef.
 * @param  ADCUI_Flag: specifies the flag to check.
 *         This parameter can be one of the @ref ADCUI_Flags_TypeDef values.
 * @retval @ref FlagStatus - The state of ADCUI flag (SET or RESET).
 */
FlagStatus ADCUI_GetFlagStatus(ADCUI_Unit_TypeDef UnitNumber, ADCUI_Flags_TypeDef ADCUI_Flag)
{
    FlagStatus BitStatus;

    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_FLAG(ADCUI_Flag));

    switch (UnitNumber) {

        case ADCUI_F0_UNIT:
            if (MDR_ADCUI->F0STAT & ADCUI_Flag) {
                BitStatus = SET;
            } else {
                BitStatus = RESET;
            }
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            if (MDR_ADCUI->F1STAT & ADCUI_Flag) {
                BitStatus = SET;
            } else {
                BitStatus = RESET;
            }
            break;
        case ADCUI_F2_UNIT:
            if (MDR_ADCUI->F2STAT & ADCUI_Flag) {
                BitStatus = SET;
            } else {
                BitStatus = RESET;
            }
            break;
#endif
    }
    return (BitStatus);
}

/**
 * @brief  Returns the ADCUI Fx unit Status Flags combined value.
 * @param  UnitNumber: Select the Fx unit.
 *         This parameter can be one of the following values @ref ADCUI_Unit_TypeDef.
 * @retval The ADCUI Status Flags combined value.
 */
uint32_t ADCUI_GetStatus(ADCUI_Unit_TypeDef UnitNumber)
{
    uint32_t StatusFlags;

    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            StatusFlags = MDR_ADCUI->F0STAT & ADCUI_FLAGS_MASK;
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            StatusFlags = MDR_ADCUI->F1STAT & ADCUI_FLAGS_MASK;
            break;
        case ADCUI_F2_UNIT:
            StatusFlags = MDR_ADCUI->F2STAT & ADCUI_FLAGS_MASK;
            break;
#endif
    }
    return (StatusFlags);
}

/**
 * @brief  Reset certain IT flags in one of the ADCUI blocks.
 * @param  UnitNumber: Select the Fx unit.
 *         This parameter can be one of the following values @ref ADCUI_Unit_TypeDef.
 * @param  ITFlags: specifies the IT flags to clear.
 *         This parameter can be one of the @ref ADCUI_IT_TypeDef values.
 * @retval None
 */
void ADCUI_ClearITFlags(ADCUI_Unit_TypeDef UnitNumber, uint32_t ITFlags)
{
    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_FLAG(ITFlags));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            MDR_ADCUI->F0STAT = MDR_ADCUI->F0STAT & ~ITFlags;
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            MDR_ADCUI->F1STAT = MDR_ADCUI->F1STAT & ~ITFlags;
            break;
        case ADCUI_F2_UNIT:
            MDR_ADCUI->F2STAT = MDR_ADCUI->F0STAT & ~ITFlags;
            break;
#endif
    }
}

/**
 * @brief  Checks whether the specified ADCUI IT flag is set or not.
 * @param  UnitNumber: Select the Fx unit.
 *         This parameter can be one of the following values @ref ADCUI_Unit_TypeDef.
 * @param  ADCUI_ITFlag: specifies the IT flag to check.
 *         This parameter can be one of the @ref ADCUI_IT_TypeDef values.
 * @retval @ref FlagStatus - The state of ADCUI IT flag (SET or RESET).
 */
FlagStatus ADCUI_GetITFlagStatus(ADCUI_Unit_TypeDef UnitNumber, ADCUI_IT_TypeDef ADCUI_ITFlag)
{
    FlagStatus BitStatus;

    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_FLAG(ADCUI_ITFlag));

    switch (UnitNumber) {

        case ADCUI_F0_UNIT:
            if (MDR_ADCUI->F0STAT & ADCUI_ITFlag) {
                BitStatus = SET;
            } else {
                BitStatus = RESET;
            }
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            if (MDR_ADCUI->F1STAT & ADCUI_ITFlag) {
                BitStatus = SET;
            } else {
                BitStatus = RESET;
            }
            break;
        case ADCUI_F2_UNIT:
            if (MDR_ADCUI->F2STAT & ADCUI_ITFlag) {
                BitStatus = SET;
            } else {
                BitStatus = RESET;
            }
            break;
#endif
    }
    return (BitStatus);
}

/**
 * @brief  Returns the ADCUI Fx unit Status IT Flags combined value.
 * @param  UnitNumber: Select the Fx unit.
 *         This parameter can be one of the following values @ref ADCUI_Unit_TypeDef.
 * @retval The ADCUI Status IT Flags combined value.
 */
uint32_t ADCUI_GetITStatus(ADCUI_Unit_TypeDef UnitNumber)
{
    uint32_t StatusITFlags;

    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            StatusITFlags = MDR_ADCUI->F0STAT & ADCUI_IT_MASK;
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            StatusITFlags = MDR_ADCUI->F1STAT & ADCUI_IT_MASK;
            break;
        case ADCUI_F2_UNIT:
            StatusITFlags = MDR_ADCUI->F2STAT & ADCUI_IT_MASK;
            break;
#endif
    }
    return (StatusITFlags);
}

/**
 * @brief  Enables or disables the ADCUI interrupts.
 * @param  UnitNumber: Select the Fx unit.
 *         This parameter can be one of the following values @ref ADCUI_Unit_TypeDef.
 * @param  ADCUI_IT: specifies the ADCUI interrupt sources to be enabled or disabled.
 *         This parameter can be any combination of:
 *           @arg ADCUI_Fx_IT_VF_EMP.
 *           @arg ADCUI_Fx_IT_VF_FLL.
 *           @arg ADCUI_Fx_IT_VF_OVR.
 *           @arg ADCUI_Fx_IT_IF_EMP.
 *           @arg ADCUI_Fx_IT_IF_FLL.
 *           @arg ADCUI_Fx_IT_IF_OVR.
 *           @arg ADCUI_Fx_IT_SAGF.
 *           @arg ADCUI_Fx_IT_PEAKVF.
 *           @arg ADCUI_Fx_IT_PEAKIF.
 *           @arg ADCUI_Fx_IT_WATTOVP.
 *           @arg ADCUI_Fx_IT_VAROVP.
 *           @arg ADCUI_Fx_IT_VAOV.
 *           @arg ADCUI_Fx_IT_ZXTOF.
 *           @arg ADCUI_Fx_IT_FAULTCON.
 *           @arg ADCUI_Fx_IT_APSIGN.
 *           @arg ADCUI_Fx_IT_APNLDFL.
 *           @arg ADCUI_Fx_IT_VARSIGN.
 *           @arg ADCUI_Fx_IT_VARNLDFL.
 *           @arg ADCUI_Fx_IT_VANLDFL.
 *           @arg ADCUI_Fx_IT_ZEROCRS.
 *           @arg ADCUI_Fx_IT_C3IF_EMP.
 *           @arg ADCUI_Fx_IT_C3IF_FLL.
 *           @arg ADCUI_Fx_IT_C3IF_OVR.
 *           @arg ADCUI_Fx_IT_WATTOVN.
 *           @arg ADCUI_Fx_IT_VAROVN.
 * @param  NewState - @ref FunctionalState - new state of the ADCUI interrupts.
 * @retval None.
 */
void ADCUI_ITConfig(ADCUI_Unit_TypeDef UnitNumber, uint32_t ADCUI_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_ITS(ADCUI_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Config IT state */
    switch (UnitNumber) {

        case ADCUI_F0_UNIT:
            if (NewState != DISABLE) {
                MDR_ADCUI->F0MASK |= ADCUI_IT;
            } else {
                MDR_ADCUI->F0MASK &= ~ADCUI_IT;
            }
            break;
#if defined(USE_MDR32F21QI)
        case ADCUI_F1_UNIT:
            if (NewState != DISABLE) {
                MDR_ADCUI->F1MASK |= ADCUI_IT;
            } else {
                MDR_ADCUI->F1MASK &= ~ADCUI_IT;
            }
            break;
        case ADCUI_F2_UNIT:
            if (NewState != DISABLE) {
                MDR_ADCUI->F2MASK |= ADCUI_IT;
            } else {
                MDR_ADCUI->F2MASK &= ~ADCUI_IT;
            }
            break;
#endif
    }
}

/** @} */ /* End of group ADCUI_Exported_Functions */

/** @} */ /* End of group ADCUI */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_adcui.c */

