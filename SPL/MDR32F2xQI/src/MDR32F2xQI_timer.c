/**
 *******************************************************************************
 * @file    MDR32F2xQI_timer.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    24/05/2023
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
#include "MDR32F2xQI_timer.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup TIMER TIMER
 * @{
 */

/** @defgroup TIMER_Private_Defines TIMER Private Defines
 * @{
 */

#define IS_TIMER_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_TIMER0) || \
                                     ((PERIPH) == MDR_TIMER1))

/** @} */ /* End of group TIMER_Private_Defines */

/** @addtogroup TIMER_Exported_Functions TIMER Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the TIMERx peripheral registers to their default reset values.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval None.
 */
void TIMER_DeInit(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->CNTRL = 0;
    TIMERx->CNT   = 0;
    TIMERx->PSG   = 0;
    TIMERx->ARR   = 0;

    TIMERx->CH1_CNTRL  = 0;
    TIMERx->CH1_CNTRL1 = 0;
    TIMERx->CH1_CNTRL2 = 0;
    TIMERx->CH1_DTG    = 0;

    TIMERx->CCR1  = 0;
    TIMERx->CCR11 = 0;

    TIMERx->BRKETR_CNTRL = 0;
    TIMERx->STATUS       = 0;
    TIMERx->IE           = 0;
#if defined(USE_MDR32F21QI)
    TIMERx->CH2_CNTRL  = 0;
    TIMERx->CH3_CNTRL  = 0;
    TIMERx->CH4_CNTRL  = 0;
    TIMERx->CH2_CNTRL1 = 0;
    TIMERx->CH3_CNTRL1 = 0;
    TIMERx->CH4_CNTRL1 = 0;
    TIMERx->CH2_CNTRL2 = 0;
    TIMERx->CH3_CNTRL2 = 0;
    TIMERx->CH4_CNTRL2 = 0;
    TIMERx->CH2_DTG    = 0;
    TIMERx->CH3_DTG    = 0;
    TIMERx->CH4_DTG    = 0;

    TIMERx->CCR2 = 0;
    TIMERx->CCR3 = 0;
    TIMERx->CCR4 = 0;

    TIMERx->CCR21 = 0;
    TIMERx->CCR31 = 0;
    TIMERx->CCR41 = 0;

    TIMERx->DMA_RE = 0;
#endif
}

/**
 * @brief  Initializes the TIMERx Counter peripheral according to
 *         the specified parameters in the TIMER_CntInitStruct.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  TIMER_CntInitStruct: pointer to a @ref TIMER_CNT_InitTypeDef structure
 *         that contains the configuration information for the specified TIMER Counter peripheral.
 * @retval None.
 */
void TIMER_CNT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CNT_InitTypeDef* TIMER_CntInitStruct)
{
    uint32_t TmpRegCNTRL;
    uint32_t TmpRegBRKETR_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_COUNTER_EVENT_SOURCE(TIMER_CntInitStruct->TIMER_CounterEventSource));
    assert_param(IS_TIMER_COUNTER_MODE(TIMER_CntInitStruct->TIMER_CounterMode));
    assert_param(IS_TIMER_COUNTER_DIR(TIMER_CntInitStruct->TIMER_CounterDirection));
    assert_param(IS_TIMER_FDTS_PRESCALER(TIMER_CntInitStruct->TIMER_FDTS_Prescaler));
    assert_param(IS_TIMER_ARR_UPDATE_MODE(TIMER_CntInitStruct->TIMER_ARR_UpdateMode));
    assert_param(IS_TIMER_ETR_FILTER(TIMER_CntInitStruct->TIMER_ETR_Filter));
    assert_param(IS_TIMER_ETR_PRESCALER(TIMER_CntInitStruct->TIMER_ETR_Prescaler));
    assert_param(IS_TIMER_ETR_POLARITY(TIMER_CntInitStruct->TIMER_ETR_Polarity));
    assert_param(IS_TIMER_BRK_POLARITY(TIMER_CntInitStruct->TIMER_BRK_Polarity));

    TIMERx->CNT = TIMER_CntInitStruct->TIMER_CounterValue;
    TIMERx->PSG = TIMER_CntInitStruct->TIMER_CounterPrescaler;
    TIMERx->ARR = TIMER_CntInitStruct->TIMER_CounterPeriod;

    /* Form new value for the CNTRL register */
    TmpRegCNTRL = (uint32_t)TIMER_CntInitStruct->TIMER_CounterEventSource |
                  (uint32_t)TIMER_CntInitStruct->TIMER_CounterMode |
                  (uint32_t)TIMER_CntInitStruct->TIMER_CounterDirection |
                  (uint32_t)TIMER_CntInitStruct->TIMER_FDTS_Prescaler |
                  (uint32_t)TIMER_CntInitStruct->TIMER_ARR_UpdateMode;

    /* Configure CNTRL register with new value */
    TIMERx->CNTRL = TmpRegCNTRL;

    /* Form new value for the BRKETR_CNTRL register */
    TmpRegBRKETR_CNTRL = (uint32_t)TIMER_CntInitStruct->TIMER_ETR_Filter |
                         (uint32_t)TIMER_CntInitStruct->TIMER_ETR_Prescaler |
                         (uint32_t)TIMER_CntInitStruct->TIMER_ETR_Polarity |
                         (uint32_t)TIMER_CntInitStruct->TIMER_BRK_Polarity;

    /* Configure BRKETR_CNTRL register with new value */
    TIMERx->BRKETR_CNTRL = TmpRegBRKETR_CNTRL;
}

/**
 * @brief  Fills each TIMER_CntInitStruct member with its default value.
 * @param  TIMER_CntInitStruct: pointer to a @ref TIMER_CNT_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
 */
