/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.3
  * @date    22/06/2023
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
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_dma.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */


/** @addtogroup DMA_Pri_Alt_Channels_MDR32F1QI DMA_Pri_Alt_Channels
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define SIZE        0x400

/* Private variables ---------------------------------------------------------*/
uint32_t DestBuf[SIZE] IAR_SECTION ("EXECUTABLE_MEMORY_SECTION") __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
uint32_t PriBuf[SIZE] IAR_SECTION ("EXECUTABLE_MEMORY_SECTION") __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
uint32_t AltBuf[SIZE] IAR_SECTION ("EXECUTABLE_MEMORY_SECTION") __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

volatile ErrorStatus TransferStatus1 = ERROR, TransferStatus2 = ERROR;

/* Private function prototypes -----------------------------------------------*/
void Init_RAM(uint32_t *addr, uint32_t size);
ErrorStatus Verif_mem(uint32_t BufSize, uint32_t *pBuffer1, uint32_t *pBuffer2);
uint32_t ps_rand(uint32_t addr);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initialisation memory pseudo random value
  * @param  addr - memory address
  * @param  size - memory size
  * @retval None
  */
void Init_RAM(uint32_t *addr, uint32_t size)
{
    uint32_t i;

    for(i = 0; i < size; i++)
    {
        *addr = ps_rand((uint32_t)addr + i * 4);
        addr++;
    }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufSize: buffer's size
  * @retval SUCCESS: pBuffer1 identical to pBuffer2
  *         ERROR: pBuffer1 differs from pBuffer2
  */
ErrorStatus Verif_mem(uint32_t BufSize, uint32_t *pBuffer1, uint32_t *pBuffer2)
{
    uint32_t i;

    for(i = 0; i < BufSize; i++)
    {
        if (*pBuffer1++ != *pBuffer2++)
        {
            return (ErrorStatus)ERROR;
        }
    }

    return (ErrorStatus) SUCCESS;
}

/**
  * @brief  Generation random values
  * @param  addr -
  * @retval None
  */
uint32_t ps_rand(uint32_t addr)
{
    uint32_t hash = 0;
    uint32_t i;
    char *key = (char *)&addr;

    for(i = 0; i < 4; i++)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    for(i = 0; i < 256; i++)
    {
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    DMA_ChannelInitTypeDef DMA_InitStr;
    DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
    DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;

    uint32_t DMA_Channel = 3;

    RST_CLK_DeInit();
    SystemCoreClockUpdate();

    RST_CLK_PCLKcmd(RST_CLK_PCLK_DMA, ENABLE);

    /* Init RAM */
    Init_RAM(DestBuf, SIZE);
    Init_RAM(PriBuf, SIZE);
    Init_RAM(AltBuf, SIZE);

    /* Reset all settings */
    DMA_DeInit();

    /* Set Primary Control Data */
    DMA_PriCtrlStr.DMA_SourceBaseAddr = (uint32_t)PriBuf;
    DMA_PriCtrlStr.DMA_DestBaseAddr   = (uint32_t)DestBuf;
    DMA_PriCtrlStr.DMA_SourceIncSize  = DMA_SourceIncWord;
    DMA_PriCtrlStr.DMA_DestIncSize    = DMA_DestIncWord;
    DMA_PriCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_PriCtrlStr.DMA_Mode           = DMA_Mode_Basic;
    DMA_PriCtrlStr.DMA_CycleSize      = SIZE;
    DMA_PriCtrlStr.DMA_NumContinuous  = DMA_Transfers_16;
    DMA_PriCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_PriCtrlStr.DMA_DestProtCtrl   = DMA_DestPrivileged;

    /* Set Alternate Control Data */
    DMA_AltCtrlStr.DMA_SourceBaseAddr = (uint32_t)AltBuf;
    DMA_AltCtrlStr.DMA_DestBaseAddr   = (uint32_t)DestBuf;
    DMA_AltCtrlStr.DMA_SourceIncSize  = DMA_SourceIncWord;
    DMA_AltCtrlStr.DMA_DestIncSize    = DMA_DestIncWord;
    DMA_AltCtrlStr.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_AltCtrlStr.DMA_Mode           = DMA_Mode_AutoRequest;
    DMA_AltCtrlStr.DMA_CycleSize      = SIZE;
    DMA_AltCtrlStr.DMA_NumContinuous  = DMA_Transfers_16;
    DMA_AltCtrlStr.DMA_SourceProtCtrl = DMA_SourcePrivileged;
    DMA_AltCtrlStr.DMA_DestProtCtrl   = DMA_DestPrivileged;

    /* Set Channel Structure */
    DMA_StructInit(&DMA_InitStr);
    DMA_InitStr.DMA_PriCtrlData         = &DMA_PriCtrlStr;
    DMA_InitStr.DMA_AltCtrlData         = &DMA_AltCtrlStr;
    DMA_InitStr.DMA_Priority            = DMA_Priority_Default;
    DMA_InitStr.DMA_UseBurst            = DMA_BurstClear;
    DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;

    /* Init DMA channel */
    DMA_Init(DMA_Channel, &DMA_InitStr);

    /* Run channel */
    DMA_Cmd(DMA_Channel, ENABLE);
    DMA_Request(DMA_Channel);

    /* Transfer complete */
    while(DMA_GetFlagStatus(DMA_Channel, DMA_FLAG_CHNL_ENA))
    {
        if ((MDR_DMA->STATUS & DMA_STATUS_STATE_Msk) == DMA_Mode_Stop)
        {
            DMA_Request(DMA_Channel);
        }
    }
    /* Check the correctness of written data */
    TransferStatus1 = Verif_mem(SIZE, PriBuf, DestBuf);
    /* TransferStatus1 = SUCCESS, if the data transmitted and received are correct */
    /* TransferStatus1 = ERROR, if the data transmitted and received are different */

    /* Set Channel Structure */
    DMA_InitStr.DMA_SelectDataStructure = DMA_CTRL_DATA_ALTERNATE;

    /* Init DMA channel */
    DMA_Init(DMA_Channel, &DMA_InitStr);

    /* Run channel */
    DMA_Cmd(DMA_Channel, ENABLE);
    DMA_Request(DMA_Channel);

    /* Transfer complete */
    while(DMA_GetFlagStatus(DMA_Channel, DMA_FLAG_CHNL_ENA)) {}
    /* Check the correctness of written data */
    TransferStatus2 = Verif_mem(SIZE, AltBuf, DestBuf);
    /* TransferStatus2 = SUCCESS, if the data transmitted and received are correct */
    /* TransferStatus2 = ERROR, if the data transmitted and received are different */

    while(1) {}
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

/** @} */ /* End of group DMA_Pri_Alt_Channels_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */


/******************* (C) COPYRIGHT 2025 Milandr *******************************/

/* END OF FILE main.c */


