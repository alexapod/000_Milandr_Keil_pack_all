/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    06/06/2025
 * @brief   Main program body.
 ******************************************************************************
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 */

/** @addtogroup MDR32VF0xI_StdPeriph_Examples MDR32VF0xI StdPeriph Examples
 * @{
 */
 
/** @addtogroup MDR32VF0xI_MDR1206FI_BOARD MDR1206FI Evaluation Board
 * @{
 */
 
/** @addtogroup RTOS RTOS
 * @{
 */

 /** @addtogroup MDR32VF0xI_FreeRTOS_Led MDR32VF0xI_FreeRTOS_Led
 * @{
 */
 
/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"
#include "system_MDR32VF0xI_it.h"
#include <MDR32VF0xI_port.h>
#include <MDR32VF0xI_timer.h>
#include <MDR32VF0xI_flash.h>
#include "FreeRTOS.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Private definitions ------------------------------------------------------------*/
#define LED_PORT     MDR_PORTD
#define LED_PORT_CLK RST_CLK_PCLK_PORTD

#if defined (USE_MDR1206) || defined (USE_MDR1206FI) || defined(USE_MDR1206AFI)
#define LED_PIN_1    PORT_PIN_5
#define LED_PIN_2    PORT_PIN_6
#define LED_PIN_3    PORT_PIN_7
#define LED_PIN_4    PORT_PIN_8
#elif defined (USE_MDR32F02_REV_1X) || defined (USE_MDR32F02_REV_2)
#define LED_PIN_1    PORT_PIN_0
#define LED_PIN_2    PORT_PIN_1
#define LED_PIN_3    PORT_PIN_2
#define LED_PIN_4    PORT_PIN_3
#endif

/* Private functions prototypes ---------------------------------------------*/
void freertos_risc_v_trap_handler(void);
void freertos_risc_v_mtimer_interrupt_handler(void);
void blink_task(void* parameters);
void CLK_Init(void);
void LED_Init(void);
void TIMER1_Init(void);
#if defined (USE_MDR1206) || defined (USE_MDR1206FI) || defined(USE_MDR1206AFI)
void CLIC_FreeRTOS_Init(void);
#elif defined (USE_MDR32F02_REV_1X) || defined (USE_MDR32F02_REV_2)
void PLIC_FreeRTOS_Init(void);
#endif

/* Private variables ---------------------------------------------------------*/
static QueueHandle_t xQueue = NULL;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Timer interrupt handler.
 * @param  None.
 * @return None.
 */
__INTERRUPT_MACHINE void TIMER1_IRQHandler(void)
{
    TIMER_ClearFlags(MDR_TIMER1, TIMER_FLAG_CNT_ARR);
    PORT_ToggleBit(LED_PORT, LED_PIN_3 | LED_PIN_4);
}

/**
 * @brief  FreeRTOS Task.
 * @param  Specific parameters.
 * @return None.
 */
void blink_task(void* parameters)
{
    (void)parameters;

    while (1) {
        vTaskDelay(100);
        PORT_SetBits(LED_PORT, LED_PIN_1 | LED_PIN_2);
        vTaskDelay(100);
        PORT_ResetBits(LED_PORT, LED_PIN_1 | LED_PIN_2);
    }
}

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main()
{
    CLK_Init();

#if defined (USE_MDR1206) || defined (USE_MDR1206FI) || defined(USE_MDR1206AFI)
    CLIC_FreeRTOS_Init();
#elif defined (USE_MDR32F02_REV_1X) || defined (USE_MDR32F02_REV_2)
    PLIC_FreeRTOS_Init();
#endif

    LED_Init();
    TIMER1_Init();

    xQueue = xQueueCreate(1, sizeof(uint32_t));

    if (xQueue != NULL) {
        /* Start the two tasks as described in the comments at the top of this file. */
        xTaskCreate(blink_task,                    /* The function that implements the task. */
                    "blink1",                      /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                    configMINIMAL_STACK_SIZE * 2U, /* The size of the stack to allocate to the task. */
                    NULL,                          /* The parameter passed to the task - not used in this case. */
                    (tskIDLE_PRIORITY + 1),        /* The priority assigned to the task. */
                    NULL);
        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    while (1) { }
}

/**
 * @brief  Initialization of clocking.
 * @param  None.
 * @return None.
 */
void CLK_Init(void)
{
    RST_CLK_DeInit();
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_HSI);

    RST_CLK_HSE_Cmd(ENABLE);
    while (RST_CLK_HSE_GetStatus() != SUCCESS) { }

    RST_CLK_CPU_PLL_Config(RST_CLK_PLLCPU_CLK_SRC_CPU_C1, RST_CLK_PLLCPU_MUL_5); // 40 MHz
    RST_CLK_CPU_PLL_Cmd(ENABLE);
    while (RST_CLK_CPU_PLL_GetStatus() != SUCCESS) { }

    FLASH_SetLatency(FLASH_LATENCY_CYCLE_1);

    RST_CLK_CPU_C2_ClkSelection(RST_CLK_CPU_C2_CLK_SRC_PLLCPU);
    RST_CLK_CPU_C3_SetPrescaler(RST_CLK_CPU_C3_PRESCALER_DIV_1);
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_CPU_C3);

    SystemCoreClockUpdate();
}

/**
 * @brief  Interrupt initialization function for FreeRTOS operation.
 * @param  None.
 * @return None.
 */
