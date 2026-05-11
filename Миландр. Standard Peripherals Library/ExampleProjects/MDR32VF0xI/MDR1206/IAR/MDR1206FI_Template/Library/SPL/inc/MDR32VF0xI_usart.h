/**
 *******************************************************************************
 * @file    MDR32VF0xI_usart.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    18/04/2024
 * @brief   This file contains all the functions prototypes for the USART
 *          firmware library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MDR32VF0xI_USART_H
#define MDR32VF0xI_USART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup USART USART
 * @{
 */

/** @defgroup USART_Exported_Types USART Exported Types
 * @{
 */

/**
 * @brief USART oversampling mode.
 */
typedef enum {
    USART_OVERSAMPLING_16 = (((uint32_t)0x0) << USART_CR1_OVER8_Pos), /*!< Oversampling by 16. */
    USART_OVERSAMPLING_8  = (((uint32_t)0x1) << USART_CR1_OVER8_Pos)  /*!< Oversampling by 8. */
} USART_OverSamplingMode_TypeDef;

#define IS_USART_OVERSAMPLING_MODE(MODE) (((MODE) == USART_OVERSAMPLING_16) || \
                                          ((MODE) == USART_OVERSAMPLING_8))

/**
 * @brief USART sampling mode.
 */
typedef enum {
    USART_SAMPLING_3BIT = (((uint32_t)0x0) << USART_CR3_ONEBIT_Pos), /*!< 3-bit sampling. */
    USART_SAMPLING_1BIT = (((uint32_t)0x1) << USART_CR3_ONEBIT_Pos)  /*!< 1-bit sampling. */
} USART_SamplingMode_TypeDef;

#define IS_USART_SAMPLING_MODE(MODE) (((MODE) == USART_SAMPLING_3BIT) || \
                                      ((MODE) == USART_SAMPLING_1BIT))

/**
 * @brief USART transceiver mode.
 */
typedef enum {
    USART_MODE_TX    = USART_CR1_TE,                 /*!< Enable only the transmitter. */
    USART_MODE_RX    = USART_CR1_RE,                 /*!< Enable only the receiver. */
    USART_MODE_TX_RX = (USART_CR1_TE | USART_CR1_RE) /*!< Enable the transmitter and receiver. */
} USART_Mode_TypeDef;

#define IS_USART_MODE(MODE) (((MODE) == USART_MODE_TX) || \
                             ((MODE) == USART_MODE_RX) || \
                             ((MODE) == USART_MODE_TX_RX))

/**
 * @brief USART word length.
 */
typedef enum {
    USART_WORD_LENGTH_8BIT = (((uint32_t)0x0) << USART_CR1_M_Pos), /*!< Select an 8-bit word length. */
    USART_WORD_LENGTH_9BIT = (((uint32_t)0x1) << USART_CR1_M_Pos)  /*!< Select a 9-bit word length. */
} USART_WordLength_TypeDef;

#define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WORD_LENGTH_8BIT) || \
                                      ((LENGTH) == USART_WORD_LENGTH_9BIT))

/**
 * @brief USART stop bits.
 */
typedef enum {
    USART_STOP_BITS_0p5BIT = (((uint32_t)0x1) << USART_CR2_STOP_Pos), /*!< Select 0.5 stop bit at the end of a frame when transmitting. */
    USART_STOP_BITS_1p5BIT = (((uint32_t)0x3) << USART_CR2_STOP_Pos), /*!< Select 1.5 stop bits at the end of a frame when transmitting. */
    USART_STOP_BITS_2BIT   = (((uint32_t)0x2) << USART_CR2_STOP_Pos)  /*!< Select 2 stop bits at the end of a frame when transmitting. */
} USART_StopBits_TypeDef;

#define IS_USART_STOP_BITS(STOP_BITS) (((STOP_BITS) == USART_STOP_BITS_0p5BIT) || \
                                       ((STOP_BITS) == USART_STOP_BITS_1p5BIT) || \
                                       ((STOP_BITS) == USART_STOP_BITS_2BIT))

