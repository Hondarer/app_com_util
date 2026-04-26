# テスト対象のソースファイル
TEST_SRCS := \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt/stdio_temp.c

INCDIR += \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt

# 実 mkstemp/_wfopen_s/getenv を呼ぶため mock_libc は含めない
LIBS += com_util
