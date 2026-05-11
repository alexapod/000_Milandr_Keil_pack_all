/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    05/05/2025
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

/** @addtogroup CORE CORE
 * @{
 */

/** @addtogroup MDR1206_CORE_XGOST MDR1206_CORE_XGOST
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_port.h"
#include "MDR32VF0xI_uart.h"
#include "MDR32VF0xI_utils.h"

#include "crypto_gost.h"
#define BITS 128 /* Options: 128 192 256 */
#include "aes.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Private definitions -------------------------------------------------------*/
#define MESSAGE_SIZE (1024 * 8) // 8 KiB
#define KUZN_SZ      16
#define MAGMA_SZ     8
#define AES_SZ       16

/* Private functions prototypes ----------------------------------------------*/
void ClockConfig(void);
void UARTConfig(void);
void UART_PinsConfig(void);
void TestKuznechik(void);
void TestMagma(void);
void TestStreebog(void);
void TestAES(void);

/* Private variables ---------------------------------------------------------*/
uint8_t Message[MESSAGE_SIZE] __attribute__((aligned(8))) = {};
int     Result                                            = 0;

/* Private functions ---------------------------------------------------------*/

extern int ee_printf(const char* fmt, ...);

/**
 * @brief  Put char into I/O stream.
 * @param  None.
 * @return None.
 */
int putchar(int const ch)
{
    while (UART_GetFlagStatus(MDR_UART1, UART_FLAG_TXFF) == SET) { }
    UART_SendData(MDR_UART1, (uint16_t)ch);
    return ch;
}

/**
 * @brief  Main program.
 * @param  None.
 * @return None.
 */
int main(void)
{
    ClockConfig();
    UARTConfig();
    UART_PinsConfig();

    ee_printf(GetChipID() == CHIP_ID_MDR1206FI ? "\r\nMDR1206FI" : "\r\nMDR1206AFI");
    ee_printf("\r\nRun from ");
    switch ((uint32_t)&main >> 28) {
        case 0x1:
            ee_printf("FLASH\r\n");
            break;
        case 0x2:
            ee_printf("RAM AHB\r\n");
            break;
        case 0x4:
            ee_printf("RAM TCM\r\n");
            break;
    }

    TestKuznechik();
    TestMagma();
    TestStreebog();
    TestAES();

    if (Result) {
        ee_printf("Errors found!\r\n");
        while (1) { }
    } else {
        ee_printf("Done.\r\n");
        while (1) { }
    }
}

void TestKuznechik(void)
{
    /* Test master key for Kuznechik from A.1.4 in GOST R 34.12-2015 */
    const uint8_t KuznechikTestMasterKey[32] __attribute__((aligned(8))) = {
        0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
    };

    /* Test text for Kuznechik from A.1.5 in GOST R 34.12-2015 */
    const uint8_t KuznechikTestText[KUZN_SZ] __attribute__((aligned(8))) = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00,
        0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88
    };

    /* Test encrypted text for Kuznechik from A.1.5 in GOST R 34.12-2015 */
    const uint8_t KuznechikEncryptedTestText[KUZN_SZ] __attribute__((aligned(8))) = {
        0x7F, 0x67, 0x9D, 0x90, 0xBE, 0xBC, 0x24, 0x30,
        0x5A, 0x46, 0x8D, 0x42, 0xB9, 0xD4, 0xED, 0xCD
    };

    uint8_t  KuznechikKeys[160] __attribute__((aligned(8)));
    uint8_t* KuznechikText = Message;
    uint32_t Timestamp;

    kuzn_expand_key((uint64_t*)KuznechikTestMasterKey, (uint64_t*)KuznechikKeys);

    memcpy(KuznechikText, KuznechikTestText, KUZN_SZ);
    Timestamp = CSR_Read(CSR_CYCLE);
    kuzn_encrypt((uint64_t*)(KuznechikText), (uint64_t*)KuznechikKeys);
    Timestamp = CSR_Read(CSR_CYCLE) - Timestamp;
    Result |= memcmp(KuznechikText, KuznechikEncryptedTestText, KUZN_SZ);

    kuzn_decrypt((uint64_t*)(KuznechikText), (uint64_t*)KuznechikKeys);
    Result |= memcmp(KuznechikText, KuznechikTestText, KUZN_SZ);
    memset(KuznechikText, 0, KUZN_SZ);

    Timestamp = CSR_Read(CSR_CYCLE);
    for (register int i = 0; i < MESSAGE_SIZE; i += KUZN_SZ) {
        kuzn_encrypt((uint64_t*)(KuznechikText + i), (uint64_t*)KuznechikKeys);
    }
    Timestamp = CSR_Read(CSR_CYCLE) - Timestamp;

    ee_printf("Kuznechik encrypt  %dB: %8u cycles\r\n", MESSAGE_SIZE, Timestamp);

    for (register int i = 0; i < MESSAGE_SIZE; i += KUZN_SZ) {
        kuzn_decrypt((uint64_t*)(KuznechikText + i), (uint64_t*)KuznechikKeys);
    }
    ee_printf("Kuznechik decrypt  %dB: %8u cycles\r\n", MESSAGE_SIZE, Timestamp);

    for (register int i = 0; i < MESSAGE_SIZE; ++i) {
        Result |= (KuznechikText[i] != 0);
    }
}

