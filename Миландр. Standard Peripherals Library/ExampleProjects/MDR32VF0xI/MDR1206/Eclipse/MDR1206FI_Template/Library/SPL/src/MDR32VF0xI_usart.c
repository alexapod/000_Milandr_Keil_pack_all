/**
 *******************************************************************************
 * @file    MDR32VF0xI_usart.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   This file contains all the USART firmware functions.
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
#include "MDR32VF0xI_usart.h"
#include "MDR32VF0xI_rst_clk.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup USART USART
 * @{
 */

/** @defgroup USART_Private_Defines USART Private Defines
 * @{
 */

#define USART_FLAGS_FORCE_CLEAR_MASK (USART_SR_RXNE | USART_SR_TC | USART_SR_CTS)

#define USART_IT_CR1_MASK            (USART_CR1_PEIE | USART_CR1_IDLEIE | USART_CR1_RXNEIE | USART_CR1_TCIE | USART_CR1_TXEIE)

#define USART_IT_CR3_MASK            (USART_CR3_EIE | USART_CR3_CSTIE)

/** @} */ /* End of the group USART_Private_Defines */

/** @addtogroup USART_Exported_Functions USART Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the USART peripheral registers to their default reset values.
 * @param  None.
 * @return None.
 */
void USART_DeInit(void)
{
    MDR_USART->CR1 = 0;
    MDR_USART->CR2 = 0;
    MDR_USART->CR3 = 0;
    MDR_USART->BRR = 0;
    MDR_USART->SR;
    MDR_USART->DR;
    MDR_USART->SR   = USART_FLAGS_FORCE_CLEAR_MASK;
    MDR_USART->GTPR = 0;
}

/**
 * @brief  Initialize the USART peripheral according to the specified
 *         parameters in the USART_InitStruct.
 * @note:  CPU clock should be configured before calling USART_Init() to set proper baud rate.
 * @param  USART_InitStruct: The pointer to the @ref USART_InitTypeDef structure
 *         that contains the configuration of the USART peripheral.
 * @return @ref ErrorStatus - baud rate configuration status.
 */
