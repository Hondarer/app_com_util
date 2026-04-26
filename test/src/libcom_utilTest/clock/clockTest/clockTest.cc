#include <testfw.h>
#include <com_util/clock/clock.h>
#include <mock_com_util.h>
#include <mock_time.h>
#ifdef _WIN32
    #include <mock_windows.h>
#endif
#include <stdint.h>

class clockTest : public Test
{
};

static void expect_tm_equal(const struct tm *actual, const struct tm *expected)
{
    EXPECT_EQ(expected->tm_year, actual->tm_year);
    EXPECT_EQ(expected->tm_mon, actual->tm_mon);
    EXPECT_EQ(expected->tm_mday, actual->tm_mday);
    EXPECT_EQ(expected->tm_hour, actual->tm_hour);
    EXPECT_EQ(expected->tm_min, actual->tm_min);
    EXPECT_EQ(expected->tm_sec, actual->tm_sec);
}

#ifdef _WIN32
static FILETIME to_filetime(int64_t tv_sec, int32_t tv_nsec)
{
    const uint64_t filetime_units_per_sec = 10000000ULL;
    const int64_t filetime_epoch_offset_sec = 11644473600LL;
    ULARGE_INTEGER uli;
    FILETIME file_time;

    uli.QuadPart = (uint64_t)(tv_sec + filetime_epoch_offset_sec) * filetime_units_per_sec + (uint64_t)(tv_nsec / 100);
    file_time.dwLowDateTime = uli.LowPart;
    file_time.dwHighDateTime = uli.HighPart;

    return file_time;
}
#endif

TEST_F(clockTest, monotonic_ms_converts_platform_value)
{
#ifndef _WIN32
    Mock_time mock_time;

    EXPECT_CALL(mock_time, clock_gettime(_, _, _, _, _))
        .WillOnce(
            [](const char *, const int, const char *, clockid_t clk_id, struct timespec *ts)
            {
                EXPECT_EQ(CLOCK_MONOTONIC, clk_id);
                ts->tv_sec = 12;
                ts->tv_nsec = 345678901L;
                return 0;
            });
#else
    Mock_windows mock_windows;

    EXPECT_CALL(mock_windows, GetTickCount64(_, _, _)).WillOnce(Return(12345ULL));
#endif

    EXPECT_EQ(12345U, com_util_get_monotonic_ms());
}

TEST_F(clockTest, monotonic_returns_split_platform_value)
{
    int64_t tv_sec = -1;
    int32_t tv_nsec = -1;

#ifndef _WIN32
    Mock_time mock_time;

    EXPECT_CALL(mock_time, clock_gettime(_, _, _, _, _))
        .WillOnce(
            [](const char *, const int, const char *, clockid_t clk_id, struct timespec *ts)
            {
                EXPECT_EQ(CLOCK_MONOTONIC, clk_id);
                ts->tv_sec = 12;
                ts->tv_nsec = 345678901L;
                return 0;
            });
#else
    Mock_windows mock_windows;

    EXPECT_CALL(mock_windows, GetTickCount64(_, _, _)).WillOnce(Return(12345ULL));
#endif

    com_util_get_monotonic(&tv_sec, &tv_nsec);

    EXPECT_EQ(12, tv_sec);
#ifndef _WIN32
    EXPECT_EQ(345678901, tv_nsec);
#else
    EXPECT_EQ(345000000, tv_nsec);
#endif
}

TEST_F(clockTest, realtime_returns_split_platform_value)
{
    const int64_t expected_sec = 1712345678LL;
#ifndef _WIN32
    const int32_t expected_nsec = 987654321;
    Mock_time mock_time;

    EXPECT_CALL(mock_time, clock_gettime(_, _, _, _, _))
        .WillOnce(
            [&](const char *, const int, const char *, clockid_t clk_id, struct timespec *ts)
            {
                EXPECT_EQ(CLOCK_REALTIME, clk_id);
                ts->tv_sec = expected_sec;
                ts->tv_nsec = expected_nsec;
                return 0;
            });
#else
    const int32_t expected_nsec = 987654300;
    Mock_windows mock_windows;

    EXPECT_CALL(mock_windows, GetSystemTimeAsFileTime(_, _, _, _))
        .WillOnce([&](const char *, const int, const char *, LPFILETIME file_time)
                  { *file_time = to_filetime(expected_sec, expected_nsec); });
#endif
    int64_t tv_sec = -1;
    int32_t tv_nsec = -1;

    com_util_get_realtime(&tv_sec, &tv_nsec);

    EXPECT_EQ(expected_sec, tv_sec);
    EXPECT_EQ(expected_nsec, tv_nsec);
}

