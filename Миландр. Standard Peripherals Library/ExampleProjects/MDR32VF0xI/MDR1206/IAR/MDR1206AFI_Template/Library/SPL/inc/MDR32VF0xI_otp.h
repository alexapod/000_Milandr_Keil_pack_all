/**
 *******************************************************************************
 * @file    MDR32VF0xI_otp.h
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    16/04/2024
 * @brief   This file contains all the functions prototypes for the OTP
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
#ifndef MDR32VF0xI_OTP_H
#define MDR32VF0xI_OTP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup OTP OTP
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup OTP_Exported_Types OTP Exported Types
 * @{
 */

/**
 * @brief OTP AHB access delay (DELAY_70NS).
 */
typedef enum {
    OTP_AHB_DELAY_CYCLE_1  = (((uint32_t)0x0) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 14 MHz). */
    OTP_AHB_DELAY_CYCLE_2  = (((uint32_t)0x1) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 28 MHz). */
    OTP_AHB_DELAY_CYCLE_3  = (((uint32_t)0x2) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 42 MHz). */
    OTP_AHB_DELAY_CYCLE_4  = (((uint32_t)0x3) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 57 MHz). */
    OTP_AHB_DELAY_CYCLE_5  = (((uint32_t)0x4) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 71 MHz). */
    OTP_AHB_DELAY_CYCLE_6  = (((uint32_t)0x5) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 85 MHz). */
    OTP_AHB_DELAY_CYCLE_7  = (((uint32_t)0x6) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 100 MHz). */
    OTP_AHB_DELAY_CYCLE_8  = (((uint32_t)0x7) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 114 MHz). */
    OTP_AHB_DELAY_CYCLE_9  = (((uint32_t)0x8) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 128 MHz). */
    OTP_AHB_DELAY_CYCLE_10 = (((uint32_t)0x9) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 142 MHz). */
    OTP_AHB_DELAY_CYCLE_11 = (((uint32_t)0xA) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 157 MHz). */
    OTP_AHB_DELAY_CYCLE_12 = (((uint32_t)0xB) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 171 MHz). */
    OTP_AHB_DELAY_CYCLE_13 = (((uint32_t)0xC) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 185 MHz). */
    OTP_AHB_DELAY_CYCLE_14 = (((uint32_t)0xD) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 200 MHz). */
    OTP_AHB_DELAY_CYCLE_15 = (((uint32_t)0xE) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 214 MHz). */
    OTP_AHB_DELAY_CYCLE_16 = (((uint32_t)0xF) << OTP_DELAY_0_DELAY_70NS_Pos), /*!< Select 0 OTP delay cycle for AHB read (MCU clock up to 228 MHz). */
} OTP_AHBDelayCycle_TypeDef;

#define IS_OTP_AHB_DELAY_CYCLE(CYCLE) (((CYCLE) == OTP_AHB_DELAY_CYCLE_1) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_2) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_3) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_4) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_5) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_6) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_7) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_8) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_9) ||  \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_10) || \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_11) || \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_12) || \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_13) || \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_14) || \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_15) || \
                                       ((CYCLE) == OTP_AHB_DELAY_CYCLE_16))

/**
 * @brief OTP MODULE FSM state.
 */
typedef enum {
    OTP_MODULE_FSM_STATE_IDLE               = OTP_STAT_CTRL_FSM_STATE_IDLE,          /*!< Idle. */
    OTP_MODULE_FSM_STATE_INIT               = OTP_STAT_CTRL_FSM_STATE_INIT,          /*!< Initialization. */
    OTP_MODULE_FSM_STATE_READY              = OTP_STAT_CTRL_FSM_STATE_READY,         /*!< Ready for operation. */
    OTP_MODULE_FSM_STATE_WAIT_READ_REG_DONE = OTP_STAT_CTRL_FSM_STATE_WAIT_REG_READ, /*!< Wait until read via registers is completed.  */
    OTP_MODULE_FSM_STATE_WAIT_READ_BUS_DONE = OTP_STAT_CTRL_FSM_STATE_WAIT_BUS_READ, /*!< Wait until read via the bus  is completed. */
    OTP_MODULE_FSM_STATE_WAIT_WRITE_DONE    = OTP_STAT_CTRL_FSM_STATE_WAIT_WRITE,    /*!< Wait until write is completed. */
    OTP_MODULE_FSM_STATE_DIR_CONTROL        = OTP_STAT_CTRL_FSM_STATE_DIRECT         /*!< OTP direct control mode. */
} OTP_MODULE_FSMState_TypeDef;

