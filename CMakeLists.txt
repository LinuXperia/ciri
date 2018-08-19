# cmake_minimum_required(VERSION <specify CMake version here>)
project(ciri)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(logger REQUIRED)
find_package(argtable3 REQUIRED)
find_package(jsonc REQUIRED)
find_package(libuv REQUIRED)
find_package(lmdb REQUIRED)

include_directories(source)
set(PROJECT_SOURCE_DIR  ${CMAKE_SOURCE_DIR}/source/)
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.c)

add_executable(ciri ${PROJECT_SOURCE_FILES})

target_link_libraries(ciri PRIVATE
        Threads::Threads
        ${logger}
        ${argtable3}
        ${jsonc}
        ${libuv}
        ${lmdb})

target_compile_options(ciri PRIVATE -DLOGGER_ENABLE)
