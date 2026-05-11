/**
 *******************************************************************************
 * @file    MDR32VF0xI_timer.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    28/04/2024
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
#ifndef MDR32VF0xI_TIMER_H
#define MDR32VF0xI_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup TIMER TIMER
 * @{
 */

/** @defgroup TIMER_Exported_Types TIMER Exported Types
 * @{
 */

/**
 * @brief TIMER counter event source.
 */
typedef enum {
    TIMER_CNT_EVNT_SRC_TIM_CLK = TIMER_CNTRL_EVNT_SEL_TIM_CLK, /*!< Select a rising edge event TIM_CLKd = TIM_CLK/(PSG + 1). */
    TIMER_CNT_EVNT_SRC_TMR1    = TIMER_CNTRL_EVNT_SEL_TMR1,    /*!< Select TIMER1 (CNT == ARR) event. */
    TIMER_CNT_EVNT_SRC_TMR2    = TIMER_CNTRL_EVNT_SEL_TMR2,    /*!< Select TIMER2 (CNT == ARR) event. */
    TIMER_CNT_EVNT_SRC_TMR3    = TIMER_CNTRL_EVNT_SEL_TMR3,    /*!< Select TIMER3 (CNT == ARR) event. */
    TIMER_CNT_EVNT_SRC_CH1_RE  = TIMER_CNTRL_EVNT_SEL_CH1_RE,  /*!< Select a rising edge event on channel 1. */
    TIMER_CNT_EVNT_SRC_CH2_RE  = TIMER_CNTRL_EVNT_SEL_CH2_RE,  /*!< Select a rising edge event on channel 2. */
    TIMER_CNT_EVNT_SRC_CH3_RE  = TIMER_CNTRL_EVNT_SEL_CH3_RE,  /*!< Select a rising edge event on channel 3. */
    TIMER_CNT_EVNT_SRC_CH4_RE  = TIMER_CNTRL_EVNT_SEL_CH4_RE,  /*!< Select a rising edge event on channel 4. */
    TIMER_CNT_EVNT_SRC_ETR_RE  = TIMER_CNTRL_EVNT_SEL_ETR_RE,  /*!< Select a rising edge event on ETR. */
    TIMER_CNT_EVNT_SRC_ETR_FE  = TIMER_CNTRL_EVNT_SEL_ETR_FE,  /*!< Select a falling edge event on ETR. */
    TIMER_CNT_EVNT_SRC_TMR4    = TIMER_CNTRL_EVNT_SEL_TMR4     /*!< Select TIMER4 (CNT == ARR) event. */
} TIMER_CNT_EventSource_TypeDef;

#define IS_TIMER_CNT_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CNT_EVNT_SRC_TIM_CLK) || \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_TMR1) ||    \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_TMR2) ||    \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_TMR3) ||    \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_CH1_RE) ||  \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_CH2_RE) ||  \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_CH3_RE) ||  \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_CH4_RE) ||  \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_ETR_RE) ||  \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_ETR_FE) ||  \
                                           ((SOURCE) == TIMER_CNT_EVNT_SRC_TMR4))

/**
 * @brief TIMER counter mode.
 */
typedef enum {
    TIMER_CNT_MODE_CLK_FIXED_DIR  = TIMER_CNTRL_CNT_MODE_CLK_FIXED_DIR,  /*!< The value of CNT changes on rising edge of TIM_CLKd. The direction of the count remains constant. */
    TIMER_CNT_MODE_CLK_CHANGE_DIR = TIMER_CNTRL_CNT_MODE_CLK_CHANGE_DIR, /*!< The value of CNT changes on rising edge of TIM_CLKd. The direction of the count changes. */
    TIMER_CNT_MODE_EVNT_FIXED_DIR = TIMER_CNTRL_CNT_MODE_EVNT_FIXED_DIR  /*!< The value of CNT changes on the specified event. The direction of the count remains constant. */
} TIMER_CNT_Mode_TypeDef;

#define IS_TIMER_CNT_MODE(MODE) (((MODE) == TIMER_CNT_MODE_CLK_FIXED_DIR) ||  \
                                 ((MODE) == TIMER_CNT_MODE_CLK_CHANGE_DIR) || \
                                 ((MODE) == TIMER_CNT_MODE_EVNT_FIXED_DIR))

/**
 * @brief TIMER counter direction.
 */
typedef enum {
    TIMER_CNT_DIR_UP   = (((uint32_t)0x0) << TIMER_CNTRL_DIR_Pos), /*!< Increment the TIMER CNT value. */
    TIMER_CNT_DIR_DOWN = (((uint32_t)0x1) << TIMER_CNTRL_DIR_Pos)  /*!< Decrement the TIMER CNT value. */
} TIMER_CNT_Dir_TypeDef;

#define IS_TIMER_CNT_DIR(DIR) (((DIR) == TIMER_CNT_DIR_UP) || \
                               ((DIR) == TIMER_CNT_DIR_DOWN))

/**
 * @brief TIMER period update mode.
 */
typedef enum {
    TIMER_CNT_PERIOD_UPD_IMMEDIATELY   = (((uint32_t)0x0) << TIMER_CNTRL_ARRB_EN_Pos), /*!< The CNT period (ARR register) is updated immediately. */
    TIMER_CNT_PERIOD_UPD_ON_CNT_EQ_ARR = (((uint32_t)0x1) << TIMER_CNTRL_ARRB_EN_Pos)  /*!< The CNT period (ARR register) is updated at (CNT == ARR) condition. */
} TIMER_CNT_PeriodUpdateMode_TypeDef;

#define IS_TIMER_CNT_PERIOD_UPDATE_MODE(MODE) (((MODE) == TIMER_CNT_PERIOD_UPD_IMMEDIATELY) || \
                                               ((MODE) == TIMER_CNT_PERIOD_UPD_ON_CNT_EQ_ARR))

/**
 * @brief TIMER FDTS prescaler.
 */
typedef enum {
    TIMER_FDTS_PRESCALER_DIV_1 = TIMER_CNTRL_FDTS_DIV_1, /*!< Clock signal FDTS = TIM_CLK. */
    TIMER_FDTS_PRESCALER_DIV_2 = TIMER_CNTRL_FDTS_DIV_2, /*!< Clock signal FDTS = TIM_CLK/2. */
    TIMER_FDTS_PRESCALER_DIV_3 = TIMER_CNTRL_FDTS_DIV_3, /*!< Clock signal FDTS = TIM_CLK/3. */
    TIMER_FDTS_PRESCALER_DIV_4 = TIMER_CNTRL_FDTS_DIV_4  /*!< Clock signal FDTS = TIM_CLK/4. */
} TIMER_FDTS_Prescaler_TypeDef;