void TIMER_CNT_StructInit(TIMER_CNT_InitTypeDef* TIMER_CntInitStruct)
{
    TIMER_CntInitStruct->TIMER_CounterValue       = 0;
    TIMER_CntInitStruct->TIMER_CounterPrescaler   = 0;
    TIMER_CntInitStruct->TIMER_CounterPeriod      = 0;
    TIMER_CntInitStruct->TIMER_CounterEventSource = TIMER_CNT_EVNT_SRC_TIM_CLK;
    TIMER_CntInitStruct->TIMER_CounterMode        = TIMER_CNT_MODE_CLK_FIXED_DIR;
    TIMER_CntInitStruct->TIMER_CounterDirection   = TIMER_CNT_DIR_UP;
    TIMER_CntInitStruct->TIMER_FDTS_Prescaler     = TIMER_FDTS_PRESCALER_DIV_1;
    TIMER_CntInitStruct->TIMER_ARR_UpdateMode     = TIMER_ARR_UPD_IMMEDIATELY;
    TIMER_CntInitStruct->TIMER_ETR_Filter         = TIMER_ETR_FILTER_1FF_AT_FDTS;
    TIMER_CntInitStruct->TIMER_ETR_Prescaler      = TIMER_ETR_PRESCALER_DIV_1;
    TIMER_CntInitStruct->TIMER_ETR_Polarity       = TIMER_ETR_POLARITY_NON_INV;
    TIMER_CntInitStruct->TIMER_BRK_Polarity       = TIMER_BRK_POLARITY_NON_INV;
}

/**
 * @brief  Enables or disables the specified TIMERx Counter peripheral.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  NewState - @ref FunctionalState - new state of the TIMER Counter peripheral.
 * @retval None.
 */
void TIMER_CNT_Cmd(MDR_TIMER_TypeDef* TIMERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable TIMERx Counter by setting the CNT_EN bit in the CNTRL register */
        TIMERx->CNTRL |= TIMER_CNTRL_CNT_EN;
    } else {
        /* Disable TIMERx Counter by clearing the CNT_EN bit in the CNTRL register */
        TIMERx->CNTRL &= ~TIMER_CNTRL_CNT_EN;
    }
}

/**
 * @brief  Sets the TIMERx Counter Register value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Counter: specifies the Counter register new value.
 * @retval None.
 */
void TIMER_CNT_SetCounter(MDR_TIMER_TypeDef* TIMERx, uint16_t Counter)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->CNT = Counter;
}

/**
 * @brief  Returns the TIMERx Counter Register value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval Counter Register value.
 */
uint16_t TIMER_CNT_GetCounter(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return (uint16_t)TIMERx->CNT;
}

/**
 * @brief  Sets the TIMERx TIM_CLK Prescaler Register value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Prescaler: specifies the TIM_CLK Prescaler Register value.
 * @retval None.
 */
void TIMER_CNT_SetPrescaler(MDR_TIMER_TypeDef* TIMERx, uint16_t Prescaler)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->PSG = Prescaler;
}

/**
 * @brief  Returns the TIMERx TIM_CLK Prescaler Register value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval TIM_CLK Prescaler Register value.
 */
uint16_t TIMER_CNT_GetPrescaler(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return (uint16_t)TIMERx->PSG;
}

/**
 * @brief  Sets the TIMERx Autoreload Register (ARR) Update mode.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  UpdateMode - @ref TIMER_ARR_UpdateMode_TypeDef - specifies the Autoreload Register Update mode.
 * @retval None.
 */
void TIMER_CNT_SetAutoreloadUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_ARR_UpdateMode_TypeDef UpdateMode)
{
    uint32_t TmpRegCNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ARR_UPDATE_MODE(UpdateMode));

    TmpRegCNTRL = TIMERx->CNTRL;
    TmpRegCNTRL &= ~TIMER_CNTRL_ARRB_EN_Msk;
    TmpRegCNTRL |= (uint32_t)UpdateMode;
    TIMERx->CNTRL = TmpRegCNTRL;
}

/**
 * @brief  Sets the TIMERx Autoreload Register value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Autoreload: specifies the Autoreload Register value.
 * @retval None.
 */
void TIMER_CNT_SetAutoreload(MDR_TIMER_TypeDef* TIMERx, uint16_t Autoreload)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->ARR = Autoreload;
}

/**
 * @brief  Returns the TIMERx Autoreload Register value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval Autoreload Register value.
 */
uint16_t TIMER_CNT_GetAutoreload(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return (uint16_t)TIMERx->ARR;
}

/**
 * @brief  Configures the TIMERx FDTS Prescaler.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Prescaler - @ref TIMER_FDTS_Prescaler_TypeDef - specifies the FDTS Prescaler.
 * @retval None.
 */
void TIMER_FDTS_SetPrescaler(MDR_TIMER_TypeDef* TIMERx, TIMER_FDTS_Prescaler_TypeDef Prescaler)
{
    uint32_t TmpRegCNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FDTS_PRESCALER(Prescaler));

    TmpRegCNTRL = TIMERx->CNTRL;
    TmpRegCNTRL &= ~TIMER_CNTRL_FDTS_Msk;
    TmpRegCNTRL |= (uint32_t)Prescaler;

    TIMERx->CNTRL = TmpRegCNTRL;
}

/**
 * @brief  Configures the TIMERx Counter Event source.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  CounterEventSource - @ref TIMER_CNT_EventSource_TypeDef - specifies the Event source.
 * @retval None.
 */
void TIMER_CNT_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_EventSource_TypeDef CounterEventSource)
{
    uint32_t TmpRegCNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_COUNTER_EVENT_SOURCE(CounterEventSource));

    TmpRegCNTRL = TIMERx->CNTRL;
    TmpRegCNTRL &= ~TIMER_CNTRL_EVENT_SEL_Msk;
    TmpRegCNTRL |= (uint32_t)CounterEventSource;
    TIMERx->CNTRL = TmpRegCNTRL;
}

/**
 * @brief  Configures the TIMERx count mode.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Mode - @ref TIMER_CNT_Mode_TypeDef - specifies the TIMER count mode.
 * @retval None.
 */
void TIMER_CNT_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_Mode_TypeDef Mode)
{
    uint32_t TmpRegCNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_COUNTER_MODE(Mode));

    TmpRegCNTRL = TIMERx->CNTRL;
    TmpRegCNTRL &= ~TIMER_CNTRL_CNT_MODE_Msk;
    TmpRegCNTRL |= (uint32_t)Mode;
    TIMERx->CNTRL = TmpRegCNTRL;
}

