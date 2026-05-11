/**
 ******************************************************************************
 * @file    core_extension_xgost.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    15/04/2025
 * @brief   RISC-V xGost Extension Access Layer Header File.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CORE_XGOST
#define CORE_XGOST

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "core_config.h"
#include "core_types.h"
#include "core_compiler.h"

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

#if defined(CORE_EXTENSION_XGOST)

/** @addtogroup CORE_EXTENSION_XGOST Core xGost Extension
 * @{
 */

/** @defgroup CORE_EXTENSION_XGOST_Exported_Defines Core xGost Extension Exported Defines
 * @brief XGOST instructions are R type.
 *        R type instructions syntax: ".insn r opcode, func3, func7, rd, rs1, rs2".
 * @{
 */

#if !defined(__ASSEMBLER__) && !defined(__IASMRISCV__)

#if (__riscv_xlen == 32)

/**
 * @brief  Perform an S-transform used in Magma and Streebog (4.1.1 GOST R 34.12-2015 and 5.2 GOST R 34.11-2015)
 *         on each byte of the XOR result of registers rs1 and rs2 and
 *         write the results to the corresponding bytes of returned value.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return S-transform result.
 */
__STATIC_FORCEINLINE uint32_t gost32sb(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32sbResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x42, %0, %1, %2" : "=r"(GOST32sbResult) : "r"(rs1), "r"(rs2));
    return GOST32sbResult;
}

/**
 * @brief Perform an inverse S-transform used in Magma and Streebog (4.1.1 GOST R 34.12-2015 and 5.2 GOST R 34.11-2015)
 *        for each byte of the rs1 register and perform an exclusive OR with the rs2 register on the result,
 *        after which it return the result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Inverse S-transform result.
 */
__STATIC_FORCEINLINE uint32_t gost32sbi(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32sbiResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x43, %0, %1, %2" : "=r"(GOST32sbiResult) : "r"(rs1), "r"(rs2));
    return GOST32sbiResult;
}

/**
 * @brief  Perform partial calculation of a L-transform used in Kuznechik (GOST R 34.12-2015) for 32-bit parts of 128-bit block.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Calculated partial L-transform result.
 */
__STATIC_FORCEINLINE uint32_t gost32kule(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32kuleResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x67, %0, %1, %2" : "=r"(GOST32kuleResult) : "r"(rs1), "r"(rs2));
    return GOST32kuleResult;
}

/**
 * @brief  Perform partial calculation of a L-transform used in Kuznechik (GOST R 34.12-2015) for 32-bit parts of 128-bit block.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Calculated partial L-transform result.
 */
__STATIC_FORCEINLINE uint32_t gost32kuleh(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32kulehResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x66, %0, %1, %2" : "=r"(GOST32kulehResult) : "r"(rs1), "r"(rs2));
    return GOST32kulehResult;
}

/**
 * @brief  Perform partial calculation of an inverse L-transform used in Kuznechik (GOST R 34.12-2015) for 32-bit parts of 128-bit block.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Calculated partial inverse L-transform result.
 */
__STATIC_FORCEINLINE uint32_t gost32kuld(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32kuldResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x64, %0, %1, %2" : "=r"(GOST32kuldResult) : "r"(rs1), "r"(rs2));
    return GOST32kuldResult;
}

/**
 * @brief  Perform partial calculation of an inverse L-transform used in Kuznechik (GOST R 34.12-2015) for 32-bit parts of 128-bit block.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Calculated partial inverse L-transform result.
 */
__STATIC_FORCEINLINE uint32_t gost32kuldh(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32kuldhResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x65, %0, %1, %2" : "=r"(GOST32kuldhResult) : "r"(rs1), "r"(rs2));
    return GOST32kuldhResult;
}

/**
 * @brief  Perform a G[k] transform used in Magma (GOST R 34.12-2015) for 64-bit block.
 * @param  rs1: Upper 32-bits of the original data block.
 * @param  rs2: 32-bit round key.
 * @return G[k] transform result.
 */
__STATIC_FORCEINLINE uint32_t gost32mgma(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32mgmaResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x68, %0, %1, %2" : "=r"(GOST32mgmaResult) : "r"(rs1), "r"(rs2));
    return GOST32mgmaResult;
}

