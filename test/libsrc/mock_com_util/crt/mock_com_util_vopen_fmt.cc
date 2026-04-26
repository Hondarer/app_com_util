#include <stdarg.h>
#include <stdio.h>
#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_vopen_fmt(int flags, int mode, const char *format, va_list args)
{
    int rtc = -1;

    char buf[4096];
    vsnprintf(buf, sizeof(buf), format, args);

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_vopen_fmt(flags, mode, buf);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s %d, %d, %s", __func__, flags, mode, buf);
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
