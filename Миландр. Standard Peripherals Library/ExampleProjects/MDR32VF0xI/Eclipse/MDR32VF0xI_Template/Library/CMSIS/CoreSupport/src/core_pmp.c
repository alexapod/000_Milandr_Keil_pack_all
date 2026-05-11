/**
 *******************************************************************************
 * @file    core_pmp.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    29/04/2025
 * @brief   RISC-V PMP Access Layer Source File.
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
#include "core_pmp.h"
#include "core_csr.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(PMP_PRESENT)

/** @addtogroup CORE_PMP PMP
 * @{
 */

/** @defgroup CORE_PMP_Private_Defines PMP Private Defines
 * @{
 */

#define PMP_ADDR_SHIFT (2)

#if (__riscv_xlen == 32)
#define CSR_PMPCFGx_L_Msk (((uint_xlen_t)CSR_PMPxCFG_L << 24) | ((uint_xlen_t)CSR_PMPxCFG_L << 16) | ((uint_xlen_t)CSR_PMPxCFG_L << 8) | (uint_xlen_t)CSR_PMPxCFG_L)
#elif (__riscv_xlen == 64)
#define CSR_PMPCFGx_L_Msk (((uint_xlen_t)CSR_PMPxCFG_L << 56) | ((uint_xlen_t)CSR_PMPxCFG_L << 48) | ((uint_xlen_t)CSR_PMPxCFG_L << 40) | ((uint_xlen_t)CSR_PMPxCFG_L << 32) | ((uint_xlen_t)CSR_PMPxCFG_L << 24) | ((uint_xlen_t)CSR_PMPxCFG_L << 16) | ((uint_xlen_t)CSR_PMPxCFG_L << 8) | (uint_xlen_t)CSR_PMPxCFG_L)
#endif

#define IS_PMP_CFG_REGISTER(INDEX)              ((INDEX) <= (PMP_NUM_ENTRIES / PMP_NUM_ENTRIES_PER_CSR))
#define IS_PMP_ADDR_REGISTER(INDEX)             ((INDEX) <= (PMP_NUM_ENTRIES - 1))

#define IS_PMP_GRANULARITY_ALIGNED(VALUE)       (((VALUE) & ((1UL << PMP_GRANULARITY) - 1)) == 0)
#define IS_PMP_SIZE_ALIGNED(VALUE, SIZE)        (((VALUE) & ((SIZE) - 1)) == 0)
#define IS_PMP_POWER_OF_2(VALUE)                ((VALUE) && (((VALUE) & ((VALUE) - 1)) == 0))

#define IS_PMP_R_W_ACCESS_RESERVED(READ, WRITE) ((READ) | !(WRITE))

#if (__riscv_xlen == 64)
#define IS_PMP_MAX_SIZE(VALUE) ((VALUE) < (1UL << 55))
#endif

/** @} */ /* End of group CORE_PMP_Private_Defines */

/** @defgroup CORE_PMP_Private_Functions_Declarations PMP Private Functions Declarations
 * @{
 */

static void        PMP_SetCfgRegister(uint32_t Index, uint_xlen_t Value);
static uint_xlen_t PMP_GetCfgRegister(uint32_t Index);

static void        PMP_SetAddrRegister(uint32_t Index, uint_xlen_t Value);
static uint_xlen_t PMP_GetAddrRegister(uint32_t Index);

static void    PMP_SetCfgEntry(uint32_t Index, uint8_t Value);
static uint8_t PMP_GetCfgEntry(uint32_t Index);

__STATIC_FORCEINLINE uint32_t PMP_CountTailingZero(uint_xlen_t Value);

/** @} */ /* End of the group CORE_PMP_Private_Functions_Declarations */

/** @addtogroup CORE_PMP_Private_Functions PMP Private Functions
 * @{
 */

/**
 * @brief  Set PMPCFGx register.
 * @param  Index: Register index.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES / PMP_NUM_ENTRIES_PER_CSR (for max PMP_NUM_ENTRIES: 0-3 for RV32 and 0-1 for RV64).
 * @param  Value: Register value to set.
 * @return None.
 */
