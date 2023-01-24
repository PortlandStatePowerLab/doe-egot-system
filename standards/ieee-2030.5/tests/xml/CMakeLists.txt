find_package(Boost REQUIRED)

add_executable (xml_tests
    main.cpp
    dcap_tests.cpp
    sdev_tests.cpp
    edev_tests.cpp
    rg_tests.cpp
    dstat_tests.cpp
    fsa_tests.cpp
    frp_tests.cpp 
    frq_tests.cpp
    sub_tests.cpp
    ntfy_tests.cpp
    rsps_tests.cpp
    rsp_tests.cpp
    tm_tests.cpp
    ps_tests.cpp
)

target_link_libraries(xml_tests gtest gtest_main SEP_Models XML_Validator Boost::boost utilities pthread)

target_include_directories(
    xml_tests PUBLIC 
    ${Boost_INCLUDE_DIRS}
    ${SEP_Models_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)