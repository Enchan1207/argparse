#
#
#
cmake_minimum_required(VERSION 3.21)

# GoogleTestのフェッチと有効化
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest) # gtest_系関数の読み込み

# argvの生成に使う
include(FetchContent)
FetchContent_Declare(
    tinystr
    GIT_REPOSITORY https://github.com/Enchan1207/tinystr.git
    GIT_TAG v0.2.0
)
FetchContent_MakeAvailable(tinystr)

# テストターゲットの構成
add_executable(argparse_test)
target_sources(argparse_test PRIVATE
    test_argparse.cpp
    test_argument.cpp
)
target_link_libraries(argparse_test PRIVATE
    argparse
    tinystr
    GTest::gtest_main
)
target_include_directories(argparse_test
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)

# テストの実行
gtest_discover_tests(argparse_test)
