set(COMPONENT_NAME sunspec_modbus)

add_library(${COMPONENT_NAME} STATIC
    device.cpp
    modbus_adapter.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
    modbus_tcp
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${modbus_tcp_INCLUDE_DIRS}/include
)