/**
 *******************************************************************************
 * @file    MDR32VF0xI_crc.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/01/2025
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
#include "MDR32VF0xI_crc.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup CRC CRC
 * @{
 */

/** @defgroup CRC_Exported_Functions CRC Exported Functions
 * @{
 */

/**
 * @brief  Reset the CRC peripheral registers to their default reset values.
 * @param  None.
 * @return None.
 */
void CRC_DeInit(void)
{
    MDR_CRC->CTRL = 0x00000000;
    MDR_CRC->STAT = CRC_STAT_FIFOOVER; /* Reset FIFOOVER bit. */
    MDR_CRC->VAL  = 0x00000000;
    MDR_CRC->POL  = 0x00010001;
}

/**
 * @brief  Initialize the CRC peripheral according to the specified
 *         parameters in the CRC_InitStruct.
 * @param  CRC_InitStruct: The pointer to the @ref CRC_InitTypeDef structure
 *         that contains the configuration information for the specified CRC peripheral.
 * @return None.
 */
void CRC_Init(const CRC_InitTypeDef* CRC_InitStruct)
{
    /* Check the parameters. */
    assert_param(IS_CRC_DATA_SIZE(CRC_InitStruct->CRC_DataSize));
    assert_param(IS_CRC_DATA_LOAD_SIZE(CRC_InitStruct->CRC_DataLoadSize));
    assert_param(IS_FUNCTIONAL_STATE(CRC_InitStruct->CRC_DMAState));
    assert_param(IS_CRC_ENDIAN_MODE(CRC_InitStruct->CRC_EndianMode));
    assert_param(IS_CRC_POLYNOM(CRC_InitStruct->CRC_Polynom));
    assert_param(IS_CRC_START_VALUE(CRC_InitStruct->CRC_StartValue));

    /* Set CRC CTRL register. */
    MDR_CRC->CTRL = (uint32_t)(CRC_InitStruct->CRC_DataSize) |
                    (uint32_t)(CRC_InitStruct->CRC_DataLoadSize) |
                    ((uint32_t)CRC_InitStruct->CRC_DMAState << CRC_CTRL_DMAEN_Pos) |
                    (uint32_t)(CRC_InitStruct->CRC_EndianMode);

    /* Set an initial polynom. */
    MDR_CRC->POL = CRC_InitStruct->CRC_Polynom;

    /* Set an initial value. */
    MDR_CRC->VAL = CRC_InitStruct->CRC_StartValue;
}

/**
 * @brief  Fill each CRC_InitStruct member with its default value.
 * @param  CRC_InitStruct: The pointer to the @ref CRC_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
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
 * @brief  Enable or disable the specified CRC peripheral.
 * @param  NewState: @ref FunctionalState - a new state of the CRC peripheral.
 * @return None.
 */
void CRC_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_CRC->CTRL |= CRC_CTRL_CRCEN;
    } else {
        MDR_CRC->CTRL &= ~CRC_CTRL_CRCEN;
    }
}

/**
 * @brief  Get the CRC peripheral work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the CRC peripheral.
 */
FunctionalState CRC_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_CRC->CTRL & CRC_CTRL_CRCEN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set the input data size.
 * @param  DataSize: @ref CRC_DataSize_TypeDef - the size of the input data.
 * @return None.
 */
void CRC_SetDataSize(CRC_DataSize_TypeDef DataSize)
{
    uint32_t TempReg;

    /* Check the parameters. */
    assert_param(IS_CRC_DATA_SIZE(DataSize));

    /* Set data size */
    TempReg = MDR_CRC->CTRL & (~CRC_CTRL_DCSIZE_Msk);
    TempReg |= (uint32_t)DataSize;

    MDR_CRC->CTRL = TempReg;
}

/**
 * @brief  Set the size of the loaded data.
 * @param  DataLoadSize: @ref CRC_DataLoadSize_TypeDef - the size of the loaded data.
 * @return None.
 */
void CRC_SetDataLoadSize(CRC_DataLoadSize_TypeDef DataLoadSize)
{
    uint32_t TempReg;

    /* Check the parameters. */
    assert_param(IS_CRC_DATA_LOAD_SIZE(DataLoadSize));

    /* Set the size of the loaded data. */
    TempReg = MDR_CRC->CTRL & (~CRC_CTRL_DLSIZE_Msk);
    TempReg |= (uint32_t)DataLoadSize;

    MDR_CRC->CTRL = TempReg;
}