/**
 * @brief USART parity.
 */
typedef enum {
    USART_PARITY_NONE = (((uint32_t)0x0) << USART_CR1_PCE_Pos),                                         /*!< Parity control is disabled. */
    USART_PARITY_ODD  = (((uint32_t)0x1) << USART_CR1_PCE_Pos) | (((uint32_t)0x1) << USART_CR1_PS_Pos), /*!< Parity control is enabled, odd parity is selected. */
    USART_PARITY_EVEN = (((uint32_t)0x1) << USART_CR1_PCE_Pos) | (((uint32_t)0x0) << USART_CR1_PS_Pos)  /*!< Parity control is enabled, even parity is selected. */
} USART_Parity_TypeDef;

#define IS_USART_PARITY(PARITY) (((PARITY) == USART_PARITY_NONE) || \
                                 ((PARITY) == USART_PARITY_ODD) ||  \
                                 ((PARITY) == USART_PARITY_EVEN))

/**
 * @brief USART duplex mode.
 */
typedef enum {
    USART_DUPLEX_FULL = (((uint32_t)0x0) << USART_CR3_HDSEL_Pos), /*!< Full duplex mode. */
    USART_DUPLEX_HALF = (((uint32_t)0x1) << USART_CR3_HDSEL_Pos)  /*!< Half duplex mode. */
} USART_DuplexMode_TypeDef;

#define IS_USART_DUPLEX_MODE(MODE) (((MODE) == USART_DUPLEX_FULL) || \
                                    ((MODE) == USART_DUPLEX_HALF))

/**
 * @brief USART mute mode.
 */
typedef enum {
    USART_MUTE_DISABLE             = ((uint32_t)0x0),                 /*!< Mute is disabled. */
    USART_MUTE_WAKEUP_IDLE_LINE    = USART_CR1_RWU,                   /*!< Mute is enabled, wakeup on the idle line. */
    USART_MUTE_WAKEUP_ADDRESS_MARK = (USART_CR1_RWU | USART_CR1_WAKE) /*!< Mute is enabled, wakeup on address mark. */
} USART_MuteWakeupMode_TypeDef;

#define IS_USART_WAKEUP_MODE(MODE) (((MODE) == USART_MUTE_DISABLE) ||          \
                                    ((MODE) == USART_MUTE_WAKEUP_IDLE_LINE) || \
                                    ((MODE) == USART_MUTE_WAKEUP_ADDRESS_MARK))

/**
 * @brief USART clock state.
 */
typedef enum {
    USART_CLOCK_DISABLE = (((uint32_t)0x0) << USART_CR2_CLKEN_Pos), /*!< Disable the clock. */
    USART_CLOCK_ENABLE  = (((uint32_t)0x1) << USART_CR2_CLKEN_Pos)  /*!< Enable the clock. */
} USART_ClockOutput_TypeDef;

#define IS_USART_CLOCK_OUTPUT(CLK) (((CLK) == USART_CLOCK_DISABLE) || \
                                    ((CLK) == USART_CLOCK_ENABLE))

/**
 * @brief USART clock polarity.
 */
typedef enum {
    USART_CLOCK_POLARITY_LOW  = (((uint32_t)0x0) << USART_CR2_CPOL_Pos), /*!< Constant 0 outside the frame. */
    USART_CLOCK_POLARITY_HIGH = (((uint32_t)0x1) << USART_CR2_CPOL_Pos)  /*!< Constant 1 outside the frame. */
} USART_ClockPolarity_TypeDef;

#define IS_USART_CLOCK_POLARITY(POL) (((POL) == USART_CLOCK_POLARITY_LOW) || \
                                      ((POL) == USART_CLOCK_POLARITY_HIGH))

/**
 * @brief USART clock phase.
 */
