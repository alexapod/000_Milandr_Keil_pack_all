/**
 ******************************************************************************
 * @file    system_MDR32VF0xI.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    10/04/2025
 * @brief   Device Peripheral Access Layer System Source File for MDR32VF0xI.
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
#include "system_MDR32VF0xI.h"
#include "system_MDR32VF0xI_it.h"

/** @addtogroup DEVICE_SUPPORT Device Support
 * @{
 */

/** @addtogroup MDR32VF0xI_DEVICE MDR32VF0xI
 *  @{
 */

/** @addtogroup MDR32VF0xI_System MDR32VF0xI System
 * @{
 */

/** @defgroup MDR32VF0xI_System_Exported_Variables MDR32VF0xI System Exported Variables
 * @{
 */

/**
 * @brief System clock frequency (core clock) value.
 */

#if defined(USE_MDR32F02)
uint32_t SystemCoreClock = HSI_FREQUENCY_Hz;
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
uint32_t SystemCoreClock = HSI_FREQUENCY_Hz / 16;
#endif

/** @} */ /* End of group MDR32VF0xI_System_Exported_Variables */

/** @defgroup MDR32VF0xI_System_Private_Functions_Declarations MDR32VF0xI System Private Functions Declarations
 * @{
 */

__STATIC_FORCEINLINE void SystemInitIRQ(void);
__STATIC_FORCEINLINE void SystemInitCycleCounter(void);
#if defined(FACTORY_DATA_SYSTEM_INIT)
__STATIC_FORCEINLINE void SystemInitTrim(void);
#endif
#if defined(WORKAROUND_ERROR_BLDO_NOT_OPERATED)
__STATIC_FORCEINLINE void       SystemInitWorkaround(void);
__RAM_TEXT_NOINLINE static void DelayCoreClockDefault(void);
#endif

/** @} */ /* End of the group MDR32VF0xI_System_Private_Functions_Declarations */

/** @defgroup MDR32VF0xI_System_Exported_Functions MDR32VF0xI System Exported Functions
 * @{
 */

/**
 * @brief  Update SystemCoreClock according to clock register values.
 * @param  None.
 * @return None.
 */
void SystemCoreClockUpdate(void)
{
    uint32_t CPU_C1_Freq = 0, CPU_C2_Freq = 0, CPU_C3_Freq = 0;
    uint32_t PLL_Mult = 0;
    uint32_t Temp1 = 0, Temp2 = 0;

    /* Compute CPU_CLK frequency. */

    Temp1 = MDR_RST_CLK->CPU_CLOCK;

    /* Select CPU_CLK from HSI, CPU_C3, LSE, LSI cases. */
    switch (Temp1 & RST_CLK_CPU_CLOCK_HCLK_SEL_Msk) {
        case RST_CLK_CPU_CLOCK_HCLK_SEL_HSI:
            SystemCoreClock = HSI_FREQUENCY_Hz;
            break;

        case RST_CLK_CPU_CLOCK_HCLK_SEL_LSE:
            SystemCoreClock = LSE_FREQUENCY_Hz;
            break;

        case RST_CLK_CPU_CLOCK_HCLK_SEL_LSI:
            SystemCoreClock = LSI_FREQUENCY_Hz;
            break;

        case RST_CLK_CPU_CLOCK_HCLK_SEL_CPU_C3:
            /* Determine CPU_C1 frequency. */
            switch (Temp1 & RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk) {
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSI:
                    CPU_C1_Freq = HSI_FREQUENCY_Hz;
                    break;
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSI_DIV_2:
                    CPU_C1_Freq = HSI_FREQUENCY_Hz / 2;
                    break;
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSE:
                    CPU_C1_Freq = HSE_FREQUENCY_Hz;
                    break;
                case RST_CLK_CPU_CLOCK_CPU_C1_SEL_HSE_DIV_2:
                    CPU_C1_Freq = HSE_FREQUENCY_Hz / 2;
                    break;
            }

            /* Determine CPU_C2 frequency. */
            if ((Temp1 & RST_CLK_CPU_CLOCK_CPU_C2_SEL) != 0) {
                /* Determine CPU PLL output frequency. */
                Temp2    = MDR_RST_CLK->PLL_CONTROL;
                PLL_Mult = ((Temp2 & RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk) >> RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos) + 1;

                /* Determine CPU_PLL source. */
                if ((Temp2 & RST_CLK_PLL_CONTROL_PLL_CPU_SEL) != 0) {
                    CPU_C2_Freq = CPU_C1_Freq * PLL_Mult;
                } else {
                    CPU_C2_Freq = HSE_FREQUENCY_Hz * PLL_Mult;
                }
            } else {
                CPU_C2_Freq = CPU_C1_Freq;
            }

            /* Determine CPU_C3 frequency. */
            Temp1 = ((Temp1 & RST_CLK_CPU_CLOCK_CPU_C3_SEL_Msk) >> RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos);
            if ((Temp1 & 0x8U) == 0x00) {
                CPU_C3_Freq = CPU_C2_Freq;
            } else {
                CPU_C3_Freq = CPU_C2_Freq >> ((Temp1 & 0x7U) + 1);
            }
            SystemCoreClock = CPU_C3_Freq;
            break;
    }
}

