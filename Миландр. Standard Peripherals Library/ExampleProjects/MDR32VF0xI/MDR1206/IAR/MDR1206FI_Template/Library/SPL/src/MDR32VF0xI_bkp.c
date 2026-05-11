/**
 ******************************************************************************
 * @file    MDR32VF0xI_bkp.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    05/06/2025
 * @brief   This file contains all the BKP firmware functions.
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

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_bkp.h"
#include "MDR32VF0xI_utils.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup BKP BKP
 * @{
 */

/** @defgroup BKP_Private_Defines BKP Private Defines
 * @{
 */

#define BKP_RTC_CS_FLAG_MASK (BKP_RTC_CS_OWF |   \
                              BKP_RTC_CS_SECF |  \
                              BKP_RTC_CS_WUTF |  \
                              BKP_RTC_CS_WEC |   \
                              BKP_RTC_CS_ALRAF | \
                              BKP_RTC_CS_ALRBF | \
                              BKP_RTC_CS_TSF)

#define BKP_RTC_CS_FLAG_CLR_MASK (BKP_RTC_CS_OWF |   \
                                  BKP_RTC_CS_SECF |  \
                                  BKP_RTC_CS_WUTF |  \
                                  BKP_RTC_CS_ALRAF | \
                                  BKP_RTC_CS_ALRBF | \
                                  BKP_RTC_CS_TSF)

#define BKP_RTC_CS_IT_MASK (BKP_RTC_CS_OWF_IE |   \
                            BKP_RTC_CS_SECF_IE |  \
                            BKP_RTC_CS_WUTF_IE |  \
                            BKP_RTC_CS_ALRAF_IE | \
                            BKP_RTC_CS_ALRBF_IE)

#define BKP_RTC_TAFCR_FLAG_MASK (BKP_RTC_TAFCR_TAMP_IN_SEL_Msk | \
                                 BKP_RTC_TAFCR_TS_IN_SEL_Msk)

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define BKP_RTC_TAFCR_FLAG_CLR_MASK (BKP_RTC_TAFCR_TAMP_IN_SEL_Msk | \
                                     BKP_RTC_TAFCR_TS_IN_SEL_Msk)
#endif

#define BKP_RTC_TAFCR_IT_MASK (BKP_RTC_TAFCR_TAMP_IE | \
                               BKP_RTC_TAFCR_TS_IE)

#define BKP_RTC_TR_SECONDS_MASK    (BKP_RTC_TR_SU_Msk | BKP_RTC_TR_ST_Msk)
#define BKP_RTC_TR_MINUTES_MASK    (BKP_RTC_TR_MNU_Msk | BKP_RTC_TR_MNT_Msk)
#define BKP_RTC_TR_HOURS_MASK      (BKP_RTC_TR_HU_Msk | BKP_RTC_TR_HT_Msk)

#define BKP_RTC_DR_DATE_MASK       (BKP_RTC_DR_DU_Msk | BKP_RTC_DR_DT_Msk)
#define BKP_RTC_DR_MONTH_MASK      (BKP_RTC_DR_MU_Msk | BKP_RTC_DR_MT_Msk)
#define BKP_RTC_DR_YEAR_MASK       (BKP_RTC_DR_YU_Msk | BKP_RTC_DR_YT_Msk)

#define BKP_RTC_ALARM_SECONDS_MASK (BKP_RTC_ALARMxR_SU_Msk | BKP_RTC_ALARMxR_ST_Msk)
#define BKP_RTC_ALARM_MINUTES_MASK (BKP_RTC_ALARMxR_MNU_Msk | BKP_RTC_ALARMxR_MNT_Msk)
#define BKP_RTC_ALARM_HOURS_MASK   (BKP_RTC_ALARMxR_HU_Msk | BKP_RTC_ALARMxR_HT_Msk)
#define BKP_RTC_ALARM_DATE_MASK    (BKP_RTC_ALARMxR_DU_Msk | BKP_RTC_ALARMxR_DT_Msk)

/** @} */ /* End of the group BKP_Private_Defines */

/** @defgroup BKP_Private_Functions_Declarations BKP Private Functions Declarations
 * @{
 */

static void BKP_RTC_GetDateTimeReg(uint32_t DateRegVal, uint32_t TimeRegVal, BKP_RTC_DateTime_TypeDef* RTC_DateTime);

/** @} */ /* End of the group BKP_Private_Functions_Declarations */

/** @addtogroup BKP_Exported_Functions BKP Exported Functions
 * @{
 */

/** @addtogroup BKP_Common_Control_Functions BKP Common Control Functions
 * @{
 */

/**
 * @brief  Lock/Unlock write access to the BKP registers. The BKP registers are locked by default.
 * @param  LockState: @ref FlagStatus - a new lock state of the BKP registers.
 *         This parameter must be one of the @ref FlagStatus values:
 *             @arg RESET: Unlock the write access;
 *             @arg SET: Lock the write access.
 * @return None.
 */
void BKP_SetRegistersLock(FlagStatus LockState)
{
    /* Check the parameters. */
    assert_param(IS_BIT_STATUS(LockState));

    if (LockState != RESET) {
        /* Lock write access if SET. */
        MDR_BKP->WPR = BKP_WPR_BKP_WPR_LOCK;
    } else {
        /* Unlock write access if RESET. */
        MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
    }
}

/**
 * @brief  Get the current BKP write access lock state. The BKP registers are locked by default.
 * @param  None.
 * @return @ref FlagStatus - write lock state:
 *             @arg RESET: Unlocked;
 *             @arg SET: Locked.
 */
FlagStatus BKP_GetRegistersLock(void)
{
    if (MDR_BKP->WPR == BKP_WPR_BKP_WPR_UNLOCK) {
        /* BKP write access is unlocked. */
        return RESET;
    } else {
        /* BKP write access is locked. */
        return SET;
    }
}

/**
 * @brief  Deinitialize the registers of the BKP subblocks to their default reset values.
 * @note   The following register fields are not reset:
 *             BKP_LDO: FPOR and MODE[1:0] - fields used by the standard boot program;
 *             BKP_LDO: LDO_BOOST[1:0]     - LDO voltage regulator trimming (only for MDR1206FI and MDR1206AFI);
 *             BKP_CLK: HSI_LSI_TRIM[5:0]  - HSI and LSI clock trimming.
 * @note   Before calling BKP_DeInit(BKP_RTC/BKP_ALL), you must wait until the last write to the RTC registers is completed by calling BKP_RTC_WaitForUpdate().
 * @note   When calling BKP_DeInit(BKP_RTC/BKP_ALL), RTC_CLK is switched to LSI. If the previous clock source of RTC_CLK is not LSI, then it must be enabled
 *         to correctly switch the RTC_CLK multiplexer. Also in this case, the cycle counter and core clock from SystemCoreClock are used for delay.
 *         Do not disable the cycle counter. Before calling this function, you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  Subblocks: Specify the BKP subblocks for deinitialization.
 *         This parameter can be any combination of @ref BKP_Subblocks_TypeDef values:
 *             @arg BKP_MEM:     Deinitialize the BKP RAM of cryptographic keys to all zeros;
 *             @arg BKP_CONTROL: Deinitialize the BKP control functions - JTAG and LDO, BLDO voltage regulators (except the LDO trimming for MDR1206FI and MDR1206AFI);
 *             @arg BKP_SW:      Deinitialize the BKP emergency power supply control;
 *             @arg BKP_CLK:     Deinitialize the BKP clock source control (except the HSI and LSI clock trimming);
 *             @arg BKP_RTC:     Deinitialize all RTC registers - RTC, WUT, TAMPER, TIMESTAMP and TMPCAL (TMPCAL only for MDR1206FI and MDR1206AFI);
 *             @arg BKP_ALL:     Deinitialize all BKP subblocks.
 * @return None.
 */
void BKP_DeInit(uint32_t Subblocks)
{
    uint32_t TmpReg, TmpLDO, TmpCLK;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    uint32_t TmpTMPCAL3;
#endif
    BKP_RTC_ClockSource_TypeDef PrevClockSource;

    /* Check the parameters. */
    assert_param(IS_BKP_SUBBLOCK(Subblocks));

    /* Read BKP registers. */
    TmpLDO = MDR_BKP->LDO;
    TmpCLK = MDR_BKP->CLK;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    TmpTMPCAL3 = MDR_BKP->RTC_TMPCAL3;
#endif

    /* Deinitialize the BKP MEM. */
    if ((Subblocks & BKP_MEM) != 0) {
        /* Fast clean BKP MEM if RST_CLK clock is enabled. */
        if ((MDR_RST_CLK->PER2_CLOCK & RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK) != 0) {
            TmpReg                  = MDR_RST_CLK->PER1_CLOCK;
            MDR_RST_CLK->PER1_CLOCK = TmpReg | RST_CLK_PER1_CLOCK_KEY_RESET_PROG;
            MDR_RST_CLK->PER1_CLOCK = TmpReg;
        } else {
            for (TmpReg = 0; TmpReg < 128; TmpReg++) {
                MDR_BKP->MEM[TmpReg] = 0;
            }
        }
    }

    /* Deinitialize the BKP CONTROL. */
    if ((Subblocks & BKP_CONTROL) != 0) {
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
        TmpLDO = (TmpLDO & ~(BKP_LDO_BLDO_TRIM_Msk | BKP_LDO_BLDO_BOOST | BKP_LDO_TAMPF | BKP_LDO_SW_OFF)) | BKP_LDO_JTAG_ON;
#else
        TmpLDO = (TmpLDO & ~(BKP_LDO_BLDO_TRIM_Msk | BKP_LDO_BLDO_BOOST | BKP_LDO_TAMPF | BKP_LDO_SW_OFF | BKP_LDO_LDO_BOOST_Msk)) | BKP_LDO_JTAG_ON;
#endif
    }

    /* Deinitialize the BKP SW. */
    if ((Subblocks & BKP_SW) != 0) {
        TmpLDO = (TmpLDO & ~(BKP_LDO_SW_CNTRL | BKP_LDO_TAMPF)) | BKP_LDO_SW_OFF;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
        TmpTMPCAL3 &= ~BKP_RTC_TMPCAL3_SWCTR_INV;
#endif
    }

    /* Deinitialize the BKP CLK. */
    if ((Subblocks & BKP_CLK) != 0) {
        TmpCLK = (TmpCLK & BKP_CLK_HSI_LSI_TRIM_Msk) | BKP_CLK_HSI_ON;
    }

    /* Deinitialize the BKP RTC. */
    if ((Subblocks & BKP_RTC) != 0) {
        PrevClockSource     = (BKP_RTC_ClockSource_TypeDef)(MDR_BKP->RTC_CR & BKP_RTC_CR_RTC_SEL_Msk);
        MDR_BKP->RTC_CR     = BKP_RTC_CR_RTC_RESET;
        MDR_BKP->RTC_PRL    = 0x00007FFB;
        MDR_BKP->RTC_ALRM   = 0;
        MDR_BKP->RTC_CS     = BKP_RTC_CS_FLAG_CLR_MASK;
        MDR_BKP->RTC_ALRMAR = 0;
        MDR_BKP->RTC_ALRMBR = 0;
        MDR_BKP->RTC_TAFCR  = 0;
        MDR_BKP->RTC_CR     = 0;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
        MDR_BKP->RTC_TMPCAL1 = 0x10C852DA;
        MDR_BKP->RTC_TMPCAL2 = 0xE6208001;
        TmpTMPCAL3           = (TmpTMPCAL3 & BKP_RTC_TMPCAL3_SWCTR_INV) | 0x00B52000;
#endif
        /* Wait for the RTC_CLK multiplexer to switch. */
        if (PrevClockSource != BKP_RTC_CLK_SRC_LSI) {
            BKP_RTC_WaitClkSwitch(PrevClockSource);
        }
    }

    /* Write BKP registers. */
    if ((Subblocks & (BKP_CONTROL | BKP_SW)) != 0) {
        MDR_BKP->LDO = TmpLDO;
    }
    if ((Subblocks & (BKP_CLK | BKP_RTC)) != 0) {
        MDR_BKP->CLK = TmpCLK;
    }
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    if ((Subblocks & (BKP_SW | BKP_RTC)) != 0) {
        MDR_BKP->RTC_TMPCAL3 = TmpTMPCAL3;
    }
#endif
}

