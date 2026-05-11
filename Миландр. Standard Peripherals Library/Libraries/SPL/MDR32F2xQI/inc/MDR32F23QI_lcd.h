/**
 *******************************************************************************
 * @file    MDR32F23QI_lcd.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    25/05/2023
 * @brief   This file contains all the functions prototypes for the LCD
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
#ifndef __MDR32F23QI_LCD_H
#define __MDR32F23QI_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F23QI_StdPeriph_Driver MDR32F23QI Standard Peripherial Driver
 * @{
 */

#if defined(USE_MDR32F23QI)

/** @addtogroup LCD
 * @{
 */

/** @defgroup LCD_Exported_Types LCD Exported Types
 * @{
 */

/**
 * @brief LCD Control circuit
 */

typedef enum {
    LCD_MUX_STATIC = LCD_CR_M_STATIC,
    LCD_MUX_DIV_2  = LCD_CR_M_DIV_2,
    LCD_MUX_DIV_3  = LCD_CR_M_DIV_3,
    LCD_MUX_DIV_4  = LCD_CR_M_DIV_4
} LCD_Multiplex_TypeDef;

#define IS_LCD_CONTROL_MUX(MUX) (((MUX) == LCD_MUX_STATIC) || \
                                 ((MUX) == LCD_MUX_DIV_2) ||  \
                                 ((MUX) == LCD_MUX_DIV_3) ||  \
                                 ((MUX) == LCD_MUX_DIV_4))

/**
 * @brief LCD Bias mode
 */

typedef enum {
    LCD_MULTBIAS_DIV_3 = (((uint32_t)0x0) << LCD_CR_B_Pos),
    LCD_MULTBIAS_DIV_2 = (((uint32_t)0x1) << LCD_CR_B_Pos)
} LCD_MultiBias_TypeDef;

#define IS_LCD_BIAS(BIAS) (((BIAS) == LCD_MULTBIAS_DIV_3) || \
                           ((BIAS) == LCD_MULTBIAS_DIV_2))

/**
 * @brief LCD Blink mode
 */
typedef enum {
    LCD_BLINK_OFF   = LCD_CR_BF_OFF,
    LCD_BLINK_2Hz   = LCD_CR_BF_2Hz,
    LCD_BLINK_1Hz   = LCD_CR_BF_1Hz,
    LCD_BLINK_0p5Hz = LCD_CR_BF_0p5Hz
} LCD_BlinkFreq_TypeDef;

#define IS_LCD_BLINK_FREQ(FREQ) (((FREQ) == LCD_BLINK_OFF) || \
                                 ((FREQ) == LCD_BLINK_2Hz) || \
                                 ((FREQ) == LCD_BLINK_1Hz) || \
                                 ((FREQ) == LCD_BLINK_0p5Hz))

/**
 * @brief LCD Circuit select
 */
typedef enum {
    LCD_MAIN_CIRCUIT = (((uint32_t)0x0) << LCD_CR_A_Pos),
    LCD_ALT_CIRCUIT  = (((uint32_t)0x1) << LCD_CR_A_Pos)
} LCD_Circuit_TypeDef;

#define IS_LCD_CIRCUIT(CIR) (((CIR) == LCD_MAIN_CIRCUIT) || \
                             ((CIR) == LCD_ALT_CIRCUIT))
/**
 * @brief LCD Vlcd select
 */
typedef enum {
    LCD_VLCD_INTERNAL = (((uint32_t)0x0) << LCD_CR_VLCDON_Pos),
    LCD_VLCD_EXTERNAL = (((uint32_t)0x1) << LCD_CR_VLCDON_Pos)
} LCD_SourceVLCD_TypeDef;

#define IS_LCD_VLCD(VLCD) (((VLCD) == LCD_VLCD_INTERNAL) || \
                           ((VLCD) == LCD_VLCD_EXTERNAL))

/**
 * @brief LCD Clock select
 */
typedef enum {
    LCD_CLK_LSE = (((uint32_t)0x0) << LCD_CR_CLK_SEL_Pos),
    LCD_CLK_LSI = (((uint32_t)0x1) << LCD_CR_CLK_SEL_Pos)
} LCD_SourceClock_TypeDef;

#define IS_LCD_CLK(CLK) (((CLK) == LCD_CLK_LSE) || \
                         ((CLK) == LCD_CLK_LSI))

/**
 * @brief LCD Sreen Data definition
 */

typedef struct {
    uint32_t SEGMCOM0;
    uint32_t SEGMCOM1;
    uint32_t SEGMCOM2;
    uint32_t SEGMCOM3;
} LCD_SreenData;

/**
 * @brief  LCD Init Structure definition
 */
typedef struct
{
    LCD_Multiplex_TypeDef LCD_Multiplex;     /*!< Specifies control scheme selection.
                                                  This parameter can be a value of @ref LCD_Multiplex_TypeDef values. */
    LCD_MultiBias_TypeDef LCD_MultiBias;     /*!< Specifies bias mode selection.
                                                  This parameter can be a value of @ref LCD_MultiBias_TypeDef values. */
    LCD_BlinkFreq_TypeDef LCD_BlinkFreq;     /*!< Specifies LCD flicker resolution.
                                                  This parameter can be a value of @ref LCD_BlinkFreq_TypeDef values. */
    LCD_Circuit_TypeDef LCD_Circuit;         /*!< Specifies LCD flicker scheme.
                                                  This parameter can be a value of @ref LCD_Circuit_TypeDef values. */
    LCD_SourceVLCD_TypeDef LCD_SourceVLCD;   /*!< Specifies LCD voltage source selection.
                                                  This parameter can be a value of @ref LCD_SourceVLCD_TypeDef values. */
    uint16_t LCD_Divider;                    /*!< Specifies divider of the reference frequency of the oscillator 32.768 kHz.
                                                  This parameter can be a number between 0x0000 and 0xFFFF.*/
    LCD_SourceClock_TypeDef LCD_SourceClock; /*!< Specifies LCD synchronization frequency selection.
                                                  This parameter can be a value of @ref LCD_SourceClock_TypeDef values. */
} LCD_InitTypeDef;

/** @} */ /* End of group LCD_Exported_Types */

/** @defgroup LCD_Exported_Functions LCD Exported Functions
 * @{
 */
void LCD_DeInit(void);
void LCD_Init(const LCD_InitTypeDef* LCD_InitStruct);
void LCD_StructInit(LCD_InitTypeDef* LCD_InitStruct);
void LCD_Cmd(FunctionalState NewState);

void LCD_SetScreen(LCD_SreenData* pData);
void LCD_SetScreenAlt(LCD_SreenData* pData);

/** @} */ /* End of group LCD_Exported_Functions */

/** @} */ /* End of group LCD */

#endif    /* #if defined (USE_MDR32F23QI) */

/** @} */ /* End of group __MDR32F23QI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F23QI_LCD_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F23QI_lcd.h */

