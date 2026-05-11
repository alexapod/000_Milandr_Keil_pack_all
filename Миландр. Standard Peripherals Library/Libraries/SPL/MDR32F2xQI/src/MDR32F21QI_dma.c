/**
 *******************************************************************************
 * @file    MDR32F21QI_dma.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
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
#include "MDR32F21QI_dma.h"

/** @addtogroup __MDR32F21QI_StdPeriph_Driver MDR32F21QI Standard Peripherial Driver
 * @{
 */

#if defined(USE_MDR32F21QI)

/** @defgroup DMA DMA
 * @{
 */

/** @addtogroup DMA_Private_Variables DMA Private Variables
 * @{
 */

/**
 * @brief DMA Channel Control Data Table
 */

/* Select data alignment */
#if (DMA_CHANNELS_NUMBER == 1)
#define DATA_ALIGN 32
#elif (DMA_CHANNELS_NUMBER == 2)
#define DATA_ALIGN 64
#elif ((DMA_CHANNELS_NUMBER >= 3) && (DMA_CHANNELS_NUMBER <= 4))
#define DATA_ALIGN 128
#elif ((DMA_CHANNELS_NUMBER >= 5) && (DMA_CHANNELS_NUMBER <= 8))
#define DATA_ALIGN 256
#elif ((DMA_CHANNELS_NUMBER >= 9) && (DMA_CHANNELS_NUMBER <= 16))
#define DATA_ALIGN 512
#elif ((DMA_CHANNELS_NUMBER >= 17) && (DMA_CHANNELS_NUMBER <= 32))
#define DATA_ALIGN 1024
#endif

#if defined(__ICCARM__) /* IAR Compiler */
#pragma data_alignment = DATA_ALIGN
DMA_CtrlData_TypeDef DMA_ControlTable[DMA_CHANNELS_NUMBER * (1 + DMA_ALTERNATE_DATA)];
#elif defined(__CMCARM__)      /* Phyton CMC-ARM Compiler */
#pragma locate DMA_ControlTable 0x20000000 noinit
DMA_CtrlData_TypeDef DMA_ControlTable[DMA_CHANNELS_NUMBER * (1 + DMA_ALTERNATE_DATA)];
#elif defined(__ARMCC_VERSION) /* ARM Compiler */
DMA_CtrlData_TypeDef DMA_ControlTable[DMA_CHANNELS_NUMBER * (1 + DMA_ALTERNATE_DATA)] __attribute__((aligned(DATA_ALIGN)));
#elif defined(__GNUC__)        /* CNU Compiler */
DMA_CtrlData_TypeDef DMA_ControlTable[DMA_CHANNELS_NUMBER * (1 + DMA_ALTERNATE_DATA)] __attribute__((aligned(DATA_ALIGN)));
#endif

/** @} */ /* End of group DMA_Private_Variables */

/** @defgroup DMA_Exported_Functions DMA Exported Functions
 * @{
 */

/**
 * @brief  Deinitializes the DMA registers to their default reset values
 *         and clears pending DMA NVIC interrupt request.
 * @param  None.
 * @retval None.
 */
void DMA_DeInit(void)
{
    MDR_DMA->CFG               = 0x00;                  /* Master Enable Off */
    MDR_DMA->CTRL_BASE_PTR     = 0x00;                  /* Control data base pointer */
    MDR_DMA->CHNL_SW_REQUEST   = 0x00;                  /* Disable all sw requests */
    MDR_DMA->CHNL_USEBURST_SET = 0xFFFFFFFF;            /* Disable burst mode */
    MDR_DMA->CHNL_REQ_MASK_SET = 0xFFFFFFFF;            /* Disable all channels */

    MDR_DMA->CHNL_ENABLE_CLR   = 0xFFFFFFFF;            /* Clear channel enable */
    MDR_DMA->CHNL_PRI_ALT_CLR  = 0xFFFFFFFF;            /* Reset to primary data structure */
    MDR_DMA->CHNL_PRIORITY_CLR = 0xFFFFFFFF;            /* Reset to default priority */
    MDR_DMA->ERR_CLR           = DMA_ERR_CLR_ERR_CLR;   /* Clear dma_err status */

    MDR_DMA->CFG               = DMA_CFG_MASTER_ENABLE; /* Master Enable On */
    MDR_DMA->CHNL_REQ_MASK_SET = 0xFFFFFFFF;
    MDR_DMA->CHNL_ENABLE_SET   = 0xFFFFFFFF;            /* Enablee all channels */
    NVIC_ClearPendingIRQ(DMA_IRQn);
}

