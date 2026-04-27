#include <com_util/crt/path.h>

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
