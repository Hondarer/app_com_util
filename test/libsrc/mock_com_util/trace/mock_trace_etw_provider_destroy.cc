#include <testfw.h>
#include <mock_com_util.h>

#if defined(PLATFORM_WINDOWS)

WEAK_ATR void trace_etw_provider_destroy(trace_etw_provider_t *handle)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->trace_etw_provider_destroy(handle);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p\n", __func__, (void *)handle);
    }
}

#endif /* PLATFORM_WINDOWS */