typedef enum {
    USART_CLOCK_PHASE_1EDGE = (((uint32_t)0x0) << USART_CR2_CPHA_Pos), /*!< Data sampling on the 1st edge. */
    USART_CLOCK_PHASE_2EDGE = (((uint32_t)0x1) << USART_CR2_CPHA_Pos)  /*!< Data sampling on the 2nd edge. */
} USART_ClockPhase_TypeDef;

#define IS_USART_CLOCK_PHASE(PHASE) (((PHASE) == USART_CLOCK_PHASE_1EDGE) || \
                                     ((PHASE) == USART_CLOCK_PHASE_2EDGE))

/**
 * @brief USART last bit clock impulse.
 */
typedef enum {
    USART_CLOCK_LAST_BIT_DISABLE = (((uint32_t)0x0) << USART_CR2_LBCL_Pos), /*!< There is no clock impulse in the last bit in sync mode. */
    USART_CLOCK_LAST_BIT_ENABLE  = (((uint32_t)0x1) << USART_CR2_LBCL_Pos)  /*!< There is clock impulse in the last bit in sync mode. */
} USART_ClockLastBitPulse_TypeDef;

#define IS_USART_CLOCK_LAST_BIT_PULSE(PULSE) (((PULSE) == USART_CLOCK_LAST_BIT_DISABLE) || \
                                              ((PULSE) == USART_CLOCK_LAST_BIT_ENABLE))

/**
 * @brief USART Smartcard mode selection.
 */
typedef enum {
    USART_SMARTCARD_DISABLE = (((uint32_t)0x0) << USART_CR3_SCEN_Pos), /*!< Disable Smartcard mode. */
    USART_SMARTCARD_ENABLE  = (((uint32_t)0x1) << USART_CR3_SCEN_Pos)  /*!< Enable Smartcard mode. */
} USART_SmartcardMode_TypeDef;

#define IS_USART_SMARTCARD(SC) (((SC) == USART_SMARTCARD_DISABLE) || \
                                ((SC) == USART_SMARTCARD_ENABLE))

/**
 * @brief USART NACK send in Smartcard mode.
 */
typedef enum {
    USART_SMARTCARD_NACK_DISABLE = (((uint32_t)0x0) << USART_CR3_NACK_Pos), /*!< Do not send NACK. */
    USART_SMARTCARD_NACK_ENABLE  = (((uint32_t)0x1) << USART_CR3_NACK_Pos)  /*!< Send NACK in Smartcard mode on parity error. */
} USART_SmartcardNACK_TypeDef;

#define IS_USART_SMARTCARD_NACK(NACK) (((NACK) == USART_SMARTCARD_NACK_DISABLE) || \
                                       ((NACK) == USART_SMARTCARD_NACK_ENABLE))

/**
 * @brief USART hardware flow control.
 */
typedef enum {
    USART_HARDWARE_FLOW_CONTROL_NONE    = ((uint32_t)0x00),                 /*!< Disable RTS and CTS flow control. */
    USART_HARDWARE_FLOW_CONTROL_RTS     = USART_CR3_RTSE,                   /*!< Enable only RTS flow control. */
    USART_HARDWARE_FLOW_CONTROL_CTS     = USART_CR3_CTSE,                   /*!< Enable only CTS flow control. */
    USART_HARDWARE_FLOW_CONTROL_RTS_CTS = (USART_CR3_RTSE | USART_CR3_CTSE) /*!< Enable RTS and CTS flow control. */
} USART_HardwareFlowControl_TypeDef;

#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL) (((CONTROL) == USART_HARDWARE_FLOW_CONTROL_NONE) || \
                                                 ((CONTROL) == USART_HARDWARE_FLOW_CONTROL_RTS) ||  \
                                                 ((CONTROL) == USART_HARDWARE_FLOW_CONTROL_CTS) ||  \
                                                 ((CONTROL) == USART_HARDWARE_FLOW_CONTROL_RTS_CTS))

