########## COMMON SETTINGS ##########

###
# compilation options
###
IF (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /O2 /bigobj")

    # was causing conflics with gtest build
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})

    IF ("${MSVC_RUNTIME_LIBRARY_CONFIG}" STREQUAL "")
        set(MSVC_RUNTIME_LIBRARY_CONFIG "/MD")
    ENDIF()

    foreach (flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
        IF ("${MSVC_RUNTIME_LIBRARY_CONFIG}" STREQUAL "/MT")
            string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        ELSEIF ("${MSVC_RUNTIME_LIBRARY_CONFIG}" STREQUAL "/MD")
            string(REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
        ELSE ()
            string(REPLACE "/MD" "${MSVC_RUNTIME_LIBRARY_CONFIG}" ${flag_var} "${${flag_var}}")
            string(REPLACE "/MT" "${MSVC_RUNTIME_LIBRARY_CONFIG}" ${flag_var} "${${flag_var}}")
        ENDIF()
    endforeach()

    add_definitions(-D_UNICODE)
    add_definitions(-DUNICODE)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
ELSE ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra -O3")
ENDIF (WIN32)