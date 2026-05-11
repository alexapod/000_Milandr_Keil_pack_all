/**
 ******************************************************************************
 * @file    MDR32VF0xI_bkp.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    23/05/2025
 * @brief   This file contains all the functions prototypes for the BKP
 *          firmware library.
 ******************************************************************************
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
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MDR32VF0xI_BKP_H
#define MDR32VF0xI_BKP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup BKP BKP
 * @{
 */

/** @defgroup BKP_Exported_Types BKP Exported Types
 * @{
 */

/**
 * @brief BKP subblocks.
 */
typedef enum {
    BKP_MEM     = ((uint32_t)0x1 << 0), /*!< BKP MEM subblock: RAM of cryptographic keys (512 bytes). */
    BKP_CONTROL = ((uint32_t)0x1 << 1), /*!< BKP CONTROL subblock: JTAG and voltage regulators. */
    BKP_SW      = ((uint32_t)0x1 << 2), /*!< BKP SW subblock: emergency power supply control. */
    BKP_CLK     = ((uint32_t)0x1 << 3), /*!< BKP CLK subblock: clock source control. */
    BKP_RTC     = ((uint32_t)0x1 << 4), /*!< BKP RTC subblock: RTC, WUT, TAMPER, TIMESTAMP and TMPCAL (TMPCAL only for MDR1206FI and MDR1206AFI). */
    BKP_ALL     = ((uint32_t)0x1F)      /*!< Select all subblocks. */
} BKP_Subblocks_TypeDef;

#define IS_BKP_SUBBLOCK(SUBBLOCK) (((SUBBLOCK) & ~(uint32_t)(BKP_ALL)) == 0x0)

/**
 * @brief BKP BLDO boost/trim.
 */
typedef enum {
    BKP_BLDO_BOOST_TYPICAL   = (((uint32_t)0x0) << BKP_LDO_BLDO_TRIM_Pos),                      /*!< Typical battery power regulator voltage. */
    BKP_BLDO_BOOST_PLUS_2pct = (((uint32_t)0x1) << BKP_LDO_BLDO_TRIM_Pos) | BKP_LDO_BLDO_BOOST, /*!< Trim battery power regulator with + 2% from typical voltage. */
    BKP_BLDO_BOOST_PLUS_4pct = (((uint32_t)0x2) << BKP_LDO_BLDO_TRIM_Pos) | BKP_LDO_BLDO_BOOST, /*!< Trim battery power regulator with + 4% from typical voltage. */
    BKP_BLDO_BOOST_PLUS_6pct = (((uint32_t)0x3) << BKP_LDO_BLDO_TRIM_Pos) | BKP_LDO_BLDO_BOOST  /*!< Trim battery power regulator with + 6% from typical voltage. */
} BKP_BLDO_Boost_TypeDef;

#define IS_BKP_BLDO_BOOST(BOOST) (((BOOST) == BKP_BLDO_BOOST_TYPICAL) ||   \
                                  ((BOOST) == BKP_BLDO_BOOST_PLUS_2pct) || \
                                  ((BOOST) == BKP_BLDO_BOOST_PLUS_4pct) || \
                                  ((BOOST) == BKP_BLDO_BOOST_PLUS_6pct))

/**
 * @brief BKP WAKEUPx lines.
 */
typedef enum {
    BKP_WAKEUP_1 = BKP_LDO_WAKEUP1, /*!< Specify the WAKEUP1 input. */
    BKP_WAKEUP_2 = BKP_LDO_WAKEUP2, /*!< Specify the WAKEUP2 input. */
    BKP_WAKEUP_3 = BKP_LDO_WAKEUP3  /*!< Specify the WAKEUP3 input. */
} BKP_WAKEUP_TypeDef;

#define IS_BKP_WAKEUP(WAKEUP) (((WAKEUP) == BKP_WAKEUP_1) || \
                               ((WAKEUP) == BKP_WAKEUP_2) || \
                               ((WAKEUP) == BKP_WAKEUP_3))

/**
 * @brief BKP LSE (Low Speed External) oscillator clock mode and source selection constants.
 */
typedef enum {
    BKP_LSE_OFF    = ((uint32_t)0x0),                 /*!< Switch off LSE oscillator clock. */
    BKP_LSE_ON     = BKP_CLK_LSE_ON,                  /*!< Switch on LSE oscillator clock with the internal clock source. */
    BKP_LSE_BYPASS = BKP_CLK_LSE_ON | BKP_CLK_LSE_BYP /*!< Switch on LSE oscillator clock with an external clock source. */
} BKP_LSE_Mode_TypeDef;

#define IS_BKP_LSE_MODE(MODE) (((MODE) == BKP_LSE_OFF) || \
                               ((MODE) == BKP_LSE_ON) ||  \
                               ((MODE) == BKP_LSE_BYPASS))

/**
 * @brief BKP clock sources ready flags.
 */
typedef enum {
    BKP_FLAG_HSIRDY = BKP_CLK_HSI_RDY, /*!< Flag for entering the operating mode of the HSI oscillator clock. */
    BKP_FLAG_LSIRDY = BKP_CLK_LSI_RDY, /*!< Flag for entering the operating mode of the LSI oscillator clock. */
    BKP_FLAG_LSERDY = BKP_CLK_LSE_RDY  /*!< Flag for entering the operating mode of the LSE oscillator clock. */
} BKP_CLK_Flags_TypeDef;

#define IS_BKP_CLK_FLAG(FLAG) (((FLAG) == BKP_FLAG_HSIRDY) || \
                               ((FLAG) == BKP_FLAG_LSIRDY) || \
                               ((FLAG) == BKP_FLAG_LSERDY))

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief BKP SW polarity configuration.
 */
typedef enum {
    BKP_SW_POLARITY_NON_INV = (((uint32_t)0x0) << BKP_RTC_TMPCAL3_SWCTR_INV_Pos), /*!< BKP SW output is not inverted. */
    BKP_SW_POLARITY_INV     = (((uint32_t)0x1) << BKP_RTC_TMPCAL3_SWCTR_INV_Pos)  /*!< BKP SW output is inverted. */
} BKP_SW_Polarity_TypeDef;

