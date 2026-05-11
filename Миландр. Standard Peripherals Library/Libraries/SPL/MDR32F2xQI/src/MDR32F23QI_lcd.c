/**
 *******************************************************************************
 * @file    MDR32F23QI_lcd.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    25/05/2023
 * @brief   This file contains all the LCD firmware functions.
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
#include "MDR32F23QI_lcd.h"

/** @addtogroup __MDR32F23QI_StdPeriph_Driver MDR32F23QI Standard Peripherial Driver
 * @{
 */

#if defined(USE_MDR32F23QI)

/** @addtogroup LCD LCD
 * @{
 */

/** @defgroup LCD_Private_Defines LCD Private Defines
 * @{
 */

#define IS_LCD_DIV(DIV) ((DIV) <= 0xFFFF)

/** @} */ /* End of group LCD_Private_Defines */

/** @defgroup LCD_Exported_Functions LCD Exported Functions
 * @{
 */
/**
 * @brief  Resets the LCD peripheral registers to their default reset values.
 * @param  None.
 * @retval None.
 */

void LCD_DeInit(void)
{
    MDR_LCD->CR    = 0;
    MDR_LCD->ROW1  = 0;
    MDR_LCD->ROW2  = 0;
    MDR_LCD->ROW3  = 0;
    MDR_LCD->ROW4  = 0;
    MDR_LCD->AROW1 = 0;
    MDR_LCD->AROW2 = 0;
    MDR_LCD->AROW3 = 0;
    MDR_LCD->AROW4 = 0;
}

/**
 * @brief  Set main memory data the LCD peripheral of the BP0-3 outputs.
 * @param  pData: Pointer to @ref LCD_SreenData structure from data rows.
 * @retval None.
 */
void LCD_SetScreen(LCD_SreenData* pData)
{
    MDR_LCD->ROW1 = pData->SEGMCOM0;
    MDR_LCD->ROW2 = pData->SEGMCOM1;
    MDR_LCD->ROW3 = pData->SEGMCOM2;
    MDR_LCD->ROW4 = pData->SEGMCOM3;
}

/**
 * @brief  Set a alternative memory data the LCD peripheral of the BP0-3 outputs.
 * @param  pData: Pointer to @ref LCD_SreenData structure from data rows.
 * @retval None.
 */
void LCD_SetScreenAlt(LCD_SreenData* pData)
{
    MDR_LCD->AROW1 = pData->SEGMCOM0;
    MDR_LCD->AROW2 = pData->SEGMCOM1;
    MDR_LCD->AROW3 = pData->SEGMCOM2;
    MDR_LCD->AROW4 = pData->SEGMCOM3;
}

/**
 * @brief  Fills each LCD_InitStruct member with its default value.
 * @param  LCD_InitStruct: pointer to a @ref LCD_InitStruct structure which will be initialized.
 * @retval None.
 */
void LCD_StructInit(LCD_InitTypeDef* LCD_InitStruct)
{
    /* General config */
    LCD_InitStruct->LCD_Multiplex   = LCD_MUX_STATIC;
    LCD_InitStruct->LCD_MultiBias   = LCD_MULTBIAS_DIV_3;
    LCD_InitStruct->LCD_BlinkFreq   = LCD_BLINK_OFF;
    LCD_InitStruct->LCD_Circuit     = LCD_MAIN_CIRCUIT;
    LCD_InitStruct->LCD_SourceVLCD  = LCD_VLCD_INTERNAL;
    LCD_InitStruct->LCD_Divider     = 0;
    LCD_InitStruct->LCD_SourceClock = LCD_CLK_LSE;
}

/**
 * @brief  Initializes the LCD peripheral according to the specified
 *         parameters in the LCD_InitStruct.
 * @param  LCD_InitStruct: pointer to a @ref LCD_InitTypeDef structure
 *         that contains the configuration information for the specified LCD peripheral.
 * @retval None.
 */
void LCD_Init(const LCD_InitTypeDef* LCD_InitStruct)
{
    uint32_t TempCR;

    /* Check the parameters */
    assert_param(IS_LCD_CONTROL_MUX(LCD_InitStruct->LCD_Multiplex));
    assert_param(IS_LCD_BIAS(LCD_InitStruct->LCD_MultiBias));
    assert_param(IS_LCD_BLINK_FREQ(LCD_InitStruct->LCD_BlinkFreq));
    assert_param(IS_LCD_CIRCUIT(LCD_InitStruct->LCD_Circuit));
    assert_param(IS_LCD_VLCD(LCD_InitStruct->LCD_SourceVLCD));
    assert_param(IS_LCD_DIV(LCD_InitStruct->LCD_Divider));
    assert_param(IS_LCD_CLK(LCD_InitStruct->LCD_SourceClock));

    /* Config the LCD control register */
    TempCR = ((uint32_t)LCD_InitStruct->LCD_Multiplex) |
             ((uint32_t)LCD_InitStruct->LCD_MultiBias) |
             ((uint32_t)LCD_InitStruct->LCD_BlinkFreq) |
             ((uint32_t)LCD_InitStruct->LCD_Circuit) |
             ((uint32_t)LCD_InitStruct->LCD_SourceVLCD) |
             ((uint32_t)LCD_InitStruct->LCD_Divider << LCD_CR_DIV_Pos) |
             ((uint32_t)LCD_InitStruct->LCD_SourceClock);

    MDR_LCD->CR = TempCR;
}

/**
 * @brief  Enables or disables the specified LCD peripheral.
 * @param  NewState - @ref FunctionalState - new state of the LCD peripheral.
 * @retval None.
 */
void LCD_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        MDR_LCD->CR |= LCD_CR_E_Msk;
    } else {
        MDR_LCD->CR &= ~LCD_CR_E_Msk;
    }
}

/** @} */ /* End of group LCD_Exported_Functions */

/** @} */ /* End of group LCD */

#endif    /* #if defined (USE_MDR32F23QI) */

/** @} */ /* End of group __MDR32F23QI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F23QI_lcd.c */

