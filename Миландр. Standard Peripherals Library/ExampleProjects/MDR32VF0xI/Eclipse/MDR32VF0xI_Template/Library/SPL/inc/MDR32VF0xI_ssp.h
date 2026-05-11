/**
 *******************************************************************************
 * @file    MDR32VF0xI_ssp.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    18/04/2024
 * @brief   This file contains all the functions prototypes for the SSP
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
#ifndef MDR32VF0xI_SSP_H
#define MDR32VF0xI_SSP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup SSP SSP
 * @{
 */

/** @defgroup SSP_Exported_Types SSP Exported Types
 * @{
 */

/**
 * @brief SSP mode.
 */
typedef enum {
    SSP_MODE_MASTER = (((uint32_t)0x0) << SSP_CR1_MS_Pos), /*!< Specify the SSP master mode. */
    SSP_MODE_SLAVE  = (((uint32_t)0x1) << SSP_CR1_MS_Pos)  /*!< Specify the SSP slave mode. */
} SSP_Mode_TypeDef;

#define IS_SSP_MODE(MODE) (((MODE) == SSP_MODE_MASTER) || \
                           ((MODE) == SSP_MODE_SLAVE))

/**
 * @brief SSP word length.
 */
typedef enum {
    SSP_WORD_LENGTH_4BIT  = SSP_CR0_DSS_4BIT,  /*!< Select a 4-bit data size. */
    SSP_WORD_LENGTH_5BIT  = SSP_CR0_DSS_5BIT,  /*!< Select a 5-bit data size. */
    SSP_WORD_LENGTH_6BIT  = SSP_CR0_DSS_6BIT,  /*!< Select a 6-bit data size. */
    SSP_WORD_LENGTH_7BIT  = SSP_CR0_DSS_7BIT,  /*!< Select a 7-bit data size. */
    SSP_WORD_LENGTH_8BIT  = SSP_CR0_DSS_8BIT,  /*!< Select a 8-bit data size. */
    SSP_WORD_LENGTH_9BIT  = SSP_CR0_DSS_9BIT,  /*!< Select a 9-bit data size. */
    SSP_WORD_LENGTH_10BIT = SSP_CR0_DSS_10BIT, /*!< Select a 10-bit data size. */
    SSP_WORD_LENGTH_11BIT = SSP_CR0_DSS_11BIT, /*!< Select a 11-bit data size. */
    SSP_WORD_LENGTH_12BIT = SSP_CR0_DSS_12BIT, /*!< Select a 12-bit data size. */
    SSP_WORD_LENGTH_13BIT = SSP_CR0_DSS_13BIT, /*!< Select a 13-bit data size. */
    SSP_WORD_LENGTH_14BIT = SSP_CR0_DSS_14BIT, /*!< Select a 14-bit data size. */
    SSP_WORD_LENGTH_15BIT = SSP_CR0_DSS_15BIT, /*!< Select a 15-bit data size. */
    SSP_WORD_LENGTH_16BIT = SSP_CR0_DSS_16BIT, /*!< Select a 16-bit data size. */
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    SSP_WORD_LENGTH_17BIT = SSP_CR0_DSS_17BIT, /*!< Select a 17-bit data size. */
    SSP_WORD_LENGTH_18BIT = SSP_CR0_DSS_18BIT, /*!< Select a 18-bit data size. */
    SSP_WORD_LENGTH_19BIT = SSP_CR0_DSS_19BIT, /*!< Select a 19-bit data size. */
    SSP_WORD_LENGTH_20BIT = SSP_CR0_DSS_20BIT, /*!< Select a 20-bit data size. */
    SSP_WORD_LENGTH_21BIT = SSP_CR0_DSS_21BIT, /*!< Select a 21-bit data size. */
    SSP_WORD_LENGTH_22BIT = SSP_CR0_DSS_22BIT, /*!< Select a 22-bit data size. */
    SSP_WORD_LENGTH_23BIT = SSP_CR0_DSS_23BIT, /*!< Select a 23-bit data size. */
    SSP_WORD_LENGTH_24BIT = SSP_CR0_DSS_24BIT, /*!< Select a 24-bit data size. */
    SSP_WORD_LENGTH_25BIT = SSP_CR0_DSS_25BIT, /*!< Select a 25-bit data size. */
    SSP_WORD_LENGTH_26BIT = SSP_CR0_DSS_26BIT, /*!< Select a 26-bit data size. */
    SSP_WORD_LENGTH_27BIT = SSP_CR0_DSS_27BIT, /*!< Select a 27-bit data size. */
    SSP_WORD_LENGTH_28BIT = SSP_CR0_DSS_28BIT, /*!< Select a 28-bit data size. */
    SSP_WORD_LENGTH_29BIT = SSP_CR0_DSS_29BIT, /*!< Select a 29-bit data size. */
    SSP_WORD_LENGTH_30BIT = SSP_CR0_DSS_30BIT, /*!< Select a 30-bit data size. */
    SSP_WORD_LENGTH_31BIT = SSP_CR0_DSS_31BIT, /*!< Select a 31-bit data size. */
    SSP_WORD_LENGTH_32BIT = SSP_CR0_DSS_32BIT  /*!< Select a 32-bit data size. */
#endif
} SSP_WordLength_TypeDef;