/**
 * @brief  Setup the microcontroller system:
 *          - SystemCoreClock variable;
 *          - cycle counter configuration;
 *          - interrupt configuration.
 * @note   This function should be used only after reset.
 * @param  None.
 * @return None.
 */
void SystemInit(void)
{

#if defined(FACTORY_DATA_SYSTEM_INIT)
    SystemInitTrim();
#endif
#if defined(WORKAROUND_ERROR_BLDO_NOT_OPERATED)
    SystemInitWorkaround();
#endif
    SystemInitIRQ();
    SystemInitCycleCounter();

    SystemCoreClockUpdate();
}

/** @} */ /* End of group MDR32VF0xI_System_Exported_Functions */

/** @defgroup MDR32VF0xI_System_Private_Functions MDR32VF0xI System Private Functions
 * @{
 */

/**
 * @brief  Setup the microcontroller interrupt controller.
 * @param  None.
 * @return None.
 */
__STATIC_FORCEINLINE void SystemInitIRQ(void)
{
#if defined(USE_MDR32F02)
    int Index;

    /* Disable all interrupts in MCU. */
    IT_GlobalDisableIRQ();
    PLIC_DisableExternalIRQ(PLIC_PRIVILEGE_IRQ_MODE_M);
    /* Set lowest PLIC IRQ threshold. */
    PLIC_SetThresholdIRQ(PLIC_THRESHOLD_0_ENABLE_ALL);
    /* Set the minimum priority for each interrupt vector. */
    for (Index = 1; Index < 31; Index++) {
        if (Index == 19) {
            Index++;
        }
        PLIC_SetPriorityIRQ((IRQn_TypeDef)Index, PLIC_PRIORITY_LOWEST);
    }
#if defined(PLIC_SYSTEM_INIT)
    /* Algorithm for removing an interrupt request to the PLIC block from DMA. */

    /* Enable SSP block clocking to complete generation of DMA requests. */
    MDR_RST_CLK->PER2_CLOCK |= (RST_CLK_PER2_CLOCK_PCLK_EN_SSP1 |
                                RST_CLK_PER2_CLOCK_PCLK_EN_SSP2 |
                                RST_CLK_PER2_CLOCK_PCLK_EN_SSP3);
    /* Enable DMA interrupt in PLIC block. */
    PLIC_EnableIRQ(DMA_IRQn);
    /* Terminate with DMA interrupt in PLIC block. */
    IRQn_TypeDef irqn = PLIC_ClaimIRQ();
    PLIC_CompleteIRQ(irqn);
    /* Disable DMA interrupt in PLIC block. */
    PLIC_DisableIRQ(DMA_IRQn);
    /* Set Trap_IRQHandler in PLIC. */
    PLIC_SetTrapVector(PLIC_PRIVILEGE_IRQ_MODE_M, (IRQHandler_TypeDef)Trap_IRQHandler);
    /* Disable SSP block clocking. */
    MDR_RST_CLK->PER2_CLOCK &= ~(RST_CLK_PER2_CLOCK_PCLK_EN_SSP1 |
                                 RST_CLK_PER2_CLOCK_PCLK_EN_SSP2 |
                                 RST_CLK_PER2_CLOCK_PCLK_EN_SSP3);
#endif
    /* Enable all interrupts in MCU. */
    IT_GlobalEnableIRQ();
    PLIC_EnableExternalIRQ(PLIC_PRIVILEGE_IRQ_MODE_M);

#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
#if defined(CLIC_SYSTEM_INIT)
    CLIC_InitTypeDef     CLIC_InitStruct;
    CLIC_IRQ_InitTypeDef CLIC_InitStructIRQ;
#endif

    IT_GlobalDisableIRQ(IT_PRIVILEGE_MODE_IRQ_M);
#if defined(CLIC_SYSTEM_INIT)
    /* Initializing CLIC global parameters. */
    CLIC_InitStruct.CLIC_PrivilegeLevels = CLIC_SYSTEM_INIT_PRIVILEGE_LEVELS;
    CLIC_InitStruct.CLIC_MaxLevels       = CLIC_SYSTEM_INIT_MAX_LEVELS;
    CLIC_Init(&CLIC_InitStruct);
    /* Initializing CLIC IRQ parameters. */
    CLIC_InitStructIRQ.CLIC_EnableIRQ        = DISABLE;
    CLIC_InitStructIRQ.CLIC_TriggerIRQ       = CLIC_SYSTEM_INIT_TRIGGER_IRQ;
    CLIC_InitStructIRQ.CLIC_PrivilegeModeIRQ = CLIC_SYSTEM_INIT_PRIVILEGE_MODE_IRQ;
#if defined(CLIC_SYSTEM_INIT_VECTOR_MODE_IRQ)
    CLIC_InitStructIRQ.CLIC_VectorModeIRQ = ENABLE;
#else
    CLIC_InitStructIRQ.CLIC_VectorModeIRQ = DISABLE;
#endif
    CLIC_InitStructIRQ.CLIC_LevelIRQ    = 1;
    CLIC_InitStructIRQ.CLIC_PriorityIRQ = 1;
    CLIC_InitAllIRQ(&CLIC_InitStructIRQ);
    /* Set rising edge triggering for DMA interrupt. */
    CLIC_InitStructIRQ.CLIC_TriggerIRQ = CLIC_TRIGGER_IRQ_EDGE_RISING;
    CLIC_InitIRQ(DMA_IRQn, &CLIC_InitStructIRQ);
#endif
    CLIC_SetTrapVector(CLIC_PRIVILEGE_MODE_IRQ_M, (IRQHandler_TypeDef)Trap_IRQHandler);
    CLIC_SetVectorTable(CLIC_PRIVILEGE_MODE_IRQ_M, InterruptVectorTable);
    IT_GlobalEnableIRQ(IT_PRIVILEGE_MODE_IRQ_M);
#endif
}