/**
 * @brief  Perform byte transpose of registers rs1 and rs2,
 *         according to the following algorithm:
 *         uint32_t gost32tau1(uint32_t rs1, uint32_t rs2)
 *         {
 *             uint32_t rd;
 *             rd = (((rs1 >> 0) & 0xFF) << 0) |
 *             (((rs1 >> 16) & 0xFF) << 8) |
 *             (((rs2 >> 0) & 0xFF) << 16) |
 *             (((rs2 >> 16) & 0xFF) << 24);
 *             return rd;
 *         }
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Byte transpose result.
 */
__STATIC_FORCEINLINE uint32_t gost32tau1(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32tau1Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x50, %0, %1, %2" : "=r"(GOST32tau1Result) : "r"(rs1), "r"(rs2));
    return GOST32tau1Result;
}

/**
 * @brief  Perform byte transpose of registers rs1 and rs2,
 *         according to the following algorithm:
 *         uint32_t gost32tau2(uint32_t rs1, uint32_t rs2)
 *         {
 *             uint32_t rd;
 *             rd = (((rs1 >> 8) & 0xFF) << 0) |
 *             (((rs1 >> 24) & 0xFF) << 8) |
 *             (((rs2 >> 8) & 0xFF) << 16) |
 *             (((rs2 >> 24) & 0xFF) << 24);
 *             return rd;
 *         }
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Byte transpose result.
 */
__STATIC_FORCEINLINE uint32_t gost32tau2(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32tau2Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x51, %0, %1, %2" : "=r"(GOST32tau2Result) : "r"(rs1), "r"(rs2));
    return GOST32tau2Result;
}

/**
 * @brief  Return lower part of l-transform result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Lower part of l-transform.
 */
__STATIC_FORCEINLINE uint32_t gost32lin1(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32lin1Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x52, %0, %1, %2" : "=r"(GOST32lin1Result) : "r"(rs1), "r"(rs2));
    return GOST32lin1Result;
}

/**
 * @brief  Return upper part of l-transform result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Upper part of l-transform.
 */
__STATIC_FORCEINLINE uint32_t gost32lin2(uint32_t rs1, uint32_t rs2)
{
    uint32_t GOST32lin2Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x53, %0, %1, %2" : "=r"(GOST32lin2Result) : "r"(rs1), "r"(rs2));
    return GOST32lin2Result;
}

#elif (__riscv_xlen == 64)

/**
 * @brief  Perform a S-transform used in Magma and Streebog (4.1.1 GOST R 34.12-2015 and 5.2 GOST R 34.11-2015)
 *         on each byte of the XOR result of registers rs1 and rs2 and
 *         write the results to the corresponding bytes of returned value.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return S-transform result.
 */
__STATIC_FORCEINLINE uint64_t gost64sb(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64sbResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x02, %0, %1, %2" : "=r"(GOST64sbResult) : "r"(rs1), "r"(rs2));
    return GOST64sbResult;
}

/**
 * @brief Perform an inverse S-transform used in Magma and Streebog (4.1.1 GOST R 34.12-2015 and 5.2 GOST R 34.11-2015)
 *        for each byte of the rs1 register and perform an exclusive OR with the rs2 register on the result,
 *        after which it return the result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Inverse S-transform result.
 */
__STATIC_FORCEINLINE uint64_t gost64sbi(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64sbiResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x03, %0, %1, %2" : "=r"(GOST64sbiResult) : "r"(rs1), "r"(rs2));
    return GOST64sbiResult;
}

/**
 * @brief  Perform a L-transform used in Kuznechik (GOST R 34.12-2015) for 64-bit parts of 128-bit block.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return L-transform result for upper 64-bit part (if rs1 - lower 64-bit part of original data block, rs2 - upper 64-bit part of original data block) or
 *         L-transform result for lower 64-bit part (if rs1 - upper 64-bit part of L-transform result, rs2 - lower 64-bit part of original data block).
 */
__STATIC_FORCEINLINE uint64_t gost64kule(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64kuleResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x27, %0, %1, %2" : "=r"(GOST64kuleResult) : "r"(rs1), "r"(rs2));
    return GOST64kuleResult;
}

/**
 * @brief  Perform an inverse L-transform used in Kuznechik (GOST R 34.12-2015) for 64-bit parts of 128-bit block same way as gost64kule, but return lower 64-bits of result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Inverse L-transform result (same way as gost64kule, but return lower 64-bits of result).
 */
__STATIC_FORCEINLINE uint64_t gost64kuld(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64kuldResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x24, %0, %1, %2" : "=r"(GOST64kuldResult) : "r"(rs1), "r"(rs2));
    return GOST64kuldResult;
}

