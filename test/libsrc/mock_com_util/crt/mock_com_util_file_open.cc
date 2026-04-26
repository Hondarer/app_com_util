#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_file_open(com_util_file_t *file, const char *path, uint32_t flags)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_file_open(file, path, flags);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %s, %u", __func__, (void *)file, path, flags);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> %d\n", rtc);
        }
        else
        {
            printf("\n");
        }
    }

    return rtc;
}