#define IS_TIMER_FDTS_PRESCALER(VALUE) (((VALUE) == TIMER_FDTS_PRESCALER_DIV_1) || \
                                        ((VALUE) == TIMER_FDTS_PRESCALER_DIV_2) || \
                                        ((VALUE) == TIMER_FDTS_PRESCALER_DIV_3) || \
                                        ((VALUE) == TIMER_FDTS_PRESCALER_DIV_4))

/**
 * @brief TIMER ETR filter configuration.
 */
typedef enum {
    TIMER_ETR_FILTER_1FF_AT_FDTS        = TIMER_BRKETR_CNTRL_ETR_FLTR_1_FDTS,        /*!< Signal is latched by 1 trigger at FDTS frequency. */
    TIMER_ETR_FILTER_2FF_AT_TIM_CLK     = TIMER_BRKETR_CNTRL_ETR_FLTR_2_TIM_CLK,     /*!< Signal is latched by 2 triggers at TIM_CLK frequency (2xT_TIM_CLK). */
    TIMER_ETR_FILTER_4FF_AT_TIM_CLK     = TIMER_BRKETR_CNTRL_ETR_FLTR_4_TIM_CLK,     /*!< Signal is latched by 4 triggers at TIM_CLK frequency (4xT_TIM_CLK). */
    TIMER_ETR_FILTER_8FF_AT_TIM_CLK     = TIMER_BRKETR_CNTRL_ETR_FLTR_8_TIM_CLK,     /*!< Signal is latched by 8 triggers at TIM_CLK frequency (8xT_TIM_CLK). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_2  = TIMER_BRKETR_CNTRL_ETR_FLTR_6_FDTS_DIV_2,  /*!< Signal is latched by 6 triggers at FDTS/2  frequency (12xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_2  = TIMER_BRKETR_CNTRL_ETR_FLTR_8_FDTS_DIV_2,  /*!< Signal is latched by 8 triggers at FDTS/2  frequency (16xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_4  = TIMER_BRKETR_CNTRL_ETR_FLTR_6_FDTS_DIV_4,  /*!< Signal is latched by 6 triggers at FDTS/4  frequency (24xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_4  = TIMER_BRKETR_CNTRL_ETR_FLTR_8_FDTS_DIV_4,  /*!< Signal is latched by 8 triggers at FDTS/4  frequency (32xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_8  = TIMER_BRKETR_CNTRL_ETR_FLTR_6_FDTS_DIV_8,  /*!< Signal is latched by 6 triggers at FDTS/8  frequency (48xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_8  = TIMER_BRKETR_CNTRL_ETR_FLTR_8_FDTS_DIV_8,  /*!< Signal is latched by 8 triggers at FDTS/8  frequency (64xT_FDTS). */
    TIMER_ETR_FILTER_5FF_AT_FDTS_DIV_16 = TIMER_BRKETR_CNTRL_ETR_FLTR_5_FDTS_DIV_16, /*!< Signal is latched by 5 triggers at FDTS/16 frequency (80xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_16 = TIMER_BRKETR_CNTRL_ETR_FLTR_6_FDTS_DIV_16, /*!< Signal is latched by 6 triggers at FDTS/16 frequency (96xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_16 = TIMER_BRKETR_CNTRL_ETR_FLTR_8_FDTS_DIV_16, /*!< Signal is latched by 8 triggers at FDTS/16 frequency (128xT_FDTS). */
    TIMER_ETR_FILTER_5FF_AT_FDTS_DIV_32 = TIMER_BRKETR_CNTRL_ETR_FLTR_5_FDTS_DIV_32, /*!< Signal is latched by 5 triggers at FDTS/32 frequency (160xT_FDTS). */
    TIMER_ETR_FILTER_6FF_AT_FDTS_DIV_32 = TIMER_BRKETR_CNTRL_ETR_FLTR_6_FDTS_DIV_32, /*!< Signal is latched by 6 triggers at FDTS/32 frequency (192xT_FDTS). */
    TIMER_ETR_FILTER_8FF_AT_FDTS_DIV_32 = TIMER_BRKETR_CNTRL_ETR_FLTR_8_FDTS_DIV_32  /*!< Signal is latched by 8 triggers at FDTS/32 frequency (256xT_FDTS). */
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
 * @brief TIMER ETR prescaler.
 */
typedef enum {
    TIMER_ETR_PRESCALER_DIV_1 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_1, /*!< Select input frequency divider by 1. */
    TIMER_ETR_PRESCALER_DIV_2 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_2, /*!< Select input frequency divider by 2. */
    TIMER_ETR_PRESCALER_DIV_4 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_4, /*!< Select input frequency divider by 4. */
    TIMER_ETR_PRESCALER_DIV_8 = TIMER_BRKETR_CNTRL_ETR_PSC_DIV_8  /*!< Select input frequency divider by 8. */
} TIMER_ETR_Prescaler_TypeDef;

#define IS_TIMER_ETR_PRESCALER(VALUE) (((VALUE) == TIMER_ETR_PRESCALER_DIV_1) || \
                                       ((VALUE) == TIMER_ETR_PRESCALER_DIV_2) || \
                                       ((VALUE) == TIMER_ETR_PRESCALER_DIV_4) || \
                                       ((VALUE) == TIMER_ETR_PRESCALER_DIV_8))

/**
 * @brief TIMER ETR polarity configuration.
 */
typedef enum {
    TIMER_ETR_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_BRKETR_CNTRL_ETR_INV_Pos), /*!< ETR input is not inverted. */
    TIMER_ETR_POLARITY_INV     = (((uint32_t)0x1) << TIMER_BRKETR_CNTRL_ETR_INV_Pos)  /*!< ETR input is inverted. */
} TIMER_ETR_Polarity_TypeDef;

#define IS_TIMER_ETR_POLARITY(STATE) (((STATE) == TIMER_ETR_POLARITY_NON_INV) || \
                                      ((STATE) == TIMER_ETR_POLARITY_INV))

/**
 * @brief TIMER BRK polarity configuration.
 */
typedef enum {
    TIMER_BRK_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_BRKETR_CNTRL_BRK_INV_Pos), /*!< BRK input is not inverted. */
    TIMER_BRK_POLARITY_INV     = (((uint32_t)0x1) << TIMER_BRKETR_CNTRL_BRK_INV_Pos)  /*!< BRK input is inverted. */
} TIMER_BRK_Polarity_TypeDef;

