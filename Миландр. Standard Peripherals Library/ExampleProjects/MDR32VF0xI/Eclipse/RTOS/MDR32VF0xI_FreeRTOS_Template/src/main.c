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

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"
#include "FreeRTOS.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Private definitions ------------------------------------------------------------*/

/* Private functions prototypes ---------------------------------------------*/
void freertos_risc_v_trap_handler(void);
void freertos_risc_v_mtimer_interrupt_handler(void);
#if defined (USE_MDR1206) || defined (USE_MDR1206FI) || defined(USE_MDR1206AFI)
void CLIC_FreeRTOS_Init(void);
#elif defined (USE_MDR32F02_REV_1X) || defined (USE_MDR32F02_REV_2)
void PLIC_FreeRTOS_Init(void);
#endif

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

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
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main()
{
#if defined (USE_MDR1206) || defined (USE_MDR1206FI) || defined(USE_MDR1206AFI)
    CLIC_FreeRTOS_Init();
#elif defined (USE_MDR32F02_REV_1X) || defined (USE_MDR32F02_REV_2)
    PLIC_FreeRTOS_Init();
#endif

    while (1) { }
}

