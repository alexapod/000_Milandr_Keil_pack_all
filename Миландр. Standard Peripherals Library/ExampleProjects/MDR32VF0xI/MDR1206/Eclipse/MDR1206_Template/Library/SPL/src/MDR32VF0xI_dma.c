/**
 *******************************************************************************
 * @file    MDR32VF0xI_dma.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    03/04/2025
 * @brief   This file contains all the DMA firmware functions.
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
#include "MDR32VF0xI_dma.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @defgroup DMA DMA
 * @{
 */

/** @addtogroup DMA_Private_Variables DMA Private Variables
 * @{
 */

/**
 * @brief DMA channel control data table.
 */
#if defined(DMA_ALTERNATE_DATA)
#define DMA_CHANNELS_MODIFIER 1
#else
#define DMA_CHANNELS_MODIFIER 0
#endif

#if defined(__GNUC__) /* GCC compiler. */
__RAM_AHB_BSS DMA_CtrlData_TypeDef DMA_ControlTable[(32 * DMA_CHANNELS_MODIFIER) + DMA_CHANNELS_NUMBER] __attribute__((aligned(1024)));
#elif defined(__ICCRISCV__) /* IAR RISC-V compiler. */
__RAM_AHB_BSS DMA_CtrlData_TypeDef DMA_ControlTable[(32 * DMA_CHANNELS_MODIFIER) + DMA_CHANNELS_NUMBER] __attribute__((aligned(1024)));
#else
#error "Unsupported compiler is used."
#endif

/** @} */ /* End of the group DMA_Private_Variables */

/** @defgroup DMA_Exported_Functions DMA Exported Functions
 * @{
 */

/**
 * @brief  Set DMA to safe state. Disable burst mode, mask and enable all channels, enable DMA.
 * @param  None.
 * @return None.
 */
void DMA_DeInit(void)
{
    MDR_DMA->CFG               = 0;          /* Master Enable off. */
    MDR_DMA->CTRL_BASE_PTR     = 0;          /* Control data base pointer. */
    MDR_DMA->CHNL_SW_REQUEST   = 0;          /* Disable all software requests. */
    MDR_DMA->CHNL_USEBURST_SET = 0xFFFFFFFF; /* Disable burst mode. */

    MDR_DMA->CHNL_ENABLE_CLR   = 0xFFFFFFFF;          /* Clear channel enable. */
    MDR_DMA->CHNL_PRI_ALT_CLR  = 0xFFFFFFFF;          /* Reset to primary data structure .*/
    MDR_DMA->CHNL_PRIORITY_CLR = 0xFFFFFFFF;          /* Reset to default priority. */
    MDR_DMA->ERR_CLR           = DMA_ERR_CLR_ERR_CLR; /* Clear dma_err status. */

    MDR_DMA->CFG               = DMA_CFG_MASTER_ENABLE; /* Master Enable on. */
    MDR_DMA->CHNL_REQ_MASK_SET = 0xFFFFFFFF;            /* Mask all channels. */
    MDR_DMA->CHNL_ENABLE_SET   = 0xFFFFFFFF;            /* Enable all channels. */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    CLIC_ClearPendingIRQ(DMA_IRQn);
#endif
}

/**
 * @brief  Enable or disable the DMA controller.
 * @param  NewState: @ref FunctionalState - a new state of the DMA controller.
 * @return None.
 */
void DMA_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Enable/Disable the DMA controller. */
    if (NewState != DISABLE) {
        MDR_DMA->CFG = DMA_CFG_MASTER_ENABLE; /* Master Enable on. */
    } else {
        MDR_DMA->CFG = 0; /* Master Enable off. */
    }
}

/**
 * @brief  Get the DMA controller work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the DMA controller.
 */
FunctionalState DMA_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_DMA->STATUS & DMA_STATUS_MASTER_ENABLE) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Initialize the DMA control data structure according to the specified parameters.
 * @param  DMA_CtrlDataPtr: The pointer to the @ref DMA_CtrlData_InitTypeDef structure
 *         that contains the control data structure to initialize.
 * @param  DMA_CtrlTablePtr: The pointer to the @ref DMA_CtrlData_TypeDef structure that
 *         contains the initial control data configuration, provided by the application.
 * @return None.
 */
