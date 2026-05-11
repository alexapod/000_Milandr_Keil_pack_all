/**
 *******************************************************************************
 * @file    MDR32F2xQI_timer.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    24/05/2023
 * @brief   This file contains all the functions prototypes for the TIMER
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
#ifndef __MDR32F2xQI_TIMER_H
#define __MDR32F2xQI_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32F2xQI_config.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup TIMER TIMER
 * @{
 */

/** @defgroup TIMER_Exported_Types TIMER Exported Types
 * @{
 */

/**
 * @brief TIMER Counter Event Source
 */
typedef enum {
    TIMER_CNT_EVNT_SRC_TIM_CLK = TIMER_CNTRL_EVENT_SEL_TIM_CLK, /*!< Selects rising edge event TIM_CLK. */
    TIMER_CNT_EVNT_SRC_TIM0    = TIMER_CNTRL_EVENT_SEL_TIM0,    /*!< Selects TIMER0 (CNT == ARR) event. */
    TIMER_CNT_EVNT_SRC_TIM1    = TIMER_CNTRL_EVENT_SEL_TIM1,    /*!< Selects TIMER1 (CNT == ARR) event. */
    TIMER_CNT_EVNT_SRC_CH1     = TIMER_CNTRL_EVENT_SEL_CH1,     /*!< Selects Channel 1 event. */
#if defined(USE_MDR32F21QI)
    TIMER_CNT_EVNT_SRC_CH2 = TIMER_CNTRL_EVENT_SEL_CH2,         /*!< Selects Channel 2 event. */
    TIMER_CNT_EVNT_SRC_CH3 = TIMER_CNTRL_EVENT_SEL_CH3,         /*!< Selects Channel 3 event. */
    TIMER_CNT_EVNT_SRC_CH4 = TIMER_CNTRL_EVENT_SEL_CH4,         /*!< Selects Channel 4 event. */
#endif
    TIMER_CNT_EVNT_SRC_ETR_RE = TIMER_CNTRL_EVENT_SEL_ETR_RE,   /*!< Selects a rising edge event on ETR. */
    TIMER_CNT_EVNT_SRC_ETR_FE = TIMER_CNTRL_EVENT_SEL_ETR_FE    /*!< Selects a falling edge event on ETR. */
} TIMER_CNT_EventSource_TypeDef;

#if defined(USE_MDR32F21QI)
#define IS_TIMER_COUNTER_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CNT_EVNT_SRC_TIM_CLK) || \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_TIM0) ||    \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_TIM1) ||    \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_CH1) ||     \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_CH2) ||     \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_CH3) ||     \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_CH4) ||     \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_ETR_RE) ||  \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_ETR_FE))
#elif defined(USE_MDR32F23QI)
#define IS_TIMER_COUNTER_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CNT_EVNT_SRC_TIM_CLK) || \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_TIM0) ||    \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_TIM1) ||    \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_CH1) ||     \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_ETR_RE) ||  \
                                               ((SOURCE) == TIMER_CNT_EVNT_SRC_ETR_FE))
#endif

/**
 * @brief TIMER Counter Mode
 */
typedef enum {
    TIMER_CNT_MODE_CLK_FIXED_DIR  = TIMER_CNTRL_CNT_MODE_CLK_FIXED_DIR,  /*!< The value of CNT changes on rising edge of TIM_CLK. The direction of the count remains constant. */
    TIMER_CNT_MODE_CLK_CHANGE_DIR = TIMER_CNTRL_CNT_MODE_CLK_CHANGE_DIR, /*!< The value of CNT changes on rising edge of TIM_CLK. The direction of the count changes. */
    TIMER_CNT_MODE_EVNT_FIXED_DIR = TIMER_CNTRL_CNT_MODE_EVNT_FIXED_DIR  /*!< The value of CNT changes on the specified event. The direction of the count remains constant. */
} TIMER_CNT_Mode_TypeDef;

#define IS_TIMER_COUNTER_MODE(MODE) (((MODE) == TIMER_CNT_MODE_CLK_FIXED_DIR) ||  \
                                     ((MODE) == TIMER_CNT_MODE_CLK_CHANGE_DIR) || \
                                     ((MODE) == TIMER_CNT_MODE_EVNT_FIXED_DIR))

/**
 * @brief TIMER Counter Direction
 */
typedef enum {
    TIMER_CNT_DIR_UP   = (((uint32_t)0x0) << TIMER_CNTRL_DIR_Pos), /*!< Increments the timer CNT counter value. */
    TIMER_CNT_DIR_DOWN = (((uint32_t)0x1) << TIMER_CNTRL_DIR_Pos)  /*!< Decrements the timer CNT counter value. */
} TIMER_CNT_Dir_TypeDef;

#define IS_TIMER_COUNTER_DIR(DIR) (((DIR) == TIMER_CNT_DIR_UP) || \
                                   ((DIR) == TIMER_CNT_DIR_DOWN))

/**
 * @brief TIMER FDTS Prescaler
 */
typedef enum {
    TIMER_FDTS_PRESCALER_DIV_1 = TIMER_CNTRL_FDTS_DIV_1, /*!< The FDTS data sampling rate is every TIM_CLK. */
    TIMER_FDTS_PRESCALER_DIV_2 = TIMER_CNTRL_FDTS_DIV_2, /*!< The FDTS data sampling rate is every 2nd TIM_CLK. */
    TIMER_FDTS_PRESCALER_DIV_3 = TIMER_CNTRL_FDTS_DIV_3, /*!< The FDTS data sampling rate is every 3rd TIM_CLK. */
    TIMER_FDTS_PRESCALER_DIV_4 = TIMER_CNTRL_FDTS_DIV_4  /*!< The FDTS data sampling rate is every 4th TIM_CLK. */
} TIMER_FDTS_Prescaler_TypeDef;

#define IS_TIMER_FDTS_PRESCALER(VALUE) (((VALUE) == TIMER_FDTS_PRESCALER_DIV_1) || \
                                        ((VALUE) == TIMER_FDTS_PRESCALER_DIV_2) || \
                                        ((VALUE) == TIMER_FDTS_PRESCALER_DIV_3) || \
                                        ((VALUE) == TIMER_FDTS_PRESCALER_DIV_4))

/**
 * @brief TIMER ARR Update Mode
 */
typedef enum {
    TIMER_ARR_UPD_IMMEDIATELY   = (((uint32_t)0x0) << TIMER_CNTRL_ARRB_EN_Pos), /*!< The ARR register is updated immediately. */
    TIMER_ARR_UPD_ON_CNT_EQ_ARR = (((uint32_t)0x1) << TIMER_CNTRL_ARRB_EN_Pos)  /*!< The ARR register is updated at (CNT == ARR) condition. */
} TIMER_ARR_UpdateMode_TypeDef;

#define IS_TIMER_ARR_UPDATE_MODE(MODE) (((MODE) == TIMER_ARR_UPD_IMMEDIATELY) || \
                                        ((MODE) == TIMER_ARR_UPD_ON_CNT_EQ_ARR))

/**
 * @brief TIMER ETR Filter configuration
 */
