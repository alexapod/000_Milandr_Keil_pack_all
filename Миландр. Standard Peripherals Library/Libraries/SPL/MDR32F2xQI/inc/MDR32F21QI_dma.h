/**
 *******************************************************************************
 * @file    MDR32F21QI_dma.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
 * @brief   This file contains all the functions prototypes for the DMA
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
#ifndef __MDR32F21QI_DMA_H
#define __MDR32F21QI_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F21QI_StdPeriph_Driver MDR32F21QI Standard Peripherial Driver
 * @{
 */

#if defined(USE_MDR32F21QI)

/** @addtogroup DMA
 * @{
 */

/** @defgroup DMA_Exported_Types DMA Exported Types
 * @{
 */

/**
 * @brief DMA valid channels
 */
typedef enum {
    DMA_CHANNEL_UART0_TX = ((uint8_t)(0)),  /*!< UART0 TX channel. */
    DMA_CHANNEL_UART0_RX = ((uint8_t)(1)),  /*!< UAART0 RX channel. */
    DMA_CHANNEL_UART1_TX = ((uint8_t)(2)),  /*!< UART1 TX channel. */
    DMA_CHANNEL_UART1_RX = ((uint8_t)(3)),  /*!< UART1 RX channel. */
    DMA_CHANNEL_SSP_TX   = ((uint8_t)(4)),  /*!< SSP TX channel. */
    DMA_CHANNEL_SSP_RX   = ((uint8_t)(5)),  /*!< SSP RX channel. */
    DMA_CHANNEL_CRC      = ((uint8_t)(6)),  /*!< CRC channel. */
    DMA_CHANNEL_SW1      = ((uint8_t)(7)),  /*!< Software channel 1. */
    DMA_CHANNEL_SW2      = ((uint8_t)(8)),  /*!< Software channel 2. */
    DMA_CHANNEL_SW3      = ((uint8_t)(9)),  /*!< Software channel 3. */
    DMA_CHANNEL_TIM0     = ((uint8_t)(10)), /*!< TIMER0 channel. */
    DMA_CHANNEL_TIM1     = ((uint8_t)(11)), /*!< TIMER1 channel. */
    DMA_CHANNEL_ADCUI_I0 = ((uint8_t)(12)), /*!< ADCUI I0 channel. */
    DMA_CHANNEL_ADCUI_V0 = ((uint8_t)(13)), /*!< ADCUI V0 channel. */
    DMA_CHANNEL_ADCUI_I1 = ((uint8_t)(14)), /*!< ADCUI I1 channel. */
    DMA_CHANNEL_ADCUI_V1 = ((uint8_t)(15)), /*!< ADCUI V1 channel. */
    DMA_CHANNEL_ADCUI_I2 = ((uint8_t)(16)), /*!< ADCUI I2 channel. */
    DMA_CHANNEL_ADCUI_V2 = ((uint8_t)(17)), /*!< ADCUI V2 channel. */
    DMA_CHANNEL_ADCUI_I3 = ((uint8_t)(18)), /*!< ADCUI I3 channel. */
    DMA_CHANNEL_SW4      = ((uint8_t)(19)), /*!< Software channel 4. */
    DMA_CHANNEL_SW5      = ((uint8_t)(20)), /*!< Software channel 5. */
    DMA_CHANNEL_SW6      = ((uint8_t)(21)), /*!< Software channel 6. */
    DMA_CHANNEL_SW7      = ((uint8_t)(22)), /*!< Software channel 7. */
    DMA_CHANNEL_SW8      = ((uint8_t)(23)), /*!< Software channel 8. */
    DMA_CHANNEL_SW9      = ((uint8_t)(24)), /*!< Software channel 9. */
    DMA_CHANNEL_SW10     = ((uint8_t)(25)), /*!< Software channel 10. */
    DMA_CHANNEL_SW11     = ((uint8_t)(26)), /*!< Software channel 11. */
    DMA_CHANNEL_SW12     = ((uint8_t)(27)), /*!< Software channel 12. */
    DMA_CHANNEL_SW13     = ((uint8_t)(28)), /*!< Software channel 13. */
    DMA_CHANNEL_SW14     = ((uint8_t)(29)), /*!< Software channel 14. */
    DMA_CHANNEL_ADC      = ((uint8_t)(30)), /*!< ADC channel. */
    DMA_CHANNEL_SW15     = ((uint8_t)(31))  /*!< Software channel 15. */
} DMA_ValidChannels_TypeDef;

