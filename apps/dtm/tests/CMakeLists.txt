set(COMPONENT_NAME trust_demo)

add_executable (${COMPONENT_NAME}
    demo.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    trust_https
    trust_cta2045
    https_server
    XML_Validator
    flecs_world
    utilities
    dtm_server
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${trust_https_INCLUDE_DIRS}
    ${https_server_INCLUDE_DIRS}
    ${XML_Validator_INCLUDE_DIRS}
    ${flecs_world_INCLUDE_DIRS}
    ${trust_cta2045_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
    ${dtm_server_INCLUDE_DIRS}
)