/**
 * @brief OTP BLOCK FSM state.
 */
typedef enum {
    OTP_BLOCK_FSM_STATE_IDLE                   = (((uint32_t)0x00) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Idle. */
    OTP_BLOCK_FSM_STATE_WAIT_OFF               = (((uint32_t)0x01) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Enter power saving mode. */
    OTP_BLOCK_FSM_STATE_RESET_PREPARE          = (((uint32_t)0x02) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Prepare for reset. */
    OTP_BLOCK_FSM_STATE_RESET                  = (((uint32_t)0x03) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Reset. */
    OTP_BLOCK_FSM_STATE_RESET_END              = (((uint32_t)0x04) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< End of reset. */
    OTP_BLOCK_FSM_STATE_ACTIVE                 = (((uint32_t)0x05) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Active state. */
    OTP_BLOCK_FSM_STATE_PAUSE_READ_AFTER_WRITE = (((uint32_t)0x06) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Pause read mode after writing. */
    OTP_BLOCK_FSM_STATE_READ_PREPARE           = (((uint32_t)0x07) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Prepare for reading. */
    OTP_BLOCK_FSM_STATE_READ                   = (((uint32_t)0x08) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Read state. */
    OTP_BLOCK_FSM_STATE_READ_END               = (((uint32_t)0x09) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< End of reading. */
    OTP_BLOCK_FSM_STATE_WRITE_PREPARE          = (((uint32_t)0x0A) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Prepare for writing. */
    OTP_BLOCK_FSM_STATE_WRITE_HOLD_DATA        = (((uint32_t)0x0B) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Hold the data for writing. */
    OTP_BLOCK_FSM_STATE_WRITE_HOLD_DATA_END    = (((uint32_t)0x0C) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< End of holding the data. */
    OTP_BLOCK_FSM_STATE_PROGRAM_PREPARE        = (((uint32_t)0x0D) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Prepare for programming. */
    OTP_BLOCK_FSM_STATE_PROGRAM_PUMP_PREPARE   = (((uint32_t)0x0E) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Charge pump circuit preparation. */
    OTP_BLOCK_FSM_STATE_PROGRAM                = (((uint32_t)0x0F) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Programming. */
    OTP_BLOCK_FSM_STATE_PROGRAM_PUMP_END       = (((uint32_t)0x10) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Disable charge pump. */
    OTP_BLOCK_FSM_STATE_PROGRAM_WAIT           = (((uint32_t)0x11) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Wait for end of programming. */
    OTP_BLOCK_FSM_STATE_WRITE_WAIT             = (((uint32_t)0x12) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Wait for end of writing. */
    OTP_BLOCK_FSM_STATE_DIR_CONTROL_PREPARE    = (((uint32_t)0x13) << OTP_STAT_OTP_FSM_STATE_Pos), /*!< Prepare for direct control. */
    OTP_BLOCK_FSM_STATE_DIR_CONTROL            = (((uint32_t)0x14) << OTP_STAT_OTP_FSM_STATE_Pos)  /*!< Direct control mode. */
} OTP_BLOCK_FSMState_TypeDef;

/**
 * @brief OTP MODULE flags.
 */
typedef enum {
    OTP_MODULE_FLAG_BUSY                  = OTP_STAT_CTRL_BUSY,       /*!< OTP module is busy. */
    OTP_MODULE_FLAG_LOCK                  = OTP_STAT_CTRL_OTP_LOCK,   /*!< OTP module write lock flag. */
    OTP_MODULE_FLAG_PARTIAL_LOCK          = OTP_STAT_CTRL_OTP_PLOCK,  /*!< OTP module partial write lock flag. */
    OTP_MODULE_FLAG_RW_ERROR              = OTP_STAT_CTRL_RW_ERROR,   /*!< OTP module read/write error. */
    OTP_MODULE_FLAG_TEST_OPT_REG_CRC      = OTP_STAT_CTRL_TEST_CRC,   /*!< OTP module TEST_OPT_REG CRC state. */
    OTP_MODULE_FLAG_WRITE_PROTECT_REG_CRC = OTP_STAT_CTRL_WRITE_PCRC, /*!< OTP module WRITE_PROTECT_REG CRC state. */
    OTP_MODULE_FLAG_READ_PROTECT_REG_CRC  = OTP_STAT_CTRL_READ_PCRC   /*!< OTP module READ_PROTECT_REG CRC state. */
} OTP_MODULE_Flags_TypeDef;

#define IS_OTP_MODULE_FLAG(FLAG) (((FLAG) == OTP_MODULE_FLAG_BUSY) ||                  \
                                  ((FLAG) == OTP_MODULE_FLAG_LOCK) ||                  \
                                  ((FLAG) == OTP_MODULE_FLAG_PARTIAL_LOCK) ||          \
                                  ((FLAG) == OTP_MODULE_FLAG_RW_ERROR) ||              \
                                  ((FLAG) == OTP_MODULE_FLAG_TEST_OPT_REG_CRC) ||      \
                                  ((FLAG) == OTP_MODULE_FLAG_WRITE_PROTECT_REG_CRC) || \
                                  ((FLAG) == OTP_MODULE_FLAG_READ_PROTECT_REG_CRC))

#define IS_OTP_MODULE_FLAGS(FLAGS) (((FLAGS) & ~(uint32_t)(OTP_MODULE_FLAG_BUSY |                  \
                                                           OTP_MODULE_FLAG_LOCK |                  \
                                                           OTP_MODULE_FLAG_PARTIAL_LOCK |          \
                                                           OTP_MODULE_FLAG_RW_ERROR |              \
                                                           OTP_MODULE_FLAG_TEST_OPT_REG_CRC |      \
                                                           OTP_MODULE_FLAG_WRITE_PROTECT_REG_CRC | \
                                                           OTP_MODULE_FLAG_READ_PROTECT_REG_CRC)) == 0)

/**
 * @brief OTP BLOCK flags.
 */
typedef enum {
    OTP_BLOCK_FLAG_BUSY = OTP_STAT_OTP_BUSY, /*!< OTP block is busy. */
    OTP_BLOCK_FLAG_LOCK = OTP_STAT_OTP_LOCK  /*!< OTP block write lock flag. */
} OTP_BLOCK_Flags_TypeDef;

#define IS_OTP_BLOCK_FLAG(FLAG)   (((FLAG) == OTP_BLOCK_FLAG_BUSY) || ((FLAG) == OTP_BLOCK_FLAG_LOCK))

#define IS_OTP_BLOCK_FLAGS(FLAGS) (((FLAGS) & ~(uint32_t)(OTP_BLOCK_FLAG_BUSY | OTP_BLOCK_FLAG_LOCK)) == 0)

/**
 * @brief OTP memory protection regions.
 */
typedef enum {
    OTP_PROTECT_REGION_BYTE_0_2047      = OTP_WRITE_PROTECT_0, /*!< OTP memory protection for region 0. */
    OTP_PROTECT_REGION_BYTE_2048_4095   = OTP_WRITE_PROTECT_1, /*!< OTP memory protection for region 1. */
    OTP_PROTECT_REGION_BYTE_4096_6143   = OTP_WRITE_PROTECT_2, /*!< OTP memory protection for region 2. */
    OTP_PROTECT_REGION_BYTE_6144_8191   = OTP_WRITE_PROTECT_3, /*!< OTP memory protection for region 3. */
    OTP_PROTECT_REGION_BYTE_8192_10239  = OTP_WRITE_PROTECT_4, /*!< OTP memory protection for region 4. */
    OTP_PROTECT_REGION_BYTE_10240_12287 = OTP_WRITE_PROTECT_5, /*!< OTP memory protection for region 5. */
    OTP_PROTECT_REGION_BYTE_12288_14335 = OTP_WRITE_PROTECT_6, /*!< OTP memory protection for region 6. */
    OTP_PROTECT_REGION_BYTE_14336_16383 = OTP_WRITE_PROTECT_7  /*!< OTP memory protection for region 7. */
} OTP_ProtectionRegions_TypeDef;

#define IS_OTP_PROT_REGIONS(PRGS) (((PRGS) & ~(uint32_t)(OTP_PROTECT_REGION_BYTE_0_2047 |      \
                                                         OTP_PROTECT_REGION_BYTE_2048_4095 |   \
                                                         OTP_PROTECT_REGION_BYTE_4096_6143 |   \
                                                         OTP_PROTECT_REGION_BYTE_6144_8191 |   \
                                                         OTP_PROTECT_REGION_BYTE_8192_10239 |  \
                                                         OTP_PROTECT_REGION_BYTE_10240_12287 | \
                                                         OTP_PROTECT_REGION_BYTE_12288_14335 | \
                                                         OTP_PROTECT_REGION_BYTE_14336_16383)) == 0)

/**
 * @brief  OTP register access delays init structure definition.
 */
typedef struct {
    uint8_t OTP_RegDelay20ns;  /*!< This member configures delay >= 20 ns for OTP memory register access.
                                    This parameter can be any number from 0 to 15. */
    uint8_t OTP_RegDelay50ns;  /*!< This member configures delay >= 50 ns for OTP memory register access.
                                    This parameter can be any number from 0 to 15. */
    uint16_t OTP_RegDelay1us;  /*!< This member configures delay [1 us; 2 us] for OTP memory register access.
                                   This parameter can be any number from 0 to 511. */
    uint32_t OTP_RegDelay16us; /*!< This member configures delay [16 us; 17 us] for OTP memory register access.
                                   This parameter can be any number from 0 to 131071. */
} OTP_RegDelays_InitTypeDef;

/** @} */ /* End of the group OTP_Exported_Types */

/** @addtogroup OTP_Exported_Defines OTP Exported Defines
 * @{
 */

#define OTP_BIT_ADDR_TO_BYTE(BIT)    (((BIT) & 0x1FFF8) >> 3)
#define OTP_BYTE_ADDR_TO_BIT(BYTE)   (((BYTE) & 0x3FFF) << 3)

#define IS_OTP_REG_DELAY_20NS(DELAY) (((DELAY) & (uint32_t)0xF) == 0)
#define IS_OTP_REG_DELAY_50NS(DELAY) (((DELAY) & (uint32_t)0xF) == 0)
#define IS_OTP_REG_DELAY_1US(DELAY)  (((DELAY) & (uint32_t)0x1F) == 0)
#define IS_OTP_REG_DELAY_16US(DELAY) (((DELAY) & (uint32_t)0x1FF) == 0)

/** @} */ /* End of the group OTP_Exported_Defines */

/** @addtogroup OTP_Exported_Functions OTP Exported Functions
 * @{
 */

void OTP_SetAHBDelay(OTP_AHBDelayCycle_TypeDef AHBDelayCycle);

void OTP_RegAccessDelaysConfig(const OTP_RegDelays_InitTypeDef* OTP_RegDelays_InitStruct);

void        OTP_RegAccessDelaysStructInit(OTP_RegDelays_InitTypeDef* OTP_RegDelays_InitStruct);
ErrorStatus OTP_RegAccessDelaysStructConfig(OTP_RegDelays_InitTypeDef* OTP_RegDelays_InitStruct, uint32_t ClockFrequencyHz);

uint8_t  OTP_ReadByte(uint32_t ByteAddress);
uint16_t OTP_ReadHalfWord(uint32_t ByteAddress);
uint32_t OTP_ReadWord(uint32_t ByteAddress);

void OTP_ProgramBit(uint32_t BitAddress, uint8_t DataBit);
void OTP_ProgramByte(uint32_t ByteAddress, uint8_t DataByte);
void OTP_ProgramHalfWord(uint32_t ByteAddress, uint16_t DataHalfWord);
void OTP_ProgramWord(uint32_t ByteAddress, uint32_t DataWord);

void     OTP_SetReadProtection(uint32_t ReadProtection);
uint32_t OTP_GetReadProtection(void);

void     OTP_SetWriteProtection(uint32_t WriteProtection);
uint32_t OTP_GetWriteProtection(void);

FlagStatus OTP_MODULE_GetFlagStatus(OTP_MODULE_Flags_TypeDef Flag);
uint32_t   OTP_MODULE_GetStatus(void);

FlagStatus OTP_BLOCK_GetFlagStatus(OTP_BLOCK_Flags_TypeDef Flag);
uint32_t   OTP_BLOCK_GetStatus(void);

OTP_MODULE_FSMState_TypeDef OTP_MODULE_GetFSMState(void);
OTP_BLOCK_FSMState_TypeDef  OTP_BLOCK_GetFSMState(void);

uint8_t OTP_GetDebugProtection(void);

/** @} */ /* End of the group OTP_Exported_Functions */

/** @} */ /* End of the group OTP */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_OTP_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_otp.h */

