#include <com_util/crt/string.h>

#include <errno.h>
#include <string.h>

COM_UTIL_EXPORT int COM_UTIL_API com_util_strcpy(char *dest,
                                                  size_t dest_size,
                                                  const char *src)
{
    size_t len;

    if (dest == NULL || dest_size == 0 || src == NULL)
    {
        return EINVAL;
    }

    len = strlen(src);
    if (len + 1 > dest_size)
    {
        dest[0] = '\0';
        return ERANGE;
    }

    memcpy(dest, src, len + 1);
    return 0;
}

COM_UTIL_EXPORT int COM_UTIL_API com_util_strncpy(char *dest,
                                                   size_t dest_size,
                                                   const char *src,
                                                   size_t count)
{
    size_t len;

    if (dest == NULL || dest_size == 0 || src == NULL)
    {
        return EINVAL;
    }

    len = strlen(src);
    if (len > count)
    {
        len = count;
    }
    if (len >= dest_size)
    {
        len = dest_size - 1;
    }

    memcpy(dest, src, len);
    dest[len] = '\0';
    return 0;
}

COM_UTIL_EXPORT int COM_UTIL_API com_util_strcat(char *dest,
                                                  size_t dest_size,
                                                  const char *src)
{
    size_t dest_len;
    size_t src_len;

    if (dest == NULL || dest_size == 0 || src == NULL)
    {
        return EINVAL;
    }

    dest_len = 0;
    while (dest_len < dest_size && dest[dest_len] != '\0')
    {
        dest_len++;
    }
    if (dest_len >= dest_size)
    {
        dest[0] = '\0';
        return ERANGE;
    }

    src_len = strlen(src);
    if (dest_len + src_len + 1 > dest_size)
    {
        return ERANGE;
    }

    memcpy(dest + dest_len, src, src_len + 1);
    return 0;
}

COM_UTIL_EXPORT int COM_UTIL_API com_util_wcscpy(wchar_t *dest,
                                                  size_t   dest_size,
                                                  const wchar_t *src)
{
    size_t len;

    if (dest == NULL || dest_size == 0 || src == NULL)
    {
        return EINVAL;
    }

    len = wcslen(src);
    if (len + 1 > dest_size)
    {
        dest[0] = L'\0';
        return ERANGE;
    }

    wmemcpy(dest, src, len + 1);
    return 0;
}

static const char *skip_space(const char *p)
{
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n' ||
           *p == '\v' || *p == '\f')
    {
        p++;
    }
    return p;
}

static int copy_token(const char **cursor, char *dest, size_t dest_size)
{
    const char *start;
    size_t len;

    if (dest == NULL || dest_size == 0)
    {
        return -1;
    }

    start = skip_space(*cursor);
    len = 0;
    while (start[len] != '\0' &&
           start[len] != ' ' && start[len] != '\t' &&
           start[len] != '\r' && start[len] != '\n' &&
           start[len] != '\v' && start[len] != '\f')
    {
        len++;
    }

    if (len == 0 || len >= dest_size)
    {
        dest[0] = '\0';
        return -1;
    }

    memcpy(dest, start, len);
    dest[len] = '\0';
    *cursor = start + len;
    return 0;
}

COM_UTIL_EXPORT int COM_UTIL_API com_util_scan_tokens3(const char *text,
                                                        char *token1,
                                                        size_t token1_size,
                                                        char *token2,
                                                        size_t token2_size,
                                                        char *token3,
                                                        size_t token3_size)
{
    const char *cursor;
    int count = 0;

    if (text == NULL)
    {
        return 0;
    }

    cursor = text;
    if (copy_token(&cursor, token1, token1_size) != 0)
    {
        return count;
    }
    count++;

    if (copy_token(&cursor, token2, token2_size) != 0)
    {
        return count;
    }
    count++;

    if (copy_token(&cursor, token3, token3_size) != 0)
    {
        return count;
    }
    count++;

    return count;
}