void PMP_SetCfgRegister(uint32_t Index, uint_xlen_t Value)
{
    /* Check the parameters. */
    assert_param(IS_PMP_CFG_REGISTER(Index));

#if (__riscv_xlen == 32)
    switch (Index) {
        case 0:
            CSR_Write(CSR_PMPCFG0, Value);
            break;
        case 1:
            CSR_Write(CSR_PMPCFG1, Value);
            break;
        case 2:
            CSR_Write(CSR_PMPCFG2, Value);
            break;
        case 3:
            CSR_Write(CSR_PMPCFG3, Value);
            break;
        default:
            break;
    }
#elif (__riscv_xlen == 64)
    switch (Index) {
        case 0:
            CSR_Write(CSR_PMPCFG0, Value);
            break;
        case 1:
            CSR_Write(CSR_PMPCFG2, Value);
            break;
        default:
            break;
    }
#endif
}

/**
 * @brief  Get PMPCFGx register.
 * @param  Index: Register index.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES / PMP_NUM_ENTRIES_PER_CSR (for max PMP_NUM_ENTRIES: 0-3 for RV32 and 0-1 for RV64).
 * @return Value of the PMPCFGx register.
 */
uint_xlen_t PMP_GetCfgRegister(uint32_t Index)
{
    /* Check the parameters. */
    assert_param(IS_PMP_CFG_REGISTER(Index));

#if (__riscv_xlen == 32)
    switch (Index) {
        case 0:
            return CSR_Read(CSR_PMPCFG0);
        case 1:
            return CSR_Read(CSR_PMPCFG1);
        case 2:
            return CSR_Read(CSR_PMPCFG2);
        case 3:
            return CSR_Read(CSR_PMPCFG3);
        default:
            return 0;
    }
#elif (__riscv_xlen == 64)
    switch (Index) {
        case 0:
            return CSR_Read(CSR_PMPCFG0);
        case 1:
            return CSR_Read(CSR_PMPCFG2);
        default:
            return 0;
    }
#endif
}

/**
 * @brief  Set PMPADDRx register.
 * @param  Index: Register index.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @param  Value: Register value to set.
 * @return None.
 */
void PMP_SetAddrRegister(uint32_t Index, uint_xlen_t Value)
{
    /* Check the parameters. */
    assert_param(IS_PMP_ADDR_REGISTER(Index));

    switch (Index) {
        case 0:
            CSR_Write(CSR_PMPADDR0, Value);
            break;
        case 1:
            CSR_Write(CSR_PMPADDR1, Value);
            break;
        case 2:
            CSR_Write(CSR_PMPADDR2, Value);
            break;
        case 3:
            CSR_Write(CSR_PMPADDR3, Value);
            break;
        case 4:
            CSR_Write(CSR_PMPADDR4, Value);
            break;
        case 5:
            CSR_Write(CSR_PMPADDR5, Value);
            break;
        case 6:
            CSR_Write(CSR_PMPADDR6, Value);
            break;
        case 7:
            CSR_Write(CSR_PMPADDR7, Value);
            break;
        case 8:
            CSR_Write(CSR_PMPADDR8, Value);
            break;
        case 9:
            CSR_Write(CSR_PMPADDR9, Value);
            break;
        case 10:
            CSR_Write(CSR_PMPADDR10, Value);
            break;
        case 11:
            CSR_Write(CSR_PMPADDR11, Value);
            break;
        case 12:
            CSR_Write(CSR_PMPADDR12, Value);
            break;
        case 13:
            CSR_Write(CSR_PMPADDR13, Value);
            break;
        case 14:
            CSR_Write(CSR_PMPADDR14, Value);
            break;
        case 15:
            CSR_Write(CSR_PMPADDR15, Value);
            break;
        default:
            break;
    }
}

/**
 * @brief  Get PMPADDRx register.
 * @param  Index: Register index.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @return Value of the PMPADDRx register.
 */