void TestMagma(void)
{
    /* Test master key for Magma from A.2.3 in GOST R 34.12-2015 */
    const uint8_t MagmaTestMasterKey[32] __attribute__((aligned(8))) = {
        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
        0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
    };

    /* Test test for Magma from A.2.4 in GOST R 34.12-2015 */
    const uint8_t MagmaTestText[MAGMA_SZ] __attribute__((aligned(8))) = {
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
    };

    /* Test encrypted text for Magma from A.2.4 in GOST R 34.12-2015 */
    const uint8_t MagmaTestEncryptedText[MAGMA_SZ] __attribute__((aligned(8))) = {
        0x4e, 0xe9, 0x01, 0xe5, 0xc2, 0xd8, 0xca, 0x3d
    };

    uint8_t* MagmaText = Message;
    uint32_t Timestamp;

    memcpy(MagmaText, MagmaTestText, MAGMA_SZ);
    magma_encrypt((uint8_t*)(MagmaText), (uint32_t*)MagmaTestMasterKey);
    Result |= memcmp(MagmaText, MagmaTestEncryptedText, MAGMA_SZ);
    magma_decrypt((uint8_t*)(MagmaText), (uint32_t*)MagmaTestMasterKey);
    Result |= memcmp(MagmaText, MagmaTestText, MAGMA_SZ);
    memset(MagmaText, 0, MAGMA_SZ);

    Timestamp = CSR_Read(CSR_CYCLE);
    for (register int i = 0; i < MESSAGE_SIZE; i += MAGMA_SZ) {
        magma_encrypt((uint8_t*)(MagmaText + i), (uint32_t*)MagmaTestMasterKey);
    }
    Timestamp = CSR_Read(CSR_CYCLE) - Timestamp;
    ee_printf("Magma     encrypt  %dB: %8u cycles\r\n", MESSAGE_SIZE, Timestamp);

    Timestamp = CSR_Read(CSR_CYCLE);
    for (register int i = 0; i < MESSAGE_SIZE; i += MAGMA_SZ) {
        magma_decrypt((uint8_t*)(MagmaText + i), (uint32_t*)MagmaTestMasterKey);
    }
    Timestamp = CSR_Read(CSR_CYCLE) - Timestamp;
    ee_printf("Magma     decrypt  %dB: %8u cycles\r\n", MESSAGE_SIZE, Timestamp);

    for (size_t i = MAGMA_SZ; i < MESSAGE_SIZE; ++i) {
        Result |= (MagmaText[i] != 0);
    }
}

