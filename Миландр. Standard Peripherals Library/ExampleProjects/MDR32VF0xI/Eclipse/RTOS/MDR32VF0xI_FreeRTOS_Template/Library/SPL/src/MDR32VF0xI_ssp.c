/**
 *******************************************************************************
 * @file    MDR32VF0xI_ssp.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/01/2025
 * @brief   This file contains all the SSP firmware functions.
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
#include "MDR32VF0xI_ssp.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup SSP SSP
 * @{
 */

/** @defgroup SSP_Private_Defines SSP Private Defines
 * @{
 */
#define IS_SSP_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_SSP1) || \
                                   ((PERIPH) == MDR_SSP2) || \
                                   ((PERIPH) == MDR_SSP3))

#define SSP_FLAG_MASK (SSP_SR_TFE | SSP_SR_TNF | SSP_SR_RNE | SSP_SR_RFF | SSP_SR_BSY)

#if defined(USE_MDR32F02_REV_1X)
#define SSP_IT_MASK (SSP_IMSC_RORIM | SSP_IMSC_RTIM | SSP_IMSC_RXIM | SSP_IMSC_TXIM)

#else
#define SSP_IT_MASK (SSP_IMSC_RORIM | SSP_IMSC_RTIM | SSP_IMSC_RXIM | SSP_IMSC_TXIM | \
                     SSP_IMSC_RNEIM | SSP_IMSC_TFEIM | SSP_IMSC_TNBSYIM)
#endif

#define SSP_IT_CLR_MASK (SSP_ICR_RORIC | SSP_ICR_RTIC)

/** @} */ /* End of the group SSP_Private_Defines */

/** @addtogroup SSP_Exported_Functions SSP Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the SSPx peripheral registers to their default reset values.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @return None.
 */
void SSP_DeInit(MDR_SSP_TypeDef* SSPx)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    SSPx->CR1   = 0;
    SSPx->CR0   = 0;
    SSPx->CPSR  = 0;
    SSPx->IMSC  = 0;
    SSPx->DMACR = 0;
    /* Clear SSPRORINTR and SSPRTINTR interrupts. */
    SSPx->ICR = SSP_IT_CLR_MASK;
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    /* Activating transmitter FIFO reset. */
    SSPx->CR1 = SSP_CR1_RESTXFIFO;
    while ((SSPx->CR1 & SSP_CR1_RESTXFIFO) != 0) { }
#endif
}

/**
 * @brief  Initialize the SSPx peripheral according to
 *         the specified parameters in the SSP_InitStruct.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  SSP_InitStruct: The pointer to the @ref SSP_InitTypeDef structure that
 *         contains the configuration information for the specified SSPx peripheral.
 * @return None.
 */
void SSP_Init(MDR_SSP_TypeDef* SSPx, const SSP_InitTypeDef* SSP_InitStruct)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_SPEED_FACTOR(SSP_InitStruct->SSP_SCR));
    assert_param(IS_SSP_SPEED_DIVIDER(SSP_InitStruct->SSP_CPSDVSR));
    assert_param(IS_SSP_MODE(SSP_InitStruct->SSP_Mode));
    assert_param(IS_SSP_WORD_LENGTH(SSP_InitStruct->SSP_WordLength));
    assert_param(IS_SSP_CLOCK_PHASE(SSP_InitStruct->SSP_ClockPhase));
    assert_param(IS_SSP_CLOCK_POLARITY(SSP_InitStruct->SSP_ClockPolarity));
    assert_param(IS_SSP_FRAME_FORMAT(SSP_InitStruct->SSP_FrameFormat));
    assert_param(IS_FUNCTIONAL_STATE(SSP_InitStruct->SSP_SlaveModeOutput));
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    assert_param(IS_FUNCTIONAL_STATE(SSP_InitStruct->SSP_FastSPISlave));
#endif
    assert_param(IS_FUNCTIONAL_STATE(SSP_InitStruct->SSP_LoopbackMode));

    /* SSP CR1 configuration. */
    TmpReg = (uint32_t)SSP_InitStruct->SSP_LoopbackMode |
             (uint32_t)SSP_InitStruct->SSP_Mode |
             (((uint32_t)!SSP_InitStruct->SSP_SlaveModeOutput) << SSP_CR1_SOD_Pos);
    SSPx->CR1 = TmpReg;

    /* SSP CR0 configuration. */
    TmpReg = (uint32_t)SSP_InitStruct->SSP_WordLength |
             (uint32_t)SSP_InitStruct->SSP_FrameFormat |
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
             (((uint32_t)SSP_InitStruct->SSP_FastSPISlave) << SSP_CR0_SSPFRX_Pos) |