/**
 * @brief  Setup the RISC-V cycle counter.
 * @param  None.
 * @return None.
 */
__STATIC_FORCEINLINE void SystemInitCycleCounter(void)
{
    CSR_SetBits(CSR_MCOUNTEREN, CSR_MCOUNTEREN_CY);
#if defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    CSR_ClearBits(CSR_MCOUNTINHIBIT, CSR_MCOUNTINHIBIT_CY);
#endif
}

#if defined(FACTORY_DATA_SYSTEM_INIT)
/**
 * @brief  Setup the microcontroller trim values from factory data.
 * @param  None.
 * @return None.
 */
__STATIC_FORCEINLINE void SystemInitTrim(void)
{
    uint32_t Per2Clk, BKPKey, BKPData;
#if defined(USE_MDR32F02)
    Per2Clk                 = MDR_RST_CLK->PER2_CLOCK;
    MDR_RST_CLK->PER2_CLOCK = Per2Clk | RST_CLK_PER2_CLOCK_PCLK_EN_BKP;
    BKPKey                  = MDR_BKP->WPR;
    if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
        MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
    }

    BKPData = MDR_BKP->CLK;
    BKPData &= ~(BKP_CLK_HSI_LSI_TRIM_Msk);
    BKPData |= ((OTP_SPECIAL_FIELDS->HSI_TRIM << BKP_CLK_HSI_LSI_TRIM_Pos) & BKP_CLK_HSI_LSI_TRIM_Msk);
    MDR_BKP->CLK = BKPData;

    if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
        MDR_BKP->WPR = BKPKey;
    }
    MDR_RST_CLK->PER2_CLOCK = Per2Clk;
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    uint8_t                          CalcTrimCS = 0;
    uint32_t                         Index;
    MDR_FLASH_SpecialFields_TypeDef* FlashFactoryData;
