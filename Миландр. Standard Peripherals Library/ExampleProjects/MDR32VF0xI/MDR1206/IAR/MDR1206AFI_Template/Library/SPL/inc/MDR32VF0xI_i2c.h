/**
 *******************************************************************************
 * @file    MDR32VF0xI_i2c.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    14/05/2025
 * @brief   This file contains all the functions prototypes for the I2C
 *          firmware library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MDR32VF0xI_I2C_H
#define MDR32VF0xI_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32VF0xI_config.h"

/** @addtogroup MDR32VF0xI_StdPeriph_Driver MDR32VF0xI Standard Peripheral Driver
 * @{
 */

/** @addtogroup I2C I2C
 * @{
 */

/** @defgroup I2C_Exported_Types I2C Exported Types
 * @{
 */

/**
 * @brief I2C transfer direction.
 */
typedef enum {
    I2C_DIR_TRANSMITTER = ((uint32_t)0x0), /*!< Transmitter mode. */
    I2C_DIR_RECEIVER    = ((uint32_t)0x1)  /*!< Receiver mode. */
} I2C_TransferDirection_TypeDef;

#define IS_I2C_TRANSFER_DIRECTION(DIRECTION) (((DIRECTION) == I2C_DIR_TRANSMITTER) || \
                                              ((DIRECTION) == I2C_DIR_RECEIVER))

/**
 * @brief I2C master to slave acknowledge.
 */
typedef enum {
    I2C_SEND_TO_SLAVE_ACK  = (((uint32_t)0x0) << I2C_CMD_ACK_Pos), /*!< Send acknowledge (ACK). */
    I2C_SEND_TO_SLAVE_NACK = (((uint32_t)0x1) << I2C_CMD_ACK_Pos)  /*!< Send negative acknowledge (NACK). */
} I2C_MasterToSlaveAcknowledge_TypeDef;

#define IS_I2C_SEND_ACKNOWLEDGE(ACK) (((ACK) == I2C_SEND_TO_SLAVE_ACK) || \
                                      ((ACK) == I2C_SEND_TO_SLAVE_NACK))

/** @defgroup I2C_FLAGS I2C Status Flags Definition
 * @{
 */

/**
 * @brief Flags based on the I2C_CMD register.
 *        These flags are the copies of the corresponding I2C_CMD register bits.
 */
typedef enum {
    I2C_FLAG_CMD_NACK  = (I2C_CMD_ACK << 0),  /*!< The master will send NACK after reading from a slave. */
    I2C_FLAG_CMD_WR    = (I2C_CMD_WR << 0),   /*!< A master to slave transfer is in progress. */
    I2C_FLAG_CMD_RD    = (I2C_CMD_RD << 0),   /*!< A slave to master transfer is in progress. */
    I2C_FLAG_CMD_STOP  = (I2C_CMD_STOP << 0), /*!< The STOP condition transfer is selected. */
    I2C_FLAG_CMD_START = (I2C_CMD_START << 0) /*!< The START condition transfer is selected. */
} I2C_CommandFlags_TypeDef;

/**
 * @brief Flags based on I2C_STA register.
 *        These flags are the copies of the corresponding I2C_STA register bits.
 */
typedef enum {
    I2C_FLAG_STA_IRQ        = (I2C_STA_INT << 8),      /*!< The I2C interrupt flag is set. */
    I2C_FLAG_STA_TRANSFER   = (I2C_STA_TR_PROG << 8),  /*!< The transfer is in progress (I2C_FLAG_CMD_WR | I2C_FLAG_CMD_RD). */
    I2C_FLAG_STA_LOST_ARB   = (I2C_STA_LOST_ARB << 8), /*!< The arbitration is lost at the transfer of the last byte. */
    I2C_FLAG_STA_BUS_BUSY   = (I2C_STA_BUSY << 8),     /*!< Some device holds the I2C bus. */
    I2C_FLAG_STA_SLAVE_NACK = (I2C_STA_RX_ACK << 8)    /*!< Negative acknowledge (NACK) has been received from a slave. */
} I2C_Status_TypeDef;

