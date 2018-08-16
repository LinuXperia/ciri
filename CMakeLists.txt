# cmake_minimum_required(VERSION <specify CMake version here>)
project(nigiri)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(LIBUV_DEPS_DIR ${CMAKE_SOURCE_DIR}/deps/libuv)
include_directories(${LIBUV_DEPS_DIR}/src/include)
find_library(LIBUV_STATIC_LIBRARY NAMES libuv.a libuv PATHS ${LIBUV_DEPS_DIR}/src PATH_SUFFIXES .libs Release NO_DEFAULT_PATH)
#find_library(LIBUV_SHARED_LIBRARY NAMES uv libuv PATHS ${LIBUV_DEPS_DIR}/src PATH_SUFFIXES .libs Release NO_DEFAULT_PATH)
if(NOT LIBUV_STATIC_LIBRARY)
    configure_file(cmake/in/libuv.in ${LIBUV_DEPS_DIR}/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${LIBUV_DEPS_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${LIBUV_DEPS_DIR})
    find_library(LIBUV_STATIC_LIBRARY NAMES libuv.a libuv PATHS ${LIBUV_DEPS_DIR}/src PATH_SUFFIXES .libs Release NO_DEFAULT_PATH)
endif()

set(JSONC_DEPS_DIR ${CMAKE_SOURCE_DIR}/deps/json-c)
include_directories(${JSONC_DEPS_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${JSONC_DEPS_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${JSONC_DEPS_DIR})
find_library(JSONC_LIBRARY NAMES json-c.a json-c PATHS ${JSONC_DEPS_DIR} Release NO_DEFAULT_PATH)

add_executable(nigiri nigiri.c)

link_directories(${JSONC_DEPS_DIR}/src/.libs)
target_link_libraries(nigiri PRIVATE Threads::Threads ${LIBUV_STATIC_LIBRARY} ${JSONC_LIBRARY})