ErrorStatus USART_Init(const USART_InitTypeDef* USART_InitStruct)
{
    uint32_t             TmpReg, USART_CLK_Freq;
    uint32_t             Divider;
    uint32_t             IntegerDivider;
    uint32_t             FractionalDivider;
    uint32_t             SpeedError;
    RST_CLK_Freq_TypeDef RST_CLK_Clocks;
    ErrorStatus          Status = ERROR;

    /* Check the parameters. */
    assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
    assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
    assert_param(IS_USART_DUPLEX_MODE(USART_InitStruct->USART_Duplex));
    assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
    assert_param(IS_USART_STOP_BITS(USART_InitStruct->USART_StopBits));
    assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
    assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
    assert_param(IS_USART_OVERSAMPLING_MODE(USART_InitStruct->USART_OverSamplingMode));
    assert_param(IS_USART_SAMPLING_MODE(USART_InitStruct->USART_SamplingMode));
    assert_param(IS_USART_CLOCK_OUTPUT(USART_InitStruct->USART_ClockOutput));
    assert_param(IS_USART_CLOCK_POLARITY(USART_InitStruct->USART_ClockPolarity));
    assert_param(IS_USART_CLOCK_LAST_BIT_PULSE(USART_InitStruct->USART_ClockLastBitPulse));
    assert_param(IS_USART_CLOCK_PHASE(USART_InitStruct->USART_ClockPhase));
    assert_param(IS_USART_SMARTCARD(USART_InitStruct->USART_Smartcard_Mode));
    assert_param(IS_USART_SMARTCARD_NACK(USART_InitStruct->USART_Smartcard_NACK));
    assert_param(IS_USART_SMARTCARD_CLOCK_PRESCALER(USART_InitStruct->USART_Smartcard_ClockPrescaler));

    /* The LBCL, CPOL and CPHA bits have to be selected when both the transmitter and the
       receiver are disabled (TE=RE=0) to ensure that the clock pulses are functioning correctly. */
    MDR_USART->CR1 &= ~(USART_CR1_RE_Msk | USART_CR1_TE_Msk);

    /* USART CR2 configuration. */
    TmpReg = MDR_USART->CR2;
    TmpReg &= ~(USART_CR2_CPHA_Msk | USART_CR2_CPOL_Msk | USART_CR2_CLKEN_Msk |
                USART_CR2_LBCL_Msk | USART_CR2_STOP_Msk);
    TmpReg |= (uint32_t)(USART_InitStruct->USART_StopBits) |
              (uint32_t)(USART_InitStruct->USART_ClockOutput) |
              (uint32_t)(USART_InitStruct->USART_ClockPolarity) |
              (uint32_t)(USART_InitStruct->USART_ClockLastBitPulse) |
              (uint32_t)(USART_InitStruct->USART_ClockPhase);
    MDR_USART->CR2 = TmpReg;

    /* USART CR1 configuration. */
    TmpReg = MDR_USART->CR1;
    TmpReg &= ~(USART_CR1_RE_Msk | USART_CR1_TE_Msk |
                USART_CR1_PS_Msk | USART_CR1_PCE_Msk | USART_CR1_OVER8_Msk);
    TmpReg |= (uint32_t)(USART_InitStruct->USART_Mode) |
              (uint32_t)(USART_InitStruct->USART_Parity) |
              (uint32_t)(USART_InitStruct->USART_WordLength) |
              (uint32_t)(USART_InitStruct->USART_OverSamplingMode);
    MDR_USART->CR1 = TmpReg;

    /* USART CR3 configuration. */
    TmpReg = MDR_USART->CR3;
    TmpReg &= ~(USART_CR3_HDSEL_Msk | USART_CR3_NACK_Msk | USART_CR3_SCEN_Msk |
                USART_CR3_RTSE_Msk | USART_CR3_CTSE_Msk | USART_CR3_ONEBIT_Msk);
    TmpReg |= (uint32_t)(USART_InitStruct->USART_Duplex) |
              (uint32_t)(USART_InitStruct->USART_SamplingMode) |
              (uint32_t)(USART_InitStruct->USART_HardwareFlowControl) |
              (uint32_t)(USART_InitStruct->USART_Smartcard_Mode) |
              (uint32_t)(USART_InitStruct->USART_Smartcard_NACK);
    MDR_USART->CR3 = TmpReg;

    MDR_USART->GTPR = (((uint32_t)USART_InitStruct->USART_Smartcard_ClockPrescaler >> 1) & USART_GTPR_PSC_Msk) |
                      (((uint32_t)USART_InitStruct->USART_Smartcard_GuardTime << USART_GTPR_GT_Pos) & USART_GTPR_GT_Msk);

    /* Configure the USART baud rate. */
    RST_CLK_GetClocksFreq(&RST_CLK_Clocks, RST_CLK_CLOCK_FREQ_CPU_CLK);

    USART_CLK_Freq = RST_CLK_Clocks.CPU_CLK_Frequency;

    Divider = USART_CLK_Freq / USART_InitStruct->USART_BaudRate;

    SpeedError = ((USART_CLK_Freq * 10) / (Divider * USART_InitStruct->USART_BaudRate / 10));

    if ((SpeedError >= 98) && (SpeedError <= 102)) {
        if ((USART_InitStruct->USART_Smartcard_Mode == USART_SMARTCARD_DISABLE) ||
            (USART_InitStruct->USART_OverSamplingMode == USART_OVERSAMPLING_8)) {
            /* Smartcard mode disabled or OVER8=1. */
            IntegerDivider    = Divider >> 3;
            FractionalDivider = Divider & 0x7;
        } else {
            IntegerDivider    = Divider >> 4;
            FractionalDivider = Divider & 0xF;
        }

        MDR_USART->BRR = (IntegerDivider << USART_BRR_DIV_MANTISSA_Pos) | FractionalDivider;
        Status         = SUCCESS;
    }

    return Status;
}

