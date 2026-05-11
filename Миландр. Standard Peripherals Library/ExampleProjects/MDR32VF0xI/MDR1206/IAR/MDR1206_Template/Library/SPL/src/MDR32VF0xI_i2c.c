/**
 *******************************************************************************
 * @file    MDR32VF0xI_i2c.c
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    13/05/2025
 * @brief   This file contains all the I2C firmware functions.
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
#include "MDR32VF0xI_i2c.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @defgroup I2C I2C
 * @{
 */

/** @defgroup I2C_Exported_Functions I2C Exported Functions
 * @{
 */

/**
 * @brief  Reset the I2C peripheral registers to their default reset values.
 * @param  None.
 * @return None.
 */
void I2C_DeInit(void)
{
    MDR_I2C->CTR = 0;
    MDR_I2C->CMD = I2C_CMD_CLRINT;
    MDR_I2C->TXD = 0;
    MDR_I2C->PRL = 0xFF;
    MDR_I2C->PRH = 0xFF;
}

/**
 * @brief  Enable or disable the I2C peripheral.
 * @param  NewState: @ref FunctionalState - a new state of the I2C peripheral.
 * @return None.
 */
void I2C_Cmd(FunctionalState NewState)
{
    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable I2C by setting the EN_I2C bit in the CTR register. */
        MDR_I2C->CTR |= I2C_CTR_EN_I2C;
    } else {
        /* Disable I2C by resetting the EN_I2C bit in the CTR register. */
        MDR_I2C->CTR &= ~I2C_CTR_EN_I2C;
    }
}

/**
 * @brief  Get the I2C peripheral work state.
 * @param  None.
 * @return @ref FunctionalState - the current work state of the I2C peripheral.
 */
FunctionalState I2C_GetCmdState(void)
{
    FunctionalState State;

    if ((MDR_I2C->CTR & I2C_CTR_EN_I2C) == 0) {
        State = DISABLE;
    } else {
        State = ENABLE;
    }

    return State;
}

/**
 * @brief  Set the I2C prescaler registers value.
 * @param  I2C_ClkDiv: Specify the TIM_CLK prescaler register value.
 * @note   F_SCL = HCLK / (5 * (I2C_ClkDiv + 1)).
 * @return None.
 */
void I2C_SetPrescaler(uint16_t I2C_ClkDiv)
{
    /* Check the parameters. */
    assert_param(IS_I2C_CLKDIV(I2C_ClkDiv));

    MDR_I2C->PRL = I2C_ClkDiv & I2C_PRL_PR_Msk;
    MDR_I2C->PRH = I2C_ClkDiv >> 8;
}

/**
 * @brief  Return the I2C prescaler registers value.
 * @param  None.
 * @return Prescaler registers value.
 */
uint16_t I2C_GetPrescaler(void)
{
    return (uint16_t)((MDR_I2C->PRH << 8) | (MDR_I2C->PRL));
}

/**
 * @brief  Transmit an 7-bit address (1 byte) to select a slave device.
 * @param  Address: Specify the slave 7-bit address which is to be transmitted.
 * @param  Direction: @ref I2C_TransferDirection_TypeDef - specify whether
 *         the I2C device will be a transmitter or a receiver.
 * @return None.
 */
void I2C_Send7BitAddress(uint8_t Address, I2C_TransferDirection_TypeDef Direction)
{
    /* Check the parameters. */
    assert_param(IS_I2C_ADDR_7BIT(Address));
    assert_param(IS_I2C_TRANSFER_DIRECTION(Direction));

    MDR_I2C->TXD = (((uint32_t)Address << 1) | (uint32_t)Direction);
    MDR_I2C->CMD = I2C_CMD_START | I2C_CMD_WR;
}

/**
 * @brief  Send a byte via the I2C peripheral.
 * @param  ByteToSend: Byte to be transmitted.
 * @return None.
 */
void I2C_SendData(uint8_t ByteToSend)
{
    MDR_I2C->TXD = ByteToSend;
    MDR_I2C->CMD = I2C_CMD_WR;
}

/**
 * @brief  Generate I2C STOP condition.
 * @param  None.
 * @return None.
 */
void I2C_SendSTOP(void)
{
    MDR_I2C->CMD = I2C_CMD_STOP;
}

/**
 * @brief  Start receiving the data from the slave.
 * @param  Acknowledge - @ref I2C_MasterToSlaveAcknowledge_TypeDef - specify
 *         the acknowledge state at the end of the data receiving.
 * @return None.
 */
void I2C_StartReceiveData(I2C_MasterToSlaveAcknowledge_TypeDef Acknowledge)
{
    /* Check the parameters. */
    assert_param(IS_I2C_SEND_ACKNOWLEDGE(Acknowledge));

    MDR_I2C->CMD = I2C_CMD_RD | (uint32_t)Acknowledge;
}

