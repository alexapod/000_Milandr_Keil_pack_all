/**
 *******************************************************************************
 * @file    MDR32VF0xI_adcui.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    20/05/2025
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
#include "MDR32VF0xI_adcui.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @defgroup ADCUI ADCUI
 * @{
 */

/** @defgroup ADCUI_Private_Defines ADCUI Private Defines
 * @{
 */

#define IS_ADCUI_SAGLVL(SAGLVL)     ((SAGLVL) <= 0xFFFF)
#define IS_ADCUI_SAGCYC(SAGCYC)     ((SAGCYC) <= 0xFF)
#define IS_ADCUI_ZXTOUT(ZXTOUT)     ((ZXTOUT) <= 0xFFF)

#define IS_ADCUI_FXPHASE(PHASE)     (((PHASE) >= -126) && ((PHASE) <= 127))
#define IS_ADCUI_FXVIRMSOS(UIRMSOS) ((UIRMSOS) <= 0xFFF)

#define IS_ADCUI_FXPWRGAIN(PWRGAIN) ((PWRGAIN) <= 0xFFF)
#define IS_ADCUI_FXPWROS(PWROS)     ((PWROS) <= 0xFFFF)

#define IS_ADCUI_FXVIPKLVL(LVL)     ((LVL) <= 0xFFFF)

#if defined(USE_MDR32F02_REV_1X)
#define IS_ADCUI_CCAL_GAIN(GAIN) ((GAIN) <= 0xFFF)
#endif

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define IS_ADCUI_CCAL_GAIN(GAIN) ((GAIN) <= 0xFFFF)
#endif

#define DEINIT_FLAGS0 (ADCUI_F0STAT_F0VF_OVR |  \
                       ADCUI_F0STAT_F0IF_OVR |  \
                       ADCUI_F0STAT_F0SAGF |    \
                       ADCUI_F0STAT_F0PEAKVF |  \
                       ADCUI_F0STAT_F0PEAKIF |  \
                       ADCUI_F0STAT_F0WATTOVP | \
                       ADCUI_F0STAT_F0VAROVP |  \
                       ADCUI_F0STAT_F0VAOV |    \
                       ADCUI_F0STAT_F0ZXTOF |   \
                       ADCUI_F0STAT_F0APSIGN |  \
                       ADCUI_F0STAT_F0VARSIGN | \
                       ADCUI_F0STAT_F0ZEROCRS | \
                       ADCUI_F0STAT_C3IF_OVR |  \
                       ADCUI_F0STAT_F0WATTOVN | \
                       ADCUI_F0STAT_F0VAROVN)

#define DEINIT_FLAGSx (ADCUI_FxSTAT_FxVF_OVR |  \
                       ADCUI_FxSTAT_FxIF_OVR |  \
                       ADCUI_FxSTAT_FxSAGF |    \
                       ADCUI_FxSTAT_FxPEAKVF |  \
                       ADCUI_FxSTAT_FxPEAKIF |  \
                       ADCUI_FxSTAT_FxWATTOVP | \
                       ADCUI_FxSTAT_FxVAROVP |  \
                       ADCUI_FxSTAT_FxVAOV |    \
                       ADCUI_FxSTAT_FxZXTOF |   \
                       ADCUI_FxSTAT_FxAPSIGN |  \
                       ADCUI_FxSTAT_FxVARSIGN | \
                       ADCUI_FxSTAT_FxZEROCRS | \
                       ADCUI_FxSTAT_FxWATTOVN | \
                       ADCUI_FxSTAT_FxVAROVN)

/** @} */ /* End of the group ADCUI_Private_Defines */

/** @defgroup ADCUI_Exported_Functions ADCUI Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the ADCUI peripheral registers to their default reset values.
 * @param  None.
 * @return None.
 */
void ADCUI_DeInit(void)
{
    MDR_ADCUI->CTRL1 = 0;
    MDR_ADCUI->CTRL2 = 0xFFFFFF;
    MDR_ADCUI->CTRL3 = 0xFF;

    MDR_ADCUI->F0CTR   = 0;
    MDR_ADCUI->F0WC    = 0;
    MDR_ADCUI->F0VC    = 0;
    MDR_ADCUI->F0AC    = 0;
    MDR_ADCUI->F0MD0   = 0;
    MDR_ADCUI->F0MD1   = 0;
    MDR_ADCUI->F0VPEAK = 0;
    MDR_ADCUI->F0IPEAK = 0;
    MDR_ADCUI->F0STAT  = DEINIT_FLAGS0;
    MDR_ADCUI->F0MASK  = 0;

    MDR_ADCUI->F1CTR   = 0;
    MDR_ADCUI->F1WC    = 0;
    MDR_ADCUI->F1VC    = 0;
    MDR_ADCUI->F1AC    = 0;
    MDR_ADCUI->F1MD0   = 0;
    MDR_ADCUI->F1MD1   = 0;
    MDR_ADCUI->F1VPEAK = 0;
    MDR_ADCUI->F1IPEAK = 0;
    MDR_ADCUI->F1STAT  = DEINIT_FLAGSx;
    MDR_ADCUI->F1MASK  = 0;

    MDR_ADCUI->F2CTR   = 0;
    MDR_ADCUI->F2WC    = 0;
    MDR_ADCUI->F2VC    = 0;
    MDR_ADCUI->F2AC    = 0;
    MDR_ADCUI->F2MD0   = 0;
    MDR_ADCUI->F2MD1   = 0;
    MDR_ADCUI->F2VPEAK = 0;
    MDR_ADCUI->F2IPEAK = 0;
    MDR_ADCUI->F2STAT  = DEINIT_FLAGSx;
    MDR_ADCUI->F2MASK  = 0;

    MDR_ADCUI->CCAL1 = 0;
    MDR_ADCUI->CCAL2 = 0;
    MDR_ADCUI->CCAL3 = 0;
    MDR_ADCUI->CCAL4 = 0;

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    MDR_ADCUI->LOAD = 0;
#endif

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    MDR_ADCUI->MSC       = 0;
    MDR_ADCUI->FILTERCFG = (0x802 << ADCUI_FILTERCFG_CHPF_COEFF_Pos) |
                           (0x803 << ADCUI_FILTERCFG_CLRMS_COEFF_Pos);
    MDR_ADCUI->CLKPHASE1 = (0x200 << ADCUI_CLKPHASE1_I0PHASE_Pos) |
                           (0x200 << ADCUI_CLKPHASE1_I1PHASE_Pos) |
                           (0x200 << ADCUI_CLKPHASE1_I2PHASE_Pos);
    MDR_ADCUI->CLKPHASE2 = (0x200 << ADCUI_CLKPHASE2_I3PHASE_Pos);
#endif
}

