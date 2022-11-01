set(COMPONENT_NAME https_client)

add_library(${COMPONENT_NAME} STATIC
  client.cpp
  single_client.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  Boost::boost
  OpenSSL::SSL
  XML_Validator
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${Boost_INCLUDE_DIRS}
  ${OpenSSL_INCLUDE_DIRS}
  ${XML_Validator_INCLUDE_DIRS}
)