/**
 * @brief USART flags.
 */
typedef enum {
    USART_FLAG_PARITY_ERROR          = USART_SR_PE,   /*!< Parity error. */
    USART_FLAG_FRAMING_ERROR         = USART_SR_FE,   /*!< Framing error. */
    USART_FLAG_NOISE_ERROR           = USART_SR_NF,   /*!< Noise is detected. */
    USART_FLAG_OVERRUN_ERROR         = USART_SR_ORE,  /*!< Overrun error. */
    USART_FLAG_IDLE_LINE             = USART_SR_IDLE, /*!< Idle line is detected. */
    USART_FLAG_RECEIVER_NOT_EMPTY    = USART_SR_RXNE, /*!< Receiver is not empty. */
    USART_FLAG_TRANSMISSION_COMPLETE = USART_SR_TC,   /*!< Transmission is completed. */
    USART_FLAG_TRANSMITTER_EMPTY     = USART_SR_TXE,  /*!< Transmitter is empty. */
    USART_FLAG_CTS                   = USART_SR_CTS   /*!< CTS level has been changed. */
} USART_Flags_TypeDef;

#define IS_USART_FLAG(FLAG) (((FLAG) == USART_FLAG_PARITY_ERROR) ||          \
                             ((FLAG) == USART_FLAG_FRAMING_ERROR) ||         \
                             ((FLAG) == USART_FLAG_NOISE_ERROR) ||           \
                             ((FLAG) == USART_FLAG_OVERRUN_ERROR) ||         \
                             ((FLAG) == USART_FLAG_IDLE_LINE) ||             \
                             ((FLAG) == USART_FLAG_RECEIVER_NOT_EMPTY) ||    \
                             ((FLAG) == USART_FLAG_TRANSMISSION_COMPLETE) || \
                             ((FLAG) == USART_FLAG_TRANSMITTER_EMPTY) ||     \
                             ((FLAG) == USART_FLAG_CTS))

#define IS_USART_FLAGS(FLAGS) (((FLAGS) & ~((uint32_t)(USART_FLAG_PARITY_ERROR |          \
                                                       USART_FLAG_FRAMING_ERROR |         \
                                                       USART_FLAG_NOISE_ERROR |           \
                                                       USART_FLAG_OVERRUN_ERROR |         \
                                                       USART_FLAG_IDLE_LINE |             \
                                                       USART_FLAG_RECEIVER_NOT_EMPTY |    \
                                                       USART_FLAG_TRANSMISSION_COMPLETE | \
                                                       USART_FLAG_TRANSMITTER_EMPTY |     \
                                                       USART_FLAG_CTS))) == 0)

#define IS_USART_FLAGS_CLR(FLAGS) (((FLAGS) & ~((uint32_t)(USART_FLAG_RECEIVER_NOT_EMPTY |    \
                                                           USART_FLAG_TRANSMISSION_COMPLETE | \
                                                           USART_FLAG_CTS))) == 0)

/**
 * @brief USART interrupt definition.
 */
typedef enum {
    USART_IT_PARITY_ERROR          = USART_CR1_PEIE,   /*!< Parity error interrupt. */
    USART_IT_ERROR                 = USART_CR3_EIE,    /*!< Error interrupt (DMAR=1 & (FE=1 | ORE=1 | NF=1)). */
    USART_IT_IDLE_LINE             = USART_CR1_IDLEIE, /*!< Idle line interrupt. */
    USART_IT_RECEIVER_NOT_EMPTY    = USART_CR1_RXNEIE, /*!< Not empty receiver interrupt. */
    USART_IT_TRANSMISSION_COMPLETE = USART_CR1_TCIE,   /*!< Completed transmission interrupt. */
    USART_IT_TRANSMITTER_EMPTY     = USART_CR1_TXEIE,  /*!< Empty transmitter interrupt. */
    USART_IT_CTS                   = USART_CR3_CSTIE   /*!< Changed CTS level interrupt. */
} USART_IT_TypeDef;