/** @} */ /* End of the group BKP_Common_Control_Functions */

/** @addtogroup BKP_Control_Functions BKP Control Functions
 * @{
 */

/**
 * @brief  Enable or disable the JTAG interface.
 * @param  NewState: @ref FunctionalState - a new state of the JTAG interface.
 * @return None.
 */
void BKP_JTAG_Cmd(FunctionalState NewState)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TmpReg = MDR_BKP->LDO & ~(BKP_LDO_SW_OFF | BKP_LDO_TAMPF | BKP_LDO_JTAG_ON);
    if (NewState != DISABLE) {
        TmpReg |= BKP_LDO_JTAG_ON;
    }
    MDR_BKP->LDO = TmpReg;
}

/**
 * @brief  Get the JTAG interface work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the JTAG interface.
 */
FunctionalState BKP_JTAG_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_BKP->LDO & BKP_LDO_JTAG_ON) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Get WAKEUPx input state.
 * @param  Wakeup: @ref BKP_WAKEUP_TypeDef - specify a WAKEUPx input.
 * @return @ref FlagStatus - the current WAKEUPx input state.
 */
FlagStatus BKP_GetWAKEUPStatus(BKP_WAKEUP_TypeDef Wakeup)
{
    /* Check the parameters. */
    assert_param(IS_BKP_WAKEUP(Wakeup));

    if ((MDR_BKP->LDO & (uint32_t)Wakeup) != 0) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Set the internal voltage regulator trimming.
 * @param  LDO_Boost: Trimming value of the internal voltage regulator.
 *         This parameter is a value from 0x0 to 0x3, where 0x0 is a typical value.
 * @return None.
 */
void BKP_LDO_SetBoostTrim(uint8_t LDO_Boost)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_LDO_BOOST(LDO_Boost));

    TmpReg = MDR_BKP->LDO & ~(BKP_LDO_SW_OFF | BKP_LDO_TAMPF);
    TmpReg &= ~(BKP_LDO_LDO_BOOST_Msk);
    TmpReg |= (uint32_t)LDO_Boost << BKP_LDO_LDO_BOOST_Pos;
    MDR_BKP->LDO = TmpReg;
}

/**
 * @brief  Get the internal voltage regulator trimming.
 * @param  None.
 * @return Trimming value of the internal voltage regulator.
 */
uint8_t BKP_LDO_GetBoostTrim(void)
{
    return (uint8_t)((MDR_BKP->LDO & BKP_LDO_LDO_BOOST_Msk) >> BKP_LDO_LDO_BOOST_Pos);
}

/**
 * @brief  Set the internal BKP voltage regulator trimming.
 * @param  BLDO_Boost: @ref BKP_BLDO_Boost_TypeDef - trimming value of the internal BKP voltage regulator.
 * @return None.
 */
void BKP_BLDO_SetBoostTrim(BKP_BLDO_Boost_TypeDef BLDO_Boost)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_BLDO_BOOST(BLDO_Boost));

    TmpReg = MDR_BKP->LDO & ~(BKP_LDO_SW_OFF | BKP_LDO_TAMPF);
    TmpReg &= ~(BKP_LDO_BLDO_BOOST | BKP_LDO_BLDO_TRIM_Msk);
    TmpReg |= (uint32_t)BLDO_Boost;
    MDR_BKP->LDO = TmpReg;
}

/**
 * @brief  Get the internal BKP voltage regulator trimming.
 * @param  None.
 * @return @ref BKP_BLDO_Boost_TypeDef - trimming value of the internal BKP voltage regulator.
 */
BKP_BLDO_Boost_TypeDef BKP_BLDO_GetBoostTrim(void)
{
    return (BKP_BLDO_Boost_TypeDef)(MDR_BKP->LDO & (BKP_LDO_BLDO_BOOST | BKP_LDO_BLDO_TRIM_Msk));
}

/** @} */ /* End of the group BKP_Control_Functions */

/** @addtogroup BKP_Software_Functions BKP Software Functions
 * @{
 */

/**
 * @brief  Set the power on reset flag (FPOR).
 * @param  PORFlag: @ref FlagStatus - a new state of the FPOR flag.
 * @return None.
 */
void BKP_SetFlagPOR(FlagStatus PORFlag)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BIT_STATUS(PORFlag));

    TmpReg = MDR_BKP->LDO & ~(BKP_LDO_SW_OFF | BKP_LDO_TAMPF | BKP_LDO_FPOR);
    if (PORFlag != RESET) {
        TmpReg |= BKP_LDO_FPOR;
    }
    MDR_BKP->LDO = TmpReg;
}

/**
 * @brief  Get the power on reset flag (FPOR).
 * @param  None.
 * @return @ref FlagStatus - the current state of FPOR (SET or RESET).
 */
FlagStatus BKP_GetFlagPOR(void)
{
    FlagStatus Status;

    if ((MDR_BKP->LDO & BKP_LDO_FPOR) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Set the MCU boot mode (if used in bootloader).
 * @param  Mode: MCU boot mode.
 *         This parameter can be a value from 0x0 to 0x3.
 * @return None.
 */
void BKP_SetMODE(uint8_t Mode)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_MODE(Mode));

    TmpReg = MDR_BKP->LDO & ~(BKP_LDO_SW_OFF | BKP_LDO_TAMPF | BKP_LDO_MODE_Msk);
    TmpReg |= (uint32_t)Mode << BKP_LDO_MODE_Pos;
    MDR_BKP->LDO = TmpReg;
}

/**
 * @brief  Get the MCU boot mode (if used in bootloader).
 * @param  None.
 * @return MCU boot mode (if used in bootloader).
 */
uint8_t BKP_GetMODE(void)
{
    return (uint8_t)((MDR_BKP->LDO & BKP_LDO_MODE_Msk) >> BKP_LDO_MODE_Pos);
}

/** @} */ /* End of the group BKP_Software_Functions */

/** @addtogroup BKP_Emergency_Power_Supply_Control_Functions BKP Emergency Power Supply Control Functions
 * @{
 */

/**
 * @brief  Enable or disable the emergency power supply control using battery.
 * @param  NewState: @ref FunctionalState - a new state of the emergency power supply control.
 * @return None.
 */
void BKP_SW_Cmd(FunctionalState NewState)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TmpReg = MDR_BKP->LDO & ~(BKP_LDO_SW_OFF | BKP_LDO_TAMPF | BKP_LDO_SW_CNTRL);
    if (NewState != DISABLE) {
        TmpReg |= BKP_LDO_SW_CNTRL;
    }
    MDR_BKP->LDO = TmpReg;
}

/**
 * @brief  Get the emergency power supply control state.
 * @param  None.
 * @return @ref FunctionalState - the current state of the emergency power supply control.
 */
FunctionalState BKP_SW_GetCmdState(void)
{
    return (FunctionalState)((MDR_BKP->LDO & BKP_LDO_SW_CNTRL) >> BKP_LDO_SW_CNTRL_Pos);
}

/**
 * @brief  Disable the emergency power supply (clear SW_PWR to 0).
 * @param  None.
 * @return None.
 */
void BKP_SW_DisablePower(void)
{
    MDR_BKP->LDO = (MDR_BKP->LDO & ~BKP_LDO_TAMPF) | BKP_LDO_SW_OFF;
}

/**
 * @brief  Get the emergency power supply status (SW_PWR status) when SW_CNTRL = 1.
 * @param  None.
 * @return @ref FlagStatus - the current state of the emergency power supply status.
 *         This parameter can be one of the @ref FlagStatus enum values:
 *             @arg SET:   The emergency power supply is switched on (SW_PWR = 1).
 *             @arg RESET: The emergency power supply is switched off (SW_PWR = 0).
 */
FlagStatus BKP_SW_GetPowerStatus(void)
{
    FlagStatus Status;

    if ((MDR_BKP->LDO & BKP_LDO_SW_OFF) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief  Configure the BKP SW output inversion.
 * @param  Polarity: @ref BKP_SW_Polarity_TypeDef - enable or disable inversion of the BKP SW output.
 * @return None.
 */
void BKP_SW_SetPolarity(BKP_SW_Polarity_TypeDef Polarity)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_SW_POLARITY(Polarity));

    TmpReg = MDR_BKP->RTC_TMPCAL3 & ~BKP_RTC_TMPCAL3_SWCTR_INV;
    TmpReg |= (uint32_t)Polarity;
    MDR_BKP->RTC_TMPCAL3 = TmpReg;
}

/**
 * @brief  Get the BKP SW output inversion state.
 * @param  None.
 * @return @ref BKP_SW_Polarity_TypeDef - the BKP SW output inversion state.
 */
BKP_SW_Polarity_TypeDef BKP_SW_GetPolarity(void)
{
    return (BKP_SW_Polarity_TypeDef)(MDR_BKP->RTC_TMPCAL3 & BKP_RTC_TMPCAL3_SWCTR_INV);
}
#endif

/** @} */ /* End of the group BKP_Emergency_Power_Supply_Control_Functions */

/** @addtogroup BKP_Clock_Source_Control_Functions BKP Clock Source Control Functions
 * @{
 */

/**
 * @brief  HSI (High Speed Internal) clock mode selection.
 * @param  NewState: @ref FunctionalState - the mode selector (switch off (DISABLE) or on (ENABLE)).
 * @return None.
 */
