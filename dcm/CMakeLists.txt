cmake_minimum_required(VERSION 3.14)

# project variables
set(PROJECT_VERSION 1.0.0)
set(PROJECT_NAME egot)

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

# Find packages go here.
include(FetchContent)
include(ExternalProject)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master
)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v2.3.2
)

FetchContent_Declare(
  SEP
  GIT_REPOSITORY https://github.com/PortlandStatePowerLab/doe-egot-sep.git
  GIT_TAG        XMLAdapter
)

FetchContent_MakeAvailable(googletest flecs SEP)

ExternalProject_Add (
  ssl-ca
  GIT_REPOSITORY https://github.com/PortlandStatePowerLab/ssl-ca.git
  GIT_TAG        main
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND COMMAND COMMAND ${CMAKE_COMMAND} -E copy_directory
  <SOURCE_DIR>/root-ca ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# project dirs
add_subdirectory(src)
add_subdirectory(tests)