#define IS_BKP_SW_POLARITY(POL) (((POL) == BKP_SW_POLARITY_NON_INV) || \
                                 ((POL) == BKP_SW_POLARITY_INV))
#endif

/**
 * @brief BKP RTC WUT clock source.
 */
typedef enum {
    BKP_RTC_WUT_CLK_SRC_SEC_CLK        = BKP_RTC_CR_WUCK_SEL_SEC_CLK,       /*!< WUT clock is the same as for RTC/Calendar (SEC_CLK). */
    BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_2  = BKP_RTC_CR_WUCK_SEL_RTC_CLK_DIV_2, /*!< WUT clock is the RTC_CLK divided by 2. */
    BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_4  = BKP_RTC_CR_WUCK_SEL_RTC_CLK_DIV_4, /*!< WUT clock is the RTC_CLK divided by 4. */
    BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_8  = BKP_RTC_CR_WUCK_SEL_RTC_CLK_DIV_8, /*!< WUT clock is the RTC_CLK divided by 8. */
    BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_16 = BKP_RTC_CR_WUCK_SEL_RTC_CLK_DIV_16 /*!< WUT clock is the RTC_CLK divided by 16. */
} BKP_RTC_WUT_ClockSource_TypeDef;

#define IS_BKP_RTC_WUT_CLOCK_SOURCE(CLK) (((CLK) == BKP_RTC_WUT_CLK_SRC_SEC_CLK) ||       \
                                          ((CLK) == BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_2) || \
                                          ((CLK) == BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_4) || \
                                          ((CLK) == BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_8) || \
                                          ((CLK) == BKP_RTC_WUT_CLK_SRC_RTC_CLK_DIV_16))

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief BKP RTC WUT SW control.
 */
typedef enum {
    BKP_RTC_WUT_SW_CONTROL_SW_PWR_LOW  = (((uint32_t)0x0) << BKP_RTC_TAFCR_WAKE_SLEEP_Pos), /*!< SW_PWR = 0 (switch is open) when WUTF is asserted. */
    BKP_RTC_WUT_SW_CONTROL_SW_PWR_HIGH = (((uint32_t)0x1) << BKP_RTC_TAFCR_WAKE_SLEEP_Pos)  /*!< SW_PWR = 1 (switch is closed) when WUTF is asserted. */
} BKP_RTC_WUT_SWControl_TypeDef;

#define IS_BKP_RTC_WUT_SW_CONTROL(SW) (((SW) == BKP_RTC_WUT_SW_CONTROL_SW_PWR_LOW) || \
                                       ((SW) == BKP_RTC_WUT_SW_CONTROL_SW_PWR_HIGH))
#endif

/**
 * @brief BKP RTC clock source.
 */
typedef enum {
    BKP_RTC_CLK_SRC_LSI     = BKP_RTC_CR_RTC_SEL_LSI,     /*!< The LSI oscillator clock is selected as the RTC clock source. */
    BKP_RTC_CLK_SRC_LSE     = BKP_RTC_CR_RTC_SEL_LSE,     /*!< The LSE oscillator clock is selected as the RTC clock source. */
    BKP_RTC_CLK_SRC_HSI_RTC = BKP_RTC_CR_RTC_SEL_HSI_RTC, /*!< The HSI_RTC clock is selected as the RTC clock source. */
    BKP_RTC_CLK_SRC_HSE_RTC = BKP_RTC_CR_RTC_SEL_HSE_RTC  /*!< The HSE_RTC clock is selected as the RTC clock source. */
} BKP_RTC_ClockSource_TypeDef;

#define IS_BKP_RTC_CLOCK_SOURCE(CLK) (((CLK) == BKP_RTC_CLK_SRC_LSI) ||     \
                                      ((CLK) == BKP_RTC_CLK_SRC_LSE) ||     \
                                      ((CLK) == BKP_RTC_CLK_SRC_HSI_RTC) || \
                                      ((CLK) == BKP_RTC_CLK_SRC_HSE_RTC))

/**
 * @brief BKP RTC time format.
 */
typedef enum {
    BKP_RTC_FMT_24H = ((uint32_t)0x0), /*!< Specify the RTC 24 hour/day format. */
    BKP_RTC_FMT_12H = ((uint32_t)0x1)  /*!< Specify the RTC 12 hour (AM/PM) format. */
} BKP_RTC_FMT_TypeDef;

#define IS_BKP_RTC_TIME_FORMAT(FMT) (((FMT) == BKP_RTC_FMT_24H) || \
                                     ((FMT) == BKP_RTC_FMT_12H))

/**
 * @brief BKP RTC day of week.
 */
typedef enum {
    BKP_RTC_WEEKDAY_MONDAY    = ((uint32_t)0x1), /*!< Specify the RTC MONDAY. */
    BKP_RTC_WEEKDAY_TUESDAY   = ((uint32_t)0x2), /*!< Specify the RTC TUESDAY. */
    BKP_RTC_WEEKDAY_WEDNESDAY = ((uint32_t)0x3), /*!< Specify the RTC WEDNESDAY. */
    BKP_RTC_WEEKDAY_THURSDAY  = ((uint32_t)0x4), /*!< Specify the RTC THURSDAY. */
    BKP_RTC_WEEKDAY_FRIDAY    = ((uint32_t)0x5), /*!< Specify the RTC FRIDAY. */
    BKP_RTC_WEEKDAY_SATURDAY  = ((uint32_t)0x6), /*!< Specify the RTC SATURDAY. */
    BKP_RTC_WEEKDAY_SUNDAY    = ((uint32_t)0x7)  /*!< Specify the RTC SUNDAY. */
} BKP_RTC_WeekDays_TypeDef;

#define IS_BKP_RTC_WEEKDAY(WDU) ((((WDU) & ~(uint32_t)0x7) == 0) && \
                                 ((WDU) != 0))

/**
 * @brief BKP RTC alarm.
 */