/** @} */ /* End of the group I2C_FLAGS */

/** @} */ /* End of the group I2C_Exported_Types */

/** @defgroup I2C_Exported_Defines I2C Exported Defines
 * @{
 */

/** @defgroup I2C_CLKDIV I2C Clock Divider
 * @{
 */

#define IS_I2C_CLKDIV(CLKDIV) (((CLKDIV) >> 16) == 0)

/** @} */ /* End of the group I2C_CLKDIV */

/** @defgroup I2C_ADDR I2C Address
 * @{
 */

#define IS_I2C_ADDR_7BIT(ADDR) (((ADDR) & ~((uint32_t)0x7F)) == 0)

/** @} */ /* End of the group I2C_ADDR */

/** @addtogroup I2C_FLAGS_DEF I2C Status Software Flags Definition
 * @{
 */

/**
 * @brief Software flags.
 *        These flags are calculated by I2C firmware library.
 */
#define I2C_FLAG_CMD_ACK         ((uint32_t)I2C_FLAG_CMD_NACK << 16)       /*!< The master will send ACK after reading from a slave (inversion of the I2C_FLAG_CMD_NACK flag). */
#define I2C_FLAG_CMD_NO_WR       ((uint32_t)I2C_FLAG_CMD_WR << 16)         /*!< No master to slave transfer (inversion of the I2C_FLAG_CMD_WR flag). */
#define I2C_FLAG_CMD_NO_RD       ((uint32_t)I2C_FLAG_CMD_RD << 16)         /*!< No slave to master transfer (inversion of the I2C_FLAG_CMD_RD). */
#define I2C_FLAG_CMD_NO_STOP     ((uint32_t)I2C_FLAG_CMD_STOP << 16)       /*!< STOP condition is reset (inversion of the I2C_FLAG_CMD_STOP flag). */
#define I2C_FLAG_CMD_NO_START    ((uint32_t)I2C_FLAG_CMD_START << 16)      /*!< START condition is reset (inversion of the I2C_FLAG_CMD_START flag). */
#define I2C_FLAG_STA_NO_IRQ      ((uint32_t)I2C_FLAG_STA_IRQ << 16)        /*!< The I2C interrupt flag is cleared (inversion of the I2C_FLAG_STA_IRQ flag). */
#define I2C_FLAG_STA_NO_TRANSFER ((uint32_t)I2C_FLAG_STA_TRANSFER << 16)   /*!< No transfer (inversion of the I2C_FLAG_STA_TRANSFER flag). */
#define I2C_FLAG_STA_ARB_OK      ((uint32_t)I2C_FLAG_STA_LOST_ARB << 16)   /*!< Arbitration is OK (inversion of the I2C_FLAG_STA_LOST_ARB flag). */
#define I2C_FLAG_STA_BUS_FREE    ((uint32_t)I2C_FLAG_STA_BUS_BUSY << 16)   /*!< I2C bus is free (inversion of the I2C_FLAG_STA_BUS_BUSY flag). */
#define I2C_FLAG_STA_SLAVE_ACK   ((uint32_t)I2C_FLAG_STA_SLAVE_NACK << 16) /*!< Acknowledge has been received from a slave (inversion of the I2C_FLAG_STA_SLAVE_NACK flag). */