/**
 * @brief  Fill each USART_InitStruct member with its default value.
 * @param  USART_InitStruct: The pointer to the @ref USART_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
    USART_InitStruct->USART_BaudRate                 = 9600;
    USART_InitStruct->USART_Mode                     = USART_MODE_TX_RX;
    USART_InitStruct->USART_Duplex                   = USART_DUPLEX_FULL;
    USART_InitStruct->USART_WordLength               = USART_WORD_LENGTH_8BIT;
    USART_InitStruct->USART_StopBits                 = USART_STOP_BITS_2BIT;
    USART_InitStruct->USART_Parity                   = USART_PARITY_NONE;
    USART_InitStruct->USART_HardwareFlowControl      = USART_HARDWARE_FLOW_CONTROL_NONE;
    USART_InitStruct->USART_OverSamplingMode         = USART_OVERSAMPLING_16;
    USART_InitStruct->USART_SamplingMode             = USART_SAMPLING_3BIT;
    USART_InitStruct->USART_ClockOutput              = USART_CLOCK_DISABLE;
    USART_InitStruct->USART_ClockPolarity            = USART_CLOCK_POLARITY_LOW;
    USART_InitStruct->USART_ClockPhase               = USART_CLOCK_PHASE_1EDGE;
    USART_InitStruct->USART_ClockLastBitPulse        = USART_CLOCK_LAST_BIT_DISABLE;
    USART_InitStruct->USART_Smartcard_Mode           = USART_SMARTCARD_DISABLE;
    USART_InitStruct->USART_Smartcard_NACK           = USART_SMARTCARD_NACK_DISABLE;
    USART_InitStruct->USART_Smartcard_GuardTime      = 0;
    USART_InitStruct->USART_Smartcard_ClockPrescaler = 2;
}

/**
 * @brief  Enable or disable the USART peripheral.
 * @param  NewState: @ref FunctionalState - a new state of the USART peripheral.
 * @return None.
 */
void USART_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_USART->CR1 |= USART_CR1_UE;
    } else {
        MDR_USART->CR1 &= ~USART_CR1_UE;
    }
}

/**
 * @brief  Get the USART peripheral work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the USART peripheral.
 */
FunctionalState USART_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_USART->CR1 & USART_CR1_UE) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Transmit single data via the USART peripheral.
 * @param  Data: The data to transmit.
 * @return None.
 */
void USART_SendData(uint16_t Data)
{
    /* Check the parameters. */
    assert_param(IS_USART_DATA(Data));

    /* Transmitted data. */
    MDR_USART->DR = (uint32_t)Data;
}

/**
 * @brief  Return the data most recently received by the USART peripheral.
 * @return The received data.
 */
uint16_t USART_ReceiveData(void)
{
    /* Received data. */
    return (uint16_t)MDR_USART->DR;
}

/**
 * @brief  Sending of a break symbol.
 * @param  NewState: @ref FunctionalState - a new state of the line break generation.
 * @return None.
 */
void USART_BreakLine(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Set SBK bit in the USART CR1 register. */
        MDR_USART->CR1 |= USART_CR1_SBK;
    } else {
        /* Reset SBK bit in the USART CR1 register. */
        MDR_USART->CR1 &= ~USART_CR1_SBK;
    }
}

/**
 * @brief  Mute/unmute USART and set the wakeup conditions.
 * @param  MuteWakeupMode: @ref USART_MuteWakeupMode_TypeDef - the mute and wakeup mode.
 * @return None.
 */
void USART_MuteCmd(USART_MuteWakeupMode_TypeDef MuteWakeupMode)
{
    uint32_t TempReg;

    /* Check the parameters. */
    assert_param(IS_USART_WAKEUP_MODE(MuteWakeupMode));

    TempReg = MDR_USART->CR1;
    TempReg &= ~(USART_CR1_RWU_Msk | USART_CR1_WAKE_Msk);
    TempReg |= (uint32_t)MuteWakeupMode;
    MDR_USART->CR1 = TempReg;
}

/**
 * @brief  Get the USART mute status and wakeup conditions.
 * @note   If not in mute state, ignore wakeup conditions and return only mute status.
 * @return @ref USART_MuteWakeupMode_TypeDef - a current mute and wakeup mode.
 */
USART_MuteWakeupMode_TypeDef USART_GetMuteModeStatus(void)
{
    uint32_t TempReg;

    TempReg = MDR_USART->CR1;

    if ((TempReg & USART_CR1_RWU_Msk) != 0) {
        /* Return mute status and wakeup conditions. */
        return (USART_MuteWakeupMode_TypeDef)(TempReg & (USART_CR1_RWU_Msk | USART_CR1_WAKE_Msk));
    } else {
        /* Return mute status. */
        return USART_MUTE_DISABLE;
    }
}

/**
 * @brief  Set the address of the USART node which is used in the multiprocessor communication
 *         during the Mute mode for wake up with the address mark detection.
 * @param  NodeAddress: 4-bit USART node address.
 * @return None.
 */
void USART_SetNodeAddress(uint8_t NodeAddress)
{
    /* Check the parameters. */
    assert_param(IS_USART_ADDRESS_MARK(NodeAddress));

    MDR_USART->CR2 = (MDR_USART->CR2 & ~USART_CR2_ADD_Msk) | ((uint32_t)NodeAddress & USART_CR2_ADD_Msk);
}

