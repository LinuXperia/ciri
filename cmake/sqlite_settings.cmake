set(sqlite_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/deps/include)
set(sqlite_URL https://mirror.bazel.build/www.sqlite.org/2018/sqlite-amalgamation-3230100.zip)
set(sqlite_HASH SHA256=4239a1f69e5721d07d9a374eb84d594225229e54be4ee628da2995f4315d8dfc)
set(sqlite_BUILD ${CMAKE_SOURCE_DIR}/deps/sqlite)
set(sqlite_INSTALL ${CMAKE_SOURCE_DIR}/deps)

if(WIN32)
    set(sqlite_STATIC_LIBRARIES ${sqlite_INSTALL}/sqlite.lib)
else()
    set(sqlite_STATIC_LIBRARIES ${sqlite_INSTALL}/libsqlite.a)
endif()

set(sqlite_HEADERS
        "${sqlite_BUILD}/sqlite3.h"
        "${sqlite_BUILD}/sqlite3ext.h"
        )

if (WIN32)
    ExternalProject_Add("sqlite_dep"
            PREFIX sqlite
            URL ${sqlite_URL}
            URL_HASH ${sqlite_HASH}
            PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sqlite/CMakeLists.txt ${sqlite_BUILD}
            BUILD_BYPRODUCTS ${sqlite_STATIC_LIBRARIES}
            INSTALL_DIR ${sqlite_INSTALL}
            DOWNLOAD_DIR "${sqlite_BUILD}"
            SOURCE_DIR "${sqlite_BUILD}"
            CMAKE_CACHE_ARGS
            -DCMAKE_BUILD_TYPE:STRING=Release
            -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
            -DCMAKE_INSTALL_PREFIX:STRING=${sqlite_INSTALL}
            )

else()
    ExternalProject_Add("sqlite_dep"
            PREFIX sqlite
            URL ${sqlite_URL}
            URL_HASH ${sqlite_HASH}
            PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sqlite/CMakeLists.txt ${sqlite_BUILD}
            INSTALL_DIR ${sqlite_INSTALL}
            DOWNLOAD_DIR "${sqlite_BUILD}"
            SOURCE_DIR "${sqlite_BUILD}"
            CMAKE_CACHE_ARGS
            -DCMAKE_BUILD_TYPE:STRING=Release
            -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
            -DCMAKE_INSTALL_PREFIX:STRING=${sqlite_INSTALL}
            )

endif()

target_link_libraries(${CMAKE_PROJECT_NAME} sqlite)

add_dependencies(${CMAKE_PROJECT_NAME} sqlite_dep)
