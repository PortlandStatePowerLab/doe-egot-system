find_package(Boost REQUIRED)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(googletest)

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

target_link_libraries(xml_tests gtest gtest_main Model XML Boost::boost pthread)
target_include_directories(
    xml_tests PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${Boost_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)

add_custom_command(
    TARGET xml_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/bin
)
