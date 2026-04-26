#include <testfw.h>
#include <com_util/trace/trace_file.h>

extern "C" {

void trace_file_sink_destroy_on_unload(trace_file_sink_t *handle)
{
    (void)handle;
}

}
