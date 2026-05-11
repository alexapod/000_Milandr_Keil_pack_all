/**
 *******************************************************************************
 * @file    MDR32F2xQI_uart.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    24/05/2023
 * @brief   This file contains all the functions prototypes for the UART
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
#ifndef __MDR32F2xQI_UART_H
#define __MDR32F2xQI_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup UART UART
 * @{
 */

/** @defgroup UART_Exported_Types UART Exported Types
 * @{
 */

/**
 * @brief UART Transfer Mode
 */
typedef enum {
    UART_MODE_TX    = UART_CR_TXE,                /*!< Enables only transmitter. */
    UART_MODE_RX    = UART_CR_RXE,                /*!< Enables only receiver. */
    UART_MODE_TX_RX = (UART_CR_TXE | UART_CR_RXE) /*!< Enables transmitter and receiver. */
} UART_Mode_TypeDef;

#define IS_UART_MODE(MODE) (((MODE) == UART_MODE_TX) || \
                            ((MODE) == UART_MODE_RX) || \
                            ((MODE) == UART_MODE_TX_RX))

/**
 * @brief UART Word Length
 */
typedef enum {
    UART_WORD_LENGTH_5BIT = UART_LCR_H_WLEN_5BIT, /*!< Selects a 5-bit word length. */
    UART_WORD_LENGTH_6BIT = UART_LCR_H_WLEN_6BIT, /*!< Selects a 6-bit word length. */
    UART_WORD_LENGTH_7BIT = UART_LCR_H_WLEN_7BIT, /*!< Selects a 7-bit word length. */
    UART_WORD_LENGTH_8BIT = UART_LCR_H_WLEN_8BIT  /*!< Selects a 8-bit word length. */
} UART_WordLength_TypeDef;

#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == UART_WORD_LENGTH_5BIT) || \
                                     ((LENGTH) == UART_WORD_LENGTH_6BIT) || \
                                     ((LENGTH) == UART_WORD_LENGTH_7BIT) || \
                                     ((LENGTH) == UART_WORD_LENGTH_8BIT))

/**
 * @brief UART Stop Bits
 */
typedef enum {
    UART_STOP_BITS_1BIT = (((uint32_t)0x0) << UART_LCR_H_STP2_Pos), /*!< Selects 1 stop bit when transmitting at the end of a frame. */
    UART_STOP_BITS_2BIT = (((uint32_t)0x1) << UART_LCR_H_STP2_Pos)  /*!< Selects 2 stop bits when transmitting at the end of a frame. */
} UART_StopBits_TypeDef;

#define IS_UART_STOP_BITS(STOP_BITS) (((STOP_BITS) == UART_STOP_BITS_1BIT) || \
                                      ((STOP_BITS) == UART_STOP_BITS_2BIT))

/**
 * @brief UART Parity
 */
typedef enum {
    UART_PARITY_NONE = ((uint32_t)0x00),                                  /*!< Selects the mode in which the parity bit is not checked. */
    UART_PARITY_ODD  = (UART_LCR_H_PEN),                                  /*!< Selects the mode in which the parity bit pads the number of ones to an odd number. */
    UART_PARITY_EVEN = (UART_LCR_H_PEN | UART_LCR_H_EPS),                 /*!< Selects the mode in which the parity bit pads the number of ones to an even number. */
    UART_PARITY_1    = (UART_LCR_H_PEN | UART_LCR_H_SPS),                 /*!< Selects the mode in which the parity bit is always 1. */
    UART_PARITY_0    = (UART_LCR_H_PEN | UART_LCR_H_EPS | UART_LCR_H_SPS) /*!< Selects the mode in which the parity bit is always 0. */
} UART_Parity_TypeDef;

#define IS_UART_PARITY(PARITY) (((PARITY) == UART_PARITY_NONE) || \
                                ((PARITY) == UART_PARITY_ODD) ||  \
                                ((PARITY) == UART_PARITY_EVEN) || \
                                ((PARITY) == UART_PARITY_1) ||    \
                                ((PARITY) == UART_PARITY_0))

/**
 * @brief UART FIFO State
 */
typedef enum {
    UART_FIFO_DISABLE = (((uint32_t)0x0) << UART_LCR_H_FEN_Pos), /*!< Disables FIFO buffers (FIFOs become 1-byte-deep holding registers). */
    UART_FIFO_ENABLE  = (((uint32_t)0x1) << UART_LCR_H_FEN_Pos)  /*!< Enables FIFO buffers (FIFOs is a 16 location deep). */
} UART_FIFO_State_TypeDef;