typedef enum {
    TIMER_ETR_FILTER_1FF_AT_FDTS        = TIMER_BRKETR_CNTRL_ETR_FILTER_1_FDTS,        /*!< Signal is latched by 1 trigger at FDTS frequency. */
    TIMER_ETR_FILTER_2FF_AT_TIM_CLK     = TIMER_BRKETR_CNTRL_ETR_FILTER_2_TIM_CLK,     /*!< Signal is latched by 2 triggers at TIM_CLK frequency (2xT_TIM_CLK). */
    TIMER_ETR_FILTER_4FF_AT_TIM_CLK     = TIMER_BRKETR_CNTRL_ETR_FILTER_4_TIM_CLK,     /*!< Signal is latched by 4 triggers at TIM_CLK frequency (4xT_TIM_CLK). */
    TIMER_ETR_FILTER_8FF_AT_TIM_CLK     = TIMER_BRKETR_CNTRL_ETR_FILTER_8_TIM_CLK,     /*!< Signal is latched by 8 triggers at TIM_CLK frequency (8xT_TIM_CLK). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_2  = TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_2,  /*!< Signal is latched by 6 triggers at FDTS/2  frequency (12xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_2  = TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_2,  /*!< Signal is latched by 8 triggers at FDTS/2  frequency (16xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_4  = TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_4,  /*!< Signal is latched by 6 triggers at FDTS/4  frequency (24xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_4  = TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_4,  /*!< Signal is latched by 8 triggers at FDTS/4  frequency (32xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_8  = TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_8,  /*!< Signal is latched by 6 triggers at FDTS/8  frequency (48xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_8  = TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_8,  /*!< Signal is latched by 8 triggers at FDTS/8  frequency (64xT_FDTS). */
    TIMER_ETR_FILTER_5FF_AT_FDTS_DIV_16 = TIMER_BRKETR_CNTRL_ETR_FILTER_5_FDTS_DIV_16, /*!< Signal is latched by 5 triggers at FDTS/16 frequency (80xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_16 = TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_16, /*!< Signal is latched by 6 triggers at FDTS/16 frequency (96xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_16 = TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_16, /*!< Signal is latched by 8 triggers at FDTS/16 frequency (128xT_FDTS). */
    TIMER_ETR_FILTER_5FF_AT_FDTS_DIV_32 = TIMER_BRKETR_CNTRL_ETR_FILTER_5_FDTS_DIV_32, /*!< Signal is latched by 5 triggers at FDTS/32 frequency (160xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_32 = TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_32, /*!< Signal is latched by 6 triggers at FDTS/32 frequency (192xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_32 = TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_32  /*!< Signal is latched by 8 triggers at FDTS/32 frequency (256xT_FDTS). */
} TIMER_ETR_Filter_TypeDef;

#define IS_TIMER_ETR_FILTER(FILTER) (((FILTER) == TIMER_ETR_FILTER_1FF_AT_FDTS) ||        \
                                     ((FILTER) == TIMER_ETR_FILTER_2FF_AT_TIM_CLK) ||     \
                                     ((FILTER) == TIMER_ETR_FILTER_4FF_AT_TIM_CLK) ||     \
                                     ((FILTER) == TIMER_ETR_FILTER_8FF_AT_TIM_CLK) ||     \
                                     ((FILTER) == TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_2) ||  \
                                     ((FILTER) == TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_2) ||  \
                                     ((FILTER) == TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_4) ||  \
                                     ((FILTER) == TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_4) ||  \
                                     ((FILTER) == TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_8) ||  \
                                     ((FILTER) == TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_8) ||  \
                                     ((FILTER) == TIMER_ETR_FILTER_5FF_AT_FDTS_DIV_16) || \
                                     ((FILTER) == TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_16) || \
                                     ((FILTER) == TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_16) || \
                                     ((FILTER) == TIMER_ETR_FILTER_5FF_AT_FDTS_DIV_32) || \
                                     ((FILTER) == TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_32) || \
                                     ((FILTER) == TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_32))

/**
 * @brief TIMER ETR Prescaler
 */
typedef enum {
    TIMER_ETR_PRESCALER_DIV_1 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_1, /*!< Selects input frequency divider by 1. */
    TIMER_ETR_PRESCALER_DIV_2 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_2, /*!< Selects input frequency divider by 2. */
    TIMER_ETR_PRESCALER_DIV_4 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_4, /*!< Selects input frequency divider by 4. */
    TIMER_ETR_PRESCALER_DIV_8 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_8  /*!< Selects input frequency divider by 8. */
} TIMER_ETR_Prescaler_TypeDef;

#define IS_TIMER_ETR_PRESCALER(VALUE) (((VALUE) == TIMER_ETR_PRESCALER_DIV_1) || \
                                       ((VALUE) == TIMER_ETR_PRESCALER_DIV_2) || \
                                       ((VALUE) == TIMER_ETR_PRESCALER_DIV_4) || \
                                       ((VALUE) == TIMER_ETR_PRESCALER_DIV_8))

/**
 * @brief TIMER ETR Polarity Config
 */
typedef enum {
    TIMER_ETR_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_BRKETR_CNTRL_ETR_INV_Pos), /*!< ETR input is not inverted. */
    TIMER_ETR_POLARITY_INV     = (((uint32_t)0x1) << TIMER_BRKETR_CNTRL_ETR_INV_Pos)  /*!< ETR input is inverted. */
} TIMER_ETR_Polarity_TypeDef;

#define IS_TIMER_ETR_POLARITY(STATE) (((STATE) == TIMER_ETR_POLARITY_NON_INV) || \
                                      ((STATE) == TIMER_ETR_POLARITY_INV))

/**
 * @brief TIMER BRK Polarity Config
 */
typedef enum {
    TIMER_BRK_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_BRKETR_CNTRL_BRK_INV_Pos), /*!< BRK input is not inverted. */
    TIMER_BRK_POLARITY_INV     = (((uint32_t)0x1) << TIMER_BRKETR_CNTRL_BRK_INV_Pos)  /*!< BRK input is inverted. */
} TIMER_BRK_Polarity_TypeDef;

#define IS_TIMER_BRK_POLARITY(STATE) (((STATE) == TIMER_BRK_POLARITY_NON_INV) || \
                                      ((STATE) == TIMER_BRK_POLARITY_INV))

/**
 * @brief TIMER Channel Number
 */
typedef enum {
    TIMER_CH1 = ((uint32_t)0x0), /*!< Specifies the TIMER channel 1. */
#if defined(USE_MDR32F21QI)
    TIMER_CH2 = ((uint32_t)0x1), /*!< Specifies the TIMER channel 2. */
    TIMER_CH3 = ((uint32_t)0x2), /*!< Specifies the TIMER channel 3. */
    TIMER_CH4 = ((uint32_t)0x3)  /*!< Specifies the TIMER channel 4. */
#endif
} TIMER_CH_Number_TypeDef;

#if defined(USE_MDR32F21QI)
#define IS_TIMER_CHANNEL_NUMBER(NUMBER) (((NUMBER) == TIMER_CH1) || \
                                         ((NUMBER) == TIMER_CH2) || \
                                         ((NUMBER) == TIMER_CH3) || \
                                         ((NUMBER) == TIMER_CH4))
#elif defined(USE_MDR32F23QI)
#define IS_TIMER_CHANNEL_NUMBER(NUMBER) ((NUMBER) == TIMER_CH1)
#endif

/**
 * @brief TIMER Channel Mode
 */
typedef enum {
    TIMER_CH_MODE_PWM     = (((uint32_t)0x0) << TIMER_CH_CNTRL_CAP_nPWM_Pos), /*!< Specifies the PWM channel mode. */
    TIMER_CH_MODE_CAPTURE = (((uint32_t)0x1) << TIMER_CH_CNTRL_CAP_nPWM_Pos)  /*!< Specifies the Capture channel mode. */
} TIMER_CH_Mode_TypeDef;

