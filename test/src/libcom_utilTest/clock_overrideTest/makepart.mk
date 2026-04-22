# ライブラリ検索パス
LIBSDIR += \
    $(MYAPP_DIR)/prod/lib \
    $(MYAPP_DIR)/test/lib

# clock の override を無効化し、wrapper を明示的に呼び出して検証する
DEFINES += \
    COM_UTIL_GET_MONOTONIC_MS_NO_OVERRIDE \
    COM_UTIL_GET_REALTIME_UTC_NO_OVERRIDE \
    COM_UTIL_GET_REALTIME_DEADLINE_MS_NO_OVERRIDE

# ライブラリの指定
LIBS += mock_libc mock_com_util com_util
