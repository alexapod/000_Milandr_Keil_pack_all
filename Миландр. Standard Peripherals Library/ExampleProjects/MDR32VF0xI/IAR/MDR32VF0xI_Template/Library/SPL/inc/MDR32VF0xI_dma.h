/**
 *******************************************************************************
 * @file    MDR32VF0xI_dma.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    16/05/2025
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
#ifndef MDR32VF0xI_DMA_H
#define MDR32VF0xI_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup DMA DMA
 * @{
 */

/** @defgroup DMA_Exported_Types DMA Exported Types
 * @{
 */

/**
 * @brief DMA valid channels.
 */
typedef enum {
    DMA_CHANNEL_UART1_TX = ((uint8_t)(0)),  /*!< UART1 TX channel. */
    DMA_CHANNEL_UART1_RX = ((uint8_t)(1)),  /*!< UART1 RX channel. */
    DMA_CHANNEL_UART2_TX = ((uint8_t)(2)),  /*!< UART2 TX channel. */
    DMA_CHANNEL_UART2_RX = ((uint8_t)(3)),  /*!< UART2 RX channel. */
    DMA_CHANNEL_SSP1_TX  = ((uint8_t)(4)),  /*!< SSP1 TX channel. */
    DMA_CHANNEL_SSP1_RX  = ((uint8_t)(5)),  /*!< SSP1 RX channel. */
    DMA_CHANNEL_CRC      = ((uint8_t)(6)),  /*!< CRC channel. */
    DMA_CHANNEL_UART3_TX = ((uint8_t)(7)),  /*!< UART3 TX channel. */
    DMA_CHANNEL_UART3_RX = ((uint8_t)(8)),  /*!< UART3 RX channel. */
    DMA_CHANNEL_TIM3     = ((uint8_t)(9)),  /*!< TIMER3 channel. */
    DMA_CHANNEL_TIM1     = ((uint8_t)(10)), /*!< TIMER1 channel. */
    DMA_CHANNEL_TIM2     = ((uint8_t)(11)), /*!< TIMER2 channel. */
    DMA_CHANNEL_ADCUI_I0 = ((uint8_t)(12)), /*!< ADCUI I0 channel. */
    DMA_CHANNEL_ADCUI_V0 = ((uint8_t)(13)), /*!< ADCUI V0 channel. */
    DMA_CHANNEL_ADCUI_I1 = ((uint8_t)(14)), /*!< ADCUI I1 channel. */
    DMA_CHANNEL_ADCUI_V1 = ((uint8_t)(15)), /*!< ADCUI V1 channel. */
    DMA_CHANNEL_ADCUI_I2 = ((uint8_t)(16)), /*!< ADCUI I2 channel. */
    DMA_CHANNEL_ADCUI_V2 = ((uint8_t)(17)), /*!< ADCUI V2 channel. */
    DMA_CHANNEL_ADCUI_I3 = ((uint8_t)(18)), /*!< ADCUI I3 channel. */
    DMA_CHANNEL_SSP2_TX  = ((uint8_t)(19)), /*!< SSP2 TX channel. */
    DMA_CHANNEL_SSP2_RX  = ((uint8_t)(20)), /*!< SSP2 RX channel. */
    DMA_CHANNEL_SSP3_TX  = ((uint8_t)(21)), /*!< SSP3 TX channel. */
    DMA_CHANNEL_SSP3_RX  = ((uint8_t)(22)), /*!< SSP3 RX channel. */
    DMA_CHANNEL_TIM4     = ((uint8_t)(23)), /*!< TIMER4 channel. */
    DMA_CHANNEL_UART4_TX = ((uint8_t)(24)), /*!< UART4 TX channel. */
    DMA_CHANNEL_UART4_RX = ((uint8_t)(25)), /*!< UART4 RX channel. */
    DMA_CHANNEL_SW1      = ((uint8_t)(26)), /*!< Software channel 1. */
    DMA_CHANNEL_SW2      = ((uint8_t)(27)), /*!< Software channel 2. */
    DMA_CHANNEL_SW3      = ((uint8_t)(28)), /*!< Software channel 3. */
    DMA_CHANNEL_SW4      = ((uint8_t)(29)), /*!< Software channel 4. */
    DMA_CHANNEL_ADC      = ((uint8_t)(30)), /*!< ADC channel. */
    DMA_CHANNEL_SW5      = ((uint8_t)(31))  /*!< Software channel 5. */
} DMA_ValidChannel_TypeDef;