#define IS_TIMER_BRK_POLARITY(STATE) (((STATE) == TIMER_BRK_POLARITY_NON_INV) || \
                                      ((STATE) == TIMER_BRK_POLARITY_INV))

/**
 * @brief TIMER channel number.
 */
typedef enum {
    TIMER_CH1 = ((uint32_t)0x0), /*!< Specify the TIMER channel 1. */
    TIMER_CH2 = ((uint32_t)0x1), /*!< Specify the TIMER channel 2. */
    TIMER_CH3 = ((uint32_t)0x2), /*!< Specify the TIMER channel 3. */
    TIMER_CH4 = ((uint32_t)0x3)  /*!< Specify the TIMER channel 4. */
} TIMER_CH_Number_TypeDef;

#define IS_TIMER_CH_NUMBER(NUMBER) (((NUMBER) == TIMER_CH1) || \
                                    ((NUMBER) == TIMER_CH2) || \
                                    ((NUMBER) == TIMER_CH3) || \
                                    ((NUMBER) == TIMER_CH4))

/**
 * @brief TIMER channel mode.
 */
typedef enum {
    TIMER_CH_MODE_PWM     = (((uint32_t)0x0) << TIMER_CH_CNTRL0_CAP_NPWM_Pos), /*!< Specify the PWM channel mode. */
    TIMER_CH_MODE_CAPTURE = (((uint32_t)0x1) << TIMER_CH_CNTRL0_CAP_NPWM_Pos)  /*!< Specify the capture channel mode. */
} TIMER_CH_Mode_TypeDef;

#define IS_TIMER_CH_MODE(MODE) (((MODE) == TIMER_CH_MODE_PWM) || \
                                ((MODE) == TIMER_CH_MODE_CAPTURE))

/**
 * @brief TIMER channel REF format in PWM mode.
 */
typedef enum {
    TIMER_CH_PWM_REF_FORMAT_0 = TIMER_CH_CNTRL0_OCCM_FORMAT_0, /*!< REF = 0. */
    TIMER_CH_PWM_REF_FORMAT_1 = TIMER_CH_CNTRL0_OCCM_FORMAT_1, /*!< REF = 1 if: (CNT == CCR) or ((CNT == CCR1) and CCR1_EN = 1),
                                                                    else REF = 0. */
    TIMER_CH_PWM_REF_FORMAT_2 = TIMER_CH_CNTRL0_OCCM_FORMAT_2, /*!< REF = 0 if: (CNT == CCR) or ((CNT == CCR1) and CCR1_EN = 1),
                                                                    else REF = 1. */
    TIMER_CH_PWM_REF_FORMAT_3 = TIMER_CH_CNTRL0_OCCM_FORMAT_3, /*!< Toggle REF state if: (CNT == CCR) or
                                                                                        ((CNT == CCR1) and CCR1_EN = 1). */
    TIMER_CH_PWM_REF_FORMAT_4 = TIMER_CH_CNTRL0_OCCM_FORMAT_4, /*!< REF = 0. */
    TIMER_CH_PWM_REF_FORMAT_5 = TIMER_CH_CNTRL0_OCCM_FORMAT_5, /*!< REF = 1. */
    TIMER_CH_PWM_REF_FORMAT_6 = TIMER_CH_CNTRL0_OCCM_FORMAT_6, /*!< If CCR1_EN = 0:
                                                                      DIR = 0: REF = 1 if (CNT < CCR), else REF = 0,
                                                                      DIR = 1: REF = 0 if (CNT > CCR), else REF = 1,
                                                                    else if CCR1_EN = 1:
                                                                      DIR = 0: REF = 0 if (CCR <= CNT <= CCR1), else REF = 1,
                                                                      DIR = 1: REF = 0 if (CCR < CNT < CCR1), else REF = 1.
                                                                    The condition (CCR < CCR1) must be observed. */
    TIMER_CH_PWM_REF_FORMAT_7 = TIMER_CH_CNTRL0_OCCM_FORMAT_7  /*!< If CCR1_EN = 0:
                                                                       DIR = 0: REF = 0 if (CNT < CCR), else REF = 1,
                                                                       DIR = 1: REF = 1 if (CNT > CCR), else REF = 0,
                                                                    else if CCR1_EN = 1:
                                                                       DIR = 0: REF = 1 if (CCR <= CNT <= CCR1), else REF = 0,
                                                                       DIR = 1: REF = 1 if (CCR < CNT < CCR1), else REF = 0.
                                                                    The condition (CCR < CCR1) must be observed. */
} TIMER_CH_PWM_REF_Format_TypeDef;

#define IS_TIMER_CH_PWM_REF_FORMAT(FORMAT) (((FORMAT) == TIMER_CH_PWM_REF_FORMAT_0) || \
                                            ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_1) || \
                                            ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_2) || \
                                            ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_3) || \
                                            ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_4) || \
                                            ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_5) || \
                                            ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_6) || \
                                            ((FORMAT) == TIMER_CH_PWM_REF_FORMAT_7))

/**
 * @brief TIMER CCR and CCR1 update mode in PWM mode.
 */
typedef enum {
    TIMER_CH_PWM_CCR_UPD_IMMEDIATELY = (((uint32_t)0x0) << TIMER_CH_CNTRL2_CCR_RLD_Pos), /*!< The CCR and CCR1 registers is updated immediately. */
    TIMER_CH_PWM_CCR_UPD_ON_CNT_EQ_0 = (((uint32_t)0x1) << TIMER_CH_CNTRL2_CCR_RLD_Pos)  /*!< The CCR and CCR1 registers is updated at (CNT == 0) condition. */
} TIMER_CH_PWM_CCR_UpdateMode_TypeDef;

#define IS_TIMER_CH_PWM_CCR_UPDATE_MODE(MODE) (((MODE) == TIMER_CH_PWM_CCR_UPD_IMMEDIATELY) || \
                                               ((MODE) == TIMER_CH_PWM_CCR_UPD_ON_CNT_EQ_0))

/**
 * @brief TIMER channel DTG clock source in PWM mode.
 */
typedef enum {
    TIMER_CH_PWM_DTG_CLK_SRC_TIM_CLK = (((uint32_t)0x0) << TIMER_CH_DTG_EDTS_Pos), /*!< Specify the TIM_CLK signal as DTG clock source. */
    TIMER_CH_PWM_DTG_CLK_SRC_FDTS    = (((uint32_t)0x1) << TIMER_CH_DTG_EDTS_Pos)  /*!< Specify the FDTS signal as DTG clock source. */
} TIMER_CH_PWM_DTG_ClockSource_TypeDef;

