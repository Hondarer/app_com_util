#include <testfw.h>
#include <com_util/trace/trace_file.h>

extern "C" {

void com_util_trace_file_sink_destroy_on_unload(com_util_trace_file_sink_t *handle)
{
    (void)handle;
}

}
