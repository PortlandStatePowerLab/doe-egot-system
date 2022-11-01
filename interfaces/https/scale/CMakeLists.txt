set(COMPONENT_NAME ScalingServer)

add_executable (${COMPONENT_NAME}
    server.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    https_server 
    XML_Validator
    flecs_world
    utilities
    pthread)

target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${https_server_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
    ${flecs_world_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)

set(COMPONENT_NAME ScalingClient)

add_executable (${COMPONENT_NAME}
    client.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    https_client
    utilities
    pthread)

target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${https_client_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)