# テスト対象のソースファイル
TEST_SRCS := \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt/stdio_temp.c

INCDIR += \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt

# ライブラリの指定
LIBS += mock_libc com_util