void BKP_HSI_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_BKP->CLK |= BKP_CLK_HSI_ON;
    } else {
        MDR_BKP->CLK &= ~BKP_CLK_HSI_ON;
    }
}

/**
 * @brief  Get the HSI clock mode selection.
 * @param  None.
 * @return @ref FunctionalState - the current mode selector state of the HSI clock.
 */
FunctionalState BKP_HSI_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_BKP->CLK & BKP_CLK_HSI_ON) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set the HSI and LSI clock trimming.
 * @param  TrimValue: HSI and LSI frequencies trim value.
 *         This parameter must be a number from 0x00 to 0x3F.
 * @return None.
 */
void BKP_HSI_LSI_SetTrim(uint8_t TrimValue)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_HSI_LSI_TRIM_VALUE(TrimValue));

    TmpReg = MDR_BKP->CLK & ~BKP_CLK_HSI_LSI_TRIM_Msk;
    TmpReg |= (uint32_t)TrimValue << BKP_CLK_HSI_LSI_TRIM_Pos;
    MDR_BKP->CLK = TmpReg;
}

/**
 * @brief  Get the HSI and LSI clock trimming.
 * @param  None.
 * @return HSI and LSI frequencies trim value.
 */
uint8_t BKP_HSI_LSI_GetTrim(void)
{
    return (uint8_t)((MDR_BKP->CLK & BKP_CLK_HSI_LSI_TRIM_Msk) >> BKP_CLK_HSI_LSI_TRIM_Pos);
}

/**
 * @brief  HSI clock status.
 * @note   The cycle counter and core clock from SystemCoreClock are used for delay. Do not disable the cycle counter.
 *         Before calling this function, you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  None.
 * @return @ref ErrorStatus - SUCCESS if HSI clock is ready, else ERROR.
 */
ErrorStatus BKP_HSI_GetStatus(void)
{
    ErrorStatus State;
    FlagStatus  Flag;
    uint32_t    Ticks;

    /* Calculates the number of ticks according to the current clock frequency */
    Ticks = (SystemCoreClock * HSIRDY_TIMEOUT_TICK) / HSI_CLK_FREQUENCY_TYP_Hz;

    /* Wait until HSI time out has occurred. */
    DELAY_CycleCounter_WaitTicksAsm(Ticks);

    Flag = BKP_CLK_GetFlagStatus(BKP_FLAG_HSIRDY);

    if (Flag != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  LSI (Low Speed Internal) clock mode selection.
 * @param  NewState: @ref FunctionalState - the mode selector (switch off (DISABLE) or on (ENABLE)).
 * @return None.
 */
void BKP_LSI_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_BKP->CLK |= BKP_CLK_LSI_ON;
    } else {
        MDR_BKP->CLK &= ~BKP_CLK_LSI_ON;
    }
}

/**
 * @brief  Get the LSI clock mode selection.
 * @param  None.
 * @return @ref FunctionalState - the current mode selector state of the LSI clock.
 */
FunctionalState BKP_LSI_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_BKP->CLK & BKP_CLK_LSI_ON) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  LSI clock status.
 * @note   The cycle counter and core clock from SystemCoreClock are used for delay. Do not disable the cycle counter.
 *         Before calling this function, you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  None.
 * @return @ref ErrorStatus - SUCCESS if LSI clock is ready, else ERROR.
 */
ErrorStatus BKP_LSI_GetStatus(void)
{
    ErrorStatus State;
    FlagStatus  Flag;
    uint32_t    Ticks;

    /* Calculates the number of ticks according to the current clock frequency */
    Ticks = (SystemCoreClock * LSIRDY_TIMEOUT_TICK) / LSI_FREQUENCY_Hz;

    /* Wait until LSI time out has occurred. */
    DELAY_CycleCounter_WaitTicksAsm(Ticks);

    Flag = BKP_CLK_GetFlagStatus(BKP_FLAG_LSIRDY);

    if (Flag != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  LSE (Low Speed External) clock mode and source selection based on @ref LSE_EXT_GEN_MODE definition.
 * @param  NewState: @ref FunctionalState - a new state of the LSE clock.
 * @return None.
 */
void BKP_LSE_Cmd(FunctionalState NewState)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

#if !defined(LSE_EXT_GEN_MODE)
    TmpReg = MDR_BKP->CLK & ~(BKP_CLK_LSE_BYP | BKP_CLK_LSE_ON);
    if (NewState == DISABLE) {
        MDR_BKP->CLK = TmpReg;
    } else {
        MDR_BKP->CLK = TmpReg | BKP_CLK_LSE_ON;
    }
#else
    TmpReg = MDR_BKP->CLK | (BKP_CLK_LSE_BYP | BKP_CLK_LSE_ON);
    if (NewState == DISABLE) {
        MDR_BKP->CLK = TmpReg & ~BKP_CLK_LSE_ON;
    } else {
        MDR_BKP->CLK = TmpReg;
    }
#endif
}

/**
 * @brief  LSE (Low Speed External) clock mode and source selection.
 * @param  LSEMode: @ref BKP_LSE_Mode_TypeDef - the mode selector.
 * @return None.
 */
void BKP_LSE_Config(BKP_LSE_Mode_TypeDef LSEMode)
{
    /* Check the parameters. */
    assert_param(IS_BKP_LSE_MODE(LSEMode));

    MDR_BKP->CLK &= ~(BKP_CLK_LSE_ON | BKP_CLK_LSE_BYP);
    MDR_BKP->CLK |= (uint32_t)LSEMode;
}

/**
 * @brief  Get the LSE clock mode and source selection.
 * @param  None.
 * @return @ref BKP_LSE_Mode_TypeDef - current LSE mode mode and source selection.
 */
BKP_LSE_Mode_TypeDef BKP_LSE_GetModeConfig(void)
{
    return (BKP_LSE_Mode_TypeDef)(MDR_BKP->CLK & (BKP_CLK_LSE_ON | BKP_CLK_LSE_BYP));
}

/**
 * @brief  Get LSE clock status.
 * @note   The cycle counter and core clock from SystemCoreClock are used for delay. Do not disable the cycle counter.
 *         Before calling this function, you must update SystemCoreClock by calling SystemCoreClockUpdate().
 *         If the LSERDY_USER_TIMEOUT_MS definition is active, the start time for MDR1206 is calculated based on the resonator characteristics.
 * @param  None.
 * @return @ref ErrorStatus - SUCCESS if LSE clock is ready, else ERROR.
 */
ErrorStatus BKP_LSE_GetStatus(void)
{
    uint32_t    DelayConst;
    ErrorStatus State;
    FlagStatus  Flag;

    DelayConst = DELAY_CYCLE_COUNTER_GET_CONST_US(SystemCoreClock);

    /* Wait until LSE time out has occurred. */
#if defined(LSERDY_USER_TIMEOUT_MS)

/** Pi - Pi (to the tenth digit) for calculating startup time LSE. */
#define Pi (3.1415926535f)
/** Omega - cyclic frequency. */
#define Omega (2 * Pi * QUARTZ_FREQUENCY_LSE_Hz)
/** K - proportionality coefficient. Gm - transconductance of the amplifying transistor (A/V).
 * Internal microcontroller characteristics for the LSE generator.
 * Specified in the documentation and differs for CHIP_ID = 215 and CHIP_ID = 217. */
#define K_MDR1206AFI  35
#define K_MDR1206FI   12
#define Gm_MDR1206AFI (152e-6f)
#define Gm_MDR1206FI  (694e-6f)
/** Auxiliary components in calculating the start time. */
#define Comp                         (C_LOAD_LSE * C_LOAD_LSE + C_SHUNT_LSE * C_LOAD_LSE)
#define Slave_Numerator_MDR1206AFI   (4 * Gm_MDR1206AFI * C_LOAD_LSE * C_LOAD_LSE)
#define Slave_Numerator_MDR1206FI    (4 * Gm_MDR1206FI * C_LOAD_LSE * C_LOAD_LSE)
#define Slave_Denominator_MDR1206AFI ((Gm_MDR1206AFI * C_SHUNT_LSE * Gm_MDR1206AFI * C_SHUNT_LSE) + (16 * Omega * Omega * Comp * Comp))
#define Slave_Denominator_MDR1206FI  ((Gm_MDR1206FI * C_SHUNT_LSE * Gm_MDR1206FI * C_SHUNT_LSE) + (16 * Omega * Omega * Comp * Comp))

    volatile float Fraction, Main_Denominator, T_Start;

    /* Main startup time calculation */
    if (GetChipID() == CHIP_ID_MDR1206AFI) {
        Fraction         = Slave_Numerator_MDR1206AFI / Slave_Denominator_MDR1206AFI;
        Main_Denominator = Omega * (Fraction - RM_LSE);
        T_Start          = K_MDR1206AFI * ((QUALITY_FACTOR_LSE * RM_LSE) / Main_Denominator);
    } else {
        Fraction         = Slave_Numerator_MDR1206FI / Slave_Denominator_MDR1206FI;
        Main_Denominator = Omega * (Fraction - RM_LSE);
        T_Start          = K_MDR1206FI * ((QUALITY_FACTOR_LSE * RM_LSE) / Main_Denominator);
    }
    /* Convert seconds to milliseconds */
    T_Start *= 1000;

    DELAY_CycleCounter_WaitTicksAsm(DELAY_GET_TICKS_MS(((uint32_t)T_Start), DelayConst));
#else
    DELAY_CycleCounter_WaitTicksAsm(DELAY_GET_TICKS_MS(LSERDY_TIMEOUT_MS, DelayConst));
#endif

    Flag = BKP_CLK_GetFlagStatus(BKP_FLAG_LSERDY);

    if (Flag != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  LSE (Low Speed External) clock operation configuration.
 * @param  LSEConf: LSE working mode configuration.
 * @note   Default value is 0x0. In case of problems with startup with
 *         the default value of the LSEConf configuration[1:0] = 00,
 *         the generator should be started with other three configurations - 0x1, 0x2 or 0x3.
 *         Other configurations are less sensitive to the interference,
 *         but have a higher current consumption.
 * @return None.
 */
void BKP_LSE_SetWorkConfig(uint8_t LSEConf)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_LSE_CONF(LSEConf));

    TmpReg = MDR_BKP->CLK & ~BKP_CLK_LSE_CONF_Msk;
    TmpReg |= (uint32_t)LSEConf << BKP_CLK_LSE_CONF_Pos;
    MDR_BKP->CLK = TmpReg;
}

/**
 * @brief  Check whether a specified BKP CLK ready flag is set or not.
 * @param  Flag: @ref BKP_CLK_Flags_TypeDef - specify the clock generator ready flag to check.
 * @return @ref FlagStatus - a state of BKP CLK ready flag (SET or RESET).
 */
FlagStatus BKP_CLK_GetFlagStatus(BKP_CLK_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_BKP_CLK_FLAG(Flag));

    if ((MDR_BKP->CLK & (uint32_t)Flag) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}
/** @} */ /* End of the group BKP_Clock_Source_Control_Functions */

/** @addtogroup BKP_RTC_Control_Functions BKP RTC Control Functions
 * @{
 */

/**
  * @brief  Enable or disable the RTC reset.
            The RTC registers are set to their default reset values on reset.
  * @param  NewState: @ref FunctionalState - a new state of the RTC reset.
  * @return None.
  */
void BKP_RTC_Reset(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_BKP->RTC_CR |= BKP_RTC_CR_RTC_RESET;
    } else {
        MDR_BKP->RTC_CR &= ~BKP_RTC_CR_RTC_RESET;
    }
}

