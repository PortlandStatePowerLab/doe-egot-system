set(COMPONENT_NAME DCM_Comms)
add_library(${COMPONENT_NAME} STATIC
    gsp_client.cpp
    dtm_client.cpp 
    trust_cta2045_client.cpp
    trust_gsp_client.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  trust_xml
  cta2045_ucm
  utilities
  https_client
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${trust_xml_INCLUDE_DIRS}
  ${cta2045_ucm_INCLUDES_DIRS}
  ${utilities_INCLUDE_DIRS}
  ${https_client_INCLUDE_DIRS}
)