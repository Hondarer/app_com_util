#include <stdint.h>
#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_fseek(FILE *stream, int64_t offset, int whence)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_fseek(stream, offset, whence);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %" PRId64 ", %d", __func__, (void *)stream, offset, whence);
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
