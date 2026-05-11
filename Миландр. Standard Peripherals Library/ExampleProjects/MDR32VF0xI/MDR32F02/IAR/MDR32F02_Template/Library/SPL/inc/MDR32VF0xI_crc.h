/**
 *******************************************************************************
 * @file    MDR32VF0xI_crc.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    18/04/2024
 * @brief   This file contains all the functions prototypes for the CRC
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
#ifndef MDR32VF0xI_CRC_H
#define MDR32VF0xI_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup CRC CRC
 * @{
 */

/** @defgroup CRC_Exported_Types CRC Exported Types
 * @{
 */

/**
 * @brief Data size when calculating CRC.
 */
typedef enum {
    CRC_DATA_SIZE_8BIT  = (((uint32_t)0x0) << CRC_CTRL_DCSIZE_Pos), /*!< 8-bit data. */
    CRC_DATA_SIZE_16BIT = (((uint32_t)0x1) << CRC_CTRL_DCSIZE_Pos), /*!< 16-bit data. */
    CRC_DATA_SIZE_32BIT = (((uint32_t)0x2) << CRC_CTRL_DCSIZE_Pos)  /*!< 32-bit data. */
} CRC_DataSize_TypeDef;

#define IS_CRC_DATA_SIZE(DS) (((DS) == CRC_DATA_SIZE_8BIT) ||  \
                              ((DS) == CRC_DATA_SIZE_16BIT) || \
                              ((DS) == CRC_DATA_SIZE_32BIT))

/**
 * @brief CRC data load size.
 */
typedef enum {
    CRC_DATA_LOAD_SIZE_8BIT  = (((uint32_t)0x0) << CRC_CTRL_DLSIZE_Pos), /*!< 8-bit load data size. */
    CRC_DATA_LOAD_SIZE_16BIT = (((uint32_t)0x1) << CRC_CTRL_DLSIZE_Pos), /*!< 16-bit load data size. */
    CRC_DATA_LOAD_SIZE_32BIT = (((uint32_t)0x2) << CRC_CTRL_DLSIZE_Pos)  /*!< 32-bit load data size. */
} CRC_DataLoadSize_TypeDef;

#define IS_CRC_DATA_LOAD_SIZE(DLS) (((DLS) == CRC_DATA_LOAD_SIZE_8BIT) ||  \
                                    ((DLS) == CRC_DATA_LOAD_SIZE_16BIT) || \
                                    ((DLS) == CRC_DATA_LOAD_SIZE_32BIT))

/**
 * @brief CRC endian mode.
 */
typedef enum {
    CRC_MODE_LITTLE_ENDIAN = (((uint32_t)0x0) << CRC_CTRL_DATAINV_Pos), /*!< Little endian - LSB first. */
    CRC_MODE_BIG_ENDIAN    = (((uint32_t)0x1) << CRC_CTRL_DATAINV_Pos)  /*!< Big endian - MSB first. */
} CRC_EndianMode_TypeDef;

#define IS_CRC_ENDIAN_MODE(EM) (((EM) == CRC_MODE_LITTLE_ENDIAN) || \
                                ((EM) == CRC_MODE_BIG_ENDIAN))

/**
 * @brief CRC status flags.
 */
typedef enum {
    CRC_CONV_COMP  = CRC_STAT_CONVCOMP_Msk,  /*!< CRC calculation is completed. */
    CRC_FIFO_FULL  = CRC_STAT_FIFOFULL_Msk,  /*!< Data FIFO is full. */
    CRC_FIFO_EMPTY = CRC_STAT_FIFOEMPTY_Msk, /*!< Data FIFO is empty. */
    CRC_FIFO_OVER  = CRC_STAT_FIFOOVER_Msk   /*!< Data FIFO is overflowed. */
} CRC_Flags_TypeDef;

#define IS_CRC_STATUS_FLAG(SF) (((SF) == CRC_CONV_COMP) ||  \
                                ((SF) == CRC_FIFO_FULL) ||  \
                                ((SF) == CRC_FIFO_EMPTY) || \
                                ((SF) == CRC_FIFO_OVER))

#define IS_CRC_STATUS_FLAGS(SF) (((SF) & ~((uint32_t)(CRC_CONV_COMP |  \
                                                      CRC_FIFO_FULL |  \
                                                      CRC_FIFO_EMPTY | \
                                                      CRC_FIFO_OVER))) == 0)

/**
 * @brief CRC init struct defintion.
 */
typedef struct {
    CRC_DataSize_TypeDef CRC_DataSize;         /*!< A size of the data in the CRC calculation.
                                                    This parameter can be a value of the @ref CRC_DataSize_TypeDef. */
    CRC_DataLoadSize_TypeDef CRC_DataLoadSize; /*!< A size of the data to be loaded into the register DATAI.
                                                    This parameter can be a value of the @ref CRC_DataLoadSize_TypeDef. */
    FunctionalState CRC_DMAState;              /*!< A status of the DMA request generation.
                                                    This parameter can be a value of the @ref FunctionalState. */
    CRC_EndianMode_TypeDef CRC_EndianMode;     /*!< A sequence of the CRC calculation.
                                                    This parameter can be a value of the @ref CRC_EndianMode_TypeDef. */
    uint32_t CRC_Polynom;                      /*!< A polynomial for the CRC calculation.
                                                    This parameter can be a number from 0x10001 to 0x1FFFF. */
    uint32_t CRC_StartValue;                   /*!< A starting value of the CRC calculation.
                                                    This parameter can be a number from 0x00000 to 0x1FFFF. */
} CRC_InitTypeDef;

/** @} */ /* End of the group CRC_Exported_Types */

/** @defgroup CRC_Exported_Defines CRC Exported Defines
 * @{
 */

#define IS_CRC_START_VALUE(SV) (((SV) & ~CRC_VAL_CRCOUT_Msk) == 0)
#define IS_CRC_POLYNOM(POL)    (((POL) & ~CRC_POL_CRC_POL_Msk) == 0)

/** @} */ /* End of the group CRC_Exported_Defines */

/** @defgroup CRC_Exported_Functions CRC Exported Functions
 * @{
 */

void CRC_DeInit(void);
void CRC_Init(const CRC_InitTypeDef* CRC_InitStruct);

void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct);

void            CRC_Cmd(FunctionalState NewState);
FunctionalState CRC_GetCmdState(void);

void CRC_SetDataSize(CRC_DataSize_TypeDef DataSize);
void CRC_SetDataLoadSize(CRC_DataLoadSize_TypeDef DataLoadSize);

void            CRC_DMACmd(FunctionalState NewState);
FunctionalState CRC_GetDMACmdState(void);

void CRC_SetEndianMode(CRC_EndianMode_TypeDef EndianMode);

void     CRC_SetPolynom(uint32_t Polynom);
uint32_t CRC_GetPolynom(void);

void CRC_SetStartValue(uint32_t StartValue);

FlagStatus CRC_GetFlagStatus(CRC_Flags_TypeDef CRC_Flag);
uint32_t   CRC_GetStatus(void);
void       CRC_ClearFIFOOverFlag(void);

void     CRC_WriteData(uint32_t Data);
uint16_t CRC_GetCRC(void);

/** @} */ /* End of the group CRC_Exported_Functions */

/** @} */ /* End of the group CRC */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_CRC_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_crc.h */

