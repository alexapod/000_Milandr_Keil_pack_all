/**
 *******************************************************************************
 * @file    MDR32F2xQI_rst_clk.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    22/05/2023
 * @brief   This file contains all the functions prototypes for the RST_CLK
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
#ifndef __MDR32F2xQI_RST_CLK_H
#define __MDR32F2xQI_RST_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup RST_CLK
 * @{
 */

/** @defgroup RST_CLK_Exported_Types RST_CLK Exported Types
 * @{
 */

/**
 * @brief Structure type for modules clocks frequencies expressed in Hz
 */
typedef struct
{
    uint32_t CPU_CLK_Frequency;
    uint32_t UART_Frequency[2];  // UART0 and UART1 frequencies after prescaler
    uint32_t TIMER_Frequency[2]; // TIMER0 and TIMER1 frequencies after prescaler
    uint32_t SSP_Frequency;      // SSP frequency after prescaler
    uint32_t ADC_Frequency;
    uint32_t ADCUI_Frequency;
    uint32_t RTCHSI_Frequency;
    uint32_t RTCHSE_Frequency;
} RST_CLK_Freq_TypeDef;

/**
 * @brief RST_CLK HSE (High Speed External) clock mode and source selection constants
 */
typedef enum {
    RST_CLK_HSE_OFF    = ((uint32_t)0x0),                                         /*!< Switch off HSE clock generator. */
    RST_CLK_HSE_ON     = RST_CLK_HS_CONTROL_HSE_ON,                               /*!< Switch on HSE clock generator. */
    RST_CLK_HSE_BYPASS = (RST_CLK_HS_CONTROL_HSE_ON | RST_CLK_HS_CONTROL_HSE_BYP) /*!< Use external clock source. */
} RST_CLK_HSE_Mode_TypeDef;

#define IS_RST_CLK_HSE(HSE) (((HSE) == RST_CLK_HSE_OFF) || \
                             ((HSE) == RST_CLK_HSE_ON) ||  \
                             ((HSE) == RST_CLK_HSE_BYPASS))

/**
 * @brief RST_CLK CPU_PLL clock mode and source selection constants
 */
typedef enum {
    RST_CLK_PLLCPU_SRC_HSI       = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSI),
    RST_CLK_PLLCPU_SRC_HSI_DIV_2 = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSIdiv2),
    RST_CLK_PLLCPU_SRC_HSE       = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSE),
    RST_CLK_PLLCPU_SRC_HSE_DIV_2 = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSEdiv2)
} RST_CLK_PLLCPU_Source_TypeDef;

#define IS_RST_CLK_PLLCPU_SOURCE(SRC) (((SRC) == RST_CLK_PLLCPU_SRC_HSI) ||       \
                                       ((SRC) == RST_CLK_PLLCPU_SRC_HSI_DIV_2) || \
                                       ((SRC) == RST_CLK_PLLCPU_SRC_HSE) ||       \
                                       ((SRC) == RST_CLK_PLLCPU_SRC_HSE_DIV_2))

/**
 * @brief RST_CLK CPU_C1 clock mode and source selection constants
 */
typedef enum {
    RST_CLK_CPU_C1_SRC_HSI       = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSI),     /*!< HSI as CPU_C1 source. */
    RST_CLK_CPU_C1_SRC_HSI_DIV_2 = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSIdiv2), /*!< HSI/2 as CPU_C1 source. */
    RST_CLK_CPU_C1_SRC_HSE       = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSE),     /*!< HSE as CPU_C1 source. */
    RST_CLK_CPU_C1_SRC_HSE_DIV_2 = ((uint32_t)RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSEdiv2)  /*!< HSE/2 as CPU_C1 source. */
} RST_CLK_CPU_C1_Source_TypeDef;

#define IS_RST_CLK_CPU_C1_SOURCE(SRC) (((SRC) == RST_CLK_CPU_C1_SRC_HSI) ||       \
                                       ((SRC) == RST_CLK_CPU_C1_SRC_HSI_DIV_2) || \
                                       ((SRC) == RST_CLK_CPU_C1_SRC_HSE) ||       \
                                       ((SRC) == RST_CLK_CPU_C1_SRC_HSE_DIV_2))

/**
 * @brief RST_CLK PLL_CPU_MUL multiplier of the CPU_C1 clock constants
 */
