/**
 ******************************************************************************
 * @file    MDR32F21QI.h
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    26/05/2023
 * @brief   CMSIS Device Peripheral Access Layer Header File for MDR32F21QI.
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
#ifndef __MDR32F21QI_H
#define __MDR32F21QI_H

/** @addtogroup CMSIS CMSIS
 * @{
 */

/** @addtogroup MDR32F21QI MDR32F21QI
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__CC_ARM)
#pragma anon_unions
#endif

/** @defgroup MDR32F21QI_Configuration_of_CMSIS MDR32F21QI Configuration of CMSIS
 * @{
 */

#define __CM0_REV              0U /*!< Core Revision */
#define __NVIC_PRIO_BITS       2U /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig 0U /*!< Set to 1 if different SysTick Config is used */

/** @} */ /* End of group MDR32F21QI_Configuration_of_CMSIS */

/** @defgroup MDR32F21QI_Peripheral MDR32F21QI Peripheral
 * @{
 */

/**
 * @brief MDR32F21QI Interrupt Number Definition
 */
typedef enum IRQn {
    /* ARM Cortex-M0 Specific Interrupt Numbers */
    Reset_IRQn          = -15, /*!< -15 Reset Vector, invoked on Power up and warm reset */
    NonMaskableInt_IRQn = -14, /*!< -14 Non maskable Interrupt, cannot be stopped or preempted */
    HardFault_IRQn      = -13, /*!< -13 Hard Fault, all classes of Fault */
    SVCall_IRQn         = -5,  /*!< -5 System Service Call via SVC instruction */
    PendSV_IRQn         = -2,  /*!< -2 Pendable request for system service */
    SysTick_IRQn        = -1,  /*!< -1 System Tick Timer */
    /* MDR32F21QI Specific Interrupt Numbers */
    DMA_IRQn      = 0,  /*!< DMA Interrupt */
    UART0_IRQn    = 1,  /*!< UART0 Interrupt */
    UART1_IRQn    = 2,  /*!< UART1 Interrupt */
    SSP_IRQn      = 3,  /*!< SSP Interrupt */
    POWER_IRQn    = 4,  /*!< POWER Interrupt */
    WWDG_IRQn     = 5,  /*!< WWDG Interrupt */
    TIMER0_IRQn   = 6,  /*!< TIMER0 Interrupt */
    TIMER1_IRQn   = 7,  /*!< TIMER1 Interrupt */
    ADC_IRQn      = 8,  /*!< ADC Interrupt */
    BKP_RTC_IRQn  = 10, /*!< BKP RTC Interrupt */
    EXT1_IRQn     = 11, /*!< EXT_INT1 Interrupt */
    EXT2_IRQn     = 12, /*!< EXT_INT2 Interrupt */
    EXT3_IRQn     = 13, /*!< EXT_INT3 Interrupt */
    ADCUI_F0_IRQn = 14, /*!< ADCUI_F0 Interrupt */
    ADCUI_F1_IRQn = 15, /*!< ADCUI_F1 Interrupt */
    ADCUI_F2_IRQn = 16  /*!< ADCUI_F2 Interrupt */
} IRQn_Type;

/* Includes ------------------------------------------------------------------*/
#include "core_cm0.h"
#include "system_MDR32F21QI.h"
#include <stdint.h>

/** @defgroup MDR32F21QI_Peripheral_Exported_types MDR32F21QI Peripheral Exported types
  * @{
  */
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus;

