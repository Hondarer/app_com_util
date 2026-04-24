# テスト対象のソースファイル
TEST_SRCS := \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/etw/trace_etw.c \
    $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/etw/trace_etw_session.c

# TEST_SRCS の相対インクルード解決
INCDIR += $(MYAPP_DIR)/prod/libsrc/com_util/trace/backends/etw

# ライブラリ検索パス
LIBSDIR += \
    $(MYAPP_DIR)/test/lib

# ライブラリの指定
LIBS += mock_com_util com_util
