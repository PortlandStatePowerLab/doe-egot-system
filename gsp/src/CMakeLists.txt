add_subdirectory(ecs)
add_subdirectory(https)

set(COMPONENT_NAME gsp)
add_executable(${COMPONENT_NAME}
    main.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https_server
  ecs_server
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC 
  ${https_server_INCLUDE_DIRS}
  ${ecs_server_INCLUDE_DIRS}
)


add_custom_command(
    TARGET ${COMPONENT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/bin
)