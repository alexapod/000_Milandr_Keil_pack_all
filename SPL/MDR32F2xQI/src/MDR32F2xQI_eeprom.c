/**
 *******************************************************************************
 * @file    MDR32F2xQI_eeprom.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
 * @brief   This file contains all the EEPROM firmware functions.
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
#include "MDR32F2xQI_eeprom.h"
#include "MDR32F2xQI_utils.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup EEPROM EEPROM
 * @{
 */

/** @defgroup EEPROM_Private_Defines EEPROM Private Defines
 * @{
 */

#define EEPROM_REG_ACCESS_KEY              (0x8AAA5551UL)
#define EEPROM_START_ADDR                  (0x00000000UL)

#define IS_EEPROM_TWO_BYTE_ALLIGNED(ADDR)  ((ADDR & 1) == 0)
#define IS_EEPROM_FOUR_BYTE_ALLIGNED(ADDR) ((ADDR & 3) == 0)

/** @} */ /* End of group EEPROM_Private_Defines */

/** @addtogroup EEPROM_Exported_Functions EEPROM Exported Functions
 * @{
 */

/** @addtogroup EEPROM_Functions_allowed_to_be_located_in_Flash Functions allowed to be located in Flash
 * @{
 */

/**
 * @brief  Sets the EEPROM latency value.
 * @param  Latency - @ref EEPROM_Latency_TypeDef - specifies the EEPROM latency cycles value.
 * @retval None.
 */
void EEPROM_SetLatency(EEPROM_Latency_TypeDef Latency)
{
    /* Check the parameters */
    assert_param(IS_EEPROM_LATENCY(Latency));

    /* Set the new latency value */
    MDR_EEPROM->CMD = (uint32_t)Latency;
}

/**
 * @brief  Gets the EEPROM latency value.
 * @param  None.
 * @retval @ref EEPROM_Latency_TypeDef - EEPROM latency cycles value.
 */
EEPROM_Latency_TypeDef EEPROM_GetLatency(void)
{
    /* Get current latency value */
    return (EEPROM_Latency_TypeDef)((MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) >> EEPROM_CMD_DELAY_Pos);
}

/** @} */ /* End of group EEPROM_Functions_allowed_to_be_located_in_Flash */

/** @addtogroup EEPROM_Functions_not_allowed_to_be_located_in_Flash Functions not allowed to be located in Flash
 * @{
 */

/**
 * @brief  Reads the 32-bit EEPROM memory value.
 * @param  Address: The EEPROM memory word address (four byte aligned).
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Information Bank).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_INFO:      The EEPROM Information Bank.
 * @retval The selected EEPROM memory value.
 */
__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank)
{
    uint32_t Command;
    uint32_t Data;

    assert_param(IS_EEPROM_MEMORY_BANK(Bank));
    assert_param(IS_EEPROM_FOUR_BYTE_ALLIGNED(Address));

    MDR_EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
    Command         = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
    Command |= (Bank == EEPROM_BANK_INFO) ? EEPROM_CMD_IFREN : 0;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->ADR = Address;
    MDR_EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    Data = MDR_EEPROM->DO;
    Command &= EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->KEY = 0;

    return Data;
}

/**
 * @brief  Reads the 16-bit EEPROM memory value.
 * @note   Hardware supports only 32-bit word reading.
 * @param  Address: The EEPROM memory half word address (two byte aligned).
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Information Bank).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_INFO:      The EEPROM Information Bank.
 * @retval The selected EEPROM memory value.
 */
__RAMFUNC uint16_t EEPROM_ReadHalfWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank)
{
    uint32_t Data;
    uint32_t Command;
    uint32_t Shift;

    assert_param(IS_EEPROM_MEMORY_BANK(Bank));
    assert_param(IS_EEPROM_TWO_BYTE_ALLIGNED(Address));

    MDR_EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
    Command         = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
    Command |= (Bank == EEPROM_BANK_INFO) ? EEPROM_CMD_IFREN : 0;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->ADR = Address;
    MDR_EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    Data = MDR_EEPROM->DO;
    Command &= EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->KEY = 0;

    Shift = (Address & 2) * 8;
    Data >>= Shift;

    return (uint16_t)Data;
}

/**
 * @brief  Reads the 8-bit EEPROM memory value.
 * @note   Hardware supports only 32-bit word reading.
 * @param  Address: The EEPROM memory byte address.
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Information Bank).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_INFO:      The EEPROM Information Bank.
 * @retval The selected EEPROM memory value.
 */