#define IS_I2C_FLAG(FLAG)        (((FLAG) == I2C_FLAG_CMD_NACK) || \
                           ((FLAG) == I2C_FLAG_CMD_WR) ||          \
                           ((FLAG) == I2C_FLAG_CMD_RD) ||          \
                           ((FLAG) == I2C_FLAG_CMD_STOP) ||        \
                           ((FLAG) == I2C_FLAG_CMD_START) ||       \
                           ((FLAG) == I2C_FLAG_STA_IRQ) ||         \
                           ((FLAG) == I2C_FLAG_STA_TRANSFER) ||    \
                           ((FLAG) == I2C_FLAG_STA_LOST_ARB) ||    \
                           ((FLAG) == I2C_FLAG_STA_BUS_BUSY) ||    \
                           ((FLAG) == I2C_FLAG_STA_SLAVE_NACK) ||  \
                           ((FLAG) == I2C_FLAG_CMD_NO_WR) ||       \
                           ((FLAG) == I2C_FLAG_CMD_NO_RD) ||       \
                           ((FLAG) == I2C_FLAG_CMD_ACK) ||         \
                           ((FLAG) == I2C_FLAG_CMD_NO_STOP) ||     \
                           ((FLAG) == I2C_FLAG_CMD_NO_START) ||    \
                           ((FLAG) == I2C_FLAG_STA_NO_IRQ) ||      \
                           ((FLAG) == I2C_FLAG_STA_NO_TRANSFER) || \
                           ((FLAG) == I2C_FLAG_STA_ARB_OK) ||      \
                           ((FLAG) == I2C_FLAG_STA_BUS_FREE) ||    \
                           ((FLAG) == I2C_FLAG_STA_SLAVE_ACK))

#define I2C_FLAGS_Msk (I2C_FLAG_CMD_NACK |        \
                       I2C_FLAG_CMD_WR |          \
                       I2C_FLAG_CMD_RD |          \
                       I2C_FLAG_CMD_STOP |        \
                       I2C_FLAG_CMD_START |       \
                       I2C_FLAG_STA_IRQ |         \
                       I2C_FLAG_STA_TRANSFER |    \
                       I2C_FLAG_STA_LOST_ARB |    \
                       I2C_FLAG_STA_BUS_BUSY |    \
                       I2C_FLAG_STA_SLAVE_NACK |  \
                       I2C_FLAG_CMD_NO_WR |       \
                       I2C_FLAG_CMD_NO_RD |       \
                       I2C_FLAG_CMD_ACK |         \
                       I2C_FLAG_CMD_NO_STOP |     \
                       I2C_FLAG_CMD_NO_START |    \
                       I2C_FLAG_STA_NO_IRQ |      \
                       I2C_FLAG_STA_NO_TRANSFER | \
                       I2C_FLAG_STA_ARB_OK |      \
                       I2C_FLAG_STA_BUS_FREE |    \
                       I2C_FLAG_STA_SLAVE_ACK)

#define IS_I2C_FLAGS(FLAGS) (((uint32_t)(FLAGS) & ~((uint32_t)I2C_FLAGS_Msk)) == 0)

/** @} */ /* End of the group I2C_FLAGS_DEF */

/** @} */ /* End of the group I2C_Exported_Defines */

/** @defgroup I2C_Exported_Functions I2C Exported Functions
 * @{
 */

void I2C_DeInit(void);

void            I2C_Cmd(FunctionalState NewState);
FunctionalState I2C_GetCmdState(void);

void     I2C_SetPrescaler(uint16_t I2C_ClkDiv);
uint16_t I2C_GetPrescaler(void);

void    I2C_Send7BitAddress(uint8_t Address, I2C_TransferDirection_TypeDef Direction);
void    I2C_SendData(uint8_t ByteToSend);
void    I2C_SendSTOP(void);
void    I2C_StartReceiveData(I2C_MasterToSlaveAcknowledge_TypeDef Acknowledge);
uint8_t I2C_ReceiveData(void);

void     I2C_ITConfig(FunctionalState NewState);
ITStatus I2C_GetITStatus(void);
void     I2C_ClearITFlagStatus(void);

FlagStatus I2C_GetFlagStatus(uint32_t Flag);
uint32_t   I2C_GetStatus(void);

/** @} */ /* End of the group I2C_Exported_Functions */

/** @} */ /* End of the group I2C */

/** @} */ /* End of the group MDR32VF0xI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32VF0xI_I2C_H */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE MDR32VF0xI_i2c.h */

