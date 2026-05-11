/**
 *******************************************************************************
 * @file    MDR32F2xQI_uart.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    24/05/2023
 * @brief   This file contains all the UART firmware functions.
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
#include "MDR32F2xQI_uart.h"
#include "MDR32F2xQI_rst_clk.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup UART UART
 * @{
 */

/** @defgroup UART_Private_Defines UART Private Defines
 * @{
 */

#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_UART0) || \
                                    ((PERIPH) == MDR_UART1))

#define UART_IT_MASK (UART_IMSC_RIMIM | UART_IMSC_CTSMIM | UART_IMSC_DCDMIM | UART_IMSC_DSRMIM | \
                      UART_IMSC_RXIM | UART_IMSC_TXIM | UART_IMSC_RTIM | UART_IMSC_FEIM |        \
                      UART_IMSC_PEIM | UART_IMSC_BEIM | UART_IMSC_OEIM)

#define UART_FLAG_MASK         (UART_FR_BUSY | UART_FR_RXFE | UART_FR_TXFF | UART_FR_RXFF | UART_FR_TXFE)

#define UART_MODEM_INPUT_MASK  (UART_FR_CTS | UART_FR_DSR | UART_FR_DCD | UART_FR_RI)

#define UART_MODEM_OUTPUT_MASK (UART_CR_DTR | UART_CR_RTS | UART_CR_OUT1 | UART_CR_OUT2)

#define UART_F_IR_LP_BAUD16    ((uint32_t)1843200) /*!< F_IrLPBaud16 nominal frequency Hz */

/** @} */ /* End of group UART_Private_Defines */

/** @addtogroup UART_Exported_Functions UART Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the UARTx peripheral registers to their default reset values.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @retval None.
 */
void UART_DeInit(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameter */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    UARTx->CR      = 0;
    UARTx->RSR_ECR = 0;
    UARTx->ILPR    = 0;
    UARTx->IBRD    = 0;
    UARTx->FBRD    = 0;
    UARTx->LCR_H   = 0;
    UARTx->IFLS    = UART_IFLS_TXIFLSEL_8WORD | UART_IFLS_RXIFLSEL_8WORD;
    UARTx->IMSC    = 0;
    UARTx->ICR     = UART_IT_MASK;
#if defined(USE_MDR32F21QI)
    UARTx->DMACR = 0;
#endif

    /* Set CR.RXE and CR.TXE bits */
    UARTx->CR = UART_CR_TXE | UART_CR_RXE;
}

/**
 * @brief  Initializes the UARTx peripheral according to the specified
 *         parameters in the UART_InitStruct.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  UART_InitStruct: pointer to a @ref UART_InitTypeDef structure
 *         that contains the configuration information for the specified UART peripheral.
 * @retval @ref ErrorStatus - The Baud Rate status.
 */