uint_xlen_t PMP_GetAddrRegister(uint32_t Index)
{
    /* Check the parameters. */
    assert_param(IS_PMP_ADDR_REGISTER(Index));

    switch (Index) {
        case 0:
            return CSR_Read(CSR_PMPADDR0);
        case 1:
            return CSR_Read(CSR_PMPADDR1);
        case 2:
            return CSR_Read(CSR_PMPADDR2);
        case 3:
            return CSR_Read(CSR_PMPADDR3);
        case 4:
            return CSR_Read(CSR_PMPADDR4);
        case 5:
            return CSR_Read(CSR_PMPADDR5);
        case 6:
            return CSR_Read(CSR_PMPADDR6);
        case 7:
            return CSR_Read(CSR_PMPADDR7);
        case 8:
            return CSR_Read(CSR_PMPADDR8);
        case 9:
            return CSR_Read(CSR_PMPADDR9);
        case 10:
            return CSR_Read(CSR_PMPADDR10);
        case 11:
            return CSR_Read(CSR_PMPADDR11);
        case 12:
            return CSR_Read(CSR_PMPADDR12);
        case 13:
            return CSR_Read(CSR_PMPADDR13);
        case 14:
            return CSR_Read(CSR_PMPADDR14);
        case 15:
            return CSR_Read(CSR_PMPADDR15);
        default:
            return 0;
    }
}

/**
 * @brief  Set entry value (PMPxCFG field in PMPCFGx register).
 * @param  Index: Entry index.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @param  Value: Entry value to set.
 * @return None.
 */
void PMP_SetCfgEntry(uint32_t Index, uint8_t Value)
{
    uint_xlen_t CfgRegister;
    uint32_t    CfgRegisterIndex;
    uint32_t    CfgEntryShift;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Index));

    CfgRegisterIndex = Index / PMP_NUM_ENTRIES_PER_CSR;
    CfgRegister      = PMP_GetCfgRegister(CfgRegisterIndex);

    CfgEntryShift = (Index & (PMP_NUM_ENTRIES_PER_CSR - 1)) << 3;
    CfgRegister   = (CfgRegister & ~((uint_xlen_t)CSR_PMPCFGx_PMPx0CFG_Msk << CfgEntryShift)) | ((uint_xlen_t)Value << CfgEntryShift);

    PMP_SetCfgRegister(CfgRegisterIndex, CfgRegister);
}

/**
 * @brief  Get entry value (PMPxCFG field in PMPCFGx register).
 * @param  Index: Entry index.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @return Entry value.
 */
uint8_t PMP_GetCfgEntry(uint32_t Index)
{
    uint_xlen_t CfgRegister;
    uint32_t    CfgRegisterIndex;
    uint8_t     CfgEntry;
    uint32_t    CfgEntryShift;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Index));

    CfgRegisterIndex = Index / PMP_NUM_ENTRIES_PER_CSR;
    CfgRegister      = PMP_GetCfgRegister(CfgRegisterIndex);

    CfgEntryShift = (Index & (PMP_NUM_ENTRIES_PER_CSR - 1)) << 3;
    CfgEntry      = (uint8_t)((CfgRegister >> CfgEntryShift) & (uint_xlen_t)CSR_PMPCFGx_PMPx0CFG_Msk);

    return CfgEntry;
}

/**
 * @brief  Count tailing zero.
 * @param  Value: Value to count the tailing zeros.
 * @return Number of tailing zeros in value.
 */
uint32_t PMP_CountTailingZero(uint_xlen_t Value)
{
    uint32_t Zeros = 0;

    while ((Value & 0x1) == 0) {
        Zeros++;
        Value >>= 1;
    }

    return Zeros;
}

/** @} */ /* End of the group CORE_PMP_Private_Functions */

/** @addtogroup CORE_PMP_Exported_Functions PMP Exported Functions
 * @{
 */

/**
 * @brief  Deinitialize the PMP CSRs to their default reset values.
 * @param  None.
 * @return @ref ErrorStatus - the status of the PMP deinitialization.
 *         This parameter can be one of the following values:
 *             @arg SUCCESS: The PMP deinitialized successfully.
 *             @arg ERROR:   The PMP was not fully deinitialized because one or more configurable PMP entries are locked.
 */
