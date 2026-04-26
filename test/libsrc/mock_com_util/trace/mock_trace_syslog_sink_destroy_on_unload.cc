#include <testfw.h>
#include <com_util/base/platform.h>

#if defined(PLATFORM_LINUX)

#include <com_util/trace/trace_syslog.h>

extern "C" {

void trace_syslog_sink_destroy_on_unload(trace_syslog_sink_t *handle)
{
    (void)handle;
}

}

#endif /* PLATFORM_LINUX */