void TestStreebog(void)
{
    /* Test Message for Streebog for A.1 from GOST R 34.11-2012 */
    const uint8_t StreebogTestTextA1[63] = {
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x30, 0x31, 0x32
    };

    const uint8_t StreebogTestTextA1Hash512[64] = {
        0x1b, 0x54, 0xd0, 0x1a, 0x4a, 0xf5, 0xb9, 0xd5,
        0xcc, 0x3d, 0x86, 0xd6, 0x8d, 0x28, 0x54, 0x62,
        0xb1, 0x9a, 0xbc, 0x24, 0x75, 0x22, 0x2f, 0x35,
        0xc0, 0x85, 0x12, 0x2b, 0xe4, 0xba, 0x1f, 0xfa,
        0x00, 0xad, 0x30, 0xf8, 0x76, 0x7b, 0x3a, 0x82,
        0x38, 0x4c, 0x65, 0x74, 0xf0, 0x24, 0xc3, 0x11,
        0xe2, 0xa4, 0x81, 0x33, 0x2b, 0x08, 0xef, 0x7f,
        0x41, 0x79, 0x78, 0x91, 0xc1, 0x64, 0x6f, 0x48
    };

    const uint8_t StreebogTestTextA1Hash256[32] = {
        0x9d, 0x15, 0x1e, 0xef, 0xd8, 0x59, 0x0b, 0x89,
        0xda, 0xa6, 0xba, 0x6c, 0xb7, 0x4a, 0xf9, 0x27,
        0x5d, 0xd0, 0x51, 0x02, 0x6b, 0xb1, 0x49, 0xa4,
        0x52, 0xfd, 0x84, 0xe5, 0xe5, 0x7b, 0x55, 0x00
    };

    /* Test Message for Streebog for A.2 from GOST R 34.11-2012 */
    const uint8_t StreebogTestTextA2[72] = {
        0xd1, 0xe5, 0x20, 0xe2, 0xe5, 0xf2, 0xf0, 0xe8,
        0x2c, 0x20, 0xd1, 0xf2, 0xf0, 0xe8, 0xe1, 0xee,
        0xe6, 0xe8, 0x20, 0xe2, 0xed, 0xf3, 0xf6, 0xe8,
        0x2c, 0x20, 0xe2, 0xe5, 0xfe, 0xf2, 0xfa, 0x20,
        0xf1, 0x20, 0xec, 0xee, 0xf0, 0xff, 0x20, 0xf1,
        0xf2, 0xf0, 0xe5, 0xeb, 0xe0, 0xec, 0xe8, 0x20,
        0xed, 0xe0, 0x20, 0xf5, 0xf0, 0xe0, 0xe1, 0xf0,
        0xfb, 0xff, 0x20, 0xef, 0xeb, 0xfa, 0xea, 0xfb,
        0x20, 0xc8, 0xe3, 0xee, 0xf0, 0xe5, 0xe2, 0xfb
    };

    const uint8_t StreebogTestTextA2Hash512[64] = {
        0x1e, 0x88, 0xe6, 0x22, 0x26, 0xbf, 0xca, 0x6f,
        0x99, 0x94, 0xf1, 0xf2, 0xd5, 0x15, 0x69, 0xe0,
        0xda, 0xf8, 0x47, 0x5a, 0x3b, 0x0f, 0xe6, 0x1a,
        0x53, 0x00, 0xee, 0xe4, 0x6d, 0x96, 0x13, 0x76,
        0x03, 0x5f, 0xe8, 0x35, 0x49, 0xad, 0xa2, 0xb8,
        0x62, 0x0f, 0xcd, 0x7c, 0x49, 0x6c, 0xe5, 0xb3,
        0x3f, 0x0c, 0xb9, 0xdd, 0xdc, 0x2b, 0x64, 0x60,
        0x14, 0x3b, 0x03, 0xda, 0xba, 0xc9, 0xfb, 0x28
    };

    const uint8_t StreebogTestTextA2Hash256[32] = {
        0x9d, 0xd2, 0xfe, 0x4e, 0x90, 0x40, 0x9e, 0x5d,
        0xa8, 0x7f, 0x53, 0x97, 0x6d, 0x74, 0x05, 0xb0,
        0xc0, 0xca, 0xc6, 0x28, 0xfc, 0x66, 0x9a, 0x74,
        0x1d, 0x50, 0x06, 0x3c, 0x55, 0x7e, 0x8f, 0x50
    };

    uint8_t  StreebogHash[64];
    uint8_t* StreebogMessage = Message;
    uint32_t Timestamp;

    streebog_hash(StreebogTestTextA1, 63, 512, StreebogHash);
    Result |= memcmp(StreebogHash, StreebogTestTextA1Hash512, 64);

    streebog_hash(StreebogTestTextA1, 63, 256, StreebogHash);
    Result |= memcmp(StreebogHash, StreebogTestTextA1Hash256, 32);

    streebog_hash(StreebogTestTextA2, 72, 512, StreebogHash);
    Result |= memcmp(StreebogHash, StreebogTestTextA2Hash512, 64);

    streebog_hash(StreebogTestTextA2, 72, 256, StreebogHash);
    Result |= memcmp(StreebogHash, StreebogTestTextA2Hash256, 32);

    Timestamp = CSR_Read(CSR_CYCLE);
    streebog_hash(StreebogMessage, MESSAGE_SIZE, 512, StreebogHash);
    Timestamp = CSR_Read(CSR_CYCLE) - Timestamp;
    ee_printf("Streebog  hash512  %dB: %8u cycles\r\n", MESSAGE_SIZE, Timestamp);
}

