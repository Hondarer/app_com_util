/**
 *******************************************************************************
 *  @file           sys/stat.h
 *  @brief          stat 系 CRT 抽象 API。
 *  @author         Tetsuo Honda
 *  @date           2026/04/22
 *
 *  @copyright      Copyright (C) Tetsuo Honda. 2026. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef COM_UTIL_CRT_SYS_STAT_H
#define COM_UTIL_CRT_SYS_STAT_H

#include <stdarg.h>
#include <sys/stat.h>
#include <com_util/base/compiler.h>
#include <com_util/base/platform.h>
#include <com_util_export.h>

#ifndef COM_UTIL_FILE_STAT_T_DEFINED
#define COM_UTIL_FILE_STAT_T_DEFINED
#if defined(PLATFORM_LINUX)
typedef struct stat com_util_file_stat_t;
#elif defined(PLATFORM_WINDOWS)
typedef struct _stat64 com_util_file_stat_t;
#endif /* PLATFORM_ */
#endif /* COM_UTIL_FILE_STAT_T_DEFINED */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    COM_UTIL_EXPORT int COM_UTIL_API com_util_stat(com_util_file_stat_t *buf,
                                                    const char       *path);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_mkdir(const char *path);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_stat_fmt(com_util_file_stat_t *buf,
                                                        const char       *format,
                                                        ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 3)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vstat_fmt(com_util_file_stat_t *buf,
                                                         const char       *format,
                                                         va_list           args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 0)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_mkdir_fmt(const char *format, ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 1, 2)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vmkdir_fmt(const char *format,
                                                          va_list     args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 1, 0)))
#endif /* COMPILER_GCC */
        ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COM_UTIL_CRT_SYS_STAT_H */