#define IS_TIMER_CH_PWM_DTG_CLK_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_PWM_DTG_CLK_SRC_TIM_CLK) || \
                                                ((SOURCE) == TIMER_CH_PWM_DTG_CLK_SRC_FDTS))

/**
 * @brief TIMER channel events prescaler in capture mode.
 */
typedef enum {
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_1 = TIMER_CH_CNTRL0_CH_PSC_DIV_1, /*!< Each event is captured. */
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_2 = TIMER_CH_CNTRL0_CH_PSC_DIV_2, /*!< Capturing every 2nd event. */
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_4 = TIMER_CH_CNTRL0_CH_PSC_DIV_4, /*!< Capturing every 4th event. */
    TIMER_CH_CAP_EVNT_PRESCALER_DIV_8 = TIMER_CH_CNTRL0_CH_PSC_DIV_8  /*!< Capturing every 8th event. */
} TIMER_CH_CAP_EventPrescaler_TypeDef;

#define IS_TIMER_CH_CAP_EVENT_PRESCALER(VALUE) (((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_1) || \
                                                ((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_2) || \
                                                ((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_4) || \
                                                ((VALUE) == TIMER_CH_CAP_EVNT_PRESCALER_DIV_8))

/**
 * @brief TIMER channel CCR event source in capture mode.
 */
typedef enum {
    TIMER_CH_CAP_CCR_EVNT_SRC_RE      = TIMER_CH_CNTRL0_CH_SEL_CH_RE,   /*!< Select rising edge from current TIMER channel. */
    TIMER_CH_CAP_CCR_EVNT_SRC_FE      = TIMER_CH_CNTRL0_CH_SEL_CH_FE,   /*!< Select falling edge from current TIMER channel. */
    TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp1 = TIMER_CH_CNTRL0_CH_SEL_CHp1_RE, /*!< Select rising edge from other TIMER channel (current channel plus 1). */
    TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp2 = TIMER_CH_CNTRL0_CH_SEL_CHp2_RE  /*!< Select rising edge from other TIMER channel (current channel plus 2). */
} TIMER_CH_CAP_CCR_EventSource_TypeDef;

#define IS_TIMER_CH_CAP_CCR_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_RE) ||      \
                                                  ((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_FE) ||      \
                                                  ((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp1) || \
                                                  ((SOURCE) == TIMER_CH_CAP_CCR_EVNT_SRC_RE_CHp2))

/**
 * @brief TIMER channel CCR1 event source in capture mode.
 */
typedef enum {
    TIMER_CH_CAP_CCR1_EVNT_SRC_RE      = TIMER_CH_CNTRL2_CH_SEL1_CH_RE,   /*!< Select rising edge from current TIMER channel. */
    TIMER_CH_CAP_CCR1_EVNT_SRC_FE      = TIMER_CH_CNTRL2_CH_SEL1_CH_FE,   /*!< Select falling edge from current TIMER channel. */
    TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp1 = TIMER_CH_CNTRL2_CH_SEL1_CHp1_FE, /*!< Select falling edge from other TIMER channel (current channel plus 1). */
    TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp2 = TIMER_CH_CNTRL2_CH_SEL1_CHp2_FE  /*!< Select falling edge from other TIMER channel (current channel plus 2). */
} TIMER_CH_CAP_CCR1_EventSource_TypeDef;

#define IS_TIMER_CH_CAP_CCR1_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_RE) ||      \
                                                   ((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_FE) ||      \
                                                   ((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp1) || \
                                                   ((SOURCE) == TIMER_CH_CAP_CCR1_EVNT_SRC_FE_CHp2))

/**
 * @brief TIMER channel filter configuration.
 */
typedef enum {
    TIMER_CH_FILTER_1FF_AT_FDTS        = TIMER_CH_CNTRL0_CH_FLTR_1_FDTS,        /*!< Signal is latched by 1 trigger at FDTS frequency. */
    TIMER_CH_FILTER_2FF_AT_TIM_CLK     = TIMER_CH_CNTRL0_CH_FLTR_2_TIM_CLK,     /*!< Signal is latched by 2 triggers at TIM_CLK frequency (2xT_TIM_CLK). */
    TIMER_CH_FILTER_4FF_AT_TIM_CLK     = TIMER_CH_CNTRL0_CH_FLTR_4_TIM_CLK,     /*!< Signal is latched by 4 triggers at TIM_CLK frequency (4xT_TIM_CLK). */
    TIMER_CH_FILTER_8FF_AT_TIM_CLK     = TIMER_CH_CNTRL0_CH_FLTR_8_TIM_CLK,     /*!< Signal is latched by 8 triggers at TIM_CLK frequency (8xT_TIM_CLK). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_2  = TIMER_CH_CNTRL0_CH_FLTR_6_FDTS_DIV_2,  /*!< Signal is latched by 6 triggers at FDTS/2  frequency (12xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_2  = TIMER_CH_CNTRL0_CH_FLTR_8_FDTS_DIV_2,  /*!< Signal is latched by 8 triggers at FDTS/2  frequency (16xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_4  = TIMER_CH_CNTRL0_CH_FLTR_6_FDTS_DIV_4,  /*!< Signal is latched by 6 triggers at FDTS/4  frequency (24xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_4  = TIMER_CH_CNTRL0_CH_FLTR_8_FDTS_DIV_4,  /*!< Signal is latched by 8 triggers at FDTS/4  frequency (32xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_8  = TIMER_CH_CNTRL0_CH_FLTR_6_FDTS_DIV_8,  /*!< Signal is latched by 6 triggers at FDTS/8  frequency (48xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_8  = TIMER_CH_CNTRL0_CH_FLTR_8_FDTS_DIV_8,  /*!< Signal is latched by 8 triggers at FDTS/8  frequency (64xT_FDTS). */
    TIMER_CH_FILTER_5FF_AT_FDTS_DIV_16 = TIMER_CH_CNTRL0_CH_FLTR_5_FDTS_DIV_16, /*!< Signal is latched by 5 triggers at FDTS/16 frequency (80xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_16 = TIMER_CH_CNTRL0_CH_FLTR_6_FDTS_DIV_16, /*!< Signal is latched by 6 triggers at FDTS/16 frequency (96xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_16 = TIMER_CH_CNTRL0_CH_FLTR_8_FDTS_DIV_16, /*!< Signal is latched by 8 triggers at FDTS/16 frequency (128xT_FDTS). */
    TIMER_CH_FILTER_5FF_AT_FDTS_DIV_32 = TIMER_CH_CNTRL0_CH_FLTR_5_FDTS_DIV_32, /*!< Signal is latched by 5 triggers at FDTS/32 frequency (160xT_FDTS). */
    TIMER_CH_FILTER_6FF_AT_FDTS_DIV_32 = TIMER_CH_CNTRL0_CH_FLTR_6_FDTS_DIV_32, /*!< Signal is latched by 6 triggers at FDTS/32 frequency (192xT_FDTS). */
    TIMER_CH_FILTER_8FF_AT_FDTS_DIV_32 = TIMER_CH_CNTRL0_CH_FLTR_8_FDTS_DIV_32  /*!< Signal is latched by 8 triggers at FDTS/32 frequency (256xT_FDTS). */
} TIMER_CH_Filter_TypeDef;

#define IS_TIMER_CH_FILTER(FILTER) (((FILTER) == TIMER_CH_FILTER_1FF_AT_FDTS) ||        \
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
 * @brief TIMER channel positive output polarity.
 */
typedef enum {
    TIMER_CH_OUTP_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_CH_CNTRL1_INV_Pos), /*!< The channel positive output is not inverted. */
    TIMER_CH_OUTP_POLARITY_INV     = (((uint32_t)0x1) << TIMER_CH_CNTRL1_INV_Pos)  /*!< The channel positive output is inverted. */
} TIMER_CH_OUTP_Polarity_TypeDef;

#define IS_TIMER_CH_OUTP_POLARITY(STATE) (((STATE) == TIMER_CH_OUTP_POLARITY_NON_INV) || \
                                          ((STATE) == TIMER_CH_OUTP_POLARITY_INV))

/**
 * @brief TIMER channel positive output source.
 */
typedef enum {
    TIMER_CH_OUTP_SRC_0   = TIMER_CH_CNTRL1_SELO_ALW0, /*!< Select the '0' state on the CHy line. */
    TIMER_CH_OUTP_SRC_1   = TIMER_CH_CNTRL1_SELO_ALW1, /*!< Select the '1' state on the CHy line. */
    TIMER_CH_OUTP_SRC_REF = TIMER_CH_CNTRL1_SELO_REF,  /*!< Select the REF state on the CHy line. */
    TIMER_CH_OUTP_SRC_DTG = TIMER_CH_CNTRL1_SELO_DTG   /*!< Select the DTG output state on the CHy line. */
} TIMER_CH_OUTP_Source_TypeDef;

#define IS_TIMER_CH_OUTP_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_OUTP_SRC_0) ||   \
                                         ((SOURCE) == TIMER_CH_OUTP_SRC_1) ||   \
                                         ((SOURCE) == TIMER_CH_OUTP_SRC_REF) || \
                                         ((SOURCE) == TIMER_CH_OUTP_SRC_DTG))

