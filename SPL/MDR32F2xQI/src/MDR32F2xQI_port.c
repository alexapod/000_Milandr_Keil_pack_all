/**
 *******************************************************************************
 * @file    MDR32F2xQI_port.c
 * @author  Milandr Application Team
 * @version V1.0.0
 * @date    30/05/2023
 * @brief   This file contains all the PORT firmware functions.
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
#include "MDR32F2xQI_port.h"

/** @addtogroup __MDR32F2xQI_StdPeriph_Driver MDR32F2xQI Standard Peripherial Driver
 * @{
 */

/** @defgroup PORT PORT
 * @{
 */

/** @defgroup PORT_Private_Defines PORT Private Defines
 * @{
 */

#define IS_PORT_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_PORTA) || \
                                    ((PERIPH) == MDR_PORTB) || \
                                    ((PERIPH) == MDR_PORTC))

/** @} */ /* End of group PORT_Private_Defines */

/** @defgroup PORT_Exported_Functions PORT Exported Functions
 * @{
 */

/**
 * @brief  Resets the MDR_PORTx peripheral registers to their default reset values.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @retval None.
 */
void PORT_DeInit(MDR_PORT_TypeDef* PORTx)
{
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));

    PORTx->ANALOG = 0;
    PORTx->PULL   = 0;
    PORTx->OE     = 0;
    PORTx->RXTX   = 0;
    PORTx->FUNC   = 0;
    PORTx->PD     = 0;
    PORTx->PWR    = 0;
    PORTx->GFEN   = 0;
}

/**
 * @brief  Initializes the PORTx peripheral according to the specified
 *         parameters in the PORT_InitStruct.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PORT_InitStruct: pointer to a @ref PORT_InitTypeDef structure that
 *         contains the configuration information for the specified PORT peripheral.
 * @retval None.
 */
void PORT_Init(MDR_PORT_TypeDef* PORTx, const PORT_InitTypeDef* PORT_InitStruct)
{
    uint32_t TempOE;
    uint32_t TempFUNC;
    uint32_t TempANALOG;
    uint32_t TempPULL;
    uint32_t TempPD;
    uint32_t TempPWR;
    uint32_t TempGFEN;
    uint32_t PortPin, Pos, MaskS, MaskL, MaskD;

    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_PORT_PIN(PORT_InitStruct->PORT_Pin));
    assert_param(IS_PORT_MODE(PORT_InitStruct->PORT_Mode));
    assert_param(IS_PORT_DIR(PORT_InitStruct->PORT_Direction));
    assert_param(IS_PORT_FUNC(PORT_InitStruct->PORT_Function));
    assert_param(IS_PORT_POWER(PORT_InitStruct->PORT_Power));
    assert_param(IS_PORT_DRIVER(PORT_InitStruct->PORT_Driver));
    assert_param(IS_PORT_PULL_UP(PORT_InitStruct->PORT_PullUp));
    assert_param(IS_PORT_PULL_DOWN(PORT_InitStruct->PORT_PullDown));
    assert_param(IS_PORT_HYSTERESIS(PORT_InitStruct->PORT_Hysteresis));
    assert_param(IS_PORT_GFEN(PORT_InitStruct->PORT_GlitchFilter));

    /* Get current PORT register values */
    TempOE     = PORTx->OE;
    TempFUNC   = PORTx->FUNC;
    TempANALOG = PORTx->ANALOG;
    TempPULL   = PORTx->PULL;
    TempPD     = PORTx->PD;
    TempPWR    = PORTx->PWR;
    TempGFEN   = PORTx->GFEN;

    /* Form new values */
    Pos   = 0;
    MaskS = 0x0001;
    MaskL = 0x00000003;
    MaskD = 0x00010001;

    for (PortPin = PORT_InitStruct->PORT_Pin; PortPin; PortPin >>= 1) {
        if (PortPin & 0x1) {
            TempOE     = (TempOE & ~MaskS) | ((uint32_t)PORT_InitStruct->PORT_Direction << Pos);
            TempFUNC   = (TempFUNC & ~MaskL) | ((uint32_t)PORT_InitStruct->PORT_Function << (Pos * 2));
            TempANALOG = (TempANALOG & ~MaskS) | ((uint32_t)PORT_InitStruct->PORT_Mode << Pos);
            TempPULL   = (TempPULL & ~MaskD) |
                       ((uint32_t)PORT_InitStruct->PORT_PullUp << (Pos + PORT_PULL_PULL_UP_Pos)) |
                       ((uint32_t)PORT_InitStruct->PORT_PullDown << Pos);
            TempPD = (TempPD & ~MaskD) |
                     ((uint32_t)PORT_InitStruct->PORT_Hysteresis << (Pos + PORT_PD_SHM_Pos)) |
                     ((uint32_t)PORT_InitStruct->PORT_Driver << Pos);
            TempPWR  = (TempPWR & ~MaskL) | ((uint32_t)PORT_InitStruct->PORT_Power << (Pos * 2));
            TempGFEN = (TempGFEN & ~MaskS) | ((uint32_t)PORT_InitStruct->PORT_GlitchFilter << Pos);
        }
        MaskS <<= 1;
        MaskL <<= 2;
        MaskD <<= 1;
        Pos++;
    }

    /* Configure PORT registers with new values */
    PORTx->OE     = TempOE & (~SWD_PINS(PORTx));
    PORTx->FUNC   = TempFUNC & (~SWD_PINS2(PORTx));
    PORTx->ANALOG = TempANALOG & (~SWD_PINS(PORTx));
    PORTx->PULL   = TempPULL & (~SWD_PINS3(PORTx));
    PORTx->PD     = TempPD & (~SWD_PINS3(PORTx));
    PORTx->PWR    = TempPWR & (~SWD_PINS2(PORTx));
    PORTx->GFEN   = TempGFEN & (~SWD_PINS(PORTx));
}