/**
 * @brief  Enable or disable the CRC DMA request.
 * @param  NewState: @ref FunctionalState - a new state of the CRC DMA request.
 * @return None.
 */
void CRC_DMACmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_CRC->CTRL |= CRC_CTRL_DMAEN;
    } else {
        MDR_CRC->CTRL &= ~CRC_CTRL_DMAEN;
    }
}

/**
 * @brief  Get the CRC DMA request work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the CRC DMA request.
 */
FunctionalState CRC_GetDMACmdState(void)
{
    FunctionalState State;

    if ((MDR_CRC->CTRL & CRC_CTRL_DMAEN) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set the endian mode.
 * @param  EndianMode: @ref CRC_EndianMode_TypeDef - a new value of the CRC endian mode.
 * @return None.
 */
void CRC_SetEndianMode(CRC_EndianMode_TypeDef EndianMode)
{
    /* Check the parameters. */
    assert_param(IS_CRC_ENDIAN_MODE(EndianMode));

    if (EndianMode != CRC_MODE_LITTLE_ENDIAN) {
        MDR_CRC->CTRL |= CRC_CTRL_DATAINV;
    } else {
        MDR_CRC->CTRL &= ~CRC_CTRL_DATAINV;
    }
}

/**
 * @brief  Set the CRC polynom.
 * @note   Bits 0 and 16 will be always set to 1.
 * @param  Polynom: A new value corresponding to the CRC polynom.
 *         This parameter can be a number from 0x10001 to 0x1FFFF.
 * @return None.
 */
void CRC_SetPolynom(uint32_t Polynom)
{
    /* Check the parameters. */
    assert_param(IS_CRC_POLYNOM(Polynom));

    MDR_CRC->POL = Polynom;
}

/**
 * @brief  Get the CRC polynom.
 * @param  None.
 * @return Current CRC polynom value. Bits 0 and 16 are always set to 1.
 */
uint32_t CRC_GetPolynom(void)
{
    return MDR_CRC->POL;
}

/**
 * @brief  Set an initial value for the CRC calculation.
 * @param  StartValue: An initial CRC value.
 *         This parameter can be a number from 0x00000 to 0x1FFFF.
 * @return None.
 */
void CRC_SetStartValue(uint32_t StartValue)
{
    /* Check the parameters. */
    assert_param(IS_CRC_START_VALUE(StartValue));

    MDR_CRC->VAL = StartValue;
}

/**
 * @brief  Check whether the specified CRC status flag is set or not.
 * @param  CRC_Flag: @ref CRC_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - the state of a current status flag (SET or RESET).
 */
FlagStatus CRC_GetFlagStatus(CRC_Flags_TypeDef CRC_Flag)
{
    FlagStatus Flag;

    /* Check the parameters. */
    assert_param(IS_CRC_STATUS_FLAG(CRC_Flag));

    if ((MDR_CRC->STAT & (uint32_t)CRC_Flag) != 0) {
        Flag = SET;
    } else {
        Flag = RESET;
    }

    return (Flag);
}

/**
 * @brief  Return a combined value of the CRC status flags.
 * @param  None.
 * @return A combined value of CRC status flags (@ref CRC_Flags_TypeDef).
 */
uint32_t CRC_GetStatus(void)
{
    return MDR_CRC->STAT;
}

/**
 * @brief  Clear the FIFO overloaded flag.
 * @param  None.
 * @return None.
 */
void CRC_ClearFIFOOverFlag(void)
{
    MDR_CRC->STAT = CRC_STAT_FIFOOVER;
}

/**
 * @brief  Write new data to CRC FIFO.
 * @param  Data: Data loaded into FIFO.
 * @return None.
 */
void CRC_WriteData(uint32_t Data)
{
    MDR_CRC->DATAI = Data;
}

/**
 * @brief  Return the CRC result.
 * @param  None.
 * @return CRC result register.
 */
uint16_t CRC_GetCRC(void)
{
    return (uint16_t)(MDR_CRC->VAL & CRC_VAL_CRCOUT_Msk);
}

/** @} */ /* End of the group CRC_Exported_Functions */

/** @} */ /* End of the group CRC */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_crc.c */

