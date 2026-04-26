#include <wchar.h>
#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_wcscpy(wchar_t *dest, size_t dest_size, const wchar_t *src)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_wcscpy(dest, dest_size, src);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p, %zu, 0x%p", __func__, (void *)dest, dest_size, (const void *)src);
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
