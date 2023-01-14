set(TARGET rest_server)

set(SOURCES
    rest_server.cpp

    http/request_handler.cpp
    http/method_handler.cpp
    http/controllers/users_controller.cpp
    http/controllers/goods_controller.cpp

    models/tables/users.cpp
    models/tables/goods.cpp
)

set(LIBRARIES
    ${CONAN_LIBS}
)

add_library(${TARGET} ${SOURCES})
target_link_libraries(rest_server PRIVATE ${LIBRARIES})