#define IS_DMA_CHANNEL(CHANNEL) ((CHANNEL) <= (DMA_CHANNELS_NUMBER - 1))

/**
 * @brief DMA state.
 */
typedef enum {
    DMA_STATE_IDLE           = (((uint32_t)0x0) << DMA_STATUS_STATE_Pos), /*!< DMA is idle. */
    DMA_STATE_READ_CONFIG    = (((uint32_t)0x1) << DMA_STATUS_STATE_Pos), /*!< DMA read channel configuration. */
    DMA_STATE_READ_SRC_ADDR  = (((uint32_t)0x2) << DMA_STATUS_STATE_Pos), /*!< DMA read source end pointer. */
    DMA_STATE_READ_DST_ADDR  = (((uint32_t)0x3) << DMA_STATUS_STATE_Pos), /*!< DMA read destination end pointer. */
    DMA_STATE_READ_SRC_DATA  = (((uint32_t)0x4) << DMA_STATUS_STATE_Pos), /*!< DMA read source data. */
    DMA_STATE_WRITE_DST_DATA = (((uint32_t)0x5) << DMA_STATUS_STATE_Pos), /*!< DMA read destination data. */
    DMA_STATE_WAIT_REQUEST   = (((uint32_t)0x6) << DMA_STATUS_STATE_Pos), /*!< DMA wait for request. */
    DMA_STATE_UPDATE_CONFIG  = (((uint32_t)0x7) << DMA_STATUS_STATE_Pos), /*!< DMA write channel configuration. */
    DMA_STATE_HALT           = (((uint32_t)0x8) << DMA_STATUS_STATE_Pos), /*!< DMA is suspended. */
    DMA_STATE_COMPLETE       = (((uint32_t)0x9) << DMA_STATUS_STATE_Pos), /*!< DMA is completed. */
    DMA_STATE_SG_MODE        = (((uint32_t)0xA) << DMA_STATUS_STATE_Pos)  /*!< DMA scatter mode. */
} DMA_State_TypeDef;

/**
 * @brief DMA source or destination incremented mode.
 */
typedef enum {
    DMA_DATA_INC_8BIT  = ((uint32_t)0x0), /*!< Data increment step - 8 bits. */
    DMA_DATA_INC_16BIT = ((uint32_t)0x1), /*!< Data increment step - 16 bits. */
    DMA_DATA_INC_32BIT = ((uint32_t)0x2), /*!< Data increment step - 32 bits. */
    DMA_DATA_INC_NO    = ((uint32_t)0x3)  /*!< No data increment step. */
} DMA_DataIncMode_TypeDef;

#define IS_DMA_DATA_INC(INC) (((INC) == DMA_DATA_INC_8BIT) ||  \
                              ((INC) == DMA_DATA_INC_16BIT) || \
                              ((INC) == DMA_DATA_INC_32BIT) || \
                              ((INC) == DMA_DATA_INC_NO))

/**
 * @brief DMA memory data size.
 */