#if defined(USE_MDR1206)
    uint32_t ChipID;
    Per2Clk                 = MDR_RST_CLK->PER2_CLOCK;
    MDR_RST_CLK->PER2_CLOCK = Per2Clk | RST_CLK_PER2_CLOCK_PCLK_EN_FLASH;
    ChipID                  = MDR_FLASH->CHIP_ID_CTRL & FLASH_CHIP_ID_CTRL_CHIP_ID_Msk;
    MDR_RST_CLK->PER2_CLOCK = Per2Clk;

    if (ChipID == FLASH_CHIP_ID_CTRL_CHIP_ID217) {
        FlashFactoryData = MDR_FLASH_SPECIAL_FIELDS_MDR1206FI;
    } else {
        FlashFactoryData = MDR_FLASH_SPECIAL_FIELDS_MDR1206AFI;
    }
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI)
    FlashFactoryData = MDR_FLASH_SPECIAL_FIELDS;
#endif

    for (Index = 0; Index < 5; Index++) {
        CalcTrimCS += (uint8_t)(FlashFactoryData->UNIQUE_ID[Index] >> 0);
        CalcTrimCS += (uint8_t)(FlashFactoryData->UNIQUE_ID[Index] >> 8);
        CalcTrimCS += (uint8_t)(FlashFactoryData->UNIQUE_ID[Index] >> 16);
        CalcTrimCS += (uint8_t)(FlashFactoryData->UNIQUE_ID[Index] >> 24);
    }
    CalcTrimCS += FlashFactoryData->TRIM_HSI;
    CalcTrimCS += FlashFactoryData->TRIM_BG;
    CalcTrimCS += FlashFactoryData->TRIM_LDO;
    CalcTrimCS += FlashFactoryData->TRIM_TS;

    if (CalcTrimCS == FlashFactoryData->TRIM_CS) {
        Per2Clk                 = MDR_RST_CLK->PER2_CLOCK;
        MDR_RST_CLK->PER2_CLOCK = Per2Clk | RST_CLK_PER2_CLOCK_PCLK_EN_BKP | RST_CLK_PER2_CLOCK_PCLK_EN_ADC;
        BKPKey                  = MDR_BKP->WPR;
        if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
        }

        BKPData = MDR_BKP->CLK;
        BKPData &= ~(BKP_CLK_HSI_LSI_TRIM_Msk);
        BKPData |= ((FlashFactoryData->TRIM_HSI << BKP_CLK_HSI_LSI_TRIM_Pos) & BKP_CLK_HSI_LSI_TRIM_Msk);
        MDR_BKP->CLK = BKPData;

        BKPData = MDR_BKP->LDO;
        BKPData &= ~(BKP_LDO_LDO_BOOST_Msk | BKP_LDO_SW_OFF_Msk | BKP_LDO_TAMPF_Msk);
        BKPData |= ((FlashFactoryData->TRIM_LDO << BKP_LDO_LDO_BOOST_Pos) & BKP_LDO_LDO_BOOST_Msk);
        MDR_BKP->LDO = BKPData;

        MDR_ADC->ADC_TRIM = ((FlashFactoryData->TRIM_BG << ADC_TRIM_BG_TRIM_Pos) & ADC_TRIM_BG_TRIM_Msk);

        if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKPKey;
        }
        MDR_RST_CLK->PER2_CLOCK = Per2Clk;
    } else {
        Per2Clk                 = MDR_RST_CLK->PER2_CLOCK;
        MDR_RST_CLK->PER2_CLOCK = Per2Clk | RST_CLK_PER2_CLOCK_PCLK_EN_BKP | RST_CLK_PER2_CLOCK_PCLK_EN_ADC;
        BKPKey                  = MDR_BKP->WPR;
        if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
        }

        BKPData = MDR_BKP->CLK;
        BKPData &= ~(BKP_CLK_HSI_LSI_TRIM_Msk);
#if defined(USE_MDR1206)
        if (ChipID == FLASH_CHIP_ID_CTRL_CHIP_ID217) {
            BKPData |= (TRIM_HSI_MDR1206FI_VALUE_TYP << BKP_CLK_HSI_LSI_TRIM_Pos);
        } else {
            BKPData |= (TRIM_HSI_MDR1206AFI_VALUE_TYP << BKP_CLK_HSI_LSI_TRIM_Pos);
        }
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI)
        BKPData |= (TRIM_HSI_VALUE_TYP << BKP_CLK_HSI_LSI_TRIM_Pos);