#define IS_USART_CONFIG_IT(IT) (((IT) == USART_IT_PARITY_ERROR) ||          \
                                ((IT) == USART_IT_ERROR) ||                 \
                                ((IT) == USART_IT_IDLE_LINE) ||             \
                                ((IT) == USART_IT_RECEIVER_NOT_EMPTY) ||    \
                                ((IT) == USART_IT_TRANSMISSION_COMPLETE) || \
                                ((IT) == USART_IT_TRANSMITTER_EMPTY) ||     \
                                ((IT) == USART_IT_CTS))

#define IS_USART_CONFIG_ITS(ITS) (((ITS) & ~((uint32_t)(USART_IT_PARITY_ERROR |          \
                                                        USART_IT_ERROR |                 \
                                                        USART_IT_IDLE_LINE |             \
                                                        USART_IT_RECEIVER_NOT_EMPTY |    \
                                                        USART_IT_TRANSMISSION_COMPLETE | \
                                                        USART_IT_TRANSMITTER_EMPTY |     \
                                                        USART_IT_CTS))) == 0)

/**
 * @brief USART DMA control.
 */
typedef enum {
    USART_DMA_TX = USART_CR3_DMAT, /*!< Enable request to the DMA from the transmitter. */
    USART_DMA_RX = USART_CR3_DMAR  /*!< Enable request to the DMA from the receiver. */
} USART_DMA_Control_TypeDef;

#define IS_USART_DMA_CONTROL(CONTROL) (((CONTROL) == USART_DMA_TX) || \
                                       ((CONTROL) == USART_DMA_RX))

#define IS_USART_DMA_CONTROLS(CONTROL) (((CONTROL) & ~(uint32_t)(USART_DMA_TX | USART_DMA_RX)) == 0)

/**
 * @brief  USART init structure definition.
 */
typedef struct {
    uint32_t           USART_BaudRate;                           /*!< This member configures the USART baud rate. */
    USART_Mode_TypeDef USART_Mode;                               /*!< Specify the permission for the transmitter and receiver.
                                                                      This parameter can be a value of the @ref USART_Mode_TypeDef. */
    USART_DuplexMode_TypeDef USART_Duplex;                       /*!< Specify USART duplex mode.
                                                                      This parameter can be a value of the @ref USART_DuplexMode_TypeDef. */
    USART_WordLength_TypeDef USART_WordLength;                   /*!< Specify the number of data bits to be transmitted or received in a frame.
                                                                      This parameter can be a value of the @ref USART_WordLength_TypeDef. */
    USART_StopBits_TypeDef USART_StopBits;                       /*!< Specify the number of stop bits to transmit.
                                                                      This parameter can be a value of the @ref USART_StopBits_TypeDef. */
    USART_Parity_TypeDef USART_Parity;                           /*!< Specify the parity mode.
                                                                      This parameter can be a value of the @ref USART_Parity_TypeDef. */
    USART_HardwareFlowControl_TypeDef USART_HardwareFlowControl; /*!< Specify the hardware flow control mode.
                                                                      This parameter can be a value of the @ref USART_HardwareFlowControl_TypeDef. */
    USART_OverSamplingMode_TypeDef USART_OverSamplingMode;       /*!< Specify the oversampling mode.
                                                                      This parameter can be a value of the @ref USART_OverSamplingMode_TypeDef. */
    USART_SamplingMode_TypeDef USART_SamplingMode;               /*!< Specify the sampling mode.
                                                                      This parameter can be a value of the @ref USART_SamplingMode_TypeDef. */

    USART_ClockOutput_TypeDef USART_ClockOutput;             /*!< Specify whether the USART clock is enabled or disabled.
                                                                  This parameter can be a value of the @ref USART_ClockOutput_TypeDef. */
    USART_ClockPolarity_TypeDef USART_ClockPolarity;         /*!< Specify a steady state of the serial clock.
                                                                  This parameter can be a value of the @ref USART_ClockPolarity_TypeDef. */
    USART_ClockPhase_TypeDef USART_ClockPhase;               /*!< Specify the clock transition on which the bit capture is fulfilled.
                                                                  This parameter can be a value of the @ref USART_ClockPhase_TypeDef. */
    USART_ClockLastBitPulse_TypeDef USART_ClockLastBitPulse; /*!< Specify whether the clock pulse corresponding to the last transmitted
                                                                  data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                                                  This parameter can be a value of the @ref USART_ClockLastBitPulse_TypeDef. */

    USART_SmartcardMode_TypeDef USART_Smartcard_Mode; /*!< Specify whether the Smartcard mode is used.
                                                           This parameter can be a value of the @ref USART_SmartcardMode_TypeDef. */
    USART_SmartcardNACK_TypeDef USART_Smartcard_NACK; /*!< Specify whether a NACK is sent in the Smartcard mode.
                                                           This parameter can be a value of the @ref USART_SmartcardNACK_TypeDef. */
    uint8_t USART_Smartcard_GuardTime;                /*!< This member configures the USART Smartcard ETU number within guard time. */
    uint8_t USART_Smartcard_ClockPrescaler;           /*!< Specify the USART Smartcard clock prescaler.
                                                           This parameter can be an even number from 2 to 62. */
} USART_InitTypeDef;

