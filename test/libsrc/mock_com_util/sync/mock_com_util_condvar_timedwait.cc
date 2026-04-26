#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_condvar_timedwait(com_util_condvar_t *cv, com_util_mutex_t *mtx, uint32_t timeout_ms)
{
    int rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_condvar_timedwait(cv, mtx, timeout_ms);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s %u", __func__, timeout_ms);
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