#endif
             (uint32_t)SSP_InitStruct->SSP_ClockPolarity |
             (uint32_t)SSP_InitStruct->SSP_ClockPhase |
             (((uint32_t)SSP_InitStruct->SSP_SCR) << SSP_CR0_SCR_Pos);
    SSPx->CR0 = TmpReg;

    /* SSP CPSR configuration. */
    SSPx->CPSR = SSP_InitStruct->SSP_CPSDVSR;
}

/**
 * @brief  Fill each SSP_InitStruct member with its default value.
 * @param  SSP_InitStruct: The pointer to the @ref SSP_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct)
{
    /* SSP_InitStruct members default value. */
    /* Initialize the SSP max speed. */
    SSP_InitStruct->SSP_SCR     = 0;
    SSP_InitStruct->SSP_CPSDVSR = 2;
    /* Initialize the SSP_Mode member. */
    SSP_InitStruct->SSP_Mode = SSP_MODE_MASTER;
    /* Initialize the SSP_WordLength member. */
    SSP_InitStruct->SSP_WordLength = SSP_WORD_LENGTH_8BIT;
    /* Initialize the SSP_ClockPhase member. */
    SSP_InitStruct->SSP_ClockPhase = SSP_CLOCK_PHASE_1EDGE;
    /* Initialize the SSP_ClockPolarity member. */
    SSP_InitStruct->SSP_ClockPolarity = SSP_CLOCK_POLARITY_LOW;
    /* Initialize the SSP_FrameFormat member. */
    SSP_InitStruct->SSP_FrameFormat = SSP_FRAME_FORMAT_SPI;
    /* Initialize the SSP_SlaveModeOutput member. */
    SSP_InitStruct->SSP_SlaveModeOutput = ENABLE;
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    /* Initialize the SSP_FastSPISlave member. */
    SSP_InitStruct->SSP_FastSPISlave = DISABLE;
#endif
    /* Initialize the SSP_LoopbackMode member. */
    SSP_InitStruct->SSP_LoopbackMode = DISABLE;
}

/**
 * @brief  Enable or disable the SSPx peripheral.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  NewState: @ref FunctionalState - a new state of the SSPx peripheral.
 * @return None.
 */
void SSP_Cmd(MDR_SSP_TypeDef* SSPx, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value. */
    if (NewState != DISABLE) {
        SSPx->CR1 |= SSP_CR1_SSE;
    } else {
        SSPx->CR1 &= ~SSP_CR1_SSE;
    }
}

/**
 * @brief  Get a specified SSPx peripheral work state.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @return @ref FunctionalState - the current work state of a specified SSPx peripheral.
 */
FunctionalState SSP_GetCmdState(MDR_SSP_TypeDef* SSPx)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    if ((SSPx->CR1 & SSP_CR1_SSE) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Transmit single data via the SSPx peripheral.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  Data: The data to transmit.
 * @return None.
 */
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void SSP_SendData(MDR_SSP_TypeDef* SSPx, uint32_t Data)
#else
void SSP_SendData(MDR_SSP_TypeDef* SSPx, uint16_t Data)
#endif
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    /* Transmit the data. */
    SSPx->DR = Data;
}

/**
 * @brief  Return the most recently received data by the SSPx peripheral.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @return The received data.
 */
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
uint32_t SSP_ReceiveData(MDR_SSP_TypeDef* SSPx)
#else
uint16_t SSP_ReceiveData(MDR_SSP_TypeDef* SSPx)
#endif
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    /* Receive the data. */
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    return SSPx->DR;
#else
    return (uint16_t)SSPx->DR;
#endif
}

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief  Clear the transmitter FIFO.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @return None.
 */
void SSP_TransmitterFIFOClear(MDR_SSP_TypeDef* SSPx)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    SSPx->CR1 |= SSP_CR1_RESTXFIFO;
}
#endif

/**
 * @brief  Enable or disable the SSP_TXD output in the slave mode.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  NewState: @ref FunctionalState - a new state of the SSP_TXD output.
 * @return None.
 */
void SSP_SlaveOutputConfig(MDR_SSP_TypeDef* SSPx, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form a new value. */
    if (NewState != DISABLE) {
        SSPx->CR1 &= ~SSP_CR1_SOD;
    } else {
        SSPx->CR1 |= SSP_CR1_SOD;
    }
}

/**
 * @brief  Check whether a specified SSPx status flag is set or not.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  Flag: Specify a flag to check.
 *         This parameter can be one of the @ref SSP_Flags_TypeDef values.
 * @return @ref FlagStatus - the current state of a status flag (SET or RESET).
 */
