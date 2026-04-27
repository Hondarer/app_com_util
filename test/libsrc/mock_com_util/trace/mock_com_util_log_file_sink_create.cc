#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR com_util_log_file_sink_t *com_util_log_file_sink_create(const char *path, size_t max_bytes, int generations)
{
    com_util_log_file_sink_t *rtc = nullptr;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_log_file_sink_create(path, max_bytes, generations);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s \"%s\"", __func__, path != nullptr ? path : "(null)");
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
