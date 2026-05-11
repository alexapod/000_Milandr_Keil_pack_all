/**
 ******************************************************************************
 * @file    MDR32F2xQI_utils.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
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
#include "MDR32F2xQI_utils.h"
#if (USE_STDIO_RETARGET != 0)
#include "MDR32F2xQI_rst_clk.h"
#include "MDR32F2xQI_port.h"
#include "MDR32F2xQI_uart.h"
#include <stdio.h>
#endif

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @addtogroup UTILS UTILS
 * @{
 */

/** @defgroup UTILS_Private_Variables UTILS Private Variables
 * @{
 */

/** @defgroup UTILS_DELAY_Private_Variables UTILS DELAY
 * @{
 */

static uint32_t DelayMode = DELAY_MODE_PROGRAM;

static uint32_t DelayProgramConstUs = DELAY_PROGRAM_GET_CONST_US(HSI_FREQUENCY_Hz);
static uint32_t DelayProgramConstMs = DELAY_PROGRAM_GET_CONST_MS(HSI_FREQUENCY_Hz);

static uint32_t DelaySysTickConstUs = DELAY_SYSTICK_GET_CONST_US(HSI_FREQUENCY_Hz);
static uint32_t DelaySysTickConstMs = DELAY_SYSTICK_GET_CONST_MS(HSI_FREQUENCY_Hz);

/** @} */ /* End of group UTILS_DELAY_Private_Variables */

/** @defgroup UTILS_STDIO_Private_Variables UTILS STDIO
 * @{
 */
#if (USE_STDIO_RETARGET != 0)
#if defined(__ARMCC_VERSION) /* ARM Compiler */
#if defined(__CC_ARM)        /* ARM Compiler 5 */
struct __FILE {
    int handle;
};
#endif /* __CC_ARM */
FILE __stdout;
FILE __stdin;
#endif    /* __ARMCC_VERSION */
#endif    /* USE_STDIO_RETARGET */

/** @} */ /* End of group UTILS_STDIO_Private_Variables */

/** @} */ /* End of group UTILS_Private_Variables */

/** @defgroup UTILS_Private_Defines UTILS Private Defines
 * @{
 */

/** @defgroup UTILS_STDIO_Private_Defines UTILS STDIO
 * @{
 */

#define STDIO_PUTCHAR                int fputc(int ch, FILE* f)
#define STDIO_GETCHAR                int fgetc(FILE* f)

#define IS_STDIO_UART_PERIPH(PERIPH) (((PERIPH) == MDR_UART0) || \
                                      ((PERIPH) == MDR_UART1))

/** @} */ /* End of group UTILS_STDIO_Private_Defines */

/** @} */ /* End of group UTILS_Private_Defines */

/** @defgroup UTILS_Private_Types UTILS Private Types
 * @{
 */

/** @defgroup UTILS_STDIO_Private_Types UTILS STDIO
 * @{
 */
#if (USE_STDIO_RETARGET == 1)
/**
 * @brief  STDIO UART Init Structure definition
 */
typedef struct
{
    uint32_t STDIO_UART_BaudRate;                      /*!< This member configures the UART communication baud rate.
                                                            The baud rate is computed using the following formula:
                                                             - IntegerDivider = ((UARTCLK) / (16 * (UART_BaudRate)))
                                                             - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 64) + 0.5 */
    UART_WordLength_TypeDef STDIO_UART_WordLength;     /*!< Specifies the number of data bits transmitted or received in a frame.
                                                            This parameter can be a value of @ref UART_WordLength_TypeDef */
    UART_StopBits_TypeDef STDIO_UART_StopBits;         /*!< Specifies the number of stop bits transmitted.
                                                            This parameter can be a value of @ref UART_StopBits_TypeDef */
    UART_Parity_TypeDef STDIO_UART_Parity;             /*!< Specifies the parity mode.
                                                            This parameter can be a value of @ref UART_Parity_TypeDef */
    RST_CLK_PER1_C2_TypeDef STDIO_UART_PER1_C2_Source; /*!< Specifies the PER1_C2 clock source for UART.
                                                            This parameter is one of @ref RST_CLK_PER1_C2_TypeDef values. */
} STDIO_UART_InitTypeDef;
#endif

/** @} */ /* End of group UTILS_STDIO_Private_Types */

/** @} */ /* End of group UTILS_Private_Types */

/** @defgroup UTILS_Private_Function_Prototypes UTILS Private Functions Prototypes
 * @{
 */

/** @defgroup UTILS_DELAY_Private_Function_Prototypes UTILS DELAY
 * @{
 */

void DELAY_SYSTICK_Init(void);
void DELAY_SYSTICK_WaitTicks(uint32_t Ticks);

/** @} */ /* End of group UTILS_DELAY_Private_Function_Prototypes */

