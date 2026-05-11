/**
 *******************************************************************************
 * @file    MDR32F21QI_crc.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    19/05/2023
 * @brief   This file contains all the CRC firmware functions.
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
#include "MDR32F21QI_crc.h"

/** @addtogroup __MDR32F21QI_StdPeriph_Driver MDR32F21QI Standard Peripherial Driver
 * @{
 */

#if defined(USE_MDR32F21QI)

/** @addtogroup CRC CRC
 * @{
 */

/** @defgroup CRC_Exported_Functions CRC Exported Functions
 * @{
 */

/**
 * @brief  Resets the CRC peripheral registers to their default reset values.
 * @param  None.
 * @retval None.
 */
void CRC_DeInit(void)
{
    MDR_CRC->CTRL = 0x00000000;
    MDR_CRC->STAT = CRC_STAT_FIFOOVER; // Reset FIFOOVER bit
    MDR_CRC->VAL  = 0x00000000;
    MDR_CRC->POL  = 0x00000000;
}

/**
 * @brief  Initializes the CRC peripheral according to the specified
 *         parameters in the CRC_InitStruct.
 * @param  CRC_InitStruct: pointer to a @ref CRC_InitTypeDef structure
 *         that contains the configuration information for the specified CRC peripheral.
 * @retval None.
 */
void CRC_Init(CRC_InitTypeDef* CRC_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_CRC_DATA_SIZE(CRC_InitStruct->CRC_DataSize));
    assert_param(IS_CRC_DATA_LOAD_SIZE(CRC_InitStruct->CRC_DataLoadSize));
    assert_param(IS_FUNCTIONAL_STATE(CRC_InitStruct->CRC_DMAState));
    assert_param(IS_CRC_ENDIAN_MODE(CRC_InitStruct->CRC_EndianMode));
    assert_param(IS_CRC_POLYNOM(CRC_InitStruct->CRC_Polynom));
    assert_param(IS_CRC_START_VALUE(CRC_InitStruct->CRC_StartValue));

    /* Set CRC CTRL register */
    MDR_CRC->CTRL = (uint32_t)CRC_InitStruct->CRC_DataSize |
                    (uint32_t)CRC_InitStruct->CRC_DataLoadSize |
                    ((uint32_t)CRC_InitStruct->CRC_DMAState << CRC_CTRL_DMAEN_Pos) |
                    (uint32_t)CRC_InitStruct->CRC_EndianMode;

    /* Set initial polynom */
    MDR_CRC->POL = CRC_InitStruct->CRC_Polynom;

    /* Set initial value */
    MDR_CRC->VAL = CRC_InitStruct->CRC_StartValue;
}

/**
 * @brief  Fills each CRC_InitStruct member with its default value.
 * @param  CRC_InitStruct: pointer to a @ref CRC_InitTypeDef structure
 *         that is to be initialized.
 * @retval None.
 */
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct)
{
    CRC_InitStruct->CRC_DataSize     = CRC_DATA_SIZE_8BIT;
    CRC_InitStruct->CRC_DataLoadSize = CRC_DATA_LOAD_SIZE_8BIT;
    CRC_InitStruct->CRC_DMAState     = DISABLE;
    CRC_InitStruct->CRC_EndianMode   = CRC_MODE_LITTLE_ENDIAN;
    CRC_InitStruct->CRC_Polynom      = 0;
    CRC_InitStruct->CRC_StartValue   = 0;
}

/**
 * @brief  Enables or disables the specified CRC peripheral.
 * @param  NewState - @ref FunctionalState - new state of the CRC peripheral.
 * @retval None.
 */
void CRC_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_CRC->CTRL |= CRC_CTRL_CRCEN;
    } else {
        MDR_CRC->CTRL &= ~CRC_CTRL_CRCEN;
    }
}

/**
 * @brief  Set the input data size.
 * @param  DataSize - @ref CRC_DataSize_TypeDef - the size of input data.
 * @retval None.
 */
void CRC_SetDataSize(CRC_DataSize_TypeDef DataSize)
{
    uint32_t TempReg;

    /* Check the parameters */
    assert_param(IS_CRC_DATA_SIZE(DataSize));

    /* Set data size */
    TempReg = MDR_CRC->CTRL & (~CRC_CTRL_DCSIZE_Msk);
    TempReg |= (uint32_t)DataSize;

    MDR_CRC->CTRL = TempReg;
}

