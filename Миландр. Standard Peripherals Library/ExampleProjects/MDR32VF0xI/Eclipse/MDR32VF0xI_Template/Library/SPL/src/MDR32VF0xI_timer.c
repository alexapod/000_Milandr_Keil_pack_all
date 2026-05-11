/**
 *******************************************************************************
 * @file    MDR32VF0xI_timer.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/01/2025
 * @brief   This file contains all the TIMER firmware functions.
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
#include "MDR32VF0xI_timer.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup TIMER TIMER
 * @{
 */

/** @defgroup TIMER_Private_Defines TIMER Private Defines
 * @{
 */

#define IS_TIMER_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_TIMER1) || \
                                     ((PERIPH) == MDR_TIMER2) || \
                                     ((PERIPH) == MDR_TIMER3) || \
                                     ((PERIPH) == MDR_TIMER4))

/** @} */ /* End of the group TIMER_Private_Defines */

/** @addtogroup TIMER_Exported_Functions TIMER Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the TIMERx peripheral registers to their default reset values.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return None.
 */
void TIMER_DeInit(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->CNTRL = 0;
    TIMERx->CNT   = 0;
    TIMERx->PSG   = 0;
    TIMERx->ARR   = 0;

    TIMERx->CH1_CNTRL0 = 0;
    TIMERx->CH1_CNTRL1 = 0;
    TIMERx->CH1_CNTRL2 = 0;
    TIMERx->CH1_DTG    = 0;
    TIMERx->CH1_CCR    = 0;
    TIMERx->CH1_CCR1   = 0;

    TIMERx->CH2_CNTRL0 = 0;
    TIMERx->CH2_CNTRL1 = 0;
    TIMERx->CH2_CNTRL2 = 0;
    TIMERx->CH2_DTG    = 0;
    TIMERx->CH2_CCR    = 0;
    TIMERx->CH2_CCR1   = 0;

    TIMERx->CH3_CNTRL0 = 0;
    TIMERx->CH3_CNTRL1 = 0;
    TIMERx->CH3_CNTRL2 = 0;
    TIMERx->CH3_DTG    = 0;
    TIMERx->CH3_CCR    = 0;
    TIMERx->CH3_CCR1   = 0;

    TIMERx->CH4_CNTRL0 = 0;
    TIMERx->CH4_CNTRL1 = 0;
    TIMERx->CH4_CNTRL2 = 0;
    TIMERx->CH4_DTG    = 0;
    TIMERx->CH4_CCR    = 0;
    TIMERx->CH4_CCR1   = 0;

    TIMERx->BRKETR_CNTRL = 0;
    TIMERx->STATUS       = 0;
    TIMERx->IE           = 0;
    TIMERx->DMA_RE       = 0;
}

/**
 * @brief  Initialize the TIMERx counter according to
 *         the specified parameters in the TIMER_CntInitStruct.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  TIMER_CntInitStruct: The pointer to the @ref TIMER_CNT_InitTypeDef structure
 *         that contains the configuration information for the specified counter.
 * @return None.
 */
void TIMER_CNT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CNT_InitTypeDef* TIMER_CntInitStruct)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CNT_EVENT_SOURCE(TIMER_CntInitStruct->TIMER_CNT_EventSource));
    assert_param(IS_TIMER_CNT_MODE(TIMER_CntInitStruct->TIMER_CNT_Mode));
    assert_param(IS_TIMER_CNT_DIR(TIMER_CntInitStruct->TIMER_CNT_Direction));
    assert_param(IS_TIMER_CNT_PERIOD_UPDATE_MODE(TIMER_CntInitStruct->TIMER_CNT_PeriodUpdateMode));
    assert_param(IS_TIMER_FDTS_PRESCALER(TIMER_CntInitStruct->TIMER_FDTS_Prescaler));
    assert_param(IS_TIMER_ETR_FILTER(TIMER_CntInitStruct->TIMER_ETR_Filter));
    assert_param(IS_TIMER_ETR_PRESCALER(TIMER_CntInitStruct->TIMER_ETR_Prescaler));
    assert_param(IS_TIMER_ETR_POLARITY(TIMER_CntInitStruct->TIMER_ETR_Polarity));
    assert_param(IS_TIMER_BRK_POLARITY(TIMER_CntInitStruct->TIMER_BRK_Polarity));

    TIMERx->CNT = TIMER_CntInitStruct->TIMER_CNT_Counter;
    TIMERx->PSG = TIMER_CntInitStruct->TIMER_CNT_Prescaler;
    TIMERx->ARR = TIMER_CntInitStruct->TIMER_CNT_Period;

    /* Form a new value for the CNTRL register. */
    TmpReg = (uint32_t)TIMER_CntInitStruct->TIMER_CNT_EventSource |
             (uint32_t)TIMER_CntInitStruct->TIMER_CNT_Mode |
             (uint32_t)TIMER_CntInitStruct->TIMER_CNT_Direction |
             (uint32_t)TIMER_CntInitStruct->TIMER_CNT_PeriodUpdateMode |
             (uint32_t)TIMER_CntInitStruct->TIMER_FDTS_Prescaler;

    /* Configure the CNTRL register with a new value. */
    TIMERx->CNTRL = TmpReg;

    /* Form a new value for the BRKETR_CNTRL register. */
    TmpReg = (uint32_t)TIMER_CntInitStruct->TIMER_ETR_Filter |
             (uint32_t)TIMER_CntInitStruct->TIMER_ETR_Prescaler |
             (uint32_t)TIMER_CntInitStruct->TIMER_ETR_Polarity |
             (uint32_t)TIMER_CntInitStruct->TIMER_BRK_Polarity;

    /* Configure the BRKETR_CNTRL register with a new value. */
    TIMERx->BRKETR_CNTRL = TmpReg;
}