/**
 * @brief  Configures the TIMERx Counter direction.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Direction - @ref TIMER_CNT_Dir_TypeDef - specifies the TIMER Counter direction.
 * @retval None.
 */
void TIMER_CNT_SetDirection(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_Dir_TypeDef Direction)
{
    uint32_t TmpRegCNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_COUNTER_DIR(Direction));

    TmpRegCNTRL = TIMERx->CNTRL;
    TmpRegCNTRL &= ~TIMER_CNTRL_DIR_Msk;
    TmpRegCNTRL |= (uint32_t)Direction;
    TIMERx->CNTRL = TmpRegCNTRL;
}

/**
 * @brief  Returns the TIMERx Counter direction.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval @ref TIMER_CNT_Dir_TypeDef - The current TIMER Counter direction.
 */
TIMER_CNT_Dir_TypeDef TIMER_CNT_GetDirection(MDR_TIMER_TypeDef* TIMERx)
{
    TIMER_CNT_Dir_TypeDef Status;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    if ((TIMERx->CNTRL & TIMER_CNTRL_DIR_Msk) == 0) {
        Status = TIMER_CNT_DIR_UP;
    } else {
        Status = TIMER_CNT_DIR_DOWN;
    }

    return Status;
}

/**
 * @brief  Checks whether the TIMERx CNT, PSG or ARR write operation is in progress or not.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval @ref FlagStatus - The WR_CMPL flag current state:
 *             @arg SET:   Write to CNT, PSG or ARR registers in progress.
 *             @arg RESET: Write to CNT, PSG or ARR registers completed.
 */
FlagStatus TIMER_CNT_GetWriteStatus(MDR_TIMER_TypeDef* TIMERx)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    if ((TIMERx->CNTRL & TIMER_CNTRL_WR_CMPL_Msk) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Configures the TIMERx ETR input.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Prescaler - @ref TIMER_ETR_Prescaler_TypeDef - specifies the ETR signal prescaler value.
 * @param  Polarity - @ref TIMER_ETR_Polarity_TypeDef - enables or disables inversion on ETR input.
 * @param  Filter - @ref TIMER_ETR_Filter_TypeDef - specifies the ETR Filter configuration.
 * @retval None.
 */
void TIMER_ETR_InputConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler, TIMER_ETR_Polarity_TypeDef Polarity, TIMER_ETR_Filter_TypeDef Filter)
{
    uint32_t TmpRegBRKETR_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_PRESCALER(Prescaler));
    assert_param(IS_TIMER_ETR_POLARITY(Polarity));
    assert_param(IS_TIMER_ETR_FILTER(Filter));

    TmpRegBRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    TmpRegBRKETR_CNTRL &= ~(TIMER_BRKETR_CNTRL_ETR_FILTER_Msk | TIMER_BRKETR_CNTRL_ETR_PSC_Msk | TIMER_BRKETR_CNTRL_ETR_INV_Msk);
    TmpRegBRKETR_CNTRL |= (uint32_t)Prescaler |
                          (uint32_t)Polarity |
                          (uint32_t)Filter;
    TIMERx->BRKETR_CNTRL = TmpRegBRKETR_CNTRL;
}

/**
 * @brief  Configures the TIMERx ETR Filter peripheral.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Filter - @ref TIMER_ETR_Filter_TypeDef - specifies the ETR Filter configuration.
 * @retval None.
 */
void TIMER_ETR_FilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Filter_TypeDef Filter)
{
    uint32_t TmpRegBRKETR_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_FILTER(Filter));

    TmpRegBRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    TmpRegBRKETR_CNTRL &= ~TIMER_BRKETR_CNTRL_ETR_FILTER_Msk;
    TmpRegBRKETR_CNTRL |= (uint32_t)Filter;
    TIMERx->BRKETR_CNTRL = TmpRegBRKETR_CNTRL;
}

/**
 * @brief  Configures the TIMERx ETR signal prescaler value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Prescaler - @ref TIMER_ETR_Prescaler_TypeDef - specifies the ETR signal prescaler value.
 * @retval None.
 */
void TIMER_ETR_PrescalerConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler)
{
    uint32_t TmpRegBRKETR_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_PRESCALER(Prescaler));

    TmpRegBRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    TmpRegBRKETR_CNTRL &= ~TIMER_BRKETR_CNTRL_ETR_PSC_Msk;
    TmpRegBRKETR_CNTRL |= (uint32_t)Prescaler;
    TIMERx->BRKETR_CNTRL = TmpRegBRKETR_CNTRL;
}

/**
 * @brief  Configures the TIMERx ETR input inversion.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Polarity - @ref TIMER_ETR_Polarity_TypeDef - enables or disables inversion on ETR input.
 * @retval None.
 */
void TIMER_ETR_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Polarity_TypeDef Polarity)
{
    uint32_t TmpRegBRKETR_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_POLARITY(Polarity));

    TmpRegBRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    TmpRegBRKETR_CNTRL &= ~TIMER_BRKETR_CNTRL_ETR_INV_Msk;
    TmpRegBRKETR_CNTRL |= (uint32_t)Polarity;
    TIMERx->BRKETR_CNTRL = TmpRegBRKETR_CNTRL;
}

/**
 * @brief  Configures the TIMERx BRK input inversion.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Polarity - @ref TIMER_BRK_Polarity_TypeDef - enables or disables inversion on BRK input.
 * @retval None.
 */
void TIMER_BRK_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_BRK_Polarity_TypeDef Polarity)
{
    uint32_t TmpRegBRKETR_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_ETR_POLARITY(Polarity));

    TmpRegBRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    TmpRegBRKETR_CNTRL &= ~TIMER_BRKETR_CNTRL_BRK_INV_Msk;
    TmpRegBRKETR_CNTRL |= (uint32_t)Polarity;
    TIMERx->BRKETR_CNTRL = TmpRegBRKETR_CNTRL;
}

/**
 * @brief  Initializes the TIMERx Channel peripheral according to
 *         the specified parameters in the TIMER_ChInitStruct.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  TIMER_ChInitStruct: pointer to a @ref TIMER_CH_InitTypeDef structure
 *         that contains the configuration information for the specified
 *         TIMER Channel peripheral.
 * @retval None.
 */
