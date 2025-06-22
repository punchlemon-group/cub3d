#!/bin/bash

# テスト用ディレクトリとプログラムの設定
TEST_DIR="$(dirname "$0")"
TEST_CASES_DIR="$TEST_DIR/test_cases"
EXPECTED_OUTPUT_DIR="$TEST_DIR/expected_output"
PROGRAM="./cub3D"

# 色の設定
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
RESET="\033[0m"

# テスト結果のカウンタ
PASSED=0
FAILED=0
TOTAL=0
MEMORY_LEAKS=0

# valgrindのオプションとフラグ
USE_VALGRIND=false
VALGRIND_LOG_DIR="$TEST_DIR/valgrind_logs"

# 使用方法を表示
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo "Options:"
    echo "  -v, --valgrind    Run tests with valgrind memory leak detection"
    echo "  -h, --help        Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                # Run normal tests"
    echo "  $0 --valgrind     # Run tests with valgrind"
}

# コマンドライン引数を解析
while [[ $# -gt 0 ]]; do
    case $1 in
        -v|--valgrind)
            USE_VALGRIND=true
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            usage
            exit 1
            ;;
    esac
done

# 前提条件をチェック
echo "Checking prerequisites..."

# プログラムの存在確認
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}Error: $PROGRAM not found${RESET}"
    echo "Please build the program first: make"
    exit 1
fi

# テストケースディレクトリの確認
if [ ! -d "$TEST_CASES_DIR" ]; then
    echo -e "${RED}Error: Test cases directory not found: $TEST_CASES_DIR${RESET}"
    exit 1
fi

# valgrindが利用可能かチェック
if [ "$USE_VALGRIND" = true ]; then
    if ! command -v valgrind &> /dev/null; then
        echo -e "${RED}Error: valgrind is not installed${RESET}"
        echo "Please install valgrind: sudo apt-get install valgrind"
        exit 1
    fi
    
    # valgrindログディレクトリを作成
    mkdir -p "$VALGRIND_LOG_DIR"
    echo -e "${YELLOW}Running tests with valgrind memory leak detection...${RESET}"
    echo "Valgrind logs will be saved to: $VALGRIND_LOG_DIR"
fi

# valgrindでプログラムを実行する関数
run_with_valgrind() {
    local test_file="$1"
    local log_file="$2"
    
    valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --log-file="$log_file" \
        --error-exitcode=42 \
        "$PROGRAM" "$test_file" 2>&1
}

# valgrindログを解析してメモリリークを検出
check_memory_leaks() {
    local log_file="$1"
    local test_name="$2"
    
    if [ ! -f "$log_file" ]; then
        echo -e "${RED}✗ VALGRIND ERROR${RESET}: Log file not found for $test_name"
        return 1
    fi
    
    # メモリリークの確認
    local definitely_lost=$(grep "definitely lost:" "$log_file" | grep -o '[0-9,]* bytes' | head -1 | tr -d ',')
    local possibly_lost=$(grep "possibly lost:" "$log_file" | grep -o '[0-9,]* bytes' | head -1 | tr -d ',')
    local still_reachable=$(grep "still reachable:" "$log_file" | grep -o '[0-9,]* bytes' | head -1 | tr -d ',')
    local error_summary=$(grep "ERROR SUMMARY:" "$log_file" | grep -o '[0-9]* errors' | head -1)
    
    # バイト数を抽出（空の場合は0に設定）
    definitely_lost=${definitely_lost:-0}
    possibly_lost=${possibly_lost:-0}
    
    if [ "$definitely_lost" != "0" ] || [ "$possibly_lost" != "0" ] || [[ "$error_summary" != "0 errors" ]]; then
        echo -e "${RED}✗ MEMORY LEAK${RESET}: $test_name"
        echo "  Definitely lost: $definitely_lost bytes"
        echo "  Possibly lost: $possibly_lost bytes"
        echo "  Still reachable: $still_reachable bytes"
        echo "  $error_summary"
        echo "  Full log: $log_file"
        MEMORY_LEAKS=$((MEMORY_LEAKS+1))
        return 1
    else
        echo -e "${GREEN}✓ NO LEAKS${RESET}: $test_name"
        return 0
    fi
}