ErrorStatus PMP_DeInit(void)
{
    uint32_t Index, NumCfgRegisters;

    /* Clear PMPCFGx and PMPADDRx registers. */
    NumCfgRegisters = (PMP_NUM_ENTRIES / PMP_NUM_ENTRIES_PER_CSR) + 1;
    for (Index = 0; Index < NumCfgRegisters; Index++) {
        PMP_SetCfgRegister(Index, 0);
    }

    for (Index = 0; Index < PMP_NUM_ENTRIES; Index++) {
        PMP_SetAddrRegister(Index, 0);
    }

    /* Checking PMPCFGx registers for locked entries. */
    for (Index = 0; Index < NumCfgRegisters; Index++) {
        if ((PMP_GetCfgRegister(Index) & CSR_PMPCFGx_L_Msk) != 0) {
            return ERROR;
        }
    }

    return SUCCESS;
}

/**
 * @brief  Initialize the PMP entry according to the specified parameters in the PMP_EntryInitStruct.
 * @param  Entry: Entry number.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @param  PMP_EntryInitStruct: The pointer to the @ref PMP_Entry_InitTypeDef structure
 *         that contains the configuration information for the PMP entry.
 * @return @ref ErrorStatus - the status of the PMP initialization.
 *         This parameter can be one of the following values:
 *             @arg SUCCESS: The PMP entry initialized successfully.
 *             @arg ERROR:   The PMP entry was not initialized because one or more configurable PMP entries are locked.
 */
ErrorStatus PMP_EntryInit(uint32_t Entry, const PMP_Entry_InitTypeDef* PMP_EntryInitStruct)
{
    uint8_t     EntryValue;
    ErrorStatus Status;

    /* Check the parameters (without the checks performed in PMP_SetModeRange()). */
    assert_param(IS_PMP_ACCESS(PMP_EntryInitStruct->PMP_Access));
    assert_param(IS_FUNCTIONAL_STATE(PMP_EntryInitStruct->PMP_Lock));

    /* Set the PMP entry mode and range (base address and size). */
    Status = PMP_SetModeRange(Entry, PMP_EntryInitStruct->PMP_Mode, PMP_EntryInitStruct->PMP_Address, PMP_EntryInitStruct->PMP_Size);

    /* Check the entry for locking. */
    if (Status == SUCCESS) {
        /* Configure entry access attributes. */
        EntryValue = PMP_GetCfgEntry(Entry) & (uint8_t)~(CSR_PMPxCFG_R | CSR_PMPxCFG_W | CSR_PMPxCFG_X | CSR_PMPxCFG_L);
        EntryValue |= ((uint8_t)PMP_EntryInitStruct->PMP_Access) |
                      ((uint8_t)PMP_EntryInitStruct->PMP_Lock << CSR_PMPxCFG_L_Pos);
        PMP_SetCfgEntry(Entry, EntryValue);
    }

    return Status;
}

/**
 * @brief  Get the PMP entry configuration.
 * @param  Entry: Entry number.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @param  PMP_EntryInitStruct: The pointer to the @ref PMP_Entry_InitTypeDef structure
 *         into which the configuration data will be written.
 * @return None.
 */
void PMP_EntryGetConfig(uint32_t Entry, PMP_Entry_InitTypeDef* PMP_EntryInitStruct)
{
    uint8_t EntryValue;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Entry));

    /* Get the PMP entry mode and range (base address and size). */
    PMP_GetModeRange(Entry, &PMP_EntryInitStruct->PMP_Mode, &PMP_EntryInitStruct->PMP_Address, &PMP_EntryInitStruct->PMP_Size);

    /* Get entry access attributes. */
    EntryValue                      = PMP_GetCfgEntry(Entry);
    PMP_EntryInitStruct->PMP_Access = (PMP_Access_TypeDef)(EntryValue & (CSR_PMPxCFG_R | CSR_PMPxCFG_W | CSR_PMPxCFG_X));
    PMP_EntryInitStruct->PMP_Lock   = (FunctionalState)((EntryValue & CSR_PMPxCFG_L) >> CSR_PMPxCFG_L_Pos);
}