void TIMER_CH_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_InitTypeDef* TIMER_ChInitStruct)
{
    uint32_t TmpRegCH_Number;
    uint32_t TmpRegCH_CNTRL;
    uint32_t TmpRegCH_CNTRL2;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(TIMER_ChInitStruct->TIMER_CH_Number));
    assert_param(IS_TIMER_CHANNEL_MODE(TIMER_ChInitStruct->TIMER_CH_Mode));
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_CCR1_Cmd));
    assert_param(IS_TIMER_CHANNEL_PWM_REF_FORMAT(TIMER_ChInitStruct->TIMER_CH_PWM_REF_Format));
    assert_param(IS_TIMER_CHANNEL_PWM_CCR_UPDATE_MODE(TIMER_ChInitStruct->TIMER_CH_PWM_CCR_UpdateMode));
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_PWM_ETR_Reset));
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_PWM_BRK_Reset));
    assert_param(IS_TIMER_CHANNEL_CAP_CCR_EVENT_SOURCE(TIMER_ChInitStruct->TIMER_CH_CAP_CCR_EventSource));
    assert_param(IS_TIMER_CHANNEL_CAP_CCR1_EVENT_SOURCE(TIMER_ChInitStruct->TIMER_CH_CAP_CCR1_EventSource));
    assert_param(IS_TIMER_CHANNEL_CAP_EVENT_PRESCALER(TIMER_ChInitStruct->TIMER_CH_CAP_EventPrescaler));
#if (defined USE_MDR32F23QI)
    assert_param(IS_FUNCTIONAL_STATE(TIMER_ChInitStruct->TIMER_CH_CAP_EventDelay));
#endif
    assert_param(IS_TIMER_CHANNEL_FILTER(TIMER_ChInitStruct->TIMER_CH_Filter));

    TmpRegCH_Number = (uint32_t)TIMER_ChInitStruct->TIMER_CH_Number;

    TmpRegCH_CNTRL = (uint32_t)TIMER_ChInitStruct->TIMER_CH_Mode |
                     (uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_REF_Format |
                     (uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_EventPrescaler |
                     (uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_CCR_EventSource |
                     (uint32_t)TIMER_ChInitStruct->TIMER_CH_Filter;

    if (TIMER_ChInitStruct->TIMER_CH_PWM_ETR_Reset != DISABLE) {
        TmpRegCH_CNTRL |= TIMER_CH_CNTRL_ETREN_Msk | TIMER_CH_CNTRL_OCCE_Msk;
    }

    if (TIMER_ChInitStruct->TIMER_CH_PWM_BRK_Reset != DISABLE) {
        TmpRegCH_CNTRL |= TIMER_CH_CNTRL_BRKEN_Msk;
    }

    *(&TIMERx->CH1_CNTRL + TmpRegCH_Number) = TmpRegCH_CNTRL;

    TmpRegCH_CNTRL2 = (uint32_t)TIMER_ChInitStruct->TIMER_CH_PWM_CCR_UpdateMode |
                      (uint32_t)TIMER_ChInitStruct->TIMER_CH_CAP_CCR1_EventSource;

    if (TIMER_ChInitStruct->TIMER_CH_CCR1_Cmd != DISABLE) {
        TmpRegCH_CNTRL2 |= TIMER_CH_CNTRL2_CCR1_EN_Msk;
    }
#if (defined USE_MDR32F23QI)
    if (TIMER_ChInitStruct->TIMER_CH_CAP_EventDelay != DISABLE) {
        TmpRegCH_CNTRL2 |= TIMER_CH_CNTRL2_EV_DELAY_Msk;
    }
#endif
    *(&TIMERx->CH1_CNTRL2 + TmpRegCH_Number) = TmpRegCH_CNTRL2;
}

/**
 * @brief  Fills each TIMER_ChInitStruct member with its default value.
 * @param  TIMER_ChInitStruct: pointer to a @ref TIMER_CH_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
 */
void TIMER_CH_StructInit(TIMER_CH_InitTypeDef* TIMER_ChInitStruct)
{
    TIMER_ChInitStruct->TIMER_CH_Number   = TIMER_CH1;
    TIMER_ChInitStruct->TIMER_CH_Mode     = TIMER_CH_MODE_PWM;
    TIMER_ChInitStruct->TIMER_CH_CCR1_Cmd = DISABLE;

    TIMER_ChInitStruct->TIMER_CH_PWM_REF_Format     = TIMER_CH_PWM_REF_FORMAT_0;
    TIMER_ChInitStruct->TIMER_CH_PWM_CCR_UpdateMode = TIMER_CH_PWM_CCR_UPD_IMMEDIATELY;
    TIMER_ChInitStruct->TIMER_CH_PWM_ETR_Reset      = DISABLE;
    TIMER_ChInitStruct->TIMER_CH_PWM_BRK_Reset      = DISABLE;

    TIMER_ChInitStruct->TIMER_CH_CAP_CCR_EventSource  = TIMER_CH_CAP_CCR_EVNT_SRC_RE;
    TIMER_ChInitStruct->TIMER_CH_CAP_CCR1_EventSource = TIMER_CH_CAP_CCR1_EVNT_SRC_RE;
    TIMER_ChInitStruct->TIMER_CH_CAP_EventPrescaler   = TIMER_CH_CAP_EVNT_PRESCALER_DIV_1;
#if defined(USE_MDR32F23QI)
    TIMER_ChInitStruct->TIMER_CH_CAP_EventDelay = ENABLE;
#endif
    TIMER_ChInitStruct->TIMER_CH_Filter = TIMER_CH_FILTER_1FF_AT_FDTS;
}

/**
 * @brief  Sets the TIMERx Channel Capture Compare Register (CCR) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  CCR: specifies the Capture Compare Register (CCR) new value.
 * @retval None.
 */
void TIMER_CH_SetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint16_t CCR)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));

    *(&TIMERx->CCR1 + (uint32_t)Channel) = CCR;
}

