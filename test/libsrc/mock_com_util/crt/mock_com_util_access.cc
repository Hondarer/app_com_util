#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_access(const char *path, int mode)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_access(path, mode);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s %s, %d", __func__, path, mode);
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
