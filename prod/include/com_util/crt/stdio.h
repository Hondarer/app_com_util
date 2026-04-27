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
 *  Unicode (_W 系関数) に変換します。\n
 *  出力パス (@p path_out 等) はプラットフォームによらず @ref PLATFORM_PATH_SEP (`"/"`) に
 *  統一されます。パスセパレータの詳細な方針は @ref path.h を参照してください。
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

    COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_fopen(const char *path, const char *modes, int *errno_out);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_remove(const char *path);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_rename(const char *oldpath, const char *newpath);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fclose(FILE *stream);

    COM_UTIL_EXPORT size_t COM_UTIL_API com_util_fread(void *ptr, size_t size, size_t count, FILE *stream);

    COM_UTIL_EXPORT size_t COM_UTIL_API com_util_fwrite(const void *ptr, size_t size, size_t count, FILE *stream);

    COM_UTIL_EXPORT char *COM_UTIL_API com_util_fgets(char *buf, int size, FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fputs(const char *str, FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fprintf(FILE *stream, const char *format, ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 3)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vfprintf(FILE *stream, const char *format, va_list args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 2, 0)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fflush(FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_feof(FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_ferror(FILE *stream);

    COM_UTIL_EXPORT void COM_UTIL_API com_util_clearerr(FILE *stream);

    COM_UTIL_EXPORT void COM_UTIL_API com_util_rewind(FILE *stream);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_fseek(FILE *stream, int64_t offset, int whence);

    COM_UTIL_EXPORT int64_t COM_UTIL_API com_util_ftell(FILE *stream);

    COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_fopen_fmt(const char *modes, int *errno_out, const char *format, ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 3, 4)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_vfopen_fmt(const char *modes, int *errno_out, const char *format,
                                                           va_list args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 3, 0)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_remove_fmt(const char *format, ...)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 1, 2)))
#endif /* COMPILER_GCC */
        ;

    COM_UTIL_EXPORT int COM_UTIL_API com_util_vremove_fmt(const char *format, va_list args)
#if defined(COMPILER_GCC)
        __attribute__((format(printf, 1, 0)))
#endif /* COMPILER_GCC */
        ;

    /**
     *  @brief          一意な一時ファイルを atomic に作成し、指定されたモードで開きます。
     *  @param[in]      prefix       ファイル名先頭につける識別子 (UTF-8)。NULL 可。
     *                               4 文字以上を渡した場合は先頭 3 文字を採用します。
     *  @param[in]      modes        fopen 互換のモード文字列 ("wb", "w", "w+b" など)。
     *                               NULL を渡した場合は NULL を返し、@p errno_out に EINVAL を格納します。
     *                               一時ファイルは常に新規作成のため "r"/"rb" は意味を持ちませんが、
     *                               API 層での制限は課しません。
     *  @param[out]     path_out     生成された一時ファイル絶対パス (UTF-8) の格納先。
     *  @param[in]      path_size    @p path_out のサイズ (バイト)。PLATFORM_PATH_MAX 以上を推奨します。
     *  @param[out]     errno_out    エラー詳細の格納先。NULL 可。
     *  @return         成功時はオープンされた FILE*、失敗時は NULL を返します。
     *
     *  @details
     *  Linux 環境では TMPDIR (未設定なら "/tmp") に "<prefix>XXXXXX" のテンプレートで
     *  mkstemp() によりファイルを atomic に作成し、その fd を fdopen(@p modes) で FILE* に
     *  変換します。\n
     *  @p modes に "w"/"w+" を指定しても fdopen() の仕様上ファイルの切り詰めは発生しません。
     *  mkstemp() が新規作成したファイルは常に空のため、実用上の影響はありません。\n
     *  Windows 環境では GetTempPathW + GetTempFileNameW でユニーク名を生成し、
     *  _wfopen_s() で指定モードにて開きます。@p path_out は wchar→UTF-8 変換した結果が
     *  格納されます。\n
     *  呼び出し元は不要になったら com_util_fclose() でクローズし、
     *  必要なら com_util_remove() でファイルを削除する責任があります。
     */
    COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_fopen_temp(const char *prefix, const char *modes, char *path_out,
                                                           size_t path_size, int *errno_out);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COM_UTIL_CRT_STDIO_H */
