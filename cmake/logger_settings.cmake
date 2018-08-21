ExternalProject_Add("logger_dep"
        GIT_SUBMODULES ""
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps"
        CMAKE_ARGS "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-Wno-dev"
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        CMAKE_ARGS "-DCMAKE_C_FLAGS=${FORWARD_FLAGS}"
        INSTALL_COMMAND cmake -E echo "Skipping install step."
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/logger")

include_directories(${CMAKE_SOURCE_DIR}/deps/logger/include)

target_link_libraries(${CMAKE_PROJECT_NAME} logger)

add_dependencies(${CMAKE_PROJECT_NAME} logger_dep)