/**
 *******************************************************************************
 * @file    MDR32VF0xI_power.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    24/01/2025
 * @brief   This file contains all the POWER firmware functions.
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
#include "MDR32VF0xI_power.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @defgroup POWER POWER
 * @{
 */

/** @defgroup POWER_Exported_Functions POWER Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the POWER peripheral registers to their default reset values.
 * @note   PVD can not be disabled before next POR reset.
 * @param  None.
 * @return None.
 */
void POWER_DeInit(void)
{
    MDR_POWER->PVDCS = (uint32_t)0x00000000;
    MDR_POWER->PVDCS = (uint32_t)0x00000000;
}

/**
 * @brief  Initialize the POWER peripheral according to the specified
 *         parameters in the POWER_InitStruct.
 * @param  POWER_InitStruct: The pointer to the @ref POWER_InitTypeDef structure that
 *         contains the configuration information for the POWER peripheral.
 * @return None.
 */
void POWER_Init(const POWER_InitTypeDef* POWER_InitStruct)
{
    uint32_t Temp;

    /* Check the parameters. */
    assert_param(IS_POWER_PVD_LEVEL(POWER_InitStruct->POWER_PVDLevel));
    assert_param(IS_POWER_PVDB_LEVEL(POWER_InitStruct->POWER_PVBDLevel));
    assert_param(IS_POWER_PVD_INV(POWER_InitStruct->POWER_InterruptInversionEnable));

    Temp = MDR_POWER->PVDCS;

    /* Clear specified bits. */
    Temp &= ~(POWER_PVDCS_PLS_Msk | POWER_PVDCS_PLSB_Msk | POWER_PVDCS_INV | POWER_PVDCS_INVB);

    /* Set specified bits according to structure values. */
    Temp |= (uint32_t)(POWER_InitStruct->POWER_PVDLevel) |
            (uint32_t)(POWER_InitStruct->POWER_PVBDLevel) |
            (uint32_t)(POWER_InitStruct->POWER_InterruptInversionEnable);

    /* Store the new value. */
    MDR_POWER->PVDCS = Temp;
}

/**
 * @brief  Fill each POWER_InitStruct member with its default value.
 * @param  POWER_InitStruct: The pointer to the @ref POWER_InitTypeDef structure
 *         which will be initialized.
 * @return None.
 */
void POWER_StructInit(POWER_InitTypeDef* POWER_InitStruct)
{
    /* Reset the values of POWER initialization structure parameters. */
    POWER_InitStruct->POWER_PVDLevel                 = POWER_PVD_LEVEL_2p3V;
    POWER_InitStruct->POWER_PVBDLevel                = POWER_PVBD_LEVEL_1p8V;
    POWER_InitStruct->POWER_InterruptInversionEnable = 0;
}

/**
 * @brief  Enable or disable the power voltage detector.
 * @note   Once enabled, PVD can not be disabled before next POR reset.
 * @param  PowerDetector: Specified Power Voltage Detector.
 *         This parameter can be any combination of the @ref POWER_DetectorEnable_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the Power Voltage Detector.
 * @return None.
 */
void POWER_Cmd(uint32_t PowerDetector, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_POWER_DETECTORS(PowerDetector));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_POWER->PVDCS |= PowerDetector;
    } else {
        MDR_POWER->PVDCS &= ~PowerDetector;
    }
}

/**
 * @brief  Get the power voltage detector work state.
 * @param  PowerDetector: @ref POWER_DetectorEnable_TypeDef - specified Power Voltage Detector.
 * @return @ref FunctionalState - the current work state of the power voltage detector.
 */