#define IS_TIMER_CHANNEL_MODE(MODE) (((MODE) == TIMER_CH_MODE_PWM) || \
                                     ((MODE) == TIMER_CH_MODE_CAPTURE))

/**
 * @brief TIMER Channel REF Format in PWM mode
 */
typedef enum {
    TIMER_CH_PWM_REF_FORMAT_0 = TIMER_CH_CNTRL_OCCM_FORMAT_0, /*!< REF = 0. */
    TIMER_CH_PWM_REF_FORMAT_1 = TIMER_CH_CNTRL_OCCM_FORMAT_1, /*!< REF = 1 if: (CNT == CCR) or ((CNT == CCR1) and CCR1_EN = 1),
                                                                   else REF = 0. */
    TIMER_CH_PWM_REF_FORMAT_2 = TIMER_CH_CNTRL_OCCM_FORMAT_2, /*!< REF = 0 if: (CNT == CCR) or ((CNT == CCR1) and CCR1_EN = 1),
                                                                   else REF = 1. */
    TIMER_CH_PWM_REF_FORMAT_3 = TIMER_CH_CNTRL_OCCM_FORMAT_3, /*!< Toggle REF state if: (CNT == CCR) or
                                                                                       ((CNT == CCR1) and CCR1_EN = 1). */
    TIMER_CH_PWM_REF_FORMAT_4 = TIMER_CH_CNTRL_OCCM_FORMAT_4, /*!< REF = 0. */
    TIMER_CH_PWM_REF_FORMAT_5 = TIMER_CH_CNTRL_OCCM_FORMAT_5, /*!< REF = 1. */
    TIMER_CH_PWM_REF_FORMAT_6 = TIMER_CH_CNTRL_OCCM_FORMAT_6, /*!< If CCR1_EN = 0:
                                                                     DIR = 0: REF = 1 if (CNT < CCR), else REF = 0,
                                                                     DIR = 1: REF = 0 if (CNT > CCR), else REF = 1,
                                                                   else if CCR1_EN = 1:
                                                                     DIR = 0: REF = 0 if (CCR ≤ CNT ≤ CCR1), else REF = 1,
                                                                     DIR = 1: REF = 0 if (CCR < CNT < CCR1), else REF = 1.
                                                                   The condition (CCR < CCR1) must be observed. */
    TIMER_CH_PWM_REF_FORMAT_7 = TIMER_CH_CNTRL_OCCM_FORMAT_7  /*!< If CCR1_EN = 0:
                                                                      DIR = 0: REF = 0 if (CNT < CCR), else REF = 1,
                                                                      DIR = 1: REF = 1 if (CNT > CCR), else REF = 0,
                                                                   else if CCR1_EN = 1:
                                                                      DIR = 0: REF = 1 if (CCR ≤ CNT ≤ CCR1), else REF = 0,
                                                                      DIR = 1: REF = 1 if (CCR < CNT < CCR1), else REF = 0.
                                                                   The condition (CCR < CCR1) must be observed. */
} TIMER_CH_PWM_REF_Format_TypeDef;

#define IS_TIMER_CHANNEL_PWM_REF_FORMAT(FORMAT) (((FORMAT) == TIMER_CH_PWM_REF_FORMAT_0) || \
                                                 ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_1) || \
                                                 ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_2) || \
                                                 ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_3) || \
                                                 ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_4) || \
                                                 ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_5) || \
                                                 ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_6) || \
                                                 ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_7))

/**
 * @brief TIMER CCR and CCR1 Update mode in PWM mode
 */
typedef enum {
    TIMER_CH_PWM_CCR_UPD_IMMEDIATELY = (((uint32_t)0x0) << TIMER_CH_CNTRL2_CCRRLD_Pos), /*!< The CCR and CCR1 registers is updated immediately. */
    TIMER_CH_PWM_CCR_UPD_ON_CNT_EQ_0 = (((uint32_t)0x1) << TIMER_CH_CNTRL2_CCRRLD_Pos)  /*!< The CCR and CCR1 registers is updated at (CNT == 0) condition. */
} TIMER_CH_PWM_CCR_UpdateMode_TypeDef;

#define IS_TIMER_CHANNEL_PWM_CCR_UPDATE_MODE(MODE) (((MODE) == TIMER_CH_PWM_CCR_UPD_IMMEDIATELY) || \
                                                    ((MODE) == TIMER_CH_PWM_CCR_UPD_ON_CNT_EQ_0))

/**
 * @brief TIMER Channel Events Prescaler in capture mode
 */
typedef enum {
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_1 = TIMER_CH_CNTRL_CHPSC_DIV_1, /*!< Each event is captured. */
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_2 = TIMER_CH_CNTRL_CHPSC_DIV_2, /*!< Capturing every 2nd event */
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_4 = TIMER_CH_CNTRL_CHPSC_DIV_4, /*!< Capturing every 4th event */
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_8 = TIMER_CH_CNTRL_CHPSC_DIV_8  /*!< Capturing every 8th event */
} TIMER_CH_CAP_EventPrescaler_TypeDef;

