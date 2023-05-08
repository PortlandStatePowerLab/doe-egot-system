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

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v3.2.1
)

FetchContent_MakeAvailable(googletest flecs)

add_subdirectory(utilities)
# add_subdirectory(standards)
# add_subdirectory(ecs)
# add_subdirectory(interfaces)
# add_subdirectory(dtm)
# add_subdirectory(dcm)
# add_subdirectory(gsp)


# install resources for programs
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_CURRENT_SOURCE_DIR}/ssl/root-ca/
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/root-ca
)