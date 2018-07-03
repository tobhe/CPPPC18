cmake_minimum_required(VERSION 3.8)

project(a-07)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
add_compile_options (-Wall -Wextra -Wpedantic -fPIC -Wfatal-errors)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable( log
  ${CMAKE_SOURCE_DIR}/log.cc
)

find_package( Threads )

add_executable(threads
  ${CMAKE_SOURCE_DIR}/threads.cc
  )

target_link_libraries(threads
  ${CMAKE_THREAD_LIBS_INIT}
  )
