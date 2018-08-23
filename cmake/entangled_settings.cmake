set(entangled_BUILD ${CMAKE_SOURCE_DIR}/deps/entangled)

ExternalProject_Add("entangled_dep"
        GIT_SUBMODULES ""
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cmake/entangled/CMakeLists.txt ${entangled_BUILD}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps"
        CMAKE_ARGS "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_SOURCE_DIR}/deps/lib"
        CMAKE_ARGS "-Wno-dev"
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        CMAKE_ARGS "-DCMAKE_C_FLAGS=${FORWARD_FLAGS}"
        CMAKE_ARGS "-DCMAKE_PROJECT_entangled_INCLUDE=${CMAKE_SOURCE_DIR}/cmake/fix_entangled.cmake"
        SOURCE_DIR "${entangled_BUILD}")

include_directories(${CMAKE_SOURCE_DIR}/deps/include/entangled)

target_link_libraries(${CMAKE_PROJECT_NAME} entangled)

add_dependencies(entangled_dep logger_dep)

add_dependencies(${CMAKE_PROJECT_NAME} entangled_dep)