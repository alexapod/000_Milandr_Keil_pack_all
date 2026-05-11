/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    14/06/2023
  * @brief   Main program body.
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
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_i2c.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup I2C_Recive_VE92 I2C_Recive
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define ADRESS          0x00
#define TRANS_COUNT     5

/* Private variables ---------------------------------------------------------*/
I2C_InitTypeDef I2C_InitStruct;
PORT_InitTypeDef PortInit;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t i;
    static uint32_t dat;

    RST_CLK_DeInit();

    /* Select HSE as CPU_CLK source */
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    while(RST_CLK_HSEstatus() == ERROR);
    RST_CLK_CPUclkSelectionC1(RST_CLK_CPU_C1srcHSEdiv1);
    RST_CLK_CPU_PLLuse(DISABLE);
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);

    SystemCoreClockUpdate();

    /* Enables peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_I2C), ENABLE);

    /* Configure PORTC pins 0, 1 (I2C_SCL, I2C_SDA) */
    PORT_StructInit(&PortInit);
    PortInit.PORT_Pin     = (PORT_Pin_0 | PORT_Pin_1);
    PortInit.PORT_FUNC    = PORT_FUNC_ALTER;
    PortInit.PORT_SPEED   = PORT_SPEED_MAXFAST;
    PortInit.PORT_MODE    = PORT_MODE_DIGITAL;
    PortInit.PORT_PULL_UP = PORT_PULL_UP_ON;
    PORT_Init(MDR_PORTC, &PortInit);

    /* Enables I2C peripheral */
    I2C_Cmd(ENABLE);

    /* Initialize I2C_InitStruct */
    I2C_StructInit(&I2C_InitStruct);
    I2C_InitStruct.I2C_ClkDiv = 16;
    I2C_InitStruct.I2C_Speed = I2C_SPEED_UP_TO_400KHz;

    /* Configure I2C parameters */
    I2C_Init(&I2C_InitStruct);

    while(1)
    {
        /* Wait I2C bus is free */
        while(I2C_GetFlagStatus(I2C_FLAG_BUS_FREE) != SET);

        /* Send adress */
        I2C_Send7bitAddress(ADRESS,I2C_Direction_Receiver);

        /* Wait end of transfer */
        while(I2C_GetFlagStatus(I2C_FLAG_nTRANS) != SET);

        /* Recive data if ACK was send */
        if (I2C_GetFlagStatus(I2C_FLAG_SLAVE_ACK) == SET)
        {
            for(i = 0; i < TRANS_COUNT; i++)
            {
                /* Recive byte and send ack */
                I2C_StartReceiveData(I2C_Send_to_Slave_ACK);

                /* Wait end of transfer */
                while(I2C_GetFlagStatus(I2C_FLAG_nTRANS) != SET);

                /* Get data from I2C RXD register */
                dat = I2C_GetReceivedData();
            }
        }

        /* Send stop */
        I2C_SendSTOP();
    }
}

/**
  * @brief  Reports the source file name, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the source file name and line number.
       Ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while(1) {}
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    /* User can add his own implementation to report the source file name, line number and
       expression text.
       Ex: printf("Wrong parameters value (%s): file %s on line %d\r\n", expr, file, line) */

    /* Infinite loop */
    while(1) {}
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group I2C_Recive_VE92 */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


