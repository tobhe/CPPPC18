cmake_minimum_required(VERSION 3.8)

project(a-07)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
add_compile_options (-Wall -Wextra -Wpedantic -fPIC -Wfatal-errors)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.2.0)
    message (FATAL_ERROR "GNU g++ 7.2.0 or later required.")
  endif ()
else ()
  message (FATAL_ERROR "Only GNU gcc (7.2.0+) compiles this (because gcov).")
endif ()


add_executable( log
  ${CMAKE_SOURCE_DIR}/log.cc
)

find_package( Threads )

add_executable( chunks
  ${CMAKE_SOURCE_DIR}/chunks.cc
  )

add_executable(semantic_surprise
  ${CMAKE_SOURCE_DIR}/semantic_surprise.cc
  )

add_executable(threads
  ${CMAKE_SOURCE_DIR}/threads.cc
  )

target_link_libraries(threads
  ${CMAKE_THREAD_LIBS_INIT}
  )
