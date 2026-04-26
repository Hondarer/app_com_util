#include <stdarg.h>
#include <stdio.h>
#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_vfprintf(FILE *stream, const char *format, va_list args)
{
    int rtc = -1;

    char buf[1024];
    vsnprintf(buf, sizeof(buf), format, args);

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_vfprintf(stream, buf);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %s", __func__, (void *)stream, buf);
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