typedef enum {
    DMA_MEMORY_DATA_SIZE_8BIT  = (((uint32_t)0x0) << DMA_CHANNEL_CFG_SRC_SIZE_Pos) | (((uint32_t)0x0) << DMA_CHANNEL_CFG_DST_SIZE_Pos), /*!< Data size - 8 bits. */
    DMA_MEMORY_DATA_SIZE_16BIT = (((uint32_t)0x1) << DMA_CHANNEL_CFG_SRC_SIZE_Pos) | (((uint32_t)0x1) << DMA_CHANNEL_CFG_DST_SIZE_Pos), /*!< Data size - 16 bits. */
    DMA_MEMORY_DATA_SIZE_32BIT = (((uint32_t)0x2) << DMA_CHANNEL_CFG_SRC_SIZE_Pos) | (((uint32_t)0x2) << DMA_CHANNEL_CFG_DST_SIZE_Pos)  /*!< Data size - 32 bits. */
} DMA_MemoryDataSize_TypeDef;

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MEMORY_DATA_SIZE_8BIT) ||  \
                                       ((SIZE) == DMA_MEMORY_DATA_SIZE_16BIT) || \
                                       ((SIZE) == DMA_MEMORY_DATA_SIZE_32BIT))

/**
 * @brief DMA operating mode.
 */
