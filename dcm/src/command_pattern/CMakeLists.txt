set(COMPONENT_NAME command_pattern)

add_library(${COMPONENT_NAME} STATIC
  dcm_commands.cpp 
  ecs_dcm.cpp 
  s_sim_invoker.cpp 
  simple_sim_receiver.cpp 
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https_client
  SEP::Model
  ecs_client
  dtm_msg_writer
  cta2045_receiver
  SEP::XML
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${ecs_client_INCLUDE_DIRS}
  ${https_client_INCLUDE_DIRS}
  ${dtm_msg_writer_INCLUDE_DIRS}
  ${cta2045_receiver_INCLUDE_DIRS}
  ${SEP_INCLUDES_DIRS}
)