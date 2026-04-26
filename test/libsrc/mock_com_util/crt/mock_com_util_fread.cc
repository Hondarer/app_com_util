#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR size_t com_util_fread(void *ptr, size_t size, size_t count, FILE *stream)
{
    size_t rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_fread(ptr, size, count, stream);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %zu, %zu, 0x%p", __func__, ptr, size, count, (void *)stream);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> %zu\n", rtc);
        }
        else
        {
            printf("\n");
        }
    }

    return rtc;
}