/**
 * @brief  Returns the TIMERx Channel Capture Compare Register (CCR) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @retval Channel Capture Compare Register (CCR) value.
 */
uint16_t TIMER_CH_GetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));

    return (uint16_t) * (&TIMERx->CCR1 + (uint32_t)Channel);
}

/**
 * @brief  Checks whether the TIMERx CCR write operation is in progress or not.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @retval @ref FlagStatus - The CHy_CNTRL.WR_CMPL flag current state:
 *             @arg SET:   Write to CCR register in progress.
 *             @arg RESET: Write to CCR register completed.
 */
FlagStatus TIMER_CH_GetCCRWriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    __IO uint32_t* TmpPtrCH_CNTRL;
    FlagStatus     Status;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    if ((*TmpPtrCH_CNTRL & TIMER_CH_CNTRL_WR_CMPL) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Enables or disables the TIMERx Channel CCR1 register.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  NewState - @ref FunctionalState - new state of the CCR1_EN bit.
 * @retval None.
 */
void TIMER_CH_CCR1Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* TmpPtrCH_CNTRL2;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TmpPtrCH_CNTRL2 = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the TIMERx Channel CCR1 register by setting the CCR1_EN bit in the CHy_CNTRL2 register */
        *TmpPtrCH_CNTRL2 |= TIMER_CH_CNTRL2_CCR1_EN_Msk;
    } else {
        /* Disable the TIMERx Channel CCR1 register by clearing the CCR1_EN bit in the CHy_CNTRL2 register */
        *TmpPtrCH_CNTRL2 &= ~TIMER_CH_CNTRL2_CCR1_EN_Msk;
    }
}

/**
 * @brief  Sets the TIMERx Channel Capture Compare Register 1 (CCR1) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  CCR1: specifies the Capture Compare Register 1 (CCR1) new value.
 * @retval None.
 */
void TIMER_CH_SetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint16_t CCR1)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));

    *(&TIMERx->CCR11 + (uint32_t)Channel) = CCR1;
}

/**
 * @brief  Returns the TIMERx Channel Capture Compare Register 1 (CCR1) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @retval Channel Capture Compare Register 1 (CCR1) value.
 */
uint16_t TIMER_CH_GetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));

    return (uint16_t) * (&TIMERx->CCR11 + (uint32_t)Channel);
}

/**
 * @brief  Checks whether the TIMERx CCR1 write operation is in progress or not.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @retval @ref FlagStatus - The CHy_CNTRL.WR_CMPL1 flag current state:
 *             @arg SET:   Write to CCR1 register in progress.
 *             @arg RESET: Write to CCR1 register completed.
 */
FlagStatus TIMER_CH_GetCCR1WriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel)
{
    __IO uint32_t* TmpPtrCH_CNTRL;
    FlagStatus     Status;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    if ((*TmpPtrCH_CNTRL & TIMER_CH_CNTRL_WR_CMPL1) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Sets the TIMERx Channel Capture Compare Registers (CCR and CCR1) update mode.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  UpdateMode - @ref TIMER_CH_PWM_CCR_UpdateMode_TypeDef - specifies the Capture Compare Registers (CCR and CCR1) update mode.
 * @retval None.
 */
void TIMER_CH_PWM_SetCompareUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_CCR_UpdateMode_TypeDef UpdateMode)
{
    __IO uint32_t* TmpPtrCH_CNTRL2;
    uint32_t       TmpRegCH_CNTRL2;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_PWM_CCR_UPDATE_MODE(UpdateMode));

    TmpPtrCH_CNTRL2 = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    TmpRegCH_CNTRL2 = *TmpPtrCH_CNTRL2;
    TmpRegCH_CNTRL2 &= ~TIMER_CH_CNTRL2_CCRRLD_Msk;
    TmpRegCH_CNTRL2 |= (uint32_t)UpdateMode;
    *TmpPtrCH_CNTRL2 = TmpRegCH_CNTRL2;
}

/**
 * @brief  Configures the TIMERx REF signal format.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Format - @ref TIMER_CH_PWM_REF_Format_TypeDef - new value of the REF signal format.
 * @retval None.
 */
void TIMER_CH_PWM_REF_FormatConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_REF_Format_TypeDef Format)
{
    __IO uint32_t* TmpPtrCH_CNTRL;
    uint32_t       TmpRegCH_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_PWM_REF_FORMAT(Format));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    TmpRegCH_CNTRL = *TmpPtrCH_CNTRL;
    TmpRegCH_CNTRL &= ~TIMER_CH_CNTRL_OCCM_Msk;
    TmpRegCH_CNTRL |= (uint32_t)Format;
    *TmpPtrCH_CNTRL = TmpRegCH_CNTRL;
}

/**
 * @brief  Enables or disables TIMERx Channel ETR Reset (REF reset when ETR input is high).
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  NewState - @ref FunctionalState - new state of the ETR Reset.
 * @retval None.
 */
void TIMER_CH_PWM_ETR_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* TmpPtrCH_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the TIMERx Channel ETR Reset by setting the ETREN and OCCE bits in the CHy_CNTRL register */
        *TmpPtrCH_CNTRL |= TIMER_CH_CNTRL_ETREN_Msk | TIMER_CH_CNTRL_OCCE_Msk;
    } else {
        /* Disable the TIMERx Channel ETR Reset by clearing the ETREN and OCCE bits in the CHy_CNTRL register */
        *TmpPtrCH_CNTRL &= ~(TIMER_CH_CNTRL_ETREN_Msk | TIMER_CH_CNTRL_OCCE_Msk);
    }
}

/**
 * @brief  Enables or disables TIMERx Channel BKR Reset (REF and DTG reset when BKR input is low).
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  NewState - @ref FunctionalState - new state of the BRK Reset.
 * @retval None.
 */
void TIMER_CH_PWM_BRK_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* TmpPtrCH_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the TIMERx Channel BRK Reset by setting the BRKEN bit in the CHy_CNTRL register */
        *TmpPtrCH_CNTRL |= TIMER_CH_CNTRL_BRKEN_Msk;
    } else {
        /* Disable the TIMERx Channel BRK Reset by clearing the BRKEN bit in the CHy_CNTRL register */
        *TmpPtrCH_CNTRL &= ~TIMER_CH_CNTRL_BRKEN_Msk;
    }
}

