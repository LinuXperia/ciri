cmake_minimum_required(VERSION 3.1)
project(entangled)

#[[
if(MSVC)
    list(APPEND entangled_cflags /W4)
elseif(CMAKE_C_COMPILER_ID MATCHES "AppleClang|Clang|GNU")
    list(APPEND entangled_cflags -fvisibility=hidden --std=gnu89)
    list(APPEND entangled_cflags -Wall -Wextra -Wstrict-prototypes)
    list(APPEND entangled_cflags -Wno-unused-parameter)
endif()
]]

set(entangled_headers
        common/curl-p/digest.h
        common/curl-p/indices.h
        common/curl-p/trit.h
        #common/helpers/checksum.h
        common/helpers/digest.h
        common/helpers/pow.h
        #common/helpers/sign.h
        common/kerl/bigint.h
        common/kerl/converter.h
        #common/kerl/hash.h
        #common/kerl/kerl.h
        common/model/transaction.h
        common/network/components/broadcaster.h
        common/network/components/processor.h
        common/network/components/receiver.h
        common/network/components/requester.h
        common/network/components/responder.h
        common/network/iota_packet.h
        common/network/neighbor.h
        common/network/uri_parser.h
        common/pow/pow.h
        #common/sign/v2/iss.h.inc
        #common/sign/v2/iss_curl.h
        #common/sign/v2/iss_kerl.h
        common/trinary/add.h
        common/trinary/bct.h
        common/trinary/flex_trit.h
        common/trinary/ptrit_incr.h
        common/trinary/trit_array.h
        common/trinary/trit_byte.h
        common/trinary/trit_long.h
        common/trinary/trit_ptrit.h
        common/trinary/trit_tryte.h
        common/trinary/tryte_long.h
        utils/containers/lists/concurrent_list.h.inc
        utils/containers/lists/concurrent_list_neighbor.h
        utils/containers/lists/concurrent_list_trit_array.h
        utils/containers/queues/concurrent_queue.h.inc
        utils/containers/queues/concurrent_queue_packet.h
        utils/containers/queues/concurrent_queue_transaction_request.h
        utils/containers/queues/concurrent_queue_trit_array.h)

set(entangled_sources
        common/curl-p/curl_p.c
        common/curl-p/digest.c
        #common/helpers/checksum.c
        common/helpers/digest.c
        common/helpers/pow.c
        #common/helpers/sign.c
        common/kerl/bigint.c
        common/kerl/converter.c
        #common/kerl/hash.c
        #common/kerl/kerl.c
        common/model/transaction.c
        common/network/components/broadcaster.c
        common/network/components/processor.c
        common/network/components/receiver.c
        common/network/components/requester.c
        common/network/components/responder.c
        common/network/iota_packet.c
        common/network/neighbor.c
        common/network/uri_parser.c
        common/pow/pow.c
        #common/sign/v2/iss.c.inc
        #common/sign/v2/iss_curl.c
        #common/sign/v2/iss_kerl.c
        common/trinary/add.c
        common/trinary/bct.c
        common/trinary/flex_trit.c
        common/trinary/ptrit_incr.c
        common/trinary/trit_array.c
        common/trinary/trit_byte.c
        common/trinary/trit_long.c
        common/trinary/trit_ptrit.c
        common/trinary/trit_tryte.c
        common/trinary/tryte_long.c
        utils/containers/lists/concurrent_list.c.inc
        utils/containers/lists/concurrent_list_neighbor.c
        utils/containers/lists/concurrent_list_trit_array.c
        utils/containers/queues/concurrent_queue.c.inc
        utils/containers/queues/concurrent_queue_packet.c
        utils/containers/queues/concurrent_queue_transaction_request.c
        utils/containers/queues/concurrent_queue_trit_array.c)


include_directories(${CMAKE_SOURCE_DIR})

add_library(entangled STATIC ${entangled_sources})
target_compile_options(entangled PRIVATE -DLOGGER_ENABLE)
target_compile_definitions(entangled PRIVATE ${entangled_defines})
target_compile_options(entangled PRIVATE ${entangled_cflags})
#target_include_directories(entangled PRIVATE ${entangled_headers})
#target_link_libraries(entangled_a ${entangled_libraries})

install(FILES ${entangled_headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/entangled)

#[[
if(UNIX)
    set(includedir ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
    set(libdir ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
    set(prefix ${CMAKE_INSTALL_PREFIX})
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    #install(TARGETS entangled LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install(TARGETS entangled_a ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
]]