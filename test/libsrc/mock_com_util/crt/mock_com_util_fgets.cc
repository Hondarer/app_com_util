#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR char *com_util_fgets(char *buf, int size, FILE *stream)
{
    char *rtc = nullptr;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_fgets(buf, size, stream);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %d, 0x%p", __func__, (void *)buf, size, (void *)stream);
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
