#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_logger_set_stderr_level(com_util_logger_t *handle, com_util_log_level_t level)
{
    int rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_logger_set_stderr_level(handle, level);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %d", __func__, (void *)handle, (int)level);
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
