
########## GLOBAL CONFIGURATION ##########

cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

project(ciri)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

########## MISC CONFIG ##########

include(misc)

########## PROJECT DIRECTORIES ##########

set(PROJECT_SOURCE_DIR  ${CMAKE_SOURCE_DIR}/source/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

########## PROJECT FILES ##########

file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.c)
include_directories("${PROJECT_SOURCE_DIR}")

########## DEPENDENCIES ##########

# Note: to refresh deps folder: git pull --recurse-submodules

include_directories(${CMAKE_SOURCE_DIR}/deps/include)
link_directories(${CMAKE_SOURCE_DIR}/deps/lib)

########## EXECUTABLE ##########

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCE_FILES})
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -DLOGGER_ENABLE -v)

########## COMPILATION SETTINGS ##########

#include(compilation_settings)

########## EXTERNAL LIBRARIES ##########

include(logger_settings)
include(argtable3_settings)
include(jsonc_settings)
include(libuv_settings)
include(lmdb_settings)
include(sqlite_settings)

########## INSTALL ##########

install(CODE "FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})")
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ DESTINATION bin USE_SOURCE_PERMISSIONS)

########## DEFAULT CONFIG ##########

configure_file(${CMAKE_MODULE_PATH}/in/config.json.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json)