/**
 * @brief  Set the load data size.
 * @param  DataLoadSize - @ref CRC_DataLoadSize_TypeDef - the size of loading data.
 * @retval None.
 */
void CRC_SetDataLoadSize(CRC_DataLoadSize_TypeDef DataLoadSize)
{
    uint32_t TempReg;

    /* Check the parameters */
    assert_param(IS_CRC_DATA_LOAD_SIZE(DataLoadSize));

    /* Set data load size */
    TempReg = MDR_CRC->CTRL & (~CRC_CTRL_DLSIZE_Msk);
    TempReg |= (uint32_t)DataLoadSize;

    MDR_CRC->CTRL = TempReg;
}

/**
 * @brief  Enables or disables the CRC DMA request.
 * @param  NewState - @ref FunctionalState - new state of the CRC DMA request.
 * @retval None.
 */
void CRC_DMACmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_CRC->CTRL |= CRC_CTRL_DMAEN;
    } else {
        MDR_CRC->CTRL &= ~CRC_CTRL_DMAEN;
    }
}

/**
 * @brief  Set the endian mode.
 * @param  EndianMode - @ref CRC_EndianMode_TypeDef - new value of the CRC endian mode.
 * @retval None.
 */
void CRC_SetEndianMode(CRC_EndianMode_TypeDef EndianMode)
{
    /* Check the parameters */
    assert_param(IS_CRC_ENDIAN_MODE(EndianMode));

    if (EndianMode != CRC_MODE_LITTLE_ENDIAN) {
        MDR_CRC->CTRL |= CRC_CTRL_DATAINV;
    } else {
        MDR_CRC->CTRL &= ~CRC_CTRL_DATAINV;
    }
}

/**
 * @brief  Set the CRC polynom.
 * @param  Polynom: new value of the CRC polynom.
 *         This parameter can be a number between 0x10001 and 0x1FFFF.
 * @retval None.
 */
void CRC_SetPolynom(uint32_t Polynom)
{
    /* Check the parameters */
    assert_param(IS_CRC_POLYNOM(Polynom));

    MDR_CRC->POL = Polynom;
}

/**
 * @brief  The initial value for CRC calculation.
 * @param  StartValue: the start CRC value.
 *         This parameter can be a number between 0x00000 and 0x1FFFF.
 * @retval None.
 */
void CRC_SetStartValue(uint32_t StartValue)
{
    /* Check the parameters */
    assert_param(IS_CRC_START_VALUE(StartValue));

    MDR_CRC->VAL = StartValue;
}

/**
 * @brief  Checks whether the specified CRC Status flag is set or not.
 * @param  CRC_Flag - @ref CRC_Flags_TypeDef - specifies the flag to check.
 * @retval @ref FlagStatus - Current Status flag state (SET or RESET).
 */
FlagStatus CRC_GetFlagStatus(CRC_Flags_TypeDef CRC_Flag)
{
    FlagStatus Flag;

    /* Check the parameters */
    assert_param(IS_CRC_STATUS_FLAG(CRC_Flag));

    if (MDR_CRC->STAT & (uint32_t)CRC_Flag) {
        Flag = SET;
    } else {
        Flag = RESET;
    }

    return (Flag);
}

/**
 * @brief  Checks whether the specified CRC Status flags is set or not.
 * @param  None.
 * @retval Combined value of CRC Status Flags (active @ref CRC_Flags_TypeDef).
 */
uint32_t CRC_GetStatus(void)
{
    return MDR_CRC->STAT;
}

/**
 * @brief  Clear the FIFO overloaded flag.
 * @param  None.
 * @retval None.
 */
void CRC_ClearFIFOOverFlag(void)
{
    MDR_CRC->STAT |= CRC_STAT_FIFOOVER;
}

/**
 * @brief  Write new data to CRC FIFO.
 * @param  Data: data value loaded into FIFO.
 * @retval None.
 */
void CRC_WriteData(uint32_t Data)
{
    MDR_CRC->DATAI = Data;
}

/**
 * @brief  Returns the CRC result.
 * @param  None.
 * @retval CRC result register value.
 */
uint16_t CRC_GetCRC(void)
{
    return (MDR_CRC->VAL & CRC_VAL_CRCOUT_Msk);
}

/** @} */ /* End of group CRC_Exported_Functions */

/** @} */ /* End of group CRC */

#endif    /* #if defined (USE_MDR32F21QI) */

/** @} */ /* End of group __MDR32F21QI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F21QI_crc.c */

