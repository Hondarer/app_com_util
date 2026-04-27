#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void com_util_log_file_sink_destroy(com_util_log_file_sink_t *handle)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->com_util_log_file_sink_destroy(handle);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p\n", __func__, (void *)handle);
    }
}
