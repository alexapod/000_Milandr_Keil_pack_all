/**
 ******************************************************************************
 * @file    MDR32VF0xI_utils.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    20/05/2025
 * @brief   This file contains all utility functions of the firmware library.
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

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_utils.h"
#if defined(USE_MDR32F02_REV_1X)
#include "MDR32VF0xI_bkp.h"
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#include "MDR32VF0xI_flash.h"
#endif

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup UTILS UTILS
 * @{
 */

/** @defgroup UTILS_Private_Variables UTILS Private Variables
 * @{
 */

static DELAY_Mode_TypeDef DelayMode = DELAY_MODE_PROGRAM;

static uint32_t DelayConstUs = (uint32_t)(((uint64_t)HSI_FREQUENCY_Hz << 31) / (uint64_t)64000000);
static uint32_t DelayConstMs = (uint32_t)(((uint64_t)HSI_FREQUENCY_Hz << 31) / (uint64_t)65536000);

/** @} */ /* End of the group UTILS_Private_Variables */

/** @defgroup UTILS_Private_Function_Prototypes UTILS Private Functions Prototypes
 * @{
 */

static ErrorStatus        DELAY_MachineTimer_Init(void);
__STATIC_FORCEINLINE void DELAY_MachineTimer_WaitTicks(uint32_t Ticks);

static void DELAY_CycleCounter_Init(void);

/** @} */ /* End of the group UTILS_Private_Function_Prototypes */

/** @addtogroup UTILS_Exported_Functions UTILS Exported Functions
 * @{
 */

/**
 * @brief  Initialize the DELAY module according to a specified mode.
 * @note   The core clock from SystemCoreClock is used to calculate the delay time.
 *         You must configure the required core clock and call SystemCoreClockUpdate() before calling DELAY_Init().
 * @param  Mode: @ref DELAY_Mode_TypeDef - specify the delay mode.
 * @return @ref ErrorStatus - SUCCESS if initialized, else ERROR.
 */
ErrorStatus DELAY_Init(DELAY_Mode_TypeDef Mode)
{
    assert_param(IS_DELAY_MODE(Mode));

    DelayMode = Mode;

    switch (DelayMode) {
        case DELAY_MODE_PROGRAM:
            DelayConstUs = DELAY_PROGRAM_GET_CONST_US(SystemCoreClock);
            DelayConstMs = DELAY_PROGRAM_GET_CONST_MS(SystemCoreClock);
            break;
        case DELAY_MODE_MACHINE_TIMER:
#if defined(USE_MDR32F02_REV_1X)
            DelayConstUs = DELAY_MACHINE_TIMER_GET_CONST_US(LSE_FREQUENCY_Hz);
            DelayConstMs = DELAY_MACHINE_TIMER_GET_CONST_MS(LSE_FREQUENCY_Hz);
#else
            DelayConstUs = DELAY_MACHINE_TIMER_GET_CONST_US(SystemCoreClock / 2);
            DelayConstMs = DELAY_MACHINE_TIMER_GET_CONST_MS(SystemCoreClock / 2);
#endif
            return DELAY_MachineTimer_Init();
            break;
        case DELAY_MODE_CYCLE_COUNTER:
            DelayConstUs = DELAY_CYCLE_COUNTER_GET_CONST_US(SystemCoreClock);
            DelayConstMs = DELAY_CYCLE_COUNTER_GET_CONST_MS(SystemCoreClock);
            DELAY_CycleCounter_Init();
            break;
    }
    return SUCCESS;
}

/**
 * @brief  Perform a blocking delay in microseconds.
 * @param  Us: Specify the delay time in microseconds.
 *         This parameter can be a value up to 2^26 = 67108864.
 * @return None.
 */
void DELAY_WaitUs(uint32_t Us)
{
    uint32_t DelayTicksUs;

    DelayTicksUs = DELAY_GET_TICKS_US(Us, DelayConstUs);

    switch (DelayMode) {
        case DELAY_MODE_PROGRAM:
            DELAY_PROGRAM_WaitLoopsAsm(DelayTicksUs);
            break;
        case DELAY_MODE_MACHINE_TIMER:
            DELAY_MachineTimer_WaitTicks(DelayTicksUs);
            break;
        case DELAY_MODE_CYCLE_COUNTER:
            DELAY_CycleCounter_WaitTicksAsm(DelayTicksUs);
            break;
    }
}