#define IS_UART_FIFO_STATE(STATE) (((STATE) == UART_FIFO_DISABLE) || \
                                   ((STATE) == UART_FIFO_ENABLE))

/**
 * @brief UART FIFO fill level definition
 */
typedef enum {
    UART_FIFO_LEVEL_2WORD  = UART_IFLS_TXIFLSEL_2WORD,  /*!< Selects the 1/8 fill level of the FIFO buffer. */
    UART_FIFO_LEVEL_4WORD  = UART_IFLS_TXIFLSEL_4WORD,  /*!< Selects the 1/4 fill level of the FIFO buffer.*/
    UART_FIFO_LEVEL_8WORD  = UART_IFLS_TXIFLSEL_8WORD,  /*!< Selects the 1/2 fill level of the FIFO buffer. */
    UART_FIFO_LEVEL_12WORD = UART_IFLS_TXIFLSEL_12WORD, /*!< Selects the 3/4 fill level of the FIFO buffer. */
    UART_FIFO_LEVEL_14WORD = UART_IFLS_TXIFLSEL_14WORD  /*!< Selects the 7/8 fill level of the FIFO buffer. */
} UART_FIFO_Level_TypeDef;

#define IS_UART_FIFO_LEVEL(FIFO_LEVEL) (((FIFO_LEVEL) == UART_FIFO_LEVEL_2WORD) ||  \
                                        ((FIFO_LEVEL) == UART_FIFO_LEVEL_4WORD) ||  \
                                        ((FIFO_LEVEL) == UART_FIFO_LEVEL_8WORD) ||  \
                                        ((FIFO_LEVEL) == UART_FIFO_LEVEL_12WORD) || \
                                        ((FIFO_LEVEL) == UART_FIFO_LEVEL_14WORD))

/**
 * @brief UART Hardware Flow Control
 */
typedef enum {
    UART_HARDWARE_FLOW_CONTROL_NONE    = ((uint32_t)0x00),               /*!< Disables RTS and CTS flow control. */
    UART_HARDWARE_FLOW_CONTROL_RTS     = UART_CR_RTSEN,                  /*!< Enables only RTS flow control. */
    UART_HARDWARE_FLOW_CONTROL_CTS     = UART_CR_CTSEN,                  /*!< Enables only CTS flow control. */
    UART_HARDWARE_FLOW_CONTROL_RTS_CTS = (UART_CR_RTSEN | UART_CR_CTSEN) /*!< Enables RTS and CTS flow control. */
} UART_HardwareFlowControl_TypeDef;

#define IS_UART_HARDWARE_FLOW_CONTROL(CONTROL) (((CONTROL) == UART_HARDWARE_FLOW_CONTROL_NONE) || \
                                                ((CONTROL) == UART_HARDWARE_FLOW_CONTROL_RTS) ||  \
                                                ((CONTROL) == UART_HARDWARE_FLOW_CONTROL_CTS) ||  \
                                                ((CONTROL) == UART_HARDWARE_FLOW_CONTROL_RTS_CTS))

/**
 * @brief UART Loopback Mode
 */
typedef enum {
    UART_LOOPBACK_MODE_DISABLE = (((uint32_t)0x0) << UART_CR_LBE_Pos), /*!< Disables loopback mode. */
    UART_LOOPBACK_MODE_ENABLE  = (((uint32_t)0x1) << UART_CR_LBE_Pos)  /*!< Enables loopback mode. */
} UART_LoopbackMode_TypeDef;

#define IS_UART_LOOPBACK_MODE(MODE) (((MODE) == UART_LOOPBACK_MODE_DISABLE) || \
                                     ((MODE) == UART_LOOPBACK_MODE_ENABLE))

/**
 * @brief UART Modem Control Input Lines
 */
typedef enum {
    UART_MODEM_INPUT_CTS = UART_FR_CTS, /*!< Inverted state on nUARTCTS line. */
    UART_MODEM_INPUT_DSR = UART_FR_DSR, /*!< Inverted state on nUARTDSR line. */
    UART_MODEM_INPUT_DCD = UART_FR_DCD, /*!< Inverted state on nUARTDCD line. */
    UART_MODEM_INPUT_RI  = UART_FR_RI   /*!< Inverted state on nUARTRI line. */
} UART_ModemInput_TypeDef;