/**
 * @brief  Fill each ADCUI_InitStruct member with its default value.
 * @param  ADCUI_InitStruct: The pointer to the @ref ADCUI_InitTypeDef structure
 *         which will be initialized.
 * @return None.
 */
void ADCUI_StructInit(ADCUI_InitTypeDef* ADCUI_InitStruct)
{
    ADCUI_InitStruct->ADCUI_DataResol              = ADCUI_DATA_RESOL_16BIT;
    ADCUI_InitStruct->ADCUI_ZeroCrossLowPassFilter = ADCUI_ZXLPF_FILTER_ENABLE;
    ADCUI_InitStruct->ADCUI_PeriodLength           = ADCUI_PER_LENGTH_1;
    ADCUI_InitStruct->ADCUI_ActivePowerNoLoad      = ADCUI_APNOLOAD_FULL;
    ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad    = ADCUI_VARNOLOAD_FULL;
    ADCUI_InitStruct->ADCUI_FullPowerNoLoad        = ADCUI_VANOLOAD_FULL;
    ADCUI_InitStruct->ADCUI_FreqVEnable            = DISABLE;
    ADCUI_InitStruct->ADCUI_VRefConfig             = ADCUI_REFERENCE_VOLTAGE_EXTERNAL;
    ADCUI_InitStruct->ADCUI_ZeroCrossUpdateRMS     = ADCUI_REG_CONTINUOUS_UPDATE;
    ADCUI_InitStruct->ADCUI_Divider                = ADCUI_OVERSAMPLING_DIV_256;
    ADCUI_InitStruct->ADCUI_VoltageDropLevel       = 0xFFFF;
    ADCUI_InitStruct->ADCUI_VoltageHalfCyclesDrop  = 0xFF;
    ADCUI_InitStruct->ADCUI_ZeroCrossTimeOut       = 0xFFF;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_InitStruct->ADCUI_ClockFrequency = ADCUI_CLK_FREQUENCY_4MHz;
    ADCUI_InitStruct->ADCUI_ChopperPeriod  = ADCUI_CHOPPER_PERIOD_256;
#endif
}

/**
 * @brief  Initialize the ADCUI peripheral according to
 *         the specified parameters in the ADCUI_InitStruct.
 * @param  ADCUI_InitStruct: The pointer to a @ref ADCUI_InitTypeDef structure
 *         that contains the configuration information for the specified ADCUI peripheral.
 * @return None.
 */
void ADCUI_Init(const ADCUI_InitTypeDef* ADCUI_InitStruct)
{
    uint32_t TempCTRL1, TempCTRL2, TempCTRL3;

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    uint32_t TempLOAD = 0;
#endif

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    uint32_t TempFILTERCFG, TempCLKPHASE1;
#endif

    /* Check the parameters. */
    assert_param(IS_ADCUI_DATA_RESOL(ADCUI_InitStruct->ADCUI_DataResol));
    assert_param(IS_ZXLPF_FILTER(ADCUI_InitStruct->ADCUI_ZeroCrossLowPassFilter));
    assert_param(IS_ADCUI_PER_LENGTH(ADCUI_InitStruct->ADCUI_PeriodLength));
    assert_param(IS_ADCUI_APNOLOAD(ADCUI_InitStruct->ADCUI_ActivePowerNoLoad));
    assert_param(IS_ADCUI_VARNOLOAD(ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad));
    assert_param(IS_ADCUI_VANOLOAD(ADCUI_InitStruct->ADCUI_FullPowerNoLoad));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_InitStruct->ADCUI_FreqVEnable));
    assert_param(IS_ADCUI_REFERENCE_VOLTAGE(ADCUI_InitStruct->ADCUI_VRefConfig));
    assert_param(IS_ADCUI_ZXRMS_REG_UPDATE(ADCUI_InitStruct->ADCUI_ZeroCrossUpdateRMS));
    assert_param(IS_ADCUI_OSR_COF(ADCUI_InitStruct->ADCUI_Divider));
    assert_param(IS_ADCUI_SAGLVL(ADCUI_InitStruct->ADCUI_VoltageDropLevel));
    assert_param(IS_ADCUI_SAGCYC(ADCUI_InitStruct->ADCUI_VoltageHalfCyclesDrop));
    assert_param(IS_ADCUI_ZXTOUT(ADCUI_InitStruct->ADCUI_ZeroCrossTimeOut));
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    assert_param(IS_ADCUI_CLK_FREQUENCY(ADCUI_InitStruct->ADCUI_ClockFrequency));
    assert_param(IS_ADCUI_CHOPPER_PERIOD(ADCUI_InitStruct->ADCUI_ChopperPeriod));
    assert_param(IS_ADCUI_CLK_OSR_VALID(ADCUI_InitStruct->ADCUI_ClockFrequency, ADCUI_InitStruct->ADCUI_Divider));
#endif

    /* Config the ADCUI control1 register. */
    TempCTRL1 = ((uint32_t)ADCUI_InitStruct->ADCUI_DataResol) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_ZeroCrossLowPassFilter) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_PeriodLength) |
#if defined(USE_MDR32F02_REV_1X)
                ((uint32_t)ADCUI_InitStruct->ADCUI_ActivePowerNoLoad) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_FullPowerNoLoad) |
#endif
                ((uint32_t)ADCUI_InitStruct->ADCUI_FreqVEnable << ADCUI_CTRL1_FREQSEL_Pos) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_VRefConfig) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_ZeroCrossUpdateRMS) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_Divider);

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    if ((((uint32_t)ADCUI_InitStruct->ADCUI_ActivePowerNoLoad) & ADCUI_LOAD_APNOLOAD_Msk) != 0) {
        TempLOAD |= ((uint32_t)ADCUI_InitStruct->ADCUI_ActivePowerNoLoad);
    } else {
        TempCTRL1 |= ((uint32_t)ADCUI_InitStruct->ADCUI_ActivePowerNoLoad);
    }
    if ((((uint32_t)ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad) & ADCUI_LOAD_VARNOLOAD_Msk) != 0) {
        TempLOAD |= ((uint32_t)ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad);
    } else {
        TempCTRL1 |= ((uint32_t)ADCUI_InitStruct->ADCUI_ReactivePowerNoLoad);
    }
    if ((((uint32_t)ADCUI_InitStruct->ADCUI_FullPowerNoLoad) &
         (ADCUI_LOAD_VANOLOAD_Msk & ~ADCUI_CTRL1_VANOLOAD_Msk)) != 0) {
        TempLOAD |= ((uint32_t)ADCUI_InitStruct->ADCUI_FullPowerNoLoad);
    } else {
        TempCTRL1 |= ((uint32_t)ADCUI_InitStruct->ADCUI_FullPowerNoLoad);
    }
    MDR_ADCUI->LOAD = TempLOAD;