/** @defgroup UTILS_STDIO_Private_Function_Prototypes UTILS STDIO
 * @{
 */

#if (USE_STDIO_RETARGET == 1)
ErrorStatus STDIO_UartInit(MDR_UART_TypeDef* STDIO_UARTx, STDIO_UART_InitTypeDef* STDIO_UART_InitStruct);
#endif

/** @} */ /* End of group UTILS_STDIO_Private_Function_Prototypes */

/** @} */ /* End of group UTILS_Private_Function_Prototypes */

/** @addtogroup UTILS_Exported_Functions UTILS Exported Functions
 * @{
 */

/** @addtogroup UTILS_LOW_POWER_Exported_Functions UTILS LOW POWER
 * @{
 */

/**
 * @brief  Enters SLEEP mode.
 * @param  SleepMode - @ref LOW_POWER_Mode_TypeDef - specifies
 *         the low power mode: Sleep or Sleepdeep.
 * @param  EntryMode - @ref LOW_POWER_Mode_Entry_TypeDef - specifies
 *         entry into SLEEP mode with a WFE or WFI instruction.
 * @retval None.
 */
void LOW_POWER_EnterSLEEPMode(LOW_POWER_Mode_TypeDef SleepMode, LOW_POWER_Mode_Entry_TypeDef EntryMode)
{
    /* Check the parameters */
    assert_param(IS_LOW_POWER_MODE(SleepMode));
    assert_param(IS_LOW_POWER_MODE_ENTRY(EntryMode));

    /* Select sleep mode with SLEEPDEEP bit of Core System Control Register */
    if (SleepMode == LOW_POWER_MODE_SLEEPDEEP) {
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    } else {
        SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    }

    /* Select sleep entry mode */
    if (EntryMode == LOW_POWER_MODE_ENTRY_WFE) {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    } else {
        /* Request Wait For Interrupt */
        __WFI();
    }
}

/**
 * @brief  Enables or disables Sleep-On-Exit feature when returning from Handler mode to Thread mode.
 * @param  NewState - @ref FunctionalState - new state of SLEEPONEXIT bit.
 * @retval None.
 */
void LOW_POWER_SleepOnExit(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    } else {
        SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
    }
}

/**
 * @brief  Enables or disables wakeup from sleep (WFE) when any interrupt goes from inactive to pending.
 * @param  NewState - @ref FunctionalState - new state of SEVONPEND bit.
 * @retval None.
 */
void LOW_POWER_SEVOnPend(FunctionalState NewState)
{
    /* Check the parameter */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form new value */
    if (NewState != DISABLE) {
        SCB->SCR |= SCB_SCR_SEVONPEND_Msk;
    } else {
        SCB->SCR &= ~SCB_SCR_SEVONPEND_Msk;
    }
}

/** @} */ /* End of group UTILS_LOW_POWER_Exported_Functions */

/** @addtogroup UTILS_DELAY_Exported_Functions UTILS DELAY
 * @{
 */

/**
 * @brief  Initializes the DELAY module according to the specified mode.
 * @note   The core clock from SystemCoreClock is used to calculate the delay time.
 *         Before calling DELAY_Init(), you must configure the required core clock and call SystemCoreClockUpdate().
 * @param  Mode - @ref DELAY_Mode_TypeDef - specifies the Delay mode.
 * @retval None.
 */
void DELAY_Init(DELAY_Mode_TypeDef Mode)
{
    assert_param(IS_DELAY_MODE(Mode));

    DelayMode = Mode;

    switch (DelayMode) {
        case DELAY_MODE_PROGRAM:
            DelayProgramConstUs = DELAY_PROGRAM_GET_CONST_US(SystemCoreClock);
            DelayProgramConstMs = DELAY_PROGRAM_GET_CONST_MS(SystemCoreClock);
            break;
        case DELAY_MODE_SYSTICK:
            DELAY_SYSTICK_Init();
            DelaySysTickConstUs = DELAY_SYSTICK_GET_CONST_US(SystemCoreClock);
            DelaySysTickConstMs = DELAY_SYSTICK_GET_CONST_MS(SystemCoreClock);
            break;
    }
}

/**
 * @brief  Performs a blocking delay in microseconds.
 * @param  Us: specifies the delay time in microseconds.
 *         This parameter can be a value:
 *         - DELAY_MODE_PROGRAM: Us <= 16785412 / CPU_CLK (MHz);
 *         - DELAY_MODE_SYSTICK: Us <= 4294967295 / CPU_CLK (MHz).
 * @retval None.
 */
void DELAY_WaitUs(uint32_t Us)
{
    switch (DelayMode) {
        case DELAY_MODE_PROGRAM:
            DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_US_LOOPS(Us, DelayProgramConstUs));
            break;
        case DELAY_MODE_SYSTICK:
            DELAY_SYSTICK_WaitTicks(DELAY_SYSTICK_GET_TICKS(Us, DelaySysTickConstUs));
            break;
    }
}

