#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR com_util_tracer_state_t com_util_tracer_get_state(com_util_tracer_t *handle)
{
    com_util_tracer_state_t rtc = COM_UTIL_TRACER_STATE_DISPOSED;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_tracer_get_state(handle);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p", __func__, (void *)handle);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> %d\n", (int)rtc);
        }
        else
        {
            printf("\n");
        }
    }

    return rtc;
}