/**
 * @brief  Perform a blocking delay in milliseconds.
 * @param  Ms: Specify the delay time in milliseconds.
 *         This parameter can be a value up to 2^32 / CPU_CLK (kHz), but not more than 2^18 = 262144.
 * @return None.
 */
void DELAY_WaitMs(uint32_t Ms)
{
    uint32_t DelayTicksMs;

    DelayTicksMs = DELAY_GET_TICKS_MS(Ms, DelayConstMs);

    switch (DelayMode) {
        case DELAY_MODE_PROGRAM:
            DELAY_PROGRAM_WaitLoopsAsm(DelayTicksMs);
            break;
        case DELAY_MODE_MACHINE_TIMER:
            DELAY_MachineTimer_WaitTicks(DelayTicksMs);
            break;
        case DELAY_MODE_CYCLE_COUNTER:
            DELAY_CycleCounter_WaitTicksAsm(DelayTicksMs);
            break;
    }
}

/**
 * @brief  Initialize trimmings according to factory data.
 * @note:  For MDR32F02 factory data is not validated with CRC, so trimmings will always be initialized from factory data
 *         and function will always return SUCCESS.
 * @param  None.
 * @return @ref ErrorStatus - SUCCESS if initialized with factory data trimmings, ERROR if initialized with default trimmings.
 */
ErrorStatus FactoryDataTrimInit(void)
{
    uint32_t Temp1, Temp2, Temp3;
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    FLASH_FactoryData_TypeDef FactoryData;
    ErrorStatus               DataValid;

    DataValid = FLASH_ReadFactoryData(&FactoryData);
    if (DataValid == SUCCESS) {
        Temp1                   = MDR_RST_CLK->PER2_CLOCK;
        MDR_RST_CLK->PER2_CLOCK = Temp1 | RST_CLK_PER2_CLOCK_PCLK_EN_BKP | RST_CLK_PER2_CLOCK_PCLK_EN_ADC;
        Temp2                   = MDR_BKP->WPR;
        if (Temp2 != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
        }

        Temp3 = MDR_BKP->CLK;
        Temp3 &= ~(BKP_CLK_HSI_LSI_TRIM_Msk);
        Temp3 |= ((FactoryData.TrimHSI << BKP_CLK_HSI_LSI_TRIM_Pos) & BKP_CLK_HSI_LSI_TRIM_Msk);
        MDR_BKP->CLK = Temp3;

        Temp3 = MDR_BKP->LDO;
        Temp3 &= ~(BKP_LDO_LDO_BOOST_Msk | BKP_LDO_SW_OFF_Msk | BKP_LDO_TAMPF_Msk);
        Temp3 |= ((FactoryData.TrimLDO << BKP_LDO_LDO_BOOST_Pos) & BKP_LDO_LDO_BOOST_Msk);
        MDR_BKP->LDO = Temp3;

        MDR_ADC->ADC_TRIM = ((FactoryData.TrimBG << ADC_TRIM_BG_TRIM_Pos) & ADC_TRIM_BG_TRIM_Msk);

        if (Temp2 != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = Temp2;
        }
        MDR_RST_CLK->PER2_CLOCK = Temp1;
    } else {
#if defined(USE_MDR1206)
        if (GetChipID() == CHIP_ID_MDR1206FI) {
            FactoryData.TrimHSI = TRIM_HSI_MDR1206FI_VALUE_TYP;
            FactoryData.TrimBG  = TRIM_BG_MDR1206FI_VALUE_TYP;
        } else {
            FactoryData.TrimHSI = TRIM_HSI_MDR1206AFI_VALUE_TYP;
            FactoryData.TrimBG  = TRIM_BG_MDR1206AFI_VALUE_TYP;
        }
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI)
        FactoryData.TrimHSI = TRIM_HSI_VALUE_TYP;
        FactoryData.TrimBG  = TRIM_BG_VALUE_TYP;
#endif

        Temp1                   = MDR_RST_CLK->PER2_CLOCK;
        MDR_RST_CLK->PER2_CLOCK = Temp1 | RST_CLK_PER2_CLOCK_PCLK_EN_BKP | RST_CLK_PER2_CLOCK_PCLK_EN_ADC;
        Temp2                   = MDR_BKP->WPR;
        if (Temp2 != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
        }

        Temp3 = MDR_BKP->CLK;
        Temp3 &= ~(BKP_CLK_HSI_LSI_TRIM_Msk);
        Temp3 |= ((FactoryData.TrimHSI << BKP_CLK_HSI_LSI_TRIM_Pos) & BKP_CLK_HSI_LSI_TRIM_Msk);
        MDR_BKP->CLK = Temp3;

        MDR_ADC->ADC_TRIM = ((FactoryData.TrimBG << ADC_TRIM_BG_TRIM_Pos) & ADC_TRIM_BG_TRIM_Msk);

        if (Temp2 != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = Temp2;
        }
        MDR_RST_CLK->PER2_CLOCK = Temp1;
    }
    return DataValid;