/**
 * @brief  Initializes the DMA control data structure according to the specified parameters.
 * @param  DMA_CtrlDataPtr: pointer to a @ref DMA_CtrlData_InitTypeDef structure
 *         that contains the control data structure to initialize.
 * @param  DMA_CtrlTablePtr: pointer to a @ref DMA_CtrlData_TypeDef structure that
 *         contains the initial control data configuration, provided by the application.
 * @retval None.
 */
void DMA_CtrlDataInit(DMA_CtrlData_InitTypeDef* DMA_CtrlDataPtr, DMA_CtrlData_TypeDef* DMA_CtrlTablePtr)
{
    /* Check DMA configuration parameters */
    assert_param(IS_DMA_CHANNELS(DMA_CHANNELS_NUMBER));

    /* Check the parameters */
    assert_param(IS_DMA_DATA_INC(DMA_CtrlDataPtr->DMA_SourceIncSize));
    assert_param(IS_DMA_DATA_INC(DMA_CtrlDataPtr->DMA_DestIncSize));
    assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_CtrlDataPtr->DMA_MemoryDataSize));
    assert_param(IS_DMA_MODE(DMA_CtrlDataPtr->DMA_Mode));
    assert_param(IS_DMA_CYCLE_SIZE(DMA_CtrlDataPtr->DMA_CycleSize));
    assert_param(IS_DMA_ARB_PERIOD(DMA_CtrlDataPtr->DMA_ArbitrationPeriod));

    /* DMA Source Data End Address */
    if (DMA_CtrlDataPtr->DMA_SourceIncSize == DMA_DATA_INC_NO) {
        DMA_CtrlTablePtr->DMA_SourceEndAddr = DMA_CtrlDataPtr->DMA_SourceBaseAddr;
    } else {
        DMA_CtrlTablePtr->DMA_SourceEndAddr = (DMA_CtrlDataPtr->DMA_SourceBaseAddr +
                                               (((uint32_t)DMA_CtrlDataPtr->DMA_CycleSize - 1) << ((uint32_t)(DMA_CtrlDataPtr->DMA_SourceIncSize))));
    }

    /* DMA Destination Data End Address */
    if (DMA_CtrlDataPtr->DMA_Mode == DMA_MODE_MEM_SG_PRIMARY) {
        /* Memory Scatter-Gather mode */
        DMA_CtrlTablePtr->DMA_DestEndAddr = (DMA_CtrlDataPtr->DMA_DestBaseAddr + 12);
    } else {
        /* Other modes */
        if (DMA_CtrlDataPtr->DMA_DestIncSize == DMA_DATA_INC_NO) {
            DMA_CtrlTablePtr->DMA_DestEndAddr = DMA_CtrlDataPtr->DMA_DestBaseAddr;
        } else {
            DMA_CtrlTablePtr->DMA_DestEndAddr = (DMA_CtrlDataPtr->DMA_DestBaseAddr +
                                                 (((uint32_t)DMA_CtrlDataPtr->DMA_CycleSize - 1) << ((uint32_t)(DMA_CtrlDataPtr->DMA_DestIncSize))));
        }
    }

    /* DMA Control Data */
    DMA_CtrlTablePtr->DMA_Control.w = (((uint32_t)(DMA_CtrlDataPtr->DMA_DestIncSize) << DMA_CHANNEL_CFG_DST_INC_Pos) |
                                       DMA_CtrlDataPtr->DMA_MemoryDataSize |
                                       ((uint32_t)(DMA_CtrlDataPtr->DMA_SourceIncSize) << DMA_CHANNEL_CFG_SRC_INC_Pos) |
                                       DMA_CtrlDataPtr->DMA_ArbitrationPeriod |
                                       (((uint32_t)DMA_CtrlDataPtr->DMA_CycleSize - 1) << DMA_CHANNEL_CFG_N_MINUS_1_Pos) |
                                       DMA_CtrlDataPtr->DMA_Mode);
}