void DMA_CtrlDataInit(const DMA_CtrlData_InitTypeDef* DMA_CtrlDataPtr, DMA_CtrlData_TypeDef* DMA_CtrlTablePtr)
{
    /* Check the parameters. */
    assert_param(IS_DMA_DATA_INC(DMA_CtrlDataPtr->DMA_SourceIncSize));
    assert_param(IS_DMA_DATA_INC(DMA_CtrlDataPtr->DMA_DestIncSize));
    assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_CtrlDataPtr->DMA_MemoryDataSize));
    assert_param(IS_DMA_MODE(DMA_CtrlDataPtr->DMA_Mode));
    assert_param(((DMA_CtrlDataPtr->DMA_Mode == DMA_MODE_MEM_SG_PRIMARY) || (DMA_CtrlDataPtr->DMA_Mode == DMA_MODE_PER_SG_PRIMARY)) ? IS_DMA_SG_PRIMARY_CYCLE_SIZE(DMA_CtrlDataPtr->DMA_CycleSize) : IS_DMA_CYCLE_SIZE(DMA_CtrlDataPtr->DMA_CycleSize));
    assert_param(IS_DMA_ARB_PERIOD(DMA_CtrlDataPtr->DMA_ArbitrationPeriod));

    /* DMA source data end address. */
    if (DMA_CtrlDataPtr->DMA_SourceIncSize == DMA_DATA_INC_NO) {
        DMA_CtrlTablePtr->DMA_SourceEndAddr = DMA_CtrlDataPtr->DMA_SourceBaseAddr;
    } else {
        DMA_CtrlTablePtr->DMA_SourceEndAddr = (DMA_CtrlDataPtr->DMA_SourceBaseAddr +
                                               (((uint32_t)DMA_CtrlDataPtr->DMA_CycleSize - 1) << ((uint32_t)(DMA_CtrlDataPtr->DMA_SourceIncSize))));
    }

    /* DMA destination data end address. */
    if ((DMA_CtrlDataPtr->DMA_Mode == DMA_MODE_MEM_SG_PRIMARY) || (DMA_CtrlDataPtr->DMA_Mode == DMA_MODE_PER_SG_PRIMARY)) {
        /* Scatter-gather mode, alternate data structure end address. */
        DMA_CtrlTablePtr->DMA_DestEndAddr = (DMA_CtrlDataPtr->DMA_DestBaseAddr + 12);
    } else {
        /* Other modes. */
        if (DMA_CtrlDataPtr->DMA_DestIncSize == DMA_DATA_INC_NO) {
            DMA_CtrlTablePtr->DMA_DestEndAddr = DMA_CtrlDataPtr->DMA_DestBaseAddr;
        } else {
            DMA_CtrlTablePtr->DMA_DestEndAddr = (DMA_CtrlDataPtr->DMA_DestBaseAddr +
                                                 (((uint32_t)DMA_CtrlDataPtr->DMA_CycleSize - 1) << ((uint32_t)(DMA_CtrlDataPtr->DMA_DestIncSize))));
        }
    }

    /* DMA control data. */
    DMA_CtrlTablePtr->DMA_Control.w = (((uint32_t)(DMA_CtrlDataPtr->DMA_DestIncSize) << DMA_CHANNEL_CFG_DST_INC_Pos) |
                                       ((uint32_t)DMA_CtrlDataPtr->DMA_MemoryDataSize) |
                                       ((uint32_t)(DMA_CtrlDataPtr->DMA_SourceIncSize) << DMA_CHANNEL_CFG_SRC_INC_Pos) |
                                       ((uint32_t)DMA_CtrlDataPtr->DMA_ArbitrationPeriod) |
                                       (((uint32_t)DMA_CtrlDataPtr->DMA_CycleSize - 1) << DMA_CHANNEL_CFG_N_MINUS_1_Pos) |
                                       (uint32_t)(DMA_CtrlDataPtr->DMA_Mode));
}

