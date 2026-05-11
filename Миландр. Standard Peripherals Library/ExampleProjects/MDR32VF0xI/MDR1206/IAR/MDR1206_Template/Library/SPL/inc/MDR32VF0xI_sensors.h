/**
 *******************************************************************************
 * @file    MDR32VF0xI_sensors.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    11/04/2024
 * @brief   This file contains all the functions prototypes for the SENSORS
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
#ifndef MDR32VF0xI_SENSORS_H
#define MDR32VF0xI_SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup SENSORS SENSORS
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup SENSORS_Exported_Types SENSORS Exported Types
 * @{
 */

/**
 * @brief SENSORS sensors enumeration.
 */
typedef enum {
    SENSORS_SENSOR_LIGHT = SENSORS_STATE_REG_LIGHT_SENSOR_ALARM, /*!< Light sensor. */
    SENSORS_SENSOR_EMFI1 = SENSORS_STATE_REG_MESH_EMFI_ALARM1,   /*!< EMFI1 sensor. */
    SENSORS_SENSOR_EMFI2 = SENSORS_STATE_REG_MESH_EMFI_ALARM2,   /*!< EMFI2 sensor. */
    SENSORS_SENSOR_EMDF3 = SENSORS_STATE_REG_MESH_EMFI_ALARM3,   /*!< EMFI3 sensor. */
    SENSORS_SENSOR_MESH  = SENSORS_STATE_REG_MESH_ACTIVE_ALARM   /*!< Active mesh sensor. */
} SENSORS_Sensors_TypeDef;

#define IS_SENSORS_SENSOR(SENS) (((SENS) == SENSORS_SENSOR_LIGHT) || \
                                 ((SENS) == SENSORS_SENSOR_EMFI1) || \
                                 ((SENS) == SENSORS_SENSOR_EMFI2) || \
                                 ((SENS) == SENSORS_SENSOR_EMDF3) || \
                                 ((SENS) == SENSORS_SENSOR_MESH))

#define IS_SENSORS_SENSORS(SENS) (((SENS) & ~((uint32_t)(SENSORS_SENSOR_LIGHT | \
                                                         SENSORS_SENSOR_EMFI1 | \
                                                         SENSORS_SENSOR_EMFI2 | \
                                                         SENSORS_SENSOR_EMDF3 | \
                                                         SENSORS_SENSOR_MESH))) == 0)

/**
 * @brief SENSORS mesh prescaler.
 */
typedef enum {
    SENSORS_MESH_PRESCALER_DIV_3   = SENSORS_MESHCNTR_MESH_CLK_DIV_3,
    SENSORS_MESH_PRESCALER_DIV_4   = SENSORS_MESHCNTR_MESH_CLK_DIV_4,
    SENSORS_MESH_PRESCALER_DIV_8   = SENSORS_MESHCNTR_MESH_CLK_DIV_8,
    SENSORS_MESH_PRESCALER_DIV_16  = SENSORS_MESHCNTR_MESH_CLK_DIV_16,
    SENSORS_MESH_PRESCALER_DIV_32  = SENSORS_MESHCNTR_MESH_CLK_DIV_32,
    SENSORS_MESH_PRESCALER_DIV_64  = SENSORS_MESHCNTR_MESH_CLK_DIV_64,
    SENSORS_MESH_PRESCALER_DIV_128 = SENSORS_MESHCNTR_MESH_CLK_DIV_128,
    SENSORS_MESH_PRESCALER_DIV_256 = SENSORS_MESHCNTR_MESH_CLK_DIV_265
} SENSORS_MeshPrescaler_TypeDef;

#define IS_SENSORS_MESH_PRESCALER(DIV) (((DIV) == SENSORS_MESH_PRESCALER_DIV_3) ||   \
                                        ((DIV) == SENSORS_MESH_PRESCALER_DIV_4) ||   \
                                        ((DIV) == SENSORS_MESH_PRESCALER_DIV_8) ||   \
                                        ((DIV) == SENSORS_MESH_PRESCALER_DIV_16) ||  \
                                        ((DIV) == SENSORS_MESH_PRESCALER_DIV_32) ||  \
                                        ((DIV) == SENSORS_MESH_PRESCALER_DIV_64) ||  \
                                        ((DIV) == SENSORS_MESH_PRESCALER_DIV_128) || \
                                        ((DIV) == SENSORS_MESH_PRESCALER_DIV_256))

/**
 * @brief SENSORS mesh init structure defintion.
 */
typedef struct {
    uint32_t                      SENSORS_MeshKey[8];       /*!< Mesh key (GOST 28147-89). */
    uint32_t                      SENSORS_MeshInitValue[2]; /*!< Mesh initial value (GOST 28147-89). */
    SENSORS_MeshPrescaler_TypeDef SENSORS_MeshPrescaler;    /*!< Mesh clock prescaler.
                                                                 This parameter can be a value of the @ref SENSORS_MeshPrescaler_TypeDef. */
} SENSORS_Mesh_InitTypeDef;

/** @} */ /* End of the group SENSORS_Exported_Types */

/** @defgroup SENSORS_Exported_Functions SENSORS Exported Functions
 * @{
 */

void SENSORS_Enable(uint32_t Sensors);
void SENSORS_ITEnable(uint32_t Sensors);
void SENSORS_KeyResetEnable(uint32_t Sensors);

void SENSORS_Mesh_Init(const SENSORS_Mesh_InitTypeDef* Mesh_InitStruct);
void SENSORS_Mesh_StructInit(SENSORS_Mesh_InitTypeDef* Mesh_InitStruct);

uint32_t SENSORS_ReadHistory(void);
void     SENSORS_ResetHistory(uint32_t Sensors);
uint32_t SENSORS_ReadRealTime(void);

/** @} */ /* End of the group SENSORS_Exported_Functions */

/** @} */ /* End of the group SENSORS */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_SENSORS_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_sensors.h */

