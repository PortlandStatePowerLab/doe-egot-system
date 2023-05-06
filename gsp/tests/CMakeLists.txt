set(COMPONENT_NAME gsp_tests)

add_executable (${COMPONENT_NAME}
    main.cpp
    dcap_tests.cpp
    sdev_tests.cpp
    edev_tests.cpp
    edev_list_tests.cpp
    frp_list_tests.cpp 
    frp_tests.cpp 
    frq_list_tests.cpp 
    frq_tests.cpp 
    rg_tests.cpp
    dstat_tests.cpp
    fsa_tests.cpp
    sub_tests.cpp
    ntfy_tests.cpp
    rsp_tests.cpp
    rsps_tests.cpp
    tm_tests.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    gtest 
    gtest_main 
    Boost::boost
    Boost::filesystem
    https_server 
    https_client
    XML_Validator
    gsp_ecs
    utilities
    pthread)

target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${googletest_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${https_server_INCLUDE_DIRS}
    ${https_client_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
    ${gsp_ecs_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)