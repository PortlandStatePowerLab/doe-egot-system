set(COMPONENT_NAME dtm_server)

add_library(${COMPONENT_NAME} STATIC
    dtm_server.cpp
)

# Set up the libraries and header search paths for this target
target_link_libraries(${COMPONENT_NAME} PUBLIC
    Boost::python 
    ${PYTHON_LIBRARIES} 
    utilities
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include> 
    ${Boost_INCLUDE_DIRS}
    ${utilities_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)