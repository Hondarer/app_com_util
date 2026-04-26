# テスト対象のソースファイル
TEST_SRCS := \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/etw/trace_etw.c \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/etw/trace_etw_session.c \
    $(MYAPP_DIR)/prod/libsrc/com_util/crt/string.c

# TEST_SRCS の相対インクルード解決
INCDIR += \
    $(MYAPP_DIR)/prod/libsrc/com_util/crt \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/etw
