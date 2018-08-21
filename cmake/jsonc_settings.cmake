ExternalProject_Add("jsonc_dep"
        GIT_SUBMODULES ""
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps"
        CMAKE_ARGS "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-Wno-dev"
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        CMAKE_ARGS "-DCMAKE_C_FLAGS=${FORWARD_FLAGS}"
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/json-c")

include_directories(${CMAKE_SOURCE_DIR}/deps/include/json-c)

target_link_libraries(${CMAKE_PROJECT_NAME} json-c)

add_dependencies(${CMAKE_PROJECT_NAME} jsonc_dep)