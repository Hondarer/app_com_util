#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int com_util_sym_loader_is_default(com_util_sym_loader_entry_t *fobj)
{
    int rtc = 0;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->com_util_sym_loader_is_default(fobj);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p", __func__, (void *)fobj);
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