/**
 * @brief  Fill each TIMER_CntInitStruct member with its default value.
 * @param  TIMER_CntInitStruct: The pointer to the @ref TIMER_CNT_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void TIMER_CNT_StructInit(TIMER_CNT_InitTypeDef* TIMER_CntInitStruct)
{
    TIMER_CntInitStruct->TIMER_CNT_Counter          = 0;
    TIMER_CntInitStruct->TIMER_CNT_Prescaler        = 0;
    TIMER_CntInitStruct->TIMER_CNT_Period           = 0;
    TIMER_CntInitStruct->TIMER_CNT_EventSource      = TIMER_CNT_EVNT_SRC_TIM_CLK;
    TIMER_CntInitStruct->TIMER_CNT_Mode             = TIMER_CNT_MODE_CLK_FIXED_DIR;
    TIMER_CntInitStruct->TIMER_CNT_Direction        = TIMER_CNT_DIR_UP;
    TIMER_CntInitStruct->TIMER_CNT_PeriodUpdateMode = TIMER_CNT_PERIOD_UPD_IMMEDIATELY;
    TIMER_CntInitStruct->TIMER_FDTS_Prescaler       = TIMER_FDTS_PRESCALER_DIV_1;
    TIMER_CntInitStruct->TIMER_ETR_Filter           = TIMER_ETR_FILTER_1FF_AT_FDTS;
    TIMER_CntInitStruct->TIMER_ETR_Prescaler        = TIMER_ETR_PRESCALER_DIV_1;
    TIMER_CntInitStruct->TIMER_ETR_Polarity         = TIMER_ETR_POLARITY_NON_INV;
    TIMER_CntInitStruct->TIMER_BRK_Polarity         = TIMER_BRK_POLARITY_NON_INV;
}

/**
 * @brief  Enable or disable the specified TIMERx counter.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  NewState: @ref FunctionalState - a new state of the counter.
 * @return None.
 */
void TIMER_CNT_Cmd(MDR_TIMER_TypeDef* TIMERx, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the TIMERx counter by setting the CNT_EN bit in the CNTRL register. */
        TIMERx->CNTRL |= TIMER_CNTRL_CNT_EN;
    } else {
        /* Disable the TIMERx counter by clearing the CNT_EN bit in the CNTRL register. */
        TIMERx->CNTRL &= ~TIMER_CNTRL_CNT_EN;
    }
}

/**
 * @brief  Get a specified TIMERx counter work state.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return @ref FunctionalState - the current work state of the specified TIMERx counter.
 */
FunctionalState TIMER_CNT_GetCmdState(MDR_TIMER_TypeDef* TIMERx)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    if ((TIMERx->CNTRL & TIMER_CNTRL_CNT_EN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set the TIMERx counter register value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Counter: Specify a new value of the counter register.
 * @return None.
 */
void TIMER_CNT_SetCounter(MDR_TIMER_TypeDef* TIMERx, uint32_t Counter)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->CNT = Counter;
}

/**
 * @brief  Return the TIMERx counter register value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return Counter register value.
 */
uint32_t TIMER_CNT_GetCounter(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return TIMERx->CNT;
}

/**
 * @brief  Set the TIMERx TIM_CLK prescaler register value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Prescaler: Specify the TIM_CLK prescaler register value.
 * @return None.
 */
void TIMER_CNT_SetPrescaler(MDR_TIMER_TypeDef* TIMERx, uint32_t Prescaler)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->PSG = Prescaler;
}

/**
 * @brief  Return the TIMERx TIM_CLK prescaler register value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return TIM_CLK prescaler register value.
 */
uint32_t TIMER_CNT_GetPrescaler(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return TIMERx->PSG;
}

/**
 * @brief  Set the TIMERx counter period (ARR register) update mode.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  PeriodUpdateMode: @ref TIMER_CNT_PeriodUpdateMode_TypeDef - specify the counter period (ARR register) update mode.
 * @return None.
 */
void TIMER_CNT_SetPeriodUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_PeriodUpdateMode_TypeDef PeriodUpdateMode)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CNT_PERIOD_UPDATE_MODE(PeriodUpdateMode));

    TmpReg = TIMERx->CNTRL;
    TmpReg &= ~TIMER_CNTRL_ARRB_EN;
    TmpReg |= (uint32_t)PeriodUpdateMode;
    TIMERx->CNTRL = TmpReg;
}

/**
 * @brief  Set the TIMERx counter period (ARR register) value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Period: Specify the counter period (ARR register) value. The full counter period is Period + 1.
 * @return None.
 */
void TIMER_CNT_SetPeriod(MDR_TIMER_TypeDef* TIMERx, uint32_t Period)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->ARR = Period;
}

/**
 * @brief  Return the TIMERx counter period (ARR register) value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return Counter period (ARR register) value.
 */
uint32_t TIMER_CNT_GetPeriod(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return TIMERx->ARR;
}

/**
 * @brief  Configure the TIMERx FDTS prescaler.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Prescaler: @ref TIMER_FDTS_Prescaler_TypeDef - specify the FDTS prescaler.
 * @return None.
 */
