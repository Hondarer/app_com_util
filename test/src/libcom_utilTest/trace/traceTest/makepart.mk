# テスト対象のソースファイル
TEST_SRCS := \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/trace.c

# TEST_SRCS の相対インクルード解決
INCDIR += \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/file

ifdef PLATFORM_LINUX
INCDIR += $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/syslog
endif

ifdef PLATFORM_WINDOWS
INCDIR += $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/etw
endif

# ライブラリ検索パス
LIBSDIR += $(MYAPP_DIR)/test/lib

# ライブラリの指定
LIBS += mock_libc mock_com_util
