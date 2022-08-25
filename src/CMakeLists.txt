#
#
#

cmake_minimum_required(VERSION 3.21)

add_library(argparse)
target_sources(argparse PRIVATE
    argparse.cpp
)
target_include_directories(argparse PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
