#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_file_write(com_util_file_t *file, const void *buf, size_t len)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_file_write(file, buf, len);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, 0x%p, %zu", __func__, (void *)file, buf, len);
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
