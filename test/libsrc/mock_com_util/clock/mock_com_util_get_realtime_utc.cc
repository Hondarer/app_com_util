#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void com_util_get_realtime_utc(struct tm *utc_tm, int32_t *tv_nsec)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->com_util_get_realtime_utc(utc_tm, tv_nsec);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s\n", __func__);
    }
}
