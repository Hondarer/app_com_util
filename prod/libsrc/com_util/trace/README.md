# trace - クロスプラットフォーム トレース基盤

`trace` は、Windows と Linux の両方で同じコードからトレースを出力するためのユーティリティです。  
`com_util/trace/logger.h` を唯一の入口として、OS トレース、ファイル、`stderr` を共通のトレースレベルで扱えます。

## 目的

アプリケーションから見れば、Windows では ETW、Linux では syslog という違いを意識せずにトレースを書けます。  
さらに、OS トレースとは別にファイル出力と `stderr` 出力を併用でき、それぞれに独立したしきい値を設定できます。

- OS ごとのトレース API 差異を吸収する
- OS トレース / ファイル / `stderr` を同じハンドルで管理する
- 出力先ごとに `CRITICAL` から `DEBUG` までのしきい値を分けられる
- 呼び出し側は `trace.h` だけを見ればよい

## 設計の要点

`trace` は、設定フェーズと出力フェーズを分けたライフサイクルを持ちます。  
`com_util_logger_create()` 直後は stopped 状態で、`com_util_logger_set_*()` による設定変更が可能です。  
`com_util_logger_start()` 後は started 状態となり、`com_util_logger_write()` 系で出力できます。

```text
create -> set_name / set_* -> start -> write -> stop -> destroy
```

started 中は設定変更できず、設定を変える場合は一度 `com_util_logger_stop()` で stopped に戻します。  
`com_util_logger_destroy()` は started / stopped のどちらからでも呼べます。

## トレースレベル

共通レベルは `COM_UTIL_LOG_LEVEL_CRITICAL` から `COM_UTIL_LOG_LEVEL_DEBUG` までの 6 段階で、`COM_UTIL_LOG_LEVEL_NONE` はその出力先を無効化します。

- `COM_UTIL_LOG_LEVEL_CRITICAL`: 致命的エラー
- `COM_UTIL_LOG_LEVEL_ERROR`: エラー
- `COM_UTIL_LOG_LEVEL_WARNING`: 警告
- `COM_UTIL_LOG_LEVEL_INFO`: 通常の運用情報
- `COM_UTIL_LOG_LEVEL_VERBOSE`: 詳細な診断情報
- `COM_UTIL_LOG_LEVEL_DEBUG`: 最も詳細な診断情報
- `COM_UTIL_LOG_LEVEL_NONE`: 出力しない

Windows ETW と Linux syslog には `VERBOSE` より細かい標準レベルがないため、`COM_UTIL_LOG_LEVEL_DEBUG` は
OS トレースでは `COM_UTIL_LOG_LEVEL_VERBOSE` と同じ詳細度として扱われます。  
一方でファイルと `stderr` では `DEBUG` を独立したレベル文字で区別します。

各出力先は「設定レベル以上に重大なメッセージだけを出す」動作です。

## デフォルト動作

`com_util_logger_create()` 直後の既定値は次のとおりです。

- OS トレース: `COM_UTIL_LOG_LEVEL_INFO`
- ファイル: `COM_UTIL_LOG_LEVEL_ERROR`
- `stderr`: `COM_UTIL_LOG_LEVEL_NONE`

ただし、ファイル出力はパス未設定のままでは有効になりません。  
ファイルを使う場合は `com_util_logger_set_file_level()` で出力先パスを設定します。

## 出力先

### OS トレース

OS 標準のトレース基盤へ送ります。

- Windows: ETW
- Linux: syslog

通常は `trace.h` 経由で使い、プラットフォームごとの backend を直接触る必要はありません。

### ファイル

ローカルファイルへ 1 行ずつ追記します。  
サイズ上限に達すると `path`, `path.1`, `path.2` の形式でローテーションします。

### stderr

コンソールやサービス起動時の即時確認向けです。  
UTC タイムスタンプ付きの 1 行テキストで出力されます。

```text
2026-04-02 12:34:56.789 I application started
2026-04-02 12:34:56.790 D polling state dump
```

## 代表 API

### `com_util_logger_create`

トレースハンドルを作成します。  
初期名は実行ファイル名で、取得できない場合は `"unknown"` になります。

### `com_util_logger_set_name`

識別名を設定します。  
複数インスタンスを識別したい場合は識別番号付きの名前を使えます。

### `com_util_logger_set_os_level`

OS トレースのしきい値を設定します。

### `com_util_logger_set_file_level`

ファイル出力先、ファイル用しきい値、最大サイズ、世代数を設定します。  
ファイル出力を使う場合の入口です。

### `com_util_logger_set_stderr_level`

`stderr` 出力のしきい値を設定します。

### `com_util_logger_start` / `com_util_logger_stop`

出力の開始と停止を行います。  
設定変更は stopped 中、書き込みは started 中に行います。

### `com_util_logger_write` / `com_util_logger_writef`

通常のトレースメッセージを書き込みます。

### `com_util_logger_write_hex` / `com_util_logger_write_hexf`

バイナリデータを HEX テキストとして書き込みます。  
通信データやバッファ内容を確認したいときに使います。

## 使い方

呼び出し側は backend の違いを書き分けず、同じコードで利用できます。

```c
#include <com_util/trace/logger.h>

int main(void)
{
    com_util_logger_t *logger = com_util_logger_create();
    if (logger == NULL) {
        return 1;
    }

    com_util_logger_set_name(logger, "myapp", 0);
    com_util_logger_start(logger);

    com_util_logger_write(logger, COM_UTIL_LOG_LEVEL_INFO, "application started");
    com_util_logger_writef(logger, COM_UTIL_LOG_LEVEL_WARNING, "retry=%d", 3);

    com_util_logger_stop(logger);
    com_util_logger_destroy(logger);
    return 0;
}
```

ファイル出力を有効にする場合は、start 前に file sink を設定します。

```c
#include <com_util/trace/logger.h>

com_util_logger_t *logger = com_util_logger_create();

com_util_logger_set_name(logger, "myapp", 0);
com_util_logger_set_os_level(logger, COM_UTIL_LOG_LEVEL_WARNING);
com_util_logger_set_file_level(logger, "./logs/myapp.log",
                           COM_UTIL_LOG_LEVEL_INFO, 0, 0);
com_util_logger_set_stderr_level(logger, COM_UTIL_LOG_LEVEL_CRITICAL);
com_util_logger_start(logger);

com_util_logger_write(logger, COM_UTIL_LOG_LEVEL_INFO, "service ready");

com_util_logger_destroy(logger);
```

`max_bytes == 0` は既定値、`generations <= 0` も既定値として扱われます。

## プラットフォームごとの動作

### Windows

- OS トレースは ETW を使う
- `trace` 上位では ETW プロバイダ登録を共有する
- `stderr` とファイルは共通の書式で扱う

### Linux

- OS トレースは syslog を使う
- `stderr` とファイルは共通の書式で扱う
- syslog の facility や `ident` は内部で `trace` が管理する

## 注意点

- 設定関数は stopped 状態でのみ使えます
- メッセージ長には共通上限があり、長文は安全な範囲で切り詰められます
- HEX 出力も上限があり、収まらない場合は末尾を省略します
- ファイル出力はローカルファイルシステム向けです
- backend 固有の制約は各 backend README を参照してください

## backend ドキュメント

- `backends/etw/README.md`: Windows ETW backend
- `backends/file/README.md`: ファイル backend
- `backends/syslog/README.md`: Linux syslog backend