#define IS_UART_MODEM_INPUT(INPUT) (((INPUT) == UART_MODEM_INPUT_CTS) || \
                                    ((INPUT) == UART_MODEM_INPUT_DSR) || \
                                    ((INPUT) == UART_MODEM_INPUT_DCD) || \
                                    ((INPUT) == UART_MODEM_INPUT_RI))

/**
 * @brief UART Modem Control Output Lines
 */
typedef enum {
    UART_MODEM_OUTPUT_DTR  = UART_CR_DTR,  /*!< Sets the inverted value on nUARTDTR line */
    UART_MODEM_OUTPUT_RTS  = UART_CR_RTS,  /*!< Sets the inverted value on nUARTRTS line (only used if CR.RTSEn = 0). */
    UART_MODEM_OUTPUT_OUT1 = UART_CR_OUT1, /*!< Sets the inverted value on nUARTOut1 line (used only in loopback mode: nUARTDCD = nUARTOut1). */
    UART_MODEM_OUTPUT_OUT2 = UART_CR_OUT2  /*!< Sets the inverted value on nUARTOut2 line (used only in loopback mode: nUARTRI = nUARTOut2). */
} UART_ModemOutput_TypeDef;

#define IS_UART_MODEM_OUTPUT(OUTPUT) (((OUTPUT) == UART_MODEM_OUTPUT_DTR) ||  \
                                      ((OUTPUT) == UART_MODEM_OUTPUT_RTS) ||  \
                                      ((OUTPUT) == UART_MODEM_OUTPUT_OUT1) || \
                                      ((OUTPUT) == UART_MODEM_OUTPUT_OUT2))

#define IS_UART_MODEM_OUTPUTS(OUTPUTS) (((OUTPUTS) & ~(uint32_t)(UART_MODEM_OUTPUT_DTR |  \
                                                                 UART_MODEM_OUTPUT_RTS |  \
                                                                 UART_MODEM_OUTPUT_OUT1 | \
                                                                 UART_MODEM_OUTPUT_OUT2)) == 0)

/**
 * @brief UART Flags
 */
typedef enum {
    UART_FLAG_BUSY = UART_FR_BUSY, /*!< Transmitter busy. */
    UART_FLAG_RXFE = UART_FR_RXFE, /*!< Receive FIFO empty. */
    UART_FLAG_TXFF = UART_FR_TXFF, /*!< Transmit FIFO full. */
    UART_FLAG_RXFF = UART_FR_RXFF, /*!< Receive FIFO full. */
    UART_FLAG_TXFE = UART_FR_TXFE  /*!< Transmit FIFO empty. */
} UART_Flags_TypeDef;

#define IS_UART_FLAG(FLAG) (((FLAG) == UART_FLAG_BUSY) || \
                            ((FLAG) == UART_FLAG_RXFE) || \
                            ((FLAG) == UART_FLAG_TXFF) || \
                            ((FLAG) == UART_FLAG_RXFF) || \
                            ((FLAG) == UART_FLAG_TXFE))

/**
 * @brief UART Interrupt definition
 */
typedef enum {
    UART_IT_RI  = UART_IMSC_RIMIM,  /*!< Line nUARTRI change interrupt (UARTRIINTR) */
    UART_IT_CTS = UART_IMSC_CTSMIM, /*!< Line nUARTCTS change interrupt (UARTCTSINTR) */
    UART_IT_DCD = UART_IMSC_DCDMIM, /*!< Line nUARTDCD change interrupt (UARTDCDINTR) */
    UART_IT_DSR = UART_IMSC_DSRMIM, /*!< Line nUARTDSR change interrupt (UARTDSRINTR) */
    UART_IT_RX  = UART_IMSC_RXIM,   /*!< Receiver interrupt (UARTRXINTR) */
    UART_IT_TX  = UART_IMSC_TXIM,   /*!< Transmitter interrupt (UARTTXINTR) */
    UART_IT_RT  = UART_IMSC_RTIM,   /*!< Data input timeout interrupt (UARTRTINTR) */
    UART_IT_FE  = UART_IMSC_FEIM,   /*!< Frame structure error interrupt (UARTFEINTR) */
    UART_IT_PE  = UART_IMSC_PEIM,   /*!< Parity error interrupt (UARTPEINTR) */
    UART_IT_BE  = UART_IMSC_BEIM,   /*!< Line break interrupt (UARTBEINTR) */
    UART_IT_OE  = UART_IMSC_OEIM,   /*!< Buffer overflow interrupt (UARTOEINTR) */
} UART_IT_TypeDef;