/**
 * @brief  Performs a blocking delay in milliseconds.
 * @param  Ms: specifies the delay time in milliseconds.
 *         This parameter can be a value:
 *         - DELAY_MODE_PROGRAM: Ms <= 17179869 / CPU_CLK (MHz);
 *         - DELAY_MODE_SYSTICK: Ms <= 4294967 / CPU_CLK (MHz).
 * @retval None.
 */
void DELAY_WaitMs(uint32_t Ms)
{
    switch (DelayMode) {
        case DELAY_MODE_PROGRAM:
            DELAY_PROGRAM_WaitLoopsAsm(DELAY_PROGRAM_GET_MS_LOOPS(Ms, DelayProgramConstMs));
            break;
        case DELAY_MODE_SYSTICK:
            DELAY_SYSTICK_WaitTicks(DELAY_SYSTICK_GET_TICKS(Ms, DelaySysTickConstMs));
            break;
    }
}

/** @} */ /* End of group UTILS_DELAY_Exported_Functions */

/** @addtogroup UTILS_STDIO_Exported_Functions UTILS STDIO
 * @{
 */

#if (USE_STDIO_RETARGET != 0)
/**
 * @brief  Initializes the peripheral selected in USE_STDIO_RETARGET (MDR32F2xQI_config.h) for standard input/output.
 * @param  None.
 * @retval @ref ErrorStatus - Peripheral device initialization status.
 */
ErrorStatus STDIO_Init(void)
{
    ErrorStatus Status = ERROR;
#if (USE_STDIO_RETARGET == 1)
    STDIO_UART_InitTypeDef STDIO_UART_InitStruct;

    STDIO_UART_InitStruct.STDIO_UART_BaudRate       = STDIO_UART_BAUD_RATE;
    STDIO_UART_InitStruct.STDIO_UART_WordLength     = STDIO_UART_WORD_LENGTH;
    STDIO_UART_InitStruct.STDIO_UART_StopBits       = STDIO_UART_STOP_BITS;
    STDIO_UART_InitStruct.STDIO_UART_Parity         = STDIO_UART_PARITY;
    STDIO_UART_InitStruct.STDIO_UART_PER1_C2_Source = STDIO_UART_CLK_SRC;

    Status = STDIO_UartInit(STDIO_UART, &STDIO_UART_InitStruct);
#endif

    return Status;
}

#if (USE_STDIO_RETARGET == 1)
/**
 * @brief  Writes the character specified by ch (converted to uint8_t) to the UART FIFOTX.
 * @param  ch: Character.
 * @param  f:  Stream handle.
 * @retval ch: The character written.
 */
STDIO_PUTCHAR
{
    /* Wait until there is enough space in TX buffer */
    while (UART_GetFlagStatus(STDIO_UART, UART_FLAG_TXFF) == SET) { }
    UART_SendData(STDIO_UART, (uint8_t)ch);

    return ch;
}

/**
 * @brief  Obtains the next character (converted to uint8_t) from the UART FIFORX.
 * @param  f:  Stream handle.
 * @retval ch: The next character from the UART FIFORX.
 */
STDIO_GETCHAR
{
    /* Wait until a character is received */
    while (UART_GetFlagStatus(STDIO_UART, UART_FLAG_RXFE) == SET) { }

    return UART_DATA(UART_ReceiveData(STDIO_UART));
}
#endif
#endif

/** @} */ /* End of group UTILS_STDIO_Exported_Functions */

/** @} */ /* End of group UTILS_Exported_Functions */

/** @defgroup UTILS_Private_Functions UTILS Private Functions
 * @{
 */

/** @defgroup UTILS_DELAY_Private_Functions UTILS DELAY
 * @{
 */

/**
 * @brief  Initializes and starts the System Tick Timer. The System Tick Timer is clocked at the core clock.
 * @param  None.
 * @retval None.
 */
void DELAY_SYSTICK_Init(void)
{
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
    SysTick->VAL  = 0UL;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief  Performs a blocking delay with a System Tick Timer in ticks.
 * @param  Ticks: specifies the delay time in ticks.
 * @retval None.
 */
void DELAY_SYSTICK_WaitTicks(uint32_t Ticks)
{
    uint32_t NumOfReloads;

    SysTick->LOAD = Ticks;
    SysTick->VAL  = 0UL;
    NumOfReloads  = Ticks >> 24;
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) { }

    if (NumOfReloads) {
        SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
        SysTick->VAL  = 0UL;
        while (NumOfReloads--) {
            while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) { }
        }
    }
}

/** @} */ /* End of group UTILS_DELAY_Private_Functions */

/** @defgroup UTILS_STDIO_Private_Functions UTILS STDIO
 * @{
 */

