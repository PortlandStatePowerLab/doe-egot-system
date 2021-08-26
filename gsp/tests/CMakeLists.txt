set(COMPONENT_NAME gsp_tests)

add_executable (${COMPONENT_NAME}
    main.cpp
    use_case_1.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    gtest 
    gtest_main 
    Boost::boost
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${Boost_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)