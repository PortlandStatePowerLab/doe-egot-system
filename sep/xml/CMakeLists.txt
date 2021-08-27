include(FindXercesC)
find_package(XercesC REQUIRED)
find_package(Boost REQUIRED)

set(COMPONENT_NAME XML_Validator)
add_library(${COMPONENT_NAME} STATIC
    adapter.cpp
    xml_validator.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} SEP_Models Boost::boost ${XercesC_LIBRARY})

target_include_directories(
    ${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${SEP_Models_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIR}
)