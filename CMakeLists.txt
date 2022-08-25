#
#
#

cmake_minimum_required(VERSION 3.21)

project(argparse
    VERSION 0.1.0
    DESCRIPTION "parse command-line arguments in C++"
    LANGUAGES C CXX
)

# optional使いたかった
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ソースディレクトリ
add_subdirectory(src)

# 依存関係としてビルドされている場合は、tests/ を除外する
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(ARGPARSE_BUILD_TESTS "whether to build tests" ON)

    if(ARGPARSE_BUILD_TESTS)
        message(NOTICE "testing enabled")
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()