/**
 * @brief  Perform a G[k] transform used in Magma (GOST R 34.12-2015) for 64-bit block.
 * @param  rs1: Original data block.
 * @param  rs2: 32-bit round key, should be placed in lower bits of rs2.
 * @return G[k] transform result.
 */
__STATIC_FORCEINLINE uint64_t gost64mgma(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64mgmaResult;
    __ASM volatile(".insn r 0x2B, 0x4, 0x28, %0, %1, %2" : "=r"(GOST64mgmaResult) : "r"(rs1), "r"(rs2));
    return GOST64mgmaResult;
}

/**
 * @brief  Perform byte transpose of registers rs1 and rs2,
 *         according to the following algorithm:
 *         uint64_t gost64tau1(uint64_t rs1, uint64_t rs2)
 *         {
 *             uint64_t rd;
 *             rd = (((rs1 >> 0) & 0xFF) << 0) |
 *             (((rs1 >> 16) & 0xFF) << 8) |
 *             (((rs1 >> 32) & 0xFF) << 16) |
 *             (((rs1 >> 48) & 0xFF) << 24) |
 *             (((rs2 >> 0) & 0xFF) << 32) |
 *             (((rs2 >> 16) & 0xFF) << 40) |
 *             (((rs2 >> 32) & 0xFF) << 48) |
 *             (((rs2 >> 48) & 0xFF) << 56);
 *             return rd;
 *         }
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Byte transpose result.
 */
__STATIC_FORCEINLINE uint64_t gost64tau1(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64tau1Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x10, %0, %1, %2" : "=r"(GOST64tau1Result) : "r"(rs1), "r"(rs2));
    return GOST64tau1Result;
}

/**
 * @brief  Perform byte transpose of registers rs1 and rs2,
 *         according to the following algorithm:
 *         uint64_t gost64tau2(uint64_t rs1, uint64_t rs2)
 *         {
 *             uint64_t rd;
 *             rd = (((rs1 >> 8) & 0xFF) << 0) |
 *             (((rs1 >> 24) & 0xFF) << 8) |
 *             (((rs1 >> 40) & 0xFF) << 16) |
 *             (((rs1 >> 56) & 0xFF) << 24) |
 *             (((rs2 >> 8) & 0xFF) << 32) |
 *             (((rs2 >> 24) & 0xFF) << 40) |
 *             (((rs2 >> 40) & 0xFF) << 48) |
 *             (((rs2 >> 56) & 0xFF) << 56);
 *             return rd;
 *         }
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Byte transpose result.
 */
__STATIC_FORCEINLINE uint64_t gost64tau2(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64tau2Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x11, %0, %1, %2" : "=r"(GOST64tau2Result) : "r"(rs1), "r"(rs2));
    return GOST64tau2Result;
}

/**
 * @brief  Perform byte transpose of registers rs1 and rs2 same as gost64tau1, perform l-transform on byte transpose result and return l-transform result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Byte transpose result after l-transform.
 */
__STATIC_FORCEINLINE uint64_t gost64lin1(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64lin1Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x12, %0, %1, %2" : "=r"(GOST64lin1Result) : "r"(rs1), "r"(rs2));
    return GOST64lin1Result;
}

/**
 * @brief  Perform byte transpose of registers rs1 and rs2 same as gost64tau2, perform l-transform on byte transpose result and return l-transform result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Byte transpose result after l-transform.
 */
__STATIC_FORCEINLINE uint64_t gost64lin2(uint64_t rs1, uint64_t rs2)
{
    uint64_t GOST64lin2Result;
    __ASM volatile(".insn r 0x2B, 0x4, 0x13, %0, %1, %2" : "=r"(GOST64lin2Result) : "r"(rs1), "r"(rs2));
    return GOST64lin2Result;
}

#endif /* (__riscv_xlen == 64) */

/** @addtogroup CORE_EXTENSION_XGOST_Exported_Functions Core xGost Extension Exported Functions
 * @{
 */

#if (__riscv_xlen == 32)

/**
 * @brief  Perform a S-transform used in Magma and Streebog (4.1.1 GOST R 34.12-2015 and 5.2 GOST R 34.11-2015)
 *         on each byte of the XOR result of registers rs1 and rs2 and
 *         write the results to the corresponding bytes of returned value.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return S-transform result.
 */