__RAMFUNC uint8_t EEPROM_ReadByte(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank)
{
    uint32_t Data;
    uint32_t Command;
    uint32_t Shift;

    assert_param(IS_EEPROM_MEMORY_BANK(Bank));

    MDR_EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
    Command         = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
    Command |= (Bank == EEPROM_BANK_INFO) ? EEPROM_CMD_IFREN : 0;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->ADR = Address;
    MDR_EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    MDR_EEPROM->DO; /* Idle Reading for Delay */
    Data = MDR_EEPROM->DO;
    Command &= EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->KEY = 0;

    Shift = (Address & 3) * 8;
    Data >>= Shift;

    return (uint8_t)Data;
}

/**
 * @brief  Erases one page (512 byte) of the selected EEPROM memory bank.
 * @note   The EEPROM Information Bank is divided into blocks of 2K bytes,
 *         the starting address of the block is N*0x8000, where N is the block number.
 * @note   The core clock from SystemCoreClock is used to calculate the delay time.
 *         Before calling EEPROM_ErasePage(), you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  Address: Page Address in the EEPROM memory.
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Information Bank).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_INFO:      The EEPROM Information Bank.
 * @retval None.
 */
__RAMFUNC void EEPROM_ErasePage(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank)
{
    uint32_t Command, DelayConstUs;

    assert_param(IS_EEPROM_MEMORY_BANK(Bank));

    DelayConstUs = DELAY_PROGRAM_GET_CONST_US(SystemCoreClock);

    MDR_EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
    Command         = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
    Command |= (Bank == EEPROM_BANK_INFO) ? EEPROM_CMD_IFREN : 0;
    MDR_EEPROM->CMD = Command;

    MDR_EEPROM->ADR = Address; /* Page Address */
    MDR_EEPROM->DI  = 0;
    Command |= EEPROM_CMD_XE | EEPROM_CMD_ERASE;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(10, DelayConstUs)); /* Wait for 10 us */
    Command |= EEPROM_CMD_NVSTR;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(30000, DelayConstUs)); /* Wait for 30 ms */
    Command &= ~EEPROM_CMD_ERASE;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(5, DelayConstUs)); /* Wait for 5 us */
    Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(1, DelayConstUs)); /* Wait for 1 us */

    Command &= EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->KEY = 0;

    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(4000, DelayConstUs)); /* Wait for 4 ms */
}

/**
 * @brief  Erases one block of the selected EEPROM memory bank.
 * @note   Erasing Information Block automatically erases Main Block.
 * @note   The block size of EEPROM Main Bank is 32K bytes, the block size of EEPROM Information Bank is 2K bytes.
 *         The starting address of the EEPROM information bank block is N*0x8000, where N is the block number.
 * @note   The core clock from SystemCoreClock is used to calculate the delay time.
 *         Before calling EEPROM_EraseBlock(), you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  Address: Block Address in the EEPROM memory.
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Main and Information Banks).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_ALL:       The EEPROM Main and Information Banks.
 * @retval None.
 */
__RAMFUNC void EEPROM_EraseBlock(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank)
{
    uint32_t Command, DelayConstUs;

    assert_param(IS_EEPROM_ERASE_BANK(Bank));

    DelayConstUs = DELAY_PROGRAM_GET_CONST_US(SystemCoreClock);

    MDR_EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
    Command         = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
    Command |= (Bank == EEPROM_BANK_ALL) ? EEPROM_CMD_IFREN : 0;
    MDR_EEPROM->CMD = Command;

    MDR_EEPROM->ADR = Address; /* Block Address */
    MDR_EEPROM->DI  = 0;
    Command |= EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_ERASE;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(10, DelayConstUs)); /* Wait for 10 us */
    Command |= EEPROM_CMD_NVSTR;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(30000, DelayConstUs)); /* Wait for 30 ms */
    Command &= ~EEPROM_CMD_ERASE;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(100, DelayConstUs)); /* Wait for 100 us */
    Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_NVSTR);
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(1, DelayConstUs)); /* Wait for 1 us */

    Command &= EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->KEY = 0;

    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(4000, DelayConstUs)); /* Wait for 4 ms */
}

/**
 * @brief  Programs the 32-bit EEPROM memory value.
 * @note   The core clock from SystemCoreClock is used to calculate the delay time.
 *         Before calling EEPROM_ProgramWord(), you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  Address: The EEPROM memory word address (four byte aligned).
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Information Bank).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_INFO:      The EEPROM Information Bank.
 * @param  Data: The data value to be programmed.
 * @retval None.
 */