void TIMER_FDTS_SetPrescaler(MDR_TIMER_TypeDef* TIMERx, TIMER_FDTS_Prescaler_TypeDef Prescaler)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FDTS_PRESCALER(Prescaler));

    TmpReg = TIMERx->CNTRL;
    TmpReg &= ~TIMER_CNTRL_FDTS_Msk;
    TmpReg |= (uint32_t)Prescaler;
    TIMERx->CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx counter event source.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  EventSource: @ref TIMER_CNT_EventSource_TypeDef - specify the counter event source.
 * @return None.
 */
void TIMER_CNT_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_EventSource_TypeDef EventSource)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CNT_EVENT_SOURCE(EventSource));

    TmpReg = TIMERx->CNTRL;
    TmpReg &= ~TIMER_CNTRL_EVNT_SEL_Msk;
    TmpReg |= (uint32_t)EventSource;
    TIMERx->CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx counter mode.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Mode: @ref TIMER_CNT_Mode_TypeDef - specify the counter mode.
 * @return None.
 */
void TIMER_CNT_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_Mode_TypeDef Mode)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CNT_MODE(Mode));

    TmpReg = TIMERx->CNTRL;
    TmpReg &= ~TIMER_CNTRL_CNT_MODE_Msk;
    TmpReg |= (uint32_t)Mode;
    TIMERx->CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx counter direction.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Direction: @ref TIMER_CNT_Dir_TypeDef - specify the counter direction.
 * @return None.
 */
void TIMER_CNT_SetDirection(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_Dir_TypeDef Direction)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CNT_DIR(Direction));

    TmpReg = TIMERx->CNTRL;
    TmpReg &= ~TIMER_CNTRL_DIR;
    TmpReg |= (uint32_t)Direction;
    TIMERx->CNTRL = TmpReg;
}

/**
 * @brief  Return the TIMERx counter direction.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return @ref TIMER_CNT_Dir_TypeDef - the current counter direction.
 */
TIMER_CNT_Dir_TypeDef TIMER_CNT_GetDirection(MDR_TIMER_TypeDef* TIMERx)
{
    TIMER_CNT_Dir_TypeDef Direction;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    if ((TIMERx->CNTRL & TIMER_CNTRL_DIR) == 0) {
        Direction = TIMER_CNT_DIR_UP;
    } else {
        Direction = TIMER_CNT_DIR_DOWN;
    }

    return Direction;
}

/**
 * @brief  Check whether the TIMERx CNT, PSG or ARR write operation is in progress or not.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return @ref FlagStatus - the CNTRL.WR_CMPL flag current state:
 *             @arg SET:   Writing to the CNT, PSG or ARR registers is in progress.
 *             @arg RESET: Writing to the CNT, PSG or ARR registers is completed.
 */
FlagStatus TIMER_CNT_GetWriteStatus(MDR_TIMER_TypeDef* TIMERx)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    if ((TIMERx->CNTRL & TIMER_CNTRL_WR_CMPL) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Configure the TIMERx ETR input.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Prescaler: @ref TIMER_ETR_Prescaler_TypeDef - specify the ETR signal prescaler value.
 * @param  Polarity: @ref TIMER_ETR_Polarity_TypeDef - enable or disable inversion of the ETR input.
 * @param  Filter: @ref TIMER_ETR_Filter_TypeDef - specify the ETR filter configuration.
 * @return None.
 */
void TIMER_ETR_InputConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler, TIMER_ETR_Polarity_TypeDef Polarity, TIMER_ETR_Filter_TypeDef Filter)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_PRESCALER(Prescaler));
    assert_param(IS_TIMER_ETR_POLARITY(Polarity));
    assert_param(IS_TIMER_ETR_FILTER(Filter));

    TmpReg = TIMERx->BRKETR_CNTRL;
    TmpReg &= ~(TIMER_BRKETR_CNTRL_ETR_FLTR_Msk | TIMER_BRKETR_CNTRL_ETR_PSC_Msk | TIMER_BRKETR_CNTRL_ETR_INV);
    TmpReg |= (uint32_t)Prescaler |
              (uint32_t)Polarity |
              (uint32_t)Filter;
    TIMERx->BRKETR_CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx ETR filter.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Filter: @ref TIMER_ETR_Filter_TypeDef - specify the ETR filter configuration.
 * @return None.
 */
void TIMER_ETR_FilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Filter_TypeDef Filter)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_FILTER(Filter));

    TmpReg = TIMERx->BRKETR_CNTRL;
    TmpReg &= ~TIMER_BRKETR_CNTRL_ETR_FLTR_Msk;
    TmpReg |= (uint32_t)Filter;
    TIMERx->BRKETR_CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx ETR signal prescaler value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Prescaler: @ref TIMER_ETR_Prescaler_TypeDef - specify the ETR signal prescaler value.
 * @return None.
 */
void TIMER_ETR_PrescalerConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_PRESCALER(Prescaler));

    TmpReg = TIMERx->BRKETR_CNTRL;
    TmpReg &= ~TIMER_BRKETR_CNTRL_ETR_PSC_Msk;
    TmpReg |= (uint32_t)Prescaler;
    TIMERx->BRKETR_CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx ETR input inversion.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Polarity: @ref TIMER_ETR_Polarity_TypeDef - enable or disable inversion of the ETR input.
 * @return None.
 */
void TIMER_ETR_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Polarity_TypeDef Polarity)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_POLARITY(Polarity));

    TmpReg = TIMERx->BRKETR_CNTRL;
    TmpReg &= ~TIMER_BRKETR_CNTRL_ETR_INV;
    TmpReg |= (uint32_t)Polarity;
    TIMERx->BRKETR_CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx BRK input inversion.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Polarity: @ref TIMER_BRK_Polarity_TypeDef - enable or disable inversion of the BRK input.
 * @return None.
 */
