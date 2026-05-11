/**
 *******************************************************************************
 * @file    MDR32F2xQI_power.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    17/05/2023
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
#ifndef __MDR32F2xQI_POWER_H
#define __MDR32F2xQI_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup POWER
 * @{
 */

/** @defgroup POWER_Exported_Types POWER Exported Types
 * @{
 */

/**
 *  @brief POWER Voltage Detector Enable Flags
 */
typedef enum {
    POWER_DETECTOR_PVD  = ((uint32_t)POWER_PVDCS_PVDEN), /*!< Ucc voltage detector */
    POWER_DETECTOR_PVBD = ((uint32_t)POWER_PVDCS_PVDBEN) /*!< BUcc voltage detector */
} POWER_DetectorEnable_TypeDef;

#define IS_POWER_DETECTOR(PWR) (((PWR) & ~(POWER_DETECTOR_PVD | POWER_DETECTOR_PVBD)) == 0)

/**
 *  @brief POWER Voltage Detector Level
 */
typedef enum {
#if defined(USE_MDR32F21QI)
    POWER_PVD_LEVEL_2p0V = ((uint32_t)0x0 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p2V = ((uint32_t)0x1 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p4V = ((uint32_t)0x2 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p6V = ((uint32_t)0x3 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p8V = ((uint32_t)0x4 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p0V = ((uint32_t)0x5 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p2V = ((uint32_t)0x6 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p4V = ((uint32_t)0x7 << POWER_PVDCS_PLS_Pos)
#elif defined(USE_MDR32F23QI)
    POWER_PVD_LEVEL_1p0V  = ((uint32_t)0x0 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_1p2V  = ((uint32_t)0x1 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_1p4V  = ((uint32_t)0x2 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_1p6V  = ((uint32_t)0x3 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_1p8V  = ((uint32_t)0x4 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p0V  = ((uint32_t)0x5 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p2V  = ((uint32_t)0x6 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p4V  = ((uint32_t)0x7 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p6V  = ((uint32_t)0x8 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_2p8V  = ((uint32_t)0x9 << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p0V  = ((uint32_t)0xA << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p2V  = ((uint32_t)0xB << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p4V  = ((uint32_t)0xC << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p6V  = ((uint32_t)0xD << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_3p8V  = ((uint32_t)0xE << POWER_PVDCS_PLS_Pos),
    POWER_PVD_LEVEL_4p0V  = ((uint32_t)0xF << POWER_PVDCS_PLS_Pos)
#endif
} POWER_VoltageDetectorLvl_TypeDef;

#define IS_POWER_PVD_LEVEL(LVL) (((LVL) & ~POWER_PVDCS_PLS_Msk) == 0)

/**
 *  @brief POWER Battery Voltage Detector Level
 */
typedef enum {
#if defined(USE_MDR32F21QI)
    POWER_PVBD_LEVEL_1p8V = ((uint32_t)0x0 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_2p2V = ((uint32_t)0x1 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_2p6V = ((uint32_t)0x2 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_3p0V = ((uint32_t)0x3 << POWER_PVDCS_PBLS_Pos)
#elif defined(USE_MDR32F23QI)
    POWER_PVBD_LEVEL_1p0V = ((uint32_t)0x0 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_1p2V = ((uint32_t)0x1 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_1p4V = ((uint32_t)0x2 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_1p6V = ((uint32_t)0x3 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_1p8V = ((uint32_t)0x4 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_2p0V = ((uint32_t)0x5 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_2p2V = ((uint32_t)0x6 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_2p4V = ((uint32_t)0x7 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_2p6V = ((uint32_t)0x8 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_2p8V = ((uint32_t)0x9 << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_3p0V = ((uint32_t)0xA << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_3p2V = ((uint32_t)0xB << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_3p4V = ((uint32_t)0xC << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_3p6V = ((uint32_t)0xD << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_3p8V = ((uint32_t)0xE << POWER_PVDCS_PBLS_Pos),
    POWER_PVBD_LEVEL_4p0V = ((uint32_t)0xF << POWER_PVDCS_PBLS_Pos)
#endif
} POWER_BattVoltageDetectorLvl_TypeDef;

#define IS_POWER_PVBD_LEVEL(LVL) (((LVL) & ~POWER_PVDCS_PBLS_Msk) == 0)

/**
 *  @brief POWER Voltage Detector Output Flags
 */
typedef enum {
    POWER_FLAG_PVD  = ((uint32_t)POWER_PVDCS_PVD), /*!< Power voltage detection flag */
    POWER_FLAG_PVBD = ((uint32_t)POWER_PVDCS_PVBD) /*!< Battery voltage detection flag */
} POWER_Flags_TypeDef;

#define IS_POWER_FLAG(F)  (((F) == POWER_FLAG_PVD) || ((F) == POWER_FLAG_PVBD))

#define IS_POWER_FLAGS(F) (((F) == POWER_FLAG_PVD) ||  \
                           ((F) == POWER_FLAG_PVBD) || \
                           ((F) == (POWER_FLAG_PVD & POWER_FLAG_PVBD)))

/**
 *  @brief POWER Voltage Detector Interrupt Enable
 */
typedef enum {
    POWER_IT_PVD  = ((uint32_t)POWER_PVDCS_IEPVD), /*!< PVD interrupt enable  */
    POWER_IT_PVBD = ((uint32_t)POWER_PVDCS_IEPVBD) /*!< PVBD interrupt enable */
} POWER_VoltageDetectorITEnable_TypeDef;

#define IS_POWER_PVD_IT(F) (((F) == POWER_IT_PVD) || ((F) == POWER_IT_PVBD))

/**
 *  @brief POWER Voltage Detector Interrupt Inversion
 */
typedef enum {
    POWER_INV_PVD  = ((uint32_t)POWER_PVDCS_INV), /*!< PVD inversion enable  */
    POWER_INV_PVBD = ((uint32_t)POWER_PVDCS_INVB) /*!< PVBD inversion enable */
} POWER_VoltageDetectorITInversion_TypeDef;

#define IS_POWER_PVD_INV(F) (((F) == POWER_INV_PVD) || ((F) == POWER_INV_PVBD))

/** @} */ /* End of group POWER_Exported_Types */

/** @defgroup POWER_Exported_Functions POWER Exported Functions
 * @{
 */

void POWER_DeInit(void);
void POWER_Cmd(uint32_t PowerDetector, FunctionalState NewState);

void POWER_PVD_LevelConfig(POWER_VoltageDetectorLvl_TypeDef POWER_PVD_Level);
void POWER_PVBD_LevelConfig(POWER_BattVoltageDetectorLvl_TypeDef POWER_PVBD_Level);

FlagStatus POWER_GetFlagStatus(POWER_Flags_TypeDef POWER_Flag);
uint32_t   POWER_GetStatus(void);
void       POWER_ClearFlags(uint32_t POWER_Flags);

void POWER_FlagInversionConfig(uint32_t FlagInversion, FunctionalState NewState);

void       POWER_ITConfig(uint32_t POWER_IT, FunctionalState NewState);
FlagStatus POWER_GetITFlagStatus(POWER_Flags_TypeDef POWER_Flag);
uint32_t   POWER_GetITStatus(void);

/**
 * @brief  Clears POWER interrupt requests.
 * @param  IT_Flags: specifies the POWER interrupt request to clear.
 *         This parameter can be any combination of @ref POWER_Flags_TypeDef values.
 * @retval None.
 */
#define POWER_ClearITFlags(IT_Flags) POWER_ClearFlags(IT_Flags)

/** @} */ /* End of group POWER_Exported_Functions */

/** @} */ /* End of group POWER */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_POWER_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_power.h */