/**
 * @brief  Initialize the DMA channel DMA_ControlTable structure according to the specified parameters.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  DMA_CtrlDataType: @ref DMA_DataStructSelection_TypeDef - select the data structure.
 * @param  DMA_CtrlStruct: The pointer to the @ref DMA_CtrlData_InitTypeDef structure that contains the initial
 *         control data configuration, provided by the application for the specified DMA Channel.
 * @return None.
 */
void DMA_CtrlInit(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlDataType, const DMA_CtrlData_InitTypeDef* DMA_CtrlStruct)
{
    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(DMA_CtrlDataType));

    if (DMA_CtrlDataType == DMA_CTRL_DATA_PRIMARY) {
        /* Primary control data init. */
        DMA_CtrlDataInit(DMA_CtrlStruct, &DMA_ControlTable[DMA_Channel]);
#if defined(DMA_ALTERNATE_DATA)
    } else {
        /* Alternate control data init. */
        DMA_CtrlDataInit(DMA_CtrlStruct, &DMA_ControlTable[32 + DMA_Channel]);
#endif
    }
}

/**
 * @brief  Initialize the DMA scatter-gather task structure according to the specified parameters.
 * @param  DMA_Task: Specify the current task number. Numeration begins with 0.
 * @param  DMA_CtrlStruct: the pointer to the @ref DMA_CtrlData_InitTypeDef structure
 *         that contains the control data information for the specified task.
 * @param  DMA_SG_TaskArray: the pointer to the @ref DMA_CtrlData_TypeDef array that
 *         contains the copy of the alternate control data information for the specified task.
 * @return None.
 */
void DMA_SG_CtrlInit(uint32_t DMA_Task, DMA_CtrlData_TypeDef* DMA_SG_TaskArray, const DMA_CtrlData_InitTypeDef* DMA_CtrlStruct)
{
    DMA_CtrlDataInit(DMA_CtrlStruct, &DMA_SG_TaskArray[DMA_Task]);
}

/**
 * @brief  Initialize the DMA channel according to
 *         the specified parameters in the DMA_InitStruct.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  DMA_InitStruct: The pointer to the @ref DMA_Channel_InitTypeDef structure that
 *         contains the configuration information for the specified DMA channel.
 * @return None.
 */
void DMA_ChannelInit(uint8_t DMA_Channel, const DMA_Channel_InitTypeDef* DMA_InitStruct)
{
    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(DMA_InitStruct->DMA_UseHighPriority));
    assert_param(IS_FUNCTIONAL_STATE(DMA_InitStruct->DMA_UseBurst));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(DMA_InitStruct->DMA_SelectDataStructure));

    /* Check the CTRL_BASE_PTR initialization. */
    MDR_DMA->CTRL_BASE_PTR = (uint32_t)DMA_ControlTable;

    /* Primary control data init. */
    if (DMA_InitStruct->DMA_PriCtrlData) {
        DMA_CtrlDataInit(DMA_InitStruct->DMA_PriCtrlData, &DMA_ControlTable[DMA_Channel]);
    }

#if defined(DMA_ALTERNATE_DATA)
    /* Alternate control data init. */
    if (DMA_InitStruct->DMA_AltCtrlData) {
        DMA_CtrlDataInit(DMA_InitStruct->DMA_AltCtrlData, &DMA_ControlTable[32 + DMA_Channel]);
    }
#endif

    /* Burst mode. */
    if (DMA_InitStruct->DMA_UseBurst == ENABLE) {
        MDR_DMA->CHNL_USEBURST_SET = (1 << DMA_Channel);
    } else {
        MDR_DMA->CHNL_USEBURST_CLR = (1 << DMA_Channel);
    }

    /* Primary or alternate control data structure selection. */
    if (DMA_InitStruct->DMA_SelectDataStructure == DMA_CTRL_DATA_PRIMARY) {
        MDR_DMA->CHNL_PRI_ALT_CLR = (1 << DMA_Channel); /* Use primary. */
    } else {
        MDR_DMA->CHNL_PRI_ALT_SET = (1 << DMA_Channel); /* Use alternate. */
    }

    /* Channel priority set */
    if (DMA_InitStruct->DMA_UseHighPriority == ENABLE) {
        MDR_DMA->CHNL_PRIORITY_SET = (1 << DMA_Channel); /* High priority. */
    } else {
        MDR_DMA->CHNL_PRIORITY_CLR = (1 << DMA_Channel); /* Default priority. */
    }

    /* Channel mask clear. */
    MDR_DMA->CHNL_REQ_MASK_CLR = (1 << DMA_Channel);
}

