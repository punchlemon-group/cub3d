# cub3D Tests
## テスト実行方法

#### 基本的なテスト実行
```bash
./tests/integration/run_tests.sh
```

#### メモリリーク検出付きテスト実行
```bash
./tests/integration/run_tests.sh --valgrind
```
```bash
./tests/integration/run_tests.sh -v
```

## 前提条件

- プログラムがビルド済み (cub3Dがある)
- valgrindオプション使用時は**valgrind**がインストール済みである

## テストケース構成
```
tests/integration/
├── test_cases/           # テストケースファイル（.cub）
│   ├── invalid/         # 無効なマップファイル
│   └── valid/           # 有効なマップファイル
├── expected_output/     # 期待される出力ファイル
└── valgrind_logs/       # valgrindログ（実行時に生成）
```
## 注意事項

- validテストは2秒間プロセスが動作することを確認して成功としてる
- valgrindはinvalidテストケースにのみ適用してる
- テスト実行中は一時ファイルが`/tmp/test_output_*.txt`に作成て、自動的に削除される