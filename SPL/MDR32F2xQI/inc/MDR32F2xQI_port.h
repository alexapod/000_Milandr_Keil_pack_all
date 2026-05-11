/**
 *******************************************************************************
 * @file    MDR32F2xQI_port.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
 * @brief   This file contains all the functions prototypes for the PORT
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
#ifndef __MDR32F2xQI_PORT_H
#define __MDR32F2xQI_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup PORT
 * @{
 */

/** @defgroup PORT_Exported_Types PORT Exported Types
 * @{
 */

/**
 * @brief PORT pins enumeration.
 */
typedef enum {
    PORT_PIN_0   = PORT_RXTX_RXTX0,   /*!< Pin 0 selected */
    PORT_PIN_1   = PORT_RXTX_RXTX1,   /*!< Pin 1 selected */
    PORT_PIN_2   = PORT_RXTX_RXTX2,   /*!< Pin 2 selected */
    PORT_PIN_3   = PORT_RXTX_RXTX3,   /*!< Pin 3 selected */
    PORT_PIN_4   = PORT_RXTX_RXTX4,   /*!< Pin 4 selected */
    PORT_PIN_5   = PORT_RXTX_RXTX5,   /*!< Pin 5 selected */
    PORT_PIN_6   = PORT_RXTX_RXTX6,   /*!< Pin 6 selected */
    PORT_PIN_7   = PORT_RXTX_RXTX7,   /*!< Pin 7 selected */
    PORT_PIN_8   = PORT_RXTX_RXTX8,   /*!< Pin 8 selected */
    PORT_PIN_9   = PORT_RXTX_RXTX9,   /*!< Pin 9 selected */
    PORT_PIN_10  = PORT_RXTX_RXTX10,  /*!< Pin 10 selected */
    PORT_PIN_11  = PORT_RXTX_RXTX11,  /*!< Pin 11 selected */
    PORT_PIN_12  = PORT_RXTX_RXTX12,  /*!< Pin 12 selected */
    PORT_PIN_13  = PORT_RXTX_RXTX13,  /*!< Pin 13 selected */
    PORT_PIN_14  = PORT_RXTX_RXTX14,  /*!< Pin 14 selected */
    PORT_PIN_15  = PORT_RXTX_RXTX15,  /*!< Pin 15 selected */
    PORT_PIN_ALL = PORT_RXTX_RXTX_Msk /*!< All pins selected */
} PORT_Pin_TypeDef;

#define IS_PORT_PIN(PIN) ((((PIN) & ~PORT_RXTX_RXTX_Msk) == 0x00) && \
                          ((PIN) != 0x00))

#define IS_GET_PORT_PIN(PIN) (((PIN) == PORT_PIN_0) ||  \
                              ((PIN) == PORT_PIN_1) ||  \
                              ((PIN) == PORT_PIN_2) ||  \
                              ((PIN) == PORT_PIN_3) ||  \
                              ((PIN) == PORT_PIN_4) ||  \
                              ((PIN) == PORT_PIN_5) ||  \
                              ((PIN) == PORT_PIN_6) ||  \
                              ((PIN) == PORT_PIN_7) ||  \
                              ((PIN) == PORT_PIN_8) ||  \
                              ((PIN) == PORT_PIN_9) ||  \
                              ((PIN) == PORT_PIN_10) || \
                              ((PIN) == PORT_PIN_11) || \
                              ((PIN) == PORT_PIN_12) || \
                              ((PIN) == PORT_PIN_13) || \
                              ((PIN) == PORT_PIN_14) || \
                              ((PIN) == PORT_PIN_15))

/**
 * @brief PORT pin analog-digital mode enumeration.
 */
typedef enum {
    PORT_MODE_ANALOG  = 0x0,
    PORT_MODE_DIGITAL = 0x1
} PORT_Mode_TypeDef;

#define IS_PORT_MODE(MODE) (((MODE) == PORT_MODE_ANALOG) || \
                            ((MODE) == PORT_MODE_DIGITAL))

/**
 * @brief PORT pin direction (OE) enumeration.
 */
typedef enum {
    PORT_DIRECTION_IN  = 0x0,
    PORT_DIRECTION_OUT = 0x1
} PORT_Direction_TypeDef;

#define IS_PORT_DIR(DIR) (((DIR) == PORT_DIRECTION_IN) || ((DIR) == PORT_DIRECTION_OUT))

/**
 * @brief PORT pin function enumeration.
 */
typedef enum {
    PORT_FUNCTION_PORT        = 0x0,
    PORT_FUNCTION_MAIN        = 0x1,
    PORT_FUNCTION_ALTERNATIVE = 0x2,
    PORT_FUNCTION_OVERRIDEN   = 0x3
} PORT_Function_TypeDef;

