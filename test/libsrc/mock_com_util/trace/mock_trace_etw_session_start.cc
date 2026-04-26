#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_WINDOWS)

WEAK_ATR trace_etw_session_t *trace_etw_session_start(
    const char *session_name,
    const char *provider_guid_str,
    trace_etw_event_callback_t callback,
    void *context,
    int *out_status)
{
    trace_etw_session_t *rtc = nullptr;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->trace_etw_session_start(
            session_name, provider_guid_str, callback, context, out_status);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s \"%s\"", __func__, session_name != nullptr ? session_name : "(null)");
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> 0x%p\n", (void *)rtc);
        }
        else
        {
            printf("\n");
        }
    }

    return rtc;
}

#endif /* PLATFORM_WINDOWS */
