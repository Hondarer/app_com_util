#include <stdarg.h>
#include <stdio.h>
#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_vstat_fmt(com_util_file_stat_t *buf, const char *format, va_list args)
{
    int rtc = -1;

    char path[4096];
    vsnprintf(path, sizeof(path), format, args);

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_vstat_fmt(buf, path);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %s", __func__, (void *)buf, path);
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
