#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_strncpy(char *dest, size_t dest_size, const char *src, size_t count)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_strncpy(dest, dest_size, src, count);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %zu, %s, %zu", __func__, (void *)dest, dest_size, src, count);
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
