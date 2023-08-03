add_subdirectory(dtm)
add_subdirectory(dcm)
add_subdirectory(gsp)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/dtm/
    ${CMAKE_BINARY_DIR}/bin/
)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/me/
    ${CMAKE_BINARY_DIR}/bin/
)