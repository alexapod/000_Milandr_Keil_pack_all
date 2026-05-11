/**
 ******************************************************************************
 * @file    MDR32F2xQI_bkp.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    29/05/2023
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
#include "MDR32F2xQI_bkp.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup BKP BKP
 * @{
 */

/** @defgroup BKP_Private_Defines BKP Private Defines
 * @{
 */

#define BKP_RTC_FLAG_MASK (BKP_RTC_CS_OWF |  \
                           BKP_RTC_CS_SECF | \
                           BKP_RTC_CS_ALRF | \
                           BKP_RTC_CS_WEC)

#define BKP_RTC_FLAG_CLR_MASK (BKP_RTC_CS_OWF |  \
                               BKP_RTC_CS_SECF | \
                               BKP_RTC_CS_ALRF)

#define BKP_DUCC_MODE_MASK (BKP_REG_0E_LOW_Msk | \
                            BKP_REG_0E_SELECTRI_Msk)

/** @} */ /* End of group BKP_Private_Defines */

/** @addtogroup BKP_Exported_Functions BKP Exported Functions
 * @{
 */

/** @addtogroup BKP_Control_Functions BKP control functions
 * @{
 */

/**
 * @brief  Deinitializes the BKP peripheral registers to their default reset values.
 * @param  None
 * @retval None
 */
void BKP_DeInit(void)
{
    uint32_t* TmpPtrBKP_REG = (uint32_t*)MDR_BKP_BASE;
    uint32_t  NumReg;

    for (NumReg = 0; NumReg < (BKP_REG_0E >> 2); NumReg++) {
        TmpPtrBKP_REG[NumReg] = 0;
    }

    MDR_BKP->REG_0E   = BKP_REG_0E_SW_EN_SW_ENABLED_2;
    MDR_BKP->REG_0F   = (BKP_REG_0F_LSI_ON_Msk | (0x10UL << BKP_REG_0F_LSI_TRIM_Pos) |
                       BKP_REG_0F_HSI_ON_Msk | (0x20UL << BKP_REG_0F_HSI_TRIM_Pos));
    MDR_BKP->RTC_CNT  = 0;
    MDR_BKP->RTC_DIV  = 0;
    MDR_BKP->RTC_PRL  = 0;
    MDR_BKP->RTC_ALRM = 0;
    MDR_BKP->RTC_CS   = BKP_RTC_FLAG_CLR_MASK;
}

/**
 * @brief  Enables or disables the Serial Wire Debug (SWD) interface.
 * @param  NewState - @ref FunctionalState - new state of the SWD.
 * @retval None.
 */
void BKP_SWDCmd(FunctionalState NewState)
{
    uint32_t TmpReg;

    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Clear SW_EN[1:0] and COV_DET bits */
    TmpReg = MDR_BKP->REG_0E & ~(BKP_REG_0E_SW_EN_Msk | BKP_REG_0E_COV_DET_Msk);

    /* Form new value */
    if (NewState != DISABLE) {
        TmpReg |= BKP_REG_0E_SW_EN_SW_ENABLED_2;
    }

    /* Configure BKP_REG_0E register with new value */
    MDR_BKP->REG_0E = TmpReg;
}

/**
 * @brief  Select the internal voltage regulator DUcc mode based on clock frequency.
 * @param  DUccMode - @ref BKP_DUСС_Mode_TypeDef - specifies the DUcc mode.
 * @retval None.
 */
void BKP_DUcc_SetMode(BKP_DUСС_Mode_TypeDef DUccMode)
{
    uint32_t TmpReg;

    /* Check the parameter */
    assert_param(IS_BKP_DUCC_MODE(DUccMode));

    /* Clear BKP_REG_0E[5:0] and COV_DET bits */
    TmpReg = MDR_BKP->REG_0E & ~(BKP_DUCC_MODE_MASK | BKP_REG_0E_COV_DET_Msk);
    /* Set BKP_REG_0E[5:0] bits according to DUcc mode */
    TmpReg |= (uint32_t)DUccMode;

    /* Configure BKP_REG_0E register with new value */
    MDR_BKP->REG_0E = TmpReg;
}

/**
 * @brief  Sets the output voltage level of the internal voltage regulator DUcc.
 * @param  OutVoltage - @ref BKP_DUCC_OutVoltage_TypeDef - approximate output voltage level DUcc.
 * @retval None.
 */
