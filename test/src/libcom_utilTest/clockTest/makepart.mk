# テスト対象のソースファイル
TEST_SRCS := \
    $(MYAPP_DIR)/prod/libsrc/com_util/clock/clock.c

# clock の override を無効化し、本物の実装を直接検証する
DEFINES += \
    CLOCK_GET_MONOTONIC_MS_NO_OVERRIDE \
    CLOCK_GET_REALTIME_UTC_NO_OVERRIDE \
    CLOCK_GET_REALTIME_DEADLINE_MS_NO_OVERRIDE

# ライブラリの指定
LIBS += mock_libc
