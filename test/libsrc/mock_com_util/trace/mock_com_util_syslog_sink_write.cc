#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_LINUX)

WEAK_ATR int com_util_syslog_sink_write(com_util_syslog_sink_t *handle, int level, const char *message)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_syslog_sink_write(handle, level, message);
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

#endif /* PLATFORM_LINUX */
