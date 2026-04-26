ifdef PLATFORM_LINUX
    # mock_com_util::Mock_com_util() コンストラクタが 127 個の ON_CALL を持つため、GCC の                                                                                                                                                                                                
    # -fvar-tracking-assignments が内部サイズ制限を超えてしまい、以下の備考が出力される。
    #
    # mock_com_util.cc:6:1: 備考: 変数追跡サイズ制限が -fvar-tracking-assignments を超過しています。
    # -fvar-tracking-assignments 無しで再度試みています
    #
    # --param=var-tracking-assignments-dom-ops-limit=<n> で上限値を引き上げると、追跡を継続しつつ
    # 備考を抑制することができる。
    CXXFLAGS += --param=var-tracking-assignments-dom-ops-limit=400000
endif
