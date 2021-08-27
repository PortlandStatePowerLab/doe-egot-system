set(COMPONENT_NAME dcm_testing)

add_executable (${COMPONENT_NAME}
    main.cpp
    https_tests.cpp
    ecs_tests.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    gtest 
    gtest_main 
    Boost::boost
    https
    ecs
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    ${https_INCLUDE_DIRS}
    ${ecs_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)