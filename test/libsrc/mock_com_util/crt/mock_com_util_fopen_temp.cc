#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR FILE *com_util_fopen_temp(const char *prefix,
                                    char       *path_out,
                                    size_t      path_size,
                                    int        *errno_out)
{
    FILE *fp = nullptr;

    if (_mock_com_util != nullptr)
    {
        fp = _mock_com_util->com_util_fopen_temp(prefix, path_out, path_size, errno_out);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s %s, 0x%p, %zu, 0x%p",
               __func__,
               (prefix != nullptr) ? prefix : "(null)",
               (void *)path_out,
               path_size,
               (void *)errno_out);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> 0x%p\n", (void *)fp);
        }
        else
        {
            printf("\n");
        }
    }

    return fp;
}
