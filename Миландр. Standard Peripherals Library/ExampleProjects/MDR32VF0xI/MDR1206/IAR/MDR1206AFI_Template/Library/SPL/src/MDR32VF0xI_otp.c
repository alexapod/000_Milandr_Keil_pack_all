/**
 *******************************************************************************
 * @file    MDR32VF0xI_otp.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   This file contains all the OTP firmware functions.
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
#include "MDR32VF0xI_otp.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

#if defined(USE_MDR32F02)

/** @addtogroup OTP OTP
 *  @warning This module can be used only for microcontrollers MDR32F02.
 * @{
 */

/** @defgroup OTP_Private_Defines OTP Private Defines
 * @{
 */

/* Minimum frequency for proper delays for register access.
   Specified by DELAY_01US range [1 us; 2 us]. 500 kHz corresponds to 2 us. */
#define OTP_REG_DELAY_MIN_FREQ 500000

#define OTP_DELAY_0_REG_DELAYS (OTP_DELAY_0_DELAY_20NS_Msk | \
                                OTP_DELAY_0_DELAY_50NS_Msk | \
                                OTP_DELAY_0_DELAY_1US_Msk)

#define OTP_MODULE_FLAG_MASK (uint32_t)(OTP_MODULE_FLAG_BUSY |                  \
                                        OTP_MODULE_FLAG_LOCK |                  \
                                        OTP_MODULE_FLAG_PARTIAL_LOCK |          \
                                        OTP_MODULE_FLAG_RW_ERROR |              \
                                        OTP_MODULE_FLAG_TEST_OPT_REG_CRC |      \
                                        OTP_MODULE_FLAG_WRITE_PROTECT_REG_CRC | \
                                        OTP_MODULE_FLAG_READ_PROTECT_REG_CRC)

#define OTP_BLOCK_FLAG_MASK         (OTP_STAT_OTP_BUSY | OTP_STAT_OTP_LOCK)

#define IS_OTP_VALID_BIT_ADDR(ADDR) ((((ADDR) & ~0x1FFFFU) == OTP_BOOT_BASE * 8) || \
                                     (((ADDR) & ~0x1FFFFU) == OTP_BASE * 8) ||      \
                                     (((ADDR) & ~0x1FFFFU) == 0))

#define IS_OTP_VALID_BYTE_ADDR(ADDR) ((((ADDR) & ~0x3FFFU) == OTP_BOOT_BASE) || \
                                      (((ADDR) & ~0x3FFFU) == OTP_BASE) ||      \
                                      (((ADDR) & ~0x3FFFU) == 0))

#define IS_OTP_HALFWORD_BYTE_ADDR_IN_MEM_BOUNDS(ADDR) (((ADDR) & 0x3FFFU) <= OTP_BOOT_SIZE - 2)
#define IS_OTP_WORD_BYTE_ADDR_IN_MEM_BOUNDS(ADDR)     (((ADDR) & 0x3FFFU) <= OTP_BOOT_SIZE - 4)

#if defined(USE_FACTORY_DATA_PROTECTION)
#define IS_OTP_BIT_ADDR_OUTSIDE_FACTORY_DATA(ADDR) ((ADDR) < OTP_BYTE_ADDR_TO_BIT(0x3FE0))
#endif

/** @} */ /* End of the group OTP_Private_Defines */

/** @addtogroup OTP_Exported_Functions OTP Exported Functions
 * @{
 */

/**
 * @brief  Set delay for AHB access to OTP memory.
 * @note   The number of delay cycles should be set before
 *         the clock frequency increases or after the clock frequency decreases.
 * @param  ClockFrequencyHz: Core frequency in Hz.
 * @return None.
 */
void OTP_SetAHBDelay(OTP_AHBDelayCycle_TypeDef AHBDelayCycle)
{
    /* Check the parameters. */
    assert_param(IS_OTP_AHB_DELAY_CYCLE(AHBDelayCycle));

    MDR_OTP->DELAY_0 = (MDR_OTP->DELAY_0 & OTP_DELAY_0_REG_DELAYS) | (uint32_t)AHBDelayCycle;
}