typedef enum {
    RST_CLK_PLLCPU_MUL_1  = 0,
    RST_CLK_PLLCPU_MUL_2  = 1,
    RST_CLK_PLLCPU_MUL_3  = 2,
    RST_CLK_PLLCPU_MUL_4  = 3,
    RST_CLK_PLLCPU_MUL_5  = 4,
    RST_CLK_PLLCPU_MUL_6  = 5,
    RST_CLK_PLLCPU_MUL_7  = 6,
    RST_CLK_PLLCPU_MUL_8  = 7,
    RST_CLK_PLLCPU_MUL_9  = 8,
    RST_CLK_PLLCPU_MUL_10 = 9,
    RST_CLK_PLLCPU_MUL_11 = 10,
    RST_CLK_PLLCPU_MUL_12 = 11,
    RST_CLK_PLLCPU_MUL_13 = 12,
    RST_CLK_PLLCPU_MUL_14 = 13,
    RST_CLK_PLLCPU_MUL_15 = 14,
    RST_CLK_PLLCPU_MUL_16 = 15
} RST_CLK_PLLCPU_Multiplier_TypeDef;

#define IS_RST_CLK_PLLCPU_MUL(SRC) (((SRC) & ~0xFUL) == 0)

/**
 * @brief RST_CLK CPU_C2 clock source selection constants
 */
typedef enum {
    RST_CLK_CPU_C2_SRC_CPU_C1 = ((uint32_t)0x0 << RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos), /*!< CPU_C1 as CPU_C2 source. */
    RST_CLK_CPU_C2_SRC_PLLCPU = ((uint32_t)0x1 << RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos)  /*!< CPU_PLL as CPU_C2 source. */
} RST_CLK_CPU_C2_Source_TypeDef;

#define IS_RST_CLK_CPU_C2_SOURCE(SRC) (((SRC) == RST_CLK_CPU_C2_SRC_CPU_C1) || \
                                       ((SRC) == RST_CLK_CPU_C2_SRC_PLLCPU))

/**
 * @brief RST_CLK CPU_PLL output clock CPU_CLK_DIV divider constants
 */
typedef enum {
    RST_CLK_CPU_PRESCALER_DIV_1   = ((uint32_t)0x0 << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_2   = ((uint32_t)0x8 << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_4   = ((uint32_t)0x9 << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_8   = ((uint32_t)0xA << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_16  = ((uint32_t)0xB << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_32  = ((uint32_t)0xC << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_64  = ((uint32_t)0xD << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_128 = ((uint32_t)0xE << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos),
    RST_CLK_CPU_PRESCALER_DIV_256 = ((uint32_t)0xF << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos)
} RST_CLK_CPU_C3_Prescaler_TypeDef;

#define IS_RST_CLK_CPU_C3_DIV(DIV) (((DIV) == RST_CLK_CPU_PRESCALER_DIV_1) ||   \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_2) ||   \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_4) ||   \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_8) ||   \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_16) ||  \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_32) ||  \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_64) ||  \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_128) || \
                                    ((DIV) == RST_CLK_CPU_PRESCALER_DIV_256))

/**
 * @brief RST_CLK CPU_CLK source CPU_CLK selector constants
 */
typedef enum {
    RST_CLK_CPU_CLK_HSI    = ((uint32_t)RST_CLK_CPU_CLOCK_HCLK_SEL_HSI),
    RST_CLK_CPU_CLK_CPU_C3 = ((uint32_t)RST_CLK_CPU_CLOCK_HCLK_SEL_CPU_C3),
    RST_CLK_CPU_CLK_LSE    = ((uint32_t)RST_CLK_CPU_CLOCK_HCLK_SEL_LSE),
    RST_CLK_CPU_CLK_LSI    = ((uint32_t)RST_CLK_CPU_CLOCK_HCLK_SEL_LSI)
} RST_CLK_HCLK_Source_TypeDef;

#define IS_RST_CLK_HCLK_SOURCE(SRC) (((SRC) == RST_CLK_CPU_CLK_HSI) ||    \
                                     ((SRC) == RST_CLK_CPU_CLK_CPU_C3) || \
                                     ((SRC) == RST_CLK_CPU_CLK_LSE) ||    \
                                     ((SRC) == RST_CLK_CPU_CLK_LSI))

/**
 * @brief RST_CLK ADC_CLK source selector constants
 */
typedef enum {
    RST_CLK_ADC_CLK_CPU_C1  = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_CPU_C1),
    RST_CLK_ADC_CLK_PER1_C1 = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_PER1_C1),
    RST_CLK_ADC_CLK_PLLCPU  = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_PLLCPUo),
    RST_CLK_ADC_CLK_HSI_CLK = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_HSI_CLK)
} RST_CLK_ADC_Source_TypeDef;

#define IS_RST_CLK_ADC_CLK_SOURCE(SRC) (((SRC) == RST_CLK_ADC_CLK_CPU_C1) ||  \
                                        ((SRC) == RST_CLK_ADC_CLK_PER1_C1) || \
                                        ((SRC) == RST_CLK_ADC_CLK_PLLCPU) ||  \
                                        ((SRC) == RST_CLK_ADC_CLK_HSI_CLK))

