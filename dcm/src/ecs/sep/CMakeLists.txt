set(COMPONENT_NAME ecs_sep)

add_library(${COMPONENT_NAME} STATIC
  dcap.cpp
  fsa.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  flecs
  trust_https
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${flecs_INCLUDE_DIRS}
  ${trust_https_INCLUDE_DIRS}
)