/**
 *******************************************************************************
 *  @file           unistd.h
 *  @brief          unistd/io 系 CRT 抽象 API。
 *  @author         Tetsuo Honda
 *  @date           2026/04/22
 *
 *  @copyright      Copyright (C) Tetsuo Honda. 2026. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef COM_UTIL_CRT_UNISTD_H
#define COM_UTIL_CRT_UNISTD_H

#include <stdarg.h>
#include <com_util/base/compiler.h>
#include <com_util/base/platform.h>
#include <com_util_export.h>

#if defined(PLATFORM_LINUX)
    #include <unistd.h>
#elif defined(PLATFORM_WINDOWS)
    #include <io.h>
#endif /* PLATFORM_ */

#ifdef DOXYGEN
    #define COM_UTIL_ACCESS_FMT_F_OK 0
    #define COM_UTIL_ACCESS_FMT_R_OK 4
    #define COM_UTIL_ACCESS_FMT_W_OK 2
#else /* !DOXYGEN */
    #if defined(PLATFORM_LINUX)
        #define COM_UTIL_ACCESS_FMT_F_OK F_OK
        #define COM_UTIL_ACCESS_FMT_R_OK R_OK
        #define COM_UTIL_ACCESS_FMT_W_OK W_OK
    #elif defined(PLATFORM_WINDOWS)
        #define COM_UTIL_ACCESS_FMT_F_OK 0
        #define COM_UTIL_ACCESS_FMT_R_OK 4
        #define COM_UTIL_ACCESS_FMT_W_OK 2
    #endif /* PLATFORM_ */
#endif     /* DOXYGEN */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    COM_UTIL_EXPORT int COM_UTIL_API com_util_access(const char *path,
                                                      int         mode);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_access_fmt(int mode,
                                                          const char *format,
                                                          ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 3)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vaccess_fmt(int mode,
                                                           const char *format,
                                                           va_list args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 0)))
#endif /* COMPILER_GCC */
        ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COM_UTIL_CRT_UNISTD_H */
