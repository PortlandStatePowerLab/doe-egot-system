find_package(Boost REQUIRED)

add_executable (xml_tests
    main.cpp
    active_power_test.cpp
    flow_reservation_request_test.cpp
    flow_reservation_response_test.cpp
    device_capability_test.cpp
    end_device_test.cpp
    self_device_test.cpp
    time_test.cpp
)

target_link_libraries(xml_tests gtest gtest_main SEP_Models XML_Validator Boost::boost pthread)

target_include_directories(
    xml_tests PUBLIC 
    ${Boost_INCLUDE_DIRS}
    ${SEP_Models_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)