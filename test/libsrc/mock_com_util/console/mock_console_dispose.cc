#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void console_dispose(void)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->console_dispose();
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s\n", __func__);
    }
}