#if defined (USE_MDR1206) || defined (USE_MDR1206FI) || defined(USE_MDR1206AFI)
void CLIC_FreeRTOS_Init(void)
{
    IT_GlobalDisableIRQ(IT_PRIVILEGE_MODE_IRQ_M);

    /* FreeRTOS: override the trap handler.*/
    CLIC_SetTrapVector(CLIC_PRIVILEGE_MODE_IRQ_M, freertos_risc_v_trap_handler);
    /* FreeRTOS: override the machine timer interrupt handler.*/
    InterruptVectorTable[MTIP_IRQn] = freertos_risc_v_mtimer_interrupt_handler;

    IT_GlobalEnableIRQ(IT_PRIVILEGE_MODE_IRQ_M);
}
#elif defined (USE_MDR32F02_REV_1X) || defined (USE_MDR32F02_REV_2)
void PLIC_FreeRTOS_Init(void)
{
    IT_GlobalDisableIRQ();

    /* FreeRTOS: override the trap handler.*/
    PLIC_SetTrapVector(PLIC_PRIVILEGE_IRQ_MODE_M, freertos_risc_v_trap_handler);
    /* FreeRTOS: override the machine timer interrupt handler.*/
    InterruptVectorTable[7] = freertos_risc_v_mtimer_interrupt_handler;

    IT_GlobalEnableIRQ();
}
#endif

/**
 * @brief  LEDs configuration.
 * @param  None.
 * @return None.
 */
void LED_Init(void)
{
    static const PORT_InitTypeDef PORT_LED_InitStructure = {
        .PORT_Pin       = (LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4),
        .PORT_Direction = PORT_DIRECTION_OUTPUT,
        .PORT_Function  = PORT_FUNCTION_PORT,
        .PORT_Mode      = PORT_MODE_DIGITAL,
        .PORT_Power     = PORT_POWER_NOMINAL_UPTO_2mA,
        .PORT_PullUp    = PORT_PULL_UP_OFF,
        .PORT_PullDown  = PORT_PULL_DOWN_OFF
    };

    RST_CLK_PCLKCmd(LED_PORT_CLK, ENABLE);
    PORT_SetBits(LED_PORT, (LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4));
    PORT_Init(LED_PORT, &PORT_LED_InitStructure);
}

/**
 * @brief  Initialization of timer.
 * @param  None.
 * @return None.
 */
void TIMER1_Init(void)
{
    static const TIMER_CNT_InitTypeDef TIMER1_CNT_InitStructure = {
        .TIMER_CNT_Counter          = 0,
        .TIMER_CNT_Prescaler        = 0,
        .TIMER_CNT_Period           = (uint32_t)(8E6 - 1),
        .TIMER_CNT_EventSource      = TIMER_CNT_EVNT_SRC_TIM_CLK,
        .TIMER_CNT_Mode             = TIMER_CNT_MODE_CLK_FIXED_DIR,
        .TIMER_CNT_Direction        = TIMER_CNT_DIR_UP,
        .TIMER_CNT_PeriodUpdateMode = TIMER_CNT_PERIOD_UPD_IMMEDIATELY,
        .TIMER_FDTS_Prescaler       = TIMER_FDTS_PRESCALER_DIV_1,
        .TIMER_ETR_Filter           = TIMER_ETR_FILTER_1FF_AT_FDTS,
        .TIMER_ETR_Prescaler        = TIMER_ETR_PRESCALER_DIV_1,
        .TIMER_ETR_Polarity         = TIMER_ETR_POLARITY_NON_INV,
        .TIMER_BRK_Polarity         = TIMER_BRK_POLARITY_NON_INV
    };

    RST_CLK_PCLKCmd(RST_CLK_PCLK_TIMER1, ENABLE);

    /* TIMER1 frequency: 8MHz. */
    RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_CLK_SRC_CPU_C1);
    RST_CLK_PER1_C2_SetPrescaler(RST_CLK_PER1_C2_TIM1, RST_CLK_PER1_PRESCALER_DIV_1);
    RST_CLK_PER1_C2_Cmd(RST_CLK_PER1_C2_TIM1, ENABLE);

    TIMER_DeInit(MDR_TIMER1);
    TIMER_CNT_Init(MDR_TIMER1, &TIMER1_CNT_InitStructure);

    /*  TIMER1 interrupt: TIMER_FLAG_CNT_ARR. */
    TIMER_ITConfig(MDR_TIMER1, TIMER_FLAG_CNT_ARR, ENABLE);

#if defined (USE_MDR1206) || defined (USE_MDR1206FI) || defined(USE_MDR1206AFI)
    CLIC_EnableIRQ(TIMER1_IRQn);
#elif defined (USE_MDR32F02_REV_1X) || defined (USE_MDR32F02_REV_2)
    PLIC_EnableExternalIRQ(PLIC_PRIVILEGE_IRQ_MODE_M);
	PLIC_SetPriorityIRQ(TIMER1_IRQn, PLIC_PRIORITY_HIGHEST);
    PLIC_EnableIRQ(TIMER1_IRQn);
#endif

    /* Enable TIMER1. */
    TIMER_CNT_Cmd(MDR_TIMER1, ENABLE);
}

/**
 * @brief  Report the source file name, the source line number and expression
 *         text (if USE_ASSERT_INFO == 2) where the assert_param error has occurred.
 * @param  file: Pointer to the source file name.
 * @param  line: assert_param error line source number.
 * @param  expr: Reported expression text.
 * @return None.
 */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;
    while (1) { }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    (void)file;
    (void)line;
    (void)expr;
    while (1) { }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group MDR32VF0xI_FreeRTOS_Led */

/** @} */ /* End of group RTOS */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