/**
 * @brief TIMER channel positive output mode.
 */
typedef enum {
    TIMER_CH_OUTP_MODE_IN        = TIMER_CH_CNTRL1_SELOE_ALW0, /*!< Select the input mode on the CHy line. */
    TIMER_CH_OUTP_MODE_OUT       = TIMER_CH_CNTRL1_SELOE_ALW1, /*!< Select the output mode on the CHy line. */
    TIMER_CH_OUTP_MODE_REF_AS_OE = TIMER_CH_CNTRL1_SELOE_REF,  /*!< The REF signal specifies the CHy line mode. */
    TIMER_CH_OUTP_MODE_DTG_AS_OE = TIMER_CH_CNTRL1_SELOE_DTG   /*!< The DTG output specifies the CHy line mode. */
} TIMER_CH_OUTP_Mode_TypeDef;

#define IS_TIMER_CH_OUTP_MODE(MODE) (((MODE) == TIMER_CH_OUTP_MODE_IN) ||        \
                                     ((MODE) == TIMER_CH_OUTP_MODE_OUT) ||       \
                                     ((MODE) == TIMER_CH_OUTP_MODE_REF_AS_OE) || \
                                     ((MODE) == TIMER_CH_OUTP_MODE_DTG_AS_OE))

/**
 * @brief TIMER channel negative output polarity.
 */
typedef enum {
    TIMER_CH_OUTN_POLARITY_NON_INV = (((uint32_t)0x0) << TIMER_CH_CNTRL1_NINV_Pos), /*!< The channel negative output is not inverted. */
    TIMER_CH_OUTN_POLARITY_INV     = (((uint32_t)0x1) << TIMER_CH_CNTRL1_NINV_Pos)  /*!< The channel negative output is inverted. */
} TIMER_CH_OUTN_Polarity_TypeDef;

#define IS_TIMER_CH_OUTN_POLARITY(STATE) (((STATE) == TIMER_CH_OUTN_POLARITY_NON_INV) || \
                                          ((STATE) == TIMER_CH_OUTN_POLARITY_INV))

/**
 * @brief TIMER channel negative output source.
 */
typedef enum {
    TIMER_CH_OUTN_SRC_0   = TIMER_CH_CNTRL1_NSELO_ALW0, /*!< Select the '0' state on the nCHy line. */
    TIMER_CH_OUTN_SRC_1   = TIMER_CH_CNTRL1_NSELO_ALW1, /*!< Select the '1' state on the nCHy line. */
    TIMER_CH_OUTN_SRC_REF = TIMER_CH_CNTRL1_NSELO_REF,  /*!< Select the nREF state on the nCHy line. */
    TIMER_CH_OUTN_SRC_DTG = TIMER_CH_CNTRL1_NSELO_DTG   /*!< Select the DTG output state on the nCHy line. */
} TIMER_CH_OUTN_Source_TypeDef;

#define IS_TIMER_CH_OUTN_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_OUTN_SRC_0) ||   \
                                         ((SOURCE) == TIMER_CH_OUTN_SRC_1) ||   \
                                         ((SOURCE) == TIMER_CH_OUTN_SRC_REF) || \
                                         ((SOURCE) == TIMER_CH_OUTN_SRC_DTG))

/**
 * @brief TIMER channel negative output mode.
 */
typedef enum {
    TIMER_CH_OUTN_MODE_IN        = TIMER_CH_CNTRL1_NSELOE_ALW0, /*!< Select the input mode on the nCHy line. */
    TIMER_CH_OUTN_MODE_OUT       = TIMER_CH_CNTRL1_NSELOE_ALW1, /*!< Select the output mode on the nCHy line. */
    TIMER_CH_OUTN_MODE_REF_AS_OE = TIMER_CH_CNTRL1_NSELOE_REF,  /*!< The nREF signal specifies the nCHy line mode. */
    TIMER_CH_OUTN_MODE_DTG_AS_OE = TIMER_CH_CNTRL1_NSELOE_DTG   /*!< The DTG output specifies the nCHy line mode. */
} TIMER_CH_OUTN_Mode_TypeDef;