/**
 * @brief  Fills each PORT_InitStruct member with its default value.
 * @param  PORT_InitStruct: pointer to a @ref PORT_InitTypeDef structure
 *         which will be initialized.
 * @retval None.
 */
void PORT_StructInit(PORT_InitTypeDef* PORT_InitStruct)
{
    /* Reset PORT initialization structure parameters values */
    PORT_InitStruct->PORT_Pin          = PORT_PIN_ALL;
    PORT_InitStruct->PORT_Mode         = PORT_MODE_ANALOG;
    PORT_InitStruct->PORT_Direction    = PORT_DIRECTION_IN;
    PORT_InitStruct->PORT_Function     = PORT_FUNCTION_PORT;
    PORT_InitStruct->PORT_Power        = PORT_POWER_OUTPUT_OFF;
    PORT_InitStruct->PORT_Driver       = PORT_DRIVER_PUSH_PULL;
    PORT_InitStruct->PORT_PullUp       = PORT_PULL_UP_OFF;
    PORT_InitStruct->PORT_PullDown     = PORT_PULL_DOWN_OFF;
    PORT_InitStruct->PORT_Hysteresis   = PORT_HYSTERESIS_DISABLE;
    PORT_InitStruct->PORT_GlitchFilter = PORT_GLITCH_FILTER_DISABLE;
}

/**
 * @brief  Reads the specified input port pin.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PORT_Pin - @ref PORT_Pin_TypeDef - specifies the port bit to read.
 *         This parameter can be PORT_Pin_x where x can be:
 *             (0..15) for MDR_PORTA,
 *             (0..14) for MDR_PORTB,
 *             (0...7) for MDR_PORTC for MDR32F21QI and (0...15) for MDR32F23QI.
 * @retval @ref BitStatus - the input port pin value.
 */
BitStatus PORT_ReadInputDataBit(MDR_PORT_TypeDef* PORTx, PORT_Pin_TypeDef PORT_Pin)
{
    BitStatus Status;

    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_GET_PORT_PIN(PORT_Pin));

    if ((PORTx->RXTX & (uint32_t)PORT_Pin) != RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Reads the specified PORT input data port.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @retval PORT input data port value. Bits (16..31) are always 0.
 */
uint32_t PORT_ReadInputData(MDR_PORT_TypeDef* PORTx)
{
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));

    return (PORTx->RXTX);
}

/**
 * @brief  Reads the specified ouptut port pin.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PORT_Pin - @ref PORT_Pin_TypeDef - specifies the port bit to read.
 *         This parameter can be PORT_Pin_x where x can be:
 *             (0..15) for MDR_PORTA,
 *             (0..14) for MDR_PORTB,
 *             (0...7) for MDR_PORTC for MDR32F21QI and (0...15) for MDR32F23QI.
 * @retval @ref BitStatus - the ouptut port pin value.
 */
BitStatus PORT_ReadOutputDataBit(MDR_PORT_TypeDef* PORTx, PORT_Pin_TypeDef PORT_Pin)
{
    BitStatus Status;

    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_GET_PORT_PIN(PORT_Pin));

    if ((PORTx->RDTX & (uint32_t)PORT_Pin) != RESET) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Reads the specified PORT output data port.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @retval PORT output data port value. Bits (16..31) are always 0.
 */
