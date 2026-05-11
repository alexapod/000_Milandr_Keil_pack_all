/**
 *******************************************************************************
 * @file    MDR32F2xQI_ssp.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    26/04/2023
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
#include "MDR32F2xQI_ssp.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup SSP SSP
 * @{
 */

/** @defgroup SSP_Private_Defines SSP Private Defines
 * @{
 */

#define SSP_FLAG_MASK (SSP_SR_TFE | SSP_SR_TNF | \
                       SSP_SR_RNE | SSP_SR_RFF | \
                       SSP_SR_BSY)

#define SSP_IT_MASK (SSP_IMSC_RORIM | SSP_IMSC_RTIM | \
                     SSP_IMSC_RXIM | SSP_IMSC_TXIM)

/** @} */ /* End of group SSP_Private_Defines */

/** @addtogroup SSP_Exported_Functions SSP Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the SSP peripheral registers to their default reset values.
 * @param  None.
 * @retval None.
 */
void SSP_DeInit(void)
{
    MDR_SSP->CR1  = 0;
    MDR_SSP->CR0  = 0;
    MDR_SSP->CPSR = 0;
    MDR_SSP->IMSC = 0;
#if defined(USE_MDR32F21QI)
    MDR_SSP->DMACR = 0;
#endif
    /* Clear interrupts SSPRORINTR and SSPRTINTR */
    MDR_SSP->ICR = SSP_ICR_RORIC_Msk | SSP_ICR_RTIC_Msk;
}

/**
 * @brief  Initializes the SSP peripheral according to
 *         the specified parameters in the SSP_InitStruct.
 * @param  SSP_InitStruct: pointer to a @ref SSP_InitTypeDef structure that
 *         contains the configuration information for the specified SSP peripheral.
 * @retval None.
 */
void SSP_Init(const SSP_InitTypeDef* SSP_InitStruct)
{
    uint32_t TmpReg;

    /* Check the parameters */
    assert_param(IS_SSP_SPEED_FACTOR(SSP_InitStruct->SSP_SCR));
    assert_param(IS_SSP_SPEED_DIVIDER(SSP_InitStruct->SSP_CPSDVSR));
    assert_param(IS_SSP_MODE(SSP_InitStruct->SSP_Mode));
    assert_param(IS_SSP_WORD_LENGTH(SSP_InitStruct->SSP_WordLength));
    assert_param(IS_SSP_CLOCK_PHASE(SSP_InitStruct->SSP_ClockPhase));
    assert_param(IS_SSP_CLOCK_POLARITY(SSP_InitStruct->SSP_ClockPolarity));
    assert_param(IS_SSP_FRAME_FORMAT(SSP_InitStruct->SSP_FrameFormat));
    assert_param(IS_SSP_SLAVE_MODE_OUTPUT_CONFIG(SSP_InitStruct->SSP_SlaveModeOutput));
    assert_param(IS_SSP_LOOPBACK_MODE(SSP_InitStruct->SSP_LoopbackMode));

    /* SSP CR1 Configuration */
    TmpReg = (uint32_t)SSP_InitStruct->SSP_LoopbackMode |
             (uint32_t)SSP_InitStruct->SSP_Mode |
             (uint32_t)SSP_InitStruct->SSP_SlaveModeOutput;
    MDR_SSP->CR1 = TmpReg;

    /* SSP CR0 Configuration */
    TmpReg = (uint32_t)SSP_InitStruct->SSP_WordLength |
             (uint32_t)SSP_InitStruct->SSP_FrameFormat |
             (uint32_t)SSP_InitStruct->SSP_ClockPolarity |
             (uint32_t)SSP_InitStruct->SSP_ClockPhase |
             (((uint32_t)SSP_InitStruct->SSP_SCR) << SSP_CR0_SCR_Pos);
    MDR_SSP->CR0 = TmpReg;

    /* SSP CPSR Configuration */
    MDR_SSP->CPSR = SSP_InitStruct->SSP_CPSDVSR;
}

/**
 * @brief  Fills each SSP_InitStruct member with its default value.
 * @param  SSP_InitStruct: pointer to a @ref SSP_InitTypeDef structure
 *         that is to be initialized.
 * @retval None.
 */
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct)
{
    /* SSP_InitStruct members default value */
    /* Initialize the SSP max speed */
    SSP_InitStruct->SSP_SCR     = 0;
    SSP_InitStruct->SSP_CPSDVSR = 2;
    /* Initialize the SPI_Mode member */
    SSP_InitStruct->SSP_Mode = SSP_MODE_MASTER;
    /* initialize the SSP_WordLength member */
    SSP_InitStruct->SSP_WordLength = SSP_WORD_LENGTH_8BIT;
    /* Initialize the SSP_ClockPhase member */
    SSP_InitStruct->SSP_ClockPhase = SSP_CLOCK_PHASE_1EDGE;
    /* Initialize the SSP_ClockPolarity member */
    SSP_InitStruct->SSP_ClockPolarity = SSP_CLOCK_POLARITY_LOW;
    /* Initialize the SSP_FrameFormat member */
    SSP_InitStruct->SSP_FrameFormat = SSP_FRAME_FORMAT_SPI;
    /* Initialize the SSP_SlaveModeOutput member */
    SSP_InitStruct->SSP_SlaveModeOutput = SSP_SLAVE_MODE_OUTPUT_ENABLE;
    /* Initialize the SSP_LoopbackMode member */
    SSP_InitStruct->SSP_LoopbackMode = SSP_LOOPBACK_MODE_DISABLE;
}

