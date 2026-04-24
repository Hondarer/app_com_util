# テスト対象のソースファイル
TEST_SRCS := \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt/file.c

INCDIR += \
	$(MYAPP_DIR)/prod/libsrc/com_util/crt

# ライブラリの指定
LIBS += com_util
