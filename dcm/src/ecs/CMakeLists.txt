# http://mariobadr.com/creating-a-header-only-library-with-cmake.html
set(COMPONENT_NAME ecs)
add_library(${COMPONENT_NAME} INTERFACE)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_include_directories(
    ${COMPONENT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${COMPONENT_NAME} INTERFACE 
  flecs
  pthread
)