#endif

    /* Write to the ADCUI control1 register. */
    MDR_ADCUI->CTRL1 = TempCTRL1;

    /* Config the ADCUI control2 register. */
    TempCTRL2 = ((uint32_t)ADCUI_InitStruct->ADCUI_VoltageDropLevel << ADCUI_CTRL2_SAGLVL_Pos) |
                ((uint32_t)ADCUI_InitStruct->ADCUI_VoltageHalfCyclesDrop << ADCUI_CTRL2_SAGCYC_Pos);

    /* Write to the ADCUI control2 register. */
    MDR_ADCUI->CTRL2 = TempCTRL2;

    /* Config the ADCUI control3 register. */
    TempCTRL3 = ((uint32_t)ADCUI_InitStruct->ADCUI_ZeroCrossTimeOut << ADCUI_CTRL3_ZXTOUT_Pos);

    /* Write to the ADCUI control3 register. */
    MDR_ADCUI->CTRL3 = TempCTRL3;

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    /* Config the ADCUI FILTERCFG register. */
    TempFILTERCFG = ((uint32_t)ADCUI_InitStruct->ADCUI_ChopperPeriod);

    /* Write to the ADCUI FILTERCFG register. */
    MDR_ADCUI->FILTERCFG |= TempFILTERCFG;

    /* Config the ADCUI CLKPHASE1 register. */
    TempCLKPHASE1 = ((uint32_t)ADCUI_InitStruct->ADCUI_ClockFrequency);

    /* Write to the ADCUI CLKPHASE1 register. */
    MDR_ADCUI->CLKPHASE1 |= TempCLKPHASE1;
#endif
}

/**
 * @brief  Reset the digital unit of the ADCUI blocks.
 * @param  NewState: @ref FunctionalState - a new state of the ADC digital unit.
 * @return None.
 */
void ADCUI_ResetDigital(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_ADCUI->CTRL1 |= ADCUI_CTRL1_RESET_DIG;
    } else {
        MDR_ADCUI->CTRL1 &= ~ADCUI_CTRL1_RESET_DIG;
    }
}

/**
 * @brief Initialize the ADCUI Fx peripheral according to
 *        the specified parameters in the ADCUI_FxUnitInitStruct.
 * @param UnitNumber: @ref ADCUI_Unit_TypeDef - a number of the initialized channel.
 * @param ADCUI_FxUnitInitStruct: The pointer to a @ref ADCUI_FxUnit_InitTypeDef
 *        structure that contains the configuration information.
 * @return None.
 */
void ADCUI_Fx_Init(ADCUI_Unit_TypeDef UnitNumber, const ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct)
{
    uint32_t TempFxCTR, TempFxMD0, TempFxWC, TempFxVC, TempFxAC, TempFxMD1, TempCCALx, TempCCAL4;

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    uint32_t TempMSC = 0;
#endif

    /* Check the parameters. */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_INT_STATE(ADCUI_FxUnitInitStruct->ADCUI_Fx_IntegratorEnable));
    assert_param(IS_ADCUI_INT_STATE(ADCUI_FxUnitInitStruct->ADCUI_F0_I3IntegratorEnable));
    assert_param(IS_ADCUI_VASEL(ADCUI_FxUnitInitStruct->ADCUI_SourceRegFullPower));
    assert_param(IS_ADCUI_IGAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain));
    assert_param(IS_ADCUI_VGAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain));
    assert_param(IS_ADCUI_FXPHASE(ADCUI_FxUnitInitStruct->ADCUI_Fx_PhaseShift));
    assert_param(IS_ADCUI_IGAIN(ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain));
    assert_param(IS_ADCUI_FXVIRMSOS(ADCUI_FxUnitInitStruct->ADCUI_Fx_IRMSCalibration));
    assert_param(IS_ADCUI_FXVIRMSOS(ADCUI_FxUnitInitStruct->ADCUI_Fx_VRMSCalibration));
    assert_param(IS_ADCUI_VDAT_SOURCE(ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceVDAT));
    assert_param(IS_ADCUI_IDAT_SOURCE(ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceIDAT));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBIGainEnable));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBVGainEnable));
    assert_param(IS_FUNCTIONAL_STATE(ADCUI_FxUnitInitStruct->ADCUI_F0_6dBI3GainEnable));
    assert_param(IS_ADCUI_F0I3SEL_SELECT(ADCUI_FxUnitInitStruct->ADCUI_F0_I3SelectDataFilter));
    assert_param(IS_ADCUI_CHANNELI_SELECT(ADCUI_FxUnitInitStruct->ADCUI_F0_IChannelSelect));
    assert_param(IS_ADCUI_FXPWROS(ADCUI_FxUnitInitStruct->ADCUI_Fx_ActivePowerOffsetCalibration));
    assert_param(IS_ADCUI_FXPWRGAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_ActivePowerGainCalibration));
    assert_param(IS_ADCUI_FXPWROS(ADCUI_FxUnitInitStruct->ADCUI_Fx_ReactivePowerOffsetCalibration));
    assert_param(IS_ADCUI_FXPWRGAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_ReactivePowerGainCalibration));
    assert_param(IS_ADCUI_FXPWRGAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_FullPowerGainCalibration));
    assert_param(IS_ADCUI_FXVIPKLVL(ADCUI_FxUnitInitStruct->ADCUI_Fx_VPeakLevel));
    assert_param(IS_ADCUI_FXVIPKLVL(ADCUI_FxUnitInitStruct->ADCUI_Fx_IPeakLevel));
    assert_param(IS_ADCUI_CCAL_GAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_IGainCalibration));
    assert_param(IS_ADCUI_CCAL_GAIN(ADCUI_FxUnitInitStruct->ADCUI_Fx_VGainCalibration));
    assert_param(IS_ADCUI_CCAL_GAIN(ADCUI_FxUnitInitStruct->ADCUI_F0_I3GainCalibration));
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    assert_param(IS_ADCUI_FxISEL_SELECT(ADCUI_FxUnitInitStruct->ADCUI_Fx_ISelectDataFilter));
#endif

    /* Configure main registers of the ADCUI Fx unit. */
    TempFxCTR = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IntegratorEnable << ADCUI_FxCTR_FxINTEN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_SourceRegFullPower) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_PhaseShift << ADCUI_FxCTR_FxVPHASE_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IRMSCalibration << ADCUI_FxCTR_FxIRMSOS_Pos);

    TempFxWC = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_ActivePowerOffsetCalibration << ADCUI_FxWC_FxWATTOS_Pos) |
               ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_ActivePowerGainCalibration << ADCUI_FxWC_FxWGAIN_Pos);

    TempFxVC = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_ReactivePowerOffsetCalibration << ADCUI_FxVC_FxVAROS_Pos) |
               ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_ReactivePowerGainCalibration << ADCUI_FxVC_FxVARGAIN_Pos);

    TempFxAC = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VRMSCalibration << ADCUI_FxAC_FxVRMSOS_Pos) |
               ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_FullPowerGainCalibration << ADCUI_F0AC_F0VAGAIN_Pos);

    TempFxMD0 = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceVDAT) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceIDAT) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBIGainEnable << ADCUI_FxMD0_IxGAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBVGainEnable << ADCUI_FxMD0_VxGAIN_Pos);

    TempFxMD1 = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IPeakLevel << ADCUI_FxMD1_FxIPKLVL_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VPeakLevel << ADCUI_FxMD1_FxVPKLVL_Pos);

    TempCCALx = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VGainCalibration << ADCUI_CCALx_VxBGAIN_Pos) |
                ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IGainCalibration << ADCUI_CCALx_IxBGAIN_Pos);

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            TempFxCTR |= ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3IntegratorEnable << ADCUI_F0CTR_F0I3NTEN_Pos) |
                         ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain << ADCUI_F0CTR_F0I0GAIN_Pos) |
                         ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain << ADCUI_F0CTR_F0VGAIN_Pos) |
                         ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain << ADCUI_F0CTR_F0I3GAIN_Pos);
            TempFxMD0 |= ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_6dBI3GainEnable << ADCUI_F0MD0_I3GAIN_Pos) |
                         ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_IChannelSelect);

            TempFxAC |= ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3SelectDataFilter);

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
            TempMSC = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_ISelectDataFilter << ADCUI_MSC_F0ISEL_HPF_Pos);
