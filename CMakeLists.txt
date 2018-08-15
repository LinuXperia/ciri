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

set(UVW_DEPS_DIR ${CMAKE_SOURCE_DIR}/deps/uvw)
include_directories(${UVW_DEPS_DIR}/src)

add_executable(nigiri main.cpp)

if(LIBUV_STATIC_LIBRARY)
    #Skip build
else()
    configure_file(cmake/in/libuv.in ${LIBUV_DEPS_DIR}/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${LIBUV_DEPS_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${LIBUV_DEPS_DIR})
endif()

target_link_libraries(nigiri PRIVATE Threads::Threads ${LIBUV_STATIC_LIBRARY})

