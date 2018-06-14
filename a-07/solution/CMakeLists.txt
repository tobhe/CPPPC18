cmake_minimum_required(VERSION 3.8)

project(a-07)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
add_compile_options (-Wall -Wextra -Wpedantic -fPIC -Wfatal-errors)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable( has_sum
  ${CMAKE_SOURCE_DIR}/has_sum.cc
  )

target_include_directories( has_sum
  PRIVATE
  ${CMAKE_SOURCE_DIR}
  )