FunctionalState POWER_GetCmdState(POWER_DetectorEnable_TypeDef PowerDetector)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_POWER_DETECTOR(PowerDetector));

    if ((MDR_POWER->PVDCS & (uint32_t)PowerDetector) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Configure the voltage threshold detected by the Power Voltage Detector (PVD).
 * @param  POWER_PVD_Level: @ref POWER_VoltageDetectorLvl_TypeDef - specify the PVD detection level.
 * @return None.
 */
void POWER_PVD_LevelConfig(POWER_VoltageDetectorLvl_TypeDef POWER_PVD_Level)
{
    uint32_t Temp;

    /* Check the parameters. */
    assert_param(IS_POWER_PVD_LEVEL(POWER_PVD_Level));

    Temp = MDR_POWER->PVDCS;

    /* Clear PLS bits. */
    Temp &= ~POWER_PVDCS_PLS_Msk;

    /* Set PLS bits according to POWER_PVD_Level value. */
    Temp |= (uint32_t)POWER_PVD_Level;

    /* Store the new value. */
    MDR_POWER->PVDCS = Temp;
}

/**
 * @brief  Configure the voltage threshold detected by the Power Voltage Battery Detector (PVBD).
 * @param  POWER_PVDB_Level: @ref POWER_BattVoltageDetectorLvl_TypeDef - specify the PVBD detection level.
 * @return None.
 */
void POWER_PVDB_LevelConfig(POWER_BattVoltageDetectorLvl_TypeDef POWER_PVDB_Level)
{
    uint32_t Temp;

    /* Check the parameters. */
    assert_param(IS_POWER_PVDB_LEVEL(POWER_PVDB_Level));

    Temp = MDR_POWER->PVDCS;

    /* Clear PBLS bits. */
    Temp &= ~POWER_PVDCS_PLSB_Msk;

    /* Set PBLS bits according to POWER_PVDB_Level value. */
    Temp |= (uint32_t)POWER_PVDB_Level;

    /* Store the new value. */
    MDR_POWER->PVDCS = Temp;
}

/**
 * @brief  Check whether the specified POWER detection flag is set or not.
 * @param  POWER_Flag: @ref POWER_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - a state of POWER_Flag (SET or RESET).
 */
FlagStatus POWER_GetFlagStatus(POWER_Flags_TypeDef POWER_Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_POWER_FLAG(POWER_Flag));

    if ((MDR_POWER->PVDCS & (uint32_t)POWER_Flag) != (uint32_t)RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    /* Return the flag status. */
    return Status;
}

/**
 * @brief  Return a combined value of the POWER detection flags.
 * @param  None.
 * @return A combined value of POWER status flags (@ref POWER_Flags_TypeDef).
 */
uint32_t POWER_GetStatus(void)
{
    return (MDR_POWER->PVDCS & (POWER_PVDCS_PVD | POWER_PVDCS_PVBD));
}

/**
 * @brief  Clear the POWER pending flags.
 * @param  POWER_Flags: Specify the flags to clear.
 *         This parameter can be any combination of the @ref POWER_Flags_TypeDef values.
 * @return None.
 */
void POWER_ClearFlags(uint32_t POWER_Flags)
{
    /* Check the parameters. */
    assert_param(IS_POWER_FLAGS(POWER_Flags));

    MDR_POWER->PVDCS &= ~POWER_Flags;
    MDR_POWER->PVDCS &= ~POWER_Flags;
}

/**
 * @brief  Enable or disable inversion of the specified POWER voltage detection flags.
 * @param  FlagInversion: Specify the PVD flags to invert.
 *         This parameter can be any combination of the @ref POWER_VoltageDetectorITInversion_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of inversion of the specified POWER voltage flag.
 * @return None.
 */
void POWER_FlagInversionConfig(uint32_t FlagInversion, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_POWER_PVD_INV(FlagInversion));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_POWER->PVDCS |= FlagInversion;
    } else {
        MDR_POWER->PVDCS &= ~(uint32_t)FlagInversion;
    }
}

/**
 * @brief  Enable or disable the specified POWER interrupts.
 * @param  POWER_IT: Specify the PVD interrupts sources to be enabled or disabled.
 *         This parameter can be any combination of the @ref POWER_VoltageDetectorITEnable_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the specified POWER interrupts.
 * @return None.
 */
void POWER_ITConfig(uint32_t POWER_IT, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_POWER_PVD_IT(POWER_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_POWER->PVDCS |= POWER_IT;
    } else {
        MDR_POWER->PVDCS &= ~(uint32_t)POWER_IT;
    }
}

/** @} */ /* End of the group POWER_Exported_Functions */

/** @} */ /* End of the group POWER */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_power.c */