# テスト関数
run_test() {
    local test_file="$1"
    local expected_output_file="$2"
    local test_name="$(basename "$test_file")"
    
    echo "Running test: $test_name"
    TOTAL=$((TOTAL+1))
    
    local output
    local exit_code
    local valgrind_log=""
    
    # valgrindを使用する場合とそうでない場合を分ける
    if [ "$USE_VALGRIND" = true ] && [[ "$test_file" == *"/invalid/"* ]]; then
        # invalidテストケースでvalgrindを使用
        valgrind_log="$VALGRIND_LOG_DIR/$(basename "$test_file").log"
        echo "Running with valgrind..."
        
        output=$(run_with_valgrind "$test_file" "$valgrind_log")
        exit_code=$?
        
        # valgrindのエラーコード42は除外して元のプログラムの終了コードを取得
        if [ $exit_code -eq 42 ]; then
            exit_code=1  # valgrindエラーの場合、通常は元のプログラムも失敗していると仮定
        fi
        
        # メモリリークチェック
        check_memory_leaks "$valgrind_log" "$test_name"
        
    elif [[ "$test_file" == *"/valid/"* ]]; then
        # 有効なマップファイルの場合：3秒でタイムアウト
        echo "Valid map test - using timeout..."
        
        # バックグラウンドでプログラムを実行
        $PROGRAM "$test_file" > /tmp/test_output_$$.txt 2>&1 &
        local pid=$!
        
        # 2秒待機してプロセスの状態をチェック
        sleep 2
        
        # プロセスがまだ動いている場合（レンダリング中）、正常と判断
        if kill -0 $pid 2>/dev/null; then
            # プロセスを終了
            kill $pid 2>/dev/null
            wait $pid 2>/dev/null
            
            # 有効なマップファイルの場合は成功と判断
            output=""
            exit_code=0
            echo "Process was running (rendering), considered successful"
        else
            # プロセスが既に終了している場合は出力を確認
            wait $pid
            exit_code=$?
            output=$(cat /tmp/test_output_$$.txt)
            echo "Process ended early, checking output..."
        fi
        
        # 一時ファイルを削除
        rm -f /tmp/test_output_$$.txt
    else
        # 無効なマップファイルの場合は通常通り実行
        output=$($PROGRAM "$test_file" 2>&1)
        exit_code=$?
    fi
    
    # 期待される出力を取得
    if [ -f "$expected_output_file" ]; then
        expected=$(cat "$expected_output_file")
        expected_exit_code=$(cat "$expected_output_file.exit" 2>/dev/null || echo "1")
        
        # 出力を比較
        if [ "$output" = "$expected" ] && [ "$exit_code" -eq "$expected_exit_code" ]; then
            echo -e "${GREEN}✓ PASSED${RESET}: $test_name"
            PASSED=$((PASSED+1))
        else
            echo -e "${RED}✗ FAILED${RESET}: $test_name"
            echo "Expected output:"
            echo "$expected"
            echo "Actual output:"
            echo "$output"
            echo "Expected exit code: $expected_exit_code"
            echo "Actual exit code: $exit_code"
            FAILED=$((FAILED+1))
        fi
    else
        echo -e "${RED}✗ ERROR${RESET}: Missing expected output file for $test_name"
        FAILED=$((FAILED+1))
    fi
    
    echo "---------------------------------"
}

# メインテスト実行部分
echo "==================================="
echo "Starting cub3D integration tests..."
echo "Test cases directory: $TEST_CASES_DIR"
echo "Expected output directory: $EXPECTED_OUTPUT_DIR"
echo "==================================="

# テストケースを検索して実行（サブシェルを避けるためにforループを使用）
if [ -d "$TEST_CASES_DIR" ]; then
    # .cubファイルを配列に格納
    TEST_FILES=($(find "$TEST_CASES_DIR" -name "*.cub" -type f | sort))
    
    if [ ${#TEST_FILES[@]} -eq 0 ]; then
        echo -e "${YELLOW}Warning: No .cub test files found in $TEST_CASES_DIR${RESET}"
        echo "Please create test case files with .cub extension"
        
        # ディレクトリ構造を表示
        echo "Current directory structure:"
        find "$TEST_CASES_DIR" -type f | head -10
    else
        echo "Found ${#TEST_FILES[@]} test files"
        
        # 各テストファイルを実行
        for test_file in "${TEST_FILES[@]}"; do
            # 期待される出力ファイルのパスを生成
            relative_path="${test_file#$TEST_CASES_DIR/}"
            expected_output_file="$EXPECTED_OUTPUT_DIR/${relative_path}"
            
            run_test "$test_file" "$expected_output_file"
        done
    fi
else
    echo -e "${RED}Error: Test cases directory does not exist: $TEST_CASES_DIR${RESET}"
    exit 1
fi

# テスト結果の表示
echo "==================================="
echo "Test results: $PASSED/$TOTAL passed"
if [ "$USE_VALGRIND" = true ]; then
    echo "Memory leak results: $MEMORY_LEAKS/$TOTAL tests had memory leaks"
fi

if [ $FAILED -eq 0 ] && [ $MEMORY_LEAKS -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${RESET}"
    if [ "$USE_VALGRIND" = true ]; then
        echo -e "${GREEN}No memory leaks detected!${RESET}"
    fi
else
    if [ $FAILED -gt 0 ]; then
        echo -e "${RED}$FAILED tests failed.${RESET}"
    fi
    if [ $MEMORY_LEAKS -gt 0 ]; then
        echo -e "${RED}$MEMORY_LEAKS tests had memory leaks.${RESET}"
        echo "Check valgrind logs in: $VALGRIND_LOG_DIR"
    fi
    exit 1
fi