#define IS_TIMER_CHANNEL_CAP_EVENT_PRESCALER(VALUE) (((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_1) || \
                                                     ((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_2) || \
                                                     ((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_4) || \
                                                     ((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_8))

/**
 * @brief TIMER Channel CCR Event Source in capture mode
 */
typedef enum {
    TIMER_CH_CAP_CCR_EVNT_SRC_RE = TIMER_CH_CNTRL_CHSEL_CH_RE,        /*!< Selects rising edge from current TIMER channel. */
    TIMER_CH_CAP_CCR_EVNT_SRC_FE = TIMER_CH_CNTRL_CHSEL_CH_FE,        /*!< Selects falling edge from current TIMER channel. */
#if defined(USE_MDR32F21QI)
    TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp1 = TIMER_CH_CNTRL_CHSEL_CHp1_RE, /*!< Selects rising edge from other TIMER channel (current channel plus 1). */
    TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp2 = TIMER_CH_CNTRL_CHSEL_CHp2_RE  /*!< Selects rising edge from other TIMER channel (current channel plus 2). */
#endif
} TIMER_CH_CAP_CCR_EventSource_TypeDef;

#if defined(USE_MDR32F21QI)
#define IS_TIMER_CHANNEL_CAP_CCR_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_RE) ||      \
                                                       ((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_FE) ||      \
                                                       ((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp1) || \
                                                       ((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp2))
#elif defined(USE_MDR32F23QI)
#define IS_TIMER_CHANNEL_CAP_CCR_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_RE) || \
                                                       ((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_FE))
#endif

/**
 * @brief TIMER Channel CCR1 Event Source in capture mode
 */
typedef enum {
    TIMER_CH_CAP_CCR1_EVNT_SRC_RE = TIMER_CH_CNTRL2_CHSEL_CH_RE,        /*!< Selects rising edge from current TIMER channel. */
    TIMER_CH_CAP_CCR1_EVNT_SRC_FE = TIMER_CH_CNTRL2_CHSEL_CH_FE,        /*!< Selects falling edge from current TIMER channel. */
#if defined(USE_MDR32F21QI)
    TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp1 = TIMER_CH_CNTRL2_CHSEL_CHp1_FE, /*!< Selects falling edge from other TIMER channel (current channel plus 1). */
    TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp2 = TIMER_CH_CNTRL2_CHSEL_CHp2_FE  /*!< Selects falling edge from other TIMER channel (current channel plus 2). */
#endif
} TIMER_CH_CAP_CCR1_EventSource_TypeDef;

#if defined(USE_MDR32F21QI)
#define IS_TIMER_CHANNEL_CAP_CCR1_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_RE) ||      \
                                                        ((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_FE) ||      \
                                                        ((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp1) || \
                                                        ((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp2))
#elif defined(USE_MDR32F23QI)
#define IS_TIMER_CHANNEL_CAP_CCR1_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_RE) || \
                                                        ((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_FE))
#endif

/**
 * @brief TIMER Channel Filter configuration
 */
typedef enum {
    TIMER_CH_FILTER_1FF_AT_FDTS        = TIMER_CH_CNTRL_CHFLTR_1_FDTS,        /*!< Signal is latched by 1 trigger at FDTS frequency. */
    TIMER_CH_FILTER_2FF_AT_TIM_CLK     = TIMER_CH_CNTRL_CHFLTR_2_TIM_CLK,     /*!< Signal is latched by 2 triggers at TIM_CLK frequency (2xT_TIM_CLK). */
    TIMER_CH_FILTER_4FF_AT_TIM_CLK     = TIMER_CH_CNTRL_CHFLTR_4_TIM_CLK,     /*!< Signal is latched by 4 triggers at TIM_CLK frequency (4xT_TIM_CLK). */
    TIMER_CH_FILTER_8FF_AT_TIM_CLK     = TIMER_CH_CNTRL_CHFLTR_8_TIM_CLK,     /*!< Signal is latched by 8 triggers at TIM_CLK frequency (8xT_TIM_CLK). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_2  = TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_2,  /*!< Signal is latched by 6 triggers at FDTS/2  frequency (12xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_2  = TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_2,  /*!< Signal is latched by 8 triggers at FDTS/2  frequency (16xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_4  = TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_4,  /*!< Signal is latched by 6 triggers at FDTS/4  frequency (24xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_4  = TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_4,  /*!< Signal is latched by 8 triggers at FDTS/4  frequency (32xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_8  = TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_8,  /*!< Signal is latched by 6 triggers at FDTS/8  frequency (48xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_8  = TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_8,  /*!< Signal is latched by 8 triggers at FDTS/8  frequency (64xT_FDTS). */
    TIMER_CH_FILTER_5FF_AT_FDTS_DIV_16 = TIMER_CH_CNTRL_CHFLTR_5_FDTS_DIV_16, /*!< Signal is latched by 5 triggers at FDTS/16 frequency (80xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_16 = TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_16, /*!< Signal is latched by 6 triggers at FDTS/16 frequency (96xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_16 = TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_16, /*!< Signal is latched by 8 triggers at FDTS/16 frequency (128xT_FDTS). */
    TIMER_CH_FILTER_5FF_AT_FDTS_DIV_32 = TIMER_CH_CNTRL_CHFLTR_5_FDTS_DIV_32, /*!< Signal is latched by 5 triggers at FDTS/32 frequency (160xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_32 = TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_32, /*!< Signal is latched by 6 triggers at FDTS/32 frequency (192xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_32 = TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_32  /*!< Signal is latched by 8 triggers at FDTS/32 frequency (256xT_FDTS). */
} TIMER_CH_Filter_TypeDef;

#define IS_TIMER_CHANNEL_FILTER(FILTER) (((FILTER) == TIMER_CH_FILTER_1FF_AT_FDTS) ||        \
                                         ((FILTER) == TIMER_CH_FILTER_2FF_AT_TIM_CLK) ||     \
                                         ((FILTER) == TIMER_CH_FILTER_4FF_AT_TIM_CLK) ||     \
                                         ((FILTER) == TIMER_CH_FILTER_8FF_AT_TIM_CLK) ||     \
                                         ((FILTER) == TIMER_CH_FILTER_6FF_AT_FDTS_DIV_2) ||  \
                                         ((FILTER) == TIMER_CH_FILTER_8FF_AT_FDTS_DIV_2) ||  \
                                         ((FILTER) == TIMER_CH_FILTER_6FF_AT_FDTS_DIV_4) ||  \
                                         ((FILTER) == TIMER_CH_FILTER_8FF_AT_FDTS_DIV_4) ||  \
                                         ((FILTER) == TIMER_CH_FILTER_6FF_AT_FDTS_DIV_8) ||  \
                                         ((FILTER) == TIMER_CH_FILTER_8FF_AT_FDTS_DIV_8) ||  \
                                         ((FILTER) == TIMER_CH_FILTER_5FF_AT_FDTS_DIV_16) || \
                                         ((FILTER) == TIMER_CH_FILTER_6FF_AT_FDTS_DIV_16) || \
                                         ((FILTER) == TIMER_CH_FILTER_8FF_AT_FDTS_DIV_16) || \
                                         ((FILTER) == TIMER_CH_FILTER_5FF_AT_FDTS_DIV_32) || \
                                         ((FILTER) == TIMER_CH_FILTER_6FF_AT_FDTS_DIV_32) || \
                                         ((FILTER) == TIMER_CH_FILTER_8FF_AT_FDTS_DIV_32))

/**
 * @brief TIMER Channel Positive Output Polarity
 */
typedef enum {
    TIMER_CH_OUTP_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_CH_CNTRL1_INV_Pos), /*!< The channel positive output is not inverted. */
    TIMER_CH_OUTP_POLARITY_INV     = (((uint32_t)0x1) << TIMER_CH_CNTRL1_INV_Pos)  /*!< The channel positive output is inverted. */
} TIMER_CH_OUTP_Polarity_TypeDef;

#define IS_TIMER_CHANNEL_OUTP_POLARITY(STATE) (((STATE) == TIMER_CH_OUTP_POLARITY_NON_INV) || \
                                               ((STATE) == TIMER_CH_OUTP_POLARITY_INV))

/**
 * @brief TIMER Channel Positive Output Source
 */
typedef enum {
    TIMER_CH_OUTP_SRC_0   = TIMER_CH_CNTRL1_SELO_ALW0, /*!< Selects the '0' state on the CHy line. */
    TIMER_CH_OUTP_SRC_1   = TIMER_CH_CNTRL1_SELO_ALW1, /*!< Selects the '1' state on the CHy line. */
    TIMER_CH_OUTP_SRC_REF = TIMER_CH_CNTRL1_SELO_REF,  /*!< Selects the REF state on the CHy line. */
    TIMER_CH_OUTP_SRC_DTG = TIMER_CH_CNTRL1_SELO_DTG   /*!< Selects the DTG output state on the CHy line. */
} TIMER_CH_OUTP_Source_TypeDef;

#define IS_TIMER_CHANNEL_OUTP_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_OUTP_SRC_0) ||   \
                                              ((SOURCE) == TIMER_CH_OUTP_SRC_1) ||   \
                                              ((SOURCE) == TIMER_CH_OUTP_SRC_REF) || \
                                              ((SOURCE) == TIMER_CH_OUTP_SRC_DTG))

/**
 * @brief TIMER Channel Positive Output Mode
 */
typedef enum {
    TIMER_CH_OUTP_MODE_IN        = TIMER_CH_CNTRL1_SELOE_ALW0, /*!< Selects the Input mode on the CHy line. */
    TIMER_CH_OUTP_MODE_OUT       = TIMER_CH_CNTRL1_SELOE_ALW1, /*!< Selects the Output mode on the CHy line. */
    TIMER_CH_OUTP_MODE_REF_AS_OE = TIMER_CH_CNTRL1_SELOE_REF,  /*!< The REF signal specifies the CHy line mode. */
    TIMER_CH_OUTP_MODE_DTG_AS_OE = TIMER_CH_CNTRL1_SELOE_DTG   /*!< The DTG output specifies the CHy line mode. */
} TIMER_CH_OUTP_Mode_TypeDef;

#define IS_TIMER_CHANNEL_OUTP_MODE(MODE) (((MODE) == TIMER_CH_OUTP_MODE_IN) ||        \
                                          ((MODE) == TIMER_CH_OUTP_MODE_OUT) ||       \
                                          ((MODE) == TIMER_CH_OUTP_MODE_REF_AS_OE) || \
                                          ((MODE) == TIMER_CH_OUTP_MODE_DTG_AS_OE))

/**
 * @brief TIMER Channel Negative Output Polarity
 */
typedef enum {
    TIMER_CH_OUTN_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_CH_CNTRL1_NINV_Pos), /*!< The channel negative output is not inverted. */
    TIMER_CH_OUTN_POLARITY_INV     = (((uint32_t)0x1) << TIMER_CH_CNTRL1_NINV_Pos)  /*!< The channel negative output is inverted. */
} TIMER_CH_OUTN_Polarity_TypeDef;

