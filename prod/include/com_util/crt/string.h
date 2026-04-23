/**
 *******************************************************************************
 *  @file           string.h
 *  @brief          string 系 CRT 抽象 API。
 *  @author         Tetsuo Honda
 *  @date           2026/04/22
 *
 *  @copyright      Copyright (C) Tetsuo Honda. 2026. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef COM_UTIL_CRT_STRING_H
#define COM_UTIL_CRT_STRING_H

#include <stddef.h>
#include <stdarg.h>
#include <wchar.h>
#include <com_util/base/compiler.h>
#include <com_util_export.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    COM_UTIL_EXPORT int COM_UTIL_API com_util_strcpy(char *dest,
                                                      size_t dest_size,
                                                      const char *src);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_strncpy(char *dest,
                                                       size_t dest_size,
                                                       const char *src,
                                                       size_t count);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_strcat(char *dest,
                                                      size_t dest_size,
                                                      const char *src);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_wcscpy(wchar_t *dest,
                                                      size_t   dest_size,
                                                      const wchar_t *src);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_sscanf(const char *buffer,
                                                      const char *format,
                                                      ...)
#if defined(COMPILER_GCC)
        __attribute__((format(scanf, 2, 3)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vsscanf(const char *buffer,
                                                       const char *format,
                                                       va_list args)
#if defined(COMPILER_GCC)
        __attribute__((format(scanf, 2, 0)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_scan_tokens3(const char *text,
                                                            char *token1,
                                                            size_t token1_size,
                                                            char *token2,
                                                            size_t token2_size,
                                                            char *token3,
                                                            size_t token3_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COM_UTIL_CRT_STRING_H */
