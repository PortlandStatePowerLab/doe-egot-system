set(COMPONENT_NAME https_server)

add_library(${COMPONENT_NAME} STATIC
  https_server.cpp   
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC
  Boost::boost
  Boost::filesystem
  OpenSSL::SSL
  gsp_ecs
  SEP_Models
  utilities
  SEP_WADL
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
	${Boost_INCLUDE_DIRS}
  ${OpenSSL_INCLUDE_DIRS}
  ${gsp_ecs_INCLUDE_DIRS}
  ${SEP_Models_INCLUDE_DIRS}
  ${utilities_INCLUDE_DIRS}
  ${SEP_WADL_INCLUDE_DIRS}
)