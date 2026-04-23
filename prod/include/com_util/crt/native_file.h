/**
 *******************************************************************************
 *  @file           native_file.h
 *  @brief          ネイティブ低レベルファイル I/O 抽象 API。
 *  @author         Tetsuo Honda
 *  @date           2026/04/24
 *
 *  @details
 *  Windows の HANDLE ベース I/O と Linux の fd ベース I/O を共通化し、
 *  UTF-8 パスを受け取る低レベル書き込み用 API を提供します。
 *
 *  @copyright      Copyright (C) Tetsuo Honda. 2026. All rights reserved.
 *
 *******************************************************************************
 */

#ifndef COM_UTIL_CRT_NATIVE_FILE_H
#define COM_UTIL_CRT_NATIVE_FILE_H

#include <stddef.h>
#include <stdint.h>
#include <com_util/base/platform.h>
#include <com_util_export.h>

#if defined(PLATFORM_WINDOWS)
    #include <com_util/base/windows_sdk.h>
#endif /* PLATFORM_WINDOWS */

#define COM_UTIL_NATIVE_FILE_OPEN_CREATE            (1u << 0)
#define COM_UTIL_NATIVE_FILE_OPEN_TRUNCATE          (1u << 1)
#define COM_UTIL_NATIVE_FILE_OPEN_APPEND            (1u << 2)
#define COM_UTIL_NATIVE_FILE_OPEN_WRITE_THROUGH     (1u << 3)
#define COM_UTIL_NATIVE_FILE_OPEN_SHARE_READ        (1u << 4)
#define COM_UTIL_NATIVE_FILE_OPEN_SHARE_DELETE      (1u << 5)

typedef struct com_util_native_file
{
#if defined(PLATFORM_LINUX)
    int handle;
#elif defined(PLATFORM_WINDOWS)
    HANDLE handle;
#endif /* PLATFORM_ */
} com_util_native_file_t;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    COM_UTIL_EXPORT void COM_UTIL_API com_util_native_file_init(com_util_native_file_t *file);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_native_file_open(com_util_native_file_t *file,
                                                                const char             *path,
                                                                uint32_t                flags);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_native_file_write(com_util_native_file_t *file,
                                                                 const void             *buf,
                                                                 size_t                  len);

    COM_UTIL_EXPORT int COM_UTIL_API com_util_native_file_get_size(com_util_native_file_t *file,
                                                                    size_t                 *size_out);

    COM_UTIL_EXPORT void COM_UTIL_API com_util_native_file_close(com_util_native_file_t *file);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COM_UTIL_CRT_NATIVE_FILE_H */
