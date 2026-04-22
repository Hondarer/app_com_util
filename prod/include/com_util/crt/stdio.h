/**
 *******************************************************************************
 *  @file           stdio.h
 *  @brief          stdio 系 CRT 抽象 API。
 *  @author         Tetsuo Honda
 *  @date           2026/04/22
 *
 *  @details
 *  C 標準ファイル I/O 関数をプラットフォーム差異なしで使用できるラッパーを提供します。\n
 *  ファイルパスを受け取る関数は UTF-8 文字列として扱い、Windows では内部で
 *  Unicode (_W 系関数) に変換します。
 *
 *  @copyright      Copyright (C) Tetsuo Honda. 2026. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef COM_UTIL_CRT_STDIO_H
#define COM_UTIL_CRT_STDIO_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <com_util/base/compiler.h>
#include <com_util_export.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_fopen(const char *path,
                                                       const char *modes,
                                                       int        *errno_out);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_remove(const char *path);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_rename(const char *oldpath,
                                                      const char *newpath);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fclose(FILE *stream);

    COM_UTIL_EXPORT size_t COM_UTIL_API com_util_fread(void  *ptr,
                                                        size_t size,
                                                        size_t count,
                                                        FILE  *stream);

    COM_UTIL_EXPORT size_t COM_UTIL_API com_util_fwrite(const void *ptr,
                                                         size_t      size,
                                                         size_t      count,
                                                         FILE       *stream);

    COM_UTIL_EXPORT char *COM_UTIL_API com_util_fgets(char *buf,
                                                       int   size,
                                                       FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fputs(const char *str,
                                                     FILE       *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fprintf(FILE       *stream,
                                                       const char *format,
                                                       ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 3)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vfprintf(FILE       *stream,
                                                        const char *format,
                                                        va_list     args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 0)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fflush(FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_feof(FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_ferror(FILE *stream);

    COM_UTIL_EXPORT void COM_UTIL_API com_util_clearerr(FILE *stream);

    COM_UTIL_EXPORT void COM_UTIL_API com_util_rewind(FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fseek(FILE   *stream,
                                                     int64_t offset,
                                                     int     whence);

    COM_UTIL_EXPORT int64_t COM_UTIL_API com_util_ftell(FILE *stream);

    COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_fopen_fmt(const char *modes,
                                                           int        *errno_out,
                                                           const char *format,
                                                           ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 3, 4)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_vfopen_fmt(const char *modes,
                                                            int        *errno_out,
                                                            const char *format,
                                                            va_list     args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 3, 0)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_remove_fmt(const char *format, ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 1, 2)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vremove_fmt(const char *format,
                                                           va_list     args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 1, 0)))
#endif /* COMPILER_GCC */
        ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COM_UTIL_CRT_STDIO_H */
