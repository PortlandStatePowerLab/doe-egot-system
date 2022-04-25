set(COMPONENT_NAME flecs_world)

add_library(${COMPONENT_NAME} STATIC
  world.cpp
  access_module.cpp
  sep_common_module.cpp
  sep_smart_energy_module.cpp
  sep_support_module.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  flecs
  SEP_Models
  XML_Validator
  Boost::boost
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${flecs_INCLUDE_DIRS}
  ${SEP_Models_INCLUDE_DIRS}
  ${XML_Validator_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)