#define IS_TIMER_CH_OUTN_MODE(MODE) (((MODE) == TIMER_CH_OUTN_MODE_IN) ||        \
                                     ((MODE) == TIMER_CH_OUTN_MODE_OUT) ||       \
                                     ((MODE) == TIMER_CH_OUTN_MODE_REF_AS_OE) || \
                                     ((MODE) == TIMER_CH_OUTN_MODE_DTG_AS_OE))

/**
 * @brief TIMER status flags.
 */
typedef enum {
    TIMER_FLAG_CNT_ZERO     = TIMER_STATUS_CNT_ZERO_EVNT,     /*!< The (CNT == 0) condition occurred. */
    TIMER_FLAG_CNT_ARR      = TIMER_STATUS_CNT_ARR_EVNT,      /*!< The (CNT == ARR) condition occurred. */
    TIMER_FLAG_ETR_RE       = TIMER_STATUS_ETR_RE_EVNT,       /*!< The ETR rising edge occurred. */
    TIMER_FLAG_ETR_FE       = TIMER_STATUS_ETR_FE_EVNT,       /*!< The ETR falling edge occurred. */
    TIMER_FLAG_BRK          = TIMER_STATUS_BRK_EVNT,          /*!< The (BRK == 1) condition occurred. */
    TIMER_FLAG_CH1_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVNT_CH1,  /*!< The Channel 1 CCR capture condition occurred. */
    TIMER_FLAG_CH2_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVNT_CH2,  /*!< The Channel 2 CCR capture condition occurred. */
    TIMER_FLAG_CH3_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVNT_CH3,  /*!< The Channel 3 CCR capture condition occurred. */
    TIMER_FLAG_CH4_CAP_CCR  = TIMER_STATUS_CCR_CAP_EVNT_CH4,  /*!< The Channel 4 CCR capture condition occurred. */
    TIMER_FLAG_CH1_PWM_REF  = TIMER_STATUS_CCR_REF_EVNT_CH1,  /*!< The Channel 1 (REF == 1) condition occurred. */
    TIMER_FLAG_CH2_PWM_REF  = TIMER_STATUS_CCR_REF_EVNT_CH2,  /*!< The Channel 2 (REF == 1) condition occurred. */
    TIMER_FLAG_CH3_PWM_REF  = TIMER_STATUS_CCR_REF_EVNT_CH3,  /*!< The Channel 3 (REF == 1) condition occurred. */
    TIMER_FLAG_CH4_PWM_REF  = TIMER_STATUS_CCR_REF_EVNT_CH4,  /*!< The Channel 4 (REF == 1) condition occurred. */
    TIMER_FLAG_CH1_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVNT_CH1, /*!< The Channel 1 CCR1 capture condition occurred. */
    TIMER_FLAG_CH2_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVNT_CH2, /*!< The Channel 2 CCR1 capture condition occurred. */
    TIMER_FLAG_CH3_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVNT_CH3, /*!< The Channel 3 CCR1 capture condition occurred. */
    TIMER_FLAG_CH4_CAP_CCR1 = TIMER_STATUS_CCR_CAP1_EVNT_CH4  /*!< The Channel 4 CCR1 capture condition occurred. */
} TIMER_Flags_TypeDef;

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

#define IS_TIMER_FLAGS(FLAGS) (((FLAGS) & ~((uint32_t)TIMER_FLAG_MASK)) == 0)

/**
 * @brief TIMER counter init structure definition.
 */
typedef struct {
    uint32_t TIMER_CNT_Counter;                                    /*!< Specify the initial counter value.
                                                                        This parameter can be a number from 0x00000000 to 0xFFFFFFFF. */
    uint32_t TIMER_CNT_Prescaler;                                  /*!< Specify the prescaler value used to divide the TIM_CLK.
                                                                        This parameter can be a number from 0x00000000 to 0xFFFFFFFF.
                                                                        TIM_CLKd = TIM_CLK/(TIMER_CNT_Prescaler + 1). */
    uint32_t TIMER_CNT_Period;                                     /*!< Specify the counter period that will be loaded into the ARR register at the next update event.
                                                                        The full counter period is TIMER_CNT_Period + 1.
                                                                        This parameter must be a number from 0x00000000 to 0xFFFFFFFF. */
    TIMER_CNT_EventSource_TypeDef TIMER_CNT_EventSource;           /*!< Specify the counter event source.
                                                                        This parameter can be a value of @ref TIMER_CNT_EventSource_TypeDef. */
    TIMER_CNT_Mode_TypeDef TIMER_CNT_Mode;                         /*!< Specify the counter mode.
                                                                        This parameter can be a value of @ref TIMER_CNT_Mode_TypeDef.
                                                                        Note: TIMER_CNT_Mode use with TIMER_CNT_EventSource!
                                                                              If TIMER_CNT_EventSource != TIMER_CNT_EVNT_SRC_TIM_CLK, then TIMER_CNT_Mode = TIMER_CNT_MODE_EVNT_FIXED_DIR. */
    TIMER_CNT_Dir_TypeDef TIMER_CNT_Direction;                     /*!< Specify the counter direction.
                                                                        This parameter can be a value of @ref TIMER_CNT_Dir_TypeDef. */
    TIMER_CNT_PeriodUpdateMode_TypeDef TIMER_CNT_PeriodUpdateMode; /*!< Specify the counter period (ARR register) updating mode.
                                                                        This parameter can be a value of @ref TIMER_CNT_PeriodUpdateMode_TypeDef. */
    TIMER_FDTS_Prescaler_TypeDef TIMER_FDTS_Prescaler;             /*!< Specify the FDTS prescaler configuration.
                                                                        This parameter can be a value of @ref TIMER_FDTS_Prescaler_TypeDef. */
    TIMER_ETR_Filter_TypeDef TIMER_ETR_Filter;                     /*!< Specify the ETR filter configuration.
                                                                        This parameter can be a value of @ref TIMER_ETR_Filter_TypeDef. */
    TIMER_ETR_Prescaler_TypeDef TIMER_ETR_Prescaler;               /*!< Specify the ETR prescaler configuration.
                                                                        This parameter can be a value of @ref TIMER_ETR_Prescaler_TypeDef. */
    TIMER_ETR_Polarity_TypeDef TIMER_ETR_Polarity;                 /*!< Specify the ETR polarity configuration.
                                                                        This parameter can be a value of @ref TIMER_ETR_Polarity_TypeDef. */
    TIMER_BRK_Polarity_TypeDef TIMER_BRK_Polarity;                 /*!< Specify the BRK polarity configuration.
                                                                        This parameter can be a value of @ref TIMER_BRK_Polarity_TypeDef. */
} TIMER_CNT_InitTypeDef;