/** @} */ /* End of the group USART_Exported_Types */

/** @defgroup USART_Exported_Defines USART Exported Defines
 * @{
 */

/** @defgroup USART_Baudrate USART Baudrate
 * @{
 */

#define IS_USART_BAUDRATE(BAUDRATE)             ((BAUDRATE) <= (60 * 1000000 / 8))

#define IS_USART_DATA(DATA)                     (((DATA) & ~USART_DR_DR_Msk) == 0)

#define IS_USART_SMARTCARD_CLOCK_PRESCALER(PSC) (((PSC) >= 2) && ((PSC) <= 62) && (((PSC) & 0x1) == 0))

#define IS_USART_ADDRESS_MARK(ADDR)             (((ADDR) & ~USART_CR2_ADD_Msk) == 0)

/** @} */ /* End of the group USART_Baudrate */

/** @} */ /* End of the group USART_Exported_Defines */

/** @addtogroup USART_Exported_Functions USART Exported Functions
 * @{
 */

void        USART_DeInit(void);
ErrorStatus USART_Init(const USART_InitTypeDef* USART_InitStruct);

void USART_StructInit(USART_InitTypeDef* USART_InitStruct);

void            USART_Cmd(FunctionalState NewState);
FunctionalState USART_GetCmdState(void);

void     USART_SendData(uint16_t Data);
uint16_t USART_ReceiveData(void);

void USART_BreakLine(FunctionalState NewState);

void                         USART_MuteCmd(USART_MuteWakeupMode_TypeDef MuteWakeupMode);
USART_MuteWakeupMode_TypeDef USART_GetMuteModeStatus(void);
void                         USART_SetNodeAddress(uint8_t NodeAddress);
uint8_t                      USART_GetNodeAddress(void);

void    USART_SetSmartcardGuardTime(uint8_t GuardTime);
uint8_t USART_GetSmartcardGuardTime(void);

FlagStatus USART_GetFlagStatus(USART_Flags_TypeDef Flag);
uint32_t   USART_GetStatus(void);
void       USART_ClearFlags(uint32_t Flags);

void USART_ITConfig(uint32_t ITs, FunctionalState NewState);

void            USART_DMACmd(uint32_t DMAControl, FunctionalState NewState);
FunctionalState USART_GetDMACmdState(USART_DMA_Control_TypeDef DMAControl);

/** @} */ /* End of the group USART_Exported_Functions */

/** @} */ /* End of the group USART */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_USART_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_usart.h */