void BKP_DUcc_SetOutVoltage(BKP_DUCC_OutVoltage_TypeDef OutVoltage)
{
    uint32_t TmpReg;

    /* Check the parameter */
    assert_param(IS_BKP_DUCC_OUT_VOLTAGE(OutVoltage));

    /* Clear Trim[4:3] and COV_DET bits */
    TmpReg = MDR_BKP->REG_0E & ~(BKP_REG_0E_TRIM43_Msk | BKP_REG_0E_COV_DET_Msk);
    /* Set Trim[4:3] bits according to output voltage */
    TmpReg |= (uint32_t)OutVoltage;

    /* Configure BKP_REG_0E register with new value */
    MDR_BKP->REG_0E = TmpReg;
}

/**
 * @brief  Sets the internal voltage regulator DUcc trim.
 * @param  DUccTrim - @ref BKP_DUСС_Trim_TypeDef - specifies the DUcc trim.
 * @retval None.
 */
void BKP_DUcc_SetTrim(BKP_DUСС_Trim_TypeDef DUccTrim)
{
    uint32_t TmpReg;

    /* Check the parameter */
    assert_param(IS_BKP_DUCC_TRIM(DUccTrim));

    /* Clear Trim[2:0] and COV_DET bits */
    TmpReg = MDR_BKP->REG_0E & ~(BKP_REG_0E_TRIM20_Msk | BKP_REG_0E_COV_DET_Msk);
    /* Set Trim[2:0] bits according to DUcc trim */
    TmpReg |= (uint32_t)DUccTrim;

    /* Configure BKP_REG_0E register with new value */
    MDR_BKP->REG_0E = TmpReg;
}

/**
 * @brief  Enables or disables the current limit protection (150 mA) for the internal voltage regulator DUcc.
 * @param  NewState - @ref FunctionalState - new state of the current limit protection DUcc (ENABLE or DISABLE).
 * @retval None.
 */
void BKP_DUcc_CurrentLimitProtectionCmd(FunctionalState NewState)
{
    uint32_t TmpReg;

    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Clear COV_DET bit */
    TmpReg = MDR_BKP->REG_0E & ~BKP_REG_0E_COV_DET_Msk;

    /* Form new value */
    if (NewState != DISABLE) {
        TmpReg |= BKP_REG_0E_ILIMEN_Msk;
    } else {
        TmpReg &= ~BKP_REG_0E_ILIMEN_Msk;
    }

    /* Configure BKP_REG_0E register with new value */
    MDR_BKP->REG_0E = TmpReg;
}

/**
 * @brief  Sets the power on reset flag (FPOR).
 * @param  None.
 * @retval None.
 */
void BKP_SetFlagPOR(void)
{
    MDR_BKP->REG_0E = (MDR_BKP->REG_0E & ~BKP_REG_0E_COV_DET_Msk) | BKP_REG_0E_FPOR_Msk;
}

/**
 * @brief  Gets the power on reset flag (FPOR).
 * @param  None.
 * @retval @ref FlagStatus - Current state of FPOR (SET or RESET).
 */
FlagStatus BKP_GetFlagPOR(void)
{
    FlagStatus Status;

    if (MDR_BKP->REG_0E & BKP_REG_0E_FPOR_Msk) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
  * @brief  Sets the device unauthorized access flag (COV_DET).
            COV_DET == 1 means no device tampering was detected.
  * @param  None.
  * @retval None.
  */
void BKP_SetFlagCOVDET(void)
{
    MDR_BKP->REG_0E |= BKP_REG_0E_COV_DET_Msk;
}

/**
 * @brief  Gets the flag of unauthorized access to the device (COV_DET).
 * @param  None
 * @retval @ref FlagStatus - Current state of COV_DET bit.
 *         This parameter can be one of the @ref FlagStatus enum values:
 *             @arg SET:   Device was not opened.
 *             @arg RESET: Unauthorized device access detected.
 */
FlagStatus BKP_GetFlagCOVDET(void)
{
    FlagStatus Status;

    if (MDR_BKP->REG_0E & BKP_REG_0E_COV_DET_Msk) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Enters STANDBY mode.
 * @note   STANDBY mode is exited by the following events:
 *         - low level at WAKEUP pin;
 *         - RTC alarm (ALRF flag).
 * @param  None.
 * @retval None.
 */
__NO_RETURN void BKP_EnterSTANDBYMode(void)
{
    /* Ensure all outstanding memory accesses included buffered write are completed before enter STANDBY mode */
    __DSB();

    /* Enter STANDBY mode */
    MDR_BKP->REG_0F |= BKP_REG_0F_STANDBY_Msk;

    /* Ensure completion of memory access */
    __DSB();

    /* Waiting to enter STANDBY mode */
    for (;;) {
        __NOP();
    }
}

/** @} */ /* End of group BKP_Control_Functions */

/** @addtogroup BKP_Clock_Source_Control_Functions BKP clock source control functions
 * @{
 */

/**
 * @brief  HSI (High Speed Internal) clock mode selection.
 * @param  NewState - @ref FunctionalState - mode selector (switch off (DISABLE) or on (ENABLE)).
 * @retval None.
 */
void BKP_HSI_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable HSI generator by setting the HSI_ON bit in the BKP_REG_0F register */
        MDR_BKP->REG_0F |= BKP_REG_0F_HSI_ON_Msk;
    } else {
        /* Disable HSI generator by resetting the HSI_ON bit in the BKP_REG_0F register */
        MDR_BKP->REG_0F &= ~BKP_REG_0F_HSI_ON_Msk;
    }
}

