/**
 *******************************************************************************
 * @file    MDR32F2xQI_ssp.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    26/04/2023
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
#ifndef __MDR32F2xQI_SSP_H
#define __MDR32F2xQI_SSP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup SSP SSP
 * @{
 */

/** @defgroup SSP_Exported_Types SSP Exported Types
 * @{
 */

/**
 * @brief SSP Mode
 */
typedef enum {
    SSP_MODE_MASTER = (((uint32_t)0x0) << SSP_CR1_MS_Pos), /*!< Specifies the SSP master mode. */
    SSP_MODE_SLAVE  = (((uint32_t)0x1) << SSP_CR1_MS_Pos)  /*!< Specifies the SSP slave mode. */
} SSP_Mode_TypeDef;

#define IS_SSP_MODE(MODE) (((MODE) == SSP_MODE_MASTER) || \
                           ((MODE) == SSP_MODE_SLAVE))

/**
 * @brief SSP Word Length
 */
typedef enum {
    SSP_WORD_LENGTH_4BIT  = SSP_CR0_DSS_4BIT,  /*!< Selects a 4-bit data size. */
    SSP_WORD_LENGTH_5BIT  = SSP_CR0_DSS_5BIT,  /*!< Selects a 5-bit data size. */
    SSP_WORD_LENGTH_6BIT  = SSP_CR0_DSS_6BIT,  /*!< Selects a 6-bit data size. */
    SSP_WORD_LENGTH_7BIT  = SSP_CR0_DSS_7BIT,  /*!< Selects a 7-bit data size. */
    SSP_WORD_LENGTH_8BIT  = SSP_CR0_DSS_8BIT,  /*!< Selects a 8-bit data size. */
    SSP_WORD_LENGTH_9BIT  = SSP_CR0_DSS_9BIT,  /*!< Selects a 9-bit data size. */
    SSP_WORD_LENGTH_10BIT = SSP_CR0_DSS_10BIT, /*!< Selects a 10-bit data size. */
    SSP_WORD_LENGTH_11BIT = SSP_CR0_DSS_11BIT, /*!< Selects a 11-bit data size. */
    SSP_WORD_LENGTH_12BIT = SSP_CR0_DSS_12BIT, /*!< Selects a 12-bit data size. */
    SSP_WORD_LENGTH_13BIT = SSP_CR0_DSS_13BIT, /*!< Selects a 13-bit data size. */
    SSP_WORD_LENGTH_14BIT = SSP_CR0_DSS_14BIT, /*!< Selects a 14-bit data size. */
    SSP_WORD_LENGTH_15BIT = SSP_CR0_DSS_15BIT, /*!< Selects a 15-bit data size. */
    SSP_WORD_LENGTH_16BIT = SSP_CR0_DSS_16BIT  /*!< Selects a 16-bit data size. */
} SSP_WordLength_TypeDef;

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

/**
 * @brief SSP Clock Phase (SPH)
 */
typedef enum {
    SSP_CLOCK_PHASE_1EDGE = (((uint32_t)0x0) << SSP_CR0_SPH_Pos), /*!< Selects data sampling on 1 edge of SSP_CLK. */
    SSP_CLOCK_PHASE_2EDGE = (((uint32_t)0x1) << SSP_CR0_SPH_Pos)  /*!< Selects data sampling on 2 edge of SSP_CLK. */
} SSP_ClockPhase_TypeDef;

#define IS_SSP_CLOCK_PHASE(PHASE) (((PHASE) == SSP_CLOCK_PHASE_1EDGE) || \
                                   ((PHASE) == SSP_CLOCK_PHASE_2EDGE))

/**
 * @brief SSP Clock Polarity (SPO)
 */
typedef enum {
    SSP_CLOCK_POLARITY_LOW  = (((uint32_t)0x0) << SSP_CR0_SPO_Pos), /*!< Selects a low level for the initial state of SSP_CLK. */
    SSP_CLOCK_POLARITY_HIGH = (((uint32_t)0x1) << SSP_CR0_SPO_Pos)  /*!< Selects a high level for the initial state of SSP_CLK. */
} SSP_ClockPolarity_TypeDef;

#define IS_SSP_CLOCK_POLARITY(STATE) (((STATE) == SSP_CLOCK_POLARITY_LOW) || \
                                      ((STATE) == SSP_CLOCK_POLARITY_HIGH))

/**
 * @brief SSP Frame Format (FRF)
 */