#define IS_PORT_FUNC(FUNC) (((FUNC) == PORT_FUNCTION_PORT) || ((FUNC) == PORT_FUNCTION_MAIN) || \
                            ((FUNC) == PORT_FUNCTION_ALTERNATIVE) || ((FUNC) == PORT_FUNCTION_OVERRIDEN))

/**
 * @brief PORT pin power (PWR) enumeration.
 */
typedef enum {
    PORT_POWER_OUTPUT_OFF    = 0x0,
    PORT_POWER_SPEED_SLOW    = 0x1,
    PORT_POWER_SPEED_FAST    = 0x2,
    PORT_POWER_SPEED_MAXFAST = 0x3
} PORT_Power_TypeDef;

#define IS_PORT_POWER(PWR) (((PWR) == PORT_POWER_OUTPUT_OFF) || ((PWR) == PORT_POWER_SPEED_SLOW) || \
                            ((PWR) == PORT_POWER_SPEED_FAST) || ((PWR) == PORT_POWER_SPEED_MAXFAST))

/**
 * @brief PORT pin driver type enumeration.
 */
typedef enum {
    PORT_DRIVER_PUSH_PULL  = 0x0,
    PORT_DRIVER_OPEN_DRAIN = 0x1
} PORT_Driver_TypeDef;

#define IS_PORT_DRIVER(PD) (((PD) == PORT_DRIVER_PUSH_PULL) || \
                            ((PD) == PORT_DRIVER_OPEN_DRAIN))

/**
 * @brief PORT pin pull-up resister usage enumeration.
 */
typedef enum {
    PORT_PULL_UP_OFF = 0x0,
    PORT_PULL_UP_ON  = 0x1
} PORT_PullUp_TypeDef;

#define IS_PORT_PULL_UP(PULL_UP) (((PULL_UP) == PORT_PULL_UP_OFF) || \
                                  ((PULL_UP) == PORT_PULL_UP_ON))

/**
 * @brief PORT pin pull-down resister usage enumeration.
 */
typedef enum {
    PORT_PULL_DOWN_OFF = 0x0,
    PORT_PULL_DOWN_ON  = 0x1
} PORT_PullDown_TypeDef;

#define IS_PORT_PULL_DOWN(PULL_DOWN) (((PULL_DOWN) == PORT_PULL_DOWN_ON) || \
                                      ((PULL_DOWN) == PORT_PULL_DOWN_OFF))

/**
 * @brief PORT pin input hysteresis enumeration.
 */
typedef enum {
    PORT_HYSTERESIS_DISABLE = 0x0,
    PORT_HYSTERESIS_ENABLE  = 0x1
} PORT_Hysteresis_TypeDef;

#define IS_PORT_HYSTERESIS(SHM) (((SHM) == PORT_HYSTERESIS_DISABLE) || \
                                 ((SHM) == PORT_HYSTERESIS_ENABLE))

/**
 * @brief PORT pin glitch filter usage enumeration.
 */
typedef enum {
    PORT_GLITCH_FILTER_DISABLE = 0x0,
    PORT_GLITCH_FILTER_ENABLE  = 0x1
} PORT_GlitchFilter_TypeDef;

#define IS_PORT_GFEN(PORT_GFEN) (((PORT_GFEN) == PORT_GLITCH_FILTER_DISABLE) || \
                                 ((PORT_GFEN) == PORT_GLITCH_FILTER_ENABLE))

/**
 * @brief PORT Init structure definition
 */
typedef struct
{
    uint16_t PORT_Pin;                           /*!< Specifies PORT pins to be configured.
                                                      This parameter is any combination of @ref PORT_Pin_TypeDef values. */
    PORT_Mode_TypeDef PORT_Mode;                 /*!< Specifies the operating mode for the selected pins.
                                                      This parameter is one of @ref PORT_Mode_TypeDef values. */
    PORT_Direction_TypeDef PORT_Direction;       /*!< Specifies in/out mode for the selected pins.
                                                      This parameter is one of @ref PORT_Direction_TypeDef values. */
    PORT_Function_TypeDef PORT_Function;         /*!< Specifies operating function for the selected pins.
                                                      This parameter is one of @ref PORT_Function_TypeDef values. */
    PORT_Power_TypeDef PORT_Power;               /*!< Specifies power for the selected pins.
                                                      This parameter is one of @ref PORT_Power_TypeDef values. */
    PORT_Driver_TypeDef PORT_Driver;             /*!< Specifies driver type for the selected pins.
                                                      This parameter is one of @ref PORT_Driver_TypeDef values. */
    PORT_PullUp_TypeDef PORT_PullUp;             /*!< Specifies pull up state for the selected pins.
                                                      This parameter is one of @ref PORT_PullUp_TypeDef values. */
    PORT_PullDown_TypeDef PORT_PullDown;         /*!< Specifies pull down state for the selected pins.
                                                      This parameter is one of @ref PORT_PullDown_TypeDef values. */
    PORT_Hysteresis_TypeDef PORT_Hysteresis;     /*!< Specifies input hysteresis for the selected pins.
                                                      This parameter is one of @ref PORT_Hysteresis_TypeDef values. */
    PORT_GlitchFilter_TypeDef PORT_GlitchFilter; /*!< Specifies glitch filter state for the selected pins.
                                                      This parameter is one of @ref PORT_GlitchFilter_TypeDef values. */
} PORT_InitTypeDef;

