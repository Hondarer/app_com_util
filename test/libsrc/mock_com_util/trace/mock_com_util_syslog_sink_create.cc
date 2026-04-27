#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_LINUX)

WEAK_ATR com_util_syslog_sink_t *com_util_syslog_sink_create(const char *ident, int facility)
{
    com_util_syslog_sink_t *rtc = nullptr;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_syslog_sink_create(ident, facility);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s \"%s\"", __func__, ident != nullptr ? ident : "(null)");
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

#endif /* PLATFORM_LINUX */
