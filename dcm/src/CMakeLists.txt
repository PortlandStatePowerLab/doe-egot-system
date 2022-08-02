set(COMPONENT_NAME dcm)

add_executable(${COMPONENT_NAME} 
  main.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  SEP_Models
  XML_Validator
  cta2045_ucm
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  ${SEP_Models_INCLUDES_DIRS}
  ${XML_Validator_INCLUDES_DIRS}
  ${cta2045_ucm_INCLUDES_DIRS}
)