#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_gmtime(struct tm *utc_tm, const time_t *timep)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_gmtime(utc_tm, timep);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, 0x%p", __func__, (void *)utc_tm, (const void *)timep);
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