/**
 * @brief  Enable or disable the RTC.
 * @param  NewState: @ref FunctionalState - a new state of the RTC.
 * @return None.
 */
void BKP_RTC_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_BKP->RTC_CR |= BKP_RTC_CR_RTC_EN;
    } else {
        MDR_BKP->RTC_CR &= ~BKP_RTC_CR_RTC_EN;
    }
}

/**
 * @brief  Get the RTC work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the RTC.
 */
FunctionalState BKP_RTC_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_BKP->RTC_CR & BKP_RTC_CR_RTC_EN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Wait until the last write operation on RTC registers has finished.
 * @note   This function must be called before any write to the following RTC registers:
 *         RTC_WUTR, RTC_PREDIV_S, RTC_TR, RTC_DR.
 * @param  None.
 * @return None.
 */
void BKP_RTC_WaitForUpdate(void)
{
    /* Loop while WEC flag is not reset. */
    while ((MDR_BKP->RTC_CS & BKP_RTC_CS_WEC) != 0) { }
}

/**
 * @brief  Configure the RTC clock source.
 * @note   Switching the RTC_CLK frequency requires both frequency sources to be enabled.
 *         Exception: first switch from a disabled LSI to another source after a power reset.
 *         In this case, enabling the LSI frequency is not necessary.
 * @note   To wait for a valid RTC_CLK frequency after switching use BKP_RTC_WaitClkSwitch().
 * @param  ClockSource: @ref BKP_RTC_ClockSource_TypeDef - specify the RTC clock source.
 * @return None.
 */
void BKP_RTC_SetClkSource(BKP_RTC_ClockSource_TypeDef ClockSource)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_CLOCK_SOURCE(ClockSource));

    TmpReg = MDR_BKP->RTC_CR & ~BKP_RTC_CR_RTC_SEL_Msk;
    TmpReg |= (uint32_t)ClockSource;
    MDR_BKP->RTC_CR = TmpReg;
}

/**
 * @brief  Get the RTC clock source.
 * @param  None.
 * @return @ref BKP_RTC_ClockSource_TypeDef - the RTC clock source.
 */
BKP_RTC_ClockSource_TypeDef BKP_RTC_GetClkSource(void)
{
    return (BKP_RTC_ClockSource_TypeDef)(MDR_BKP->RTC_CR & BKP_RTC_CR_RTC_SEL_Msk);
}

/**
 * @brief  Wait for the RTC_CLK multiplexer to switch for the selected clock source (3 periods of the frequency).
 * @note   A valid RTC_CLK is formed after 3 periods of the frequency from which switching occurs (1st call BKP_RTC_WaitClkSwitch()),
 *         plus 3 periods of the frequency to which switching occurs (2nd call BKP_RTC_WaitClkSwitch()).
 *         Exception: first switch from a disabled LSI to another source after a power reset. In this case,
 *         a valid RTC_CLK is formed after 3 periods of the frequency to which the switching occurs.
 * @note   The cycle counter and core clock from SystemCoreClock are used for delay. Do not disable the cycle counter.
 *         Before calling this function, you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  ClockSource: @ref BKP_RTC_ClockSource_TypeDef - specify the RTC clock source.
 * @return None.
 */
void BKP_RTC_WaitClkSwitch(BKP_RTC_ClockSource_TypeDef ClockSource)
{
    uint32_t RTC_Freq, Ticks, TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_CLOCK_SOURCE(ClockSource));

    switch (ClockSource) {
        case BKP_RTC_CLK_SRC_LSI:
            RTC_Freq = LSI_FREQUENCY_Hz;
            break;
        case BKP_RTC_CLK_SRC_LSE:
            RTC_Freq = LSE_FREQUENCY_Hz;
            break;
        case BKP_RTC_CLK_SRC_HSI_RTC:
            TmpReg = MDR_RST_CLK->RTC_CLOCK >> RST_CLK_RTC_CLOCK_HSI_SEL_Pos;
            if ((TmpReg & ((uint32_t)0x8)) == 0) {
                RTC_Freq = HSI_FREQUENCY_Hz;
            } else {
                RTC_Freq = HSI_FREQUENCY_Hz >> ((TmpReg & ((uint32_t)0x7)) + 1);
            }
            break;
        case BKP_RTC_CLK_SRC_HSE_RTC:
            TmpReg = MDR_RST_CLK->RTC_CLOCK;
            if ((TmpReg & ((uint32_t)0x8)) == 0) {
                RTC_Freq = HSE_FREQUENCY_Hz;
            } else {
                RTC_Freq = HSE_FREQUENCY_Hz >> ((TmpReg & ((uint32_t)0x7)) + 1);
            }
            break;
        default:
            RTC_Freq = 0;
            break;
    }

    if (RTC_Freq != 0) {
        /* Calculates the number of ticks according to the current clock frequency. */
        Ticks = (SystemCoreClock * BKP_RTC_CLK_MUX_SWITCH_TICK) / RTC_Freq;

        /* Wait for the RTC_CLK multiplexer to switch. */
        DELAY_CycleCounter_WaitTicksAsm(Ticks);
    }
}

/**
 * @brief  Configure the RTC_CLK clock calibration value.
 * @note   After writing, the internal register is updated after 2 clock cycles of the RTC_CLK frequency.
 * @param  Calibration: specify the number of RTC_CLK clocks out of 2^20 to be discarded.
 *         This parameter can be a number from 0x00 to 0xFF.
 * @return None.
 */
void BKP_RTC_SetClkCalibration(uint8_t Calibration)
{
    uint32_t TmpReg;

    TmpReg = MDR_BKP->RTC_CR & ~BKP_RTC_CR_RTC_CAL_Msk;
    TmpReg |= (uint32_t)Calibration << BKP_RTC_CR_RTC_CAL_Pos;
    MDR_BKP->RTC_CR = TmpReg;
}

/**
 * @brief  Get the RTC_CLK clock calibration value.
 * @param  None.
 * @return RTC_CLK clock calibration value.
 */
uint8_t BKP_RTC_GetClkCalibration(void)
{
    return (uint8_t)((MDR_BKP->RTC_CR & BKP_RTC_CR_RTC_CAL_Msk) >> BKP_RTC_CR_RTC_CAL_Pos);
}

/**
 * @brief  Set the RTC_CLK prescaler counter value.
 * @note   Before calling this function, you must wait until the last write to the RTC registers is completed by calling BKP_RTC_WaitForUpdate().
 * @param  PrescalerCounterValue: a new value of the RTC_CLK prescaler counter.
 *         This parameter can be a number from 0x00000000 to 0x000FFFFF.
 * @return None.
 */
void BKP_RTC_SetPrescalerCounter(uint32_t PrescalerCounterValue)
{
    /* Check the parameters. */
    assert_param(IS_BKP_RTC_PRESCALER_COUNTER_VALUE(PrescalerCounterValue));

    MDR_BKP->RTC_PREDIV_S = PrescalerCounterValue;
}

/**
 * @brief  Get the RTC_CLK prescaler counter value.
 * @param  None.
 * @return RTC_CLK prescaler counter value.
 */
uint32_t BKP_RTC_GetPrescalerCounter(void)
{
    return MDR_BKP->RTC_PREDIV_S;
}

/**
 * @brief  Set the value of the RTC_CLK prescaler.
 * @note   Frequency SEC_CLK = RTC_CLK / (PrescalerValue + 1).
 * @note   After writing, the internal register is updated after 2 clock cycles of the RTC_CLK frequency.
 * @param  PrescalerValue: a new value of the RTC_CLK prescaler.
 *         This parameter can be a number from 0x00000000 to 0x000FFFFF.
 * @return None.
 */
void BKP_RTC_SetPrescaler(uint32_t PrescalerValue)
{
    /* Check the parameters. */
    assert_param(IS_BKP_RTC_PRESCALER_VALUE(PrescalerValue));

    MDR_BKP->RTC_PRL = PrescalerValue;
}

/**
 * @brief  Get the value of the RTC_CLK prescaler.
 * @note   Frequency SEC_CLK = RTC_CLK / (PrescalerValue + 1).
 * @param  None.
 * @return RTC_CLK prescaler value.
 */
uint32_t BKP_RTC_GetPrescaler(void)
{
    return MDR_BKP->RTC_PRL;
}

/**
 * @brief  Set the date and time in BCD format.
 * @param  RTC_DateTime: The pointer to the @ref BKP_RTC_DateTime_TypeDef structure
 *         that is used for the date and time initialization.
 * @param  SetDate: @ref BitStatus - a date should be set.
 * @param  SetTime: @ref BitStatus - time should be set.
 * @return None.
 */