/**
 * @brief  Initializes the DMA Channel DMA_ControlTable structure according to the specified parameters.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @param  DMA_CtrlDataType - @ref DMA_DataStructSelection_TypeDef - data structure selection
 * @param  DMA_CtrlStruct: pointer to a @ref DMA_CtrlData_InitTypeDef structure that contains the initial
 *         control data configuration, provided by the application for the specified DMA Channel.
 * @retval None.
 */
void DMA_CtrlInit(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlDataType, DMA_CtrlData_InitTypeDef* DMA_CtrlStruct)
{
    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(DMA_CtrlDataType));

    if (DMA_CtrlDataType == DMA_CTRL_DATA_PRIMARY) {
        /* Primary Control Data Init */
        DMA_CtrlDataInit(DMA_CtrlStruct, &DMA_ControlTable[DMA_Channel]);
#if (DMA_ALTERNATE_DATA == 1)
    } else {
        /* Alternate Control Data Init */
        uint32_t StructPtr = (MDR_DMA->ALT_CTRL_BASE_PTR + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
        DMA_CtrlDataInit(DMA_CtrlStruct, (DMA_CtrlData_TypeDef*)StructPtr);
#endif
    }
}

/**
 * @brief  Initializes the DMA Scatter-Gather Task structure according to the specified parameters.
 * @param  DMA_Task: specifies the current task number. Begins with 0.
 * @param  DMA_CtrlStruct: pointer to a @ref DMA_CtrlData_InitTypeDef structure
 *         that contains the control data information for the specified task.
 * @param  DMA_SG_TaskArray: pointer to a @ref DMA_CtrlData_TypeDef array that
 *         contains the copy of the alternate control data information for the specified task.
 * @retval None.
 */
void DMA_SG_CtrlInit(uint32_t DMA_Task, DMA_CtrlData_TypeDef* DMA_SG_TaskArray, DMA_CtrlData_InitTypeDef* DMA_CtrlStruct)
{
    DMA_CtrlDataInit(DMA_CtrlStruct, &DMA_SG_TaskArray[DMA_Task]);
}

/**
 * @brief  Initializes the DMA Channel in Memory Scatter-Gather mode.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @param  DMA_SG_InitStruct: pointer to a @ref DMA_SG_Channel_InitTypeDef array that
 *         contains the configuration information for the specified DMA Channel.
 * @retval None.
 */
