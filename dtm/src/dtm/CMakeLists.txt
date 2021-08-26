set(COMPONENT_NAME dtm_server)

add_library(${COMPONENT_NAME} STATIC
    dtm_server.cpp
)

# Set up the libraries and header search paths for this target
target_link_libraries(${COMPONENT_NAME} PUBLIC
    Boost::python 
    ${PYTHON_LIBRARIES} 
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include> 
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

# install the target and create export-set
install(
    TARGETS ${COMPONENT_NAME}
    EXPORT ${COMPONENT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(
    EXPORT ${COMPONENT_NAME}Targets
    FILE ${COMPONENT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake
)