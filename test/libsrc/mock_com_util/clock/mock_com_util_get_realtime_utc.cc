#include <testfw.h>
#include <mock_com_util.h>
#include <com_util/clock/clock.h>
#include <com_util/clock/mock_clock.h>

void delegate_real_com_util_get_realtime_utc(struct tm *utc_tm, int32_t *tv_nsec)
{
    com_util_get_realtime_utc(utc_tm, tv_nsec);
}

void mock_com_util_get_realtime_utc(struct tm *utc_tm, int32_t *tv_nsec)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->com_util_get_realtime_utc(utc_tm, tv_nsec);
    }
    else
    {
        delegate_real_com_util_get_realtime_utc(utc_tm, tv_nsec);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, 0x%p", __func__, (void *)utc_tm, (void *)tv_nsec);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            if (utc_tm != nullptr)
            {
                printf(" -> %04d-%02d-%02d %02d:%02d:%02d",
                       utc_tm->tm_year + 1900, utc_tm->tm_mon + 1, utc_tm->tm_mday,
                       utc_tm->tm_hour, utc_tm->tm_min, utc_tm->tm_sec);
            }
            if (tv_nsec != nullptr)
            {
                printf(", %ld[ns]", (long)*tv_nsec);
            }
            printf("\n");
        }
        else
        {
            printf("\n");
        }
    }
}