/**
 * @brief  Configure the OTP module delays for register access to OTP according
 *         to the specified parameters in the OTP_RegDelays_InitStruct.
 * @param  OTP_RegDelays_InitStruct: The pointer to the @ref OTP_RegDelays_InitTypeDef
 *         structure that contains the configuration information for OTP delays.
 * @return None.
 */
void OTP_RegAccessDelaysConfig(const OTP_RegDelays_InitTypeDef* OTP_RegDelays_InitStruct)
{
    uint32_t DelayReg;

    /* Check the parameters. */
    assert_param(IS_OTP_REG_DELAY_20NS(OTP_RegDelays_InitStruct->OTP_RegDelay20ns));
    assert_param(IS_OTP_REG_DELAY_50NS(OTP_RegDelays_InitStruct->OTP_RegDelay50ns));
    assert_param(IS_OTP_REG_DELAY_1US(OTP_RegDelays_InitStruct->OTP_RegDelay1us));
    assert_param(IS_OTP_REG_DELAY_16US(OTP_RegDelays_InitStruct->OTP_RegDelay16us));

    DelayReg = ((uint32_t)(OTP_RegDelays_InitStruct->OTP_RegDelay20ns) << OTP_DELAY_0_DELAY_20NS_Pos);

    DelayReg |= ((uint32_t)(OTP_RegDelays_InitStruct->OTP_RegDelay50ns) << OTP_DELAY_0_DELAY_50NS_Pos);

    DelayReg |= ((uint32_t)(OTP_RegDelays_InitStruct->OTP_RegDelay1us) << OTP_DELAY_0_DELAY_1US_Pos);

    MDR_OTP->DELAY_0 = (MDR_OTP->DELAY_0 & OTP_DELAY_0_DELAY_70NS_Msk) | DelayReg;

    MDR_OTP->DELAY_1 = OTP_RegDelays_InitStruct->OTP_RegDelay16us;
}

/**
 * @brief  Fill each OTP_RegDelays_InitStruct member with its default value.
 * @param  OTP_RegDelays_InitStruct: The pointer to the @ref OTP_RegDelays_InitTypeDef structure
 *         which is to be initialized.
 * @return None.
 */
void OTP_RegAccessDelaysStructInit(OTP_RegDelays_InitTypeDef* OTP_RegDelays_InitStruct)
{
    OTP_RegDelays_InitStruct->OTP_RegDelay20ns = 0;
    OTP_RegDelays_InitStruct->OTP_RegDelay50ns = 0;
    OTP_RegDelays_InitStruct->OTP_RegDelay1us  = 1;
    OTP_RegDelays_InitStruct->OTP_RegDelay16us = 127;
}

/**
 * @brief  Configure the OTP module delays for register access to OTP
 *         in OTP_RegDelays_InitStruct structure.
 * @note   Delays are configured approximately and may falsely fail.
 * @param  OTP_RegDelays_InitStruct: The pointer to the @ref OTP_RegDelays_InitTypeDef
 *         structure that contains the configuration information for OTP delays.
 * @param  ClockFrequencyHz: Target OTP module (= CPU clock) frequency in Hz.
 * @return @ref ErrorStatus - validity of delays for a given frequency.
 *         Depends on 1 us ([1 us; 2 us]) delay and 16 us ([16 us; 17 us]) delay.
 */
