#include <stdarg.h>
#include <stdio.h>
#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR FILE *com_util_vfopen_fmt(const char *modes, int *errno_out, const char *format, va_list args)
{
    FILE *rtc = nullptr;

    char buf[4096];
    vsnprintf(buf, sizeof(buf), format, args);

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_vfopen_fmt(modes, errno_out, buf);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s %s, 0x%p, %s", __func__, modes, (void *)errno_out, buf);
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