void TIMER_BRK_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_BRK_Polarity_TypeDef Polarity)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_BRK_POLARITY(Polarity));

    TmpReg = TIMERx->BRKETR_CNTRL;
    TmpReg &= ~TIMER_BRKETR_CNTRL_BRK_INV;
    TmpReg |= (uint32_t)Polarity;
    TIMERx->BRKETR_CNTRL = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel filter.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  Filter: @ref TIMER_CH_Filter_TypeDef - specify the channel filter configuration.
 * @return None.
 */
void TIMER_CH_FilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_Filter_TypeDef Filter)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_FILTER(Filter));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL0_CH_FLTR_Msk;
    TmpReg |= (uint32_t)Filter;
    *PtrReg = TmpReg;
}

/**
 * @brief  Initialize the TIMERx channel according to
 *         the specified parameters in the TIMER_ChInitStruct.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  TIMER_ChInitStruct: The pointer to the @ref TIMER_CH_InitTypeDef structure
 *         that contains the configuration information for a specified channel.
 * @return None.
 */
void TIMER_CH_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_InitTypeDef* TIMER_ChInitStruct)
{
    uint32_t Channel;
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(TIMER_ChInitStruct->TIMER_CH_Number));
    assert_param(IS_TIMER_CH_MODE(TIMER_ChInitStruct->TIMER_CH_Mode));
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_UseCCR1));
    assert_param(IS_TIMER_CH_PWM_REF_FORMAT(TIMER_ChInitStruct->TIMER_CH_PWM_REF_Format));
    assert_param(IS_TIMER_CH_PWM_CCR_UPDATE_MODE(TIMER_ChInitStruct->TIMER_CH_PWM_CCR_UpdateMode));
    assert_param(IS_TIMER_CH_PWM_DTG_CLK_SOURCE(TIMER_ChInitStruct->TIMER_CH_PWM_DTG_ClockSource));
    assert_param(IS_TIMER_CH_PWM_DTG_AUX_PRESCALER(TIMER_ChInitStruct->TIMER_CH_PWM_DTG_AuxPrescaler));
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_PWM_ETR_UseReset));
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_PWM_BRK_UseReset));
    assert_param(IS_TIMER_CH_CAP_CCR_EVENT_SOURCE(TIMER_ChInitStruct->TIMER_CH_CAP_CCR_EventSource));
    assert_param(IS_TIMER_CH_CAP_CCR1_EVENT_SOURCE(TIMER_ChInitStruct->TIMER_CH_CAP_CCR1_EventSource));
    assert_param(IS_TIMER_CH_CAP_EVENT_PRESCALER(TIMER_ChInitStruct->TIMER_CH_CAP_EventPrescaler));
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_CAP_UseEventDelay));
    assert_param(IS_TIMER_CH_FILTER(TIMER_ChInitStruct->TIMER_CH_CAP_Filter));

    Channel = (uint32_t)TIMER_ChInitStruct->TIMER_CH_Number;

    TmpReg = ((uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_DTG_MainPrescaler << TIMER_CH_DTG_DTG_Pos) |
             ((uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_DTG_AuxPrescaler << TIMER_CH_DTG_DTGX_Pos) |
             (uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_DTG_ClockSource;

    *(&TIMERx->CH1_DTG + Channel) = TmpReg;

    TmpReg = (uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_CCR_UpdateMode |
             (uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_CCR1_EventSource |
             ((uint32_t)TIMER_ChInitStruct->TIMER_CH_UseCCR1 << TIMER_CH_CNTRL2_CCR1_EN_Pos) |
             ((uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_UseEventDelay << TIMER_CH_CNTRL2_EVNT_DLY_Pos);

    *(&TIMERx->CH1_CNTRL2 + Channel) = TmpReg;

    TmpReg = (uint32_t)TIMER_ChInitStruct->TIMER_CH_Mode |
             (uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_REF_Format |
             (uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_EventPrescaler |
             (uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_CCR_EventSource |
             (uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_Filter |
             ((uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_BRK_UseReset << TIMER_CH_CNTRL0_BRK_EN_Pos);

    if (TIMER_ChInitStruct->TIMER_CH_PWM_ETR_UseReset != DISABLE) {
        TmpReg |= TIMER_CH_CNTRL0_ETR_EN | TIMER_CH_CNTRL0_OCCE;
    }

    *(&TIMERx->CH1_CNTRL0 + Channel) = TmpReg;
}

/**
 * @brief  Fill each TIMER_ChInitStruct member with its default value.
 * @param  TIMER_ChInitStruct: The pointer to the @ref TIMER_CH_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void TIMER_CH_StructInit(TIMER_CH_InitTypeDef* TIMER_ChInitStruct)
{
    /* General channel parameters. */
    TIMER_ChInitStruct->TIMER_CH_Number  = TIMER_CH1;
    TIMER_ChInitStruct->TIMER_CH_Mode    = TIMER_CH_MODE_PWM;
    TIMER_ChInitStruct->TIMER_CH_UseCCR1 = DISABLE;

    /* Channel parameters if the PWM mode is selected. */
    TIMER_ChInitStruct->TIMER_CH_PWM_REF_Format        = TIMER_CH_PWM_REF_FORMAT_0;
    TIMER_ChInitStruct->TIMER_CH_PWM_CCR_UpdateMode    = TIMER_CH_PWM_CCR_UPD_IMMEDIATELY;
    TIMER_ChInitStruct->TIMER_CH_PWM_DTG_ClockSource   = TIMER_CH_PWM_DTG_CLK_SRC_TIM_CLK;
    TIMER_ChInitStruct->TIMER_CH_PWM_DTG_MainPrescaler = 0;
    TIMER_ChInitStruct->TIMER_CH_PWM_DTG_AuxPrescaler  = 0;
    TIMER_ChInitStruct->TIMER_CH_PWM_ETR_UseReset      = DISABLE;
    TIMER_ChInitStruct->TIMER_CH_PWM_BRK_UseReset      = DISABLE;

    /* Channel parameters if the capture mode is selected. */
    TIMER_ChInitStruct->TIMER_CH_CAP_CCR_EventSource  = TIMER_CH_CAP_CCR_EVNT_SRC_RE;
    TIMER_ChInitStruct->TIMER_CH_CAP_CCR1_EventSource = TIMER_CH_CAP_CCR1_EVNT_SRC_RE;
    TIMER_ChInitStruct->TIMER_CH_CAP_EventPrescaler   = TIMER_CH_CAP_EVNT_PRESCALER_DIV_1;
    TIMER_ChInitStruct->TIMER_CH_CAP_UseEventDelay    = ENABLE;
    TIMER_ChInitStruct->TIMER_CH_CAP_Filter           = TIMER_CH_FILTER_1FF_AT_FDTS;
}

/**
 * @brief  Set the TIMERx channel capture/compare register (CCR) value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  CCR: Specify a new value of the capture/compare register (CCR).
 * @return None.
 */
void TIMER_CH_SetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint32_t CCR)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    *(&TIMERx->CH1_CCR + (uint32_t)Channel) = CCR;
}

/**
 * @brief  Return the TIMERx channel capture/compare register (CCR) value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return Channel capture/compare register (CCR) value.
 */
uint32_t TIMER_CH_GetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    return (uint32_t)*(&TIMERx->CH1_CCR + (uint32_t)Channel);
}

/**
 * @brief  Check whether the TIMERx CCR write operation is in progress or not.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return @ref FlagStatus - the CHy_CNTRL0.WR_CMPL flag current state:
 *             @arg SET:   Writing to the CCR is in progress.
 *             @arg RESET: Writing to the CCR is completed.
 */
FlagStatus TIMER_CH_GetCCRWriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    __IO uint32_t* PtrReg;
    FlagStatus     Status;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    if ((*PtrReg & TIMER_CH_CNTRL0_WR_CMPL) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Enable or disable the TIMERx channel CCR1 register.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  NewState: @ref FunctionalState - a new state of the CCR1_EN bit.
 * @return None.
 */
void TIMER_CH_CCR1Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    PtrReg = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the TIMERx channel CCR1 register by setting the CCR1_EN bit in the CHy_CNTRL2 register. */
        *PtrReg |= TIMER_CH_CNTRL2_CCR1_EN;
    } else {
        /* Disable the TIMERx channel CCR1 register by clearing the CCR1_EN bit in the CHy_CNTRL2 register. */
        *PtrReg &= ~TIMER_CH_CNTRL2_CCR1_EN;
    }
}

/**
 * @brief  Get the TIMERx channel CCR1 register work state.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return @ref FunctionalState - the current state of the CCR1_EN bit.
 */
FunctionalState TIMER_CH_GetCCR1CmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    FunctionalState State;
    __IO uint32_t*  PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    PtrReg = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    if ((*PtrReg & TIMER_CH_CNTRL2_CCR1_EN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set TIMERx channel capture/compare register 1 (CCR1) value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  CCR1: Specify a new value of channel capture/compare register 1 (CCR1).
 * @return None.
 */
void TIMER_CH_SetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint32_t CCR1)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    *(&TIMERx->CH1_CCR1 + (uint32_t)Channel) = CCR1;
}

/**
 * @brief  Return TIMERx channel capture/compare register 1 (CCR1) value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return Channel capture/compare register 1 (CCR1) value.
 */
uint32_t TIMER_CH_GetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    return (uint32_t)*(&TIMERx->CH1_CCR1 + (uint32_t)Channel);
}

/**
 * @brief  Check whether the TIMERx CCR1 write operation is in progress or not.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return @ref FlagStatus - the CHy_CNTRL0.WR_CMPL1 flag current state:
 *             @arg SET:   Writing  to CCR1 is in progress.
 *             @arg RESET: Writing to CCR1 is completed.
 */
FlagStatus TIMER_CH_GetCCR1WriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    __IO uint32_t* PtrReg;
    FlagStatus     Status;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    if ((*PtrReg & TIMER_CH_CNTRL0_WR_CMPL1) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Set the TIMERx channel capture/compare registers (CCR and CCR1) update mode.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  UpdateMode: @ref TIMER_CH_PWM_CCR_UpdateMode_TypeDef - specify the channel capture/compare registers (CCR and CCR1) update mode.
 * @return None.
 */
void TIMER_CH_PWM_SetCompareUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_CCR_UpdateMode_TypeDef UpdateMode)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_PWM_CCR_UPDATE_MODE(UpdateMode));

    PtrReg = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL2_CCR_RLD;
    TmpReg |= (uint32_t)UpdateMode;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx REF signal format.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  Format: @ref TIMER_CH_PWM_REF_Format_TypeDef - a new value of the REF signal format.
 * @return None.
 */
void TIMER_CH_PWM_REF_FormatConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_REF_Format_TypeDef Format)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_PWM_REF_FORMAT(Format));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL0_OCCM_Msk;
    TmpReg |= (uint32_t)Format;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx dead time generator (DTG).
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  MainPrescaler: Specify a main prescaler value.
 *         This parameter can be a number from 0x00 to 0xFF.
 * @param  AuxPrescaler: Specify an auxiliary prescaler value.
 *         This parameter can be a number from 0x00 to 0x0F.
 * @param  ClockSource: @ref TIMER_CH_PWM_DTG_ClockSource_TypeDef - specify the DTG clock source.
 * @return None.
 */
void TIMER_CH_PWM_DTG_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint8_t MainPrescaler, uint8_t AuxPrescaler, TIMER_CH_PWM_DTG_ClockSource_TypeDef ClockSource)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_PWM_DTG_AUX_PRESCALER(AuxPrescaler));
    assert_param(IS_TIMER_CH_PWM_DTG_CLK_SOURCE(ClockSource));

    TmpReg = ((uint32_t)MainPrescaler << TIMER_CH_DTG_DTG_Pos) |
             ((uint32_t)AuxPrescaler << TIMER_CH_DTG_DTGX_Pos) |
             (uint32_t)ClockSource;

    *(&TIMERx->CH1_DTG + (uint32_t)Channel) = TmpReg;
}