ErrorStatus OTP_RegAccessDelaysStructConfig(OTP_RegDelays_InitTypeDef* OTP_RegDelays_InitStruct, uint32_t ClockFrequencyHz)
{
    uint32_t    Delay20ns, Delay50ns, Delay1us, Delay16us;
    float       ClockPeriodNs, Delay1usTime, Delay16usTime;
    ErrorStatus Delay1usValidity  = ERROR;
    ErrorStatus Delay16usValidity = ERROR;

    /* Check the parameters. */
    assert_param(ClockFrequencyHz >= OTP_REG_DELAY_MIN_FREQ);
    assert_param(ClockFrequencyHz <= 60000000);

    /* Clock frequency should be higher than minimum for DELAY_01US and lower than maximum CPU frequency. */
    if ((ClockFrequencyHz >= OTP_REG_DELAY_MIN_FREQ) && (ClockFrequencyHz <= 60000000)) {

        ClockPeriodNs = (float)1000000000 / (float)ClockFrequencyHz;

        /* Use midpoint (1.5 us) of delay time interval to calculate delay. */
        Delay1us     = (uint32_t)(1500 / ClockPeriodNs); // Middle point.
        Delay1usTime = (float)(Delay1us + 1) * ClockPeriodNs;

        if (Delay1usTime < 1000.0) {
            /* Result is lower than left border, try to increase delay value. */
            Delay1us += 1;
            Delay1usTime = (float)(Delay1us + 1) * ClockPeriodNs;

            /* Check if changes were successful. */
            if ((Delay1usTime >= 1000.0) && (Delay1usTime <= 2000.0)) {
                Delay1usValidity = SUCCESS;
            }
        } else if (Delay1usTime > 2000.0) {
            /* Result is higher than right border, try to decrease delay value. */

            /* Check if could decrease value. */
            if (Delay1us != 0) {
                Delay1us -= 1;
                Delay1usTime = (float)(Delay1us + 1) * ClockPeriodNs;
                /* Check if changes were successful. */
                if ((Delay1usTime >= 1000.0) && (Delay1usTime <= 2000.0)) {
                    Delay1usValidity = SUCCESS;
                }
            }
        } else {
            Delay1usValidity = SUCCESS;
        }

        /* No need to calculate 16 us delay if 1 us delay calculations failed. */
        if (Delay1usValidity == SUCCESS) {

            /* Use midpoint (16.5 us) of delay time interval to calculate delay. */
            Delay16us     = (uint32_t)(16500 / ClockPeriodNs);
            Delay16usTime = (float)(Delay16us + 1) * ClockPeriodNs;

            if (Delay16usTime < 16000.0) {
                /* Result is lower than left border, try to increase delay value. */
                Delay16us += 1;
                Delay16usTime = (float)(Delay16us + 1) * ClockPeriodNs;

                /* Check if changes were successful. */
                if ((Delay16usTime >= 16000.0) && (Delay16usTime <= 17000.0)) {
                    Delay16usValidity = SUCCESS;
                }
            } else if (Delay16usTime > 17000.0) {
                /* Result is higher than right border, try to decrease delay value. */
                /* Check if could decrease value. */
                if (Delay16us != 0) {

                    Delay16us -= 1;
                    Delay16usTime = (float)(Delay16us + 1) * ClockPeriodNs;
                    /* Check if changes were successful. */
                    if ((Delay16usTime >= 16000.0) && (Delay16usTime <= 17000.0)) {
                        Delay16usValidity = SUCCESS;
                    }
                }
            } else {
                Delay16usValidity = SUCCESS;
            }
        }

        if ((Delay1usValidity == SUCCESS) && (Delay16usValidity == SUCCESS)) {
            /* Calculate 20 ns delay: >= 20 ns. */
            Delay20ns = (20U * ClockFrequencyHz / 1000000000U);
            /* Calculate 50 ns delay: >= 50 ns. */
            Delay50ns = (50U * ClockFrequencyHz / 1000000000U);

            OTP_RegDelays_InitStruct->OTP_RegDelay20ns = (uint8_t)Delay20ns;
            OTP_RegDelays_InitStruct->OTP_RegDelay50ns = (uint8_t)Delay50ns;
            OTP_RegDelays_InitStruct->OTP_RegDelay1us  = (uint16_t)Delay1us;
            OTP_RegDelays_InitStruct->OTP_RegDelay16us = Delay16us;
        }
    }

    return (ErrorStatus)(Delay1usValidity & Delay16usValidity);
}

/**
 * @brief  Read an 8-bit OTP memory value.
 * @param  ByteAddress: Byte address.
 * @return OTP memory byte.
 */