typedef enum {
    SSP_FRAME_FORMAT_SPI       = SSP_CR0_FRF_SPI,      /*!< Selects the Motorola SPI frame format. */
    SSP_FRAME_FORMAT_SSI       = SSP_CR0_FRF_SSI,      /*!< Selects the TI SSI frame format. */
    SSP_FRAME_FORMAT_MICROWIRE = SSP_CR0_FRF_MICROWIRE /*!< Selects the National Semiconductor Microwire frame format. */
} SSP_FrameFormat_TypeDef;

#define IS_SSP_FRAME_FORMAT(FORMAT) (((FORMAT) == SSP_FRAME_FORMAT_SPI) || \
                                     ((FORMAT) == SSP_FRAME_FORMAT_SSI) || \
                                     ((FORMAT) == SSP_FRAME_FORMAT_MICROWIRE))

/**
 * @brief SSP Slave-mode Output
 */
typedef enum {
    SSP_SLAVE_MODE_OUTPUT_ENABLE  = (((uint32_t)0x0) << SSP_CR1_SOD_Pos), /*!< Enables SSP_TXD output in slave mode. */
    SSP_SLAVE_MODE_OUTPUT_DISABLE = (((uint32_t)0x1) << SSP_CR1_SOD_Pos)  /*!< Disables SSP_TXD output in slave mode. */
} SSP_SlaveModeOutput_TypeDef;

#define IS_SSP_SLAVE_MODE_OUTPUT_CONFIG(CONFIG) (((CONFIG) == SSP_SLAVE_MODE_OUTPUT_ENABLE) || \
                                                 ((CONFIG) == SSP_SLAVE_MODE_OUTPUT_DISABLE))

/**
 * @brief SSP Loopback Mode
 */
typedef enum {
    SSP_LOOPBACK_MODE_DISABLE = (((uint32_t)0x0) << SSP_CR1_LBM_Pos), /*!< Disables loopback mode. */
    SSP_LOOPBACK_MODE_ENABLE  = (((uint32_t)0x1) << SSP_CR1_LBM_Pos)  /*!< Enables loopback mode. */
} SSP_LoopbackMode_TypeDef;

#define IS_SSP_LOOPBACK_MODE(MODE) (((MODE) == SSP_LOOPBACK_MODE_DISABLE) || \
                                    ((MODE) == SSP_LOOPBACK_MODE_ENABLE))

/**
 * @brief SSP SSP Flags
 */
typedef enum {
    SSP_FLAG_TFE = SSP_SR_TFE, /*!< Transmit FIFO empty. */
    SSP_FLAG_TNF = SSP_SR_TNF, /*!< Transmit FIFO not full. */
    SSP_FLAG_RNE = SSP_SR_RNE, /*!< Receive FIFO not empty. */
    SSP_FLAG_RFF = SSP_SR_RFF, /*!< Receive FIFO full. */
    SSP_FLAG_BSY = SSP_SR_BSY  /*!< SSP busy. */
} SSP_Flags_TypeDef;

#define IS_SSP_FLAG(FLAG) (((FLAG) == SSP_FLAG_TFE) || \
                           ((FLAG) == SSP_FLAG_TNF) || \
                           ((FLAG) == SSP_FLAG_RNE) || \
                           ((FLAG) == SSP_FLAG_RFF) || \
                           ((FLAG) == SSP_FLAG_BSY))

/**
 * @brief SSP SSP Interrupt definition
 */
typedef enum {
    SSP_IT_ROR = SSP_IMSC_RORIM, /*!< Receive FIFO overrun. */
    SSP_IT_RT  = SSP_IMSC_RTIM,  /*!< Receive timeout. */
    SSP_IT_RX  = SSP_IMSC_RXIM,  /*!< Receive FIFO half full or more. */
    SSP_IT_TX  = SSP_IMSC_TXIM,  /*!< Transmit FIFO half empty or less. */
} SSP_IT_TypeDef;

#define IS_SSP_CONFIG_IT(IT) (((IT) == SSP_IT_ROR) || \
                              ((IT) == SSP_IT_RT) ||  \
                              ((IT) == SSP_IT_RX) ||  \
                              ((IT) == SSP_IT_TX))

#define IS_SSP_CONFIG_ITS(ITS) (((ITS) & ~(uint32_t)(SSP_IT_ROR | \
                                                     SSP_IT_RT |  \
                                                     SSP_IT_RX |  \
                                                     SSP_IT_TX)) == 0)

#define IS_SSP_RESET_ITS(ITS) (((ITS) & ~(uint32_t)(SSP_IT_ROR | \
                                                    SSP_IT_RT)) == 0)

#if defined(USE_MDR32F21QI)
/**
 * @brief SSP DMA request
 */