/**
 * @brief  Enable or disable the TIMERx channel ETR reset (the REF reset when the ETR input is high).
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  NewState: @ref FunctionalState - a new state of the ETR reset.
 * @return None.
 */
void TIMER_CH_PWM_ETR_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the TIMERx channel ETR reset by setting the ETR_EN and OCCE bits in the CHy_CNTRL0 register. */
        *PtrReg |= TIMER_CH_CNTRL0_ETR_EN | TIMER_CH_CNTRL0_OCCE;
    } else {
        /* Disable the TIMERx channel ETR reset by clearing the ETR_EN and OCCE bits in the CHy_CNTRL0 register. */
        *PtrReg &= ~(TIMER_CH_CNTRL0_ETR_EN | TIMER_CH_CNTRL0_OCCE);
    }
}

/**
 * @brief  Get the TIMERx channel ETR reset work state.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return @ref FunctionalState - the current work state of the TIMERx channel ETR reset.
 */
FunctionalState TIMER_CH_PWM_ETR_GetResetCmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    FunctionalState State;
    __IO uint32_t*  PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    if ((*PtrReg & (TIMER_CH_CNTRL0_ETR_EN | TIMER_CH_CNTRL0_OCCE)) != (TIMER_CH_CNTRL0_ETR_EN | TIMER_CH_CNTRL0_OCCE)) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Enable or disable the TIMERx channel BKR reset (REF and DTG reset when the BKR input is low).
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  NewState: @ref FunctionalState - a new state of the BRK reset.
 * @return None.
 */