void DMA_SG_Init(uint8_t DMA_Channel, DMA_SG_Channel_InitTypeDef* DMA_SG_InitStruct)
{
    DMA_CtrlData_InitTypeDef DMA_PriCtrlData;

    /* Check the parameters */
    assert_param(DMA_ALTERNATE_DATA == 1);
    assert_param(DMA_SG_InitStruct != 0);
    assert_param(DMA_SG_InitStruct->DMA_SG_TaskNumber != 0);
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(DMA_SG_InitStruct->DMA_UseHighPriority));
    assert_param(IS_FUNCTIONAL_STATE(DMA_SG_InitStruct->DMA_UseBurst));

    /* Check the CTRL_BASE_PTR initialization */
    MDR_DMA->CTRL_BASE_PTR = (uint32_t)DMA_ControlTable;

    /* Primary Control Data Init */
    DMA_PriCtrlData.DMA_SourceBaseAddr    = (uint32_t)(DMA_SG_InitStruct->DMA_SG_TaskArray);
    DMA_PriCtrlData.DMA_DestBaseAddr      = (MDR_DMA->ALT_CTRL_BASE_PTR + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
    DMA_PriCtrlData.DMA_SourceIncSize     = DMA_DATA_INC_32BIT;
    DMA_PriCtrlData.DMA_DestIncSize       = DMA_DATA_INC_32BIT;
    DMA_PriCtrlData.DMA_MemoryDataSize    = DMA_MEMORY_DATA_SIZE_32BIT;
    DMA_PriCtrlData.DMA_Mode              = DMA_MODE_MEM_SG_PRIMARY;
    DMA_PriCtrlData.DMA_CycleSize         = DMA_SG_InitStruct->DMA_SG_TaskNumber << 2;
    DMA_PriCtrlData.DMA_ArbitrationPeriod = DMA_ARB_AFTER_4;

    DMA_CtrlDataInit(&DMA_PriCtrlData, &DMA_ControlTable[DMA_Channel]);

    /* Burst mode */
    if (DMA_SG_InitStruct->DMA_UseBurst == ENABLE) {
        MDR_DMA->CHNL_USEBURST_SET = (1 << DMA_Channel);
    } else {
        MDR_DMA->CHNL_USEBURST_CLR = (1 << DMA_Channel);
    }

    /* Channel mask clear */
    MDR_DMA->CHNL_REQ_MASK_CLR = (1 << DMA_Channel);

    /* Enable channel */
    MDR_DMA->CHNL_ENABLE_SET = (1 << DMA_Channel);

    /* Primary - Alternate control data structure selection */
    MDR_DMA->CHNL_PRI_ALT_CLR = (1 << DMA_Channel); /* Use Primary */

    /* Channel priority set */
    if (DMA_SG_InitStruct->DMA_UseHighPriority == ENABLE) {
        MDR_DMA->CHNL_PRIORITY_SET = (1 << DMA_Channel); /* High priority */
    } else {
        MDR_DMA->CHNL_PRIORITY_CLR = (1 << DMA_Channel); /* Default priority */
    }
}

/**
 * @brief  Initializes the DMA Channel according to
 *         the specified parameters in the DMA_InitStruct.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @param  DMA_InitStruct: pointer to a @ref DMA_Channel_InitTypeDef structure that
 *         contains the configuration information for the specified DMA Channel.
 * @retval None.
 */
void DMA_Init(uint8_t DMA_Channel, DMA_Channel_InitTypeDef* DMA_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(DMA_InitStruct->DMA_UseHighPriority));
    assert_param(IS_FUNCTIONAL_STATE(DMA_InitStruct->DMA_UseBurst));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(DMA_InitStruct->DMA_SelectDataStructure));

    /* Check the CTRL_BASE_PTR initialisation */
    MDR_DMA->CTRL_BASE_PTR = (uint32_t)DMA_ControlTable;

    /* Primary Control Data Init */
    if (DMA_InitStruct->DMA_PriCtrlData) {
        DMA_CtrlDataInit(DMA_InitStruct->DMA_PriCtrlData, &DMA_ControlTable[DMA_Channel]);
    }

#if (DMA_ALTERNATE_DATA == 1)
    /* Alternate Control Data Init */
    if (DMA_InitStruct->DMA_AltCtrlData) {
        uint32_t StructPtr = (MDR_DMA->ALT_CTRL_BASE_PTR + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
        DMA_CtrlDataInit(DMA_InitStruct->DMA_AltCtrlData, (DMA_CtrlData_TypeDef*)StructPtr);
    }
#endif

    /* Burst mode */
    if (DMA_InitStruct->DMA_UseBurst == ENABLE) {
        MDR_DMA->CHNL_USEBURST_SET = (1 << DMA_Channel);
    } else {
        MDR_DMA->CHNL_USEBURST_CLR = (1 << DMA_Channel);
    }

    /* Channel mask clear */
    MDR_DMA->CHNL_REQ_MASK_CLR = (1 << DMA_Channel);

    /* Enable channel */
    MDR_DMA->CHNL_ENABLE_SET = (1 << DMA_Channel);

    /* Primary or Alternate control data structure selection */
    if (DMA_InitStruct->DMA_SelectDataStructure == DMA_CTRL_DATA_PRIMARY) {
        MDR_DMA->CHNL_PRI_ALT_CLR = (1 << DMA_Channel); /* Use Primary */
    } else {
        MDR_DMA->CHNL_PRI_ALT_SET = (1 << DMA_Channel); /* Use Alternate */
    }

    /* Channel priority set */
    if (DMA_InitStruct->DMA_UseHighPriority == ENABLE) {
        MDR_DMA->CHNL_PRIORITY_SET = (1 << DMA_Channel); /* High priority */
    } else {
        MDR_DMA->CHNL_PRIORITY_CLR = (1 << DMA_Channel); /* Default priority */
    }
}