#define IS_DMA_CHANNEL(CHANNEL) ((CHANNEL) <= (DMA_CHANNELS_NUMBER - 1))

/**
 * @brief DMA state
 */
typedef enum {
    DMA_STATE_IDLE           = (0x0UL << DMA_STATUS_STATE_Pos), /*!< DMA idle. */
    DMA_STATE_READ_CONFIG    = (0x1UL << DMA_STATUS_STATE_Pos), /*!< DMA read channel config. */
    DMA_STATE_READ_SRC_ADDR  = (0x2UL << DMA_STATUS_STATE_Pos), /*!< DMA read source end pointer. */
    DMA_STATE_READ_DST_ADDR  = (0x3UL << DMA_STATUS_STATE_Pos), /*!< DMA read destination end pointer. */
    DMA_STATE_READ_SRC_DATA  = (0x4UL << DMA_STATUS_STATE_Pos), /*!< DMA read source data. */
    DMA_STATE_WRITE_DST_DATA = (0x5UL << DMA_STATUS_STATE_Pos), /*!< DMA read destination data. */
    DMA_STATE_WAIT_REQUEST   = (0x6UL << DMA_STATUS_STATE_Pos), /*!< DMA wait request. */
    DMA_STATE_UPDATE_CONFIG  = (0x7UL << DMA_STATUS_STATE_Pos), /*!< DMA write channel config. */
    DMA_STATE_HALT           = (0x8UL << DMA_STATUS_STATE_Pos), /*!< DMA suspended. */
    DMA_STATE_COMPLETE       = (0x9UL << DMA_STATUS_STATE_Pos), /*!< DMA completed. */
    DMA_STATE_SG_MODE        = (0x10UL << DMA_STATUS_STATE_Pos) /*!< DMA Scatter mode. */
} DMA_State_TypeDef;

/**
 * @brief DMA source or destination incremented mode
 */
typedef enum {
    DMA_DATA_INC_8BIT  = 0x0, /*!< Data increment step 8bit. */
    DMA_DATA_INC_16BIT = 0x1, /*!< Data increment step 16bit. */
    DMA_DATA_INC_32BIT = 0x2, /*!< Data increment step 32bit. */
    DMA_DATA_INC_NO    = 0x3  /*!< No data increment step. */
} DMA_DataIncMode_TypeDef;

#define IS_DMA_DATA_INC(INC) (((INC) == DMA_DATA_INC_8BIT) ||  \
                              ((INC) == DMA_DATA_INC_16BIT) || \
                              ((INC) == DMA_DATA_INC_32BIT) || \
                              ((INC) == DMA_DATA_INC_NO))

/**
 * @brief DMA memory data size
 */
typedef enum {
    DMA_MEMORY_DATA_SIZE_8BIT  = (0x0UL << DMA_CHANNEL_CFG_SRC_SIZE_Pos) | (0x0UL << DMA_CHANNEL_CFG_DST_SIZE_Pos), /*!< Data size 8bit. */
    DMA_MEMORY_DATA_SIZE_16BIT = (0x1UL << DMA_CHANNEL_CFG_SRC_SIZE_Pos) | (0x1UL << DMA_CHANNEL_CFG_DST_SIZE_Pos), /*!< Data size 16bit. */
    DMA_MEMORY_DATA_SIZE_32BIT = (0x2UL << DMA_CHANNEL_CFG_SRC_SIZE_Pos) | (0x2UL << DMA_CHANNEL_CFG_DST_SIZE_Pos)  /*!< Data size 32bit. */
} DMA_MemoryDataSize_TypeDef;

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MEMORY_DATA_SIZE_8BIT) ||  \
                                       ((SIZE) == DMA_MEMORY_DATA_SIZE_16BIT) || \
                                       ((SIZE) == DMA_MEMORY_DATA_SIZE_32BIT))

