add_subdirectory(dtm)

set(COMPONENT_NAME dtm)

add_executable(${COMPONENT_NAME} main.cpp)

# Set up the libraries and header search paths for this target
target_link_libraries(${COMPONENT_NAME} PUBLIC
    dtm_server
    utilities
    pthread
)
target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${dtm_server_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
)