#if defined(DMA_ALTERNATE_DATA)
/**
 * @brief  Initialize the DMA channel in the scatter-gather mode.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  DMA_SG_InitStruct: the pointer to the @ref DMA_SG_Channel_InitTypeDef array that
 *         contains the configuration information for the specified DMA channel.
 * @param  DMA_SG_Mode: @ref DMA_OperatingMode_TypeDef - specify the primary channel scatter-gather mode.
 *         This parameter can be one of the following values:
 *             @arg DMA_MODE_MEM_SG_PRIMARY: Memory scatter-gather mode;
 *             @arg DMA_MODE_PER_SG_PRIMARY: Peripheral scatter-gather mode.
 * @return None.
 */
void DMA_SG_ChannelInit(uint8_t DMA_Channel, const DMA_SG_Channel_InitTypeDef* DMA_SG_InitStruct, DMA_OperatingMode_TypeDef DMA_SG_Mode)
{
    DMA_CtrlData_InitTypeDef DMA_PriCtrlData;

    /* Check the parameters. */
    assert_param(DMA_SG_InitStruct != 0);
    assert_param(DMA_SG_InitStruct->DMA_SG_TaskNumber != 0);
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(DMA_SG_InitStruct->DMA_UseHighPriority));
    assert_param(IS_FUNCTIONAL_STATE(DMA_SG_InitStruct->DMA_UseBurst));
    assert_param(IS_DMA_SG_PRIMARY_MODE(DMA_SG_Mode));

    /* Check the CTRL_BASE_PTR initialization. */
    MDR_DMA->CTRL_BASE_PTR = (uint32_t)DMA_ControlTable;

    /* Primary control data init. */
    DMA_PriCtrlData.DMA_SourceBaseAddr    = (uint32_t)(DMA_SG_InitStruct->DMA_SG_TaskArray);
    DMA_PriCtrlData.DMA_DestBaseAddr      = (uint32_t)(&DMA_ControlTable[32 + DMA_Channel]);
    DMA_PriCtrlData.DMA_SourceIncSize     = DMA_DATA_INC_32BIT;
    DMA_PriCtrlData.DMA_DestIncSize       = DMA_DATA_INC_32BIT;
    DMA_PriCtrlData.DMA_MemoryDataSize    = DMA_MEMORY_DATA_SIZE_32BIT;
    DMA_PriCtrlData.DMA_Mode              = DMA_SG_Mode;
    DMA_PriCtrlData.DMA_CycleSize         = (DMA_SG_InitStruct->DMA_SG_TaskNumber) << 2;
    DMA_PriCtrlData.DMA_ArbitrationPeriod = DMA_ARB_AFTER_4;

    DMA_CtrlDataInit(&DMA_PriCtrlData, &DMA_ControlTable[DMA_Channel]);

    /* Burst mode. */
    if (DMA_SG_InitStruct->DMA_UseBurst == ENABLE) {
        MDR_DMA->CHNL_USEBURST_SET = (1 << DMA_Channel);
    } else {
        MDR_DMA->CHNL_USEBURST_CLR = (1 << DMA_Channel);
    }

    /* Primary - alternate control data structure selection. */
    MDR_DMA->CHNL_PRI_ALT_CLR = (1 << DMA_Channel); /* Use primary. */

    /* Set channel priority. */
    if (DMA_SG_InitStruct->DMA_UseHighPriority == ENABLE) {
        MDR_DMA->CHNL_PRIORITY_SET = (1 << DMA_Channel); /* High priority. */
    } else {
        MDR_DMA->CHNL_PRIORITY_CLR = (1 << DMA_Channel); /* Default priority. */
    }

    /* Clear channel mask. */
    MDR_DMA->CHNL_REQ_MASK_CLR = (1 << DMA_Channel);
}
#endif

