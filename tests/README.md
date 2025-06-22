 cub3D Integration Tests

このディレクトリには、cub3Dプログラムの統合テストが含まれています。

## テスト実行方法

### 基本的なテスト実行
```bash
./tests/integration/run_tests.sh
```

### メモリリーク検出付きテスト実行
```bash
./tests/integration/run_tests.sh --valgrind
```

### ヘルプの表示
```bash
./tests/integration/run_tests.sh --help
```

## 前提条件

- プログラムがビルド済みであること (`make`を実行)
- valgrindオプション使用時は`valgrind`がインストール済みであること

## テストケース構成

```
tests/integration/
├── test_cases/           # テストケースファイル（.cub）
│   ├── invalid/         # 無効なマップファイル
│   └── valid/           # 有効なマップファイル
├── expected_output/     # 期待される出力ファイル
└── valgrind_logs/       # valgrindログ（実行時に生成）
```

## テスト結果の見方

### 基本テスト
- `✓ PASSED`: テストが成功
- `✗ FAILED`: テストが失敗（期待される出力と異なる）
- `✗ ERROR`: 期待される出力ファイルが見つからない

### valgrindテスト（invalidテストのみ）
- `✓ NO LEAKS`: メモリリークなし
- `✗ MEMORY LEAK`: メモリリークを検出

## 最終結果

```bash
===================================
Test results: 17/17 passed
Memory leak results: 0/17 tests had memory leaks  # valgrind使用時のみ
All tests passed!
No memory leaks detected!                          # valgrind使用時のみ
```

## トラブルシューティング

### プログラムが見つからない
```bash
Error: ./cub3D not found
Please build the program first: make
```
→ `make`を実行してプログラムをビルドしてください

### valgrindが見つからない
```bash
Error: valgrind is not installed
Please install valgrind: sudo apt-get install valgrind
```
→ `sudo apt-get install valgrind`でvalgrindをインストールしてください

### メモリリークが検出された場合
詳細なログが`tests/integration/valgrind_logs/`に保存されます。
ファイル名は`<テストケース名>.log`の形式です。

## 注意事項

- validテストは2秒間プロセスが動作することを確認して成功とします
- valgrindはinvalidテストケースにのみ適用されます（validテストは描画処理で時間がかかるため）
- テスト実行中は一時ファイルが`/tmp/test_output_*.txt`に作成されますが、自動的に削除されます
