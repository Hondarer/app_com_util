#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR com_util_log_level_t com_util_logger_get_os_level(com_util_logger_t *handle)
{
    com_util_log_level_t rtc = COM_UTIL_LOG_LEVEL_NONE;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_logger_get_os_level(handle);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p", __func__, (void *)handle);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> %d\n", (int)rtc);
        }
        else
        {
            printf("\n");
        }
    }

    return rtc;
}