__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank, uint32_t Data)
{
    uint32_t Command, DelayConstUs;

    assert_param(IS_EEPROM_MEMORY_BANK(Bank));
    assert_param(IS_EEPROM_FOUR_BYTE_ALLIGNED(Address));

    DelayConstUs = DELAY_PROGRAM_GET_CONST_US(SystemCoreClock);

    MDR_EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
    Command         = MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk;
    Command |= EEPROM_CMD_CON;
    Command |= (Bank == EEPROM_BANK_INFO) ? EEPROM_CMD_IFREN : 0;
    MDR_EEPROM->CMD = Command;

    MDR_EEPROM->ADR = Address;
    MDR_EEPROM->DI  = Data;
    Command |= EEPROM_CMD_XE | EEPROM_CMD_PROG;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(5, DelayConstUs)); /* Wait for 5 us */
    Command |= EEPROM_CMD_NVSTR;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(10, DelayConstUs)); /* Wait for 10 us */
    Command |= EEPROM_CMD_YE;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(30, DelayConstUs)); /* Wait for 30 us */
    Command &= ~EEPROM_CMD_YE;
    MDR_EEPROM->CMD = Command;
    Command &= ~EEPROM_CMD_PROG;
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(5, DelayConstUs)); /* Wait for 5 us */
    Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
    MDR_EEPROM->CMD = Command;
    DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(1, DelayConstUs)); /* Wait for 1 us */

    MDR_EEPROM->CMD = Command & EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->KEY = 0;
}

/**
 * @brief  Programs the 16-bit EEPROM memory value.
 * @note   Hardware supports only 32-bit word programming.
 * @note   The core clock from SystemCoreClock is used to calculate the delay time.
 *         Before calling EEPROM_ProgramHalfWord(), you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  Address: The EEPROM memory half word address (two byte aligned).
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Information Bank).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_INFO:      The EEPROM Information Bank.
 * @param  Data: The data value to be programmed.
 * @retval None.
 */
__RAMFUNC void EEPROM_ProgramHalfWord(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank, uint16_t Data)
{
    uint32_t Mask;
    uint32_t Tmp;
    uint32_t Shift;
    uint32_t ProgData;

    assert_param(IS_EEPROM_MEMORY_BANK(Bank));
    assert_param(IS_EEPROM_TWO_BYTE_ALLIGNED(Address));

    Shift    = (Address & 2) * 8;
    ProgData = (uint32_t)Data << Shift;
    Mask     = 0xFFFFUL << Shift;

    Tmp      = EEPROM_ReadWord(Address, Bank);
    ProgData = (Tmp & ~Mask) | (ProgData & Mask);

    EEPROM_ProgramWord(Address, Bank, ProgData);
}

/**
 * @brief  Programs the 8-bit EEPROM memory value.
 * @note   Hardware supports only 32-bit word programming.
 * @note   The core clock from SystemCoreClock is used to calculate the delay time.
 *         Before calling EEPROM_ProgramByte(), you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  Address: The EEPROM memory byte address.
 * @param  Bank - @ref EEPROM_MemoryBank_TypeDef - Selects EEPROM Bank (Main Bank or Information Bank).
 *         This parameter can be one of the following values:
 *             @arg EEPROM_BANK_MAIN:      The EEPROM Main Bank.
 *             @arg EEPROM_BANK_INFO:      The EEPROM Information Bank.
 * @param  Data: The data value to be programmed.
 * @retval None.
 */
__RAMFUNC void EEPROM_ProgramByte(uint32_t Address, EEPROM_MemoryBank_TypeDef Bank, uint8_t Data)
{
    uint32_t Mask;
    uint32_t Tmp;
    uint32_t Shift;
    uint32_t ProgData;

    assert_param(IS_EEPROM_MEMORY_BANK(Bank));

    Shift    = (Address & 3) * 8;
    ProgData = (uint32_t)Data << Shift;
    Mask     = 0xFFUL << Shift;

    Tmp      = EEPROM_ReadWord(Address, Bank);
    ProgData = (Tmp & ~Mask) | (ProgData & Mask);

    EEPROM_ProgramWord(Address, Bank, ProgData);
}

/**
 * @brief   Updates data cache. Use after reprogramming data in EEPROM.
 * @param   None.
 * @retval  None.
 */
__RAMFUNC void EEPROM_UpdateDCache(void)
{
    volatile uint32_t  NumWord, Tmp;
    volatile uint32_t* PtrEEPROM = (uint32_t*)(EEPROM_START_ADDR);

    /* Reading EEPROM memory to update the data cache */
    for (NumWord = 2; NumWord > 0; NumWord--) {
        Tmp = PtrEEPROM[NumWord];
    }
}

/** @} */ /* End of group EEPROM_Functions_not_allowed_to_be_located_in_Flash */

/** @} */ /* End of group EEPROM_Exported_Functions */

/** @} */ /* End of group EEPROM */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_eeprom.c */

