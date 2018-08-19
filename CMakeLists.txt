project(ciri)
cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
configure_file(${CMAKE_SOURCE_DIR}/cmake/in/config.json.in ${CMAKE_BINARY_DIR}/config.json)

find_package(Threads REQUIRED)
find_package(logger REQUIRED)
find_package(argtable3 REQUIRED)
find_package(jsonc REQUIRED)
find_package(libuv REQUIRED)
find_package(lmdb REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(PROJECT_SOURCE_DIR  ${CMAKE_SOURCE_DIR}/source/)
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.c)

include_directories(source)
add_executable(ciri ${PROJECT_SOURCE_FILES})

target_link_libraries(ciri PRIVATE
        Threads::Threads
        ${logger}
        ${argtable3}
        ${jsonc}
        ${libuv}
        ${lmdb})

target_compile_options(ciri PRIVATE -DLOGGER_ENABLE)
