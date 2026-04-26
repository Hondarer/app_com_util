#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_WINDOWS)

WEAK_ATR void trace_etw_session_stop(trace_etw_session_t *session)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->trace_etw_session_stop(session);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p\n", __func__, (void *)session);
    }
}

#endif /* PLATFORM_WINDOWS */
