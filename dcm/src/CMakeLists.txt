add_subdirectory(https)
add_subdirectory(ecs)

set(COMPONENT_NAME dcm)

add_executable(${COMPONENT_NAME} 
  main.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https
  SEP::Model
  SEP::XML
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  ${https_INCLUDE_DIRS}
  ${SEP_INCLUDES_DIRS}
)