#elif defined(USE_MDR32F02)
    Temp1                   = MDR_RST_CLK->PER2_CLOCK;
    MDR_RST_CLK->PER2_CLOCK = Temp1 | RST_CLK_PER2_CLOCK_PCLK_EN_BKP;
    Temp2                   = MDR_BKP->WPR;
    if (Temp2 != BKP_WPR_BKP_WPR_UNLOCK) {
        MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
    }

    Temp3 = MDR_BKP->CLK;
    Temp3 &= ~(BKP_CLK_HSI_LSI_TRIM_Msk);
    Temp3 |= ((OTP_SPECIAL_FIELDS->HSI_TRIM << BKP_CLK_HSI_LSI_TRIM_Pos) & BKP_CLK_HSI_LSI_TRIM_Msk);
    MDR_BKP->CLK = Temp3;

    if (Temp2 != BKP_WPR_BKP_WPR_UNLOCK) {
        MDR_BKP->WPR = Temp2;
    }
    MDR_RST_CLK->PER2_CLOCK = Temp1;
    return SUCCESS;
#endif
}

#if defined(USE_MDR1206)
/**
 * @brief  Get microcontroller ID (215 or 217) for MDR1206.
 * @note   This function can be used only for MDR1206 microcontroller.
 * @param  None.
 * @return Microcontroller ID value.
 */
uint8_t GetChipID(void)
{
    uint32_t        Per2Clock;
    static uint32_t ChipID;

    if (ChipID == 0) {
        Per2Clock = MDR_RST_CLK->PER2_CLOCK;

        MDR_RST_CLK->PER2_CLOCK = Per2Clock | RST_CLK_PER2_CLOCK_PCLK_EN_FLASH;
        ChipID                  = MDR_FLASH->CHIP_ID_CTRL;

        MDR_RST_CLK->PER2_CLOCK = Per2Clock;

        ChipID = (ChipID & FLASH_CHIP_ID_CTRL_CHIP_ID_Msk) >> FLASH_CHIP_ID_CTRL_CHIP_ID_Pos;
    }

    return (uint8_t)ChipID;
}
#endif

/**
 * @brief  System reset using WWDG.
 * @note   Does not reset BKP domain and IWDG.
 * @param  WWDG_C2_Source: @ref RST_CLK_WWDG_C2_ClockSource_TypeDef - specify WWDG_C2 clock source.
 *         The selected WWDG_C2 clock source must be configured before calling WWDG_SystemReset().
 *         For a faster reset, it is recommended to select the highest frequency.
 * @return None.
 */