/** @} */ /* End of group PORT_Exported_Types */

/** @defgroup PORT_Exported_Defines PORT Exported Defines
 * @{
 */

/** @defgroup PORT_SWD_define PORT SWD define
 * @{
 */
#if defined(USE_SWD)
#if defined(USE_MDR32F21QI)
#define PORT_SWD       MDR_PORTA                                 /*!< Port containing SWD interface */
#define PORT_SWD_MASK  (PORT_OE_OE6 | PORT_OE_OE7)               /*!< SWD pins: OE, ANALOG, GFEN mask */
#define PORT_SWD_MASK2 (PORT_FUNC_MODE6 | PORT_FUNC_MODE7)       /*!< SWD pins: FUNC, PWR mask */
#define PORT_SWD_MASK3 (PORT_PULL_PULL_DOWN6 | PORT_PULL_PULL_DOWN7 | \
                        PORT_PULL_PULL_UP6 | PORT_PULL_PULL_UP7) /*!< SWD pins: PULL, PD mask */
#elif defined(USE_MDR32F23QI)
#define PORT_SWD       MDR_PORTB                                 /*!< Port containing SWD interface */
#define PORT_SWD_MASK  (PORT_OE_OE2 | PORT_OE_OE3)               /*!< SWD pins: OE, ANALOG, GFEN mask */
#define PORT_SWD_MASK2 (PORT_FUNC_MODE2 | PORT_FUNC_MODE3)       /*!< SWD pins: FUNC, PWR mask */
#define PORT_SWD_MASK3 (PORT_PULL_PULL_DOWN2 | PORT_PULL_PULL_DOWN3 | \
                        PORT_PULL_PULL_UP2 | PORT_PULL_PULL_UP3) /*!< SWD pins: PULL, PD mask */
#endif
#endif

#if defined(PORT_SWD)
#define SWD_PINS(PORT)  (((PORT) == PORT_SWD) ? PORT_SWD_MASK : 0)
#define SWD_PINS2(PORT) (((PORT) == PORT_SWD) ? PORT_SWD_MASK2 : 0)
#define SWD_PINS3(PORT) (((PORT) == PORT_SWD) ? PORT_SWD_MASK3 : 0)
#else
#define SWD_PINS(PORT)  0
#define SWD_PINS2(PORT) 0
#define SWD_PINS3(PORT) 0
#endif

#define IS_NOT_SWD_PIN(PORT, PIN) (((PIN)&SWD_PINS(PORT)) == 0x00)

/** @} */ /* End of group PORT_SWD_define */

/** @} */ /* End of group PORT_Exported_Defines */

/** @defgroup PORT_Exported_Functions PORT Exported Functions
 * @{
 */

void PORT_DeInit(MDR_PORT_TypeDef* PORTx);
void PORT_Init(MDR_PORT_TypeDef* PORTx, const PORT_InitTypeDef* PORT_InitStruct);
void PORT_StructInit(PORT_InitTypeDef* PORT_InitStruct);

BitStatus PORT_ReadInputDataBit(MDR_PORT_TypeDef* PORTx, PORT_Pin_TypeDef PORT_Pin);
uint32_t  PORT_ReadInputData(MDR_PORT_TypeDef* PORTx);

BitStatus PORT_ReadOutputDataBit(MDR_PORT_TypeDef* PORTx, PORT_Pin_TypeDef PORT_Pin);
uint32_t  PORT_ReadOutputData(MDR_PORT_TypeDef* PORTx);

void PORT_SetBits(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin);
void PORT_ResetBits(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin);

void PORT_WriteBit(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin, BitStatus BitVal);
void PORT_ToggleBit(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin);

void PORT_Write(MDR_PORT_TypeDef* PORTx, uint32_t PortVal);

/** @} */ /* End of group PORT_Exported_Functions */

/** @} */ /* End of group PORT */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_PORT_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_port.h */