#define IS_BIT_STATUS(STATUS)       (((STATUS) == RESET) || ((STATUS) == SET))

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE)  (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/** @} */ /* End of group MDR32F21QI_Peripheral_Exported_types */

/** @defgroup MDR32F21QI_Peripheral_Units MDR32F21QI Peripheral Units
 * @{
 */

/** @defgroup MDR32F21QI_SSP MDR_SSP
 * @{
 */

/**
 * @brief MDR32F21QI SSP control structure
 */
typedef struct {
    __IO uint32_t CR0;   /*!<SSP Control0 Register */
    __IO uint32_t CR1;   /*!<SSP Control1 Register */
    __IO uint32_t DR;    /*!<SSP Data Register */
    __IO uint32_t SR;    /*!<SSP Status Register */
    __IO uint32_t CPSR;  /*!<SSP Clock Prescaler Register */
    __IO uint32_t IMSC;  /*!<SSP Interrupt Mask Register */
    __IO uint32_t RIS;   /*!<SSP Interrupt Pending Register */
    __IO uint32_t MIS;   /*!<SSP Masked Interrupt Pending Register */
    __IO uint32_t ICR;   /*!<SSP Interrupt Clear Register */
    __IO uint32_t DMACR; /*!<SSP DMA Control Register */
} MDR_SSP_TypeDef;

/** @defgroup MDR32F21QI_SSP_Defines SSP Defines
 * @{
 */

/** @defgroup MDR32F21QI_SSP_CR0 SSP_CR0
 * @{
 */

#define SSP_CR0_DSS_Pos       0
#define SSP_CR0_DSS_Msk       (0xFUL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_4BIT      (0x3UL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_5BIT      (0x4UL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_6BIT      (0x5UL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_7BIT      (0x6UL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_8BIT      (0x7UL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_9BIT      (0x8UL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_10BIT     (0x9UL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_11BIT     (0xAUL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_12BIT     (0xBUL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_13BIT     (0xCUL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_14BIT     (0xDUL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_15BIT     (0xEUL << SSP_CR0_DSS_Pos)
#define SSP_CR0_DSS_16BIT     (0xFUL << SSP_CR0_DSS_Pos)

#define SSP_CR0_FRF_Pos       4
#define SSP_CR0_FRF_Msk       (0x3UL << SSP_CR0_FRF_Pos)
#define SSP_CR0_FRF_SPI       (0x0UL << SSP_CR0_FRF_Pos)
#define SSP_CR0_FRF_SSI       (0x1UL << SSP_CR0_FRF_Pos)
#define SSP_CR0_FRF_MICROWIRE (0x2UL << SSP_CR0_FRF_Pos)

#define SSP_CR0_SPO_Pos       6
#define SSP_CR0_SPO_Msk       (0x1UL << SSP_CR0_SPO_Pos)
#define SSP_CR0_SPO           SSP_CR0_SPO_Msk

#define SSP_CR0_SPH_Pos       7
#define SSP_CR0_SPH_Msk       (0x1UL << SSP_CR0_SPH_Pos)
#define SSP_CR0_SPH           SSP_CR0_SPH_Msk

#define SSP_CR0_SCR_Pos       8
#define SSP_CR0_SCR_Msk       (0xFFUL << SSP_CR0_SCR_Pos)

/** @} */ /* End of group MDR32F21QI_SSP_CR0 */

/** @defgroup MDR32F21QI_SSP_CR1 SSP_CR1
 * @{
 */

#define SSP_CR1_LBM_Pos 0
#define SSP_CR1_LBM_Msk (0x1UL << SSP_CR1_LBM_Pos)
#define SSP_CR1_LBM     SSP_CR1_LBM_Msk

#define SSP_CR1_SSE_Pos 1
#define SSP_CR1_SSE_Msk (0x1UL << SSP_CR1_SSE_Pos)
#define SSP_CR1_SSE     SSP_CR1_SSE_Msk

#define SSP_CR1_MS_Pos  2
#define SSP_CR1_MS_Msk  (0x1UL << SSP_CR1_MS_Pos)
#define SSP_CR1_MS      SSP_CR1_MS_Msk

#define SSP_CR1_SOD_Pos 3
#define SSP_CR1_SOD_Msk (0x1UL << SSP_CR1_SOD_Pos)
#define SSP_CR1_SOD     SSP_CR1_SOD_Msk

/** @} */ /* End of group MDR32F21QI_SSP_CR1 */

/** @defgroup MDR32F21QI_SSP_DR SSP_DR
 * @{
 */

#define SSP_DR_DATA_Pos 0
#define SSP_DR_DATA_Msk (0xFFFFUL << SSP_DR_DATA_Pos)

/** @} */ /* End of group MDR32F21QI_SSP_DR */

/** @defgroup MDR32F21QI_SSP_SR SSP_SR
 * @{
 */

#define SSP_SR_TFE_Pos 0
#define SSP_SR_TFE_Msk (0x1UL << SSP_SR_TFE_Pos)
#define SSP_SR_TFE     SSP_SR_TFE_Msk

#define SSP_SR_TNF_Pos 1
#define SSP_SR_TNF_Msk (0x1UL << SSP_SR_TNF_Pos)
#define SSP_SR_TNF     SSP_SR_TNF_Msk

#define SSP_SR_RNE_Pos 2
#define SSP_SR_RNE_Msk (0x1UL << SSP_SR_RNE_Pos)
#define SSP_SR_RNE     SSP_SR_RNE_Msk

#define SSP_SR_RFF_Pos 3
#define SSP_SR_RFF_Msk (0x1UL << SSP_SR_RFF_Pos)
#define SSP_SR_RFF     SSP_SR_RFF_Msk

#define SSP_SR_BSY_Pos 4
#define SSP_SR_BSY_Msk (0x1UL << SSP_SR_BSY_Pos)
#define SSP_SR_BSY     SSP_SR_BSY_Msk

/** @} */ /* End of group MDR32F21QI_SSP_SR */

/** @defgroup MDR32F21QI_SSP_CPSR SSP_CPSR
 * @{
 */

#define SSP_CPSR_CPSDVSR_Pos 0
#define SSP_CPSR_CPSDVSR_Msk (0xFFUL << SSP_CPSR_CPSDVSR_Pos)

/** @} */ /* End of group MDR32F21QI_SSP_CPSR */

/** @defgroup MDR32F21QI_SSP_IMSC SSP_IMSC
 * @{
 */

#define SSP_IMSC_RORIM_Pos 0
#define SSP_IMSC_RORIM_Msk (0x1UL << SSP_IMSC_RORIM_Pos)
#define SSP_IMSC_RORIM     SSP_IMSC_RORIM_Msk

#define SSP_IMSC_RTIM_Pos  1
#define SSP_IMSC_RTIM_Msk  (0x1UL << SSP_IMSC_RTIM_Pos)
#define SSP_IMSC_RTIM      SSP_IMSC_RTIM_Msk

#define SSP_IMSC_RXIM_Pos  2
#define SSP_IMSC_RXIM_Msk  (0x1UL << SSP_IMSC_RXIM_Pos)
#define SSP_IMSC_RXIM      SSP_IMSC_RXIM_Msk

#define SSP_IMSC_TXIM_Pos  3
#define SSP_IMSC_TXIM_Msk  (0x1UL << SSP_IMSC_TXIM_Pos)
#define SSP_IMSC_TXIM      SSP_IMSC_TXIM_Msk

/** @} */ /* End of group MDR32F21QI_SSP_IMSC */

/** @defgroup MDR32F21QI_SSP_RIS SSP_RIS
 * @{
 */

#define SSP_RIS_RORRIS_Pos 0
#define SSP_RIS_RORRIS_Msk (0x1UL << SSP_RIS_RORRIS_Pos)
#define SSP_RIS_RORRIS     SSP_RIS_RORRIS_Msk

#define SSP_RIS_RTRIS_Pos  1
#define SSP_RIS_RTRIS_Msk  (0x1UL << SSP_RIS_RTRIS_Pos)
#define SSP_RIS_RTRIS      SSP_RIS_RTRIS_Msk

#define SSP_RIS_RXRIS_Pos  2
#define SSP_RIS_RXRIS_Msk  (0x1UL << SSP_RIS_RXRIS_Pos)
#define SSP_RIS_RXRIS      SSP_RIS_RXRIS_Msk

#define SSP_RIS_TXRIS_Pos  3
#define SSP_RIS_TXRIS_Msk  (0x1UL << SSP_RIS_TXRIS_Pos)
#define SSP_RIS_TXRIS      SSP_RIS_TXRIS_Msk

/** @} */ /* End of group MDR32F21QI_SSP_RIS */

/** @defgroup MDR32F21QI_SSP_MIS SSP_MIS
 * @{
 */

#define SSP_MIS_RORMIS_Pos 0
#define SSP_MIS_RORMIS_Msk (0x1UL << SSP_MIS_RORMIS_Pos)
#define SSP_MIS_RORMIS     SSP_MIS_RORMIS_Msk

#define SSP_MIS_RTMIS_Pos  1
#define SSP_MIS_RTMIS_Msk  (0x1UL << SSP_MIS_RTMIS_Pos)
#define SSP_MIS_RTMIS      SSP_MIS_RTMIS_Msk

#define SSP_MIS_RXMIS_Pos  2
#define SSP_MIS_RXMIS_Msk  (0x1UL << SSP_MIS_RXMIS_Pos)
#define SSP_MIS_RXMIS      SSP_MIS_RXMIS_Msk

#define SSP_MIS_TXMIS_Pos  3
#define SSP_MIS_TXMIS_Msk  (0x1UL << SSP_MIS_TXMIS_Pos)
#define SSP_MIS_TXMIS      SSP_MIS_TXMIS_Msk

/** @} */ /* End of group MDR32F21QI_SSP_MIS */

/** @defgroup MDR32F21QI_SSP_ICR SSP_ICR
 * @{
 */

#define SSP_ICR_RORIC_Pos 0
#define SSP_ICR_RORIC_Msk (0x1UL << SSP_ICR_RORIC_Pos)
#define SSP_ICR_RORIC     SSP_ICR_RORIC_Msk

#define SSP_ICR_RTIC_Pos  1
#define SSP_ICR_RTIC_Msk  (0x1UL << SSP_ICR_RTIC_Pos)
#define SSP_ICR_RTIC      SSP_ICR_RTIC_Msk

/** @} */ /* End of group MDR32F21QI_SSP_ICR */

/** @defgroup MDR32F21QI_SSP_DMACR SSP_DMACR
 * @{
 */

#define SSP_DMACR_RXDMAE_Pos 0
#define SSP_DMACR_RXDMAE_Msk (0x1UL << SSP_DMACR_RXDMAE_Pos)
#define SSP_DMACR_RXDMAE     SSP_DMACR_RXDMAE_Msk

#define SSP_DMACR_TXDMAE_Pos 1
#define SSP_DMACR_TXDMAE_Msk (0x1UL << SSP_DMACR_TXDMAE_Pos)
#define SSP_DMACR_TXDMAE     SSP_DMACR_TXDMAE_Msk

/** @} */ /* End of group MDR32F21QI_SSP_DMACR */

/** @} */ /* End of group MDR32F21QI_SSP_Defines */

/** @} */ /* End of group MDR32F21QI_SSP */

/** @defgroup MDR32F21QI_UART MDR_UART
 * @{
 */

/**
 * @brief MDR32F21QI UART control structure
 */
typedef struct {
    __IO uint32_t DR;      /*!<UART Data Register */
    __IO uint32_t RSR_ECR; /*!<UART Receive Status Register / Error Clear Register */
    __I uint32_t  RESERVED0[4];
    __IO uint32_t FR;      /*!<UART Flag Register */
    __I uint32_t  RESERVED1;
    __IO uint32_t ILPR;    /*!<UART IrDA Low-Power Counter Register */
    __IO uint32_t IBRD;    /*!<UART Integer Baud Rate Register */
    __IO uint32_t FBRD;    /*!<UART Fractional Baud Rate Register */
    __IO uint32_t LCR_H;   /*!<UART Line Control Register */
    __IO uint32_t CR;      /*!<UART Control Register */
    __IO uint32_t IFLS;    /*!<UART Interrupt FIFO Level Select Register */
    __IO uint32_t IMSC;    /*!<UART Interrupt Mask Set/Clear Register */
    __IO uint32_t RIS;     /*!<UART Raw Interrupt Status Register */
    __IO uint32_t MIS;     /*!<UART Masked Interrupt Status Register */
    __IO uint32_t ICR;     /*!<UART Interrupt Clear Register */
    __IO uint32_t DMACR;   /*!<UART DMA Control Register */
} MDR_UART_TypeDef;

/** @defgroup MDR32F21QI_UART_Defines UART Defines
 * @{
 */

/** @defgroup MDR32F21QI_UART_DR UART_DR
 * @{
 */

#define UART_DR_DATA_Pos 0
#define UART_DR_DATA_Msk (0xFFUL << UART_DR_DATA_Pos)

#define UART_DR_FE_Pos   8
#define UART_DR_FE_Msk   (0x1UL << UART_DR_FE_Pos)
#define UART_DR_FE       UART_DR_FE_Msk

#define UART_DR_PE_Pos   9
#define UART_DR_PE_Msk   (0x1UL << UART_DR_PE_Pos)
#define UART_DR_PE       UART_DR_PE_Msk

#define UART_DR_BE_Pos   10
#define UART_DR_BE_Msk   (0x1UL << UART_DR_BE_Pos)
#define UART_DR_BE       UART_DR_BE_Msk

#define UART_DR_OE_Pos   11
#define UART_DR_OE_Msk   (0x1UL << UART_DR_OE_Pos)
#define UART_DR_OE       UART_DR_OE_Msk

/** @} */ /* End of group MDR32F21QI_UART_DR */

/** @defgroup MDR32F21QI_UART_RSR_ECR UART_RSR_ECR
 * @{
 */

#define UART_RSR_ECR_FE_Pos 0
#define UART_RSR_ECR_FE_Msk (0x1UL << UART_RSR_ECR_FE_Pos)
#define UART_RSR_ECR_FE     UART_RSR_ECR_FE_Msk

#define UART_RSR_ECR_PE_Pos 1
#define UART_RSR_ECR_PE_Msk (0x1UL << UART_RSR_ECR_PE_Pos)
#define UART_RSR_ECR_PE     UART_RSR_ECR_PE_Msk

#define UART_RSR_ECR_BE_Pos 2
#define UART_RSR_ECR_BE_Msk (0x1UL << UART_RSR_ECR_BE_Pos)
#define UART_RSR_ECR_BE     UART_RSR_ECR_BE_Msk

#define UART_RSR_ECR_OE_Pos 3
#define UART_RSR_ECR_OE_Msk (0x1UL << UART_RSR_ECR_OE_Pos)
#define UART_RSR_ECR_OE     UART_RSR_ECR_OE_Msk

/** @} */ /* End of group MDR32F21QI_UART_RSR_ECR */

/** @defgroup MDR32F21QI_UART_FR UART_FR
 * @{
 */

#define UART_FR_CTS_Pos  0
#define UART_FR_CTS_Msk  (0x1UL << UART_FR_CTS_Pos)
#define UART_FR_CTS      UART_FR_CTS_Msk

#define UART_FR_DSR_Pos  1
#define UART_FR_DSR_Msk  (0x1UL << UART_FR_DSR_Pos)
#define UART_FR_DSR      UART_FR_DSR_Msk

#define UART_FR_DCD_Pos  2
#define UART_FR_DCD_Msk  (0x1UL << UART_FR_DCD_Pos)
#define UART_FR_DCD      UART_FR_DCD_Msk

#define UART_FR_BUSY_Pos 3
#define UART_FR_BUSY_Msk (0x1UL << UART_FR_BUSY_Pos)
#define UART_FR_BUSY     UART_FR_BUSY_Msk

#define UART_FR_RXFE_Pos 4
#define UART_FR_RXFE_Msk (0x1UL << UART_FR_RXFE_Pos)
#define UART_FR_RXFE     UART_FR_RXFE_Msk

#define UART_FR_TXFF_Pos 5
#define UART_FR_TXFF_Msk (0x1UL << UART_FR_TXFF_Pos)
#define UART_FR_TXFF     UART_FR_TXFF_Msk

#define UART_FR_RXFF_Pos 6
#define UART_FR_RXFF_Msk (0x1UL << UART_FR_RXFF_Pos)
#define UART_FR_RXFF     UART_FR_RXFF_Msk

#define UART_FR_TXFE_Pos 7
#define UART_FR_TXFE_Msk (0x1UL << UART_FR_TXFE_Pos)
#define UART_FR_TXFE     UART_FR_TXFE_Msk

#define UART_FR_RI_Pos   8
#define UART_FR_RI_Msk   (0x1UL << UART_FR_RI_Pos)
#define UART_FR_RI       UART_FR_RI_Msk

/** @} */ /* End of group MDR32F21QI_UART_FR */

/** @defgroup MDR32F21QI_UART_ILPR UART_ILPR
 * @{
 */

#define UART_ILPR_ILPDVSR_Pos 0
#define UART_ILPR_ILPDVSR_Msk (0xFFUL << UART_ILPR_ILPDVSR_Pos)

/** @} */ /* End of group MDR32F21QI_UART_ILPR */

/** @defgroup MDR32F21QI_UART_IBRD UART_IBRD
 * @{
 */

#define UART_IBRD_BAUD_DIVINT_Pos 0
#define UART_IBRD_BAUD_DIVINT_Msk (0xFFFFUL << UART_IBRD_BAUD_DIVINT_Pos)

/** @} */ /* End of group MDR32F21QI_UART_IBRD */

/** @defgroup MDR32F21QI_UART_FBRD UART_FBRD
 * @{
 */

#define UART_FBRD_BAUD_DIVFRAC_Pos 0
#define UART_FBRD_BAUD_DIVFRAC_Msk (0x3FUL << UART_FBRD_BAUD_DIVFRAC_Pos)

/** @} */ /* End of group MDR32F21QI_UART_FBRD */

/** @defgroup MDR32F21QI_UART_LCR_H UART_LCR_H
 * @{
 */

#define UART_LCR_H_BRK_Pos   0
#define UART_LCR_H_BRK_Msk   (0x1UL << UART_LCR_H_BRK_Pos)
#define UART_LCR_H_BRK       UART_LCR_H_BRK_Msk

#define UART_LCR_H_PEN_Pos   1
#define UART_LCR_H_PEN_Msk   (0x1UL << UART_LCR_H_PEN_Pos)
#define UART_LCR_H_PEN       UART_LCR_H_PEN_Msk

#define UART_LCR_H_EPS_Pos   2
#define UART_LCR_H_EPS_Msk   (0x1UL << UART_LCR_H_EPS_Pos)
#define UART_LCR_H_EPS       UART_LCR_H_EPS_Msk

#define UART_LCR_H_STP2_Pos  3
#define UART_LCR_H_STP2_Msk  (0x1UL << UART_LCR_H_STP2_Pos)
#define UART_LCR_H_STP2      UART_LCR_H_STP2_Msk

#define UART_LCR_H_FEN_Pos   4
#define UART_LCR_H_FEN_Msk   (0x1UL << UART_LCR_H_FEN_Pos)
#define UART_LCR_H_FEN       UART_LCR_H_FEN_Msk

#define UART_LCR_H_WLEN_Pos  5
#define UART_LCR_H_WLEN_Msk  (0x3UL << UART_LCR_H_WLEN_Pos)
#define UART_LCR_H_WLEN_5BIT (0x0UL << UART_LCR_H_WLEN_Pos)
#define UART_LCR_H_WLEN_6BIT (0x1UL << UART_LCR_H_WLEN_Pos)
#define UART_LCR_H_WLEN_7BIT (0x2UL << UART_LCR_H_WLEN_Pos)
#define UART_LCR_H_WLEN_8BIT (0x3UL << UART_LCR_H_WLEN_Pos)

#define UART_LCR_H_SPS_Pos   7
#define UART_LCR_H_SPS_Msk   (0x1UL << UART_LCR_H_SPS_Pos)
#define UART_LCR_H_SPS       UART_LCR_H_SPS_Msk

/** @} */ /* End of group MDR32F21QI_UART_LCR_H */

/** @defgroup MDR32F21QI_UART_CR UART_CR
 * @{
 */

#define UART_CR_UARTEN_Pos 0
#define UART_CR_UARTEN_Msk (0x1UL << UART_CR_UARTEN_Pos)
#define UART_CR_UARTEN     UART_CR_UARTEN_Msk

#define UART_CR_SIREN_Pos  1
#define UART_CR_SIREN_Msk  (0x1UL << UART_CR_SIREN_Pos)
#define UART_CR_SIREN      UART_CR_SIREN_Msk

#define UART_CR_SIRLP_Pos  2
#define UART_CR_SIRLP_Msk  (0x1UL << UART_CR_SIRLP_Pos)
#define UART_CR_SIRLP      UART_CR_SIRLP_Msk

#define UART_CR_LBE_Pos    7
#define UART_CR_LBE_Msk    (0x1UL << UART_CR_LBE_Pos)
#define UART_CR_LBE        UART_CR_LBE_Msk

#define UART_CR_TXE_Pos    8
#define UART_CR_TXE_Msk    (0x1UL << UART_CR_TXE_Pos)
#define UART_CR_TXE        UART_CR_TXE_Msk

#define UART_CR_RXE_Pos    9
#define UART_CR_RXE_Msk    (0x1UL << UART_CR_RXE_Pos)
#define UART_CR_RXE        UART_CR_RXE_Msk

#define UART_CR_DTR_Pos    10
#define UART_CR_DTR_Msk    (0x1UL << UART_CR_DTR_Pos)
#define UART_CR_DTR        UART_CR_DTR_Msk

#define UART_CR_RTS_Pos    11
#define UART_CR_RTS_Msk    (0x1UL << UART_CR_RTS_Pos)
#define UART_CR_RTS        UART_CR_RTS_Msk

#define UART_CR_OUT1_Pos   12
#define UART_CR_OUT1_Msk   (0x1UL << UART_CR_OUT1_Pos)
#define UART_CR_OUT1       UART_CR_OUT1_Msk

#define UART_CR_OUT2_Pos   13
#define UART_CR_OUT2_Msk   (0x1UL << UART_CR_OUT2_Pos)
#define UART_CR_OUT2       UART_CR_OUT2_Msk

#define UART_CR_RTSEN_Pos  14
#define UART_CR_RTSEN_Msk  (0x1UL << UART_CR_RTSEN_Pos)
#define UART_CR_RTSEN      UART_CR_RTSEN_Msk

#define UART_CR_CTSEN_Pos  15
#define UART_CR_CTSEN_Msk  (0x1UL << UART_CR_CTSEN_Pos)
#define UART_CR_CTSEN      UART_CR_CTSEN_Msk

/** @} */ /* End of group MDR32F21QI_UART_CR */

/** @defgroup MDR32F21QI_UART_IFLS UART_IFLS
 * @{
 */

#define UART_IFLS_TXIFLSEL_Pos    0
#define UART_IFLS_TXIFLSEL_Msk    (0x7UL << UART_IFLS_TXIFLSEL_Pos)
#define UART_IFLS_TXIFLSEL_2WORD  (0x0UL << UART_IFLS_TXIFLSEL_Pos)
#define UART_IFLS_TXIFLSEL_4WORD  (0x1UL << UART_IFLS_TXIFLSEL_Pos)
#define UART_IFLS_TXIFLSEL_8WORD  (0x2UL << UART_IFLS_TXIFLSEL_Pos)
#define UART_IFLS_TXIFLSEL_12WORD (0x3UL << UART_IFLS_TXIFLSEL_Pos)
#define UART_IFLS_TXIFLSEL_14WORD (0x4UL << UART_IFLS_TXIFLSEL_Pos)

#define UART_IFLS_RXIFLSEL_Pos    3
#define UART_IFLS_RXIFLSEL_Msk    (0x7UL << UART_IFLS_RXIFLSEL_Pos)
#define UART_IFLS_RXIFLSEL_2WORD  (0x0UL << UART_IFLS_RXIFLSEL_Pos)
#define UART_IFLS_RXIFLSEL_4WORD  (0x1UL << UART_IFLS_RXIFLSEL_Pos)
#define UART_IFLS_RXIFLSEL_8WORD  (0x2UL << UART_IFLS_RXIFLSEL_Pos)
#define UART_IFLS_RXIFLSEL_12WORD (0x3UL << UART_IFLS_RXIFLSEL_Pos)
#define UART_IFLS_RXIFLSEL_14WORD (0x4UL << UART_IFLS_RXIFLSEL_Pos)

/** @} */ /* End of group MDR32F21QI_UART_IFLS */

/** @defgroup MDR32F21QI_UART_IMSC UART_IMSC
 * @{
 */

#define UART_IMSC_RIMIM_Pos  0
#define UART_IMSC_RIMIM_Msk  (0x1UL << UART_IMSC_RIMIM_Pos)
#define UART_IMSC_RIMIM      UART_IMSC_RIMIM_Msk

#define UART_IMSC_CTSMIM_Pos 1
#define UART_IMSC_CTSMIM_Msk (0x1UL << UART_IMSC_CTSMIM_Pos)
#define UART_IMSC_CTSMIM     UART_IMSC_CTSMIM_Msk

#define UART_IMSC_DCDMIM_Pos 2
#define UART_IMSC_DCDMIM_Msk (0x1UL << UART_IMSC_DCDMIM_Pos)
#define UART_IMSC_DCDMIM     UART_IMSC_DCDMIM_Msk

#define UART_IMSC_DSRMIM_Pos 3
#define UART_IMSC_DSRMIM_Msk (0x1UL << UART_IMSC_DSRMIM_Pos)
#define UART_IMSC_DSRMIM     UART_IMSC_DSRMIM_Msk

#define UART_IMSC_RXIM_Pos   4
#define UART_IMSC_RXIM_Msk   (0x1UL << UART_IMSC_RXIM_Pos)
#define UART_IMSC_RXIM       UART_IMSC_RXIM_Msk

#define UART_IMSC_TXIM_Pos   5
#define UART_IMSC_TXIM_Msk   (0x1UL << UART_IMSC_TXIM_Pos)
#define UART_IMSC_TXIM       UART_IMSC_TXIM_Msk

#define UART_IMSC_RTIM_Pos   6
#define UART_IMSC_RTIM_Msk   (0x1UL << UART_IMSC_RTIM_Pos)
#define UART_IMSC_RTIM       UART_IMSC_RTIM_Msk

#define UART_IMSC_FEIM_Pos   7
#define UART_IMSC_FEIM_Msk   (0x1UL << UART_IMSC_FEIM_Pos)
#define UART_IMSC_FEIM       UART_IMSC_FEIM_Msk

#define UART_IMSC_PEIM_Pos   8
#define UART_IMSC_PEIM_Msk   (0x1UL << UART_IMSC_PEIM_Pos)
#define UART_IMSC_PEIM       UART_IMSC_PEIM_Msk

#define UART_IMSC_BEIM_Pos   9
#define UART_IMSC_BEIM_Msk   (0x1UL << UART_IMSC_BEIM_Pos)
#define UART_IMSC_BEIM       UART_IMSC_BEIM_Msk

#define UART_IMSC_OEIM_Pos   10
#define UART_IMSC_OEIM_Msk   (0x1UL << UART_IMSC_OEIM_Pos)
#define UART_IMSC_OEIM       UART_IMSC_OEIM_Msk

/** @} */ /* End of group MDR32F21QI_UART_IMSC */

/** @defgroup MDR32F21QI_UART_RIS UART_RIS
 * @{
 */

#define UART_RIS_RIRMIS_Pos  0
#define UART_RIS_RIRMIS_Msk  (0x1UL << UART_RIS_RIRMIS_Pos)
#define UART_RIS_RIRMIS      UART_RIS_RIRMIS_Msk

#define UART_RIS_CTSRMIS_Pos 1
#define UART_RIS_CTSRMIS_Msk (0x1UL << UART_RIS_CTSRMIS_Pos)
#define UART_RIS_CTSRMIS     UART_RIS_CTSRMIS_Msk

#define UART_RIS_DCDRMIS_Pos 2
#define UART_RIS_DCDRMIS_Msk (0x1UL << UART_RIS_DCDRMIS_Pos)
#define UART_RIS_DCDRMIS     UART_RIS_DCDRMIS_Msk

#define UART_RIS_DSRRMIS_Pos 3
#define UART_RIS_DSRRMIS_Msk (0x1UL << UART_RIS_DSRRMIS_Pos)
#define UART_RIS_DSRRMIS     UART_RIS_DSRRMIS_Msk

#define UART_RIS_RXRIS_Pos   4
#define UART_RIS_RXRIS_Msk   (0x1UL << UART_RIS_RXRIS_Pos)
#define UART_RIS_RXRIS       UART_RIS_RXRIS_Msk

#define UART_RIS_TXRIS_Pos   5
#define UART_RIS_TXRIS_Msk   (0x1UL << UART_RIS_TXRIS_Pos)
#define UART_RIS_TXRIS       UART_RIS_TXRIS_Msk

#define UART_RIS_RTRIS_Pos   6
#define UART_RIS_RTRIS_Msk   (0x1UL << UART_RIS_RTRIS_Pos)
#define UART_RIS_RTRIS       UART_RIS_RTRIS_Msk

#define UART_RIS_FERIS_Pos   7
#define UART_RIS_FERIS_Msk   (0x1UL << UART_RIS_FERIS_Pos)
#define UART_RIS_FERIS       UART_RIS_FERIS_Msk

#define UART_RIS_PERIS_Pos   8
#define UART_RIS_PERIS_Msk   (0x1UL << UART_RIS_PERIS_Pos)
#define UART_RIS_PERIS       UART_RIS_PERIS_Msk

#define UART_RIS_BERIS_Pos   9
#define UART_RIS_BERIS_Msk   (0x1UL << UART_RIS_BERIS_Pos)
#define UART_RIS_BERIS       UART_RIS_BERIS_Msk

#define UART_RIS_OERIS_Pos   10
#define UART_RIS_OERIS_Msk   (0x1UL << UART_RIS_OERIS_Pos)
#define UART_RIS_OERIS       UART_RIS_OERIS_Msk

/** @} */ /* End of group MDR32F21QI_UART_RIS */

/** @defgroup MDR32F21QI_UART_MIS UART_MIS
 * @{
 */

#define UART_MIS_RIMMIS_Pos  0
#define UART_MIS_RIMMIS_Msk  (0x1UL << UART_MIS_RIMMIS_Pos)
#define UART_MIS_RIMMIS      UART_MIS_RIMMIS_Msk

#define UART_MIS_CTSMMIS_Pos 1
#define UART_MIS_CTSMMIS_Msk (0x1UL << UART_MIS_CTSMMIS_Pos)
#define UART_MIS_CTSMMIS     UART_MIS_CTSMMIS_Msk

#define UART_MIS_DCDMMIS_Pos 2
#define UART_MIS_DCDMMIS_Msk (0x1UL << UART_MIS_DCDMMIS_Pos)
#define UART_MIS_DCDMMIS     UART_MIS_DCDMMIS_Msk

#define UART_MIS_DSRMMIS_Pos 3
#define UART_MIS_DSRMMIS_Msk (0x1UL << UART_MIS_DSRMMIS_Pos)
#define UART_MIS_DSRMMIS     UART_MIS_DSRMMIS_Msk

#define UART_MIS_RXMIS_Pos   4
#define UART_MIS_RXMIS_Msk   (0x1UL << UART_MIS_RXMIS_Pos)
#define UART_MIS_RXMIS       UART_MIS_RXMIS_Msk

#define UART_MIS_TXMIS_Pos   5
#define UART_MIS_TXMIS_Msk   (0x1UL << UART_MIS_TXMIS_Pos)
#define UART_MIS_TXMIS       UART_MIS_TXMIS_Msk

#define UART_MIS_RTMIS_Pos   6
#define UART_MIS_RTMIS_Msk   (0x1UL << UART_MIS_RTMIS_Pos)
#define UART_MIS_RTMIS       UART_MIS_RTMIS_Msk

#define UART_MIS_FEMIS_Pos   7
#define UART_MIS_FEMIS_Msk   (0x1UL << UART_MIS_FEMIS_Pos)
#define UART_MIS_FEMIS       UART_MIS_FEMIS_Msk

#define UART_MIS_PEMIS_Pos   8
#define UART_MIS_PEMIS_Msk   (0x1UL << UART_MIS_PEMIS_Pos)
#define UART_MIS_PEMIS       UART_MIS_PEMIS_Msk

#define UART_MIS_BEMIS_Pos   9
#define UART_MIS_BEMIS_Msk   (0x1UL << UART_MIS_BEMIS_Pos)
#define UART_MIS_BEMIS       UART_MIS_BEMIS_Msk

#define UART_MIS_OEMIS_Pos   10
#define UART_MIS_OEMIS_Msk   (0x1UL << UART_MIS_OEMIS_Pos)
#define UART_MIS_OEMIS       UART_MIS_OEMIS_Msk

/** @} */ /* End of group MDR32F21QI_UART_MIS */

/** @defgroup MDR32F21QI_UART_ICR UART_ICR
 * @{
 */

#define UART_ICR_RIMIC_Pos  0
#define UART_ICR_RIMIC_Msk  (0x1UL << UART_ICR_RIMIC_Pos)
#define UART_ICR_RIMIC      UART_ICR_RIMIC_Msk

#define UART_ICR_CTSMIC_Pos 1
#define UART_ICR_CTSMIC_Msk (0x1UL << UART_ICR_CTSMIC_Pos)
#define UART_ICR_CTSMIC     UART_ICR_CTSMIC_Msk

#define UART_ICR_DCDMIC_Pos 2
#define UART_ICR_DCDMIC_Msk (0x1UL << UART_ICR_DCDMIC_Pos)
#define UART_ICR_DCDMIC     UART_ICR_DCDMIC_Msk

#define UART_ICR_DSRMIC_Pos 3
#define UART_ICR_DSRMIC_Msk (0x1UL << UART_ICR_DSRMIC_Pos)
#define UART_ICR_DSRMIC     UART_ICR_DSRMIC_Msk

#define UART_ICR_RXIC_Pos   4
#define UART_ICR_RXIC_Msk   (0x1UL << UART_ICR_RXIC_Pos)
#define UART_ICR_RXIC       UART_ICR_RXIC_Msk

#define UART_ICR_TXIC_Pos   5
#define UART_ICR_TXIC_Msk   (0x1UL << UART_ICR_TXIC_Pos)
#define UART_ICR_TXIC       UART_ICR_TXIC_Msk

#define UART_ICR_RTIC_Pos   6
#define UART_ICR_RTIC_Msk   (0x1UL << UART_ICR_RTIC_Pos)
#define UART_ICR_RTIC       UART_ICR_RTIC_Msk

#define UART_ICR_FEIC_Pos   7
#define UART_ICR_FEIC_Msk   (0x1UL << UART_ICR_FEIC_Pos)
#define UART_ICR_FEIC       UART_ICR_FEIC_Msk

#define UART_ICR_PEIC_Pos   8
#define UART_ICR_PEIC_Msk   (0x1UL << UART_ICR_PEIC_Pos)
#define UART_ICR_PEIC       UART_ICR_PEIC_Msk

#define UART_ICR_BEIC_Pos   9
#define UART_ICR_BEIC_Msk   (0x1UL << UART_ICR_BEIC_Pos)
#define UART_ICR_BEIC       UART_ICR_BEIC_Msk

#define UART_ICR_OEIC_Pos   10
#define UART_ICR_OEIC_Msk   (0x1UL << UART_ICR_OEIC_Pos)
#define UART_ICR_OEIC       UART_ICR_OEIC_Msk

/** @} */ /* End of group MDR32F21QI_UART_ICR */

/** @defgroup MDR32F21QI_UART_DMACR UART_DMACR
 * @{
 */

#define UART_DMACR_RXDMAE_Pos   0
#define UART_DMACR_RXDMAE_Msk   (0x1UL << UART_DMACR_RXDMAE_Pos)
#define UART_DMACR_RXDMAE       UART_DMACR_RXDMAE_Msk

#define UART_DMACR_TXDMAE_Pos   1
#define UART_DMACR_TXDMAE_Msk   (0x1UL << UART_DMACR_TXDMAE_Pos)
#define UART_DMACR_TXDMAE       UART_DMACR_TXDMAE_Msk

#define UART_DMACR_DMAONERR_Pos 2
#define UART_DMACR_DMAONERR_Msk (0x1UL << UART_DMACR_DMAONERR_Pos)
#define UART_DMACR_DMAONERR     UART_DMACR_DMAONERR_Msk

/** @} */ /* End of group MDR32F21QI_UART_DMACR */

/** @} */ /* End of group MDR32F21QI_UART_Defines */

/** @} */ /* End of group MDR32F21QI_UART */

/** @defgroup MDR32F21QI_EEPROM MDR_EEPROM
 * @{
 */

/**
 * @brief MDR32F21QI EEPROM control structure
 */
typedef struct {
    __IO uint32_t CMD; /*!<EEPROM Command Register */
    __IO uint32_t ADR; /*!<EEPROM Address Register */
    __IO uint32_t DI;  /*!<EEPROM Read Data Register */
    __IO uint32_t DO;  /*!<EEPROM Write Data Register */
    __IO uint32_t KEY; /*!<EEPROM Key Register */
} MDR_EEPROM_TypeDef;

/** @defgroup MDR32F21QI_EEPROM_Defines EEPROM Defines
 * @{
 */

/** @defgroup MDR32F21QI_EEPROM_CMD EEPROM_CMD
 * @{
 */

#define EEPROM_CMD_CON_Pos       0
#define EEPROM_CMD_CON_Msk       (0x1UL << EEPROM_CMD_CON_Pos)
#define EEPROM_CMD_CON           EEPROM_CMD_CON_Msk

#define EEPROM_CMD_DELAY_Pos     3
#define EEPROM_CMD_DELAY_Msk     (0x3UL << EEPROM_CMD_DELAY_Pos)
#define EEPROM_CMD_DELAY_CYCLE_0 (0x0UL << EEPROM_CMD_DELAY_Pos)
#define EEPROM_CMD_DELAY_CYCLE_1 (0x1UL << EEPROM_CMD_DELAY_Pos)

#define EEPROM_CMD_XE_Pos        6
#define EEPROM_CMD_XE_Msk        (0x1UL << EEPROM_CMD_XE_Pos)
#define EEPROM_CMD_XE            EEPROM_CMD_XE_Msk

#define EEPROM_CMD_YE_Pos        7
#define EEPROM_CMD_YE_Msk        (0x1UL << EEPROM_CMD_YE_Pos)
#define EEPROM_CMD_YE            EEPROM_CMD_YE_Msk

#define EEPROM_CMD_SE_Pos        8
#define EEPROM_CMD_SE_Msk        (0x1UL << EEPROM_CMD_SE_Pos)
#define EEPROM_CMD_SE            EEPROM_CMD_SE_Msk

#define EEPROM_CMD_IFREN_Pos     9
#define EEPROM_CMD_IFREN_Msk     (0x1UL << EEPROM_CMD_IFREN_Pos)
#define EEPROM_CMD_IFREN         EEPROM_CMD_IFREN_Msk

#define EEPROM_CMD_ERASE_Pos     10
#define EEPROM_CMD_ERASE_Msk     (0x1UL << EEPROM_CMD_ERASE_Pos)
#define EEPROM_CMD_ERASE         EEPROM_CMD_ERASE_Msk

#define EEPROM_CMD_MAS1_Pos      11
#define EEPROM_CMD_MAS1_Msk      (0x1UL << EEPROM_CMD_MAS1_Pos)
#define EEPROM_CMD_MAS1          EEPROM_CMD_MAS1_Msk

#define EEPROM_CMD_PROG_Pos      12
#define EEPROM_CMD_PROG_Msk      (0x1UL << EEPROM_CMD_PROG_Pos)
#define EEPROM_CMD_PROG          EEPROM_CMD_PROG_Msk

#define EEPROM_CMD_NVSTR_Pos     13
#define EEPROM_CMD_NVSTR_Msk     (0x1UL << EEPROM_CMD_NVSTR_Pos)
#define EEPROM_CMD_NVSTR         EEPROM_CMD_NVSTR_Msk

/** @} */ /* End of group MDR32F21QI_EEPROM_CMD */

/** @defgroup MDR32F21QI_EEPROM_ADR EEPROM_ADR
 * @{
 */

#define EEPROM_ADR_ADR_Pos 0
#define EEPROM_ADR_ADR_Msk (0xFFFFFFFFUL << EEPROM_ADR_ADR_Pos)

/** @} */ /* End of group MDR32F21QI_EEPROM_ADR */

/** @defgroup MDR32F21QI_EEPROM_DI EEPROM_DI
 * @{
 */

#define EEPROM_DI_DATA_Pos 0
#define EEPROM_DI_DATA_Msk (0xFFFFFFFFUL << EEPROM_DI_DATA_Pos)

/** @} */ /* End of group MDR32F21QI_EEPROM_DI */

/** @defgroup MDR32F21QI_EEPROM_DO EEPROM_DO
 * @{
 */

#define EEPROM_DO_DATA_Pos 0
#define EEPROM_DO_DATA_Msk (0xFFFFFFFFUL << EEPROM_DO_DATA_Pos)

/** @} */ /* End of group MDR32F21QI_EEPROM_DO */

/** @defgroup MDR32F21QI_EEPROM_KEY EEPROM_KEY
 * @{
 */

#define EEPROM_KEY_KEY_Pos 0
#define EEPROM_KEY_KEY_Msk (0xFFFFFFFFUL << EEPROM_KEY_KEY_Pos)

/** @} */ /* End of group MDR32F21QI_EEPROM_KEY */

/** @} */ /* End of group MDR32F21QI_EEPROM_Defines */

/** @} */ /* End of group MDR32F21QI_EEPROM */

/** @defgroup MDR32F21QI_RST_CLK MDR_RST_CLK
 * @{
 */

/**
 * @brief MDR32F21QI RST_CLK control structure
 */
typedef struct {
    __IO uint32_t CLOCK_STATUS; /*!<RST_CLK Clock Status Register */
    __IO uint32_t PLL_CONTROL;  /*!<RST_CLK PLL Control Register */
    __IO uint32_t HS_CONTROL;   /*!<RST_CLK HS Control Register */
    __IO uint32_t CPU_CLOCK;    /*!<RST_CLK CPU Clock Register */
    __IO uint32_t PER1_CLOCK;   /*!<RST_CLK PER1 Clock Register */
    __IO uint32_t ADC_CLOCK;    /*!<RST_CLK ADC Clock Register */
    __IO uint32_t RTC_CLOCK;    /*!<RST_CLK RTC Clock Register */
    __IO uint32_t PER2_CLOCK;   /*!<RST_CLK Peripheral Clock Enable Register */
    __I uint32_t  RESERVED0;
    __IO uint32_t TIM_CLOCK;    /*!<RST_CLK Timer Clock Register */
    __IO uint32_t UART_CLOCK;   /*!<RST_CLK UART Clock Register */
    __IO uint32_t SSP_CLOCK;    /*!<RST_CLK SSP Clock Register */
} MDR_RST_CLK_TypeDef;

/** @defgroup MDR32F21QI_RST_CLK_Defines RST_CLK Defines
 * @{
 */

/** @defgroup MDR32F21QI_RST_CLK_CLOCK_STATUS RST_CLK CLOCK_STATUS
 * @{
 */

#define RST_CLK_CLOCK_STATUS_PLLCPURDY_Pos 1
#define RST_CLK_CLOCK_STATUS_PLLCPURDY_Msk (0x1UL << RST_CLK_CLOCK_STATUS_PLLCPURDY_Pos)
#define RST_CLK_CLOCK_STATUS_PLLCPURDY     RST_CLK_CLOCK_STATUS_PLLCPURDY_Msk

#define RST_CLK_CLOCK_STATUS_HSERDY_Pos    2
#define RST_CLK_CLOCK_STATUS_HSERDY_Msk    (0x1UL << RST_CLK_CLOCK_STATUS_HSERDY_Pos)
#define RST_CLK_CLOCK_STATUS_HSERDY        RST_CLK_CLOCK_STATUS_HSERDY_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_CLOCK_STATUS */

/** @defgroup MDR32F21QI_RST_CLK_PLL_CONTROL RST_CLK PLL_CONTROL
 * @{
 */

#define RST_CLK_PLL_CONTROL_PLL_CPU_ON_Pos  2
#define RST_CLK_PLL_CONTROL_PLL_CPU_ON_Msk  (0x1UL << RST_CLK_PLL_CONTROL_PLL_CPU_ON_Pos)
#define RST_CLK_PLL_CONTROL_PLL_CPU_ON      RST_CLK_PLL_CONTROL_PLL_CPU_ON_Msk

#define RST_CLK_PLL_CONTROL_PLL_CPU_RLD_Pos 3
#define RST_CLK_PLL_CONTROL_PLL_CPU_RLD_Msk (0x1UL << RST_CLK_PLL_CONTROL_PLL_CPU_RLD_Pos)
#define RST_CLK_PLL_CONTROL_PLL_CPU_RLD     RST_CLK_PLL_CONTROL_PLL_CPU_RLD_Msk

#define RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos 8
#define RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk (0xFUL << RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos)

/** @} */ /* End of group MDR32F21QI_RST_CLK_PLL_CONTROL */

/** @defgroup MDR32F21QI_RST_CLK_HS_CONTROL RST_CLK HS_CONTROL
 * @{
 */

#define RST_CLK_HS_CONTROL_HSE_ON_Pos  0
#define RST_CLK_HS_CONTROL_HSE_ON_Msk  (0x1UL << RST_CLK_HS_CONTROL_HSE_ON_Pos)
#define RST_CLK_HS_CONTROL_HSE_ON      RST_CLK_HS_CONTROL_HSE_ON_Msk

#define RST_CLK_HS_CONTROL_HSE_BYP_Pos 1
#define RST_CLK_HS_CONTROL_HSE_BYP_Msk (0x1UL << RST_CLK_HS_CONTROL_HSE_BYP_Pos)
#define RST_CLK_HS_CONTROL_HSE_BYP     RST_CLK_HS_CONTROL_HSE_BYP_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_HS_CONTROL */

/** @defgroup MDR32F21QI_RST_CLK_CPU_CLOCK RST_CLK CPU_CLOCK
 * @{
 */

#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos     0
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk     (0x3UL << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos)
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSI     (0x0UL << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos)
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSIdiv2 (0x1UL << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos)
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSE     (0x2UL << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos)
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSEdiv2 (0x3UL << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos)

#define RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos     2
#define RST_CLK_CPU_CLOCK_CPU_C2_SEL_Msk     (0x1UL << RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos)
#define RST_CLK_CPU_CLOCK_CPU_C2_SEL         RST_CLK_CPU_CLOCK_CPU_C2_SEL_Msk

#define RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos     4
#define RST_CLK_CPU_CLOCK_CPU_C3_SEL_Msk     (0xFUL << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos)

#define RST_CLK_CPU_CLOCK_HCLK_SEL_Pos       8
#define RST_CLK_CPU_CLOCK_HCLK_SEL_Msk       (0x3UL << RST_CLK_CPU_CLOCK_HCLK_SEL_Pos)
#define RST_CLK_CPU_CLOCK_HCLK_SEL_HSI       (0x0UL << RST_CLK_CPU_CLOCK_HCLK_SEL_Pos)
#define RST_CLK_CPU_CLOCK_HCLK_SEL_CPU_C3    (0x1UL << RST_CLK_CPU_CLOCK_HCLK_SEL_Pos)
#define RST_CLK_CPU_CLOCK_HCLK_SEL_LSE       (0x2UL << RST_CLK_CPU_CLOCK_HCLK_SEL_Pos)
#define RST_CLK_CPU_CLOCK_HCLK_SEL_LSI       (0x3UL << RST_CLK_CPU_CLOCK_HCLK_SEL_Pos)

/** @} */ /* End of group MDR32F21QI_RST_CLK_CPU_CLOCK */

/** @defgroup MDR32F21QI_RST_CLK_PER1_CLOCK RST_CLK PER1_CLOCK
 * @{
 */

#define RST_CLK_PER1_CLOCK_C1_SEL_Pos     0
#define RST_CLK_PER1_CLOCK_C1_SEL_Msk     (0x3UL << RST_CLK_PER1_CLOCK_C1_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C1_SEL_LSI     (0x0UL << RST_CLK_PER1_CLOCK_C1_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C1_SEL_LSIdiv2 (0x1UL << RST_CLK_PER1_CLOCK_C1_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C1_SEL_LSE     (0x2UL << RST_CLK_PER1_CLOCK_C1_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C1_SEL_LSEdiv2 (0x3UL << RST_CLK_PER1_CLOCK_C1_SEL_Pos)

#define RST_CLK_PER1_CLOCK_C2_SEL_Pos     2
#define RST_CLK_PER1_CLOCK_C2_SEL_Msk     (0x3UL << RST_CLK_PER1_CLOCK_C2_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C2_SEL_CPU_C1  (0x0UL << RST_CLK_PER1_CLOCK_C2_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C2_SEL_PER1_C1 (0x1UL << RST_CLK_PER1_CLOCK_C2_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C2_SEL_PLLCPUo (0x2UL << RST_CLK_PER1_CLOCK_C2_SEL_Pos)
#define RST_CLK_PER1_CLOCK_C2_SEL_HSI_CLK (0x3UL << RST_CLK_PER1_CLOCK_C2_SEL_Pos)

#define RST_CLK_PER1_CLOCK_DEBUG_EN_Pos   4
#define RST_CLK_PER1_CLOCK_DEBUG_EN_Msk   (0x1UL << RST_CLK_PER1_CLOCK_DEBUG_EN_Pos)
#define RST_CLK_PER1_CLOCK_DEBUG_EN       RST_CLK_PER1_CLOCK_DEBUG_EN_Msk

#define RST_CLK_PER1_CLOCK_DMA_EN_Pos     5
#define RST_CLK_PER1_CLOCK_DMA_EN_Msk     (0x1UL << RST_CLK_PER1_CLOCK_DMA_EN_Pos)
#define RST_CLK_PER1_CLOCK_DMA_EN         RST_CLK_PER1_CLOCK_DMA_EN_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_PER1_CLOCK */

/** @defgroup MDR32F21QI_RST_CLK_ADC_CLOCK RST_CLK ADC_CLOCK
 * @{
 */

/* Bit field positions: */
#define RST_CLK_ADC_CLOCK_ADC_C1_SEL_Pos       0
#define RST_CLK_ADC_CLOCK_ADC_C1_SEL_Msk       (0x3UL << RST_CLK_ADC_CLOCK_ADC_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADC_C1_SEL_CPU_C1    (0x0UL << RST_CLK_ADC_CLOCK_ADC_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADC_C1_SEL_PER1_C1   (0x1UL << RST_CLK_ADC_CLOCK_ADC_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADC_C1_SEL_PLLCPUo   (0x2UL << RST_CLK_ADC_CLOCK_ADC_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADC_C1_SEL_HSI_CLK   (0x3UL << RST_CLK_ADC_CLOCK_ADC_C1_SEL_Pos)

#define RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Pos     2
#define RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Msk     (0x3UL << RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_CPU_C1  (0x0UL << RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_PER1_C1 (0x1UL << RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_PLLCPUo (0x2UL << RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_HSI_CLK (0x3UL << RST_CLK_ADC_CLOCK_ADCUI_C1_SEL_Pos)

#define RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos     4
#define RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Msk     (0xFUL << RST_CLK_ADC_CLOCK_ADCUI_C3_SEL_Pos)

#define RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos       8
#define RST_CLK_ADC_CLOCK_ADC_C3_SEL_Msk       (0xFUL << RST_CLK_ADC_CLOCK_ADC_C3_SEL_Pos)

#define RST_CLK_ADC_CLOCK_ADCUI_CLK_EN_Pos     12
#define RST_CLK_ADC_CLOCK_ADCUI_CLK_EN_Msk     (0x1UL << RST_CLK_ADC_CLOCK_ADCUI_CLK_EN_Pos)
#define RST_CLK_ADC_CLOCK_ADCUI_CLK_EN         RST_CLK_ADC_CLOCK_ADCUI_CLK_EN_Msk

#define RST_CLK_ADC_CLOCK_ADC_CLK_EN_Pos       13
#define RST_CLK_ADC_CLOCK_ADC_CLK_EN_Msk       (0x1UL << RST_CLK_ADC_CLOCK_ADC_CLK_EN_Pos)
#define RST_CLK_ADC_CLOCK_ADC_CLK_EN           RST_CLK_ADC_CLOCK_ADC_CLK_EN_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_ADC_CLOCK */

/** @defgroup MDR32F21QI_RST_CLK_RTC_CLOCK RST_CLK RTC_CLOCK
 * @{
 */

#define RST_CLK_RTC_CLOCK_HSE_SEL_Pos    0
#define RST_CLK_RTC_CLOCK_HSE_SEL_Msk    (0xFUL << RST_CLK_RTC_CLOCK_HSE_SEL_Pos)

#define RST_CLK_RTC_CLOCK_HSI_SEL_Pos    4
#define RST_CLK_RTC_CLOCK_HSI_SEL_Msk    (0xFUL << RST_CLK_RTC_CLOCK_HSI_SEL_Pos)

#define RST_CLK_RTC_CLOCK_HSE_RTC_EN_Pos 8
#define RST_CLK_RTC_CLOCK_HSE_RTC_EN_Msk (0x1UL << RST_CLK_RTC_CLOCK_HSE_RTC_EN_Pos)
#define RST_CLK_RTC_CLOCK_HSE_RTC_EN     RST_CLK_RTC_CLOCK_HSE_RTC_EN_Msk

#define RST_CLK_RTC_CLOCK_HSI_RTC_EN_Pos 9
#define RST_CLK_RTC_CLOCK_HSI_RTC_EN_Msk (0x1UL << RST_CLK_RTC_CLOCK_HSI_RTC_EN_Pos)
#define RST_CLK_RTC_CLOCK_HSI_RTC_EN     RST_CLK_RTC_CLOCK_HSI_RTC_EN_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_RTC_CLOCK */

/** @defgroup MDR32F21QI_RST_CLK_PER2_CLOCK RST_CLK PER2_CLOCK
 * @{
 */

#define RST_CLK_PER2_CLOCK_PCLK_EN_SPI_Pos     0
#define RST_CLK_PER2_CLOCK_PCLK_EN_SPI_Msk     (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_SPI_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_SPI         RST_CLK_PER2_CLOCK_PCLK_EN_SPI_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_UART0_Pos   1
#define RST_CLK_PER2_CLOCK_PCLK_EN_UART0_Msk   (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_UART0_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_UART0       RST_CLK_PER2_CLOCK_PCLK_EN_UART0_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_UART1_Pos   2
#define RST_CLK_PER2_CLOCK_PCLK_EN_UART2_Msk   (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_UART1_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_UART2       RST_CLK_PER2_CLOCK_PCLK_EN_UART2_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_EEPROM_Pos  3
#define RST_CLK_PER2_CLOCK_PCLK_EN_EEPROM_Msk  (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_EEPROM_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_EEPROM      RST_CLK_PER2_CLOCK_PCLK_EN_EEPROM_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK_Pos 4
#define RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK_Msk (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK     RST_CLK_PER2_CLOCK_PCLK_EN_RST_CLK_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_DMA_Pos     5
#define RST_CLK_PER2_CLOCK_PCLK_EN_DMA_Msk     (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_DMA_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_DMA         RST_CLK_PER2_CLOCK_PCLK_EN_DMA_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_ADC_Pos     8
#define RST_CLK_PER2_CLOCK_PCLK_EN_ADC_Msk     (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_ADC_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_ADC         RST_CLK_PER2_CLOCK_PCLK_EN_ADC_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_WWDT_Pos    9
#define RST_CLK_PER2_CLOCK_PCLK_EN_WWDT_Msk    (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_WWDT_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_WWDT        RST_CLK_PER2_CLOCK_PCLK_EN_WWDT_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_IWDT_Pos    10
#define RST_CLK_PER2_CLOCK_PCLK_EN_IWDT_Msk    (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_IWDT_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_IWDT        RST_CLK_PER2_CLOCK_PCLK_EN_IWDT_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_POWER_Pos   11
#define RST_CLK_PER2_CLOCK_PCLK_EN_POWER_Msk   (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_POWER_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_POWER       RST_CLK_PER2_CLOCK_PCLK_EN_POWER_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Pos     12
#define RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Msk     (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_BKP         RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI_Pos   13
#define RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI_Msk   (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI       RST_CLK_PER2_CLOCK_PCLK_EN_ADCUI_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_TIMER0_Pos  14
#define RST_CLK_PER2_CLOCK_PCLK_EN_TIMER0_Msk  (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_TIMER0_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_TIMER0      RST_CLK_PER2_CLOCK_PCLK_EN_TIMER0_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_TIMER1_Pos  15
#define RST_CLK_PER2_CLOCK_PCLK_EN_TIMER1_Msk  (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_TIMER1_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_TIMER1      RST_CLK_PER2_CLOCK_PCLK_EN_TIMER1_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTA_Pos   16
#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTA_Msk   (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_PORTA_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTA       RST_CLK_PER2_CLOCK_PCLK_EN_PORTA_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTB_Pos   17
#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTB_Msk   (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_PORTB_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTB       RST_CLK_PER2_CLOCK_PCLK_EN_PORTB_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTC_Pos   18
#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTC_Msk   (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_PORTC_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_PORTC       RST_CLK_PER2_CLOCK_PCLK_EN_PORTC_Msk

#define RST_CLK_PER2_CLOCK_PCLK_EN_CRC_Pos     19
#define RST_CLK_PER2_CLOCK_PCLK_EN_CRC_Msk     (0x1UL << RST_CLK_PER2_CLOCK_PCLK_EN_CRC_Pos)
#define RST_CLK_PER2_CLOCK_PCLK_EN_CRC         RST_CLK_PER2_CLOCK_PCLK_EN_CRC_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_PER2_CLOCK */

/** @defgroup MDR32F21QI_RST_CLK_TIM_CLOCK RST_CLK TIM_CLOCK
 * @{
 */

#define RST_CLK_TIM_CLOCK_TIM0_BRG_Pos    0
#define RST_CLK_TIM_CLOCK_TIM0_BRG_Msk    (0x7UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV1   (0x0UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV2   (0x1UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV4   (0x2UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV8   (0x3UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV16  (0x4UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV32  (0x5UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV64  (0x6UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_BRG_DIV128 (0x7UL << RST_CLK_TIM_CLOCK_TIM0_BRG_Pos)

#define RST_CLK_TIM_CLOCK_TIM1_BRG_Pos    8
#define RST_CLK_TIM_CLOCK_TIM1_BRG_Msk    (0x7UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV1   (0x0UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV2   (0x1UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV4   (0x2UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV8   (0x3UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV16  (0x4UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV32  (0x5UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV64  (0x6UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_BRG_DIV128 (0x7UL << RST_CLK_TIM_CLOCK_TIM1_BRG_Pos)

#define RST_CLK_TIM_CLOCK_TIM0_CLK_EN_Pos 24
#define RST_CLK_TIM_CLOCK_TIM0_CLK_EN_Msk (0x1UL << RST_CLK_TIM_CLOCK_TIM0_CLK_EN_Pos)
#define RST_CLK_TIM_CLOCK_TIM0_CLK_EN     RST_CLK_TIM_CLOCK_TIM0_CLK_EN_Msk

#define RST_CLK_TIM_CLOCK_TIM1_CLK_EN_Pos 25
#define RST_CLK_TIM_CLOCK_TIM1_CLK_EN_Msk (0x1UL << RST_CLK_TIM_CLOCK_TIM1_CLK_EN_Pos)
#define RST_CLK_TIM_CLOCK_TIM1_CLK_EN     RST_CLK_TIM_CLOCK_TIM1_CLK_EN_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_TIM_CLOCK */

/** @defgroup MDR32F21QI_RST_CLK_UART_CLOCK RST_CLK UART_CLOCK
 * @{
 */

#define RST_CLK_UART_CLOCK_UART0_BRG_Pos    0
#define RST_CLK_UART_CLOCK_UART0_BRG_Msk    (0x7UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV1   (0x0UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV2   (0x1UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV4   (0x2UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV8   (0x3UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV16  (0x4UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV32  (0x5UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV64  (0x6UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART0_BRG_DIV128 (0x7UL << RST_CLK_UART_CLOCK_UART0_BRG_Pos)

#define RST_CLK_UART_CLOCK_UART1_BRG_Pos    8
#define RST_CLK_UART_CLOCK_UART1_BRG_Msk    (0x7UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV1   (0x0UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV2   (0x1UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV4   (0x2UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV8   (0x3UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV16  (0x4UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV32  (0x5UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV64  (0x6UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)
#define RST_CLK_UART_CLOCK_UART1_BRG_DIV128 (0x7UL << RST_CLK_UART_CLOCK_UART1_BRG_Pos)

#define RST_CLK_UART_CLOCK_UART0_CLK_EN_Pos 24
#define RST_CLK_UART_CLOCK_UART0_CLK_EN_Msk (0x1UL << RST_CLK_UART_CLOCK_UART0_CLK_EN_Pos)
#define RST_CLK_UART_CLOCK_UART0_CLK_EN     RST_CLK_UART_CLOCK_UART0_CLK_EN_Msk

#define RST_CLK_UART_CLOCK_UART1_CLK_EN_Pos 25
#define RST_CLK_UART_CLOCK_UART1_CLK_EN_Msk (0x1UL << RST_CLK_UART_CLOCK_UART1_CLK_EN_Pos)
#define RST_CLK_UART_CLOCK_UART1_CLK_EN     RST_CLK_UART_CLOCK_UART1_CLK_EN_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_UART_CLOCK */

/** @defgroup MDR32F21QI_RST_CLK_SSP_CLOCK RST_CLK SSP_CLOCK
 * @{
 */

#define RST_CLK_SSP_CLOCK_SSP_BRG_Pos    0
#define RST_CLK_SSP_CLOCK_SSP_BRG_Msk    (0x7UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV1   (0x0UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV2   (0x1UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV4   (0x2UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV8   (0x3UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV16  (0x4UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV32  (0x5UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV64  (0x6UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)
#define RST_CLK_SSP_CLOCK_SSP_BRG_DIV128 (0x7UL << RST_CLK_SSP_CLOCK_SSP_BRG_Pos)

#define RST_CLK_SSP_CLOCK_SSP_CLK_EN_Pos 24
#define RST_CLK_SSP_CLOCK_SSP_CLK_EN_Msk (0x1UL << RST_CLK_SSP_CLOCK_SSP_CLK_EN_Pos)
#define RST_CLK_SSP_CLOCK_SSP_CLK_EN     RST_CLK_SSP_CLOCK_SSP_CLK_EN_Msk

/** @} */ /* End of group MDR32F21QI_RST_CLK_SSP_CLOCK */

/** @} */ /* End of group MDR32F21QI_RST_CLK_Defines */

/** @} */ /* End of group MDR32F21QI_RST_CLK */

/** @defgroup MDR32F21QI_DMA MDR_DMA
 * @{
 */

/**
 * @brief MDR32F21QI DMA control structure
 */
typedef struct {
    __IO uint32_t STATUS;            /*!<DMA Status Register */
    __IO uint32_t CFG;               /*!<DMA Configuration Register */
    __IO uint32_t CTRL_BASE_PTR;     /*!<DMA Channel Control Data Base pointer Register */
    __IO uint32_t ALT_CTRL_BASE_PTR; /*!<DMA Channel Alternate Control Data Base Bointer Register */
    __IO uint32_t WAITONREQ_STATUS;  /*!<DMA Channel Wait On Request Status Register */
    __IO uint32_t CHNL_SW_REQUEST;   /*!<DMA Channel software request */
    __IO uint32_t CHNL_USEBURST_SET; /*!<DMA Channel Useburst Set Register */
    __IO uint32_t CHNL_USEBURST_CLR; /*!<DMA Channel Useburst Clear Register */
    __IO uint32_t CHNL_REQ_MASK_SET; /*!<DMA Channel Request Mask Set Register */
    __IO uint32_t CHNL_REQ_MASK_CLR; /*!<DMA Channel Request Mask Clear Register */
    __IO uint32_t CHNL_ENABLE_SET;   /*!<DMA Channel Enable Set Register */
    __IO uint32_t CHNL_ENABLE_CLR;   /*!<DMA Channel Enable Clear Register */
    __IO uint32_t CHNL_PRI_ALT_SET;  /*!<DMA Channel Primary-Alternate Set Register */
    __IO uint32_t CHNL_PRI_ALT_CLR;  /*!<DMA Channel Primary-Alternate Clear Register */
    __IO uint32_t CHNL_PRIORITY_SET; /*!<DMA Channel Priority Set Register */
    __IO uint32_t CHNL_PRIORITY_CLR; /*!<DMA Channel Priority Clear Register */
    __I uint32_t  RESERVED0[3];
    __IO uint32_t ERR_CLR;           /*!<DMA Bus Error Flag Clear Register */
} MDR_DMA_TypeDef;

/** @defgroup MDR32F21QI_DMA_Defines DMA Defines
 * @{
 */

/** @defgroup MDR32F21QI_DMA_STATUS DMA STATUS
 * @{
 */

#define DMA_STATUS_MASTER_ENABLE_Pos 0
#define DMA_STATUS_MASTER_ENABLE_Msk (0x1UL << DMA_STATUS_MASTER_ENABLE_Pos)
#define DMA_STATUS_MASTER_ENABLE     DMA_STATUS_MASTER_ENABLE_Msk

#define DMA_STATUS_STATE_Pos         4
#define DMA_STATUS_STATE_Msk         (0xFUL << DMA_STATUS_STATE_Pos)

#define DMA_STATUS_CHNLS_MINUS1_Pos  16
#define DMA_STATUS_CHNLS_MINUS1_Msk  (0x1FUL << DMA_STATUS_CHNLS_MINUS1_Pos)

#define DMA_STATUS_TEST_STATUS_Pos   28
#define DMA_STATUS_TEST_STATUS_Msk   (0xFUL << DMA_STATUS_TEST_STATUS_Pos)

/** @} */ /* End of group MDR32F21QI_DMA_STATUS */

/** @defgroup MDR32F21QI_DMA_CFG DMA_CFG
 * @{
 */

#define DMA_CFG_MASTER_ENABLE_Pos     0
#define DMA_CFG_MASTER_ENABLE_Msk     (0x1UL << DMA_CFG_MASTER_ENABLE_Pos)
#define DMA_CFG_MASTER_ENABLE         DMA_CFG_MASTER_ENABLE_Msk

#define DMA_CFG_CHNL_PROT_CTRL_Pos    5
#define DMA_CFG_CHNL_PROT_CTRL_Msk    (0x7UL << DMA_CFG_CHNL_PROT_CTRL_Pos)
#define DMA_CFG_CHNL_PROT_CTRL_HPROT1 (0x1UL << DMA_CFG_CHNL_PROT_CTRL_Pos)
#define DMA_CFG_CHNL_PROT_CTRL_HPROT2 (0x2UL << DMA_CFG_CHNL_PROT_CTRL_Pos)
#define DMA_CFG_CHNL_PROT_CTRL_HPROT3 (0x4UL << DMA_CFG_CHNL_PROT_CTRL_Pos)

/** @} */ /* End of group MDR32F21QI_DMA_CFG */

/** @defgroup MDR32F21QI_DMA_ERR_CLR DMA_ERR_CLR
 * @{
 */

#define DMA_ERR_CLR_ERR_CLR_Pos 0
#define DMA_ERR_CLR_ERR_CLR_Msk (0x1UL << DMA_ERR_CLR_ERR_CLR_Pos)
#define DMA_ERR_CLR_ERR_CLR     DMA_ERR_CLR_ERR_CLR_Msk

/** @} */ /* End of group MDR32F21QI_DMA_ERR_CLR */

/** @defgroup MDR32F21QI_DMA_CHANNEL_CFG DMA CHANNEL_CFG
 * @{
 */

#define DMA_CHANNEL_CFG_CYCLE_CTRL_Pos             0
#define DMA_CHANNEL_CFG_CYCLE_CTRL_Msk             (0x7UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_STOP            (0x0UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_BASIC           (0x1UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_AUTO_REQUEST    (0x2UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_PING_PONG       (0x3UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_MEM_SCATTER_PRI (0x4UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_MEM_SCATTER_ALT (0x5UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_PER_SCATTER_PRI (0x6UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)
#define DMA_CHANNEL_CFG_CYCLE_CTRL_PER_SCATTER_ALT (0x7UL << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos)

#define DMA_CHANNEL_CFG_NEXT_USEBURST_Pos          3
#define DMA_CHANNEL_CFG_NEXT_USEBURST_Msk          (0x1UL << DMA_CHANNEL_CFG_NEXT_USEBURST_Pos)
#define DMA_CHANNEL_CFG_NEXT_USEBURST              DMA_CHANNEL_CFG_NEXT_USEBURST_Msk

#define DMA_CHANNEL_CFG_N_MINUS_1_Pos              4
#define DMA_CHANNEL_CFG_N_MINUS_1_Msk              (0x3FFUL << DMA_CHANNEL_CFG_N_MINUS_1_Pos)

#define DMA_CHANNEL_CFG_R_POWER_Pos                14
#define DMA_CHANNEL_CFG_R_POWER_Msk                (0xFUL << DMA_CHANNEL_CFG_R_POWER_Pos)

#define DMA_CHANNEL_CFG_SRC_PROT_CTRL_Pos          18
#define DMA_CHANNEL_CFG_SRC_PROT_CTRL_Msk          (0x7UL << DMA_CHANNEL_CFG_SRC_PROT_CTRL_Pos)
#define DMA_CHANNEL_CFG_SRC_PROT_CTRL_HPROT1       (0x1UL << DMA_CHANNEL_CFG_SRC_PROT_CTRL_Pos)
#define DMA_CHANNEL_CFG_SRC_PROT_CTRL_HPROT2       (0x2UL << DMA_CHANNEL_CFG_SRC_PROT_CTRL_Pos)
#define DMA_CHANNEL_CFG_SRC_PROT_CTRL_HPROT3       (0x4UL << DMA_CHANNEL_CFG_SRC_PROT_CTRL_Pos)

#define DMA_CHANNEL_CFG_DST_PROT_CTRL_Pos          21
#define DMA_CHANNEL_CFG_DST_PROT_CTRL_Msk          (0x7UL << DMA_CHANNEL_CFG_DST_PROT_CTRL_Pos)
#define DMA_CHANNEL_CFG_DST_PROT_CTRL_HPROT1       (0x1UL << DMA_CHANNEL_CFG_DST_PROT_CTRL_Pos)
#define DMA_CHANNEL_CFG_DST_PROT_CTRL_HPROT2       (0x2UL << DMA_CHANNEL_CFG_DST_PROT_CTRL_Pos)
#define DMA_CHANNEL_CFG_DST_PROT_CTRL_HPROT3       (0x4UL << DMA_CHANNEL_CFG_DST_PROT_CTRL_Pos)

#define DMA_CHANNEL_CFG_SRC_SIZE_Pos               24
#define DMA_CHANNEL_CFG_SRC_SIZE_Msk               (0x3UL << DMA_CHANNEL_CFG_SRC_SIZE_Pos)
#define DMA_CHANNEL_CFG_SRC_SIZE_8BIT              (0x0UL << DMA_CHANNEL_CFG_SRC_SIZE_Pos)
#define DMA_CHANNEL_CFG_SRC_SIZE_16BIT             (0x1UL << DMA_CHANNEL_CFG_SRC_SIZE_Pos)
#define DMA_CHANNEL_CFG_SRC_SIZE_32BIT             (0x2UL << DMA_CHANNEL_CFG_SRC_SIZE_Pos)

#define DMA_CHANNEL_CFG_SRC_INC_Pos                26
#define DMA_CHANNEL_CFG_SRC_INC_Msk                (0x3UL << DMA_CHANNEL_CFG_SRC_INC_Pos)
#define DMA_CHANNEL_CFG_SRC_INC_8BIT               (0x0UL << DMA_CHANNEL_CFG_SRC_INC_Pos)
#define DMA_CHANNEL_CFG_SRC_INC_16BIT              (0x1UL << DMA_CHANNEL_CFG_SRC_INC_Pos)
#define DMA_CHANNEL_CFG_SRC_INC_32BIT              (0x2UL << DMA_CHANNEL_CFG_SRC_INC_Pos)
#define DMA_CHANNEL_CFG_SRC_INC_NO                 (0x3UL << DMA_CHANNEL_CFG_SRC_INC_Pos)

#define DMA_CHANNEL_CFG_DST_SIZE_Pos               28
#define DMA_CHANNEL_CFG_DST_SIZE_Msk               (0x3UL << DMA_CHANNEL_CFG_DST_SIZE_Pos)
#define DMA_CHANNEL_CFG_DST_SIZE_8BIT              (0x0UL << DMA_CHANNEL_CFG_DST_SIZE_Pos)
#define DMA_CHANNEL_CFG_DST_SIZE_16BIT             (0x1UL << DMA_CHANNEL_CFG_DST_SIZE_Pos)
#define DMA_CHANNEL_CFG_DST_SIZE_32BIT             (0x2UL << DMA_CHANNEL_CFG_DST_SIZE_Pos)

#define DMA_CHANNEL_CFG_DST_INC_Pos                30
#define DMA_CHANNEL_CFG_DST_INC_Msk                (0x3UL << DMA_CHANNEL_CFG_DST_INC_Pos)
#define DMA_CHANNEL_CFG_DST_INC_8BIT               (0x0UL << DMA_CHANNEL_CFG_DST_INC_Pos)
#define DMA_CHANNEL_CFG_DST_INC_16BIT              (0x1UL << DMA_CHANNEL_CFG_DST_INC_Pos)
#define DMA_CHANNEL_CFG_DST_INC_32BIT              (0x2UL << DMA_CHANNEL_CFG_DST_INC_Pos)
#define DMA_CHANNEL_CFG_DST_INC_NO                 (0x3UL << DMA_CHANNEL_CFG_DST_INC_Pos)

/** @} */ /* End of group MDR32F21QI_DMA_CHANNEL_CFG */

/** @} */ /* End of group MDR32F21QI_DMA_Defines */

/** @} */ /* End of group MDR32F21QI_DMA */

/** @defgroup MDR32F21QI_ADC MDR_ADC
 * @{
 */

/**
 * @brief MDR32F21QI ADC control structure
 */
typedef struct {
    __IO uint32_t ADC1_CFG;     /*!<ADC1 Configuration Register */
    __IO uint32_t ADC2_CFG;     /*!<ADC2 Configuration Register */
    __IO uint32_t ADC1_H_LEVEL; /*!<ADC1 High Level Register */
    __I uint32_t  RESERVED0;
    __IO uint32_t ADC1_L_LEVEL; /*!<ADC1 Low Level Register */
    __I uint32_t  RESERVED1;
    __IO uint32_t ADC1_RESULT;  /*!<ADC1 Result Register */
    __I uint32_t  RESERVED2;
    __IO uint32_t ADC1_STATUS;  /*!<ADC1 Status Register */
    __I uint32_t  RESERVED3;
    __IO uint32_t ADC1_CHSEL;   /*!<ADC1 Channel Selector Register */
    __I uint32_t  RESERVED4;
    __IO uint32_t ADC1_TRIM;    /*!<ADC Reference Voltage Trim */
} MDR_ADC_TypeDef;

/** @defgroup MDR32F21QI_ADC_Defines ADC Defines
 * @{
 */

/** @defgroup MDR32F21QI_ADC1_CFG ADC1_CFG
 * @{
 */

#define ADC1_CFG_REG_ADON_Pos     0
#define ADC1_CFG_REG_ADON_Msk     (0x1UL << ADC1_CFG_REG_ADON_Pos)
#define ADC1_CFG_REG_ADON         ADC1_CFG_REG_ADON_Msk

#define ADC1_CFG_REG_GO_Pos       1
#define ADC1_CFG_REG_GO_Msk       (0x1UL << ADC1_CFG_REG_GO_Pos)
#define ADC1_CFG_REG_GO           ADC1_CFG_REG_GO_Msk

#define ADC1_CFG_REG_CLKS_Pos     2
#define ADC1_CFG_REG_CLKS_Msk     (0x1UL << ADC1_CFG_REG_CLKS_Pos)
#define ADC1_CFG_REG_CLKS         ADC1_CFG_REG_CLKS_Msk

#define ADC1_CFG_REG_SAMPLE_Pos   3
#define ADC1_CFG_REG_SAMPLE_Msk   (0x1UL << ADC1_CFG_REG_SAMPLE_Pos)
#define ADC1_CFG_REG_SAMPLE       ADC1_CFG_REG_SAMPLE_Msk

#define ADC1_CFG_REG_CHS_Pos      4
#define ADC1_CFG_REG_CHS_Msk      (0x1FUL << ADC1_CFG_REG_CHS_Pos)

#define ADC1_CFG_REG_CHCH_Pos     9
#define ADC1_CFG_REG_CHCH_Msk     (0x1UL << ADC1_CFG_REG_CHCH_Pos)
#define ADC1_CFG_REG_CHCH         ADC1_CFG_REG_CHCH_Msk

#define ADC1_CFG_REG_RNGC_Pos     10
#define ADC1_CFG_REG_RNGC_Msk     (0x1UL << ADC1_CFG_REG_RNGC_Pos)
#define ADC1_CFG_REG_RNGC         ADC1_CFG_REG_RNGC_Msk

#define ADC1_CFG_M_REF_Pos        11
#define ADC1_CFG_M_REF_Msk        (0x1UL << ADC1_CFG_M_REF_Pos)
#define ADC1_CFG_M_REF            ADC1_CFG_M_REF_Msk

#define ADC1_CFG_REG_DIVCLK_Pos   12
#define ADC1_CFG_REG_DIVCLK_Msk   (0xFUL << ADC1_CFG_REG_DIVCLK_Pos)

#define ADC1_CFG_TS_EN_Pos        17
#define ADC1_CFG_TS_EN_Msk        (0x1UL << ADC1_CFG_TS_EN_Pos)
#define ADC1_CFG_TS_EN            ADC1_CFG_TS_EN_Msk

#define ADC1_CFG_TS_BUF_EN_Pos    18
#define ADC1_CFG_TS_BUF_EN_Msk    (0x1UL << ADC1_CFG_TS_BUF_EN_Pos)
#define ADC1_CFG_TS_BUF_EN        ADC1_CFG_TS_BUF_EN_Msk

#define ADC1_CFG_SEL_TS_Pos       19
#define ADC1_CFG_SEL_TS_Msk       (0x1UL << ADC1_CFG_SEL_TS_Pos)
#define ADC1_CFG_SEL_TS           ADC1_CFG_SEL_TS_Msk

#define ADC1_CFG_SEL_VREF_Pos     20
#define ADC1_CFG_SEL_VREF_Msk     (0x1UL << ADC1_CFG_SEL_VREF_Pos)
#define ADC1_CFG_SEL_VREF         ADC1_CFG_SEL_VREF_Msk

#define ADC1_CFG_DELAY_GO_Pos     25
#define ADC1_CFG_DELAY_GO_Msk     (0x7UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_0 (0x0UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_1 (0x1UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_2 (0x2UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_3 (0x3UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_4 (0x4UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_5 (0x5UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_6 (0x6UL << ADC1_CFG_DELAY_GO_Pos)
#define ADC1_CFG_DELAY_GO_PCLKd_7 (0x7UL << ADC1_CFG_DELAY_GO_Pos)

#define ADC1_CFG_DELAY_ADC_Pos    28
#define ADC1_CFG_DELAY_ADC_Msk    (0xFUL << ADC1_CFG_DELAY_ADC_Pos)

/** @} */ /* End of group MDR32F21QI_ADC1_CFG */

/** @defgroup MDR32F21QI_ADC2_CFG ADC2_CFG
 * @{
 */

#define ADC2_CFG_ADC1_OP_Pos 17
#define ADC2_CFG_ADC1_OP_Msk (0x1UL << ADC2_CFG_ADC1_OP_Pos)
#define ADC2_CFG_ADC1_OP     ADC2_CFG_ADC1_OP_Msk

/** @} */ /* End of group MDR32F21QI_ADC2_CFG */

/** @defgroup MDR32F21QI_ADC1_H_LEVEL ADC1_H_LEVEL
 * @{
 */

#define ADC1_H_LEVEL_REG_H_LEVEL_Pos 0
#define ADC1_H_LEVEL_REG_H_LEVEL_Msk (0xFFFUL << ADC1_H_LEVEL_REG_H_LEVEL_Pos)

/** @} */ /* End of group MDR32F21QI_ADC1_H_LEVEL */

/** @defgroup MDR32F21QI_ADC1_L_LEVEL ADC1_L_LEVEL
 * @{
 */

#define ADC1_L_LEVEL_REG_L_LEVEL_Pos 0
#define ADC1_L_LEVEL_REG_L_LEVEL_Msk (0xFFFUL << ADC1_L_LEVEL_REG_L_LEVEL_Pos)

/** @} */ /* End of group MDR32F21QI_ADC1_L_LEVEL */

/** @defgroup MDR32F21QI_ADC1_RESULT ADC1_RESULT
 * @{
 */

#define ADC1_RESULT_RESULT_Pos  0
#define ADC1_RESULT_RESULT_Msk  (0xFFFUL << ADC1_RESULT_RESULT_Pos)

#define ADC1_RESULT_CHANNEL_Pos 16
#define ADC1_RESULT_CHANNEL_Msk (0xFFFUL << ADC1_RESULT_CHANNEL_Pos)

/** @} */ /* End of group MDR32F21QI_ADC1_RESULT */

/** @defgroup MDR32F21QI_ADC1_STATUS ADC1_STATUS
 * @{
 */

#define ADC1_STATUS_FLG_REG_OVERWRITE_Pos 0
#define ADC1_STATUS_FLG_REG_OVERWRITE_Msk (0x1UL << ADC1_STATUS_FLG_REG_OVERWRITE_Pos)
#define ADC1_STATUS_FLG_REG_OVERWRITE     ADC1_STATUS_FLG_REG_OVERWRITE_Msk

#define ADC1_STATUS_FLG_REG_AWOIFEN_Pos   1
#define ADC1_STATUS_FLG_REG_AWOIFEN_Msk   (0x1UL << ADC1_STATUS_FLG_REG_AWOIFEN_Pos)
#define ADC1_STATUS_FLG_REG_AWOIFEN       ADC1_STATUS_FLG_REG_AWOIFEN_Msk

#define ADC1_STATUS_FLG_REG_EOCIF_Pos     2
#define ADC1_STATUS_FLG_REG_EOCIF_Msk     (0x1UL << ADC1_STATUS_FLG_REG_EOCIF_Pos)
#define ADC1_STATUS_FLG_REG_EOCIF         ADC1_STATUS_FLG_REG_EOCIF_Msk

#define ADC1_STATUS_AWOIF_IE_Pos          3
#define ADC1_STATUS_AWOIF_IE_Msk          (0x1UL << ADC1_STATUS_AWOIF_IE_Pos)
#define ADC1_STATUS_AWOIF_IE              ADC1_STATUS_AWOIF_IE_Msk

#define ADC1_STATUS_ECOIF_IE_Pos          4
#define ADC1_STATUS_ECOIF_IE_Msk          (0x1UL << ADC1_STATUS_ECOIF_IE_Pos)
#define ADC1_STATUS_ECOIF_IE              ADC1_STATUS_ECOIF_IE_Msk

/** @} */ /* End of group MDR32F21QI_ADC1_STATUS */

/** @defgroup MDR32F21QI_ADC1_CHSEL ADC1_CHSEL
 * @{
 */

#define ADC1_CHSEL_SL_CH_CH_REF0_Pos  0
#define ADC1_CHSEL_SL_CH_CH_REF0_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF0_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF0      ADC1_CHSEL_SL_CH_CH_REF0_Msk

#define ADC1_CHSEL_SL_CH_CH_REF1_Pos  1
#define ADC1_CHSEL_SL_CH_CH_REF1_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF1_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF1      ADC1_CHSEL_SL_CH_CH_REF1_Msk

#define ADC1_CHSEL_SL_CH_CH_REF2_Pos  2
#define ADC1_CHSEL_SL_CH_CH_REF2_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF2_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF2      ADC1_CHSEL_SL_CH_CH_REF2_Msk

#define ADC1_CHSEL_SL_CH_CH_REF3_Pos  3
#define ADC1_CHSEL_SL_CH_CH_REF3_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF3_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF3      ADC1_CHSEL_SL_CH_CH_REF3_Msk

#define ADC1_CHSEL_SL_CH_CH_REF4_Pos  4
#define ADC1_CHSEL_SL_CH_CH_REF4_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF4_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF4      ADC1_CHSEL_SL_CH_CH_REF4_Msk

#define ADC1_CHSEL_SL_CH_CH_REF5_Pos  5
#define ADC1_CHSEL_SL_CH_CH_REF5_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF5_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF5      ADC1_CHSEL_SL_CH_CH_REF5_Msk

#define ADC1_CHSEL_SL_CH_CH_REF6_Pos  6
#define ADC1_CHSEL_SL_CH_CH_REF6_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF6_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF6      ADC1_CHSEL_SL_CH_CH_REF6_Msk

#define ADC1_CHSEL_SL_CH_CH_REF7_Pos  7
#define ADC1_CHSEL_SL_CH_CH_REF7_Msk  (0x1UL << ADC1_CHSEL_SL_CH_CH_REF7_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF7      ADC1_CHSEL_SL_CH_CH_REF7_Msk

#define ADC1_CHSEL_SL_CH_CH_REF30_Pos 30
#define ADC1_CHSEL_SL_CH_CH_REF30_Msk (0x1UL << ADC1_CHSEL_SL_CH_CH_REF30_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF30     ADC1_CHSEL_SL_CH_CH_REF30_Msk

#define ADC1_CHSEL_SL_CH_CH_REF31_Pos 31
#define ADC1_CHSEL_SL_CH_CH_REF31_Msk (0x1UL << ADC1_CHSEL_SL_CH_CH_REF31_Pos)
#define ADC1_CHSEL_SL_CH_CH_REF31     ADC1_CHSEL_SL_CH_CH_REF31_Msk

/** @} */ /* End of group MDR32F21QI_ADC1_CHSEL */

/** @defgroup MDR32F21QI_ADC1_TRIM ADC1_TRIM
 * @{
 */

#define ADC1_TRIM_TS_TRIM_Pos      1
#define ADC1_TRIM_TS_TRIM_Msk      (0x1FUL << ADC1_TRIM_TS_TRIM_Pos)

#define ADC1_TRIM_SEL_VREF_BUF_Pos 6
#define ADC1_TRIM_SEL_VREF_BUF_Msk (0x1UL << ADC1_TRIM_SEL_VREF_BUF_Pos)
#define ADC1_TRIM_SEL_VREF_BUF     ADC1_TRIM_SEL_VREF_BUF_Msk

/** @} */ /* End of group MDR32F21QI_ADC1_TRIM */

/** @} */ /* End of group MDR32F21QI_ADC_Defines */

/** @} */ /* End of group MDR32F21QI_ADC */

/** @defgroup MDR32F21QI_WWDG MDR_WWDG
 * @{
 */

/**
 * @brief MDR32F21QI WWDG control structure
 */
typedef struct {
    __IO uint32_t CR;  /*!<WWDG Command Register */
    __IO uint32_t CFR; /*!<WWDG Configuration Register */
    __IO uint32_t SR;  /*!<WWDG Status Register */
} MDR_WWDG_TypeDef;

/** @defgroup MDR32F21QI_IWDG_Defines IWDG Defines
 * @{
 */

/** @defgroup MDR32F21QI_WWDG_CR WWDG_CR
 * @{
 */

#define WWDG_CR_T_Pos    0
#define WWDG_CR_T_Msk    (0x7FUL << WWDG_CR_T_Pos)

#define WWDG_CR_WDGA_Pos 7
#define WWDG_CR_WDGA_Msk (0x1UL << WWDG_CR_WDGA_Pos)
#define WWDG_CR_WDGA     WWDG_CR_WDGA_Msk

/** @} */ /* End of group MDR32F21QI_WWDG_CR */

/** @defgroup MDR32F21QI_WWDG_CFR WWDG CFR
 * @{
 */

#define WWDG_CFR_W_Pos    0
#define WWDG_CFR_W_Msk    (0x7FUL << WWDG_CFR_W_Pos)

#define WWDG_CFR_WGTB_Pos 7
#define WWDG_CFR_WGTB_Msk ((uint32_t)0x3UL << WWDG_CFR_WGTB_Pos)

#define WWDG_CFR_EWI_Pos  9
#define WWDG_CFR_EWI_Msk  ((uint32_t)0x1UL << WWDG_CFR_EWI_Pos)
#define WWDG_CFR_EWI      WWDG_CFR_EWI_Msk

/** @} */ /* End of group MDR32F21QI_WWDG_CFR */

/** @defgroup MDR32F21QI_WWDG_SR WWDG_SR
 * @{
 */

#define WWDG_SR_EWIF_Pos 0
#define WWDG_SR_EWIF_Msk (0x1UL << WWDG_SR_EWIF_Pos)
#define WWDG_SR_EWIF     WWDG_SR_EWIF_Msk

/** @} */ /* End of group MDR32F21QI_WWDG_SR */

/** @} */ /* End of group MDR32F21QI_WWDG_Defines */

/** @} */ /* End of group MDR32F21QI_WWDG */

/** @defgroup MDR32F21QI_IWDG MDR_IWDG
 * @{
 */

/**
 * @brief MDR32F21QI IWDG control structure
 */
typedef struct {
    __IO uint32_t KR;  /*!<IWDG Key Register */
    __IO uint32_t PR;  /*!<IWDG Clock Prescaler Register */
    __IO uint32_t RLR; /*!<IWDG Reload Register */
    __IO uint32_t SR;  /*!<IWDG Status Register */
} MDR_IWDG_TypeDef;

/** @defgroup MDR32F21QI_IWDG_Defines IWDG Defines
 * @{
 */

/** @defgroup MDR32F21QI_IWDG_KR IWDG_KR
 * @{
 */

#define IWDG_KR_KEY_Pos 0
#define IWDG_KR_KEY_Msk (0xFFFFUL << IWDG_KR_KEY_Pos)

/** @} */ /* End of group MDR32F21QI_IWDG_KR */

/** @defgroup MDR32F21QI_IWDG_PR IWDG_PR
 * @{
 */

#define IWDG_PR_PR_Pos    0
#define IWDG_PR_PR_Msk    (0x7UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_DIV4   (0x0UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_DIV8   (0x1UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_DIV16  (0x2UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_DIV32  (0x3UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_DIV64  (0x4UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_DIV128 (0x5UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_DIV256 (0x6UL << IWDG_PR_PR_Pos)

/** @} */ /* End of group MDR32F21QI_IWDG_PR */

/** @defgroup MDR32F21QI_IWDG_RLR IWDG_RLR
 * @{
 */

#define IWDG_RLR_RLR_Pos 0
#define IWDG_RLR_RLR_Msk (0xFFFUL << IWDG_RLR_RLR_Pos)

/** @} */ /* End of group MDR32F21QI_IWDG_RLR */

/** @defgroup MDR32F21QI_IWDG_SR IWDG_SR
 * @{
 */

#define IWDG_SR_PVU_Pos 0
#define IWDG_SR_PVU_Msk (0x1UL << IWDG_SR_PVU_Pos)
#define IWDG_SR_PVU     IWDG_SR_PVU_Msk

#define IWDG_SR_RVU_Pos 1
#define IWDG_SR_RVU_Msk (0x1UL << IWDG_SR_RVU_Pos)
#define IWDG_SR_RVU     IWDG_SR_RVU_Msk

/** @} */ /* End of group MDR32F21QI_IWDG_SR */

/** @} */ /* End of group MDR32F21QI_IWDG_Defines */

/** @} */ /* End of group MDR32F21QI_IWDG */

/** @defgroup MDR32F21QI_POWER MDR_POWER
 * @{
 */

/**
 * @brief MDR32F21QI POWER control structure
 */
typedef struct {
    __IO uint32_t PVDCS; /*!<POWER Power Detector Control/Status Register */
} MDR_POWER_TypeDef;

/** @defgroup MDR32F21QI_POWER_Defines POWER Defines
 * @{
 */

/** @defgroup MDR32F21QI_POWER_PVDCS POWER_PVDCS
 * @{
 */

#define POWER_PVDCS_PVDEN_Pos  0
#define POWER_PVDCS_PVDEN_Msk  (0x1UL << POWER_PVDCS_PVDEN_Pos)
#define POWER_PVDCS_PVDEN      POWER_PVDCS_PVDEN_Msk

#define POWER_PVDCS_PBLS_Pos   1
#define POWER_PVDCS_PBLS_Msk   (0x3UL << POWER_PVDCS_PBLS_Pos)
#define POWER_PVDCS_PBLS_1p8V  (0x0UL << POWER_PVDCS_PBLS_Pos)
#define POWER_PVDCS_PBLS_2p2V  (0x1UL << POWER_PVDCS_PBLS_Pos)
#define POWER_PVDCS_PBLS_2p6V  (0x2UL << POWER_PVDCS_PBLS_Pos)
#define POWER_PVDCS_PBLS_3p0V  (0x3UL << POWER_PVDCS_PBLS_Pos)

#define POWER_PVDCS_PLS_Pos    3
#define POWER_PVDCS_PLS_Msk    (0x7UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_2p0V   (0x0UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_2p2V   (0x1UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_2p4V   (0x2UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_2p6V   (0x3UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_2p8V   (0x4UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_3p0V   (0x5UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_3p2V   (0x6UL << POWER_PVDCS_PLS_Pos)
#define POWER_PVDCS_PLS_3p4V   (0x7UL << POWER_PVDCS_PLS_Pos)

#define POWER_PVDCS_PVBD_Pos   6
#define POWER_PVDCS_PVBD_Msk   (0x1UL << POWER_PVDCS_PVBD_Pos)
#define POWER_PVDCS_PVBD       POWER_PVDCS_PVBD_Msk

#define POWER_PVDCS_PVD_Pos    7
#define POWER_PVDCS_PVD_Msk    (0x1UL << POWER_PVDCS_PVD_Pos)
#define POWER_PVDCS_PVD        POWER_PVDCS_PVD_Msk

#define POWER_PVDCS_IEPVBD_Pos 8
#define POWER_PVDCS_IEPVBD_Msk (0x1UL << POWER_PVDCS_IEPVBD_Pos)
#define POWER_PVDCS_IEPVBD     POWER_PVDCS_IEPVBD_Msk

#define POWER_PVDCS_IEPVD_Pos  9
#define POWER_PVDCS_IEPVD_Msk  (0x1UL << POWER_PVDCS_IEPVD_Pos)
#define POWER_PVDCS_IEPVD      POWER_PVDCS_IEPVD_Msk

#define POWER_PVDCS_INVB_Pos   10
#define POWER_PVDCS_INVB_Msk   (0x1UL << POWER_PVDCS_INVB_Pos)
#define POWER_PVDCS_INVB       POWER_PVDCS_INVB_Msk

#define POWER_PVDCS_INV_Pos    11
#define POWER_PVDCS_INV_Msk    (0x1UL << POWER_PVDCS_INV_Pos)
#define POWER_PVDCS_INV        POWER_PVDCS_INV_Msk

#define POWER_PVDCS_PVDBEN_Pos 12
#define POWER_PVDCS_PVDBEN_Msk (0x1UL << POWER_PVDCS_PVDBEN_Pos)
#define POWER_PVDCS_PVDBEN     POWER_PVDCS_PVDBEN_Msk

/** @} */ /* End of group MDR32F21QI_POWER_PVDCS */

/** @} */ /* End of group MDR32F21QI_POWER_Defines */

/** @} */ /* End of group MDR32F21QI_POWER */

/** @defgroup MDR32F21QI_BKP MDR_BKP
 * @{
 */

/**
 * @brief MDR32F21QI BKP and RTC control structure
 */
typedef struct {
    __IO uint32_t REG_00;   /*!<BKP Register 0 */
    __IO uint32_t REG_01;   /*!<BKP Register 1 */
    __IO uint32_t REG_02;   /*!<BKP Register 2 */
    __IO uint32_t REG_03;   /*!<BKP Register 3 */
    __IO uint32_t REG_04;   /*!<BKP Register 4 */
    __IO uint32_t REG_05;   /*!<BKP Register 5 */
    __IO uint32_t REG_06;   /*!<BKP Register 6 */
    __IO uint32_t REG_07;   /*!<BKP Register 7 */
    __IO uint32_t REG_08;   /*!<BKP Register 8 */
    __IO uint32_t REG_09;   /*!<BKP Register 9 */
    __IO uint32_t REG_0A;   /*!<BKP Register 10 */
    __IO uint32_t REG_0B;   /*!<BKP Register 11 */
    __IO uint32_t REG_0C;   /*!<BKP Register 12 */
    __IO uint32_t REG_0D;   /*!<BKP Register 13 */
    __IO uint32_t REG_0E;   /*!<BKP Register 14 (PSS Control Register) */
    __IO uint32_t REG_0F;   /*!<BKP Register 15 (RTC & Generator Control Register) */
    __IO uint32_t RTC_CNT;  /*!<RTC Counter Register */
    __IO uint32_t RTC_DIV;  /*!<RTC Prescaler Counter Register */
    __IO uint32_t RTC_PRL;  /*!<RTC Prescaler Reload Value Register */
    __IO uint32_t RTC_ALRM; /*!<RTC Alarm Register */
    __IO uint32_t RTC_CS;   /*!<RTC Control and Status Register */
} MDR_BKP_TypeDef;

/** @defgroup MDR32F21QI_BKP_Defines BKP Defines
 * @{
 */

/** @defgroup MDR32F21QI_BKP_REG_00 BKP_REG_00
 * @{
 */

#define BKP_REG_00_BKP_REG_Pos 0
#define BKP_REG_00_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_00_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_00 */

/** @defgroup MDR32F21QI_BKP_REG_01 BKP_REG_01
 * @{
 */

#define BKP_REG_01_BKP_REG_Pos 0
#define BKP_REG_01_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_01_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_01 */

/** @defgroup MDR32F21QI_BKP_REG_02 BKP_REG_02
 * @{
 */

#define BKP_REG_02_BKP_REG_Pos 0
#define BKP_REG_02_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_02_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_02 */

/** @defgroup MDR32F21QI_BKP_REG_03 BKP_REG_03
 * @{
 */

#define BKP_REG_03_BKP_REG_Pos 0
#define BKP_REG_03_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_03_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_03 */

/** @defgroup MDR32F21QI_BKP_REG_04 BKP_REG_04
 * @{
 */

#define BKP_REG_04_BKP_REG_Pos 0
#define BKP_REG_04_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_04_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_04 */

/** @defgroup MDR32F21QI_BKP_REG_05 BKP_REG_05
 * @{
 */

#define BKP_REG_05_BKP_REG_Pos 0
#define BKP_REG_05_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_05_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_05 */

/** @defgroup MDR32F21QI_BKP_REG_06 BKP_REG_06
 * @{
 */

#define BKP_REG_06_BKP_REG_Pos 0
#define BKP_REG_06_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_06_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_06 */

/** @defgroup MDR32F21QI_BKP_REG_07 BKP_REG_07
 * @{
 */

#define BKP_REG_07_BKP_REG_Pos 0
#define BKP_REG_07_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_07_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_07 */

/** @defgroup MDR32F21QI_BKP_REG_08 BKP_REG_08
 * @{
 */

#define BKP_REG_08_BKP_REG_Pos 0
#define BKP_REG_08_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_08_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_08 */

/** @defgroup MDR32F21QI_BKP_REG_09 BKP_REG_09
 * @{
 */

#define BKP_REG_09_BKP_REG_Pos 0
#define BKP_REG_09_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_09_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_09 */

/** @defgroup MDR32F21QI_BKP_REG_0A BKP_REG_0A
 * @{
 */

#define BKP_REG_0A_BKP_REG_Pos 0
#define BKP_REG_0A_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_0A_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_0A */

/** @defgroup MDR32F21QI_BKP_REG_0B BKP_REG_0B
 * @{
 */

#define BKP_REG_0B_BKP_REG_Pos 0
#define BKP_REG_0B_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_0B_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_0B */

/** @defgroup MDR32F21QI_BKP_REG_0C BKP_REG_0C
 * @{
 */

#define BKP_REG_0C_BKP_REG_Pos 0
#define BKP_REG_0C_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_0C_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_0C */

/** @defgroup MDR32F21QI_BKP_REG_0D BKP_REG_0D
 * @{
 */

#define BKP_REG_0D_BKP_REG_Pos 0
#define BKP_REG_0D_BKP_REG_Msk (0xFFFFFFFFUL << BKP_REG_0D_BKP_REG_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_REG_0D */

/** @defgroup MDR32F21QI_BKP_REG_0E BKP_REG_0E
 * @{
 */

#define BKP_REG_0E_LOW_Pos             0
#define BKP_REG_0E_LOW_Msk             (0x7UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_UPTO_10MHz  (0x0UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_UPTO_200kHz (0x1UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_UPTO_500kHz (0x2UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_UPTO_1MHz   (0x3UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_OFF         (0x4UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_UPTO_40MHz  (0x5UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_UPTO_80MHz  (0x6UL << BKP_REG_0E_LOW_Pos)
#define BKP_REG_0E_LOW_CLK_OVER_80MHz  (0x7UL << BKP_REG_0E_LOW_Pos)

#define BKP_REG_0E_SELECTRI_Pos        3
#define BKP_REG_0E_SELECTRI_Msk        (0x7UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_6k    (0x0UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_270k  (0x1UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_90k   (0x2UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_24k   (0x3UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_900k  (0x4UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_2k    (0x5UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_400   (0x6UL << BKP_REG_0E_SELECTRI_Pos)
#define BKP_REG_0E_SELECTRI_LOAD_100   (0x7UL << BKP_REG_0E_SELECTRI_Pos)

#define BKP_REG_0E_SW_EN_Pos           6
#define BKP_REG_0E_SW_EN_Msk           (0x3UL << BKP_REG_0E_SW_EN_Pos)
#define BKP_REG_0E_SW_EN_SW_DISABLED   (0x0UL << BKP_REG_0E_SW_EN_Pos)
#define BKP_REG_0E_SW_EN_SW_ENABLED_1  (0x1UL << BKP_REG_0E_SW_EN_Pos)
#define BKP_REG_0E_SW_EN_SW_ENABLED_2  (0x2UL << BKP_REG_0E_SW_EN_Pos)
#define BKP_REG_0E_SW_EN_SW_ENABLED_3  (0x3UL << BKP_REG_0E_SW_EN_Pos)

#define BKP_REG_0E_TRIM20_Pos          8
#define BKP_REG_0E_TRIM20_Msk          (0x7UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_PLUS_100mV   (0x0UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_PLUS_060mV   (0x1UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_PLUS_040mV   (0x2UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_PLUS_010mV   (0x3UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_MINUS_010mV  (0x4UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_MINUS_040mV  (0x5UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_MINUS_060mV  (0x6UL << BKP_REG_0E_TRIM20_Pos)
#define BKP_REG_0E_TRIM20_MINUS_100mV  (0x7UL << BKP_REG_0E_TRIM20_Pos)

#define BKP_REG_0E_FPOR_Pos            11
#define BKP_REG_0E_FPOR_Msk            (0x1UL << BKP_REG_0E_FPOR_Pos)
#define BKP_REG_0E_FPOR                BKP_REG_0E_FPOR_Msk

#define BKP_REG_0E_TRIM43_Pos          12
#define BKP_REG_0E_TRIM43_Msk          (0x3UL << BKP_REG_0E_TRIM43_Pos)
#define BKP_REG_0E_TRIM43_1p8V         (0x0UL << BKP_REG_0E_TRIM43_Pos)
#define BKP_REG_0E_TRIM43_1p6V         (0x1UL << BKP_REG_0E_TRIM43_Pos)
#define BKP_REG_0E_TRIM43_1p4V         (0x2UL << BKP_REG_0E_TRIM43_Pos)
#define BKP_REG_0E_TRIM43_1p2V         (0x3UL << BKP_REG_0E_TRIM43_Pos)

#define BKP_REG_0E_COV_DET_Pos         14
#define BKP_REG_0E_COV_DET_Msk         (0x1UL << BKP_REG_0E_COV_DET_Pos)
#define BKP_REG_0E_COV_DET             BKP_REG_0E_COV_DET_Msk

#define BKP_REG_0E_ILIMEN_Pos          15
#define BKP_REG_0E_ILIMEN_Msk          (0x1UL << BKP_REG_0E_ILIMEN_Pos)
#define BKP_REG_0E_ILIMEN              BKP_REG_0E_ILIMEN_Msk

/** @} */ /* End of group MDR32F21QI_BKP_REG_0E */

/** @defgroup MDR32F21QI_BKP_REG_0F BKP_REG_0F
 * @{
 */

#define BKP_REG_0F_LSE_ON_Pos      0
#define BKP_REG_0F_LSE_ON_Msk      (0x1UL << BKP_REG_0F_LSE_ON_Pos)
#define BKP_REG_0F_LSE_ON          BKP_REG_0F_LSE_ON_Msk

#define BKP_REG_0F_LSE_BYP_Pos     1
#define BKP_REG_0F_LSE_BYP_Msk     (0x1UL << BKP_REG_0F_LSE_BYP_Pos)
#define BKP_REG_0F_LSE_BYP         BKP_REG_0F_LSE_BYP_Msk

#define BKP_REG_0F_RTC_SEL_Pos     2
#define BKP_REG_0F_RTC_SEL_Msk     (0x3UL << BKP_REG_0F_RTC_SEL_Pos)
#define BKP_REG_0F_RTC_SEL_LSI     (0x0UL << BKP_REG_0F_RTC_SEL_Pos)
#define BKP_REG_0F_RTC_SEL_LSE     (0x1UL << BKP_REG_0F_RTC_SEL_Pos)
#define BKP_REG_0F_RTC_SEL_HSI_RTC (0x2UL << BKP_REG_0F_RTC_SEL_Pos)
#define BKP_REG_0F_RTC_SEL_HSE_RTC (0x3UL << BKP_REG_0F_RTC_SEL_Pos)

#define BKP_REG_0F_RTC_EN_Pos      4
#define BKP_REG_0F_RTC_EN_Msk      (0x1UL << BKP_REG_0F_RTC_EN_Pos)
#define BKP_REG_0F_RTC_EN          BKP_REG_0F_RTC_EN_Msk

#define BKP_REG_0F_RTC_CAL_Pos     5
#define BKP_REG_0F_RTC_CAL_Msk     (0xFFUL << BKP_REG_0F_RTC_CAL_Pos)

#define BKP_REG_0F_LSE_RDY_Pos     13
#define BKP_REG_0F_LSE_RDY_Msk     (0x1UL << BKP_REG_0F_LSE_RDY_Pos)
#define BKP_REG_0F_LSE_RDY         BKP_REG_0F_LSE_RDY_Msk

#define BKP_REG_0F_LSI_ON_Pos      15
#define BKP_REG_0F_LSI_ON_Msk      (0x1UL << BKP_REG_0F_LSI_ON_Pos)
#define BKP_REG_0F_LSI_ON          BKP_REG_0F_LSI_ON_Msk

#define BKP_REG_0F_LSI_TRIM_Pos    16
#define BKP_REG_0F_LSI_TRIM_Msk    (0x1FUL << BKP_REG_0F_LSI_TRIM_Pos)

#define BKP_REG_0F_LSI_RDY_Pos     21
#define BKP_REG_0F_LSI_RDY_Msk     (0x1UL << BKP_REG_0F_LSI_RDY_Pos)
#define BKP_REG_0F_LSI_RDY         BKP_REG_0F_LSI_RDY_Msk

#define BKP_REG_0F_HSI_ON_Pos      22
#define BKP_REG_0F_HSI_ON_Msk      (0x1UL << BKP_REG_0F_HSI_ON_Pos)
#define BKP_REG_0F_HSI_ON          BKP_REG_0F_HSI_ON_Msk

#define BKP_REG_0F_HSI_RDY_Pos     23
#define BKP_REG_0F_HSI_RDY_Msk     (0x1UL << BKP_REG_0F_HSI_RDY_Pos)
#define BKP_REG_0F_HSI_RDY         BKP_REG_0F_HSI_RDY_Msk

#define BKP_REG_0F_HSI_TRIM_Pos    24
#define BKP_REG_0F_HSI_TRIM_Msk    (0x3FUL << BKP_REG_0F_HSI_TRIM_Pos)

#define BKP_REG_0F_STANDBY_Pos     30
#define BKP_REG_0F_STANDBY_Msk     (0x1UL << BKP_REG_0F_STANDBY_Pos)
#define BKP_REG_0F_STANDBY         BKP_REG_0F_STANDBY_Msk

#define BKP_REG_0F_RTC_RESET_Pos   31
#define BKP_REG_0F_RTC_RESET_Msk   (0x1UL << BKP_REG_0F_RTC_RESET_Pos)
#define BKP_REG_0F_RTC_RESET       BKP_REG_0F_RTC_RESET_Msk

/** @} */ /* End of group MDR32F21QI_BKP_REG_0F */

/** @defgroup MDR32F21QI_BKP_RTC_CNT BKP_RTC_CNT
 * @{
 */

#define BKP_RTC_CNT_RTC_CNT_Pos 0
#define BKP_RTC_CNT_RTC_CNT_Msk (0xFFFFFFFFUL << BKP_RTC_CNT_RTC_CNT_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_RTC_CNT */

/** @defgroup MDR32F21QI_BKP_RTC_DIV BKP_RTC_DIV
 * @{
 */

#define BKP_RTC_DIV_RTC_DIV_Pos 0
#define BKP_RTC_DIV_RTC_DIV_Msk (0xFFFFFUL << BKP_RTC_DIV_RTC_DIV_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_RTC_DIV */

/** @defgroup MDR32F21QI_BKP_RTC_PRL BKP_RTC_PRL
 * @{
 */

#define BKP_RTC_PRL_RTC_PRL_Pos 0
#define BKP_RTC_PRL_RTC_PRL_Msk (0xFFFFFUL << BKP_RTC_PRL_RTC_PRL_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_RTC_PRL */

/** @defgroup MDR32F21QI_BKP_RTC_ALRM BKP_RTC_ALRM
 * @{
 */

#define BKP_RTC_ALRM_RTC_ALRM_Pos 0
#define BKP_RTC_ALRM_RTC_ALRM_Msk (0xFFFFFFFFUL << BKP_RTC_ALRM_RTC_ALRM_Pos)

/** @} */ /* End of group MDR32F21QI_BKP_RTC_ALRM */

/** @defgroup MDR32F21QI_BKP_RTC_CS BKP_RTC_CS
 * @{
 */

#define BKP_RTC_CS_OWF_Pos     0
#define BKP_RTC_CS_OWF_Msk     (0x1UL << BKP_RTC_CS_OWF_Pos)
#define BKP_RTC_CS_OWF         BKP_RTC_CS_OWF_Msk

#define BKP_RTC_CS_SECF_Pos    1
#define BKP_RTC_CS_SECF_Msk    (0x1UL << BKP_RTC_CS_SECF_Pos)
#define BKP_RTC_CS_SECF        BKP_RTC_CS_SECF_Msk

#define BKP_RTC_CS_ALRF_Pos    2
#define BKP_RTC_CS_ALRF_Msk    (0x1UL << BKP_RTC_CS_ALRF_Pos)
#define BKP_RTC_CS_ALRF        BKP_RTC_CS_ALRF_Msk

#define BKP_RTC_CS_OWF_IE_Pos  3
#define BKP_RTC_CS_OWF_IE_Msk  (0x1UL << BKP_RTC_CS_OWF_IE_Pos)
#define BKP_RTC_CS_OWF_IE      BKP_RTC_CS_OWF_IE_Msk

#define BKP_RTC_CS_SECF_IE_Pos 4
#define BKP_RTC_CS_SECF_IE_Msk (0x1UL << BKP_RTC_CS_SECF_IE_Pos)
#define BKP_RTC_CS_SECF_IE     BKP_RTC_CS_SECF_IE_Msk

#define BKP_RTC_CS_ALRF_IE_Pos 5
#define BKP_RTC_CS_ALRF_IE_Msk (0x1UL << BKP_RTC_CS_ALRF_IE_Pos)
#define BKP_RTC_CS_ALRF_IE     BKP_RTC_CS_ALRF_IE_Msk

#define BKP_RTC_CS_WEC_Pos     6
#define BKP_RTC_CS_WEC_Msk     (0x1UL << BKP_RTC_CS_WEC_Pos)
#define BKP_RTC_CS_WEC         BKP_RTC_CS_WEC_Msk

/** @} */ /* End of group MDR32F21QI_BKP_RTC_CS */

/** @} */ /* End of group MDR32F21QI_BKP_Defines */

/** @} */ /* End of group MDR32F21QI_BKP */

/** @defgroup MDR32F21QI_ADCUI ADCUI
 * @{
 */

/**
 * @brief MDR32F21QI ADCUI control structure
 */
typedef struct {
    __IO uint32_t CTRL1;   /*!<ADCUI General Control1 Register */
    __IO uint32_t CTRL2;   /*!<ADCUI General control2 Register */
    __IO uint32_t CTRL3;   /*!<ADCUI General Control3 Register */
    __IO uint32_t F0CTR;   /*!<ADCUI Control Register for channel F0 */
    __IO uint32_t F0WC;    /*!<ADCUI Active Power Calculation Control Register for Channel F0 */
    __IO uint32_t F0WATTP; /*!<ADCUI Positive Active Power Value Register for Channel F0 */
    __IO uint32_t F0WATTN; /*!<ADCUI Negative Active Power Value Register for Channel F0 */
    __IO uint32_t F0VC;    /*!<ADCUI Reactive Power Calculation Control Register for Channel F0 */
    __IO uint32_t F0VARP;  /*!<ADCUI Positive Reactive Power Value Register for Channel F0 */
    __IO uint32_t F0VARN;  /*!<ADCUI Negative Reactive Power Value Register for Channel F0 */
    __IO uint32_t F0AC;    /*!<ADCUI Apparent Power Calculation Control Register for Channel F0 */
    __IO uint32_t F0VR;    /*!<ADCUI Apparent Power Value Register for Channel F0 */
    __IO uint32_t F0MD0;   /*!<ADCUI Parameters0 Register for Channel F0 */
    __IO uint32_t F0MD1;   /*!<ADCUI Parameters1 Register for Channel F0 */
    __IO uint32_t F0VPEAK; /*!<ADCUI Register of Peak Value in Voltage Channel in Channel F0 */
    __IO uint32_t F0IPEAK; /*!<ADCUI Register of Peak Calue in Current Channel in Channel F0 */
    __IO uint32_t F0VDAT;  /*!<ADCUI Voltage Register V0 for Channel F0 */
    __IO uint32_t F0I0DAT; /*!<ADCUI Current Register I0 for Channel F0 */
    __IO uint32_t F0I3DAT; /*!<ADCUI Current Register I3 for Channel F0 */
    __IO uint32_t F0VRMS;  /*!<ADCUI RMS Value Channel Voltage F0 Register */
    __IO uint32_t F0VRMS2; /*!<ADCUI RMS Squared in F0 Voltage Channel Register */
    __IO uint32_t F0IRMS;  /*!<ADCUI RMS Current Channel F0 Register */
    __IO uint32_t F0IRMS2; /*!<ADCUI RMS Squared in Current Channel F0 Register */
    __IO uint32_t F0STAT;  /*!<ADCUI Channel status F0 Register */
    __IO uint32_t F0MASK;  /*!<ADCUI F0 Channel Interrupt Mask */
    __IO uint32_t F1CTR;   /*!<ADCUI Control Register for channel F1 */
    __IO uint32_t F1WC;    /*!<ADCUI Active Power Calculation Control Register for Channel F1 */
    __IO uint32_t F1WATTP; /*!<ADCUI Positive Active Power Value Register for Channel F1 */
    __IO uint32_t F1WATTN; /*!<ADCUI Negative Active Power Value Register for Channel F1 */
    __IO uint32_t F1VC;    /*!<ADCUI Reactive Power Calculation Control Register for Channel F1 */
    __IO uint32_t F1VARP;  /*!<ADCUI Positive Reactive Power Value Register for Channel F1 */
    __IO uint32_t F1VARN;  /*!<ADCUI Negative Reactive Power Value Register for Channel F1 */
    __IO uint32_t F1AC;    /*!<ADCUI Apparent Power Calculation Control Register for Channel F1 */
    __IO uint32_t F1VR;    /*!<ADCUI Apparent Power Value Register for Channel F1 */
    __IO uint32_t F1MD0;   /*!<ADCUI Parameters0 Register for Channel F1 */
    __IO uint32_t F1MD1;   /*!<ADCUI Parameters1 Register for Channel F1 */
    __IO uint32_t F1MD2;   /*!<ADCUI Parameters2 Register for Channel F1 */
    __IO uint32_t F1VPEAK; /*!<ADCUI Register of Peak Value in Voltage Channel in Channel F1 */
    __IO uint32_t F1IPEAK; /*!<ADCUI Register of Peak Calue in Current Channel in Channel F1 */
    __IO uint32_t F1VDAT;  /*!<ADCUI Voltage Register V1 for Channel F1 */
    __IO uint32_t F1IDAT;  /*!<ADCUI Current Register I1 for Channel F1 */
    __IO uint32_t F1VRMS;  /*!<ADCUI RMS Value Channel Voltage F1 Register */
    __IO uint32_t F1VRMS2; /*!<ADCUI RMS Squared in F1 Voltage Channel Register */
    __IO uint32_t F1IRMS;  /*!<ADCUI RMS Current Channel F1 Register */
    __IO uint32_t F1IRMS2; /*!<ADCUI RMS Squared in Current Channel F1 Register */
    __IO uint32_t F1STAT;  /*!<ADCUI Channel status F1 Register */
    __IO uint32_t F1MASK;  /*!<ADCUI F1 Channel Interrupt Mask */
    __IO uint32_t F2CTR;   /*!<ADCUI Control Register for channel F2 */
    __IO uint32_t F2WC;    /*!<ADCUI Active Power Calculation Control Register for Channel F2 */
    __IO uint32_t F2WATTP; /*!<ADCUI Positive Active Power Value Register for Channel F2 */
    __IO uint32_t F2WATTN; /*!<ADCUI Negative Active Power Value Register for Channel F2 */
    __IO uint32_t F2VC;    /*!<ADCUI Reactive Power Calculation Control Register for Channel F2 */
    __IO uint32_t F2VARP;  /*!<ADCUI Positive Reactive Power Value Register for Channel F2 */
    __IO uint32_t F2VARN;  /*!<ADCUI Negative Reactive Power Value Register for Channel F2 */
    __IO uint32_t F2AC;    /*!<ADCUI Apparent Power Calculation Control Register for Channel F2 */
    __IO uint32_t F2VR;    /*!<ADCUI Apparent Power Value Register for Channel F2 */
    __IO uint32_t F2MD0;   /*!<ADCUI Parameters0 Register for Channel F2 */
    __IO uint32_t F2MD1;   /*!<ADCUI Parameters1 Register for Channel F2 */
    __IO uint32_t F2MD2;   /*!<ADCUI Parameters2 Register for Channel F2 */
    __IO uint32_t F2VPEAK; /*!<ADCUI Register of Peak Value in Voltage Channel in Channel F2 */
    __IO uint32_t F2IPEAK; /*!<ADCUI Register of Peak Calue in Current Channel in Channel F2 */
    __IO uint32_t F2VDAT;  /*!<ADCUI Voltage Register V2 for Channel F1 */
    __IO uint32_t F2IDAT;  /*!<ADCUI Current Register I2 for Channel F1 */
    __IO uint32_t F2VRMS;  /*!<ADCUI RMS Value Channel Voltage F2 Register */
    __IO uint32_t F2VRMS2; /*!<ADCUI RMS Squared in F2 Voltage Channel Register */
    __IO uint32_t F2IRMS;  /*!<ADCUI RMS Current Channel F2 Register */
    __IO uint32_t F2IRMS2; /*!<ADCUI RMS Squared in Current Channel F2 Register */
    __IO uint32_t F2STAT;  /*!<ADCUI Channel status F2 Register */
    __IO uint32_t F2MASK;  /*!<ADCUI F2 Channel Interrupt Mask */
    __IO uint32_t CCAL1;   /*!<ADCUI Current Channel Calibration Register 1 */
    __IO uint32_t CCAL2;   /*!<ADCUI Current Channel Calibration Register 2 */
    __IO uint32_t CCAL3;   /*!<ADCUI Current Channel Calibration Register 3 */
    __IO uint32_t CCAL4;   /*!<ADCUI Current channel calibration register 4 */
} MDR_ADCUI_TypeDef;

/** @defgroup MDR32F21QI_ADCUI_Defines ADCUI Defines
 * @{
 */

/** @defgroup MDR32F21QI_ADCUI_CTRL1 ADCUI_CTRL1
 * @{
 */

#define ADCUI_CTRL1_I0EN_Pos             0
#define ADCUI_CTRL1_I0EN_Msk             (0x1UL << ADCUI_CTRL1_I0EN_Pos)
#define ADCUI_CTRL1_I0EN                 ADCUI_CTRL1_I0EN_Msk

#define ADCUI_CTRL1_V0EN_Pos             1
#define ADCUI_CTRL1_V0EN_Msk             (0x1UL << ADCUI_CTRL1_V0EN_Pos)
#define ADCUI_CTRL1_V0EN                 ADCUI_CTRL1_V0EN_Msk

#define ADCUI_CTRL1_I1EN_Pos             2
#define ADCUI_CTRL1_I1EN_Msk             (0x1UL << ADCUI_CTRL1_I1EN_Pos)
#define ADCUI_CTRL1_I1EN                 ADCUI_CTRL1_I1EN_Msk

#define ADCUI_CTRL1_V1EN_Pos             3
#define ADCUI_CTRL1_V1EN_Msk             (0x1UL << ADCUI_CTRL1_V1EN_Pos)
#define ADCUI_CTRL1_V1EN                 ADCUI_CTRL1_V1EN_Msk

#define ADCUI_CTRL1_I2EN_Pos             4
#define ADCUI_CTRL1_I2EN_Msk             (0x1UL << ADCUI_CTRL1_I2EN_Pos)
#define ADCUI_CTRL1_I2EN                 ADCUI_CTRL1_I2EN_Msk

#define ADCUI_CTRL1_V2EN_Pos             5
#define ADCUI_CTRL1_V2EN_Msk             (0x1UL << ADCUI_CTRL1_V2EN_Pos)
#define ADCUI_CTRL1_V2EN                 ADCUI_CTRL1_V2EN_Msk

#define ADCUI_CTRL1_I3EN_Pos             6
#define ADCUI_CTRL1_I3EN_Msk             (0X1UL << ADCUI_CTRL1_I3EN_Pos)
#define ADCUI_CTRL1_I3EN                 ADCUI_CTRL1_I3EN_Msk

#define ADCUI_CTRL1_RESOL_Pos            7
#define ADCUI_CTRL1_RESOL_Msk            (0x1UL << ADCUI_CTRL1_RESOL_Pos)
#define ADCUI_CTRL1_RESOL                ADCUI_CTRL1_RESOL_Msk

#define ADCUI_CTRL1_ZXLPF_Pos            8
#define ADCUI_CTRL1_ZXLPF_Msk            (0x1UL << ADCUI_CTRL1_ZXLPF_Pos)
#define ADCUI_CTRL1_ZXLPF                ADCUI_CTRL1_ZXLPF_Msk

#define ADCUI_CTRL1_PER_LENGHT_Pos       9
#define ADCUI_CTRL1_PER_LENGHT_Msk       (0x7UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_1         (0x0UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_2         (0x1UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_4         (0x2UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_8         (0x3UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_16        (0x4UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_32        (0x5UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_64        (0x6UL << ADCUI_CTRL1_PER_LENGHT_Pos)
#define ADCUI_CTRL1_PER_LENGHT_128       (0x7UL << ADCUI_CTRL1_PER_LENGHT_Pos)

#define ADCUI_CTRL1_APNOLOAD_Pos         12
#define ADCUI_CTRL1_APNOLOAD_Msk         (0x3UL << ADCUI_CTRL1_APNOLOAD_Pos)
#define ADCUI_CTRL1_APNOLOAD_FULL        (0x0UL << ADCUI_CTRL1_APNOLOAD_Pos)
#define ADCUI_CTRL1_APNOLOAD_0p012pct    (0x1UL << ADCUI_CTRL1_APNOLOAD_Pos)
#define ADCUI_CTRL1_APNOLOAD_0p0061pct   (0x2UL << ADCUI_CTRL1_APNOLOAD_Pos)
#define ADCUI_CTRL1_APNOLOAD_0p00305pct  (0x3UL << ADCUI_CTRL1_APNOLOAD_Pos)

#define ADCUI_CTRL1_VARNOLOAD_Pos        15
#define ADCUI_CTRL1_VARNOLOAD_Msk        (0x3UL << ADCUI_CTRL1_VARNOLOAD_Pos)
#define ADCUI_CTRL1_VARNOLOAD_FULL       (0x0UL << ADCUI_CTRL1_VARNOLOAD_Pos)
#define ADCUI_CTRL1_VARNOLOAD_0p012pct   (0x1UL << ADCUI_CTRL1_VARNOLOAD_Pos)
#define ADCUI_CTRL1_VARNOLOAD_0p0061pct  (0x2UL << ADCUI_CTRL1_VARNOLOAD_Pos)
#define ADCUI_CTRL1_VARNOLOAD_0p00305pct (0x3UL << ADCUI_CTRL1_VARNOLOAD_Pos)

#define ADCUI_CTRL1_VANOLOAD_Pos         17
#define ADCUI_CTRL1_VANOLOAD_Msk         (0x3UL << ADCUI_CTRL1_VANOLOAD_Pos)
#define ADCUI_CTRL1_VANOLOAD_FULL        (0x0UL << ADCUI_CTRL1_VANOLOAD_Pos)
#define ADCUI_CTRL1_VANOLOAD_0p012pct    (0x1UL << ADCUI_CTRL1_VANOLOAD_Pos)
#define ADCUI_CTRL1_VANOLOAD_0p0061pct   (0x2UL << ADCUI_CTRL1_VANOLOAD_Pos)
#define ADCUI_CTRL1_VANOLOAD_0p00305pct  (0x3UL << ADCUI_CTRL1_VANOLOAD_Pos)

#define ADCUI_CTRL1_FREQSEL_Pos          19
#define ADCUI_CTRL1_FREQSEL_Msk          (0x1UL << ADCUI_CTRL1_FREQSEL_Pos)
#define ADCUI_CTRL1_FREQSEL              ADCUI_CTRL1_FREQSEL_Msk

#define ADCUI_CTRL1_VREF_SEL_Pos         20
#define ADCUI_CTRL1_VREF_SEL_Msk         (0x1UL << ADCUI_CTRL1_VREF_SEL_Pos)
#define ADCUI_CTRL1_VREF_SEL             ADCUI_CTRL1_VREF_SEL_Msk

#define ADCUI_CTRL1_BUF_BYP_Pos          21
#define ADCUI_CTRL1_BUF_BYP_Msk          (0x1UL << ADCUI_CTRL1_BUF_BYP_Pos)
#define ADCUI_CTRL1_BUF_BYP              ADCUI_CTRL1_BUF_BYP_Msk

#define ADCUI_CTRL1_CHOP_EN_Pos          22
#define ADCUI_CTRL1_CHOP_EN_Msk          (0x1UL << ADCUI_CTRL1_CHOP_EN_Pos)
#define ADCUI_CTRL1_CHOP_EN              ADCUI_CTRL1_CHOP_EN_Msk

#define ADCUI_CTRL1_CHOP_FREQ_Pos        23
#define ADCUI_CTRL1_CHOP_FREQ_Msk        (0x3UL << ADCUI_CTRL1_CHOP_FREQ_Pos)
#define ADCUI_CTRL1_CHOP_FREQ_DIV_2      (0x0UL << ADCUI_CTRL1_CHOP_FREQ_Pos)
#define ADCUI_CTRL1_CHOP_FREQ_DIV_4      (0x1UL << ADCUI_CTRL1_CHOP_FREQ_Pos)
#define ADCUI_CTRL1_CHOP_FREQ_DIV_8      (0x2UL << ADCUI_CTRL1_CHOP_FREQ_Pos)
#define ADCUI_CTRL1_CHOP_FREQ_DIV_16     (0x3UL << ADCUI_CTRL1_CHOP_FREQ_Pos)

#define ADCUI_CTRL1_ZXRMS_Pos            27
#define ADCUI_CTRL1_ZXRMS_Msk            (0x1UL << ADCUI_CTRL1_ZXRMS_Pos)
#define ADCUI_CTRL1_ZXRMS                ADCUI_CTRL1_ZXRMS_Msk

#define ADCUI_CTRL1_RESET_DIG_Pos        28
#define ADCUI_CTRL1_RESET_DIG_Msk        (0x1UL << ADCUI_CTRL1_RESET_DIG_Pos)
#define ADCUI_CTRL1_RESET_DIG            ADCUI_CTRL1_RESET_DIG_Msk

#define ADCUI_CTRL1_IBOOST_Pos           29
#define ADCUI_CTRL1_IBOOST_Msk           (0x1UL << ADCUI_CTRL1_IBOOST_Pos)
#define ADCUI_CTRL1_IBOOST               ADCUI_CTRL1_IBOOST_Msk

#define ADCUI_CTRL1_OSR_CONF_Pos         30
#define ADCUI_CTRL1_OSR_CONF_Msk         (0x3UL << ADCUI_CTRL1_OSR_CONF_Pos)
#define ADCUI_CTRL1_OSR_CONF_256_4kHz    (0x0UL << ADCUI_CTRL1_OSR_CONF_Pos)
#define ADCUI_CTRL1_OSR_CONF_128_8kHz    (0x1UL << ADCUI_CTRL1_OSR_CONF_Pos)
#define ADCUI_CTRL1_OSR_CONF_64_16kHz    (0x2UL << ADCUI_CTRL1_OSR_CONF_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_CTRL1 */

/** @defgroup MDR32F21QI_ADCUI_CTRL2 ADCUI_CTRL2
 * @{
 */

#define ADCUI_CTRL2_SAGLVL_Pos 0
#define ADCUI_CTRL2_SAGLVL_Msk (0xFFFFUL << ADCUI_CTRL2_SAGLVL_Pos)

#define ADCUI_CTRL2_SAGCYC_Pos 16
#define ADCUI_CTRL2_SAGCYC_Msk (0xFFUL << ADCUI_CTRL2_SAGCYC_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_CTRL2 */

/** @defgroup MDR32F21QI_ADCUI_CTRL3 ADCUI_CTRL3
 * @{
 */

#define ADCUI_CTRL3_ZXTOUT_Pos 0
#define ADCUI_CTRL3_ZXTOUT_Msk (0xFFFUL << ADCUI_CTRL3_ZXTOUT_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_CTRL3 */

/** @defgroup MDR32F21QI_ADCUI_FxCTR ADCUI_FxCTR
 * @{
 */

#define ADCUI_FxCTR_FxI0NTEN_Pos  0
#define ADCUI_FxCTR_FxI0NTEN_Msk  (0x1UL << ADCUI_FxCTR_FxI0NTEN_Pos)
#define ADCUI_FxCTR_FxI0NTEN      ADCUI_FxCTR_FxI0NTEN_Msk

#define ADCUI_FxCTR_FxI3NTEN_Pos  1
#define ADCUI_FxCTR_FxI3NTEN_Msk  (0x1UL << ADCUI_FxCTR_FxI3NTEN_Pos)
#define ADCUI_FxCTR_FxI3NTEN      ADCUI_FxCTR_FxI3NTEN_Msk

#define ADCUI_FxCTR_FxVASEL_Pos   2
#define ADCUI_FxCTR_FxVASEL_Msk   (0x1UL << ADCUI_FxCTR_FxVASEL_Pos)
#define ADCUI_FxCTR_FxVASEL       ADCUI_FxCTR_FxVASEL_Msk

#define ADCUI_FxCTR_FxRARS_Pos    3
#define ADCUI_FxCTR_FxRARS_Msk    (0x1UL << ADCUI_FxCTR_FxRARS_Pos)
#define ADCUI_FxCTR_FxRARS        ADCUI_FxCTR_FxRARS_Msk

#define ADCUI_FxCTR_FxRRRS_Pos    4
#define ADCUI_FxCTR_FxRRRS_Msk    (0x1UL << ADCUI_FxCTR_FxRRRS_Pos)
#define ADCUI_FxCTR_FxRRRS        ADCUI_FxCTR_FxRRRS_Msk

#define ADCUI_FxCTR_FxRVRS_Pos    5
#define ADCUI_FxCTR_FxRVRS_Msk    (0x1UL << ADCUI_FxCTR_FxRVRS_Pos)
#define ADCUI_FxCTR_FxRVRS        ADCUI_FxCTR_FxRVRS_Msk

#define ADCUI_FxCTR_FxIGAIN_Pos   6
#define ADCUI_FxCTR_FxI0GAIN_Msk  (0x3UL << ADCUI_FxCTR_FxIGAIN_Pos)
#define ADCUI_FxCTR_FxI0GAIN_0dB  (0x0UL << ADCUI_FxCTR_FxIGAIN_Pos)
#define ADCUI_FxCTR_FxI0GAIN_6dB  (0x1UL << ADCUI_FxCTR_FxIGAIN_Pos)
#define ADCUI_FxCTR_FxI0GAIN_12dB (0x2UL << ADCUI_FxCTR_FxIGAIN_Pos)
#define ADCUI_FxCTR_FxI0GAIN_18dB (0x3UL << ADCUI_FxCTR_FxIGAIN_Pos)

#define ADCUI_FxCTR_FxVGAIN_Pos   8
#define ADCUI_FxCTR_FxVGAIN_Msk   (0x3UL << ADCUI_FxCTR_FxVGAIN_Pos)
#define ADCUI_FxCTR_FxVGAIN_0dB   (0x0UL << ADCUI_FxCTR_FxVGAIN_Pos)
#define ADCUI_FxCTR_FxVGAIN_6dB   (0x1UL << ADCUI_FxCTR_FxVGAIN_Pos)
#define ADCUI_FxCTR_FxVGAIN_12dB  (0x2UL << ADCUI_FxCTR_FxVGAIN_Pos)
#define ADCUI_FxCTR_FxVGAIN_18dB  (0x3UL << ADCUI_FxCTR_FxVGAIN_Pos)

#define ADCUI_FxCTR_FxVPHASE_Pos  10
#define ADCUI_FxCTR_FxVPHASE_Msk  (0xFFUL << ADCUI_FxCTR_FxVPHASE_Pos)

#define ADCUI_FxCTR_FxI3GAIN_Pos  18
#define ADCUI_FxCTR_FxI3GAIN_Msk  (0x3UL << ADCUI_FxCTR_FxI3GAIN_Pos)
#define ADCUI_FxCTR_FxI3GAIN_0dB  (0x0UL << ADCUI_FxCTR_FxI3GAIN_Pos)
#define ADCUI_FxCTR_FxI3GAIN_6dB  (0x1UL << ADCUI_FxCTR_FxI3GAIN_Pos)
#define ADCUI_FxCTR_FxI3GAIN_12dB (0x2UL << ADCUI_FxCTR_FxI3GAIN_Pos)
#define ADCUI_FxCTR_FxI3GAIN_18dB (0x3UL << ADCUI_FxCTR_FxI3GAIN_Pos)

#define ADCUI_FxCTR_FxIRMSOS_Pos  20
#define ADCUI_FxCTR_FxIRMSOS_Msk  (0xFFFUL << ADCUI_FxCTR_FxIRMSOS_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxCTR */

/** @defgroup MDR32F21QI_ADCUI_FxWC ADCUI_FxWC
 * @{
 */

#define ADCUI_FxWC_FxWATTOS_Pos 0
#define ADCUI_FxWC_FxWATTOS_Msk (0xFFFFUL << ADCUI_FxWC_FxWATTOS_Pos)

#define ADCUI_FxWC_FxWGAIN_Pos  16
#define ADCUI_FxWC_FxWGAIN_Msk  (0xFFFUL << ADCUI_FxWC_FxWGAIN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxWC */

/** @defgroup MDR32F21QI_ADCUI_FxWATTP ADCUI_FxWATTP
 * @{
 */

#define ADCUI_FxWATTP_FxWATTHRP_Pos 0
#define ADCUI_FxWATTP_FxWATTHRP_Msk (0xFFFFFFFFUL << ADCUI_FxWATTP_FxWATTHRP_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxWATTP */

/** @defgroup MDR32F21QI_ADCUI_FxWATTN ADCUI_FxWATTN
 * @{
 */

#define ADCUI_FxWATTN_FxWATTHRN_Pos 0
#define ADCUI_FxWATTN_FxWATTHRN_Msk (0xFFFFFFFFUL << ADCUI_FxWATTN_FxWATTHRN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxWATTN */

/** @defgroup MDR32F21QI_ADCUI_FxVC ADCUI_FxVC
 * @{
 */

#define ADCUI_FxVC_FxVAROS_Pos   0
#define ADCUI_FxVC_FxVAROS_Msk   (0xFFFFUL << ADCUI_FxVC_FxVAROS_Pos)

#define ADCUI_FxVC_FxVARGAIN_Pos 16
#define ADCUI_FxVC_FxVARGAIN_Msk (0xFFFUL << ADCUI_FxVC_FxVARGAIN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVC */

/** @defgroup MDR32F21QI_ADCUI_FxVARP ADCUI_FxVARP
 * @{
 */

#define ADCUI_FxVARP_FxVARHRP_Pos 0
#define ADCUI_FxVARP_FxVARHRP_Msk (0xFFFFFFFFUL << ADCUI_FxVARP_FxVARHRP_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVARP */

/** @defgroup MDR32F21QI_ADCUI_FxVARN ADCUI_FxVARN
 * @{
 */

#define ADCUI_FxVARN_FxVARHRN_Pos 0
#define ADCUI_FxVARN_FxVARHRN_Msk (0xFFFFFFFFUL << ADCUI_FxVARN_FxVARHRN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVARN */

/** @defgroup MDR32F21QI_ADCUI_FxAC ADCUI_FxAC
 * @{
 */

#define ADCUI_FxAC_FxVRMSOS_Pos 0
#define ADCUI_FxAC_FxVRMSOS_Msk (0xFFFUL << ADCUI_FxAС_FxVRMSOS_Pos)

#define ADCUI_FxAC_FxVAGAIN_Pos 16
#define ADCUI_FxAC_FxVAGAIN_Msk (0xFFFUL << ADCUI_FxAC_FxVAGAIN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxAC */

/** @defgroup MDR32F21QI_ADCUI_FxVR ADCUI_FxVR
 * @{
 */

#define ADCUI_FxVR_FxVAHR_Pos 0
#define ADCUI_FxVR_FxVAHR_Msk (0xFFFFFFFFUL << ADCUI_FxVR_FxVAHR_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVR */

/** @defgroup MDR32F21QI_ADCUI_FxMD0 ADCUI_FxMD0
 * @{
 */

#define ADCUI_FxMD0_FxVSEL_Pos           0
#define ADCUI_FxMD0_FxVSEL_Msk           (0x3UL << ADCUI_FxMD0_FxVSEL_Pos)
#define ADCUI_FxMD0_FxVSEL_V             (0x0UL << ADCUI_FxMD0_FxVSEL_Pos)
#define ADCUI_FxMD0_FxVSEL_ACTIVEPOWER   (0x1UL << ADCUI_FxMD0_FxVSEL_Pos)
#define ADCUI_FxMD0_FxVSEL_REACTIVEPOWER (0x2UL << ADCUI_FxMD0_FxVSEL_Pos)
#define ADCUI_FxMD0_FxVSEL_FULLPOWER     (0x3UL << ADCUI_FxMD0_FxVSEL_Pos)

#define ADCUI_FxMD0_FxISEL_Pos           2
#define ADCUI_FxMD0_FxISEL_Msk           (0x3UL << ADCUI_FxMD0_FxISEL_Pos)
#define ADCUI_FxMD0_FxISEL_I             (0x0UL << ADCUI_FxMD0_FxISEL_Pos)
#define ADCUI_FxMD0_FxISEL_ACTIVEPOWER   (0x1UL << ADCUI_FxMD0_FxISEL_Pos)
#define ADCUI_FxMD0_FxISEL_REACTIVEPOWER (0x2UL << ADCUI_FxMD0_FxISEL_Pos)
#define ADCUI_FxMD0_FxISEL_FULLPOWER     (0x3UL << ADCUI_FxMD0_FxISEL_Pos)

#define ADCUI_FxMD0_FxACTS_Pos           4
#define ADCUI_FxMD0_FxACTS_Msk           (0x1UL << ADCUI_FxMD0_FxACTS_Pos)
#define ADCUI_FxMD0_FxACTS               ADCUI_FxMD0_FxACTS_Msk

#define ADCUI_FxMD0_FxREACTS_Pos         5
#define ADCUI_FxMD0_FxREACTS_Msk         (0x1UL << ADCUI_FxMD0_FxREACTS_Pos)
#define ADCUI_FxMD0_FxREACTS             ADCUI_FxMD0_FxREACTS_Msk

#define ADCUI_FxMD0_IxGAIN_Pos           6
#define ADCUI_FxMD0_IxGAIN_Msk           (0x1UL << ADCUI_FxMD0_IxGAIN_Pos)
#define ADCUI_FxMD0_IxGAIN               ADCUI_FxMD0_IxGAIN_Msk

#define ADCUI_FxMD0_VxGAIN_Pos           7
#define ADCUI_FxMD0_VxGAIN_Msk           (0x1UL << ADCUI_FxMD0_VxGAIN_Pos)
#define ADCUI_FxMD0_VxGAIN               ADCUI_FxMD0_VxGAIN_Msk

#define ADCUI_FxMD0_I3GAIN_Pos           8
#define ADCUI_FxMD0_I3GAIN_Msk           (0x1UL << ADCUI_FxMD0_I3GAIN_Pos)
#define ADCUI_FxMD0_I3GAIN               ADCUI_FxMD0_I3GAIN_Msk

#define ADCUI_FxMD0_FxPER_FREQ_Pos       12
#define ADCUI_FxMD0_FxPER_FREQ_Msk       (0x1FFFFUL << ADCUI_FxMD0_FxPER_FREQ_Pos)

#define ADCUI_FxMD0_FxI3SEL_Pos          29
#define ADCUI_FxMD0_FxI3SEL_Msk          (0x1UL << ADCUI_FxMD0_FxI3SEL_Pos)
#define ADCUI_FxMD0_FxI3SEL              ADCUI_FxMD0_FxI3SEL_Msk

#define ADCUI_FxMD0_FxSEL_I_CH_Pos       30
#define ADCUI_FxMD0_FxSEL_I_CH_Msk       (0x3UL << ADCUI_FxMD0_FxSEL_I_CH_Pos)
#define ADCUI_FxMD0_FxSEL_I_CH_AUTO      (0x0UL << ADCUI_FxMD0_FxSEL_I_CH_Pos)
#define ADCUI_FxMD0_FxSEL_I_CH_ACTIVEI0  (0x1UL << ADCUI_FxMD0_FxSEL_I_CH_Pos)
#define ADCUI_FxMD0_FxSEL_I_CH_ACTIVEI3  (0x2UL << ADCUI_FxMD0_FxSEL_I_CH_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxMD0 */

/** @defgroup MDR32F21QI_ADCUI_FxMD1 ADCUI_FxMD1
 * @{
 */

#define ADCUI_FxMD1_FxIPKLVL_Pos 0
#define ADCUI_FxMD1_FxIPKLVL_Msk (0xFFFFUL << ADCUI_FxMD1_FxIPKLVL_Pos)

#define ADCUI_FxMD1_FxVPKLVL_Pos 16
#define ADCUI_FxMD1_FxVPKLVL_Msk (0xFFFFUL << ADCUI_FxMD1_FxVPKLVL_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxMD1 */

/** @defgroup MDR32F21QI_ADCUI_FxVPEAK ADCUI_FxVPEAK
 * @{
 */

#define ADCUI_FxVPEAK_FxVPEAK_Pos 0
#define ADCUI_FxVPEAK_FxVPEAK_Msk (0xFFFFFFUL << ADCUI_FxVPEAK_FxVPEAK_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVPEAK */

/** @defgroup MDR32F21QI_ADCUI_FxIPEAK ADCUI_FxIPEAK
 * @{
 */

#define ADCUI_FxIPEAK_FxIPEAK_Pos 0
#define ADCUI_FxIPEAK_FxIPEAK_Msk (0xFFFFFFUL << ADCUI_FxIPEAK_FxIPEAK_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxIPEAK */

/** @defgroup MDR32F21QI_ADCUI_FxVDAT ADCUI_FxVDAT
 * @{
 */

#define ADCUI_FxVDAT_FxVDAT_Pos 0
#define ADCUI_FxVDAT_FxVDAT_Msk (0xFFFFFFUL << ADCUI_FxVDAT_FxVDAT_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVDAT */

/** @defgroup MDR32F21QI_ADCUI_FxI0DAT ADCUI_FxI0DAT
 * @{
 */

#define ADCUI_FxI0DAT_FxI0DAT_Pos 0
#define ADCUI_FxI0DAT_FxI0DAT_Msk (0xFFFFFFUL << ADCUI_FxI0DAT_FxI0DAT_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxI0DAT */

/** @defgroup MDR32F21QI_ADCUI_FxI3DAT ADCUI_FxI3DAT
 * @{
 */

#define ADCUI_FxI3DAT_FxI3DAT_Pos 0
#define ADCUI_FxI3DAT_FxI3DAT_Msk (0xFFFFFFUL << ADCUI_FxI3DAT_FxI3DAT_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxI3DAT */

/** @defgroup MDR32F21QI_ADCUI_FxVRMS ADCUI_FxVRMS
 * @{
 */

#define ADCUI_FxVRMS_FxVRMS_Pos 0
#define ADCUI_FxVRMS_FxVRMS_Msk (0xFFFFFFUL << ADCUI_FxVRMS_FxVRMS_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVRMS */

/** @defgroup MDR32F21QI_ADCUI_FxVRMS2 ADCUI_FxVRMS2
 * @{
 */

#define ADCUI_FxVRMS2_FxVRMS2_Pos 0
#define ADCUI_FxVRMS2_FxVRMS2_Msk (0xFFFFFFFFUL << ADCUI_FxVRMS2_FxVRMS2_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxVRMS2 */

/** @defgroup MDR32F21QI_ADCUI_FxIRMS ADCUI_FxIRMS
 * @{
 */

#define ADCUI_FxIRMS_FxIRMS_Pos 0
#define ADCUI_FxIRMS_FxIRMS_Msk (0xFFFFFFUL << ADCUI_FxIRMS_FxIRMS_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxIRMS */

/** @defgroup MDR32F21QI_ADCUI_FxIRMS2 ADCUI_FxIRMS2
 * @{
 */

#define ADCUI_FxIRMS2_FxIRMS2_Pos 0
#define ADCUI_FxIRMS2_FxIRMS2_Msk (0xFFFFFFFFUL << ADCUI_FxIRMS2_FxIRMS2_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_FxIRMS2 */

/** @defgroup MDR32F21QI_ADCUI_FxSTAT ADCUI_FxSTAT
 * @{
 */

#define ADCUI_FxSTAT_FxVF_EMP_Pos   0
#define ADCUI_FxSTAT_FxVF_EMP_Msk   (0x1UL << ADCUI_FxSTAT_FxVF_EMP_Pos)
#define ADCUI_FxSTAT_FxVF_EMP       ADCUI_FxSTAT_FxVF_EMP_Msk

#define ADCUI_FxSTAT_FxVF_FLL_Pos   1
#define ADCUI_FxSTAT_FxVF_FLL_Msk   (0x1UL << ADCUI_FxSTAT_FxVF_FLL_Pos)
#define ADCUI_FxSTAT_FxVF_FLL       ADCUI_FxSTAT_FxVF_FLL_Msk

#define ADCUI_FxSTAT_FxVF_OVR_Pos   2
#define ADCUI_FxSTAT_FxVF_OVR_Msk   (0x1UL << ADCUI_FxSTAT_FxVF_OVR_Pos)
#define ADCUI_FxSTAT_FxVF_OVR       ADCUI_FxSTAT_FxVF_OVR_Msk

#define ADCUI_FxSTAT_FxIF_EMP_Pos   3
#define ADCUI_FxSTAT_FxIF_EMP_Msk   (0x1UL << ADCUI_FxSTAT_FxIF_EMP_Pos)
#define ADCUI_FxSTAT_FxIF_EMP       ADCUI_FxSTAT_FxIF_EMP_Msk

#define ADCUI_FxSTAT_FxIF_FLL_Pos   4
#define ADCUI_FxSTAT_FxIF_FLL_Msk   (0x1UL << ADCUI_FxSTAT_FxIF_FLL_Pos)
#define ADCUI_FxSTAT_FxIF_FLL       ADCUI_FxSTAT_FxIF_FLL_Msk

#define ADCUI_FxSTAT_FxIF_OVR_Pos   5
#define ADCUI_FxSTAT_FxIF_OVR_Msk   (0x1UL << ADCUI_FxSTAT_FxIF_OVR_Pos)
#define ADCUI_FxSTAT_FxIF_OVR       ADCUI_FxSTAT_FxIF_OVR_Msk

#define ADCUI_FxSTAT_FxSAGF_Pos     6
#define ADCUI_FxSTAT_FxSAGF_Msk     (0x1UL << ADCUI_FxSTAT_FxSAGF_Pos)
#define ADCUI_FxSTAT_FxSAGF         ADCUI_FxSTAT_FxSAGF_Msk

#define ADCUI_FxSTAT_FxPEAKVF_Pos   7
#define ADCUI_FxSTAT_FxPEAKVF_Msk   (0x1UL << ADCUI_FxSTAT_FxPEAKVF_Pos)
#define ADCUI_FxSTAT_FxPEAKVF       ADCUI_FxSTAT_FxPEAKVF_Msk

#define ADCUI_FxSTAT_FxPEAKIF_Pos   8
#define ADCUI_FxSTAT_FxPEAKIF_Msk   (0x1UL << ADCUI_FxSTAT_FxPEAKIF_Pos)
#define ADCUI_FxSTAT_FxPEAKIF       ADCUI_FxSTAT_FxPEAKIF_Msk

#define ADCUI_FxSTAT_FxWATTOVP_Pos  9
#define ADCUI_FxSTAT_FxWATTOVP_Msk  (0x1UL << ADCUI_FxSTAT_FxWATTOVP_Pos)
#define ADCUI_FxSTAT_FxWATTOVP      ADCUI_FxSTAT_FxWATTOVP_Msk

#define ADCUI_FxSTAT_FxVAROVP_Pos   10
#define ADCUI_FxSTAT_FxVAROVP_Msk   (0x1UL << ADCUI_FxSTAT_FxVAROVP_Pos)
#define ADCUI_FxSTAT_FxVAROVP       ADCUI_FxSTAT_FxVAROVP_Msk

#define ADCUI_FxSTAT_FxVAOV_Pos     11
#define ADCUI_FxSTAT_FxVAOV_Msk     (0x1UL << ADCUI_FxSTAT_FxVAOV_Pos)
#define ADCUI_FxSTAT_FxVAOV         ADCUI_FxSTAT_FxVAOV_Msk

#define ADCUI_FxSTAT_FxZXTOF_Pos    12
#define ADCUI_FxSTAT_FxZXTOF_Msk    (0x1UL << ADCUI_FxSTAT_FxZXTOF_Pos)
#define ADCUI_FxSTAT_FxZXTOF        ADCUI_FxSTAT_FxZXTOF_Msk

#define ADCUI_FxSTAT_FxICHANNEL_Pos 13
#define ADCUI_FxSTAT_FxICHANNEL_Msk (0x1UL << ADCUI_FxSTAT_FxICHANNEL_Pos)
#define ADCUI_FxSTAT_FxICHANNEL     ADCUI_FxSTAT_FxICHANNEL_Msk

#define ADCUI_FxSTAT_FxFAULTCON_Pos 14
#define ADCUI_FxSTAT_FxFAULTCON_Msk (0x1UL << ADCUI_FxSTAT_FxFAULTCON_Pos)
#define ADCUI_FxSTAT_FxFAULTCON     ADCUI_FxSTAT_FxFAULTCON_Msk

#define ADCUI_FxSTAT_FxAPSIGN_Pos   15
#define ADCUI_FxSTAT_FxAPSIGN_Msk   (0x1UL << ADCUI_FxSTAT_FxAPSIGN_Pos)
#define ADCUI_FxSTAT_FxAPSIGN       ADCUI_FxSTAT_FxAPSIGN_Msk

#define ADCUI_FxSTAT_FxAPNLDFL_Pos  16
#define ADCUI_FxSTAT_FxAPNLDFL_Msk  (0x1UL << ADCUI_FxSTAT_FxAPNLDFL_Pos)
#define ADCUI_FxSTAT_FxAPNLDFL      ADCUI_FxSTAT_FxAPNLDFL_Msk

#define ADCUI_FxSTAT_FxVARSIGN_Pos  17
#define ADCUI_FxSTAT_FxVARSIGN_Msk  (0x1UL << ADCUI_FxSTAT_FxVARSIGN_Pos)
#define ADCUI_FxSTAT_FxVARSIGN      ADCUI_FxSTAT_FxVARSIGN_Msk

#define ADCUI_FxSTAT_FxVARNLDFL_Pos 18
#define ADCUI_FxSTAT_FxVARNLDFL_Msk (0x1UL << ADCUI_FxSTAT_FxVARNLDFL_Pos)
#define ADCUI_FxSTAT_FxVARNLDFL     ADCUI_FxSTAT_FxVARNLDFL_Msk

#define ADCUI_FxSTAT_FxVANLDFL_Pos  20
#define ADCUI_FxSTAT_FxVANLDFL_Msk  (0x1UL << ADCUI_FxSTAT_FxVANLDFL_Pos)
#define ADCUI_FxSTAT_FxVANLDFL      ADCUI_FxSTAT_FxVANLDFL_Msk

#define ADCUI_FxSTAT_FxZEROCRS_Pos  21
#define ADCUI_FxSTAT_FxZEROCRS_Msk  (0x1UL << ADCUI_FxSTAT_FxZEROCRS_Pos)
#define ADCUI_FxSTAT_FxZEROCRS      ADCUI_FxSTAT_FxZEROCRS_Msk

#define ADCUI_FxSTAT_C3IF_EMP_Pos   22
#define ADCUI_FxSTAT_C3IF_EMP_Msk   (0x1UL << ADCUI_FxSTAT_C3IF_EMP_Pos)
#define ADCUI_FxSTAT_C3IF_EMP       ADCUI_FxSTAT_C3IF_EMP_Msk

#define ADCUI_FxSTAT_C3IF_FLL_Pos   23
#define ADCUI_FxSTAT_C3IF_FLL_Msk   (0x1UL << ADCUI_FxSTAT_C3IF_FLL_Pos)
#define ADCUI_FxSTAT_C3IF_FLL       ADCUI_FxSTAT_C3IF_FLL_Msk

#define ADCUI_FxSTAT_C3IF_OVR_Pos   24
#define ADCUI_FxSTAT_C3IF_OVR_Msk   (0x1UL << ADCUI_FxSTAT_C3IF_OVR_Pos)
#define ADCUI_FxSTAT_C3IF_OVR       ADCUI_FxSTAT_C3IF_OVR_Msk

#define ADCUI_FxSTAT_FxWATTOVN_Pos  25
#define ADCUI_FxSTAT_FxWATTOVN_Msk  (0x1UL << ADCUI_FxSTAT_FxWATTOVN_Pos)
#define ADCUI_FxSTAT_FxWATTOVN      ADCUI_FxSTAT_FxWATTOVN_Msk

#define ADCUI_FxSTAT_FxVAROVN_Pos   26
#define ADCUI_FxSTAT_FxVAROVN_Msk   (0x1UL << ADCUI_FxSTAT_FxVAROVN_Pos)
#define ADCUI_FxSTAT_FxVAROVN       ADCUI_FxSTAT_FxVAROVN_Msk

/** @} */ /* End of group MDR32F21QI_ADCUI_FxSTAT */

/** @defgroup MDR32F21QI_ADCUI_FxMASK ADCUI_FxMASK
 * @{
 */

#define ADCUI_FxMASK_FxVF_EMPM_Pos   0
#define ADCUI_FxMASK_FxVF_EMPM_Msk   (0x1UL << ADCUI_FxMASK_FxVF_EMPM_Pos)
#define ADCUI_FxMASK_FxVF_EMPM       ADCUI_FxMASK_FxVF_EMPM_Msk

#define ADCUI_FxMASK_FxVF_FLLM_Pos   1
#define ADCUI_FxMASK_FxVF_FLLM_Msk   (0x1UL << ADCUI_FxMASK_FxVF_FLLM_Pos)
#define ADCUI_FxMASK_FxVF_FLLM       ADCUI_FxMASK_FxVF_FLLM_Msk

#define ADCUI_FxMASK_FxVF_OVRM_Pos   2
#define ADCUI_FxMASK_FxVF_OVRM_Msk   (0x1UL << ADCUI_FxMASK_FxVF_OVRM_Pos)
#define ADCUI_FxMASK_FxVF_OVRM       ADCUI_FxMASK_FxVF_OVRM_Msk

#define ADCUI_FxMASK_FxIF_EMPM_Pos   3
#define ADCUI_FxMASK_FxIF_EMPM_Msk   (0x1UL << ADCUI_FxMASK_FxIF_EMPM_Pos)
#define ADCUI_FxMASK_FxIF_EMPM       ADCUI_FxMASK_FxIF_EMPM_Msk

#define ADCUI_FxMASK_FxIF_FLLM_Pos   4
#define ADCUI_FxMASK_FxIF_FLLM_Msk   (0x1UL << ADCUI_FxMASK_FxIF_FLLM_Pos)
#define ADCUI_FxMASK_FxIF_FLLM       ADCUI_FxMASK_FxIF_FLLM_Msk

#define ADCUI_FxMASK_FxIF_OVRM_Pos   5
#define ADCUI_FxMASK_FxIF_OVRM_Msk   (0x1UL << ADCUI_FxMASK_FxIF_OVRM_Pos)
#define ADCUI_FxMASK_FxIF_OVRM       ADCUI_FxMASK_FxIF_OVRM_Msk

#define ADCUI_FxMASK_FxSAGFM_Pos     6
#define ADCUI_FxMASK_FxSAGFM_Msk     (0x1UL << ADCUI_FxMASK_FxSAGFM_Pos)
#define ADCUI_FxMASK_FxSAGFM         ADCUI_FxMASK_FxSAGFM_Msk

#define ADCUI_FxMASK_FxPEAKVFM_Pos   7
#define ADCUI_FxMASK_FxPEAKVFM_Msk   (0x1UL << ADCUI_FxMASK_FxPEAKVFM_Pos)
#define ADCUI_FxMASK_FxPEAKVFM       ADCUI_FxMASK_FxPEAKVFM_Msk

#define ADCUI_FxMASK_FxPEAKIFM_Pos   8
#define ADCUI_FxMASK_FxPEAKIFM_Msk   (0x1UL << ADCUI_FxMASK_FxPEAKIFM_Pos)
#define ADCUI_FxMASK_FxPEAKIFM       ADCUI_FxMASK_FxPEAKIFM_Msk

#define ADCUI_FxMASK_FxWATTOVPM_Pos  9
#define ADCUI_FxMASK_FxWATTOVPM_Msk  (0x1UL << ADCUI_FxMASK_FxWATTOVPM_Pos)
#define ADCUI_FxMASK_FxWATTOVPM      ADCUI_FxMASK_FxWATTOVPM_Msk

#define ADCUI_FxMASK_FxVAROVPM_Pos   10
#define ADCUI_FxMASK_FxVAROVPM_Msk   (0x1UL << ADCUI_FxMASK_FxVAROVPM_Pos)
#define ADCUI_FxMASK_FxVAROVPM       ADCUI_FxMASK_FxVAROVPM_Msk

#define ADCUI_FxMASK_FxVAOVM_Pos     11
#define ADCUI_FxMASK_FxVAOVM_Msk     (0x1UL << ADCUI_FxMASK_FxVAOVM_Pos)
#define ADCUI_FxMASK_FxVAOVM         ADCUI_FxMASK_FxVAOVM_Msk

#define ADCUI_FxMASK_FxZXTOFM_Pos    12
#define ADCUI_FxMASK_FxZXTOFM_Msk    (0x1UL << ADCUI_FxMASK_FxZXTOFM_Pos)
#define ADCUI_FxMASK_FxZXTOFM        ADCUI_FxMASK_FxZXTOFM_Msk

#define ADCUI_FxMASK_FxFAULTCONM_Pos 14
#define ADCUI_FxMASK_FxFAULTCONM_Msk (0x1UL << ADCUI_FxMASK_FxFAULTCONM_Pos)
#define ADCUI_FxMASK_FxFAULTCONM     ADCUI_FxMASK_FxFAULTCONM_Msk

#define ADCUI_FxMASK_FxAPSIGNM_Pos   15
#define ADCUI_FxMASK_FxAPSIGNM_Msk   (0x1UL << ADCUI_FxMASK_FxAPSIGNM_Pos)
#define ADCUI_FxMASK_FxAPSIGNM       ADCUI_FxMASK_FxAPSIGNM_Msk

#define ADCUI_FxMASK_FxAPNLDFLM_Pos  16
#define ADCUI_FxMASK_FxAPNLDFLM_Msk  (0x1UL << ADCUI_FxMASK_FxAPNLDFLM_Pos)
#define ADCUI_FxMASK_FxAPNLDFLM      ADCUI_FxMASK_FxAPNLDFLM_Msk

#define ADCUI_FxMASK_FxVARSIGNM_Pos  17
#define ADCUI_FxMASK_FxVARSIGNM_Msk  (0x1UL << ADCUI_FxMASK_FxVARSIGNM_Pos)
#define ADCUI_FxMASK_FxVARSIGNM      ADCUI_FxMASK_FxVARSIGNM_Msk

#define ADCUI_FxMASK_FxVARNLDFLM_Pos 18
#define ADCUI_FxMASK_FxVARNLDFLM_Msk (0x1UL << ADCUI_FxMASK_FxVARNLDFLM_Pos)
#define ADCUI_FxMASK_FxVARNLDFLM     ADCUI_FxMASK_FxVARNLDFLM_Msk

#define ADCUI_FxMASK_FxVANLDFLM_Pos  20
#define ADCUI_FxMASK_FxVANLDFLM_Msk  (0x1UL << ADCUI_FxMASK_FxVANLDFLM_Pos)
#define ADCUI_FxMASK_FxVANLDFLM      ADCUI_FxMASK_FxVANLDFLM_Msk

#define ADCUI_FxMASK_FxZEROCRSM_Pos  21
#define ADCUI_FxMASK_FxZEROCRSM_Msk  (0x1UL << ADCUI_FxMASK_FxZEROCRSM_Pos)
#define ADCUI_FxMASK_FxZEROCRSM      ADCUI_FxMASK_FxZEROCRSM_Msk

#define ADCUI_FxMASK_C3IF_EMPM_Pos   22
#define ADCUI_FxMASK_C3IF_EMPM_Msk   (0x1UL << ADCUI_FxMASK_C3IF_EMPM_Pos)
#define ADCUI_FxMASK_C3IF_EMPM       ADCUI_FxMASK_C3IF_EMPM_Msk

#define ADCUI_FxMASK_C3IF_FLLM_Pos   23
#define ADCUI_FxMASK_C3IF_FLLM_Msk   (0x1UL << ADCUI_FxMASK_C3IF_FLLM_Pos)
#define ADCUI_FxMASK_C3IF_FLLM       ADCUI_FxMASK_C3IF_FLLM_Msk

#define ADCUI_FxMASK_C3IF_OVRM_Pos   24
#define ADCUI_FxMASK_C3IF_OVRM_Msk   (0x1UL << ADCUI_FxMASK_C3IF_OVRM_Pos)
#define ADCUI_FxMASK_C3IF_OVRM       ADCUI_FxMASK_C3IF_OVRM_Msk

#define ADCUI_FxMASK_FxWATTOVNM_Pos  25
#define ADCUI_FxMASK_FxWATTOVNM_Msk  (0x1UL << ADCUI_FxMASK_FxWATTOVNM_Pos)
#define ADCUI_FxMASK_FxWATTOVNM      ADCUI_FxMASK_FxWATTOVNM_Msk

#define ADCUI_FxMASK_FxVAROVNM_Pos   26
#define ADCUI_FxMASK_FxVAROVNM_Msk   (0x1UL << ADCUI_FxMASK_FxVAROVNM_Pos)
#define ADCUI_FxMASK_FxVAROVNM       ADCUI_FxMASK_FxVAROVNM_Msk

/** @} */ /* End of group MDR32F21QI_ADCUI_FxMASK */

/** @defgroup MDR32F21QI_ADCUI_CCAL1 ADCUI_CCAL1
 * @{
 */

#define ADCUI_CCAL1_V0BGAIN_Pos 0
#define ADCUI_CCAL1_V0BGAIN_Msk (0xFFFUL << ADCUI_CCAL1_V0BGAIN_Pos)

#define ADCUI_CCAL1_I0BGAIN_Pos 12
#define ADCUI_CCAL1_I0BGAIN_Msk (0xFFFUL << ADCUI_CCAL1_I0BGAIN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_CCAL1 */

/** @defgroup MDR32F21QI_ADCUI_CCAL2 ADCUI_CCAL2
 * @{
 */

#define ADCUI_CCAL2_V1BGAIN_Pos 0
#define ADCUI_CCAL2_V1BGAIN_Msk (0xFFFUL << ADCUI_CCAL2_V1BGAIN_Pos)

#define ADCUI_CCAL2_I1BGAIN_Pos 12
#define ADCUI_CCAL2_I1BGAIN_Msk (0xFFFUL << ADCUI_CCAL2_I1BGAIN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_CCAL2 */

/** @defgroup MDR32F21QI_ADCUI_CCAL3 ADCUI_CCAL3
 * @{
 */

#define ADCUI_CCAL3_V2BGAIN_Pos 0
#define ADCUI_CCAL3_V2BGAIN_Msk (0xFFFUL << ADCUI_CCAL3_V2BGAIN_Pos)

#define ADCUI_CCAL3_I2BGAIN_Pos 12
#define ADCUI_CCAL3_I2BGAIN_Msk (0xFFFUL << ADCUI_CCAL3_I2BGAIN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_CCAL3 */

/** @defgroup MDR32F21QI_ADCUI_CCAL4 ADCUI_CCAL4
 * @{
 */

#define ADCUI_CCAL4_I3BGAIN_Pos 0
#define ADCUI_CCAL4_I3BGAIN_Msk (0xFFFUL << ADCUI_CCAL4_I3BGAIN_Pos)

/** @} */ /* End of group MDR32F21QI_ADCUI_CCAL4 */

/** @} */ /* End of group MDR32F21QI_ADCUI_Defines */

/** @} */ /* End of group MDR32F21QI_ADCUI */

/** @defgroup MDR32F21QI_TIMER MDR_TIMER
 * @{
 */

/**
 * @brief MDR32F21QI TIMER control structure
 */
typedef struct {
    __IO uint32_t CNT;          /*!<TIMER Counter Register */
    __IO uint32_t PSG;          /*!<TIMER Clock Prescaler Register */
    __IO uint32_t ARR;          /*!<TIMER Auto-Reload Register */
    __IO uint32_t CNTRL;        /*!<TIMER Control Register */
    __IO uint32_t CCR1;         /*!<TIMER Capture/Compare Register 1 */
    __IO uint32_t CCR2;         /*!<TIMER Capture/Compare Register 2 */
    __IO uint32_t CCR3;         /*!<TIMER Capture/Compare Register 3 */
    __IO uint32_t CCR4;         /*!<TIMER Capture/Compare Register 4 */
    __IO uint32_t CH1_CNTRL;    /*!<TIMER Channel 1 Control Register */
    __IO uint32_t CH2_CNTRL;    /*!<TIMER Channel 2 Control Register */
    __IO uint32_t CH3_CNTRL;    /*!<TIMER Channel 3 Control Register */
    __IO uint32_t CH4_CNTRL;    /*!<TIMER Channel 4 Control Register */
    __IO uint32_t CH1_CNTRL1;   /*!<TIMER Channel 1 Control1 Register */
    __IO uint32_t CH2_CNTRL1;   /*!<TIMER Channel 2 Control1 Register */
    __IO uint32_t CH3_CNTRL1;   /*!<TIMER Channel 3 Control1 Register */
    __IO uint32_t CH4_CNTRL1;   /*!<TIMER Channel 4 Control1 Register */
    __IO uint32_t CH1_DTG;      /*!<TIMER Channel 1 DTG Register */
    __IO uint32_t CH2_DTG;      /*!<TIMER Channel 2 DTG Register */
    __IO uint32_t CH3_DTG;      /*!<TIMER Channel 3 DTG Register */
    __IO uint32_t CH4_DTG;      /*!<TIMER Channel 4 DTG Register */
    __IO uint32_t BRKETR_CNTRL; /*!<TIMER BRK/ETR Control Register */
    __IO uint32_t STATUS;       /*!<TIMER Status Register */
    __IO uint32_t IE;           /*!<TIMER Interrupt Enable Register */
    __IO uint32_t DMA_RE;       /*!<TIMER DMA Request Enable Register */
    __IO uint32_t CH1_CNTRL2;   /*!<TIMER Channel 1 Control2 Register */
    __IO uint32_t CH2_CNTRL2;   /*!<TIMER Channel 2 Control2 Register */
    __IO uint32_t CH3_CNTRL2;   /*!<TIMER Channel 3 Control2 Register */
    __IO uint32_t CH4_CNTRL2;   /*!<TIMER Channel 4 Control2 Register */
    __IO uint32_t CCR11;        /*!<TIMER Capture/Compare1 Register 1 */
    __IO uint32_t CCR21;        /*!<TIMER Capture/Compare1 Register 2 */
    __IO uint32_t CCR31;        /*!<TIMER Capture/Compare1 Register 3 */
    __IO uint32_t CCR41;        /*!<TIMER Capture/Compare1 Register 4 */
} MDR_TIMER_TypeDef;

/** @defgroup MDR32F21QI_TIMER_Defines TIMER Defines
 * @{
 */

/** @defgroup MDR32F21QI_TIMER_CNT TIMER_CNT
 * @{
 */

#define TIMER_CNT_CNT_Pos 0
#define TIMER_CNT_CNT_Msk (0xFFFFUL << TIMER_CNT_CNT_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_CNT */

/** @defgroup MDR32F21QI_TIMER_PSG TIMER_PSG
 * @{
 */

#define TIMER_PSG_PSG_Pos 0
#define TIMER_PSG_PSG_Msk (0xFFFFUL << TIMER_PSG_PSG_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_PSG */

/** @defgroup MDR32F21QI_TIMER_ARR TIMER_ARR
 * @{
 */

#define TIMER_ARR_ARR_Pos 0
#define TIMER_ARR_ARR_Msk (0xFFFFUL << TIMER_ARR_ARR_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_ARR */

/** @defgroup MDR32F21QI_TIMER_CNTRL TIMER_CNTRL
 * @{
 */

#define TIMER_CNTRL_CNT_EN_Pos              0
#define TIMER_CNTRL_CNT_EN_Msk              (0x1UL << TIMER_CNTRL_CNT_EN_Pos)
#define TIMER_CNTRL_CNT_EN                  TIMER_CNTRL_CNT_EN_Msk

#define TIMER_CNTRL_ARRB_EN_Pos             1
#define TIMER_CNTRL_ARRB_EN_Msk             (0x1UL << TIMER_CNTRL_ARRB_EN_Pos)
#define TIMER_CNTRL_ARRB_EN                 TIMER_CNTRL_ARRB_EN_Msk

#define TIMER_CNTRL_WR_CMPL_Pos             2
#define TIMER_CNTRL_WR_CMPL_Msk             (0x1UL << TIMER_CNTRL_WR_CMPL_Pos)
#define TIMER_CNTRL_WR_CMPL                 TIMER_CNTRL_WR_CMPL_Msk

#define TIMER_CNTRL_DIR_Pos                 3
#define TIMER_CNTRL_DIR_Msk                 (0x1UL << TIMER_CNTRL_DIR_Pos)
#define TIMER_CNTRL_DIR                     TIMER_CNTRL_DIR_Msk

#define TIMER_CNTRL_FDTS_Pos                4
#define TIMER_CNTRL_FDTS_Msk                (0x3UL << TIMER_CNTRL_FDTS_Pos)
#define TIMER_CNTRL_FDTS_DIV_1              (0x0UL << TIMER_CNTRL_FDTS_Pos)
#define TIMER_CNTRL_FDTS_DIV_2              (0x1UL << TIMER_CNTRL_FDTS_Pos)
#define TIMER_CNTRL_FDTS_DIV_3              (0x2UL << TIMER_CNTRL_FDTS_Pos)
#define TIMER_CNTRL_FDTS_DIV_4              (0x3UL << TIMER_CNTRL_FDTS_Pos)

#define TIMER_CNTRL_CNT_MODE_Pos            6
#define TIMER_CNTRL_CNT_MODE_Msk            (0x3UL << TIMER_CNTRL_CNT_MODE_Pos)
#define TIMER_CNTRL_CNT_MODE_CLK_FIXED_DIR  (0x0UL << TIMER_CNTRL_CNT_MODE_Pos)
#define TIMER_CNTRL_CNT_MODE_CLK_CHANGE_DIR (0x1UL << TIMER_CNTRL_CNT_MODE_Pos)
#define TIMER_CNTRL_CNT_MODE_EVNT_FIXED_DIR (0x2UL << TIMER_CNTRL_CNT_MODE_Pos)

#define TIMER_CNTRL_EVENT_SEL_Pos           8
#define TIMER_CNTRL_EVENT_SEL_Msk           (0xFUL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_TIM_CLK       (0x0UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_TIM0          (0x1UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_TIM1          (0x2UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_CH1           (0x4UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_CH2           (0x5UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_CH3           (0x6UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_CH4           (0x7UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_ETR_RE        (0x8UL << TIMER_CNTRL_EVENT_SEL_Pos)
#define TIMER_CNTRL_EVENT_SEL_ETR_FE        (0x9UL << TIMER_CNTRL_EVENT_SEL_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_CNTRL */

/** @defgroup MDR32F21QI_TIMER_CCR TIMER_CCR
 * @{
 */

#define TIMER_CCR_CCR_Pos 0
#define TIMER_CCR_CCR_Msk (0xFFFFUL << TIMER_CCR_CCR_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_CCR */

/** @defgroup MDR32F21QI_TIMER_CH_CNTRL TIMER_CH_CNTRL
 * @{
 */

#define TIMER_CH_CNTRL_CHFLTR_Pos           0
#define TIMER_CH_CNTRL_CHFLTR_Msk           (0xFUL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_1_FDTS        (0x0UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_2_TIM_CLK     (0x1UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_4_TIM_CLK     (0x2UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_8_TIM_CLK     (0x3UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_2  (0x4UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_2  (0x5UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_4  (0x6UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_4  (0x7UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_8  (0x8UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_8  (0x9UL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_5_FDTS_DIV_16 (0xAUL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_16 (0xBUL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_16 (0xCUL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_5_FDTS_DIV_32 (0xDUL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_6_FDTS_DIV_32 (0xEUL << TIMER_CH_CNTRL_CHFLTR_Pos)
#define TIMER_CH_CNTRL_CHFLTR_8_FDTS_DIV_32 (0xFUL << TIMER_CH_CNTRL_CHFLTR_Pos)

#define TIMER_CH_CNTRL_CHSEL_Pos            4
#define TIMER_CH_CNTRL_CHSEL_Msk            (0x3UL << TIMER_CH_CNTRL_CHSEL_Pos)
#define TIMER_CH_CNTRL_CHSEL_CH_RE          (0x0UL << TIMER_CH_CNTRL_CHSEL_Pos)
#define TIMER_CH_CNTRL_CHSEL_CH_FE          (0x1UL << TIMER_CH_CNTRL_CHSEL_Pos)
#define TIMER_CH_CNTRL_CHSEL_CHp1_RE        (0x2UL << TIMER_CH_CNTRL_CHSEL_Pos)
#define TIMER_CH_CNTRL_CHSEL_CHp2_RE        (0x3UL << TIMER_CH_CNTRL_CHSEL_Pos)

#define TIMER_CH_CNTRL_CHPSC_Pos            6
#define TIMER_CH_CNTRL_CHPSC_Msk            (0x3UL << TIMER_CH_CNTRL_CHPSC_Pos)
#define TIMER_CH_CNTRL_CHPSC_DIV_1          (0x0UL << TIMER_CH_CNTRL_CHPSC_Pos)
#define TIMER_CH_CNTRL_CHPSC_DIV_2          (0x1UL << TIMER_CH_CNTRL_CHPSC_Pos)
#define TIMER_CH_CNTRL_CHPSC_DIV_4          (0x2UL << TIMER_CH_CNTRL_CHPSC_Pos)
#define TIMER_CH_CNTRL_CHPSC_DIV_8          (0x3UL << TIMER_CH_CNTRL_CHPSC_Pos)

#define TIMER_CH_CNTRL_OCCE_Pos             8
#define TIMER_CH_CNTRL_OCCE_Msk             (0x1UL << TIMER_CH_CNTRL_OCCE_Pos)
#define TIMER_CH_CNTRL_OCCE                 TIMER_CH_CNTRL_OCCE_Msk

#define TIMER_CH_CNTRL_OCCM_Pos             9
#define TIMER_CH_CNTRL_OCCM_Msk             (0x7UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_0        (0x0UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_1        (0x1UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_2        (0x2UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_3        (0x3UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_4        (0x4UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_5        (0x5UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_6        (0x6UL << TIMER_CH_CNTRL_OCCM_Pos)
#define TIMER_CH_CNTRL_OCCM_FORMAT_7        (0x7UL << TIMER_CH_CNTRL_OCCM_Pos)

#define TIMER_CH_CNTRL_BRKEN_Pos            12
#define TIMER_CH_CNTRL_BRKEN_Msk            (0x1UL << TIMER_CH_CNTRL_BRKEN_Pos)
#define TIMER_CH_CNTRL_BRKEN                TIMER_CH_CNTRL_BRKEN_Msk

#define TIMER_CH_CNTRL_ETREN_Pos            13
#define TIMER_CH_CNTRL_ETREN_Msk            (0x1UL << TIMER_CH_CNTRL_ETREN_Pos)
#define TIMER_CH_CNTRL_ETREN                TIMER_CH_CNTRL_ETREN_Msk

#define TIMER_CH_CNTRL_WR_CMPL_Pos          14
#define TIMER_CH_CNTRL_WR_CMPL_Msk          (0x1UL << TIMER_CH_CNTRL_WR_CMPL_Pos)
#define TIMER_CH_CNTRL_WR_CMPL              TIMER_CH_CNTRL_WR_CMPL_Msk

#define TIMER_CH_CNTRL_CAP_nPWM_Pos         15
#define TIMER_CH_CNTRL_CAP_nPWM_Msk         (0x1UL << TIMER_CH_CNTRL_CAP_nPWM_Pos)
#define TIMER_CH_CNTRL_CAP_nPWM             TIMER_CH_CNTRL_CAP_nPWM_Msk

#define TIMER_CH_CNTRL_WR_CMPL1_Pos         16
#define TIMER_CH_CNTRL_WR_CMPL1_Msk         (0x1UL << TIMER_CH_CNTRL_WR_CMPL1_Pos)
#define TIMER_CH_CNTRL_WR_CMPL1             TIMER_CH_CNTRL_WR_CMPL1_Msk

/** @} */ /* End of group MDR32F21QI_TIMER_CH_CNTRL */

/** @defgroup MDR32F21QI_TIMER_CH_CNTRL1 TIMER_CH_CNTRL1
 * @{
 */

#define TIMER_CH_CNTRL1_SELOE_Pos   0
#define TIMER_CH_CNTRL1_SELOE_Msk   (0x3UL << TIMER_CH_CNTRL1_SELOE_Pos)
#define TIMER_CH_CNTRL1_SELOE_ALW0  (0x0UL << TIMER_CH_CNTRL1_SELOE_Pos)
#define TIMER_CH_CNTRL1_SELOE_ALW1  (0x1UL << TIMER_CH_CNTRL1_SELOE_Pos)
#define TIMER_CH_CNTRL1_SELOE_REF   (0x2UL << TIMER_CH_CNTRL1_SELOE_Pos)
#define TIMER_CH_CNTRL1_SELOE_DTG   (0x3UL << TIMER_CH_CNTRL1_SELOE_Pos)

#define TIMER_CH_CNTRL1_SELO_Pos    2
#define TIMER_CH_CNTRL1_SELO_Msk    (0x3UL << TIMER_CH_CNTRL1_SELO_Pos)
#define TIMER_CH_CNTRL1_SELO_ALW0   (0x0UL << TIMER_CH_CNTRL1_SELO_Pos)
#define TIMER_CH_CNTRL1_SELO_ALW1   (0x1UL << TIMER_CH_CNTRL1_SELO_Pos)
#define TIMER_CH_CNTRL1_SELO_REF    (0x2UL << TIMER_CH_CNTRL1_SELO_Pos)
#define TIMER_CH_CNTRL1_SELO_DTG    (0x3UL << TIMER_CH_CNTRL1_SELO_Pos)

#define TIMER_CH_CNTRL1_INV_Pos     4
#define TIMER_CH_CNTRL1_INV_Msk     (0x1UL << TIMER_CH_CNTRL1_INV_Pos)
#define TIMER_CH_CNTRL1_INV         TIMER_CH_CNTRL1_INV_Msk

#define TIMER_CH_CNTRL1_NSELOE_Pos  8
#define TIMER_CH_CNTRL1_NSELOE_Msk  (0x3UL << TIMER_CH_CNTRL1_NSELOE_Pos)
#define TIMER_CH_CNTRL1_NSELOE_ALW0 (0x0UL << TIMER_CH_CNTRL1_NSELOE_Pos)
#define TIMER_CH_CNTRL1_NSELOE_ALW1 (0x1UL << TIMER_CH_CNTRL1_NSELOE_Pos)
#define TIMER_CH_CNTRL1_NSELOE_REF  (0x2UL << TIMER_CH_CNTRL1_NSELOE_Pos)
#define TIMER_CH_CNTRL1_NSELOE_DTG  (0x3UL << TIMER_CH_CNTRL1_NSELOE_Pos)

#define TIMER_CH_CNTRL1_NSELO_Pos   10
#define TIMER_CH_CNTRL1_NSELO_Msk   (0x3UL << TIMER_CH_CNTRL1_NSELO_Pos)
#define TIMER_CH_CNTRL1_NSELO_ALW0  (0x0UL << TIMER_CH_CNTRL1_NSELO_Pos)
#define TIMER_CH_CNTRL1_NSELO_ALW1  (0x1UL << TIMER_CH_CNTRL1_NSELO_Pos)
#define TIMER_CH_CNTRL1_NSELO_REF   (0x2UL << TIMER_CH_CNTRL1_NSELO_Pos)
#define TIMER_CH_CNTRL1_NSELO_DTG   (0x3UL << TIMER_CH_CNTRL1_NSELO_Pos)

#define TIMER_CH_CNTRL1_NINV_Pos    12
#define TIMER_CH_CNTRL1_NINV_Msk    (0x1UL << TIMER_CH_CNTRL1_NINV_Pos)
#define TIMER_CH_CNTRL1_NINV        TIMER_CH_CNTRL1_NINV_Msk

/** @} */ /* End of group MDR32F21QI_TIMER_CH_CNTRL1 */

/** @defgroup MDR32F21QI_TIMER_CH_DTG TIMER_CH_DTG
 * @{
 */

#define TIMER_CH_DTG_DTGX_Pos 0
#define TIMER_CH_DTG_DTGX_Msk (0xFUL << TIMER_CH_DTG_DTGX_Pos)

#define TIMER_CH_DTG_EDTS_Pos 4
#define TIMER_CH_DTG_EDTS_Msk (0x1UL << TIMER_CH_DTG_EDTS_Pos)
#define TIMER_CH_DTG_EDTS     TIMER_CH_DTG_EDTS_Msk

#define TIMER_CH_DTG_DTG_Pos  8
#define TIMER_CH_DTG_DTG_Msk  (0xFFUL << TIMER_CH_DTG_DTG_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_CH_DTG */

/** @defgroup MDR32F21QI_TIMER_BRKETR_CNTRL TIMER_BRKETR_CNTRL
 * @{
 */

#define TIMER_BRKETR_CNTRL_BRK_INV_Pos              0
#define TIMER_BRKETR_CNTRL_BRK_INV_Msk              (0x1UL << TIMER_BRKETR_CNTRL_BRK_INV_Pos)
#define TIMER_BRKETR_CNTRL_BRK_INV                  TIMER_BRKETR_CNTRL_BRK_INV_Msk

#define TIMER_BRKETR_CNTRL_ETR_INV_Pos              1
#define TIMER_BRKETR_CNTRL_ETR_INV_Msk              (0x1UL << TIMER_BRKETR_CNTRL_ETR_INV_Pos)
#define TIMER_BRKETR_CNTRL_ETR_INV                  TIMER_BRKETR_CNTRL_ETR_INV_Msk

#define TIMER_BRKETR_CNTRL_ETR_PSC_Pos              2
#define TIMER_BRKETR_CNTRL_ETR_PSC_Msk              (0x3UL << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)
#define TIMER_BRKETR_CNTRL_ETR_PSC_DIV_1            (0x0UL << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)
#define TIMER_BRKETR_CNTRL_ETR_PSC_DIV_2            (0x1UL << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)
#define TIMER_BRKETR_CNTRL_ETR_PSC_DIV_4            (0x2UL << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)
#define TIMER_BRKETR_CNTRL_ETR_PSC_DIV_8            (0x3UL << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)

#define TIMER_BRKETR_CNTRL_ETR_FILTER_Pos           4
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Msk           (0xFUL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_1_FDTS        (0x0UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_2_TIM_CLK     (0x1UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_4_TIM_CLK     (0x2UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_8_TIM_CLK     (0x3UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_2  (0x4UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_2  (0x5UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_4  (0x6UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_4  (0x7UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_8  (0x8UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_8  (0x9UL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_5_FDTS_DIV_16 (0xAUL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_16 (0xBUL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_16 (0xCUL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_5_FDTS_DIV_32 (0xDUL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_6_FDTS_DIV_32 (0xEUL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_8_FDTS_DIV_32 (0xFUL << TIMER_BRKETR_CNTRL_ETR_FILTER_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_BRKETR_CNTRL */

/** @defgroup MDR32F21QI_TIMER_STATUS TIMER_STATUS
 * @{
 */

#define TIMER_STATUS_CNT_ZERO_EVENT_Pos     0
#define TIMER_STATUS_CNT_ZERO_EVENT_Msk     (0x1UL << TIMER_STATUS_CNT_ZERO_EVENT_Pos)
#define TIMER_STATUS_CNT_ZERO_EVENT         TIMER_STATUS_CNT_ZERO_EVENT_Msk

#define TIMER_STATUS_CNT_ARR_EVENT_Pos      1
#define TIMER_STATUS_CNT_ARR_EVENT_Msk      (0x1UL << TIMER_STATUS_CNT_ARR_EVENT_Pos)
#define TIMER_STATUS_CNT_ARR_EVENT          TIMER_STATUS_CNT_ARR_EVENT_Msk

#define TIMER_STATUS_ETR_RE_EVENT_Pos       2
#define TIMER_STATUS_ETR_RE_EVENT_Msk       (0x1UL << TIMER_STATUS_ETR_RE_EVENT_Pos)
#define TIMER_STATUS_ETR_RE_EVENT           TIMER_STATUS_ETR_RE_EVENT_Msk

#define TIMER_STATUS_ETR_FE_EVENT_Pos       3
#define TIMER_STATUS_ETR_FE_EVENT_Msk       (0x1UL << TIMER_STATUS_ETR_FE_EVENT_Pos)
#define TIMER_STATUS_ETR_FE_EVENT           TIMER_STATUS_ETR_FE_EVENT_Msk

#define TIMER_STATUS_BRK_EVENT_Pos          4
#define TIMER_STATUS_BRK_EVENT_Msk          (0x1UL << TIMER_STATUS_BRK_EVENT_Pos)
#define TIMER_STATUS_BRK_EVENT              TIMER_STATUS_BRK_EVENT_Msk

#define TIMER_STATUS_CCR_CAP_EVENT_CH1_Pos  5
#define TIMER_STATUS_CCR_CAP_EVENT_CH1_Msk  (0x1UL << TIMER_STATUS_CCR_CAP_EVENT_CH1_Pos)
#define TIMER_STATUS_CCR_CAP_EVENT_CH1      TIMER_STATUS_CCR_CAP_EVENT_CH1_Msk

#define TIMER_STATUS_CCR_CAP_EVENT_CH2_Pos  6
#define TIMER_STATUS_CCR_CAP_EVENT_CH2_Msk  (0x1UL << TIMER_STATUS_CCR_CAP_EVENT_CH2_Pos)
#define TIMER_STATUS_CCR_CAP_EVENT_CH2      TIMER_STATUS_CCR_CAP_EVENT_CH2_Msk

#define TIMER_STATUS_CCR_CAP_EVENT_CH3_Pos  7
#define TIMER_STATUS_CCR_CAP_EVENT_CH3_Msk  (0x1UL << TIMER_STATUS_CCR_CAP_EVENT_CH3_Pos)
#define TIMER_STATUS_CCR_CAP_EVENT_CH3      TIMER_STATUS_CCR_CAP_EVENT_CH3_Msk

#define TIMER_STATUS_CCR_CAP_EVENT_CH4_Pos  8
#define TIMER_STATUS_CCR_CAP_EVENT_CH4_Msk  (0x1UL << TIMER_STATUS_CCR_CAP_EVENT_CH4_Pos)
#define TIMER_STATUS_CCR_CAP_EVENT_CH4      TIMER_STATUS_CCR_CAP_EVENT_CH4_Msk

#define TIMER_STATUS_CCR_REF_EVENT_CH1_Pos  9
#define TIMER_STATUS_CCR_REF_EVENT_CH1_Msk  (0x1UL << TIMER_STATUS_CCR_REF_EVENT_CH1_Pos)
#define TIMER_STATUS_CCR_REF_EVENT_CH1      TIMER_STATUS_CCR_REF_EVENT_CH1_Msk

#define TIMER_STATUS_CCR_REF_EVENT_CH2_Pos  10
#define TIMER_STATUS_CCR_REF_EVENT_CH2_Msk  (0x1UL << TIMER_STATUS_CCR_REF_EVENT_CH2_Pos)
#define TIMER_STATUS_CCR_REF_EVENT_CH2      TIMER_STATUS_CCR_REF_EVENT_CH2_Msk

#define TIMER_STATUS_CCR_REF_EVENT_CH3_Pos  11
#define TIMER_STATUS_CCR_REF_EVENT_CH3_Msk  (0x1UL << TIMER_STATUS_CCR_REF_EVENT_CH3_Pos)
#define TIMER_STATUS_CCR_REF_EVENT_CH3      TIMER_STATUS_CCR_REF_EVENT_CH3_Msk

#define TIMER_STATUS_CCR_REF_EVENT_CH4_Pos  12
#define TIMER_STATUS_CCR_REF_EVENT_CH4_Msk  (0x1UL << TIMER_STATUS_CCR_REF_EVENT_CH4_Pos)
#define TIMER_STATUS_CCR_REF_EVENT_CH4      TIMER_STATUS_CCR_REF_EVENT_CH4_Msk

#define TIMER_STATUS_CCR_CAP1_EVENT_CH1_Pos 13
#define TIMER_STATUS_CCR_CAP1_EVENT_CH1_Msk (0x1UL << TIMER_STATUS_CCR_CAP1_EVENT_CH1_Pos)
#define TIMER_STATUS_CCR_CAP1_EVENT_CH1     TIMER_STATUS_CCR_CAP1_EVENT_CH1_Msk

#define TIMER_STATUS_CCR_CAP1_EVENT_CH2_Pos 14
#define TIMER_STATUS_CCR_CAP1_EVENT_CH2_Msk (0x1UL << TIMER_STATUS_CCR_CAP1_EVENT_CH2_Pos)
#define TIMER_STATUS_CCR_CAP1_EVENT_CH2     TIMER_STATUS_CCR_CAP1_EVENT_CH2_Msk

#define TIMER_STATUS_CCR_CAP1_EVENT_CH3_Pos 15
#define TIMER_STATUS_CCR_CAP1_EVENT_CH3_Msk (0x1UL << TIMER_STATUS_CCR_CAP1_EVENT_CH3_Pos)
#define TIMER_STATUS_CCR_CAP1_EVENT_CH3     TIMER_STATUS_CCR_CAP1_EVENT_CH3_Msk

#define TIMER_STATUS_CCR_CAP1_EVENT_CH4_Pos 16
#define TIMER_STATUS_CCR_CAP1_EVENT_CH4_Msk (0x1UL << TIMER_STATUS_CCR_CAP1_EVENT_CH4_Pos)
#define TIMER_STATUS_CCR_CAP1_EVENT_CH4     TIMER_STATUS_CCR_CAP1_EVENT_CH4_Msk

/** @} */ /* End of group MDR32F21QI_TIMER_STATUS */

/** @defgroup MDR32F21QI_TIMER_IE TIMER_IE
 * @{
 */

#define TIMER_IE_CNT_ZERO_EVENT_IE_Pos     0
#define TIMER_IE_CNT_ZERO_EVENT_IE_Msk     (0x1UL << TIMER_IE_CNT_ZERO_EVENT_IE_Pos)
#define TIMER_IE_CNT_ZERO_EVENT_IE         TIMER_IE_CNT_ZERO_EVENT_IE_Msk

#define TIMER_IE_CNT_ARR_EVENT_IE_Pos      1
#define TIMER_IE_CNT_ARR_EVENT_IE_Msk      (0x1UL << TIMER_IE_CNT_ARR_EVENT_IE_Pos)
#define TIMER_IE_CNT_ARR_EVENT_IE          TIMER_IE_CNT_ARR_EVENT_IE_Msk

#define TIMER_IE_ETR_RE_EVENT_IE_Pos       2
#define TIMER_IE_ETR_RE_EVENT_IE_Msk       (0x1UL << TIMER_IE_ETR_RE_EVENT_IE_Pos)
#define TIMER_IE_ETR_RE_EVENT_IE           TIMER_IE_ETR_RE_EVENT_IE_Msk

#define TIMER_IE_ETR_FE_EVENT_IE_Pos       3
#define TIMER_IE_ETR_FE_EVENT_IE_Msk       (0x1UL << TIMER_IE_ETR_FE_EVENT_IE_Pos)
#define TIMER_IE_ETR_FE_EVENT_IE           TIMER_IE_ETR_FE_EVENT_IE_Msk

#define TIMER_IE_BRK_EVENT_IE_Pos          4
#define TIMER_IE_BRK_EVENT_IE_Msk          (0x1UL << TIMER_IE_BRK_EVENT_IE_Pos)
#define TIMER_IE_BRK_EVENT_IE              TIMER_IE_BRK_EVENT_IE_Msk

#define TIMER_IE_CCR_CAP_EVENT_IE_CH1_Pos  5
#define TIMER_IE_CCR_CAP_EVENT_IE_CH1_Msk  (0x1UL << TIMER_IE_CCR_CAP_EVENT_IE_CH1_Pos)
#define TIMER_IE_CCR_CAP_EVENT_IE_CH1      TIMER_IE_CCR_CAP_EVENT_IE_CH1_Msk

#define TIMER_IE_CCR_CAP_EVENT_IE_CH2_Pos  6
#define TIMER_IE_CCR_CAP_EVENT_IE_CH2_Msk  (0x1UL << TIMER_IE_CCR_CAP_EVENT_IE_CH2_Pos)
#define TIMER_IE_CCR_CAP_EVENT_IE_CH2      TIMER_IE_CCR_CAP_EVENT_IE_CH2_Msk

#define TIMER_IE_CCR_CAP_EVENT_IE_CH3_Pos  7
#define TIMER_IE_CCR_CAP_EVENT_IE_CH3_Msk  (0x1UL << TIMER_IE_CCR_CAP_EVENT_IE_CH3_Pos)
#define TIMER_IE_CCR_CAP_EVENT_IE_CH3      TIMER_IE_CCR_CAP_EVENT_IE_CH3_Msk

#define TIMER_IE_CCR_CAP_EVENT_IE_CH4_Pos  8
#define TIMER_IE_CCR_CAP_EVENT_IE_CH4_Msk  (0x1UL << TIMER_IE_CCR_CAP_EVENT_IE_CH4_Pos)
#define TIMER_IE_CCR_CAP_EVENT_IE_CH4      TIMER_IE_CCR_CAP_EVENT_IE_CH4_Msk

#define TIMER_IE_CCR_REF_EVENT_IE_CH1_Pos  9
#define TIMER_IE_CCR_REF_EVENT_IE_CH1_Msk  (0x1UL << TIMER_IE_CCR_REF_EVENT_IE_CH1_Pos)
#define TIMER_IE_CCR_REF_EVENT_IE_CH1      TIMER_IE_CCR_REF_EVENT_IE_CH1_Msk

#define TIMER_IE_CCR_REF_EVENT_IE_CH2_Pos  10
#define TIMER_IE_CCR_REF_EVENT_IE_CH2_Msk  (0x1UL << TIMER_IE_CCR_REF_EVENT_IE_CH2_Pos)
#define TIMER_IE_CCR_REF_EVENT_IE_CH2      TIMER_IE_CCR_REF_EVENT_IE_CH2_Msk

#define TIMER_IE_CCR_REF_EVENT_IE_CH3_Pos  11
#define TIMER_IE_CCR_REF_EVENT_IE_CH3_Msk  (0x1UL << TIMER_IE_CCR_REF_EVENT_IE_CH3_Pos)
#define TIMER_IE_CCR_REF_EVENT_IE_CH3      TIMER_IE_CCR_REF_EVENT_IE_CH3_Msk

#define TIMER_IE_CCR_REF_EVENT_IE_CH4_Pos  12
#define TIMER_IE_CCR_REF_EVENT_IE_CH4_Msk  (0x1UL << TIMER_IE_CCR_REF_EVENT_IE_CH4_Pos)
#define TIMER_IE_CCR_REF_EVENT_IE_CH4      TIMER_IE_CCR_REF_EVENT_IE_CH4_Msk

#define TIMER_IE_CCR_CAP1_EVENT_IE_CH1_Pos 13
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH1_Msk (0x1UL << TIMER_IE_CCR_CAP1_EVENT_IE_CH1_Pos)
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH1     TIMER_IE_CCR_CAP1_EVENT_IE_CH1_Msk

#define TIMER_IE_CCR_CAP1_EVENT_IE_CH2_Pos 14
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH2_Msk (0x1UL << TIMER_IE_CCR_CAP1_EVENT_IE_CH2_Pos)
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH2     TIMER_IE_CCR_CAP1_EVENT_IE_CH2_Msk

#define TIMER_IE_CCR_CAP1_EVENT_IE_CH3_Pos 15
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH3_Msk (0x1UL << TIMER_IE_CCR_CAP1_EVENT_IE_CH3_Pos)
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH3     TIMER_IE_CCR_CAP1_EVENT_IE_CH3_Msk

#define TIMER_IE_CCR_CAP1_EVENT_IE_CH4_Pos 16
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH4_Msk (0x1UL << TIMER_IE_CCR_CAP1_EVENT_IE_CH4_Pos)
#define TIMER_IE_CCR_CAP1_EVENT_IE_CH4     TIMER_IE_CCR_CAP1_EVENT_IE_CH4_Msk

/** @} */ /* End of group MDR32F21QI_TIMER_IE */

/** @defgroup MDR32F21QI_TIMER_DMA_RE TIMER_DMA_RE
 * @{
 */

#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE_Pos     0
#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE_Msk     (0x1UL << TIMER_DMA_RE_CNT_ZERO_EVENT_RE_Pos)
#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE         TIMER_DMA_RE_CNT_ZERO_EVENT_RE_Msk

#define TIMER_DMA_RE_CNT_ARR_EVENT_RE_Pos      1
#define TIMER_DMA_RE_CNT_ARR_EVENT_RE_Msk      (0x1UL << TIMER_DMA_RE_CNT_ARR_EVENT_RE_Pos)
#define TIMER_DMA_RE_CNT_ARR_EVENT_RE          TIMER_DMA_RE_CNT_ARR_EVENT_RE_Msk

#define TIMER_DMA_RE_ETR_RE_EVENT_RE_Pos       2
#define TIMER_DMA_RE_ETR_RE_EVENT_RE_Msk       (0x1UL << TIMER_DMA_RE_ETR_RE_EVENT_RE_Pos)
#define TIMER_DMA_RE_ETR_RE_EVENT_RE           TIMER_DMA_RE_ETR_RE_EVENT_RE_Msk

#define TIMER_DMA_RE_ETR_FE_EVENT_RE_Pos       3
#define TIMER_DMA_RE_ETR_FE_EVENT_RE_Msk       (0x1UL << TIMER_DMA_RE_ETR_FE_EVENT_RE_Pos)
#define TIMER_DMA_RE_ETR_FE_EVENT_RE           TIMER_DMA_RE_ETR_FE_EVENT_RE_Msk

#define TIMER_DMA_RE_BRK_EVENT_RE_Pos          4
#define TIMER_DMA_RE_BRK_EVENT_RE_Msk          (0x1UL << TIMER_DMA_RE_BRK_EVENT_RE_Pos)
#define TIMER_DMA_RE_BRK_EVENT_RE              TIMER_DMA_RE_BRK_EVENT_RE_Msk

#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH1_Pos  5
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH1_Msk  (0x1UL << TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH1_Pos)
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH1      TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH1_Msk

#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH2_Pos  6
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH2_Msk  (0x1UL << TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH2_Pos)
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH2      TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH2_Msk

#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH3_Pos  7
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH3_Msk  (0x1UL << TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH3_Pos)
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH3      TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH3_Msk

#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH4_Pos  8
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH4_Msk  (0x1UL << TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH4_Pos)
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH4      TIMER_DMA_RE_CCR_CAP_EVENT_RE_CH4_Msk

#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH1_Pos  9
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH1_Msk  (0x1UL << TIMER_DMA_RE_CCR_REF_EVENT_RE_CH1_Pos)
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH1      TIMER_DMA_RE_CCR_REF_EVENT_RE_CH1_Msk

#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH2_Pos  10
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH2_Msk  (0x1UL << TIMER_DMA_RE_CCR_REF_EVENT_RE_CH2_Pos)
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH2      TIMER_DMA_RE_CCR_REF_EVENT_RE_CH2_Msk

#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH3_Pos  11
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH3_Msk  (0x1UL << TIMER_DMA_RE_CCR_REF_EVENT_RE_CH3_Pos)
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH3      TIMER_DMA_RE_CCR_REF_EVENT_RE_CH3_Msk

#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH4_Pos  12
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH4_Msk  (0x1UL << TIMER_DMA_RE_CCR_REF_EVENT_RE_CH4_Pos)
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_CH4      TIMER_DMA_RE_CCR_REF_EVENT_RE_CH4_Msk

#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH1_Pos 13
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH1_Msk (0x1UL << TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH1_Pos)
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH1     TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH1_Msk

#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH2_Pos 14
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH2_Msk (0x1UL << TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH2_Pos)
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH2     TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH2_Msk

#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH3_Pos 15
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH3_Msk (0x1UL << TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH3_Pos)
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH3     TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH3_Msk

#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH4_Pos 16
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH4_Msk (0x1UL << TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH4_Pos)
#define TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH4     TIMER_DMA_RE_CCR_CAP1_EVENT_RE_CH4_Msk

/** @} */ /* End of group MDR32F21QI_TIMER_DMA_RE */

/** @defgroup MDR32F21QI_TIMER_CH_CNTRL2 TIMER_CH_CNTRL2
 * @{
 */

#define TIMER_CH_CNTRL2_CHSEL_Pos     0
#define TIMER_CH_CNTRL2_CHSEL_Msk     (0x3UL << TIMER_CH_CNTRL2_CHSEL_Pos)
#define TIMER_CH_CNTRL2_CHSEL_CH_RE   (0x0UL << TIMER_CH_CNTRL2_CHSEL_Pos)
#define TIMER_CH_CNTRL2_CHSEL_CH_FE   (0x1UL << TIMER_CH_CNTRL2_CHSEL_Pos)
#define TIMER_CH_CNTRL2_CHSEL_CHp1_FE (0x2UL << TIMER_CH_CNTRL2_CHSEL_Pos)
#define TIMER_CH_CNTRL2_CHSEL_CHp2_FE (0x3UL << TIMER_CH_CNTRL2_CHSEL_Pos)

#define TIMER_CH_CNTRL2_CCR1_EN_Pos   2
#define TIMER_CH_CNTRL2_CCR1_EN_Msk   (0x1UL << TIMER_CH_CNTRL2_CCR1_EN_Pos)
#define TIMER_CH_CNTRL2_CCR1_EN       TIMER_CH_CNTRL2_CCR1_EN_Msk

#define TIMER_CH_CNTRL2_CCRRLD_Pos    3
#define TIMER_CH_CNTRL2_CCRRLD_Msk    (0x1UL << TIMER_CH_CNTRL2_CCRRLD_Pos)
#define TIMER_CH_CNTRL2_CCRRLD        TIMER_CH_CNTRL2_CCRRLD_Msk

/** @} */ /* End of group MDR32F21QI_TIMER_CH_CNTRL2 */

/** @defgroup MDR32F21QI_TIMER_CCR1 TIMER_CCR1
 * @{
 */

#define TIMER_CCR1_CCR1_Pos 0
#define TIMER_CCR1_CCR1_Msk (0xFFFFUL << TIMER_CCR1_CCR1_Pos)

/** @} */ /* End of group MDR32F21QI_TIMER_CCR1 */

/** @} */ /* End of group MDR32F21QI_TIMER_Defines */

/** @} */ /* End of group MDR32F21QI_TIMER */

/** @defgroup MDR32F21QI_PORT MDR_PORT
 * @{
 */

/**
 * @brief MDR32F21QI PORT control structure
 */
typedef struct {
    __IO uint32_t RXTX;   /*!<PORT Data Register */
    __IO uint32_t OE;     /*!<PORT Output Enable Register */
    __IO uint32_t FUNC;   /*!<PORT Function Register */
    __IO uint32_t ANALOG; /*!<PORT Analog Function Register */
    __IO uint32_t PULL;   /*!<PORT Pull Up/Down Register */
    __IO uint32_t PD;     /*!<PORT Driver Mode Register */
    __IO uint32_t PWR;    /*!<PORT Power Register */
    __IO uint32_t GFEN;   /*!<PORT Filter Configuration Register */
    __IO uint32_t SETTX;  /*!<PORT Set Output Register */
    __IO uint32_t CLRTX;  /*!<PORT Reset Output Register */
    __IO uint32_t RDTX;   /*!<PORT Read Output Register */
} MDR_PORT_TypeDef;

/** @defgroup MDR32F21QI_PORT_Defines PORT Defines
 * @{
 */

/** @defgroup MDR32F21QI_PORT_RXTX PORT_RXTX
 * @{
 */

#define PORT_RXTX_RXTX_Pos 0
#define PORT_RXTX_RXTX_Msk (0xFFFFUL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX0    (0x0001UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX1    (0x0002UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX2    (0x0004UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX3    (0x0008UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX4    (0x0010UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX5    (0x0020UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX6    (0x0040UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX7    (0x0080UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX8    (0x0100UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX9    (0x0200UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX10   (0x0400UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX11   (0x0800UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX12   (0x1000UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX13   (0x2000UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX14   (0x4000UL << PORT_RXTX_RXTX_Pos)
#define PORT_RXTX_RXTX15   (0x8000UL << PORT_RXTX_RXTX_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_RXTX */

/** @defgroup MDR32F21QI_PORT_OE PORT_OE
 * @{
 */

#define PORT_OE_OE_Pos 0
#define PORT_OE_OE_Msk (0xFFFFUL << PORT_OE_OE_Pos)
#define PORT_OE_OE0    (0x0001UL << PORT_OE_OE_Pos)
#define PORT_OE_OE1    (0x0002UL << PORT_OE_OE_Pos)
#define PORT_OE_OE2    (0x0004UL << PORT_OE_OE_Pos)
#define PORT_OE_OE3    (0x0008UL << PORT_OE_OE_Pos)
#define PORT_OE_OE4    (0x0010UL << PORT_OE_OE_Pos)
#define PORT_OE_OE5    (0x0020UL << PORT_OE_OE_Pos)
#define PORT_OE_OE6    (0x0040UL << PORT_OE_OE_Pos)
#define PORT_OE_OE7    (0x0080UL << PORT_OE_OE_Pos)
#define PORT_OE_OE8    (0x0100UL << PORT_OE_OE_Pos)
#define PORT_OE_OE9    (0x0200UL << PORT_OE_OE_Pos)
#define PORT_OE_OE10   (0x0400UL << PORT_OE_OE_Pos)
#define PORT_OE_OE11   (0x0800UL << PORT_OE_OE_Pos)
#define PORT_OE_OE12   (0x1000UL << PORT_OE_OE_Pos)
#define PORT_OE_OE13   (0x2000UL << PORT_OE_OE_Pos)
#define PORT_OE_OE14   (0x4000UL << PORT_OE_OE_Pos)
#define PORT_OE_OE15   (0x8000UL << PORT_OE_OE_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_OE */

/** @defgroup MDR32F21QI_PORT_FUNC PORT_FUNC
 * @{
 */

#define PORT_FUNC_MODE_Pos 0
#define PORT_FUNC_MODE_Msk (0xFFFFFFFFUL)
#define PORT_FUNC_MODE0    (0x00000003UL)
#define PORT_FUNC_MODE1    (0x0000000CUL)
#define PORT_FUNC_MODE2    (0x00000030UL)
#define PORT_FUNC_MODE3    (0x000000C0UL)
#define PORT_FUNC_MODE4    (0x00000300UL)
#define PORT_FUNC_MODE5    (0x00000C00UL)
#define PORT_FUNC_MODE6    (0x00003000UL)
#define PORT_FUNC_MODE7    (0x0000C000UL)
#define PORT_FUNC_MODE8    (0x00030000UL)
#define PORT_FUNC_MODE9    (0x000C0000UL)
#define PORT_FUNC_MODE10   (0x00300000UL)
#define PORT_FUNC_MODE11   (0x00C00000UL)
#define PORT_FUNC_MODE12   (0x03000000UL)
#define PORT_FUNC_MODE13   (0x0C000000UL)
#define PORT_FUNC_MODE14   (0x30000000UL)
#define PORT_FUNC_MODE15   (0xC0000000UL)

/** @} */ /* End of group MDR32F21QI_PORT_FUNC */

/** @defgroup MDR32F21QI_PORT_ANALOG PORT_ANALOG
 * @{
 */

#define PORT_ANALOG_ANALOG_EN_Pos 0
#define PORT_ANALOG_ANALOG_EN_Msk (0xFFFFUL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN0    (0x0001UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN1    (0x0002UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN2    (0x0004UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN3    (0x0008UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN4    (0x0010UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN5    (0x0020UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN6    (0x0040UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN7    (0x0080UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN8    (0x0100UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN9    (0x0200UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN10   (0x0400UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN11   (0x0800UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN12   (0x1000UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN13   (0x2000UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN14   (0x4000UL << PORT_ANALOG_ANALOG_EN_Pos)
#define PORT_ANALOG_ANALOG_EN15   (0x8000UL << PORT_ANALOG_ANALOG_EN_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_ANALOG */

/** @defgroup MDR32F21QI_PORT_PULL PORT_PULL
 * @{
 */

#define PORT_PULL_PULL_DOWN_Pos 0
#define PORT_PULL_PULL_DOWN_Msk (0xFFFFUL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN0    (0x0001UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN1    (0x0002UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN2    (0x0004UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN3    (0x0008UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN4    (0x0010UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN5    (0x0020UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN6    (0x0040UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN7    (0x0080UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN8    (0x0100UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN9    (0x0200UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN10   (0x0400UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN11   (0x0800UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN12   (0x1000UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN13   (0x2000UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN14   (0x4000UL << PORT_PULL_PULL_DOWN_Pos)
#define PORT_PULL_PULL_DOWN15   (0x8000UL << PORT_PULL_PULL_DOWN_Pos)

#define PORT_PULL_PULL_UP_Pos   16
#define PORT_PULL_PULL_UP_Msk   (0xFFFFUL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP0      (0x0001UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP1      (0x0002UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP2      (0x0004UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP3      (0x0008UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP4      (0x0010UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP5      (0x0020UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP6      (0x0040UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP7      (0x0080UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP8      (0x0100UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP9      (0x0200UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP10     (0x0400UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP11     (0x0800UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP12     (0x1000UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP13     (0x2000UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP14     (0x4000UL << PORT_PULL_PULL_UP_Pos)
#define PORT_PULL_PULL_UP15     (0x8000UL << PORT_PULL_PULL_UP_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_PULL */

/** @defgroup MDR32F21QI_PORT_PD PORT_PD
 * @{
 */

#define PORT_PD_PD_Pos  0
#define PORT_PD_PD_Msk  (0xFFFFUL << PORT_PD_PD_Pos)
#define PORT_PD_PD0     (0x0001UL << PORT_PD_PD_Pos)
#define PORT_PD_PD1     (0x0002UL << PORT_PD_PD_Pos)
#define PORT_PD_PD2     (0x0004UL << PORT_PD_PD_Pos)
#define PORT_PD_PD3     (0x0008UL << PORT_PD_PD_Pos)
#define PORT_PD_PD4     (0x0010UL << PORT_PD_PD_Pos)
#define PORT_PD_PD5     (0x0020UL << PORT_PD_PD_Pos)
#define PORT_PD_PD6     (0x0040UL << PORT_PD_PD_Pos)
#define PORT_PD_PD7     (0x0080UL << PORT_PD_PD_Pos)
#define PORT_PD_PD8     (0x0100UL << PORT_PD_PD_Pos)
#define PORT_PD_PD9     (0x0200UL << PORT_PD_PD_Pos)
#define PORT_PD_PD10    (0x0400UL << PORT_PD_PD_Pos)
#define PORT_PD_PD11    (0x0800UL << PORT_PD_PD_Pos)
#define PORT_PD_PD12    (0x1000UL << PORT_PD_PD_Pos)
#define PORT_PD_PD13    (0x2000UL << PORT_PD_PD_Pos)
#define PORT_PD_PD14    (0x4000UL << PORT_PD_PD_Pos)
#define PORT_PD_PD15    (0x8000UL << PORT_PD_PD_Pos)

#define PORT_PD_SHM_Pos 16
#define PORT_PD_SHM_Msk (0xFFFFUL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM0    (0x0001UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM1    (0x0002UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM2    (0x0004UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM3    (0x0008UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM4    (0x0010UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM5    (0x0020UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM6    (0x0040UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM7    (0x0080UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM8    (0x0100UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM9    (0x0200UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM10   (0x0400UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM11   (0x0800UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM12   (0x1000UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM13   (0x2000UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM14   (0x4000UL << PORT_PD_SHM_Pos)
#define PORT_PD_SHM15   (0x8000UL << PORT_PD_SHM_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_PD */

/** @defgroup MDR32F21QI_PORT_PWR PORT_PWR
 * @{
 */

#define PORT_PWR_PWR_Pos 0
#define PORT_PWR_PWR_Msk (0xFFFFFFFFUL)
#define PORT_PWR_PWR0    (0x00000003UL)
#define PORT_PWR_PWR1    (0x0000000CUL)
#define PORT_PWR_PWR2    (0x00000030UL)
#define PORT_PWR_PWR3    (0x000000C0UL)
#define PORT_PWR_PWR4    (0x00000300UL)
#define PORT_PWR_PWR5    (0x00000C00UL)
#define PORT_PWR_PWR6    (0x00003000UL)
#define PORT_PWR_PWR7    (0x0000C000UL)
#define PORT_PWR_PWR8    (0x00030000UL)
#define PORT_PWR_PWR9    (0x000C0000UL)
#define PORT_PWR_PWR10   (0x00300000UL)
#define PORT_PWR_PWR11   (0x00C00000UL)
#define PORT_PWR_PWR12   (0x03000000UL)
#define PORT_PWR_PWR13   (0x0C000000UL)
#define PORT_PWR_PWR14   (0x30000000UL)
#define PORT_PWR_PWR15   (0xC0000000UL)

/** @} */ /* End of group MDR32F21QI_PORT_PWR */

/** @defgroup MDR32F21QI_PORT_GFEN PORT_GFEN
 * @{
 */

#define PORT_GFEN_GFEN_Pos 0
#define PORT_GFEN_GFEN_Msk (0xFFFFUL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN0    (0x0001UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN1    (0x0002UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN2    (0x0004UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN3    (0x0008UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN4    (0x0010UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN5    (0x0020UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN6    (0x0040UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN7    (0x0080UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN8    (0x0100UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN9    (0x0200UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN10   (0x0400UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN11   (0x0800UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN12   (0x1000UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN13   (0x2000UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN14   (0x4000UL << PORT_GFEN_GFEN_Pos)
#define PORT_GFEN_GFEN15   (0x8000UL << PORT_GFEN_GFEN_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_GFEN */

/** @defgroup MDR32F21QI_PORT_SETTX PORT_SETTX
 * @{
 */

#define PORT_SETTX_SETTX_Pos 0
#define PORT_SETTX_SETTX_Msk (0xFFFFUL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX0    (0x0001UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX1    (0x0002UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX2    (0x0004UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX3    (0x0008UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX4    (0x0010UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX5    (0x0020UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX6    (0x0040UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX7    (0x0080UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX8    (0x0100UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX9    (0x0200UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX10   (0x0400UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX11   (0x0800UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX12   (0x1000UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX13   (0x2000UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX14   (0x4000UL << PORT_SETTX_SETTX_Pos)
#define PORT_SETTX_SETTX15   (0x8000UL << PORT_SETTX_SETTX_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_SETTX */

/** @defgroup MDR32F21QI_PORT_CLRTX PORT_CLRTX
 * @{
 */

#define PORT_CLRTX_CLRTX_Pos 0
#define PORT_CLRTX_CLRTX_Msk (0xFFFFUL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX0    (0x0001UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX1    (0x0002UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX2    (0x0004UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX3    (0x0008UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX4    (0x0010UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX5    (0x0020UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX6    (0x0040UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX7    (0x0080UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX8    (0x0100UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX9    (0x0200UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX10   (0x0400UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX11   (0x0800UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX12   (0x1000UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX13   (0x2000UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX14   (0x4000UL << PORT_CLRTX_CLRTX_Pos)
#define PORT_CLRTX_CLRTX15   (0x8000UL << PORT_CLRTX_CLRTX_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_CLRTX */

/** @defgroup MDR32F21QI_PORT_RDTX PORT_RDTX
 * @{
 */

#define PORT_RDTX_RDTX_Pos 0
#define PORT_RDTX_RDTX_Msk (0xFFFFUL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX0    (0x0001UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX1    (0x0002UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX2    (0x0004UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX3    (0x0008UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX4    (0x0010UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX5    (0x0020UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX6    (0x0040UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX7    (0x0080UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX8    (0x0100UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX9    (0x0200UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX10   (0x0400UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX11   (0x0800UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX12   (0x1000UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX13   (0x2000UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX14   (0x4000UL << PORT_RDTX_RDTX_Pos)
#define PORT_RDTX_RDTX15   (0x8000UL << PORT_RDTX_RDTX_Pos)

/** @} */ /* End of group MDR32F21QI_PORT_RDTX */

/** @} */ /* End of group MDR32F21QI_PORT_Defines */

/** @} */ /* End of group MDR32F21QI_PORT */

/** @defgroup MDR32F21QI_CRC MDR_CRC
 * @{
 */

/**
 * @brief MDR32F21QI CRC control structure
 */
typedef struct {
    __IO uint32_t CTRL;  /*!<CRC Control Register */
    __IO uint32_t STAT;  /*!<CRC Status Register */
    __IO uint32_t DATAI; /*!<CRC Input FIFO Data Register */
    __IO uint32_t VAL;   /*!<CRC Value Register */
    __IO uint32_t POL;   /*!<CRC Polynomial Register */
} MDR_CRC_TypeDef;

/** @defgroup MDR32F21QI_CRC_Defines CRC Defines
 * @{
 */

/** @defgroup MDR32F21QI_CRC_CTRL CRC_CTRL
 * @{
 */

#define CRC_CTRL_CRCEN_Pos    0
#define CRC_CTRL_CRCEN_Msk    (0x1UL << CRC_CTRL_CRCEN_Pos)
#define CRC_CTRL_CRCEN        CRC_CTRL_CRCEN_Msk

#define CRC_CTRL_DATAINV_Pos  1
#define CRC_CTRL_DATAINV_Msk  (0x1UL << CRC_CTRL_DATAINV_Pos)
#define CRC_CTRL_DATAINV      CRC_CTRL_DATAINV_Msk

#define CRC_CTRL_DMAEN_Pos    2
#define CRC_CTRL_DMAEN_Msk    (0x1UL << CRC_CTRL_DMAEN_Pos)
#define CRC_CTRL_DMAEN        CRC_CTRL_DMAEN_Msk

#define CRC_CTRL_DLSIZE_Pos   3
#define CRC_CTRL_DLSIZE_Msk   (0x3UL << CRC_CTRL_DLSIZE_Pos)
#define CRC_CTRL_DLSIZE_8BIT  (0x0UL << CRC_CTRL_DLSIZE_Pos)
#define CRC_CTRL_DLSIZE_16BIT (0x1UL << CRC_CTRL_DLSIZE_Pos)
#define CRC_CTRL_DLSIZE_32BIT (0x2UL << CRC_CTRL_DLSIZE_Pos)

#define CRC_CTRL_DCSIZE_Pos   5
#define CRC_CTRL_DCSIZE_Msk   (0x3UL << CRC_CTRL_DCSIZE_Pos)
#define CRC_CTRL_DCSIZE_8BIT  (0x0UL << CRC_CTRL_DCSIZE_Pos)
#define CRC_CTRL_DCSIZE_16BIT (0x1UL << CRC_CTRL_DCSIZE_Pos)
#define CRC_CTRL_DCSIZE_32BIT (0x2UL << CRC_CTRL_DCSIZE_Pos)

/** @} */ /* End of group MDR32F21QI_CRC_CTRL */

/** @defgroup MDR32F21QI_CRC_STAT CRC_STAT
 * @{
 */

/* Bit field positions: */
#define CRC_STAT_CONVCOMP_Pos  0
#define CRC_STAT_CONVCOMP_Msk  (0x1UL << CRC_STAT_CONVCOMP_Pos)
#define CRC_STAT_CONVCOMP      CRC_STAT_CONVCOMP_Msk

#define CRC_STAT_FIFOFULL_Pos  1
#define CRC_STAT_FIFOFULL_Msk  (0x1UL << CRC_STAT_FIFOFULL_Pos)
#define CRC_STAT_FIFOFULL      CRC_STAT_FIFOFULL_Msk

#define CRC_STAT_FIFOEMPTY_Pos 2
#define CRC_STAT_FIFOEMPTY_Msk (0x1UL << CRC_STAT_FIFOEMPTY_Pos)
#define CRC_STAT_FIFOEMPTY     CRC_STAT_FIFOEMPTY_Msk

#define CRC_STAT_FIFOOVER_Pos  3
#define CRC_STAT_FIFOOVER_Msk  (0x1UL << CRC_STAT_FIFOOVER_Pos)
#define CRC_STAT_FIFOOVER      CRC_STAT_FIFOOVER_Msk

/** @} */ /* End of group MDR32F21QI_CRC_STAT */

/** @defgroup MDR32F21QI_CRC_DATAI CRC_DATAI
 * @{
 */

#define CRC_DATAI_DATA_IN_Pos 0
#define CRC_DATAI_DATA_IN_Msk (0xFFFFFFFFUL << CRC_DATAI_DATA_IN_Pos)

/** @} */ /* End of group MDR32F21QI_CRC_DATAI */

/** @defgroup MDR32F21QI_CRC_VAL CRC_VAL
 * @{
 */

#define CRC_VAL_CRCOUT_Pos 0
#define CRC_VAL_CRCOUT_Msk (0xFFFFUL << CRC_VAL_CRCOUT_Pos)

/** @} */ /* End of group MDR32F21QI_CRC_VAL */

/** @defgroup MDR32F21QI_CRC_POL CRC_POL
 * @{
 */

#define CRC_POL_CRC_POL_Pos 0
#define CRC_POL_CRC_POL_Msk (0x1FFFFUL << CRC_POL_CRC_POL_Pos)

/** @} */ /* End of group MDR32F21QI_CRC_POL */

/** @} */ /* End of group MDR32F21QI_CRC_Defines */

/** @} */ /* End of group MDR32F21QI_CRC */

/** @} */ /* End of group MDR32F21QI_Peripheral_Units */

/** @defgroup MDR32F21QI_Peripheral_Memory_Map MDR32F21QI Peripheral Memory Map
 * @{
 */

#define MDR_SSP_BASE     (0x40000000)
#define MDR_UART0_BASE   (0x40008000)
#define MDR_UART1_BASE   (0x40010000)
#define MDR_EEPROM_BASE  (0x40018000)
#define MDR_RST_CLK_BASE (0x40020000)
#define MDR_DMA_BASE     (0x40028000)
#define MDR_ADC_BASE     (0x40040000)
#define MDR_WWDG_BASE    (0x40048000)
#define MDR_IWDG_BASE    (0x40050000)
#define MDR_POWER_BASE   (0x40058000)
#define MDR_BKP_BASE     (0x40060000)
#define MDR_ADCUI_BASE   (0x40068000)
#define MDR_TIMER0_BASE  (0x40070000)
#define MDR_TIMER1_BASE  (0x40078000)
#define MDR_PORTA_BASE   (0x40080000)
#define MDR_PORTB_BASE   (0x40088000)
#define MDR_PORTC_BASE   (0x40090000)
#define MDR_CRC_BASE     (0x40098000)

/** @} */ /* End of group MDR32F21QI_Peripheral_Memory_Map */

/** @defgroup MDR32F21QI_Peripheral_Declaration MDR32F21QI Peripheral Declaration
 * @{
 */

#define MDR_SSP     ((MDR_SSP_TypeDef*)MDR_SSP_BASE)
#define MDR_UART0   ((MDR_UART_TypeDef*)MDR_UART0_BASE)
#define MDR_UART1   ((MDR_UART_TypeDef*)MDR_UART1_BASE)
#define MDR_EEPROM  ((MDR_EEPROM_TypeDef*)MDR_EEPROM_BASE)
#define MDR_RST_CLK ((MDR_RST_CLK_TypeDef*)MDR_RST_CLK_BASE)
#define MDR_DMA     ((MDR_DMA_TypeDef*)MDR_DMA_BASE)
#define MDR_ADC     ((MDR_ADC_TypeDef*)MDR_ADC_BASE)
#define MDR_WWDG    ((MDR_WWDG_TypeDef*)MDR_WWDG_BASE)
#define MDR_IWDG    ((MDR_IWDG_TypeDef*)MDR_IWDG_BASE)
#define MDR_POWER   ((MDR_POWER_TypeDef*)MDR_POWER_BASE)
#define MDR_BKP     ((MDR_BKP_TypeDef*)MDR_BKP_BASE)
#define MDR_ADCUI   ((MDR_ADCUI_TypeDef*)MDR_ADCUI_BASE)
#define MDR_TIMER0  ((MDR_TIMER_TypeDef*)MDR_TIMER0_BASE)
#define MDR_TIMER1  ((MDR_TIMER_TypeDef*)MDR_TIMER1_BASE)
#define MDR_PORTA   ((MDR_PORT_TypeDef*)MDR_PORTA_BASE)
#define MDR_PORTB   ((MDR_PORT_TypeDef*)MDR_PORTB_BASE)
#define MDR_PORTC   ((MDR_PORT_TypeDef*)MDR_PORTC_BASE)
#define MDR_CRC     ((MDR_CRC_TypeDef*)MDR_CRC_BASE)

/** @} */ /* End of group MDR32F21QI_Peripheral_Declaration */

#ifdef __cplusplus
} // extern "C" block end
#endif

/** @} */ /* End of group MDR32F21QI_Peripheral */

/** @} */ /* End of group MDR32F21QI */

/** @} */ /* End of group CMSIS */

#endif    /* __MDR32F21QI_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F21QI.h */