#define IS_TIMER_CHANNEL_OUTN_POLARITY(STATE) (((STATE) == TIMER_CH_OUTN_POLARITY_NON_INV) || \
                                               ((STATE) == TIMER_CH_OUTN_POLARITY_INV))

/**
 * @brief TIMER Channel Negative Output Source
 */
typedef enum {
    TIMER_CH_OUTN_SRC_0   = TIMER_CH_CNTRL1_NSELO_ALW0, /*!< Selects the '0' state on the nCHy line. */
    TIMER_CH_OUTN_SRC_1   = TIMER_CH_CNTRL1_NSELO_ALW1, /*!< Selects the '1' state on the nCHy line. */
    TIMER_CH_OUTN_SRC_REF = TIMER_CH_CNTRL1_NSELO_REF,  /*!< Selects the nREF state on the nCHy line. */
    TIMER_CH_OUTN_SRC_DTG = TIMER_CH_CNTRL1_NSELO_DTG   /*!< Selects the DTG output state on the nCHy line. */
} TIMER_CH_OUTN_Source_TypeDef;

#define IS_TIMER_CHANNEL_OUTN_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_OUTN_SRC_0) ||   \
                                              ((SOURCE) == TIMER_CH_OUTN_SRC_1) ||   \
                                              ((SOURCE) == TIMER_CH_OUTN_SRC_REF) || \
                                              ((SOURCE) == TIMER_CH_OUTN_SRC_DTG))

/**
 * @brief TIMER Channel Negative Output Mode
 */
typedef enum {
    TIMER_CH_OUTN_MODE_IN        = TIMER_CH_CNTRL1_NSELOE_ALW0, /*!< Selects the Input mode on the nCHy line. */
    TIMER_CH_OUTN_MODE_OUT       = TIMER_CH_CNTRL1_NSELOE_ALW1, /*!< Selects the Output mode on the nCHy line. */
    TIMER_CH_OUTN_MODE_REF_AS_OE = TIMER_CH_CNTRL1_NSELOE_REF,  /*!< The nREF signal specifies the nCHy line mode. */
    TIMER_CH_OUTN_MODE_DTG_AS_OE = TIMER_CH_CNTRL1_NSELOE_DTG   /*!< The DTG output specifies the nCHy line mode. */
} TIMER_CH_OUTN_Mode_TypeDef;

#define IS_TIMER_CHANNEL_OUTN_MODE(MODE) (((MODE) == TIMER_CH_OUTN_MODE_IN) ||        \
                                          ((MODE) == TIMER_CH_OUTN_MODE_OUT) ||       \
                                          ((MODE) == TIMER_CH_OUTN_MODE_REF_AS_OE) || \
                                          ((MODE) == TIMER_CH_OUTN_MODE_DTG_AS_OE))

/**
 * @brief TIMER Channel DTG Clock Source
 */
typedef enum {
    TIMER_CH_DTG_CLK_SRC_TIM_CLK = (((uint32_t)0x0) << TIMER_CH_DTG_EDTS_Pos), /*!< Specifies the TIM_CLK signal as DTG clock source. */
    TIMER_CH_DTG_CLK_SRC_FDTS    = (((uint32_t)0x1) << TIMER_CH_DTG_EDTS_Pos)  /*!< Specifies the FDTS signal as DTG clock source. */
} TIMER_CH_DTG_ClockSource_TypeDef;

#define IS_TIMER_CHANNEL_DTG_CLK_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_DTG_CLK_SRC_TIM_CLK) || \
                                                 ((SOURCE) == TIMER_CH_DTG_CLK_SRC_FDTS))

/**
 * @brief TIMER Flags
 */
typedef enum {
    TIMER_FLAG_CNT_ZERO     = TIMER_STATUS_CNT_ZERO_EVENT,     /*!< The (CNT == 0) condition occurred. */
    TIMER_FLAG_CNT_ARR      = TIMER_STATUS_CNT_ARR_EVENT,      /*!< The (CNT == ARR) condition occurred. */
    TIMER_FLAG_ETR_RE       = TIMER_STATUS_ETR_RE_EVENT,       /*!< The ETR rising edge occurred. */
    TIMER_FLAG_ETR_FE       = TIMER_STATUS_ETR_FE_EVENT,       /*!< The ETR falling edge occurred. */
    TIMER_FLAG_BRK          = TIMER_STATUS_BRK_EVENT,          /*!< The (BRK == 1) condition occurred. */
    TIMER_FLAG_CH1_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVENT_CH1,  /*!< The Channel 1 CCR capture condition occurred. */
    TIMER_FLAG_CH1_PWM_REF  = TIMER_STATUS_CCR_REF_EVENT_CH1,  /*!< The Channel 1 (REF == 1) condition occurred. */
    TIMER_FLAG_CH1_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVENT_CH1, /*!< The Channel 1 CCR1 capture condition occurred. */
#if defined(USE_MDR32F21QI)
    TIMER_FLAG_CH2_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVENT_CH2,  /*!< The Channel 2 CCR capture condition occurred. */
    TIMER_FLAG_CH3_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVENT_CH3,  /*!< The Channel 3 CCR capture condition occurred. */
    TIMER_FLAG_CH4_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVENT_CH4,  /*!< The Channel 4 CCR capture condition occurred. */
    TIMER_FLAG_CH2_PWM_REF  = TIMER_STATUS_CCR_REF_EVENT_CH2,  /*!< The Channel 2 (REF == 1) condition occurred. */
    TIMER_FLAG_CH3_PWM_REF  = TIMER_STATUS_CCR_REF_EVENT_CH3,  /*!< The Channel 3 (REF == 1) condition occurred. */
    TIMER_FLAG_CH4_PWM_REF  = TIMER_STATUS_CCR_REF_EVENT_CH4,  /*!< The Channel 4 (REF == 1) condition occurred. */
    TIMER_FLAG_CH2_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVENT_CH2, /*!< The Channel 2 CCR1 capture condition occurred. */
    TIMER_FLAG_CH3_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVENT_CH3, /*!< The Channel 3 CCR1 capture condition occurred. */
    TIMER_FLAG_CH4_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVENT_CH4  /*!< The Channel 4 CCR1 capture condition occurred. */
#endif
} TIMER_Flags_TypeDef;

