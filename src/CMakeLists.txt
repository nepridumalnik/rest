set(TARGET rest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    main.cpp

    rest_server.cpp
    request_handler.cpp

    http/method_handler.cpp
    http/simple_rest.cpp
)

set(LIBRARIES
    ${CONAN_LIBS}
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
