set(logger_BUILD ${CMAKE_SOURCE_DIR}/deps/logger)

ExternalProject_Add("logger_dep"
        GIT_SUBMODULES ""
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cmake/logger/CMakeLists.txt ${logger_BUILD}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps"
        CMAKE_ARGS "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-Wno-dev"
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        CMAKE_ARGS "-DCMAKE_C_FLAGS=${FORWARD_FLAGS}"
        SOURCE_DIR "${logger_BUILD}")

#include_directories(${CMAKE_SOURCE_DIR}/deps/logger/include)

target_link_libraries(${CMAKE_PROJECT_NAME} logger)

add_dependencies(${CMAKE_PROJECT_NAME} logger_dep)