/**
 * @brief  Fill each DMA_InitStruct member with its default value.
 * @param  DMA_InitStruct: The pointer to the @ref DMA_Channel_InitTypeDef structure
 *         to be initialized.
 * @return None.
 */
void DMA_StructInit(DMA_Channel_InitTypeDef* DMA_InitStruct)
{
    DMA_InitStruct->DMA_PriCtrlData         = 0;
    DMA_InitStruct->DMA_AltCtrlData         = 0;
    DMA_InitStruct->DMA_UseHighPriority     = DISABLE;
    DMA_InitStruct->DMA_UseBurst            = DISABLE;
    DMA_InitStruct->DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;
}

/**
 * @brief  Fill each DMA_SG_InitStruct member with its default value.
 * @param  DMA_SG_InitStruct: The pointer to the @ref DMA_SG_Channel_InitTypeDef structure
 *         to be be initialized.
 * @return None.
 */
void DMA_SG_StructInit(DMA_SG_Channel_InitTypeDef* DMA_SG_InitStruct)
{
    DMA_SG_InitStruct->DMA_SG_TaskArray    = 0;
    DMA_SG_InitStruct->DMA_SG_TaskNumber   = 0;
    DMA_SG_InitStruct->DMA_UseHighPriority = DISABLE;
    DMA_SG_InitStruct->DMA_UseBurst        = DISABLE;
}

/**
 * @brief  Enable or disable the specified DMA channel.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  NewState: @ref FunctionalState - a new state of the DMA channel.
 * @return None.
 */
void DMA_ChannelCmd(uint8_t DMA_Channel, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Enable/Disable the channel. */
    if (NewState != DISABLE) {
        MDR_DMA->CHNL_ENABLE_SET = (1 << DMA_Channel);
    } else {
        MDR_DMA->CHNL_ENABLE_CLR = (1 << DMA_Channel);
    }
}

/**
 * @brief  Get the specified DMA channel permission state.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @return @ref FunctionalState - the current permission state of the specified DMA channel.
 */
FunctionalState DMA_GetChannelCmdState(uint8_t DMA_Channel)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));

    if ((MDR_DMA->CHNL_ENABLE_SET & (1 << DMA_Channel)) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Enable or disable request mask for the specified DMA channel.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  NewState: @ref FunctionalState - a new state of the DMA channel request mask.
 * @return None.
 */
void DMA_ChannelRequestMaskCmd(uint8_t DMA_Channel, FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Enable/Disable the channel request mask. */
    if (NewState != DISABLE) {
        MDR_DMA->CHNL_REQ_MASK_SET = (1 << DMA_Channel);
    } else {
        MDR_DMA->CHNL_REQ_MASK_CLR = (1 << DMA_Channel);
    }
}

/**
 * @brief  Get the specified DMA channel request mask state.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @return @ref FunctionalState - the current request mask state of the specified DMA channel.
 */
FunctionalState DMA_GetChannelRequestMaskCmdState(uint8_t DMA_Channel)
{
    FunctionalState State;

    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));

    if ((MDR_DMA->CHNL_REQ_MASK_SET & (1 << DMA_Channel)) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Generate software request for the specified DMA channel.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @return None.
 */
void DMA_ChannelRequest(uint8_t DMA_Channel)
{
    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));

    /* Set the SW Request */
    MDR_DMA->CHNL_SW_REQUEST = (1 << DMA_Channel);
}

/**
 * @brief  Reload the DMA channel CycleSize and ChannelMode.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  SelectDataStruct: @ref DMA_DataStructSelection_TypeDef - the data structure to change.
 * @param  CycleSize: New cycle size.
 * @param  ChannelMode: @ref DMA_OperatingMode_TypeDef - a new channel mode.
 * @return None.
 */