void TestAES(void)
{
#ifdef __riscv_zkn
    const uint8_t AES_MasterKey[] __attribute__((aligned(8))) = {
        0x00,
        0x01,
        0x02,
        0x03,
        0x04,
        0x05,
        0x06,
        0x07,
        0x08,
        0x09,
        0x0A,
        0x0B,
        0x0C,
        0x0D,
        0x0E,
        0x0F,
#if BITS > 128
        0x10,
        0x11,
        0x12,
        0x13,
        0x14,
        0x15,
        0x16,
        0x17,
#if BITS > 192
        0x18,
        0x19,
        0x1A,
        0x1B,
        0x1C,
        0x1D,
        0x1E,
        0x1F,
#endif
#endif
    };

    const uint8_t AES_TestText[AES_SZ] __attribute__((aligned(8))) = {
        0x00,
        0x11,
        0x22,
        0x33,
        0x44,
        0x55,
        0x66,
        0x77,
        0x88,
        0x99,
        0xAA,
        0xBB,
        0xCC,
        0xDD,
        0xEE,
        0xFF,
    };

    const uint8_t AES_EncryptedTestText[AES_SZ] __attribute__((aligned(8))) = {
#if BITS == 128
        0x69,
        0xC4,
        0xE0,
        0xD8,
        0x6A,
        0x7B,
        0x04,
        0x30,
        0xD8,
        0xCD,
        0xB7,
        0x80,
        0x70,
        0xB4,
        0xC5,
        0x5A,
#elif BITS == 192
        0xDD,
        0xA9,
        0x7C,
        0xA4,
        0x86,
        0x4C,
        0xDF,
        0xE0,
        0x6E,
        0xAF,
        0x70,
        0xA0,
        0xEC,
        0x0D,
        0x71,
        0x91,
#else // BITS == 256
        0x8E,
        0xA2,
        0xB7,
        0xCA,
        0x51,
        0x67,
        0x45,
        0xBF,
        0xEA,
        0xFC,
        0x49,
        0x90,
        0x4B,
        0x49,
        0x60,
        0x89,
#endif
    };

    uint32_t AES_keys[AES_RK_WORDS] __attribute__((aligned(8)));
    uint8_t* AES_text = Message;
    uint32_t Timestamp;

    memcpy(AES_text, AES_TestText, sizeof(AES_TestText));
    aes_enc_key(AES_keys, AES_MasterKey);

    Timestamp = CSR_Read(CSR_CYCLE);
    for (register int i = 0; i < MESSAGE_SIZE; i += AES_SZ) {
        aes_enc_ecb(AES_text + i, AES_text + i, AES_keys);
    }
    Timestamp = CSR_Read(CSR_CYCLE) - Timestamp;
    ee_printf("AES128    encrypt  %dB: %8u cycles\r\n", MESSAGE_SIZE, Timestamp);
    Result |= memcmp(AES_text, AES_EncryptedTestText, AES_SZ);
#else
    ee_printf("AES128 test was skipped because compiler does not support ZKN extension instructions.");
#endif
}