#endif

            TempCCAL4 = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_F0_I3GainCalibration << ADCUI_CCAL4_I3BGAIN_Pos);
            break;

        case ADCUI_F1_UNIT:
            TempFxCTR |= ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain << ADCUI_FxCTR_FxIGAIN_Pos) |
                         ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain << ADCUI_FxCTR_FxVGAIN_Pos);
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
            TempMSC = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_ISelectDataFilter << ADCUI_MSC_F1ISEL_HPF_Pos);
#endif
            break;

        case ADCUI_F2_UNIT:
            TempFxCTR |= ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain << ADCUI_FxCTR_FxIGAIN_Pos) |
                         ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain << ADCUI_FxCTR_FxVGAIN_Pos);
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
            TempMSC = ((uint32_t)ADCUI_FxUnitInitStruct->ADCUI_Fx_ISelectDataFilter << ADCUI_MSC_F2ISEL_HPF_Pos);
#endif
            break;
        default:
            break;
    }

    /* Write all main registers of the ADCUI Fx unit. */
    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            MDR_ADCUI->F0CTR = TempFxCTR;
            MDR_ADCUI->F0WC  = TempFxWC;
            MDR_ADCUI->F0VC  = TempFxVC;
            MDR_ADCUI->F0AC  = TempFxAC;
            MDR_ADCUI->F0MD0 = TempFxMD0;
            MDR_ADCUI->F0MD1 = TempFxMD1;
            MDR_ADCUI->CCAL1 = TempCCALx;
            MDR_ADCUI->CCAL4 = TempCCAL4;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
            MDR_ADCUI->MSC |= TempMSC;
#endif
            break;
        case ADCUI_F1_UNIT:
            MDR_ADCUI->F1CTR = TempFxCTR;
            MDR_ADCUI->F1WC  = TempFxWC;
            MDR_ADCUI->F1VC  = TempFxVC;
            MDR_ADCUI->F1AC  = TempFxAC;
            MDR_ADCUI->F1MD0 = TempFxMD0;
            MDR_ADCUI->F1MD1 = TempFxMD1;
            MDR_ADCUI->CCAL2 = TempCCALx;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
            MDR_ADCUI->MSC |= TempMSC;
#endif
            break;
        case ADCUI_F2_UNIT:
            MDR_ADCUI->F2CTR = TempFxCTR;
            MDR_ADCUI->F2WC  = TempFxWC;
            MDR_ADCUI->F2VC  = TempFxVC;
            MDR_ADCUI->F2AC  = TempFxAC;
            MDR_ADCUI->F2MD0 = TempFxMD0;
            MDR_ADCUI->F2MD1 = TempFxMD1;
            MDR_ADCUI->CCAL3 = TempCCALx;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
            MDR_ADCUI->MSC |= TempMSC;
#endif
            break;
        default:
            break;
    }
}

/**
 * @brief Fill each ADCUI_FxUnitInitStruct member with its default value.
 * @param ADCUI_FxUnitInitStruct: The pointer to a @ref ADCUI_FxUnit_InitTypeDef
 *        structure which is to be initialized.
 * @return None.
 */
void ADCUI_Fx_StructInit(ADCUI_FxUnit_InitTypeDef* ADCUI_FxUnitInitStruct)
{
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IntegratorEnable   = ADCUI_INT_ENABLE;
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3IntegratorEnable = ADCUI_INT_ENABLE;
    ADCUI_FxUnitInitStruct->ADCUI_SourceRegFullPower    = ADCUI_FULL_ENERGY;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain = ADCUI_IGAIN_6dB;
#endif
#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IGain = ADCUI_IGAIN_0dB;
#endif
    ADCUI_FxUnitInitStruct->ADCUI_Fx_VGain      = ADCUI_VGAIN_0dB;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_PhaseShift = 0;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain = ADCUI_IGAIN_6dB;
#endif
#if defined(USE_MDR32F02_REV_1X) || defined(USE_MDR32F02_REV_2)
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3Gain = ADCUI_IGAIN_0dB;
#endif
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IRMSCalibration                = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_VRMSCalibration                = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceVDAT                     = ADCUI_Fx_VDAT_U_BEFORE_HPF;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_SourceIDAT                     = ADCUI_Fx_IDAT_I;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBIGainEnable                 = DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_6dBVGainEnable                 = DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_F0_6dBI3GainEnable                = DISABLE;
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3SelectDataFilter             = ADCUI_F0I3SEL_AFTER_HPF;
    ADCUI_FxUnitInitStruct->ADCUI_F0_IChannelSelect                 = ADCUI_F0_I_CH_AUTO;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_ActivePowerOffsetCalibration   = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_ActivePowerGainCalibration     = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_ReactivePowerOffsetCalibration = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_ReactivePowerGainCalibration   = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_FullPowerGainCalibration       = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_VPeakLevel                     = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IPeakLevel                     = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_IGainCalibration               = 0;
    ADCUI_FxUnitInitStruct->ADCUI_Fx_VGainCalibration               = 0;
    ADCUI_FxUnitInitStruct->ADCUI_F0_I3GainCalibration              = 0;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    ADCUI_FxUnitInitStruct->ADCUI_Fx_ISelectDataFilter = ADCUI_FxISEL_BEFORE_HPF;
#endif
}