typedef enum {
    SSP_DMA_REQ_RX = SSP_DMACR_RXDMAE, /*!< Enables request to DMA from receiver. */
    SSP_DMA_REQ_TX = SSP_DMACR_TXDMAE  /*!< Enables request to DMA from transmitter. */
} SSP_DMA_Reqs_TypeDef;

#define IS_SSP_DMA_REQS(REQS) (((REQS) & ~(uint32_t)(SSP_DMA_REQ_RX | \
                                                     SSP_DMA_REQ_TX)) == 0)
#endif

/**
 * @brief  SSP Init structure definition
 */
typedef struct
{
    uint8_t SSP_CPSDVSR;                             /*!< This member configures the SSP clock divider.
                                                          This parameter is an even number from 2 to 254 */
    uint8_t SSP_SCR;                                 /*!< This member configures the SSP communication speed.
                                                          This parameter is number from 0 to 255.
                                                          The information rate is computed using the following formula:
                                                          SSPCLK / (SSP_CPSDVSR * (1 + SSP_SCR)) */
    SSP_Mode_TypeDef SSP_Mode;                       /*!< Specifies the SSP operation mode (master or slave).
                                                          This parameter can be a value of @ref SSP_Mode_TypeDef */
    SSP_WordLength_TypeDef SSP_WordLength;           /*!< Specifies the number of data bits transmitted or received in a frame.
                                                          This parameter can be a value of @ref SSP_WordLength_TypeDef */
    SSP_ClockPhase_TypeDef SSP_ClockPhase;           /*!< Specifies the phase of SSP_CLK (data sampling on edge 1 or 2).
                                                          This parameter can be a value of @ref SSP_ClockPhase_TypeDef */
    SSP_ClockPolarity_TypeDef SSP_ClockPolarity;     /*!< Specifies the polarity of SSP_CLK (initial state is low or high).
                                                          This parameter is one of @ref SSP_ClockPolarity_TypeDef */
    SSP_FrameFormat_TypeDef SSP_FrameFormat;         /*!< Specifies the frame format (SPI, SSI, MICROWIRE).
                                                          This parameter can be a value of @ref SSP_FrameFormat_TypeDef */
    SSP_SlaveModeOutput_TypeDef SSP_SlaveModeOutput; /*!< Enables or disables the SSP_TXD output in slave mode.
                                                          This parameter can be a value of @ref SSP_SlaveModeOutput_TypeDef */
    SSP_LoopbackMode_TypeDef SSP_LoopbackMode;       /*!< Enables or disables the loopback mode.
                                                          This parameter can be a value of @ref SSP_LoopbackMode_TypeDef */
} SSP_InitTypeDef;

/** @} */ /* End of group SSP_Exported_Types */

/** @defgroup SSP_Exported_Defines SSP Exported Defines
 * @{
 */

#define IS_SSP_SPEED_FACTOR(DIVIDER)  (((DIVIDER) & ~(SSP_CR0_SCR_Msk >> SSP_CR0_SCR_Pos)) == 0)

#define IS_SSP_SPEED_DIVIDER(DIVIDER) (((DIVIDER) & ~(SSP_CPSR_CPSDVSR_Msk & 0xFEUL)) == 0)

/** @} */ /* End of group SSP_Exported_Defines */

/** @addtogroup SSP_Exported_Functions SSP Exported Functions
 * @{
 */

void SSP_DeInit(void);

void SSP_Init(const SSP_InitTypeDef* SSP_InitStruct);
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct);

void SSP_Cmd(FunctionalState NewState);

void     SSP_SendData(uint16_t Data);
uint16_t SSP_ReceiveData(void);

FlagStatus SSP_GetFlagStatus(SSP_Flags_TypeDef Flag);
uint32_t   SSP_GetStatus(void);

void     SSP_ITConfig(uint32_t ITs, FunctionalState NewState);
ITStatus SSP_GetITFlagStatus(SSP_IT_TypeDef IT);
uint32_t SSP_GetITStatus(void);
ITStatus SSP_GetITNonMaskedFlagStatus(SSP_IT_TypeDef IT);
uint32_t SSP_GetITNonMaskedStatus(void);
void     SSP_ClearITFlags(uint32_t ITs);

void SSP_SlaveOutputConfig(FunctionalState NewState);

#if defined(USE_MDR32F21QI)
void SSP_DMACmd(uint32_t DMAReqs, FunctionalState NewState);
#endif

/** @} */ /* End of group SSP_Exported_Functions */

/** @} */ /* End of group SSP */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_SSP_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_ssp.h */

