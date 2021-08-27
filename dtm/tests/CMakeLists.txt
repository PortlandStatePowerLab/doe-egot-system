set(COMPONENT_NAME demo)

add_executable (${COMPONENT_NAME}
    demo.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    Boost::boost
    https_client
    https_server
    dtm_server
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${GSP_INCLUDE_DIRS}
    ${dtm_server_INCLUDE_DIRS}
    ${DCM_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)