uint8_t OTP_ReadByte(uint32_t ByteAddress)
{
    uint32_t BitAddress;

    /* Check the parameters. */
    assert_param(IS_OTP_VALID_BYTE_ADDR(ByteAddress));

    BitAddress = OTP_BYTE_ADDR_TO_BIT(ByteAddress);

    /* Wait while busy. */
    while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSY) != 0) { }

    MDR_OTP->RW_CMD = (BitAddress << OTP_RW_CMD_ADDR_Pos) | OTP_RW_CMD_READ;

    /* Wait while busy. */
    while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSY) != 0) { }

    return (uint8_t)MDR_OTP->READ_DATA;
}

/**
 * @brief  Read a 16-bit OTP memory value.
 * @note   Hardware supports only 8-bit word reading.
 * @param  ByteAddress: Byte address.
 * @return OTP memory halfword.
 */
uint16_t OTP_ReadHalfWord(uint32_t ByteAddress)
{
    uint16_t Data;

    /* Check the parameters. */
    assert_param(IS_OTP_VALID_BYTE_ADDR(ByteAddress));
    assert_param(IS_OTP_HALFWORD_BYTE_ADDR_IN_MEM_BOUNDS(ByteAddress));

    Data = (uint16_t)(OTP_ReadByte(ByteAddress) | (OTP_ReadByte(ByteAddress + 1) << 8));

    return Data;
}

/**
 * @brief  Read a 32-bit OTP memory value.
 * @note   Hardware supports only 8-bit word reading.
 * @param  ByteAddress: Byte address.
 * @return OTP memory word.
 */
uint32_t OTP_ReadWord(uint32_t ByteAddress)
{
    uint32_t Data;

    /* Check the parameters. */
    assert_param(IS_OTP_VALID_BYTE_ADDR(ByteAddress));
    assert_param(IS_OTP_WORD_BYTE_ADDR_IN_MEM_BOUNDS(ByteAddress));

    Data = (uint32_t)(OTP_ReadByte(ByteAddress) | (OTP_ReadByte(ByteAddress + 1) << 8) |
                      (OTP_ReadByte(ByteAddress + 2) << 16) | (OTP_ReadByte(ByteAddress + 3) << 24));

    return Data;
}

/**
 * @brief  Program a single OTP bit.
 * @param  BitAddress: Bit address.
 * @param  DataBit: Data bit.
 *         This parameter must be 0 or 1.
 * @return None.
 */
void OTP_ProgramBit(uint32_t BitAddress, uint8_t DataBit)
{
    /* Check the parameters. */
    assert_param(IS_OTP_VALID_BIT_ADDR(BitAddress));

#if defined(USE_FACTORY_DATA_PROTECTION)
    if (IS_OTP_BIT_ADDR_OUTSIDE_FACTORY_DATA(BitAddress) && ((DataBit & 0x1) != 0)) {
#else
    if ((DataBit & 0x1) != 0) {
#endif
        /* Wait while busy. */
        while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSY) != 0) { }

        MDR_OTP->RW_CMD = (BitAddress << OTP_RW_CMD_ADDR_Pos) | OTP_RW_CMD_DATA | OTP_RW_CMD_WRITE;

        /* Wait while busy. */
        while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSY) != 0) { }
    }
}

/**
 * @brief  Program an 8-bit OTP value.
 * @note   Hardware supports only single bit programming.
 * @param  ByteAddress: Byte address.
 * @param  DataByte: 8-bit data to write.
 * @return None.
 */
void OTP_ProgramByte(uint32_t ByteAddress, uint8_t DataByte)
{
    uint32_t Tmp;

    /* Check the parameters. */
    assert_param(IS_OTP_VALID_BYTE_ADDR(ByteAddress));

    for (Tmp = 0; Tmp < 8; Tmp++) {
#if defined(USE_FACTORY_DATA_PROTECTION)
        if (!IS_OTP_BIT_ADDR_OUTSIDE_FACTORY_DATA(OTP_BYTE_ADDR_TO_BIT(ByteAddress) + Tmp)) {
            /* As byte program performed per-bit incrementally and factory data is at the end of OTP, skip all remaining iteration. */
            return;
        }
#endif
        OTP_ProgramBit((OTP_BYTE_ADDR_TO_BIT(ByteAddress) + Tmp), (DataByte >> Tmp));
    }
}

