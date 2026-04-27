#include <com_util/crt/path.h>
#include "crt_internal.h"
#include <errno.h>
#if defined(PLATFORM_LINUX)
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
#endif

COM_UTIL_EXPORT char *COM_UTIL_API com_util_normalize_path_sep(char *path)
{
    char *p;
    for (p = path; *p != '\0'; ++p)
    {
        if (*p == '\\')
        {
            *p = PLATFORM_PATH_SEP_CHR;
        }
    }
    return path;
}

COM_UTIL_EXPORT int COM_UTIL_API com_util_get_temp_dir(char   *path_out,
                                                        size_t  path_size,
                                                        int    *errno_out)
{
    if (path_out == NULL || path_size == 0u)
    {
        if (errno_out != NULL) { *errno_out = EINVAL; }
        return -1;
    }

#if defined(PLATFORM_LINUX)
    {
        const char *tmpdir = getenv("TMPDIR");
        size_t      len;
        int         n;

        if (tmpdir == NULL || tmpdir[0] == '\0')
        {
            tmpdir = "/tmp";
        }

        len = strlen(tmpdir);
        while (len > 1u && tmpdir[len - 1u] == PLATFORM_PATH_SEP_CHR) { --len; }

        n = snprintf(path_out, path_size, "%.*s", (int)len, tmpdir);
        if (n < 0 || (size_t)n >= path_size)
        {
            if (errno_out != NULL) { *errno_out = ENAMETOOLONG; }
            return -1;
        }
        return 0;
    }
#elif defined(PLATFORM_WINDOWS)
    {
        wchar_t wdir[PLATFORM_PATH_MAX];
        DWORD   dwret;
        size_t  len;

        dwret = GetTempPathW((DWORD)(sizeof(wdir) / sizeof(wdir[0])), wdir);
        if (dwret == 0u || dwret >= (DWORD)(sizeof(wdir) / sizeof(wdir[0])))
        {
            if (errno_out != NULL) { *errno_out = (int)GetLastError(); }
            return -1;
        }

        if (com_util_wpath_to_utf8(path_out, path_size, wdir) < 0)
        {
            if (errno_out != NULL) { *errno_out = ENAMETOOLONG; }
            return -1;
        }

        /* GetTempPathW は末尾 '\' を付けて返す。変換後は '/' になるので除去する */
        len = strlen(path_out);
        while (len > 1u && path_out[len - 1u] == PLATFORM_PATH_SEP_CHR)
        {
            path_out[--len] = '\0';
        }
        return 0;
    }
#endif /* PLATFORM_ */
}