/**
 * @brief Clear the ADCUI power counter for specified Fx unit.
 * @param UnitNumber: @ref ADCUI_Unit_TypeDef - a number of the channel.
 * @param PowerCounter: @ref ADCUI_Power_TypeDef - a selected power counter to clear.
 * @return None.
 */
void ADCUI_Fx_ClearPowerCounter(ADCUI_Unit_TypeDef UnitNumber, ADCUI_Power_TypeDef PowerCounter)
{
    /* Check the parameters. */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_POWERS(PowerCounter));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            switch (PowerCounter) {
                case ADCUI_POWER_ACTIVE:
                    MDR_ADCUI->F0CTR |= (1 << ADCUI_F0CTR_F0RARS_Pos);
                    break;
                case ADCUI_POWER_REACTIVE:
                    MDR_ADCUI->F0CTR |= (1 << ADCUI_F0CTR_F0RRRS_Pos);
                    break;
                case ADCUI_POWER_FULL:
                    MDR_ADCUI->F0CTR |= (1 << ADCUI_F0CTR_F0RVRS_Pos);
                    break;
            }
            break;
        case ADCUI_F1_UNIT:
            switch (PowerCounter) {
                case ADCUI_POWER_ACTIVE:
                    MDR_ADCUI->F1CTR |= (1 << ADCUI_FxCTR_FxRARS_Pos);
                    break;
                case ADCUI_POWER_REACTIVE:
                    MDR_ADCUI->F1CTR |= (1 << ADCUI_FxCTR_FxRRRS_Pos);
                    break;
                case ADCUI_POWER_FULL:
                    MDR_ADCUI->F1CTR |= (1 << ADCUI_FxCTR_FxRVRS_Pos);
                    break;
            }
            break;
        case ADCUI_F2_UNIT:
            switch (PowerCounter) {
                case ADCUI_POWER_ACTIVE:
                    MDR_ADCUI->F2CTR |= (1 << ADCUI_FxCTR_FxRARS_Pos);
                    break;
                case ADCUI_POWER_REACTIVE:
                    MDR_ADCUI->F2CTR |= (1 << ADCUI_FxCTR_FxRRRS_Pos);
                    break;
                case ADCUI_POWER_FULL:
                    MDR_ADCUI->F2CTR |= (1 << ADCUI_FxCTR_FxRVRS_Pos);
                    break;
            }
            break;
        default:
            break;
    }
}

/**
 * @brief  ADCUI channel configuration.
 * @param  Channels: @ref ADCUI_Channel_TypeDef - specify the ADCUI channel to be enabled or disabled.
 * @param  NewState: @ref FunctionalState - the new states of the specified ADCUI channels.
 * @return None.
 */
void ADCUI_ChannelConfig(uint32_t Channels, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNELS(Channels));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_ADCUI->CTRL1 |= Channels;
    } else {
        MDR_ADCUI->CTRL1 &= ~Channels;
    }
}

/**
 * @brief  Selecting DMA operating mode (single or block transactions).
 * @param  Channels: @ref ADCUI_Channel_TypeDef - specify the ADCUI channel to be enabled or disabled.
 * @param  Mode: @ref ADCUI_DmaTransMode_TypeDef - specify DMA transaction mode.
 * @param  NewState: @ref FunctionalState - the new states of the specified ADCUI channels when configuring the DMA operating mode.
 * @return None.
 */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void ADCUI_DMAConfig(uint32_t Channels, ADCUI_DmaTransMode_TypeDef Mode, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNELS(Channels));
    assert_param(IS_ADCUI_DMA_TRANSACTIONS_MODE(Mode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    switch (Mode) {
        case ADCUI_DMA_TRANSACTIONS_SINGLE:
            if (NewState != DISABLE) {
                MDR_ADCUI->MSC |= (Channels << ADCUI_MSC_DMA_EN_RQ_S_Pos);
            } else {
                MDR_ADCUI->MSC &= (~Channels << ADCUI_MSC_DMA_EN_RQ_S_Pos);
            }
            break;
        case ADCUI_DMA_TRANSACTIONS_BLOCK:
            if (NewState != DISABLE) {
                MDR_ADCUI->MSC |= Channels;
            } else {
                MDR_ADCUI->MSC &= ~Channels;
            }
            break;
        default:
            break;
    }
}
#endif

/**
 * @brief  ADCUI chopper configuration.
 * @param  ChannelNumber: @ref ADCUI_Channel_TypeDef - specify the ADCUI channel in which you want to enable or disable the chopper.
 * @param  NewState: @ref FunctionalState - the new states of the specified ADCUI channels for working with chopper.
 * @return None.
 */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void ADCUI_ChopperConfig(ADCUI_Channel_TypeDef ChannelNumber, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNELS(ChannelNumber));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        switch (ChannelNumber) {
            case ADCUI_CH_F0_I0:
                MDR_ADCUI->CTRL2 |= (1 << ADCUI_CTRL2_DCHPENI0_Pos);
                break;
            case ADCUI_CH_F0_V0:
                MDR_ADCUI->CTRL2 |= (1 << ADCUI_CTRL2_DCHPENV0_Pos);
                break;
            case ADCUI_CH_F1_I1:
                MDR_ADCUI->CTRL2 |= (1 << ADCUI_CTRL2_DCHPENI1_Pos);
                break;
            case ADCUI_CH_F1_V1:
                MDR_ADCUI->CTRL2 |= (1 << ADCUI_CTRL2_DCHPENV1_Pos);
                break;
            case ADCUI_CH_F2_I2:
                MDR_ADCUI->CTRL2 |= (1 << ADCUI_CTRL2_DCHPENI2_Pos);
                break;
            case ADCUI_CH_F2_V2:
                MDR_ADCUI->CTRL2 |= (1 << ADCUI_CTRL2_DCHPENV2_Pos);
                break;
            case ADCUI_CH_F0_I3:
                MDR_ADCUI->CTRL2 |= (1 << ADCUI_CTRL2_DCHPENI3_Pos);
                break;
            default:
                break;
        }
    } else {
        switch (ChannelNumber) {
            case ADCUI_CH_F0_I0:
                MDR_ADCUI->CTRL2 &= ~((uint32_t)1 << ADCUI_CTRL2_DCHPENI0_Pos);
                break;
            case ADCUI_CH_F0_V0:
                MDR_ADCUI->CTRL2 &= ~((uint32_t)1 << ADCUI_CTRL2_DCHPENV0_Pos);
                break;
            case ADCUI_CH_F1_I1:
                MDR_ADCUI->CTRL2 &= ~((uint32_t)1 << ADCUI_CTRL2_DCHPENI1_Pos);
                break;
            case ADCUI_CH_F1_V1:
                MDR_ADCUI->CTRL2 &= ~((uint32_t)1 << ADCUI_CTRL2_DCHPENV1_Pos);
                break;
            case ADCUI_CH_F2_I2:
                MDR_ADCUI->CTRL2 &= ~((uint32_t)1 << ADCUI_CTRL2_DCHPENI2_Pos);
                break;
            case ADCUI_CH_F2_V2:
                MDR_ADCUI->CTRL2 &= ~((uint32_t)1 << ADCUI_CTRL2_DCHPENV2_Pos);
                break;
            case ADCUI_CH_F0_I3:
                MDR_ADCUI->CTRL2 &= ~((uint32_t)1 << ADCUI_CTRL2_DCHPENI3_Pos);
                break;
            default:
                break;
        }
    }
}
#endif

