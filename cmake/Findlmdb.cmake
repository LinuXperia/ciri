set(LMDB_DEPS_DIR ${CMAKE_SOURCE_DIR}/deps/lmdb)
set(LMDB_SOURCE_DIR ${LMDB_DEPS_DIR}/libraries/liblmdb)
configure_file(cmake/in/gitignore.in ${LMDB_SOURCE_DIR}/.gitignore COPYONLY)
configure_file(cmake/in/lmdb.in ${LMDB_SOURCE_DIR}/CMakeLists.txt COPYONLY)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${LMDB_SOURCE_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${LMDB_SOURCE_DIR})
find_library(lmdb NAMES lmdb.a lmdb PATHS ${LMDB_SOURCE_DIR} Release NO_DEFAULT_PATH)
include_directories(${LMDB_SOURCE_DIR})