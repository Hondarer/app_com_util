# テスト対象のソースファイル
TEST_SRCS := \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/file/trace_file.c

# TEST_SRCS の相対インクルード解決
INCDIR += \
    $(MYAPP_DIR)/prod/libsrc/com_util/crt \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/file

# ライブラリ検索パス
LIBSDIR += $(MYAPP_DIR)/test/lib

# ライブラリの指定
LIBS += mock_libc mock_com_util