typedef enum {
    BKP_RTC_ALARM_A = ((uint32_t)0x1), /*!< Specify the RTC alarm A. */
    BKP_RTC_ALARM_B = ((uint32_t)0x2)  /*!< Specify the RTC alarm B. */
} BKP_RTC_Alarm_TypeDef;

#define IS_BKP_RTC_ALARM(ALARM) (((ALARM) == BKP_RTC_ALARM_A) || \
                                 ((ALARM) == BKP_RTC_ALARM_B))

/**
 * @brief BKP RTC TAMPER.
 */
typedef enum {
#if defined(USE_MDR32F02_REV_1X)
    BKP_RTC_TAMPER_ALL = BKP_RTC_TAFCR_TAMP_EN /*!< Specify the all TAMPERs (WAKEUP3-WAKEUP1 inputs). */
#else
    BKP_RTC_TAMPER_1   = BKP_RTC_TAFCR_TAMP_EN_W1, /*!< Specify the TAMPER 1 (WAKEUP1 input). */
    BKP_RTC_TAMPER_2   = BKP_RTC_TAFCR_TAMP_EN_W2, /*!< Specify the TAMPER 2 (WAKEUP2 input). */
    BKP_RTC_TAMPER_3   = BKP_RTC_TAFCR_TAMP_EN_W3, /*!< Specify the TAMPER 3 (WAKEUP3 input). */
    BKP_RTC_TAMPER_ALL = BKP_RTC_TAFCR_TAMP_EN_W1 |
                         BKP_RTC_TAFCR_TAMP_EN_W2 |
                         BKP_RTC_TAFCR_TAMP_EN_W3 /*!< Specify the all TAMPERs (WAKEUP3-WAKEUP1 inputs). */
#endif
} BKP_RTC_TAMPER_TypeDef;

#if defined(USE_MDR32F02_REV_1X)
#define IS_BKP_RTC_TAMPER(TAMPS)  ((TAMPS) == BKP_RTC_TAMPER_ALL)

#define IS_BKP_RTC_TAMPERS(TAMPS) ((TAMPS) == BKP_RTC_TAMPER_ALL)
#else
#define IS_BKP_RTC_TAMPER(TAMPS) (((TAMPS) == BKP_RTC_TAMPER_1) || \
                                  ((TAMPS) == BKP_RTC_TAMPER_2) || \
                                  ((TAMPS) == BKP_RTC_TAMPER_3) || \
                                  ((TAMPS) == BKP_RTC_TAMPER_ALL))

#define IS_BKP_RTC_TAMPERS(TAMPS) (((TAMPS) & ~(uint32_t)(BKP_RTC_TAMPER_1 | \
                                                          BKP_RTC_TAMPER_2 | \
                                                          BKP_RTC_TAMPER_3 | \
                                                          BKP_RTC_TAMPER_ALL)) == 0)
#endif

/**
 * @brief BKP RTC TAMPER WAKEUPx inputs.
 */
typedef enum {
    BKP_RTC_TAMPER_W1 = ((uint32_t)0x1), /*!< Specify the TAMPER to capture event on WAKEUP1 input. */
    BKP_RTC_TAMPER_W2 = ((uint32_t)0x2), /*!< Specify the TAMPER to capture event on WAKEUP2 input. */
    BKP_RTC_TAMPER_W3 = ((uint32_t)0x4), /*!< Specify the TAMPER to capture event on WAKEUP3 input. */
} BKP_RTC_TAMPER_Wakeup_TypeDef;

#define IS_BKP_RTC_TAMPER_WAKEUPS(TAMP_WS) (((TAMP_WS) & ~(uint32_t)(BKP_RTC_TAMPER_W1 | \
                                                                     BKP_RTC_TAMPER_W2 | \
                                                                     BKP_RTC_TAMPER_W3)) == 0)

/**
 * @brief BKP RTC TAMPER WAKEUPx event.
 */
typedef enum {
    BKP_RTC_TAMPER_EVNT_EDGE_RISING_LEVEL_HIGH = (((uint32_t)0x0) << BKP_RTC_TAFCR_TAMP_TRG_Pos), /*!< Select the rising edge or high level to capture the TAMPER event. */
    BKP_RTC_TAMPER_EVNT_EDGE_FALLING_LEVEL_LOW = (((uint32_t)0x1) << BKP_RTC_TAFCR_TAMP_TRG_Pos), /*!< Select the falling edge or low level to capture the TAMPER event. */
#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    BKP_RTC_TAMPER_EVNT_LEVEL_HIGH   = (((uint32_t)0x0) << BKP_RTC_TAFCR_TAMP_TRG_Pos) | (((uint32_t)0x1) << BKP_RTC_TAFCR_TAMP_EDGE_W_Pos),  /*!< Select the high level to capture the TAMPER event. */
    BKP_RTC_TAMPER_EVNT_LEVEL_LOW    = (((uint32_t)0x1) << BKP_RTC_TAFCR_TAMP_TRG_Pos) | (((uint32_t)0x1) << BKP_RTC_TAFCR_TAMP_EDGE_W_Pos),  /*!< Select the low level to capture the TAMPER event. */
    BKP_RTC_TAMPER_EVNT_EDGE_RISING  = (((uint32_t)0x0) << BKP_RTC_TAFCR_TAMP_TRG_Pos) | (((uint32_t)0x1) << BKP_RTC_TAFCR_TAMP_LEVEL_W_Pos), /*!< Select the rising edge to capture the TAMPER event. */
    BKP_RTC_TAMPER_EVNT_EDGE_FALLING = (((uint32_t)0x1) << BKP_RTC_TAFCR_TAMP_TRG_Pos) | (((uint32_t)0x1) << BKP_RTC_TAFCR_TAMP_LEVEL_W_Pos)  /*!< Select the falling edge to capture the TAMPER event. */
#endif
} BKP_RTC_TAMPER_Event_TypeDef;

#if defined(USE_MDR32F02_REV_1X)
#define IS_BKP_RTC_TAMPER_EVENT(EVNT) (((EVNT) == BKP_RTC_TAMPER_EVNT_EDGE_RISING_LEVEL_HIGH) || \
                                       ((EVNT) == BKP_RTC_TAMPER_EVNT_EDGE_FALLING_LEVEL_LOW))