/**
 * @brief DMA operating mode
 */
typedef enum {
    DMA_MODE_STOP                   = (0x0UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode stop. */
    DMA_MODE_BASIC                  = (0x1UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode basic cycle. */
    DMA_MODE_AUTO_REQUEST           = (0x2UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode auto-request. */
    DMA_MODE_PING_PONG              = (0x3UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode ping-pong. */
    DMA_MODE_MEM_SG_PRIMARY         = (0x4UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode memory scatter using primary structure. */
    DMA_MODE_MEM_SG_ALTERNATE       = (0x5UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode memory scatter using alternate structure. */
    DMA_MODE_PER_SG_PRIMARY         = (0x6UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode peripheral scatter using primary structure. */
    DMA_MODE_PER_SG_ALTERNATE       = (0x7UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Mode peripheral scatter using alternate structure. */
    DMA_MODE_PER_SG_ALTERNATE_BURST = (0xFUL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)  /*!< Mode peripheral scatter using alternate structure + burst. */
} DMA_OperatingMode_TypeDef;

#define IS_DMA_MODE(MODE) (((MODE) == DMA_MODE_STOP) ||             \
                           ((MODE) == DMA_MODE_BASIC) ||            \
                           ((MODE) == DMA_MODE_AUTO_REQUEST) ||     \
                           ((MODE) == DMA_MODE_PING_PONG) ||        \
                           ((MODE) == DMA_MODE_MEM_SG_PRIMARY) ||   \
                           ((MODE) == DMA_MODE_MEM_SG_ALTERNATE) || \
                           ((MODE) == DMA_MODE_PER_SG_PRIMARY) ||   \
                           ((MODE) == DMA_MODE_PER_SG_ALTERNATE) || \
                           ((MODE) == DMA_MODE_PER_SG_ALTERNATE_BURST))

/**
 * @brief DMA number continuous transfers (number of transfers before next arbitration)
 */
typedef enum {
    DMA_ARB_AFTER_1    = (0x0UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 1 continuous transfer    . */
    DMA_ARB_AFTER_2    = (0x1UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 2 continuous transfers. */
    DMA_ARB_AFTER_4    = (0x2UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 4 continuous transfers. */
    DMA_ARB_AFTER_8    = (0x3UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 8 continuous transfers. */
    DMA_ARB_AFTER_16   = (0x4UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 16 continuous transfers. */
    DMA_ARB_AFTER_32   = (0x5UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 32 continuous transfers. */
    DMA_ARB_AFTER_64   = (0x6UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 64 continuous transfers. */
    DMA_ARB_AFTER_128  = (0x7UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 128 continuous transfers. */
    DMA_ARB_AFTER_256  = (0x8UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 256 continuous transfers. */
    DMA_ARB_AFTER_512  = (0x9UL << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 512 continuous transfers. */
    DMA_ARB_AFTER_1024 = (0xAUL << DMA_CHANNEL_CFG_R_POWER_Pos)  /*!< 1024 continuous transfers. */
} DMA_ArbitrPeriod_TypeDef;

#define IS_DMA_ARB_PERIOD(PERIOD) (((PERIOD) == DMA_ARB_AFTER_1) ||   \
                                   ((PERIOD) == DMA_ARB_AFTER_2) ||   \
                                   ((PERIOD) == DMA_ARB_AFTER_4) ||   \
                                   ((PERIOD) == DMA_ARB_AFTER_8) ||   \
                                   ((PERIOD) == DMA_ARB_AFTER_16) ||  \
                                   ((PERIOD) == DMA_ARB_AFTER_32) ||  \
                                   ((PERIOD) == DMA_ARB_AFTER_64) ||  \
                                   ((PERIOD) == DMA_ARB_AFTER_128) || \
                                   ((PERIOD) == DMA_ARB_AFTER_256) || \
                                   ((PERIOD) == DMA_ARB_AFTER_512) || \
                                   ((PERIOD) == DMA_ARB_AFTER_1024))

/**
 * @brief DMA data structure selection
 */
typedef enum {
    DMA_CTRL_DATA_PRIMARY = 0x0,
#if (DMA_ALTERNATE_DATA == 1)
    DMA_CTRL_DATA_ALTERNATE = 0x1
#endif
} DMA_DataStructSelection_TypeDef;

#if (DMA_ALTERNATE_DATA == 1)
#define IS_DMA_SELECT_DATA_STRUCTURE(TYPE) (((TYPE) == DMA_CTRL_DATA_PRIMARY) || \
                                            ((TYPE) == DMA_CTRL_DATA_ALTERNATE))
#else
#define IS_DMA_SELECT_DATA_STRUCTURE(TYPE) (((TYPE) == DMA_CTRL_DATA_PRIMARY))
#endif

/**
 * @brief DMA flags definition
 */
typedef enum {
    DMA_FLAG_DMA_ENABLED       = 0x1, /*!< DMA unit global enable status. */
    DMA_FLAG_DMA_ERR           = 0x2, /*!< DMA unit bus error status. */
    DMA_FLAG_CHANNEL_ENABLED   = 0x3, /*!< DMA channel enable status. */
    DMA_FLAG_CHANNEL_MASK      = 0x4, /*!< DMA channel request mask status. */
    DMA_FLAG_CHANNEL_WAIT      = 0x5, /*!< DMA channel wait on request status. */
    DMA_FLAG_CHANNEL_BURST     = 0x6, /*!< DMA channel burst mode status. */
    DMA_FLAG_CHANNEL_ALTERNATE = 0x7, /*!< DMA channel alternate control data status. */
    DMA_FLAG_CHANNEL_PRIORITY  = 0x8  /*!< DMA channel priority status. */
} DMA_Flags_TypeDef;

#define IS_DMA_FLAG(FLAG) (((FLAG) == DMA_FLAG_DMA_ENABLED) ||       \
                           ((FLAG) == DMA_FLAG_DMA_ERR) ||           \
                           ((FLAG) == DMA_FLAG_CHANNEL_ENABLED) ||   \
                           ((FLAG) == DMA_FLAG_CHANNEL_MASK) ||      \
                           ((FLAG) == DMA_FLAG_CHANNEL_WAIT) ||      \
                           ((FLAG) == DMA_FLAG_CHANNEL_BURST) ||     \
                           ((FLAG) == DMA_FLAG_CHANNEL_ALTERNATE) || \
                           ((FLAG) == DMA_FLAG_CHANNEL_PRIORITY))

/**
 * @brief DMA Channel Primary / Alternate Control Data initialization structure definition
 */
typedef struct {
    uint32_t                DMA_SourceBaseAddr;     /*!< Specifies the source base address for DMA Channelx. */
    uint32_t                DMA_DestBaseAddr;       /*!< Specifies the destination base address for DMA Channelx. */
    DMA_DataIncMode_TypeDef DMA_SourceIncSize;      /*!< Specifies the source address register increment value.
                                                         This parameter can be a value of @ref DMA_DataIncMode_TypeDef */
    DMA_DataIncMode_TypeDef DMA_DestIncSize;        /*!< Specifies the destination address register increment value.
                                                         This parameter can be a value of @ref DMA_DataIncMode_TypeDef */
    DMA_MemoryDataSize_TypeDef DMA_MemoryDataSize;  /*!< Specifies the Memory data width.
                                                         This parameter can be a value of @ref DMA_MemoryDataSize_TypeDef */
    DMA_OperatingMode_TypeDef DMA_Mode;             /*!< Specifies the operation mode of the DMA Channelx.
                                                         This parameter can be a value of @ref DMA_OperatingMode_TypeDef. */
    uint32_t DMA_CycleSize;                         /*!< Specifies the  total number of DMA transfers that the DMA cycle contains.
                                                         This parameter can be a value of [1; 1024] (@ref DMA_cycle_size). */
    DMA_ArbitrPeriod_TypeDef DMA_ArbitrationPeriod; /*!< Specifies how many DMA transfers can occur before the DMA controller rearbitrates.
                                                         This parameter can be a value of @ref DMA_ArbitrPeriod_TypeDef. */
} DMA_CtrlData_InitTypeDef;

/**
 * @brief  DMA Channel Control union type to access control_cfg.
 */
typedef union {
    struct {
        uint32_t cycle_ctrl    : 3;  /*!< bit:  0..2  Channel work mode */
        uint32_t next_useburst : 1;  /*!< bit:  3  Reserved */
        uint32_t n_minus_1     : 10; /*!< bit:  4..13  DMA cycle total transfers minus 1. */
        uint32_t R_power       : 4;  /*!< bit:  14..17  Transfers amount before re-arbitration. */
        uint32_t src_prot_ctrl : 3;  /*!< bit:  18..20  HPROT[3:1] control on source data read. */
        uint32_t dst_prot_ctrl : 3;  /*!< bit:  21..23  HPROT[3:1] control on destination data write. */
        uint32_t src_size      : 2;  /*!< bit:  24..25  Source data size. */
        uint32_t src_inc       : 2;  /*!< bit:  26..27  Source address increment. */
        uint32_t dst_size      : 2;  /*!< bit:  28..29  Destination data size. */
        uint32_t dst_inc       : 2;  /*!< bit:  30..31  Destination address increment. */
    } b;                             /*!< Structure used for bit  access */
    uint32_t w;                      /*!< Type      used for word access */
} DMA_Control_TypeDef;

/**
 * @brief  DMA Channel Control Data structure definition
 */
typedef struct {
    uint32_t            DMA_SourceEndAddr; /*!< Specifies the DMA channel source end address */
    uint32_t            DMA_DestEndAddr;   /*!< Specifies the DMA channel destination end address. */
    DMA_Control_TypeDef DMA_Control;       /*!< Specifies the DMA channel control data configuration. */
    uint32_t            DMA_Unused;        /*!< Specifies the DMA channel unused memory. */
} DMA_CtrlData_TypeDef;

/**
 * @brief DMA Channel Init structure definition
 */
typedef struct {
    DMA_CtrlData_InitTypeDef* DMA_PriCtrlData;               /*!< Specifies the pointer to the primary control data structure.
                                                                  This parameter should be NULL if primary data structure is not used */
    DMA_CtrlData_InitTypeDef* DMA_AltCtrlData;               /*!< Specifies the pointer to the alternate control data structure.
                                                                  This parameter should be NULL if alternate data structure is not used */
    FunctionalState DMA_UseHighPriority;                     /*!< Specifies the software priority for the DMA Channel.
                                                                  This parameter can be a value of @ref FunctionalState */
    FunctionalState DMA_UseBurst;                            /*!< Disables single request to generate DMA requests for the DMA Channelx.
                                                                  This parameter can be a value of @ref FunctionalState */
    DMA_DataStructSelection_TypeDef DMA_SelectDataStructure; /*!< Specifies the primary /alternate data structure to use by the DMA channel.
                                                                  This parameter can be a value of @ref DMA_DataStructSelection_TypeDef. */
} DMA_Channel_InitTypeDef;

/**
 * @brief DMA Channel Scatter-Gather Init structure definition
 */
typedef struct {
    DMA_CtrlData_TypeDef* DMA_SG_TaskArray; /*!< Specifies the pointer to the Scatter-Gather task structures array.
                                                 The size of the array should be equal to DMA_SG_TaskNumber.
                                                 Every structure of the array should contain the copy of the alternate
                                                 control data for the related task. It will be used by DMA to configure
                                                 the alternate control data while operating in the scatter-gather mode */
    uint32_t        DMA_SG_TaskNumber;      /*!< Specifies the number of scatter-gather tasks to be executed by DMA */
    FunctionalState DMA_UseHighPriority;    /*!< Specifies the software priority for the DMA Channelx.
                                                 This parameter can be a value of @ref FunctionalState */
    FunctionalState DMA_UseBurst;           /*!< Disables single request to generate DMA requests for the DMA Channelx.
                                                 This parameter can be a value of @ref FunctionalState */
} DMA_SG_Channel_InitTypeDef;

/** @} */ /* End of group DMA_Exported_Types */

/** @defgroup DMA_Exported_Defines DMA Exported Defines
 * @{
 */

/** @defgroup DMA_channels_number DMA channels number
 * @{
 */

#if (DMA_ALTERNATE_DATA == 1)
#define DMA_CHANNELS_NUMBER 32
#endif

#define IS_DMA_CHANNELS(NUMBER) (((NUMBER) >= 1) && ((NUMBER) <= DMA_CHANNELS_NUMBER))

/** @} */ /* End of group DMA_channels_number */

/** @defgroup DMA_cycle_size DMA cycle size
 * @{
 */

#define IS_DMA_CYCLE_SIZE(SIZE) (((SIZE) >= 1) && ((SIZE) <= 1024))

/** @} */ /* End of group DMA_cycle_size */

/** @} */ /* End of group DMA_Exported_Defines */

/** @addtogroup DMA_Exported_Variables DMA Exported Variables
 * @{
 */

/**
 * @brief DMA Channel Control Data Table
 */

extern DMA_CtrlData_TypeDef DMA_ControlTable[];

/** @} */ /* End of group DMA_Exported_Variables */

/** @defgroup DMA_Exported_Functions DMA Exported Functions
 * @{
 */

void DMA_DeInit(void);

void DMA_CtrlDataInit(DMA_CtrlData_InitTypeDef* DMA_CtrlDataPtr, DMA_CtrlData_TypeDef* DMA_CtrlTablePtr);
void DMA_CtrlInit(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlDataType, DMA_CtrlData_InitTypeDef* DMA_CtrlStruct);
void DMA_SG_CtrlInit(uint32_t DMA_Task, DMA_CtrlData_TypeDef* DMA_SG_TaskArray, DMA_CtrlData_InitTypeDef* DMA_CtrlStruct);

void DMA_Init(uint8_t DMA_Channel, DMA_Channel_InitTypeDef* DMA_InitStruct);
void DMA_SG_Init(uint8_t DMA_Channel, DMA_SG_Channel_InitTypeDef* DMA_SG_InitStruct);

void DMA_StructInit(DMA_Channel_InitTypeDef* DMA_InitStruct);
void DMA_SG_StructInit(DMA_SG_Channel_InitTypeDef* DMA_InitStruct);

void DMA_Cmd(uint8_t DMA_Channel, FunctionalState NewState);

void DMA_Request(uint8_t DMA_Channel);
void DMA_ClearError(void);

void DMA_ChannelReloadCycle(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct,
                            uint32_t CycleSize, DMA_OperatingMode_TypeDef ChannelMode);

uint32_t DMA_GetChannelTransferCounter(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlData);

DMA_OperatingMode_TypeDef DMA_GetChannelState(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlData);

FlagStatus DMA_GetFlagStatus(uint8_t DMA_Channel, DMA_Flags_TypeDef DMA_Flag);

DMA_State_TypeDef DMA_GetState(void);

/** @} */ /* End of group DMA_Exported_Functions */

/** @} */ /* End of group DMA */

#endif    /* #if defined (USE_MDR32F21QI) */

/** @} */ /* End of group __MDR32F21QI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F21QI_DMA_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F21QI_dma.h */

