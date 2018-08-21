configure_file(cmake/in/lmdb.in ${CMAKE_SOURCE_DIR}/deps/lmdb/libraries/liblmdb/CMakeLists.txt COPYONLY)

ExternalProject_Add("lmdb_dep"
        GIT_SUBMODULES ""
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps"
        CMAKE_ARGS "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-Wno-dev"
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        CMAKE_ARGS "-DCMAKE_C_FLAGS=${FORWARD_FLAGS}"
        INSTALL_COMMAND cmake -E echo "Skipping install step."
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/lmdb/libraries/liblmdb")

include_directories(${CMAKE_SOURCE_DIR}/deps/lmdb/libraries/liblmdb)

target_link_libraries(${CMAKE_PROJECT_NAME} lmdb)

add_dependencies(${CMAKE_PROJECT_NAME} lmdb_dep)