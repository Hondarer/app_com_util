#include <testfw.h>
#include <mock_com_util.h>

WEAK_ATR void symbol_loader_dispose(symbol_loader_entry_t *const *fobj_array, size_t fobj_length)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->symbol_loader_dispose(fobj_array, fobj_length);
    }

    if (getTraceLevel() > TRACE_NONE)
    {
        printf("  > %s\n", __func__);
    }
}
