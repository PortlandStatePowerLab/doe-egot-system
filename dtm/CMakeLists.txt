cmake_minimum_required(VERSION 3.14)

# project variables
set(PROJECT_VERSION 1.0.0)
set(PROJECT_NAME DTM)
set(ALLOW_DUPLICATE_CUSTOM_TARGETS true)

# This is your project statement. You should always list languages;
project(
  ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  LANGUAGES CXX
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find python and Boost - both are required dependencies
find_package(PythonLibs 3 REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)

include(ExternalProject)
if (NOT TARGET ssl-ca)
  ExternalProject_Add (
    ssl-ca
    GIT_REPOSITORY https://github.com/PortlandStatePowerLab/ssl-ca.git
    GIT_TAG        main
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND COMMAND ${CMAKE_COMMAND} -E copy_directory
    <SOURCE_DIR>/root-ca ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/certs
  )
endif()

include(FetchContent)
FetchContent_Declare(
  DCM
  GIT_REPOSITORY https://github.com/PortlandStatePowerLab/doe-egot-dcm.git
  GIT_TAG        main
)

FetchContent_Declare(
  GSP
  GIT_REPOSITORY https://github.com/PortlandStatePowerLab/doe-egot-gsp.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(DCM GSP)

add_subdirectory(src)
add_subdirectory(tests)