/**
 * @brief  HSI clock frequency adjustment by HSITRIM setting.
 * @param  HSITrimValue: HSI frequency trim value.
 *         This parameter must be a number between 0 and 0x3F.
 * @retval None.
 */
void BKP_HSI_Adjust(uint32_t HSITrimValue)
{
    uint32_t TmpReg;

    /* Check the parameters */
    assert_param(IS_BKP_HSI_TRIM_VALUE(HSITrimValue));

    TmpReg = MDR_BKP->REG_0F;

    /* Clear HSITRIM[5:0] bits */
    TmpReg &= ~BKP_REG_0F_HSI_TRIM_Msk;

    /* Set the HSITRIM[5:0] bits according to HSITrimValue value */
    TmpReg |= HSITrimValue << BKP_REG_0F_HSI_TRIM_Pos;

    /* Store the new value */
    MDR_BKP->REG_0F = TmpReg;
}

/**
 * @brief  HSI clock status.
 * @param  None.
 * @retval @ref ErrorStatus: SUCCESS if HSI clock is ready, else ERROR.
 */
ErrorStatus BKP_HSI_GetStatus(void)
{
    __IO uint32_t StartCounter = 0;
    ErrorStatus   State;
    FlagStatus    Flag;

    /* Wait until HSI is ready or time out is occurred */
    do {
        Flag = BKP_CLK_GetFlagStatus(BKP_FLAG_HSIRDY);
        StartCounter++;
    } while ((StartCounter < HSIRDY_TIMEOUT_TICK) && (Flag == RESET));

    if (BKP_CLK_GetFlagStatus(BKP_FLAG_HSIRDY) != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  LSI (Low Speed Internal) clock mode selection.
 * @param  NewState - @ref FunctionalState - mode selector (switch off (DISABLE) or on (ENABLE)).
 * @retval None.
 */
void BKP_LSI_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable LSI generator by setting the LSI_ON bit in the BKP_REG_0F register */
        MDR_BKP->REG_0F |= BKP_REG_0F_LSI_ON_Msk;
    } else {
        /* Disable LSI generator by resetting the LSI_ON bit in the BKP_REG_0F register */
        MDR_BKP->REG_0F &= ~BKP_REG_0F_LSI_ON_Msk;
    }
}

/**
 * @brief  LSI clock frequency adjustment by LSITRIM setting.
 * @param  LSITrimValue: LSI frequency trim value.
 *         This parameter must be a number between 0 and 0x1F.
 * @retval None.
 */
void BKP_LSI_Adjust(uint32_t LSITrimValue)
{
    uint32_t TmpReg;

    /* Check the parameters */
    assert_param(IS_BKP_LSI_TRIM_VALUE(LSITrimValue));

    TmpReg = MDR_BKP->REG_0F;

    /* Clear LSITRIM[4:0] bits */
    TmpReg &= ~BKP_REG_0F_LSI_TRIM_Msk;

    /* Set the LSITRIM[4:0] bits according to LSITrimValue value */
    TmpReg |= LSITrimValue << BKP_REG_0F_LSI_TRIM_Pos;

    /* Store the new value */
    MDR_BKP->REG_0F = TmpReg;
}

/**
 * @brief  LSI clock status.
 * @param  None.
 * @retval @ref ErrorStatus - SUCCESS if LSI clock is ready, else ERROR.
 */
