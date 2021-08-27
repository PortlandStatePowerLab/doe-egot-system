add_subdirectory(https)
add_subdirectory(ecs)

set(COMPONENT_NAME dcm)

add_executable(${COMPONENT_NAME} 
  main.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https
  SEP_Models
  XML_Validator
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  ${https_INCLUDE_DIRS}
  ${SEP_Models_INCLUDES_DIRS}
  ${XML_Validator_INCLUDES_DIRS}
)