#if defined(USE_MDR32F21QI)
#define TIMER_FLAG_MASK (TIMER_FLAG_CNT_ZERO |     \
                         TIMER_FLAG_CNT_ARR |      \
                         TIMER_FLAG_ETR_RE |       \
                         TIMER_FLAG_ETR_FE |       \
                         TIMER_FLAG_BRK |          \
                         TIMER_FLAG_CH1_CAP_CCR |  \
                         TIMER_FLAG_CH2_CAP_CCR |  \
                         TIMER_FLAG_CH3_CAP_CCR |  \
                         TIMER_FLAG_CH4_CAP_CCR |  \
                         TIMER_FLAG_CH1_PWM_REF |  \
                         TIMER_FLAG_CH2_PWM_REF |  \
                         TIMER_FLAG_CH3_PWM_REF |  \
                         TIMER_FLAG_CH4_PWM_REF |  \
                         TIMER_FLAG_CH1_CAP_CCR1 | \
                         TIMER_FLAG_CH2_CAP_CCR1 | \
                         TIMER_FLAG_CH3_CAP_CCR1 | \
                         TIMER_FLAG_CH4_CAP_CCR1)

#define IS_TIMER_FLAG(FLAG) (((FLAG) == TIMER_FLAG_CNT_ZERO) ||     \
                             ((FLAG) == TIMER_FLAG_CNT_ARR) ||      \
                             ((FLAG) == TIMER_FLAG_ETR_RE) ||       \
                             ((FLAG) == TIMER_FLAG_ETR_FE) ||       \
                             ((FLAG) == TIMER_FLAG_BRK) ||          \
                             ((FLAG) == TIMER_FLAG_CH1_CAP_CCR) ||  \
                             ((FLAG) == TIMER_FLAG_CH2_CAP_CCR) ||  \
                             ((FLAG) == TIMER_FLAG_CH3_CAP_CCR) ||  \
                             ((FLAG) == TIMER_FLAG_CH4_CAP_CCR) ||  \
                             ((FLAG) == TIMER_FLAG_CH1_PWM_REF) ||  \
                             ((FLAG) == TIMER_FLAG_CH2_PWM_REF) ||  \
                             ((FLAG) == TIMER_FLAG_CH3_PWM_REF) ||  \
                             ((FLAG) == TIMER_FLAG_CH4_PWM_REF) ||  \
                             ((FLAG) == TIMER_FLAG_CH1_CAP_CCR1) || \
                             ((FLAG) == TIMER_FLAG_CH2_CAP_CCR1) || \
                             ((FLAG) == TIMER_FLAG_CH3_CAP_CCR1) || \
                             ((FLAG) == TIMER_FLAG_CH4_CAP_CCR1))
#elif defined(USE_MDR32F23QI)
#define TIMER_FLAG_MASK (TIMER_FLAG_CNT_ZERO |    \
                         TIMER_FLAG_CNT_ARR |     \
                         TIMER_FLAG_ETR_RE |      \
                         TIMER_FLAG_ETR_FE |      \
                         TIMER_FLAG_BRK |         \
                         TIMER_FLAG_CH1_CAP_CCR | \
                         TIMER_FLAG_CH1_PWM_REF | \
                         TIMER_FLAG_CH1_CAP_CCR1)

#define IS_TIMER_FLAG(FLAG) (((FLAG) == TIMER_FLAG_CNT_ZERO) ||    \
                             ((FLAG) == TIMER_FLAG_CNT_ARR) ||     \
                             ((FLAG) == TIMER_FLAG_ETR_RE) ||      \
                             ((FLAG) == TIMER_FLAG_ETR_FE) ||      \
                             ((FLAG) == TIMER_FLAG_BRK) ||         \
                             ((FLAG) == TIMER_FLAG_CH1_CAP_CCR) || \
                             ((FLAG) == TIMER_FLAG_CH1_PWM_REF) || \
                             ((FLAG) == TIMER_FLAG_CH1_CAP_CCR1))
#endif
#define IS_TIMER_FLAGS(FLAGS) (((FLAGS) & ~((uint32_t)TIMER_FLAG_MASK)) == 0)

/**
 * @brief TIMER Counter Init structure definition
 */
typedef struct
{
    uint16_t TIMER_CounterValue;                            /*!< Specifies the initial counter value.
                                                                 This parameter can be a number between 0x0000 and 0xFFFF. */
    uint16_t TIMER_CounterPrescaler;                        /*!< Specifies the prescaler value used to divide the TIM_CLK.
                                                                 This parameter can be a number between 0x0000 and 0xFFFF.
                                                                 CLK = TIM_CLK/(TIMER_CounterPrescaler + 1) */
    uint16_t TIMER_CounterPeriod;                           /*!< Specifies the value to be loaded into the Auto-Reload Register (ARR)
                                                                 at the next update event (full period = ARR (TIMER_CounterPeriod) + 1).
                                                                 This parameter must be a number between 0x0000 and 0xFFFF.  */
    TIMER_CNT_EventSource_TypeDef TIMER_CounterEventSource; /*!< Specifies the Counter Event source.
                                                                 This parameter can be a value of @ref TIMER_CNT_EventSource_TypeDef */
    TIMER_CNT_Mode_TypeDef TIMER_CounterMode;               /*!< Specifies the counter mode.
                                                                 This parameter can be a value of @ref TIMER_CNT_Mode_TypeDef
                                                                 Note: TIMER_CounterMode use with TIMER_CounterEventSource!
                                                                       If TIMER_CounterEventSource != TIMER_EVNT_SRC_TIM_CLK, then TIMER_CounterMode = TIMER_CNT_MODE_EVNT_FIXED_DIR */
    TIMER_CNT_Dir_TypeDef TIMER_CounterDirection;           /*!< Specifies the counter direction.
                                                                 This parameter can be a value of @ref TIMER_CNT_Dir_TypeDef */
    TIMER_FDTS_Prescaler_TypeDef TIMER_FDTS_Prescaler;      /*!< Specifies the FDTS Prescaler configuration.
                                                                 This parameter can be a value of @ref TIMER_FDTS_Prescaler_TypeDef */
    TIMER_ARR_UpdateMode_TypeDef TIMER_ARR_UpdateMode;      /*!< Specifies the Auto-Reload Register (ARR) updating mode.
                                                                 This parameter can be a value of @ref TIMER_ARR_UpdateMode_TypeDef */
    TIMER_ETR_Filter_TypeDef TIMER_ETR_Filter;              /*!< Specifies the ETR Filter configuration.
                                                                 This parameter can be a value of @ref TIMER_ETR_Filter_TypeDef */
    TIMER_ETR_Prescaler_TypeDef TIMER_ETR_Prescaler;        /*!< Specifies the ETR Prescaler configuration.
                                                                 This parameter can be a value of @ref TIMER_ETR_Prescaler_TypeDef */
    TIMER_ETR_Polarity_TypeDef TIMER_ETR_Polarity;          /*!< Specifies the ETR Polarity configuration.
                                                                 This parameter can be a value of @ref TIMER_ETR_Polarity_TypeDef */
    TIMER_BRK_Polarity_TypeDef TIMER_BRK_Polarity;          /*!< Specifies the BRK Polarity configuration.
                                                                 This parameter can be a value of @ref TIMER_BRK_Polarity_TypeDef */
} TIMER_CNT_InitTypeDef;