void TIMER_CH_PWM_BRK_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the TIMERx channel BRK reset by setting the BRK_EN bit in the CHy_CNTRL0 register. */
        *PtrReg |= TIMER_CH_CNTRL0_BRK_EN;
    } else {
        /* Disable the TIMERx channel BRK reset by clearing the BRK_EN bit in the CHy_CNTRL0 register. */
        *PtrReg &= ~TIMER_CH_CNTRL0_BRK_EN;
    }
}

/**
 * @brief  Get the TIMERx channel BKR reset work state.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return @ref FunctionalState - the current work state of the TIMERx channel BKR reset.
 */
FunctionalState TIMER_CH_PWM_BRK_GetResetCmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    FunctionalState State;
    __IO uint32_t*  PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    if ((*PtrReg & TIMER_CH_CNTRL0_BRK_EN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Configure the TIMERx capture events prescaler value.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  EventPrescaler: @ref TIMER_CH_CAP_EventPrescaler_TypeDef - specify the channel capture events prescaler value.
 * @return None.
 */
void TIMER_CH_CAP_SetEventPrescaler(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_EventPrescaler_TypeDef EventPrescaler)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_CAP_EVENT_PRESCALER(EventPrescaler));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL0_CH_PSC_Msk;
    TmpReg |= (uint32_t)EventPrescaler;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel capture event source for the CCR register.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  EventSource: @ref TIMER_CH_CAP_CCR_EventSource_TypeDef - specify the channel capture event source for the CCR register.
 * @return None.
 */
void TIMER_CH_CAP_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR_EventSource_TypeDef EventSource)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_CAP_CCR_EVENT_SOURCE(EventSource));

    PtrReg = &TIMERx->CH1_CNTRL0 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL0_CH_SEL_Msk;
    TmpReg |= (uint32_t)EventSource;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel capture event source for the CCR1 register.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  Event1Source: @ref TIMER_CH_CAP_CCR1_EventSource_TypeDef - specify the channel capture event source for the CCR1 register.
 * @return None.
 */
void TIMER_CH_CAP_Event1SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR1_EventSource_TypeDef Event1Source)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_CAP_CCR1_EVENT_SOURCE(Event1Source));

    PtrReg = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL2_CH_SEL1_Msk;
    TmpReg |= (uint32_t)Event1Source;
    *PtrReg = TmpReg;
}

/**
 * @brief  Enable or disable the synchronization between the capture event and the update of the CCR and CCR1 registers.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  NewState: @ref FunctionalState - a new state of the EVNT_DLY bit.
 * @return None.
 */
void TIMER_CH_CAP_EventDelayCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    PtrReg = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the TIMERx channel event delay by setting the EVNT_DLY bit in the CHy_CNTRL2 register. */
        *PtrReg |= TIMER_CH_CNTRL2_EVNT_DLY;
    } else {
        /* Disable the TIMERx channel event delay by clearing the EVNT_DLY bit in the CHy_CNTRL2 register. */
        *PtrReg &= ~TIMER_CH_CNTRL2_EVNT_DLY;
    }
}