#if defined(USE_MDR32F02_REV_1X)
#define IS_SSP_WORD_LENGTH(LENGTH) (((LENGTH) == SSP_WORD_LENGTH_4BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_5BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_6BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_7BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_8BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_9BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_10BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_11BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_12BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_13BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_14BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_15BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_16BIT))
#elif defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define IS_SSP_WORD_LENGTH(LENGTH) (((LENGTH) == SSP_WORD_LENGTH_4BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_5BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_6BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_7BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_8BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_9BIT) ||  \
                                    ((LENGTH) == SSP_WORD_LENGTH_10BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_11BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_12BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_13BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_14BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_15BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_16BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_17BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_18BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_19BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_20BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_21BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_22BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_23BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_24BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_25BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_26BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_27BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_28BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_29BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_30BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_31BIT) || \
                                    ((LENGTH) == SSP_WORD_LENGTH_32BIT))
#endif

/**
 * @brief SSP clock phase (SPH).
 */
typedef enum {
    SSP_CLOCK_PHASE_1EDGE = (((uint32_t)0x0) << SSP_CR0_SPH_Pos), /*!< Select the data sampling on the 1st edge of SSP_CLK. */
    SSP_CLOCK_PHASE_2EDGE = (((uint32_t)0x1) << SSP_CR0_SPH_Pos)  /*!< Select the data sampling on the 2nd edge of SSP_CLK. */
} SSP_ClockPhase_TypeDef;

#define IS_SSP_CLOCK_PHASE(PHASE) (((PHASE) == SSP_CLOCK_PHASE_1EDGE) || \
                                   ((PHASE) == SSP_CLOCK_PHASE_2EDGE))

/**
 * @brief SSP clock polarity (SPO).
 */
typedef enum {
    SSP_CLOCK_POLARITY_LOW  = (((uint32_t)0x0) << SSP_CR0_SPO_Pos), /*!< Select the low level for the initial state of SSP_CLK. */
    SSP_CLOCK_POLARITY_HIGH = (((uint32_t)0x1) << SSP_CR0_SPO_Pos)  /*!< Select the high level for the initial state of SSP_CLK. */
} SSP_ClockPolarity_TypeDef;

#define IS_SSP_CLOCK_POLARITY(STATE) (((STATE) == SSP_CLOCK_POLARITY_LOW) || \
                                      ((STATE) == SSP_CLOCK_POLARITY_HIGH))

/**
 * @brief SSP frame format (FRF).
 */
typedef enum {
    SSP_FRAME_FORMAT_SPI       = SSP_CR0_FRF_SPI,      /*!< Select the Motorola SPI frame format. */
    SSP_FRAME_FORMAT_SSI       = SSP_CR0_FRF_SSI,      /*!< Select the TI SSI frame format. */
    SSP_FRAME_FORMAT_MICROWIRE = SSP_CR0_FRF_MICROWIRE /*!< Select the National Semiconductor Microwire frame format. */
} SSP_FrameFormat_TypeDef;

#define IS_SSP_FRAME_FORMAT(FORMAT) (((FORMAT) == SSP_FRAME_FORMAT_SPI) || \
                                     ((FORMAT) == SSP_FRAME_FORMAT_SSI) || \
                                     ((FORMAT) == SSP_FRAME_FORMAT_MICROWIRE))

/**
 * @brief SSP status flags.
 */
typedef enum {
    SSP_FLAG_TFE = SSP_SR_TFE, /*!< Transmit FIFO is empty. */
    SSP_FLAG_TNF = SSP_SR_TNF, /*!< Transmit FIFO is not full. */
    SSP_FLAG_RNE = SSP_SR_RNE, /*!< Receive FIFO is not empty. */
    SSP_FLAG_RFF = SSP_SR_RFF, /*!< Receive FIFO is full. */
    SSP_FLAG_BSY = SSP_SR_BSY  /*!< SSP is busy. */
} SSP_Flags_TypeDef;