#if (USE_STDIO_RETARGET == 1)
/**
 * @brief  Initializes the UARTx peripheral according to the specified
 *         parameters STDIO_UART in MDR32F2xQI_config.h for standard input/output.
 * @param  STDIO_UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values: MDR_UART0, MDR_UART1.
 * @param  STDIO_UART_InitStruct: pointer to a @ref STDIO_UART_InitTypeDef structure
 *         that contains the configuration information for the specified UART peripheral.
 * @retval @ref ErrorStatus - The UARTx peripheral initialization status.
 */
ErrorStatus STDIO_UartInit(MDR_UART_TypeDef* STDIO_UARTx, STDIO_UART_InitTypeDef* STDIO_UART_InitStruct)
{
    PORT_InitTypeDef          PORT_InitStructure;
    UART_InitTypeDef          UART_InitStructure;
    RST_CLK_PER1_C2_X_TypeDef PER1_C2_UARTx = RST_CLK_PER1_C2_UART0;
    MDR_PORT_TypeDef*         PORTx         = MDR_PORTB;
    ErrorStatus               Status        = ERROR;

    /* Check the parameters */
    assert_param(IS_STDIO_UART_PERIPH(STDIO_UARTx));
    assert_param(IS_UART_BAUDRATE(STDIO_UART_InitStruct->STDIO_UART_BaudRate));
    assert_param(IS_UART_WORD_LENGTH(STDIO_UART_InitStruct->STDIO_UART_WordLength));
    assert_param(IS_UART_STOP_BITS(STDIO_UART_InitStruct->STDIO_UART_StopBits));
    assert_param(IS_UART_PARITY(STDIO_UART_InitStruct->STDIO_UART_Parity));
    assert_param(IS_RST_CLK_PER1_C2_CLK_SOURCE(STDIO_UART_InitStruct->STDIO_UART_PER1_C2_Source));

    /* Configure STDIO UART Pins */
    if (STDIO_UARTx == MDR_UART0) {
        RST_CLK_PCLKCmd(RST_CLK_PCLK_PORTB, ENABLE);
        PORTx = MDR_PORTB;
    } else if (STDIO_UARTx == MDR_UART1) {
        RST_CLK_PCLKCmd(RST_CLK_PCLK_PORTC, ENABLE);
        PORTx = MDR_PORTC;
    }

    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin      = PORT_PIN_0 | PORT_PIN_1;
    PORT_InitStructure.PORT_Mode     = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_Function = PORT_FUNCTION_MAIN;
    PORT_InitStructure.PORT_Power    = PORT_POWER_SPEED_MAXFAST;

    PORT_Init(PORTx, &PORT_InitStructure);

    /* Configure STDIO UART */
    if (STDIO_UARTx == MDR_UART0) {
        RST_CLK_PCLKCmd(RST_CLK_PCLK_UART0, ENABLE);
        PER1_C2_UARTx = RST_CLK_PER1_C2_UART0;
    } else if (STDIO_UARTx == MDR_UART1) {
        RST_CLK_PCLKCmd(RST_CLK_PCLK_UART1, ENABLE);
        PER1_C2_UARTx = RST_CLK_PER1_C2_UART1;
    }
#if defined(USE_MDR32F21QI)
    RST_CLK_PER1_C2_ClkSelection(STDIO_UART_InitStruct->STDIO_UART_PER1_C2_Source);
#elif defined(USE_MDR32F23QI)
    RST_CLK_PER1_C2_ClkSelection(PER1_C2_UARTx, STDIO_UART_InitStruct->STDIO_UART_PER1_C2_Source);
#endif
    RST_CLK_PER1_C2_SetPrescaler(PER1_C2_UARTx, RST_CLK_PER1_PRESCALER_DIV_1);
    RST_CLK_PER1_C2_Cmd(PER1_C2_UARTx, ENABLE);

    UART_DeInit(STDIO_UARTx);

    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.UART_BaudRate   = STDIO_UART_InitStruct->STDIO_UART_BaudRate;
    UART_InitStructure.UART_WordLength = STDIO_UART_InitStruct->STDIO_UART_WordLength;
    UART_InitStructure.UART_StopBits   = STDIO_UART_InitStruct->STDIO_UART_StopBits;
    UART_InitStructure.UART_Parity     = STDIO_UART_InitStruct->STDIO_UART_Parity;
    UART_InitStructure.UART_FIFO_State = UART_FIFO_ENABLE;

    Status = UART_Init(STDIO_UARTx, &UART_InitStructure);

    if (Status == SUCCESS) {
        UART_Cmd(STDIO_UARTx, ENABLE);
    }

    return Status;
}
#endif    /* USE_STDIO_RETARGET */

/** @} */ /* End of group UTILS_STDIO_Private_Functions */

/** @} */ /* End of group UTILS_Private_Functions */

/** @} */ /* End of group UTILS */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_utils.c */