/**
 * @brief  Program a 16-bit OTP value.
 * @note   Hardware supports only single bit programming.
 * @param  ByteAddress: Byte address.
 * @param  DataHalfWord: 16-bit data to write.
 * @return None.
 */
void OTP_ProgramHalfWord(uint32_t ByteAddress, uint16_t DataHalfWord)
{
    uint32_t Tmp;

    /* Check the parameters. */
    assert_param(IS_OTP_VALID_BYTE_ADDR(ByteAddress));
    assert_param(IS_OTP_HALFWORD_BYTE_ADDR_IN_MEM_BOUNDS(ByteAddress));

    for (Tmp = 0; Tmp < 16; Tmp++) {
#if defined(USE_FACTORY_DATA_PROTECTION)
        if (!IS_OTP_BIT_ADDR_OUTSIDE_FACTORY_DATA(OTP_BYTE_ADDR_TO_BIT(ByteAddress) + Tmp)) {
            /* As halfword program performed per-bit incrementally and factory data is at the end of OTP, skip all remaining iteration. */
            return;
        }
#endif
        OTP_ProgramBit((OTP_BYTE_ADDR_TO_BIT(ByteAddress) + Tmp), (uint8_t)(DataHalfWord >> Tmp));
    }
}

/**
 * @brief  Program a 32-bit OTP value.
 * @note   Hardware supports only single bit programming.
 * @param  ByteAddress: Byte address.
 * @param  DataWord: 32-bit data to write.
 * @return None.
 */
void OTP_ProgramWord(uint32_t ByteAddress, uint32_t DataWord)
{
    uint32_t Tmp;

    /* Check the parameters. */
    assert_param(IS_OTP_VALID_BYTE_ADDR(ByteAddress));
    assert_param(IS_OTP_WORD_BYTE_ADDR_IN_MEM_BOUNDS(ByteAddress));

    for (Tmp = 0; Tmp < 32; Tmp++) {
#if defined(USE_FACTORY_DATA_PROTECTION)
        if (!IS_OTP_BIT_ADDR_OUTSIDE_FACTORY_DATA(OTP_BYTE_ADDR_TO_BIT(ByteAddress) + Tmp)) {
            /* As word program performed per-bit incrementally and factory data is at the end of OTP, skip all remaining iteration. */
            return;
        }
#endif
        OTP_ProgramBit((OTP_BYTE_ADDR_TO_BIT(ByteAddress) + Tmp), (uint8_t)(DataWord >> Tmp));
    }
}

/**
 * @brief  Set read protection for regions.
 * @note   Could be set only ones, reset by a system reset.
 * @param  ReadProtection: Read protection for regions.
 *         This parameter must be any combination of @ref OTP_ProtectionRegions_TypeDef values.
 * @return None.
 */
void OTP_SetReadProtection(uint32_t ReadProtection)
{
    /* Check the parameters. */
    assert_param(IS_OTP_PROT_REGIONS(ReadProtection));

    MDR_OTP->READ_PROTECT = ReadProtection;
}

/**
 * @brief  Get read protection state of the regions.
 * @param  None.
 * @return A combined value of the individual read protection states (@ref OTP_ProtectionRegions_TypeDef).
 */
uint32_t OTP_GetReadProtection(void)
{
    return MDR_OTP->READ_PROTECT;
}

/**
 * @brief  Set write protection for regions.
 * @note   Could be set only ones, reset only by the power-on reset.
 * @param  WriteProtection: Write protection for regions.
 *         This parameter must be any combination of @ref OTP_ProtectionRegions_TypeDef values.
 * @return None.
 */
void OTP_SetWriteProtection(uint32_t WriteProtection)
{
    /* Check the parameters. */
    assert_param(IS_OTP_PROT_REGIONS(WriteProtection));

    MDR_OTP->WRITE_PROTECT = WriteProtection;
}

