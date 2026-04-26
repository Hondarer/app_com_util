#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_WINDOWS)

WEAK_ATR int trace_etw_provider_write(trace_etw_provider_t *handle, int level, const char *service, const char *message)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->trace_etw_provider_write(handle, level, service, message);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s %d \"%s\"", __func__, level, message != nullptr ? message : "(null)");
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

#endif /* PLATFORM_WINDOWS */
