#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_LINUX)

WEAK_ATR int com_util_syslog_sink_rename(com_util_syslog_sink_t *handle, const char *new_ident)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_syslog_sink_rename(handle, new_ident);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s \"%s\"", __func__, new_ident != nullptr ? new_ident : "(null)");
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

#endif /* PLATFORM_LINUX */