#define IS_SSP_FLAG(FLAG) (((FLAG) == SSP_FLAG_TFE) || \
                           ((FLAG) == SSP_FLAG_TNF) || \
                           ((FLAG) == SSP_FLAG_RNE) || \
                           ((FLAG) == SSP_FLAG_RFF) || \
                           ((FLAG) == SSP_FLAG_BSY))

/**
 * @brief SSP interrupt definition.
 */
typedef enum {
    SSP_IT_ROR = SSP_IMSC_RORIM, /*!< Receive FIFO is overrun. */
    SSP_IT_RT  = SSP_IMSC_RTIM,  /*!< Receive timeout. */
    SSP_IT_RX  = SSP_IMSC_RXIM,  /*!< Receive FIFO is half or more full. */
    SSP_IT_TX  = SSP_IMSC_TXIM,  /*!< Transmit FIFO is half or less empty. */
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    SSP_IT_RNE   = SSP_IMSC_RNEIM,   /*!< Receive FIFO is not empty. */
    SSP_IT_TFE   = SSP_IMSC_TFEIM,   /*!< Transmit FIFO is empty. */
    SSP_IT_TNBSY = SSP_IMSC_TNBSYIM, /*!< Transmit shift register is empty. */
#endif
} SSP_IT_TypeDef;

#if defined(USE_MDR32F02_REV_1X)
#define IS_SSP_CONFIG_IT(IT) (((IT) == SSP_IT_ROR) || \
                              ((IT) == SSP_IT_RT) ||  \
                              ((IT) == SSP_IT_RX) ||  \
                              ((IT) == SSP_IT_TX))

#define IS_SSP_CONFIG_ITS(ITS) (((ITS) & ~(uint32_t)(SSP_IT_ROR | \
                                                     SSP_IT_RT |  \
                                                     SSP_IT_RX |  \
                                                     SSP_IT_TX)) == 0)
#elif defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define IS_SSP_CONFIG_IT(IT) (((IT) == SSP_IT_ROR) || \
                              ((IT) == SSP_IT_RT) ||  \
                              ((IT) == SSP_IT_RX) ||  \
                              ((IT) == SSP_IT_TX) ||  \
                              ((IT) == SSP_IT_RNE) || \
                              ((IT) == SSP_IT_TFE) || \
                              ((IT) == SSP_IT_TNBSY))

#define IS_SSP_CONFIG_ITS(ITS) (((ITS) & ~(uint32_t)(SSP_IT_ROR | \
                                                     SSP_IT_RT |  \
                                                     SSP_IT_RX |  \
                                                     SSP_IT_TX |  \
                                                     SSP_IT_RNE | \
                                                     SSP_IT_TFE | \
                                                     SSP_IT_TNBSY)) == 0)
#endif

#define IS_SSP_RESET_ITS(ITS) (((ITS) & ~(uint32_t)(SSP_IT_ROR | \
                                                    SSP_IT_RT)) == 0)

/**
 * @brief SSP DMA request.
 */
typedef enum {
    SSP_DMA_REQ_RX = SSP_DMACR_RXDMAE, /*!< Enable the request from the receiver to the DMA. */
    SSP_DMA_REQ_TX = SSP_DMACR_TXDMAE  /*!< Enable the request form the transmitter to the DMA. */
} SSP_DMA_Reqs_TypeDef;

#define IS_SSP_DMA_REQ(REQ) (((REQ) == SSP_DMA_REQ_RX) || \
                             ((REQ) == SSP_DMA_REQ_TX))

#define IS_SSP_DMA_REQS(REQS) (((REQS) & ~(uint32_t)(SSP_DMA_REQ_RX | \
                                                     SSP_DMA_REQ_TX)) == 0)

/**
 * @brief  SSP init structure definition.
 */