/**
 * @brief  Configures the TIMERx Capture events prescaler value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Prescaler - @ref TIMER_CH_CAP_EventPrescaler_TypeDef - specifies the Capture evens prescaler value.
 * @retval None.
 */
void TIMER_CH_CAP_SetEventPrescaler(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_EventPrescaler_TypeDef Prescaler)
{
    __IO uint32_t* TmpPtrCH_CNTRL;
    uint32_t       TmpRegCH_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_CAP_EVENT_PRESCALER(Prescaler));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    TmpRegCH_CNTRL = *TmpPtrCH_CNTRL;
    TmpRegCH_CNTRL &= ~TIMER_CH_CNTRL_CHPSC_Msk;
    TmpRegCH_CNTRL |= (uint32_t)Prescaler;
    *TmpPtrCH_CNTRL = TmpRegCH_CNTRL;
}

/**
 * @brief  Configures the TIMERx Channel Capture Event source for the CCR register.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  EventSource - @ref TIMER_CH_CAP_CCR_EventSource_TypeDef - specifies the Event source for the CCR register.
 * @retval None.
 */
void TIMER_CH_CAP_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR_EventSource_TypeDef EventSource)
{
    __IO uint32_t* TmpPtrCH_CNTRL;
    uint32_t       TmpRegCH_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_CAP_CCR_EVENT_SOURCE(EventSource));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    TmpRegCH_CNTRL = *TmpPtrCH_CNTRL;
    TmpRegCH_CNTRL &= ~TIMER_CH_CNTRL_CHSEL_Msk;
    TmpRegCH_CNTRL |= (uint32_t)EventSource;
    *TmpPtrCH_CNTRL = TmpRegCH_CNTRL;
}

/**
 * @brief  Configures the TIMERx Channel Capture Event source for the CCR1 register.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Event1Source - @ref TIMER_CH_CAP_CCR1_EventSource_TypeDef - specifies the Event source for the CCR1 register.
 * @retval None.
 */
void TIMER_CH_CAP_Event1SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR1_EventSource_TypeDef Event1Source)
{
    __IO uint32_t* TmpPtrCH_CNTRL2;
    uint32_t       TmpRegCH_CNTRL2;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_CAP_CCR1_EVENT_SOURCE(Event1Source));

    TmpPtrCH_CNTRL2 = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    TmpRegCH_CNTRL2 = *TmpPtrCH_CNTRL2;
    TmpRegCH_CNTRL2 &= ~TIMER_CH_CNTRL2_CHSEL_Msk;
    TmpRegCH_CNTRL2 |= (uint32_t)Event1Source;
    *TmpPtrCH_CNTRL2 = TmpRegCH_CNTRL2;
}

#if (defined USE_MDR32F23QI)
/**
 * @brief  Enables or disables synchronization between the capture event and the update of registers CCR and CCR1.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  NewState - @ref FunctionalState - new state of the EV_DELAY bit.
 * @retval None
 */
void TIMER_CH_CAP_EventDelayCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState)
{
    __IO uint32_t* TmpPtrCH_CNTRL2;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TmpPtrCH_CNTRL2 = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the TIMERx Channel event delay by setting the EV_DELAY bit in the CHy_CNTRL2 register */
        *TmpPtrCH_CNTRL2 |= TIMER_CH_CNTRL2_EV_DELAY_Msk;
    } else {
        /* Disable the TIMERx Channel event delay by clearing the EV_DELAY bit in the CHy_CNTRL2 register */
        *TmpPtrCH_CNTRL2 &= ~TIMER_CH_CNTRL2_EV_DELAY_Msk;
    }
}
#endif

/**
 * @brief  Configures the TIMERx Channel Filter peripheral.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Filter - @ref TIMER_CH_Filter_TypeDef - specifies the Channel Filter configuration.
 * @retval None.
 */
void TIMER_CH_FilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_Filter_TypeDef Filter)
{
    __IO uint32_t* TmpPtrCH_CNTRL;
    uint32_t       TmpRegCH_CNTRL;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_FILTER(Filter));

    TmpPtrCH_CNTRL = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    TmpRegCH_CNTRL = *TmpPtrCH_CNTRL;
    TmpRegCH_CNTRL &= ~TIMER_CH_CNTRL_CHFLTR_Msk;
    TmpRegCH_CNTRL |= (uint32_t)Filter;
    *TmpPtrCH_CNTRL = TmpRegCH_CNTRL;
}

/**
 * @brief  Initializes the TIMERx Channel Output peripheral according to
 *         the specified parameters in the TIMER_ChOutInitStruct.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  TIMER_ChOutInitStruct: pointer to a @ref TIMER_CH_OUT_InitTypeDef structure
 *         that contains the configuration information for the specified
 *         TIMER Channel Outputs peripheral.
 * @retval None.
 */
