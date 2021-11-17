# http://mariobadr.com/creating-a-header-only-library-with-cmake.html
set(COMPONENT_NAME SEP_Models)
add_library(${COMPONENT_NAME} INTERFACE)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_include_directories(
    ${COMPONENT_NAME} INTERFACE include/
)

add_subdirectory(xml)
add_subdirectory(tests)