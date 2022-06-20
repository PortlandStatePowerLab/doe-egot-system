set(COMPONENT_NAME mock_go)

add_library(${COMPONENT_NAME} STATIC
    mock_go.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
    Boost::boost
    Boost::filesystem
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)