#else
#define IS_BKP_RTC_TAMPER_EVENT(EVNT) (((EVNT) == BKP_RTC_TAMPER_EVNT_EDGE_RISING_LEVEL_HIGH) || \
                                       ((EVNT) == BKP_RTC_TAMPER_EVNT_EDGE_FALLING_LEVEL_LOW) || \
                                       ((EVNT) == BKP_RTC_TAMPER_EVNT_LEVEL_HIGH) ||             \
                                       ((EVNT) == BKP_RTC_TAMPER_EVNT_LEVEL_LOW) ||              \
                                       ((EVNT) == BKP_RTC_TAMPER_EVNT_EDGE_RISING) ||            \
                                       ((EVNT) == BKP_RTC_TAMPER_EVNT_EDGE_FALLING))
#endif

/**
 * @brief BKP RTC TIMESTAMP WAKEUPx inputs.
 */
typedef enum {
    BKP_RTC_TIMESTAMP_W1 = ((uint32_t)0x1), /*!< Specify the TIMESTAMP to capture event on WAKEUP1 input. */
    BKP_RTC_TIMESTAMP_W2 = ((uint32_t)0x2), /*!< Specify the TIMESTAMP to capture event on WAKEUP2 input. */
    BKP_RTC_TIMESTAMP_W3 = ((uint32_t)0x4)  /*!< Specify the TIMESTAMP to capture event on WAKEUP3 input. */
} BKP_RTC_TIMESTAMP_Wakeup_TypeDef;

#define IS_BKP_RTC_TIMESTAMP_WAKEUP(TS_W) (((TS_W) == BKP_RTC_TIMESTAMP_W1) || \
                                           ((TS_W) == BKP_RTC_TIMESTAMP_W2) || \
                                           ((TS_W) == BKP_RTC_TIMESTAMP_W3))

#define IS_BKP_RTC_TIMESTAMP_WAKEUPS(TS_WS) (((TS_WS) & ~(uint32_t)(BKP_RTC_TIMESTAMP_W1 | \
                                                                    BKP_RTC_TIMESTAMP_W2 | \
                                                                    BKP_RTC_TIMESTAMP_W3)) == 0)

/**
 * @brief BKP RTC TIMESTAMP WAKEUPx event.
 */
typedef enum {
    BKP_RTC_TIMESTAMP_EVNT_EDGE_RISING  = (((uint32_t)0x0) << BKP_RTC_TAFCR_TS_EDGE_Pos), /*!< Select the rising edge to capture the TIMESTAMP event. */
    BKP_RTC_TIMESTAMP_EVNT_EDGE_FALLING = (((uint32_t)0x1) << BKP_RTC_TAFCR_TS_EDGE_Pos)  /*!< Select the falling edge to capture the TIMESTAMP event. */
} BKP_RTC_TIMESTAMP_Event_TypeDef;

#define IS_BKP_RTC_TIMESTAMP_EVENT(EVNT) (((EVNT) == BKP_RTC_TIMESTAMP_EVNT_EDGE_RISING) || \
                                          ((EVNT) == BKP_RTC_TIMESTAMP_EVNT_EDGE_FALLING))

/**
 * @brief BKP RTC interrupt definition.
 */
typedef enum {
    BKP_RTC_IT_SECF      = BKP_RTC_CS_SECF_IE,          /*!< RTC second event interrupt. */
    BKP_RTC_IT_ALARM_A   = BKP_RTC_CS_ALRAF_IE,         /*!< RTC alarm A event interrupt. */
    BKP_RTC_IT_ALARM_B   = BKP_RTC_CS_ALRBF_IE,         /*!< RTC alarm B event interrupt. */
    BKP_RTC_IT_WUTF      = BKP_RTC_CS_WUTF_IE,          /*!< WUT alarm event interrupt. */
    BKP_RTC_IT_OWF       = BKP_RTC_CS_OWF_IE,           /*!< WUT overflow event interrupt. */
    BKP_RTC_IT_TAMPER    = BKP_RTC_TAFCR_TAMP_IE << 16, /*!< TAMPER event interrupt. */
    BKP_RTC_IT_TIMESTAMP = BKP_RTC_TAFCR_TS_IE << 16    /*!< TIMESTAMP event interrupt. */
} BKP_RTC_IT_TypeDef;

#define IS_BKP_RTC_CONFIG_IT(IT) (((IT) == BKP_RTC_IT_SECF) ||    \
                                  ((IT) == BKP_RTC_IT_ALARM_A) || \
                                  ((IT) == BKP_RTC_IT_ALARM_B) || \
                                  ((IT) == BKP_RTC_IT_WUTF) ||    \
                                  ((IT) == BKP_RTC_IT_OWF) ||     \
                                  ((IT) == BKP_RTC_IT_TAMPER) ||  \
                                  ((IT) == BKP_RTC_IT_TIMESTAMP))

#define IS_BKP_RTC_CONFIG_ITS(ITS) (((ITS) & ~(uint32_t)(BKP_RTC_IT_SECF |    \
                                                         BKP_RTC_IT_ALARM_A | \
                                                         BKP_RTC_IT_ALARM_B | \
                                                         BKP_RTC_IT_WUTF |    \
                                                         BKP_RTC_IT_OWF |     \
                                                         BKP_RTC_IT_TAMPER |  \
                                                         BKP_RTC_IT_TIMESTAMP)) == 0)

/**
 * @brief BKP RTC flags.
 */