void DMA_ChannelReloadCycle(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct,
                            uint32_t CycleSize, DMA_OperatingMode_TypeDef ChannelMode)
{
    DMA_CtrlData_TypeDef* ChnlData;

    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(SelectDataStruct));
    assert_param(IS_DMA_CYCLE_SIZE(CycleSize));
    assert_param(IS_DMA_MODE(ChannelMode));

#if defined(DMA_ALTERNATE_DATA)
    if (SelectDataStruct == DMA_CTRL_DATA_PRIMARY) {
#endif
        ChnlData = &DMA_ControlTable[DMA_Channel];
#if defined(DMA_ALTERNATE_DATA)
    } else {
        ChnlData = &DMA_ControlTable[32 + DMA_Channel];
    }
#endif

    ChnlData->DMA_Control.w = (ChnlData->DMA_Control.w & ~(DMA_CHANNEL_CFG_N_MINUS_1_Msk | DMA_CHANNEL_CFG_CYCLE_CTRL_Msk | DMA_CHANNEL_CFG_NEXT_USEBURST_Msk)) |
                              ((CycleSize - 1) << DMA_CHANNEL_CFG_N_MINUS_1_Pos) | ((uint32_t)ChannelMode);
}

/**
 * @brief  Return the number of remaining transfers in the current DMA channel cycle.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  SelectDataStruct: @ref DMA_DataStructSelection_TypeDef - specify
 *         the primary / alternate control data table to check.
 * @return The number of the remaining transfers in the current
 *         DMA channel cycle and the current control data structure.
 */
uint32_t DMA_GetChannelTransferCounter(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct)
{
    DMA_CtrlData_TypeDef* ChnlData;

    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(SelectDataStruct));

#if defined(DMA_ALTERNATE_DATA)
    if (SelectDataStruct == DMA_CTRL_DATA_PRIMARY) {
#endif
        ChnlData = &DMA_ControlTable[DMA_Channel];
#if defined(DMA_ALTERNATE_DATA)
    } else {
        ChnlData = &DMA_ControlTable[32 + DMA_Channel];
    }
#endif

    return (((ChnlData->DMA_Control.w & DMA_CHANNEL_CFG_N_MINUS_1_Msk) >> DMA_CHANNEL_CFG_N_MINUS_1_Pos) + 1);
}

/**
 * @brief  Select data structure for DMA channel.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  SelectDataStruct: @ref DMA_DataStructSelection_TypeDef - specify
 *         the primary / alternate data structure to use.
 * @return None.
 */
void DMA_ChannelSetControl(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct)
{
    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(SelectDataStruct));

    /* Primary or alternate control data structure selection. */
    if (SelectDataStruct == DMA_CTRL_DATA_PRIMARY) {
        MDR_DMA->CHNL_PRI_ALT_CLR = (1 << DMA_Channel); /* Use primary. */
    } else {
        MDR_DMA->CHNL_PRI_ALT_SET = (1 << DMA_Channel); /* Use alternate. */
    }
}

/**
 * @brief  Get data structure used by DMA channel.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @return @ref DMA_DataStructSelection_TypeDef - data structure (primary or alternate) used by DMA channel.
 */
DMA_DataStructSelection_TypeDef DMA_ChannelGetControl(uint8_t DMA_Channel)
{
    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));

    return (DMA_DataStructSelection_TypeDef)((MDR_DMA->CHNL_PRI_ALT_CLR & (1 << DMA_Channel)) != 0);
}

/**
 * @brief  Return the current DMA channel operating mode.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of the @ref DMA_ValidChannel_TypeDef.
 * @param  SelectDataStruct: @ref DMA_DataStructSelection_TypeDef - specify
 *         the primary / alternate control data table to check.
 * @return @ref DMA_OperatingMode_TypeDef - the current DMA channel state.
 */
DMA_OperatingMode_TypeDef DMA_GetChannelMode(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct)
{
    DMA_OperatingMode_TypeDef ChannelMode;
    DMA_CtrlData_TypeDef*     ChnlData;

    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(SelectDataStruct));