/**
 * @brief TIMER Channel Init structure definition
 */
typedef struct
{
    TIMER_CH_Number_TypeDef TIMER_CH_Number;                             /*!< Specifies the TIMER Channel number to be configured.
                                                                              This parameter can be a value of @ref TIMER_CH_Number_TypeDef */
    TIMER_CH_Mode_TypeDef TIMER_CH_Mode;                                 /*!< Specifies the TIMER Channel mode.
                                                                              This parameter can be a value of @ref TIMER_CH_Mode_TypeDef */
    FunctionalState TIMER_CH_CCR1_Cmd;                                   /*!< Enables or disables the CCR1 register.
                                                                              This parameter can be a value of @ref FunctionalState */
    TIMER_CH_PWM_REF_Format_TypeDef TIMER_CH_PWM_REF_Format;             /*!< Specifies the REF signal format in PWM mode.
                                                                              This parameter can be a value of @ref TIMER_CH_PWM_REF_Format_TypeDef */
    TIMER_CH_PWM_CCR_UpdateMode_TypeDef TIMER_CH_PWM_CCR_UpdateMode;     /*!< Specifies the TIMER CCR, CCR1 update mode in PWM mode.
                                                                              This parameter can be a value of @ref TIMER_CH_PWM_CCR_UpdateMode_TypeDef */
    FunctionalState TIMER_CH_PWM_ETR_Reset;                              /*!< Enables or disables REF reset by ETR (active high) in PWM mode.
                                                                              This parameter can be a value of @ref FunctionalState */
    FunctionalState TIMER_CH_PWM_BRK_Reset;                              /*!< Enables or disables REF and DTG reset by BRK (active low) in PWM mode.
                                                                              This parameter can be a value of @ref FunctionalState */
    TIMER_CH_CAP_CCR_EventSource_TypeDef TIMER_CH_CAP_CCR_EventSource;   /*!< Specifies the Channel CCR Event source in capture mode.
                                                                              This parameter can be a value of @ref TIMER_CH_CAP_CCR_EventSource_TypeDef */
    TIMER_CH_CAP_CCR1_EventSource_TypeDef TIMER_CH_CAP_CCR1_EventSource; /*!< Specifies the Channel CCR1 Event source in capture mode.
                                                                              This parameter can be a value of @ref TIMER_CH_CAP_CCR1_EventSource_TypeDef */
    TIMER_CH_CAP_EventPrescaler_TypeDef TIMER_CH_CAP_EventPrescaler;     /*!< Specifies the TIMER Channel Events Prescaler configuration in capture mode.
                                                                              This parameter can be a value of @ref TIMER_CH_CAP_EventPrescaler_TypeDef */
#if defined(USE_MDR32F23QI)
    FunctionalState TIMER_CH_CAP_EventDelay;                             /*!< Enables or disables synchronization between the capture event and the update of registers CCR and CCR1.
                                                                              This parameter can be a value of @ref FunctionalState */
#endif
    TIMER_CH_Filter_TypeDef TIMER_CH_Filter;                             /*!< Specifies the TIMER Channel Filter configuration.
                                                                              This parameter can be a value of @ref TIMER_CH_Filter_TypeDef */
} TIMER_CH_InitTypeDef;

/**
 * @brief TIMER Channel Output Init structure definition
 */
typedef struct
{
    TIMER_CH_Number_TypeDef TIMER_CH_Number;                   /*!< Specifies the TIMER Channel number to be configured.
                                                                    This parameter can be a value of @ref TIMER_CH_Number_TypeDef */
    TIMER_CH_OUTP_Polarity_TypeDef TIMER_CH_OUTP_Polarity;     /*!< Specifies the TIMER CHy output polarity.
                                                                    This parameter can be a value of @ref TIMER_CH_OUTP_Polarity_TypeDef */
    TIMER_CH_OUTP_Source_TypeDef TIMER_CH_OUTP_Source;         /*!< Specifies the TIMER CHy output source.
                                                                    This parameter can be a value of @ref TIMER_CH_OUTP_Source_TypeDef */
    TIMER_CH_OUTP_Mode_TypeDef TIMER_CH_OUTP_Mode;             /*!< Specifies the TIMER CHy output enable source.
                                                                    This parameter can be a value of @ref TIMER_CH_OUTP_Mode_TypeDef */
    TIMER_CH_OUTN_Polarity_TypeDef TIMER_CH_OUTN_Polarity;     /*!< Enables or disables the TIMER nCHy output inversion.
                                                                    This parameter can be a value of @ref TIMER_CH_OUTN_Polarity_TypeDef */
    TIMER_CH_OUTN_Source_TypeDef TIMER_CH_OUTN_Source;         /*!< Specifies the TIMER nCHy output source.
                                                                    This parameter can be a value of @ref TIMER_CH_OUTN_Source_TypeDef */
    TIMER_CH_OUTN_Mode_TypeDef TIMER_CH_OUTN_Mode;             /*!< Specifies the TIMER nCHy output enable source.
                                                                    This parameter can be a value of @ref TIMER_CH_OUTN_Mode_TypeDef */
    TIMER_CH_DTG_ClockSource_TypeDef TIMER_CH_DTG_ClockSource; /*!< Specifies the TIMER DTG clock source.
                                                                    This parameter can be a value of @ref TIMER_CH_DTG_ClockSource_TypeDef */
    uint8_t TIMER_CH_DTG_MainPrescaler;                        /*!< Specifies the main prescaler of TIMER DTG.
                                                                    This parameter can be a number between 0x00 and 0xFF.
                                                                    Delay DTGdel = TIMER_CH_DTG_MainPrescaler*(TIMER_CH_DTG_AuxPrescaler + 1) clocks. */
    uint8_t TIMER_CH_DTG_AuxPrescaler;                         /*!< Specifies the auxiliary prescaler of TIMER DTG.
                                                                    This parameter can be a number between 0x00 and 0x0F.
                                                                    Delay DTGdel = TIMER_CH_DTG_MainPrescaler*(TIMER_CH_DTG_AuxPrescaler + 1) clocks. */
} TIMER_CH_OUT_InitTypeDef;

/** @} */ /* End of group TIMER_Exported_Types */

/** @defgroup TIMER_Exported_Defines TIMER Exported Defines
 * @{
 */

/** @defgroup TIMER_CH_DTG_Prescaler TIMER Channel DTG Prescaler
 * @{
 */

#define IS_TIMER_CHANNEL_DTG_AUX_PRESCALER(VALUE) (((VALUE) & ~TIMER_CH_DTG_DTGX_Msk) == 0)

/** @} */ /* End of group TIMER_CH_DTG_Prescaler */

/** @} */ /* End of group TIMER_Exported_Defines */

/** @addtogroup TIMER_Exported_Functions TIMER Exported Functions
 * @{
 */

void TIMER_DeInit(MDR_TIMER_TypeDef* TIMERx);

void TIMER_CNT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CNT_InitTypeDef* TIMER_CntInitStruct);
void TIMER_CNT_StructInit(TIMER_CNT_InitTypeDef* TIMER_CntInitStruct);
void TIMER_CNT_Cmd(MDR_TIMER_TypeDef* TIMERx, FunctionalState NewState);

