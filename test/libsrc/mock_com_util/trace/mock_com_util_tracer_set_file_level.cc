#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_tracer_set_file_level(com_util_tracer_t *handle, const char *path,
                                  com_util_trace_level_t level, size_t max_bytes,
                                  int generations)
{
    int rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_tracer_set_file_level(handle, path, level, max_bytes,
                                                     generations);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %s, %d, %zu, %d", __func__,
               (void *)handle, path, (int)level, max_bytes, generations);
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