typedef enum {
    BKP_RTC_FLAG_SECF         = BKP_RTC_CS_SECF,            /*!< RTC second event flag. */
    BKP_RTC_FLAG_ALARM_A      = BKP_RTC_CS_ALRAF,           /*!< RTC alarm A event flag. */
    BKP_RTC_FLAG_ALARM_B      = BKP_RTC_CS_ALRBF,           /*!< RTC alarm B event flag. */
    BKP_RTC_FLAG_WUTF         = BKP_RTC_CS_WUTF,            /*!< WUT alarm event flag. */
    BKP_RTC_FLAG_OWF          = BKP_RTC_CS_OWF,             /*!< WUT overflow event flag. */
    BKP_RTC_FLAG_WEC          = BKP_RTC_CS_WEC,             /*!< RTC and WUT write operation flag. */
    BKP_RTC_FLAG_TAMPER       = BKP_LDO_TAMPF,              /*!< TAMPER event flag (WAKEUP3-WAKEUP1). */
    BKP_RTC_FLAG_TAMPER_W1    = BKP_RTC_TAFCR_TAMP_IN_SEL1, /*!< TAMPER WAKEUP1 event flag. */
    BKP_RTC_FLAG_TAMPER_W2    = BKP_RTC_TAFCR_TAMP_IN_SEL2, /*!< TAMPER WAKEUP2 event flag. */
    BKP_RTC_FLAG_TAMPER_W3    = BKP_RTC_TAFCR_TAMP_IN_SEL3, /*!< TAMPER WAKEUP3 event flag. */
    BKP_RTC_FLAG_TIMESTAMP    = BKP_RTC_CS_TSF,             /*!< TIMESTAMP event flag (WAKEUP3-WAKEUP1). */
    BKP_RTC_FLAG_TIMESTAMP_W1 = BKP_RTC_TAFCR_TS_IN_SEL1,   /*!< TIMESTAMP WAKEUP1 event flag. */
    BKP_RTC_FLAG_TIMESTAMP_W2 = BKP_RTC_TAFCR_TS_IN_SEL2,   /*!< TIMESTAMP WAKEUP2 event flag. */
    BKP_RTC_FLAG_TIMESTAMP_W3 = BKP_RTC_TAFCR_TS_IN_SEL3,   /*!< TIMESTAMP WAKEUP3 event flag. */
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    BKP_RTC_FLAG_TMPCAL_RESULTRDY = BKP_RTC_TMPCAL3_TEMP_RESULT_RDY /*!< TMPCAL result ready flag. */
#endif
} BKP_RTC_Flags_TypeDef;

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#define IS_BKP_RTC_FLAG(FLAG) (((FLAG) == BKP_RTC_FLAG_SECF) ||         \
                               ((FLAG) == BKP_RTC_FLAG_ALARM_A) ||      \
                               ((FLAG) == BKP_RTC_FLAG_ALARM_B) ||      \
                               ((FLAG) == BKP_RTC_FLAG_WUTF) ||         \
                               ((FLAG) == BKP_RTC_FLAG_OWF) ||          \
                               ((FLAG) == BKP_RTC_FLAG_WEC) ||          \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER) ||       \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER_W1) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER_W2) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER_W3) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W1) || \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W2) || \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W3) || \
                               ((FLAG) == BKP_RTC_FLAG_TMPCAL_RESULTRDY))
#else
#define IS_BKP_RTC_FLAG(FLAG) (((FLAG) == BKP_RTC_FLAG_SECF) ||         \
                               ((FLAG) == BKP_RTC_FLAG_ALARM_A) ||      \
                               ((FLAG) == BKP_RTC_FLAG_ALARM_B) ||      \
                               ((FLAG) == BKP_RTC_FLAG_WUTF) ||         \
                               ((FLAG) == BKP_RTC_FLAG_OWF) ||          \
                               ((FLAG) == BKP_RTC_FLAG_WEC) ||          \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER) ||       \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER_W1) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER_W2) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TAMPER_W3) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP) ||    \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W1) || \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W2) || \
                               ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W3))
#endif

#if defined(USE_MDR32F02_REV_1X)
#define IS_BKP_RTC_FLAG_CLR(FLAG) (((FLAG) == BKP_RTC_FLAG_SECF) ||    \
                                   ((FLAG) == BKP_RTC_FLAG_ALARM_A) || \
                                   ((FLAG) == BKP_RTC_FLAG_ALARM_B) || \
                                   ((FLAG) == BKP_RTC_FLAG_WUTF) ||    \
                                   ((FLAG) == BKP_RTC_FLAG_OWF) ||     \
                                   ((FLAG) == BKP_RTC_FLAG_TAMPER) ||  \
                                   ((FLAG) == BKP_RTC_FLAG_TIMESTAMP))

#define IS_BKP_RTC_FLAGS_CLR(FLAGS) (((FLAGS) & ~(uint32_t)(BKP_RTC_FLAG_SECF |    \
                                                            BKP_RTC_FLAG_ALARM_A | \
                                                            BKP_RTC_FLAG_ALARM_B | \
                                                            BKP_RTC_FLAG_WUTF |    \
                                                            BKP_RTC_FLAG_OWF |     \
                                                            BKP_RTC_FLAG_TAMPER |  \
                                                            BKP_RTC_FLAG_TIMESTAMP)) == 0)
#else
#define IS_BKP_RTC_FLAG_CLR(FLAG) (((FLAG) == BKP_RTC_FLAG_SECF) ||         \
                                   ((FLAG) == BKP_RTC_FLAG_ALARM_A) ||      \
                                   ((FLAG) == BKP_RTC_FLAG_ALARM_B) ||      \
                                   ((FLAG) == BKP_RTC_FLAG_WUTF) ||         \
                                   ((FLAG) == BKP_RTC_FLAG_OWF) ||          \
                                   ((FLAG) == BKP_RTC_FLAG_TAMPER) ||       \
                                   ((FLAG) == BKP_RTC_FLAG_TAMPER_W1) ||    \
                                   ((FLAG) == BKP_RTC_FLAG_TAMPER_W2) ||    \
                                   ((FLAG) == BKP_RTC_FLAG_TAMPER_W3) ||    \
                                   ((FLAG) == BKP_RTC_FLAG_TIMESTAMP) ||    \
                                   ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W1) || \
                                   ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W2) || \
                                   ((FLAG) == BKP_RTC_FLAG_TIMESTAMP_W3))

