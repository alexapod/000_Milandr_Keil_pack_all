/**
 *******************************************************************************
 * @file    MDR32VF0xI_power.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    09/04/2024
 * @brief   This file contains all the functions prototypes for the POWER
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
#ifndef MDR32VF0xI_POWER_H
#define MDR32VF0xI_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup POWER POWER
 * @{
 */

/** @defgroup POWER_Exported_Types POWER Exported Types
 * @{
 */

/**
 *  @brief POWER voltage detector enable flags.
 */
typedef enum {
    POWER_DETECTOR_PVD  = ((uint32_t)POWER_PVDCS_PVDEN), /*!< Ucc voltage detector. */
    POWER_DETECTOR_PVBD = ((uint32_t)POWER_PVDCS_PVDBEN) /*!< BUcc voltage detector. */
} POWER_DetectorEnable_TypeDef;

#define IS_POWER_DETECTOR(PWR) (((PWR) == POWER_DETECTOR_PVD) || \
                                ((PWR) == POWER_DETECTOR_PVBD))

#define IS_POWER_DETECTORS(PWR) (((PWR) & ~(uint32_t)(POWER_DETECTOR_PVD | \
                                                      POWER_DETECTOR_PVBD)) == 0)

/**
 *  @brief POWER voltage detector level.
 */
typedef enum {
    POWER_PVD_LEVEL_2p3V = (((uint32_t)0x0) << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p4V = (((uint32_t)0x1) << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p5V = (((uint32_t)0x2) << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p6V = (((uint32_t)0x3) << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p7V = (((uint32_t)0x4) << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p8V = (((uint32_t)0x5) << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p9V = (((uint32_t)0x6) << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p0V = (((uint32_t)0x7) << POWER_PVDCS_PLS_Pos)
} POWER_VoltageDetectorLvl_TypeDef;

#define IS_POWER_PVD_LEVEL(LVL) (((LVL) & ~POWER_PVDCS_PLS_Msk) == 0)

/**
 *  @brief POWER battery voltage detector level.
 */
typedef enum {
    POWER_PVBD_LEVEL_1p8V = (((uint32_t)0x0) << POWER_PVDCS_PLSB_Pos),
    POWER_PVBD_LEVEL_2p0V = (((uint32_t)0x1) << POWER_PVDCS_PLSB_Pos),
    POWER_PVBD_LEVEL_2p2V = (((uint32_t)0x2) << POWER_PVDCS_PLSB_Pos),
    POWER_PVBD_LEVEL_2p4V = (((uint32_t)0x3) << POWER_PVDCS_PLSB_Pos),
    POWER_PVBD_LEVEL_2p6V = (((uint32_t)0x4) << POWER_PVDCS_PLSB_Pos),
    POWER_PVBD_LEVEL_2p8V = (((uint32_t)0x5) << POWER_PVDCS_PLSB_Pos),
    POWER_PVBD_LEVEL_3p0V = (((uint32_t)0x6) << POWER_PVDCS_PLSB_Pos),
    POWER_PVBD_LEVEL_3p2V = (((uint32_t)0x7) << POWER_PVDCS_PLSB_Pos)
} POWER_BattVoltageDetectorLvl_TypeDef;

#define IS_POWER_PVDB_LEVEL(LVL) (((LVL) & ~POWER_PVDCS_PLSB_Msk) == 0)

/**
 *  @brief POWER voltage detector output flags.
 */
typedef enum {
    POWER_FLAG_PVD  = ((uint32_t)POWER_PVDCS_PVD), /*!< Power voltage detection flag. */
    POWER_FLAG_PVDB = ((uint32_t)POWER_PVDCS_PVBD) /*!< Battery voltage detection flag. */
} POWER_Flags_TypeDef;

#define IS_POWER_FLAG(PWR_FLAG) (((PWR_FLAG) == POWER_FLAG_PVD) || \
                                 ((PWR_FLAG) == POWER_FLAG_PVDB))

#define IS_POWER_FLAGS(PWR_FLAGS) (((PWR_FLAGS) & ~(uint32_t)(POWER_FLAG_PVD | \
                                                              POWER_FLAG_PVDB)) == 0)

/**
 *  @brief POWER voltage detector interrupt enable.
 */
typedef enum {
    POWER_IT_PVD  = ((uint32_t)POWER_PVDCS_IEPVD), /*!< PVD interrupt enable. */
    POWER_IT_PVDB = ((uint32_t)POWER_PVDCS_IEPVDB) /*!< PVBD interrupt enable. */
} POWER_VoltageDetectorITEnable_TypeDef;

#define IS_POWER_PVD_IT(IT) (((IT) == POWER_IT_PVD) || \
                             ((IT) == POWER_IT_PVDB))

#define IS_POWER_PVD_ITS(IT) (((IT) & ~((uint32_t)(POWER_IT_PVD | \
                                                   POWER_IT_PVDB))) == 0)

/**
 *  @brief POWER voltage detector interrupt inversion.
 */
typedef enum {
    POWER_INV_PVD  = ((uint32_t)POWER_PVDCS_INV), /*!< PVD inversion enable. */
    POWER_INV_PVDB = ((uint32_t)POWER_PVDCS_INVB) /*!< PVBD inversion enable. */
} POWER_VoltageDetectorITInversion_TypeDef;

#define IS_POWER_PVD_INV(INV) (((INV) & ~((uint32_t)(POWER_INV_PVD | \
                                                     POWER_INV_PVDB))) == 0)

/**
 * @brief POWER init structure definition.
 */
typedef struct {
    POWER_VoltageDetectorLvl_TypeDef POWER_PVDLevel;      /*!< Specify PVD voltage threshold.
                                                               This parameter can be a value of th e@ref POWER_VoltageDetectorLvl_TypeDef. */
    POWER_BattVoltageDetectorLvl_TypeDef POWER_PVBDLevel; /*!< Specify PVBD voltage threshold.
                                                               This parameter can be a value of the @ref POWER_BattVoltageDetectorLvl_TypeDef. */
    uint32_t POWER_InterruptInversionEnable;              /*!< Specify POWER interrupts inversion.
                                                               This parameter can be any combination of the @ref POWER_VoltageDetectorITInversion_TypeDef values. */
} POWER_InitTypeDef;

/** @} */ /* End of the group POWER_Exported_Types */

/** @defgroup POWER_Exported_Functions POWER Exported Functions
 * @{
 */

void POWER_DeInit(void);
void POWER_Init(const POWER_InitTypeDef* POWER_InitStruct);
void POWER_StructInit(POWER_InitTypeDef* POWER_InitStruct);

void            POWER_Cmd(uint32_t PowerDetector, FunctionalState NewState);
FunctionalState POWER_GetCmdState(POWER_DetectorEnable_TypeDef PowerDetector);

void POWER_PVD_LevelConfig(POWER_VoltageDetectorLvl_TypeDef POWER_PVD_Level);
void POWER_PVDB_LevelConfig(POWER_BattVoltageDetectorLvl_TypeDef POWER_PVDB_Level);

FlagStatus POWER_GetFlagStatus(POWER_Flags_TypeDef POWER_Flag);
uint32_t   POWER_GetStatus(void);
void       POWER_ClearFlags(uint32_t POWER_Flags);

void POWER_FlagInversionConfig(uint32_t FlagInversion, FunctionalState NewState);

void POWER_ITConfig(uint32_t POWER_IT, FunctionalState NewState);

/** @} */ /* End of the group POWER_Exported_Functions */

/** @} */ /* End of the group POWER */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_POWER_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_power.h */