/**
 * @brief  Get the work state of the synchronization between the capture event and the update of the CCR and CCR1 registers.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @return @ref FunctionalState - the current state of the EVNT_DLY bit.
 */
FunctionalState TIMER_CH_CAP_GetEventDelayCmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    FunctionalState State;
    __IO uint32_t*  PtrReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));

    PtrReg = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    if ((*PtrReg & TIMER_CH_CNTRL2_EVNT_DLY) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Initialize the TIMERx channel output according to
 *         the specified parameters in the TIMER_ChOutInitStruct.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  TIMER_ChOutInitStruct: The pointer to the @ref TIMER_CH_OUT_InitTypeDef structure
 *         that contains the configuration information for the specified channel outputs.
 * @return None.
 */
void TIMER_CH_OUT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_OUT_InitTypeDef* TIMER_ChOutInitStruct)
{
    uint32_t Channel;
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(TIMER_ChOutInitStruct->TIMER_CH_Number));
    assert_param(IS_TIMER_CH_OUTP_POLARITY(TIMER_ChOutInitStruct->TIMER_CH_OUTP_Polarity));
    assert_param(IS_TIMER_CH_OUTP_SOURCE(TIMER_ChOutInitStruct->TIMER_CH_OUTP_Source));
    assert_param(IS_TIMER_CH_OUTP_MODE(TIMER_ChOutInitStruct->TIMER_CH_OUTP_Mode));
    assert_param(IS_TIMER_CH_OUTN_POLARITY(TIMER_ChOutInitStruct->TIMER_CH_OUTN_Polarity));
    assert_param(IS_TIMER_CH_OUTN_SOURCE(TIMER_ChOutInitStruct->TIMER_CH_OUTN_Source));
    assert_param(IS_TIMER_CH_OUTN_MODE(TIMER_ChOutInitStruct->TIMER_CH_OUTN_Mode));

    Channel = (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_Number;

    TmpReg = (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTP_Polarity |
             (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTP_Source |
             (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTP_Mode |
             (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTN_Polarity |
             (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTN_Source |
             (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTN_Mode;

    *(&TIMERx->CH1_CNTRL1 + Channel) = TmpReg;
}

/**
 * @brief  Fill each TIMER_ChOutInitStruct member with its default value.
 * @param  TIMER_ChOutInitStruct: The pointer to the @ref TIMER_CH_OUT_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void TIMER_CH_OUT_StructInit(TIMER_CH_OUT_InitTypeDef* TIMER_ChOutInitStruct)
{
    TIMER_ChOutInitStruct->TIMER_CH_Number = TIMER_CH1;

    TIMER_ChOutInitStruct->TIMER_CH_OUTP_Polarity = TIMER_CH_OUTP_POLARITY_NON_INV;
    TIMER_ChOutInitStruct->TIMER_CH_OUTP_Source   = TIMER_CH_OUTP_SRC_0;
    TIMER_ChOutInitStruct->TIMER_CH_OUTP_Mode     = TIMER_CH_OUTP_MODE_IN;

    TIMER_ChOutInitStruct->TIMER_CH_OUTN_Polarity = TIMER_CH_OUTN_POLARITY_NON_INV;
    TIMER_ChOutInitStruct->TIMER_CH_OUTN_Source   = TIMER_CH_OUTN_SRC_0;
    TIMER_ChOutInitStruct->TIMER_CH_OUTN_Mode     = TIMER_CH_OUTN_MODE_IN;
}

/**
 * @brief  Configure the TIMERx channel positive output.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  OutSource: @ref TIMER_CH_OUTP_Source_TypeDef - specify the channel positive output source.
 * @param  Mode: @ref TIMER_CH_OUTP_Mode_TypeDef - specify the channel positive output mode (output enable source).
 * @param  Polarity: @ref TIMER_CH_OUTP_Polarity_TypeDef - enable or disable the channel positive output inversion.
 * @return None.
 */
void TIMER_CH_OUTP_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Source_TypeDef OutSource, TIMER_CH_OUTP_Mode_TypeDef Mode, TIMER_CH_OUTP_Polarity_TypeDef Polarity)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTP_SOURCE(OutSource));
    assert_param(IS_TIMER_CH_OUTP_MODE(Mode));
    assert_param(IS_TIMER_CH_OUTP_POLARITY(Polarity));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~(TIMER_CH_CNTRL1_INV | TIMER_CH_CNTRL1_SELO_Msk | TIMER_CH_CNTRL1_SELOE_Msk);
    TmpReg |= (uint32_t)Polarity |
              (uint32_t)OutSource |
              (uint32_t)Mode;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel positive output source.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  OutSource: @ref TIMER_CH_OUTP_Source_TypeDef - specify the channel positive output source.
 * @return None.
 */
void TIMER_CH_OUTP_SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Source_TypeDef OutSource)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTP_SOURCE(OutSource));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL1_SELO_Msk;
    TmpReg |= (uint32_t)OutSource;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel positive output mode (output enable source).
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  Mode: @ref TIMER_CH_OUTP_Mode_TypeDef - specify the channel positive output mode (output enable source).
 * @return None.
 */
void TIMER_CH_OUTP_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Mode_TypeDef Mode)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTP_MODE(Mode));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL1_SELOE_Msk;
    TmpReg |= (uint32_t)Mode;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel positive output polarity.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  Polarity: @ref TIMER_CH_OUTP_Polarity_TypeDef - enable or disable the channel positive output inversion.
 * @return None.
 */
