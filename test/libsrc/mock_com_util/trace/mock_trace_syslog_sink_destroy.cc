#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_LINUX)

WEAK_ATR void trace_syslog_sink_destroy(trace_syslog_sink_t *handle)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->trace_syslog_sink_destroy(handle);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p\n", __func__, (void *)handle);
    }
}

#endif /* PLATFORM_LINUX */