void TIMER_CH_OUT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_OUT_InitTypeDef* TIMER_ChOutInitStruct)
{
    uint32_t TmpRegCH_Number;
    uint32_t TmpRegCH_CNTRL1;
    uint32_t TmpRegCH_DTG;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(TIMER_ChOutInitStruct->TIMER_CH_Number));
    assert_param(IS_TIMER_CHANNEL_OUTP_POLARITY(TIMER_ChOutInitStruct->TIMER_CH_OUTP_Polarity));
    assert_param(IS_TIMER_CHANNEL_OUTP_SOURCE(TIMER_ChOutInitStruct->TIMER_CH_OUTP_Source));
    assert_param(IS_TIMER_CHANNEL_OUTP_MODE(TIMER_ChOutInitStruct->TIMER_CH_OUTP_Mode));
    assert_param(IS_TIMER_CHANNEL_OUTN_POLARITY(TIMER_ChOutInitStruct->TIMER_CH_OUTN_Polarity));
    assert_param(IS_TIMER_CHANNEL_OUTN_SOURCE(TIMER_ChOutInitStruct->TIMER_CH_OUTN_Source));
    assert_param(IS_TIMER_CHANNEL_OUTN_MODE(TIMER_ChOutInitStruct->TIMER_CH_OUTN_Mode));
    assert_param(IS_TIMER_CHANNEL_DTG_CLK_SOURCE(TIMER_ChOutInitStruct->TIMER_CH_DTG_ClockSource));
    assert_param(IS_TIMER_CHANNEL_DTG_AUX_PRESCALER(TIMER_ChOutInitStruct->TIMER_CH_DTG_AuxPrescaler));

    TmpRegCH_Number = (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_Number;

    TmpRegCH_CNTRL1 = (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTP_Polarity |
                      (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTP_Source |
                      (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTP_Mode |
                      (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTN_Polarity |
                      (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTN_Source |
                      (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_OUTN_Mode;

    *(&TIMERx->CH1_CNTRL1 + TmpRegCH_Number) = TmpRegCH_CNTRL1;

    TmpRegCH_DTG = ((uint32_t)TIMER_ChOutInitStruct->TIMER_CH_DTG_MainPrescaler << TIMER_CH_DTG_DTG_Pos) |
                   ((uint32_t)TIMER_ChOutInitStruct->TIMER_CH_DTG_AuxPrescaler << TIMER_CH_DTG_DTGX_Pos) |
                   (uint32_t)TIMER_ChOutInitStruct->TIMER_CH_DTG_ClockSource;

    *(&TIMERx->CH1_DTG + TmpRegCH_Number) = TmpRegCH_DTG;
}

/**
 * @brief  Fills each TIMER_ChOutInitStruct member with its default value.
 * @param  TIMER_ChOutInitStruct: pointer to a @ref TIMER_CH_OUT_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
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

    TIMER_ChOutInitStruct->TIMER_CH_DTG_ClockSource   = TIMER_CH_DTG_CLK_SRC_TIM_CLK;
    TIMER_ChOutInitStruct->TIMER_CH_DTG_MainPrescaler = 0;
    TIMER_ChOutInitStruct->TIMER_CH_DTG_AuxPrescaler  = 0;
}

/**
 * @brief  Configures the TIMERx Dead Time Generator (DTG) peripheral.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  MainPrescaler: specifies the Main Prescaler value.
 *         This parameter can be a number between 0x00 and 0xFF.
 * @param  AuxPrescaler: specifies the Auxiliary Prescaler value.
 *         This parameter can be a number between 0x00 and 0x0F.
 * @param  ClockSource - @ref TIMER_CH_DTG_ClockSource_TypeDef - specifies the DTG clock source.
 * @retval None.
 */
void TIMER_CH_OUT_DTGConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint8_t MainPrescaler, uint8_t AuxPrescaler, TIMER_CH_DTG_ClockSource_TypeDef ClockSource)
{
    uint32_t TmpRegCH_DTG;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_DTG_AUX_PRESCALER(AuxPrescaler));
    assert_param(IS_TIMER_CHANNEL_DTG_CLK_SOURCE(ClockSource));

    TmpRegCH_DTG = ((uint32_t)MainPrescaler << TIMER_CH_DTG_DTG_Pos) |
                   ((uint32_t)AuxPrescaler << TIMER_CH_DTG_DTGX_Pos) |
                   (uint32_t)ClockSource;

    *(&TIMERx->CH1_DTG + (uint32_t)Channel) = TmpRegCH_DTG;
}

/**
 * @brief  Configures the TIMERx Channel positive output.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  OutSource - @ref TIMER_CH_OUTP_Source_TypeDef - specifies the Channel Positive Output source.
 * @param  Mode - @ref TIMER_CH_OUTP_Mode_TypeDef - specifies the Channel Positive Output mode (output enable source).
 * @param  Polarity - @ref TIMER_CH_OUTP_Polarity_TypeDef - enables or disables the Channel Positive Output inversion.
 * @retval None.
 */
void TIMER_CH_OUTP_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Source_TypeDef OutSource, TIMER_CH_OUTP_Mode_TypeDef Mode, TIMER_CH_OUTP_Polarity_TypeDef Polarity)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTP_SOURCE(OutSource));
    assert_param(IS_TIMER_CHANNEL_OUTP_MODE(Mode));
    assert_param(IS_TIMER_CHANNEL_OUTP_POLARITY(Polarity));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~(TIMER_CH_CNTRL1_INV_Msk | TIMER_CH_CNTRL1_SELO_Msk | TIMER_CH_CNTRL1_SELOE_Msk);
    TmpRegCH_CNTRL1 |= (uint32_t)Polarity |
                       (uint32_t)OutSource |
                       (uint32_t)Mode;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Configures the TIMERx Channel Positive Output source.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  OutSource - @ref TIMER_CH_OUTP_Source_TypeDef - specifies the Channel Positive Output source.
 * @retval None.
 */
void TIMER_CH_OUTP_SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Source_TypeDef OutSource)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTP_SOURCE(OutSource));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~TIMER_CH_CNTRL1_SELO_Msk;
    TmpRegCH_CNTRL1 |= (uint32_t)OutSource;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Configures the TIMERx Channel Positive Output mode (enable source).
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Mode - @ref TIMER_CH_OUTP_Mode_TypeDef - specifies the Channel Positive Output mode (output enable source).
 * @retval None.
 */
void TIMER_CH_OUTP_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Mode_TypeDef Mode)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTP_MODE(Mode));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~TIMER_CH_CNTRL1_SELOE_Msk;
    TmpRegCH_CNTRL1 |= (uint32_t)Mode;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Configures the TIMERx Channel Positive Output polarity.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Polarity - @ref TIMER_CH_OUTP_Polarity_TypeDef - enables or disables the Channel Positive Output inversion.
 * @retval None
 */
void TIMER_CH_OUTP_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Polarity_TypeDef Polarity)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTP_POLARITY(Polarity));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~TIMER_CH_CNTRL1_INV_Msk;
    TmpRegCH_CNTRL1 |= (uint32_t)Polarity;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Configures the TIMERx Channel Negative Output.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  OutSource - @ref TIMER_CH_OUTN_Source_TypeDef - specifies the Channel Negative Output source.
 * @param  Mode - @ref TIMER_CH_OUTN_Mode_TypeDef - specifies the Channel Negative Output mode (output enable source).
 * @param  Polarity - @ref TIMER_CH_OUTN_Polarity_TypeDef - enables or disables the Channel Negative Output inversion.
 * @retval None.
 */