typedef enum {
    DMA_MODE_STOP                   = (((uint32_t)0x0) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Stop mode. */
    DMA_MODE_BASIC                  = (((uint32_t)0x1) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Basic cycle mode. */
    DMA_MODE_AUTO_REQUEST           = (((uint32_t)0x2) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Auto-request mode. */
    DMA_MODE_PING_PONG              = (((uint32_t)0x3) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Ping-pong mode (for both primary and alternate structures in ping-pong mode). */
    DMA_MODE_MEM_SG_PRIMARY         = (((uint32_t)0x4) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Memory scatter mode using primary structure (for primary structure in memory scatter mode). */
    DMA_MODE_MEM_SG_ALTERNATE       = (((uint32_t)0x5) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Memory scatter mode using alternate structure (for alternate structure in memory scatter mode). */
    DMA_MODE_PER_SG_PRIMARY         = (((uint32_t)0x6) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Peripheral scatter mode using primary structure (for primary structure in peripheral scatter mode). */
    DMA_MODE_PER_SG_ALTERNATE       = (((uint32_t)0x7) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos), /*!< Peripheral scatter mode using alternate structure (for alternate structure in peripheral scatter mode). */
    DMA_MODE_PER_SG_ALTERNATE_BURST = (((uint32_t)0xF) << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)  /*!< Peripheral scatter mode using alternate structure + burst (for alternate structure in peripheral scatter mode). */
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

#define IS_DMA_SG_PRIMARY_MODE(MODE) (((MODE) == DMA_MODE_MEM_SG_PRIMARY) || \
                                      ((MODE) == DMA_MODE_PER_SG_PRIMARY))

/**
 * @brief The number of DMA continuous transfers (the number of transfers before the next arbitration).
 */
typedef enum {
    DMA_ARB_AFTER_1    = (((uint32_t)0x0) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 1 continuous transfer. */
    DMA_ARB_AFTER_2    = (((uint32_t)0x1) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 2 continuous transfers. */
    DMA_ARB_AFTER_4    = (((uint32_t)0x2) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 4 continuous transfers. */
    DMA_ARB_AFTER_8    = (((uint32_t)0x3) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 8 continuous transfers. */
    DMA_ARB_AFTER_16   = (((uint32_t)0x4) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 16 continuous transfers. */
    DMA_ARB_AFTER_32   = (((uint32_t)0x5) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 32 continuous transfers. */
    DMA_ARB_AFTER_64   = (((uint32_t)0x6) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 64 continuous transfers. */
    DMA_ARB_AFTER_128  = (((uint32_t)0x7) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 128 continuous transfers. */
    DMA_ARB_AFTER_256  = (((uint32_t)0x8) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 256 continuous transfers. */
    DMA_ARB_AFTER_512  = (((uint32_t)0x9) << DMA_CHANNEL_CFG_R_POWER_Pos), /*!< 512 continuous transfers. */
    DMA_ARB_AFTER_1024 = (((uint32_t)0xA) << DMA_CHANNEL_CFG_R_POWER_Pos)  /*!< 1024 continuous transfers (i.e. no arbitration). */
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
 * @brief DMA data structure selection.
 */
typedef enum {
    DMA_CTRL_DATA_PRIMARY = ((uint32_t)0x0),
#if defined(DMA_ALTERNATE_DATA)
    DMA_CTRL_DATA_ALTERNATE = ((uint32_t)0x1)
#endif
} DMA_DataStructSelection_TypeDef;

#if defined(DMA_ALTERNATE_DATA)
#define IS_DMA_SELECT_DATA_STRUCTURE(TYPE) (((TYPE) == DMA_CTRL_DATA_PRIMARY) || \
                                            ((TYPE) == DMA_CTRL_DATA_ALTERNATE))
#else
#define IS_DMA_SELECT_DATA_STRUCTURE(TYPE) (((TYPE) == DMA_CTRL_DATA_PRIMARY))
#endif

/**
 * @brief DMA flags definition.
 */
typedef enum {
    DMA_FLAG_DMA_ENABLED       = ((uint32_t)0x1), /*!< DMA controller global enable status. */
    DMA_FLAG_DMA_ERR           = ((uint32_t)0x2), /*!< DMA controller bus error status. */
    DMA_FLAG_CHANNEL_ENABLED   = ((uint32_t)0x3), /*!< DMA channel enable status. */
    DMA_FLAG_CHANNEL_MASK      = ((uint32_t)0x4), /*!< DMA channel request mask status. */
    DMA_FLAG_CHANNEL_WAIT      = ((uint32_t)0x5), /*!< DMA channel wait on request status. */
    DMA_FLAG_CHANNEL_BURST     = ((uint32_t)0x6), /*!< DMA channel burst mode status. */
    DMA_FLAG_CHANNEL_ALTERNATE = ((uint32_t)0x7), /*!< DMA channel alternate control data status. */
    DMA_FLAG_CHANNEL_PRIORITY  = ((uint32_t)0x8)  /*!< DMA channel priority status. */
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
 * @brief DMA channel primary / alternate control data initialization structure definition.
 */
typedef struct {
    uint32_t                DMA_SourceBaseAddr;     /*!< Specify the source base address for the DMA Channelx. */
    uint32_t                DMA_DestBaseAddr;       /*!< Specify the destination base address for the DMA Channelx. */
    DMA_DataIncMode_TypeDef DMA_SourceIncSize;      /*!< Specify the source address register increment value.
                                                         This parameter can be a value of the @ref DMA_DataIncMode_TypeDef. */
    DMA_DataIncMode_TypeDef DMA_DestIncSize;        /*!< Specify the destination address register increment value.
                                                         This parameter can be a value of the @ref DMA_DataIncMode_TypeDef. */
    DMA_MemoryDataSize_TypeDef DMA_MemoryDataSize;  /*!< Specify the Memory data width.
                                                         This parameter can be a value of the @ref DMA_MemoryDataSize_TypeDef. */
    DMA_OperatingMode_TypeDef DMA_Mode;             /*!< Specify the operation mode of the DMA Channelx.
                                                         This parameter can be a value of the @ref DMA_OperatingMode_TypeDef. */
    uint32_t DMA_CycleSize;                         /*!< Specify the total number of the DMA transfers that the DMA cycle contains.
                                                         This parameter can be a value from the range [1; 1024] (@ref DMA_cycle_size). */
    DMA_ArbitrPeriod_TypeDef DMA_ArbitrationPeriod; /*!< Specify how many DMA transfers can occur before the DMA controller rearbitrates.
                                                         This parameter can be a value of the @ref DMA_ArbitrPeriod_TypeDef. */
} DMA_CtrlData_InitTypeDef;

/**
 * @brief DMA channel control union type to access control_cfg.
 */
typedef union {
    struct {
        volatile uint32_t cycle_ctrl    : 3;  /*!< bit:  0..2    Channel operation mode. */
        volatile uint32_t next_useburst : 1;  /*!< bit:  3       Control chnl_useburst_set[C] in scatter-gather mode after finishing alternate data structure. */
        volatile uint32_t n_minus_1     : 10; /*!< bit:  4..13   DMA cycle total transfers minus 1. */
        volatile uint32_t R_power       : 4;  /*!< bit:  14..17  The number of transfers before re-arbitration. */
        volatile uint32_t src_prot_ctrl : 3;  /*!< bit:  18..20  HPROT[3:1] control on source data read. */
        volatile uint32_t dst_prot_ctrl : 3;  /*!< bit:  21..23  HPROT[3:1] control on destination data write. */
        volatile uint32_t src_size      : 2;  /*!< bit:  24..25  Source data size. */
        volatile uint32_t src_inc       : 2;  /*!< bit:  26..27  Source address increment. */
        volatile uint32_t dst_size      : 2;  /*!< bit:  28..29  Destination data size. */
        volatile uint32_t dst_inc       : 2;  /*!< bit:  30..31  Destination address increment. */
    } b;                                      /*!< Structure used for bit  access. */
    volatile uint32_t w;                      /*!< Type      used for word access. */
} DMA_Control_TypeDef;

/**
 * @brief DMA channel control data structure definition.
 */
typedef struct {
    volatile uint32_t            DMA_SourceEndAddr; /*!< Specify the DMA channel source end address. */
    volatile uint32_t            DMA_DestEndAddr;   /*!< Specify the DMA channel destination end address. */
    volatile DMA_Control_TypeDef DMA_Control;       /*!< Specify the DMA channel control data configuration. */
    volatile uint32_t            DMA_Unused;        /*!< Specify the DMA channel unused memory. */
} DMA_CtrlData_TypeDef;

/**
 * @brief DMA channel init structure definition.
 */
typedef struct {
    DMA_CtrlData_InitTypeDef* DMA_PriCtrlData;               /*!< Specify the pointer to the primary control data structure.
                                                                  This parameter must be NULL if the primary data structure is not used. */
    DMA_CtrlData_InitTypeDef* DMA_AltCtrlData;               /*!< Specify the pointer to the alternate control data structure.
                                                                  This parameter must be NULL if the alternate data structure is not used. */
    FunctionalState DMA_UseHighPriority;                     /*!< Specify the software priority for the DMA Channel.
                                                                  This parameter can be a value of the @ref FunctionalState */
    FunctionalState DMA_UseBurst;                            /*!< Disable a single request to generate DMA requests for the DMA Channelx.
                                                                  This parameter can be a value of the @ref FunctionalState */
    DMA_DataStructSelection_TypeDef DMA_SelectDataStructure; /*!< Specify the primary /alternate data structure to be used by the DMA channel.
                                                                  This parameter can be a value of the @ref DMA_DataStructSelection_TypeDef. */
} DMA_Channel_InitTypeDef;

/**
 * @brief DMA channel scatter-gather init structure definition.
 */
typedef struct {
    DMA_CtrlData_TypeDef* DMA_SG_TaskArray; /*!< Specify the pointer to the scatter-gather task structures array.
                                                 The size of the array must be equal to DMA_SG_TaskNumber.
                                                 Every structure of the array must contain the copy of the alternate
                                                 control data for the related task. It will be used by the DMA to configure
                                                 the alternate control data while operating in the scatter-gather mode. */
    uint32_t        DMA_SG_TaskNumber;      /*!< Specify the number of scatter-gather tasks to be executed by DMA. */
    FunctionalState DMA_UseHighPriority;    /*!< Specify the software priority for the DMA Channelx.
                                                 This parameter can be a value of the @ref FunctionalState. */
    FunctionalState DMA_UseBurst;           /*!< Disable a single request to generate DMA requests for the DMA Channelx.
                                                 This parameter can be a value of the @ref FunctionalState. */
} DMA_SG_Channel_InitTypeDef;

/** @} */ /* End of the group DMA_Exported_Types */

/** @defgroup DMA_Exported_Defines DMA Exported Defines
 * @{
 */

/** @defgroup DMA_Cycle_Size DMA Cycle Size
 * @{
 */

#define IS_DMA_CYCLE_SIZE(SIZE)            (((SIZE) >= 1) && ((SIZE) <= 1024))
#define IS_DMA_SG_PRIMARY_CYCLE_SIZE(SIZE) (IS_DMA_CYCLE_SIZE(SIZE) && (((SIZE) & 0x3) == 0))

/** @} */ /* End of the group DMA_Cycle_Size */

/** @} */ /* End of the group DMA_Exported_Defines */

/** @addtogroup DMA_Exported_Variables DMA exported variables
 * @{
 */

/**
 * @brief DMA channel control data table.
 */
extern DMA_CtrlData_TypeDef DMA_ControlTable[];

/** @} */ /* End of the group DMA_Exported_Variables */

/** @defgroup DMA_Exported_Functions DMA Exported Functions
 * @{
 */

void DMA_DeInit(void);

void            DMA_Cmd(FunctionalState NewState);
FunctionalState DMA_GetCmdState(void);

void DMA_CtrlDataInit(const DMA_CtrlData_InitTypeDef* DMA_CtrlDataPtr, DMA_CtrlData_TypeDef* DMA_CtrlTablePtr);
void DMA_CtrlInit(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlDataType, const DMA_CtrlData_InitTypeDef* DMA_CtrlStruct);
void DMA_SG_CtrlInit(uint32_t DMA_Task, DMA_CtrlData_TypeDef* DMA_SG_TaskArray, const DMA_CtrlData_InitTypeDef* DMA_CtrlStruct);

void DMA_ChannelInit(uint8_t DMA_Channel, const DMA_Channel_InitTypeDef* DMA_InitStruct);
#if defined(DMA_ALTERNATE_DATA)
void DMA_SG_ChannelInit(uint8_t DMA_Channel, const DMA_SG_Channel_InitTypeDef* DMA_SG_InitStruct, DMA_OperatingMode_TypeDef DMA_SG_Mode);
#endif

void DMA_StructInit(DMA_Channel_InitTypeDef* DMA_InitStruct);
void DMA_SG_StructInit(DMA_SG_Channel_InitTypeDef* DMA_InitStruct);

void            DMA_ChannelCmd(uint8_t DMA_Channel, FunctionalState NewState);
FunctionalState DMA_GetChannelCmdState(uint8_t DMA_Channel);

void            DMA_ChannelRequestMaskCmd(uint8_t DMA_Channel, FunctionalState NewState);
FunctionalState DMA_GetChannelRequestMaskCmdState(uint8_t DMA_Channel);

void DMA_ChannelRequest(uint8_t DMA_Channel);

void DMA_ChannelReloadCycle(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct,
                            uint32_t CycleSize, DMA_OperatingMode_TypeDef ChannelMode);

uint32_t DMA_GetChannelTransferCounter(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct);

void                            DMA_ChannelSetControl(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct);
DMA_DataStructSelection_TypeDef DMA_ChannelGetControl(uint8_t DMA_Channel);

DMA_OperatingMode_TypeDef DMA_GetChannelMode(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct);

FlagStatus DMA_GetFlagStatus(uint8_t DMA_Channel, DMA_Flags_TypeDef DMA_Flag);

void DMA_ClearError(void);

DMA_State_TypeDef DMA_GetState(void);

/** @} */ /* End of the group DMA_Exported_Functions */

/** @} */ /* End of the group DMA */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_DMA_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_dma.h */