/**
 * @brief  Return the result of the operation for the specified ADCUI channel.
 * @param  ChannelNumber: @ref ADCUI_Channel_TypeDef - ADCUI channel number.
 * @return A value of the ADCUI result register for the specified channel.
 */
uint32_t ADCUI_GetResult(ADCUI_Channel_TypeDef ChannelNumber)
{
    uint32_t ResultChannel = 0;

    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNEL(ChannelNumber));

    switch (ChannelNumber) {
        case ADCUI_CH_F0_I0:
            ResultChannel = MDR_ADCUI->F0I0DAT;
            break;
        case ADCUI_CH_F0_V0:
            ResultChannel = MDR_ADCUI->F0VDAT;
            break;
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
        case ADCUI_CH_F0_I3:
            ResultChannel = MDR_ADCUI->F0I3DAT;
            break;
        default:
            break;
    }
    return (ResultChannel);
}

/**
 * @brief  Return the ADCUI power accumulator for a specified Fx unit.
 * @param  UnitNumber: @ref ADCUI_Unit_TypeDef - select ADCUI Fx unit.
 * @param  PowerAccumulator: @ref ADCUI_Power_TypeDef - power accumulator.
 * @param  ReturnNegative: @ref FunctionalState - return negative power. Count only for active and reactive power.
 * @return ADCUI power accumulator value.
 */
uint64_t ADCUI_GetPowerAccumulator(ADCUI_Unit_TypeDef  UnitNumber,
                                   ADCUI_Power_TypeDef PowerAccumulator,
                                   FunctionalState     ReturnNegative)
{
    volatile uint32_t *PtrPowerLow, *PtrPowerHigh;
    uint32_t           PowerLow, PowerHigh;

    volatile uint32_t* PowersArray[30] = {
        &(MDR_ADCUI->F0WATTP), &(MDR_ADCUI->F0WATTP_L), &(MDR_ADCUI->F0WATTN), &(MDR_ADCUI->F0WATTN_L),
        &(MDR_ADCUI->F0VARP), &(MDR_ADCUI->F0VARP_L), &(MDR_ADCUI->F0VARN), &(MDR_ADCUI->F0VARN_L),
        &(MDR_ADCUI->F0VARP), &(MDR_ADCUI->F0VR_L),
        &(MDR_ADCUI->F1WATTP), &(MDR_ADCUI->F1WATTP_L), &(MDR_ADCUI->F1WATTN), &(MDR_ADCUI->F1WATTN_L),
        &(MDR_ADCUI->F1VARP), &(MDR_ADCUI->F1VARP_L), &(MDR_ADCUI->F1VARN), &(MDR_ADCUI->F1VARN_L),
        &(MDR_ADCUI->F1VARP), &(MDR_ADCUI->F1VR_L),
        &(MDR_ADCUI->F2WATTP), &(MDR_ADCUI->F2WATTP_L), &(MDR_ADCUI->F2WATTN), &(MDR_ADCUI->F2WATTN_L),
        &(MDR_ADCUI->F2VARP), &(MDR_ADCUI->F2VARP_L), &(MDR_ADCUI->F2VARN), &(MDR_ADCUI->F2VARN_L),
        &(MDR_ADCUI->F2VARP), &(MDR_ADCUI->F2VR_L)
    };

    /* Check the parameters. */
    assert_param(IS_ADCUI_POWER(PowerAccumulator));
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_FUNCTIONAL_STATE(ReturnNegative));

    if (PowerAccumulator == ADCUI_POWER_FULL) {
        ReturnNegative = DISABLE;
    }

    PtrPowerLow  = (PowersArray[((uint32_t)UnitNumber * 10) +
                               ((uint32_t)PowerAccumulator * 4) +
                               ((uint32_t)ReturnNegative * 2) + 1]);
    PtrPowerHigh = (PowersArray[((uint32_t)UnitNumber * 10) +
                                ((uint32_t)PowerAccumulator * 4) +
                                ((uint32_t)ReturnNegative * 2)]);

    do {
        PowerHigh = *PtrPowerHigh;
        PowerLow  = *PtrPowerLow;
    } while (PowerHigh != *PtrPowerHigh);

    return (uint64_t)(((uint64_t)PowerHigh << 32) | PowerLow);
}

/**
 * @brief  Return the peak value for a specific channel.
 * @param  ChannelNumber: @ref ADCUI_Channel_TypeDef - a channel number.
 *         This parameter should be one of the following values:
 *             @arg ADCUI_CH_F0_I0: I0 channel of F0 unit.
 *             @arg ADCUI_CH_F0_V0: V0 channel of F0 unit.
 *             @arg ADCUI_CH_F1_I1: I1 channel of F1 unit.
 *             @arg ADCUI_CH_F1_V1: V1 channel of F1 unit.
 *             @arg ADCUI_CH_F2_I2: I2 channel of F2 unit.
 *             @arg ADCUI_CH_F2_V2: V2 channel of F2 unit.
 * @return ADCUI peak value for a specified channel.
 */
