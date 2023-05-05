set(COMPONENT_NAME gsp)
add_subdirectory(ecs)
add_subdirectory(https)

add_executable(${COMPONENT_NAME}
    main.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    Boost::boost
    Boost::filesystem
    SEP_Models
    https_server 
    XML_Validator
    gsp_ecs
    utilities
    pthread
)

target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${Boost_INCLUDE_DIRS}
    ${SEP_Models_INCLUDE_DIRS}
    ${https_server_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
    ${gsp_ecs_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)