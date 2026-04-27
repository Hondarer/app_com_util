#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void com_util_console_init(void)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->com_util_console_init();
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s\n", __func__);
    }
}