ErrorStatus UART_Init(MDR_UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
    uint32_t             TmpReg, UART_CLK_Freq;
    uint32_t             RealSpeed;
    uint32_t             Divider;
    uint32_t             IntegerDivider;
    uint32_t             FractionalDivider;
    int32_t              SpeedError;
    RST_CLK_Freq_TypeDef RST_CLK_Clocks;
    ErrorStatus          Status = SUCCESS;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));
    assert_param(IS_UART_MODE(UART_InitStruct->UART_Mode));
    assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
    assert_param(IS_UART_STOP_BITS(UART_InitStruct->UART_StopBits));
    assert_param(IS_UART_PARITY(UART_InitStruct->UART_Parity));
    assert_param(IS_UART_FIFO_STATE(UART_InitStruct->UART_FIFO_State));
    assert_param(IS_UART_FIFO_LEVEL(UART_InitStruct->UART_FIFO_TxLevel));
    assert_param(IS_UART_FIFO_LEVEL(UART_InitStruct->UART_FIFO_RxLevel));
    assert_param(IS_UART_HARDWARE_FLOW_CONTROL(UART_InitStruct->UART_HardwareFlowControl));
    assert_param(IS_UART_LOOPBACK_MODE(UART_InitStruct->UART_LoopbackMode));

    /* UART CR configuration */
    /* Set TXE and RXE bits according to UART_Mode value */
    /* Set RTSEn and CTSEn bits according to UART_HardwareFlowControl value */
    /* Set LBE bit according to UART_LoopbackMode value */
    TmpReg = (uint32_t)UART_InitStruct->UART_Mode |
             (uint32_t)UART_InitStruct->UART_HardwareFlowControl |
             (uint32_t)UART_InitStruct->UART_LoopbackMode;
    UARTx->CR = TmpReg;

    /* Configure the UART Baud Rate */
    RST_CLK_GetClocksFreq(&RST_CLK_Clocks);

    if (UARTx == MDR_UART0) {
        UART_CLK_Freq = RST_CLK_Clocks.UART_Frequency[0];
    } else {
        UART_CLK_Freq = RST_CLK_Clocks.UART_Frequency[1];
    }

    /* Determine the integer part */
    Divider        = UART_CLK_Freq / (UART_InitStruct->UART_BaudRate >> 2);
    IntegerDivider = Divider >> 6;
    /* Determine the fractional part */
    FractionalDivider = (Divider & UART_FBRD_BAUD_DIVFRAC_Msk);
    /* Determine the speed error */
    RealSpeed  = (UART_CLK_Freq * 4) / ((IntegerDivider * 64) + FractionalDivider);
    SpeedError = (((int32_t)RealSpeed - (int32_t)UART_InitStruct->UART_BaudRate) * 128) / (int32_t)UART_InitStruct->UART_BaudRate;
    if ((SpeedError > 2) || (SpeedError < -2)) {
        Status = ERROR;
    } else {
        /* Write UART Baud Rate */
        UARTx->IBRD = IntegerDivider;
        UARTx->FBRD = FractionalDivider;

        /* UART LCR_H configuration */
        /* Set WLEN bits according to UART_WordLength value */
        /* Set STP2 bit according to UART_StopBits value */
        /* Set PEN, EPS and SPS bits according to UART_Parity value */
        /* Set FEN bit according to UART_FIFO_State value */
        TmpReg = (uint32_t)UART_InitStruct->UART_WordLength |
                 (uint32_t)UART_InitStruct->UART_StopBits |
                 (uint32_t)UART_InitStruct->UART_Parity |
                 (uint32_t)UART_InitStruct->UART_FIFO_State;
        UARTx->LCR_H = TmpReg;

        /* UART IFLS configuration */
        UARTx->IFLS = ((uint32_t)UART_InitStruct->UART_FIFO_TxLevel << UART_IFLS_TXIFLSEL_Pos) |
                      ((uint32_t)UART_InitStruct->UART_FIFO_RxLevel << UART_IFLS_RXIFLSEL_Pos);
    }

    return Status;
}

/**
 * @brief  Fills each UART_InitStruct member with its default value.
 * @param  UART_InitStruct: pointer to a @ref UART_InitTypeDef structure
 *         that is to be initialized.
 * @retval None.
 */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
    UART_InitStruct->UART_BaudRate            = 9600;
    UART_InitStruct->UART_Mode                = UART_MODE_TX_RX;
    UART_InitStruct->UART_WordLength          = UART_WORD_LENGTH_8BIT;
    UART_InitStruct->UART_StopBits            = UART_STOP_BITS_1BIT;
    UART_InitStruct->UART_Parity              = UART_PARITY_NONE;
    UART_InitStruct->UART_FIFO_State          = UART_FIFO_DISABLE;
    UART_InitStruct->UART_FIFO_TxLevel        = UART_FIFO_LEVEL_8WORD;
    UART_InitStruct->UART_FIFO_RxLevel        = UART_FIFO_LEVEL_8WORD;
    UART_InitStruct->UART_HardwareFlowControl = UART_HARDWARE_FLOW_CONTROL_NONE;
    UART_InitStruct->UART_LoopbackMode        = UART_LOOPBACK_MODE_DISABLE;
}

/**
 * @brief  Enables or disables the specified UART peripheral.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  NewState - @ref FunctionalState - new state of the UARTx peripheral.
 * @retval None.
 */
void UART_Cmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Enable the selected UART by setting the UARTEN bit in the CR register */
        UARTx->CR |= UART_CR_UARTEN;
    } else {
        /* Disable the selected UART by clearing the UARTEN bit in the CR register */
        UARTx->CR &= ~UART_CR_UARTEN;
    }
}

/**
 * @brief  Configures the UART IrDA interface.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  IrDAMode - @ref UART_IrDAMode_TypeDef - specifies the IrDA mode.
 * @retval None.
 */
void UART_IrDAConfig(MDR_UART_TypeDef* UARTx, UART_IrDAMode_TypeDef IrDAMode)
{
    uint32_t             UART_CLK_Freq;
    RST_CLK_Freq_TypeDef RST_CLK_Clocks;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_IRDA_MODE(IrDAMode));

    if (IrDAMode == UART_IRDA_MODE_LOW_POWER) {
        /* Configure the UART ILPR */
        RST_CLK_GetClocksFreq(&RST_CLK_Clocks);

        if (UARTx == MDR_UART0) {
            UART_CLK_Freq = RST_CLK_Clocks.UART_Frequency[0];
        } else {
            UART_CLK_Freq = RST_CLK_Clocks.UART_Frequency[1];
        }

        UARTx->ILPR = UART_CLK_Freq / UART_F_IR_LP_BAUD16;
    }

    UARTx->CR |= IrDAMode;
}

