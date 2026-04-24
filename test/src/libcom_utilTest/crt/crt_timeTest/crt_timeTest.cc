#include <testfw.h>
#include <com_util/crt/time.h>
#include <string.h>

class crt_timeTest : public Test
{
};

TEST_F(crt_timeTest, gmtime_success_epoch)
{
    struct tm utc_tm;
    time_t epoch = 0;

    memset(&utc_tm, 0xff, sizeof(utc_tm));

    int ret = com_util_gmtime(&utc_tm, &epoch);

    EXPECT_EQ(0, ret);
    EXPECT_EQ(70, utc_tm.tm_year);
    EXPECT_EQ(0, utc_tm.tm_mon);
    EXPECT_EQ(1, utc_tm.tm_mday);
    EXPECT_EQ(0, utc_tm.tm_hour);
    EXPECT_EQ(0, utc_tm.tm_min);
    EXPECT_EQ(0, utc_tm.tm_sec);
}

TEST_F(crt_timeTest, gmtime_null_tm)
{
    time_t epoch = 0;

    int ret = com_util_gmtime(NULL, &epoch);

    EXPECT_EQ(-1, ret);
}

TEST_F(crt_timeTest, gmtime_null_time)
{
    struct tm utc_tm;

    int ret = com_util_gmtime(&utc_tm, NULL);

    EXPECT_EQ(-1, ret);
}
