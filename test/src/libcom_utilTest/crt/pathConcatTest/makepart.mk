# テスト対象のソースファイル
TEST_SRCS := \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt/path.c

INCDIR += \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt

LIBS += mock_libc