/**
 * @brief  Return 4-bit USART node address.
 * @return Address of the USART node.
 */
uint8_t USART_GetNodeAddress(void)
{
    return (uint8_t)(MDR_USART->CR2 & USART_CR2_ADD_Msk);
}

/**
 * @brief  Set USART guard time for the smartcard mode.
 * @param  GuardTime: Guard time interval.
 * @return None.
 */
void USART_SetSmartcardGuardTime(uint8_t GuardTime)
{
    uint32_t TempReg;
    TempReg = MDR_USART->GTPR;

    TempReg &= ~USART_GTPR_GT_Msk;
    TempReg |= (uint32_t)GuardTime << USART_GTPR_GT_Pos;

    MDR_USART->GTPR = TempReg;
}

/**
 * @brief  Get USART smartcard mode guard time.
 * @return A value of guard time interval.
 */
uint8_t USART_GetSmartcardGuardTime(void)
{
    return (uint8_t)((MDR_USART->GTPR & USART_GTPR_GT_Msk) >> USART_GTPR_GT_Pos);
}

/**
 * @brief  Check whether the specified USART flag is set or not.
 * @param  Flag: @ref USART_Flags_TypeDef - specify the flag to check.
 * @return @ref FlagStatus - a state of the checked flag (SET or RESET).
 */
FlagStatus USART_GetFlagStatus(USART_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_USART_FLAG(Flag));

    if ((MDR_USART->SR & (uint32_t)Flag) != 0) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Return a combined value of the USART status flags.
 * @return A combined value of the USART status flags.
 */
uint32_t USART_GetStatus(void)
{
    /* Check the parameters. */

    return MDR_USART->SR;
}

/**
 * @brief  Clear the USART status flags.
 * @param  Flags: USART flags to clear.
 *         This parameter can be any combination of the following values:
 *          @arg USART_FLAG_RECEIVER_NOT_EMPTY;
 *          @arg USART_FLAG_TRANSMISSION_COMPLETE;
 *          @arg USART_FLAG_CTS.
 * @return None.
 */
void USART_ClearFlags(uint32_t Flags)
{
    /* Check the parameters. */
    assert_param(IS_USART_FLAGS_CLR(Flags));

    MDR_USART->SR = Flags;
}

/**
 * @brief  Enable or disable the USART interrupts.
 * @param  ITs: The USART interrupt sources to be enabled or disabled.
 *         This parameter can be any combination of @ref USART_IT_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the USART interrupts.
 * @return None.
 */
void USART_ITConfig(uint32_t ITs, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_USART_CONFIG_ITS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        if ((ITs & USART_IT_CR1_MASK) != 0) {
            MDR_USART->CR1 |= (ITs & USART_IT_CR1_MASK);
        }
        if ((ITs & USART_IT_CR3_MASK) != 0) {
            MDR_USART->CR3 |= (ITs & USART_IT_CR3_MASK);
        }
    } else {
        if ((ITs & USART_IT_CR1_MASK) != 0) {
            MDR_USART->CR1 &= ~(ITs & USART_IT_CR1_MASK);
        }
        if ((ITs & USART_IT_CR3_MASK) != 0) {
            MDR_USART->CR3 &= ~(ITs & USART_IT_CR3_MASK);
        }
    }
}

/**
 * @brief  Configure the USART DMA interface.
 * @param  DMAControl: Specify the DMA interface settings.
 *         This parameter can be any combination of @ref USART_DMA_Control_TypeDef values.
 * @param  NewState: @ref FunctionalState - a new state of the DMA interface settings.
 * @return None.
 */
void USART_DMACmd(uint32_t DMAControl, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_USART_DMA_CONTROLS(DMAControl));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_USART->CR3 |= DMAControl;
    } else {
        MDR_USART->CR3 &= ~DMAControl;
    }
}

/**
 * @brief  Get the USARTx DMA interface work state.
 * @param  DMAControl: @ref USART_DMA_Control_TypeDef - specify the DMA interface settings.
 * @return @ref FunctionalState - the current work state of the USARTx DMA interface.
 */
FunctionalState USART_GetDMACmdState(USART_DMA_Control_TypeDef DMAControl)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_USART_DMA_CONTROL(DMAControl));

    if ((MDR_USART->CR3 & (uint32_t)DMAControl) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/** @} */ /* End of the group USART_Exported_Functions */

/** @} */ /* End of the group USART */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_usart.c */