#endif
        MDR_BKP->CLK = BKPData;

#if defined(USE_MDR1206)
        if (ChipID == FLASH_CHIP_ID_CTRL_CHIP_ID217) {
            MDR_ADC->ADC_TRIM = (TRIM_BG_MDR1206FI_VALUE_TYP << ADC_TRIM_BG_TRIM_Pos);
        } else {
            MDR_ADC->ADC_TRIM = (TRIM_BG_MDR1206AFI_VALUE_TYP << ADC_TRIM_BG_TRIM_Pos);
        }
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI)
        MDR_ADC->ADC_TRIM = (TRIM_BG_VALUE_TYP << ADC_TRIM_BG_TRIM_Pos);
#endif

        if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKPKey;
        }
        MDR_RST_CLK->PER2_CLOCK = Per2Clk;
    }
#endif
}
#endif

#if defined(WORKAROUND_ERROR_BLDO_NOT_OPERATED)
/**
 * @brief  Apply microcontroller errors workarounds.
 * @note   For WORKAROUND_ERROR_BLDO_NOT_OPERATED for delay assume that it is only valid after power up, i.e. clock frequency is default.
 * @param  None.
 * @return None.
 */
__STATIC_FORCEINLINE void SystemInitWorkaround(void)
{
    uint32_t Per2Clk, Temp1, BKPKey;

    Per2Clk                 = MDR_RST_CLK->PER2_CLOCK;
    MDR_RST_CLK->PER2_CLOCK = Per2Clk | RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Msk | RST_CLK_PER2_CLOCK_PCLK_EN_POWER_Msk;

    MDR_POWER->PVDCS &= ~(POWER_PVDCS_PLS_Msk);
    MDR_POWER->PVDCS |= (POWER_PVDCS_PVDEN);

    MDR_POWER->PVDCS &= ~(POWER_PVDCS_PVD);
    MDR_POWER->PVDCS &= ~(POWER_PVDCS_PVD);

    Temp1 = (MDR_POWER->PVDCS & POWER_PVDCS_PVD);

    MDR_RST_CLK->PER2_CLOCK = Per2Clk | RST_CLK_PER2_CLOCK_PCLK_EN_BKP_Msk;

    if (Temp1 == POWER_PVDCS_PVD) {
        BKPKey = MDR_BKP->WPR;
        if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKP_WPR_BKP_WPR_UNLOCK;
        }

        Temp1 = MDR_BKP->LDO;
        Temp1 &= ~(BKP_LDO_SW_OFF_Msk | BKP_LDO_TAMPF_Msk);
        Temp1 |= BKP_LDO_BLDO_BOOST;
        MDR_BKP->LDO = Temp1;

        DelayCoreClockDefault();

        Temp1 &= ~BKP_LDO_BLDO_BOOST;
        MDR_BKP->LDO = Temp1;

        if (BKPKey != BKP_WPR_BKP_WPR_UNLOCK) {
            MDR_BKP->WPR = BKPKey;
        }
    } else {
        DelayCoreClockDefault();
    }
    MDR_RST_CLK->PER2_CLOCK = Per2Clk;
}

/**
 * @brief  Perform a blocking program delay in loops at default clock frequency.
 * @param  None.
 * @return None.
 */
static void DelayCoreClockDefault(void)
{
    register uint32_t Loops asm("a0");
#if defined(USE_MDR32F02)
    Loops = 205; // At 8 MHz.
#elif defined(USE_MDR1206FI) || defined(USE_MDR1206AFI) || defined(USE_MDR1206)
    Loops = 6; // At 500 kHz.
#endif
    __ASM volatile(
        "1:\n"
        "addi %0, %0, -1\n"
        "bnez %0, 1b\n" : "+r"(Loops) : :);
}
#endif

/** @} */ /* End of group MDR32VF0xI_System_Private_Functions */

/** @} */ /* End of group MDR32VF0xI_System */

/** @} */ /* End of group MDR32VF0xI_DEVICE */

/** @} */ /* End of group DEVICE_SUPPORT */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE system_MDR32VF0xI.c */