void BKP_RTC_SetDateTimeBCD(const BKP_RTC_DateTime_TypeDef* RTC_DateTime, BitStatus SetDate, BitStatus SetTime)
{
    uint32_t TmpReg1, TmpReg2;

    /* Check the parameters. */
    assert_param(IS_BIT_STATUS(SetDate));
    assert_param(IS_BIT_STATUS(SetTime));

    assert_param(SetDate ? IS_BKP_RTC_BCD_YEARS(RTC_DateTime->RTC_Year) : 1);
    assert_param(SetDate ? IS_BKP_RTC_BCD_MONTH(RTC_DateTime->RTC_Month) : 1);
    assert_param(SetDate ? IS_BKP_RTC_BCD_DAY(RTC_DateTime->RTC_Day) : 1);
    assert_param(SetDate ? IS_BKP_RTC_WEEKDAY(RTC_DateTime->RTC_WeekDay) : 1);

    assert_param(SetTime ? IS_BKP_RTC_TIME_FORMAT(RTC_DateTime->RTC_TimeFormat) : 1);
    assert_param(SetTime ? (((RTC_DateTime->RTC_TimeFormat) == BKP_RTC_FMT_12H) ? IS_BKP_RTC_BCD_PM_HOUR(RTC_DateTime->RTC_Hours) : IS_BKP_RTC_BCD_HOUR(RTC_DateTime->RTC_Hours)) : 1);
    assert_param(SetTime ? IS_BKP_RTC_BCD_MIN_SECS(RTC_DateTime->RTC_Minutes) : 1);
    assert_param(SetTime ? IS_BKP_RTC_BCD_MIN_SECS(RTC_DateTime->RTC_Seconds) : 1);

    if (SetDate || SetTime) {
        TmpReg1         = MDR_BKP->RTC_CR;
        MDR_BKP->RTC_CR = TmpReg1 & ~BKP_RTC_CR_RTC_EN;

        BKP_RTC_WaitForUpdate();
        if (SetDate == SET) {
            TmpReg2 = ((uint32_t)RTC_DateTime->RTC_Year << BKP_RTC_DR_YU_Pos) |
                      ((uint32_t)RTC_DateTime->RTC_Month << BKP_RTC_DR_MU_Pos) |
                      ((uint32_t)RTC_DateTime->RTC_Day << BKP_RTC_DR_DU_Pos) |
                      ((uint32_t)RTC_DateTime->RTC_WeekDay << BKP_RTC_DR_WDU_Pos);
            MDR_BKP->RTC_DR = TmpReg2;
            BKP_RTC_WaitForUpdate();
        }

        if (SetTime == SET) {
            TmpReg2 = ((uint32_t)RTC_DateTime->RTC_TimeFormat << BKP_RTC_TR_PM_Pos) |
                      ((uint32_t)RTC_DateTime->RTC_Hours << BKP_RTC_TR_HU_Pos) |
                      ((uint32_t)RTC_DateTime->RTC_Minutes << BKP_RTC_TR_MNU_Pos) |
                      ((uint32_t)RTC_DateTime->RTC_Seconds << BKP_RTC_TR_SU_Pos);
            MDR_BKP->RTC_TR = TmpReg2;
            BKP_RTC_WaitForUpdate();
        }

        MDR_BKP->RTC_CR = TmpReg1;
    }
}

/**
 * @brief  Get the date and time in BCD format.
 * @param  RTC_DateTime: The pointer to the @ref BKP_RTC_DateTime_TypeDef structure
 *         where the date should be stored.
 * @return None.
 */
void BKP_RTC_GetDateTimeBCD(BKP_RTC_DateTime_TypeDef* RTC_DateTime)
{
    uint32_t TempTR, TempDR;

    do {
        TempTR = MDR_BKP->RTC_TR;
        TempDR = MDR_BKP->RTC_DR;
    } while (TempTR != MDR_BKP->RTC_TR); /* Race condition. */

    BKP_RTC_GetDateTimeReg(TempDR, TempTR, RTC_DateTime);
}

/**
 * @brief  Set the date and time in BCD format for a specified alarm.
 * @param  RTC_Alarm: @ref BKP_RTC_Alarm_TypeDef - select the alarm to initialize.
 * @param  RTC_AlarmDateTime: The pointer to the @ref BKP_RTC_AlarmDateTime_TypeDef structure
 *         that is used for the date and time alarm initialization.
 * @return None.
 */
void BKP_RTC_SetAlarmBCD(BKP_RTC_Alarm_TypeDef RTC_Alarm, const BKP_RTC_AlarmDateTime_TypeDef* RTC_AlarmDateTime)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_ALARM(RTC_Alarm));
    assert_param(IS_FUNCTIONAL_STATE(RTC_AlarmDateTime->RTC_IgnoreDate));
    assert_param(IS_FUNCTIONAL_STATE(RTC_AlarmDateTime->RTC_UseWeekDayInsteadDays));
    assert_param(IS_FUNCTIONAL_STATE(RTC_AlarmDateTime->RTC_IgnoreMinutes));
    assert_param(IS_FUNCTIONAL_STATE(RTC_AlarmDateTime->RTC_IgnoreSeconds));

    assert_param((RTC_AlarmDateTime->RTC_IgnoreDate) ? 1 : (RTC_AlarmDateTime->RTC_UseWeekDayInsteadDays ? IS_BKP_RTC_WEEKDAY(RTC_AlarmDateTime->RTC_WeekDay) : 1));
    assert_param((RTC_AlarmDateTime->RTC_IgnoreDate) ? 1 : (RTC_AlarmDateTime->RTC_UseWeekDayInsteadDays ? 1 : IS_BKP_RTC_BCD_DAY(RTC_AlarmDateTime->RTC_Day)));

    assert_param((RTC_AlarmDateTime->RTC_IgnoreHours) ? 1 : IS_BKP_RTC_TIME_FORMAT(RTC_AlarmDateTime->RTC_TimeFormat));
    assert_param((RTC_AlarmDateTime->RTC_IgnoreHours) ? 1 : (((RTC_AlarmDateTime->RTC_TimeFormat) == BKP_RTC_FMT_12H) ? IS_BKP_RTC_BCD_PM_HOUR(RTC_AlarmDateTime->RTC_Hours) : IS_BKP_RTC_BCD_HOUR(RTC_AlarmDateTime->RTC_Hours)));
    assert_param((RTC_AlarmDateTime->RTC_IgnoreMinutes) ? 1 : IS_BKP_RTC_BCD_MIN_SECS(RTC_AlarmDateTime->RTC_Minutes));
    assert_param((RTC_AlarmDateTime->RTC_IgnoreSeconds) ? 1 : IS_BKP_RTC_BCD_MIN_SECS(RTC_AlarmDateTime->RTC_Seconds));

    /* Form a new value. */
    TmpReg = ((uint32_t)(RTC_AlarmDateTime->RTC_Seconds) << BKP_RTC_ALARMxR_SU_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_IgnoreSeconds) << BKP_RTC_ALARMxR_MSK1_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_Minutes) << BKP_RTC_ALARMxR_MNU_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_IgnoreMinutes) << BKP_RTC_ALARMxR_MSK2_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_Hours) << BKP_RTC_ALARMxR_HU_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_TimeFormat) << BKP_RTC_ALARMxR_PM_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_IgnoreHours) << BKP_RTC_ALARMxR_MSK3_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_UseWeekDayInsteadDays) << BKP_RTC_ALARMxR_WDSEL_Pos) |
             ((uint32_t)(RTC_AlarmDateTime->RTC_IgnoreDate) << BKP_RTC_ALARMxR_MSK4_Pos);

    if (RTC_AlarmDateTime->RTC_UseWeekDayInsteadDays != DISABLE) {
        TmpReg |= (uint32_t)(RTC_AlarmDateTime->RTC_WeekDay) << BKP_RTC_ALARMxR_DU_Pos;
    } else {
        TmpReg |= (uint32_t)(RTC_AlarmDateTime->RTC_Day) << BKP_RTC_ALARMxR_DU_Pos;
    }

    /* Write a value. */
    if (RTC_Alarm == BKP_RTC_ALARM_A) {
        MDR_BKP->RTC_ALRMAR = TmpReg;
    } else { /* (RTC_Alarm == BKP_RTC_ALARM_B) */
        MDR_BKP->RTC_ALRMBR = TmpReg;
    }
}

/**
 * @brief  Get the date and time in BCD format for a specified alarm.
 * @param  RTC_Alarm: @ref BKP_RTC_Alarm_TypeDef - select an alarm to read.
 * @param  RTC_AlarmDateTime: The pointer to the @ref BKP_RTC_AlarmDateTime_TypeDef structure
 *         where the date should be stored.
 * @return None.
 */
void BKP_RTC_GetAlarmBCD(BKP_RTC_Alarm_TypeDef RTC_Alarm, BKP_RTC_AlarmDateTime_TypeDef* RTC_AlarmDateTime)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_ALARM(RTC_Alarm));

    /* Get a register value. */
    if (RTC_Alarm == BKP_RTC_ALARM_A) {
        TmpReg = MDR_BKP->RTC_ALRMAR;
    } else {
        TmpReg = MDR_BKP->RTC_ALRMBR;
    }

    RTC_AlarmDateTime->RTC_Seconds               = (uint8_t)((TmpReg & BKP_RTC_ALARM_SECONDS_MASK) >> BKP_RTC_ALARMxR_SU_Pos);
    RTC_AlarmDateTime->RTC_IgnoreSeconds         = (FunctionalState)((TmpReg & BKP_RTC_ALARMxR_MSK1) >> BKP_RTC_ALARMxR_MSK1_Pos);
    RTC_AlarmDateTime->RTC_Minutes               = (uint8_t)((TmpReg & BKP_RTC_ALARM_MINUTES_MASK) >> BKP_RTC_ALARMxR_MNU_Pos);
    RTC_AlarmDateTime->RTC_IgnoreMinutes         = (FunctionalState)((TmpReg & BKP_RTC_ALARMxR_MSK2) >> BKP_RTC_ALARMxR_MSK2_Pos);
    RTC_AlarmDateTime->RTC_Hours                 = (uint8_t)((TmpReg & BKP_RTC_ALARM_HOURS_MASK) >> BKP_RTC_ALARMxR_HU_Pos);
    RTC_AlarmDateTime->RTC_TimeFormat            = (BKP_RTC_FMT_TypeDef)((TmpReg & BKP_RTC_ALARMxR_PM) >> BKP_RTC_ALARMxR_PM_Pos);
    RTC_AlarmDateTime->RTC_IgnoreHours           = (FunctionalState)((TmpReg & BKP_RTC_ALARMxR_MSK3) >> BKP_RTC_ALARMxR_MSK3_Pos);
    RTC_AlarmDateTime->RTC_UseWeekDayInsteadDays = (FunctionalState)((TmpReg & BKP_RTC_ALARMxR_WDSEL) >> BKP_RTC_ALARMxR_WDSEL_Pos);
    RTC_AlarmDateTime->RTC_IgnoreDate            = (FunctionalState)((TmpReg & BKP_RTC_ALARMxR_MSK4) >> BKP_RTC_ALARMxR_MSK4_Pos);

    if (RTC_AlarmDateTime->RTC_UseWeekDayInsteadDays != DISABLE) {
        RTC_AlarmDateTime->RTC_WeekDay = (BKP_RTC_WeekDays_TypeDef)((TmpReg & BKP_RTC_ALARMxR_DU_Msk) >> BKP_RTC_ALARMxR_DU_Pos);
    } else {
        RTC_AlarmDateTime->RTC_Day = (uint8_t)((TmpReg & BKP_RTC_ALARM_DATE_MASK) >> BKP_RTC_ALARMxR_DU_Pos);
    }
}

/** @addtogroup BKP_RTC_WUT_Control_Functions BKP RTC WUT Control Functions
 * @{
 */

/**
 * @brief  Configure the RTC WUT clock source.
 * @note   RTC WUT works when RTC is enabled (RTC_EN = 1 in the BKP_RTC_CR register).
 * @param  ClockSource: @ref BKP_RTC_WUT_ClockSource_TypeDef - specify the RTC WUT clock source.
 * @return None.
 */