ErrorStatus BKP_LSI_GetStatus(void)
{
    __IO uint32_t StartCounter = 0;
    ErrorStatus   State;
    FlagStatus    Flag;

    /* Wait until LSI is ready or time out is occurred */
    do {
        Flag = BKP_CLK_GetFlagStatus(BKP_FLAG_LSIRDY);
        StartCounter++;
    } while ((StartCounter < LSIRDY_TIMEOUT_TICK) && (Flag == RESET));

    if (BKP_CLK_GetFlagStatus(BKP_FLAG_LSIRDY) != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  LSE (Low Speed External) clock mode and source selection.
 * @param  LSEMode - @ref BKP_LSE_Mode_TypeDef - mode selector.
 * @retval None.
 */
void BKP_LSE_Config(BKP_LSE_Mode_TypeDef LSEMode)
{
    /* Check the parameters */
    assert_param(IS_BKP_LSE(LSEMode));

    /* Reset LSEON and LSEBYP bits before configuring the LSE */
    MDR_BKP->REG_0F &= ~(BKP_REG_0F_LSE_ON_Msk | BKP_REG_0F_LSE_BYP_Msk);

    MDR_BKP->REG_0F |= LSEMode;
}

/**
 * @brief  LSE clock status.
 * @param  None.
 * @retval @ref ErrorStatus - SUCCESS if LSE clock is ready, else ERROR.
 */
ErrorStatus BKP_LSE_GetStatus(void)
{
    __IO uint32_t StartCounter = 0;
    ErrorStatus   State;
    FlagStatus    Flag;

    /* Wait until LSE is ready or time out is occurred */
    do {
        Flag = BKP_CLK_GetFlagStatus(BKP_FLAG_LSERDY);
        StartCounter++;
    } while ((StartCounter < LSERDY_TIMEOUT_TICK) && (Flag == RESET));

    if (BKP_CLK_GetFlagStatus(BKP_FLAG_LSERDY) != RESET) {
        State = SUCCESS;
    } else {
        State = ERROR;
    }

    return State;
}

/**
 * @brief  Checks whether the specified BKP CLK ready flag is set or not.
 * @param  Flag - @ref BKP_CLK_Flags_TypeDef - specifies the clock generator ready flag to check.
 * @retval @ref FlagStatus - The state of BKP CLK ready flag (SET or RESET).
 */
FlagStatus BKP_CLK_GetFlagStatus(BKP_CLK_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_BKP_CLK_FLAG(Flag));

    if (MDR_BKP->REG_0F & (uint32_t)Flag) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/** @} */ /* End of group BKP_Clock_Source_Control_Functions */

/** @addtogroup BKP_RTC_Control_Functions BKP RTC control functions
 * @{
 */

/**
 * @brief  Enables or disables the RTC.
 * @param  NewState - @ref FunctionalState - new state of the RTC.
 * @retval None.
 */
void BKP_RTC_Cmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        MDR_BKP->REG_0F |= BKP_REG_0F_RTC_EN_Msk;
    } else {
        MDR_BKP->REG_0F &= ~BKP_REG_0F_RTC_EN_Msk;
    }
}

/**
  * @brief  Enables or disables RTC reset.
            On reset, the RTC registers are set to their default reset values.
  * @param  NewState - @ref FunctionalState - new state of the RTC reset.
  * @retval None.
  */
void BKP_RTC_Reset(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        MDR_BKP->REG_0F |= BKP_REG_0F_RTC_RESET_Msk;
    } else {
        MDR_BKP->REG_0F &= ~BKP_REG_0F_RTC_RESET_Msk;
    }
}

/**
 * @brief  Configures the RTC clock source.
 * @param  Clk - @ref BKP_RTC_CLK_TypeDef - specifies the RTC clock source.
 * @retval None.
 */
void BKP_RTC_SetClkSource(BKP_RTC_CLK_TypeDef Clk)
{
    uint32_t TmpReg;

    /* Check the parameter */
    assert_param(IS_BKP_RTC_CLK_SOURCE(Clk));

    /* Clear RTC_SEL[1:0] bits */
    TmpReg = MDR_BKP->REG_0F & ~BKP_REG_0F_RTC_SEL_Msk;
    /* Set RTC_SEL[1:0] bits according to RTC clock source */
    TmpReg |= (uint32_t)Clk;

    /* Configure BKP_REG_0F register with new value */
    MDR_BKP->REG_0F = TmpReg;
}

