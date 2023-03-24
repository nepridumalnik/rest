set(TARGET rest_server)

set(SOURCES
    rest_server.cpp

    http/request_handler.cpp
    http/controllers/user_get.cpp
    http/controllers/user_login.cpp
    http/controllers/user_register.cpp
    http/controllers/user_search.cpp

    http/models/users/users.cpp
    http/models/users/users_auth.cpp
    http/models/users/user_find_condition.cpp
    http/models/users/user_row.cpp
    http/models/users/user_auth_row.cpp

    resources/jsons.cpp
    resources/messages.cpp
    resources/connection_parameters.cpp
)

set(LIBRARIES
    ${CONAN_LIBS}
)

add_library(${TARGET} ${SOURCES})
target_link_libraries(rest_server PRIVATE ${LIBRARIES})