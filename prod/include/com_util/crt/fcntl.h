/**
 *******************************************************************************
 *  @file           fcntl.h
 *  @brief          fcntl 系 CRT 抽象 API。
 *  @author         Tetsuo Honda
 *  @date           2026/04/22
 *
 *  @copyright      Copyright (C) Tetsuo Honda. 2026. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef COM_UTIL_CRT_FCNTL_H
#define COM_UTIL_CRT_FCNTL_H

#include <stdarg.h>
#include <fcntl.h>
#include <com_util/base/compiler.h>
#include <com_util_export.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    COM_UTIL_EXPORT int COM_UTIL_API com_util_open(const char *path,
                                                    int         flags,
                                                    int         mode);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_open_fmt(int flags,
                                                        int mode,
                                                        const char *format,
                                                        ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 3, 4)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vopen_fmt(int flags,
                                                         int mode,
                                                         const char *format,
                                                         va_list args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 3, 0)))
#endif /* COMPILER_GCC */
        ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COM_UTIL_CRT_FCNTL_H */
