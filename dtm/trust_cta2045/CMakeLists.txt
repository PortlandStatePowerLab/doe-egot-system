set(COMPONENT_NAME trust_cta2045)

add_library(${COMPONENT_NAME} STATIC
    trust_ucm.cpp
    trust_device.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
    cea2045
    https_client
    trust_xml
    utilities
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${cea2045_SOURCE_DIR}/cea2045
    ${https_client_INCLUDE_DIRS}
    ${trust_xml_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)