/**
 * @brief TIMER channel init structure definition.
 */
typedef struct {
    TIMER_CH_Number_TypeDef TIMER_CH_Number; /*!< Specify the TIMER channel number to be configured.
                                                  This parameter can be a value of @ref TIMER_CH_Number_TypeDef. */
    TIMER_CH_Mode_TypeDef TIMER_CH_Mode;     /*!< Specify the TIMER channel mode.
                                                  This parameter can be a value of @ref TIMER_CH_Mode_TypeDef. */
    FunctionalState TIMER_CH_UseCCR1;        /*!< Enable or disable the CCR1 register.
                                                  This parameter can be a value of @ref FunctionalState. */

    TIMER_CH_PWM_REF_Format_TypeDef TIMER_CH_PWM_REF_Format;           /*!< Specify the REF signal format in PWM mode.
                                                                            This parameter can be a value of @ref TIMER_CH_PWM_REF_Format_TypeDef. */
    TIMER_CH_PWM_CCR_UpdateMode_TypeDef TIMER_CH_PWM_CCR_UpdateMode;   /*!< Specify the TIMER CCR, CCR1 update mode in PWM mode.
                                                                            This parameter can be a value of @ref TIMER_CH_PWM_CCR_UpdateMode_TypeDef. */
    TIMER_CH_PWM_DTG_ClockSource_TypeDef TIMER_CH_PWM_DTG_ClockSource; /*!< Specify the TIMER DTG clock source in PWM mode.
                                                                            This parameter can be a value of @ref TIMER_CH_PWM_DTG_ClockSource_TypeDef. */
    uint8_t TIMER_CH_PWM_DTG_MainPrescaler;                            /*!< Specify the main prescaler of TIMER DTG in PWM mode.
                                                                            This parameter can be a number from 0x00 to 0xFF. */
    uint8_t TIMER_CH_PWM_DTG_AuxPrescaler;                             /*!< Specify the auxiliary prescaler of TIMER DTG in PWM mode.
                                                                            This parameter can be a number from 0x00 to 0x0F.
                                                                            Delay DTGdel = TIMER_CH_PWM_DTG_MainPrescaler*(TIMER_CH_PWM_DTG_AuxPrescaler + 1) clocks. */
    FunctionalState TIMER_CH_PWM_ETR_UseReset;                         /*!< Use REF reset by ETR (active high) in PWM mode.
                                                                            This parameter can be a value of @ref FunctionalState. */
    FunctionalState TIMER_CH_PWM_BRK_UseReset;                         /*!< Use REF and DTG reset by BRK (active low) in PWM mode.
                                                                            This parameter can be a value of @ref FunctionalState. */

    TIMER_CH_CAP_CCR_EventSource_TypeDef TIMER_CH_CAP_CCR_EventSource;   /*!< Specify the channel CCR event source in capture mode.
                                                                              This parameter can be a value of @ref TIMER_CH_CAP_CCR_EventSource_TypeDef. */
    TIMER_CH_CAP_CCR1_EventSource_TypeDef TIMER_CH_CAP_CCR1_EventSource; /*!< Specify the channel CCR1 event source in capture mode.
                                                                              This parameter can be a value of @ref TIMER_CH_CAP_CCR1_EventSource_TypeDef. */
    TIMER_CH_CAP_EventPrescaler_TypeDef TIMER_CH_CAP_EventPrescaler;     /*!< Specify the TIMER channel events prescaler configuration in capture mode.
                                                                              This parameter can be a value of @ref TIMER_CH_CAP_EventPrescaler_TypeDef. */
    FunctionalState TIMER_CH_CAP_UseEventDelay;                          /*!< Use synchronization between the capture event and the update of registers CCR and CCR1.
                                                                              This parameter can be a value of @ref FunctionalState. */
    TIMER_CH_Filter_TypeDef TIMER_CH_CAP_Filter;                         /*!< Specify the TIMER channel filter configuration.
                                                                              This parameter can be a value of @ref TIMER_CH_Filter_TypeDef. */
} TIMER_CH_InitTypeDef;

/**
 * @brief TIMER channel output init structure definition.
 */
typedef struct {
    TIMER_CH_Number_TypeDef TIMER_CH_Number; /*!< Specify the TIMER channel number to be configured.
                                                  This parameter can be a value of @ref TIMER_CH_Number_TypeDef. */

    TIMER_CH_OUTP_Polarity_TypeDef TIMER_CH_OUTP_Polarity; /*!< Specify the TIMER CHy output polarity.
                                                                This parameter can be a value of @ref TIMER_CH_OUTP_Polarity_TypeDef. */
    TIMER_CH_OUTP_Source_TypeDef TIMER_CH_OUTP_Source;     /*!< Specify the TIMER CHy output source.
                                                                This parameter can be a value of @ref TIMER_CH_OUTP_Source_TypeDef. */
    TIMER_CH_OUTP_Mode_TypeDef TIMER_CH_OUTP_Mode;         /*!< Specify the TIMER CHy output enable source.
                                                                This parameter can be a value of @ref TIMER_CH_OUTP_Mode_TypeDef. */

    TIMER_CH_OUTN_Polarity_TypeDef TIMER_CH_OUTN_Polarity; /*!< Enable or disable the TIMER nCHy output inversion.
                                                                This parameter can be a value of @ref TIMER_CH_OUTN_Polarity_TypeDef. */
    TIMER_CH_OUTN_Source_TypeDef TIMER_CH_OUTN_Source;     /*!< Specify the TIMER nCHy output source.
                                                                This parameter can be a value of @ref TIMER_CH_OUTN_Source_TypeDef. */
    TIMER_CH_OUTN_Mode_TypeDef TIMER_CH_OUTN_Mode;         /*!< Specify the TIMER nCHy output enable source.
                                                                This parameter can be a value of @ref TIMER_CH_OUTN_Mode_TypeDef. */
} TIMER_CH_OUT_InitTypeDef;

/** @} */ /* End of the group TIMER_Exported_Types */

/** @defgroup TIMER_Exported_Defines TIMER Exported Defines
 * @{
 */

/** @defgroup TIMER_CH_PWM_DTG_Prescaler TIMER Channel PWM DTG Prescaler
 * @{
 */

