# You should always specify a range with the newest
# and oldest tested versions of CMake. 
cmake_minimum_required(VERSION 3.18)

# This is your project statement. You should always list languages;
project(EGoT VERSION 0.1.0 LANGUAGES CXX)

# fetch remote packages for development
find_package(Boost REQUIRED python filesystem)
find_package(Python3 COMPONENTS Interpreter Development)


# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was added in CMake 3.14; simpler usage
include(FetchContent)

include(FindXercesC)

include(FindGTest)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v3.2.1
)

FetchContent_MakeAvailable(flecs)

add_subdirectory(libs)

# install resources for programs
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/
    ${CMAKE_BINARY_DIR}/bin/
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/ssl/root-ca/
    ${CMAKE_BINARY_DIR}/bin/root-ca/
)