find_package(Boost REQUIRED)

add_executable (xml_tests
    main.cpp
    device_capability_tests.cpp
    self_device_tests.cpp
)

target_link_libraries(xml_tests gtest gtest_main SEP_Models XML_Validator Boost::boost pthread)

target_include_directories(
    xml_tests PUBLIC 
    ${Boost_INCLUDE_DIRS}
    ${SEP_Models_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)