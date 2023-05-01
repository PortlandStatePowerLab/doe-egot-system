add_subdirectory(ecs)

set(COMPONENT_NAME dcm)

add_executable (${COMPONENT_NAME}
    main.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    dcm_ecs
    trust_https
    utilities
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${dcm_ecs_INCLUDE_DIRS}
    ${trust_https_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)