/**
 * @brief  Enables or disables the SSP peripheral.
 * @param  NewState - @ref FunctionalState - new state of the SSP peripheral.
 * @retval None.
 */
void SSP_Cmd(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        MDR_SSP->CR1 |= SSP_CR1_SSE_Msk;
    } else {
        MDR_SSP->CR1 &= ~SSP_CR1_SSE_Msk;
    }
}

/**
 * @brief  Transmits single data through the SSP peripheral.
 * @param  Data: the data to transmit.
 * @retval None.
 */
void SSP_SendData(uint16_t Data)
{
    /* Transmit Data */
    MDR_SSP->DR = Data;
}

/**
 * @brief  Returns the most recent received data by the SSP peripheral.
 * @param  None.
 * @retval The received data.
 */
uint16_t SSP_ReceiveData(void)
{
    /* Receive Data */
    return (uint16_t)MDR_SSP->DR;
}

/**
 * @brief  Enables or disables the SSP_TXD output in slave mode.
 * @param  NewState - @ref FunctionalState - new state of the SSP_TXD output.
 * @retval None.
 */
void SSP_SlaveOutputConfig(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        MDR_SSP->CR1 &= ~SSP_CR1_SOD_Msk;
    } else {
        MDR_SSP->CR1 |= SSP_CR1_SOD_Msk;
    }
}

/**
 * @brief  Checks whether the specified SSP Status Flag is set or not.
 * @param  Flag: specifies the flag to check.
 *         This parameter can be one of @ref SSP_Flags_TypeDef values.
 * @retval @ref FlagStatus - Current Status Flag state (SET or RESET).
 */
FlagStatus SSP_GetFlagStatus(SSP_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameter */
    assert_param(IS_SSP_FLAG(Flag));

    if (MDR_SSP->SR & (uint32_t)Flag) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Returns the SSP Status Flags combined value.
 * @param  None.
 * @retval The SSP Status Flags combined value.
 */
uint32_t SSP_GetStatus(void)
{
    return MDR_SSP->SR & SSP_FLAG_MASK;
}

/**
 * @brief  Enables or disables the SSP interrupts.
 * @param  ITs: specifies the SSP interrupt sources to be enabled or disabled.
 *         This parameter can be any combination of @ref SSP_IT_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the SSP interrupts.
 * @retval None.
 */
void SSP_ITConfig(uint32_t ITs, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SSP_CONFIG_ITS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        MDR_SSP->IMSC |= ITs;
    } else {
        MDR_SSP->IMSC &= ~ITs;
    }
}

/**
 * @brief  Checks whether the specified SSP masked interrupt has occurred or not.
 * @param  IT: specifies the SSP interrupt source to check.
 *         This parameter can be one of @ref SSP_IT_TypeDef values.
 * @retval  @ref ITStatus - The state of IT (SET or RESET).
 */
ITStatus SSP_GetITFlagStatus(SSP_IT_TypeDef IT)
{
    ITStatus Status;

    /* Check the parameter */
    assert_param(IS_SSP_CONFIG_IT(IT));

    if (MDR_SSP->MIS & (uint32_t)IT) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Checks whether the SSP masked interrupts has occurred or not.
 * @param  None.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref SSP_IT_TypeDef.
 */
uint32_t SSP_GetITStatus(void)
{
    return MDR_SSP->MIS & SSP_IT_MASK;
}

/**
 * @brief  Checks whether the specified SSP interrupt (non masked) has occurred or not.
 * @param  IT: specifies the SSP interrupt source to check.
 *         This parameter can be one of @ref SSP_IT_TypeDef values.
 * @retval  @ref ITStatus - The state of IT (SET or RESET).
 */
ITStatus SSP_GetITNonMaskedFlagStatus(SSP_IT_TypeDef IT)
{
    ITStatus Status;

    /* Check the parameter */
    assert_param(IS_SSP_CONFIG_IT(IT));

    if (MDR_SSP->RIS & (uint32_t)IT) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Checks whether the SSP interrupts (non masked) has occurred or not.
 * @param  None.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref SSP_IT_TypeDef.
 */
uint32_t SSP_GetITNonMaskedStatus(void)
{
    return MDR_SSP->RIS & SSP_IT_MASK;
}

/**
 * @brief  Clears SSP interrupt requests.
 * @param  ITs - @ref SSP_IT_TypeDef - specifies the interrupt requests to clear.
 *         This parameter can be any combination of the following values:
 *           @arg SSP_IT_RT
 *           @arg SSP_IT_ROR
 * @retval None.
 */
void SSP_ClearITFlags(uint32_t ITs)
{
    /* Check the parameter */
    assert_param(IS_SSP_RESET_ITS(ITs));

    MDR_SSP->ICR = ITs;
}

#if defined(USE_MDR32F21QI)
/**
 * @brief  Enables or disables the SSP DMA requests.
 * @param  DMAReqs: specifies the DMA request.
 *         This parameter can be any combination of @ref SSP_DMA_Reqs_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the DMA Request sources.
 * @retval None.
 */
void SSP_DMACmd(uint32_t DMAReqs, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SSP_DMA_REQS(DMAReqs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        /* Enable the DMA transfer for selected requests in the SSP_DMACR register */
        MDR_SSP->DMACR |= DMAReqs;
    } else {
        /* Disable the DMA transfer for selected requests in the SSP_DMACR register */
        MDR_SSP->DMACR &= ~DMAReqs;
    }
}
#endif

/** @} */ /* End of group SSP_Exported_Functions */

/** @} */ /* End of group SSP */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_ssp.c */

