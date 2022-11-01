# Find python and Boost - both are required dependencies
# find_package(PythonLibs 3 REQUIRED)
# find_package(Boost COMPONENTS python REQUIRED)

add_subdirectory(trust_xml)
add_subdirectory(trust_https)
add_subdirectory(trust_cta2045)
add_subdirectory(src)
add_subdirectory(tests)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/scripts/
)