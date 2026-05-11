/**
 *******************************************************************************
 * @file    core_bm310s.h
 * @author  Milandr Application Team
 * @version V0.2.0
 * @date    28/04/2025
 * @brief   CMSIS BM-310S Core Peripheral Access Layer Header File.
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
#ifndef CORE_BM310S
#define CORE_BM310S

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup CORE_SUPPORT Core Support
 * @{
 */

/** @addtogroup CORE_BM310S BM-310S Core
 * @{
 */

/** @defgroup CORE_BM310S_Peripheral_Units BM310S Peripheral Units
 * @{
 */

#if defined(CLINT_PRESENT)
#include "core_clint.h"
#endif

#if defined(PLIC_PRESENT)
#include "core_plic.h"
#endif

#if defined(CLIC_PRESENT)
#include "core_clic.h"
#endif

#include "core_csr.h"

#if defined(PMP_PRESENT)
#include "core_pmp.h"
#endif

#if defined(CORE_EXTENSION_XGOST)
#include "core_extension_xgost.h"
#endif

#if defined(CORE_EXTENSION_M)
#include "core_extension_m.h"
#endif

#if defined(CORE_EXTENSION_ZICNTR)
#include "core_extension_zicntr.h"
#endif

#if defined(CORE_EXTENSION_ZIFENCEI)
#include "core_extension_zifencei.h"
#endif

/** @} */ /* End of group CORE_BM310S_Peripheral_Units */

/** @} */ /* End of the group CORE_BM310S */

/** @} */ /* End of the group CORE_SUPPORT */

#ifdef __cplusplus
} // extern "C" block end
#endif /* __cplusplus */

#endif /* CORE_BM310S */

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE core_bm310s.h */