/**
 * @brief  Fills each DMA_InitStruct member with its default value.
 * @param  DMA_InitStruct: pointer to a @ref DMA_Channel_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
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
 * @brief  Fills each DMA_SG_InitStruct member with its default value.
 * @param  DMA_SG_InitStruct: pointer to a @ref DMA_SG_Channel_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
 */
void DMA_SG_StructInit(DMA_SG_Channel_InitTypeDef* DMA_SG_InitStruct)
{
    DMA_SG_InitStruct->DMA_SG_TaskArray    = 0;
    DMA_SG_InitStruct->DMA_SG_TaskNumber   = 0;
    DMA_SG_InitStruct->DMA_UseHighPriority = DISABLE;
    DMA_SG_InitStruct->DMA_UseBurst        = DISABLE;
}

/**
 * @brief  Enables or disables the specified DMA Channel.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @param  NewState - @ref FunctionalState - new state of the DMA Channel.
 * @retval None.
 */
void DMA_Cmd(uint8_t DMA_Channel, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Channel Enable/Disable */
    if (NewState != DISABLE) {
        MDR_DMA->CHNL_ENABLE_SET = (1 << DMA_Channel);
    } else {
        MDR_DMA->CHNL_ENABLE_CLR = (1 << DMA_Channel);
    }
}

/**
 * @brief  Generates the specified DMA Channel software request.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @retval None.
 */
void DMA_Request(uint8_t DMA_Channel)
{
    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));

    /* Set SW Request */
    MDR_DMA->CHNL_SW_REQUEST = (1 << DMA_Channel);
}

/**
 * @brief  Clears the DMA Error bit.
 * @param  None.
 * @retval None.
 */
void DMA_ClearError(void)
{
    MDR_DMA->ERR_CLR = DMA_ERR_CLR_ERR_CLR_Msk;
}

/**
 * @brief  Reload DMA channel CycleSize and ChannelMode.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @param  SelectDataStruct - @ref DMA_DataStructSelection_TypeDef - data structure to change.
 * @param  CycleSize: new cycle size.
 * @param  ChannelMode - @ref DMA_OperatingMode_TypeDef - new channel mode.
 * @retval None.
 */
void DMA_ChannelReloadCycle(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef SelectDataStruct,
                            uint32_t CycleSize, DMA_OperatingMode_TypeDef ChannelMode)
{
    uint32_t              DMA_TableBase, Temp;
    DMA_CtrlData_TypeDef* ChnlData;

    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(SelectDataStruct));
    assert_param(IS_DMA_CYCLE_SIZE(CycleSize));
    assert_param(IS_DMA_MODE(ChannelMode));

    if (SelectDataStruct == DMA_CTRL_DATA_PRIMARY) {
        DMA_TableBase = MDR_DMA->CTRL_BASE_PTR;
#if (DMA_ALTERNATE_DATA == 1)
    } else {
        DMA_TableBase = MDR_DMA->ALT_CTRL_BASE_PTR;
#endif
    }

    ChnlData = (DMA_CtrlData_TypeDef*)(DMA_TableBase + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
    Temp     = (ChnlData->DMA_Control.w & ~DMA_CHANNEL_CFG_N_MINUS_1_Msk) |
           ((CycleSize - 1) << DMA_CHANNEL_CFG_N_MINUS_1_Pos) | ((uint32_t)ChannelMode);
    ChnlData->DMA_Control.w = Temp;
}

/**
 * @brief  Returns the number of remaining transfers
 *         in the current DMA Channel cycle.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @param  DMA_CtrlData - @ref DMA_DataStructSelection_TypeDef - specifies
 *         the primary / alternate control data table to check.
 * @retval The number of remaining transfers in the current
 *         DMA Channel cycle and the current control data structure.
 */