/**
 * @brief  Fill each PMP_EntryInitStruct member with its default value.
 * @param  PMP_EntryInitStruct: The pointer to the @ref PMP_EntryInitStruct structure
 *         which is to be initialized.
 * @return None.
 */
void PMP_EntryStructInit(PMP_Entry_InitTypeDef* PMP_EntryInitStruct)
{
    PMP_EntryInitStruct->PMP_Mode    = PMP_MODE_OFF;
    PMP_EntryInitStruct->PMP_Address = 0;
    PMP_EntryInitStruct->PMP_Size    = 0;
    PMP_EntryInitStruct->PMP_Access  = PMP_ACCESS_READ_WRITE_EXECUTE;
    PMP_EntryInitStruct->PMP_Lock    = DISABLE;
}

/**
 * @brief  Set the PMP entry mode and range (base address and size).
 * @param  Entry: Entry number.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @param  Mode: @ref PMP_Mode_TypeDef - specify a PMP entry mode.
 * @param  Address: Base address of the PMP entry.
 *         The available values for this parameter depend on Mode:
 *             - PMP_MODE_OFF: Address can be any value (writes to the PMPADDRx register with left shift of 2);
 *             - PMP_MODE_TOP_OF_RANGE:
 *                 - Entry == 0: Address must be 0;
 *                 - Entry != 0: Address can be any value aligned to 2^PMP_GRANULARITY;
 *             - PMP_MODE_NATURALLY_ALIGNED: Address can be any value aligned to Size, but not less than 2^PMP_GRANULARITY.
 * @param  Size: Size of the PMP entry in bytes.
 *         The available values for this parameter depend on Mode:
 *             - PMP_MODE_OFF: Size can be any value (not used);
 *             - PMP_MODE_TOP_OF_RANGE: Size can be any value that is a multiple of 2^PMP_GRANULARITY;
 *             - PMP_MODE_NATURALLY_ALIGNED: Size can be any value 2^N, where N=[PMP_GRANULARITY;31] for RV32 and N=[PMP_GRANULARITY;54] for RV64.
 * @return @ref ErrorStatus - the status of setting the mode and range for the PMP entry.
 *         This parameter can be one of the following values:
 *             @arg SUCCESS: The mode and range for the PMP entry have been successfully set.
 *             @arg ERROR:   The mode and range for the PMP entry have not been set because one or more configurable PMP entries are locked.
 */
ErrorStatus PMP_SetModeRange(uint32_t Entry, PMP_Mode_TypeDef Mode, uint_xlen_t Address, uint_xlen_t Size)
{
    uint8_t     EntryValue, EntryMode;
    uint_xlen_t EntryAddress, EntrySizeMask;
    uint_xlen_t PrevEntryAddress = 0;
    ErrorStatus Status           = SUCCESS;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Entry));
    assert_param(IS_PMP_MODE(Mode));
    assert_param((Mode == PMP_MODE_TOP_OF_RANGE) ? IS_PMP_GRANULARITY_ALIGNED(Size) && (Size != 0) : 1);
#if (__riscv_xlen == 32)
    assert_param((Mode == PMP_MODE_NATURALLY_ALIGNED) ? IS_PMP_POWER_OF_2(Size) && IS_PMP_GRANULARITY_ALIGNED(Size) : 1);
#elif (__riscv_xlen == 64)
    assert_param((Mode == PMP_MODE_NATURALLY_ALIGNED) ? IS_PMP_POWER_OF_2(Size) && IS_PMP_GRANULARITY_ALIGNED(Size) && IS_PMP_MAX_SIZE(Size) : 1);
