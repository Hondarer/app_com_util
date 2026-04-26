#include <com_util/crt/stdio.h>
#include <com_util/crt/path.h>

#include "crt_internal.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#if defined(PLATFORM_LINUX)
    #include <stdlib.h>
    #include <unistd.h>
#elif defined(PLATFORM_WINDOWS)
    #include <stdlib.h>
    #include <wchar.h>
#endif /* PLATFORM_ */

#if defined(PLATFORM_WINDOWS)
    /* Windows GetTempFileNameW の prefix は最大 3 文字 */
    #define COM_UTIL_TEMP_PREFIX_MAX 3u
#endif /* PLATFORM_WINDOWS */

COM_UTIL_EXPORT FILE *COM_UTIL_API com_util_fopen_temp(const char *prefix,
                                                        char       *path_out,
                                                        size_t      path_size,
                                                        int        *errno_out)
{
    if (path_out == NULL || path_size == 0u)
    {
        if (errno_out != NULL)
        {
            *errno_out = EINVAL;
        }
        return NULL;
    }

#if defined(PLATFORM_LINUX)
    {
        const char *tmpdir = getenv("TMPDIR");
        const char *pfx    = (prefix != NULL) ? prefix : "com_util_";
        int         fd;
        FILE       *fp;
        int         n;

        if (tmpdir == NULL || tmpdir[0] == '\0')
        {
            tmpdir = "/tmp";
        }

        n = snprintf(path_out, path_size, "%s/%sXXXXXX", tmpdir, pfx);
        if (n < 0 || (size_t)n >= path_size)
        {
            if (errno_out != NULL)
            {
                *errno_out = ENAMETOOLONG;
            }
            return NULL;
        }

        errno = 0;
        fd    = mkstemp(path_out);
        if (fd == -1)
        {
            if (errno_out != NULL)
            {
                *errno_out = errno;
            }
            return NULL;
        }

        fp = fdopen(fd, "wb");
        if (fp == NULL)
        {
            int saved = errno;
            close(fd);
            unlink(path_out);
            if (errno_out != NULL)
            {
                *errno_out = saved;
            }
            return NULL;
        }
        return fp;
    }
#elif defined(PLATFORM_WINDOWS)
    {
        wchar_t wdir[MAX_PATH];
        wchar_t wfile[MAX_PATH];
        wchar_t wprefix[COM_UTIL_TEMP_PREFIX_MAX + 1u];
        FILE   *fp = NULL;
        errno_t err;
        size_t  converted;
        DWORD   dwret;
        UINT    uret;

        if (prefix != NULL && strlen(prefix) > COM_UTIL_TEMP_PREFIX_MAX)
        {
            if (errno_out != NULL)
            {
                *errno_out = EINVAL;
            }
            return NULL;
        }

        dwret = GetTempPathW((DWORD)(sizeof(wdir) / sizeof(wdir[0])), wdir);
        if (dwret == 0u || dwret > (DWORD)(sizeof(wdir) / sizeof(wdir[0])))
        {
            if (errno_out != NULL)
            {
                *errno_out = (int)GetLastError();
            }
            return NULL;
        }

        {
            const char *pfx = (prefix != NULL && prefix[0] != '\0') ? prefix : "cu_";
            err = mbstowcs_s(&converted, wprefix, sizeof(wprefix) / sizeof(wprefix[0]), pfx, _TRUNCATE);
            if (err != 0)
            {
                if (errno_out != NULL)
                {
                    *errno_out = EINVAL;
                }
                return NULL;
            }
        }

        uret = GetTempFileNameW(wdir, wprefix, 0u, wfile);
        if (uret == 0u)
        {
            if (errno_out != NULL)
            {
                *errno_out = (int)GetLastError();
            }
            return NULL;
        }

        if (com_util_wpath_to_utf8(path_out, path_size, wfile) < 0)
        {
            DeleteFileW(wfile);
            if (errno_out != NULL)
            {
                *errno_out = ENAMETOOLONG;
            }
            return NULL;
        }

        err = _wfopen_s(&fp, wfile, L"wb");
        if (err != 0)
        {
            DeleteFileW(wfile);
            if (errno_out != NULL)
            {
                *errno_out = (int)err;
            }
            return NULL;
        }
        return fp;
    }
#endif /* PLATFORM_ */
}