/**
 * @brief  Enables or disables the UART IrDA interface.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  NewState - @ref FunctionalState - new state of the IrDA mode.
 * @retval None.
 */
void UART_IrDACmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Set SIREN bit in the UART CR register */
        UARTx->CR |= UART_CR_SIREN;
    } else {
        /* Reset SIREN bit in the UART CR register */
        UARTx->CR &= ~UART_CR_SIREN;
    }
}

/**
 * @brief  Specifies the fill level of the UART FIFO buffers at which
 *         events are generated for interrupts, DMA requests and hardware flow control.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  RxLevel - @ref UART_FIFO_Level_TypeDef - specifies the receiver buffer.
 * @param  TxLevel - @ref UART_FIFO_Level_TypeDef - specifies the transmitter buffer.
 * @retval None.
 */
void UART_FIFOFillLevelConfig(MDR_UART_TypeDef* UARTx, UART_FIFO_Level_TypeDef RxLevel, UART_FIFO_Level_TypeDef TxLevel)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_FIFO_LEVEL(RxLevel));
    assert_param(IS_UART_FIFO_LEVEL(TxLevel));

    UARTx->IFLS = ((uint32_t)RxLevel << UART_IFLS_RXIFLSEL_Pos) | (uint32_t)TxLevel;
}

/**
 * @brief  Transmits single data through the UARTx peripheral.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  Data: the data to transmit.
 * @retval None.
 */
void UART_SendData(MDR_UART_TypeDef* UARTx, uint8_t Data)
{
    /* Check the parameter */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    /* Transmit Data */
    UARTx->DR = (uint32_t)Data;
}

/**
 * @brief  Returns the most recent received data by the UARTx peripheral.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @retval The received data (7:0) and error flags (11:8).
 */
uint16_t UART_ReceiveData(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    /* Receive Data */
    return (uint16_t)UARTx->DR;
}

/**
 * @brief  Break transmit.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  NewState - @ref FunctionalState - new state of the line break generation.
 * @retval None.
 */
void UART_BreakLine(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Set BRK bit in the UART LCR_H register */
        UARTx->LCR_H |= UART_LCR_H_BRK;
    } else {
        /* Reset BRK bit in the UART LCR_H register */
        UARTx->LCR_H &= ~UART_LCR_H_BRK;
    }
}

/**
 * @brief  Checks whether the specified UART flag is set or not.
 * @param  UARTx: Select the UART or the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  Flag - @ref UART_Flags_TypeDef - specifies the flag to check.
 * @retval @ref FlagStatus - The state of Flag (SET or RESET).
 */
FlagStatus UART_GetFlagStatus(MDR_UART_TypeDef* UARTx, UART_Flags_TypeDef Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_FLAG(Flag));

    if (UARTx->FR & (uint32_t)Flag) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Returns the UART Status Flags combined value.
 * @param  UARTx: Select the UART or the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @retval The UART Status Flags combined value.
 */
uint32_t UART_GetStatus(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameter */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    return UARTx->FR & UART_FLAG_MASK;
}

/**
 * @brief  Enables or disables the UART interrupts.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  ITs: the UARTx interrupt sources to be enabled or disabled.
 *         This parameter can be any combination of @ref UART_IT_TypeDef values.
 * @param  NewState - @ref FunctionalState - new state of the UARTx interrupts.
 * @retval None.
 */
void UART_ITConfig(MDR_UART_TypeDef* UARTx, uint32_t ITs, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_ITS(ITs));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        UARTx->IMSC |= ITs;
    } else {
        UARTx->IMSC &= ~ITs;
    }
}

/**
 * @brief  Checks whether the specified UART masked interrupt has occurred or not.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  IT: specifies the UART interrupt source to check.
 *         This parameter can be one of @ref UART_IT_TypeDef values.
 * @retval  @ref ITStatus - The state of IT (SET or RESET).
 */
ITStatus UART_GetITFlagStatus(MDR_UART_TypeDef* UARTx, UART_IT_TypeDef IT)
{
    ITStatus Status;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_IT(IT));

    if (UARTx->MIS & (uint32_t)IT) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Checks whether the UART masked interrupts has occurred or not.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref UART_IT_TypeDef.
 */
uint32_t UART_GetITStatus(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameter */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    return UARTx->MIS & UART_IT_MASK;
}