#define IS_BKP_RTC_FLAGS_CLR(FLAGS) (((FLAGS) & ~(uint32_t)(BKP_RTC_FLAG_SECF |         \
                                                            BKP_RTC_FLAG_ALARM_A |      \
                                                            BKP_RTC_FLAG_ALARM_B |      \
                                                            BKP_RTC_FLAG_WUTF |         \
                                                            BKP_RTC_FLAG_OWF |          \
                                                            BKP_RTC_FLAG_TAMPER |       \
                                                            BKP_RTC_FLAG_TAMPER_W1 |    \
                                                            BKP_RTC_FLAG_TAMPER_W2 |    \
                                                            BKP_RTC_FLAG_TAMPER_W3 |    \
                                                            BKP_RTC_FLAG_TIMESTAMP |    \
                                                            BKP_RTC_FLAG_TIMESTAMP_W1 | \
                                                            BKP_RTC_FLAG_TIMESTAMP_W2 | \
                                                            BKP_RTC_FLAG_TIMESTAMP_W3)) == 0)
#endif

/**
 * @brief BKP RTC date and time structure.
 *        Data can be stored in BIN or BCD format, use BKP_ConvertToXX() functions to convert one format to the other.
 */
typedef struct {
    uint8_t                  RTC_Year;    /*!< Year (0-99) in binary or BCD format. */
    uint8_t                  RTC_Month;   /*!< Months (1-12) in binary or BCD format. */
    uint8_t                  RTC_Day;     /*!< Days (1-31) in binary or BCD format. */
    BKP_RTC_WeekDays_TypeDef RTC_WeekDay; /*!< A day of the week.
                                               This parameter is a value of the @ref BKP_RTC_WeekDays_TypeDef. */
    BKP_RTC_FMT_TypeDef RTC_TimeFormat;   /*!< Select 24h or 12h time format.
                                               This parameter is a value of the @ref BKP_RTC_FMT_TypeDef. */
    uint8_t RTC_Hours;                    /*!< Hours in binary or BCD format. */
    uint8_t RTC_Minutes;                  /*!< Minutes in binary or BCD format. */
    uint8_t RTC_Seconds;                  /*!< Seconds in binary or BCD format. */
} BKP_RTC_DateTime_TypeDef;

/**
 * @brief BKP RTC alarm structure.
 */
typedef struct {
    FunctionalState RTC_IgnoreDate;            /*!< The date is ignored.
                                                    This parameter is a value of the @ref FunctionalState. */
    FunctionalState RTC_UseWeekDayInsteadDays; /*!< A weekday is used instead of days (days must be ignored).
                                                    This parameter is a value of the @ref FunctionalState. */
    BKP_RTC_WeekDays_TypeDef RTC_WeekDay;      /*!< A day of the week.
                                                    This parameter is a value of the @ref BKP_RTC_WeekDays_TypeDef.
                                                    If @ref RTC_UseWeekDayInsteadDays == ENABLE, this field is used, the @ref RTC_Day is ignored. */
    uint8_t RTC_Day;                           /*!< Days (1-31) in binary or BCD format.
                                                    If @ref RTC_UseWeekDayInsteadDays == DISABLE, this field is used, the @ref RTC_WeekDay is ignored. */
    uint8_t         RTC_Hours;                 /*!< Hours in binary or BCD format. */
    uint8_t         RTC_Minutes;               /*!< Minutes in binary or BCD format. */
    uint8_t         RTC_Seconds;               /*!< Seconds in binary or BCD format. */
    FunctionalState RTC_IgnoreHours;           /*!< Hours are ignored.
                                                    This parameter is a value of the @ref FunctionalState. */
    BKP_RTC_FMT_TypeDef RTC_TimeFormat;        /*!< Select 24h or 12h time format.
                                                    This parameter is a value of the @ref BKP_RTC_FMT_TypeDef. */
    FunctionalState RTC_IgnoreMinutes;         /*!< Minutes are ignored.
                                                    This parameter is a value of the @ref FunctionalState. */
    FunctionalState RTC_IgnoreSeconds;         /*!< Seconds are ignored.
                                                    This parameter is a value of the @ref FunctionalState. */
} BKP_RTC_AlarmDateTime_TypeDef;

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/**
 * @brief BKP RTC LSE calibration constants for temperature compensation structure.
 */
typedef struct {
    uint8_t Const[16];
} BKP_RTC_TMPCAL_Calibration_TypeDef;

#define IS_BKP_RTC_TMPCAL_CALIBRATION(CAL) (((CAL) & ~(BKP_RTC_TMPCAL1_CONST0_Msk >> BKP_RTC_TMPCAL1_CONST0_Pos)) == 0)
#endif

/** @} */ /* End of the group BKP_Exported_Types */

/** @defgroup BKP_Exported_Defines BKP Exported Defines
 * @{
 */

/**
 * @brief Convert BCD format to BIN format.
 */
#define CONVERT_BCD_TO_BIN(BCD) (uint8_t)(((((uint8_t)(BCD) & 0xF0) >> 4) * 10) + ((uint8_t)(BCD) & 0x0F))

/**
 * @brief Convert BIN format to BCD format.
 */
#define CONVERT_BIN_TO_BCD(BIN) (uint8_t)(((((uint8_t)(BIN) / 10) % 10) << 4) + ((uint8_t)(BIN) % 10))

/**
 * @brief BKP LDO boost.
 */
#define IS_BKP_LDO_BOOST(BOOST) (((BOOST) & ~(BKP_LDO_LDO_BOOST_Msk >> BKP_LDO_LDO_BOOST_Pos)) == 0)

/**
 * @brief BKP MCU mode.
 */
#define IS_BKP_MODE(MODE) (((MODE) & ~(BKP_LDO_MODE_Msk >> BKP_LDO_MODE_Pos)) == 0)

/**
 * @brief BKP LSE configuration.
 */
#define IS_BKP_LSE_CONF(CONF) (((CONF) & ~(BKP_CLK_LSE_CONF_Msk >> BKP_CLK_LSE_CONF_Pos)) == 0)

/**
 * @brief BKP HSI and LSI trimming.
 */
#define IS_BKP_HSI_LSI_TRIM_VALUE(TRIM) (((TRIM) & ~(BKP_CLK_HSI_LSI_TRIM_Msk >> BKP_CLK_HSI_LSI_TRIM_Pos)) == 0)