void TIMER_CH_OUTN_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Source_TypeDef OutSource, TIMER_CH_OUTN_Mode_TypeDef Mode, TIMER_CH_OUTN_Polarity_TypeDef Polarity)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTN_SOURCE(OutSource));
    assert_param(IS_TIMER_CHANNEL_OUTN_MODE(Mode));
    assert_param(IS_TIMER_CHANNEL_OUTN_POLARITY(Polarity));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~(TIMER_CH_CNTRL1_NINV_Msk | TIMER_CH_CNTRL1_NSELO_Msk | TIMER_CH_CNTRL1_NSELOE_Msk);
    TmpRegCH_CNTRL1 |= (uint32_t)Polarity |
                       (uint32_t)OutSource |
                       (uint32_t)Mode;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Configures the TIMERx Channel Negative Output source.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  OutSource - @ref TIMER_CH_OUTN_Source_TypeDef - specifies the Channel Negative Output source.
 * @retval None.
 */
void TIMER_CH_OUTN_SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Source_TypeDef OutSource)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTN_SOURCE(OutSource));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~TIMER_CH_CNTRL1_NSELO_Msk;
    TmpRegCH_CNTRL1 |= (uint32_t)OutSource;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Configures the TIMERx Channel Negative Output mode.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Mode - @ref TIMER_CH_OUTN_Mode_TypeDef - specifies the NChannel Negative Output mode (output enable source).
 * @retval None.
 */
void TIMER_CH_OUTN_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Mode_TypeDef Mode)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTN_MODE(Mode));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~TIMER_CH_CNTRL1_NSELOE_Msk;
    TmpRegCH_CNTRL1 |= (uint32_t)Mode;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Configures the TIMERx Channel Negative Output polarity.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Polarity - @ref TIMER_CH_OUTN_Polarity_TypeDef - enables or disables the Channel Negative Output inversion.
 * @retval None.
 */
void TIMER_CH_OUTN_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Polarity_TypeDef Polarity)
{
    __IO uint32_t* TmpPtrCH_CNTRL1;
    uint32_t       TmpRegCH_CNTRL1;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_CHANNEL_NUMBER(Channel));
    assert_param(IS_TIMER_CHANNEL_OUTN_POLARITY(Polarity));

    TmpPtrCH_CNTRL1 = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    TmpRegCH_CNTRL1 = *TmpPtrCH_CNTRL1;
    TmpRegCH_CNTRL1 &= ~TIMER_CH_CNTRL1_NINV_Msk;
    TmpRegCH_CNTRL1 |= (uint32_t)Polarity;
    *TmpPtrCH_CNTRL1 = TmpRegCH_CNTRL1;
}

/**
 * @brief  Checks whether the specified TIMERx Status flag is set or not.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Flag - @ref TIMER_Flags_TypeDef - specifies the flag to check.
 * @retval @ref FlagStatus - Current Status flag state (SET or RESET).
 */
FlagStatus TIMER_GetFlagStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAG(Flag));

    if (TIMERx->STATUS & (uint32_t)Flag) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Returns the TIMERx Status Register value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval The TIMER Status Flags combined value.
 */
uint32_t TIMER_GetStatus(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return (TIMERx->STATUS);
}

/**
 * @brief  Clears the TIMERx's Status Flags.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Flags: specifies the flags to clear.
 *         This parameter can be any combination of @ref TIMER_Flags_TypeDef values.
 * @retval None.
 */
void TIMER_ClearFlags(MDR_TIMER_TypeDef* TIMERx, uint32_t Flags)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAGS(Flags));

    TIMERx->STATUS = ~Flags;
}

/**
 * @brief  Enables or disables the TIMER interrupts.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  ITs: specifies the TIMER interrupts sources to be enabled or disabled.
 *         This parameter can be any combination of @ref TIMER_Flags_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the TIMER interrupts.
 * @retval None.
 */
void TIMER_ITConfig(MDR_TIMER_TypeDef* TIMERx, uint32_t ITs, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAGS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the TIMERx Interrupt requests by setting bits in the IE register */
        TIMERx->IE |= ITs;
    } else {
        /* Disable the TIMERx Interrupt requests by clearing bits in the IE register */
        TIMERx->IE &= ~ITs;
    }
}

/**
 * @brief  Checks whether the specified TIMERx interrupt has occurred or not.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  IT - @ref TIMER_Flags_TypeDef - specifies the TIMER interrupt source to check.
 * @retval @ref ITStatus - The state of the IT (SET or RESET).
 */
ITStatus TIMER_GetITFlagStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Flags_TypeDef IT)
{
    ITStatus Status;

    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAG(IT));

    if (TIMERx->STATUS & TIMERx->IE & (uint32_t)IT) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Checks whether the TIMERx masked interrupts has occurred or not.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref TIMER_Flags_TypeDef.
 */
uint32_t TIMER_GetITStatus(MDR_TIMER_TypeDef* TIMERx)
{
    /* Check the parameter */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return TIMERx->STATUS & TIMERx->IE;
}

#if defined(USE_MDR32F21QI)
/**
 * @brief  Enables or disables the TIMERx DMA Requests.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  DMAReqs - specifies the DMA Request sources.
 *         This parameter can be any combination of @ref TIMER_Flags_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the DMA Request sources.
 * @retval None.
 */
void TIMER_DMACmd(MDR_TIMER_TypeDef* TIMERx, uint32_t DMAReqs, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_FLAGS(DMAReqs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the TIMERx DMA Requests by setting bits in the DMA_RE register */
        TIMERx->DMA_RE |= DMAReqs;
    } else {
        /* Disable the TIMERx DMA Requests by clearing bits in the DMA_RE register */
        TIMERx->DMA_RE &= ~DMAReqs;
    }
}
#endif

/** @} */ /* End of group TIMER_Exported_Functions */

/** @} */ /* End of group TIMER */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_timer.c */