#if defined(DMA_ALTERNATE_DATA)
    if (SelectDataStruct == DMA_CTRL_DATA_PRIMARY) {
#endif
        ChnlData = &DMA_ControlTable[DMA_Channel];
#if defined(DMA_ALTERNATE_DATA)
    } else {
        ChnlData = &DMA_ControlTable[32 + DMA_Channel];
    }
#endif

    ChannelMode = (DMA_OperatingMode_TypeDef)(ChnlData->DMA_Control.w & DMA_CHANNEL_CFG_CYCLE_CTRL_Msk);
    if (ChannelMode == DMA_MODE_PER_SG_ALTERNATE) {
        ChannelMode = (DMA_OperatingMode_TypeDef)(ChnlData->DMA_Control.w & (DMA_CHANNEL_CFG_CYCLE_CTRL_Msk | DMA_CHANNEL_CFG_NEXT_USEBURST_Msk));
    }

    return ChannelMode;
}

/**
 * @brief  Check whether the specified DMA channel flag is set or not.
 * @param  DMA_Channel: Select a DMA channel.
 *         This parameter can be in the range from 0 to 31 or a value of @ref DMA_ValidChannel_TypeDef and
 *         is not used when the DMA_FLAG_DMA_ENA or DMA_FLAG_DMA_ERR flags are being checked.
 * @param  DMA_Flag: @ref DMA_Flags_TypeDef - specify the flag to check.
 * @return @ref FlagStatus - Current state of DMA_FLAG (SET or RESET).
 */
FlagStatus DMA_GetFlagStatus(uint8_t DMA_Channel, DMA_Flags_TypeDef DMA_Flag)
{
    FlagStatus Status = RESET;

    /* Check the parameters. */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_FLAG(DMA_Flag));

    /* Read the flag status. */
    switch (DMA_Flag) {
        case DMA_FLAG_DMA_ENABLED:
            Status = (FlagStatus)((MDR_DMA->STATUS & DMA_STATUS_MASTER_ENABLE) != 0);
            break;
        case DMA_FLAG_DMA_ERR:
            Status = (FlagStatus)((MDR_DMA->ERR_CLR & DMA_ERR_CLR_ERR_CLR) != 0);
            break;
        case DMA_FLAG_CHANNEL_ENABLED:
            Status = (FlagStatus)((MDR_DMA->CHNL_ENABLE_SET & (1 << DMA_Channel)) != 0);
            break;
        case DMA_FLAG_CHANNEL_MASK:
            Status = (FlagStatus)((MDR_DMA->CHNL_REQ_MASK_SET & (1 << DMA_Channel)) != 0);
            break;
        case DMA_FLAG_CHANNEL_WAIT:
            Status = (FlagStatus)((MDR_DMA->WAITONREQ_STATUS & (1 << DMA_Channel)) != 0);
            break;
        case DMA_FLAG_CHANNEL_BURST:
            Status = (FlagStatus)((MDR_DMA->CHNL_USEBURST_SET & (1 << DMA_Channel)) != 0);
            break;
        case DMA_FLAG_CHANNEL_ALTERNATE:
            Status = (FlagStatus)((MDR_DMA->CHNL_PRI_ALT_SET & (1 << DMA_Channel)) != 0);
            break;
        case DMA_FLAG_CHANNEL_PRIORITY:
            Status = (FlagStatus)((MDR_DMA->CHNL_PRIORITY_SET & (1 << DMA_Channel)) != 0);
            break;
    }
    return Status;
}

/**
 * @brief  Clear the DMA Error bit.
 * @param  None.
 * @return None.
 */
void DMA_ClearError(void)
{
    MDR_DMA->ERR_CLR = DMA_ERR_CLR_ERR_CLR;
}

/**
 * @brief  Get the current DMA state.
 * @return @ref DMA_State_TypeDef - the DMA state.
 */
DMA_State_TypeDef DMA_GetState(void)
{
    return (DMA_State_TypeDef)(MDR_DMA->STATUS & DMA_STATUS_STATE_Msk);
}

/** @} */ /* End of the group DMA_Exported_Functions */

/** @} */ /* End of the group DMA */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_dma.c */

