/**
 ******************************************************************************
 * @file    core_extension_zifencei.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   RISC-V Zifencei Extension Access Layer Header File.
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
#ifndef CORE_EXT_ZIFENCEI
#define CORE_EXT_ZIFENCEI

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

#if defined(CORE_EXTENSION_ZIFENCEI)

/** @addtogroup CORE_EXTENSION_ZIFENCEI Core Zifencei Extension
 * @{
 */

/** @defgroup CORE_EXTENSION_ZIFENCEI_Exported_Defines Core Zifencei Extension Exported Defines
 * @{
 */

/**
 * @brief  FENCE.I instruction. Used to synchronize the instruction and data streams.
 * @param  None.
 * @return None.
 */
__STATIC_FORCEINLINE void rv_fence_i(void)
{
    __ASM volatile("fence.i");
}

/** @} */ /* End of group CORE_EXTENSION_ZIFENCEI_Exported_Defines */

/** @} */ /* End of the group CORE_EXTENSION_ZIFENCEI */

#endif /* CORE_EXTENSION_ZIFENCEI */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_EXT_ZIFENCEI */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_extension_zifencei.h */