TEST_F(clockTest, realtime_utc_uses_platform_conversion_result)
{
    const int64_t expected_sec = 1712345678LL;
    const int32_t expected_nsec = 246800000;
    struct tm expected_tm = {};
    struct tm actual_tm = {};
    int32_t actual_nsec = -1;
    Mock_com_util mock_com_util;

#ifndef _WIN32
    Mock_time mock_time;

    EXPECT_CALL(mock_time, clock_gettime(_, _, _, _, _))
        .WillOnce(
            [&](const char *, const int, const char *, clockid_t clk_id, struct timespec *ts)
            {
                EXPECT_EQ(CLOCK_REALTIME, clk_id);
                ts->tv_sec = expected_sec;
                ts->tv_nsec = expected_nsec;
                return 0;
            });
#else
    Mock_windows mock_windows;

    EXPECT_CALL(mock_windows, GetSystemTimeAsFileTime(_, _, _, _))
        .WillOnce([&](const char *, const int, const char *, LPFILETIME file_time)
                  { *file_time = to_filetime(expected_sec, expected_nsec); });
#endif

    EXPECT_CALL(mock_com_util, com_util_gmtime(_, _))
        .WillOnce(
            [&](struct tm *utc_tm, const time_t *timep)
            {
                EXPECT_EQ((time_t)expected_sec, *timep);
                expected_tm.tm_year = 124;
                expected_tm.tm_mon = 3;
                expected_tm.tm_mday = 5;
                expected_tm.tm_hour = 6;
                expected_tm.tm_min = 7;
                expected_tm.tm_sec = 8;
                *utc_tm = expected_tm;
                return 0;
            });

    com_util_get_realtime_utc(&actual_tm, &actual_nsec);

    expect_tm_equal(&actual_tm, &expected_tm);
    EXPECT_EQ(expected_nsec, actual_nsec);
}

TEST_F(clockTest, realtime_utc_zeroes_tm_when_com_util_gmtime_fails)
{
    const int64_t expected_sec = 1712345678LL;
    const int32_t expected_nsec = 246800000;
    struct tm actual_tm = {};
    int32_t actual_nsec = -1;
    Mock_com_util mock_com_util;

    actual_tm.tm_year = 1;
    actual_tm.tm_mon = 2;
    actual_tm.tm_mday = 3;
    actual_tm.tm_hour = 4;
    actual_tm.tm_min = 5;
    actual_tm.tm_sec = 6;

#ifndef _WIN32
    Mock_time mock_time;

    EXPECT_CALL(mock_time, clock_gettime(_, _, _, _, _))
        .WillOnce(
            [&](const char *, const int, const char *, clockid_t clk_id, struct timespec *ts)
            {
                EXPECT_EQ(CLOCK_REALTIME, clk_id);
                ts->tv_sec = expected_sec;
                ts->tv_nsec = expected_nsec;
                return 0;
            });
#else
    Mock_windows mock_windows;

    EXPECT_CALL(mock_windows, GetSystemTimeAsFileTime(_, _, _, _))
        .WillOnce([&](const char *, const int, const char *, LPFILETIME file_time)
                  { *file_time = to_filetime(expected_sec, expected_nsec); });
#endif

    EXPECT_CALL(mock_com_util, com_util_gmtime(_, _))
        .WillOnce(
            [&](struct tm *utc_tm, const time_t *timep)
            {
                EXPECT_EQ((time_t)expected_sec, *timep);
                EXPECT_EQ(&actual_tm, utc_tm);
                return -1;
            });

    com_util_get_realtime_utc(&actual_tm, &actual_nsec);

    EXPECT_EQ(0, actual_tm.tm_year);
    EXPECT_EQ(0, actual_tm.tm_mon);
    EXPECT_EQ(0, actual_tm.tm_mday);
    EXPECT_EQ(0, actual_tm.tm_hour);
    EXPECT_EQ(0, actual_tm.tm_min);
    EXPECT_EQ(0, actual_tm.tm_sec);
    EXPECT_EQ(expected_nsec, actual_nsec);
}

TEST_F(clockTest, realtime_deadline_ms_adds_timeout_without_nsec_carry)
{
    const uint64_t timeout_ms = 250;
    struct timespec abs_timeout = {};

#ifndef _WIN32
    Mock_time mock_time;

    EXPECT_CALL(mock_time, clock_gettime(_, _, _, _, _))
        .WillOnce(
            [](const char *, const int, const char *, clockid_t clk_id, struct timespec *ts)
            {
                EXPECT_EQ(CLOCK_REALTIME, clk_id);
                ts->tv_sec = 100;
                ts->tv_nsec = 100000000L;
                return 0;
            });
#else
    Mock_windows mock_windows;

    EXPECT_CALL(mock_windows, GetSystemTimeAsFileTime(_, _, _, _))
        .WillOnce([](const char *, const int, const char *, LPFILETIME file_time)
                  { *file_time = to_filetime(100, 100000000); });
#endif

    com_util_get_realtime_deadline_ms(timeout_ms, &abs_timeout);

    EXPECT_EQ(100, abs_timeout.tv_sec);
    EXPECT_EQ(350000000L, abs_timeout.tv_nsec);
}

TEST_F(clockTest, realtime_deadline_ms_carries_nsec_overflow)
{
    const uint64_t timeout_ms = 250;
    struct timespec abs_timeout = {};

#ifndef _WIN32
    Mock_time mock_time;

    EXPECT_CALL(mock_time, clock_gettime(_, _, _, _, _))
        .WillOnce(
            [](const char *, const int, const char *, clockid_t clk_id, struct timespec *ts)
            {
                EXPECT_EQ(CLOCK_REALTIME, clk_id);
                ts->tv_sec = 100;
                ts->tv_nsec = 800000000L;
                return 0;
            });
#else
    Mock_windows mock_windows;

    EXPECT_CALL(mock_windows, GetSystemTimeAsFileTime(_, _, _, _))
        .WillOnce([](const char *, const int, const char *, LPFILETIME file_time)
                  { *file_time = to_filetime(100, 800000000); });
#endif

    com_util_get_realtime_deadline_ms(timeout_ms, &abs_timeout);

    EXPECT_EQ(101, abs_timeout.tv_sec);
    EXPECT_EQ(50000000L, abs_timeout.tv_nsec);
}
