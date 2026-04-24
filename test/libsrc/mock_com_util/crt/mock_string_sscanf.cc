#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_sscanf(const char *buffer, const char *format, ...)
{
    int rtc = 0;
    va_list args;

    va_start(args, format);

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_sscanf(buffer, format, args);
    }

    va_end(args);

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s \"%s\", \"%s\"", __func__, buffer, format);
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
