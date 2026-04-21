#ifndef MOCK_CLOCK_H
#define MOCK_CLOCK_H

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif

    extern uint64_t mock_clock_get_monotonic_ms(void);
    extern void mock_clock_get_realtime_utc(struct tm *utc_tm, int32_t *tv_nsec);
    extern void mock_clock_get_realtime_deadline_ms(uint64_t timeout_ms, struct timespec *abs_timeout);

#ifdef __cplusplus
}
#endif

#ifdef _IN_OVERRIDE_HEADER_COM_UTIL_CLOCK_H

#ifndef CLOCK_GET_MONOTONIC_MS_NO_OVERRIDE
#define clock_get_monotonic_ms() mock_clock_get_monotonic_ms()
#endif /* !CLOCK_GET_MONOTONIC_MS_NO_OVERRIDE */

#ifndef CLOCK_GET_REALTIME_UTC_NO_OVERRIDE
#define clock_get_realtime_utc(utc_tm, tv_nsec) mock_clock_get_realtime_utc(utc_tm, tv_nsec)
#endif /* !CLOCK_GET_REALTIME_UTC_NO_OVERRIDE */

#ifndef CLOCK_GET_REALTIME_DEADLINE_MS_NO_OVERRIDE
#define clock_get_realtime_deadline_ms(timeout_ms, abs_timeout) \
    mock_clock_get_realtime_deadline_ms(timeout_ms, abs_timeout)
#endif /* !CLOCK_GET_REALTIME_DEADLINE_MS_NO_OVERRIDE */

#else /* _IN_OVERRIDE_HEADER_COM_UTIL_CLOCK_H */

#ifdef __cplusplus
extern "C"
{
#endif

    extern uint64_t delegate_real_clock_get_monotonic_ms(void);
    extern void delegate_real_clock_get_realtime_utc(struct tm *utc_tm, int32_t *tv_nsec);
    extern void delegate_real_clock_get_realtime_deadline_ms(uint64_t timeout_ms,
                                                             struct timespec *abs_timeout);

#ifdef __cplusplus
}
#endif

#endif /* _IN_OVERRIDE_HEADER_COM_UTIL_CLOCK_H */

#endif /* MOCK_CLOCK_H */
