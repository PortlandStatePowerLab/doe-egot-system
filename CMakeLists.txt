# You should always specify a range with the newest
# and oldest tested versions of CMake.
cmake_minimum_required(VERSION 3.14)

# set version
set(PROJECT_VERSION 2.0.0)
set(PROJECT_NAME EGOT_ESI)

# This is your project statement. You should always list languages;
project(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# fetch remote packages for development
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v2.3.2
)

FetchContent_MakeAvailable(googletest flecs)

add_subdirectory(sep)
add_subdirectory(dcm)
add_subdirectory(gsp)
add_subdirectory(dtm)

# install resources for programs
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/sep_xml/
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sep_xml
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/ssl/root-ca/
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/root-ca
)
