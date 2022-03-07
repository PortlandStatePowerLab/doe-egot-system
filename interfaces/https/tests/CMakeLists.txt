set(COMPONENT_NAME https_tests)

add_executable (${COMPONENT_NAME}
    main.cpp
    dcap_tests.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    gtest 
    gtest_main 
    https_server 
    https_client
    XML_Validator
    pthread)

target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${googletest_INCLUDE_DIRS}
    ${https_server_INCLUDE_DIRS}
    ${https_client_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
)