typedef struct {
    uint8_t SSP_CPSDVSR;                         /*!< This member configures the SSP clock divider.
                                                      This parameter is an even number from 2 to 254. */
    uint8_t SSP_SCR;                             /*!< This member configures the SSP communication speed.
                                                      This parameter is a number from 0 to 255.
                                                      The information rate is computed using the following formula:
                                                      SSPCLK / (SSP_CPSDVSR * (1 + SSP_SCR)). */
    SSP_Mode_TypeDef SSP_Mode;                   /*!< Specify the SSP operation mode (master or slave).
                                                      This parameter can be a value of the @ref SSP_Mode_TypeDef. */
    SSP_WordLength_TypeDef SSP_WordLength;       /*!< Specify the number of data bits transmitted or received in a frame.
                                                      This parameter can be a value of the @ref SSP_WordLength_TypeDef. */
    SSP_ClockPhase_TypeDef SSP_ClockPhase;       /*!< Specify the phase of SSP_CLK (data sampling on edge the 1st or 2nd).
                                                      This parameter can be a value of the @ref SSP_ClockPhase_TypeDef. */
    SSP_ClockPolarity_TypeDef SSP_ClockPolarity; /*!< Specify the polarity of SSP_CLK (the initial state is low or high).
                                                      This parameter is one of the @ref SSP_ClockPolarity_TypeDef. */
    SSP_FrameFormat_TypeDef SSP_FrameFormat;     /*!< Specify the frame format (SPI, SSI, MICROWIRE).
                                                      This parameter can be a value of the @ref SSP_FrameFormat_TypeDef. */
    FunctionalState SSP_SlaveModeOutput;         /*!< Enable or disable the SSP_TXD output in the slave mode.
                                                      This parameter can be a value of the @ref FunctionalState. */
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    FunctionalState SSP_FastSPISlave; /*!< Enable or disable fast SPI slave mode and SSP_RXD synchronization.
                                           This parameter can be a value of the @ref FunctionalState. */
#endif
    FunctionalState SSP_LoopbackMode; /*!< Enable or disable the loopback mode.
                                           This parameter can be a value of the @ref FunctionalState. */
} SSP_InitTypeDef;

/** @} */ /* End of the group SSP_Exported_Types */

/** @defgroup SSP_Exported_Defines SSP Exported Defines
 * @{
 */

#define IS_SSP_SPEED_FACTOR(DIV)  (((DIV) & ~(SSP_CR0_SCR_Msk >> SSP_CR0_SCR_Pos)) == 0)

#define IS_SSP_SPEED_DIVIDER(DIV) (((DIV) & ~(SSP_CPSR_CPSDVSR_Msk & (uint32_t)0xFE)) == 0)

/** @} */ /* End of the group SSP_Exported_Defines */

/** @addtogroup SSP_Exported_Functions SSP Exported Functions
 * @{
 */

void SSP_DeInit(MDR_SSP_TypeDef* SSPx);

void SSP_Init(MDR_SSP_TypeDef* SSPx, const SSP_InitTypeDef* SSP_InitStruct);
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct);

void            SSP_Cmd(MDR_SSP_TypeDef* SSPx, FunctionalState NewState);
FunctionalState SSP_GetCmdState(MDR_SSP_TypeDef* SSPx);

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void     SSP_SendData(MDR_SSP_TypeDef* SSPx, uint32_t Data);
uint32_t SSP_ReceiveData(MDR_SSP_TypeDef* SSPx);
#else
void     SSP_SendData(MDR_SSP_TypeDef* SSPx, uint16_t Data);
uint16_t SSP_ReceiveData(MDR_SSP_TypeDef* SSPx);
#endif

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void SSP_TransmitterFIFOClear(MDR_SSP_TypeDef* SSPx);
#endif

FlagStatus SSP_GetFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_Flags_TypeDef Flag);
uint32_t   SSP_GetStatus(MDR_SSP_TypeDef* SSPx);

void     SSP_ITConfig(MDR_SSP_TypeDef* SSPx, uint32_t ITs, FunctionalState NewState);
ITStatus SSP_GetITFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_IT_TypeDef IT);
uint32_t SSP_GetITStatus(MDR_SSP_TypeDef* SSPx);
ITStatus SSP_GetITNonMaskedFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_IT_TypeDef IT);
uint32_t SSP_GetITNonMaskedStatus(MDR_SSP_TypeDef* SSPx);
void     SSP_ClearITFlags(MDR_SSP_TypeDef* SSPx, uint32_t ITs);

void SSP_SlaveOutputConfig(MDR_SSP_TypeDef* SSPx, FunctionalState NewState);

void            SSP_DMACmd(MDR_SSP_TypeDef* SSPx, uint32_t DMAReqs, FunctionalState NewState);
FunctionalState SSP_GetDMACmdState(MDR_SSP_TypeDef* SSPx, SSP_DMA_Reqs_TypeDef DMAReq);

/** @} */ /* End of the group SSP_Exported_Functions */

/** @} */ /* End of the group SSP */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_SSP_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_ssp.h */

