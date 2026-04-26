#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void *symbol_loader_resolve(symbol_loader_entry_t *fobj)
{
    void *rtc = nullptr;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->symbol_loader_resolve(fobj);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p", __func__, (void *)fobj);
        if (getTraceLevel() >= TRACE_DETAIL)
        {
            printf(" -> 0x%p\n", rtc);
        }
        else
        {
            printf("\n");
        }
    }

    return rtc;
}
