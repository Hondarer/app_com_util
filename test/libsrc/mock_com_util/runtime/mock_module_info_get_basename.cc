#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR int module_info_get_basename(char *out_basename, size_t out_basename_sz, const void *func_addr)
{
    int rtc = -1;

    if (_mock_com_util != nullptr)
    {
        rtc = _mock_com_util->module_info_get_basename(out_basename, out_basename_sz, func_addr);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p", __func__, func_addr);
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
