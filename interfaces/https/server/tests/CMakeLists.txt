set(COMPONENT_NAME https_server_tests)

add_executable (${COMPONENT_NAME}
    main.cpp
    server.cpp
)

target_link_libraries(${COMPONENT_NAME} gtest gtest_main https_server pthread)

target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${googletest_INCLUDE_DIRS}
    ${https_server_INCLUDE_DIRS}
)