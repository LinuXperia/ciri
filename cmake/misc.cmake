if (ARCH MATCHES "32")
    set(CMAKE_C_FLAGS -m32 ${CMAKE_C_FLAGS})
    set(CMAKE_CXX_FLAGS -m32 ${CMAKE_CXX_FLAGS})
    set(FORWARD_FLAGS -m32 ${FORWARD_FLAGS})

elseif (ARCH MATCHES "64")
    set(CMAKE_C_FLAGS -m64 ${CMAKE_C_FLAGS})
    set(CMAKE_CXX_FLAGS -m64 ${CMAKE_CXX_FLAGS})
    set(FORWARD_FLAGS -m64 ${FORWARD_FLAGS})

else ()
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64 bits
        set (ARCH "64")
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
        # 32 bits
        set (ARCH "32")
    endif ()
endif ()