/**
 * @brief BKP RTC prescaler counter value.
 */
#define IS_BKP_RTC_PRESCALER_COUNTER_VALUE(VAL) (((VAL) & ~BKP_RTC_PREDIV_S_RTC_DIV_Msk) == 0)

/**
 * @brief BKP RTC prescaler value.
 */
#define IS_BKP_RTC_PRESCALER_VALUE(VAL) (((VAL) & ~BKP_RTC_PRL_RTC_PRL_Msk) == 0)

/**
 * @brief BKP RTC BCD years.
 */
#define IS_BKP_RTC_BCD_YEARS(YEAR) ((((YEAR) & (uint8_t)0xF) <= 9) && (((YEAR) & (uint8_t)0xF0) <= 0x90))

/**
 * @brief BKP RTC BIN years.
 */
#define IS_BKP_RTC_BIN_YEARS(YEAR) (((YEAR) >= 2000) && ((YEAR) <= 2099))

/**
 * @brief BKP RTC BCD month.
 */
#define IS_BKP_RTC_BCD_MONTH(MONTH) ((((MONTH) & (uint8_t)0xF) <= 9) && \
                                     (((MONTH) >= 0x01) && ((MONTH) <= 0x12)))

/**
 * @brief BKP RTC BIN month.
 */
#define IS_BKP_RTC_BIN_MONTH(MONTH) (((MONTH) >= 1) && ((MONTH) <= 12))

/**
 * @brief BKP RTC BCD days.
 */
#define IS_BKP_RTC_BCD_DAY(DAY) ((((DAY) & (uint8_t)0xF) <= 9) && \
                                 (((DAY) >= 0x01) && ((DAY) <= 0x31)))

/**
 * @brief BKP RTC BIN days.
 */
#define IS_BKP_RTC_BIN_DAY(DAY) (((DAY) >= 1) && ((DAY) <= 31))

/**
 * @brief BKP RTC BCD hours.
 */
#define IS_BKP_RTC_BCD_HOUR(HR) ((((HR) & (uint8_t)0xF) <= 9) && ((HR) <= 0x23))

/**
 * @brief BKP RTC BIN hours.
 */
#define IS_BKP_RTC_BIN_HOUR(HR) (((HR) <= 23))

/**
 * @brief BKP RTC BCD PM flag.
 */
#define IS_BKP_RTC_BCD_PM_HOUR(HR) ((((HR) & (uint8_t)0xF) <= 9) && \
                                    (((HR) >= 0x01) && ((HR) <= 0x12)))

/**
 * @brief BKP RTC BIN PM flag.
 */
#define IS_BKP_RTC_BIN_PM_HOUR(HR) (((HR) >= 1) && ((HR) <= 12))

/**
 * @brief BKP RTC BCD minutes or seconds.
 */
#define IS_BKP_RTC_BCD_MIN_SECS(MS) ((((MS) & (uint8_t)0xF) <= 9) && ((MS) <= 0x59))

/**
 * @brief BKP RTC BIN minutes or seconds.
 */
#define IS_BKP_RTC_BIN_MIN_SECS(MS) ((MS) <= 59)

/** @} */ /* End of the group BKP_Exported_Defines */

/** @addtogroup BKP_Exported_Functions BKP Exported Functions
 * @{
 */

/** @addtogroup BKP_Common_Control_Functions BKP Common Control Functions
 * @{
 */

void       BKP_SetRegistersLock(FlagStatus LockState);
FlagStatus BKP_GetRegistersLock(void);

void BKP_DeInit(uint32_t Subblocks);

/** @} */ /* End of the group BKP_Common_Control_Functions */

/** @addtogroup BKP_Control_Functions BKP Control Functions
 * @{
 */

void            BKP_JTAG_Cmd(FunctionalState NewState);
FunctionalState BKP_JTAG_GetCmdState(void);

FlagStatus BKP_GetWAKEUPStatus(BKP_WAKEUP_TypeDef Wakeup);

void    BKP_LDO_SetBoostTrim(uint8_t LDO_Boost);
uint8_t BKP_LDO_GetBoostTrim(void);

void                   BKP_BLDO_SetBoostTrim(BKP_BLDO_Boost_TypeDef BLDO_Boost);
BKP_BLDO_Boost_TypeDef BKP_BLDO_GetBoostTrim(void);

/** @} */ /* End of the group BKP_Control_Functions */

/** @addtogroup BKP_Software_Functions BKP Software Functions
 * @{
 */

void       BKP_SetFlagPOR(FlagStatus PORFlag);
FlagStatus BKP_GetFlagPOR(void);

void    BKP_SetMODE(uint8_t Mode);
uint8_t BKP_GetMODE(void);

/** @} */ /* End of the group BKP_Software_Functions */

/** @addtogroup BKP_Emergency_Power_Supply_Control_Functions BKP Emergency Power Supply Control Functions
 * @{
 */

void            BKP_SW_Cmd(FunctionalState NewState);
FunctionalState BKP_SW_GetCmdState(void);

void       BKP_SW_DisablePower(void);
FlagStatus BKP_SW_GetPowerStatus(void);

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void                    BKP_SW_SetPolarity(BKP_SW_Polarity_TypeDef Polarity);
BKP_SW_Polarity_TypeDef BKP_SW_GetPolarity(void);
#endif

/** @} */ /* End of the group BKP_Emergency_Power_Supply_Control_Functions */

/** @addtogroup BKP_Clock_Source_Control_Functions BKP Clock Source Control Functions
 * @{
 */

void            BKP_HSI_Cmd(FunctionalState NewState);
FunctionalState BKP_HSI_GetCmdState(void);
void            BKP_HSI_LSI_SetTrim(uint8_t TrimValue);
uint8_t         BKP_HSI_LSI_GetTrim(void);
ErrorStatus     BKP_HSI_GetStatus(void);

void            BKP_LSI_Cmd(FunctionalState NewState);
FunctionalState BKP_LSI_GetCmdState(void);
ErrorStatus     BKP_LSI_GetStatus(void);

