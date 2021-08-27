add_subdirectory(dtm)

set(COMPONENT_NAME dtm)

add_executable(${COMPONENT_NAME} main.cpp)

# Set up the libraries and header search paths for this target
target_link_libraries(${COMPONENT_NAME} PUBLIC
    dtm_server
    pthread
)
target_include_directories(
    ${COMPONENT_NAME} PUBLIC 
    ${dtm_server_INCLUDE_DIRS}
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtm/
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtm/
)