#define IS_UART_CONFIG_IT(IT) (((IT) == UART_IT_RI) || ((IT) == UART_IT_CTS) ||  \
                               ((IT) == UART_IT_DCD) || ((IT) == UART_IT_DSR) || \
                               ((IT) == UART_IT_RX) || ((IT) == UART_IT_TX) ||   \
                               ((IT) == UART_IT_RT) || ((IT) == UART_IT_FE) ||   \
                               ((IT) == UART_IT_PE) || ((IT) == UART_IT_BE) ||   \
                               ((IT) == UART_IT_OE))

#define IS_UART_CONFIG_ITS(ITS) (((ITS) & ~(uint32_t)(UART_IT_RI | UART_IT_CTS |  \
                                                      UART_IT_DCD | UART_IT_DSR | \
                                                      UART_IT_RX | UART_IT_TX |   \
                                                      UART_IT_RT | UART_IT_FE |   \
                                                      UART_IT_PE | UART_IT_BE |   \
                                                      UART_IT_OE)) == 0)

#if defined(USE_MDR32F21QI)
/**
 * @brief UART DMA Control
 */
typedef enum {
    UART_DMA_REQ_RX        = UART_DMACR_RXDMAE,  /*!< Enables request to DMA from receiver. */
    UART_DMA_REQ_TX        = UART_DMACR_TXDMAE,  /*!< Enables request to DMA from transmitter. */
    UART_DMA_DIS_ON_RX_ERR = UART_DMACR_DMAONERR /*!< Enables blocking a request to DMA when a receive error is detected. */
} UART_DMA_Control_TypeDef;

#define IS_UART_DMA_CONTROL(CONTROL) (((CONTROL) & ~(uint32_t)(UART_DMA_REQ_RX | \
                                                               UART_DMA_REQ_TX | \
                                                               UART_DMA_DIS_ON_RX_ERR)) == 0)
#endif

/**
 * @brief UART IrDA Low Power
 */
typedef enum {
    UART_IRDA_MODE_NORMAL    = (((uint32_t)0x0) << UART_CR_SIRLP_Pos), /*!< Selects IrDA normal mode (uses Baud16 clock). */
    UART_IRDA_MODE_LOW_POWER = (((uint32_t)0x1) << UART_CR_SIRLP_Pos)  /*!< Selects IrDA low-power mode (uses IrLPBaud16 clock, speed = 115200 baud). */
} UART_IrDAMode_TypeDef;

#define IS_UART_IRDA_MODE(MODE) (((MODE) == UART_IRDA_MODE_NORMAL) || \
                                 ((MODE) == UART_IRDA_MODE_LOW_POWER))

/**
 * @brief  UART Init Structure definition
 */
typedef struct
{
    uint32_t UART_BaudRate;                                    /*!< This member configures the UART communication baud rate.
                                                                    The baud rate is computed using the following formula:
                                                                    - IntegerDivider = ((UARTCLK) / (16 * (UART_BaudRate)))
                                                                    - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 64) + 0.5 */
    UART_Mode_TypeDef UART_Mode;                               /*!< Specifies the permission of the transmitter and receiver.
                                                                    This parameter can be a value of @ref UART_Mode_TypeDef */
    UART_WordLength_TypeDef UART_WordLength;                   /*!< Specifies the number of data bits transmitted or received in a frame.
                                                                    This parameter can be a value of @ref UART_WordLength_TypeDef */
    UART_StopBits_TypeDef UART_StopBits;                       /*!< Specifies the number of stop bits transmitted.
                                                                    This parameter can be a value of @ref UART_StopBits_TypeDef */
    UART_Parity_TypeDef UART_Parity;                           /*!< Specifies the parity mode.
                                                                    This parameter can be a value of @ref UART_Parity_TypeDef */
    UART_FIFO_State_TypeDef UART_FIFO_State;                   /*!< Enables or disables the FIFO buffers.
                                                                    This parameter can be a value of @ref UART_FIFO_State_TypeDef */
    UART_FIFO_Level_TypeDef UART_FIFO_TxLevel;                 /*!< Specifies the fill level of the TX FIFO for generating events. Only used if FIFO is enabled.
                                                                    This parameter can be a value of @ref UART_FIFO_Level_TypeDef */
    UART_FIFO_Level_TypeDef UART_FIFO_RxLevel;                 /*!< Specifies the fill level of the RX FIFO for generating events. Only used if FIFO is enabled.
                                                                    This parameter can be a value of @ref UART_FIFO_Level_TypeDef */
    UART_HardwareFlowControl_TypeDef UART_HardwareFlowControl; /*!< Specifies the hardware flow control mode.
                                                                    This parameter can be a value of @ref UART_HardwareFlowControl_TypeDef */
    UART_LoopbackMode_TypeDef UART_LoopbackMode;               /*!< Enables or disables the loopback mode.
                                                                    This parameter can be a value of @ref UART_LoopbackMode_TypeDef */
} UART_InitTypeDef;

