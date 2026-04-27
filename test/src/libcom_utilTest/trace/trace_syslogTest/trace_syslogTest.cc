#include <com_util/base/platform.h>

#if defined(PLATFORM_LINUX)

#include <syslog.h>
#include <testfw.h>
#include <com_util/trace/syslog.h>

class trace_syslogTest : public Test
{
};

// プロバイダを初期化し、有効なハンドルが返されることの確認
TEST_F(trace_syslogTest, test_init_and_dispose)
{
    com_util_syslog_sink_t *handle = com_util_syslog_sink_create("syslog_test", LOG_USER); // [手順] - syslog sink を初期化する。
    EXPECT_NE((com_util_syslog_sink_t *)NULL, handle); // [確認_正常系] - ハンドルが NULL でないこと。
    com_util_syslog_sink_destroy(handle);
}

// INFO レベルでメッセージを書き込み、戻り値が 0 であることの確認
TEST_F(trace_syslogTest, test_write_returns_zero)
{
    com_util_syslog_sink_t *handle = com_util_syslog_sink_create("syslog_test", LOG_USER);
    ASSERT_NE((com_util_syslog_sink_t *)NULL, handle);

    int result = com_util_syslog_sink_write(handle, LOG_INFO, "test message"); // [手順] - INFO レベルで書き込む。

    EXPECT_EQ(0, result); // [確認_正常系] - 戻り値が 0 であること。
    com_util_syslog_sink_destroy(handle);
}

// 全レベルで書き込みが成功することの確認
TEST_F(trace_syslogTest, test_write_all_levels)
{
    com_util_syslog_sink_t *handle = com_util_syslog_sink_create("syslog_test", LOG_USER);
    ASSERT_NE((com_util_syslog_sink_t *)NULL, handle);

    EXPECT_EQ(0, com_util_syslog_sink_write(handle, LOG_CRIT, "critical"));   // [確認_正常系] - CRIT レベルで書き込めること。
    EXPECT_EQ(0, com_util_syslog_sink_write(handle, LOG_ERR, "error"));       // [確認_正常系] - ERR レベルで書き込めること。
    EXPECT_EQ(0, com_util_syslog_sink_write(handle, LOG_WARNING, "warning")); // [確認_正常系] - WARNING レベルで書き込めること。
    EXPECT_EQ(0, com_util_syslog_sink_write(handle, LOG_INFO, "info"));       // [確認_正常系] - INFO レベルで書き込めること。
    EXPECT_EQ(0, com_util_syslog_sink_write(handle, LOG_DEBUG, "debug"));     // [確認_正常系] - DEBUG レベルで書き込めること。

    com_util_syslog_sink_destroy(handle);
}

// NULL 引数が安全に無視されることの確認
TEST_F(trace_syslogTest, test_null_arguments_are_safe)
{
    com_util_syslog_sink_t *handle = com_util_syslog_sink_create("syslog_test", LOG_USER);

    EXPECT_EQ((com_util_syslog_sink_t *)NULL, com_util_syslog_sink_create(NULL, LOG_USER)); // [確認_異常系] - NULL ident で create が失敗すること。
    EXPECT_EQ(0, com_util_syslog_sink_write(NULL, LOG_INFO, "test message"));            // [確認_異常系] - NULL ハンドルが安全であること。
    EXPECT_EQ(0, com_util_syslog_sink_write(handle, LOG_INFO, NULL));                    // [確認_異常系] - NULL message が安全であること。

    com_util_syslog_sink_destroy(handle);
    com_util_syslog_sink_destroy(NULL); // [手順] - NULL ハンドルで destroy を呼ぶ。
}

#elif defined(PLATFORM_WINDOWS)

#include <testfw.h>

TEST(trace_syslogTest, not_supported)
{
    GTEST_SKIP() << "syslog is not supported on this platform";
}

#endif /* PLATFORM_ */