void WWDG_SystemReset(RST_CLK_WWDG_C2_ClockSource_TypeDef WWDG_C2_Source)
{
    uint32_t TmpReg;

    /* Check the parameters. */
    assert_param(IS_RST_CLK_WWDG_C2_CLOCK_SOURCE(WWDG_C2_Source));

    /* Enable WDG_CLK and PCLK for WWDG. */
    TmpReg = MDR_RST_CLK->PER1_CLOCK & ~(RST_CLK_PER1_CLOCK_WDG_C2_SEL_Msk | RST_CLK_PER1_CLOCK_WDG_BRG_Msk);
    TmpReg |= (uint32_t)WWDG_C2_Source | RST_CLK_PER1_CLOCK_WDG_CLK_EN;

    MDR_RST_CLK->PER1_CLOCK = TmpReg;
    MDR_RST_CLK->PER2_CLOCK |= RST_CLK_PER2_CLOCK_PCLK_EN_WWDG;

    /* Configuration WWDG for reset: minimum window value and maximum counter value. */
    MDR_WWDG->CFR = 0x40;
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }
    MDR_WWDG->CR = WWDG_CR_WDGA_Msk | 0x7F;
    while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC_Msk) == 0) { }

    /* WWDG reload counter outside window, reset immediately by clock WWDG_CLK. */
    MDR_WWDG->CR = 0x7F;

    /* Wait reset. */
    while (1) { }
}

/** @} */ /* End of the group UTILS_Exported_Functions */

/** @defgroup UTILS_Private_Functions UTILS Private Functions
 * @{
 */

/**
 * @brief  Initialize the machine timer.
 * @note   In MDR32F02 rev 1.x: The cycle counter and core clock from SystemCoreClock are used for delay. Do not disable the cycle counter.
 *         Before calling this function, you must update SystemCoreClock by calling SystemCoreClockUpdate().
 * @param  None.
 * @return @ref ErrorStatus - SUCCESS if initialized, else ERROR.
 */
ErrorStatus DELAY_MachineTimer_Init(void)
{
#if defined(USE_MDR32F02_REV_1X)
    uint32_t TempReg1, TempReg2, TempReg3;

    /* Enable the BKP clock if it is disabled. */
    TempReg1 = MDR_RST_CLK->PER2_CLOCK;
    if ((TempReg1 & RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Msk) == 0) {
        MDR_RST_CLK->PER2_CLOCK = TempReg1 | RST_CLK_PER2_CLOCK_PCLK_EN_BKP;
    }

    /* Check the LSE_RDY flag. */
    TempReg2 = MDR_BKP->CLK;
    if ((TempReg2 & BKP_CLK_LSE_RDY_Msk) == 0) {
        /* Return error if LSE has been enabled but still is not ready. */
        if ((TempReg2 & BKP_CLK_LSE_ON_Msk) != 0) {
            return ERROR;
        }

        /* Disable BKP write protection. */
        TempReg3 = MDR_BKP->WPR;
        if (TempReg3 != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
        }
        /* Enable the LSE clock. If it is rev.1 or rev.1.1, assume errata0001 has been taken
         into account and on-board LSE generator is used. */
        BKP_LSE_Config(BKP_LSE_BYPASS);

        if (BKP_LSE_GetStatus() == ERROR) {
            return ERROR;
        }

        /* Restore the BKP_WPR register value. */
        if (TempReg3 != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = TempReg3;
        }
    }

    /* Restore the PER2_CLOCK register value. */
    if ((TempReg1 & RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Msk) == 0) {
        MDR_RST_CLK->PER2_CLOCK = TempReg1;
    }

#else
    MDR_RST_CLK->DIV_SYS_TIM = 0x00000000;
#endif
    return SUCCESS;
}

/**
 * @brief  Initialize the cycle counter.
 * @param  None.
 * @return None.
 */
void DELAY_CycleCounter_Init(void)
{
    CSR_SetBits(CSR_MCOUNTEREN, CSR_MCOUNTEREN_CY);
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    CSR_ClearBits(CSR_MCOUNTINHIBIT, CSR_MCOUNTINHIBIT_CY);
#endif
}

/**
 * @brief  Perform a blocking delay with a system tick timer, in ticks.
 * @param  Ticks: Specify the delay time in ticks.
 * @return None.
 */
void DELAY_MachineTimer_WaitTicks(uint32_t Ticks)
{
    uint64_t CompareValue = (uint64_t)Ticks + CLINT_MTIMER_GetTime();
    while (CLINT_MTIMER_GetTime() < CompareValue) { }
}

/** @} */ /* End of the group UTILS_Private_Functions */

/** @} */ /* End of the group UTILS */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_utils.c */

