#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR FILE *com_util_fopen(const char *path, const char *modes, int *errno_out)
{
    FILE *fp = nullptr;

    if (_mock_com_util != nullptr)
    {
        fp = _mock_com_util->com_util_fopen(path, modes, errno_out);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s %s, %s", __func__, path, modes);
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
