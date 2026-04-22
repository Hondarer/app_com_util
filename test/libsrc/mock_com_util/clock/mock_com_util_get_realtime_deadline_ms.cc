#include <mock_com_util.h>
#include <com_util/clock/clock.h>
#include <com_util/clock/mock_clock.h>

void delegate_real_com_util_get_realtime_deadline_ms(uint64_t timeout_ms, struct timespec *abs_timeout)
{
    com_util_get_realtime_deadline_ms(timeout_ms, abs_timeout);
}

void mock_com_util_get_realtime_deadline_ms(uint64_t timeout_ms, struct timespec *abs_timeout)
{
    if (_mock_com_util != nullptr)
    {
        _mock_com_util->com_util_get_realtime_deadline_ms(timeout_ms, abs_timeout);
    }
    else
    {
        delegate_real_com_util_get_realtime_deadline_ms(timeout_ms, abs_timeout);
    }
}
