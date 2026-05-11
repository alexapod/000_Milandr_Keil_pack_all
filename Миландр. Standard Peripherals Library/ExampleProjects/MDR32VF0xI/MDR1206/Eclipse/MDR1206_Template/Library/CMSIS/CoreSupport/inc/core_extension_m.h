/**
 ******************************************************************************
 * @file    core_extension_m.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   RISC-V M Extension Access Layer Header File.
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
#ifndef CORE_EXT_M
#define CORE_EXT_M

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

#if defined(CORE_EXTENSION_M)

/** @addtogroup CORE_EXTENSION_M Core M Extension
 * @{
 */

/** @defgroup CORE_EXTENSION_M_Exported_Defines Core M Extension Exported Defines
 * @{
 */

/**
 * @brief  Perform an XLEN-bit x XLEN-bit integer multiplication of rs1 by rs2 and
 *         return the lower XLEN bits.
 * @param  rs1: First input value.
 * @param  rs2: Second input value.
 * @return Lower XLEN bits of multiplication.
 */
__STATIC_FORCEINLINE uint_xlen_t rv_mul(uint_xlen_t rs1, uint_xlen_t rs2)
{
    uint_xlen_t lower_result;
    __ASM volatile("mul %0, %1, %2" : "=r"(lower_result) : "r"(rs1), "r"(rs2));
    return lower_result;
}

/**
 * @brief  Perform an XLEN-bit x XLEN-bit integer multiplication (signed x signed) of rs1 by rs2 and
 *         return the upper XLEN bits of the full 2 x XLEN-bit products.
 * @param  rs1: First input signed value.
 * @param  rs2: Second input signed value.
 * @return Upper XLEN bits of multiplication.
 */
__STATIC_FORCEINLINE int_xlen_t rv_mulh(int_xlen_t rs1, int_xlen_t rs2)
{
    int_xlen_t upper_result;
    __ASM volatile("mulh %0, %1, %2" : "=r"(upper_result) : "r"(rs1), "r"(rs2));
    return upper_result;
}

/**
 * @brief  Perform an XLEN-bit x XLEN-bit integer multiplication (unsigned x unsigned) of rs1 by rs2 and
 *         return the upper XLEN bits of the full 2 x XLEN-bit products.
 * @param  rs1: First input unsigned value.
 * @param  rs2: Second input unsigned value.
 * @return Upper XLEN bits of multiplication.
 */
__STATIC_FORCEINLINE uint_xlen_t rv_mulhu(uint_xlen_t rs1, uint_xlen_t rs2)
{
    uint_xlen_t upper_result;
    __ASM volatile("mulhu %0, %1, %2" : "=r"(upper_result) : "r"(rs1), "r"(rs2));
    return upper_result;
}

/**
 * @brief  Perform an XLEN-bit x XLEN-bit integer multiplication (signed x unsigned) of rs1 by rs2 and
 *         return the upper XLEN bits of the full 2 x XLEN-bit products.
 * @param  rs1: First input signed value.
 * @param  rs2: Second input unsigned value.
 * @return Upper XLEN bits of multiplication.
 */
__STATIC_FORCEINLINE int_xlen_t rv_mulhsu(int_xlen_t rs1, uint_xlen_t rs2)
{
    int_xlen_t upper_result;
    __ASM volatile("mulhsu %0, %1, %2" : "=r"(upper_result) : "r"(rs1), "r"(rs2));
    return upper_result;
}

/**
 * @brief  Perform an XLEN-bit by XLEN-bit signed integer division of rs1 by rs2 rounded towards zero.
 * @param  rs1: Signed value of the dividend.
 * @param  rs2: Signed value of the divisor.
 * @return XLEN-bit signed quotient of division.
 */