/**
 * @brief  Configures the RTC_CLK clock calibration.
 * @param  Calibration: specifies the number of RTC_CLK clocks out of 2^20 to be discarded.
 *         This parameter can be a number between 0x00 and 0xFF.
 * @retval None.
 */
void BKP_RTC_SetClkCalibration(uint8_t Calibration)
{
    uint32_t TmpReg;

    /* Clear RTC_CAL[7:0] bits */
    TmpReg = MDR_BKP->REG_0F & ~BKP_REG_0F_RTC_CAL_Msk;
    /* Set RTC_CAL[7:0] bits according to RTC calibration value */
    TmpReg |= (uint32_t)Calibration << BKP_REG_0F_RTC_CAL_Pos;

    /* Configure BKP_REG_0F register with new value */
    MDR_BKP->REG_0F = TmpReg;
}

/**
 * @brief  Waits until last write operation on RTC registers has finished.
 * @note   This function must be called before any write to RTC registers.
 * @param  None.
 * @retval None.
 */
void BKP_RTC_WaitForUpdate(void)
{
    /* Loop until WEC flag is set */
    while ((MDR_BKP->RTC_CS & BKP_RTC_CS_WEC_Msk) == BKP_RTC_CS_WEC_Msk) { }
}

/**
 * @brief  Sets the RTC counter value.
 * @param  CounterValue: RTC counter new value.
 * @retval None.
 */
void BKP_RTC_SetCounter(uint32_t CounterValue)
{
    MDR_BKP->RTC_CNT = CounterValue;
}

/**
 * @brief  Gets the RTC counter value.
 * @param  None.
 * @retval RTC counter value.
 */
uint32_t BKP_RTC_GetCounter(void)
{
    return MDR_BKP->RTC_CNT;
}

/**
 * @brief  Sets the RTC alarm value.
 * @param  AlarmValue: RTC alarm new value.
 * @retval None.
 */
void BKP_RTC_SetAlarm(uint32_t AlarmValue)
{
    MDR_BKP->RTC_ALRM = AlarmValue;
}

/**
 * @brief  Gets the RTC alarm value.
 * @param  None.
 * @retval RTC alarm value.
 */
uint32_t BKP_RTC_GetAlarm(void)
{
    return MDR_BKP->RTC_ALRM;
}

/**
 * @brief  Sets the value of the RTC_CLK prescaler.
 * @note   Frequency RTC_CLKd = RTC_CLK / (PrescalerValue + 1).
 * @param  PrescalerValue: RTC prescaler new value.
 *         This parameter can be a number between 0x00000000 and 0x000FFFFF.
 * @retval None.
 */
void BKP_RTC_SetPrescaler(uint32_t PrescalerValue)
{
    /* Check the parameter */
    assert_param(IS_BKP_RTC_PRESCALER_VALUE(PrescalerValue));

    MDR_BKP->RTC_PRL = PrescalerValue;
}

/**
 * @brief  Gets the value of the RTC_CLK prescaler.
 * @note   Frequency RTC_CLKd = RTC_CLK / (PrescalerValue + 1).
 * @param  None.
 * @retval RTC prescaler value.
 */
uint32_t BKP_RTC_GetPrescaler(void)
{
    return MDR_BKP->RTC_PRL;
}

/**
  * @brief  Sets the RTC prescaler counter value.
  * @param  PrescalerCounterValue: RTC prescaler counter new value.
            This parameter can be a number between 0x00000000 and 0x000FFFFF.
  * @retval None.
  */
void BKP_RTC_SetPrescalerCounter(uint32_t PrescalerCounterValue)
{
    /* Check the parameter */
    assert_param(IS_BKP_RTC_PRESCALER_COUNTER_VALUE(PrescalerCounterValue));

    MDR_BKP->RTC_DIV = PrescalerCounterValue;
}

/**
 * @brief  Gets the RTC prescaler counter value.
 * @param  None.
 * @retval RTC prescaler counter value.
 */
uint32_t BKP_RTC_GetPrescalerCounter(void)
{
    return MDR_BKP->RTC_DIV;
}

/**
 * @brief  Clears the RTC Status Flags.
 * @param  Flags - @ref BKP_RTC_Flags_TypeDef - specifies the flags to clear.
 *         This parameter can be any combination of the following values:
 *             @arg BKP_RTC_FLAG_OWF:  Overflow flag.
 *             @arg BKP_RTC_FLAG_SECF: Second flag.
 *             @arg BKP_RTC_FLAG_ALRF: Alarm flag.
 * @retval None.
 */
