#include <testfw.h>
#include <mock_com_util.h>
#include <com_util/clock/clock.h>
#include <com_util/clock/mock_clock.h>

uint64_t delegate_real_com_util_get_monotonic_ms(void)
{
    return com_util_get_monotonic_ms();
}

uint64_t mock_com_util_get_monotonic_ms(void)
{
    uint64_t rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_get_monotonic_ms();
    }
    else
    {
        rtc = delegate_real_com_util_get_monotonic_ms();
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
