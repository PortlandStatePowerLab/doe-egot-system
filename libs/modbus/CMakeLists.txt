set(COMPONENT_NAME modbus_tcp)

add_library(${COMPONENT_NAME} STATIC
    modbus_tcp.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
    modbus
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)