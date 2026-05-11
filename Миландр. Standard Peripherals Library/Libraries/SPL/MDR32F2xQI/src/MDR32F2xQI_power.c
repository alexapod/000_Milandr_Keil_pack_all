/**
 *******************************************************************************
 * @file    MDR32F2xQI_power.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    17/05/2023
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
#include "MDR32F2xQI_power.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @defgroup POWER POWER
 * @{
 */

/** @defgroup POWER_Exported_Functions POWER Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the POWER peripheral registers to their default reset values.
 * @param  None.
 * @retval None.
 */
void POWER_DeInit(void)
{
    MDR_POWER->PVDCS = (uint32_t)0x00000000;
    MDR_POWER->PVDCS = (uint32_t)0x00000000;
}

/**
 * @brief  Enables or disables the Ucc Power Voltage Detector PVD.
 * @param  PowerDetector: specified PVD.
 *         This parameter can be any combination of the @ref POWER_DetectorEnable_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the Power Voltage Detector.
 * @retval None.
 */
void POWER_Cmd(uint32_t PowerDetector, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_POWER_DETECTOR(PowerDetector));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_POWER->PVDCS |= (uint32_t)PowerDetector;
    } else {
        MDR_POWER->PVDCS &= ~(uint32_t)PowerDetector;
    }
}

/**
 * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
 * @param  POWER_PVD_Level - @ref POWER_VoltageDetectorLvl_TypeDef - specifies the PVD detection level.
 * @retval None.
 */
void POWER_PVD_LevelConfig(POWER_VoltageDetectorLvl_TypeDef POWER_PVD_Level)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_POWER_PVD_LEVEL(POWER_PVD_Level));

    Temp = MDR_POWER->PVDCS;

    /* Clear PLS bits */
    Temp &= (uint32_t)~POWER_PVDCS_PLS_Msk;

    /* Set PLS bits according to POWER_PVD_Level value */
    Temp |= (uint32_t)POWER_PVD_Level;

    /* Store the new value */
    MDR_POWER->PVDCS = Temp;
}

/**
 * @brief  Configures the voltage threshold detected by the Power Battery Voltage Detector(PVBD).
 * @param  POWER_PVBD_Level - @ref POWER_BattVoltageDetectorLvl_TypeDef - specifies the PVBD detection level.
 * @retval None.
 */
void POWER_PVBD_LevelConfig(POWER_BattVoltageDetectorLvl_TypeDef POWER_PVBD_Level)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_POWER_PVBD_LEVEL(POWER_PVBD_Level));

    Temp = MDR_POWER->PVDCS;

    /* Clear PBLS bits */
    Temp &= (uint32_t)~POWER_PVDCS_PBLS_Msk;

    /* Set PBLS bits according to POWER_PVBD_Level value */
    Temp |= (uint32_t)POWER_PVBD_Level;

    /* Store the new value */
    MDR_POWER->PVDCS = Temp;
}

/**
 * @brief  Checks whether the specified POWER detection flag is set or not.
 * @param  POWER_Flag - @ref POWER_Flags_TypeDef - specifies the flag to check.
 * @retval The state of POWER_Flag (SET or RESET).
 */
FlagStatus POWER_GetFlagStatus(POWER_Flags_TypeDef POWER_Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_POWER_FLAG(POWER_Flag));

    if ((MDR_POWER->PVDCS & (uint32_t)POWER_Flag) != (uint32_t)RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    /* Return the flag status */
    return Status;
}

/**
 * @brief  Get combined state of all POWER detection flags.
 * @param  None.
 * @retval Combined state of @ref POWER_Flags_TypeDef.
 */
uint32_t POWER_GetStatus(void)
{
    return (MDR_POWER->PVDCS & (POWER_PVDCS_PVD_Msk | POWER_PVDCS_PVBD_Msk));
}

/**
 * @brief  Clears the POWER's pending flags.
 * @param  POWER_Flags: specifies the flags to clear.
 *         This parameter can be any combination
 *         of the @ref POWER_Flags_TypeDef values.
 * @retval None.
 */
void POWER_ClearFlags(uint32_t POWER_Flags)
{
    /* Check the parameters */
    assert_param(IS_POWER_FLAGS(POWER_Flags));

    MDR_POWER->PVDCS &= ~POWER_Flags;
    MDR_POWER->PVDCS &= ~POWER_Flags;
}

/**
 * @brief  Enables or disables inversion of the specified POWER voltage detection flags
 * @param  FlagInversion: specifies the PVD flags to specify inversion.
 *         This parameter can be any combination of the @ref POWER_VoltageDetectorITInversion_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the specified POWER voltage flag inversion.
 * @retval None.
 */
void POWER_FlagInversionConfig(uint32_t FlagInversion, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_POWER_PVD_INV(FlagInversion));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_POWER->PVDCS |= FlagInversion;
    } else {
        MDR_POWER->PVDCS &= (uint32_t)~FlagInversion;
    }
}

/**
 * @brief  Enables or disables the specified POWER interrupts.
 * @param  POWER_IT: specifies the PVD interrupts sources to be enabled or disabled.
 *         This parameter can be any combination of the @ref POWER_VoltageDetectorITEnable_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the specified POWER interrupts.
 * @retval None.
 */
void POWER_ITConfig(uint32_t POWER_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_POWER_PVD_IT(POWER_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_POWER->PVDCS |= POWER_IT;
    } else {
        MDR_POWER->PVDCS &= (uint32_t)~POWER_IT;
    }
}

/**
 * @brief  Checks whether enabled POWER IT flag is set or not.
 * @param  POWER_Flag - @ref POWER_Flags_TypeDef - specifies the flag to check.
 * @retval The state of POWER_Flag (SET or RESET).
 */
FlagStatus POWER_GetITFlagStatus(POWER_Flags_TypeDef POWER_Flag)
{
    FlagStatus Status;
    uint32_t   Reg, FlagState, FlagEnable;

    /* Check the parameters */
    assert_param(IS_POWER_FLAG(POWER_Flag));

    Reg = MDR_POWER->PVDCS;

    FlagState = Reg & (uint32_t)POWER_Flag;

    FlagEnable = Reg & (POWER_PVDCS_IEPVD | POWER_PVDCS_IEPVBD);
    FlagEnable >>= (POWER_PVDCS_IEPVBD_Pos - POWER_PVDCS_PVBD_Pos);

    if ((FlagState & FlagEnable) != RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    /* Return the flag status */
    return Status;
}

/**
 * @brief  Checks whether enabled POWER IT flags are set or not.
 * @param  None.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref POWER_Flags_TypeDef.
 */
uint32_t POWER_GetITStatus(void)
{
    uint32_t Reg, FlagsState, FlagsEnable;

    Reg = MDR_POWER->PVDCS;

    FlagsState = Reg & (POWER_PVDCS_PVD | POWER_PVDCS_PVBD);

    FlagsEnable = Reg & (POWER_PVDCS_IEPVD | POWER_PVDCS_IEPVBD);
    FlagsEnable >>= (POWER_PVDCS_IEPVBD_Pos - POWER_PVDCS_PVBD_Pos);

    return (FlagsState & FlagsEnable);
}

/** @} */ /* End of group POWER_Exported_Functions */

/** @} */ /* End of group POWER */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_power.c */