#endif
    assert_param((Mode == PMP_MODE_TOP_OF_RANGE) ? (Entry != 0) ? IS_PMP_GRANULARITY_ALIGNED(Address) : (Address == 0) : 1);
    assert_param((Mode == PMP_MODE_NATURALLY_ALIGNED) ? IS_PMP_SIZE_ALIGNED(Address, Size) : 1);

    /* Check the entry for locking. */
    EntryValue = PMP_GetCfgEntry(Entry);
    if ((EntryValue & CSR_PMPxCFG_L) == CSR_PMPxCFG_L_UNLOCK) {
        /* Determine the entry mode and the address register value. */
        switch (Mode) {
            case PMP_MODE_OFF:
                EntryMode    = CSR_PMPxCFG_A_OFF;
                EntryAddress = Address >> PMP_ADDR_SHIFT;
                break;
            case PMP_MODE_TOP_OF_RANGE:
                EntryMode = CSR_PMPxCFG_A_TOR;
                if (Entry != 0) {
                    EntryAddress = (Address + Size) >> PMP_ADDR_SHIFT;
                    /* Check the previous entry for locking. */
                    if ((PMP_GetCfgEntry(Entry - 1) & CSR_PMPxCFG_L) == CSR_PMPxCFG_L_UNLOCK) {
                        PrevEntryAddress = Address >> PMP_ADDR_SHIFT;
                    } else {
                        Status = ERROR;
                    }
                } else {
                    EntryAddress = Size >> PMP_ADDR_SHIFT;
                }
                break;
            case PMP_MODE_NATURALLY_ALIGNED:
                if (Size == 4) {
                    EntryMode    = CSR_PMPxCFG_A_NA4;
                    EntryAddress = Address >> PMP_ADDR_SHIFT;
                } else {
                    EntryMode     = CSR_PMPxCFG_A_NAPOT;
                    EntrySizeMask = (Size >> PMP_ADDR_SHIFT) - 1;
                    EntryAddress  = ((Address >> PMP_ADDR_SHIFT) & ~EntrySizeMask) | (EntrySizeMask >> 1);
                }
                break;
            default:
                Status = ERROR;
                break;
        }
        if (Status == SUCCESS) {
            /* Disable the entry. */
            EntryValue &= (uint8_t)~CSR_PMPxCFG_A_Msk;
            PMP_SetCfgEntry(Entry, EntryValue);

            /* Configure the address register. */
            PMP_SetAddrRegister(Entry, EntryAddress);
            if ((Mode == PMP_MODE_TOP_OF_RANGE) && (Entry != 0)) {
                PMP_SetAddrRegister(Entry - 1, PrevEntryAddress);
            }

            /* Configure the entry mode. */
            PMP_SetCfgEntry(Entry, EntryMode);
        }
    } else {
        Status = ERROR;
    }

    return Status;
}

/**
 * @brief  Get the PMP entry mode and range (base address and size).
 * @param  Entry: Entry number.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @param  Mode: The pointer to the @ref PMP_Mode_TypeDef variable into which the PMP entry mode will be written.
 * @param  Address: The pointer to a variable into which the base address of the PMP entry will be written.
 * @param  Size: The pointer to a variable into which the size of the PMP entry in bytes will be written.
 * @return None.
 */
void PMP_GetModeRange(uint32_t Entry, PMP_Mode_TypeDef* Mode, uint_xlen_t* Address, uint_xlen_t* Size)
{
    uint8_t     EntryValue;
    uint_xlen_t EntryAddress, PrevEntryAddress, EntrySizeBits;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Entry));

    /* Get the entry value and the address register value. */
    EntryValue   = PMP_GetCfgEntry(Entry);
    EntryAddress = PMP_GetAddrRegister(Entry);

    /* Determine the entry mode and range (base address and size). */
    switch (EntryValue & CSR_PMPxCFG_A_Msk) {
        case CSR_PMPxCFG_A_OFF:
            *Mode    = PMP_MODE_OFF;
            *Address = EntryAddress << PMP_ADDR_SHIFT;
            *Size    = 0;
            break;
        case CSR_PMPxCFG_A_TOR:
            if (Entry != 0) {
                PrevEntryAddress = PMP_GetAddrRegister(Entry - 1);
            } else {
                PrevEntryAddress = 0;
            }
            *Mode    = PMP_MODE_TOP_OF_RANGE;
            *Address = PrevEntryAddress << PMP_ADDR_SHIFT;
            *Size    = (EntryAddress - PrevEntryAddress) << PMP_ADDR_SHIFT;
            break;
        case CSR_PMPxCFG_A_NA4:
            *Mode    = PMP_MODE_NATURALLY_ALIGNED;
            *Address = EntryAddress << PMP_ADDR_SHIFT;
            *Size    = 4;
            break;
        case CSR_PMPxCFG_A_NAPOT:
            EntrySizeBits = PMP_CountTailingZero(~EntryAddress);
            *Mode         = PMP_MODE_NATURALLY_ALIGNED;
            *Address      = (EntryAddress & ~((1UL << EntrySizeBits) - 1)) << PMP_ADDR_SHIFT;
            *Size         = 1UL << (EntrySizeBits + 1 + PMP_ADDR_SHIFT);
            break;
        default:
            break;
    }
}

