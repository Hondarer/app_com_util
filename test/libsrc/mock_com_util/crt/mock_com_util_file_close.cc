#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void com_util_file_close(com_util_file_t *file)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->com_util_file_close(file);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s 0x%p\n", __func__, (void *)file);
    }
}