/**
 * @brief  Return data byte received from the slave.
 * @param  None.
 * @return Data byte received from the slave.
 */
uint8_t I2C_ReceiveData(void)
{
    return (uint8_t)(MDR_I2C->RXD);
}

/**
 * @brief  Enable or disable the I2C interrupt.
 * @param  NewState: @ref FunctionalState - a new state of the I2C interrupt.
 * @return None.
 */
void I2C_ITConfig(FunctionalState NewState)
{
    uint32_t TempCTR;

    /* Check the parameters. */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    TempCTR = MDR_I2C->CTR;

    /* Form a new value. */
    if (NewState != DISABLE) {
        /* Enable the I2C interrupt by setting the EN_INT bit in the CTR register. */
        TempCTR |= I2C_CTR_EN_INT;
    } else {
        /* Disable the I2C interrupt by resetting the EN_INT bit in the CTR register. */
        TempCTR &= ~I2C_CTR_EN_INT;
    }

    /* Configure the CTR register with a new value. */
    MDR_I2C->CTR = TempCTR;
}

/**
 * @brief  Check whether the I2C interrupt has occurred or not.
 * @param  None.
 * @return @ref ITStatus - the current state of I2C_STA_INT (SET or RESET).
 */
ITStatus I2C_GetITStatus(void)
{
    ITStatus Status;

    if ((MDR_I2C->STA & I2C_STA_INT) == I2C_STA_INT) {
        Status = SET;
    } else {
        Status = RESET;
    }

    return Status;
}

/**
 * @brief  Clear the I2C_STA_INT interrupt pending bit.
 * @param  None.
 * @return None.
 */
void I2C_ClearITFlagStatus(void)
{
    MDR_I2C->CMD |= I2C_CMD_CLRINT;
}

/**
 * @brief  Check whether the specified I2C flag is set or not.
 * @param  Flag: Specify a flag to check.
 *         This parameter can be one of the following values:
 *           @arg I2C_FLAG_CMD_NACK:        Master will send NACK after reading from a slave.
 *           @arg I2C_FLAG_CMD_ACK:         Master will send ACK after reading from a slave.
 *           @arg I2C_FLAG_CMD_WR:          A master to slave transfer is in progress.
 *           @arg I2C_FLAG_CMD_NO_WR:       There is no a master to slave transfer.
 *           @arg I2C_FLAG_CMD_RD:          A slave to master transfer is in progress.
 *           @arg I2C_FLAG_CMD_NO_RD:       There is no a slave to master transfer.
 *           @arg I2C_FLAG_CMD_STOP:        Transfer STOP condition is selected.
 *           @arg I2C_FLAG_CMD_NO_STOP:     STOP condition is reset.
 *           @arg I2C_FLAG_CMD_START:       Transfer START condition is selected.
 *           @arg I2C_FLAG_CMD_NO_START:    START condition is reset.
 *           @arg I2C_FLAG_STA_IRQ:         The I2C interrupt pending flag is set.
 *           @arg I2C_FLAG_STA_NO_IRQ:      The I2C interrupt pending flag is cleared.
 *           @arg I2C_FLAG_STA_TRANSFER:    Transfer is in progress.
 *           @arg I2C_FLAG_STA_NO_TRANSFER: There is no transfer.
 *           @arg I2C_FLAG_STA_LOST_ARB:    Arbitration is lost at the transfer of the last byte.
 *           @arg I2C_FLAG_STA_ARB_OK:      Arbitration is ok at the transfer of the last byte.
 *           @arg I2C_FLAG_STA_BUS_BUSY:    Some device holds the I2C bus.
 *           @arg I2C_FLAG_STA_BUS_FREE:    I2C bus is free (SDA = SCL = 1).
 *           @arg I2C_FLAG_STA_SLAVE_NACK:  Negative acknowledge (NACK) has been received from a slave.
 *           @arg I2C_FLAG_STA_SLAVE_ACK:   Acknowledge (ACK) has been received from a slave.
 * @return A new state of I2C_FLAG (SET or RESET).
 */
FlagStatus I2C_GetFlagStatus(uint32_t Flag)
{
    FlagStatus Status;

    /* Check the parameters. */
    assert_param(IS_I2C_FLAG(Flag));

    if ((I2C_GetStatus() & Flag) == 0) {
        Status = RESET;
    } else {
        Status = SET;
    }

    return Status;
}

/**
 * @brief  Return a combined value of the I2C flags.
 * @param  None.
 * @return The I2C flags combined value.
 */
uint32_t I2C_GetStatus(void)
{
    uint32_t Status;

    Status = MDR_I2C->CMD | (MDR_I2C->STA << 8);
    Status |= ~Status << 16;

    return Status;
}

/** @} */ /* End of the group I2C_Exported_Functions */

/** @} */ /* End of the group I2C */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_i2c.c */