void     TIMER_CNT_SetCounter(MDR_TIMER_TypeDef* TIMERx, uint16_t Counter);
uint16_t TIMER_CNT_GetCounter(MDR_TIMER_TypeDef* TIMERx);

void     TIMER_CNT_SetPrescaler(MDR_TIMER_TypeDef* TIMERx, uint16_t Prescaler);
uint16_t TIMER_CNT_GetPrescaler(MDR_TIMER_TypeDef* TIMERx);

void     TIMER_CNT_SetAutoreloadUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_ARR_UpdateMode_TypeDef UpdateMode);
void     TIMER_CNT_SetAutoreload(MDR_TIMER_TypeDef* TIMERx, uint16_t Autoreload);
uint16_t TIMER_CNT_GetAutoreload(MDR_TIMER_TypeDef* TIMERx);

void                  TIMER_CNT_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_EventSource_TypeDef CounterEventSource);
void                  TIMER_CNT_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_Mode_TypeDef Mode);
void                  TIMER_CNT_SetDirection(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_Dir_TypeDef Direction);
TIMER_CNT_Dir_TypeDef TIMER_CNT_GetDirection(MDR_TIMER_TypeDef* TIMERx);
FlagStatus            TIMER_CNT_GetWriteStatus(MDR_TIMER_TypeDef* TIMERx);

void TIMER_FDTS_SetPrescaler(MDR_TIMER_TypeDef* TIMERx, TIMER_FDTS_Prescaler_TypeDef Prescaler);

void TIMER_ETR_InputConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler, TIMER_ETR_Polarity_TypeDef Polarity, TIMER_ETR_Filter_TypeDef Filter);
void TIMER_ETR_FilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Filter_TypeDef Filter);
void TIMER_ETR_PrescalerConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler);
void TIMER_ETR_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Polarity_TypeDef Polarity);
void TIMER_BRK_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_BRK_Polarity_TypeDef Polarity);

void TIMER_CH_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_InitTypeDef* TIMER_ChInitStruct);
void TIMER_CH_StructInit(TIMER_CH_InitTypeDef* TIMER_ChInitStruct);

void       TIMER_CH_SetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint16_t CCR);
uint16_t   TIMER_CH_GetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);
FlagStatus TIMER_CH_GetCCRWriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);

void       TIMER_CH_CCR1Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);
void       TIMER_CH_SetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint16_t CCR1);
uint16_t   TIMER_CH_GetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);
FlagStatus TIMER_CH_GetCCR1WriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);

void TIMER_CH_PWM_SetCompareUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_CCR_UpdateMode_TypeDef UpdateMode);
/**
 * @brief  Sets the TIMERx Channel Capture Compare Register (CCR) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Compare: specifies the Capture Compare Register (CCR) new value.
 * @retval None.
 */
#define TIMER_CH_PWM_SetCompare(TIMERx, Channel, Compare) TIMER_CH_SetCCR(TIMERx, Channel, Compare)

/**
 * @brief  Sets the TIMERx Channel Capture Compare Register 1 (CCR1) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @param  Compare1: specifies the Capture Compare Register 1 (CCR1) new value.
 * @retval None.
 */
#define TIMER_CH_PWM_SetCompare1(TIMERx, Channel, Compare1) TIMER_CH_SetCCR1(TIMERx, Channel, Compare1)

void TIMER_CH_PWM_REF_FormatConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_REF_Format_TypeDef Format);
void TIMER_CH_PWM_ETR_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);
void TIMER_CH_PWM_BRK_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);

/**
 * @brief  Returns the TIMERx Channel Capture Compare Register (CCR) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @retval Channel Capture Compare Register (CCR) value.
 */
#define TIMER_CH_CAP_GetCapture(TIMERx, Channel) TIMER_CH_GetCCR(TIMERx, Channel)

/**
 * @brief  Returns the TIMERx Channel Capture Compare Register 1 (CCR1) value.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  Channel - @ref TIMER_CH_Number_TypeDef - specifies the Timer Channel number.
 * @retval Channel Capture Compare Register 1 (CCR1) value.
 */
#define TIMER_CH_CAP_GetCapture1(TIMERx, Channel) TIMER_CH_GetCCR1(TIMERx, Channel)

void TIMER_CH_CAP_SetEventPrescaler(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_EventPrescaler_TypeDef Prescaler);
void TIMER_CH_CAP_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR_EventSource_TypeDef EventSource);
void TIMER_CH_CAP_Event1SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR1_EventSource_TypeDef Event1Source);
#if (defined USE_MDR32F23QI)
void TIMER_CH_CAP_EventDelayCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);
#endif
void TIMER_CH_FilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_Filter_TypeDef Filter);

void TIMER_CH_OUT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_OUT_InitTypeDef* TIMER_ChOutInitStruct);
void TIMER_CH_OUT_StructInit(TIMER_CH_OUT_InitTypeDef* TIMER_ChOutInitStruct);

void TIMER_CH_OUT_DTGConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint8_t MainPrescaler, uint8_t AuxPrescaler, TIMER_CH_DTG_ClockSource_TypeDef ClockSource);

void TIMER_CH_OUTP_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Source_TypeDef OutSource, TIMER_CH_OUTP_Mode_TypeDef Mode, TIMER_CH_OUTP_Polarity_TypeDef Polarity);
void TIMER_CH_OUTP_SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Source_TypeDef OutSource);
void TIMER_CH_OUTP_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Mode_TypeDef Mode);
void TIMER_CH_OUTP_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTP_Polarity_TypeDef Polarity);

void TIMER_CH_OUTN_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Source_TypeDef OutSource, TIMER_CH_OUTN_Mode_TypeDef Mode, TIMER_CH_OUTN_Polarity_TypeDef Polarity);
void TIMER_CH_OUTN_SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Source_TypeDef OutSource);
void TIMER_CH_OUTN_ModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Mode_TypeDef Mode);
void TIMER_CH_OUTN_PolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_OUTN_Polarity_TypeDef Polarity);

FlagStatus TIMER_GetFlagStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Flags_TypeDef Flag);
uint32_t   TIMER_GetStatus(MDR_TIMER_TypeDef* TIMERx);
void       TIMER_ClearFlags(MDR_TIMER_TypeDef* TIMERx, uint32_t Flags);

void     TIMER_ITConfig(MDR_TIMER_TypeDef* TIMERx, uint32_t ITs, FunctionalState NewState);
ITStatus TIMER_GetITFlagStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Flags_TypeDef IT);
uint32_t TIMER_GetITStatus(MDR_TIMER_TypeDef* TIMERx);

/**
 * @brief  Clears TIMERx interrupt requests.
 * @param  TIMERx: select the TIMER peripheral.
 *         This parameter can be one of the following values: MDR_TIMER0, MDR_TIMER1.
 * @param  ITs: specifies the TIMERx interrupt requests to clear.
 *         This parameter can be any combination of @ref TIMER_Flags_TypeDef values.
 * @retval None.
 */
#define TIMER_ClearITFlags(TIMERx, ITs) TIMER_ClearFlags(TIMERx, ITs)

#if defined(USE_MDR32F21QI)
void TIMER_DMACmd(MDR_TIMER_TypeDef* TIMERx, uint32_t DMAReqs, FunctionalState NewState);
#endif

/** @} */ /* End of group TIMER_Exported_Functions */

/** @} */ /* End of group TIMER */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR32F2xQI_TIMER_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_timer.h */

