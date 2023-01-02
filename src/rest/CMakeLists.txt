set(TARGET rest_server)

set(SOURCES
    rest_server.cpp
    request_handler.cpp

    http/method_handler.cpp
    http/simple_rest.cpp

    models/tables/users.cpp
)

set(LIBRARIES
    ${CONAN_LIBS}
)

add_library(${TARGET} ${SOURCES})
target_link_libraries(rest_server PRIVATE ${LIBRARIES})