void BKP_RTC_ClearFlags(uint32_t Flags)
{
    /* Check the parameter */
    assert_param(IS_BKP_RTC_FLAGS_CLR(Flags));

    MDR_BKP->RTC_CS = (MDR_BKP->RTC_CS & ~BKP_RTC_FLAG_CLR_MASK) | (uint32_t)Flags;
}

/**
 * @brief  Checks whether the specified RTC Status Flag is set or not.
 * @param  Flag: specifies the flag to check.
 *         This parameter can be one of @ref BKP_RTC_Flags_TypeDef values.
 * @retval @ref FlagStatus - Current Status Flag state (SET or RESET).
 */
FlagStatus BKP_RTC_GetFlagStatus(BKP_RTC_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameter */
    assert_param(IS_BKP_RTC_FLAG(Flag));

    if (MDR_BKP->RTC_CS & (uint32_t)Flag) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Returns the RTC Status Flags combined value.
 * @param  None.
 * @retval The RTC Status Flags combined value.
 */
uint32_t BKP_RTC_GetStatus(void)
{
    return MDR_BKP->RTC_CS & BKP_RTC_FLAG_MASK;
}

/**
 * @brief  Enables or disables the RTC interrupts.
 * @param  ITs: specifies the RTC interrupt sources to be enabled or disabled.
 *         This parameter can be any combination of @ref BKP_RTC_IT_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the RTC interrupts.
 * @retval None.
 */
void BKP_RTC_ITConfig(uint32_t ITs, FunctionalState NewState)
{
    uint32_t TmpReg;

    /* Check the parameters */
    assert_param(IS_BKP_RTC_CONFIG_ITS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Clear OWF, SECF and ALRF bits */
    TmpReg = MDR_BKP->RTC_CS & ~BKP_RTC_FLAG_CLR_MASK;

    /* Form new value */
    if (NewState != DISABLE) {
        TmpReg |= (ITs << BKP_RTC_CS_OWF_IE_Pos);
    } else {
        TmpReg &= ~(ITs << BKP_RTC_CS_OWF_IE_Pos);
    }

    /* Configure BKP_RTC_CS register with new value */
    MDR_BKP->RTC_CS = TmpReg;
}

/**
 * @brief  Checks whether the specified RTC masked interrupt has occurred or not.
 * @param  IT - @ref BKP_RTC_IT_TypeDef - specifies the RTC interrupt source to check.
 * @retval @ref ITStatus - The state of the RTC_IT (SET or RESET).
 */
ITStatus BKP_RTC_GetITFlagStatus(BKP_RTC_IT_TypeDef IT)
{
    ITStatus Status;
    uint32_t TmpReg, FlagState, FlagEn;

    /* Check the parameter */
    assert_param(IS_BKP_RTC_CONFIG_IT(IT));

    TmpReg = MDR_BKP->RTC_CS;

    FlagState = TmpReg & (uint32_t)IT;

    FlagEn = TmpReg & (BKP_RTC_CS_OWF_IE_Msk | BKP_RTC_CS_SECF_IE_Msk | BKP_RTC_CS_ALRF_IE_Msk);
    FlagEn >>= (BKP_RTC_CS_OWF_IE_Pos - BKP_RTC_CS_OWF_Pos);

    if (FlagState & FlagEn) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Checks whether the RTC masked interrupts has occurred or not.
 * @param  None.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref BKP_RTC_IT_TypeDef.
 */
uint32_t BKP_RTC_GetITStatus(void)
{
    uint32_t TmpReg, FlagsState, FlagsEn;

    TmpReg = MDR_BKP->RTC_CS;

    FlagsState = TmpReg & (BKP_RTC_CS_OWF_Msk | BKP_RTC_CS_SECF_Msk | BKP_RTC_CS_ALRF_Msk);

    FlagsEn = TmpReg & (BKP_RTC_CS_OWF_IE_Msk | BKP_RTC_CS_SECF_IE_Msk | BKP_RTC_CS_ALRF_IE_Msk);
    FlagsEn >>= (BKP_RTC_CS_OWF_IE_Pos - BKP_RTC_CS_OWF_Pos);

    return (FlagsState & FlagsEn);
}

/** @} */ /* End of group BKP_RTC_Control_Functions */

/** @} */ /* End of group BKP_Exported_Functions */

/** @} */ /* End of group BKP */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_bkp.c */