#define IS_TIMER_CH_PWM_DTG_AUX_PRESCALER(VALUE) (((VALUE) & ~TIMER_CH_DTG_DTGX_Msk) == 0)

/** @} */ /* End of the group TIMER_CH_PWM_DTG_Prescaler */

/** @} */ /* End of the group TIMER_Exported_Defines */

/** @addtogroup TIMER_Exported_Functions TIMER Exported Functions
 * @{
 */

void TIMER_DeInit(MDR_TIMER_TypeDef* TIMERx);

void TIMER_CNT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CNT_InitTypeDef* TIMER_CntInitStruct);
void TIMER_CNT_StructInit(TIMER_CNT_InitTypeDef* TIMER_CntInitStruct);

void            TIMER_CNT_Cmd(MDR_TIMER_TypeDef* TIMERx, FunctionalState NewState);
FunctionalState TIMER_CNT_GetCmdState(MDR_TIMER_TypeDef* TIMERx);

void     TIMER_CNT_SetCounter(MDR_TIMER_TypeDef* TIMERx, uint32_t Counter);
uint32_t TIMER_CNT_GetCounter(MDR_TIMER_TypeDef* TIMERx);

void     TIMER_CNT_SetPrescaler(MDR_TIMER_TypeDef* TIMERx, uint32_t Prescaler);
uint32_t TIMER_CNT_GetPrescaler(MDR_TIMER_TypeDef* TIMERx);

void     TIMER_CNT_SetPeriodUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_PeriodUpdateMode_TypeDef PeriodUpdateMode);
void     TIMER_CNT_SetPeriod(MDR_TIMER_TypeDef* TIMERx, uint32_t Period);
uint32_t TIMER_CNT_GetPeriod(MDR_TIMER_TypeDef* TIMERx);

void                  TIMER_CNT_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CNT_EventSource_TypeDef EventSource);
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
void TIMER_CH_FilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_Filter_TypeDef Filter);

void TIMER_CH_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_InitTypeDef* TIMER_ChInitStruct);
void TIMER_CH_StructInit(TIMER_CH_InitTypeDef* TIMER_ChInitStruct);

void       TIMER_CH_SetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint32_t CCR);
uint32_t   TIMER_CH_GetCCR(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);
FlagStatus TIMER_CH_GetCCRWriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);

void            TIMER_CH_CCR1Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);
FunctionalState TIMER_CH_GetCCR1CmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);
void            TIMER_CH_SetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint32_t CCR1);
uint32_t        TIMER_CH_GetCCR1(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);
FlagStatus      TIMER_CH_GetCCR1WriteStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);

void TIMER_CH_PWM_SetCompareUpdateMode(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_CCR_UpdateMode_TypeDef UpdateMode);
/**
 * @brief  Set the TIMERx channel capture/compare register (CCR) value.
 * @param  TIMERx: Select the TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify the TIMERx channel number.
 * @param  Compare: Specify the capture/compare register (CCR) new value.
 * @return None.
 */
#define TIMER_CH_PWM_SetCompare(TIMERx, Channel, Compare) TIMER_CH_SetCCR(TIMERx, Channel, Compare)

/**
 * @brief  Set the TIMERx channel capture/compare register 1 (CCR1) value.
 * @param  TIMERx: Select the TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify the TIMERx channel number.
 * @param  Compare1: Specify the capture/compare register 1 (CCR1) new value.
 * @return None.
 */
#define TIMER_CH_PWM_SetCompare1(TIMERx, Channel, Compare1) TIMER_CH_SetCCR1(TIMERx, Channel, Compare1)

void            TIMER_CH_PWM_REF_FormatConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_PWM_REF_Format_TypeDef Format);
void            TIMER_CH_PWM_DTG_Config(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, uint8_t MainPrescaler, uint8_t AuxPrescaler, TIMER_CH_PWM_DTG_ClockSource_TypeDef ClockSource);
void            TIMER_CH_PWM_ETR_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);
FunctionalState TIMER_CH_PWM_ETR_GetResetCmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);
void            TIMER_CH_PWM_BRK_ResetCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);
FunctionalState TIMER_CH_PWM_BRK_GetResetCmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);

/**
 * @brief  Return the TIMERx channel capture/compare register (CCR) value.
 * @param  TIMERx: Select the TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify the TIMERx channel number.
 * @return Channel capture/compare register (CCR) value.
 */
#define TIMER_CH_CAP_GetCapture(TIMERx, Channel) TIMER_CH_GetCCR(TIMERx, Channel)

/**
 * @brief  Return the TIMERx channel capture/compare register 1 (CCR1) value.
 * @param  TIMERx: Select the TIMER peripheral.
 *         This parameter can be one of the MDR_TIMERx values, where x is a number in range [1; 4].
 * @param  Channel: @ref TIMER_CH_Number_TypeDef - specify the TIMERx channel number.
 * @return Channel capture/compare register 1 (CCR1) value.
 */
#define TIMER_CH_CAP_GetCapture1(TIMERx, Channel) TIMER_CH_GetCCR1(TIMERx, Channel)

void TIMER_CH_CAP_SetEventPrescaler(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_EventPrescaler_TypeDef EventPrescaler);
void TIMER_CH_CAP_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR_EventSource_TypeDef EventSource);
void TIMER_CH_CAP_Event1SourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, TIMER_CH_CAP_CCR1_EventSource_TypeDef Event1Source);

void            TIMER_CH_CAP_EventDelayCmd(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel, FunctionalState NewState);
FunctionalState TIMER_CH_CAP_GetEventDelayCmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_CH_Number_TypeDef Channel);

void TIMER_CH_OUT_Init(MDR_TIMER_TypeDef* TIMERx, const TIMER_CH_OUT_InitTypeDef* TIMER_ChOutInitStruct);
void TIMER_CH_OUT_StructInit(TIMER_CH_OUT_InitTypeDef* TIMER_ChOutInitStruct);

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

void TIMER_ITConfig(MDR_TIMER_TypeDef* TIMERx, uint32_t ITs, FunctionalState NewState);

void            TIMER_DMACmd(MDR_TIMER_TypeDef* TIMERx, uint32_t DMAReqs, FunctionalState NewState);
FunctionalState TIMER_GetDMACmdState(MDR_TIMER_TypeDef* TIMERx, TIMER_Flags_TypeDef DMAReq);

/** @} */ /* End of the group TIMER_Exported_Functions */

/** @} */ /* End of the group TIMER */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_TIMER_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_timer.h */

