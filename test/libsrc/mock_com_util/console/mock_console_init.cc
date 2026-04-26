#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void console_init(void)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->console_init();
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s\n", __func__);
    }
}