/**
 * @brief  Set the access permissions for the PMP entry.
 * @param  Entry: Entry number.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @param  Access: @ref PMP_Access_TypeDef - the access permissions.
 * @return @ref ErrorStatus - the status of setting access permission for the PMP entry.
 *         This parameter can be one of the following values:
 *             @arg SUCCESS: Access permissions are set successfully.
 *             @arg ERROR:   Access permissions were not set because the PMP entry is locked.
 */
ErrorStatus PMP_SetAccess(uint32_t Entry, PMP_Access_TypeDef Access)
{
    uint8_t     EntryValue;
    ErrorStatus Status = ERROR;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Entry));
    assert_param(IS_PMP_ACCESS(Access));

    EntryValue = PMP_GetCfgEntry(Entry);
    if ((EntryValue & CSR_PMPxCFG_L) == CSR_PMPxCFG_L_UNLOCK) {
        EntryValue = (EntryValue & (uint8_t)~(CSR_PMPxCFG_R | CSR_PMPxCFG_W | CSR_PMPxCFG_X)) | (uint8_t)Access;
        PMP_SetCfgEntry(Entry, EntryValue);
        Status = SUCCESS;
    }

    return Status;
}

/**
 * @brief  Get the access permissions for the PMP entry.
 * @param  Entry: Entry number.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @return @ref PMP_Access_TypeDef - the access permissions.
 */
PMP_Access_TypeDef PMP_GetAccess(uint32_t Entry)
{
    uint8_t            EntryValue;
    PMP_Access_TypeDef Access;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Entry));

    EntryValue = PMP_GetCfgEntry(Entry);
    Access     = (PMP_Access_TypeDef)(EntryValue & (CSR_PMPxCFG_R | CSR_PMPxCFG_W | CSR_PMPxCFG_X));

    return Access;
}

/**
 * @brief   Set the PMP entry lock.
 * @warning After locking the specified PMP entry remains locked until reset.
 * @param   Entry: Entry number.
 *          This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @return  None.
 */
void PMP_SetLock(uint32_t Entry)
{
    uint8_t EntryValue;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Entry));

    EntryValue = PMP_GetCfgEntry(Entry);
    if ((EntryValue & CSR_PMPxCFG_L) == CSR_PMPxCFG_L_UNLOCK) {
        EntryValue |= CSR_PMPxCFG_L;
        PMP_SetCfgEntry(Entry, EntryValue);
    }
}

/**
 * @brief  Get the PMP entry lock status.
 * @param  Entry: Entry number.
 *         This parameter can be a value from 0 to PMP_NUM_ENTRIES - 1.
 * @return @ref FunctionalState - the PMP entry lock status.
 */
FunctionalState PMP_GetLock(uint32_t Entry)
{
    uint8_t         EntryValue;
    FunctionalState EntryLock;

    /* Check the parameters. */
    assert_param(IS_PMP_ENTRY(Entry));

    EntryValue = PMP_GetCfgEntry(Entry);
    EntryLock  = (FunctionalState)((EntryValue & CSR_PMPxCFG_L) >> CSR_PMPxCFG_L_Pos);

    return EntryLock;
}

/** @} */ /* End of group CORE_PMP_Exported_Functions */

/** @} */ /* End of group CORE_PMP */

#endif /* PMP_PRESENT */

/** @} */ /* End of group CORE_SUPPORT */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_pmp.c */