FlagStatus SSP_GetFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_FLAG(Flag));

    if ((SSPx->SR & (uint32_t)Flag) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Return a combined value of the SSPx status flags.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @return The SSPx status flags combined value.
 */
uint32_t SSP_GetStatus(MDR_SSP_TypeDef* SSPx)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    return SSPx->SR & SSP_FLAG_MASK;
}

/**
 * @brief  Enable or disable the SSPx interrupts.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  ITs: Specify the SSPx interrupt sources to enable or disable.
 *         This parameter can be any combination of the @ref SSP_IT_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the SSPx interrupts.
 * @return None.
 */
void SSP_ITConfig(MDR_SSP_TypeDef* SSPx, uint32_t ITs, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_CONFIG_ITS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form a new value. */
    if (NewState != DISABLE) {
        SSPx->IMSC |= ITs;
    } else {
        SSPx->IMSC &= ~ITs;
    }
}

/**
 * @brief  Check whether a specified SSPx masked interrupt has occurred or not.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  IT: Specify an SSPx interrupt source to check.
 *         This parameter can be one of the @ref SSP_IT_TypeDef values.
 * @return @ref ITStatus - a state of IT (SET or RESET).
 */
ITStatus SSP_GetITFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_IT_TypeDef IT)
{
    ITStatus Status;

    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_CONFIG_IT(IT));

    if ((SSPx->MIS & (uint32_t)IT) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Check whether the SSPx masked interrupts have occurred or not.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @return A combined state of the currently active interrupt flags.
 *         Return a combined value of @ref SSP_IT_TypeDef.
 */
uint32_t SSP_GetITStatus(MDR_SSP_TypeDef* SSPx)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    return SSPx->MIS & SSP_IT_MASK;
}

/**
 * @brief  Check whether a specified SSPx interrupt (non masked) has occurred or not.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  IT: Specify an SSPx interrupt source to check.
 *         This parameter can be one of the @ref SSP_IT_TypeDef values.
 * @return @ref ITStatus - a state of IT (SET or RESET).
 */
ITStatus SSP_GetITNonMaskedFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_IT_TypeDef IT)
{
    ITStatus Status;

    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_CONFIG_IT(IT));

    if ((SSPx->RIS & (uint32_t)IT) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Check whether the SSPx interrupts (non masked) have occurred or not.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @return A combined state of the currently active interrupt flags.
 *         Returns a combined value of @ref SSP_IT_TypeDef.
 */
uint32_t SSP_GetITNonMaskedStatus(MDR_SSP_TypeDef* SSPx)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));

    return SSPx->RIS & SSP_IT_MASK;
}

/**
 * @brief  Clear the SSPx interrupt requests.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  ITs: @ref SSP_IT_TypeDef - specify the interrupt requests to clear.
 *         This parameter can be any combination of the following values:
 *           @arg SSP_IT_ROR: Receive FIFO overrun interrupt.
 *           @arg SSP_IT_RT:  Receive timeout interrupt.
 * @return None.
 */
void SSP_ClearITFlags(MDR_SSP_TypeDef* SSPx, uint32_t ITs)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_RESET_ITS(ITs));

    SSPx->ICR = ITs;
}

/**
 * @brief  Enable or disable the SSPx DMA requests.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  DMAReqs: Specify a DMA request.
 *         This parameter can be any combination of the @ref SSP_DMA_Reqs_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the DMA request sources.
 * @return None.
 */
void SSP_DMACmd(MDR_SSP_TypeDef* SSPx, uint32_t DMAReqs, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_DMA_REQS(DMAReqs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the DMA transfer for selected requests in the SSP_DMACR register. */
        SSPx->DMACR |= DMAReqs;
    } else {
        /* Disable the DMA transfer for selected requests in the SSP_DMACR register. */
        SSPx->DMACR &= ~DMAReqs;
    }
}

/**
 * @brief  Get the SSPx DMA requests work state.
 * @param  SSPx: Select an SSP peripheral.
 *         This parameter can be one of the MDR_SSPx values, where x is a number in the range [1; 3].
 * @param  DMAReqs: @ref SSP_DMA_Reqs_TypeDef - specify a DMA request.
 * @return @ref FunctionalState - the current work state of the SSPx DMA requests.
 */
FunctionalState SSP_GetDMACmdState(MDR_SSP_TypeDef* SSPx, SSP_DMA_Reqs_TypeDef DMAReq)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_SSP_ALL_PERIPH(SSPx));
    assert_param(IS_SSP_DMA_REQ(DMAReq));

    if ((SSPx->DMACR & (uint32_t)DMAReq) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/** @} */ /* End of the group SSP_Exported_Functions */

/** @} */ /* End of the group SSP */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_ssp.c */

