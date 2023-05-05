set(COMPONENT_NAME gsp_ecs)

add_library(${COMPONENT_NAME} STATIC
  rg.cpp
  dcap.cpp
  edev.cpp
  frq.cpp
  frp.cpp
  rsp.cpp
  time.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  flecs
  SEP_Models
  XML_Validator
  Boost::boost
  Boost::filesystem
  OpenSSL::SSL
  utilities
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${flecs_INCLUDE_DIRS}
  ${SEP_Models_INCLUDE_DIRS}
  ${XML_Validator_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${OpenSSL_INCLUDE_DIRS}
  ${utilities_INCLUDE_DIRS}
)