uint32_t ADCUI_GetPeakValue(ADCUI_Channel_TypeDef ChannelNumber)
{
    uint32_t Value = 0;

    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNEL_NO_I3(ChannelNumber));

    switch (ChannelNumber) {
        case ADCUI_CH_F0_I0:
            Value = MDR_ADCUI->F0IPEAK;
            break;
        case ADCUI_CH_F0_V0:
            Value = MDR_ADCUI->F0VPEAK;
            break;
        case ADCUI_CH_F1_I1:
            Value = MDR_ADCUI->F1IPEAK;
            break;
        case ADCUI_CH_F1_V1:
            Value = MDR_ADCUI->F1VPEAK;
            break;
        case ADCUI_CH_F2_I2:
            Value = MDR_ADCUI->F2IPEAK;
            break;
        case ADCUI_CH_F2_V2:
            Value = MDR_ADCUI->F2VPEAK;
            break;
        default:
            break;
    }
    return Value;
}

/**
 * @brief  Clear the peak value for a specified channel.
 * @param  ChannelNumber: @ref ADCUI_Channel_TypeDef - a channel number.
 *         This parameter should be one of the following values:
 *             @arg ADCUI_CH_F0_I0: I0 channel of F0 unit.
 *             @arg ADCUI_CH_F0_V0: V0 channel of F0 unit.
 *             @arg ADCUI_CH_F1_I1: I1 channel of F1 unit.
 *             @arg ADCUI_CH_F1_V1: V1 channel of F1 unit.
 *             @arg ADCUI_CH_F2_I2: I2 channel of F2 unit.
 *             @arg ADCUI_CH_F2_V2: V2 channel of F2 unit.
 * @return None.
 */
void ADCUI_ClearPeakValue(ADCUI_Channel_TypeDef ChannelNumber)
{
    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNEL_NO_I3(ChannelNumber));

    switch (ChannelNumber) {
        case ADCUI_CH_F0_I0:
            MDR_ADCUI->F0IPEAK = 0;
            break;
        case ADCUI_CH_F0_V0:
            MDR_ADCUI->F0VPEAK = 0;
            break;
        case ADCUI_CH_F1_I1:
            MDR_ADCUI->F1IPEAK = 0;
            break;
        case ADCUI_CH_F1_V1:
            MDR_ADCUI->F1VPEAK = 0;
            break;
        case ADCUI_CH_F2_I2:
            MDR_ADCUI->F2IPEAK = 0;
            break;
        case ADCUI_CH_F2_V2:
            MDR_ADCUI->F2VPEAK = 0;
            break;
        default:
            break;
    }
}

/**
 * @brief   Return RMS value for a specified channel.
 * @param   ChannelNumber: @ref ADCUI_Channel_TypeDef - a channel number.
 *          This parameter should be one of the following values:
 *              @arg ADCUI_CH_F0_I0: I0 channel of F0 unit.
 *              @arg ADCUI_CH_F0_V0: V0 channel of F0 unit.
 *              @arg ADCUI_CH_F1_I1: I1 channel of F1 unit.
 *              @arg ADCUI_CH_F1_V1: V1 channel of F1 unit.
 *              @arg ADCUI_CH_F2_I2: I2 channel of F2 unit.
 *              @arg ADCUI_CH_F2_V2: V2 channel of F2 unit.
 *              @arg ADCUI_CH_F0_I3: I3 channel of F0 unit. For an inactive channel, which may be I0 or I3
 *                                    depending on F0MD0.F0SEL_I_CH bits.
 * @warning ChannelNumber == ADCUI_CH_F0_I3 corresponds to an inactive channel,
 *          which may be I0 or I3 depending on F0MD0.F0SEL_I_CH bits.
 * @return  ADCUI RMS value for a specified channel.
 */
uint32_t ADCUI_GetRMS(ADCUI_Channel_TypeDef ChannelNumber)
{
    uint32_t Value = 0;

    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNEL(ChannelNumber));

    switch (ChannelNumber) {
        case ADCUI_CH_F0_I0:
            Value = MDR_ADCUI->F0IRMS;
            break;
        case ADCUI_CH_F0_V0:
            Value = MDR_ADCUI->F0VRMS;
            break;
        case ADCUI_CH_F1_I1:
            Value = MDR_ADCUI->F1IRMS;
            break;
        case ADCUI_CH_F1_V1:
            Value = MDR_ADCUI->F1VRMS;
            break;
        case ADCUI_CH_F2_I2:
            Value = MDR_ADCUI->F2IRMS;
            break;
        case ADCUI_CH_F2_V2:
            Value = MDR_ADCUI->F2VRMS;
            break;
        case ADCUI_CH_F0_I3:
            Value = MDR_ADCUI->F0IRMS_INACTIVE;
            break;
        default:
            break;
    }
    return Value;
}

/**
 * @brief  Return RMS^2 value for a specified channel.
 * @param  ChannelNumber: @ref ADCUI_Channel_TypeDef - a channel number.
 *         This parameter should be one of the following values:
 *             @arg ADCUI_CH_F0_I0: I0 channel of F0 unit.
 *             @arg ADCUI_CH_F0_V0: V0 channel of F0 unit.
 *             @arg ADCUI_CH_F1_I1: I1 channel of F1 unit.
 *             @arg ADCUI_CH_F1_V1: V1 channel of F1 unit.
 *             @arg ADCUI_CH_F2_I2: I2 channel of F2 unit.
 *             @arg ADCUI_CH_F2_V2: V2 channel of F2 unit.
 * @return ADCUI RMS^2 value for a specified channel.
 */
uint32_t ADCUI_GetRMS2(ADCUI_Channel_TypeDef ChannelNumber)
{
    uint32_t Value = 0;

    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNEL_NO_I3(ChannelNumber));

    switch (ChannelNumber) {
        case ADCUI_CH_F0_I0:
            Value = MDR_ADCUI->F0IRMS2;
            break;
        case ADCUI_CH_F0_V0:
            Value = MDR_ADCUI->F0VRMS2;
            break;
        case ADCUI_CH_F1_I1:
            Value = MDR_ADCUI->F1IRMS2;
            break;
        case ADCUI_CH_F1_V1:
            Value = MDR_ADCUI->F1VRMS2;
            break;
        case ADCUI_CH_F2_I2:
            Value = MDR_ADCUI->F2IRMS2;
            break;
        case ADCUI_CH_F2_V2:
            Value = MDR_ADCUI->F2VRMS2;
            break;
        default:
            break;
    }
    return Value;
}