void TIMER_CH_OUTP_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Polarity_TypeDef Polarity)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTP_POLARITY(Polarity));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL1_INV;
    TmpReg |= (uint32_t)Polarity;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel negative output.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  OutSource: @ref TIMER_CH_OUTN_Source_TypeDef - specify the channel negative output source.
 * @param  Mode: @ref TIMER_CH_OUTN_Mode_TypeDef - specify the channel negative output mode (output enable source).
 * @param  Polarity: @ref TIMER_CH_OUTN_Polarity_TypeDef - enable or disable the channel negative output inversion.
 * @return None.
 */
void TIMER_CH_OUTN_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Source_TypeDef OutSource, TIMER_CH_OUTN_Mode_TypeDef Mode, TIMER_CH_OUTN_Polarity_TypeDef Polarity)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTN_SOURCE(OutSource));
    assert_param(IS_TIMER_CH_OUTN_MODE(Mode));
    assert_param(IS_TIMER_CH_OUTN_POLARITY(Polarity));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~(TIMER_CH_CNTRL1_NINV | TIMER_CH_CNTRL1_NSELO_Msk | TIMER_CH_CNTRL1_NSELOE_Msk);
    TmpReg |= (uint32_t)Polarity |
              (uint32_t)OutSource |
              (uint32_t)Mode;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel negative output source.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  OutSource: @ref TIMER_CH_OUTN_Source_TypeDef - specify the channel negative output source.
 * @return None.
 */
void TIMER_CH_OUTN_SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Source_TypeDef OutSource)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTN_SOURCE(OutSource));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL1_NSELO_Msk;
    TmpReg |= (uint32_t)OutSource;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel negative output mode (output enable source).
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  Mode: @ref TIMER_CH_OUTN_Mode_TypeDef - specify the channel negative output mode (output enable source).
 * @return None.
 */
void TIMER_CH_OUTN_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Mode_TypeDef Mode)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTN_MODE(Mode));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL1_NSELOE_Msk;
    TmpReg |= (uint32_t)Mode;
    *PtrReg = TmpReg;
}

/**
 * @brief  Configure the TIMERx channel negative output polarity.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify a channel number.
 * @param  Polarity: @ref TIMER_CH_OUTN_Polarity_TypeDef - enable or disable the channel negative output inversion.
 * @return None.
 */
void TIMER_CH_OUTN_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Polarity_TypeDef Polarity)
{
    __IO uint32_t* PtrReg;
    uint32_t       TmpReg;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CH_NUMBER(Channel));
    assert_param(IS_TIMER_CH_OUTN_POLARITY(Polarity));

    PtrReg = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpReg = *PtrReg;
    TmpReg &= ~TIMER_CH_CNTRL1_NINV;
    TmpReg |= (uint32_t)Polarity;
    *PtrReg = TmpReg;
}

/**
 * @brief  Check whether the specified TIMERx status flag is set or not.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Flag: @ref TIMER_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - the current status flag state (SET or RESET).
 */
FlagStatus TIMER_GetFlagStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAG(Flag));

    if ((TIMERx->STATUS & (uint32_t)Flag) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Return a combined value of the TIMERx status flags.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @return A combined value of the status flags (@ref TIMER_Flags_TypeDef).
 */
uint32_t TIMER_GetStatus(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return (TIMERx->STATUS);
}

/**
 * @brief  Clear the TIMERx status flags.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  Flags: Specify the flags to clear.
 *         This parameter can be any combination of the @ref TIMER_Flags_TypeDef values.
 * @return None.
 */
void TIMER_ClearFlags(MDR_TIMER_TypeDef* TIMERx, uint32_t Flags)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAGS(Flags));

    TIMERx->STATUS = ~Flags;
}

/**
 * @brief  Enable or disable the TIMERx interrupts.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  ITs: Specify the interrupt sources to be enabled or disabled.
 *         This parameter can be any combination of the @ref TIMER_Flags_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the interrupts.
 * @return None.
 */
void TIMER_ITConfig(MDR_TIMER_TypeDef* TIMERx, uint32_t ITs, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAGS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the TIMERx interrupt requests by setting bits in the IE register. */
        TIMERx->IE |= ITs;
    } else {
        /* Disable the TIMERx interrupt requests by clearing bits in the IE register. */
        TIMERx->IE &= ~ITs;
    }
}

/**
 * @brief  Enable or disable the TIMERx DMA requests.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  DMAReqs: Specify the DMA request sources.
 *         This parameter can be any combination of the @ref TIMER_Flags_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the DMA request sources.
 * @return None.
 */
void TIMER_DMACmd(MDR_TIMER_TypeDef* TIMERx, uint32_t DMAReqs, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAGS(DMAReqs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the TIMERx DMA requests by setting bits in the DMA_RE register. */
        TIMERx->DMA_RE |= DMAReqs;
    } else {
        /* Disable the TIMERx DMA requests by clearing bits in the DMA_RE register. */
        TIMERx->DMA_RE &= ~DMAReqs;
    }
}

/**
 * @brief  Get the TIMERx DMA requests work state.
 * @param  TIMERx: Select a TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in the range [1; 4].
 * @param  DMAReqs: @ref TIMER_Flags_TypeDef - specify a DMA request.
 * @return @ref FunctionalState - the current work state of the DMA request sources.
 */
FunctionalState TIMER_GetDMACmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_Flags_TypeDef DMAReq)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAG(DMAReq));

    if ((TIMERx->DMA_RE & (uint32_t)DMAReq) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/** @} */ /* End of the group TIMER_Exported_Functions */

/** @} */ /* End of the group TIMER */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_timer.c */