/** @} */ /* End of group UART_Exported_Types */

/** @defgroup UART_Exported_Defines UART Exported Defines
 * @{
 */

/** @defgroup UART_Baudrate UART Baudrate
 * @{
 */

#define IS_UART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) <= 921600))

/** @} */ /* End of group UART_Baudrate */

/** @defgroup UART_Data_Status UART Data Status
 * @{
 */

#define UART_DATA_OE                      UART_DR_OE
#define UART_DATA_BE                      UART_DR_BE
#define UART_DATA_PE                      UART_DR_PE
#define UART_DATA_FE                      UART_DR_FE

#define UART_DATA(DATA)                   ((uint8_t)(DATA))
#define UART_FLAGS(DATA)                  ((uint8_t)((DATA) >> 8))
#define UART_CHECK_DATA_STATUS(DATA, BIT) ((((uint32_t)(DATA)) << (31 - (BIT))) >> 31)

/** @} */ /* End of group UART_Data_Status */

/** @} */ /* End of group UART_Exported_Defines */

/** @addtogroup UART_Exported_Functions UART Exported Functions
 * @{
 */

void        UART_DeInit(MDR_UART_TypeDef* UARTx);
ErrorStatus UART_Init(MDR_UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void        UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void        UART_Cmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState);

void UART_IrDAConfig(MDR_UART_TypeDef* UARTx, UART_IrDAMode_TypeDef IrDAMode);
void UART_IrDACmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState);

void UART_FIFOFillLevelConfig(MDR_UART_TypeDef* UARTx, UART_FIFO_Level_TypeDef RxLevel, UART_FIFO_Level_TypeDef TxLevel);

void     UART_SendData(MDR_UART_TypeDef* UARTx, uint8_t Data);
uint16_t UART_ReceiveData(MDR_UART_TypeDef* UARTx);
void     UART_BreakLine(MDR_UART_TypeDef* UARTx, FunctionalState NewState);

FlagStatus UART_GetFlagStatus(MDR_UART_TypeDef* UARTx, UART_Flags_TypeDef Flag);
uint32_t   UART_GetStatus(MDR_UART_TypeDef* UARTx);

void     UART_ITConfig(MDR_UART_TypeDef* UARTx, uint32_t ITs, FunctionalState NewState);
ITStatus UART_GetITFlagStatus(MDR_UART_TypeDef* UARTx, UART_IT_TypeDef IT);
uint32_t UART_GetITStatus(MDR_UART_TypeDef* UARTx);
ITStatus UART_GetITNonMaskedFlagStatus(MDR_UART_TypeDef* UARTx, UART_IT_TypeDef IT);
uint32_t UART_GetITNonMaskedStatus(MDR_UART_TypeDef* UARTx);
void     UART_ClearITFlags(MDR_UART_TypeDef* UARTx, uint32_t ITs);

#if defined(USE_MDR32F21QI)
void UART_DMACmd(MDR_UART_TypeDef* UARTx, uint32_t DMAReqs, FunctionalState NewState);
#endif

FlagStatus UART_GetModemInput(MDR_UART_TypeDef* UARTx, UART_ModemInput_TypeDef Input);
uint32_t   UART_GetModemInputs(MDR_UART_TypeDef* UARTx);

void       UART_SetModemOutputs(MDR_UART_TypeDef* UARTx, uint32_t Outputs);
void       UART_ClearModemOutputs(MDR_UART_TypeDef* UARTx, uint32_t Outputs);
FlagStatus UART_GetModemOutput(MDR_UART_TypeDef* UARTx, UART_ModemOutput_TypeDef Output);
uint32_t   UART_GetModemOutputs(MDR_UART_TypeDef* UARTx);

/** @} */ /* End of group UART_Exported_Functions */

/** @} */ /* End of group UART */

/** @} */ /* End of group MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_UART_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_uart.h */