uint32_t DMA_GetChannelTransferCounter(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlData)
{
    DMA_CtrlData_TypeDef* StructPtr; /* Pointer to the channels's data structure */

    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(DMA_CtrlData));

    /* Init the control data pointer */
    if (DMA_CtrlData == DMA_CTRL_DATA_PRIMARY) {
        StructPtr = (DMA_CtrlData_TypeDef*)(MDR_DMA->CTRL_BASE_PTR + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
    } else {
        StructPtr = (DMA_CtrlData_TypeDef*)(MDR_DMA->ALT_CTRL_BASE_PTR + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
    }

    /* Read the number of remaining transfers */
    return (((StructPtr->DMA_Control.w & DMA_CHANNEL_CFG_N_MINUS_1_Msk) >> DMA_CHANNEL_CFG_N_MINUS_1_Pos) + 1);
}

/**
 * @brief  Returns current DMA Channel state.
 * @param  DMA_Channel: can be 0 to 31 or
 *         a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 * @param  DMA_CtrlData - @ref DMA_DataStructSelection_TypeDef - specifies
 *         the primary / alternate control data table to check.
 * @retval @ref DMA_OperatingMode_TypeDef - current DMA Channel state.
 */
DMA_OperatingMode_TypeDef DMA_GetChannelState(uint8_t DMA_Channel, DMA_DataStructSelection_TypeDef DMA_CtrlData)
{
    DMA_CtrlData_TypeDef* StructPtr; /* Pointer to the channels's data structure */

    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_SELECT_DATA_STRUCTURE(DMA_CtrlData));

    /* Init the control data pointer */
    if (DMA_CtrlData == DMA_CTRL_DATA_PRIMARY) {
        StructPtr = (DMA_CtrlData_TypeDef*)(MDR_DMA->CTRL_BASE_PTR + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
    } else {
        StructPtr = (DMA_CtrlData_TypeDef*)(MDR_DMA->ALT_CTRL_BASE_PTR + (DMA_Channel * sizeof(DMA_CtrlData_TypeDef)));
    }

    /* Read current DMA Channel state */
    return (DMA_OperatingMode_TypeDef)(StructPtr->DMA_Control.w & DMA_CHANNEL_CFG_CYCLE_CTRL_Msk);
}

/**
 * @brief  Checks whether the specified DMA Channel flag is set or not.
 * @param  DMA_Channel: can be 0 to 31 or a value of @ref DMA_ValidChannels_TypeDef to select the DMA Channel.
 *         Does not matter when check DMA_FLAG_DMA_ENA or DMA_FLAG_DMA_ERR flags.
 * @param  DMA_Flag - @ref DMA_Flags_TypeDef - specifies the flag to check.
 * @retval @ref FlagStatus - Current state of DMA_FLAG (SET or RESET).
 */
FlagStatus DMA_GetFlagStatus(uint8_t DMA_Channel, DMA_Flags_TypeDef DMA_Flag)
{
    FlagStatus Status;

    /* Check the parameters */
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_DMA_FLAG(DMA_Flag));

    /* Read Flag Status */
    switch (DMA_Flag) {
        case DMA_FLAG_DMA_ENABLED:
            Status = (FlagStatus)((MDR_DMA->STATUS & DMA_STATUS_MASTER_ENABLE) != 0);
            break;
        case DMA_FLAG_DMA_ERR:
            Status = (FlagStatus)((MDR_DMA->ERR_CLR & DMA_ERR_CLR_ERR_CLR_Msk) == 0);
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
 * @brief  Get current DMA state.
 * @retval @ref DMA_State_TypeDef - DMA state.
 */
DMA_State_TypeDef DMA_GetState(void)
{
    return (DMA_State_TypeDef)(MDR_DMA->STATUS & DMA_STATUS_STATE_Msk);
}

/** @} */ /* End of group DMA_Exported_Functions */

/** @} */ /* End of group DMA */

#endif    /* #if defined (USE_MDR32F21QI) */

/** @} */ /* End of group __MDR32F21QI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F21QI_dma.c */

