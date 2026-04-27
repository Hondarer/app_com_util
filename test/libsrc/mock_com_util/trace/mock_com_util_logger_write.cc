#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_logger_write(com_util_logger_t *handle, com_util_log_level_t level,
                         const char *message)
{
    int rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_logger_write(handle, level, message);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %d, %s", __func__, (void *)handle, (int)level, message);
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
