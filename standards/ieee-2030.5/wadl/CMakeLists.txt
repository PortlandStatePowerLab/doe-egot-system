find_package(Boost REQUIRED)

set(COMPONENT_NAME SEP_WADL)
add_library(${COMPONENT_NAME} STATIC
    wadl.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} XML_Validator utilities Boost::boost ${XercesC_LIBRARY})

target_include_directories(
    ${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${XML_Validator_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIR}
)