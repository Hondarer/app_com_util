#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR uint64_t com_util_get_monotonic_ms(void)
{
    uint64_t rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_get_monotonic_ms();
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s", __func__);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> %llu\n", (unsigned long long)rtc);
        }
        else
        {
            printf("\n");
        }
    }

    return rtc;
}
