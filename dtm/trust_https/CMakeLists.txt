set(COMPONENT_NAME trust_https)

add_library(${COMPONENT_NAME} STATIC
  trust_https.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https_client
  Boost::boost
  utilities
  XML_Validator
  trust_xml
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${https_client_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${utilities_INCLUDE_DIRS}
  ${XML_Validator_INCLUDE_DIRS}
  ${trust_xml_INCLUDE_DIRS}
)