/**
 * @brief  Checks whether the specified UART interrupt (non masked) has occurred or not.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  IT: specifies the UART interrupt source to check.
 *         This parameter can be one of @ref UART_IT_TypeDef values.
 * @retval  @ref ITStatus - The state of IT (SET or RESET).
 */
ITStatus UART_GetITNonMaskedFlagStatus(MDR_UART_TypeDef* UARTx, UART_IT_TypeDef IT)
{
    ITStatus Status;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_IT(IT));

    if (UARTx->RIS & (uint32_t)IT) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Checks whether the UART interrupts (non masked) has occurred or not.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @retval Combined state of currently active interrupt flags.
 *         Returns combined value of @ref UART_IT_TypeDef.
 */
uint32_t UART_GetITNonMaskedStatus(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameter */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    return UARTx->RIS & UART_IT_MASK;
}

/**
 * @brief  Clears UART interrupt requests.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  ITs - @ref UART_IT_TypeDef - specifies the interrupt requests to clear.
 *         This parameter can be any combination of @ref UART_IT_TypeDef values.
 * @retval None.
 */
void UART_ClearITFlags(MDR_UART_TypeDef* UARTx, uint32_t ITs)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_ITS(ITs));

    UARTx->ICR = ITs;
}

#if defined(USE_MDR32F21QI)
/**
 * @brief  Configures the UART DMA interface.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  DMAControl: specifies the DMA interface settings.
 *         This parameter can be any combination of @ref UART_DMA_Control_TypeDef values.
 * @param  NewState: new state of the DMA interface settings.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None.
 */
void UART_DMACmd(MDR_UART_TypeDef* UARTx, uint32_t DMAControl, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DMA_CONTROL(DMAControl));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Enable the DMA interface settings (requests and DMAONERR bit) in the UART DMACR register */
        UARTx->DMACR |= DMAControl;
    } else {
        /* Disable the DMA interface settings (requests and DMAONERR bit) in the UART DMACR register */
        UARTx->DMACR &= (uint32_t)~DMAControl;
    }
}
#endif

/**
 * @brief  Checks whether the specified UART modem control input is active or not.
 * @param  UARTx: Select the UART or the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  Input - @ref UART_ModemInput_TypeDef - specifies the modem control input to check.
 * @retval @ref FlagStatus - The state of Input (SET or RESET).
 */
FlagStatus UART_GetModemInput(MDR_UART_TypeDef* UARTx, UART_ModemInput_TypeDef Input)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_MODEM_INPUT(Input));

    if (UARTx->FR & (uint32_t)Input) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Returns the UART modem control inputs combined value.
 * @param  UARTx: Select the UART or the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @retval The UART modem control inputs combined value.
 */
uint32_t UART_GetModemInputs(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameter */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    return UARTx->FR & UART_MODEM_INPUT_MASK;
}

/**
 * @brief  Set UART modem control outputs.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  Outputs - @ref UART_ModemOutput_TypeDef - specifies the modem control outputs to set.
 *         This parameter can be any combination of @ref UART_ModemOutput_TypeDef values.
 * @retval None.
 */
void UART_SetModemOutputs(MDR_UART_TypeDef* UARTx, uint32_t Outputs)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_MODEM_OUTPUTS(Outputs));

    UARTx->CR |= Outputs;
}

/**
 * @brief  Clear UART modem control outputs.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  Outputs - @ref UART_ModemOutput_TypeDef - specifies the modem control outputs to clear.
 *         This parameter can be any combination of @ref UART_ModemOutput_TypeDef values.
 * @retval None.
 */
void UART_ClearModemOutputs(MDR_UART_TypeDef* UARTx, uint32_t Outputs)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_MODEM_OUTPUTS(Outputs));

    UARTx->CR &= ~Outputs;
}

/**
 * @brief  Checks whether the specified UART modem control output is active or not.
 * @param  UARTx: Select the UART or the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  Output - @ref UART_ModemOutput_TypeDef - specifies the modem control output to check.
 * @retval @ref FlagStatus - The state of Output (SET or RESET).
 */
FlagStatus UART_GetModemOutput(MDR_UART_TypeDef* UARTx, UART_ModemOutput_TypeDef Output)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_MODEM_OUTPUT(Output));

    if (UARTx->CR & (uint32_t)Output) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Returns the UART modem control outputs combined value.
 * @param  UARTx: Select the UART or the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @retval The UART modem control outputs combined value.
 */
uint32_t UART_GetModemOutputs(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameter */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    return UARTx->CR & UART_MODEM_OUTPUT_MASK;
}

/** @} */ /* End of group UART_Exported_Functions */

/** @} */ /* End of group UART */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_uart.c */

