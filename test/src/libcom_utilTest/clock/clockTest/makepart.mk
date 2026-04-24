# テスト対象のソースファイル
TEST_SRCS := \
    $(MYAPP_DIR)/prod/libsrc/com_util/clock/clock.c \
    $(MYAPP_DIR)/prod/libsrc/com_util/crt/time.c

# ライブラリの指定
LIBS += mock_libc
