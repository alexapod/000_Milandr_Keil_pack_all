/**
 *******************************************************************************
 * @file    MDR32VF0xI_sensors.c
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    28/04/2024
 * @brief   This file contains all the SENSORS firmware functions.
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
#include "MDR32VF0xI_sensors.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup SENSORS SENSORS
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup SENSORS_Exported_Functions SENSORS Exported Functions
 * @{
 */

/**
 * @brief  Enable sensors.
 * @note   Only one-time write is possible.
 * @param  Sensors: Specify the sensors to enable.
 *         This parameter can be any combination of the @ref SENSORS_Sensors_TypeDef values.
 * @return None.
 */
void SENSORS_Enable(uint32_t Sensors)
{
    /* Check the parameters. */
    assert_param(IS_SENSORS_SENSORS(Sensors));

    MDR_SENSORS->ENABLE = Sensors;
}

/**
 * @brief  Enable IT for the specified sensors.
 * @note   Only one-time write is possible.
 * @param  Sensors: Specify the sensors to enable IT.
 *         This parameter can be any combination of the @ref SENSORS_Sensors_TypeDef values.
 * @return None.
 */
void SENSORS_ITEnable(uint32_t Sensors)
{
    /* Check the parameters. */
    assert_param(IS_SENSORS_SENSORS(Sensors));

    MDR_SENSORS->INT_MASK = Sensors;
}

/**
 * @brief  Enable key reset by events from sensors.
 * @note   Only one-time write is possible.
 * @param  Sensors: Specify the sensors to enable key reset.
 *         This parameter can be any combination of the @ref SENSORS_Sensors_TypeDef values.
 * @return None.
 */
void SENSORS_KeyResetEnable(uint32_t Sensors)
{
    /* Check the parameters. */
    assert_param(IS_SENSORS_SENSORS(Sensors));

    MDR_SENSORS->K_RES_MASK = Sensors;
}

/**
 * @brief  Initialize the SENSORS mesh according to the specified
 *         parameters in the Mesh_InitStruct.
 * @param  Mesh_InitStruct: The pointer to the @ref SENSORS_Mesh_InitTypeDef structure
 *         that contains the configuration information for SENSORS mesh.
 * @return None.
 */
void SENSORS_Mesh_Init(const SENSORS_Mesh_InitTypeDef* Mesh_InitStruct)
{
    /* Check the parameters. */
    assert_param(IS_SENSORS_MESH_PRESCALER(Mesh_InitStruct->SENSORS_MeshPrescaler));

    /* Setup mesh key and value. */
    MDR_SENSORS->MESH_KEY0 = Mesh_InitStruct->SENSORS_MeshKey[0];
    MDR_SENSORS->MESH_KEY1 = Mesh_InitStruct->SENSORS_MeshKey[1];
    MDR_SENSORS->MESH_KEY2 = Mesh_InitStruct->SENSORS_MeshKey[2];
    MDR_SENSORS->MESH_KEY3 = Mesh_InitStruct->SENSORS_MeshKey[3];
    MDR_SENSORS->MESH_KEY4 = Mesh_InitStruct->SENSORS_MeshKey[4];
    MDR_SENSORS->MESH_KEY5 = Mesh_InitStruct->SENSORS_MeshKey[5];
    MDR_SENSORS->MESH_KEY6 = Mesh_InitStruct->SENSORS_MeshKey[6];
    MDR_SENSORS->MESH_KEY7 = Mesh_InitStruct->SENSORS_MeshKey[7];

    MDR_SENSORS->MESH_INIT0 = Mesh_InitStruct->SENSORS_MeshInitValue[0];
    MDR_SENSORS->MESH_INIT1 = Mesh_InitStruct->SENSORS_MeshInitValue[1];

    /* Setup mesh clock prescaler. */
    MDR_SENSORS->MESHCNTR = (uint32_t)(Mesh_InitStruct->SENSORS_MeshPrescaler);
}

/**
 * @brief  Fill each Mesh_InitStruct member with its default value.
 * @param  Mesh_InitStruct: the pointer to the @ref SENSORS_Mesh_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void SENSORS_Mesh_StructInit(SENSORS_Mesh_InitTypeDef* Mesh_InitStruct)
{
    Mesh_InitStruct->SENSORS_MeshKey[0] = 0;
    Mesh_InitStruct->SENSORS_MeshKey[1] = 0;
    Mesh_InitStruct->SENSORS_MeshKey[2] = 0;
    Mesh_InitStruct->SENSORS_MeshKey[3] = 0;
    Mesh_InitStruct->SENSORS_MeshKey[4] = 0;
    Mesh_InitStruct->SENSORS_MeshKey[5] = 0;
    Mesh_InitStruct->SENSORS_MeshKey[6] = 0;
    Mesh_InitStruct->SENSORS_MeshKey[7] = 0;

    Mesh_InitStruct->SENSORS_MeshInitValue[0] = 0;
    Mesh_InitStruct->SENSORS_MeshInitValue[1] = 0;

    Mesh_InitStruct->SENSORS_MeshPrescaler = SENSORS_MESH_PRESCALER_DIV_3;
}

/**
 * @brief  Read the latched alarm values of the sensors.
 * @return A combined value of latched alarm status of sensors (@ref SENSORS_Sensors_TypeDef).
 */
uint32_t SENSORS_ReadHistory(void)
{
    return MDR_SENSORS->STATE_REG;
}

/**
 * @brief  Clear the latched alarm flags of sensors.
 * @param  Sensors: Specify the sensors to clear.
 * @return None.
 */
void SENSORS_ResetHistory(uint32_t Sensors)
{
    /* Check the parameters. */
    assert_param(IS_SENSORS_SENSORS(Sensors));

    MDR_SENSORS->STATE_REG = ~Sensors;
}

/**
 * @brief  Get a current state of the alarm signals of the sensors.
 * @return A combined value of current alarm status of the sensors. (@ref SENSORS_Sensors_TypeDef).
 */
uint32_t SENSORS_ReadRealTime(void)
{
    return MDR_SENSORS->REAL_TIME;
}

/** @} */ /* End of the group SENSORS_Exported_Functions */

/** @} */ /* End of the group SENSORS */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_sensors.c */