/**
 * @brief  Clock configuration.
 * @param  None.
 * @return None.
 */
void ClockConfig(void)
{
    RST_CLK_DeInit();
    RST_CLK_HSE_Config(RST_CLK_HSE_ON);
    SystemCoreClockUpdate();
    while (RST_CLK_HSE_GetStatus() != SUCCESS) { }
    RST_CLK_CPU_C1_ClkSelection(RST_CLK_CPU_C1_CLK_SRC_HSE);
    RST_CLK_CPU_C2_ClkSelection(RST_CLK_CPU_C2_CLK_SRC_CPU_C1);
    RST_CLK_CPU_C3_SetPrescaler(RST_CLK_CPU_C3_PRESCALER_DIV_1);
    RST_CLK_HCLK_ClkSelection(RST_CLK_CPU_HCLK_CLK_SRC_CPU_C3);
    SystemCoreClockUpdate();
}

/**
 * @brief  UART configuration.
 * @param  None.
 * @return None.
 */
void UARTConfig(void)
{
    static const UART_InitTypeDef UART_Transmitter = {
        .UART_BaudRate            = 9600,
        .UART_Mode                = UART_MODE_TX,
        .UART_WordLength          = UART_WORD_LENGTH_8BIT,
        .UART_StopBits            = UART_STOP_BITS_1BIT,
        .UART_Parity              = UART_PARITY_NONE,
        .UART_HardwareFlowControl = UART_HARDWARE_FLOW_CONTROL_NONE,
        .UART_LoopbackMode        = UART_LOOPBACK_DISABLE,
        .UART_FIFO_Mode           = UART_FIFO_MODE_DISABLE,
        .UART_FIFO_TxThreshold    = UART_FIFO_TX_THRESHOLD_2WORD,
        .UART_FIFO_RxThreshold    = UART_FIFO_RX_THRESHOLD_2WORD,
        .UART_IRDA_Mode           = UART_IRDA_MODE_DISABLE,
        .UART_IRDA_PowerMode      = UART_IRDA_POWER_NORMAL
    };

    RST_CLK_PCLKCmd(RST_CLK_PCLK_UART1, ENABLE);

    RST_CLK_PER1_C2_ClkSelection(RST_CLK_PER1_C2_CLK_SRC_CPU_C1);
    RST_CLK_PER1_C2_Cmd(RST_CLK_PER1_C2_UART1, ENABLE);

    UART_DeInit(MDR_UART1);
    UART_Init(MDR_UART1, &UART_Transmitter);
    UART_Cmd(MDR_UART1, ENABLE);
}

/**
 * @brief  UART pins configuration.
 * @param  None.
 * @return None.
 */
void UART_PinsConfig(void)
{
    static const PORT_InitTypeDef UART_Pins = {
        .PORT_Pin       = PORT_PIN_0 | PORT_PIN_1,
        .PORT_Mode      = PORT_MODE_DIGITAL,
        .PORT_Direction = PORT_DIRECTION_INPUT_OUTPUT,
        .PORT_Function  = PORT_FUNCTION_MAIN,
        .PORT_Power     = PORT_POWER_NOMINAL_UPTO_2mA,
        .PORT_PullUp    = PORT_PULL_UP_OFF,
        .PORT_PullDown  = PORT_PULL_DOWN_OFF,
    };

    RST_CLK_PCLKCmd(RST_CLK_PCLK_PORTB, ENABLE);
    PORT_Init(MDR_PORTB, &UART_Pins);
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

/** @} */ /* End of group MDR1206_CORE_XGOST */

/** @} */ /* End of group CORE */

/** @} */ /* End of group MDR32VF0xI_MDR1206FI_BOARD */

/** @} */ /* End of group MDR32VF0xI_StdPeriph_Examples */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE main.c */


