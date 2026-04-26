#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int symbol_loader_info(symbol_loader_entry_t *const *fobj_array, size_t fobj_length)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->symbol_loader_info(fobj_array, fobj_length);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s", __func__);
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