void                 BKP_LSE_Cmd(FunctionalState NewState);
void                 BKP_LSE_Config(BKP_LSE_Mode_TypeDef LSEMode);
BKP_LSE_Mode_TypeDef BKP_LSE_GetModeConfig(void);
ErrorStatus          BKP_LSE_GetStatus(void);
void                 BKP_LSE_SetWorkConfig(uint8_t LSEConf);

FlagStatus BKP_CLK_GetFlagStatus(BKP_CLK_Flags_TypeDef Flag);

/** @} */ /* End of the group BKP_Clock_Source_Control_Functions */

/** @addtogroup BKP_RTC_Control_Functions BKP RTC Control Functions
 * @{
 */

void            BKP_RTC_Reset(FunctionalState NewState);
void            BKP_RTC_Cmd(FunctionalState NewState);
FunctionalState BKP_RTC_GetCmdState(void);

void BKP_RTC_WaitForUpdate(void);

void                        BKP_RTC_SetClkSource(BKP_RTC_ClockSource_TypeDef ClockSource);
BKP_RTC_ClockSource_TypeDef BKP_RTC_GetClkSource(void);
void                        BKP_RTC_WaitClkSwitch(BKP_RTC_ClockSource_TypeDef ClockSource);

void    BKP_RTC_SetClkCalibration(uint8_t Calibration);
uint8_t BKP_RTC_GetClkCalibration(void);

void     BKP_RTC_SetPrescalerCounter(uint32_t PrescalerCounterValue);
uint32_t BKP_RTC_GetPrescalerCounter(void);

void     BKP_RTC_SetPrescaler(uint32_t PrescalerValue);
uint32_t BKP_RTC_GetPrescaler(void);

void BKP_RTC_SetDateTimeBCD(const BKP_RTC_DateTime_TypeDef* RTC_DateTime, BitStatus SetDate, BitStatus SetTime);
void BKP_RTC_GetDateTimeBCD(BKP_RTC_DateTime_TypeDef* RTC_DateTime);

void BKP_RTC_SetAlarmBCD(BKP_RTC_Alarm_TypeDef RTC_Alarm, const BKP_RTC_AlarmDateTime_TypeDef* RTC_AlarmDateTime);
void BKP_RTC_GetAlarmBCD(BKP_RTC_Alarm_TypeDef RTC_Alarm, BKP_RTC_AlarmDateTime_TypeDef* RTC_AlarmDateTime);

/** @addtogroup BKP_RTC_WUT_Control_Functions BKP RTC WUT Control Functions
 * @{
 */

void                            BKP_RTC_WUT_SetClkSource(BKP_RTC_WUT_ClockSource_TypeDef ClockSource);
BKP_RTC_WUT_ClockSource_TypeDef BKP_RTC_WUT_GetClkSource(void);

void     BKP_RTC_WUT_SetCounter(uint32_t CounterValue);
uint32_t BKP_RTC_WUT_GetCounter(void);

void     BKP_RTC_WUT_SetAlarm(uint32_t AlarmValue);
uint32_t BKP_RTC_WUT_GetAlarm(void);

#if defined(USE_MDR32F02_REV_2) || defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
void                          BKP_RTC_WUT_SetSWControl(BKP_RTC_WUT_SWControl_TypeDef SWControl);
BKP_RTC_WUT_SWControl_TypeDef BKP_RTC_WUT_GetSWControl(void);
#endif

/** @} */ /* End of the group BKP_RTC_WUT_Control_Functions */

/** @addtogroup BKP_RTC_Event_Detection_Control_Functions BKP RTC Event Detection Control Functions
 * @{
 */

void            BKP_RTC_TAMPER_Cmd(uint32_t Tampers, FunctionalState NewState);
FunctionalState BKP_RTC_TAMPER_GetCmdState(BKP_RTC_TAMPER_TypeDef Tampers);
void            BKP_RTC_TAMPER_SetEvent(uint32_t Wakeups, BKP_RTC_TAMPER_Event_TypeDef Event);

void            BKP_RTC_TIMESTAMP_Cmd(FunctionalState NewState);
FunctionalState BKP_RTC_TIMESTAMP_GetCmdState(void);
void            BKP_RTC_TIMESTAMP_SetEvent(uint32_t Wakeups, BKP_RTC_TIMESTAMP_Event_TypeDef Event);
void            BKP_RTC_TIMESTAMP_GetDateTimeBCD(BKP_RTC_TIMESTAMP_Wakeup_TypeDef Wakeup, BKP_RTC_DateTime_TypeDef* RTC_DateTime);

/** @} */ /* End of the group BKP_RTC_Event_Detection_Control_Functions */

#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
/** @addtogroup BKP_RTC_TMPCAL_Control_Functions BKP RTC TMPCAL Control Functions
 * @{
 */

void            BKP_RTC_TMPCAL_Cmd(FunctionalState NewState);
FunctionalState BKP_RTC_TMPCAL_GetCmdState(void);

void BKP_RTC_TMPCAL_SetCalibration(const BKP_RTC_TMPCAL_Calibration_TypeDef* TMPCAL_Calibration);
void BKP_RTC_TMPCAL_GetCalibration(BKP_RTC_TMPCAL_Calibration_TypeDef* TMPCAL_Calibration);

uint8_t BKP_RTC_TMPCAL_GetResult(void);

/** @} */ /* End of the group BKP_RTC_TMPCAL_Control_Functions */
#endif

void BKP_RTC_ConvertToBINFormat(BKP_RTC_DateTime_TypeDef* RTC_DateTime);
void BKP_RTC_ConvertToBCDFormat(BKP_RTC_DateTime_TypeDef* RTC_DateTime);

void       BKP_RTC_ClearFlags(uint32_t Flags);
FlagStatus BKP_RTC_GetFlagStatus(BKP_RTC_Flags_TypeDef Flag);
uint32_t   BKP_RTC_GetStatus(void);

void BKP_RTC_ITConfig(uint32_t ITs, FunctionalState NewState);

/** @} */ /* End of the group BKP_RTC_Control_Functions */

/** @} */ /* End of the group BKP_Exported_Functions */

/** @} */ /* End of the group BKP */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_BKP_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_bkp.h */