uint32_t PORT_ReadOutputData(MDR_PORT_TypeDef* PORTx)
{
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));

    return (PORTx->RDTX);
}

/**
 * @brief  Sets the selected data port bits.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PORT_Pin - @ref PORT_Pin_TypeDef - specifies the port bit to write.
 *         This parameter can be any combination of PORT_Pin_x where x can be:
 *             (0..15) for MDR_PORTA,
 *             (0..14) for MDR_PORTB,
 *             (0...7) for MDR_PORTC for MDR32F21QI and (0...15) for MDR32F23QI.
 * @retval None.
 */
void PORT_SetBits(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin)
{
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_PORT_PIN(PORT_Pin));
    assert_param(IS_NOT_SWD_PIN(PORTx, PORT_Pin));

    PORTx->SETTX = (PORT_Pin & ~SWD_PINS(PORTx));
}

/**
 * @brief  Clears the selected data port bits.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PORT_Pin - @ref PORT_Pin_TypeDef - specifies the port bit to write.
 *         This parameter can be any combination of PORT_Pin_x where x can be:
 *             (0..15) for MDR_PORTA,
 *             (0..14) for MDR_PORTB,
 *             (0...7) for MDR_PORTC for MDR32F21QI and (0...15) for MDR32F23QI.
 * @retval None.
 */
void PORT_ResetBits(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin)
{
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_PORT_PIN(PORT_Pin));
    assert_param(IS_NOT_SWD_PIN(PORTx, PORT_Pin));

    PORTx->CLRTX = (PORT_Pin & ~SWD_PINS(PORTx));
}

/**
 * @brief  Sets or clears the selected data port bit.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PORT_Pin - @ref PORT_Pin_TypeDef - specifies the port bit to write.
 *         This parameter can be any combination of PORT_Pin_x where x can be:
 *             (0..15) for MDR_PORTA,
 *             (0..14) for MDR_PORTB,
 *             (0...7) for MDR_PORTC for MDR32F21QI and (0...15) for MDR32F23QI.
 * @param  BitVal: specifies the value to be written to the selected bit.
 *         This parameter can be one of the @ref BitStatus enum values:
 *             @arg RESET: to clear the port pin,
 *             @arg SET: to set the port pin.
 * @retval None.
 */
void PORT_WriteBit(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin, BitStatus BitVal)
{
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_GET_PORT_PIN(PORT_Pin));
    assert_param(IS_BIT_STATUS(BitVal));
    assert_param(IS_NOT_SWD_PIN(PORTx, PORT_Pin));

    if (BitVal != RESET) {
        PORTx->SETTX = (PORT_Pin & ~SWD_PINS(PORTx));
    } else {
        PORTx->CLRTX = (PORT_Pin & ~SWD_PINS(PORTx));
    }
}

/**
 * @brief  Toggles selected port bit.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PORT_Pin - @ref PORT_Pin_TypeDef - specifies the port bit to toggle.
 *         This parameter can be any combination of PORT_Pin_x where x can be:
 *             (0..15) for MDR_PORTA,
 *             (0..14) for MDR_PORTB,
 *             (0...7) for MDR_PORTC for MDR32F21QI and (0...15) for MDR32F23QI.
 * @retval None.
 */
void PORT_ToggleBit(MDR_PORT_TypeDef* PORTx, uint32_t PORT_Pin)
{
    uint32_t Temp;

    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_GET_PORT_PIN(PORT_Pin));
    assert_param(IS_NOT_SWD_PIN(PORTx, PORT_Pin));

    Temp         = PORTx->RDTX;
    PORTx->CLRTX = Temp & PORT_Pin;
    PORTx->SETTX = ~Temp & PORT_Pin;
}

/**
 * @brief  Writes data to the specified PORT data port.
 * @param  PORTx: Select MDR_PORTx peripheral. x can be (A..C).
 * @param  PortVal: specifies the value to be written to the port output data register.
 *                  For MDR_PORTA bits (16..31) are ignored,
 *                  for MDR_PORTB bits (15..31) are ignored,
 *                  for MDR_PORTC bits (15...31) for MDR32F21QI and (8...31) for MDR32F23QI are ignored.
 * @retval None.
 */
void PORT_Write(MDR_PORT_TypeDef* PORTx, uint32_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));
    assert_param(IS_NOT_SWD_PIN(PORTx, PortVal));

    PORTx->RXTX = PortVal & (~SWD_PINS(PORTx));
}

/** @} */ /* End of group PORT_Exported_Functions */

/** @} */ /* End of group PORT */

/** @} */ /* End of group __MDR32F2xQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32F2xQI_port.c */