void BKP_RTC_WUT_SetClkSource(BKP_RTC_WUT_ClockSource_TypeDef ClockSource)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_WUT_CLOCK_SOURCE(ClockSource));

    TmpReg = MDR_BKP->RTC_CR & ~BKP_RTC_CR_WUCK_SEL_Msk;
    TmpReg |= (uint32_t)ClockSource;
    MDR_BKP->RTC_CR = TmpReg;
}

/**
 * @brief  Get the RTC WUT clock source.
 * @param  None.
 * @return @ref BKP_RTC_WUT_ClockSource_TypeDef - the RTC WUT clock source.
 */
BKP_RTC_WUT_ClockSource_TypeDef BKP_RTC_WUT_GetClkSource(void)
{
    return (BKP_RTC_WUT_ClockSource_TypeDef)(MDR_BKP->RTC_CR & BKP_RTC_CR_WUCK_SEL_Msk);
}

/**
 * @brief  Set the RTC WUT counter value.
 * @note   Before calling this function, you must wait until the last write to the RTC registers is completed by calling BKP_RTC_WaitForUpdate().
 * @param  CounterValue: a new value of the RTC WUT counter.
 * @return None.
 */
void BKP_RTC_WUT_SetCounter(uint32_t CounterValue)
{
    MDR_BKP->RTC_WUTR = CounterValue;
}

/**
 * @brief  Get the RTC WUT counter value.
 * @param  None.
 * @return RTC WUT counter value.
 */
uint32_t BKP_RTC_WUT_GetCounter(void)
{
    return MDR_BKP->RTC_WUTR;
}

/**
 * @brief  Set the RTC WUT alarm value.
 * @note   After writing, the internal register is updated after 2 clock cycles of the RTC_CLK frequency.
 * @param  AlarmValue: a new value of the RTC WUT alarm.
 * @return None.
 */
void BKP_RTC_WUT_SetAlarm(uint32_t AlarmValue)
{
    MDR_BKP->RTC_ALRM = AlarmValue;
}

/**
 * @brief  Get the RTC WUT alarm value.
 * @param  None.
 * @return RTC WUT alarm value.
 */
uint32_t BKP_RTC_WUT_GetAlarm(void)
{
    return MDR_BKP->RTC_ALRM;
}

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief  Set the configuration behaviour the BKP SW output state (SW_PWR) on WUT alarm event.
 * @param  SWControl: @ref BKP_RTC_WUT_SWControl_TypeDef - the BKP SW output state configuration behaviour (SW_PWR) on WUT alarm event.
 * @return None.
 */
void BKP_RTC_WUT_SetSWControl(BKP_RTC_WUT_SWControl_TypeDef SWControl)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_WUT_SW_CONTROL(SWControl));

    TmpReg = MDR_BKP->RTC_TAFCR & ~(BKP_RTC_TAFCR_FLAG_CLR_MASK | BKP_RTC_TAFCR_WAKE_SLEEP);
    TmpReg |= (uint32_t)SWControl;
    MDR_BKP->RTC_TAFCR = TmpReg;
}

/**
 * @brief  Get the configuration behaviour of the BKP SW output state (SW_PWR) on WUT alarm event.
 * @param  None.
 * @return @ref BKP_RTC_WUT_SWControl_TypeDef - the BKP SW output state configuration behaviour (SW_PWR) on WUT alarm event.
 */
BKP_RTC_WUT_SWControl_TypeDef BKP_RTC_WUT_GetSWControl(void)
{
    return (BKP_RTC_WUT_SWControl_TypeDef)(MDR_BKP->RTC_TAFCR & BKP_RTC_TAFCR_WAKE_SLEEP);
}
#endif

/** @} */ /* End of the group BKP_RTC_WUT_Control_Functions */

/** @addtogroup BKP_RTC_Event_Detection_Control_Functions BKP RTC Event Detection Control Functions
 * @{
 */

/**
 * @brief  Enable or disable the event detection on WAKEUPx inputs for the specified TAMPER.
 * @param  Tampers: TAMPER event detection.
 *         This parameter can be any combination of @ref BKP_RTC_TAMPER_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the TAMPER event detection.
 * @return None.
 */
void BKP_RTC_TAMPER_Cmd(uint32_t Tampers, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_BKP_RTC_TAMPERS(Tampers));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

#if defined(USE_MDR32F02_REV_1X)
    if (NewState != DISABLE) {
        MDR_BKP->RTC_TAFCR |= Tampers;
    } else {
        MDR_BKP->RTC_TAFCR &= ~Tampers;
    }
#else
    if (NewState != DISABLE) {
        MDR_BKP->RTC_TAFCR = (MDR_BKP->RTC_TAFCR & ~(BKP_RTC_TAFCR_FLAG_CLR_MASK | BKP_RTC_TAFCR_TAMP_EN)) | Tampers;
    } else {
        MDR_BKP->RTC_TAFCR = (MDR_BKP->RTC_TAFCR & ~(BKP_RTC_TAFCR_FLAG_CLR_MASK | BKP_RTC_TAFCR_TAMP_EN)) & ~Tampers;
    }
#endif
}

/**
 * @brief  Get the work state of the event detection on WAKEUPx inputs for the specified TAMPER.
 * @param  Tampers: @ref BKP_RTC_TAMPER_TypeDef - TAMPER event detection.
 * @return @ref FunctionalState - the current work state of the TAMPER event detection.
 */
FunctionalState BKP_RTC_TAMPER_GetCmdState(BKP_RTC_TAMPER_TypeDef Tampers)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_TAMPER(Tampers));

    if ((MDR_BKP->RTC_TAFCR & (uint32_t)Tampers) == (uint32_t)Tampers) {
        State = ENABLE;
    } else {
        State = DISABLE;
    }

    return State;
}

/**
 * @brief  Set the capture event for the specified TAMPER WAKEUPx input.
 * @param  Wakeups: Specify the TAMPER WAKEUPx inputs for which the capture event will be set.
 *         This parameter can be any combination of @ref BKP_RTC_TAMPER_Wakeup_TypeDef values.
 * @param  Event: @ref BKP_RTC_TAMPER_Event_TypeDef - capture event on specified WAKEUPx inputs.
 * @return None.
 */
void BKP_RTC_TAMPER_SetEvent(uint32_t Wakeups, BKP_RTC_TAMPER_Event_TypeDef Event)
{
    uint32_t Pos;
    uint32_t Mask;
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_TAMPER_WAKEUPS(Wakeups));
    assert_param(IS_BKP_RTC_TAMPER_EVENT(Event));

    Pos = 0;
#if defined(USE_MDR32F02_REV_1X)
    Mask   = BKP_RTC_TAFCR_TAMP_TRG1;
    TmpReg = MDR_BKP->RTC_TAFCR;
#else
    Mask   = BKP_RTC_TAFCR_TAMP_TRG1 | BKP_RTC_TAFCR_TAMP_EDGE_W1 | BKP_RTC_TAFCR_TAMP_LEVEL_W1;
    TmpReg = MDR_BKP->RTC_TAFCR & ~BKP_RTC_TAFCR_FLAG_CLR_MASK;
#endif
    for (; Wakeups && Pos < 3; Wakeups >>= 1, Pos++) {
        if ((Wakeups & 0x1) != 0) {
            TmpReg = (TmpReg & ~(Mask << Pos)) | ((uint32_t)Event << Pos);
        }
    }
    MDR_BKP->RTC_TAFCR = TmpReg;
}

/**
 * @brief  Enable or disable the TIMESTAMP event detection on WAKEUP3-WAKEUP1 inputs.
 * @note   TIMESTAMP works when RTC is enabled (RTC_EN = 1 in the BKP_RTC_CR register).
 * @param  NewState: @ref FunctionalState - a new state of the TIMESTAMP event detection.
 * @return None.
 */
void BKP_RTC_TIMESTAMP_Cmd(FunctionalState NewState)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

#if defined(USE_MDR32F02_REV_1X)
    TmpReg = MDR_BKP->RTC_TAFCR & ~BKP_RTC_TAFCR_TS_EN;
#else
    TmpReg = MDR_BKP->RTC_TAFCR & ~(BKP_RTC_TAFCR_FLAG_CLR_MASK | BKP_RTC_TAFCR_TS_EN);
#endif
    if (NewState != DISABLE) {
        TmpReg |= BKP_RTC_TAFCR_TS_EN;
    }
    MDR_BKP->RTC_TAFCR = TmpReg;
}

/**
 * @brief  Get the work state of the TIMESTAMP event detection on WAKEUP3-WAKEUP1 inputs.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the TIMESTAMP event detection.
 */
FunctionalState BKP_RTC_TIMESTAMP_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_BKP->RTC_TAFCR & BKP_RTC_TAFCR_TS_EN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set the capture event for the specified TIMESTAMP WAKEUPx input.
 * @param  Wakeups: Specify the TIMESTAMP WAKEUPx inputs for which the capture event will be set.
 *         This parameter can be any combination of @ref BKP_RTC_TIMESTAMP_Wakeup_TypeDef values.
 * @param  Event: @ref BKP_RTC_TIMESTAMP_Event_TypeDef - capture event on specified WAKEUPx inputs.
 * @return None.
 */
void BKP_RTC_TIMESTAMP_SetEvent(uint32_t Wakeups, BKP_RTC_TIMESTAMP_Event_TypeDef Event)
{
    uint32_t Pos;
    uint32_t Mask;
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_TIMESTAMP_WAKEUPS(Wakeups));
    assert_param(IS_BKP_RTC_TIMESTAMP_EVENT(Event));

    Pos  = 0;
    Mask = BKP_RTC_TAFCR_TS_EDGE1;
#if defined(USE_MDR32F02_REV_1X)
    TmpReg = MDR_BKP->RTC_TAFCR;
#else
    TmpReg = MDR_BKP->RTC_TAFCR & ~BKP_RTC_TAFCR_FLAG_CLR_MASK;
#endif
    for (; Wakeups && Pos < 3; Wakeups >>= 1, Pos++) {
        if ((Wakeups & 0x1) != 0) {
            TmpReg = (TmpReg & ~(Mask << Pos)) | ((uint32_t)Event << Pos);
        }
    }
    MDR_BKP->RTC_TAFCR = TmpReg;
}

/**
 * @brief  Get the date and time timestamp in BCD format for a specified TIMESTAMP WAKEUPx input.
 * @param  Wakeup: @ref BKP_RTC_TIMESTAMP_Wakeup_TypeDef - TIMESTAMP WAKEUPx input.
 * @param  RTC_DateTime: The pointer to the @ref BKP_RTC_DateTime_TypeDef structure
 *         where the date must be stored.
 * @return None.
 */