/**
 * @brief  Get regions write protection state.
 * @param  None.
 * @return A combined value of the individual write protection states (@ref OTP_ProtectionRegions_TypeDef).
 */
uint32_t OTP_GetWriteProtection(void)
{
    return MDR_OTP->WRITE_PROTECT;
}

/**
 * @brief  Check whether a specified OTP MODULE status flag is set or not.
 * @param  Flag: @ref OTP_MODULE_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - the current state of a status flag (SET or RESET).
 *         For @ref OTP_MODULE_FLAG_TEST_OPT_REG_CRC, @ref OTP_MODULE_FLAG_WRITE_PROTECT_REG_CRC and
 *         @ref OTP_MODULE_FLAG_READ_PROTECT_REG_CRC SET is normal state (CRC is valid).
 */
FlagStatus OTP_MODULE_GetFlagStatus(OTP_MODULE_Flags_TypeDef Flag)
{
    /* Check the parameters. */
    assert_param(IS_OTP_MODULE_FLAG(Flag));

    if (MDR_OTP->STAT_CTRL & (uint32_t)Flag) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Return a combined value of the OTP MODULE status flags.
 * @note   For @ref OTP_MODULE_FLAG_TEST_OPT_REG_CRC, @ref OTP_MODULE_FLAG_WRITE_PROTECT_REG_CRC and
 *         @ref OTP_MODULE_FLAG_READ_PROTECT_REG_CRC "1" is normal state (CRC is valid).
 * @param  None.
 * @return A combined value of the individual OTP MODULE status flags (@ref OTP_MODULE_Flags_TypeDef).
 */
uint32_t OTP_MODULE_GetStatus(void)
{
    return MDR_OTP->STAT_CTRL & OTP_MODULE_FLAG_MASK;
}

/**
 * @brief  Check whether a specified OTP BLOCK status flag is set or not.
 * @param  Flag: @ref OTP_BLOCK_Flags_TypeDef - specify a flag to check.
 * @return @ref FlagStatus - the current state of a status flag (SET or RESET).
 */
FlagStatus OTP_BLOCK_GetFlagStatus(OTP_BLOCK_Flags_TypeDef Flag)
{
    /* Check the parameters. */
    assert_param(IS_OTP_BLOCK_FLAG(Flag));

    if (MDR_OTP->STAT & (uint32_t)Flag) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Return a combined value of the OTP BLOCK status flags.
 * @param  None.
 * @return A combined value of the individual OTP BLOCK status flags (@ref OTP_BLOCK_Flags_TypeDef).
 */
uint32_t OTP_BLOCK_GetStatus(void)
{
    return MDR_OTP->STAT & OTP_BLOCK_FLAG_MASK;
}

/**
 * @brief  Return an OTP MODULE FSM state.
 * @param  None.
 * @return @ref OTP_MODULE_FSMState_TypeDef - OTP MODULE FSM state.
 */
OTP_MODULE_FSMState_TypeDef OTP_MODULE_GetFSMState(void)
{
    return (OTP_MODULE_FSMState_TypeDef)(MDR_OTP->STAT_CTRL & OTP_STAT_CTRL_FSM_STATE_Msk);
}

/**
 * @brief  Return an OTP BLOCK FSM state.
 * @param  None.
 * @return @ref OTP_BLOCK_FSMState_TypeDef - OTP BLOCK FSM state.
 */
OTP_BLOCK_FSMState_TypeDef OTP_BLOCK_GetFSMState(void)
{
    return (OTP_BLOCK_FSMState_TypeDef)(MDR_OTP->STAT & OTP_STAT_OTP_FSM_STATE_Msk);
}

/**
 * @brief  Return an OTP debug protection. Blocks debug if any bit is not 1.
 *         This field is updated from last OTP byte (inversion of this value).
 * @param  None.
 * @return OTP debug protection.
 */
uint8_t OTP_GetDebugProtection(void)
{
    return (uint8_t)(MDR_OTP->TEST_OPT);
}

/** @} */ /* End of the group OTP_Exported_Functions */

/** @} */ /* End of the group OTP */

#endif /* #if defined(USE_MDR32F02) */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_otp.c */

