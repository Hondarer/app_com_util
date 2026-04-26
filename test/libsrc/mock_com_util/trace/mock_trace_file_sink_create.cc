#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR trace_file_sink_t *trace_file_sink_create(const char *path, size_t max_bytes, int generations)
{
    trace_file_sink_t *rtc = nullptr;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->trace_file_sink_create(path, max_bytes, generations);
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