void BKP_RTC_TIMESTAMP_GetDateTimeBCD(BKP_RTC_TIMESTAMP_Wakeup_TypeDef Wakeup, BKP_RTC_DateTime_TypeDef* RTC_DateTime)
{
    /* Check the parameters. */
    assert_param(IS_BKP_RTC_TIMESTAMP_WAKEUP(Wakeup));

    uint32_t      TempTR;
    uint32_t      TempDR;
    __I uint32_t* PtrTR;
    __I uint32_t* PtrDR;

    PtrTR = &MDR_BKP->RTC_TSTR1 + ((uint32_t)Wakeup >> 1);
    PtrDR = &MDR_BKP->RTC_TSDR1 + ((uint32_t)Wakeup >> 1);

    do {
        TempTR = *PtrTR;
        TempDR = *PtrDR;
    } while (TempTR != *PtrTR); /* Race condition. */

    BKP_RTC_GetDateTimeReg(TempDR, TempTR, RTC_DateTime);
}

/** @} */ /* End of the group BKP_RTC_Event_Detection_Control_Functions */

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/** @addtogroup BKP_RTC_TMPCAL_Control_Functions BKP RTC TMPCAL Control Functions
 * @{
 */

/**
 * @brief  Enable or disable the RTC temperature sensor for temperature compensation of the LSE clock.
 *         Temperature frequency compensation is performed by hardware decreasing the RTC_CLK prescaler (BKP_RTC_PRL)
 *         by the calibration constant specified for each RTC temperature sensor result (code 0 to 15).
 * @note   RTC TMPCAL works when RTC is enabled (RTC_EN = 1 in the BKP_RTC_CR register).
 * @param  NewState: @ref FunctionalState - a new state of the RTC temperature sensor.
 * @return None.
 */
void BKP_RTC_TMPCAL_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_BKP->RTC_TMPCAL3 |= BKP_RTC_TMPCAL3_TEMP_EN;
    } else {
        MDR_BKP->RTC_TMPCAL3 &= ~BKP_RTC_TMPCAL3_TEMP_EN;
    }
}

/**
 * @brief  Get the RTC temperature sensor work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the RTC temperature sensor.
 */
FunctionalState BKP_RTC_TMPCAL_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_BKP->RTC_TMPCAL3 & BKP_RTC_TMPCAL3_TEMP_EN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set the calibration constants for temperature compensation of the LSE clock.
 * @param  TMPCAL_Calibration: The pointer to the @ref BKP_RTC_TMPCAL_Calibration_TypeDef structure
 *         that contains the calibration constants.
 * @return None.
 */
void BKP_RTC_TMPCAL_SetCalibration(const BKP_RTC_TMPCAL_Calibration_TypeDef* TMPCAL_Calibration)
{
    uint32_t TmpReg;

#if (USE_ASSERT_INFO != 0)
    uint32_t Index;
    /* Check the parameters. */
    for (Index = 0; Index < 16; Index++) {
        assert_param(IS_BKP_RTC_TMPCAL_CALIBRATION(TMPCAL_Calibration->Const[Index]));
    }
#endif

    MDR_BKP->RTC_TMPCAL1 = ((uint32_t)TMPCAL_Calibration->Const[0] << BKP_RTC_TMPCAL1_CONST0_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[1] << BKP_RTC_TMPCAL1_CONST1_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[2] << BKP_RTC_TMPCAL1_CONST2_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[3] << BKP_RTC_TMPCAL1_CONST3_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[4] << BKP_RTC_TMPCAL1_CONST4_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[5] << BKP_RTC_TMPCAL1_CONST5_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[6] << BKP_RTC_TMPCAL1_CONST6_LOW_Pos);

    MDR_BKP->RTC_TMPCAL2 = (((uint32_t)TMPCAL_Calibration->Const[6] >> 2) << BKP_RTC_TMPCAL2_CONST6_HIGH_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[7] << BKP_RTC_TMPCAL2_CONST7_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[8] << BKP_RTC_TMPCAL2_CONST8_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[9] << BKP_RTC_TMPCAL2_CONST9_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[10] << BKP_RTC_TMPCAL2_CONST10_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[11] << BKP_RTC_TMPCAL2_CONST11_Pos) |
                           ((uint32_t)TMPCAL_Calibration->Const[12] << BKP_RTC_TMPCAL2_CONST12_LOW_Pos);

    TmpReg = MDR_BKP->RTC_TMPCAL3 & ~(BKP_RTC_TMPCAL3_CONST12_HIGH | BKP_RTC_TMPCAL3_CONST13_Msk | BKP_RTC_TMPCAL3_CONST14_Msk | BKP_RTC_TMPCAL3_CONST15_Msk);
    TmpReg |= (((uint32_t)TMPCAL_Calibration->Const[12] >> 4) << BKP_RTC_TMPCAL3_CONST12_HIGH_Pos) |
              ((uint32_t)TMPCAL_Calibration->Const[13] << BKP_RTC_TMPCAL3_CONST13_Pos) |
              ((uint32_t)TMPCAL_Calibration->Const[14] << BKP_RTC_TMPCAL3_CONST14_Pos) |
              ((uint32_t)TMPCAL_Calibration->Const[15] << BKP_RTC_TMPCAL3_CONST15_Pos);
    MDR_BKP->RTC_TMPCAL3 = TmpReg;
}

/**
 * @brief  Get the calibration constants for temperature compensation of the LSE clock.
 * @param  TMPCAL_Calibration: The pointer to the @ref BKP_RTC_TMPCAL_Calibration_TypeDef structure
 *         where the calibration constants should be stored.
 * @return None.
 */
void BKP_RTC_TMPCAL_GetCalibration(BKP_RTC_TMPCAL_Calibration_TypeDef* TMPCAL_Calibration)
{
    uint32_t TmpReg;

    TmpReg                       = MDR_BKP->RTC_TMPCAL1;
    TMPCAL_Calibration->Const[0] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL1_CONST0_Msk) >> BKP_RTC_TMPCAL1_CONST0_Pos);
    TMPCAL_Calibration->Const[1] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL1_CONST1_Msk) >> BKP_RTC_TMPCAL1_CONST1_Pos);
    TMPCAL_Calibration->Const[2] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL1_CONST2_Msk) >> BKP_RTC_TMPCAL1_CONST2_Pos);
    TMPCAL_Calibration->Const[3] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL1_CONST3_Msk) >> BKP_RTC_TMPCAL1_CONST3_Pos);
    TMPCAL_Calibration->Const[4] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL1_CONST4_Msk) >> BKP_RTC_TMPCAL1_CONST4_Pos);
    TMPCAL_Calibration->Const[5] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL1_CONST5_Msk) >> BKP_RTC_TMPCAL1_CONST5_Pos);
    TMPCAL_Calibration->Const[6] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL1_CONST6_LOW_Msk) >> BKP_RTC_TMPCAL1_CONST6_LOW_Pos);

    TmpReg = MDR_BKP->RTC_TMPCAL2;
    TMPCAL_Calibration->Const[6] |= (uint8_t)(((TmpReg & BKP_RTC_TMPCAL2_CONST6_HIGH_Msk) >> BKP_RTC_TMPCAL2_CONST6_HIGH_Pos) << 2);
    TMPCAL_Calibration->Const[7]  = (uint8_t)((TmpReg & BKP_RTC_TMPCAL2_CONST7_Msk) >> BKP_RTC_TMPCAL2_CONST7_Pos);
    TMPCAL_Calibration->Const[8]  = (uint8_t)((TmpReg & BKP_RTC_TMPCAL2_CONST8_Msk) >> BKP_RTC_TMPCAL2_CONST8_Pos);
    TMPCAL_Calibration->Const[9]  = (uint8_t)((TmpReg & BKP_RTC_TMPCAL2_CONST9_Msk) >> BKP_RTC_TMPCAL2_CONST9_Pos);
    TMPCAL_Calibration->Const[10] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL2_CONST10_Msk) >> BKP_RTC_TMPCAL2_CONST10_Pos);
    TMPCAL_Calibration->Const[11] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL2_CONST11_Msk) >> BKP_RTC_TMPCAL2_CONST11_Pos);
    TMPCAL_Calibration->Const[12] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL2_CONST12_LOW_Msk) >> BKP_RTC_TMPCAL2_CONST12_LOW_Pos);

    TmpReg = MDR_BKP->RTC_TMPCAL3;
    TMPCAL_Calibration->Const[12] |= (uint8_t)(((TmpReg & BKP_RTC_TMPCAL3_CONST12_HIGH_Msk) >> BKP_RTC_TMPCAL3_CONST12_HIGH_Pos) << 4);
    TMPCAL_Calibration->Const[13] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL3_CONST13_Msk) >> BKP_RTC_TMPCAL3_CONST13_Pos);
    TMPCAL_Calibration->Const[14] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL3_CONST14_Msk) >> BKP_RTC_TMPCAL3_CONST14_Pos);
    TMPCAL_Calibration->Const[15] = (uint8_t)((TmpReg & BKP_RTC_TMPCAL3_CONST15_Msk) >> BKP_RTC_TMPCAL3_CONST15_Pos);
}

/**
 * @brief  Return the RTC temperature sensor result.
 * @param  None.
 * @return RTC temperature sensor result.
 */
uint8_t BKP_RTC_TMPCAL_GetResult(void)
{
    return (uint8_t)((MDR_BKP->RTC_TMPCAL3 & BKP_RTC_TMPCAL3_TEMP_RESULT_Msk) >> BKP_RTC_TMPCAL3_TEMP_RESULT_Pos);
}

/** @} */ /* End of the group BKP_RTC_TMPCAL_Control_Functions */
#endif

/**
 * @brief  Convert the date and time from BCD to BIN format.
 * @param  RTC_DateTime: @ref BKP_RTC_DateTime_TypeDef - the pointer to the date/time structure to be converted.
 * @return None.
 */
void BKP_RTC_ConvertToBINFormat(BKP_RTC_DateTime_TypeDef* RTC_DateTime)
{
    RTC_DateTime->RTC_Year    = CONVERT_BCD_TO_BIN(RTC_DateTime->RTC_Year);
    RTC_DateTime->RTC_Month   = CONVERT_BCD_TO_BIN(RTC_DateTime->RTC_Month);
    RTC_DateTime->RTC_Day     = CONVERT_BCD_TO_BIN(RTC_DateTime->RTC_Day);
    RTC_DateTime->RTC_Hours   = CONVERT_BCD_TO_BIN(RTC_DateTime->RTC_Hours);
    RTC_DateTime->RTC_Minutes = CONVERT_BCD_TO_BIN(RTC_DateTime->RTC_Minutes);
    RTC_DateTime->RTC_Seconds = CONVERT_BCD_TO_BIN(RTC_DateTime->RTC_Seconds);
}

/**
 * @brief Convert the date and time from BIN to BCD format.
 * @param RTC_DateTime: @ref BKP_RTC_DateTime_TypeDef - the pointer to the date/time structure to be converted.
 * @return None.
 */
