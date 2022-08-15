set(COMPONENT_NAME trust_cta2045)

add_library(${COMPONENT_NAME} STATIC
    trust_cta2045.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
    cea2045_ucm
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${cea2045_ucm_INCLUDE_DIRS}
)