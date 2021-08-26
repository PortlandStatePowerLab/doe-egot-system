set(COMPONENT_NAME demo)

add_executable (${COMPONENT_NAME}
    demo.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    Boost::boost
    DCM::https_client
    GSP::https_server
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

add_custom_command(
    TARGET ${COMPONENT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/bin
    ${PROJECT_SOURCE_DIR}/scripts/ ${CMAKE_BINARY_DIR}/bin
)