__STATIC_INLINE uint64_t gost64sb(uint64_t rs1, uint64_t rs2)
{
    uint64_t        rd = 0;
    uint32_t*       r  = (uint32_t*)(&(rd));
    const uint32_t* r1 = (const uint32_t*)(&(rs1));
    const uint32_t* r2 = (const uint32_t*)(&(rs2));
    r[0]               = gost32sb(r1[0], r2[0]);
    r[1]               = gost32sb(r1[1], r2[1]);
    return rd;
}

/**
 * @brief Perform an inverse S-transform used in Magma and Streebog (4.1.1 GOST R 34.12-2015 and 5.2 GOST R 34.11-2015)
 *        for each byte of the rs1 register and perform an exclusive OR with the rs2 register on the result,
 *        after which it return the result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Inverse S-transform result.
 */
__STATIC_INLINE uint64_t gost64sbi(uint64_t rs1, uint64_t rs2)
{
    uint64_t        rd = 0;
    uint32_t*       r  = (uint32_t*)(&(rd));
    const uint32_t* r1 = (const uint32_t*)(&(rs1));
    const uint32_t* r2 = (const uint32_t*)(&(rs2));
    r[0]               = gost32sbi(r1[0], r2[0]);
    r[1]               = gost32sbi(r1[1], r2[1]);
    return rd;
}

/**
 * @brief  Perform an inverse L-transform used in Kuznechik (GOST R 34.12-2015) for 64-bit parts of 128-bit block same way as gost64kule, but return lower 64-bits of result.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Inverse L-transform result (same way as gost64kule, but return lower 64-bits of result).
 */
__STATIC_INLINE uint64_t gost64kuld(uint64_t rs1, uint64_t rs2)
{
    uint64_t        rd = 0;
    uint32_t*       r  = (uint32_t*)(&(rd));
    const uint32_t* r1 = (const uint32_t*)(&(rs1));
    const uint32_t* r2 = (const uint32_t*)(&(rs2));
    uint32_t        tmp;
    tmp  = gost32kuld(r2[0], r2[1]);
    r[0] = gost32kuldh(r1[0], r1[1]);
    r[0] ^= tmp;
    tmp  = gost32kuld(r2[1], r[0]);
    r[1] = gost32kuldh(r1[1], r2[0]);
    r[1] ^= tmp;
    return rd;
}

/**
 * @brief  Perform a L-transform used in Kuznechik (GOST R 34.12-2015) for 64-bit parts of 128-bit block.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return L-transform result for upper 64-bit part (if rs1 - lower 64-bit part of original data block, rs2 - upper 64-bit part of original data block) or
 *         L-transform result for lower 64-bit part (if rs1 - upper 64-bit part of L-transform result, rs2 - lower 64-bit part of original data block).
 */
__STATIC_INLINE uint64_t gost64kule(uint64_t rs1, uint64_t rs2)
{
    uint64_t        rd = 0;
    uint32_t*       r  = (uint32_t*)(&(rd));
    const uint32_t* r1 = (const uint32_t*)(&(rs1));
    const uint32_t* r2 = (const uint32_t*)(&(rs2));
    uint32_t        tmp;
    tmp  = gost32kule(r2[0], r2[1]);
    r[1] = gost32kuleh(r1[0], r1[1]);
    r[1] ^= tmp;
    tmp  = gost32kule(r1[1], r2[0]);
    r[0] = gost32kuleh(r[1], r1[0]);
    r[0] ^= tmp;
    return rd;
}

/**
 * @brief  Perform a G[k] transform used in Magma (GOST R 34.12-2015) for 64-bit block.
 * @param  rs1: Original data block.
 * @param  rs2: 32-bit round key, should be placed in lower bits of rs2.
 * @return G[k] transform result.
 */
__STATIC_INLINE uint64_t gost64mgma(uint64_t rs1, uint32_t rs2)
{
    uint64_t        rd = 0;
    uint32_t*       r  = (uint32_t*)(&(rd));
    const uint32_t* r1 = (const uint32_t*)(&(rs1));
    r[1]               = gost32mgma(r1[1], rs2);
    r[1] ^= r1[0];
    r[0] = r1[1];
    return rd;
}

#endif /* (__riscv_xlen == 32) */

/** @} */ /* End of group CORE_EXTENSION_XGOST_Exported_Functions */

#endif /* !__ASSEMBLER__ && !__IASMRISCV__ */

/** @} */ /* End of group CORE_EXTENSION_XGOST_Exported_Defines */

/** @} */ /* End of the group CORE_EXTENSION_XGOST */

#endif /* CORE_EXTENSION_XGOST */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_XGOST */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_extension_xgost.h */

