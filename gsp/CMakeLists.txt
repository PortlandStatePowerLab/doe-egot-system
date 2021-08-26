cmake_minimum_required(VERSION 3.14)

# project variables
set(PROJECT_VERSION 1.0.0)
set(PROJECT_NAME GSP)

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
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

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
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master
)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v2.3.2
)

FetchContent_MakeAvailable(googletest flecs)

# project dirs
add_subdirectory(src)
add_subdirectory(tests)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion 
)

configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION lib/cmake
)