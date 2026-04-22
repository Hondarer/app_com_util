/**
 *******************************************************************************
 *  @file           path.h
 *  @brief          CRT 抽象層で使用するパス関連定義。
 *  @author         Tetsuo Honda
 *  @date           2026/04/22
 *
 *  プラットフォームに依存せず、OS のパス最大長を表す定数 @ref PLATFORM_PATH_MAX
 *  を提供します。
 *
 *  @copyright      Copyright (C) Tetsuo Honda. 2026. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef COM_UTIL_CRT_PATH_H
#define COM_UTIL_CRT_PATH_H

#include <com_util/base/platform.h>

#ifdef DOXYGEN
    /**
     *  @def            PLATFORM_PATH_MAX
     *  @brief          OS 固有のパス最大長。
     */
    #define PLATFORM_PATH_MAX 4096
#else /* !DOXYGEN */
    #if defined(PLATFORM_LINUX)
        #include <limits.h>
        #define PLATFORM_PATH_MAX PATH_MAX
    #elif defined(PLATFORM_WINDOWS)
        #include <com_util/base/windows_sdk.h>
        #define PLATFORM_PATH_MAX MAX_PATH
    #endif /* PLATFORM_ */
#endif     /* DOXYGEN */

#endif /* COM_UTIL_CRT_PATH_H */