void BKP_RTC_ConvertToBCDFormat(BKP_RTC_DateTime_TypeDef* RTC_DateTime)
{
    RTC_DateTime->RTC_Year    = CONVERT_BIN_TO_BCD(RTC_DateTime->RTC_Year);
    RTC_DateTime->RTC_Month   = CONVERT_BIN_TO_BCD(RTC_DateTime->RTC_Month);
    RTC_DateTime->RTC_Day     = CONVERT_BIN_TO_BCD(RTC_DateTime->RTC_Day);
    RTC_DateTime->RTC_Hours   = CONVERT_BIN_TO_BCD(RTC_DateTime->RTC_Hours);
    RTC_DateTime->RTC_Minutes = CONVERT_BIN_TO_BCD(RTC_DateTime->RTC_Minutes);
    RTC_DateTime->RTC_Seconds = CONVERT_BIN_TO_BCD(RTC_DateTime->RTC_Seconds);
}

/**
 * @brief  Clear the RTC status flags.
 * @note   In MDR32F02 rev 1.x: Clearing the BKP_RTC_FLAG_TAMPER bit uses the cycle counter and core clock from SystemCoreClock for the delay.
 *         Do not disable the cycle counter. Before calling BKP_RTC_ClearFlags(BKP_RTC_FLAG_TAMPER), you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  Flags: @ref BKP_RTC_Flags_TypeDef - specify the RTC flags to clear.
 *         This parameter can be any combination of the following values:
 *             @arg BKP_RTC_FLAG_SECF:         RTC second flag.
 *             @arg BKP_RTC_FLAG_ALARM_A:      RTC alarm A event flag.
 *             @arg BKP_RTC_FLAG_ALARM_B:      RTC alarm B event flag.
 *             @arg BKP_RTC_FLAG_WUTF:         WUT alarm.
 *             @arg BKP_RTC_FLAG_OWF:          WUT overflow flag.
 *             @arg BKP_RTC_FLAG_TAMPER:       TAMPER event flag (WAKEUP3-WAKEUP1).
 *             @arg BKP_RTC_FLAG_TAMPER_W1:    TAMPER WAKEUP1 event flag (not implemented in MDR32F02 rev.1.0 and rev.1.1).
 *             @arg BKP_RTC_FLAG_TAMPER_W2:    TAMPER WAKEUP2 event flag (not implemented in MDR32F02 rev.1.0 and rev.1.1).
 *             @arg BKP_RTC_FLAG_TAMPER_W3:    TAMPER WAKEUP3 event flag (not implemented in MDR32F02 rev.1.0 and rev.1.1).
 *             @arg BKP_RTC_FLAG_TIMESTAMP:    TIMESTAMP event flag (WAKEUP3-WAKEUP1).
 *             @arg BKP_RTC_FLAG_TIMESTAMP_W1: TIMESTAMP WAKEUP1 event flag (not implemented in MDR32F02 rev.1.0 and rev.1.1).
 *             @arg BKP_RTC_FLAG_TIMESTAMP_W2: TIMESTAMP WAKEUP2 event flag (not implemented in MDR32F02 rev.1.0 and rev.1.1).
 *             @arg BKP_RTC_FLAG_TIMESTAMP_W3: TIMESTAMP WAKEUP3 event flag (not implemented in MDR32F02 rev.1.0 and rev.1.1).
 * @return None.
 */
void BKP_RTC_ClearFlags(uint32_t Flags)
{
#if defined(USE_MDR32F02_REV_1X)
    uint32_t DelayConst;
#endif
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_FLAGS_CLR(Flags));

    TmpReg = Flags & BKP_RTC_CS_FLAG_CLR_MASK;
    if (TmpReg != 0) {
        MDR_BKP->RTC_CS = (MDR_BKP->RTC_CS & ~BKP_RTC_CS_FLAG_CLR_MASK) | TmpReg;
    }

#if defined(USE_MDR32F02_REV_1X)
    if ((Flags & BKP_LDO_TAMPF) != 0) {
        DelayConst = DELAY_CYCLE_COUNTER_GET_CONST_US(SystemCoreClock);

        MDR_BKP->RTC_TAFCR &= ~BKP_RTC_TAFCR_TAMP_EN;
        DELAY_CycleCounter_WaitTicksAsm(DELAY_GET_TICKS_US(100, DelayConst)); /* Wait for 100 us. */

        MDR_BKP->LDO = (MDR_BKP->LDO & ~BKP_LDO_SW_OFF) | BKP_LDO_TAMPF;
        DELAY_CycleCounter_WaitTicksAsm(DELAY_GET_TICKS_US(100, DelayConst)); /* Wait for 100 us. */
    }
#else
    TmpReg = Flags & BKP_RTC_TAFCR_FLAG_CLR_MASK;
    if (TmpReg != 0) {
        MDR_BKP->RTC_TAFCR = (MDR_BKP->RTC_TAFCR & ~BKP_RTC_TAFCR_FLAG_CLR_MASK) | TmpReg;
    }

    if ((Flags & BKP_LDO_TAMPF) != 0) {
        MDR_BKP->LDO = (MDR_BKP->LDO & ~BKP_LDO_SW_OFF) | BKP_LDO_TAMPF;
    }
#endif
}

/**
 * @brief  Check whether a specified RTC status flag is set or not.
 * @param  Flag: @ref BKP_RTC_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - the current RTC status flag state (SET or RESET).
 */
FlagStatus BKP_RTC_GetFlagStatus(BKP_RTC_Flags_TypeDef Flag)
{
    FlagStatus Status;
    uint32_t   TmpReg;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_FLAG(Flag));

    if (((uint32_t)Flag & BKP_RTC_CS_FLAG_MASK) != 0) {
        TmpReg = MDR_BKP->RTC_CS;
    } else if (((uint32_t)Flag & BKP_RTC_TAFCR_FLAG_MASK) != 0) {
        TmpReg = MDR_BKP->RTC_TAFCR;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    } else if (((uint32_t)Flag & BKP_RTC_TMPCAL3_TEMP_RESULT_RDY) != 0) {
        TmpReg = MDR_BKP->RTC_TMPCAL3;
#endif
    } else {
        TmpReg = MDR_BKP->LDO;
    }

    if ((TmpReg & (uint32_t)Flag) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Return a combined value of the RTC status flags.
 * @param  None.
 * @return A combined value of status flags.
 */
uint32_t BKP_RTC_GetStatus(void)
{
    uint32_t Flags;

    Flags = (MDR_BKP->RTC_CS & BKP_RTC_CS_FLAG_MASK) |
            (MDR_BKP->RTC_TAFCR & BKP_RTC_TAFCR_FLAG_MASK) |
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
            (MDR_BKP->RTC_TMPCAL3 & BKP_RTC_TMPCAL3_TEMP_RESULT_RDY) |
#endif
            (MDR_BKP->LDO & BKP_LDO_TAMPF);

    return Flags;
}

/**
 * @brief  Enable or disable BKP RTC interrupts.
 * @param  ITs: Specify the BKP interrupt sources to be enabled or disabled.
 *         This parameter can be any combination of @ref BKP_RTC_IT_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of BKP RTC interrupts.
 * @return None.
 */
void BKP_RTC_ITConfig(uint32_t ITs, FunctionalState NewState)
{
    uint32_t TmpIT;

    /* Check the parameters. */
    assert_param(IS_BKP_RTC_CONFIG_ITS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Setup a new interrupts state, the RTC_CS register. */
    TmpIT = ITs & BKP_RTC_CS_IT_MASK;
    if (TmpIT != 0) {
        if (NewState != DISABLE) {
            MDR_BKP->RTC_CS = (MDR_BKP->RTC_CS & ~BKP_RTC_CS_FLAG_CLR_MASK) | TmpIT;
        } else {
            MDR_BKP->RTC_CS = (MDR_BKP->RTC_CS & ~BKP_RTC_CS_FLAG_CLR_MASK) & ~TmpIT;
        }
    }
    /* Setup a new interrupts state, the RTC_TAFCR register. */
    TmpIT = (ITs >> 16) & BKP_RTC_TAFCR_IT_MASK;
    if (TmpIT != 0) {
#if defined(USE_MDR32F02_REV_1X)
        if (NewState != DISABLE) {
            MDR_BKP->RTC_TAFCR |= TmpIT;
        } else {
            MDR_BKP->RTC_TAFCR &= ~TmpIT;
        }
#else
        if (NewState != DISABLE) {
            MDR_BKP->RTC_TAFCR = (MDR_BKP->RTC_TAFCR & ~BKP_RTC_TAFCR_FLAG_CLR_MASK) | TmpIT;
        } else {
            MDR_BKP->RTC_TAFCR = (MDR_BKP->RTC_TAFCR & ~BKP_RTC_TAFCR_FLAG_CLR_MASK) & ~TmpIT;
        }
#endif
    }
}

/**
 * @brief  Get the date and time from the specified registers.
 * @param  DateRegVal: Date register value.
 * @param  TimeRegVal: Time register value.
 * @param  RTC_DateTime: The pointer to the @ref BKP_RTC_DateTime_TypeDef where the date and time must be stored.
 * @return None.
 */
static void BKP_RTC_GetDateTimeReg(uint32_t DateRegVal, uint32_t TimeRegVal, BKP_RTC_DateTime_TypeDef* RTC_DateTime)
{
    RTC_DateTime->RTC_Year    = (uint8_t)((DateRegVal & BKP_RTC_DR_YEAR_MASK) >> BKP_RTC_DR_YU_Pos);
    RTC_DateTime->RTC_Month   = (uint8_t)((DateRegVal & BKP_RTC_DR_MONTH_MASK) >> BKP_RTC_DR_MU_Pos);
    RTC_DateTime->RTC_Day     = (uint8_t)((DateRegVal & BKP_RTC_DR_DATE_MASK) >> BKP_RTC_DR_DU_Pos);
    RTC_DateTime->RTC_WeekDay = (BKP_RTC_WeekDays_TypeDef)((DateRegVal & BKP_RTC_DR_WDU_Msk) >> BKP_RTC_DR_WDU_Pos);

    RTC_DateTime->RTC_TimeFormat = (BKP_RTC_FMT_TypeDef)((TimeRegVal & BKP_RTC_TR_PM) >> BKP_RTC_TR_PM_Pos);
    RTC_DateTime->RTC_Hours      = (uint8_t)((TimeRegVal & BKP_RTC_TR_HOURS_MASK) >> BKP_RTC_TR_HU_Pos);
    RTC_DateTime->RTC_Minutes    = (uint8_t)((TimeRegVal & BKP_RTC_TR_MINUTES_MASK) >> BKP_RTC_TR_MNU_Pos);
    RTC_DateTime->RTC_Seconds    = (uint8_t)((TimeRegVal & BKP_RTC_TR_SECONDS_MASK) >> BKP_RTC_TR_SU_Pos);
}

/** @} */ /* End of the group BKP_RTC_Control_Functions */

/** @} */ /* End of the group BKP_Exported_Functions */

/** @} */ /* End of the group BKP */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_bkp.c */