__STATIC_FORCEINLINE int_xlen_t rv_div(int_xlen_t rs1, int_xlen_t rs2)
{
    int_xlen_t result;
    __ASM volatile("div %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

/**
 * @brief  Perform an XLEN-bit by XLEN-bit unsigned integer division of rs1 by rs2 rounded towards zero.
 * @param  rs1: Unsigned value of the dividend.
 * @param  rs2: Unsigned value of the divisor.
 * @return XLEN-bit unsigned quotient of division.
 */
__STATIC_FORCEINLINE uint_xlen_t rv_divu(uint_xlen_t rs1, uint_xlen_t rs2)
{
    uint_xlen_t result;
    __ASM volatile("divu %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

/**
 * @brief  Perform an XLEN-bit by XLEN-bit signed integer remainder of rs1 by rs2.
 * @note   The sign of a nonzero result equals the sign of the dividend.
 * @param  rs1: Signed value of the dividend.
 * @param  rs2: Signed value of the divisor.
 * @return XLEN-bit signed remainder of division.
 */
__STATIC_FORCEINLINE int_xlen_t rv_rem(int_xlen_t rs1, int_xlen_t rs2)
{
    int_xlen_t result;
    __ASM volatile("rem %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

/**
 * @brief  Perform an XLEN-bit by XLEN-bit unsigned integer remainder of rs1 by rs2.
 * @param  rs1: Unsigned value of the dividend.
 * @param  rs2: Unsigned value of the divisor.
 * @return XLEN-bit unsigned remainder of division.
 */
__STATIC_FORCEINLINE uint_xlen_t rv_remu(uint_xlen_t rs1, uint_xlen_t rs2)
{
    uint_xlen_t result;
    __ASM volatile("remu %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

#if (__riscv_xlen == 64)

/**
 * @brief  Perform a integer multiplication of the lower 32 bits of rs1 and rs2 and
 *         return sign-extension of the lower 32 bits of the result.
 * @param  rs1: First input signed value.
 * @param  rs2: Second input signed value.
 * @return The lower 32 bits of the multiplication result, sign-extended to 64 bits.
 */
__STATIC_FORCEINLINE int64_t rv_mulw(int32_t rs1, int32_t rs2)
{
    int64_t lower_result;
    __ASM volatile("mulw %0, %1, %2" : "=r"(lower_result) : "r"(rs1), "r"(rs2));
    return lower_result;
}

/**
 * @brief  Perform a signed integer division of the lower 32 bits of rs1 by the lower 32 bits of rs2.
 * @param  rs1: Signed value of the dividend.
 * @param  rs2: Signed value of the divisor.
 * @return 32-bit quotient of division, sign-extended to 64 bits.
 */
__STATIC_FORCEINLINE int64_t rv_divw(int32_t rs1, int32_t rs2)
{
    int64_t result;
    __ASM volatile("divw %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

/**
 * @brief  Perform a unsigned integer division of the lower 32 bits of rs1 by the lower 32 bits of rs2.
 * @param  rs1: Unsigned value of the dividend.
 * @param  rs2: Unsigned value of the divisor.
 * @return 32-bit quotient of division, sign-extended to 64 bits.
 */
__STATIC_FORCEINLINE int64_t rv_divuw(uint32_t rs1, uint32_t rs2)
{
    int64_t result;
    __ASM volatile("divuw %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

/**
 * @brief  Perform a signed integer remainder of the lower 32 bits of rs1 by the lower 32 bits of rs2.
 * @param  rs1: Signed value of the dividend.
 * @param  rs2: Signed value of the divisor.
 * @return 32-bit remainder of division, sign-extended to 64 bits.
 */
__STATIC_FORCEINLINE int64_t rv_remw(int32_t rs1, int32_t rs2)
{
    int64_t result;
    __ASM volatile("remw %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

/**
 * @brief  Perform a unsigned integer remainder of the lower 32 bits of rs1 by the lower 32 bits of rs2.
 * @param  rs1: Unsigned value of the dividend.
 * @param  rs2: Unsigned value of the divisor.
 * @return 32-bit remainder of division, sign-extended to 64 bits.
 */
__STATIC_FORCEINLINE int64_t rv_remuw(uint32_t rs1, uint32_t rs2)
{
    int64_t result;
    __ASM volatile("remuw %0, %1, %2" : "=r"(result) : "r"(rs1), "r"(rs2));
    return result;
}

#endif /* (__riscv_xlen == 64) */

/** @} */ /* End of group CORE_EXTENSION_M_Exported_Defines */

/** @} */ /* End of the group CORE_EXTENSION_M */

#endif /* CORE_EXTENSION_M */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_EXT_M */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_extension_m.h */