/**
 * @brief RST_CLK ADC_C2_SEL output clock ADC_C3_SEL divider constants
 */
typedef enum {
    RST_CLK_ADC_PRESCALER_DIV_1   = ((uint32_t)0x0 << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_2   = ((uint32_t)0x8 << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_4   = ((uint32_t)0x9 << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_8   = ((uint32_t)0xA << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_16  = ((uint32_t)0xB << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_32  = ((uint32_t)0xC << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_64  = ((uint32_t)0xD << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_128 = ((uint32_t)0xE << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos),
    RST_CLK_ADC_PRESCALER_DIV_256 = ((uint32_t)0xF << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos)
} RST_CLK_ADC_C3_Prescaler_TypeDef;

#define IS_RST_CLK_ADC_C3_DIV(DIV) (((DIV) == RST_CLK_ADC_PRESCALER_DIV_1) ||   \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_2) ||   \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_4) ||   \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_8) ||   \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_16) ||  \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_32) ||  \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_64) ||  \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_128) || \
                                    ((DIV) == RST_CLK_ADC_PRESCALER_DIV_256))

/**
 * @brief RST_CLK ADCUI_CLK selector constants
 */
typedef enum {
    RST_CLK_ADCUI_CLK_CPU_C1  = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_CPU_C1),
    RST_CLK_ADCUI_CLK_PER1_C1 = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_PER1_C1),
    RST_CLK_ADCUI_CLK_PLLCPU  = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_PLLCPUo),
    RST_CLK_ADCUI_CLK_HSI_CLK = ((uint32_t)RST_CLK_ADC_CLOCK_ADC_C1_SEL_HSI_CLK)
} RST_CLK_ADCUI_Source_TypeDef;

#define IS_RST_CLK_ADCUI_CLK_SOURCE(SRC) (((SRC) == RST_CLK_ADCUI_CLK_CPU_C1) ||  \
                                          ((SRC) == RST_CLK_ADCUI_CLK_PER1_C1) || \
                                          ((SRC) == RST_CLK_ADCUI_CLK_PLLCPU) ||  \
                                          ((SRC) == RST_CLK_ADCUI_CLK_HSI_CLK))

/**
 * @brief RST_CLK ADCUI_CLK output clock ADCUI_CLK_DIV divider constants
 */
typedef enum {
    RST_CLK_ADCUI_PRESCALER_DIV_1   = ((uint32_t)0x0 << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_2   = ((uint32_t)0x8 << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_4   = ((uint32_t)0x9 << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_8   = ((uint32_t)0xA << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_16  = ((uint32_t)0xB << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_32  = ((uint32_t)0xC << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_64  = ((uint32_t)0xD << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_128 = ((uint32_t)0xE << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos),
    RST_CLK_ADCUI_PRESCALER_DIV_256 = ((uint32_t)0xF << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos)
} RST_CLK_ADCUI_C3_Prescaler_TypeDef;

#define IS_RST_CLK_ADCUI_C3_DIV(DIV) (((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_1) ||   \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_2) ||   \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_4) ||   \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_8) ||   \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_16) ||  \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_32) ||  \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_64) ||  \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_128) || \
                                      ((DIV) == RST_CLK_ADCUI_PRESCALER_DIV_256))

#define PCLK_BIT(BASE) ((uint32_t)(1 << ((((uint32_t)BASE) >> 15) & 0x1F)))

/**
 * @brief RST_CLK peripheral modules clock constants
 */
typedef enum {
    RST_CLK_PCLK_SSP     = PCLK_BIT(MDR_SSP_BASE),
    RST_CLK_PCLK_UART0   = PCLK_BIT(MDR_UART0_BASE),
    RST_CLK_PCLK_UART1   = PCLK_BIT(MDR_UART1_BASE),
    RST_CLK_PCLK_EEPROM  = PCLK_BIT(MDR_EEPROM_BASE),
    RST_CLK_PCLK_RST_CLK = PCLK_BIT(MDR_RST_CLK_BASE),
#if defined(USE_MDR32F21QI)
    RST_CLK_PCLK_DMA = PCLK_BIT(MDR_DMA_BASE),
    RST_CLK_PCLK_CRC = PCLK_BIT(MDR_CRC_BASE),
#endif
#if defined(USE_MDR32F23QI)
    RST_CLK_PCLK_I2C = PCLK_BIT(MDR_I2C_BASE),
    RST_CLK_PCLK_LCD = PCLK_BIT(MDR_LCD_BASE),
#endif
    RST_CLK_PCLK_ADC    = PCLK_BIT(MDR_ADC_BASE),
    RST_CLK_PCLK_WWDG   = PCLK_BIT(MDR_WWDG_BASE),
    RST_CLK_PCLK_IWDG   = PCLK_BIT(MDR_IWDG_BASE),
    RST_CLK_PCLK_POWER  = PCLK_BIT(MDR_POWER_BASE),
    RST_CLK_PCLK_BKP    = PCLK_BIT(MDR_BKP_BASE),
    RST_CLK_PCLK_ADCUI  = PCLK_BIT(MDR_ADCUI_BASE),
    RST_CLK_PCLK_TIMER0 = PCLK_BIT(MDR_TIMER0_BASE),
    RST_CLK_PCLK_TIMER1 = PCLK_BIT(MDR_TIMER1_BASE),
    RST_CLK_PCLK_PORTA  = PCLK_BIT(MDR_PORTA_BASE),
    RST_CLK_PCLK_PORTB  = PCLK_BIT(MDR_PORTB_BASE),
    RST_CLK_PCLK_PORTC  = PCLK_BIT(MDR_PORTC_BASE)
} RST_CLK_PCLK_TypeDef;

#if defined(USE_MDR32F21QI)
#define RST_CLK_PCLK_MASK (RST_CLK_PCLK_SSP | RST_CLK_PCLK_UART0 |     \
                           RST_CLK_PCLK_UART1 | RST_CLK_PCLK_EEPROM |  \
                           RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_PORTC | \
                           RST_CLK_PCLK_DMA | RST_CLK_PCLK_CRC |       \
                           RST_CLK_PCLK_ADC | RST_CLK_PCLK_WWDG |      \
                           RST_CLK_PCLK_IWDG | RST_CLK_PCLK_POWER |    \
                           RST_CLK_PCLK_BKP | RST_CLK_PCLK_ADCUI |     \
                           RST_CLK_PCLK_TIMER0 | RST_CLK_PCLK_TIMER1 | \
                           RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB)
#elif defined(USE_MDR32F23QI)
#define RST_CLK_PCLK_MASK (RST_CLK_PCLK_SSP | RST_CLK_PCLK_UART0 |     \
                           RST_CLK_PCLK_UART1 | RST_CLK_PCLK_EEPROM |  \
                           RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_PORTC | \
                           RST_CLK_PCLK_ADC | RST_CLK_PCLK_WWDG |      \
                           RST_CLK_PCLK_IWDG | RST_CLK_PCLK_POWER |    \
                           RST_CLK_PCLK_BKP | RST_CLK_PCLK_ADCUI |     \
                           RST_CLK_PCLK_TIMER0 | RST_CLK_PCLK_TIMER1 | \
                           RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB |   \
                           RST_CLK_PCLK_LCD | RST_CLK_PCLK_I2C)
#endif
#define IS_RST_CLK_PCLK(PCLK) (((PCLK)&RST_CLK_PCLK_MASK) == (PCLK))

/**
 * @brief RST_CLK PER1_C1 clock source constants
 */
typedef enum {
    RST_CLK_PER1_C1_CLK_SRC_LSI       = ((uint32_t)RST_CLK_PER1_CLOCK_C1_SEL_LSI),
    RST_CLK_PER1_C1_CLK_SRC_LSI_DIV_2 = ((uint32_t)RST_CLK_PER1_CLOCK_C1_SEL_LSIdiv2),
    RST_CLK_PER1_C1_CLK_SRC_LSE       = ((uint32_t)RST_CLK_PER1_CLOCK_C1_SEL_LSE),
    RST_CLK_PER1_C1_CLK_SRC_LSE_DIV_2 = ((uint32_t)RST_CLK_PER1_CLOCK_C1_SEL_LSEdiv2)
} RST_CLK_PER1_C1_TypeDef;

#define IS_RST_CLK_PER1_C1_CLK_SOURCE(SRC) (((SRC) == RST_CLK_PER1_C1_CLK_SRC_LSI) ||       \
                                            ((SRC) == RST_CLK_PER1_C1_CLK_SRC_LSI_DIV_2) || \
                                            ((SRC) == RST_CLK_PER1_C1_CLK_SRC_LSE) ||       \
                                            ((SRC) == RST_CLK_PER1_C1_CLK_SRC_LSE_DIV_2))

/**
 * @brief RST_CLK PER1_C2 clock source constants
 */
typedef enum {
    RST_CLK_PER1_C2_CLK_SRC_CPU_C1  = ((uint32_t)0x0),
    RST_CLK_PER1_C2_CLK_SRC_PER1_C1 = ((uint32_t)0x1),
    RST_CLK_PER1_C2_CLK_SRC_PLLCPU  = ((uint32_t)0x2),
    RST_CLK_PER1_C2_CLK_SRC_HSI_CLK = ((uint32_t)0x3)
} RST_CLK_PER1_C2_TypeDef;

#define IS_RST_CLK_PER1_C2_CLK_SOURCE(SRC) (((SRC) == RST_CLK_PER1_C2_CLK_SRC_CPU_C1) ||  \
                                            ((SRC) == RST_CLK_PER1_C2_CLK_SRC_PER1_C1) || \
                                            ((SRC) == RST_CLK_PER1_C2_CLK_SRC_PLLCPU) ||  \
                                            ((SRC) == RST_CLK_PER1_C2_CLK_SRC_HSI_CLK))

/**
 * @brief RST_CLK PER1 peripheral selection constants
 */
typedef enum {
    RST_CLK_PER1_C2_TIM0  = ((uint32_t)0x0),
    RST_CLK_PER1_C2_TIM1  = ((uint32_t)0x1),
    RST_CLK_PER1_C2_UART0 = ((uint32_t)0x2),
    RST_CLK_PER1_C2_UART1 = ((uint32_t)0x3),
    RST_CLK_PER1_C2_SSP   = ((uint32_t)0x4)
} RST_CLK_PER1_C2_X_TypeDef;

#define IS_RST_CLK_PER1_CLK(PER1_CLK) (((PER1_CLK) == RST_CLK_PER1_C2_TIM0) ||  \
                                       ((PER1_CLK) == RST_CLK_PER1_C2_TIM1) ||  \
                                       ((PER1_CLK) == RST_CLK_PER1_C2_UART0) || \
                                       ((PER1_CLK) == RST_CLK_PER1_C2_UART1) || \
                                       ((PER1_CLK) == RST_CLK_PER1_C2_SSP))

/**
 * @brief RST_CLK PER1_C2 divider constants
 */
typedef enum {
    RST_CLK_PER1_PRESCALER_DIV_1   = ((uint32_t)0x0),
    RST_CLK_PER1_PRESCALER_DIV_2   = ((uint32_t)0x1),
    RST_CLK_PER1_PRESCALER_DIV_4   = ((uint32_t)0x2),
    RST_CLK_PER1_PRESCALER_DIV_8   = ((uint32_t)0x3),
    RST_CLK_PER1_PRESCALER_DIV_16  = ((uint32_t)0x4),
    RST_CLK_PER1_PRESCALER_DIV_32  = ((uint32_t)0x5),
    RST_CLK_PER1_PRESCALER_DIV_64  = ((uint32_t)0x6),
    RST_CLK_PER1_PRESCALER_DIV_128 = ((uint32_t)0x7)
} RST_CLK_PER1_C2_Prescaler_TypeDef;

#define IS_RST_CLK_PER1_C2_DIV(DIV) (((DIV) == RST_CLK_PER1_PRESCALER_DIV_1) ||  \
                                     ((DIV) == RST_CLK_PER1_PRESCALER_DIV_2) ||  \
                                     ((DIV) == RST_CLK_PER1_PRESCALER_DIV_4) ||  \
                                     ((DIV) == RST_CLK_PER1_PRESCALER_DIV_8) ||  \
                                     ((DIV) == RST_CLK_PER1_PRESCALER_DIV_16) || \
                                     ((DIV) == RST_CLK_PER1_PRESCALER_DIV_32) || \
                                     ((DIV) == RST_CLK_PER1_PRESCALER_DIV_64) || \
                                     ((DIV) == RST_CLK_PER1_PRESCALER_DIV_128))

/**
 * @brief RST_CLK flag identifiers
 */
typedef enum {
    RST_CLK_FLAG_HSERDY    = RST_CLK_CLOCK_STATUS_HSERDY,
    RST_CLK_FLAG_PLLCPURDY = RST_CLK_CLOCK_STATUS_PLLCPURDY
} RST_CLK_Flags_TypeDef;

#define IS_RST_CLK_FLAG(FLAG) (((FLAG) == RST_CLK_FLAG_HSERDY) || \
                               ((FLAG) == RST_CLK_FLAG_PLLCPURDY))

/**
 * @brief RST_CLK HSI clock HSI_C1_SEL divider constants
 */
typedef enum {
    RST_CLK_HSI_PRESCALER_DIV_1   = ((uint32_t)0x0 << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_2   = ((uint32_t)0x8 << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_4   = ((uint32_t)0x9 << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_8   = ((uint32_t)0xA << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_16  = ((uint32_t)0xB << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_32  = ((uint32_t)0xC << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_64  = ((uint32_t)0xD << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_128 = ((uint32_t)0xE << RST_CLK_RTC_CLOCK_HSI_SEL_Pos),
    RST_CLK_HSI_PRESCALER_DIV_256 = ((uint32_t)0xF << RST_CLK_RTC_CLOCK_HSI_SEL_Pos)
} RST_CLK_HSI_C1_Prescaler_TypeDef;

#define IS_RST_CLK_HSI_CLK_DIV(DIV) (((DIV) == RST_CLK_HSI_PRESCALER_DIV_1) ||   \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_2) ||   \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_4) ||   \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_8) ||   \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_16) ||  \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_32) ||  \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_64) ||  \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_128) || \
                                     ((DIV) == RST_CLK_HSI_PRESCALER_DIV_256))

/**
 * @brief RST_CLK HSE clock HSE_C1_SEL divider constants for RTCHSE
 */
typedef enum {
    RST_CLK_HSE_PRESCALER_DIV_1   = ((uint32_t)0x0 << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_2   = ((uint32_t)0x8 << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_4   = ((uint32_t)0x9 << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_8   = ((uint32_t)0xA << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_16  = ((uint32_t)0xB << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_32  = ((uint32_t)0xC << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_64  = ((uint32_t)0xD << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_128 = ((uint32_t)0xE << RST_CLK_RTC_CLOCK_HSE_SEL_Pos),
    RST_CLK_HSE_PRESCALER_DIV_256 = ((uint32_t)0xF << RST_CLK_RTC_CLOCK_HSE_SEL_Pos)
} RST_CLK_HSE_C1_Prescaler_TypeDef;

#define IS_RST_CLK_HSE_CLK_DIV(DIV) (((DIV) == RST_CLK_HSE_PRESCALER_DIV_1) ||   \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_2) ||   \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_4) ||   \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_8) ||   \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_16) ||  \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_32) ||  \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_64) ||  \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_128) || \
                                     ((DIV) == RST_CLK_HSE_PRESCALER_DIV_256))

/** @} */ /* End of group RST_CLK_Exported_Types */

/** @defgroup RST_CLK_Exported_Defines RST_CLK Exported Defines
 * @{
 */

#define IS_RST_CLK_HSI_TRIM_VALUE(TRIM) ((TRIM) <= 0x3F)
#define IS_RST_CLK_LSI_TRIM_VALUE(TRIM) ((TRIM) <= 0x1F)

/** @} */ /* End of group RST_CLK_Exported_Defines */

/** @defgroup RST_CLK_Exported_Functions RST_CLK Exported Functions
 * @{
 */

void RST_CLK_DeInit(void);

void        RST_CLK_HSE_Config(RST_CLK_HSE_Mode_TypeDef HSE_Mode);
ErrorStatus RST_CLK_HSE_GetStatus(void);

void        RST_CLK_CPU_PLL_Config(RST_CLK_PLLCPU_Source_TypeDef PLLCPU_Source, uint32_t PLLCPU_Multiplier);
void        RST_CLK_CPU_PLL_Cmd(FunctionalState NewState);
ErrorStatus RST_CLK_CPU_PLL_GetStatus(void);

void RST_CLK_CPU_C1_ClkSelection(RST_CLK_CPU_C1_Source_TypeDef CPU_C1_Source);
void RST_CLK_CPU_C2_ClkSelection(RST_CLK_CPU_C2_Source_TypeDef CPU_C2_Source);
void RST_CLK_CPU_C3_SetPrescaler(RST_CLK_CPU_C3_Prescaler_TypeDef CPU_CLK_DivValue);
void RST_CLK_HCLK_ClkSelection(RST_CLK_HCLK_Source_TypeDef CPU_HCLK_Source);

void RST_CLK_ADC_ClkSelection(RST_CLK_ADC_Source_TypeDef ADC_CLK_Source);
void RST_CLK_ADC_SetPrescaler(RST_CLK_ADC_C3_Prescaler_TypeDef ADC_CLK_DivValue);
void RST_CLK_ADC_ClkCmd(FunctionalState NewState);

void RST_CLK_ADCUI_ClkDeInit(void);
void RST_CLK_ADCUI_ClkSelection(RST_CLK_ADCUI_Source_TypeDef ADCUI_CLK_C1_Source);
void RST_CLK_ADCUI_SetPrescaler(RST_CLK_ADCUI_C3_Prescaler_TypeDef ADCUI_CLK_DivValue);
void RST_CLK_ADCUI_ClkCmd(FunctionalState NewState);

void RST_CLK_HSI_C1_SetPrescaler(RST_CLK_HSI_C1_Prescaler_TypeDef HSI_CLK_DivValue);
void RST_CLK_RTC_HSI_ClkCmd(FunctionalState NewState);

void RST_CLK_HSE_C1_SetPrescaler(RST_CLK_HSE_C1_Prescaler_TypeDef HSE_CLK_DivValue);
void RST_CLK_RTC_HSE_ClkCmd(FunctionalState NewState);

void RST_CLK_PER1_C1_ClkSelection(RST_CLK_PER1_C1_TypeDef PER1_C1_Source);
#if defined(USE_MDR32F21QI)
void RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_TypeDef PER1_C2_Source);
#elif defined(USE_MDR32F23QI)
void RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_X_TypeDef PER1_CLK, RST_CLK_PER1_C2_TypeDef PER1_C2_Source);
#endif
void RST_CLK_PER1_C2_SetPrescaler(RST_CLK_PER1_C2_X_TypeDef PER1_CLK, RST_CLK_PER1_C2_Prescaler_TypeDef PER1_C2_DivValue);
void RST_CLK_PER1_C2_Cmd(RST_CLK_PER1_C2_X_TypeDef PER1_CLK, FunctionalState NewState);

#if defined(USE_MDR32F21QI)
void            RST_CLK_DMACmd(FunctionalState NewState);
FunctionalState RST_CLK_DMAState(void);
#endif

void            RST_CLK_DEBUGCmd(FunctionalState NewState);
FunctionalState RST_CLK_DEBUGState(void);

void RST_CLK_PCLKCmd(uint32_t RST_CLK_PCLK, FunctionalState NewState);

void RST_CLK_GetClocksFreq(RST_CLK_Freq_TypeDef* RST_CLK_Clocks);

FlagStatus RST_CLK_GetFlagStatus(RST_CLK_Flags_TypeDef RST_CLK_Flag);

/** @} */ /* End of group RST_CLK_Exported_Functions */

/** @} */ /* End of group RST_CLK */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_RST_CLK_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_rst_clk.h */

