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

# テストターゲットの構成
add_executable(argparse_test)
target_sources(argparse_test PRIVATE
    test_argparse.cpp
)
target_link_libraries(argparse_test PRIVATE
    argparse
    GTest::gtest_main
)
target_include_directories(argparse_test
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)

# テストの実行
gtest_discover_tests(argparse_test)
