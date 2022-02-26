set(COMPONENT_NAME https_client_tests)

add_executable (${COMPONENT_NAME}
    main.cpp
    client.cpp
)

target_link_libraries(${COMPONENT_NAME} gtest gtest_main https_client pthread)

target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${googletest_INCLUDE_DIRS}
    ${https_client_INCLUDE_DIRS}
)