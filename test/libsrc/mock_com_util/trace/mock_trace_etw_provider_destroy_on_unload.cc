#include <testfw.h>
#include <com_util/base/platform.h>

#if defined(PLATFORM_WINDOWS)

#include <com_util/trace/trace_etw.h>

extern "C" {

void trace_etw_provider_destroy_on_unload(trace_etw_provider_t *handle, int process_terminating)
{
    (void)handle;
    (void)process_terminating;
}

}

#endif /* PLATFORM_WINDOWS */