/**
 * @brief  Return a phase shift of V1 or V2 channels in relation to V0.
 * @param  ChannelNumber: @ref ADCUI_Channel_TypeDef - a channel number.
 *         This parameter should be one of the following values:
 *             @arg ADCUI_CH_F1_V1: V1 channel of F1 unit.
 *             @arg ADCUI_CH_F2_V2: V2 channel of F2 unit.
 * @return ADCUI phase shift of a specified voltage channel in relation to V0.
 */
uint32_t ADCUI_GetVPhaseShiftRelativeV0(ADCUI_Channel_TypeDef ChannelNumber)
{
    uint32_t Value;

    /* Check the parameters. */
    assert_param(IS_ADCUI_CHANNEL_V1_V2(ChannelNumber));

    if (ChannelNumber == ADCUI_CH_F1_V1) {
        Value = MDR_ADCUI->F1MD2;
    } else {
        Value = MDR_ADCUI->F2MD2;
    }

    return Value;
}

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief  Return ADCUI effective value of the voltage in the channel period.
 * @param  UnitNumber: @ref ADCUI_Unit_TypeDef - select an ADCUI Fx unit.
 * @return ADCUI voltage effective value.
 */
uint32_t ADCUI_GetVoltageTrueRMS(ADCUI_Unit_TypeDef UnitNumber)
{
    uint32_t Result = 0;

    /* Check the parameters. */
    assert_param(IS_ADCUI_UNIT(UnitNumber));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            Result = MDR_ADCUI->F0VRMS_TRUE;
            break;
        case ADCUI_F1_UNIT:
            Result = MDR_ADCUI->F1VRMS_TRUE;
            break;
        case ADCUI_F2_UNIT:
            Result = MDR_ADCUI->F2VRMS_TRUE;
            break;
        default:
            break;
    }
    return Result;
}
#endif

/**
 * @brief  Reset certain flags in one of ADCUI units.
 * @param  UnitNumber: @ref ADCUI_Unit_TypeDef - select an ADCUI Fx unit.
 * @param  Flags: Specify the flags to clear.
 *         This parameter can be any combination of @ref ADCUI_Flags_TypeDef values.
 * @return None.
 */
void ADCUI_ClearFlags(ADCUI_Unit_TypeDef UnitNumber, uint32_t Flags)
{
    /* Check the parameters. */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_FLAG(Flags));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            MDR_ADCUI->F0STAT |= Flags;
            break;
        case ADCUI_F1_UNIT:
            MDR_ADCUI->F1STAT |= Flags;
            break;
        case ADCUI_F2_UNIT:
            MDR_ADCUI->F2STAT |= Flags;
            break;
        default:
            break;
    }
}

/**
 * @brief  Check whether a specified ADCUI flag is set or not.
 * @param  UnitNumber: @ref ADCUI_Unit_TypeDef - select an ADCUI Fx unit.
 * @param  ADCUI_Flag: @ref ADCUI_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - a state of ADCUI flag (SET or RESET).
 */
FlagStatus ADCUI_GetFlagStatus(ADCUI_Unit_TypeDef UnitNumber, ADCUI_Flags_TypeDef ADCUI_Flag)
{
    FlagStatus Flag = RESET;

    /* Check the parameters. */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_FLAG(ADCUI_Flag));

    switch (UnitNumber) {

        case ADCUI_F0_UNIT:
            if ((MDR_ADCUI->F0STAT & (uint32_t)ADCUI_Flag) != 0) {
                Flag = SET;
            } else {
                Flag = RESET;
            }
            break;
        case ADCUI_F1_UNIT:
            if ((MDR_ADCUI->F1STAT & (uint32_t)ADCUI_Flag) != 0) {
                Flag = SET;
            } else {
                Flag = RESET;
            }
            break;
        case ADCUI_F2_UNIT:
            if ((MDR_ADCUI->F2STAT & (uint32_t)ADCUI_Flag) != 0) {
                Flag = SET;
            } else {
                Flag = RESET;
            }
            break;
        default:
            break;
    }
    return (Flag);
}

/**
 * @brief  Return a combined value of the ADCUI Fx unit status flags.
 * @param  UnitNumber: @ref ADCUI_Unit_TypeDef - select an ADCUI Fx unit.
 * @return A combined value of ADCUI status flags.
 */
uint32_t ADCUI_GetStatus(ADCUI_Unit_TypeDef UnitNumber)
{
    uint32_t StatusFlags = 0;

    /* Check the parameters. */
    assert_param(IS_ADCUI_UNIT(UnitNumber));

    switch (UnitNumber) {
        case ADCUI_F0_UNIT:
            StatusFlags = MDR_ADCUI->F0STAT & ADCUI_FLAGS_MASK;
            break;
        case ADCUI_F1_UNIT:
            StatusFlags = MDR_ADCUI->F1STAT & ADCUI_FLAGS_MASK;
            break;
        case ADCUI_F2_UNIT:
            StatusFlags = MDR_ADCUI->F2STAT & ADCUI_FLAGS_MASK;
            break;
        default:
            break;
    }
    return (StatusFlags);
}

/**
 * @brief  Enable or disable the ADCUI interrupts.
 * @param  UnitNumber: @ref ADCUI_Unit_TypeDef - select an ADCUI Fx unit.
 * @param  ADCUI_IT: Specify the ADCUI interrupt sources to be enabled or disabled.
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
 * @param  NewState: @ref FunctionalState - a new state of the ADCUI interrupts.
 * @return None.
 */
void ADCUI_ITConfig(ADCUI_Unit_TypeDef UnitNumber, uint32_t ADCUI_IT, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_ADCUI_UNIT(UnitNumber));
    assert_param(IS_ADCUI_ITS(ADCUI_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Configure IT state. */
    switch (UnitNumber) {

        case ADCUI_F0_UNIT:
            if (NewState != DISABLE) {
                MDR_ADCUI->F0MASK |= ADCUI_IT;
            } else {
                MDR_ADCUI->F0MASK &= ~ADCUI_IT;
            }
            break;
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
        default:
            break;
    }
}

/** @} */ /* End of the group ADCUI_Exported_Functions */

/** @} */ /* End of the group ADCUI */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_adcui.c */

